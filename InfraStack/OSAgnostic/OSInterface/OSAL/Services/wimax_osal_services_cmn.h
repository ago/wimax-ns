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
#ifndef _WIMAX_OSAL_SERVICES_CMN_H_
#define _WIMAX_OSAL_SERVICES_CMN_H_

#include "wimax_osal_types.h"

#define OSAL_BASIC_DB_FILE_SIZE	(14 * 1024)
#define OSAL_DEFUALT_CHUNK_SIZE 1024
#define OSAL_DEFUALT_STR_LEN		1024
#define OSAL_EAP_PASSWORD_SIZE 256
#define OSAL_SYSTEM_FILE_NOT_FOUND		2

#define WIN32_STRING "Windows.32"
#define WIN95_STRING "Windows.95"
#define WIN98_STRING "Windows.98"
#define WINNT_STRING "Windows.NT"
#define WINXP_STRING "Windows.XP"
#define WIN2000_STRING "Windows.2000"
#define WINVISTA_STRING "Windows.Vista"
#define WIN7_STRING "Windows.Win7"
#define SP1_STRING_FULL_NAME "Service Pack 1"
#define SP2_STRING_FULL_NAME "Service Pack 2"
#define SP3_STRING_FULL_NAME "Service Pack 3"
#define SP4_STRING_FULL_NAME "Service Pack 4"
#define SP5_STRING_FULL_NAME "Service Pack 5"
#define SP6_STRING_FULL_NAME "Service Pack 6"
#define SP1_STRING_SHORT_NAME "SP1"
#define SP2_STRING_SHORT_NAME "SP2"
#define SP3_STRING_SHORT_NAME "SP3"
#define SP4_STRING_SHORT_NAME "SP4"
#define SP5_STRING_SHORT_NAME "SP5"
#define SP6_STRING_SHORT_NAME "SP6"

#define OSAL_SERVER_ID_SIZE				32
#define OSAL_DEV_ID_SIZE					64

#define OSAL_DEVICE_VERSION_MAX_LENGTH 64
#define OSAL_FreeIfAllocated(x) { if (x != NULL) { free(x); x = NULL; } }

#define DIGEST_LEN 16

int OSAL_doubleSlashInPath(char* srcStr, char* dstStr, int nSizeOfDst);
void OSAL_BuildFullPath(char* src, char* dstFull, int nSizeFull);
BOOL OSAL_writeData (BYTE *buf, UINT32 bufSize, const char* fileName);
BOOL OSAL_readData (const char *fileName, BYTE *buf, size_t *bufSize);
BOOL OSAL_FindDeviceFileName(char *deviceName);
BOOL OSAL_GetOSVersion(char *osVersion);
void OSAL_ByteArrayToCharArray(UINT32 buffSize, void* pbuffData, char * pseudoNai);
void OSAL_CalcSecret(char* serverID, char* serialnumber, char* sharedSecret, char* result, size_t * resultSize);
BOOL XUTILS_BinToStr64(UINT8*   pPduBin, UINT32      lBinDataLen,
					   char*  p64BaseStr, size_t *  p64BaseStrLen);


#endif //_WIMAX_OSAL_SERVICES_CMN_H_