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
#ifndef _WMX_SDK_APDO_CMN_H
#define _WMX_SDK_APDO_CMN_H



#include "CommonServices.h"
#include "WrappersCommon.h"
#include "wmxSDK_Nds_Cmn.h"
//#include "wmxSDK_Nds_3.h"
#include "wimax_osal_config_controler.h"


#define MAX_APDO_PATH 1024
#define MAX_APDO_GET_RESULT 1024
#define BEK_LENGTH 17 // 16 bytes + 1 for null terminated
#define MAX_DM_ACCOUNT_NAME 100

/// <summary>
/// Type definition for a variable containing a leaf in the OMA DM tree. 
/// </summary>
typedef INT8			*wmx_APDOPath_t;
typedef wmx_APDOPath_t	*wmx_pAPDOPath_t;

/// <summary>
/// Type definition for an enum specifying the types of data in the APDO functions
/// </summary>
typedef enum _wmx_APDOType_t
{
	APDO_Integer = 0x1,
	APDO_Float,
	APDO_Double,
	APDO_String,
	APDO_Bool,
	APDO_Node
} wmx_APDOType_t, *wmx_pAPDOType_t;

#define MAX_ALERT_CONTENT 512
#define MAX_PROVISIONING_CLIENT_CFG_DATA_BLOB 1024
#define MAX_APDO_OOB_MESSAGE 1024
#define MAX_APDO_ACTIVATION_CONNECTION 1024

typedef UINT8 wmx_BEKBuffer_t[BEK_LENGTH], *wmx_pBEKBuffer_t;

/// <summary>
/// Type definition for a buffer whose content is alert type specific
/// (for example, for a user action approval request, a verbose string describing the planned action is given as the content).
/// </summary>
typedef UINT8	*wmx_ApdoAlertContent_t;

/// <summary>
/// Type definition for a buffer containing a blob of data to be stored by the provisioning agent.
/// </summary>
typedef UINT8   *wmx_ProvisioningClientCfgDataBlob_t;
typedef wmx_ProvisioningClientCfgDataBlob_t   *wmx_pProvisioningClientCfgDataBlob_t;

/// <summary>
/// Type definition for an encryption key used to decrypt bootstrap messages. 
/// The BEK is derived from the EMSK key after the EMSK is generated at the end of
/// a successful EAP exchange that occurs in the Authentication phase of the WiMAX network entry.
/// </summary>
typedef UINT8   *wmx_pBEK_t; 

/// <summary>
/// Type definition for a buffer containing the data to be passed to the client.
/// </summary>
typedef UINT8   *wmx_ApdoOobMessage_t; 

///	<summary>
///	Type definition for a struct for FUMO Update.
///	<summary>
typedef struct _wmx_FUMOUpdateContent_t
{
	UINT32 downloadedBytes;
	UINT32 totalBytes; 
}wmx_FUMOUpdateContent_t, *wmx_pFUMOUpdateContent_t;

/// <summary>
/// Type definition for a boolean value indicating whether the current connection is for activation 
/// (meaning, among other things, bootstrap info is expected to arrive) or regular service use.
/// </summary>
typedef BOOL   wmx_ApdoActivationConnection_t; 


/// <summary>
/// Type definition for an enum specifying the status to be indicated to the SDK.
/// </summary>
typedef enum _wmx_ApdoSessionStatus_t
{
	SessionWaitingForBootstrap,
	SessionBootstrapArrived,
	SessionStart,
	SessionEndSuccess,
	SessionEndFailure,
	SessionUpdateFailedNetworkDisconnect,
	SessionUpdateFailedBadAuthentication 
} wmx_ApdoSessionStatus_t, *wmx_pApdoSessionStatus_t;

/// <summary>
/// Type definition for an enum specifying the alert to be notified to the SDK.
/// </summary>
typedef enum _wmx_ApdoAlert_t 
{
	ActionApprovalRequest        //The server requests the SDK to approve its next action (for example, the download of data to the device).
								 //Implementation specific, the device may decide to ask the user for approval or approve the action on its own.
} wmx_ApdoAlert_t, *wmx_pApdoAlert_t;

/// <summary>
/// Type definition for an enum specifying the response.
/// </summary>
typedef enum _wmx_ApdoAlertResponse_t 
{
	ActionRequestApproved,
	ActionRequestDenied
} wmx_ApdoAlertResponse_t, *wmx_pApdoAlertResponse_t;

/// <summary>
/// Type definition for an enum specifying the FUMO Download Progress.
/// </summary>
typedef enum _wmx_FUMOUpdate_t
{
	FumoUpdateDownloadProgress
} wmx_FUMOUpdate_t, *wmx_pFUMOUpdate_t;

/// <summary>
/// Type definition for an enum specifying whether the link is up or down.
/// </summary>
typedef enum _wmx_ApdoLinkStatus_t 
{
	APDO_linkUp,
	APDO_linkDown
} wmx_ApdoLinkStatus_t , *wmx_pApdoLinkStatus_t ;

// TODO: Oran - removed in merge - check if this is ok
/*typedef enum _wmx_EapType_t
{
	EAP_TLS = 13,
	EAP_TTLS = 21,
	EAP_AKA = 23,
	PLAIN_MSCHAPv2 = 256,
	EAP_MSCHAPv2 = 1000,
	CHAP = 7
} wmx_EapType_t, *wmx_pEapType_t;

/// <summary>
/// An enum which specifies the possible certificates' type
/// </summary>
typedef enum _CertType_t
{
	Device = 0x1,
	CA
}CertType_t, *pCertType_t;

/// <summary>
/// An enum which specifies all the client's authentication statuses
/// </summary>
typedef enum _ClientAuth_t
{
	NotRequired = 0x0,  //authentication isn't required
	Required			//authentication required
}ClientAuth_t, *pClientAuth_t;*/

//////////////////////////////////////////////////////////////////////////
/// <summary>
/// Type definition for an enum specifying whether the link is up or down.
/// </summary>
typedef enum _wmx_ApdoDownloadStatus_t 
{
	DownloadApproved,
	DownloadDenied,
	UpdateDenied
} wmx_ApdoDownloadStatus_t , *wmx_pApdoDownloadStatus_t ;

typedef struct _wmx_ApdoOperatorConfigurations_t
{
	BOOL					preProvBStrap; //determined whether to use pre provisioned bootstrap
	BOOL					pollingInterval; // determines whether to use special pooling interval = -1 
	BOOL					blockUDP; //determines whether to block the use of UDP
	BOOL					pollingSupported;
	BOOL					pollingAttempts; // determines whether to use the new polling attempts MO.
	char					nspTagName[MAX_SIZE_OF_NSP_NAME];
	BOOL					disableOTAP;
	BOOL					disablePseudoNAI;

}wmx_ApdoOperatorConfigurations_t, *wmx_pApdoOperatorConfigurations_t;

typedef struct _wmx_ApdoDeleteDMAccountCBStruct_t
{
	// enum for allowing one or all delete
	// consider sending <x> entry
	char accountName[MAX_DM_ACCOUNT_NAME];
} wmx_ApdoDeleteDMAccountCBStruct_t, *wmx_pApdoDeleteDMAccountCBStruct_t;

#endif // _WMX_SDK_APDO_CMN_H