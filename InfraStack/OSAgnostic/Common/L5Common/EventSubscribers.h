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
#ifndef EVENT_SUBSCRIBERS_H
#define EVENT_SUBSCRIBERS_H

#include "List.h"
#include "L5Common.h"	

//This struct declare an item in the list, which holds an indication ID and its targetIds list
typedef struct  
{
	wmx_pCtrlStatusUpdateCB_t subscriberCB;
} EventSubscriber, *pEventSubscriber;



pEventSubscriber AddSubscriber(List *pList, wmx_pCtrlStatusUpdateCB_t subscriberCB);
BOOL RemoveSubscriber(List *pList, wmx_pCtrlStatusUpdateCB_t subscriberCB);
//EventSubscriber *GetIndicatorSubscribers(List *pList, wmx_pCtrlStatusUpdateCB_t subscriberCB, BOOL bCreateNew);
void AllocSubscribersList(List **ppList);
void CleanSubscribersList(List **ppList);
void SendEventToSubscribers(List *pList, wmx_CtrlStatus_t status);

#endif //EVENT_SUBSCRIBERS_H