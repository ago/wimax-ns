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
#ifndef _AES_CCM_H
#define _AES_CCM_H

#include "TypesProxy.h"

#define TLEN 8
#define TLEN_BITS 64

#define BLOCK_SIZE_BITS 128
#define BLOCK_SIZE 16
#define BLOCK_SIZE_D 16.0


#define COUNTER_BLOCK_FLAGS 1	

#define B0_FLAGS 0x19
/*
*  Return code when using AES-CCM functions
*/
typedef enum
{
	AES_CCM_SUCCESS = 0,
	// [mzur][todo] check which value should be invalid - invalid if out buffer is not enough
	AES_CCM_INVALID,
	AES_CCM_BUFFER_TOO_SHORT,
	AES_CCM_KEY_ERROR,
	AES_CCM_FAILURE
} AES_CCM_ReturnCode;

AES_CCM_ReturnCode AES_CCM_Decrypt(UINT8* pCipherText, 
								   UINT8* pCipherKey, 
								   UINT8* pPlainText, 
								   UINT32 plainTextSize,
								   UINT32* actualPlainTextSize);


#endif // _AES_CCM_
