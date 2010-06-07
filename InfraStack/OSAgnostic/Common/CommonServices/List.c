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
#include "List.h"
#include "CommonServices.h"
#include <stdlib.h>

//*******************************************
//Initialize the list
//safe - if TRUE then the list is thread safe.
//*******************************************


void List_Init(List *pList, BOOL threadSafe)
{
	if(!pList)
		return ;

	pList->pHead = NULL;
	pList->dwLength = 0;
	
	if (TRUE == threadSafe)
	{
		pList->pLock = malloc(sizeof(OSAL_critical_section));		// @@@ : JSS (Replaced CRITICAL_SECTION)
		OSAL_init_critical_section(pList->pLock);

	}
	else
	{
		pList->pLock = NULL;
	}
}

//*******************************************
//Finalize the list
//*******************************************
void List_Finalize(List *pList)
{
	if(!pList)
		return ;
	
	if (NULL != pList->pLock)
	{
		OSAL_delete_critical_section(pList->pLock);
		free(pList->pLock);
		pList->pLock = NULL;
	}
}

//*******************************************
//Clear the List -  free all items in the list.
//*******************************************
void List_Clear(List *pList)
{
	ListItem *pTempItem;

	if(!pList)
		return ;

	if (NULL != pList->pLock)
	{
		OSAL_enter_critical_section(pList->pLock);
	}

	while(NULL != (pTempItem = pList->pHead))
	{
		pList->pHead = pList->pHead->pNextItem;
		free(pTempItem);
	}
	pList->dwLength = 0;
	pList->pHead = NULL;
	
	if (NULL != pList->pLock)
	{
		OSAL_exit_critical_section(pList->pLock);
	}
}
//*******************************************
//Add new item to the list
//*******************************************
void List_AddItem(List *pList, void *pItemData)
{
	ListItem *pNewItem;

	if(!pList)
		return ;

	pNewItem = (ListItem*)malloc(sizeof(ListItem));
	pNewItem ->pData = pItemData;
	
	if (NULL != pList->pLock)
	{
		OSAL_enter_critical_section(pList->pLock);
	}
	pNewItem ->pNextItem = pList->pHead;
	pList->pHead = pNewItem ;
	pList->dwLength++;
	
	if (NULL != pList->pLock)
	{
		OSAL_exit_critical_section(pList->pLock);
	}
}

//*******************************************
//Remove item from the list
//Returns 1 if item was removed, 
//0 if not found
//*******************************************
UINT32 List_RemoveItem(List *pList, void *pItemData)
{
	//Search for the ListItem:
	ListItem *previousItem = NULL;
	ListItem *temp;// = pList->pHead; - move after the lock
	UINT32 dwFound = 0;

	if(!pList)
		return dwFound;
	
	if (NULL != pList->pLock)
	{
		OSAL_enter_critical_section(pList->pLock);
	}

	temp = pList->pHead;

	while(NULL != temp)
	{
		if (temp->pData == pItemData)//Item found!
		{
			if(NULL == previousItem)//This is the first Item
			{
				pList->pHead = temp->pNextItem;	
			}
			else
			{
				previousItem->pNextItem = temp->pNextItem;
			}
			
			free(temp);
			pList->dwLength--;
			dwFound = 1;
			break;
		}

		previousItem = temp;
		temp = temp->pNextItem;
	}

	if (NULL != pList->pLock)
	{
		OSAL_exit_critical_section(pList->pLock);
	}

	return dwFound;
}

//*******************************************
// Return the length of the list
//*******************************************
UINT32 List_Length(List *pList)
{
	UINT32 len;
	if(!pList)
		return 0;

	if (NULL != pList->pLock)
	{
		OSAL_enter_critical_section(pList->pLock);
	}

	len = pList->dwLength;
	
	if (NULL != pList->pLock)
	{
		OSAL_exit_critical_section(pList->pLock);
	}

	return len;
}

//Iterators Functions:

//*******************************************
// Create an Iterator on the list
//*******************************************
ListItem* CreateIterator(List *pList)
{
	if(!pList)
		return NULL;

	if (NULL != pList->pLock)
	{
		OSAL_enter_critical_section(pList->pLock);
	}
	return NULL;
}

//*******************************************
// Free the current locked Iterator
//*******************************************
void FreeIterator(List *pList)
{
	if(!pList)
		return ;

	if (NULL != pList->pLock)
	{
		OSAL_exit_critical_section(pList->pLock);
	}
}

//*******************************************
// Get the next iterator item.
// the handle argument got by the 'CreateIterator' or by the previous 'Iterator_GetNext' call.
//*******************************************
ListItem* Iterator_GetNext(List *pList, ListItem* handle, void **ppData)
{
	ListItem *pNextItem;

	if(!pList)
		return NULL;

	if (NULL == handle)//This is the first 'GetNext' request
	{
		pNextItem = pList->pHead;
	}
	else
	{
		pNextItem = ((ListItem *)handle)->pNextItem;
	}

	if (NULL != pNextItem)
	{
		*ppData = pNextItem->pData;
	}
	
	return pNextItem;
}
//*******************************************
