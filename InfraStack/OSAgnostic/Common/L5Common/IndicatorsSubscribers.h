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
#ifndef INDICATIONS_SUBSCRIBERS_DEFINE
#define INDICATIONS_SUBSCRIBERS_DEFINE

#include "List.h"
#include "L5Common.h"

//This struct declare an item in the list, which holds an indication ID and its targetIds list
typedef struct  
{
	List subscribersList;
	UINT32 id;
} IndicatorSubscribers;

typedef struct
{
	tL5DispatcherFunctions *pSenderFuncs; // this can be released only after the pipe handler is stopped
	L5_CONNECTION senderL5Conn;
	List *pSubscribersList; // this can be released only after the pipe handler is stopped
	UINT32 indication_id;
	UINT32 indication_buffer_size;
	BYTE  indication_buffer[1];
} SendIndData;

EXPORT void Indications_AddSubscriber(IndicatorSubscribers *indSubscribers, UINT32 subscriberID);
EXPORT BOOL Indications_RemoveSubscriber(IndicatorSubscribers *indSubscribers, UINT32 subscriberID);
EXPORT IndicatorSubscribers *GetIndicatorSubscribers(List *pList, UINT32 indication_id, BOOL bCreateNew);
EXPORT void AllocIndicatorsList(List **ppList);
EXPORT void EmptyIndicatorsList(List **ppList);
EXPORT void CleanIndicatorsList(List **ppList);
EXPORT void SendIndicationToSubscribers( UINT32 indication_id, SendIndData *pSendIndicationData, UINT32 sendIndicationDataLength );


#endif //INDICATIONS_SUBSCRIBERS_DEFINE