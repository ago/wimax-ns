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

/*
 * Function:     GetUserConnectMode
 * Description:  Get the user connection mode
 * Return:       0 for success or 1 for failure
 */
int wimaxcu_get_user_connect_mode(WIMAX_API_DEVICE_ID_P p_device_id)
{
	WIMAX_API_CONNECTION_MODE connectMode;
	WIMAX_API_RET wmxStatus;

	wmxStatus = GetConnectionMode(p_device_id, &connectMode);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		PrintWmxStatus(wmxStatus);
		return 1;
	}

	PrintUserConnectionMode(connectMode);
	return 0;
}

/*
 * Function:     SetUserConnectMode
 * Description:  Change the user connect mode
 * Return:       0 for success or 1 for failure
 */
int wimaxcu_set_user_connect_mode(WIMAX_API_DEVICE_ID_P p_device_id,
		       char *connect_mode, char *scan_mode)
{
	int ret;
	WIMAX_API_RET wmxStatus;
	WIMAX_API_CONNECTION_MODE userConnectMode, currentConnectMode;
	WIMAX_API_DEVICE_STATUS DeviceStatus;
	WIMAX_API_CONNECTION_PROGRESS_INFO ConnectionProgressInfo;

	wmxStatus = GetConnectionMode(p_device_id, &currentConnectMode);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		PrintWmxStatus(wmxStatus);
		return 1;
	}

	userConnectMode = currentConnectMode;
	ret =
	    ConvertCharToConnectionMode(connect_mode, scan_mode,
					&userConnectMode);
	if (ret == -1) {
		printf("Specified Scan/Connect mode(s) not recognized.\n");
		PrintUserConnectionMode(currentConnectMode);
		return 1;
	} else if (ret == -2) {
		printf("WARNING: Invalid connect and scan combination.\n");
		printf("Auto connection requires semi scan mode.\n");
		PrintUserConnectionMode(currentConnectMode);
		return 1;
	}

	if (userConnectMode == currentConnectMode) {
		printf("The specified connect mode is already in place.\n");
		PrintUserConnectionMode(currentConnectMode);
		return 1;
	}
	if (ret == 1) {
		wmxStatus =
		    GetDeviceStatus(p_device_id, &DeviceStatus,
				    &ConnectionProgressInfo);
		if (WIMAX_API_RET_SUCCESS != wmxStatus) {
			PrintWmxStatus(wmxStatus);
			return 2;
		}
	}

	if((userConnectMode == WIMAX_API_CONNECTION_SEMI_MANUAL_SCAN_AUTO_CONNECT)&&((DeviceStatus==WIMAX_API_DEVICE_STATUS_RF_OFF_SW)||(DeviceStatus==WIMAX_API_DEVICE_STATUS_RF_OFF_HW)||(DeviceStatus==WIMAX_API_DEVICE_STATUS_RF_OFF_HW_SW))){
		printf("Error:Please turn the Radio On\n");
		return 1;
	}

	wmxStatus = SetConnectionMode(p_device_id, userConnectMode);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		// PrintWmxStatus(wmxStatus);
		if (WIMAX_API_RET_FAILED == wmxStatus) {
			BOOL isEnable;
			wmxStatus =
			    GetConnectedAsCurrentPreferredCapabilityStatus
			    (p_device_id, &isEnable);
			if (wmxStatus == WIMAX_API_RET_SUCCESS) {
				if (isEnable == FALSE) {
					printf
					    ("Current Connected Network Preferred settings are disabled\n");
					printf
					    ("Hence could not set the connect mode to Auto \n");
					printf
					    ("Going back to the pprevious connect mode \n");
					wmxStatus =
					    SetConnectionMode(p_device_id,
							      currentConnectMode);
					if (WIMAX_API_RET_SUCCESS != wmxStatus) {
						PrintWmxStatus(wmxStatus);
					} else {
						PrintUserConnectionMode
						    (currentConnectMode);
					}
					return 1;
				} else {
					printf("Operation Failed \n");
					return 1;
				}
			}
		}
		PrintWmxStatus(wmxStatus);
		return 1;
	}
	// Unset the preferred NSP
	if (userConnectMode == WIMAX_API_CONNECTION_MANUAL_SCAN_MANUAL_CONNECT) {
		g_preferred_NSP_ID = 0;
		SetCurrentPreferredProfiles(p_device_id, &g_preferred_NSP_ID, 0);
	}
	PrintUserConnectionMode(userConnectMode);
	
	return 0;
}

/*
 * Function:     wimaxcu_get_system_status
 * Description:  Get the WiMAX device status from the GetDeviceStatus API
 * Return:       0 for success or 1 for failure
 */
int wimaxcu_get_system_status(WIMAX_API_DEVICE_ID_P p_device_id)
{
	WIMAX_API_RET wmxStatus;
	WIMAX_API_DEVICE_STATUS DeviceStatus;
	WIMAX_API_CONNECTION_PROGRESS_INFO ConnectionProgressInfo;

	wmxStatus =
	    GetDeviceStatus(p_device_id, &DeviceStatus,
			    &ConnectionProgressInfo);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		PrintWmxStatus(wmxStatus);
		return 1;
	}

	PrintDeviceStatus(DeviceStatus);
	return 0;
}

/*
 * Function:     wimaxcu_get_connect_status
 * Description:  Get the current connection status of WiMAX Device
 * Return:       0 for success or 1 for failure
 */
int wimaxcu_get_connect_status(WIMAX_API_DEVICE_ID_P p_device_id)
{
	WIMAX_API_RET wmxStatus;
	WIMAX_API_DEVICE_STATUS DeviceStatus;
	WIMAX_API_CONNECTION_PROGRESS_INFO ConnectionProgressInfo;

	wmxStatus =
	    GetDeviceStatus(p_device_id, &DeviceStatus,
			    &ConnectionProgressInfo);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		PrintWmxStatus(wmxStatus);
		return 1;
	}

	PrintDeviceStatus(DeviceStatus);

	// if connected or idle, display connected NSP info
	if (DeviceStatus == WIMAX_API_DEVICE_STATUS_Data_Connected) {
		wimaxcu_get_conn_nsp(p_device_id);
		wimaxcu_get_conn_time(p_device_id);
	}

	return 0;
}

/*
 * Function:     wimaxcu_get_rf_status
 * Description:  Get WiMAX radio status
 * Return:       0 for success or 1 for failure
 */
int wimaxcu_get_rf_status(WIMAX_API_DEVICE_ID_P p_device_id)
{
	WIMAX_API_RET wmxStatus;
	WIMAX_API_DEVICE_STATUS DeviceStatus;
	WIMAX_API_CONNECTION_PROGRESS_INFO ConnectionProgressInfo;

	wmxStatus =
	    GetDeviceStatus(p_device_id, &DeviceStatus,
			    &ConnectionProgressInfo);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		PrintWmxStatus(wmxStatus);
		return 1;
	}

	printf("Radio Status: ");
	switch (DeviceStatus) {
	case WIMAX_API_DEVICE_STATUS_UnInitialized:
		printf("Device is not ready\n");
		break;
	case WIMAX_API_DEVICE_STATUS_RF_OFF_HW_SW:
		printf("HW and SW Radios are OFF\n");
		break;
	case WIMAX_API_DEVICE_STATUS_RF_OFF_HW:
		printf("HW radio is OFF\n");
		break;
	case WIMAX_API_DEVICE_STATUS_RF_OFF_SW:
		printf("SW radio is OFF\n");
		break;
	default:
		printf("HW and SW radios are ON\n");
	}
	return 0;
}

/*
 * Function:     wimaxcu_get_stats
 * Description:  Get statistics data
 * Return:       0 for success or 1 for failure
 */
int wimaxcu_get_stats(WIMAX_API_DEVICE_ID_P p_device_id)
{
	WIMAX_API_RET wmxStatus;
	WIMAX_API_CONNECTION_STAT Statistics;
	WIMAX_API_DEVICE_STATUS DeviceStatus;
	WIMAX_API_CONNECTION_PROGRESS_INFO ConnectionProgressInfo;

	wmxStatus =
	    GetDeviceStatus(p_device_id, &DeviceStatus,
			    &ConnectionProgressInfo);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		PrintWmxStatus(wmxStatus);
		return 1;
	}

	if (DeviceStatus != WIMAX_API_DEVICE_STATUS_Data_Connected) {
		// Dispaly a proper message and exit
		switch (DeviceStatus) {
		case WIMAX_API_DEVICE_STATUS_UnInitialized:
			printf("ERROR: Device not Initialized\n");
			break;
		case WIMAX_API_DEVICE_STATUS_RF_OFF_HW_SW:
			printf("WARNING: HW and SW Radio is turned OFF\n");
			break;
		case WIMAX_API_DEVICE_STATUS_RF_OFF_HW:
			printf("WARNING: HW Radio is turned OFF\n");
			break;
		case WIMAX_API_DEVICE_STATUS_RF_OFF_SW:
			printf("WARNING: SW Radio is turned OFF\n");
			break;
		case WIMAX_API_DEVICE_STATUS_Ready:
		case WIMAX_API_DEVICE_STATUS_Scanning:
		case WIMAX_API_DEVICE_STATUS_Connecting:
			printf("WARNING: Network is not Connected\n");
			break;
		default:
			printf("ERROR: Unknown Device Status\n");
		}
		return 1;
	}

	wmxStatus = GetStatistics(p_device_id, &Statistics);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		PrintWmxStatus(wmxStatus);
		return 1;
	}

	printf("Statistics:\n");
	printf("\tTotal RX Bytes   : %lld bytes\n", Statistics.totalRxByte);
	printf("\tTotal TX Bytes   : %lld bytes\n", Statistics.totalTxByte);
	printf("\tTotal RX Packets : %lld\n", Statistics.totalRxPackets);
	printf("\tTotal TX Packets : %lld\n", Statistics.totalTxPackets);

	return 0;
}

/*
 * Function:     wimaxcu_get_device_info
 * Description:  Retrive the device info
 * Return:
 */
int wimaxcu_get_device_info(WIMAX_API_DEVICE_ID_P p_device_id)
{
	WIMAX_API_RET wmxStatus = WIMAX_API_RET_SUCCESS;

	// Device Version
	WIMAX_API_DEVICE_INFO device_info;
	WIMAX_API_NVM_VERSION nvm_ver;
	WIMAX_API_WMF_COMPLIANCE_VERSION wmf_ver;
	wmxStatus = GetDeviceInformation(p_device_id, &device_info);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		PrintWmxStatus(wmxStatus);
		return 1;
	}

	wmxStatus = GetWMFComplianceVersion(&wmf_ver);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		PrintWmxStatus(wmxStatus);
		return 1;
	}

	wmxStatus = GetNVMImageVersion(p_device_id, &nvm_ver);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		PrintWmxStatus(wmxStatus);
		return 1;
	}


	PrintDeviceInfo(&device_info, &wmf_ver, &nvm_ver);

	return 0;
}

/*
 * Function:     GetVersionInfo
 * Description:  Display the version information
 * Return:
 */
int wimaxcu_get_version_info(WIMAX_API_DEVICE_ID_P p_device_id)
{
	WIMAX_API_RET wmxStatus = WIMAX_API_RET_SUCCESS;

	WIMAX_API_DEVICE_INFO device_info;
	WIMAX_API_WMF_COMPLIANCE_VERSION wmf_version;

	wmxStatus = GetDeviceInformation(p_device_id, &device_info);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		PrintWmxStatus(wmxStatus);
		return 1;
	}

	wmxStatus = GetWMFComplianceVersion(&wmf_version);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		PrintWmxStatus(wmxStatus);
		return 1;
	}

	PrintVersionInfo(&device_info, &wmf_version);

	return 0;
}

/*
 * Function:     wimaxcu_get_user_link_status
 * Description:  Get the link status
 * Return:       0 for success (connected) or 1 for failure
 */
int wimaxcu_get_user_link_status(WIMAX_API_DEVICE_ID_P p_device_id)
{
	WIMAX_API_RET wmxStatus = WIMAX_API_RET_SUCCESS;
	WIMAX_API_CONNECTED_NSP_INFO ConnectedNSP;
	WIMAX_API_LINK_STATUS_INFO LinkStatus;

	wmxStatus = GetConnectedNSP(p_device_id, &ConnectedNSP);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		printf("Link Status: Network is not connected.\n");
		return 1;
	}
	wmxStatus = GetLinkStatus(p_device_id, &LinkStatus);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		PrintWmxStatus(wmxStatus);
		return 1;
	}
	PrintUserLinkStatus(&LinkStatus);
	return 0;
}

//return 0 success 
//      1 fail
int wimaxcu_get_user_link_status_ex(WIMAX_API_DEVICE_ID_P p_device_id)
{
	WIMAX_API_RET wmxStatus = WIMAX_API_RET_SUCCESS;
	WIMAX_API_CONNECTED_NSP_INFO_EX ConnectedNSP;
	WIMAX_API_LINK_STATUS_INFO_EX LinkStatus;

	wmxStatus = GetConnectedNSPEx(p_device_id, &ConnectedNSP);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		printf("Link Status: Network is not connected.\n");
		return 1;
	}
	wmxStatus = GetLinkStatusEx(p_device_id, &LinkStatus);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		PrintWmxStatus(wmxStatus);
		return 1;
	}
	PrintUserLinkStatusEx(&LinkStatus);
	return 0;
}

/*
 * Function:     wimaxcu_radio_on
 * Description:  Turn on the Radio
 * Return:       0 for success,
                 1 for failure, or
                 2 for non-command related error
 */
int wimaxcu_set_radio_on(WIMAX_API_DEVICE_ID_P p_device_id)
{
	int ret = 0;
	WIMAX_API_RET wmxStatus;
	WIMAX_API_DEVICE_STATUS DeviceStatus;
	WIMAX_API_CONNECTION_PROGRESS_INFO ConnectionProgressInfo;

	wmxStatus =
	    GetDeviceStatus(p_device_id, &DeviceStatus,
			    &ConnectionProgressInfo);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		PrintWmxStatus(wmxStatus);
		return 2;
	}

	if (DeviceStatus == WIMAX_API_DEVICE_STATUS_RF_OFF_SW) {
		wmxStatus = CmdControlPowerManagement(p_device_id, WIMAX_API_RF_ON);
		if (WIMAX_API_RET_SUCCESS != wmxStatus) {
			PrintWmxStatus(wmxStatus);
            ret = 1;
		} else {
			// Wait 5 secs to get a confirmation of the updated(desired) device state before declaring success
			if (!wmxcu_sem_timeout(&g_semRfState, 5 * 1000)) {
				if ((g_devState ==
				     WIMAX_API_DEVICE_STATUS_Ready)
				    || (g_devState ==
					WIMAX_API_DEVICE_STATUS_Scanning)
				    || (g_devState ==
					WIMAX_API_DEVICE_STATUS_Connecting)
				    || (g_devState ==
					WIMAX_API_DEVICE_STATUS_Data_Connected))
				{
					printf("SW Radio is turned ON.\n");
					ret = 0;
				} else {
					printf
					    ("ERROR: Failed to turn SW Radio ON.\n");
					ret = 1;
				}
			} else {
				printf("ERROR: Failed to turn SW Radio ON.\n");
				ret = 1;
			}
		}
	} else if (DeviceStatus == WIMAX_API_DEVICE_STATUS_RF_OFF_HW_SW ||
		   DeviceStatus == WIMAX_API_DEVICE_STATUS_RF_OFF_HW) {
		printf
		    ("HW Radio is OFF.\nDisable HW Kill to turn ON the SW Radio.\n");
		ret = 1;
	} else if (DeviceStatus == WIMAX_API_DEVICE_STATUS_UnInitialized) {
		printf
		    ("ERROR: Turning the SW Radio ON unsuccessfull - Device is UnInitialized.\n");
		ret = 1;
	} else {
		printf("HW and SW Radios are ON.\n");
	}
	return ret;
}

/*
 * Function:     wimaxcu_radio_off
 * Description:  Turn off the radio
 * Return:       0 for success,
                 1 for failure, or
                 2 for non-command related error
 */
int wimaxcu_set_radio_off(WIMAX_API_DEVICE_ID_P p_device_id)
{
	int ret = 0;
	WIMAX_API_RET wmxStatus;
	WIMAX_API_DEVICE_STATUS DeviceStatus;
	WIMAX_API_CONNECTION_PROGRESS_INFO ConnectionProgressInfo;

	wmxStatus =
	    GetDeviceStatus(p_device_id, &DeviceStatus,
			    &ConnectionProgressInfo);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		PrintWmxStatus(wmxStatus);
		return 2;
	}

	if (DeviceStatus == WIMAX_API_DEVICE_STATUS_RF_OFF_HW) {
		printf
		    ("HW Radio is OFF.\nDisable HW Kill to turn OFF the SW Radio.\n");
		return 0;
	} else if (DeviceStatus == WIMAX_API_DEVICE_STATUS_RF_OFF_SW) {
		printf("SW Radio is already turned OFF. \n");
		return 0;
	} else if (DeviceStatus == WIMAX_API_DEVICE_STATUS_RF_OFF_HW_SW) {
		printf("HW and SW Radios are already turned OFF.\n");
		return 0;
	}

	if (DeviceStatus != WIMAX_API_DEVICE_STATUS_UnInitialized) {
		wmxStatus =
		    CmdControlPowerManagement(p_device_id, WIMAX_API_RF_OFF);
		if (WIMAX_API_RET_SUCCESS != wmxStatus) {
			PrintWmxStatus(wmxStatus);
			return 1;
		} else {
			// Wait 5 secs to get a confirmation of the updated(desired) device state before declaring success
			if (!wmxcu_sem_timeout(&g_semRfState, 5 * 1000)) {
				if (g_devState ==
				    WIMAX_API_DEVICE_STATUS_RF_OFF_SW) {
					// printf("SW Radio is turned OFF\n");
					ret = 0;
				} else {
					printf
					    ("ERROR: Failed to turn SW Radio OFF.\n");
					ret = 1;
				}
			} else {
				printf("ERROR: Failed to turn SW Radio OFF.\n");
				ret = 1;
			}
		}
	} else {
		printf
		    ("ERROR: Turning the SW Radion OFF unsuccessfull - Device is UnInitialized.\n");
		ret = 2;
	}
	return ret;
}

/*
 * Function:
 * Description:
 * Param:
 * Return:
 */
void wimaxcu_get_conn_nsp(WIMAX_API_DEVICE_ID_P p_device_id)
{
	WIMAX_API_RET wmxStatus = WIMAX_API_RET_SUCCESS;
	WIMAX_API_CONNECTED_NSP_INFO ConnectedNSP;
	WIMAX_API_LINK_STATUS_INFO LinkStatus;

	wmxStatus = GetLinkStatus(p_device_id, &LinkStatus);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		PrintWmxStatus(wmxStatus);
		return;
	}

	wmxStatus = GetConnectedNSP(p_device_id, &ConnectedNSP);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		PrintWmxStatus(wmxStatus);
		return;
	}
	ConnectedNSP.RSSI = LinkStatus.RSSI;
	ConnectedNSP.CINR = LinkStatus.CINR;
	PrintConnectedNSPInfo(&ConnectedNSP);
}

void wimaxcu_get_conn_nsp_ex(WIMAX_API_DEVICE_ID_P p_device_id)
{
	WIMAX_API_RET wmxStatus = WIMAX_API_RET_SUCCESS;
	WIMAX_API_CONNECTED_NSP_INFO_EX ConnectedNSP;
	WIMAX_API_LINK_STATUS_INFO_EX LinkStatus;

	wmxStatus = GetLinkStatusEx(p_device_id, &LinkStatus);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		PrintWmxStatus(wmxStatus);
		return;
	}

	wmxStatus = GetConnectedNSPEx(p_device_id, &ConnectedNSP);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		PrintWmxStatus(wmxStatus);
		return;
	}
	ConnectedNSP.RSSI = LinkStatus.RSSI;
	ConnectedNSP.CINR = LinkStatus.CINR;
	ConnectedNSP.linkQuality = LinkStatus.linkQuality;
	PrintUserLinkStatusEx(&ConnectedNSP);
}

void wimaxcu_get_conn_time(WIMAX_API_DEVICE_ID_P p_device_id)
{
	WIMAX_API_RET wmxStatus = WIMAX_API_RET_SUCCESS;
	WIMAX_API_CONNECTION_TIME connectionTime;

	wmxStatus = GetConnectionTime(p_device_id, &connectionTime);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		PrintWmxStatus(wmxStatus);
		return;
	}
	PrintConnectionTime(connectionTime);
}


/*
 * Function:     wimaxcu_get_contact_info
 * Description:  Get the contact info of given NSP
 * Return:       0 for success or 1 for failure
 */
int wimaxcu_get_contact_info(WIMAX_API_DEVICE_ID_P p_device_id, char *str_nspid)
{
	WIMAX_API_RET wmxStatus = WIMAX_API_RET_SUCCESS;
	WIMAX_API_CONTACT_INFO *pContactInfo = NULL;
	WIMAX_API_PROFILE_INFO_P profilelist = NULL;
	UINT32 SizeOfContactList = MAX_PROFILE;
	UINT32 numProfileList = MAX_PROFILE;
	char profile_name[MAX_SIZE_OF_NSP_NAME];

	char tmp_nspID_str[MAX_NSP_ID_LEN];
	BOOL found_nsp = FALSE;
	int i, cmd;
	int ret = 0;

	profilelist = (WIMAX_API_PROFILE_INFO_P) malloc(sizeof(WIMAX_API_PROFILE_INFO) * MAX_PROFILE);
	memset(profilelist, 0, sizeof(WIMAX_API_PROFILE_INFO) * MAX_PROFILE);

	wmxStatus = GetSelectProfileList(p_device_id, profilelist, &numProfileList);
	if (wmxStatus != WIMAX_API_RET_SUCCESS) {
	printf("ERROR: Retriving the Network list was unsuccessfull");
	//PrintWmxStatus(wmxStatus);
	free(profilelist);
	return 1;
	}

	if (numProfileList == 0){
	printf ("WARNING: Cannot find any available network.\n");
	free(profilelist);
	return 1;
	}
	
	for (i = 0; i < numProfileList ; i++) {
		sprintf(tmp_nspID_str, "%d", profilelist[i].profileID);
		
		if (strcmp(tmp_nspID_str, str_nspid) == 0) {
			found_nsp = TRUE;
			break;
		}
	}
	if (found_nsp == FALSE) {
		printf("WARNING: Cannot find the matching Network ID(%s) \n", str_nspid);
		free(profilelist);
		return 1;
	}
	pContactInfo = (WIMAX_API_CONTACT_INFO_P) malloc(sizeof(WIMAX_API_CONTACT_INFO) *   MAX_PROFILE);
	if (pContactInfo == NULL) {
		printf("ERROR: INternal failure\n");
		free(profilelist);
		return 1;
	}
	
	strncpy(profile_name,profilelist[i].profileName,strlen(profilelist[i].profileName)-1);
	
	wmxStatus = GetContactInformation(p_device_id, profile_name, pContactInfo, &SizeOfContactList);
	if (wmxStatus != WIMAX_API_RET_SUCCESS) {
		printf("ERROR: Retriving the Contact Information was unsuccessfull\n");
		ret = 1;
	} else {
		printf("%s Contact Information:\n", profilelist[i].profileName);
		if (SizeOfContactList > 0) {
			for (cmd = 0; cmd < SizeOfContactList; cmd++) {
				printf("\tTitle: %s\n",
				       pContactInfo[cmd].textForURI);
				printf("\tURL  : %s\n", pContactInfo[cmd].URI);
			}
			ret = 0;
		} else {
			printf("Contact Information Un-Available.\n");
			ret = 1;
		}
	}

	free(profilelist);
	free(pContactInfo);

	return ret;
}

void wimaxcu_get_odm_info(WIMAX_API_DEVICE_ID_P p_device_id)
{
	int i;
	WIMAX_API_RET wmxStatus;
	WIMAX_API_BINARY_BLOB bin_blob;
	UINT32 bin_blob_size;
	bin_blob_size = sizeof(bin_blob);
	//BinaryBlob = malloc(sizeof(BinaryBlob));
	wmxStatus = GetODMInformation(p_device_id, bin_blob ,&bin_blob_size);
	if(wmxStatus != WIMAX_API_RET_SUCCESS)
	{
		printf("ERROR: Failed to get ODM version\n");
		PrintWmxStatus(wmxStatus);
		return 1;
	}
	printf("ODM Information\n");
	for(i = 0; i < bin_blob_size; i++) {
		printf("%c",bin_blob[i]);	
	}
	printf("\n");
	return 0;
}

void wimaxcu_get_nvm_info(WIMAX_API_DEVICE_ID_P p_device_id)
{
	WIMAX_API_NVM_VERSION NVMImageVersion;
	WIMAX_API_RET wmxStatus;
	wmxStatus = GetNVMImageVersion(p_device_id, &NVMImageVersion);

	if(wmxStatus != WIMAX_API_RET_SUCCESS)
	{
		printf("ERROR: Failed to get NVM image version\n");
		PrintWmxStatus(wmxStatus);
		return 1;
	}
	
	PrintNVMImageVersion(&NVMImageVersion);
	
	return 0;
}

void wimaxcu_get_ip_interface(WIMAX_API_DEVICE_ID_P p_device_id)
{
	WIMAX_API_RET wmxStatus;
	WIMAX_API_INTERFACE_INFO InterfaceInfo;
	wmxStatus = GetIPInterfaceIndex(p_device_id, &InterfaceInfo);
	if (wmxStatus == WIMAX_API_RET_SUCCESS) {
		//printf("%s",InterfaceInfo );
	}
}

void wimaxcu_set_fast_reconnect(WIMAX_API_DEVICE_ID_P p_device_id, BOOL isEnabled)
{
	WIMAX_API_RET wmxStatus;

	wmxStatus = SetFastReconnectCapabilityStatus(p_device_id, isEnabled);
	if (wmxStatus == WIMAX_API_RET_SUCCESS) {
		if (isEnabled == 0)
			printf("Fast Reconnect Disabled\n");
		else
			printf("Fase Reconnect Enabled\n");

	} else {
		printf("Failed to set Fast Reconnect settings\n");
	}
}

void wimaxcu_get_fast_reconnect(WIMAX_API_DEVICE_ID_P p_device_id)
{
	WIMAX_API_RET wmxStatus;
	BOOL isEnabled;

	wmxStatus = GetFastReconnectCapabilityStatus(p_device_id, &isEnabled);

	if (wmxStatus == WIMAX_API_RET_SUCCESS) {
		if (isEnabled == 0)
			printf("Fast Reconnect Disabled\n");
		else if (isEnabled == 1)
			printf("Fase Reconnect Enabled\n");

	}
}

void wimaxcu_set_connected_as_current(WIMAX_API_DEVICE_ID_P p_device_id, BOOL isEnable)
{
	WIMAX_API_RET wmxStatus;
	wmxStatus =
	    SetConnectedAsCurrentPreferredCapabilityStatus(p_device_id,
							   isEnable);
	if (wmxStatus == WIMAX_API_RET_SUCCESS) {
		if (isEnable == 0)
			printf
			    ("Current Connected Network Preferred settings are disabled\n");
		else if (isEnable == 1)
			printf
			    ("Current Connected Network Preferred settings are enabled\n");

	} else
		printf("Failed to set preferred settings\n");

}

void wimaxcu_get_connected_as_current(WIMAX_API_DEVICE_ID_P p_device_id)
{
	WIMAX_API_RET wmxStatus;
	BOOL isEnable;
	wmxStatus =
	    GetConnectedAsCurrentPreferredCapabilityStatus(p_device_id,
							   &isEnable);
	if (wmxStatus == WIMAX_API_RET_SUCCESS) {
		if (isEnable == FALSE)
			printf
			    ("Current Connected Network Preferred settings are disabled\n");
		else
			printf
			    ("Current Connected Network Preferred settings are enabled\n");
	} else {
		printf("Failed to get preferred settings\n");
	}

}

void wimaxcu_get_api_ex_version(WIMAX_API_DEVICE_ID_P p_device_id)
{
	UINT32 WmxApiExVersion;
	WIMAX_API_RET wmxStatus;
	wmxStatus = GetWmxApiExVersion(&WmxApiExVersion);
	if (wmxStatus == WIMAX_API_RET_SUCCESS) {
		printf("%ld\n", WmxApiExVersion);
	}
}

void wimaxcu_set_coex_mode(WIMAX_API_DEVICE_ID_P p_device_id,
		 WIMAX_API_COEXISTENCE_MODE coexMode)
{

	WIMAX_API_RET wmxStatus;
	// WSS LINUX START - EVP Specific
	// Kalyan: EVP supports only CM mode
	// So The following code under EVP_SUPPORTS_CM_ONLY is for EVP only
	// The macro EVP_SUPPORTS_CM_ONLY is defined in Makefile
#ifdef EVP_SUPPORTS_CM_ONLY
	if (coexMode == MODE_CM) {
#endif
		// WSS LINUX End
		wmxStatus = SetCoexistenceMode(p_device_id, coexMode);
		// WSS LINUX START - EVP Specific
#ifdef EVP_SUPPORTS_CM_ONLY
	} else {
		printf("Could not change Coex to XOR Mode\n");
		printf("EVP hardware does not support XOR Mode\n");
		return;
	}
#endif
	// WSS LINUX End
	if (wmxStatus == WIMAX_API_RET_SUCCESS) {
		switch (coexMode) {
		case MODE_XOR:
			printf("Coex changed to XOR Mode\n");
			break;
		case MODE_CM:
			printf("Coex changed to CM Mode\n");
			break;
		}
	} else
		printf("Failed to set the Co-Ex Mode\n");
}

void wimaxcu_get_coex_mode(WIMAX_API_DEVICE_ID_P p_device_id)
{
	WIMAX_API_RET wmxStatus;
	WIMAX_API_COEXISTENCE_MODE CoexMode;
	wmxStatus = GetCoexistenceMode(p_device_id, &CoexMode);
	if (wmxStatus == WIMAX_API_RET_SUCCESS) {
		switch (CoexMode) {
		case MODE_XOR:
			printf("Coex is set to MODE_XOR\n");
			break;
		case MODE_CM:
			printf("Coex is set to MODE_CM\n");
			break;
		}
	}
}
