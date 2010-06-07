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
#ifndef _WMX_SDK_SUP_DEFINES_H
#define _WMX_SDK_SUP_DEFINES_H

//EAP methods:
#define SWC_EAP_TYPE_NONE		 0
#define SWC_EAP_TYPE_IDENTITY		 1
#define SWC_EAP_TYPE_NOTIFICATION	 2
#define SWC_EAP_TYPE_NAK		 3
#define SWC_EAP_TYPE_MD5		 4
#define SWC_EAP_TYPE_OTP		 5
#define SWC_EAP_TYPE_GTC		 6
#define SWC_EAP_TYPE_TLS		 13
#define SWC_EAP_TYPE_LEAP		 17
#define SWC_EAP_TYPE_SIM		 18
#define SWC_EAP_TYPE_TTLS		 21
#define SWC_EAP_TYPE_PEAP		 25
#define SWC_EAP_TYPE_MSCHAPV2		 26
#define SWC_EAP_TYPE_TLV		 33
#define SWC_EAP_TYPE_FAST		 43
#define SWC_EAP_TYPE_PSK		 255 /* Not defined */
#define SWC_EAP_TYPE_AKA		 23 /* Not defined */

//Phase 2 (inner) methods:
#define SWC_PHASE2_METHOD_EAP_GTC	1
#define SWC_PHASE2_METHOD_EAP_MSCHAPV2	2
#define SWC_PHASE2_METHOD_EAP_MD5	3
#define SWC_PHASE2_METHOD_GTC		4
#define SWC_PHASE2_METHOD_MSCHAPV2	5
#define SWC_PHASE2_METHOD_MSCHAP	6
#define SWC_PHASE2_METHOD_CHAP		7
#define SWC_PHASE2_METHOD_EAP_TLS	8
#define SWC_PHASE2_METHOD_PAP		9

// eventType:
#define     SWC_CALLBACK_TYPE_CREDENTIAL  1
#define     SWC_CALLBACK_TYPE_EVENT       2

//credId:
//For SWC_CALLBACK_TYPE_CREDENTIAL (When you get one of the following, you should call the appropriate PVC wrapper api/s)
#define     SWC_CRED_IDENTITY       1
#define     SWC_CRED_PASSWORD       2     
#define     SWC_CRED_PRIVATE_KEY    11    
#define		SWC_CRED_CA_CERTIFICATE	12

//For SWC_CALLBACK_TYPE_EVENT (although for now it�s for knowledge only, no action is required)
#define SWC_EV_REJECTED_CREDENTIAL	1
#define SWC_EV_REJECTED_METHOD		2
#define SWC_EV_REJECTED_IDENTITY	3
#define SWC_EV_REJECTED_CERTIFICATE	4
#define SWC_EV_REJECTED_CHALLENGE	5
#define SWC_EV_RESTRICTED_LOGON_HOURS	6
#define SWC_EV_ACCOUNT_DISABLED		7
#define SWC_EV_ACCOUNT_NO_DIAL_IN	8
#define SWC_EV_TLV_INVALID		9
#define SWC_EV_TLV_UNKNOWN		10
#define SWC_EV_TLV_NAK			11
#define SWC_EV_FAST_CMAC_INVALID	12
#define SWC_EV_FAST_PROVISION_SUCCESS	13
#define SWC_EV_FAST_INVALID_PAC_KEY	14
#define SWC_EV_FAST_INVALID_PAC_OPAQUE	15
#define SWC_EV_EAP_CLEAR_TEXT_FAILURE	16
#define SWC_EV_EAP_CLEAR_TEXT_SUCCESS	17
#define SWC_EV_EAP_FAILURE		18
#define SWC_EV_EAP_SUCCESS		19
#define SWC_EV_EAP_INTERMEDIATE_FAILURE	20
#define SWC_EV_EAP_INTERMEDIATE_SUCCESS	21
#define SWC_EV_SIM_PIN_INCORRECT	22
#define SWC_EV_SIM_PIN_REQUIRED		23
#define SWC_EV_SIM_NO_READER		24
#define SWC_EV_SIM_NO_CARD		25
#define SWC_EV_SIM_FAILURE		26
#define SWC_EV_EAP_METHOD_BASE 		0x1000 /* Not a real event, just an offset */

#define SWC_EV_EAP_METHOD_TLS	(SWC_EV_EAP_METHOD_BASE + SWC_EAP_TYPE_TLS)
#define SWC_EV_EAP_METHOD_TTLS	(SWC_EV_EAP_METHOD_BASE + SWC_EAP_TYPE_TTLS)
#define SWC_EV_EAP_METHOD_PEAP	(SWC_EV_EAP_METHOD_BASE + SWC_EAP_TYPE_PEAP)
#define SWC_EV_EAP_METHOD_SIM	(SWC_EV_EAP_METHOD_BASE + SWC_EAP_TYPE_SIM)
#define SWC_EV_EAP_METHOD_AKA	(SWC_EV_EAP_METHOD_BASE + SWC_EAP_TYPE_AKA)
#define SWC_EV_EAP_METHOD_PSK	(SWC_EV_EAP_METHOD_BASE + SWC_EAP_TYPE_PSK)
#define SWC_EV_EAP_METHOD_LEAP	(SWC_EV_EAP_METHOD_BASE + SWC_EAP_TYPE_LEAP)
#define SWC_EV_EAP_METHOD_FAST	(SWC_EV_EAP_METHOD_BASE + SWC_EAP_TYPE_FAST)
#endif // _WMX_SDK_SUP_DEFINES_H