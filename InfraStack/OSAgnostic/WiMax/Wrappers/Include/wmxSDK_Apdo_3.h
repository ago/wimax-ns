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
#ifndef _WMX_SDK_APDO_3_H
#define _WMX_SDK_APDO_3_H


#include "wmxSDK_Apdo_Cmn.h"
#include "wmxSDK_Nds_3.h"



/// <summary>
/// Once registered, this callback will be called when the SDK wishes to inform of changes in the WiMAX connection.
///
/// The BEK is the new bootstrap message decryption key.
///
/// The ProvisioningClientCfgDataBlob contains data stored by the provisioning client in the L4-db for 
/// persistency using the wmx_StoreProvisioningClientCfgDataBlob() API.
/// </summary>
///
/// <param name="linkStatus">(IN) An enum specifying whether the link is up or down.</param>
/// <param name="nspId">(IN) A struct specifying the NSP_ID of the NSP with which a connection was established / broken.</param>
/// <param name="activationConnection">(IN) A boolean value indicating whether the current connection is for activation (meaning, among other things,
///									   bootstrap info is expected to arrive) or regular service use.</param>
/// <param name="realm">(IN)nsp realm.</param>
typedef void (WMX_EXT_CALL_CONV *wmx_pApdoLinkStatusCB_t)(wmx_ApdoLinkStatus_t linkStatus, char operatorName[WMX_NSP_NAME_MAX_SIZE],
														  wmx_NSPid_t nspId, wmx_ApdoActivationConnection_t activationConnection,
														  char realm[WMX_NSP_REALM_MAX_SIZE]);

/// <summary>
/// Once registered, this callback will be called by the SDK to indicates a response on an alert.
/// In some cases getting the response involves user interaction through the CM and in that case the user�s input is relayed from the CM.
/// </summary>
///
/// <param name="alertResponse">(IN) An enum specifying the response.</param>
typedef void (WMX_EXT_CALL_CONV *wmx_pApdoAlertResponseCB_t)( wmx_ApdoAlertResponse_t alertResponse );
					
/// <summary>
/// Once registered, this callback may be used to pass L2 Bootstrap or notification messages to the provisioning client, if supported.
///
/// This is called Out-Of-Band because it is meant to pass to the client notifications it may also 
/// receive on its own through different transport mechanisms.
/// </summary>
///
/// <param name="oobMessage">(IN) A buffer containing the data to be passed to the client.</param>
//typedef void (WMX_EXT_CALL_CONV *wmx_pApdoOobNotificationCB_t)( wmx_ApdoOobMessage_t oobMessage );

/// <summary>
/// This callback triggers a wmx_APDOSessionStatus call (for use when the APDO logic comes up and wants to query the status).
/// </summary>
typedef void (WMX_EXT_CALL_CONV *wmx_pRefreshApdoSessionStatusCB_t)();

/// <summary>
/// Once registered, this callback will be called as a notification for download operation status.
/// </summary>
///
/// <param name="downloadStatus">(IN) An enum specifying whether the download was approved or denied.</param>
typedef void (WMX_EXT_CALL_CONV *wmx_pApdoFumoDownloadApprovalStatusCB_t)( wmx_ApdoDownloadStatus_t downloadStatus );

/// <summary>
/// Once registered, this callback will be called when requesting to delete account from tree.xml
/// </summary>
///
/// <param name="downloadStatus">(IN) Account name to delete.</param>
typedef void (WMX_EXT_CALL_CONV *wmx_pApdoDeleteDMAccountCB_t)( wmx_ApdoDeleteDMAccountCBStruct_t apdoDeleteDMAccountCBStruct);

/// <summary>
/// This API gets a value from the APDO tree. If the path doesn't exist, NULL is returned with success status code.
/// </summary>
///
/// <param name="pAPDOPath">(IN) The path of the value to retrieve.</param>
/// <param name="pValue">(OUT) The value returned from the APDO tree.</param>
/// <param name="pAPDOType">(OUT) The type of the value returned from the APDO tree.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetAPDOinfo( wmx_APDOPath_t pAPDOPath, void *pValue, wmx_pAPDOType_t pAPDOType );

/// <summary>
/// This API adds a value to the APDO tree. If the path given already exists, nothing is done.
/// </summary>
///
/// <param name="pAPDOPath">(IN) The path of the value to add.</param>
/// <param name="pValue">(IN) The value to add to the APDO tree.</param>
/// <param name="pAPDOType">(IN) The type of the value to add.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_AddAPDOinfo( wmx_APDOPath_t pAPDOPath, void *pValue, wmx_APDOType_t APDOType );

/// <summary>
/// This API provides a boolean that reveals if the polling mechanism is supported.
/// </summary>
///
/// <param name="pDevCAP_t">(IN\OUT) The buffer should be a boolean parameter.</param>
///
/// <returns>A wmx_Status_t value.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetPollingIntervalSupportedMode (BOOL *pollingIntervalSupported);
/// <summary>
/// This API updates a value in the APDO tree. If the path given doesn't exist, nothing is done.
/// </summary>
///
/// <param name="pAPDOPath">(IN) The path of the value to update.</param>
/// <param name="pValue">(IN) The new value.</param>
/// <param name="pAPDOType">(IN) The type of the value to update.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_UpdateAPDOinfo( wmx_APDOPath_t pAPDOPath, void *pValue, wmx_APDOType_t APDOType );

/// <summary>
/// This API deletes a leaf in the APDO tree. If the path given doesn't represent a leaf, nothing is done.
/// </summary>
///
/// <param name="pAPDOPath">(IN) The path to delete.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_DeleteAPDOinfo( wmx_APDOPath_t pAPDOPath );

/// <summary>
/// This API triggers an operation in the device based on the data contained in the node specified in the API�s argument. 
/// While the concept of the operation triggered on a specific node may be known to the server, 
/// the exact implementation is dependant on the client (example, pop up a browser window to surf to a URI given as the value in the specified node).
/// </summary>
///
/// <param name="pAPDOPath">(IN) The path of the node on which to trigger an operation.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_ExecuteAPDOinfo( wmx_APDOPath_t pAPDOPath ); 

/// <summary>
/// This API allows the provisioning client to notify the SDK of events during a session with the server.
/// </summary>
///
/// <param name="sessionStatus">(IN) An enum specifying the status to be indicated to the SDK.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_ApdoSessionStatus( wmx_ApdoSessionStatus_t sessionStatus );

/// <summary>
/// This API allows the provisioning client to pass a request from the server to do GUI/User query via CM.
/// </summary>
///
/// <param name="alert">(IN) An enum specifying the alert to be notified to the SDK.</param>
/// <param name="alertContent">(IN) A buffer whose content is alert type specific (for example, for a user action approval request, 
///                            a verbose string describing the planned action is given as the content).</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_ApdoAlertNotification(wmx_ApdoAlert_t alert, wmx_ApdoAlertContent_t alertContent ); 

/// <summary>
/// This API allows the provisioning client to provide information on the number of FUMO bites downloaded so far.
/// </summary>
///
/// <param name="alert">(IN) An enum specifying the alert to be notified to the SDK.</param>
/// <param name="alertContent">(IN) A buffer whose content is alert type specific (for example, for a user action approval request, 
///                            a verbose string describing the planned action is given as the content).</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_ApdoFumoUpdate(wmx_FUMOUpdate_t updateType, wmx_FUMOUpdateContent_t updateContent ); 


/// <summary>
/// Used by the client to store a data buffer in the L4-db for persistency.
///
/// The client can retrieve the blob by using the wmx_GetProvisioningClientCfgDataBlob() API or by waiting for 
/// the ApdoLinkStatusCB callback to be triggered when a connection to an NSP is made (link up).
/// </summary>
///
/// <param name="nspId">(IN) A struct specifying the NSP_ID of the NSP to which the cfg data should be attached.</param>
/// <param name="cfgDataBlob">(IN) A buffer containing a blob of data to be stored by the provisioning agent.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
//wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_StoreProvisioningClientCfgDataBlob( wmx_NSPid_t nspId, wmx_ProvisioningClientCfgDataBlob_t cfgDataBlob);
																						
/// <summary>
/// Used by the client to retrieve a data buffer stored in the L4-db for persistency.
///
/// The same blob is also passed to the client when a connection is made to an NSP, using the ApdoLinkStatusCB callback.
/// </summary>
///
/// <param name="nspId">(IN) A struct specifying the NSP_ID of the NSP to which the cfg data is attached.</param>
/// <param name="cfgDataBlob">(OUT) A buffer containing a blob of data stored by the provisioning agent using the wmx_StoreProvisioningClientCfgDataBlob() API.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
//wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetProvisioningClientCfgDataBlob( wmx_NSPid_t nspId, wmx_pProvisioningClientCfgDataBlob_t pCfgDataBlob);		


/// <summary>
/// The registration API for a wmx_pApdoLinkStatusCB_t callback function.
/// </summary>
///
/// <param name="alertResponse">(IN) A pointer to the application function to be called (more details in the callback's definition).</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_RegisterApdoLinkStatusCB( wmx_pApdoLinkStatusCB_t ApdoLinkStatusCB );


/// <summary>
/// The de-registration API for a wmx_pApdoLinkStatusCB_t callback function.
/// </summary>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_UnregisterApdoLinkStatusCB();

/// <summary>
/// The registration API for a wmx_pApdoAlertResponseCB_t callback function.
/// </summary>
///
/// <param name="alertResponse">(IN) A pointer to the application function to be called (more details in the callback's definition).</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_RegisterApdoAlertResponseCB( wmx_pApdoAlertResponseCB_t ApdoAlertResponseCB );


/// <summary>
/// The de-registration API for a wmx_pApdoAlertResponseCB_t callback function.
/// </summary>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_UnregisterApdoAlertResponseCB();

/// <summary>
/// The registration API for a wmx_pApdoOobNotificationCB_t callback function.
/// </summary>
///
/// <param name="oobMessage">(IN) A pointer to the application function to be called (more details in the callback's definition).</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
//wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_RegisterApdoOobNotificationCB( wmx_pApdoOobNotificationCB_t ApdoOobNotificationCB );


/// <summary>
/// The de-registration API for a wmx_pApdoOobNotificationCB_t callback function.
/// </summary>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
//wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_UnregisterApdoOobNotificationCB();

/// <summary>
/// The registration API for a wmx_pRefreshApdoSessionStatusCB_t callback function.
/// </summary>
///
/// <param name="refreshApdoSessionStatusCB">(IN) A pointer to the application function to be called (more details in the callback's definition).</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_RegisterRefreshApdoSessionStatusCB( wmx_pRefreshApdoSessionStatusCB_t refreshApdoSessionStatusCB);


/// <summary>
/// The de-registration API for a wmx_pRefreshApdoSessionStatusCB_t callback function.
/// </summary>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_UnregisterRefreshApdoSessionStatusCB();

/// <summary>
/// The registration API for a wmx_pApdoFumoALinkStatusCB_t callback function.
/// </summary>
///
/// <param name="alertResponse">(IN) A pointer to the application function to be called (more details in the callback's definition).</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_RegisterApdoFumoDownloadApprovalStatusCB( wmx_pApdoFumoDownloadApprovalStatusCB_t apdoFumoDownloadApprovalStatusCB );


/// <summary>
/// The de-registration API for a wmx_pApdoFumoALinkStatusCB_t callback function.
/// </summary>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_UnregisterApdoFumoDownloadApprovalStatusCB();

/// <summary>
/// The registration API for a wmx_pApdoDeleteDMAccountCB_t callback function.
/// </summary>
///
/// <param name="alertResponse">(IN) A pointer to the application function to be called (more details in the callback's definition).</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_RegisterApdoDeleteDMAccountCB( wmx_pApdoDeleteDMAccountCB_t apdoDeleteDMAccountCB );


/// <summary>
/// The de-registration API for a wmx_pApdoDeleteDMAccountCB_t callback function.
/// </summary>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_UnregisterApdoDeleteDMAccountCB();

/// <summary>
/// This API should be used when there is a package which was downloaded and and update should start.
/// </summary>
///
/// <param name="path">(IN) The path of the downloaded package.</param>
/// <param name="fileName">(IN) The fileName of the downloaded package.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_ApdoFumoSetPackagePath(char* path, char* fileName);


/// <summary>
/// This API should be used in order to decrypt bootstrap message.
/// </summary>
///
/// <param name="inBuffer">(IN) The buffer which contains the encrypted message.</param>
/// <param name="inBufferSize">(IN) The size of the encrypted message.</param>
/// <param name="outBuffer">(IN\OUT) The buffer which contains the decrypted message should be allocated.</param>
/// <param name="outBufferSize">(IN) The size of the out buffer.</param>
/// <param name="actualOutBufferSize">(OUT) The actual needed size of the decrypted message.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_DecBootStrap(UINT8* inBuffer, UINT32 inBufferSize, UINT8* outBuffer, UINT32 outBufferSize, UINT32* actualOutBufferSize);


/// <summary>
/// This API provides bootstrap information.
/// </summary>
///
/// <param name="buffer">(IN\OUT) The buffer should be allocated and will be filled with the bootstrap message.</param>
/// <param name="bufferSize">(IN) The number of bytes allocated for this buffer.</param>
/// <param name="actualSize">(OUT) The actual size of the bootstrap message. If the actualSize is zero, 
///		there is no bootstrap message available. If the actualSize is larger than the bufferSize, 
///		this value represents the size that should be allocated for the buffer.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_ApdoGetServerParams(UINT8* buffer, size_t bufferSize, size_t* actualSize);


/// <summary>
/// This API provides operator special behavior information of the currently connected NSP if does not have then 
/// </summary>
///
/// <param name="buffer">(IN\OUT) The buffer should be allocated and will be filled with the apdo operator configuration struct.</param>
/// <param name="bufferSize">(IN) The number of bytes allocated for this buffer.</param>
/// <param name="actualSize">(OUT) The actual size of the  apdo operator configuration struct. 
///		
///
/// <returns>A wmx_Status_t value.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetApdoOperatorConfigurations(wmx_pApdoOperatorConfigurations_t currentConfiguration, size_t currentConfigurationSize, UINT32 * currentConfigurationActualSize);

/// <summary>
/// This API return data regarding the current link up and connected operator
/// </summary>
///
/// <param name="linkStatus">(OUT) Current link status.</param>
/// <param name="nspName">(OUT) If connected - the current operator name otherwise null.</param>
/// <param name="nspId">(OUT) </param>
/// <param name="realm">(OUT) </param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetApdoConnectionParameters(wmx_pApdoLinkStatus_t linkStatus, 
																	 char nspName[WMX_NSP_NAME_MAX_SIZE], 
																	 wmx_pNSPid_t nspId, 
																	 char realm[WMX_NSP_REALM_MAX_SIZE],
																	 char toDmAcc[MAX_ACCOUNT_NAME_SIZE]);

#endif // _WMX_SDK_APDO_3_H