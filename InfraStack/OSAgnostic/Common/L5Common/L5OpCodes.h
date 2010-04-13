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
#ifndef _INTEL_80216_L5_OPCODES_H
#define _INTEL_80216_L5_OPCODES_H

#define OPCODE_INVALID -1;

//OPCODE Bases:
#define L4_PROXY_OPCODE_BASE 0
#define NDNS_OPCODE_BASE 1000
#define SUP_OPCODE_BASE 2000
#define ACT_OPCODE_BASE 3000
//#define NDIS_OPCODE_BASE 4000
#define DND_AGENT_OPCODE_BASE 4000

//#define TEST_OPCODE_BASE 1000
//typedef enum _TEST_AGENT_L5_OPCODE
//{
//	TEST_OPCODE_NDNS_GOLD_SCAN = TEST_OPCODE_BASE
//} TEST_AGENT_L5_OPCODE;


typedef enum _L4_PROXY_AGENT_L5_OPCODE
{
	L4_PROXY_OPCODE_SEND_OID = L4_PROXY_OPCODE_BASE,
	L4_PROXY_OPCODE_SEND_L4_OPCODE,

	L4_PROXY_OPCODE_REGISTER_STATUS_INDICATION,
	L4_PROXY_OPCODE_UNREGISTER_STATUS_INDICATION,

	L4_PROXY_OPCODE_REGISTER_L4_INDICATION,
	L4_PROXY_OPCODE_UNREGISTER_L4_INDICATION,


	L4_PROXY_OPCODE_L4_INDICATION_ARRIVED,
	L4_PROXY_OPCODE_STATUS_INDICATION_ARRIVED
} L4_PROXY_AGENT_L5_OPCODE;
//
/*typedef enum _NDIS_TRACE_L5_OPCODE
{
	TRACE_AGENT_OPCODE_SET_PATH = NDIS_OPCODE_BASE,	
	TRACE_AGENT_OPCODE_GET_PATH,
} _NDIS_TRACE_L5_OPCODE;*/

typedef enum _DND_AGENT_L5_OPCODE
{
	DND_AGENT_OPCODE_SET_PATH = DND_AGENT_OPCODE_BASE,
	DND_AGENT_OPCODE_GET_PATH,
	DND_AGENT_OPCODE_FILE_WRITE,
	DND_AGENT_OPCODE_GET_WRITE_POS,
	DND_AGENT_OPCODE_SET_MON_FILTER,
	DND_AGENT_OPCODE_GET_MON_FILTER,
	DND_AGENT_OPCODE_SET_MON_CONTROL
}DND_AGENT_L5_OPCODE;

//The following Message IDs are the services supported by the NDnS:
//Incoming Messages:
typedef enum _NDNS_AGENT_L5_OPCODE
{
	//Indication Handling OPCODES
	NDNS_OPCODE_REGISTER_INDICATION = NDNS_OPCODE_BASE,
	NDNS_OPCODE_UNREGISTER_INDICATION,
	NDNS_OPCODE_INDICATION_ARRIVED,

	//Commands OPCODES
	NDNS_OPCODE_COMMAND,

	//Data Getters
	NDNS_OPCODE_GET,
	
	//User Connection Mode
	NDNS_OPCODE_SET,

	//APDO opcodes
	NDNS_OPCODE_APDO
} NDNS_AGENT_L5_OPCODE;

//The following Message IDs are the services supported by the Supplicant:
//Incoming Messages:
typedef enum _SUP_AGENT_L5_OPCODE
{
	//Indication Handling OPCODES
	SUP_OPCODE_REGISTER_INDICATION = SUP_OPCODE_BASE,
	SUP_OPCODE_UNREGISTER_INDICATION,
	SUP_OPCODE_INDICATION_ARRIVED,
	
	//Credentials setters
	SUP_OPCODE_SET,

	//Supp config
	SUP_OPCODE_ENABLE,
	SUP_OPCODE_DISABLE,
	SUP_OPCODE_RESET
} SUP_AGENT_L5_OPCODE;

//The following Message IDs are the services supported by Act:
//Incoming Messages:
typedef enum _ACT_L5_OPCODE
{	
	// Version 
	ACT_OPCODE_VALIDATE_VERSION = ACT_OPCODE_BASE,	// Version validation request
	ACT_OPCODE_GET_VERSION,							// Version getter

	// Production
	ACT_OPCODE_RESET_FOR_PRODUCTION,

	// Driver connectivity reports
	ACT_OPCODE_DRIVER_UP,

	// Errors reports
	ACT_OPCODE_ERROR_REPORT,

	// Remove report
	ACT_OPCODE_DEVICE_REMOVED,

	ACT_OPCODE_GET_DRIVER_STATE,

	ACT_OPCODE_FULL_RESTART,

	ACT_OPCODE_KDAPI_ADAPTER_RESTART,

	ACT_OPCODE_RESET_DEVICE,

	ACT_OPCODE_CLOSE
} ACT_L5_OPCODE;




#endif // _INTEL_80216_L5_OPCODES_H