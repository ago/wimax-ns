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
#include "wimax_osal_types.h"
#include "wimax_osal_string.h"
#include "wimax_osal_primitives.h"

#include "RemoveExcessFiles.h"

#include "L4ConfigurationManager.h"
#include "TraceModule.h"
#include "L5Common.h"		

static UINT32			maxNumberOfDirectories;
static char		rootDirectoryPath[_MAX_PATH];
static char		directorySearchPath[_MAX_PATH];
typedef struct
{
	int             num_entries;
	int             max_entries;
	OSAL_FIND_DATA *files;
} flist;

extern tUtilityFunctions *pUtils;

// This method sort 2 directories by their creation time (the validity of the arguments is on the caller responsibility)
int SortDirectories(const void *a, const void *b)
{
	OSAL_filetime_ex ta = ((OSAL_FIND_DATA *) a)->ftCreationTime;	
	OSAL_filetime_ex tb = ((OSAL_FIND_DATA *) b)->ftCreationTime;		
	if (ta.dwHighDateTime > tb.dwHighDateTime)
	{
		return(-1);
	}
	else if (ta.dwHighDateTime < tb.dwHighDateTime)
	{
		return(+1);
	}
	else // high date is the same
	{
		if (ta.dwLowDateTime > tb.dwLowDateTime)
		{
			return(-1);
		}
		else
		{
			return(+1);
		}
	}
}


// This method adds a 'OSAL_FIND_DATA' struct to the file list(the validity of the arguments is on the caller responsibility)
void AddDirectory(flist* list, OSAL_FIND_DATA data)
{
	// resize the list if needed
	if (list->num_entries == list->max_entries)
	{
		int   newsize = list->max_entries == 0 ? 16 : list->max_entries * 2;
		OSAL_FIND_DATA *temp = (OSAL_FIND_DATA *) realloc(list->files, newsize * sizeof(OSAL_FIND_DATA));
		if (temp == NULL)
		{
			TRACE(TR_MOD_DND_AGENT, TR_SEV_ERR, "[AddDirectory] - Error creating directories array");
			//Check if need error code.
			return;
		}
		else
		{
			list->max_entries = newsize;
			list->files = temp;
		}
	}

	// add the new directory
	list->files[list->num_entries++] = data;
}



// 'DeleteDirectory' gets a directory name and deleted the directory (and all files in it)
void DeleteDirectory(char* rootDir)
{
	static char	filePath[_MAX_PATH];
	int				pathLength = 0;
	OSAL_findHandle			fileHandle;			// handle of the file we are currently deleting
	OSAL_FIND_DATA tempInfo;

	// create a string to look for files in the directory
	pathLength = OSAL_snprintf(filePath,  _MAX_PATH, _MAX_PATH, "%s/", rootDir);
	OSAL_snprintf(filePath + pathLength, _MAX_PATH - pathLength, _MAX_PATH - pathLength, "*");

	// first we remove all files in the directory
	fileHandle = OSAL_FindFirstFile(filePath, &tempInfo);
	if (fileHandle != INVALID_HANDLE_VALUE)
	{
		do
		{
			if ((OSAL_stricmp(tempInfo.cFileName, ".")  != 0) &&
				(OSAL_stricmp(tempInfo.cFileName, "..") != 0))
			{
				OSAL_snprintf(filePath+pathLength, _MAX_PATH - pathLength, _MAX_PATH - pathLength, tempInfo.cFileName);
				if (OSAL_delete_file(filePath) == 0)
				{
					TRACE(TR_MOD_DND_AGENT, TR_SEV_WARNING, "[DeleteDirectory] - Cannot delete file %s. Returned error: %d", filePath, GetLastError());
				}
			}
		} 
		while (OSAL_FindNextFile(fileHandle, &tempInfo));

		OSAL_FindClose(fileHandle);
	}
	else
	{
		TRACE(TR_MOD_DND_AGENT, TR_SEV_WARNING, "[DeleteDirectory]: Error finding files in directory");
	}

	// then we remove the directory itself
	if (OSAL_remove_directory(rootDir) == 0)
	{
		TRACE(TR_MOD_DND_AGENT, TR_SEV_WARNING, "[DeleteDirectory]: Error removing directory %s. Error is %d", rootDir, GetLastError());
	}
}
// This is the method that is run by the delete thread
void EraseDirectoriesThreadMethod(void *dummy)
{
	flist           list = { 0, 0, NULL };	// list of directories 
	OSAL_findHandle          searchHandle;			// handle of the directory we are currently checking
	OSAL_FIND_DATA tempInfo;
	static char	filePath[_MAX_PATH];
	int				pathLength = 0;
	int i;

	UNREFERENCED_PARAMETER(dummy);

	// create a list of directories (only trace directories)
	searchHandle = OSAL_FindFirstFile(directorySearchPath, &tempInfo);
	if (searchHandle != INVALID_HANDLE_VALUE)
	{
		do
		{
			if ((OSAL_stricmp(tempInfo.cFileName, ".")  != 0) &&
				(OSAL_stricmp(tempInfo.cFileName, "..") != 0) &&
				(tempInfo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&   // if is a directory
				((tempInfo.cFileName[0] == '2') && (tempInfo.cFileName[1] == '0') )) // trace directories start with 2008_ for instance.
			{
				AddDirectory(&list, tempInfo);
			}
		} 
		while (OSAL_FindNextFile(searchHandle, &tempInfo));

		if (GetLastError() != ERROR_NO_MORE_FILES)
		{
			TRACE(TR_MOD_DND_AGENT, TR_SEV_ERR, "[EraseDirectoriesThreadMethod]: Error reading the directories");
		}
		OSAL_FindClose(searchHandle);
	}
	else
	{
		TRACE(TR_MOD_DND_AGENT, TR_SEV_WARNING, "[EraseDirectoriesThreadMethod]: Error finding files in directory %s", directorySearchPath);
	}

	// sort the list by creation time
	qsort(list.files, list.num_entries, sizeof(OSAL_FIND_DATA), SortDirectories);

	// remove all wanted directories
	for (i = maxNumberOfDirectories; i< list.num_entries; i++)
	{
		pathLength  = OSAL_snprintf(filePath,  _MAX_PATH, _MAX_PATH, "%s", rootDirectoryPath);
		pathLength += OSAL_snprintf(filePath+pathLength, _MAX_PATH - pathLength, _MAX_PATH - pathLength, "/");
		pathLength += OSAL_snprintf(filePath+pathLength, _MAX_PATH - pathLength, _MAX_PATH - pathLength, list.files[i].cFileName);
		DeleteDirectory(filePath);
	}

	// free the file list
	free(list.files);
}

// This method deletes all dirs but the n last created (n is read from a registry key)
void EraseExcessDirectories(char* rootDir)
{
	UINT32 pathLength;
	OSAL_findHandle		fileEraseThread;

	// read the maximum number of directories from the registry
	L4Configurations_getMaxNumOfDirs(&maxNumberOfDirectories);
	
	// if 'maxNumberOfDirectories' is '0' it means we want to disable this feature
	if (maxNumberOfDirectories == 0)
	{
		return;
	}
	
	// save the root directory (for later use)
	OSAL_sprintf_s(rootDirectoryPath,  _MAX_PATH, "%s", rootDir);

	// create and save the directory search path
	pathLength = OSAL_sprintf_s(directorySearchPath,  _MAX_PATH, "%s", rootDir);
	OSAL_sprintf_s(directorySearchPath+pathLength, _MAX_PATH - pathLength, "/*");

	// Open the thread that deletes the directories
	if (0 != OSAL_create_thread(EraseDirectoriesThreadMethod, NULL, &fileEraseThread ))
	{
		TRACE(TR_MOD_DND_AGENT, TR_SEV_ERR, "[EraseExcessDirectories] - EraseExcessDirectories failed.Error creating directory erase thread");
		fileEraseThread = NULL;
	}	
}

