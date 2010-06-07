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
#include "EventSubscribers.h"

#include "CommonServices.h"


//*******************************************
// Allocate and Initialize the List
//*******************************************
void AllocSubscribersList(List **ppList)
{
	//allocate the list
	*ppList = (List*)malloc(sizeof(List));
	List_Init(*ppList, TRUE);
}


//*******************************************
// Clean the subscribers list items and free the list
//*******************************************
void CleanSubscribersList(List **ppList)
{
	ListItem* handle;
	EventSubscriber *pTempSub = NULL;
	
	handle = CreateIterator(*ppList);
	
	//free all the EventSubscriber structs
	handle = Iterator_GetNext(*ppList, handle, (void**)&pTempSub);
	while (handle != NULL)
	{		
		free(pTempSub);
		pTempSub = NULL;
		handle = Iterator_GetNext(*ppList, handle, (void**)&pTempSub);
	}

	FreeIterator(*ppList);

	List_Clear(*ppList);
	List_Finalize(*ppList);
	free(*ppList);
	(*ppList) = NULL;
}


//*******************************************
//find the relevant subscriber item.
//*******************************************
EventSubscriber *FindEventSubscriber(List *pList, wmx_pCtrlStatusUpdateCB_t subscriberCB)
{
	ListItem* handle;
	EventSubscriber *pTempSub = NULL;

	VERIFY(pList);

	handle = CreateIterator(pList);

	handle = Iterator_GetNext(pList, handle, (void**)&pTempSub);
	while (handle != NULL)
	{
		if(pTempSub->subscriberCB == subscriberCB)//this is the Item
		{
			FreeIterator(pList);
			return pTempSub;
		}
		handle = Iterator_GetNext(pList, handle, (void**)&pTempSub);
	}
	FreeIterator(pList);	

	return NULL;
}


//*******************************************
// Add a subscriber to the EventSubscriber list
//*******************************************
pEventSubscriber AddSubscriber(List *pList, wmx_pCtrlStatusUpdateCB_t subscriberCB)
{
	EventSubscriber *pTempSub = NULL;
	
	pTempSub = (EventSubscriber*)malloc(sizeof(EventSubscriber));
	if (pTempSub != NULL)
	{
		pTempSub->subscriberCB = subscriberCB;
		List_AddItem(pList, pTempSub);
	}

	return pTempSub;
}


//*******************************************
// Remove a subscriber from the EventSubscriber list
//*******************************************
BOOL RemoveSubscriber(List *pList, wmx_pCtrlStatusUpdateCB_t subscriberCB)
{
	pEventSubscriber sub = FindEventSubscriber(pList, subscriberCB);	

	if ((sub != NULL) && (List_RemoveItem(pList, (void*)sub)))
	{
		return TRUE;
	}
	return FALSE;
}


//*******************************************
// Iterate the EventSubscriber list and invoke the callbacks stored in its items
//*******************************************
void SendEventToSubscribers(List *pList, wmx_CtrlStatus_t status)
{
	ListItem* handle;
	EventSubscriber *pTempSub = NULL;

	VERIFY(pList);

	handle = CreateIterator(pList);

	handle = Iterator_GetNext(pList, handle, (void**)&pTempSub);
	while (handle != NULL)
	{
		if(pTempSub->subscriberCB != NULL) // just in case...
		{
			pTempSub->subscriberCB(status);
		}
		handle = Iterator_GetNext(pList, handle, (void**)&pTempSub);
	}
	FreeIterator(pList);
}