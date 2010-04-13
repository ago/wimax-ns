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
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>


#include "wimax_osal_primitives.h"
#include "IPC_Common.h"


int SOCKETS_ReadExac(int socket, int neededSize,
		     char *inBuf, int inSize,
		     char *outBuf, char *remBuf, int *remSize)
{
	fd_set readFDs;
	long res;
	char tmpBuf[MAX_DATA_SIZE];
	int cnt = inSize;
	int rv;
	int left = neededSize - cnt;
	typedef struct timeval TIMEVAL;
	TIMEVAL timeOutVal;
	int attempts = MAX_RCV_ATTEMPTS_NUM;

	timeOutVal.tv_sec = 0;
	timeOutVal.tv_usec = RCV_TIMEOUT;
	*remSize = 0;

	if( socket == 0 )
	{
		return 0;
	}
	if( neededSize < 0 )
	{
		return 0;
	}

	if( inSize > 0 )
	{
		// copy the input buffer to the output buffer and to the remainder buffer if needed
		if( inSize > neededSize )
		{
			memcpy(outBuf, inBuf, neededSize);
			*remSize = inSize - neededSize;
			memcpy(remBuf, inBuf + neededSize, *remSize);

			return 1;
		}
		else // inSize <= neededSize
		{
			memcpy(outBuf, inBuf, inSize);
		}
	}

	while( ( left > 0 ) && ( attempts > 0 ) )
	{
		// using select instead of recv to avoid blocking
		// TODO - check if setting of readFDs can be done only once

		// prepare the select arguments
		FD_ZERO(&readFDs);
		FD_SET(socket, &readFDs);

		res = select(socket + 1, &readFDs, (fd_set*) 0, (fd_set*) 0, &timeOutVal );
		if( res == -1) 
		{
			return 0;
		}

		if (res != 0)	// means that there was no timeout and that FD_ISSET( socket, &readFDs ) == TRUE
		{
			rv = recv(socket, tmpBuf, MAX_DATA_SIZE, 0);
			if (rv > 0) {
				if (rv > left) {
					memcpy(outBuf + cnt, tmpBuf, left);
					*remSize = rv - left;
					memcpy(remBuf, tmpBuf + left, *remSize);

					return 1;
				} else	// rv <= left
				{
					memcpy(outBuf + cnt, tmpBuf, rv);
				}

				cnt += rv;
				left -= rv;
			}
		}

		attempts--;
	}

	if (left > 0) 
	{
		return 0;
	}

	return 1;
}

int SOCKETS_Write(int socket, char *s, int len)
{
	char *str;
	int res;

	if (socket == 0) {
		//TRACE(TR_MOD_COMMON_SOCKET, TR_SEV_WARNING, (L"Cannot send. Invalid socket.");
		return -1;
	}
	if ((len <= 0) || (len > MAX_DATA_SIZE)) {
		//TRACE(TR_MOD_COMMON_SOCKET, TR_SEV_WARNING, (L"Cannot send. Invalid message length: %d, range: 1-%d", len, MAX_DATA_SIZE);
		return 0;
	}
	// TODO - maybe can do double send instead of malloc
	//TRACE(TR_MOD_COMMON_SOCKET, TR_SEV_INFO, (L"Sending message to a client");
	str = (char *)malloc((len + 4) * sizeof(char));
	if (str == NULL) {
		//TRACE(TR_MOD_COMMON_SOCKET, TR_SEV_ALERT, (L"malloc failed");
		return -1;
	}
	((int *)str)[0] = len;
	memcpy(str + 4, s, len);

	// send the message
	res = send(socket, str, len + 4, 0);

	free(str);
	str = NULL;

	return res;
}

// TODO - check if recv can be called with size zero so that this function won't receive buf and rv
void SOCKETS_Read(int socket, char *buf, int rv, SOCKETS_HandleData dataHandler,
		  SOCKETS_CLIENT_ID client, void *context)
{
	char sizeBuf[4];
	char remBuf[MAX_DATA_SIZE];
	int remSize = 0;
	int size;

	do {
		//TRACE(TR_MOD_COMMON_SOCKET, TR_SEV_INFO, (L"Reading the message size");
		if (remSize > 0) {
			if (!SOCKETS_ReadExac
			    (socket, 4, remBuf, remSize, sizeBuf, remBuf,
			     &remSize)) {
				//TRACE(TR_MOD_COMMON_SOCKET, TR_SEV_WARNING, (L"Problem reading the message size");
				return;
			}
		} else {
			if (!SOCKETS_ReadExac
			    (socket, 4, buf, rv, sizeBuf, remBuf, &remSize)) {
				//TRACE(TR_MOD_COMMON_SOCKET, TR_SEV_WARNING, (L"Problem reading the message size");
				return;
			}
		}

		size = ((int *)sizeBuf)[0];
		if ((size <= 0) || (size > MAX_DATA_SIZE)) {
			//TRACE(TR_MOD_COMMON_SOCKET, TR_SEV_WARNING, (L"Message size is not in range: %d, range: 1-%d", size, MAX_DATA_SIZE);
			return;
		}
		//TRACE(TR_MOD_COMMON_SOCKET, TR_SEV_INFO, (L"Reading the message");
		if (!SOCKETS_ReadExac
		    (socket, size, remBuf, remSize, buf, remBuf, &remSize)) {
			//TRACE(TR_MOD_COMMON_SOCKET, TR_SEV_WARNING, (L"Problem reading the message");
			return;
		}
		//TRACE(TR_MOD_COMMON_SOCKET, TR_SEV_INFO, (L"Calling the data handler");
		if (dataHandler != NULL) {
			dataHandler(buf, size, client, context);
		}
	}
	while (remSize != 0);
}

