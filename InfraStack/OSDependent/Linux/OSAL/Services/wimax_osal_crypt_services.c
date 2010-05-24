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
#define  _GNU_SOURCE

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#include "wimax_osal_trace.h"
#include "wimax_osal_primitives.h"
#include "wimax_osal_string.h"
#include "wimax_osal_services.h"

//#include "TraceModule.h"
#include "wimax_osal_services_cmn.h"
#include "wimax_osal_crypt_services.h"

//WiMAX Obfuscation - header files

#include "zlib.h"

#include <fcntl.h>

#include <sys/stat.h>

#include <stdlib.h>

//WiMAX Obfuscation



#define TRACE(x, y, z, ...)



struct DbHeader

{

	long header;

};


/*
srcbuf[IN]
srcbufLen [IN]
*encryptedBufLen [OUT]
encryptedBuf [OUT]
*/
BOOL OSAL_Crypt_EncryptBuffer(char *srcbuf, UINT32 srcbufLen, BYTE* encryptedBuf, size_t *encryptedBufLen)

{

	int ret=0;

	

	

	OSALTRACE(OSAL_INFO, ("OSAL_Crypt_EncryptBuffer [IN]"));

	

	if ( (srcbuf == NULL) || ( srcbufLen == 0) || (encryptedBuf == NULL) ){

			OSALTRACE(OSAL_ERROR, ("OSAL_Crypt_EncryptBuffer: Source Buffer is NULL"));

			return FALSE;

		}

	if ( (*encryptedBufLen > 0) && (encryptedBuf == NULL) ){

		OSALTRACE(OSAL_ERROR, ("OSAL_Crypt_EncryptBuffer : Destination Buffer is NULL"));

			return FALSE;

	}

	



	memset(encryptedBuf,'\0',*encryptedBufLen);



	ret = OSAL_GetObfuscateConfig();

	if(ret==1)

	{

		OSALTRACE(OSAL_INFO, ("OSAL_Crypt_EncryptBuffer: Obfuscation disbaled"));

		if ( *encryptedBufLen < srcbufLen ) 

		{

			OSALTRACE(OSAL_ERROR, ("OSAL_Crypt_EncryptBuffer: In-corrected buffer Len"));

			*encryptedBufLen = srcbufLen;

			return FALSE;

		}

	

		memcpy( encryptedBuf, srcbuf, srcbufLen);	

		*encryptedBufLen = srcbufLen;

	

	}else 

	if(ret==0){

		OSALTRACE(OSAL_INFO, ("OSAL_Crypt_EncryptBuffer : Obfuscation Enabled"));

		struct DbHeader msgheader;

		msgheader.header =0;

	

	

		//Start: zlib libray specific

		Bytef *cBuffer;

		uLongf cBufferLen;

		//End





		cBufferLen = srcbufLen* 1.1 + 12;

		cBuffer = malloc(cBufferLen);

		if(cBuffer==NULL){

			OSALTRACE(OSAL_ERROR, ("OSAL_Crypt_EncryptBuffer:Failed to allocate memory"));

			return FALSE;

		}

		

		//zlib library 

		ret = compress(cBuffer,&cBufferLen,srcbuf,srcbufLen);

		if(ret!=0){

			// Z_MEM_ERROR    (-4) if there was not enough memory - This cannot be handled and it returns FALSE;

			//Z_BUF_ERROR    (-5) if there was not enough room in the output buffer

			if(ret==-5){

				int cnt=2;

				int numOfIterations=0;

				OSALTRACE(OSAL_ERROR, ("OSAL_Crypt_EncryptBuffer:Failed to Compress:"));

				do{

					free(cBuffer);

					cBuffer=NULL;

					cBufferLen = srcbufLen * (cnt*(1.1 +12));

					cBuffer = malloc(cBufferLen);

					if(cBuffer!=NULL)

						ret = compress(cBuffer,&cBufferLen,srcbuf,srcbufLen);

					else

						return FALSE;

	

					cnt+=2;

					numOfIterations+=1;

				}while(numOfIterations<3);

				OSALTRACE(OSAL_INFO, ("OSAL_Crypt_EncryptBuffer the correct destination buffer should be %d",*encryptedBufLen) );

			

				if(cBuffer!=NULL)

					free(cBuffer);

					

				if(ret!=0)	

					return FALSE;

			}

			else

				return FALSE;

		}

		

		if(*encryptedBufLen >= cBufferLen + sizeof(msgheader)){

			OSALTRACE(OSAL_INFO, ("OSAL_Crypt_EncryptBuffer - updating the encryptedBuf"));			

			msgheader.header = srcbufLen;

			memcpy(encryptedBuf,&msgheader,sizeof(msgheader));

			memcpy(encryptedBuf + sizeof(msgheader) ,cBuffer,cBufferLen);

		}

		else

		{	OSALTRACE(OSAL_INFO, ("OSAL_Crypt_EncryptBuffer - In sufficient buffer its need %d",*encryptedBufLen));			

			*encryptedBufLen = sizeof(msgheader) + (size_t)cBufferLen;	

			free(cBuffer);

			

			return FALSE;

		}

		

		*encryptedBufLen = (size_t)cBufferLen + sizeof(msgheader);



		free(cBuffer);

			

	}

	OSALTRACE(OSAL_INFO, ("OSAL_Crypt_EncryptBuffer [OUT]"));

	return TRUE;



}



// buff [In & OUT]- the buffer to decrypt.

// BuffLen [In & OUT] - the len of the input buffer to decrypt

BOOL OSAL_Crypt_DecryptBuffer(BYTE* encryptedBuff, size_t encBuffLen,char *decryptedBuff,size_t *sizeOfDecryptedBuff)

{

	

	int ret=0;

	

	OSALTRACE(OSAL_INFO, ("OSAL_Crypt_DecryptBuffer [IN]"));

	

	if ( (encryptedBuff == NULL) || ( encBuffLen == 0) || (decryptedBuff == NULL) ){

			OSALTRACE(OSAL_ERROR, ("OSAL_Crypt_DecryptBuffer: Source Buffer is NULL"));

			return FALSE;

		}

	if ( (*sizeOfDecryptedBuff > 0) && (decryptedBuff == NULL) ){

		OSALTRACE(OSAL_ERROR, ("OSAL_Crypt_DecryptBuffer: Destination buffer NULL"));

			return FALSE;

	}

	ret = OSAL_GetObfuscateConfig();

		if(ret==1)

		{	

			OSALTRACE(OSAL_ERROR, ("OSAL_Crypt_DecryptBuffer : Obfuscation disbaled"));

			if ( *sizeOfDecryptedBuff < encBuffLen ) 

			{

				OSALTRACE(OSAL_ERROR, ("OSAL_Crypt_DecryptBuffer: In-corrected buffer Len"));

				*sizeOfDecryptedBuff = encBuffLen;

				return FALSE;

			}

			

			memcpy( decryptedBuff, encryptedBuff, encBuffLen);	

			*sizeOfDecryptedBuff = encBuffLen;

		}

		if(ret==0){

			OSALTRACE(OSAL_ERROR, ("OSAL_Crypt_DecryptBuffer: Obfuscation enabled"));

			struct DbHeader headerStruct;

			long header=0;

			

			header = *(long*)encryptedBuff;



			if(*sizeOfDecryptedBuff < header ){

				*sizeOfDecryptedBuff = header ;

				OSALTRACE(OSAL_ERROR, ("OSAL_Crypt_DecryptBuffer:In sufficient buffer!")); 

				return FALSE;

			}

				

			//Most of the times it should not fail here. 

			ret = uncompress(decryptedBuff,sizeOfDecryptedBuff,encryptedBuff+sizeof(headerStruct),encBuffLen - sizeof(headerStruct));

			if(ret!=0){

				OSALTRACE(OSAL_ERROR, ("OSAL_Crypt_DecryptBuffer:Failed to Decrypt!"));

				*sizeOfDecryptedBuff = header;

				

				return FALSE;

			}

			OSALTRACE(OSAL_INFO, ("uncompress success results: ucBufferLen: %d", sizeOfDecryptedBuff));

	}

	OSALTRACE(OSAL_ERROR, ("OSAL_Crypt_DecryptBuffer [OUT]"));

	return TRUE;

}

//use this function only while AppSrv is not running
BOOL OSAL_Crypt_ConveretEncryptedToDecryptFile(char* xmlFileName, char* binFileName)
{
	BOOL res = FALSE;
	FILE *stream;
	size_t buffLen = 0;
	BYTE* buff = NULL;
	size_t ucbuffLen = 0;
	BYTE* ucbuff = NULL;

	if(NULL != binFileName)
	{
		printf("the encrypted file name is %s\n",binFileName);
	}
	else
	{
		printf("the encrypted file name is empty\n");
		return FALSE;
	}
	if(NULL != xmlFileName)
	{
		printf("the clear text file name is %s\n",xmlFileName);
	}
	else
	{
		printf("the clear text file name is empty\n");
		return FALSE;
	}

	OSAL_readData(binFileName, NULL, &buffLen); //should fail and return the actual file size
	buff = (BYTE *)malloc(buffLen);
	if(NULL != buff)
	{
		res = OSAL_readData(binFileName, buff, &buffLen);
		if(TRUE != res) 
		{
			free(buff);
			buff = NULL;
		}
	}

	if(NULL == buff) 
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ALERT, "unable to read the file %s",binFileName);
		return FALSE;
	}

	
	ucbuffLen = buffLen;
	ucbuff = (BYTE*)malloc(ucbuffLen);
	if(ucbuff == NULL) {
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ALERT, "malloc failed");
		free(buff);
		return FALSE;
	}

	if(FALSE == OSAL_Crypt_DecryptBuffer(buff, buffLen, ucbuff, &ucbuffLen))
	{
		free(buff);
		free(ucbuff);
		return FALSE;
	}

	if((stream = fopen(xmlFileName, "w")) != NULL)
	{
		printf("Failure to open the file %s\n",xmlFileName);
		//unable to open the file
		free(buff);
		free(ucbuff);
		return FALSE;
	}
	fwrite(buff, sizeof(CHAR), buffLen, stream);

	fclose(stream);
	free(buff);
	free(ucbuff);

	printf("The file %s was decrypted into the file %s with success\n", binFileName, xmlFileName);

	return TRUE;

}

//this function should not run while AppSrv is running
BOOL OSAL_Crypt_ConveretDecryptedToEncryptedFile(char* binFileName, char* xmlFileName)
{

//#define	BASIC_DB_FILE_SIZE	(14 * 1024)	// TODO::OSAL-WORK::Non-Critical but important - Will be removed from here.

	FILE *stream;
	BOOL rc = FALSE;
	size_t buffSize = OSAL_BASIC_DB_FILE_SIZE;
	PCHAR buff = NULL;
	size_t encryptedBuffLen;
	BYTE *encryptedBuff = NULL;



	if(NULL != binFileName)
	{
		printf("the encrypted file name is %s\n",binFileName);
	}
	else
	{
		printf("the encrypted file name is empty\n");
		return FALSE;
	}
	if(NULL != xmlFileName)
	{
		printf("the clear text file name is %s\n",xmlFileName);
	}
	else
	{
		printf("the clear text file name is empty\n");
		return FALSE;
	}

	printf("starting reading the file %s\n",binFileName);
	if( ( stream = fopen( xmlFileName, "r" )) != NULL )
	{
		printf("The file %s was not opened\n",xmlFileName);
		return FALSE;
	}
	// Get file size
	fseek(stream, 0, SEEK_END);
	buffSize = ftell(stream);
	fseek(stream, 0, SEEK_SET);

	buff = (CHAR *)malloc(buffSize);
	if(NULL == buff)
	{
		fclose(stream);
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ALERT, "db_ReadData - buf malloc failed");
		return FALSE;
	}

	buffSize = fread(buff, sizeof(BYTE), buffSize, stream);
	fclose(stream);

	printf("read the file %s ended with success\n",binFileName);

	encryptedBuffLen = buffSize *3;
	encryptedBuff = (BYTE *)malloc(encryptedBuffLen);
	if(NULL != encryptedBuff)
	{
		rc = OSAL_Crypt_EncryptBuffer(buff, (DWORD)buffSize, encryptedBuff, &encryptedBuffLen);
		if(TRUE != rc)
		{
			free(encryptedBuff);
			encryptedBuff = (BYTE *)malloc(encryptedBuffLen);
			if(NULL !=  encryptedBuff)
			{
				rc = OSAL_Crypt_EncryptBuffer(buff, (DWORD)buffSize, encryptedBuff, &encryptedBuffLen);
			}
		}

	}

	if(TRUE == rc)
	{
		printf("encrypted the file %s ended with success\n",binFileName);
		rc = OSAL_writeData(encryptedBuff, (UINT32)encryptedBuffLen, binFileName);
		if(TRUE != rc)
		{
			printf("unable to write the buffer into the file %s\n",binFileName);
		}
	}
	if(NULL != encryptedBuff)
	{
		free(encryptedBuff);
	}
	free(buff);

	return rc;

}



//credential handling functions

int OSAL_Crypt_EapCreateDecryptPass(UINT8* passwordBuff, size_t* passwordLen)
{
	unsigned encryptedDataLen;
	BYTE* encryptedData = NULL;
	
	
	FILE *stream;
	CHAR path[OSAL_DEFUALT_STR_LEN];
	BYTE *encryptedPass = NULL;
	int mult = 1;

	int valid = (passwordLen != NULL);

	OSALTRACE(OSAL_ERROR, ("enter - with %s, passwordLenvalid: %s, len: %d", (char *) passwordBuff, valid ? "valid" : "invalid", valid ? *passwordLen : 0));

	OSAL_BuildFullPath((char *)passwordBuff, path, OSAL_DEFUALT_STR_LEN);

	OSALTRACE(OSAL_ERROR, ("About to open file-path %s", (char *) path));
	stream = fopen(path, "rb");
	if (stream == NULL) 
	{
		OSALTRACE(OSAL_ERROR, ("Failed to open file: %s", (char *) path));
		return FALSE;
	}

	OSALTRACE(OSAL_ERROR, ("Opened file successfully"));
	do{
		OSAL_FreeIfAllocated(encryptedPass);
		encryptedPass = (BYTE *)calloc(OSAL_DEFUALT_STR_LEN * mult, sizeof(char));
		if (encryptedPass == NULL)
		{
			OSALTRACE(OSAL_ERROR, ("Crypt_EapCreateDecryptPass: Error allocating memory"));
			return FALSE;
		}
		encryptedDataLen = (UINT32)fread(encryptedPass, sizeof(BYTE), OSAL_DEFUALT_STR_LEN, stream);
		mult++;
	}while (!(encryptedDataLen < (UINT32)(OSAL_DEFUALT_STR_LEN * (mult - 1))));

	OSALTRACE(OSAL_DEBUG, ("After loop encryptedDataLen: %d", encryptedDataLen));
	encryptedData = encryptedPass;

	// Close the file...
	fclose(stream);

	// TODO::OSAL-WORK::NON-CRITICAL/Encryption/Decryption - Can be implemented later 
	// For now we wont decrypt the password. (infeasible in open source context)

	if ( *passwordLen < (int) encryptedDataLen )
	{
			OSAL_FreeIfAllocated(encryptedPass);
			OSALTRACE(OSAL_ERROR, ("Insufficient buffer size passed"));
			return FALSE;
	}

	strncpy((char *)passwordBuff, (char *)encryptedData, *passwordLen);
	*passwordLen = encryptedDataLen - 1;

	OSAL_FreeIfAllocated(encryptedPass);
			
	OSALTRACE(OSAL_ERROR, ("Returning with success - %s", (char *)passwordBuff));
	return TRUE;

}

/// <summary>
/// Sets the encrypted password into the right possition in the NSP
/// and generate new file (its name is going to be saved as the password name) that contain the encrypted password
/// </summary>
BOOL OSAL_Crypt_SetEncryptedPassword(char *password, char *passwordToEncrypt)
{
	int done=FALSE, encryptedFileNumber;
	CHAR encryptedFileName[OSAL_DEFUALT_STR_LEN];
	FILE *file = NULL;
	CHAR path[OSAL_DEFUALT_STR_LEN];
	static unsigned addToSead=0;

	OSALTRACE(OSAL_ERROR, ("Enter with - existing pwd file: %s, pwd to encrypt: %s", password, (char *)passwordToEncrypt));

	//delete the file of the old password (if exist)and then continue to Add new one
	OSAL_BuildFullPath(password, path, OSAL_DEFUALT_STR_LEN);
	remove(path);

	//create random file name to save the password in
	do{
		srand( addToSead + (unsigned)time( NULL ) );
		addToSead++;
		encryptedFileNumber = rand();
		if(encryptedFileNumber)
		{
			OSAL_itoa_s(encryptedFileNumber, encryptedFileName, OSAL_DEFUALT_STR_LEN, 10);
			OSAL_BuildFullPath(encryptedFileName, path, OSAL_DEFUALT_STR_LEN);

			if( ( file = fopen( path, "r" )) == NULL )
			{
				done = TRUE;
			}
			else 
			{
				//the file exist and was open - need to close it 
				fclose(file);
			}
		}
	}while(!done);

	OSALTRACE(OSAL_ERROR, ("New password file: %s", encryptedFileName));

	if( ( file = fopen( path, "w" )) == NULL )
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR,"Crypt_SetEncryptedPassword: unable to open new file for the encrypted password");
		memset(passwordToEncrypt, strnlen(passwordToEncrypt, OSAL_DEFUALT_STR_LEN), 0);
		return FALSE;
	}
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO,"The file holding the encrypted password is %s\n",encryptedFileName);

	// NOTE: On Linux we dont encrypt the password 

	fwrite(passwordToEncrypt, 1, strlen(passwordToEncrypt)+1, file) ;
	fclose(file);


	OSAL_strcpy_s(password ,OSAL_DEFUALT_STR_LEN,encryptedFileName);

	OSALTRACE(OSAL_ERROR, ("Returning success"));

	return TRUE;
}

/// <summary>
/// Gets the encrepted password from the specific file name and decrypt it
/// </summary>
BOOL OSAL_Crypt_GetEncyptedPassword(char *passwordFileName, char *decryptedPassword)
{
	FILE *file = NULL;
	CHAR path[OSAL_DEFUALT_STR_LEN];
	UINT32 buffSize = 0;
	int done =FALSE, i = 1;
	BYTE *buffData = NULL;
	BOOL rc = TRUE;

	OSAL_BuildFullPath(passwordFileName, path, OSAL_DEFUALT_STR_LEN);

	if( ( file = fopen( path, "r" )) == NULL )
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR,"Crypt_GetEncyptedPassword: unable to open file contain the encrypted password");
		return FALSE;
	}

	//find the right size of the encrypted buffer and copy the file content into it
	do
	{
		buffData = (BYTE *)malloc(OSAL_DEFUALT_STR_LEN * i);
		if (buffData == NULL)
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ALERT,"Crypt_GetEncyptedPassword: unable to malloc buffer for encrypted password");
			return FALSE;
		}
		buffSize = (UINT32)fread(buffData, sizeof(BYTE), (OSAL_DEFUALT_STR_LEN * i), file); 
		if(((int)buffSize) < (OSAL_DEFUALT_STR_LEN * i))
		{
			done = TRUE;
			fclose(file);
		}
		else
		{
			//the buffer is too small allocate again;
			free(buffData);
			i++;
			buffData = NULL;
		}
	} while(!done);

	// NOTE: On linux the password file would be store in plain text

	OSAL_strncpy_s(decryptedPassword, OSAL_DEFUALT_STR_LEN, (char *)buffData, buffSize);
	rc = TRUE;

	free(buffData);
	return rc;
}


// Defined in NDnS but creates a backward dependence :-(
	
#define NUMBER_OF_GENERATED_CHARS_FOR_PSUEDO_NAI		33


// Implicit assumption is to generate a random string of NUMBER_OF_GENERATED_BYTES_FOR_NAI size in the incoming buffer
BOOL OSAL_CreateRandomBit(char *pseudoNai, int buffSize)
{
	char *tmpBuffer = NULL;
	int pos = 0;
	int r_num;
	int i=0;

	OSALTRACE(OSAL_DEBUG, ("Enter psuedoNai: %s, size: %d, tmpBufferSize: %d", 
						pseudoNai ? "valid" : "null", buffSize, sizeof(tmpBuffer)));

	if ( (pseudoNai == NULL ) || (buffSize == 0) )
		return FALSE;

	tmpBuffer = calloc(buffSize + 12, sizeof(char));	// Allocate extra to account for the way numbers are appended below in the loop

	if ( tmpBuffer == NULL)
		return FALSE;

	srand( (unsigned)time( NULL ) );

	OSALTRACE(OSAL_DEBUG, ("After srand"));

	while ( (pos < NUMBER_OF_GENERATED_CHARS_FOR_PSUEDO_NAI) && ( pos < buffSize) )
	{
		r_num = rand();

		pos += sprintf(tmpBuffer + pos, "%x", r_num);
	}
	
	OSALTRACE(OSAL_DEBUG, ("After rand loop. pos : %d", pos));

	pos = buffSize;
	tmpBuffer[pos-1] = '\0';

	// Upper case the alphabets..
	for (i=0;i<pos;i++)
		if ( !(tmpBuffer[i] >= '0' && tmpBuffer[i] <= '9') )
			tmpBuffer[i] = toupper(tmpBuffer[i]);
	
	memset(pseudoNai, 0, buffSize);

	strncpy(pseudoNai, tmpBuffer, buffSize -1 );

	free(tmpBuffer);

	OSALTRACE(OSAL_DEBUG, ("Returning with %s", pseudoNai));
	return TRUE;
}

void OSAL_CalcSecret(char* serverID, char* serialnumber, char* sharedSecret, char* result, size_t * resultSize)
{
	// TODO::OSAL-WORK::NON-CRITICAL but IMPORTANT / CalcSecret - This functionality does not get used in Linux side??

	// This does not get used on Linux side. 

	// do nothing
}
