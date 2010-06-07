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
#include "NDnSAgent_Internals.h"
#include "NDnSAgent_APDO.h"
#include "NDnSAgent_DB_if.h"
#include "NDnSAgent.h"

#include "CommonServices.h"
#include "WrappersCommon.h"
#include "L5OpCodes.h"		

#include "L4ConfigurationManager.h"
#include "wmxSDK_Apdo_Internals.h"
#include "wmxSDK_Apdo_Cmn.h"
#include "wmxSDK_Apdo_Utils.h"
#include "NDnSAgent_Utils.h"
#include "wmxSDK_Nds_Cmn.h"
#include "wmxSDK_Nds_IndHandler.h"		
#include "wimax_osal_config_controler.h"

#include "NDnSAgent_Monitor.h"

#include "NDnSAgent_DB_Internal.h"
#include "wimax_osal_ip_services.h"

#define TO_DM_ACCOUNT_STR	"To-DMAcc"
#define SERVER_ID_STR	"ServerID"
#define FUMO_BRANCH			"FwUpdate"
#define DOWNLOAD_STATE_PATH	"FUMO/FwUpdate/State"
extern BOOL RunWithDSim;

// Declarations
void CheckIfProvisioningStarted();
void HandleApdoSessionStatus(wmx_ApdoSessionStatus_t sessionStatus);
void HandleAPDOFailure(wmx_Status_t status);

wmx_Status_t GetPackageInfo(void *buffer, UINT32 *bufferSize)
{
	wmx_PackageInfo_t pkgInfo;
	FumoInternalParams_t fumoInternalParams;	
	char mandatoryUpdateLogic[MAX_REGISTRY_ANSWER] = {0};
	wmx_Status_t st;
	size_t pathLen = 0;
	size_t fileNameLen = 0;
	BOOL mandatoryUpdate;

	if (*bufferSize >= sizeof(wmx_PackageInfo_t))
	{
		memset(&pkgInfo, 0, sizeof(wmx_PackageInfo_t));
		st = L4db_GetFumoInternalInfo(&fumoInternalParams);

		if (st != WMX_ST_OK)
		{
			return st;
		}

		pathLen = OSAL_strnlen(fumoInternalParams.pkgPath, MAX_APDO_PATH) + 1;
		fileNameLen = OSAL_strnlen(fumoInternalParams.pkgFileName, MAX_FILE_NAME_SIZE) + 1;
		
		OSAL_memcpy_s(pkgInfo.filePath, MAX_APDO_PATH, fumoInternalParams.pkgPath, pathLen);
		OSAL_memcpy_s(pkgInfo.fileName, MAX_FILE_NAME_SIZE, fumoInternalParams.pkgFileName, fileNameLen);

		//// Instead of calling direct to the installer we call the updater with package name as a parameter
		//// Updater should be in AppSrv root directory
		//pRootPathW = L4Configurations_getRootPath();

		//if(pRootPathW)
		//{			
		//	wcstombs_s(&numOfCharConverted, pRootPath, MAX_REGISTRY_ANSWER, pRootPathW, strlen(pRootPathW));
		//	OSAL_memcpy_s(pkgInfo.filePath, MAX_APDO_PATH, pRootPath, OSAL_strnlen(pRootPath, MAX_APDO_PATH));
		//}
		//else
		//{
		//	pkgInfo.filePath[0] = '\0';
		//}

		//// Copy updater name, package path and file name and arguments
		//OSAL_memcpy_s(pkgInfo.fileName, MAX_SIZE_OF_STRING_BUFFER, UPDATER_FILE_NAME, strlen(UPDATER_FILE_NAME));		
		//						

		pkgInfo.forceReboot = FALSE;

		L4Configurations_getApdoMandatoryUpdateLogic(mandatoryUpdateLogic);
		
		if (0 == OSAL_stricmp(DEFAULT_TRUE_LOWER, mandatoryUpdateLogic))
		{
			mandatoryUpdate = TRUE;
		}
		else
		{
			mandatoryUpdate = FALSE;
		}

		// Set flags according to operation type
		if (fumoInternalParams.fumoOperation == foDownload)
		{
			pkgInfo.mandatoryUpdate = !mandatoryUpdate;
			pkgInfo.warnUser = TRUE;			
		}
		else if (fumoInternalParams.fumoOperation == foDownloadAndUpdate)
		{
			pkgInfo.mandatoryUpdate = mandatoryUpdate;
			pkgInfo.warnUser = TRUE;			
		}
		*(wmx_pPackageInfo_t)buffer = pkgInfo;

	
		return WMX_ST_OK;
	}

	return WMX_ST_FAIL;
}

wmx_Status_t GetAPDOinfo(void *buffer, UINT32 *resultBufferSize, void *resultBuffer)
{	
	wmx_APDOType_t APDOType;
	wmx_APDOPath_t givenPath;
	wmx_Status_t status;	
	char *tmpResultBuffer;
	
	tmpResultBuffer = (char*)malloc(MAX_APDO_GET_RESULT);
	if (tmpResultBuffer == 0) return WMX_ST_PIPE_FAILURE;

	// Parse the given buffer to type and path
	wmxApdo_ParseAPDOBufferNoValue(buffer, &givenPath, &APDOType);

	// Call the function that fetches the value from the local DB
	status = L4db_GetAPDOinfo( (wmx_APDOPath_t)givenPath, (char *)tmpResultBuffer, &APDOType );

	if (status != WMX_ST_OK) 
	{
		free(tmpResultBuffer);
		return status;
	}

	// Check that the given buffer is large enough
	if (*resultBufferSize < sizeof(wmx_APDOType_t) + wmxApdo_GetBufferLength(tmpResultBuffer, APDOType))
	{
		free(tmpResultBuffer);
		return WMX_ST_PIPE_FAILURE;
	}

	// create the return buffer
	OSAL_memcpy_s(resultBuffer, *resultBufferSize, &APDOType, sizeof(wmx_APDOType_t));
	//OSAL_memcpy_s((char*)resultBuffer + sizeof(wmx_APDOType_t), *resultBufferSize-sizeof(wmx_APDOType_t), tmpResultBuffer, OSAL_strnlen((char*)tmpResultBuffer, *resultBufferSize) + 1); // +1 for the \0
	OSAL_memcpy_s((char*)resultBuffer + sizeof(wmx_APDOType_t), *resultBufferSize-sizeof(wmx_APDOType_t), tmpResultBuffer, wmxApdo_GetBufferLength(tmpResultBuffer, APDOType)); 

	*resultBufferSize = sizeof(wmx_APDOType_t) + wmxApdo_GetBufferLength(tmpResultBuffer, APDOType);

	free(tmpResultBuffer);
	return WMX_ST_OK;
}

wmx_Status_t AddAPDOinfo(void *buffer, UINT32 *bufferSize)
{	
	wmx_APDOPath_t givenPath;
	char *pValue;
	wmx_APDOType_t APDOType;	
	wmx_Status_t st;

	UNREFERENCED_PARAMETER(bufferSize);

	// Parse the given buffer to type, path and value
	wmxApdo_ParseAPDOBuffer(buffer, &givenPath, &pValue, &APDOType);

	// If setting pseudo MO To-DMAcc don't set provisioning as started
	// And part of FUMO process
	if ((strstr((char *)givenPath, TO_DM_ACCOUNT_STR) == NULL) &&
		(strstr((char *)givenPath, SERVER_ID_STR) == NULL) &&
		(strstr((char *)givenPath, FUMO_BRANCH) == NULL))
	{
		CheckIfProvisioningStarted();
	}
	
	// Call the function that adds the value to the local DB
	st = L4db_AddAPDOinfo( (wmx_APDOPath_t)givenPath, pValue, APDOType );

	HandleAPDOFailure(st);

	return st;
}

// The value we get here must be integer since we must update the db before calling this function
// and in the db there are already validation on the values and type of the download state.
wmx_Status_t CheckStateForFaiure(char *pNewState, char* pCurrState)
{
	wmx_Status_t st = WMX_ST_OK;
	char buff[BUFF_SIZE];
	DownloadState_t newDownloadState;
	DownloadState_t currDownloadState;

	OSAL_sprintf_s(buff,sizeof(buff) - 1, "%d", *(int*)pNewState);

	st = ConvertToDownloadState(buff, &newDownloadState);
	
	if (st != WMX_ST_OK)
	{
		TRACE(TR_MOD_APDO_AGENT, TR_SEV_ERR, "CheckStateForFaiure fail convert new download state");
		return st;
	}

	OSAL_sprintf_s(buff,sizeof(buff) - 1, "%d", *(int*)pCurrState);
	st = ConvertToDownloadState(buff, &currDownloadState);

	if (st != WMX_ST_OK)
	{
		TRACE(TR_MOD_APDO_AGENT, TR_SEV_ERR, "CheckStateForFaiure fail convert new download state");
		return st;
	}

	if (newDownloadState != currDownloadState)
	{
		switch(newDownloadState)
		{
	case dsDownloadFailed:
		st = WMX_ST_OK;
		NDnSAgent_PackageUpdate(psUpdateFailed);
		TRACE(TR_MOD_APDO_AGENT, TR_SEV_DEBUG, "Download state = dsDownloadFailed");
		break;
	case dsUpdateFailedHaveData:
		st = WMX_ST_OK;
		NDnSAgent_PackageUpdate(psUpdateFailed);
		TRACE(TR_MOD_APDO_AGENT, TR_SEV_DEBUG, "Download state = dsUpdateFailedHaveData");
		break;
	case dsUpdateFailedNoData:
		st = WMX_ST_OK;
		NDnSAgent_PackageUpdate(psUpdateFailed);
		TRACE(TR_MOD_APDO_AGENT, TR_SEV_DEBUG, "Download state = dsUpdateFailedNoData");
		break;
	// non-failure cases
	case dsDownloadIdle:
	case dsDownloadProgressing:
	case dsDownloadComplete:
	case dsReadyToUpdate:
	case dsUpdateProgressing:
	case dsUpdateSuccessfulHaveData:
	case dsUpdateSuccessfulNoData:
		break;
	// undefined download state
	default:
		st = WMX_ST_FAIL;
		TRACE(TR_MOD_APDO_AGENT, TR_SEV_ERR, "Download state is unknown");
		}
	}
	else
	{
		TRACE(TR_MOD_APDO_AGENT, TR_SEV_DEBUG, "CheckStateForFaiure - set to same Download state");
	}
	return st;
}
wmx_Status_t UpdateAPDOinfo(void *buffer, UINT32 *bufferSize)
{	
	wmx_APDOPath_t givenPath;
	char *pValue;
	wmx_APDOType_t APDOType;
	wmx_Status_t st;
	char currState[MAX_APDO_GET_RESULT];
	wmx_APDOType_t currStateType;
	BOOL checkState = FALSE;

	UNREFERENCED_PARAMETER(bufferSize);

	// Parse the given buffer to type, path and value
	wmxApdo_ParseAPDOBuffer(buffer, &givenPath, &pValue, &APDOType);

	// If setting pseudo MO To-DMAcc don't set provisioning as started
	// And part of FUMO process
	if ((strstr((char *)givenPath, TO_DM_ACCOUNT_STR) == NULL) &&
		(strstr((char *)givenPath, SERVER_ID_STR) == NULL) &&
		(strstr((char *)givenPath, FUMO_BRANCH) == NULL))
	{
		CheckIfProvisioningStarted();
	}	

	else if (OSAL_strstr((char *)givenPath, DOWNLOAD_STATE_PATH) != NULL)
	{
		st = L4db_GetAPDOinfo((char*)givenPath, currState, &currStateType);
		if (st != WMX_ST_OK)
		{
			TRACE(TR_MOD_APDO_AGENT, TR_SEV_ERR, "UpdateAPDOinfo - Failed to get current state.");
			checkState = FALSE;
		}
		else
		{			
			checkState = TRUE;
		}
	}
	// Call the function that updates the value in the local DB
	st = L4db_UpdateAPDOinfo( givenPath, pValue, APDOType );

	HandleAPDOFailure(st);
	if ((st == WMX_ST_OK) && (checkState))
	{		
		TRACE(TR_MOD_APDO_AGENT, TR_SEV_NOTICE, "UpdateAPDOinfo - before save to DB");
		SaveToDB();		
		st = CheckStateForFaiure(pValue, currState);
	}

	return st;
}

wmx_Status_t DeleteAPDOinfo(void *buffer, UINT32 *bufferSize)
{	
	wmx_Status_t st;
	UNREFERENCED_PARAMETER(bufferSize);	
	
	// If setting pseudo MO To-DMAcc don't set provisioning as started
	// And part of FUMO process
	// Note - serverID mo should be considered in the future as provisioning. 
	// We need to separate to specific API
	if ((strstr((char *)buffer, TO_DM_ACCOUNT_STR) == NULL) &&
		(strstr((char *)buffer, SERVER_ID_STR) == NULL) &&
		(strstr((char *)buffer, FUMO_BRANCH) == NULL))
	{
		CheckIfProvisioningStarted();
	}
	
	// Call the function that deletes the value from the local DB
	st = L4db_DeleteAPDOinfo( buffer );
	
	if (st != WMX_ST_DATA_UNAVAILABLE)
	{
		HandleAPDOFailure(st);
	}

	return st;
}

// In current versions there is only support for two types of execute commands - 
// First type is FUMO commands the second type is contacts execute for popping web browser.
wmx_Status_t ExecuteAPDOinfo(void *buffer, UINT32 *bufferSize)
{	
	char downloadPath[MAX_APDO_PATH];
	char downloadAndUpdatePath[MAX_APDO_PATH];
	BOOL res;
	char* pDownloadSubStr;
	char* pDownloadAndUpdateSubStr;
	char* pUpdateSubStr;
	wmx_Status_t st;
	ContactsInfo_t contactInfo;
	
	UNREFERENCED_PARAMETER(bufferSize);

	if (buffer != NULL)
	{	
		// Check if the command is FUMO
		if (strstr(buffer, L4DB_XML_TOKEN_FUMO) != NULL)
		{
			res = NDnSAgent_BuildFumoPath(FUMO_DOWNLOAD_PATH_SUFFIX, downloadPath, MAX_APDO_PATH);		

			if (!res)
			{		
				TRACE(TR_MOD_APDO_AGENT, TR_SEV_ERR, "Failed to build FUMO download path for FUMO execute.");
				return WMX_ST_FAIL;
			}

			res = NDnSAgent_BuildFumoPath(FUMO_DOWNLOAD_AND_UPDATE_PATH_SUFFIX, downloadAndUpdatePath, MAX_APDO_PATH);
			if (!res)
			{
				TRACE(TR_MOD_APDO_AGENT, TR_SEV_ERR, "Failed to build FUMO download and update path for FUMO execute.");
				return WMX_ST_FAIL;
			}

			// MZUR TODO change logic
			pDownloadSubStr = strstr(buffer, FUMO_DOWNLOAD_PATH_SUFFIX);
			pDownloadAndUpdateSubStr = strstr(buffer, FUMO_DOWNLOAD_AND_UPDATE_PATH_SUFFIX);
			pUpdateSubStr = strstr(buffer, FUMO_UPDATE_PATH_SUFFIX);
	
			// Compare path from buffer and according to result send suitable provisioning operation				
			// Download And Update
			if ((strcmp(buffer, downloadAndUpdatePath) == 0) || (pDownloadAndUpdateSubStr != NULL))		
			{	
				TRACE(TR_MOD_APDO_AGENT, TR_SEV_DEBUG, "FUMO download and update path execute.");
				L4db_SetFumoInternalFumoOperation(foDownloadAndUpdate);
				NDnSAgent_PackageUpdate(psUpdateReceived);
			}
			// Download
			else if ((strcmp(buffer, downloadPath) == 0) || (pDownloadSubStr != NULL))
			{
				TRACE(TR_MOD_APDO_AGENT, TR_SEV_DEBUG, "FUMO seperate download path execute.");
				L4db_SetFumoInternalFumoOperation(foDownload);
				NDnSAgent_PackageUpdate(psUpdateReceived);
			}		
			else
			{
				TRACE(TR_MOD_APDO_AGENT, TR_SEV_DEBUG, "FUMO seperate update path execute.");
				L4db_SetFumoInternalFumoOperation(foUpdate);				
			}
		}
		// Check if command is contacts		
		else 
		{
			st = L4db_GetContactInfoByPath(&contactInfo, buffer);

			if (st == WMX_ST_OK)
			{
				TRACE(TR_MOD_APDO_AGENT, TR_SEV_DEBUG, "Contacts path execute.");
				NDnSAgent_ProvisioningOperation(poUpdateLoadWebBrowser, (UINT16)contactInfo.uriType);
			}
			else
			{
				TRACE(TR_MOD_APDO_AGENT, TR_SEV_ERR, "APDO unrecognized execute command.");
				return WMX_ST_FAIL;
			}
		}
	}

	return WMX_ST_OK;
}

wmx_Status_t APDOSetPackagePath(void *buffer, UINT32 *bufferSize)
{	
	size_t pathLen = 0;
	size_t nameLen = 0;	
	char path[MAX_PATH];
	char name[MAX_FILENAME_LEN];

	wmx_Status_t st;

	char packageName[MAX_REGISTRY_ANSWER];
	BME_MonitorInstallingInd MonitorInstallingInd;

	UNREFERENCED_PARAMETER(bufferSize);

	// Get parameters from buffer
	pathLen = *(UINT32*)buffer;	
	memcpy(path, (char*)buffer + sizeof(UINT32), pathLen);
	nameLen = *((char*)buffer + sizeof(UINT32) + pathLen);
	memcpy(name, (char*)buffer + sizeof(UINT32) + pathLen + sizeof(UINT32), nameLen);

	// Update path and name in l4db
	st = L4db_SetFumoInternalPackagePath(path);	
	if (st != WMX_ST_OK)
	{
		return st;
	}

	// Build path for updater
	OSAL_strcpy_s(packageName, MAX_REGISTRY_ANSWER, path);
	OSAL_strcat_s(packageName, MAX_REGISTRY_ANSWER, "\\");
	OSAL_strcat_s(packageName, MAX_REGISTRY_ANSWER - pathLen, name);

	// Update path and name in registry for updater use
	L4Configurations_setPackagePath(packageName);

	st = L4db_SetFumoInternalPackageFileName(name);	
	if (st != WMX_ST_OK)
	{
		return st;
	}

	// Set install flag in registry	
	L4Configurations_setInstalling(DEFAULT_TRUE_STR);	
	TRACE(TR_MOD_APDO_AGENT, TR_SEV_DEBUG, "Installing flag was set to True. Initiating install process");
	

	MonitorInstallingInd = BMV_InstallingMonitorInit;
	wmx_PopulateMonitorInstallingInd(MonitorInstallingInd);
	// Initiate install process
	NDnSAgent_PackageUpdate(psUpdateStarted);	

	return st;
}

wmx_Status_t GetNSPContactInfoByName(char* nspName, void *buffer, UINT32 *bufferSize)
{
	wmx_Status_t status; 
	UINT32 numOfNSPs = WMX_NSPS_MAX_NUM;
	wmx_NSPid_t pNSPids[WMX_NSPS_MAX_NUM];
	ProvisionedNsp_t provisionedNsp;
	UINT32 i;
	BOOL found = FALSE;

	TRACE(TR_MOD_APDO_AGENT, TR_SEV_DEBUG, "GetNSPContactInfoByName [IN]");

	status = L4db_GetProvisionedNspIds(pNSPids, &numOfNSPs);
	
	if (status != WMX_ST_OK)
	{
		TRACE(TR_MOD_APDO_AGENT, TR_SEV_DEBUG, "GetNSPContactInfoByName Failed to L4db_GetProvisionedNspIds");
		return WMX_ST_FAIL;
	}

	for (i=0; i<numOfNSPs; i++)
	{		
		status = L4db_GetProvisionedNsp(pNSPids[i], &provisionedNsp);

		if (status == WMX_ST_OK)
		{
			TRACE(TR_MOD_APDO_AGENT, TR_SEV_DEBUG, "GetNSPContactInfoByName current name %s", 
				provisionedNsp.nwParams.provisionedName);
			TRACE(TR_MOD_APDO_AGENT, TR_SEV_DEBUG, "GetNSPContactInfoByName wanted name %s", nspName);

			// check if the requested nspName is one of the provisioned NSPs
			if (OSAL_stricmp(nspName, provisionedNsp.nwParams.provisionedName) == 0)
			{
				status = GetContactInfo(pNSPids[i], buffer, bufferSize);
				found = TRUE;
				break;
			}
		}		
	}

	if (!found)
	{
		TRACE(TR_MOD_APDO_AGENT, TR_SEV_DEBUG, "GetNSPContactInfoByName Failed to find nsp %s", nspName);
		status = WMX_ST_FAIL;
	}

	TRACE(TR_MOD_APDO_AGENT, TR_SEV_DEBUG, "GetNSPContactInfoByName [OUT]");
	return status; 
}

wmx_Status_t GetContactInfo(wmx_NSPid_t nspId, void *buffer, UINT32 *bufferSize)
{
	ProvisionedNsp_t provisionedNsp;
	wmx_ContactInformation_t contactInformation[WMX_URI_MAX_NUM];
	UINT32 resultSize;
	wmx_Status_t st;
	UINT32 i;
	TRACE(TR_MOD_APDO_AGENT, TR_SEV_DEBUG, "GetContactInfo [IN]");

	if (nspId != (wmx_NSPid_t)L4DB_INVALID_INDEX )
	{
		st = L4db_GetProvisionedNsp(nspId, &provisionedNsp);
		if (st != WMX_ST_OK || provisionedNsp.contactsSize <= 0)
		{
			return WMX_ST_DATA_UNAVAILABLE;
		}

		for (i = 0; i < provisionedNsp.contactsSize; i++)
		{
			OSAL_memcpy_s(contactInformation[i].text,  
					sizeof(contactInformation[i].text),
					provisionedNsp.contacts[i].text, sizeof(provisionedNsp.contacts[i].text));

			TRACE(TR_MOD_APDO_AGENT, TR_SEV_DEBUG, "GetContactInfo text[%d]=%s", i, contactInformation[i].text);
			OSAL_memcpy_s(contactInformation[i].uri,  
					sizeof(contactInformation[i].uri),
					provisionedNsp.contacts[i].uri, sizeof(provisionedNsp.contacts[i].uri));

			TRACE(TR_MOD_APDO_AGENT, TR_SEV_DEBUG, "GetContactInfo uri[%d]=%s", i, contactInformation[i].uri);
			contactInformation[i].uriType = provisionedNsp.contacts[i].uriType;
			TRACE(TR_MOD_APDO_AGENT, TR_SEV_DEBUG, "GetContactInfo uri type =[%d]", contactInformation[i].uriType);
		}

		// Get the minimum size
		resultSize = (*bufferSize <= provisionedNsp.contactsSize * sizeof(wmx_ContactInformation_t) ?
			*bufferSize : provisionedNsp.contactsSize * sizeof(wmx_ContactInformation_t));

		OSAL_memcpy_s(buffer, *bufferSize, (wmx_pContactInformation_t)contactInformation, resultSize);

		*bufferSize = resultSize;
	}
	else
	{
		return WMX_ST_WRONG_ARGUMENT;
	}

	TRACE(TR_MOD_APDO_AGENT, TR_SEV_DEBUG, "GetContactInfo [OUT]");
	return WMX_ST_OK;
}

//wmx_Status_t DeprovisionNSP(wmx_NSPid_t nspId)
//{	
//	wmx_NSPFullData_t nsp;
//	wmx_Status_t status;
//
//	L4db_DeProvisionNsp(
//	status = NdsDB_GetNSP( nspId, &nsp);
//	
//	if (status != WMX_ST_OK)
//	{
//		return status;
//	}
//
//	// Call the function that deletes the all the provisioned data of the given NSP
//	return NdsDB_DeProvisionNSP(nsp.serverId);	
//}

wmx_Status_t RestoreBckProvisioningDB()
{		
	wmx_Status_t status = WMX_ST_OK;

	// If we are in state different then RF-OFF return fail
	if (g_ndnsContext.systemState != RfOff)
	{
		TRACE(TR_MOD_APDO_AGENT, TR_SEV_NOTICE, "RestoreBckProvisioningDB - Restore not possible when system state=[%d].", g_ndnsContext.systemState);
		return WMX_ST_FAIL;
	}

	// Call the ND&S DB to restore the backup DB
	L4db_RestoreFromDefaults();
	
	return status;
}

wmx_Status_t RestoreFactorySettings()
{		
	wmx_Status_t status = WMX_ST_OK;
	CHAR readFromNVM[MAX_ANSWER_SIZE];
	// If we are in state different then RF-OFF return fail
	if (g_ndnsContext.systemState != RfOff)
	{
		TRACE(TR_MOD_APDO_AGENT, TR_SEV_NOTICE, "RestoreFactorySettings - Restore not possible when system state=[%d].", g_ndnsContext.systemState);
		return WMX_ST_FAIL;
	}

	// Call the ND&S DB to restore factory settings
	status = L4db_RestoreFromDefaults();

	if (status == WMX_ST_OK)
	{
		// Also send notification to OMA client to delete DM account 
		// MZUR - TODO add function to get active nsp dm account name
		NDnSAgent_ApdoDeleteDMAccountInd("./DMAcc/xohm");
		NDnSAgent_ApdoDeleteDMAccountInd("./DMAcc/uqc");


		// Reset the current preferred NSP to NULL
		L4db_SetCurrentPreferredNsp((wmx_NSPid_t)L4DB_INVALID_INDEX);
	}

	ClearAvailableNSPsList();
	
	// Update the package version in L4DB
	L4db_UpdatePackageVersion();

	///Nardimon resotre
	// If registry key is set to true update L4db from NVM 
	L4Configurations_getAPDOReadFromNvm(readFromNVM);

	if (0 == OSAL_stricmp(DEFAULT_TRUE_LOWER, readFromNVM))
	{		
		L4db_UpdateFromNVM();  
	}		

	return status;
}

// bufferSize is IN/OUT parameter for the size of the NSPs buffer. The param is initiated with the buffer allocated size.
// pNSP is a pointer to the first wmx_NSP_t struct, the rest come continuously after
wmx_Status_t GetUnprovisionedNspIDs(UINT32 *bufferSize, wmx_pNSPid_t pNspIDs)
{		
	UINT32 elementSize = sizeof(wmx_NSPid_t);
	UINT32 numElements = *bufferSize / elementSize;
	Profile_t profiles[MAX_NUM_OF_RECENT_NSPS];
	wmx_Status_t status = WMX_ST_WRONG_ARGUMENT;
	UINT32 i;

	if (*bufferSize % elementSize == 0)
	{		
		// Call the function that fetches the value from the local DB
		status =  L4db_GetUnprovisionedProfilesList((pProfile_t)profiles, &numElements);

		if (status == WMX_ST_OK)
		{
			for (i=0; i < numElements; i++)
			{
				pNspIDs[i] = profiles[i].nspID;
			}

			*bufferSize = numElements * elementSize;
		}		
	}

	return status;
}

// bufferSize is IN/OUT parameter for the size of the NSPs buffer. The param is initiated with the buffer allocated size.
// pNSP is a pointer to the first wmx_NSP_t struct, the rest come continuously after
wmx_Status_t GetProvisionedNspIDs(UINT32 *bufferSize, wmx_pNSPid_t pNspIDs)
{		
	UINT32 elementSize = sizeof(wmx_NSPid_t);
	UINT32 numElements = *bufferSize / elementSize;
	wmx_Status_t status = WMX_ST_WRONG_ARGUMENT;

	if (Ndns_GetProvisioningStarted() == TRUE)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Failed GetProvisionedNspIDs - called during provisioning");
		return WMX_ST_FAIL;
	}

	if (*bufferSize % elementSize == 0)
	{		
		// Call the function that fetches the value from the local DB
		status =  L4db_GetProvisionedNspIds(pNspIDs, &numElements);
		*bufferSize = numElements * elementSize;
	}

	return status;
}

wmx_Status_t GetProvisioningClientCfgDataBlob()
{
	return WMX_ST_OK;
}

void HandleApdoSessionStatus(wmx_ApdoSessionStatus_t sessionStatus)
{
	char path[MAX_REGISTRY_ANSWER];
	wmx_ProvisioningOperation_t provisioningOperation = poUpdateStarted;
	BOOL raiseInd = FALSE;
	wmx_Status_t monitorStatus;
	
	wmx_PopulateOMASessionMonitor(sessionStatus);
	switch (sessionStatus)
	{
	case 	SessionWaitingForBootstrap:
		provisioningOperation = poUpdateWaitingForBootstrap;
		raiseInd = TRUE;
		break;
	case 	SessionBootstrapArrived:	
		provisioningOperation = poUpdateBootstrapArrived;
		//OferF - We don't need to send raise indication when bootstrap arrives
		//raiseInd = TRUE;
		break;
	case 	SessionEndSuccess:
		if (TRUE == Ndns_GetProvisioningStarted())
		{
			provisioningOperation = poUpdateCompleted;
			raiseInd = TRUE;

			// Update db after provisioning
			if (RunWithDSim == TRUE)
			{
				OSAL_BuildFullPath(NDNS_DSIM_ENC_CONFIG_FILE, path, MAX_REGISTRY_ANSWER);
				//NDnSAgent_BuildFullPathW(NDNS_DSIM_CONFIG_FILE, path, MAX_REGISTRY_ANSWER);			
			} 
			else
			{
				OSAL_BuildFullPath(WiMAX_ENC_DB, path, MAX_REGISTRY_ANSWER);
				//NDnSAgent_BuildFullPathW(WiMAX_DB, path, MAX_REGISTRY_ANSWER);			
			}
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "call L4db_SaveToFile from HandleApdoSessionStatus");
			L4db_SaveToFile(path);

			Ndns_SetProvisioningStarted(FALSE);
		}
		break;
	case 	SessionEndFailure:
		if (TRUE == Ndns_GetProvisioningStarted())
		{
			provisioningOperation = poUpdateFailed;
			raiseInd = TRUE;
			Ndns_SetProvisioningStarted(FALSE);
		}
		break;
	case 	SessionUpdateFailedNetworkDisconnect:
		if (TRUE == Ndns_GetProvisioningStarted())
		{
			provisioningOperation = poUpdateFailedNetworkDisconnect;
			raiseInd = TRUE;
			Ndns_SetProvisioningStarted(FALSE);
		}
		break;
	case 	SessionUpdateFailedBadAuthentication:
		if (TRUE == Ndns_GetProvisioningStarted())
		{
			provisioningOperation = poUpdateFailedBadAuthentication;
			raiseInd = TRUE;
			Ndns_SetProvisioningStarted(FALSE);
		}
		break;
	}					

	if (raiseInd == TRUE)
	{
		NDnSAgent_ProvisioningOperation(provisioningOperation, 0);
		if (poUpdateCompleted == provisioningOperation)
		{
			monitorStatus = wmx_PopulateMonitorOperator();
		}
	}
}

void HandleFumoUpdate(wmx_FUMOUpdateContent_t fumoUpdateContent)
{
	wmx_PackageDownloadProgressInfo_t packageUpdateInfo;
	packageUpdateInfo.downloadedBytes = fumoUpdateContent.downloadedBytes;
	packageUpdateInfo.totalBytes = fumoUpdateContent.totalBytes;
	NDnSAgent_PackageDownloadProgress(packageUpdateInfo);
}

// Check if a new provisioning session has started, if so inform the user.
void CheckIfProvisioningStarted()
{
	BOOL provisioningStarted = Ndns_GetProvisioningStarted();
	Ndns_SetProvisioningStarted(TRUE);

	// Inform the user that the provisioning has started
	if (provisioningStarted == FALSE)
	{
		NDnSAgent_ProvisioningOperation(poUpdateStarted, 0);
	}
}

void HandleAPDOFailure(wmx_Status_t status)
{
	// Inform the user about the provisioning failure only if provisioning has started and status wasn't OK.
	if ((provisioningStarted == TRUE) && (status != WMX_ST_OK))
	{
		NDnSAgent_ProvisioningOperation(poUpdateFailedInvalidProvisioning, 0);
		Ndns_SetProvisioningStarted(FALSE);
	}
}

wmx_Status_t SetServiceProviderUnlock(void *buffer, UINT32 bufferSize)
{
	wmx_Status_t retStatus;
	wmx_SpLockCode_t spLockCode;

	OSAL_memcpy_s(spLockCode.BufferArr, MAX_SP_LOCK_CODE_SIZE, buffer, bufferSize);
	spLockCode.ActualLen = (UINT16)bufferSize;

	retStatus = wmx_CmdSpLockUnLock(spLockCode);

	return retStatus;		
}

wmx_Status_t GetServiceProviderLockStatus(void *buffer, UINT32 *bufferSize)
{
	wmx_Status_t st;
	wmx_SpLock_t spLock;

	memset(&spLock, 0, sizeof(wmx_SpLock_t));

	if (*bufferSize >= sizeof(wmx_SpLock_t))
	{
		st = wmx_GetSpLockStatus(&spLock);

		if (st != WMX_ST_OK)
		{
			return st;
		}

		*(wmx_pSpLock_t)buffer = spLock;

		return WMX_ST_OK;
	}

	return WMX_ST_FAIL;
}

wmx_Status_t GetBEK(wmx_pBEKBuffer_t pBEK)
{	
	wmx_Status_t status;	

	// Call the function that fetches the value from the local DB
	status = L4db_GetBEK( pBEK );

	return status;
}

wmx_Status_t SetBEK(wmx_pBEKBuffer_t pBEK)
{	
	wmx_Status_t status;	

	// Call the function that fetches the value from the local DB
	status = L4db_SetBEK( pBEK );

	return status;
}
wmx_Status_t GetApdoLinkStatus(void *buffer, UINT32 *resultBufferSize, void *resultBuffer)
{
	wmx_pApdoLinkStatusParams_t pApdoLinkParams;
	wmx_Status_t st = WMX_ST_OK;
	wmx_NSP_t nspInfo;
	ProvisionedNsp_t nsp;
	char realmFromDHCP[WMX_NSP_REALM_MAX_SIZE];

	realmFromDHCP[0] = '\0';

	UNREFERENCED_PARAMETER(buffer);
	TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "GetApdoLinkStatus [IN]");
	if (sizeof(wmx_ApdoLinkStatusParams_t)>*resultBufferSize)
	{
		TRACE(TR_MOD_APDO_AGENT, TR_SEV_DEBUG, "GetApdoLinkStatus - returns fail. bad buffer");
		return WMX_ST_FAIL;
	}

	pApdoLinkParams = (wmx_pApdoLinkStatusParams_t)resultBuffer;

	pApdoLinkParams->nspId = 0;
	pApdoLinkParams->realm[0] = '\0';
	pApdoLinkParams->nspName[0] = '\0';
	pApdoLinkParams->toDMAcc[0] = '\0';

	if (FSM_GetState(&g_ndnsContext.fsm) == L4C_CONNECTED)
	{
		pApdoLinkParams->linkStatus = APDO_linkUp;
	}
	else
	{
		pApdoLinkParams->linkStatus = APDO_linkDown;
	}

	// If link is up update other parameters
	if (pApdoLinkParams->linkStatus == APDO_linkUp)
	{
		TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "GetApdoLinkStatus : Trying L4db_GetRecentNsp...");
		st = L4db_GetRecentNsp(&pApdoLinkParams->nspId);	
		
		if (st == WMX_ST_OK)
		{

			TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "GetApdoLinkStatus : L4db_GetRecentNsp returned WMX_ST_OK");
			st = L4db_GetProvisionedNsp(pApdoLinkParams->nspId, &nsp);

			if (st == WMX_ST_OK)
			{
				OSAL_strcpy_s(pApdoLinkParams->nspName, WMX_NSP_NAME_MAX_SIZE, nsp.tagName);	
				L4db_GetToDMAccByTagName(nsp.tagName, pApdoLinkParams->toDMAcc);
			}
			else
			{
				pApdoLinkParams->toDMAcc[0] ='\0';
			}	
		}
		else
		{
			TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "GetApdoLinkStatus : L4db_GetRecentNsp returned != WMX_ST_OK.");
			pApdoLinkParams->toDMAcc[0] ='\0';
		}
		st = GetHostName(realmFromDHCP, WMX_NSP_REALM_MAX_SIZE);

		if (st != WMX_ST_OK)
		{
			// Get realm
			st = GetNspInfo(pApdoLinkParams->nspId, &nspInfo);

			if (st == WMX_ST_OK)
			{
				TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "GetHostName != WMX_ST_OK. Using Option Pre provisioned realm if exists realm.");
				OSAL_strcpy_s(pApdoLinkParams->realm, WMX_NSP_REALM_MAX_SIZE, nspInfo.nspRealm);	
			}
		}
		else
		{
			if (realmFromDHCP[0] == '\0')
			{
				TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "GetHostName returned empty string. Using Option Pre provisioned realm if exists realm.");
				TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "Trying GetNspInfo...");
				// Get realm
				st = GetNspInfo(pApdoLinkParams->nspId, &nspInfo);

				if (st == WMX_ST_OK)
				{
					TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "GetNspInfo returned WMX_ST_OK");
					TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "GetHostName != WMX_ST_OK. Using Option Pre provisioned realm if exists realm.");
					OSAL_strcpy_s(pApdoLinkParams->realm, WMX_NSP_REALM_MAX_SIZE, nspInfo.nspRealm);	
				}
				else
				{
					TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "GetNspInfo != WMX_ST_OK. Will not be able to connect...");
				}
			}
			else
			{
				realmFromDHCP[WMX_NSP_REALM_MAX_SIZE-1]='\0';
				TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "GetHostName - returns WMX_ST_OK. Using Option 15 realm. ");
				OSAL_strcpy_s(pApdoLinkParams->realm, WMX_NSP_REALM_MAX_SIZE, realmFromDHCP);					
			}
		}
	}	
	TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "GetApdoLinkStatus [OUT]");
	return st;
}
wmx_Status_t GetApdoOperatorsConfigurations(wmx_pApdoOperatorConfigurations_t pConfigurations)
{	
	wmx_Status_t status;	

	// Call the function that fetches the value from the local DB
	status = L4db_GetApdoOperatorsConfigurations( pConfigurations );

	return status;
}

wmx_Status_t GetConnectedNSPForAPDO(UINT32 *bufferLength, UINT8 *buffer)
{	
	return NDnSAgent_GetConnectedNSPEx(bufferLength, buffer, FALSE);
}
