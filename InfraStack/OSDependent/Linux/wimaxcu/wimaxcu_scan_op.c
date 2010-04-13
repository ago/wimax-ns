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


#include<wimaxcu.h>




int wimaxcu_get_network_list_ex(WIMAX_API_DEVICE_ID_P p_device_id, CMD_ARGS scan_mode)
{
	int ret = 0;
	WIMAX_API_RET wmxStatus;
	int time_out = 0;
	WIMAX_API_CONNECTION_MODE connectMode;
	WIMAX_API_DEVICE_STATUS DeviceStatus;
	WIMAX_API_CONNECTION_PROGRESS_INFO ConnectionProgressInfo;
	WIMAX_API_NSP_INFO_EX_P pNspInfo;

	UINT32 numOfNSPs = 20;
	int i = 0;

	// initialize the variable as No Networks found
	g_noNetworksFound = 1;
	g_searchProgress = 0;
	// get the device status
	wmxStatus =
	    GetDeviceStatus(p_device_id, &DeviceStatus,
			    &ConnectionProgressInfo);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		PrintWmxStatus(wmxStatus);
		return 2;
	}

	switch (DeviceStatus) {
	case WIMAX_API_DEVICE_STATUS_UnInitialized: /**<  Device is uninitialized */
		printf("ERROR: Device not Initialized\n");
		return 2;
	case WIMAX_API_DEVICE_STATUS_RF_OFF_HW_SW:  /**<  Device RF Off(both H/W and S/W) */
		printf
		    ("WARNING: HW and SW Radios are OFF.\nPlease turn ON the HW and SW Radios to perform a scan.\n");
		return 2;
	case WIMAX_API_DEVICE_STATUS_RF_OFF_HW:     /**<  Device RF Off(via H/W switch) */
		printf
		    ("WARNING: HW Radio is OFF.\nPlease turn ON the HW Radio to perform a scan.\n");
		return 2;
	case WIMAX_API_DEVICE_STATUS_RF_OFF_SW:     /**<  Device RF Off(via S/W switch) */
		printf
		    ("WARNING: SW Radio is OFF.\nPlease turn ON the SW Radio to perform a scan.\n");
		return 2;
	case WIMAX_API_DEVICE_STATUS_Ready:	     /**<  Device is ready */
	case WIMAX_API_DEVICE_STATUS_Scanning:	     /**<  Device is scanning */
		break;
	case WIMAX_API_DEVICE_STATUS_Connecting:    /**<  Connection in progress */
		printf("WARNING: Connection is in progress\n");
		return 2;
	case WIMAX_API_DEVICE_STATUS_Data_Connected:	/**<  Layer 2 connected */
		printf
		    ("WARNING: Connection already established!\nPlease disconnect, before attempting to scan.\n");
		return 2;
	default:
		printf("ERROR: Device status Unknown.\n");
		return 2;
	}
        

	wmxStatus = SubscribeRfTaken(p_device_id, &ind_rf_taken_cb);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		PrintWmxStatus(wmxStatus);
		return 2;
	}
	wmxStatus = GetConnectionMode(p_device_id, &connectMode);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		PrintWmxStatus(wmxStatus);
		return 2;
	}

	if (connectMode == WIMAX_API_CONNECTION_MANUAL_SCAN_MANUAL_CONNECT
	    && DeviceStatus == WIMAX_API_DEVICE_STATUS_Scanning) {
		printf
		    ("WARNING: Scanning is in progress\nPlease wait for the current scan to complete.\n");
		return 2;
	}

	if (scan_mode == CMD_SCAN_ARG_PREFERRED) {

		wmxStatus =
		    SubscribeNetworkSearchEx(p_device_id,
					     &ind_network_search_cb_ex);
		if (WIMAX_API_RET_SUCCESS != wmxStatus) {
			PrintWmxStatus(wmxStatus);
			return 2;
		}
		/* In Manual mode always scan do not read the cache as we don't know when cache was updated */
		if (connectMode !=
		    WIMAX_API_CONNECTION_MANUAL_SCAN_MANUAL_CONNECT) {
			pNspInfo =
			    (WIMAX_API_NSP_INFO_EX_P) malloc(MAX_LEN *
							     sizeof
							     (WIMAX_API_NSP_INFO_EX));
			memset(pNspInfo, 0,
			       sizeof(WIMAX_API_NSP_INFO_EX) * MAX_LEN);
			wmxStatus =
			    GetNetworkListEx(p_device_id, pNspInfo, &numOfNSPs);
			if (WIMAX_API_RET_SUCCESS != wmxStatus) {
				PrintWmxStatus(wmxStatus);
				/*
				   If the Device is already scanning, it won't allow one more AppSrv will reject it
				   with the Operation Falied error
				 */
				free(pNspInfo);
				return 1;
			}

			if (numOfNSPs != 0) {
				for (i = 0; i < numOfNSPs; i++) {
					printf("\nNetwork found.\n");
					PrintNSPInfoEx(&pNspInfo[i]);
					if (wimaxcu_is_network_activated_ex
					    (p_device_id, &pNspInfo[i]))
						printf("\tActivated\n");
					else
						printf("\tNot Activated\n");
				}
				return 0;
			}
		}

		wmxStatus = CmdNetworkSearch(p_device_id);

		if (WIMAX_API_RET_SUCCESS != wmxStatus) {
			PrintWmxStatus(wmxStatus);
			if ((DeviceStatus == WIMAX_API_DEVICE_STATUS_Scanning)
			    && (wmxStatus == WIMAX_API_RET_FAILED)) {
				printf
				    ("WARNING: Scanning is in progress\nPlease wait for the current scan to complete.\n");
			}
			return 1;
		}

		printf("Scanning %2d%% Done ", g_searchProgress);
		fflush(stdout);
		do {
			if (wmxcu_sem_timeout(&g_semConnectionUtility, 5 * 1000)
			    == 1) {
				time_out++;
				//if (pthread_mutex_trylock(&g_console_owner_mutex) == 0) {
					printf("\r");
					printf("Scanning %2d%% Done ",
					       g_searchProgress);
					// printf("Scanning %2d% Done [", g_searchProgress);

					for (i = 0; i <= time_out; i++) {
						printf("=");
					}
					printf("-");
//                                      for(i = 0; i<=SCAN_TIMEOUT_IN_10SEC_ITREATIONS - time_out; i++)
//                                      {
//                                              printf(" ");
//                                      }
//                                      printf("]");
					fflush(stdout);
					//pthread_mutex_unlock(&g_console_owner_mutex);
				//}
				wmxStatus =
				    GetDeviceStatus(p_device_id, &DeviceStatus,
						    &ConnectionProgressInfo);
				if (WIMAX_API_RET_SUCCESS != wmxStatus) {
					PrintWmxStatus(wmxStatus);
					return 2;
				}

				if (DeviceStatus == WIMAX_API_DEVICE_STATUS_Ready) {
					if (g_noNetworksFound == 1) 
						printf("\nNo networks found.\n");
					break;
				}

				if (time_out > SCAN_TIMEOUT_IN_10SEC_ITREATIONS) {
					if (g_noNetworksFound == 1) {
						printf
						    ("\nNo networks found.\n");
					} else {
						printf
						    ("\nScan Operation timeout.\n");
						// As Scan operation timed out
						ret = 1;
					}
					break;
				}
			} else {
				break;
			}
		} while (1);

	} else if (scan_mode == CMD_SCAN_ARG_WIDE) {

		wmxStatus = SubscribeNetworkSearchWideScanEx(p_device_id,
							     &ind_network_search_wide_scan_cb_ex);
		if (WIMAX_API_RET_SUCCESS != wmxStatus) {
			PrintWmxStatus(wmxStatus);
			return 2;
		}
		// Display the warning message:
		printf("WARNING: Wide scan may take upto 2 minutes... \n");
		wmxStatus = CmdNetworkSearchWideScan(p_device_id);
		if (WIMAX_API_RET_SUCCESS != wmxStatus) {
			PrintWmxStatus(wmxStatus);
			/*
			   If the Device is already scanning, it won't allow one more AppSrv will reject it
			   with the Operation Falied wrror
			 */
			if ((DeviceStatus == WIMAX_API_DEVICE_STATUS_Scanning)
			    && (wmxStatus == WIMAX_API_RET_FAILED)) {
				printf
				    ("WARNING: Scanning is in progress\nPlease wait for the current scan to complete.\n ");

			}
			return 1;
		}

		if (wmxcu_sem_timeout(&g_semConnectionUtility, 120 * 1000) == 1)
			printf("No networks found.\n");
	}
	wmxStatus = UnsubscribeRfTaken(p_device_id);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		PrintWmxStatus(wmxStatus);
		return 2;
	}
	wmxStatus = UnsubscribeNetworkSearchEx(p_device_id);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		PrintWmxStatus(wmxStatus);
		return 2;
	}
	wmxStatus = UnsubscribeNetworkSearchWideScanEx(p_device_id);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		PrintWmxStatus(wmxStatus);
		return 2;
	}
	return ret;
}

/*
Function:
GetNetworkList(WIMAX_API_DEVICE_ID_P p_device_id)

Purpose:
This API casuses the device to perform a scan operation and returns a list of  detected NSPs.
This is a blocking API. It returns to the caller after a single  full scan cycle is completed.

Parameters:
WIMAX_API_DEVICE_ID_P p_device_id - device info like device index, permission etc
*/
int wimaxcu_get_network_list(WIMAX_API_DEVICE_ID_P p_device_id, CMD_ARGS scan_mode)
{
	int ret = 0;
	WIMAX_API_RET wmxStatus;
	int time_out = 0;
	WIMAX_API_CONNECTION_MODE connectMode;
	WIMAX_API_DEVICE_STATUS DeviceStatus;
	WIMAX_API_CONNECTION_PROGRESS_INFO ConnectionProgressInfo;
	WIMAX_API_NSP_INFO_P pNspInfo;

	UINT32 numOfNSPs = 20;
	int i = 0;

	// initialize the variable as No Networks found
	g_noNetworksFound = 1;
	g_searchProgress = 0;
	// get the device status
	wmxStatus =
	    GetDeviceStatus(p_device_id, &DeviceStatus,
			    &ConnectionProgressInfo);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		PrintWmxStatus(wmxStatus);
		return 2;
	}

	switch (DeviceStatus) {
	case WIMAX_API_DEVICE_STATUS_UnInitialized: /**<  Device is uninitialized */
		printf("ERROR: Device not Initialized\n");
		return 2;
	case WIMAX_API_DEVICE_STATUS_RF_OFF_HW_SW:  /**<  Device RF Off(both H/W and S/W) */
		printf
		    ("WARNING: HW and SW Radios are OFF.\nPlease turn ON the HW and SW Radios to perform a scan.\n");
		return 2;
	case WIMAX_API_DEVICE_STATUS_RF_OFF_HW:     /**<  Device RF Off(via H/W switch) */
		printf
		    ("WARNING: HW Radio is OFF.\nPlease turn ON the HW Radio to perform a scan.\n");
		return 2;
	case WIMAX_API_DEVICE_STATUS_RF_OFF_SW:     /**<  Device RF Off(via S/W switch) */
		printf
		    ("WARNING: SW Radio is OFF.\nPlease turn ON the SW Radio to perform a scan.\n");
		return 2;
	case WIMAX_API_DEVICE_STATUS_Ready:	     /**<  Device is ready */
	case WIMAX_API_DEVICE_STATUS_Scanning:	     /**<  Device is scanning */
		break;
	case WIMAX_API_DEVICE_STATUS_Connecting:    /**<  Connection in progress */
		printf("WARNING: Connection is in progress\n");
		return 2;
	case WIMAX_API_DEVICE_STATUS_Data_Connected:	/**<  Layer 2 connected */
		printf
		    ("WARNING: Connection already established!\nPlease disconnect, before attempting to scan.\n");
		return 2;
	default:
		printf("ERROR: Device status Unknown.\n");
		return 2;
	}

	wmxStatus = SubscribeRfTaken(p_device_id, &ind_rf_taken_cb);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		PrintWmxStatus(wmxStatus);
		return 2;
	}
	wmxStatus = GetConnectionMode(p_device_id, &connectMode);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		PrintWmxStatus(wmxStatus);
		return 2;
	}

	if (connectMode == WIMAX_API_CONNECTION_MANUAL_SCAN_MANUAL_CONNECT
	    && DeviceStatus == WIMAX_API_DEVICE_STATUS_Scanning) {
		printf
		    ("WARNING: Scanning is in progress\nPlease wait for the current scan to complete.\n");
		return 2;
	}

	if (scan_mode == CMD_SCAN_ARG_PREFERRED) {
		wmxStatus =
		    SubscribeNetworkSearch(p_device_id, &ind_network_search_cb);
		if (WIMAX_API_RET_SUCCESS != wmxStatus) {
			PrintWmxStatus(wmxStatus);
			return 2;
		}
		/* In Manual mode always scan do not read the cache as we don't know when cache was updated */
		if (connectMode !=  WIMAX_API_CONNECTION_MANUAL_SCAN_MANUAL_CONNECT) {
			pNspInfo =
			    (WIMAX_API_NSP_INFO_P) malloc(MAX_LEN * sizeof(WIMAX_API_NSP_INFO));
			memset(pNspInfo, 0, sizeof(WIMAX_API_NSP_INFO) * MAX_LEN);
			wmxStatus =
			    GetNetworkList(p_device_id, pNspInfo, &numOfNSPs);
			if (WIMAX_API_RET_SUCCESS != wmxStatus) {
				PrintWmxStatus(wmxStatus);
				/*
				   If the Device is already scanning, it won't allow one more AppSrv will reject it
				   with the Operation Falied error
				 */
				free(pNspInfo);
				return 1;
			}

			if (numOfNSPs != 0) {
				for (i = 0; i < numOfNSPs; i++) {
					printf("\nNetwork found.\n");
					PrintNSPInfo(&pNspInfo[i]);
					if (wimaxcu_is_network_activated
					    (p_device_id, &pNspInfo[i]))
						printf("\tActivated\n");
					else
						printf("\tNot Activated\n");
				}
				return 0;
			}
		}

		wmxStatus = CmdNetworkSearch(p_device_id);

		if (WIMAX_API_RET_SUCCESS != wmxStatus) {
			PrintWmxStatus(wmxStatus);
			if ((DeviceStatus == WIMAX_API_DEVICE_STATUS_Scanning)
			    && (wmxStatus == WIMAX_API_RET_FAILED)) {
				printf
				    ("WARNING: Scanning is in progress\nPlease wait for the current scan to complete.\n");
			}
			return 1;
		}

		printf("Scanning %2d%% Done ", g_searchProgress);
		fflush(stdout);
		do {
			if (wmxcu_sem_timeout(&g_semConnectionUtility, 5 * 1000) == 1) {
				time_out++;
				//if (pthread_mutex_trylock(&g_console_owner_mutex) == 0) 
				//{
					printf("\r");
					printf("Scanning %2d%% Done ",
					       g_searchProgress);
					// printf("Scanning %2d% Done [", g_searchProgress);

					for (i = 0; i <= time_out; i++) {
						printf("=");
					
						
					}
					printf("-");
					
//                                      for(i = 0; i<=SCAN_TIMEOUT_IN_10SEC_ITREATIONS - time_out; i++)
//                                      {
//                                              printf(" ");
//                                      }
//                                      printf("]");
					fflush(stdout);
					//pthread_mutex_unlock(&g_console_owner_mutex);
				//}
				wmxStatus =   GetDeviceStatus(p_device_id, &DeviceStatus,
						    &ConnectionProgressInfo);
				if (WIMAX_API_RET_SUCCESS != wmxStatus) {
					PrintWmxStatus(wmxStatus);
					return 2;
				}
                              	
				if (DeviceStatus == WIMAX_API_DEVICE_STATUS_Ready) {
					if (g_noNetworksFound == 1) 
						printf("\nNo networks found.\n");
					break;
				}
				//                                   
//                              } else {
//                                      printf("1No networks found.\n");
//                                      break;
//                              }
				

				if (time_out > SCAN_TIMEOUT_IN_10SEC_ITREATIONS) {
					if (g_noNetworksFound == 1) {
						printf
						    ("\n No networks found.\n");
					} else {
						printf
						    ("\n Scan Operation timeout.\n");
						// As Scan operation timed out
						ret = 1;
					}
					break;
				}
			} else {
				break;
			}
		} while (1);

	} else if (scan_mode == CMD_SCAN_ARG_WIDE) {
		// Get User Connect Mode
		int userConnectMode;
		wmxStatus = GetConnectionMode(p_device_id, &userConnectMode);
		if (WIMAX_API_RET_SUCCESS != wmxStatus) {
			PrintWmxStatus(wmxStatus);
			return 1;
		}

		if ((connectMode ==
		     WIMAX_API_CONNECTION_SEMI_MANUAL_SCAN_AUTO_CONNECT)
		    || (connectMode ==
			WIMAX_API_CONNECTION_AUTO_SCAN_AUTO_CONNECT)
		    || (connectMode ==
			WIMAX_API_CONNECTION_SEMI_MANUAL_SCAN_MANUAL_CONNECT)) {
			if (connectMode ==
			    WIMAX_API_CONNECTION_SEMI_MANUAL_SCAN_MANUAL_CONNECT)
			{
				printf
				    ("Changing Scan mode to Manual Scan mode \n");
			} else {
				printf("Changing Scan mode to manual \n");
				printf("Changing Connect mode to manual \n");
			}
			userConnectMode =
			    WIMAX_API_CONNECTION_MANUAL_SCAN_MANUAL_CONNECT;
			wmxStatus =
			    SetConnectionMode(p_device_id, userConnectMode);
			if (WIMAX_API_RET_SUCCESS != wmxStatus) {
				PrintWmxStatus(wmxStatus);
				return 1;
			}
		}

		wmxStatus = SubscribeNetworkSearchWideScan(p_device_id,
							   &ind_network_search_wide_scan_cb);
		if (WIMAX_API_RET_SUCCESS != wmxStatus) {
			PrintWmxStatus(wmxStatus);
			return 2;
		}

		// Display the warning message:
		printf("WARNING: Wide scan may take upto 2 minutes... \n");
		wmxStatus = CmdNetworkSearchWideScan(p_device_id);
		if (WIMAX_API_RET_SUCCESS != wmxStatus) {
			PrintWmxStatus(wmxStatus);
			/*
			   If the Device is already scanning, it won't allow one more AppSrv will reject it
			   with the Operation Falied wrror
			 */
			if ((DeviceStatus == WIMAX_API_DEVICE_STATUS_Scanning)
			    && (wmxStatus == WIMAX_API_RET_FAILED)) {
				printf
				    ("WARNING: Scanning is in progress\nPlease wait for the current scan to complete.\n ");

			}
			return 1;
		}

		if (wmxcu_sem_timeout(&g_semConnectionUtility, 120 * 1000) == 1)
			printf("No networks found.\n");
	}

	wmxStatus = UnsubscribeRfTaken(p_device_id);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		PrintWmxStatus(wmxStatus);
		return 2;
	}

	wmxStatus = UnsubscribeNetworkSearch(p_device_id);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		PrintWmxStatus(wmxStatus);
		return 2;
	}
	wmxStatus = UnsubscribeNetworkSearchWideScan(p_device_id);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		PrintWmxStatus(wmxStatus);
		return 2;
	}
	return ret;
}

void ind_network_search_wide_scan_cb_ex(WIMAX_API_DEVICE_ID_P p_device_id,
				  WIMAX_API_NSP_INFO_EX_P pNspList,
				  UINT32 listSize)
{
	int i;
	// Scan complete arrived.  Display the netwokr list.
	if (pNspList == NULL || listSize < 1) {
		printf("No networks found.\n");
	} else {
		for (i = 0; i < listSize; i++) {
			PrintNSPInfoEx(&pNspList[i]);
			if (wimaxcu_is_network_activated_ex(p_device_id, &pNspList[i]))
				printf("\tActivated.\n");
			else
				printf("\tNot Activated.\n");
		}
		// Unset the preferred NSP
		g_preferred_NSP_ID = 0;
		SetCurrentPreferredProfiles(p_device_id, &g_preferred_NSP_ID, 0);
	}
	// release the semaphore
	sem_post(&g_semConnectionUtility);
}

void ind_network_search_wide_scan_cb(WIMAX_API_DEVICE_ID_P p_device_id,
				WIMAX_API_NSP_INFO_P pNspList, UINT32 listSize)
{
	int i;
	// Scan complete arrived.  Display the netwokr list.
	if (pNspList == NULL || listSize < 1) {
		printf("No networks found.\n");
	} else {
		for (i = 0; i < listSize; i++) {
			PrintNSPInfo(&pNspList[i]);
			if (wimaxcu_is_network_activated(p_device_id, &pNspList[i]))
				printf("\tActivated.\n");
			else
				printf("\tNot Activated.\n");
		}
		// Unset the preferred NSP
		g_preferred_NSP_ID = 0;
		SetCurrentPreferredProfiles(p_device_id, &g_preferred_NSP_ID, 0);
	}
	// release the semaphore
	sem_post(&g_semConnectionUtility);
}

void ind_network_search_cb_ex(WIMAX_API_DEVICE_ID_P p_device_id,
			  WIMAX_API_NSP_INFO_EX_P pNspList,
			  UINT32 listSize, UINT32 searchProgress)
{
	int i;

	// Scan complete arrived.  Display the netwokr list.
	if (pNspList == NULL || listSize < 1) {
		g_searchProgress = searchProgress;
		// printf("No networks found.\n");
	} else {
		pthread_mutex_lock(&g_console_owner_mutex);
		if (searchProgress == 100) {
			for (i = 0; i < listSize; i++) {
				g_noNetworksFound = 0;
				printf("\n");
				printf("Network found.\n");
				PrintNSPInfoEx(&pNspList[i]);
				if (wimaxcu_is_network_activated_ex
				    (p_device_id, &pNspList[i]))
					printf("\tActivated.\n");
				else
					printf("\tNot Activated.\n");
			}

		} else {
			g_searchProgress = searchProgress;
		}
		pthread_mutex_unlock(&g_console_owner_mutex);
	}
	if (searchProgress == 100) {
		if (g_noNetworksFound == 1) {
			pthread_mutex_lock(&g_console_owner_mutex);
			printf("\nNo networks found.\n");
			pthread_mutex_unlock(&g_console_owner_mutex);
			// release the semaphore
			sem_post(&g_semConnectionUtility);
		} else {
			// release the semaphore
			pthread_mutex_lock(&g_console_owner_mutex);
			printf("\nScanning operation completed.\n");
			pthread_mutex_unlock(&g_console_owner_mutex);
			sem_post(&g_semConnectionUtility);
		}
	}

}

void ind_network_search_cb(WIMAX_API_DEVICE_ID_P p_device_id,
			WIMAX_API_NSP_INFO_P pNspList,
			UINT32 listSize, UINT32 searchProgress)
{
	int i;

	
	// Scan complete arrived.  Display the netwokr list.
		if (pNspList == NULL || listSize < 1) {
			g_searchProgress = searchProgress;
			// printf("No networks found.\n");
		} else {
			pthread_mutex_lock(&g_console_owner_mutex);
			if (searchProgress == 100) {
				for (i = 0; i < listSize; i++) {
					g_noNetworksFound = 0;
					printf("\n");
					printf("Network found.\n");
					PrintNSPInfo(&pNspList[i]);
					if (wimaxcu_is_network_activated
					(p_device_id, &pNspList[i]))
						printf("\tActivated.\n");
					else
						printf("\tNot Activated.\n");
				}
	
			} else {
				g_searchProgress = searchProgress;
			}
			pthread_mutex_unlock(&g_console_owner_mutex);
		}
		if (searchProgress == 100) {
			if (g_noNetworksFound == 1) {
				pthread_mutex_lock(&g_console_owner_mutex);
				printf("\nNo networks found.\n");
				pthread_mutex_unlock(&g_console_owner_mutex);
				// release the semaphore
				sem_post(&g_semConnectionUtility);
			} else {
				// release the semaphore
				pthread_mutex_lock(&g_console_owner_mutex);
				printf("\nScanning operation completed.\n");
				pthread_mutex_unlock(&g_console_owner_mutex);
				sem_post(&g_semConnectionUtility);
			}
		}
	
	
}

int wimaxcu_find_network(WIMAX_API_DEVICE_ID_P p_device_id, int profileId,
		WIMAX_API_NSP_INFO_P nspInfo)
{
	WIMAX_API_RET wmxStatus = WIMAX_API_RET_SUCCESS;
	UINT32 numProfileList = MAX_PROFILE;
	int i = 0, j = 0,ret = 0;
	int time_out = 0;
	UINT32 numOfNSPs = MAX_DEVICE;
	WIMAX_API_DEVICE_STATUS DeviceStatus;
	WIMAX_API_CONNECTION_PROGRESS_INFO ConnectionProgressInfo;
	WIMAX_API_NSP_INFO_P pNspInfo =
	    (WIMAX_API_NSP_INFO_P) malloc(MAX_LEN * sizeof(WIMAX_API_NSP_INFO));
	WIMAX_API_PROFILE_INFO_P profilelist = (WIMAX_API_PROFILE_INFO_P)
	    malloc(sizeof(WIMAX_API_PROFILE_INFO) * MAX_PROFILE);
	memset(profilelist, 0, sizeof(WIMAX_API_PROFILE_INFO) * MAX_PROFILE);

	//1. Get the profile list and network list
	wmxStatus =
	    GetSelectProfileList(p_device_id, profilelist, &numProfileList);
	if (wmxStatus != WIMAX_API_RET_SUCCESS) {
		printf("ERROR: Could not fetch the profile list- ");
		PrintWmxStatus(wmxStatus);
		return 0;
	}

	if (numProfileList == 0) {
		printf("WARNING: Profile list is empty \n");
		return 0;
	}

	for (i = 0; i < numProfileList; i++) {
		// check the match
		if (profileId == profilelist[i].profileID) {
//
			// zero the memory
			memset(pNspInfo, 0,
			       sizeof(WIMAX_API_NSP_INFO) * MAX_LEN);
			wmxStatus =
			    GetNetworkList(p_device_id, pNspInfo, &numOfNSPs);
			if (WIMAX_API_RET_SUCCESS != wmxStatus) {
				printf
				    ("ERROR: Could not fetch network list - ");
				PrintWmxStatus(wmxStatus);
				free(pNspInfo);
				free(profilelist);
				return 0;
			}
			if(numOfNSPs == 0)
			{
				//numOfNSPs is 0 now - it should be set to MAX
				numOfNSPs=MAX_DEVICE;
				printf("Searching....\n");
				wmxStatus = SubscribeNetworkSearch(p_device_id, &ind_network_search_cb );
				if (WIMAX_API_RET_SUCCESS != wmxStatus) {
				PrintWmxStatus(wmxStatus);
				return 2;
				}
				wmxStatus = CmdNetworkSearch(p_device_id);
				if (WIMAX_API_RET_SUCCESS != wmxStatus) {
					PrintWmxStatus(wmxStatus);
					return 1;
				}

				printf("Scanning %2d%% Done ", g_searchProgress);
			   	fflush(stdout);
				do {
					if (wmxcu_sem_timeout(&g_semConnectionUtility,5*1000) == 1 )
					{
						time_out++;
						//if (pthread_mutex_trylock(&g_console_owner_mutex) == 0) {
							printf("\r");
							printf("Scanning %2d%% Done ", g_searchProgress);
						// printf("Scanning %2d% Done [", g_searchProgress);
						
							for(i = 0; i<=time_out; i++)
							{
								printf("=");
							}
							printf("-");
	// 					for(i = 0; i<=SCAN_TIMEOUT_IN_10SEC_ITREATIONS - time_out; i++)
	// 					{
	// 						printf(" ");
	// 					}
	// 					printf("]");
							fflush(stdout);
						//	pthread_mutex_unlock(&g_console_owner_mutex);
						//}
						wmxStatus = GetDeviceStatus(p_device_id, &DeviceStatus, &ConnectionProgressInfo);
						if (WIMAX_API_RET_SUCCESS != wmxStatus) {
							PrintWmxStatus(wmxStatus);
							return 2;
						}
						
						if (DeviceStatus == WIMAX_API_DEVICE_STATUS_Ready) {
							if (g_noNetworksFound == 1) 
							printf("\nNo networks found.\n");
							break;
						}

						if (time_out > SCAN_TIMEOUT_IN_10SEC_ITREATIONS) {
							if (g_noNetworksFound == 1) {
								printf("\nNo networks found.\n");
							} else {
								printf("\nScan Operation timeout.\n");
							// As Scan operation timed out
								ret = 1;
							}
							break;
						}
					} else {
						break;
					}	
				} while (1);
				wmxStatus = GetNetworkList(p_device_id, pNspInfo, &numOfNSPs);
				if (WIMAX_API_RET_SUCCESS != wmxStatus) {
				printf("ERROR: Attempt to connect not successfull - ");
				PrintWmxStatus(wmxStatus);
				free(pNspInfo);
					return 2;
				}
	
				wmxStatus = UnsubscribeNetworkSearch(p_device_id);
				if (WIMAX_API_RET_SUCCESS != wmxStatus) {
					PrintWmxStatus(wmxStatus);
					return 2;
				}

			}			

			
			if (numOfNSPs == 0) {
			printf("No available networks.\n");
				free(profilelist);
				free(pNspInfo);
				return 0;
			}
			for (j = 0; j < numOfNSPs; j++) {
				if ((pNspInfo[j].NSPid & 0xffffff) == profileId) {
					// match with nspid, if there copy the nsp name and send it back
					memcpy(nspInfo, &pNspInfo[j],
					       sizeof(WIMAX_API_NSP_INFO));
					free(pNspInfo);
					free(profilelist);
					return 1;
				}
			}
		}
	}
	// return the proper status of this function

	free(profilelist);
	free(pNspInfo);
	// get the profile list and compare with nspid and return the result

	return 0;
}

/*
 * Function:     GetProfileList
 * Description:  Get the profile list
 * Return:       0 for success or 1 for failure
 */
int wimaxcu_get_profile_list(WIMAX_API_DEVICE_ID_P p_device_id)
{
	WIMAX_API_RET wmxStatus = WIMAX_API_RET_SUCCESS;
	UINT32 numProfileList = MAX_PROFILE;
	int i = 0;

	WIMAX_API_PROFILE_INFO_P profilelist = (WIMAX_API_PROFILE_INFO_P)
	    malloc(sizeof(WIMAX_API_PROFILE_INFO) * MAX_PROFILE);
	memset(profilelist, 0, sizeof(WIMAX_API_PROFILE_INFO) * MAX_PROFILE);

	wmxStatus =
	    GetSelectProfileList(p_device_id, profilelist, &numProfileList);
	if (wmxStatus != WIMAX_API_RET_SUCCESS) {
		PrintWmxStatus(wmxStatus);
		free(profilelist);
		return 1;
	}

	printf("Profile List:\n");
	for (i = 0; i < numProfileList; i++) {
		printf("\tID  : %d\n", profilelist[i].profileID);
		printf("\tName: %s\n", profilelist[i].profileName);
	}

	free(profilelist);
	return 0;
}
int wimaxcu_stop_scan(WIMAX_API_DEVICE_ID_P p_device_id)
{
	WIMAX_API_RET wmxStatus = WIMAX_API_RET_SUCCESS;
	WIMAX_API_DEVICE_STATUS DeviceStatus;
	WIMAX_API_CONNECTION_PROGRESS_INFO ConnectionProgressInfo;
	
	wmxStatus =GetDeviceStatus(p_device_id, &DeviceStatus,&ConnectionProgressInfo);
	if (WIMAX_API_RET_SUCCESS != wmxStatus)
	{
		PrintWmxStatus(wmxStatus);
		return 2;
	}
	if (DeviceStatus == WIMAX_API_DEVICE_STATUS_Scanning)
	{
		
		wmxStatus = CmdStopScan(p_device_id);
		if (WIMAX_API_RET_SUCCESS != wmxStatus) {
			printf("ERROR: Failed to stop scanning.\n");
			return 1;
		}
			
	}
}