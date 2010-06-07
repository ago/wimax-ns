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
#pragma warning(disable : 4996)

#include <share.h>

#include "wimax_osal_string.h"
#include "wimax_osal_primitives.h"

#include "wmxSDK_DnD_Internal.h"
#include "wmxSDK_DnD.h"
#include "L4ConfigurationManager.h"

#include "TraceModule.h"

static UINT32			fileSignatureSDillo = 0;
static UINT32			fileSignatureNDillo = 0;
static UINT32			fileSignatureArm0 = 0;
static UINT32			fileSignatureArm1 = 0;

// ini files names
static char			arm0StringFileName[_MAX_PATH] = "";
static char			arm1StringFileName[_MAX_PATH] = "";
static char			NdilloStringFileName[_MAX_PATH] = "";
static char			SdilloStringFileName[_MAX_PATH] = "";

static char			tmpArm0StringFileName[_MAX_PATH] = "";
static char			tmpArm1StringFileName[_MAX_PATH] = "";
static char			tmpNdilloStringFileName[_MAX_PATH] = "";
static char			tmpSdilloStringFileName[_MAX_PATH] = "";


int ConnectToStringTables()
{	
	/************************************************************************/
	/* initialize String table.                                             */
	/* String table is a pure Windows element which holds strings connected */
	/* to numbers.                                                          */
	/************************************************************************/

	//char message[MAX_MESSAGE_SIZE];
	BOOL xmlRes, failedToLoadChild = FALSE;
	char *tempText;
	pXmlElement names, arm0Node, arm1Node, nDilloNode, sDilloNode, stringTables;
	char tmpPath[MAX_REGISTRY_ANSWER];
	char trcFilesPath[MAX_REGISTRY_ANSWER];

	// first we get the file names from the xml file:
	names = CreateEmptyXmlData();

	L4Configurations_getTracePath(tmpPath);	
	OSAL_strcpy_s(trcFilesPath, _MAX_PATH, tmpPath);
	OSAL_strcat_s(trcFilesPath, _MAX_PATH, "\\TrcFileNames.xml");

	xmlRes = ReadXmlFile(names, trcFilesPath);
	if (xmlRes != TRUE)
	{
		TRACE_ERR((L"[ConnectToStringTables]: cannot load %s", trcFilesPath));
		FreeXmlData(names);
		return -1;
	}

	stringTables = FindChild(names, "StringFiles");
	arm0Node   = FindChild(stringTables, "Arm0");
	arm1Node   = FindChild(stringTables, "Arm1");
	nDilloNode = FindChild(stringTables, "NDillo");
	sDilloNode = FindChild(stringTables, "SDillo");

	// copy file names
	if (arm0Node != NULL)
	{
		tempText = (char*)GetElementInnerText(arm0Node);
		if (tempText != NULL && strcmp(tempText,""))
		{
			OSAL_strcpy_s(arm0StringFileName, _MAX_PATH, tmpPath);
			OSAL_strcat_s(arm0StringFileName, _MAX_PATH, "\\");			
			OSAL_strcat_s(arm0StringFileName, _MAX_PATH, tempText);			
		}
	}
	if (arm1Node != NULL)
	{
		tempText = (char*)GetElementInnerText(arm1Node);
		if (tempText != NULL && strcmp(tempText,""))
		{
			OSAL_strcpy_s(arm1StringFileName, _MAX_PATH, tmpPath);
			OSAL_strcat_s(arm1StringFileName, _MAX_PATH, "\\");	
			OSAL_strcat_s(arm1StringFileName, _MAX_PATH, tempText);			
		}
	}
	if (nDilloNode != NULL)
	{
		tempText = (char*)GetElementInnerText(nDilloNode);
		if (tempText != NULL && strcmp(tempText,""))
		{
			OSAL_strcpy_s(NdilloStringFileName, _MAX_PATH, tmpPath);
			OSAL_strcat_s(NdilloStringFileName, _MAX_PATH, "\\");			
			OSAL_strcat_s(NdilloStringFileName, _MAX_PATH, tempText);			
		}
	}
	if (sDilloNode != NULL)
	{
		tempText = (char*)GetElementInnerText(sDilloNode);
		if (tempText != NULL && strcmp(tempText,""))
		{
			OSAL_strcpy_s(SdilloStringFileName, _MAX_PATH, tmpPath);
			OSAL_strcat_s(SdilloStringFileName, _MAX_PATH, "\\");			
			OSAL_strcat_s(SdilloStringFileName, _MAX_PATH, tempText);			
		}
	}

	// free the xml document. this frees all inner xml nodes
	FreeXmlData(names);

	// load the string files
	if(hStringTableArm0 == INVALID_HSTRING_TABLE)
	{
		if(arm0StringFileName[0] != '\0') // if the node is not empty
		{
			hStringTableArm0 = TST_LoadLibrary(arm0StringFileName,(LPVOID)&fileSignatureArm0, sizeof(fileSignatureArm0));
			if(hStringTableArm0 == INVALID_HSTRING_TABLE)
			{
				failedToLoadChild = TRUE;
				TRACE_ERR(("[ConnectToStringTables]: cannot load Arm 0 string table file: %s", arm0StringFileName));
			}
		}
	}
	if(hStringTableArm1 == INVALID_HSTRING_TABLE)
	{
		if(arm1StringFileName[0] != '\0')
		{
			hStringTableArm1 = TST_LoadLibrary(arm1StringFileName, (LPVOID)&fileSignatureArm1, sizeof(fileSignatureArm1));
			if(hStringTableArm1 == INVALID_HSTRING_TABLE)
			{
				failedToLoadChild = TRUE;
				TRACE_ERR(("[ConnectToStringTables]: cannot load Arm 1 string table file: %s", arm1StringFileName));
			}
		}
	}
	if(hStringTableSDillo == INVALID_HSTRING_TABLE)
	{
		if(SdilloStringFileName[0] != '\0')
		{
			hStringTableSDillo = TST_LoadLibrary(SdilloStringFileName, (LPVOID)&fileSignatureSDillo, sizeof(fileSignatureSDillo));
			if(hStringTableSDillo == INVALID_HSTRING_TABLE)
			{
				failedToLoadChild = TRUE;
				TRACE_ERR(("[ConnectToStringTables]: cannot load SDillo string table file: %s", SdilloStringFileName));
			}
		}
	}
	if(hStringTableNDillo == INVALID_HSTRING_TABLE)
	{
		if(NdilloStringFileName[0] != '\0')
		{
			hStringTableNDillo =	TST_LoadLibrary(NdilloStringFileName, (LPVOID)&fileSignatureNDillo, sizeof(fileSignatureNDillo));
			if(hStringTableNDillo == INVALID_HSTRING_TABLE)
			{
				failedToLoadChild = TRUE;
				TRACE_ERR(("[ConnectToStringTables]: cannot load NDillo string table file: %s", NdilloStringFileName));
			}
		}
	}

	if (failedToLoadChild)
		return -2;

	return 0;
}

void FreeStringTables()
{
	if (hStringTableArm0 != INVALID_HSTRING_TABLE)
	{
		TST_FreeLibrary(hStringTableArm0);
		hStringTableArm0 = INVALID_HSTRING_TABLE;
	}
	if (hStringTableArm1 != INVALID_HSTRING_TABLE)
	{
		TST_FreeLibrary(hStringTableArm1);
		hStringTableArm1 = INVALID_HSTRING_TABLE;
	}
	if (hStringTableNDillo != INVALID_HSTRING_TABLE)
	{
		TST_FreeLibrary(hStringTableNDillo);
		hStringTableNDillo = INVALID_HSTRING_TABLE;
	}
	if (hStringTableSDillo != INVALID_HSTRING_TABLE)
	{
		TST_FreeLibrary(hStringTableSDillo);
		hStringTableSDillo = INVALID_HSTRING_TABLE;
	}
}


//FILE* GetFirstFile(WCHAR * path, UINT32* nextFileIndex, WCHAR * prefix, UINT32 maxNumOfFiles, BOOL isOnline)
//{
//	UINT32 nextFile = *nextFileIndex;
//	FILE* tempFile;
//	if (isOnline)
//	{
//		return GetNextFile(path, nextFile, prefix);
//	}
//
//	for (int i = 0; i < maxNumOfFiles; i++)
//	{
//		tempFile = GetNextFile(path, nextFile, prefix);
//		if (NULL != tempFile)
//		{
//			*nextFileIndex = nextFile;
//			return tempFile;
//		}
//		nextFile++;
//	}
//
//	return NULL;
//}
FILE * GetNextFile(const WCHAR * path, UINT32 nextFileIndex, WCHAR * prefix)
{
	int i;
	WCHAR logFileName[MAX_PATH];
	char tmpName[MAX_PATH];
	FILE * res;

	// Create log file name. filename = dir + filename + "." + extension
	wcscpy(logFileName, path);
	wcscat(logFileName, L"\\");
	wcscat(logFileName, prefix);

	for (i=0; i<LOG_NUM_STR_LENGTH - GetLeadingZeros(nextFileIndex); i++)
	{
		wcscat(logFileName, L"0");
	}

	_itow(nextFileIndex, &(logFileName[wcslen(logFileName)]), 10);
	wcscat(logFileName, L".log");
	WideCharToMultiByte(CP_ACP, 0, logFileName, MAX_PATH, tmpName, MAX_PATH, NULL, NULL);
	OSAL_fopen(&res, tmpName, "rb", _SH_DENYNO);
	return res;
}

INT32 GetLeadingZeros(INT32 num)
{
	int zeros = 0;

	do
	{
		zeros++;
		num /= 10;
	} while(num > 0);

	return zeros;
}


HStringTable GetStringTableArm0()
{
	return hStringTableArm0;
}
HStringTable GetStringTableArm1()
{
	return hStringTableArm1;
}
HStringTable GetStringTableSDillo()
{
	return hStringTableSDillo;
}
HStringTable GEStringTableTNDillo()
{
	return hStringTableNDillo;
}


UINT32 GetSignatureArm0()
{
	return fileSignatureArm0;
}
UINT32 GetSignatureArm1()
{
	return fileSignatureArm1;
}
UINT32 GetSignatureSDillo()
{
	return fileSignatureSDillo;
}
UINT32 GetSignatureNDillo()
{
	return fileSignatureNDillo;
}


