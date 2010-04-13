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
#ifndef _MOC_MSG_PROXY_IF_H_
#define _MOC_MSG_PROXY_IF_H_


#define MOC_PROXY_INVALID_SOCKET_ID 0xFF

//	The following Message IDs are the services supported by the L4MsgProxy:

#define MOC_PROXY_L5_MSG_ID_BASE 1000
#define MOC_PROXY_L5_MSG_ID_INVALID -1

//	Incoming Messages:

#define	MOC_PROXY_L5_MSG_ID_ACQUIRE_SOCKET_ID				MOC_PROXY_L5_MSG_ID_BASE + 0
#define	MOC_PROXY_L5_MSG_ID_ACQUIRE_SOCKET_ID_RESPONSE		MOC_PROXY_L5_MSG_ID_BASE + 1
#define	MOC_PROXY_L5_MSG_ID_RELEASE_SOCKET_ID_INDICATION	MOC_PROXY_L5_MSG_ID_BASE + 2

//	Outgoing Messages:
#define	MOC_PROXY_L5_MSG_ID_MOC_RESPONSE_INDICATION			MOC_PROXY_L5_MSG_ID_BASE + 3

//typedef enum
//{
//	MOC_PROXY_L5_MSG_ID_ACQUIRE_SOCKET_ID = 0,
//	MOC_PROXY_L5_MSG_ID_ACQUIRE_SOCKET_ID_RESPONSE,
//	MOC_PROXY_L5_MSG_ID_RELEASE_SOCKET_ID_INDICATION,
//	MOC_PROXY_L5_MSG_ID_MOC_RESPONSE_INDICATION,
//} MOC_PROXY_L5_MSG_ID;


#endif // _MOC_MSG_PROXY_IF_H_