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
#include "wimax_osal_types.h"
#include "wimax_osal_string.h"

#include "TraceModule.h"

#include <math.h>
#include <stdlib.h>
#include "AES_CCM.h"
#include "TypesProxy.h"
#include "AES.h"
#include "bootstrap.h"


// [MZUR][TODO] remove constant
#define  NONCE_OFFSET 14
//	Version (2 byte)
//	protocol (2 byte)
//	Length (4 byte)
//	Tag for Nonce (2 byte)
//	Nonce length (4 bytes)
//	Nonce (13 bytes)
//  Tag for cipher (2 byte)
//	cipher Length (4 bytes)
//  cipher text

VOID GenerateCounterBlock(UINT8 block[BLOCK_SIZE], UINT16 blockIndex, UINT8* pNonce, UINT32 nonceLen);
AES_CCM_ReturnCode ValidateSigniture(UINT8* pPlainText, UINT32 plainTextLen, UINT8* pNonce, 
									 UINT32 nonceLen, UINT8 T[BLOCK_SIZE], AES_keyInstance key);

// clen - length in bits
AES_CCM_ReturnCode AES_CCM_Decrypt(UINT8* pCipherText,  
								   UINT8* pCipherKey, 
								   UINT8* pPlainText,
								   UINT32 plainTextSize, 
								   UINT32* actualPlainTextSize)
{		
	UINT32 cipherLength = 0;	
	// number of payload blocks
	UINT32 payloadBlockNum;
	UINT16 blockIndex;

	UINT8 pCurrCounterBlock[BLOCK_SIZE];	

	UINT8* pCounterBlocks = NULL; // S 
	UINT8* pTempCounterBlocks;
	UINT8* pPayload;

	UINT8* pNonce;
	UINT32 nonceLen;

	AES_keyInstance keyInstance;
	UINT32 outBitOffset;
	AES_CCM_ReturnCode res;

	UINT8 T[TLEN];

	TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "AES_CCM_Decrypt (IN)");
	BM_BootstrapMessage_CiphertextLength_GET(pCipherText, 0, cipherLength);
	TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_DEBUG, "AES_CCM_Decrypt cipher len=%d", cipherLength);

	// Package size must be at least size of 
	if (cipherLength <= TLEN)
	{
		TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_DEBUG, "AES_CCM_Decrypt Invalid cipher len size");
		res = AES_CCM_INVALID;
		goto decrypt_exit;
	}

	// Generate Round keys from cipher key for AES:
	if(AES_SUCCESS != AES_SetEncryptKey(&keyInstance, pCipherKey, KEY_128))
	{	
		TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_DEBUG, "AES_CCM_Decrypt Failed to generate encryption key");
		res = AES_CCM_KEY_ERROR;
		goto decrypt_exit;
	}

	// Get nonce for cipher text
	BM_BootstrapMessage_NonceLength_GET(pCipherText, 0, nonceLen);	
	BM_BootstrapMessage_Nonce_GET_POS(pCipherText, 0, pNonce, outBitOffset);

	// Calculate number of payload blocks (+1 for counter block zero)
	payloadBlockNum = (UINT32)ceil(((double)cipherLength - (double)TLEN)/BLOCK_SIZE_D) + 1;

	pCounterBlocks = malloc((payloadBlockNum)*BLOCK_SIZE);		
	TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_DEBUG, "AES_CCM_Decrypt payloadBlockNum is [%d]", payloadBlockNum);
	if (pCounterBlocks == NULL)
	{
		TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_DEBUG, "AES_CCM_Decrypt Failed to alloc memory");
		res = AES_CCM_FAILURE;
		goto decrypt_exit;
	}

	pTempCounterBlocks = pCounterBlocks;

	TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_DEBUG, "AES_CCM_Decrypt- creating counter blocks");

	// Create counter blocks
	for (blockIndex=0; blockIndex<payloadBlockNum; blockIndex++)
	{		
		GenerateCounterBlock(pCurrCounterBlock, blockIndex, pNonce, nonceLen);		

		memcpy(pTempCounterBlocks, pCurrCounterBlock, BLOCK_SIZE);
		//AES_EncryptBlock(&keyInstance, pCurrCounterBlock, pTempCounterBlocks);

		pTempCounterBlocks = pTempCounterBlocks + BLOCK_SIZE;
	}

	pTempCounterBlocks = pCounterBlocks;

	for (blockIndex=0; blockIndex<payloadBlockNum; blockIndex++)
	{		
		GenerateCounterBlock(pCurrCounterBlock, blockIndex, pNonce, nonceLen);				

		AES_EncryptBlock(&keyInstance, pCurrCounterBlock, pTempCounterBlocks);

		pTempCounterBlocks = pTempCounterBlocks + BLOCK_SIZE;
	}

	BM_BootstrapMessage_Ciphertext_GET_POS(pCipherText, 0, pPayload, outBitOffset);

	*actualPlainTextSize = cipherLength - TLEN;

	if (*actualPlainTextSize > plainTextSize)
	{
		TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_DEBUG, "AES_CCM_Decrypt buffer to short");
		res = AES_CCM_BUFFER_TOO_SHORT;
		goto decrypt_exit;
	}

	TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_DEBUG, "AES_CCM_Decrypt- get plain text");
	AES_Xor(pPayload, pCounterBlocks + BLOCK_SIZE, *actualPlainTextSize, pPlainText);

	// Calculate T
	AES_Xor(pCounterBlocks, pPayload + *actualPlainTextSize, TLEN, T);

	///// Validate buffer.
	res = ValidateSigniture(pPlainText, *actualPlainTextSize, pNonce, nonceLen, T, keyInstance);	
	TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_DEBUG, "AES_CCM_Decrypt validate buffer result=%d", res);
	//res = AES_CCM_SUCCESS;
decrypt_exit:
	if (pCounterBlocks != NULL)
	{
		pTempCounterBlocks = NULL;
		free(pCounterBlocks);

	}

	TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "AES_CCM_Decrypt (OUT) res=%d", res);
	return  res;
}

VOID GenerateCounterBlock(UINT8 block[BLOCK_SIZE], UINT16 blockIndex, UINT8* pNonce, UINT32 nonceLen)
{
	// Set Flags
	block[0] = COUNTER_BLOCK_FLAGS;
	memcpy(&block[1], pNonce, nonceLen);
	block[15] = (UINT8)blockIndex & 0xff;
	block[14] = (UINT8)((blockIndex & 0xff00) >> 8);
}

// Length - in bytes
// pPayload is encrypted data + MAC.
// payloadLen is the total length of the buffer which includes the MAC. 
AES_CCM_ReturnCode ValidateSigniture(UINT8* pPlainText, UINT32 plainTextLen, UINT8* pNonce, 
									 UINT32 nonceLen, UINT8 T[BLOCK_SIZE], AES_keyInstance key)
{
	AES_CCM_ReturnCode status = AES_CCM_INVALID;
	UINT8 B0[BLOCK_SIZE];
	UINT8 Y0[BLOCK_SIZE];	

	UINT8 prevYxBlock[BLOCK_SIZE];
	UINT8 currBxBlock[BLOCK_SIZE];
	UINT8 xorRes[BLOCK_SIZE];

	//AES_keyInstance keyInstance;
	UINT32 padNum = 0;
	UINT32 i;
	UINT32 r = 0;
	// this should be the length without the MAC length
	//UINT32 payloadDataLen;
	UINT8* pBufferWithPadding = NULL;
	UINT32 bufferWithPadLen = 0;

	TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "AES_CCM ValidateSigniture (IN)");

	// Create payload data buffer + padding
	r = (UINT32)ceil(((double)plainTextLen)/BLOCK_SIZE_D);

	bufferWithPadLen = r*BLOCK_SIZE;
	pBufferWithPadding = malloc(bufferWithPadLen);

	if (pBufferWithPadding == NULL)
	{
		status = AES_CCM_FAILURE;
		TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "Failed to alloc pPayloadWithPadding");
		goto ValidateSignitureExit;
	}

	// Pad the payload buffer to block size if needed
	padNum = bufferWithPadLen - plainTextLen;

	// Copy the payload data to the temp buffer
	memcpy(pBufferWithPadding, pPlainText, plainTextLen);

	// Add padding if needed
	if (padNum != 0)
	{
		for (i=0; i<padNum; i++)
		{
			pBufferWithPadding[plainTextLen + i] = 0x0;
		}
	}

	//// Generate Round keys from cipher key for AES:
	//if(AES_SUCCESS != AES_SetEncryptKey(&keyInstance, pCipherKey, KEY_128))
	//{		
	//	status = AES_CCM_KEY_ERROR;
	//	TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "Failed to create key");
	//	goto ValidateSignitureExit;
	//		
	//}

	// Create B0 Block
	B0[0] = B0_FLAGS;
	memcpy(&B0[1], pNonce, nonceLen);
	B0[15] = (UINT8)(plainTextLen) & 0xff;
	B0[14] = (UINT8)(((plainTextLen) & 0xff00) >> 8);

	// Create Y0
	AES_EncryptBlock(&key, B0, Y0);

	memcpy(prevYxBlock, Y0, BLOCK_SIZE);	
	for (i=1; i<=r; i++)
	{
		// Copy current B block from payload
		// B1-Br are just the payload blocks since a=0 for associated data according to the standard.
		memcpy(currBxBlock, pBufferWithPadding + (i-1)*BLOCK_SIZE, BLOCK_SIZE); 
		// Create xor Bi and Yi-1
		AES_Xor(prevYxBlock, currBxBlock, BLOCK_SIZE, xorRes);
		AES_EncryptBlock(&key, xorRes, prevYxBlock);
	}

	// Compare Yr and T (message auth code)
	if (memcmp(T, prevYxBlock, TLEN) != 0)
	{
		status = AES_CCM_INVALID;
		goto ValidateSignitureExit;
	}

	status = AES_CCM_SUCCESS;
ValidateSignitureExit:
	if (pBufferWithPadding != NULL)
	{
		free(pBufferWithPadding);
	}

	TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "AES_CCM ValidateSigniture (OUT) res=%d", status);
	return status;
}

AES_CCM_ReturnCode Encrypt(UINT8* pPlainText, UINT32 plainTextLen, UINT8* pNonce, UINT32 nonceLen, UINT8* pCipherKey, 
						   UINT8** pCipherText, UINT16* cipherLen)
{
	AES_keyInstance keyInstance;

	UINT8 Y[BLOCK_SIZE];
	UINT8 B0[BLOCK_SIZE];
	UINT8 currBlock[BLOCK_SIZE];
	UINT8 xorRes[BLOCK_SIZE];
	UINT8 T[TLEN];
	UINT8 currCounterBlock[BLOCK_SIZE];

	UINT8* S;
	UINT8* tempS;	
	UINT8* tempCipher;

	UINT16 blockIndex;
	UINT16 numOfPlainBlocks;
	UINT16 numOfCounterBlocks;

	UNREFERENCED_PARAMETER(cipherLen);

	// Create B0 Block
	B0[0] = B0_FLAGS;
	memcpy(&B0[1], pNonce, nonceLen);
	B0[15] = (UINT8)(plainTextLen) & 0xff;
	B0[14] = (UINT8)(((plainTextLen) & 0xff00) >> 8);

	// Generate Round keys from cipher key for AES:
	if(AES_SUCCESS != AES_SetEncryptKey(&keyInstance, pCipherKey, KEY_128))
	{		
		return AES_CCM_KEY_ERROR;
	}

	// Create Y0
	AES_EncryptBlock(&keyInstance, B0, Y);

	numOfPlainBlocks = (UINT16)plainTextLen/BLOCK_SIZE;

	for (blockIndex=1; blockIndex<=numOfPlainBlocks; blockIndex++)
	{
		memcpy(currBlock, pPlainText + BLOCK_SIZE*(blockIndex-1), BLOCK_SIZE);

		AES_Xor(currBlock, Y, BLOCK_SIZE, xorRes);

		AES_EncryptBlock(&keyInstance, xorRes, Y);
	}

	memcpy(T, Y, TLEN);

	numOfCounterBlocks = (UINT16)ceil(plainTextLen/BLOCK_SIZE_D);

	S = malloc(numOfCounterBlocks*BLOCK_SIZE);

	tempS = S;

	for (blockIndex=1; blockIndex<=numOfCounterBlocks; blockIndex++)	
	{
		GenerateCounterBlock(currCounterBlock, blockIndex, pNonce, nonceLen);

		AES_EncryptBlock(&keyInstance, currCounterBlock, tempS);

		tempS = tempS + BLOCK_SIZE;
	}

	AES_Xor(pPlainText, S + BLOCK_SIZE, plainTextLen, *pCipherText);

	tempCipher = *pCipherText;

	tempCipher = tempCipher + plainTextLen;

	AES_Xor(T, S, TLEN, tempCipher);
	free(S);
	return AES_CCM_SUCCESS;
}

