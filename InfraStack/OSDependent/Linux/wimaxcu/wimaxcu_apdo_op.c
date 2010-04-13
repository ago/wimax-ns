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

#include "wimaxcu.h"
#include "wimaxcu_util.h"

void *user_info(void *ptr)
{
	int ch = 0;
	printf("%s \n", (char *)ptr);
	while (ch != 'q' && ch != 'Q')
		ch = getc(stdin);

	sem_post(&g_semAPDOactivation);
	return (void *)0;
}

WIMAX_API_RET register_apdo_cb(WIMAX_API_DEVICE_ID_P p_device_id)
{
	return SubscribeProvisioningOperation(p_device_id,
					      &ind_provisioning_operation_cb);
}

WIMAX_API_RET unregister_apdo_cb(WIMAX_API_DEVICE_ID_P p_device_id)
{
	return UnsubscribeProvisioningOperation(p_device_id);
}

WIMAX_API_RET register_puma_cb(WIMAX_API_DEVICE_ID_P p_device_id)
{
	return SubscribePackageUpdate(p_device_id, &ind_package_update_cb);
}

WIMAX_API_RET unregister_puma_cb(WIMAX_API_DEVICE_ID_P p_device_id)
{
	return UnsubscribePackageUpdate(p_device_id);
}

void ind_provisioning_operation_cb(WIMAX_API_DEVICE_ID_P p_device_id,
				   WIMAX_API_PROV_OPERATION
				   provisoningOperation,
				   WIMAX_API_CONTACT_TYPE contactType)
{
	WIMAX_API_RET wmxStatus = WIMAX_API_RET_SUCCESS;
	int cmd = 0;
	int flag = 0;
	WIMAX_API_CONTACT_INFO_P ContactInfo = NULL;
	UINT32 SizeOfContactList = MAX_PROFILE;
	char browserurl[MAX_SIZE_OF_STRING_BUFFER+MAX_SIZE_OF_STRING_BUFFER] = {0};

	switch (provisoningOperation) {
	case WIMAX_API_PROV_OPERATION_CFG_UPDATE_STARTED:
		printf("Provisioning Update Started...\n");
		break;
	case WIMAX_API_PROV_OPERATION_CFG_UPDATE_COMPLETED:
		printf("Provisioning Update Completed.\n");
		// set the event to exit the application
		sem_post(&g_semAPDOactivation);
		break;
	case WIMAX_API_PROV_OPERATION_CFG_UPDATE_FAILED_NETWORK_DISCONNECT:
		printf
		    ("WARNING: Provisioning Update - Network Disconnected. \n");
		// set the event to exit the application
		sem_post(&g_semAPDOactivation);
		break;
	case WIMAX_API_PROV_OPERATION_CFG_UPDATE_FAILED:
		printf("WARNING: Provisioning  Update unsuccessfull.\n");
		// set the event to exit the application
		sem_post(&g_semAPDOactivation);
		break;
	case WIMAX_API_PROV_OPERATION_CFG_UPDATE_FAILED_INVALID_PROVISIONING:
		printf("WARNING: Provisioning Update - Invalid Provisioning\n");
		// set the event to exit the application
		sem_post(&g_semAPDOactivation);
		break;
	case WIMAX_API_PROV_OPERATION_CFG_UPDATE_FAILED_BAD_AUTHENTICATION:
		printf("WARNING: Provisioning Update - Bad Authentication\n");
		// set the event to exit the application
		sem_post(&g_semAPDOactivation);
		break;
	case WIMAX_API_PROV_OPERATION_CFG_UPDATE_REQUEST_INITIAL_PROVISIONING:
		//printf("Initial provisioning\n");
		printf
		    ("The Network is attempting to update the WiMAX connection settings.\
			   These settings are critical for the proper operation of WiMAX.\n \
			   Update the WiMAX connection settings now [Y/N]:?");
		cmd = getchar();
		if (cmd == 'y' || cmd == 'Y') {
			wmxStatus =
			    SetPackageUpdateState(p_device_id,
						  WIMAX_API_PACKAGE_UPDATE_ACCEPTED);
			if (wmxStatus != WIMAX_API_RET_SUCCESS) {
				PrintWmxStatus(wmxStatus);
				sem_post(&g_semAPDOactivation);
			}
		} else {
			wmxStatus =
			    SetPackageUpdateState(p_device_id,
						  WIMAX_API_PACKAGE_UPDATE_DELAY);
			if (wmxStatus != WIMAX_API_RET_SUCCESS) {
				PrintWmxStatus(wmxStatus);
			}
			sem_post(&g_semAPDOactivation);
		}
		break;
	case WIMAX_API_PROV_OPERATION_CFG_UPDATE_REQUEST_ONGOING_PROVISIONING:
		printf("Ongoing Provisioning\n");
		/*
		   cmd = system("firefox www.intel.com");
		   printf("The network is attempting to update the WiMAX connection settings.\
		   These settings are critical for the proper operation of WiMAX.\n     \
		   \r\n\r\nUpdate the WiMAX connection settings now y/n?");
		   cmd = getchar();
		   if  (cmd == 'y' || cmd == 'Y')
		   {
		   wmxStatus = SetPackageUpdateState(p_device_id,WIMAX_API_PACKAGE_UPDATE_ACCEPTED);
		   if ( wmxStatus != WIMAX_API_RET_SUCCESS )
		   {
		   PrintWmxStatus(wmxStatus);
		   }
		   }
		   else
		   {
		   wmxStatus = SetPackageUpdateState(p_device_id,WIMAX_API_PACKAGE_UPDATE_DELAY);
		   if ( wmxStatus != WIMAX_API_RET_SUCCESS )
		   {
		   PrintWmxStatus(wmxStatus);
		   }
		   }
		 */
		break;
	case WIMAX_API_PROV_OPERATION_CFG_UPDATE_TRIGGER_CONTACT:
		ContactInfo =
		    (WIMAX_API_CONTACT_INFO_P)
		    malloc(sizeof(WIMAX_API_CONTACT_INFO) * MAX_PROFILE);
		wmxStatus =
		    GetContactInformation(p_device_id, g_sznspName, ContactInfo,
					  &SizeOfContactList);
		if (wmxStatus != WIMAX_API_RET_SUCCESS) {
			printf
			    ("WARNING: Unable to Retrive the Contact Information\n");
		} else {
			for (cmd = 0; cmd < SizeOfContactList; cmd++) {
				if (contactType == ContactInfo[cmd].contactType) {
					// TODO:: find the the browser launch idea for all OS ie midinux, Ubunto etc.,
					printf("Launching the URL %s ...\n",
					       ContactInfo[cmd].URI);
					sprintf(browserurl,"firefox %s",ContactInfo[cmd].URI);
					cmd = system(browserurl);
					flag = 1;
					break;
				}
			}
		}
		free(ContactInfo);
		if (flag == 0)
			printf("WARNING: Unable to to connect to the URL\n");
		sem_post(&g_semAPDOactivation);

		break;
	case WIMAX_API_PROV_OPERATION_CFG_UPDATE_REQUEST_RESET_PROVISIONING:
		printf
		    ("WARNING: Provisioning Update - request to Reset the Provisioning\n");
		break;
	default:
		sem_post(&g_semAPDOactivation);
		break;
	}
}

void ind_package_update_cb(WIMAX_API_DEVICE_ID_P p_device_id,
			   WIMAX_API_PACK_UPDATE packageUpdate)
{
	char consent;
	WIMAX_API_RET wmxStatus;
	//WIMAX_API_PACKAGE_INFO_P pPackageINFO;
	WIMAX_API_PACKAGE_INFO packageINFO;
	//char pathName[PATH_MAX]={0};
	//char packageName[NAME_MAX]={0};
	//char execute [PATH_MAX + NAME_MAX]={0};
	switch (packageUpdate) {
	case WIMAX_API_PACK_UPDATE_RECEIVED:
		printf("Package Update - Received \n");
		/*printf("Request to download notification received.\n");
		   wmxStatus = SetPackageUpdateState(p_device_id,WIMAX_API_PACKAGE_UPDATE_ACCEPTED);
		   if ( wmxStatus != WIMAX_API_RET_SUCCESS )
		   {
		   PrintWmxStatus(wmxStatus);
		   } */
		break;
	case WIMAX_API_PACK_UPDATE_RECEIVED_LOWER_STACK:
		printf("Package Update - Firmware update Received\n");
		break;
	case WIMAX_API_PACK_UPDATE_RECEIVED_FULL_STACK:
		printf
		    ("Package Update - Firmware, SDK and driver updates Received.\n");
		break;

	case WIMAX_API_PACK_UPDATE_RECEIVED_OMA_DM_CLIENT:
		printf("Package Update - OMA-DM client update Received.\n");
		break;

	case WIMAX_API_PACK_UPDATE_STARTED:
		wmxStatus = GetPackageInformation(p_device_id, &packageINFO);
		if (wmxStatus != WIMAX_API_RET_SUCCESS) {
			PrintWmxStatus(wmxStatus);
		}
		if ((strcmp(g_foOperationType, SW_UPGRADE_TYPE_DOWNLOAD) == 0)
		    || (strcmp(g_foOperationType, SW_UPGRADE_TYPE_UPDATE) ==
			0)) {
			printf
			    ("Request to install %s downloaded package [Y/N]:",
			     packageINFO.fileName);
			scanf("%c", &consent);
			if ((consent == 'Y') || (consent == 'y')) {
				strcat(packageINFO.filePath, "/");

#if 0				// TODO :: IMPORTANT - to be removed
				wmxStatus =
				    InstallAPDOUpdate(p_device_id,
						      packageINFO.filePath,
						      packageINFO.fileName);

				if (wmxStatus != WIMAX_API_RET_SUCCESS) {
					PrintWmxStatus(wmxStatus);
				}
				//printf("%s\n %s",packageINFO.filePath,packageINFO.fileName);

#endif
				sem_post(&g_semAPDOupdates);
			} else if ((consent == 'N') || (consent == 'n')) {

				sem_post(&g_semAPDOupdates);
			}
		} else
		    if (strcmp
			(g_foOperationType,
			 SW_UPGRADE_TYPE_DOWNLOAD_AND_UPDATE) == 0) {
			printf("%s downloaded package will be installed ",
			       packageINFO.fileName);
			strcat(packageINFO.filePath, "/");

#if 0
			wmxStatus =
			    InstallAPDOUpdate(p_device_id, packageINFO.filePath,
					      packageINFO.fileName);
			if (wmxStatus != WIMAX_API_RET_SUCCESS) {
				PrintWmxStatus(wmxStatus);
			}
#endif
			sem_post(&g_semAPDOupdates);
		}

		break;/**< Request to install package */
	case WIMAX_API_PACK_UPDATE_COMPLETED:
		printf("Package Update - Successfully Installed.\n");
		sem_post(&g_semAPDOupdates);
		break;

	case WIMAX_API_PACK_UPDATE_FAILED_NETWORK_DISCONNECTED:
		printf
		    ("WARNING: Package Update - Failed to Install - Network Disconnected.\n");
		break;
	case WIMAX_API_PACK_UPDATE_FAILED_INVALID_PACKAGE:
		printf
		    ("WARNING: Package Update - Failed to Install - Invalid Package.\n");
		sem_post(&g_semAPDOupdates);
		break;
	case WIMAX_API_PACK_UPDATE_FAILED_BAD_AUTHENTICATION:
		printf
		    ("WARNING: Package Update - Failed to Install - Bad Authentication.\n");
		sem_post(&g_semAPDOupdates);
		break;
	case WIMAX_API_PACK_UPDATE_FAILED:
		printf("Package Update - Failed to Install.\n");
		break;
		sem_post(&g_semAPDOupdates);
	}
}

void restore_pro_db(WIMAX_API_DEVICE_ID_P p_device_id)
{
	WIMAX_API_RET wmxStatus = WIMAX_API_RET_SUCCESS;
	wmxStatus = CmdRestoreBackupProvisioningDatabase(p_device_id);
	if (wmxStatus != WIMAX_API_RET_SUCCESS) {
		PrintWmxStatus(wmxStatus);
	}

}

/*
 * Function:     ServiceProviderUnlock
 * Description:  Unlock the device
 * Return:       0 for success or 1 for failure, 2 for misc failure
 */
int wimaxcu_service_provider_unlock(WIMAX_API_DEVICE_ID_P p_device_id,
				    char *unlockcode)
{
	WIMAX_API_RET wmxStatus = WIMAX_API_RET_SUCCESS;
	WIMAX_API_LOCK_STATUS LockStatus = WIMAX_API_DEVICE_UNLOCKED;
	char NSPName[MAX_SIZE_OF_NSP_NAME];

	int length = strlen(unlockcode);
	if (length <= 0) {
		printf("Unlock code is empty\n");
		return 1;
	}

	wmxStatus =
	    GetServiceProviderLockStatus(p_device_id, &LockStatus, NSPName);
	if (wmxStatus == WIMAX_API_RET_SUCCESS) {
		if (LockStatus != WIMAX_API_DEVICE_LOCKED) {
			printf("Device is not locked \n");
			return 1;
		}
	} else {
		PrintWmxStatus(wmxStatus);
		return 2;
	}

	// First check the serviceprovider locked or not
	// wchar_t *wUnlockcode = NULL;
	// wUnlockcode = (wchar_t *)malloc( (length + 1) * sizeof( wchar_t ));
	/*
	   if (! wUnlockcode)
	   {
	   printf("Memory allocation failure. in Serivceproviderunlock function\n");
	   return;
	   }

	   if  ( mbstowcs(wUnlockcode,unlockcode,length+1)== -1 )
	   {
	   printf("unable to convert sevice unlock code string to wide character\n");
	   free(wUnlockcode) ;
	   return ;
	   } */
	wmxStatus = SetServiceProviderUnLock(p_device_id, unlockcode);
	if (wmxStatus != WIMAX_API_RET_SUCCESS) {
		PrintWmxStatus(wmxStatus);
		return 1;
	}
	// free(wUnlockcode);
	return 0;
}

/*
 * Function:     installAPDOUpdates
 * Description:  Install available package
 * Return:       0 for success or 1 for failure
 */
int wimaxcu_install_apdo_updates(WIMAX_API_DEVICE_ID_P p_device_id)
{
	char consent = { 0 };
	char retbuffer[NAME_MAX] = { 0 };
	WIMAX_API_RET wmxStatus;

	WIMAX_API_DEVICE_STATUS DeviceStatus;
	WIMAX_API_CONNECTION_PROGRESS_INFO ConnectionProgressInfo;

	//Check to see if HW or SW radio is turned off
	wmxStatus =
	    GetDeviceStatus(p_device_id, &DeviceStatus,
			    &ConnectionProgressInfo);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		PrintWmxStatus(wmxStatus);
		return 1;
	}

	if (DeviceStatus == WIMAX_API_DEVICE_STATUS_RF_OFF_SW) {
		printf("WARNING: SW Radio is turned OFF\n");
		return 1;
	} else if (DeviceStatus == WIMAX_API_DEVICE_STATUS_RF_OFF_HW_SW) {
		printf("WARNING: HW and SW Radios are turned OFF\n ");
		return 1;
	} else if (DeviceStatus == WIMAX_API_DEVICE_STATUS_RF_OFF_HW) {
		printf("WARNING: HW Radio is turned OFF\n");
		return 1;
	} else {

#if 0				// TODO :: IMPORTANT -- to be removed (no FUMO functionality)
		wmxStatus = APDOupdates(p_device_id, retbuffer, NAME_MAX);
#endif
		register_puma_cb(p_device_id);
		if (retbuffer[0] != 0) {
			strcpy(g_foOperationType, retbuffer);
		}

		if (strcmp
		    (g_foOperationType,
		     SW_UPGRADE_TYPE_DOWNLOAD_AND_UPDATE) == 0)
			printf
			    ("\nPackages are available for Download and Install [Y/N]:");

		else if (strcmp(g_foOperationType, SW_UPGRADE_TYPE_DOWNLOAD) ==
			 0)
			printf("\nPackages are available for Download [Y/N]:");
		else if (strcmp(g_foOperationType, SW_UPGRADE_TYPE_UPDATE) == 0)
			printf("\nPackages are available to Install [Y/N]:");
		else {
			printf("No APDO updates are available at this time.\n");
			return 1;
		}

		scanf("%c", &consent);
		if ((consent == 'Y') || (consent == 'y')) {
			if (sem_init(&g_semAPDOupdates, 0, 0) == -1) {
				printf("ERROR: Internal failure\n");
				return 1;
			}

			wmxStatus =
			    SetPackageUpdateState(p_device_id,
						  WIMAX_API_PACKAGE_UPDATE_ACCEPTED);
			if (wmxStatus != WIMAX_API_RET_SUCCESS) {
				PrintWmxStatus(wmxStatus);
			}
			sem_wait(&g_semAPDOupdates);

		}
		if ((consent == 'N') || (consent == 'n')) {
			wmxStatus =
			    SetPackageUpdateState(p_device_id,
						  WIMAX_API_PACKAGE_UPDATE_DENIED);
			if (wmxStatus != WIMAX_API_RET_SUCCESS) {
				PrintWmxStatus(wmxStatus);
			}
		}

		wmxStatus = unregister_puma_cb(p_device_id);
		if (WIMAX_API_RET_SUCCESS != wmxStatus) {
			PrintWmxStatus(wmxStatus);
		}
	}

	return 0;
}

void wimaxcu_check_for_apdo_updates(WIMAX_API_DEVICE_ID_P p_device_id)
{
	char retbuffer[NAME_MAX];

	WIMAX_API_RET wmxStatus;
#if 0
	wmxStatus = APDOupdates(p_device_id, retbuffer, NAME_MAX);
#endif
	if (wmxStatus == WIMAX_API_RET_SUCCESS) {
		if (retbuffer[0] != 0)
			printf
			    ("\nAPDO Updates are Available. Please run \"wimaxcu update\"\n\n");
	}

}

/*
 * Function:     GetProvStatus
 * Description:  Retrive the provisioning status
 * Return:       0 for success,
                 1 for general command failure, or
                 2 for non-command related failure
 */
int wimaxcu_get_prov_status(WIMAX_API_DEVICE_ID_P p_device_id, char *str_nspid)
{
	WIMAX_API_RET wmxStatus = WIMAX_API_RET_SUCCESS;
	WIMAX_API_NSP_INFO_P pNspInfo = NULL;
	UINT32 numOfNSPs = MAX_DEVICE;
	char tmp_nspID_str[MAX_NSP_ID_LEN];
	BOOL found_nsp = FALSE;
	BOOL provStatus = FALSE;
	int i;

	pNspInfo =
	    (WIMAX_API_NSP_INFO_P) malloc(MAX_LEN * sizeof(WIMAX_API_NSP_INFO));
	if (pNspInfo == NULL) {
		printf("ERROR: Internal failure\n");
		return 2;
	}
	// find the nsp name from the given nsp id
	wmxStatus = GetNetworkList(p_device_id, pNspInfo, &numOfNSPs);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		printf("ERROR: Retriving the Network List was unsuccessfull");
		PrintWmxStatus(wmxStatus);
		free(pNspInfo);
		return 2;
	}

	if (numOfNSPs == 0) {
		printf
		    ("WARNING: Cannot find any available network.\nPlease run \"wimaxcu scan\" to update the Network List\n");
		free(pNspInfo);
		return 2;
	}

	for (i = 0; i < numOfNSPs; i++) {
		sprintf(tmp_nspID_str, "%ld", pNspInfo[i].NSPid);
		if (strcmp(tmp_nspID_str, str_nspid) == 0) {
			found_nsp = TRUE;
			break;
		}
	}

	if (found_nsp == FALSE) {
		printf
		    ("WARNING: Network ID (%s) is not in the current known list.\nVerify the Network ID or run \"wimaxcu scan\" to refresh the network list.\n",
		     str_nspid);
		free(pNspInfo);
		return 2;
	}

	wmxStatus =
	    GetProvisioningStatus(p_device_id, pNspInfo[i].NSPName,
				  &provStatus);
	if (wmxStatus != WIMAX_API_RET_SUCCESS) {
		printf
		    ("ERROR: Retriving Provisioning status was unsuccessfull\n");
		free(pNspInfo);
		return 1;
	} else {
		printf("Provision Status: %s(%s) is ", pNspInfo[i].NSPName,
		       str_nspid);
		if (provStatus == TRUE)
			printf("Provisioned.\n");
		else
			printf("Not Provisioned.\n");
	}
	free(pNspInfo);
	return 0;
}

/*
 * Function:     wimaxcu_get_sp_lock_status
 * Description:  Get the service provider's device lock status
 * Return:       0 for success or 1 for failure
 */
int wimaxcu_get_sp_lock_status(WIMAX_API_DEVICE_ID_P p_device_id)
{
	WIMAX_API_LOCK_STATUS LockStatus = WIMAX_API_DEVICE_UNLOCKED;
	WIMAX_API_RET wmxStatus = WIMAX_API_RET_SUCCESS;
	char NSPName[MAX_SIZE_OF_NSP_NAME];

	// Get the NSP Name from user
	wmxStatus =
	    GetServiceProviderLockStatus(p_device_id, &LockStatus, NSPName);
	if (wmxStatus == WIMAX_API_RET_SUCCESS) {
		if (LockStatus == WIMAX_API_DEVICE_LOCKED) {
			printf("Lock Status: Device is locked for %s Network\n",
			       NSPName);
		} else {
			printf("Lock Status: Device is unlocked.\n");
		}
	} else {
		PrintWmxStatus(wmxStatus);
		return 1;
	}
	return 0;
}
