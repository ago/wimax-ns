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
/**************************** Include Files *****************************************/

#include <Windows.h>
#include "TypesProxy.h"
#include "TraceStringTables.h"

/******************************* Defines ********************************************/

#define ARRAY_SIZE(arr)			sizeof(arr) / sizeof(arr[0])
#define TST_MAX_TABLES_NUM		(3)

/******************************** Types *********************************************/

/** 
	Defines structure containing info for a single Trace String Table.
*/
typedef struct _TraceStringTable
{
	HANDLE hFile;		/* a handle to the file, returned by CreateFile */
	HANDLE hMap;		/* a handle to the file mapping, returned by CreateFileMapping */
	LPVOID pFileView;	/* a pointer to the actual file mapping */
	LPVOID pStart;		/* a pointer to the start of strings, just beyond header */
	LPVOID pEndView;	/* a pointer just beyond the actual file view */
} TraceStringTable;

/******************************* Variables ******************************************/

static TraceStringTable s_tables[TST_MAX_TABLES_NUM] = 
{
	{INVALID_HANDLE_VALUE, INVALID_HANDLE_VALUE, NULL, NULL, NULL},
	{INVALID_HANDLE_VALUE, INVALID_HANDLE_VALUE, NULL, NULL, NULL},
	{INVALID_HANDLE_VALUE, INVALID_HANDLE_VALUE, NULL, NULL, NULL}
};

/**************************** Function declaration **********************************/

//const char *TST_GetLibraryFileName();

/*************************** Function implementation ********************************/

HStringTable	TST_LoadLibrary	(char* libraryFileName, LPVOID headerBuf, UINT32 headerSize)
{
	UINT32 dwFileSize;
	TraceStringTable *table;

	int nIndex;
	for(nIndex = 0; nIndex < ARRAY_SIZE(s_tables); nIndex++)
	{
		if(s_tables[nIndex].hFile == INVALID_HANDLE_VALUE)
			break;
	}

	if(nIndex == ARRAY_SIZE(s_tables))
		return INVALID_HSTRING_TABLE;

	table = &(s_tables[nIndex]);

	table->hFile = INVALID_HANDLE_VALUE;
	table->hMap = NULL;
	table->pEndView = NULL;
	table->pStart = NULL;
	table->pFileView = NULL;

	/* TBD: file/path name should be changed! */
	if (((table->hFile = CreateFile(libraryFileName, GENERIC_READ, FILE_SHARE_READ, NULL, 
									OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)) != INVALID_HANDLE_VALUE) &&
		((table->hMap = CreateFileMapping(table->hFile, NULL, PAGE_READONLY, 0, 0, NULL)) != NULL) &&
		((table->pFileView = MapViewOfFile(table->hMap, FILE_MAP_READ, 0, 0, 0)) != NULL) &&
		((dwFileSize = GetFileSize(table->hFile, NULL)) != 0) &&
		(headerSize <= dwFileSize)) 
	{
		table->pStart = (char *)table->pFileView + headerSize;
		table->pEndView = (char *)table->pFileView + dwFileSize;

		if(headerSize > 0)
			memcpy(headerBuf, table->pFileView, headerSize);
	}
	else
	{
		TST_FreeLibrary((HStringTable)table);
		return INVALID_HSTRING_TABLE;
	}

	return ((HStringTable)table);
}

void			TST_FreeLibrary	(HStringTable stringTable)
{
	/* TBD: check stringTable for legality */

	TraceStringTable *table = (TraceStringTable *)stringTable;

	table->pStart = NULL;
	table->pEndView = NULL;
	if(table->pFileView)
	{
		UnmapViewOfFile(table->pFileView);
		table->pFileView = NULL;
	}
	if(table->hMap != INVALID_HANDLE_VALUE)
	{
		CloseHandle(table->hMap);
		table->hMap = INVALID_HANDLE_VALUE;
	}
	if(table->hFile != INVALID_HANDLE_VALUE)
	{
		CloseHandle(table->hFile);
		table->hFile = INVALID_HANDLE_VALUE;
	}
}

int				TST_LoadString	(HStringTable	stringTable, 
								 UINT32			dwStringID,
								 char*			szBuffer,
								 int			iBufferSize)
{
	const char *cszString;
	TraceStringTable *table = (TraceStringTable *)stringTable;

	if(table->pStart == NULL) /* wrong string table handle */
	{
		return 0;
	}

	cszString = (char *)table->pStart + dwStringID;

	if(((LPVOID)cszString < table->pFileView) || (table->pEndView <= (LPVOID)cszString)) // pointer outside current file view */
	{
		return (-1 * ((UINT32)table->pEndView - (UINT32)table->pFileView));
	}

	strncpy_s(szBuffer, iBufferSize, cszString, iBufferSize);

	return 1;
}

int				TST_LoadSection	(HStringTable	stringTable, 
								 UINT32			dwSectionID,
								 LPVOID			sectionBuffer,
								 UINT32			sectionSize)
{
	/* TBD: check stringTable for legality */

	LPVOID pSection;
	TraceStringTable *table = (TraceStringTable *)stringTable;

	if(table->pStart == NULL) // wrong string table handle
	{
		return 0;
	}

	pSection = (char *)table->pStart + (dwSectionID * sectionSize);

	if((pSection < table->pFileView) || (table->pEndView <= pSection)) //pointer outside current file view
	{
		return (-1 * ((UINT32)table->pEndView - (UINT32)table->pFileView));
	}

	memcpy(sectionBuffer, pSection, sectionSize);

	return 1;
}

/*const char *TST_GetLibraryFileName()
{
	static const char *cszNone = "";
	int arg_i;

	for(arg_i = 1; arg_i < g_argc; arg_i++)
	{
		if(((g_argv[arg_i][0] == 'r') || (g_argv[arg_i][0] == 'R')) && (g_argv[arg_i][1] == ':'))
			return (g_argv[arg_i] + 2);
	}

	return cszNone;
}*/
