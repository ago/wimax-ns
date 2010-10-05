/**************************************************************************
Copyright (c) 2007-2009, Intel Corporation. All rights reserved.

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
#include <unistd.h>
#include <stdlib.h>
#include "wimax_osal_primitives.h"

#include "Messenger.h"

#include "CommonServices.h"
#include "L5Common.h"
#include "Queue.h"
#include "TraceModule.h"

#define MAX_SEQ_NUM 0x3fffffff // leaving two MSBs empty to assign priority level
#define PRIORITY_OFFSET ((sizeof(UINT32) * 8)  - 2) //2 bits are required to represent REQUEST_PRIORITY values
#define NUM_QUEUES 3

typedef struct _MSNGR_ELEM
{
	InternalHandler internalHandler;
	UINT32 internalRequestID;
	UINT32 bufferLength;
	size_t seqNum;
	void *buffer;//the start of the buffer
} MSNGR_ELEM, *pMSNGR_ELEM;


static OSAL_mutex_t g_msng_MutexQ;;
static OSAL_event_t g_msng_hIndicationEnqueuedEvent;
static OSAL_event_t g_msng_hStopIndsConsThreadEvent;
static OSAL_thread_t g_msng_hIndicationsConsumerThread;
static OSAL_event_t g_msng_hCanStop;

static char* REQUEST_PRIORITYStr[] = {	"High", "Medium", "Low"};

//static Queue g_msng_highPriorityIndicationsQueue;
//static Queue g_msng_mediumPriorityIndicationsQueue;
//static Queue g_msng_lowPriorityIndicationsQueue;

static Queue g_QueuesArr[NUM_QUEUES]; 
static OSAL_critical_section g_CrtSec;
//g_SequenceNumber consists of 30 LSBs that define the sequence number and two MSBs that define the 
//priority of the message.
//Initialized to zero. Zero indicates an invalid sequence number.
//According to these 2 MSBs we decide in which queue to search for the message.
//where as HIGH is 0, MEDIUIM - 1 and LOW - 2 - values are according to the REQUEST_PRIORITY enum
//See CalcSeqNum() for more details
static size_t g_SequenceNumber = 1;


static int eventCounter = 0;
static BOOL isInitialized = FALSE;
static BOOL isStopped = FALSE;

void MessageConsumerThreadFunc(LPVOID lpParam);

size_t CalcNewSeqNum(REQUEST_PRIORITY priority)
{
	size_t seqNum = 0;

	OSAL_enter_critical_section(&g_CrtSec);
	if (g_SequenceNumber == MAX_SEQ_NUM)
	{
		//Handling overflow - resetting 
		//Zero indicates an invalid seqNum, so immediately increasing to 1
		g_SequenceNumber = 0;
	}

	g_SequenceNumber++;
	OSAL_exit_critical_section(&g_CrtSec);

	//"pushing" the priority value to the 2 MSBs.
	seqNum = g_SequenceNumber | (priority << PRIORITY_OFFSET);

	return seqNum;
}

static void Messenger_EmptyQueue( Queue* pq )
{
	pMSNGR_ELEM pElemStruct = NULL;

	//if there are still indications in the queue, dequeue and free them.
	pElemStruct = (pMSNGR_ELEM)Queue_Dequeue(pq);
	while ( NULL != pElemStruct )
	{
		if ( NULL != pElemStruct->buffer )
		{
			free(pElemStruct->buffer);
			pElemStruct->buffer = NULL;
		}
		free(pElemStruct);
		pElemStruct = (pMSNGR_ELEM)Queue_Dequeue(pq);
	}
}

BOOL Messenger_LockQ(OSAL_mutex_t hMutex) 
{ 
	UINT32 dwWaitResult; 
	UINT32 dwErr;
	BOOL RC = FALSE;

	// Request ownership of mutex.

	if(INVALID_HANDLE_VALUE == hMutex)
	{
		TRACE(TR_MOD_MESSENGER, TR_SEV_ERR,"trying to get INVALID_HANDLE_VALUE");	
		return FALSE;
	}

	dwWaitResult = OSAL_timedlock_mutex( 
		hMutex,   // handle to mutex
		5000L);   // five-second time-out interval

	switch (dwWaitResult) 
	{
		// The thread got mutex ownership.
	case WAIT_OBJECT_0: 
		//		TRACE(TR_MOD_MESSENGER, TR_SEV_DEBUG,"Got Mutex");	
		RC = TRUE;
		break;
		// Cannot get mutex ownership due to time-out.
	case WAIT_TIMEOUT: 
		TRACE(TR_MOD_MESSENGER, TR_SEV_ERR,"Mutex timeout");	
		break;
		// Got ownership of the abandoned mutex object.
	case WAIT_ABANDONED: 
		
		TRACE(TR_MOD_MESSENGER, TR_SEV_ERR,"Mutex ABANDONED");	
		break;
	default:
		dwErr = GetLastError();
		TRACE(TR_MOD_MESSENGER, TR_SEV_ERR,"Mutex defualt err = %d",dwErr);	
		break;
	}

	return RC; 
}

void Messenger_FinalizeInternalResources()
{
	if (g_msng_hStopIndsConsThreadEvent != NULL)
	{
		OSAL_delete_event( g_msng_hStopIndsConsThreadEvent );
		g_msng_hStopIndsConsThreadEvent = NULL;
	}

	if (g_msng_hIndicationEnqueuedEvent != NULL)
	{
		OSAL_delete_event( g_msng_hIndicationEnqueuedEvent );
		g_msng_hIndicationEnqueuedEvent = NULL;
	}

	if(Messenger_LockQ(g_msng_MutexQ))
	{

		Messenger_EmptyQueue(&g_QueuesArr[HIGH]);
		Queue_Finalize(&g_QueuesArr[HIGH]);

		Messenger_EmptyQueue(&g_QueuesArr[MEDIUM]);
		Queue_Finalize(&g_QueuesArr[MEDIUM]);

		Messenger_EmptyQueue(&g_QueuesArr[LOW]);
		Queue_Finalize(&g_QueuesArr[LOW]);

		OSAL_delete_critical_section(&g_CrtSec);
		
		OSAL_unlock_mutex(g_msng_MutexQ);
		OSAL_delete_mutex(g_msng_MutexQ);
	}
	else
	{
		TRACE(TR_MOD_MESSENGER, TR_SEV_NOTICE,"Messenger_FinalizeInternalResources can't lock");
	}
	g_msng_MutexQ = INVALID_HANDLE_VALUE;

	if (g_msng_hCanStop != NULL)
	{
		OSAL_delete_event(g_msng_hCanStop);
		g_msng_hCanStop = NULL;
	}

	isInitialized = FALSE;
}
BOOL Messenger_InitializeInternalResources()
{
	static int i = 0;
	i++;
	
	OSAL_create_mutex(&g_msng_MutexQ, FALSE, NULL);
	
	OSAL_init_critical_section(&g_CrtSec);

	Queue_Initialize(&g_QueuesArr[HIGH], FALSE);
	Queue_Initialize(&g_QueuesArr[MEDIUM], FALSE);
	Queue_Initialize(&g_QueuesArr[LOW], FALSE);


	OSAL_create_event( &g_msng_hIndicationEnqueuedEvent , FALSE, FALSE, NULL );
	if (NULL == g_msng_hIndicationEnqueuedEvent)
	{
		TRACE(TR_MOD_MESSENGER, TR_SEV_ALERT, "Initialize Failed: Create g_msng_hIndicationEnqueuedEvent - Failed!");
		Messenger_FinalizeInternalResources();
		return FALSE;
	}

	OSAL_create_event( &g_msng_hStopIndsConsThreadEvent , TRUE, FALSE, NULL );
	if (NULL == g_msng_hStopIndsConsThreadEvent)
	{
		TRACE(TR_MOD_MESSENGER, TR_SEV_ALERT, "Initialize Failed: Create g_msng_hStopIndsConsThreadEvent - Failed!");
		Messenger_FinalizeInternalResources();
		return FALSE;
	}

	OSAL_create_event( &g_msng_hCanStop , TRUE, FALSE, NULL );
	if (NULL == g_msng_hCanStop)
	{
		TRACE(TR_MOD_MESSENGER, TR_SEV_ALERT, "Initialize Failed: Create g_msng_hStopIndsConsThreadEvent - Failed!");
		Messenger_FinalizeInternalResources();
		return FALSE;
	}

	return TRUE;
}

// This function Stops the sender thread
EXPORT void Messenger_Stop()
{
	TRACE(TR_MOD_MESSENGER, TR_SEV_NOTICE, "Messenger_Stop(IN)");
	if (isStopped)
	{
		return;
	}

	if(Messenger_LockQ(g_msng_MutexQ))
	{
		isStopped = TRUE;

		Messenger_EmptyQueue(&g_QueuesArr[HIGH]);		
		Messenger_EmptyQueue(&g_QueuesArr[MEDIUM]);
		Messenger_EmptyQueue(&g_QueuesArr[LOW]);
		
		OSAL_unlock_mutex(g_msng_MutexQ);		
	}
	else
	{
		TRACE(TR_MOD_MESSENGER, TR_SEV_NOTICE, "Messenger_FinalizeInternalResources can't lock");
	}

	//wmxTerminateThread(g_msng_hStopIndsConsThreadEvent, &g_msng_hIndicationsConsumerThread, TR_MOD_MESSENGER);
	OSAL_set_event(g_msng_hStopIndsConsThreadEvent);
	OSAL_timedjoin_thread(g_msng_hIndicationsConsumerThread, SHUTDOWN_TIMEOUT, NULL);
	
	TRACE(TR_MOD_MESSENGER, TR_SEV_NOTICE,"Messenger_Stop(OUT)");
}

EXPORT BOOL Messenger_Start()
{
	TRACE(TR_MOD_MESSENGER, TR_SEV_NOTICE,"Messenger_Start(IN)");

	OSAL_create_thread( MessageConsumerThreadFunc, NULL, &g_msng_hIndicationsConsumerThread );
	if (NULL == g_msng_hIndicationsConsumerThread)
	{
		TRACE(TR_MOD_MESSENGER, TR_SEV_ALERT,"Initialize Failed: Creation of g_msng_hIndicationsConsumerThread - Failed!");
		return FALSE;
	}
	isStopped = FALSE;
// 	if( g_msng_hIndicationsConsumerThread != NULL )
// 	{
// 		Messenger_Stop();
// 	}
// 
// 	// Create the Request Handling Thread
// 	// g_msng_hIndicationsConsumerThread = CreateThread( NULL, 0, MessageConsumerThreadFunc, NULL, 0, NULL );
// 	g_msng_hIndicationsConsumerThread = wmxBeginThreadEx( NULL, 0, MessageConsumerThreadFunc, NULL, 0, NULL );
// 	if (NULL == g_msng_hIndicationsConsumerThread)
// 	{
// 		TRACE(TR_MOD_MESSENGER, TR_SEV_ALERT,"Initialize Failed: Creation of g_msng_hIndicationsConsumerThread - Failed!");
// 		return FALSE;
// 	}

	TRACE(TR_MOD_MESSENGER, TR_SEV_NOTICE,"Messenger_Start(OUT)");
	return TRUE;
}

//This  function start the sender thread and initializes internal resources.
EXPORT BOOL Messenger_Initialize( )
{
	TRACE(TR_MOD_MESSENGER, TR_SEV_NOTICE,"Messenger_Initialize(IN)");

	if (FALSE == Messenger_InitializeInternalResources())
	{
		return FALSE;
	}

// 	if( FALSE == Messenger_Restart() )
// 	{
// 		return FALSE;
// 	}

	OSAL_set_event(g_msng_hCanStop);	

	TRACE(TR_MOD_MESSENGER, TR_SEV_NOTICE,"Messenger_Start(OUT)");
	return TRUE;
}

EXPORT void Messenger_Shutdown()
{
	TRACE(TR_MOD_MESSENGER, TR_SEV_INFO,"Messenger_Shutdown(IN)");
	Messenger_Stop();
	Messenger_FinalizeInternalResources();
	TRACE(TR_MOD_MESSENGER, TR_SEV_INFO,"Messenger_Shutdown(OUT)");
}

BOOL IsMatch(QueueElementData data, void * predicate)
{
	return ((pMSNGR_ELEM)data)->seqNum == (size_t)predicate;
}


EXPORT BOOL Messenger_PopRequest(size_t seqNum)
{
	size_t priority = seqNum >> PRIORITY_OFFSET;
	QueueElementData data = NULL;

	//0 is an invalid seqNum
	if (seqNum != 0)
	{
		data = Queue_RemoveElement(&g_QueuesArr[priority], (void *) seqNum, IsMatch);

		if (data != NULL)
		{
			free(data);
			data = NULL;
		}
	}
	return data != NULL;
}

// EnQueue an indication and set Indication Queued Event
// Return False if Queue operation fails
EXPORT size_t Messenger_PostRequest(	
								  REQUEST_PRIORITY priority,
								  UINT32 internalRequestID, 
								  void *buffer, UINT32 bufferLength,
								  InternalHandler internalHandler )
{
	//tL5DispatcherFunctions *funcs;
	pMSNGR_ELEM pElemStruct = (pMSNGR_ELEM)malloc(sizeof(MSNGR_ELEM));
	if (pElemStruct == NULL)
	{
		return 0;
	}

	UNREFERENCED_PARAMETER(priority);

	if (isStopped)
	{
		TRACE(TR_MOD_MESSENGER, TR_SEV_NOTICE,"Messenger is stopped - post request returns");
		free(pElemStruct);
		return 0; //0 to indicate invalid SeqNum
	}

	if(priority < 0 || priority >= MaxPriority)
	{
		TRACE(TR_MOD_MESSENGER, TR_SEV_CRITICAL,"Indication EnQueue Operation Failed. Illegal priority - %d", priority);	
		free(pElemStruct);
		return 0; //0 to indicate invalid SeqNum
	}

	pElemStruct->internalHandler = internalHandler;
	pElemStruct->internalRequestID = internalRequestID;
	pElemStruct->seqNum = CalcNewSeqNum(priority);
	pElemStruct->bufferLength = bufferLength;
	if (bufferLength != 0)
	{
		pElemStruct->buffer = malloc(bufferLength);
		OSAL_memcpy_s(pElemStruct->buffer, bufferLength, buffer, bufferLength);
	}
	else
	{
		pElemStruct->buffer = NULL;
	}

	if(Messenger_LockQ(g_msng_MutexQ))
	{
		if (Queue_Enqueue(&g_QueuesArr[priority], (QueueElementData)pElemStruct) == FALSE)
		{
			TRACE(TR_MOD_MESSENGER, TR_SEV_CRITICAL,"Indication EnQueue Operation Failed.");
			TRACE(TR_MOD_MESSENGER, TR_SEV_DEBUG,"Messenger_PostRequest release hlock 0x%x" ,g_msng_MutexQ);
			OSAL_unlock_mutex(g_msng_MutexQ);
			return 0;
		}

		TRACE(TR_MOD_MESSENGER, TR_SEV_DEBUG,"Messenger_PostRequest release hlock 0x%x" ,g_msng_MutexQ);
		OSAL_unlock_mutex(g_msng_MutexQ);
		TRACE(TR_MOD_MESSENGER, TR_SEV_INFO,"Indication EnQueue at priority %s.", REQUEST_PRIORITYStr[priority]);
	}
	else
	{
		TRACE(TR_MOD_MESSENGER, TR_SEV_ALERT,"Messenger_PostRequest can't lock");
	}

	if (0 != OSAL_set_event(g_msng_hIndicationEnqueuedEvent))
	{
		TRACE(TR_MOD_MESSENGER, TR_SEV_CRITICAL,"OSAL_set_event(g_msng_hIndicationEnqueuedEvent) failed!!");
	}
	eventCounter++;

	//return pElemStruct->seqNum;
	return eventCounter;
}

// DeQueue an indication and send it to the relevant MessageSender, return FALSE if queue is empty
BOOL ProcessMessage( Queue* pq )
{
	pMSNGR_ELEM pElemStruct = NULL;

	OSAL_reset_event(g_msng_hCanStop);
	
	if(Messenger_LockQ(g_msng_MutexQ))
	{
		TRACE(TR_MOD_MESSENGER, TR_SEV_DEBUG,"Queue_Dequeue");
		pElemStruct = (pMSNGR_ELEM)Queue_Dequeue(pq);
		TRACE(TR_MOD_MESSENGER, TR_SEV_DEBUG,"ProcessMessage release hlock 0x%x" ,g_msng_MutexQ);
		OSAL_unlock_mutex(g_msng_MutexQ);
	}
	else
	{
		TRACE(TR_MOD_MESSENGER, TR_SEV_ERR, "ProcessMessage can't lock");
	}


	if (NULL == pElemStruct)
	{
		OSAL_set_event(g_msng_hCanStop);
		return FALSE;//Queue is empty
	}
	if (NULL != pElemStruct->internalHandler)
	{
		TRACE(TR_MOD_MESSENGER, TR_SEV_DEBUG, "Send Indication from Queue to handler.");
		pElemStruct->internalHandler(	
			pElemStruct->internalRequestID,
			pElemStruct->buffer, pElemStruct->bufferLength );
	}

	//free the indication:
	if ( NULL != pElemStruct->buffer )
	{
		free(pElemStruct->buffer);
		pElemStruct->buffer = NULL;
	}
	free(pElemStruct);
	pElemStruct = NULL;

	OSAL_set_event(g_msng_hCanStop);
	return TRUE;
}

// This is the Indication consumer thread function 
void MessageConsumerThreadFunc( LPVOID lpParam )
{
	BOOL bStop = FALSE;
	BOOL bContinueProcess = FALSE;
	// It is important to put the stop event first in the array, so it will get higher priority
	// when shutting the module down.
	OSAL_event_t ahHandles[2]; 
	ahHandles[0] = g_msng_hStopIndsConsThreadEvent;
	ahHandles[1] = g_msng_hIndicationEnqueuedEvent;

	UNREFERENCED_PARAMETER(lpParam);

	TRACE(TR_MOD_MESSENGER, TR_SEV_INFO, "Indication Consumer Thread started.");

	for(;!bStop;)
	{
		switch(OSAL_multiple_wait_event(ARRAY_ENTRIES(ahHandles), ahHandles, FALSE, 3000) )		// @@@ : 5/8/09 : JSS - OSAL stuff
		{
		case WAIT_OBJECT_0:			// Stop
			TRACE(TR_MOD_MESSENGER, TR_SEV_INFO, "Stop Event Signaled - Thread Aborting clean Resources!");
			//Any indication in the queue will be freed by the Finish method and won`t be sent to subscribers.
			bStop = TRUE;
			continue;

		case (WAIT_OBJECT_0 + 1):	// indication available
			//TRACE(TR_MOD_MESSENGER, TR_SEV_INFO, (L"Indication available"));
			break;

		case WAIT_ABANDONED:
			//Stop is not needed
			TRACE(TR_MOD_MESSENGER, TR_SEV_INFO, "Wait abandoned signal for g_msng_hStopIndsConsThreadEvent!!");
			bStop = TRUE;
			continue;

		case (WAIT_ABANDONED + 1):
			//Stop is not needed
			TRACE(TR_MOD_MESSENGER, TR_SEV_INFO, "Wait abandoned signal for g_msng_hIndicationEnqueuedEvent!!");
			bStop = TRUE;
			continue;

		case WAIT_TIMEOUT:
			//Stop is not needed
			TRACE(TR_MOD_MESSENGER, TR_SEV_INFO, "Wait timeout signal!!");
			if (eventCounter>3)
			{
				TRACE(TR_MOD_MESSENGER, TR_SEV_CRITICAL, "eventCounter>3 !!!");
			}
			continue;

		default: //WAIT_FAILED
			TRACE(TR_MOD_MESSENGER, TR_SEV_CRITICAL, "Wait Failed!. error=%d", GetLastError());
			bStop = TRUE;
			continue;
		}

		// Process all Indications in queue:
		do 
		{
			eventCounter=0;

			bContinueProcess = ProcessMessage( &g_QueuesArr[HIGH] ) || 
				ProcessMessage( &g_QueuesArr[MEDIUM] ) || 
				ProcessMessage( &g_QueuesArr[LOW] );

			//Check if stop event has been sent:
			switch( OSAL_wait_event(g_msng_hStopIndsConsThreadEvent, 0) )
			{
			case WAIT_OBJECT_0:			// Stop
				TRACE(TR_MOD_MESSENGER, TR_SEV_INFO, "Stop Event Signaled (2) - Thread Aborting!");
				//Any indication in the queue will be freed by the Finish method and won`t be sent to subscribers.
				bStop = TRUE;
				continue;

			case WAIT_TIMEOUT:
				//Stop is not needed
				break;

			case WAIT_ABANDONED:
				//Stop is not needed
				bStop = TRUE;
				continue;

			default: //WAIT_FAILED
				TRACE(TR_MOD_MESSENGER, TR_SEV_ALERT, "Wait Failed!.");
				bStop = TRUE;
				continue;
			}

		} while( TRUE == bContinueProcess );//FALSE means all queues are empty.
	}	
}
