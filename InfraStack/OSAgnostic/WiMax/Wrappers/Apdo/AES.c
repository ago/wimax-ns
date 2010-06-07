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
#define _PRIVATE_AES_H


#include "TypesProxy.h"
#include "AES.h"
#include "AES_private.h"

AES_ReturnCode AES_SetEncryptKey(AES_keyInstance* pEncryptKey, const UINT8* pCipherKey,AES_KEY_SIZE keyLength)
{
    INT32 i = 0;
    UINT32 temp;
    UINT32 * pKeyBuff = (UINT32 *) &pEncryptKey->roundKey;
    
    if ( !( keyLength == KEY_128 || keyLength == KEY_192  || keyLength == KEY_256) ) // Wrong size input key
    {
        return AES_ERROR;
    }

    pKeyBuff[0] = GETuint32(pCipherKey     );
    pKeyBuff[1] = GETuint32(pCipherKey +  4);
    pKeyBuff[2] = GETuint32(pCipherKey +  8);
    pKeyBuff[3] = GETuint32(pCipherKey + 12);
    if (keyLength == KEY_128)
    {
        for (;;)
        {
            temp  = pKeyBuff[3];
            pKeyBuff[4] = (	pKeyBuff[0] ^
                (ENCRYPTION_SBOX_4[(temp >> 16) & 0xff] & 0xff000000) ^
                (ENCRYPTION_SBOX_4[(temp >>  8) & 0xff] & 0x00ff0000) ^
                (ENCRYPTION_SBOX_4[(temp      ) & 0xff] & 0x0000ff00) ^
                (ENCRYPTION_SBOX_4[(temp >> 24)       ] & 0x000000ff) ^
                ROUND_CONSTANT[i]);
            pKeyBuff[5] = pKeyBuff[1] ^ pKeyBuff[4];
            pKeyBuff[6] = pKeyBuff[2] ^ pKeyBuff[5];
            pKeyBuff[7] = pKeyBuff[3] ^ pKeyBuff[6];
            if (++i == 10)
            {
                pEncryptKey->rounds = 10;
                return AES_SUCCESS;
            }
            pKeyBuff += 4;
        }
    }

    pKeyBuff[4] = GETuint32(pCipherKey + 16);
    pKeyBuff[5] = GETuint32(pCipherKey + 20);
    if (keyLength == KEY_192)
    {
        for (;;)
        {
            temp = pKeyBuff[ 5];
            pKeyBuff[6] = (pKeyBuff[ 0] ^
                (ENCRYPTION_SBOX_4[(temp >> 16) & 0xff] & 0xff000000) ^
                (ENCRYPTION_SBOX_4[(temp >>  8) & 0xff] & 0x00ff0000) ^
                (ENCRYPTION_SBOX_4[(temp      ) & 0xff] & 0x0000ff00) ^
                (ENCRYPTION_SBOX_4[(temp >> 24)       ] & 0x000000ff) ^
                ROUND_CONSTANT[i]);
            pKeyBuff[7] = pKeyBuff[1] ^ pKeyBuff[6];
            pKeyBuff[8] = pKeyBuff[2] ^ pKeyBuff[7];
            pKeyBuff[9] = pKeyBuff[3] ^ pKeyBuff[8];
            if (++i == 8)
            {
                pEncryptKey->rounds = 12;
                return AES_SUCCESS;
            }
            pKeyBuff[10] = pKeyBuff[4] ^ pKeyBuff[9];
            pKeyBuff[11] = pKeyBuff[5] ^ pKeyBuff[10];
            pKeyBuff += 6;
        }
    }


    pKeyBuff[6] = GETuint32(pCipherKey + 24);
    pKeyBuff[7] = GETuint32(pCipherKey + 28);
    if (keyLength == KEY_256)
    {
        for (;;)
        {
            temp = pKeyBuff[7];
            pKeyBuff[8] = (pKeyBuff[0] ^
                (ENCRYPTION_SBOX_4[(temp >> 16) & 0xff] & 0xff000000) ^
                (ENCRYPTION_SBOX_4[(temp >>  8) & 0xff] & 0x00ff0000) ^
                (ENCRYPTION_SBOX_4[(temp      ) & 0xff] & 0x0000ff00) ^
                (ENCRYPTION_SBOX_4[(temp >> 24)       ] & 0x000000ff) ^
                ROUND_CONSTANT[i]);
            pKeyBuff[9] = pKeyBuff[1] ^ pKeyBuff[8];
            pKeyBuff[10] = pKeyBuff[2] ^ pKeyBuff[9];
            pKeyBuff[11] = pKeyBuff[3] ^ pKeyBuff[10];
            if (++i == 7)
            {
                pEncryptKey->rounds = 14;
                return AES_SUCCESS;
            }
            temp = pKeyBuff[11];
            pKeyBuff[12] = (pKeyBuff[4] ^
                (ENCRYPTION_SBOX_4[(temp >> 24)       ] & 0xff000000) ^
                (ENCRYPTION_SBOX_4[(temp >> 16) & 0xff] & 0x00ff0000) ^
                (ENCRYPTION_SBOX_4[(temp >>  8) & 0xff] & 0x0000ff00) ^
                (ENCRYPTION_SBOX_4[(temp      ) & 0xff] & 0x000000ff));
            pKeyBuff[13] = pKeyBuff[5] ^ pKeyBuff[12];
            pKeyBuff[14] = pKeyBuff[6] ^ pKeyBuff[13];
            pKeyBuff[15] = pKeyBuff[7] ^ pKeyBuff[14];

            pKeyBuff +=8 ;
        }
    }
    return AES_SUCCESS;
}


AES_ReturnCode AES_SetDecryptKey(AES_keyInstance* pDecryptKey, const UINT8* pCipherKey, AES_KEY_SIZE keyLength)
{
    INT32 i, j;
    UINT32 temp;

    if ( !( keyLength == KEY_128 || keyLength == KEY_192  || keyLength == KEY_256) ) // Wrong size input key
    {
        return AES_ERROR;
    }


    /* expand the cipher key: */

    if(AES_SUCCESS != AES_SetEncryptKey(pDecryptKey,pCipherKey, keyLength))
    {
        return AES_ERROR;
    }

    /* invert the order of the round keys: */
    for (i = 0, j = 4 *pDecryptKey->rounds ; i < j; i += 4, j -= 4)
    {
        temp						    = pDecryptKey->roundKey[i];
        pDecryptKey->roundKey[i]        = pDecryptKey->roundKey[j];
        pDecryptKey->roundKey[j]	    = temp;

        temp							= pDecryptKey->roundKey[i + 1];
        pDecryptKey->roundKey[i + 1]	= pDecryptKey->roundKey[j + 1];
        pDecryptKey->roundKey[j + 1]	= temp;

        temp							= pDecryptKey->roundKey[i + 2];
        pDecryptKey->roundKey[i + 2]	= pDecryptKey->roundKey[j + 2];
        pDecryptKey->roundKey[j + 2]	= temp;

        temp							= pDecryptKey->roundKey[i + 3];	
        pDecryptKey->roundKey[i + 3]	= pDecryptKey->roundKey[j + 3];	
        pDecryptKey->roundKey[j + 3]	= temp;
    }
    /*
        Apply the inverse MixColumn transform to all round keys but the first
        and the last:
    */
    for (i = 1, j=4; i < pDecryptKey->rounds; i++, j+=4)
    {

        pDecryptKey->roundKey[ 0 + j ]= 
            (
            DECRYPTION_SBOX_0[ENCRYPTION_SBOX_4[(pDecryptKey->roundKey[ 0 + j ] >> 24)			] & 0xff]	^
            DECRYPTION_SBOX_1[ENCRYPTION_SBOX_4[(pDecryptKey->roundKey[ 0 + j ] >> 16) & 0xff] & 0xff]		^
            DECRYPTION_SBOX_2[ENCRYPTION_SBOX_4[(pDecryptKey->roundKey[ 0 + j ] >>  8) & 0xff] & 0xff]		^
            DECRYPTION_SBOX_3[ENCRYPTION_SBOX_4[(pDecryptKey->roundKey[ 0 + j ]        ) & 0xff] & 0xff]	
            );

            pDecryptKey->roundKey[ 1 + j ]= 
                (
                DECRYPTION_SBOX_0[ENCRYPTION_SBOX_4[(pDecryptKey->roundKey[ 1 + j ] >> 24)			] & 0xff]	^
                DECRYPTION_SBOX_1[ENCRYPTION_SBOX_4[(pDecryptKey->roundKey[ 1 + j ] >> 16) & 0xff] & 0xff]		^
                DECRYPTION_SBOX_2[ENCRYPTION_SBOX_4[(pDecryptKey->roundKey[ 1 + j ] >>  8) & 0xff] & 0xff]		^
                DECRYPTION_SBOX_3[ENCRYPTION_SBOX_4[(pDecryptKey->roundKey[ 1 + j ]        ) & 0xff] & 0xff]	
                );

                pDecryptKey->roundKey[ 2 + j ]= 
                    (
                    DECRYPTION_SBOX_0[ENCRYPTION_SBOX_4[(pDecryptKey->roundKey[ 2 + j ] >> 24)			] & 0xff]	^
                    DECRYPTION_SBOX_1[ENCRYPTION_SBOX_4[(pDecryptKey->roundKey[ 2 + j ] >> 16) & 0xff] & 0xff]		^
                    DECRYPTION_SBOX_2[ENCRYPTION_SBOX_4[(pDecryptKey->roundKey[ 2 + j ] >>  8) & 0xff] & 0xff]		^
                    DECRYPTION_SBOX_3[ENCRYPTION_SBOX_4[(pDecryptKey->roundKey[ 2 + j ]		 ) & 0xff] & 0xff]
                    );

                    pDecryptKey->roundKey[ 3 + j ]= 
                        (
                        DECRYPTION_SBOX_0[ENCRYPTION_SBOX_4[(pDecryptKey->roundKey[ 3 + j ] >> 24)			] & 0xff]	^
                        DECRYPTION_SBOX_1[ENCRYPTION_SBOX_4[(pDecryptKey->roundKey[ 3 + j ] >> 16) & 0xff] & 0xff]		^
                        DECRYPTION_SBOX_2[ENCRYPTION_SBOX_4[(pDecryptKey->roundKey[ 3 + j ] >>  8) & 0xff] & 0xff]		^
                        DECRYPTION_SBOX_3[ENCRYPTION_SBOX_4[(pDecryptKey->roundKey[ 3 + j ]        ) & 0xff] & 0xff]	
                        );
    }

    return AES_SUCCESS;
}


VOID AES_EncryptBlock(const AES_keyInstance * pEncryptKey,
                      const UINT8 plainText[AES_BLOCK_SIZE], 
                      UINT8 cipherText[AES_BLOCK_SIZE])
{		        
			        
    UINT32 s0, s1, s2, s3, t0, t1, t2, t3;
    UINT32 lastRoundPos;


    lastRoundPos = pEncryptKey->rounds << 2;
    
        // map byte array block to cipher state and add initial round pKey:

    s0 = GETuint32(plainText     ) ^ pEncryptKey->roundKey[0];

    s1 = GETuint32(plainText +  4) ^ pEncryptKey->roundKey[1];

    s2 = GETuint32(plainText +  8) ^ pEncryptKey->roundKey[2];

    s3 = GETuint32(plainText + 12) ^ pEncryptKey->roundKey[3];


    /* round 1: */

    t0 = ENCRYPTION_SBOX_0[s0 >> 24] ^ ENCRYPTION_SBOX_1[(s1 >> 16) & 0xff] ^ ENCRYPTION_SBOX_2[(s2 >>  8) & 0xff] ^ ENCRYPTION_SBOX_3[s3 & 0xff] ^ pEncryptKey->roundKey[ 4];

    t1 = ENCRYPTION_SBOX_0[s1 >> 24] ^ ENCRYPTION_SBOX_1[(s2 >> 16) & 0xff] ^ ENCRYPTION_SBOX_2[(s3 >>  8) & 0xff] ^ ENCRYPTION_SBOX_3[s0 & 0xff] ^ pEncryptKey->roundKey[ 5];

    t2 = ENCRYPTION_SBOX_0[s2 >> 24] ^ ENCRYPTION_SBOX_1[(s3 >> 16) & 0xff] ^ ENCRYPTION_SBOX_2[(s0 >>  8) & 0xff] ^ ENCRYPTION_SBOX_3[s1 & 0xff] ^ pEncryptKey->roundKey[ 6];

    t3 = ENCRYPTION_SBOX_0[s3 >> 24] ^ ENCRYPTION_SBOX_1[(s0 >> 16) & 0xff] ^ ENCRYPTION_SBOX_2[(s1 >>  8) & 0xff] ^ ENCRYPTION_SBOX_3[s2 & 0xff] ^ pEncryptKey->roundKey[ 7];

    /* round 2: */

    s0 = ENCRYPTION_SBOX_0[t0 >> 24] ^ ENCRYPTION_SBOX_1[(t1 >> 16) & 0xff] ^ ENCRYPTION_SBOX_2[(t2 >>  8) & 0xff] ^ ENCRYPTION_SBOX_3[t3 & 0xff] ^ pEncryptKey->roundKey[ 8];

    s1 = ENCRYPTION_SBOX_0[t1 >> 24] ^ ENCRYPTION_SBOX_1[(t2 >> 16) & 0xff] ^ ENCRYPTION_SBOX_2[(t3 >>  8) & 0xff] ^ ENCRYPTION_SBOX_3[t0 & 0xff] ^ pEncryptKey->roundKey[ 9];

    s2 = ENCRYPTION_SBOX_0[t2 >> 24] ^ ENCRYPTION_SBOX_1[(t3 >> 16) & 0xff] ^ ENCRYPTION_SBOX_2[(t0 >>  8) & 0xff] ^ ENCRYPTION_SBOX_3[t1 & 0xff] ^ pEncryptKey->roundKey[10];

    s3 = ENCRYPTION_SBOX_0[t3 >> 24] ^ ENCRYPTION_SBOX_1[(t0 >> 16) & 0xff] ^ ENCRYPTION_SBOX_2[(t1 >>  8) & 0xff] ^ ENCRYPTION_SBOX_3[t2 & 0xff] ^ pEncryptKey->roundKey[11];

    /* round 3: */

    t0 = ENCRYPTION_SBOX_0[s0 >> 24] ^ ENCRYPTION_SBOX_1[(s1 >> 16) & 0xff] ^ ENCRYPTION_SBOX_2[(s2 >>  8) & 0xff] ^ ENCRYPTION_SBOX_3[s3 & 0xff] ^ pEncryptKey->roundKey[12];

    t1 = ENCRYPTION_SBOX_0[s1 >> 24] ^ ENCRYPTION_SBOX_1[(s2 >> 16) & 0xff] ^ ENCRYPTION_SBOX_2[(s3 >>  8) & 0xff] ^ ENCRYPTION_SBOX_3[s0 & 0xff] ^ pEncryptKey->roundKey[13];

    t2 = ENCRYPTION_SBOX_0[s2 >> 24] ^ ENCRYPTION_SBOX_1[(s3 >> 16) & 0xff] ^ ENCRYPTION_SBOX_2[(s0 >>  8) & 0xff] ^ ENCRYPTION_SBOX_3[s1 & 0xff] ^ pEncryptKey->roundKey[14];

    t3 = ENCRYPTION_SBOX_0[s3 >> 24] ^ ENCRYPTION_SBOX_1[(s0 >> 16) & 0xff] ^ ENCRYPTION_SBOX_2[(s1 >>  8) & 0xff] ^ ENCRYPTION_SBOX_3[s2 & 0xff] ^ pEncryptKey->roundKey[15];

    /* round 4: */

    s0 = ENCRYPTION_SBOX_0[t0 >> 24] ^ ENCRYPTION_SBOX_1[(t1 >> 16) & 0xff] ^ ENCRYPTION_SBOX_2[(t2 >>  8) & 0xff] ^ ENCRYPTION_SBOX_3[t3 & 0xff] ^ pEncryptKey->roundKey[16];

    s1 = ENCRYPTION_SBOX_0[t1 >> 24] ^ ENCRYPTION_SBOX_1[(t2 >> 16) & 0xff] ^ ENCRYPTION_SBOX_2[(t3 >>  8) & 0xff] ^ ENCRYPTION_SBOX_3[t0 & 0xff] ^ pEncryptKey->roundKey[17];

    s2 = ENCRYPTION_SBOX_0[t2 >> 24] ^ ENCRYPTION_SBOX_1[(t3 >> 16) & 0xff] ^ ENCRYPTION_SBOX_2[(t0 >>  8) & 0xff] ^ ENCRYPTION_SBOX_3[t1 & 0xff] ^ pEncryptKey->roundKey[18];

    s3 = ENCRYPTION_SBOX_0[t3 >> 24] ^ ENCRYPTION_SBOX_1[(t0 >> 16) & 0xff] ^ ENCRYPTION_SBOX_2[(t1 >>  8) & 0xff] ^ ENCRYPTION_SBOX_3[t2 & 0xff] ^ pEncryptKey->roundKey[19];

    /* round 5: */

    t0 = ENCRYPTION_SBOX_0[s0 >> 24] ^ ENCRYPTION_SBOX_1[(s1 >> 16) & 0xff] ^ ENCRYPTION_SBOX_2[(s2 >>  8) & 0xff] ^ ENCRYPTION_SBOX_3[s3 & 0xff] ^ pEncryptKey->roundKey[20];

    t1 = ENCRYPTION_SBOX_0[s1 >> 24] ^ ENCRYPTION_SBOX_1[(s2 >> 16) & 0xff] ^ ENCRYPTION_SBOX_2[(s3 >>  8) & 0xff] ^ ENCRYPTION_SBOX_3[s0 & 0xff] ^ pEncryptKey->roundKey[21];

    t2 = ENCRYPTION_SBOX_0[s2 >> 24] ^ ENCRYPTION_SBOX_1[(s3 >> 16) & 0xff] ^ ENCRYPTION_SBOX_2[(s0 >>  8) & 0xff] ^ ENCRYPTION_SBOX_3[s1 & 0xff] ^ pEncryptKey->roundKey[22];

    t3 = ENCRYPTION_SBOX_0[s3 >> 24] ^ ENCRYPTION_SBOX_1[(s0 >> 16) & 0xff] ^ ENCRYPTION_SBOX_2[(s1 >>  8) & 0xff] ^ ENCRYPTION_SBOX_3[s2 & 0xff] ^ pEncryptKey->roundKey[23];

    /* round 6: */

    s0 = ENCRYPTION_SBOX_0[t0 >> 24] ^ ENCRYPTION_SBOX_1[(t1 >> 16) & 0xff] ^ ENCRYPTION_SBOX_2[(t2 >>  8) & 0xff] ^ ENCRYPTION_SBOX_3[t3 & 0xff] ^ pEncryptKey->roundKey[24];

    s1 = ENCRYPTION_SBOX_0[t1 >> 24] ^ ENCRYPTION_SBOX_1[(t2 >> 16) & 0xff] ^ ENCRYPTION_SBOX_2[(t3 >>  8) & 0xff] ^ ENCRYPTION_SBOX_3[t0 & 0xff] ^ pEncryptKey->roundKey[25];

    s2 = ENCRYPTION_SBOX_0[t2 >> 24] ^ ENCRYPTION_SBOX_1[(t3 >> 16) & 0xff] ^ ENCRYPTION_SBOX_2[(t0 >>  8) & 0xff] ^ ENCRYPTION_SBOX_3[t1 & 0xff] ^ pEncryptKey->roundKey[26];

    s3 = ENCRYPTION_SBOX_0[t3 >> 24] ^ ENCRYPTION_SBOX_1[(t0 >> 16) & 0xff] ^ ENCRYPTION_SBOX_2[(t1 >>  8) & 0xff] ^ ENCRYPTION_SBOX_3[t2 & 0xff] ^ pEncryptKey->roundKey[27];

    /* round 7: */

    t0 = ENCRYPTION_SBOX_0[s0 >> 24] ^ ENCRYPTION_SBOX_1[(s1 >> 16) & 0xff] ^ ENCRYPTION_SBOX_2[(s2 >>  8) & 0xff] ^ ENCRYPTION_SBOX_3[s3 & 0xff] ^ pEncryptKey->roundKey[28];

    t1 = ENCRYPTION_SBOX_0[s1 >> 24] ^ ENCRYPTION_SBOX_1[(s2 >> 16) & 0xff] ^ ENCRYPTION_SBOX_2[(s3 >>  8) & 0xff] ^ ENCRYPTION_SBOX_3[s0 & 0xff] ^ pEncryptKey->roundKey[29];

    t2 = ENCRYPTION_SBOX_0[s2 >> 24] ^ ENCRYPTION_SBOX_1[(s3 >> 16) & 0xff] ^ ENCRYPTION_SBOX_2[(s0 >>  8) & 0xff] ^ ENCRYPTION_SBOX_3[s1 & 0xff] ^ pEncryptKey->roundKey[30];

    t3 = ENCRYPTION_SBOX_0[s3 >> 24] ^ ENCRYPTION_SBOX_1[(s0 >> 16) & 0xff] ^ ENCRYPTION_SBOX_2[(s1 >>  8) & 0xff] ^ ENCRYPTION_SBOX_3[s2 & 0xff] ^ pEncryptKey->roundKey[31];

    /* round 8: */

    s0 = ENCRYPTION_SBOX_0[t0 >> 24] ^ ENCRYPTION_SBOX_1[(t1 >> 16) & 0xff] ^ ENCRYPTION_SBOX_2[(t2 >>  8) & 0xff] ^ ENCRYPTION_SBOX_3[t3 & 0xff] ^ pEncryptKey->roundKey[32];

    s1 = ENCRYPTION_SBOX_0[t1 >> 24] ^ ENCRYPTION_SBOX_1[(t2 >> 16) & 0xff] ^ ENCRYPTION_SBOX_2[(t3 >>  8) & 0xff] ^ ENCRYPTION_SBOX_3[t0 & 0xff] ^ pEncryptKey->roundKey[33];

    s2 = ENCRYPTION_SBOX_0[t2 >> 24] ^ ENCRYPTION_SBOX_1[(t3 >> 16) & 0xff] ^ ENCRYPTION_SBOX_2[(t0 >>  8) & 0xff] ^ ENCRYPTION_SBOX_3[t1 & 0xff] ^ pEncryptKey->roundKey[34];

    s3 = ENCRYPTION_SBOX_0[t3 >> 24] ^ ENCRYPTION_SBOX_1[(t0 >> 16) & 0xff] ^ ENCRYPTION_SBOX_2[(t1 >>  8) & 0xff] ^ ENCRYPTION_SBOX_3[t2 & 0xff] ^ pEncryptKey->roundKey[35];

    /* round 9: */

    t0 = ENCRYPTION_SBOX_0[s0 >> 24] ^ ENCRYPTION_SBOX_1[(s1 >> 16) & 0xff] ^ ENCRYPTION_SBOX_2[(s2 >>  8) & 0xff] ^ ENCRYPTION_SBOX_3[s3 & 0xff] ^ pEncryptKey->roundKey[36];

    t1 = ENCRYPTION_SBOX_0[s1 >> 24] ^ ENCRYPTION_SBOX_1[(s2 >> 16) & 0xff] ^ ENCRYPTION_SBOX_2[(s3 >>  8) & 0xff] ^ ENCRYPTION_SBOX_3[s0 & 0xff] ^ pEncryptKey->roundKey[37];

    t2 = ENCRYPTION_SBOX_0[s2 >> 24] ^ ENCRYPTION_SBOX_1[(s3 >> 16) & 0xff] ^ ENCRYPTION_SBOX_2[(s0 >>  8) & 0xff] ^ ENCRYPTION_SBOX_3[s1 & 0xff] ^ pEncryptKey->roundKey[38];

    t3 = ENCRYPTION_SBOX_0[s3 >> 24] ^ ENCRYPTION_SBOX_1[(s0 >> 16) & 0xff] ^ ENCRYPTION_SBOX_2[(s1 >>  8) & 0xff] ^ ENCRYPTION_SBOX_3[s2 & 0xff] ^ pEncryptKey->roundKey[39];

    if (pEncryptKey->rounds > 10)
    {

        /* round 10: */

        s0 = ENCRYPTION_SBOX_0[t0 >> 24] ^ ENCRYPTION_SBOX_1[(t1 >> 16) & 0xff] ^ ENCRYPTION_SBOX_2[(t2 >>  8) & 0xff] ^ ENCRYPTION_SBOX_3[t3 & 0xff] ^ pEncryptKey->roundKey[40];

        s1 = ENCRYPTION_SBOX_0[t1 >> 24] ^ ENCRYPTION_SBOX_1[(t2 >> 16) & 0xff] ^ ENCRYPTION_SBOX_2[(t3 >>  8) & 0xff] ^ ENCRYPTION_SBOX_3[t0 & 0xff] ^ pEncryptKey->roundKey[41];

        s2 = ENCRYPTION_SBOX_0[t2 >> 24] ^ ENCRYPTION_SBOX_1[(t3 >> 16) & 0xff] ^ ENCRYPTION_SBOX_2[(t0 >>  8) & 0xff] ^ ENCRYPTION_SBOX_3[t1 & 0xff] ^ pEncryptKey->roundKey[42];

        s3 = ENCRYPTION_SBOX_0[t3 >> 24] ^ ENCRYPTION_SBOX_1[(t0 >> 16) & 0xff] ^ ENCRYPTION_SBOX_2[(t1 >>  8) & 0xff] ^ ENCRYPTION_SBOX_3[t2 & 0xff] ^ pEncryptKey->roundKey[43];

        /* round 11: */

        t0 = ENCRYPTION_SBOX_0[s0 >> 24] ^ ENCRYPTION_SBOX_1[(s1 >> 16) & 0xff] ^ ENCRYPTION_SBOX_2[(s2 >>  8) & 0xff] ^ ENCRYPTION_SBOX_3[s3 & 0xff] ^ pEncryptKey->roundKey[44];

        t1 = ENCRYPTION_SBOX_0[s1 >> 24] ^ ENCRYPTION_SBOX_1[(s2 >> 16) & 0xff] ^ ENCRYPTION_SBOX_2[(s3 >>  8) & 0xff] ^ ENCRYPTION_SBOX_3[s0 & 0xff] ^ pEncryptKey->roundKey[45];

        t2 = ENCRYPTION_SBOX_0[s2 >> 24] ^ ENCRYPTION_SBOX_1[(s3 >> 16) & 0xff] ^ ENCRYPTION_SBOX_2[(s0 >>  8) & 0xff] ^ ENCRYPTION_SBOX_3[s1 & 0xff] ^ pEncryptKey->roundKey[46];

        t3 = ENCRYPTION_SBOX_0[s3 >> 24] ^ ENCRYPTION_SBOX_1[(s0 >> 16) & 0xff] ^ ENCRYPTION_SBOX_2[(s1 >>  8) & 0xff] ^ ENCRYPTION_SBOX_3[s2 & 0xff] ^ pEncryptKey->roundKey[47];

        if (pEncryptKey->rounds > 12)
        {

            /* round 12: */

            s0 = ENCRYPTION_SBOX_0[t0 >> 24] ^ ENCRYPTION_SBOX_1[(t1 >> 16) & 0xff] ^ ENCRYPTION_SBOX_2[(t2 >>  8) & 0xff] ^ ENCRYPTION_SBOX_3[t3 & 0xff] ^ pEncryptKey->roundKey[48];

            s1 = ENCRYPTION_SBOX_0[t1 >> 24] ^ ENCRYPTION_SBOX_1[(t2 >> 16) & 0xff] ^ ENCRYPTION_SBOX_2[(t3 >>  8) & 0xff] ^ ENCRYPTION_SBOX_3[t0 & 0xff] ^ pEncryptKey->roundKey[49];

            s2 = ENCRYPTION_SBOX_0[t2 >> 24] ^ ENCRYPTION_SBOX_1[(t3 >> 16) & 0xff] ^ ENCRYPTION_SBOX_2[(t0 >>  8) & 0xff] ^ ENCRYPTION_SBOX_3[t1 & 0xff] ^ pEncryptKey->roundKey[50];

            s3 = ENCRYPTION_SBOX_0[t3 >> 24] ^ ENCRYPTION_SBOX_1[(t0 >> 16) & 0xff] ^ ENCRYPTION_SBOX_2[(t1 >>  8) & 0xff] ^ ENCRYPTION_SBOX_3[t2 & 0xff] ^ pEncryptKey->roundKey[51];

            /* round 13: */

            t0 = ENCRYPTION_SBOX_0[s0 >> 24] ^ ENCRYPTION_SBOX_1[(s1 >> 16) & 0xff] ^ ENCRYPTION_SBOX_2[(s2 >>  8) & 0xff] ^ ENCRYPTION_SBOX_3[s3 & 0xff] ^ pEncryptKey->roundKey[52];

            t1 = ENCRYPTION_SBOX_0[s1 >> 24] ^ ENCRYPTION_SBOX_1[(s2 >> 16) & 0xff] ^ ENCRYPTION_SBOX_2[(s3 >>  8) & 0xff] ^ ENCRYPTION_SBOX_3[s0 & 0xff] ^ pEncryptKey->roundKey[53];

            t2 = ENCRYPTION_SBOX_0[s2 >> 24] ^ ENCRYPTION_SBOX_1[(s3 >> 16) & 0xff] ^ ENCRYPTION_SBOX_2[(s0 >>  8) & 0xff] ^ ENCRYPTION_SBOX_3[s1 & 0xff] ^ pEncryptKey->roundKey[54];

            t3 = ENCRYPTION_SBOX_0[s3 >> 24] ^ ENCRYPTION_SBOX_1[(s0 >> 16) & 0xff] ^ ENCRYPTION_SBOX_2[(s1 >>  8) & 0xff] ^ ENCRYPTION_SBOX_3[s2 & 0xff] ^ pEncryptKey->roundKey[55];

        }

    }

    /*
     * apply last round and
     * map cipher state to byte array block:
     */

    s0 =

        (ENCRYPTION_SBOX_4[(t0 >> 24)       ] & 0xff000000) ^

        (ENCRYPTION_SBOX_4[(t1 >> 16) & 0xff] & 0x00ff0000) ^

        (ENCRYPTION_SBOX_4[(t2 >>  8) & 0xff] & 0x0000ff00) ^

        (ENCRYPTION_SBOX_4[(t3      ) & 0xff] & 0x000000ff) ^

        pEncryptKey->roundKey[lastRoundPos++];

    PUTuint32(cipherText     , s0);

    s1 =

        (ENCRYPTION_SBOX_4[(t1 >> 24)       ] & 0xff000000) ^

        (ENCRYPTION_SBOX_4[(t2 >> 16) & 0xff] & 0x00ff0000) ^

        (ENCRYPTION_SBOX_4[(t3 >>  8) & 0xff] & 0x0000ff00) ^

        (ENCRYPTION_SBOX_4[(t0      ) & 0xff] & 0x000000ff) ^

        pEncryptKey->roundKey[lastRoundPos++];

    PUTuint32(cipherText +  4, s1);

    s2 =

        (ENCRYPTION_SBOX_4[(t2 >> 24)       ] & 0xff000000) ^

        (ENCRYPTION_SBOX_4[(t3 >> 16) & 0xff] & 0x00ff0000) ^

        (ENCRYPTION_SBOX_4[(t0 >>  8) & 0xff] & 0x0000ff00) ^

        (ENCRYPTION_SBOX_4[(t1      ) & 0xff] & 0x000000ff) ^

        pEncryptKey->roundKey[lastRoundPos++];

    PUTuint32(cipherText +  8, s2);

    s3 =

        (ENCRYPTION_SBOX_4[(t3 >> 24)       ] & 0xff000000) ^

        (ENCRYPTION_SBOX_4[(t0 >> 16) & 0xff] & 0x00ff0000) ^

        (ENCRYPTION_SBOX_4[(t1 >>  8) & 0xff] & 0x0000ff00) ^

        (ENCRYPTION_SBOX_4[(t2      ) & 0xff] & 0x000000ff) ^

        pEncryptKey->roundKey[lastRoundPos];

    PUTuint32(cipherText + 12, s3);

}



VOID AES_DecryptBlock(const AES_keyInstance *  decryptKey, 
                      const UINT8 cipherText[AES_BLOCK_SIZE], 
                      UINT8 plainText[AES_BLOCK_SIZE])  
{
    UINT32 s0, s1, s2, s3, t0, t1, t2, t3;
    INT32 lastRoundPos;
    lastRoundPos = decryptKey->rounds << 2; 


    /* Map byte array block to cipher state and add initial round key: */

    s0 = GETuint32(cipherText     ) ^ decryptKey->roundKey[0];
    s1 = GETuint32(cipherText +  4) ^ decryptKey->roundKey[1];
    s2 = GETuint32(cipherText +  8) ^ decryptKey->roundKey[2];
    s3 = GETuint32(cipherText + 12) ^ decryptKey->roundKey[3];

    /* round 1: */
    t0= (DECRYPTION_SBOX_0[s0 >> 24] ^ DECRYPTION_SBOX_1[(s3 >> 16) & 0xff] ^ DECRYPTION_SBOX_2[(s2 >>  8) & 0xff] ^ DECRYPTION_SBOX_3[s1 & 0xff] ^ decryptKey->roundKey[ 4]);
    t1= (DECRYPTION_SBOX_0[s1 >> 24] ^ DECRYPTION_SBOX_1[(s0 >> 16) & 0xff] ^ DECRYPTION_SBOX_2[(s3 >>  8) & 0xff] ^ DECRYPTION_SBOX_3[s2 & 0xff] ^ decryptKey->roundKey[ 5]);
    t2= (DECRYPTION_SBOX_0[s2 >> 24] ^ DECRYPTION_SBOX_1[(s1 >> 16) & 0xff] ^ DECRYPTION_SBOX_2[(s0 >>  8) & 0xff] ^ DECRYPTION_SBOX_3[s3 & 0xff] ^ decryptKey->roundKey[ 6]);
    t3= (DECRYPTION_SBOX_0[s3 >> 24] ^ DECRYPTION_SBOX_1[(s2 >> 16) & 0xff] ^ DECRYPTION_SBOX_2[(s1 >>  8) & 0xff] ^ DECRYPTION_SBOX_3[s0 & 0xff] ^ decryptKey->roundKey[ 7]);

    /* round 2: */
    s0= (DECRYPTION_SBOX_0[t0 >> 24] ^ DECRYPTION_SBOX_1[(t3 >> 16) & 0xff] ^ DECRYPTION_SBOX_2[(t2 >>  8) & 0xff] ^ DECRYPTION_SBOX_3[t1 & 0xff] ^ decryptKey->roundKey[ 8]);
    s1= (DECRYPTION_SBOX_0[t1 >> 24] ^ DECRYPTION_SBOX_1[(t0 >> 16) & 0xff] ^ DECRYPTION_SBOX_2[(t3 >>  8) & 0xff] ^ DECRYPTION_SBOX_3[t2 & 0xff] ^ decryptKey->roundKey[ 9]);
    s2= (DECRYPTION_SBOX_0[t2 >> 24] ^ DECRYPTION_SBOX_1[(t1 >> 16) & 0xff] ^ DECRYPTION_SBOX_2[(t0 >>  8) & 0xff] ^ DECRYPTION_SBOX_3[t3 & 0xff] ^ decryptKey->roundKey[10]);
    s3= (DECRYPTION_SBOX_0[t3 >> 24] ^ DECRYPTION_SBOX_1[(t2 >> 16) & 0xff] ^ DECRYPTION_SBOX_2[(t1 >>  8) & 0xff] ^ DECRYPTION_SBOX_3[t0 & 0xff] ^ decryptKey->roundKey[11]);

    /* round 3: */
    t0= (DECRYPTION_SBOX_0[s0 >> 24] ^ DECRYPTION_SBOX_1[(s3 >> 16) & 0xff] ^ DECRYPTION_SBOX_2[(s2 >>  8) & 0xff] ^ DECRYPTION_SBOX_3[s1 & 0xff] ^ decryptKey->roundKey[12]);
    t1= (DECRYPTION_SBOX_0[s1 >> 24] ^ DECRYPTION_SBOX_1[(s0 >> 16) & 0xff] ^ DECRYPTION_SBOX_2[(s3 >>  8) & 0xff] ^ DECRYPTION_SBOX_3[s2 & 0xff] ^ decryptKey->roundKey[13]);
    t2= (DECRYPTION_SBOX_0[s2 >> 24] ^ DECRYPTION_SBOX_1[(s1 >> 16) & 0xff] ^ DECRYPTION_SBOX_2[(s0 >>  8) & 0xff] ^ DECRYPTION_SBOX_3[s3 & 0xff] ^ decryptKey->roundKey[14]);
    t3= (DECRYPTION_SBOX_0[s3 >> 24] ^ DECRYPTION_SBOX_1[(s2 >> 16) & 0xff] ^ DECRYPTION_SBOX_2[(s1 >>  8) & 0xff] ^ DECRYPTION_SBOX_3[s0 & 0xff] ^ decryptKey->roundKey[15]);

    /* round 4: */
    s0= (DECRYPTION_SBOX_0[t0 >> 24] ^ DECRYPTION_SBOX_1[(t3 >> 16) & 0xff] ^ DECRYPTION_SBOX_2[(t2 >>  8) & 0xff] ^ DECRYPTION_SBOX_3[t1 & 0xff] ^ decryptKey->roundKey[16]);
    s1= (DECRYPTION_SBOX_0[t1 >> 24] ^ DECRYPTION_SBOX_1[(t0 >> 16) & 0xff] ^ DECRYPTION_SBOX_2[(t3 >>  8) & 0xff] ^ DECRYPTION_SBOX_3[t2 & 0xff] ^ decryptKey->roundKey[17]);
    s2= (DECRYPTION_SBOX_0[t2 >> 24] ^ DECRYPTION_SBOX_1[(t1 >> 16) & 0xff] ^ DECRYPTION_SBOX_2[(t0 >>  8) & 0xff] ^ DECRYPTION_SBOX_3[t3 & 0xff] ^ decryptKey->roundKey[18]);
    s3= (DECRYPTION_SBOX_0[t3 >> 24] ^ DECRYPTION_SBOX_1[(t2 >> 16) & 0xff] ^ DECRYPTION_SBOX_2[(t1 >>  8) & 0xff] ^ DECRYPTION_SBOX_3[t0 & 0xff] ^ decryptKey->roundKey[19]);

    /* round 5: */
    t0= (DECRYPTION_SBOX_0[s0 >> 24] ^ DECRYPTION_SBOX_1[(s3 >> 16) & 0xff] ^ DECRYPTION_SBOX_2[(s2 >>  8) & 0xff] ^ DECRYPTION_SBOX_3[s1 & 0xff] ^ decryptKey->roundKey[20]);
    t1= (DECRYPTION_SBOX_0[s1 >> 24] ^ DECRYPTION_SBOX_1[(s0 >> 16) & 0xff] ^ DECRYPTION_SBOX_2[(s3 >>  8) & 0xff] ^ DECRYPTION_SBOX_3[s2 & 0xff] ^ decryptKey->roundKey[21]);
    t2= (DECRYPTION_SBOX_0[s2 >> 24] ^ DECRYPTION_SBOX_1[(s1 >> 16) & 0xff] ^ DECRYPTION_SBOX_2[(s0 >>  8) & 0xff] ^ DECRYPTION_SBOX_3[s3 & 0xff] ^ decryptKey->roundKey[22]);
    t3= (DECRYPTION_SBOX_0[s3 >> 24] ^ DECRYPTION_SBOX_1[(s2 >> 16) & 0xff] ^ DECRYPTION_SBOX_2[(s1 >>  8) & 0xff] ^ DECRYPTION_SBOX_3[s0 & 0xff] ^ decryptKey->roundKey[23]);
    /* round 6: */
    s0= (DECRYPTION_SBOX_0[t0 >> 24] ^ DECRYPTION_SBOX_1[(t3 >> 16) & 0xff] ^ DECRYPTION_SBOX_2[(t2 >>  8) & 0xff] ^ DECRYPTION_SBOX_3[t1 & 0xff] ^ decryptKey->roundKey[24]);
    s1= (DECRYPTION_SBOX_0[t1 >> 24] ^ DECRYPTION_SBOX_1[(t0 >> 16) & 0xff] ^ DECRYPTION_SBOX_2[(t3 >>  8) & 0xff] ^ DECRYPTION_SBOX_3[t2 & 0xff] ^ decryptKey->roundKey[25]);
    s2= (DECRYPTION_SBOX_0[t2 >> 24] ^ DECRYPTION_SBOX_1[(t1 >> 16) & 0xff] ^ DECRYPTION_SBOX_2[(t0 >>  8) & 0xff] ^ DECRYPTION_SBOX_3[t3 & 0xff] ^ decryptKey->roundKey[26]);
    s3= (DECRYPTION_SBOX_0[t3 >> 24] ^ DECRYPTION_SBOX_1[(t2 >> 16) & 0xff] ^ DECRYPTION_SBOX_2[(t1 >>  8) & 0xff] ^ DECRYPTION_SBOX_3[t0 & 0xff] ^ decryptKey->roundKey[27]);
    /* round 7: */
    t0= (DECRYPTION_SBOX_0[s0 >> 24] ^ DECRYPTION_SBOX_1[(s3 >> 16) & 0xff] ^ DECRYPTION_SBOX_2[(s2 >>  8) & 0xff] ^ DECRYPTION_SBOX_3[s1 & 0xff] ^ decryptKey->roundKey[28]);
    t1= (DECRYPTION_SBOX_0[s1 >> 24] ^ DECRYPTION_SBOX_1[(s0 >> 16) & 0xff] ^ DECRYPTION_SBOX_2[(s3 >>  8) & 0xff] ^ DECRYPTION_SBOX_3[s2 & 0xff] ^ decryptKey->roundKey[29]);
    t2= (DECRYPTION_SBOX_0[s2 >> 24] ^ DECRYPTION_SBOX_1[(s1 >> 16) & 0xff] ^ DECRYPTION_SBOX_2[(s0 >>  8) & 0xff] ^ DECRYPTION_SBOX_3[s3 & 0xff] ^ decryptKey->roundKey[30]);
    t3= (DECRYPTION_SBOX_0[s3 >> 24] ^ DECRYPTION_SBOX_1[(s2 >> 16) & 0xff] ^ DECRYPTION_SBOX_2[(s1 >>  8) & 0xff] ^ DECRYPTION_SBOX_3[s0 & 0xff] ^ decryptKey->roundKey[31]);
    /* round 8: */
    s0= (DECRYPTION_SBOX_0[t0 >> 24] ^ DECRYPTION_SBOX_1[(t3 >> 16) & 0xff] ^ DECRYPTION_SBOX_2[(t2 >>  8) & 0xff] ^ DECRYPTION_SBOX_3[t1 & 0xff] ^ decryptKey->roundKey[32]);
    s1= (DECRYPTION_SBOX_0[t1 >> 24] ^ DECRYPTION_SBOX_1[(t0 >> 16) & 0xff] ^ DECRYPTION_SBOX_2[(t3 >>  8) & 0xff] ^ DECRYPTION_SBOX_3[t2 & 0xff] ^ decryptKey->roundKey[33]);
    s2= (DECRYPTION_SBOX_0[t2 >> 24] ^ DECRYPTION_SBOX_1[(t1 >> 16) & 0xff] ^ DECRYPTION_SBOX_2[(t0 >>  8) & 0xff] ^ DECRYPTION_SBOX_3[t3 & 0xff] ^ decryptKey->roundKey[34]);
    s3= (DECRYPTION_SBOX_0[t3 >> 24] ^ DECRYPTION_SBOX_1[(t2 >> 16) & 0xff] ^ DECRYPTION_SBOX_2[(t1 >>  8) & 0xff] ^ DECRYPTION_SBOX_3[t0 & 0xff] ^ decryptKey->roundKey[35]);

    /* round 9: */
    t0= (DECRYPTION_SBOX_0[s0 >> 24] ^ DECRYPTION_SBOX_1[(s3 >> 16) & 0xff] ^ DECRYPTION_SBOX_2[(s2 >>  8) & 0xff] ^ DECRYPTION_SBOX_3[s1 & 0xff] ^ decryptKey->roundKey[36]);
    t1= (DECRYPTION_SBOX_0[s1 >> 24] ^ DECRYPTION_SBOX_1[(s0 >> 16) & 0xff] ^ DECRYPTION_SBOX_2[(s3 >>  8) & 0xff] ^ DECRYPTION_SBOX_3[s2 & 0xff] ^ decryptKey->roundKey[37]);
    t2= (DECRYPTION_SBOX_0[s2 >> 24] ^ DECRYPTION_SBOX_1[(s1 >> 16) & 0xff] ^ DECRYPTION_SBOX_2[(s0 >>  8) & 0xff] ^ DECRYPTION_SBOX_3[s3 & 0xff] ^ decryptKey->roundKey[38]);
    t3= (DECRYPTION_SBOX_0[s3 >> 24] ^ DECRYPTION_SBOX_1[(s2 >> 16) & 0xff] ^ DECRYPTION_SBOX_2[(s1 >>  8) & 0xff] ^ DECRYPTION_SBOX_3[s0 & 0xff] ^ decryptKey->roundKey[39]);

    if (decryptKey->rounds > 10)
    {
        /* round 10: */
        s0= (DECRYPTION_SBOX_0[t0 >> 24] ^ DECRYPTION_SBOX_1[(t3 >> 16) & 0xff] ^ DECRYPTION_SBOX_2[(t2 >>  8) & 0xff] ^ DECRYPTION_SBOX_3[t1 & 0xff] ^ decryptKey->roundKey[40]);
        s1= (DECRYPTION_SBOX_0[t1 >> 24] ^ DECRYPTION_SBOX_1[(t0 >> 16) & 0xff] ^ DECRYPTION_SBOX_2[(t3 >>  8) & 0xff] ^ DECRYPTION_SBOX_3[t2 & 0xff] ^ decryptKey->roundKey[41]);
        s2= (DECRYPTION_SBOX_0[t2 >> 24] ^ DECRYPTION_SBOX_1[(t1 >> 16) & 0xff] ^ DECRYPTION_SBOX_2[(t0 >>  8) & 0xff] ^ DECRYPTION_SBOX_3[t3 & 0xff] ^ decryptKey->roundKey[42]);
        s3= (DECRYPTION_SBOX_0[t3 >> 24] ^ DECRYPTION_SBOX_1[(t2 >> 16) & 0xff] ^ DECRYPTION_SBOX_2[(t1 >>  8) & 0xff] ^ DECRYPTION_SBOX_3[t0 & 0xff] ^ decryptKey->roundKey[43]);

        /* round 11: */
        t0= (DECRYPTION_SBOX_0[s0 >> 24] ^ DECRYPTION_SBOX_1[(s3 >> 16) & 0xff] ^ DECRYPTION_SBOX_2[(s2 >>  8) & 0xff] ^ DECRYPTION_SBOX_3[s1 & 0xff] ^ decryptKey->roundKey[44]);
        t1= (DECRYPTION_SBOX_0[s1 >> 24] ^ DECRYPTION_SBOX_1[(s0 >> 16) & 0xff] ^ DECRYPTION_SBOX_2[(s3 >>  8) & 0xff] ^ DECRYPTION_SBOX_3[s2 & 0xff] ^ decryptKey->roundKey[45]);
        t2= (DECRYPTION_SBOX_0[s2 >> 24] ^ DECRYPTION_SBOX_1[(s1 >> 16) & 0xff] ^ DECRYPTION_SBOX_2[(s0 >>  8) & 0xff] ^ DECRYPTION_SBOX_3[s3 & 0xff] ^ decryptKey->roundKey[46]);
        t3= (DECRYPTION_SBOX_0[s3 >> 24] ^ DECRYPTION_SBOX_1[(s2 >> 16) & 0xff] ^ DECRYPTION_SBOX_2[(s1 >>  8) & 0xff] ^ DECRYPTION_SBOX_3[s0 & 0xff] ^ decryptKey->roundKey[47]);

        if (decryptKey->rounds > 12)
        {
            /* round 12: */
            s0= (DECRYPTION_SBOX_0[t0 >> 24] ^ DECRYPTION_SBOX_1[(t3 >> 16) & 0xff] ^ DECRYPTION_SBOX_2[(t2 >>  8) & 0xff] ^ DECRYPTION_SBOX_3[t1 & 0xff] ^ decryptKey->roundKey[48]);
            s1= (DECRYPTION_SBOX_0[t1 >> 24] ^ DECRYPTION_SBOX_1[(t0 >> 16) & 0xff] ^ DECRYPTION_SBOX_2[(t3 >>  8) & 0xff] ^ DECRYPTION_SBOX_3[t2 & 0xff] ^ decryptKey->roundKey[49]);
            s2= (DECRYPTION_SBOX_0[t2 >> 24] ^ DECRYPTION_SBOX_1[(t1 >> 16) & 0xff] ^ DECRYPTION_SBOX_2[(t0 >>  8) & 0xff] ^ DECRYPTION_SBOX_3[t3 & 0xff] ^ decryptKey->roundKey[50]);
            s3= (DECRYPTION_SBOX_0[t3 >> 24] ^ DECRYPTION_SBOX_1[(t2 >> 16) & 0xff] ^ DECRYPTION_SBOX_2[(t1 >>  8) & 0xff] ^ DECRYPTION_SBOX_3[t0 & 0xff] ^ decryptKey->roundKey[51]);

            /* round 13: */
            t0= (DECRYPTION_SBOX_0[s0 >> 24] ^ DECRYPTION_SBOX_1[(s3 >> 16) & 0xff] ^ DECRYPTION_SBOX_2[(s2 >>  8) & 0xff] ^ DECRYPTION_SBOX_3[s1 & 0xff] ^ decryptKey->roundKey[52]);
            t1= (DECRYPTION_SBOX_0[s1 >> 24] ^ DECRYPTION_SBOX_1[(s0 >> 16) & 0xff] ^ DECRYPTION_SBOX_2[(s3 >>  8) & 0xff] ^ DECRYPTION_SBOX_3[s2 & 0xff] ^ decryptKey->roundKey[53]);
            t2= (DECRYPTION_SBOX_0[s2 >> 24] ^ DECRYPTION_SBOX_1[(s1 >> 16) & 0xff] ^ DECRYPTION_SBOX_2[(s0 >>  8) & 0xff] ^ DECRYPTION_SBOX_3[s3 & 0xff] ^ decryptKey->roundKey[54]);
            t3= (DECRYPTION_SBOX_0[s3 >> 24] ^ DECRYPTION_SBOX_1[(s2 >> 16) & 0xff] ^ DECRYPTION_SBOX_2[(s1 >>  8) & 0xff] ^ DECRYPTION_SBOX_3[s0 & 0xff] ^ decryptKey->roundKey[55]);
        }
    }

    /* Apply last round and map cipher state to byte array block: */

    s0= ((DECRYPTION_SBOX_4[(t0 >> 24)  ] & 0xff000000)      ^
        (DECRYPTION_SBOX_4[(t3 >> 16) & 0xff] & 0x00ff0000)  ^
        (DECRYPTION_SBOX_4[(t2 >>  8) & 0xff] & 0x0000ff00)  ^
        (DECRYPTION_SBOX_4[(t1 ) & 0xff] & 0x000000ff)       ^
        (decryptKey->roundKey[lastRoundPos++])                      );
    PUTuint32(plainText, s0);

    s1= ((DECRYPTION_SBOX_4[(t1 >> 24)  ] & 0xff000000)      ^
        (DECRYPTION_SBOX_4[(t0 >> 16) & 0xff] & 0x00ff0000)  ^
        (DECRYPTION_SBOX_4[(t3 >>  8) & 0xff] & 0x0000ff00)  ^
        (DECRYPTION_SBOX_4[(t2 ) & 0xff] & 0x000000ff)       ^
        (decryptKey->roundKey[lastRoundPos++])                      );
    PUTuint32(plainText +  4, s1);

    s2= ((DECRYPTION_SBOX_4[(t2 >> 24)  ] & 0xff000000)      ^
        (DECRYPTION_SBOX_4[(t1 >> 16) & 0xff] & 0x00ff0000)  ^
        (DECRYPTION_SBOX_4[(t0 >>  8) & 0xff] & 0x0000ff00)  ^
        (DECRYPTION_SBOX_4[(t3 ) & 0xff] & 0x000000ff)       ^
        (decryptKey->roundKey[lastRoundPos++])                      );
    PUTuint32(plainText +  8, s2);

    s3= ((DECRYPTION_SBOX_4[(t3 >> 24)  ] & 0xff000000)      ^
        (DECRYPTION_SBOX_4[(t2 >> 16) & 0xff] & 0x00ff0000)  ^
        (DECRYPTION_SBOX_4[(t1 >>  8) & 0xff] & 0x0000ff00)  ^
        (DECRYPTION_SBOX_4[(t0 ) & 0xff] & 0x000000ff)       ^
        (decryptKey->roundKey[lastRoundPos])                     );
    PUTuint32(plainText + 12, s3);

}


VOID AES_Xor(const UINT8 *pSourceA, const UINT8 *pSourceB, INT32 length,  UINT8 *pResult)
{
    for (length--; length >= 0 ;length--)
    { 
        pResult[length] = pSourceA[length] ^ pSourceB[length];
    }
}



