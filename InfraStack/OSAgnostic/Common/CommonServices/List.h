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
#ifndef LIST_DEFINE
#define LIST_DEFINE

#include "wimax_osal_types.h"

typedef struct _ListItem
{
	void *pData;
	struct _ListItem *pNextItem;
} ListItem;

typedef struct  
{
	OSAL_critical_section *pLock;
	ListItem *pHead;
	UINT32 dwLength;
} List;

void	List_Init(List *pList, BOOL threadSafe);
void	List_Finalize(List *pList);
void	List_AddItem(List *pList, void *pItemData);
UINT32	List_RemoveItem(List *pList, void *pItemData);
void	List_Clear(List *pList);
UINT32	List_Length(List *pList);

//Iterator functions:
ListItem*	CreateIterator(List *pList);
void	FreeIterator(List *pList);
ListItem*	Iterator_GetNext(List *pList, ListItem* handle, void **ppData);

#endif //LIST_DEFINE