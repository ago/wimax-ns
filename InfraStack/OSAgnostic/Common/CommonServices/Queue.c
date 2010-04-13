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
#include "wimax_osal_primitives.h"
#include "Queue.h"
#include "CommonServices.h"

#define SYNC_MAGIC 0xdeedbeef

//Removes a specified element from the queue
static QueueElementData Queue_RemoveElementInternal(PQueue pQueue, PQueueElement pQueueElem);


//private:
void LockQueue(PQueue pQueue)
{
	if(!pQueue)
		return ;

	if ( SYNC_MAGIC == pQueue->fSync )
	{
		OSAL_enter_critical_section( pQueue->pCS );
	}
}

void UnLockQueue(PQueue pQueue)
{
	if(!pQueue)
		return ;

	if ( SYNC_MAGIC == pQueue->fSync )
	{
		OSAL_exit_critical_section( pQueue->pCS );
	}
}
/***********************************/
void Queue_Initialize(PQueue pQueue, BOOL bSynchronized)
{
	UNREFERENCED_PARAMETER(bSynchronized);

	if(!pQueue)
		return ;
		
	if(bSynchronized) // dummy if for compiler happy.
		bSynchronized = bSynchronized;

	pQueue->dwCount = 0;
	pQueue->pHead = NULL;
	pQueue->pTail = NULL;

	if ( TRUE == bSynchronized )
	{
		pQueue->pCS = (OSAL_critical_section *)malloc( sizeof(OSAL_critical_section) );
		OSAL_init_critical_section( pQueue->pCS );
		pQueue->fSync = SYNC_MAGIC;
	}
	else
	{
		pQueue->pCS = NULL;
		pQueue->fSync = 0;
	}
}

BOOL Queue_IsSynchronized(PQueue pQueue)
{
	
	return (pQueue->fSync == SYNC_MAGIC);
}

void Queue_Finalize(PQueue pQueue)
{
	if(!pQueue)
		return ;
	if( 0 != pQueue->dwCount )
		return;
	//add trace - finalize queue which is not empty
	if ( SYNC_MAGIC == pQueue->fSync )
	{
		OSAL_delete_critical_section( pQueue->pCS );
		free(pQueue->pCS);
		pQueue->pCS = NULL;
		pQueue->fSync = 0;
	}
}

int	Queue_Count(PQueue pQueue)
{
	UINT32 count;

	if(!pQueue)
		return 0;
	
	LockQueue(pQueue);

	count = pQueue->dwCount;
	
	UnLockQueue(pQueue);

	return count;
}

BOOL Queue_Enqueue(PQueue pQueue, QueueElementData item)
{
	QueueElement *qElm;
	if(!pQueue)
		return FALSE;

	//Create new queue element and add it to the tail.
	qElm = (QueueElement*)malloc( sizeof(QueueElement) );
	if (NULL == qElm)
	{
		return FALSE;
	}
	qElm->data = item;
	qElm->pNextItem = NULL;
	
	LockQueue(pQueue);

	qElm->pPrevItem = pQueue->pTail;
	
	if (NULL == pQueue->pTail)//this is the first element
	{
		pQueue->pTail = pQueue->pHead = qElm;
	}
	else
	{
		pQueue->pTail->pNextItem = qElm;
		pQueue->pTail = qElm;
	}
	pQueue->dwCount++;

	UnLockQueue(pQueue);
	return TRUE;
}

QueueElementData Queue_Dequeue(PQueue pQueue)
{
	QueueElement *qElm;
	QueueElementData data;

	if(!pQueue)
		return NULL;

	LockQueue(pQueue);

	if (NULL == pQueue->pHead)
	{
		UnLockQueue(pQueue);
		return NULL;
	}
	
	qElm = pQueue->pHead;
	pQueue->pHead = qElm->pNextItem;

	if (NULL == qElm->pNextItem)//there is only one element
	{
		pQueue->pTail = NULL;
	}	

	data = qElm->data;
	free(qElm);
	qElm = NULL;

	pQueue->dwCount--;

	UnLockQueue(pQueue);

	return data;
}

//
//Finds the first occurrence of a queue element based on the predicate and 
//removes it from the queue
//
QueueElementData Queue_RemoveElement(PQueue pQueue, void * predicate, DoesMatch pDoesMatchFunc)
{
	QueueElementData data = NULL;
	PQueueElement currItem = NULL;

	if(!pQueue)
	{
		return NULL;
	}

	LockQueue(pQueue);

	if (NULL == pQueue->pHead)
	{
		UnLockQueue(pQueue);
		return NULL;
	}

	currItem = pQueue->pHead;
	while (currItem != NULL)
	{
		if (pDoesMatchFunc(currItem->data, predicate) == TRUE)
		{
			data = Queue_RemoveElementInternal(pQueue, currItem);
			break;
		}

		currItem = currItem->pNextItem;
	}

	UnLockQueue(pQueue);

	return data;
}

//
//Removes a specified element from the queue
//
static QueueElementData Queue_RemoveElementInternal(PQueue pQueue, PQueueElement pQueueElem)
{
	QueueElementData data;
	PQueueElement prevItem = pQueueElem->pPrevItem;
	PQueueElement nextItem = pQueueElem->pNextItem;

	if(!pQueue)
	{
		return NULL;
	}

	LockQueue(pQueue);

	if (NULL == pQueue->pHead)
	{
		UnLockQueue(pQueue);
		return NULL;
	}

	//Connect prevItem to nextItem
	if (prevItem != NULL)
	{
		prevItem->pNextItem = nextItem;
	}
	else
	{
		//pQueueElem is the queue head
		pQueue->pHead = nextItem;
	}

	//Connect nextItem to prevItem
	if (nextItem != NULL)
	{
		nextItem->pPrevItem = prevItem;
	}
	else
	{
		//pQueueElem is the queue tail
		pQueue->pTail = prevItem;
	}

	//Extract data and return...
	data = pQueueElem->data;
	free(pQueueElem);
	pQueueElem = NULL;

	pQueue->dwCount--;

	UnLockQueue(pQueue);

	return data;
}
