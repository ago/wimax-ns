/**************************************************************************
 Copyright (c) 2007-2008, Intel Corporation. All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:

  1. Redistributions of source code must retain the above copyright notice,
     this list of conditions and the following disclaimer.

  2. Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.

  3. Neither the name of the Intel Corporation nor the names of its
     contributors may be used to endorse or promote products derived from
     this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 POSSIBILITY OF SUCH DAMAGE.

***************************************************************************/
#include "wimax_osal_primitives.h"
#include "wimax_osal_string.h"


#include "DnDUtils.h"
//#include "SVNDISUIO_ioctls.h"
#include "TraceLogger.h"
#include "L3L4CommonDefines.h"
#include "wmxSDK_DnD_Cmn.h"
#include "TraceModule.h"
#include "L4ConfigurationManager.h"
#include "Act.h"
//#include "DeviceUtils.h"
#include "L4BufMan_L4Common.h"

//********************* Defines ****************************
#define SUBSYSTEM_MAX_BUF		8192 //8k
#define OUTPUT_BUF_SIZE			(2*SUBSYSTEM_MAX_BUF)
#define MAX_BUF_LEN				8192
#define NUMBER_OF_EVENTS		2

//********************* static variables *******************
static char				*parsingBuffer;
static int				copyPtr	= 0;
static pDndUtilsMsgCB_t pDnDUtilsMsgCb = NULL;
static postDnDUtilsMonitorCb postDnDUtilsFunc = NULL;
static BOOL				isThreadSuspended = TRUE;
static BOOL				isDriverBridge = FALSE;

static tUtilityFunctions *utilFn;

static int	dndUtils_SectionBufferSize(int startIndex)
{
	// there is no problem calling this method because it is called after we check that the buffer wasn't overrun
	int sizeBytes,sizeBits;
	BM_TraceLoggerMsgData_buffer_GET_SIZE(parsingBuffer + startIndex, sizeBytes, sizeBits);
	return sizeBytes + sizeBits/8;
}

static int	dndUtils_SectionSize(int startIndex, int bufferLength)
{
	int val;

	if (startIndex + 16 > bufferLength) // if we can't even read the length field
	{
		val = -1;
	}
	else // we can read the length field
	{
		BM_TraceLoggerMsgData_GET_BYTES_SIZE(parsingBuffer + startIndex, val);
		//16 - The size of the start composite
		//8 - The size of the end composite
		//We assert that we are able to approach the end barker even if the length is corrupted.
		//if (val + 16 + 8 > OUTPUT_BUF_SIZE)
		//{
		//	val = -1;
		//}
	}
	return val;
}

static BOOL dndUtils_IsStartOfSection(int startIndex)
{
	int val;
	BM_TraceLoggerMsgData_start_barker_GET(parsingBuffer + startIndex, val);
	if (val == NDIS_LOGGER_START_BARKER)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

static BOOL dndUtils_DataWasntOverrun(int startIndex)
{
	// here i don't check if the end index is in the buffer because it was checked in the "if"
	// question before it enters this method
	int endString;
	int startSeqCounter;
	int endSeqCounter;

	BM_TraceLoggerMsgData_end_barker_GET(parsingBuffer + startIndex, endString);
	BM_TraceLoggerMsgData_start_seqCounter_GET(parsingBuffer + startIndex, startSeqCounter);
	BM_TraceLoggerMsgData_end_seqCounter_GET(parsingBuffer + startIndex, endSeqCounter);

	if ((endString == NDIS_LOGGER_END_BARKER) && (startSeqCounter == endSeqCounter))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

static int	dndUtils_FindStartIndexWithoutSize(int currentIndex, int bufferLength) // currentIndex is the start index of the previous section
{
	// 'FindNextStartIndex' is given the current index, and it searches for the next buffer.
	// if it finds it, it returns the index in the array. otherwise, it returns -1.
	int ret = -1;
	int i;
	for (i=currentIndex + 1; i< bufferLength - 3; i++)
	{
		//if (dndUtils_IsStartOfSection(i, parsingBuffer))
		if (dndUtils_IsStartOfSection(i))
		{
			return i;
		}
	}
	return ret;
}

static void dndUtils_CreateOverrunBuff(UINT8 * buff)
{
	OSAL_ZeroMemory(buff, HEADER_SIZE);		
	L4BM_SetOpcode(buff, OVERRUN_FAKE_L4_OPCODE);
}

static int	dndUtils_FindStartIndexWithSize(int currentIndex, int bufferLength)
{
	// first we check if this is really the start of a section:
	if (dndUtils_IsStartOfSection(currentIndex))
	{
		int sizeOfSection = dndUtils_SectionSize(currentIndex, bufferLength);
		if (sizeOfSection == -1) // couldn't find the "length" field - for sure the will be no more start buffers
		{
			return -1;
		}
		if (currentIndex + sizeOfSection + 4 > bufferLength) // if we can't read the next sections start barker
		{
			return -1;
		}
		else
		{
			if(dndUtils_IsStartOfSection(currentIndex + sizeOfSection))
			{
				return currentIndex + sizeOfSection;
			}
			else // it it not too large, and there is no start tag - data was overridden
			{
				char overrunBuff[HEADER_SIZE];
				dndUtils_CreateOverrunBuff((UINT8*)overrunBuff);

				//numberOfLostMessagesRaised++;
				if (NULL != postDnDUtilsFunc)
				{
					postDnDUtilsFunc(0);
				}

				pDnDUtilsMsgCb(overrunBuff, HEADER_SIZE);

				return dndUtils_FindStartIndexWithoutSize(currentIndex, bufferLength);
			}
		}
	}
	else // if it is not the start we go to the start
	{
		char overrunBuff[HEADER_SIZE];
		dndUtils_CreateOverrunBuff((UINT8*)overrunBuff);

		if (NULL != postDnDUtilsFunc)
		{
			postDnDUtilsFunc(0);
		}

		pDnDUtilsMsgCb(overrunBuff, HEADER_SIZE);
		return dndUtils_FindStartIndexWithoutSize(currentIndex, bufferLength);
	}
}

static void dndUtils_ParseBuffer(int bufferLength, int *location)
{
	// 'dndUtils_ParseBuffer' parses the "parsingBuffer"
	// it gets as a single parameter the buffer length.
	// This length is the length that was read from the memory + the data that remained from the 
	// previous read action, and was not read till the end (didn't find any 'end' marker).

	int ptr				= 0;
	int amountToMove	= 0;
	int compositeSize	= 0;
	byte *addressToMove;

	TRACE(TR_MOD_DND_AGENT, TR_SEV_INFO, "[dndUtils_ParseBuffer]: Trying to parse %d bytes at location %d", bufferLength, location);

	copyPtr = *location;
	if (isThreadSuspended)
	{
		return;
	}
	// first we find the start index of the first section
	ptr = dndUtils_FindStartIndexWithoutSize(-1, bufferLength); // we start looking from the beginning
	if (ptr != -1) // we found the start index in the required length
	{
		compositeSize = dndUtils_SectionSize(ptr, bufferLength);
	}

	// while we don't pass the read data and the whole data is in the buffer
	while ((ptr != -1) && (compositeSize != -1) && ((ptr + compositeSize) <= bufferLength))
	{
		if (dndUtils_DataWasntOverrun(ptr))
		{
			void *newBuf, *outPtr;
			int outBitoff;
			int dataSize;

			// send the section's buffer to parsing
			dataSize = dndUtils_SectionBufferSize(ptr);
			BM_TraceLoggerMsgData_buffer_GET_POS(parsingBuffer + ptr, outPtr, outBitoff);
			newBuf = (void*)((size_t)outPtr + outBitoff/8);

			// Update the monitor
			if (NULL != postDnDUtilsFunc)
			{
				postDnDUtilsFunc(dataSize);
			}

			// this data will be written to the queue
			pDnDUtilsMsgCb(newBuf, dataSize);

			// find the next buffer
			ptr = dndUtils_FindStartIndexWithSize(ptr, bufferLength); // next pointer
		}
		else
		{
			char overrunBuff[HEADER_SIZE];
			dndUtils_CreateOverrunBuff((UINT8*)overrunBuff);

			if (NULL != postDnDUtilsFunc)
			{
				postDnDUtilsFunc(0);
			}

			pDnDUtilsMsgCb(overrunBuff, HEADER_SIZE);

			ptr = dndUtils_FindStartIndexWithoutSize(ptr, bufferLength); // next pointer
		}
		if (ptr != -1)
		{
			compositeSize = dndUtils_SectionSize(ptr, bufferLength); // next buffer size
		}
	}

	// now we passed the buffer size
	// this remaining data will be moved to the beginning of the buffer:
	if (ptr > -1)
	{
		amountToMove = bufferLength - ptr;
		addressToMove = (byte*)parsingBuffer + ptr;
		memmove(parsingBuffer, addressToMove, amountToMove);
		copyPtr = amountToMove;
		TRACE(TR_MOD_DND_AGENT, TR_SEV_INFO, "%d bytes were parsed", ptr);
	}
	else // if no start ptr was found, no data will be moved
	{
		copyPtr = 0;
		TRACE(TR_MOD_DND_AGENT, TR_SEV_INFO, "The whole buffer (%d bytes) was parsed", bufferLength);
	}

	*location = copyPtr;
}

//********************** public methods ********************
BOOL DnDUtils_IsDsim()
{
	char deviceWorking[64];

	L4Configurations_getDriverMode((char *)deviceWorking);

	if (FALSE == OSAL_stricmp("dSim", deviceWorking))
	{
		return TRUE;
	}

	return FALSE;
}

BOOL DnDUtils_IsRemote()
{
	char deviceWorking[64];

	if (L4Configurations_getDriverMode((char *)deviceWorking))
	{
		if (0 == OSAL_stricmp("remote", deviceWorking))
		{
			return TRUE;
		}
	}
	return FALSE;
}

BOOL DnDUtils_IsDriver()
{
	return ((!DnDUtils_IsDsim()) && (!DnDUtils_IsRemote()));
}


void PrepForAddToQueue(int dataLength, int *location)
{
	if (pDnDUtilsMsgCb != NULL)
		pDnDUtilsMsgCb(location, dataLength);
}

BOOL DnDUtils_Init(pDndUtilsMsgCB_t pMsgCb, BOOL isBridge, tUtilityFunctions *UtilFn, BOOL bSendRemote)
{
	TRACE(TR_MOD_DND_AGENT, TR_SEV_NOTICE, "DnDUtils_Init(IN), bSendRemote: %d.", bSendRemote);

	isDriverBridge = isBridge;
	utilFn = UtilFn;
	
	if(NULL != pMsgCb)
	{
		pDnDUtilsMsgCb = pMsgCb;
	}
	else
	{
		TRACE(TR_MOD_DND_AGENT, TR_SEV_ERR, "[DnDUtils_Init]Initialize Failed: DnD Utils CB is NUL");
		return FALSE;
	}

	DnDUtils_SuspendThread();
	//register on traces indication:
	if ( bSendRemote )
		utilFn->tpfnSetTraceIndicatiosCB(PrepForAddToQueue, &parsingBuffer);
	else
		utilFn->tpfnSetTraceIndicatiosCB(dndUtils_ParseBuffer, &parsingBuffer);

	return TRUE;
}

BOOL DnDUtils_Finalize()
{
	TRACE(TR_MOD_DND_AGENT, TR_SEV_NOTICE, "DnDUtils_Finalize(IN)");	

	//register on traces indication:
	if (utilFn != NULL)
	{
		utilFn->tpfnSetTraceIndicatiosCB(NULL, &parsingBuffer);
	}

	//We need to signal the thread to stop
	//first start it in case it is suspended
	DnDUtils_ResumeThread();

	//Free CB
	DnDUtils_UnRegisterPostMessage();

	//finalize the callback method
	pDnDUtilsMsgCb = NULL;

	TRACE(TR_MOD_DND_AGENT, TR_SEV_NOTICE, "DnDUtils_Finalize(OUT)");
	return TRUE;
}

BOOL DnDUtils_SuspendThread()
{
	if (FALSE == isThreadSuspended)
	{
		isThreadSuspended = TRUE;		
	}

	return TRUE;
}

BOOL DnDUtils_ResumeThread()
{
	if (TRUE == isThreadSuspended)
	{
		isThreadSuspended = FALSE;			
	}

	return TRUE;
}

void DnDUtils_RegisterPostMessage(postDnDUtilsMonitorCb cbFunc)
{
	if (NULL == cbFunc)
	{
		return;
	}

	postDnDUtilsFunc = cbFunc;
}

void DnDUtils_UnRegisterPostMessage()
{
	postDnDUtilsFunc = NULL;
}
