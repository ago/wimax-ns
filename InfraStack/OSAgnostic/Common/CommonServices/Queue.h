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
#ifndef _QUEUE_H
#define _QUEUE_H

typedef void* QueueElementData;

typedef struct _QueueElement
{
	QueueElementData data;
	struct _QueueElement *pNextItem;
	struct _QueueElement *pPrevItem;
} QueueElement, *PQueueElement;


typedef struct  
{
	OSAL_critical_section *pCS;
	QueueElement *pHead;
	QueueElement *pTail;
	UINT32 dwCount;
	UINT32 fSync;	
} Queue, *PQueue;

typedef BOOL (*DoesMatch)(QueueElementData data, void * predicate);

//Initializes an instance of a Queue struct
void		Queue_Initialize(PQueue pQueue, BOOL bSynchronized);

//Finalize an instance of a Queue struct
void		Queue_Finalize(PQueue pQueue);

//Gets the number of elements contained in the Queue.
int			Queue_Count(PQueue pQueue);

//Adds an object to the end of the Queue. 
BOOL        Queue_Enqueue(PQueue pQueue, QueueElementData item);

//Removes and returns the object at the beginning of the Queue. 
QueueElementData	Queue_Dequeue(PQueue pQueue);

//Gets a value indicating whether access to the Queue is synchronized (thread safe). 
BOOL Queue_IsSynchronized(PQueue pQueue);

//Finds the fist occurrence of a queue element according to the predicate
QueueElementData Queue_RemoveElement(PQueue pQueue, void * predicate, DoesMatch pDoesMatchFunc);

#endif  // _QUEUE_H
