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
#include "IndicatorsSubscribers.h"

#include "CommonServices.h"
#include "L3L4CommonDefines.h"
#include "TraceModule.h"


// Allocate and Initialize the List
EXPORT void AllocIndicatorsList(List **ppList)
{
	//allocate the Status indicators list structs:
	*ppList = (List*)malloc(sizeof(List));
	List_Init(*ppList, TRUE);
}
 
// Clean the subscribers list items and free the list
EXPORT void EmptyIndicatorsList(List **ppList)
{
	ListItem* handle;
	IndicatorSubscribers *pTempInd = NULL;
	
	handle = CreateIterator(*ppList);
	
	//for each indicator struct- clean the subscribers list and free the IndicatorSubscribers struct:
	handle = Iterator_GetNext(*ppList, handle, (void**)&pTempInd);
	while (handle != NULL)
	{		
		List_Clear(&(pTempInd->subscribersList));
		handle = Iterator_GetNext(*ppList, handle, (void**)&pTempInd);
	}

	FreeIterator(*ppList);	
}

EXPORT void CleanIndicatorsList(List **ppList)
{
	ListItem* handle;
	IndicatorSubscribers *pTempInd = NULL;	

	handle = CreateIterator(*ppList);

	//for each indicator struct- clean the subscribers list and free the IndicatorSubscribers struct:
	handle = Iterator_GetNext(*ppList, handle, (void**)&pTempInd);
	while (handle != NULL)
	{		
		List_Clear(&(pTempInd->subscribersList));
		List_Finalize(&(pTempInd->subscribersList));
		free(pTempInd);
		pTempInd = NULL;
		handle = Iterator_GetNext(*ppList, handle, (void**)&pTempInd);
	}

	FreeIterator(*ppList);
	List_Clear(*ppList);

	List_Finalize(*ppList);
	free(*ppList);
	(*ppList) = NULL;
}


//find the relevant InidicatorsSubscribers Item.
//bCreateNew - boolean which indicate to create a new entry to the specific id if not exist
EXPORT IndicatorSubscribers *GetIndicatorSubscribers(List *pList, UINT32 indication_id, BOOL bCreateNew)
{
	ListItem* handle;
	IndicatorSubscribers *pTempInd = NULL;

	if(pList == NULL)
	{
		return NULL;
	}

	handle = CreateIterator(pList);

	handle = Iterator_GetNext(pList, handle, (void**)&pTempInd);
	while (handle != NULL)
	{
		if(pTempInd->id	== indication_id)//this is the Item
		{
			FreeIterator(pList);
			return pTempInd;
		}
		handle = Iterator_GetNext(pList, handle, (void**)&pTempInd);
	}
	FreeIterator(pList);

	if (TRUE == bCreateNew)
	{
		//No such indicator list for the specific id - generate new one
		pTempInd = (IndicatorSubscribers*)malloc(sizeof(IndicatorSubscribers));
		pTempInd->id = indication_id;
		List_Init(&(pTempInd->subscribersList), TRUE);
		List_AddItem(pList, pTempInd);
		return pTempInd;
	}

	return NULL;
}

// Add a subscriber to the IndicatorSubscribers list
EXPORT void Indications_AddSubscriber(IndicatorSubscribers *indSubscribers, UINT32 subscriberID)
{
	//I`m using the pointer to data (in the list) as my indication id. So i don`t need to allocate/free it.
	List_AddItem(&(indSubscribers->subscribersList), (void*)((ULONG_PTR)subscriberID));
}

// Remove a subscriber from the IndicatorSubscribers list
EXPORT BOOL Indications_RemoveSubscriber(IndicatorSubscribers *indSubscribers, UINT32 subscriberID)
{
	if (List_RemoveItem(&(indSubscribers->subscribersList), (void*)((ULONG_PTR)subscriberID)))
	{
		return TRUE;
	}
	return FALSE;
}

// This  function go over the specific list (L4 SS or status SS) and send all its registered targets the indication.
// Can be used as the InternalHandler with Messenger_PostRequest
EXPORT void SendIndicationToSubscribers( UINT32 internalRequestID, void *_buffer, UINT32 bufferLength )
{
	SendIndData *buffer = _buffer;
	ListItem* handle;
	L5_TARGET_ID targetID;
	L5_TARGET_ID data;
	L5_RESULT res;
	IndicatorSubscribers *indSubscribers;
	List tempList;
	
	UNREFERENCED_PARAMETER(bufferLength);
	
	//TODO: use FailedDeliveryIndication if available to notify on send failure.

	// go over the list and send indications to all targets
	indSubscribers = GetIndicatorSubscribers(buffer->pSubscribersList, buffer->indication_id, FALSE);

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_DEBUG,"SendIndicationToSubscribers(IN) - internalRequestID=%d, indSubscribers=%d, pSubscribersList=%d, indication_id=%d",
									internalRequestID ,indSubscribers, buffer->pSubscribersList, buffer->indication_id);
	if ((NULL != indSubscribers) && (0 != List_Length(&(indSubscribers->subscribersList))))
	{		
		// Build temp list
		List_Init(&tempList, FALSE);
		handle = CreateIterator(&(indSubscribers->subscribersList));
//		handle = Iterator_GetNext(&(indSubscribers->subscribersList), handle, (void**)&targetID);
		handle = Iterator_GetNext(&(indSubscribers->subscribersList), handle, (void**)(&data));
		targetID = data;
		while (handle != NULL)
		{
			List_AddItem(&tempList, (void *)targetID);
			handle = Iterator_GetNext(&(indSubscribers->subscribersList), handle, (void**)(&data));
    		targetID = data; ////

	//		handle = Iterator_GetNext(&(indSubscribers->subscribersList), handle, (void**)&targetID);
		}

		FreeIterator(&(indSubscribers->subscribersList));

		//iterate the temp list and send the targets indication:
		handle = CreateIterator(&tempList);
		handle = Iterator_GetNext(&tempList, handle, (void**)(&data));
    	targetID = data;

	//	handle = Iterator_GetNext(&tempList, handle, (void**)&targetID);
		while (handle != NULL)
		{
			//in case we are working with remote DnD, we want to send the trace and monitor indications 
			//only to the DnD agent
			if(((L3_L4_OPCODE_REPORT_MONITOR_EVACUATE != *((UINT16 *)buffer->indication_buffer)) &&
				(L3_L4_OPCODE_REPORT_TRACE_EVACUATE != *((UINT16 *)buffer->indication_buffer))) ||
				(L5_TARGET_DND_AGENT == targetID))
			{
				TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_DEBUG,"SendIndicationToSubscribers - senderL5Conn=0x%x, targetID=%d, internalRequestID=%d",
													buffer->senderL5Conn, targetID, internalRequestID);
				res = buffer->pSenderFuncs->pfnSendReceiveMessage(
										buffer->senderL5Conn,  
										targetID, 
										internalRequestID, 
										buffer->indication_buffer, buffer->indication_buffer_size, 
										NULL, NULL, NULL);

				if ( L5_RESULT_ID_NOT_FOUND == res)
				{
					Indications_RemoveSubscriber(indSubscribers , targetID);
				}

			}
			
	//		handle = Iterator_GetNext(&tempList, handle, (void**)&targetID);

			handle = Iterator_GetNext(&tempList, handle, (void**)(&data));
    		targetID = data;


			// TODO - XXX - check L5_COMMON_UTILS_IsTargetNotExist
			// TODO - XXX - check res
			// TODO - XXX - check responseID
		}

		FreeIterator(&tempList);

		//free the temp list items:
		List_Clear(&tempList);
		List_Finalize(&tempList);
	}
	else
	{
		TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_DEBUG,"SendIndicationToSubscribers - no subscribers");
	}
}

