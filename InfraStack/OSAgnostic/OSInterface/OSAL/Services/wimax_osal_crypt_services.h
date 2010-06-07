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
#ifndef _CRYPT_SERVICES_H
#define _CRYPT_SERVICES_H

#include "wimax_osal_basictypes.h"

#define NUMBER_OF_GENERATED_BYTES_FOR_PSEUDO_NAI 17

BOOL OSAL_Crypt_EncryptBuffer(char* sourceBuffer, UINT32 bufferLength, BYTE* encryptedBuff, size_t *sizeOfEncryptedBuff);
BOOL OSAL_Crypt_DecryptBuffer(BYTE* encryptedBuff, size_t  encBuffLen, char* decryptedBuff, size_t *sizeOfDecryptedBuff);

BOOL OSAL_Crypt_ConveretDecryptedToEncryptedFile(char* binFileName, char* xmlFileName);
BOOL OSAL_Crypt_ConveretEncryptedToDecryptFile(char* xmlFileName, char* binFileName);
int OSAL_Crypt_EapCreateDecryptPass(UINT8* passwordBuff, size_t* passwordLen);
BOOL OSAL_Crypt_SetEncryptedPassword(char *password, char *passwordToEncrypt);
BOOL OSAL_Crypt_GetEncyptedPassword(char *passwordFileName, char *decryptedPassword);

BOOL OSAL_CreateRandomBit(char *pseudoNai, int buffSize);

#endif // _CRYPT_SERVICES_H