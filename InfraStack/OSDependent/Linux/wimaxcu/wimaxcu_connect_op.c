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


int wimaxcu_is_network_activated(WIMAX_API_DEVICE_ID_P p_device_id,
		       WIMAX_API_NSP_INFO_P nspInfo)
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
		return 0;
	}
	for (i = 0; i < numProfileList; i++) {
		// check the match
		if ((nspInfo->NSPid & 0xffffff) == profilelist[i].profileID) {
			free(profilelist);
			return 1;
		}
	}
	free(profilelist);
	// get the profile list and compare with nspid and return the result
	return 0;

}

int wimaxcu_is_network_activated_ex(WIMAX_API_DEVICE_ID_P p_device_id,
			 WIMAX_API_NSP_INFO_EX_P nspInfo)
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
		return 0;
	}
	for (i = 0; i < numProfileList; i++) {
		// check the match
		if ((nspInfo->NSPid & 0xffffff) == profilelist[i].profileID) {
			free(profilelist);
			return 1;
		}
	}
	free(profilelist);
	// get the profile list and compare with nspid and return the result
	return 0;

}

void ind_connect_to_network_callback(WIMAX_API_DEVICE_ID_P pDeviceId,
				 WIMAX_API_NETWORK_CONNECTION_RESP
				 networkConnectionResponse)
{
	switch (networkConnectionResponse) {
	case WIMAX_API_CONNECTION_SUCCESS:
		printf("Connection successful\n");
		if (g_preferred_NSP_ID != 0) 
			SetCurrentPreferredProfiles(pDeviceId,&g_preferred_NSP_ID, 1);	
		break;
	case WIMAX_API_CONNECTION_FAILURE:
		printf("Connection failure\n");
		break;
	default:
		printf("Unknown Connection status\n");
	}
	sem_post(&g_semConnectCompleted);

}

int wimaxcu_connect_with_profile_id(WIMAX_API_DEVICE_ID_P p_device_id, char *profileId_str)
{
	WIMAX_API_RET wmxStatus;
	// int bSuccess = 0;
	WIMAX_API_DEVICE_STATUS DeviceStatus;
	WIMAX_API_CONNECTION_PROGRESS_INFO ConnectionProgressInfo;
	WIMAX_API_CONNECTION_MODE connectMode;
	WIMAX_API_NSP_INFO nspInfo;
	WIMAX_API_PROFILE_ID profileId = 0;
	int ret = 0;

	if ((profileId_str == NULL)) {
		printf("ERROR: Invalid Parameter - missing Profile ID\n");
		return 1;
	}

	wmxStatus =
	    GetDeviceStatus(p_device_id, &DeviceStatus,
			    &ConnectionProgressInfo);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		printf("ERROR: Unable to find Device Status - ");
		PrintWmxStatus(wmxStatus);
		return 1;

	}
	wmxStatus = GetConnectionMode(p_device_id, &connectMode);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		PrintWmxStatus(wmxStatus);
		return 1;
	}
	if (connectMode == WIMAX_API_CONNECTION_AUTO_SCAN_AUTO_CONNECT) {
		printf
		    ("WARNING: The Profile is setup to Auto Connect and Auto Scan, this command would be deferred\n");
		return 1;
	}

	if (DeviceStatus == WIMAX_API_DEVICE_STATUS_Data_Connected) {
		printf
		    ("WARNING: Connection already established!\nPlease disconnect from the current network before attempting to connect.\n");

		return 1;
	}

	if (DeviceStatus != WIMAX_API_DEVICE_STATUS_Ready
	    && DeviceStatus != WIMAX_API_DEVICE_STATUS_Scanning) {
		printf("ERROR: Device is in unknown status - ");
		PrintDeviceStatus(DeviceStatus);

		return 1;
	}

	profileId = atoi(profileId_str);
	// common api get the profile list in their memory
	// We already checked to make sure that device is in
	// scanning or in ready mode, We can get list if any of these modes
	// TODO : Wait here until currecnt scan to complete
	//if (DeviceStatus == WIMAX_API_DEVICE_STATUS_Ready) {
	if (wimaxcu_find_network(p_device_id, profileId, &nspInfo) == 0) {
		printf("ERROR: Network not found. \n");
		return 1;
	}
	//}
	g_preferred_NSP_ID = nspInfo.NSPid;
	// Register to connect complete event
	wmxStatus =
	    SubscribeConnectToNetwork(p_device_id, ind_connect_to_network_callback);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		printf("ERROR: Failed to register callback\n");
		return 1;
	}

	printf("Connecting to %s Network...\n", nspInfo.NSPName);
	wmxStatus = CmdConnectToNetwork(p_device_id, nspInfo.NSPName, 0, 0);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		printf("ERROR: Connection to %s network not successfull\n",
		       nspInfo.NSPName);
		return 1;
	}

	if (wmxcu_sem_timeout(&g_semConnectCompleted, 30 * 1000) == 1) {
		printf("Connection Fail: time out\n");
		return 1;
	}

	wmxStatus = UnsubscribeConnectToNetwork(p_device_id);

	// checking the connection
	//wmxStatus =
	//    GetDeviceStatus(p_device_id, &DeviceStatus, &ConnectionProgressInfo);
	//if (WIMAX_API_RET_SUCCESS != wmxStatus) {
	//      PrintWmxStatus(wmxStatus);
	//ret = 1;
	//} else {
	//      PrintDeviceStatus(DeviceStatus);
	//ret = 0;
	//}

	return ret;
}

int wimaxcu_connect_with_nsp_info(WIMAX_API_DEVICE_ID_P p_device_id,
		       char *str_nspid, int activate)
{
	WIMAX_API_RET wmxStatus;
	char tmp_nspID_str[MAX_NSP_ID_LEN];
	UINT32 numOfNSPs = MAX_DEVICE;
	int time_out = 0;
  	int i = 0;
	int bSuccess = 0;
	WIMAX_API_DEVICE_STATUS DeviceStatus;
	WIMAX_API_CONNECTION_PROGRESS_INFO ConnectionProgressInfo;
	WIMAX_API_CONNECTION_MODE connectMode;
	WIMAX_API_PROFILE_INFO	CurrentPreferredNSPs;
  	//currently the listsize for CurrentPerferredNSPs are 1;
  	UINT32 listsize =1;

	pthread_t userinputthread;
	int ret = 0;
	BOOL wait = TRUE;
	BOOL isEnable =FALSE;
	char *msg =
	    "Waiting for initial provisioning from server...\nPress 'q' to quit.";
	WIMAX_API_NSP_INFO_P pNspInfo =
	    (WIMAX_API_NSP_INFO_P) malloc(MAX_LEN * sizeof(WIMAX_API_NSP_INFO));

	// zero the memory
	memset(pNspInfo, 0, sizeof(WIMAX_API_NSP_INFO) * MAX_LEN);

	do {
		wmxStatus =
		    GetDeviceStatus(p_device_id, &DeviceStatus,
				    &ConnectionProgressInfo);
		if (WIMAX_API_RET_SUCCESS != wmxStatus) {
			printf("ERROR: Attempt to connect not successfull - ");
			PrintWmxStatus(wmxStatus);
			free(pNspInfo);
			return 2;
		}

		if (DeviceStatus == WIMAX_API_DEVICE_STATUS_Data_Connected) {
			printf
			    ("WARNING: Connection already established!\nPlesae disconnect from the current network before attempting to connect\n");
			free(pNspInfo);
			return 1;
		}

		if (DeviceStatus != WIMAX_API_DEVICE_STATUS_Ready
		    && DeviceStatus != WIMAX_API_DEVICE_STATUS_Scanning) {
			printf("ERROR: Attempt to connect not successfull - ");
			PrintDeviceStatus(DeviceStatus);
			free(pNspInfo);
			return 2;
		}

		wmxStatus = GetConnectionMode(p_device_id, &connectMode);
		if (WIMAX_API_RET_SUCCESS != wmxStatus) {
			PrintWmxStatus(wmxStatus);
			return 2;
		}
		wmxStatus =GetCurrentPreferredProfiles(p_device_id,&CurrentPreferredNSPs,&listsize);
		if (WIMAX_API_RET_SUCCESS != wmxStatus) {
	   		PrintWmxStatus(wmxStatus);
			return 2;
		}
		if(CurrentPreferredNSPs.profileID!=0){
		
			printf("Current Preferred Profile is:\n");	;
			printf("\tID  : %d\n",CurrentPreferredNSPs.profileID);
			printf("\tName: %s\n",CurrentPreferredNSPs.profileName);
		}

		if ((DeviceStatus == WIMAX_API_DEVICE_STATUS_Ready)
		    && connectMode ==
		    WIMAX_API_CONNECTION_MANUAL_SCAN_MANUAL_CONNECT) {
			printf
			    ("In Manual Scan and Manual Connect Mode\nTrying to find the networks ...\n");
			wmxStatus =
			    SubscribeNetworkSearch(p_device_id,
						   &ind_network_search_cb);
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
					//   if (pthread_mutex_trylock(&g_console_owner_mutex) == 0) {
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
						  // pthread_mutex_unlock(&g_console_owner_mutex);
					  // }
					   wmxStatus = GetDeviceStatus(p_device_id, &DeviceStatus, &ConnectionProgressInfo);
					   if (WIMAX_API_RET_SUCCESS != wmxStatus) {
						   PrintWmxStatus(wmxStatus);
						   return 2;
					   }
// 				if (DeviceStatus == WIMAX_API_DEVICE_STATUS_Scanning) {
					   // 					
// 				} else {
// 					printf("1No networks found.\n");
// 					break;
// 				}

					   if (time_out > SCAN_TIMEOUT_IN_10SEC_ITREATIONS) {
						   if (g_noNetworksFound == 1) {
							   printf("\n No networks found.\n");
						   } else {
							   printf("\n Scan Operation timeout.\n");
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

		} else if ((DeviceStatus == WIMAX_API_DEVICE_STATUS_Ready)
			   || (DeviceStatus ==
			       WIMAX_API_DEVICE_STATUS_Scanning)) {
			wmxStatus =
			    GetNetworkList(p_device_id, pNspInfo, &numOfNSPs);
			if (WIMAX_API_RET_SUCCESS != wmxStatus) {
				printf
				    ("ERROR: Attempt to connect not successfull - ");
				PrintWmxStatus(wmxStatus);
				free(pNspInfo);
				return 2;
			}

		}
		if (numOfNSPs == 0) {
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
					   if (pthread_mutex_trylock(&g_console_owner_mutex) == 0) {
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
						   pthread_mutex_unlock(&g_console_owner_mutex);
					   }
					   wmxStatus = GetDeviceStatus(p_device_id, &DeviceStatus, &ConnectionProgressInfo);
					   if (WIMAX_API_RET_SUCCESS != wmxStatus) {
						   PrintWmxStatus(wmxStatus);
						   return 2;
					   }
// 				if (DeviceStatus == WIMAX_API_DEVICE_STATUS_Scanning) {
					   // 					
// 				} else {
// 					printf("1No networks found.\n");
// 					break;
// 				}

					   if (time_out > SCAN_TIMEOUT_IN_10SEC_ITREATIONS) {
						   if (g_noNetworksFound == 1) {
							   printf("\n No networks found.\n");
						   } else {
							   printf("\n Scan Operation timeout.\n");
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
			printf
			    ("Attempt to connect not successfull - No available networks\n");
			free(pNspInfo);
			return 1;
		} else {
			wait = FALSE;
		}

		// We should not be polling to get an update on the device state but rely on callback..
		// for now we will sleep in between to give the device some time to do work...
		sleep(1);
	} while (wait == TRUE);

	for (i = 0; i < numOfNSPs; i++) {
		sprintf(tmp_nspID_str, "%d", pNspInfo[i].NSPid);
		if (!strcmp(tmp_nspID_str, str_nspid)) {
			// check the network is activated or not
				
			if (activate) {
				if (sem_init(&g_semAPDOactivation, 0, 0)
					== -1) {
					//Semaphore could not be initialized.
					printf
						("ERROR: Activation Failed - Internal failure\n");
					free(pNspInfo);
					return 2;
				}
				printf
					("INFO: Network is Not Activated.\nStarting the Activation Process...\n");
				wmxStatus =
					register_apdo_cb(p_device_id);
				if (WIMAX_API_RET_SUCCESS != wmxStatus) {
					printf
						("ERROR: Activation Failed - ");
					PrintWmxStatus(wmxStatus);
					free(pNspInfo);
					return 2;
				}
				wmxStatus =
					register_puma_cb(p_device_id);
				if (WIMAX_API_RET_SUCCESS != wmxStatus) {
					printf
						("ERROR: Activation Failed - ");
					PrintWmxStatus(wmxStatus);
					free(pNspInfo);
					return 2;
				}
				// copy to global variable to launch again
				strcpy(g_sznspName,
					pNspInfo[i].NSPName);
			}


			g_preferred_NSP_ID = pNspInfo[i].NSPid;
			// Register to connect complete event
			wmxStatus =
			    SubscribeConnectToNetwork(p_device_id,
						      ind_connect_to_network_callback);
			if (WIMAX_API_RET_SUCCESS != wmxStatus) {
				printf("ERROR: Failed to register callback\n");
				free(pNspInfo);
				return 1;
			}
			wmxStatus =GetConnectedAsCurrentPreferredCapabilityStatus(p_device_id, &isEnable);
			if (wmxStatus == WIMAX_API_RET_SUCCESS) {
				if (isEnable == FALSE) {			
					isEnable=TRUE;
					wmxStatus = SetConnectedAsCurrentPreferredCapabilityStatus(p_device_id,isEnable );
					if (wmxStatus != WIMAX_API_RET_SUCCESS) {
						printf("Failed to set preferred settings before connecting\n");
					}
				}
			}
			printf("Connecting to %s Network...\n",
			       pNspInfo[i].NSPName); 
			    CmdConnectToNetwork(p_device_id,
						pNspInfo[i].NSPName, 0, 0);
			if (WIMAX_API_RET_SUCCESS != wmxStatus) {
				printf
				    ("ERROR: Connection to %s network not successfull\n",
				     pNspInfo[i].NSPName);
				free(pNspInfo);
				return 1;
			}
			if (wmxcu_sem_timeout(&g_semConnectCompleted, 30 * 1000)
			    == 1) {
				printf("Connection Fail: time out\n");
				free(pNspInfo);
				return 1;
			}
			wmxStatus = UnsubscribeConnectToNetwork(p_device_id);

			if (activate) {
				// spin the thread
				ret =
				    pthread_create(&userinputthread, NULL,
						   user_info, (void *)msg);
				if (wmxcu_sem_timeout
				    (&g_semAPDOactivation, 90 * 1000) == 1)
					printf
					    ("ERROR: Activation Server Not Responding (Time Out)\n");

				wmxStatus = unregister_apdo_cb(p_device_id);
				if (WIMAX_API_RET_SUCCESS != wmxStatus) {
					PrintWmxStatus(wmxStatus);
					free(pNspInfo);
					return 2;
				}
				wmxStatus = unregister_puma_cb(p_device_id);
				if (WIMAX_API_RET_SUCCESS != wmxStatus) {
					PrintWmxStatus(wmxStatus);
					free(pNspInfo);
					return 2;
				}
				pthread_cancel(userinputthread);
			}
			// checking the connection
			//wmxStatus = GetDeviceStatus(p_device_id, &DeviceStatus, &ConnectionProgressInfo);
			//if (WIMAX_API_RET_SUCCESS != wmxStatus)
			//  {
			//PrintWmxStatus(wmxStatus);
			//  }
			//else
			//  {
			//  PrintDeviceStatus(DeviceStatus);
			//  }

			bSuccess = 1;
		}
		if (bSuccess == 1)
			break;
	}

	if (!bSuccess) {
		printf
		    ("WARNING: Network ID did not match with the known list.\n");
		free(pNspInfo);
		return 1;
	}

	free(pNspInfo);
	return 0;
}

/*
 * Function:     Disconnect
 * Description:  Disconnect from the currently connected network
 */
int wimaxcu_disconnect(WIMAX_API_DEVICE_ID_P p_device_id)
{
	WIMAX_API_RET wmxStatus;
	WIMAX_API_DEVICE_STATUS DeviceStatus;
	WIMAX_API_CONNECTION_PROGRESS_INFO ConnectionProgressInfo;
	WIMAX_API_CONNECTION_MODE connectMode;

	wmxStatus =
	    GetDeviceStatus(p_device_id, &DeviceStatus,
			    &ConnectionProgressInfo);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		PrintWmxStatus(wmxStatus);
		return 2;
	}

	if (DeviceStatus != WIMAX_API_DEVICE_STATUS_Data_Connected) {
		printf("WARNING: Network already disconnected.\n");
		return 1;
	}
	// Get current connection mode
	wmxStatus = GetConnectionMode(p_device_id, &connectMode);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		PrintWmxStatus(wmxStatus);
		return 2;
	}

	if (connectMode == WIMAX_API_CONNECTION_SEMI_MANUAL_SCAN_AUTO_CONNECT
	    || connectMode == WIMAX_API_CONNECTION_AUTO_SCAN_AUTO_CONNECT) {
		ConvertCharToConnectionMode
		    (CMD_STR_MODE_ARGS_CONNECT_OPT_MANUAL, NULL, &connectMode);
		wmxStatus = SetConnectionMode(p_device_id, connectMode);
		if (WIMAX_API_RET_SUCCESS != wmxStatus) {
			PrintWmxStatus(wmxStatus);
			printf
			    ("ERROR: Changing connect mode to manual unsuccessfull\n");
			return 2;
		}
		printf("WARNING: Connect mode is now changed to manual\n");
	}

	wmxStatus = CmdDisconnectFromNetwork(p_device_id);
	if (wmxStatus != WIMAX_API_RET_SUCCESS) {
		PrintWmxStatus(wmxStatus);
		return 1;
	}

	printf("Network Disconnected.\n");
	return 0;
}

/*
 * Function:     Activate
 * Description:  Connect to un-activated network
 */
int wimaxcu_activate(WIMAX_API_DEVICE_ID_P p_device_id, char *str_nspid)
{
	if (str_nspid == NULL) {
		printf("ERROR: Network ID is not valid\n");
		return 1;
	}

	return wimaxcu_connect_with_nsp_info(p_device_id, str_nspid, 1);
}

/*
 * Function:     Deactivate
 * Description:  Deactivate already activated network
 */
int wimaxcu_deactivate(WIMAX_API_DEVICE_ID_P p_device_id, char *str_nspid)
{
	WIMAX_API_RET wmxStatus = WIMAX_API_RET_SUCCESS;
	int nspid = atoi(str_nspid);
	wmxStatus = CmdDeprovisionProfile(p_device_id, nspid);
	if (wmxStatus != WIMAX_API_RET_SUCCESS) {
		printf("ERROR: Profile Deactivate unsuccessfull\n");
		PrintWmxStatus(wmxStatus);
		return 1;
	}

	printf("Profile is Deactivated.\n");
	return 0;
}
