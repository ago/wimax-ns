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
#ifndef _TRACE_STRING_TABLES_H
#define _TRACE_STRING_TABLES_H

/************************************* Defines ********************************************/
#include <windows.h>
/** 
	Defines type for String Table handle. To be used to reference specific table.
*/
#define	HStringTable			int

/** 
	Denotes the invalid handle for String Table handle.
*/
#define INVALID_HSTRING_TABLE	((int)-1)

/************************************* Functions ******************************************/

/**
	Loading specific Trace String Table library.
	@param libraryFileName - File name to load string Table from.
	@param headerBuf - buffer to put header in.
	@param headerSize - size of the file header.
	@return handle to the new loaded library, INVALID_HSTRING_TABLE on a failure.
*/
HStringTable	TST_LoadLibrary	(char* libraryFileName, LPVOID headerBuf, UINT32 headerSize);

/**
	UnLoading specific Trace String Table library.
	@param StringTable - handle to the library.
*/
void			TST_FreeLibrary	(	HStringTable	stringTable);

/**
	Retrieves string from specific String Table library (according to string ID).
	@param StringTable - handle to the library.
	@param dwStringID - String ID of the string to retrieve.
	@param buffer - pointer to the buffer for the string.
	@param iBufferSize - the size of the buffer.
	@return non-zero upon success, 0 otherwise.
*/
int				TST_LoadString	(	HStringTable	stringTable, 
									UINT32			dwStringID,
									char*			buffer,
									int				iBufferSize);

/**
	Retrieves string from specific String Table library (according to string ID).
	@param StringTable - handle to the library.
	@param dwSectionID - String ID of the string to retrieve.
	@param sectionBuffer - pointer to the buffer for the section.
	@param sectionSize - the size of the buffer (section).
	@return non-zero upon success, 0 otherwise.
*/
int				TST_LoadSection	(	HStringTable	stringTable, 
									UINT32			dwSectionID,
									LPVOID			sectionBuffer,
									UINT32			sectionSize);


#endif // _TRACE_STRING_TABLES_H
