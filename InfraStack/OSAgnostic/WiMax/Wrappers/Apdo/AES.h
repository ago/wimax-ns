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
#ifndef _AES_H
#define _AES_H


/*********************************	Definitions	and structures 	*********************************/


// Brings the "Big Endian" INT from a pointer to a buffer
#define GETuint32(pt) ( ((UINT32)(pt)[0] << 24) ^ \
                        ((UINT32)(pt)[1] << 16) ^ \
                        ((UINT32)(pt)[2] <<  8) ^ \
                        ((UINT32)(pt)[3]      )         ) 


// Injects a given INT value to a buffer in "Big Endian"
#define PUTuint32(ct, st) { (ct)[0] = (UINT8)((st) >> 24); \
                            (ct)[1] = (UINT8)((st) >> 16); \
                            (ct)[2] = (UINT8)((st) >>  8); \
                            (ct)[3] = (UINT8)(st);              } 

//  Block size in Bytes (128 bit)
#define AES_BLOCK_SIZE  16      

//  Maximum number of rounds (When key length is 256)
#define	AES_MAXNR   	14      

/*
 *  Return code when using AES functions
 */
typedef enum
{
    AES_SUCCESS = 0,
    AES_ERROR
} AES_ReturnCode;

// Round keys structure created by initial cipher key and preprocessed for fast implementation
typedef struct
{
    INT32		rounds;							/* Number of rounds */
    UINT32		roundKey[4*(AES_MAXNR + 1)];    /* key schedule */
} AES_keyInstance;



//Key length only options for AES
typedef enum 
{
    KEY_128 = 128,
    KEY_192 = 192,
    KEY_256 = 256
}AES_KEY_SIZE;





/**
* Preforms AES encryption to a 128 bit block placing the result to a given buffer.
* Uses encrypt round keys and number of rounds made by an initial cypher key.
*
* @param encryptKey	    Key structure that contains the key and number of rounds
* @param plainText  	Input plain text. * to a buffer
* @param cipherText     Output cipher text. * to a buffer
*
* @return VOID 
*/
VOID	AES_EncryptBlock(const AES_keyInstance *  pEncryptKey, 
                         const UINT8 plainText[AES_BLOCK_SIZE], 
                         UINT8 cipherText[AES_BLOCK_SIZE]);




/**
* Preforms AES decryption to a 128 bit block placing the result to a given buffer.
* Uses decrypt round keys and number of rounds made by an initial cypher key.
*
* @param decryptKey    Key structure that contains the key and number of rounds
* @param cipherText    Input cipher text. * to a buffer
* @param plainText     Output plain text. * to a buffer
*
* @return VOID 
*/
VOID    AES_DecryptBlock(const AES_keyInstance  * pDecryptKey, 
                         const UINT8 cipherText[AES_BLOCK_SIZE], 
                         UINT8 plainText[AES_BLOCK_SIZE]);



/**
* Expand the cipher key into the encryption key schedule,
* and assign the number of rounds which are dependant on the initial key length.
*
* @param pEncryptKey	Address of round Keys structure to be created
* @param pCipherKey		Given base Key
* @param keyLength		The length of the given base key (128,192,256)			
*
* @return AES_ReturnCode    ERR If key size != 128,192,256
*/
AES_ReturnCode	AES_SetEncryptKey(AES_keyInstance* pEncryptKey, const UINT8* pCipherKey, AES_KEY_SIZE keyLength);



/**
* Expand the cipher key into the decryption round keys schedule, 
* and assign the number of rounds which are dependant on the initial key length.
* 
* @param pDecryptKey	Address of round Keys structure to be created
* @param pCipherKey	    Given base Key
* @param keyLength		The length of the given base key (128,192,256)
*
* @return AES_ReturnCode    ERR If key size != 128,192,256
*/
AES_ReturnCode	AES_SetDecryptKey(AES_keyInstance* pDecryptKey, const UINT8* pCipherKey, AES_KEY_SIZE keyLength);


/**
 * Preforms bitwise Xor of given length between two inputs to a new output
 * This operation is often used in the security implementations that use basic AES
 *
 * @param sourceA   First input buffer to Xor
 * @param sourceB   Second input buffer to Xor
 * @param length    The length in bytes to Xor
 * @param result    The Buffer to place the results
 *
 * @return VOID 
 */
VOID AES_Xor(const UINT8* pSourceA, const UINT8* pSourceB, INT32 length,  UINT8* pResult);


#endif