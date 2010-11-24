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
#include <pthread.h>
#include <unistd.h>
#include <limits.h>
#include <sys/time.h>

#define _XOPEN_SOURCE 600
#include <semaphore.h>
#include <sys/types.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <string.h>

#include <signal.h>
#include <execinfo.h>
#include <sys/types.h>
#include <sys/syslog.h>
#include <unistd.h>
#include <dirent.h>
#include <ctype.h>

#include "wimaxcu_defs.h"

#include "wimaxcu.h"
#include "wimaxcu_util.h"
// Globals...

#define MAX_DEVICE			5
#define MAX_PROFILE			32
#define MAX_LEN				80
#define WMX_SF_STATUS_MAX_NUM		100
#define VERSION_SDK_STR_MAX_SIZE	255
#define MAX_NSP_ID_LEN                  40

// used in Scan process
// Waits SCAN_TIMEOUT_IN_10SEC_ITREATIONS * 10 sec before time out
// Default value is SCAN_TIMEOUT_IN_10SEC_ITREATIONS 30 = 300 sec = 5 min
// can be modified depending upon the no of frequencies available
#define SCAN_TIMEOUT_IN_10SEC_ITREATIONS 60

/* get REG_EIP from ucontext.h */
#define __USE_GNU
#include <ucontext.h>

#define MAX_STR_LEN 256
#define MAX_FILENAME_LEN 256
	
WIMAX_API_DEVICE_ID DeviceID;

//static sem_t semWideScan;
static sem_t semConnectionUtility;
static sem_t semAPDOactivation;
static sem_t semAPDOupdates;
static sem_t semRfState;
static sem_t semConnectCompleted;
static pthread_mutex_t console_owner_mutex;
// static BOOL g_UpaterLaunched = FALSE;

static WIMAX_API_DEVICE_STATUS g_devState;

static char g_sznspName[MAX_SIZE_OF_NSP_NAME];
static char foOperationType[NAME_MAX];
// for user command for activation
void *userinfo(void *ptr);
// time out sem function
int wmxcu_sem_timeout(sem_t* s,int milliseconds);

int g_noNetworksFound = 1;
int g_searchProgress = 0;

// Set preferred NSP
int preferred_NSP_ID = 0;

static char gcLogFilePathName[MAX_FILENAME_LEN];


/*
 * Function:     Initialize
 * Description:  Initialize the WiMAX CommonAPI
 */
WIMAX_API_RET Initialize (WIMAX_API_DEVICE_ID_P pDeviceID)
{
	WIMAX_API_RET wmxStatus;
	WIMAX_API_HW_DEVICE_ID HwDeviceIdList[MAX_DEVICE];
	UINT32 numDevice = MAX_DEVICE;

	memset(HwDeviceIdList, 0, sizeof(WIMAX_API_HW_DEVICE_ID) * MAX_DEVICE);

	// open the Common API and initialize iwmax sdk, agents
    wmxStatus = WiMaxAPIOpen(pDeviceID);
	if (WIMAX_API_RET_SUCCESS != wmxStatus)
    {
        return wmxStatus;
	}

	// get the list of the device before open the device
	wmxStatus = GetListDevice(pDeviceID,
                              (WIMAX_API_HW_DEVICE_ID_P)HwDeviceIdList,
                              &numDevice);
	if (WIMAX_API_RET_SUCCESS != wmxStatus)
    {
		return wmxStatus;
	}

	pDeviceID->deviceIndex = HwDeviceIdList[0].deviceIndex;

	// Open the device to get the permission
	wmxStatus = WiMaxDeviceOpen(pDeviceID);
	if (WIMAX_API_RET_SUCCESS != wmxStatus)
    {
		return wmxStatus;
	}
	if (pthread_mutex_init(&console_owner_mutex, NULL) != 0) {
		printf("Internal Error!\n");
		return WIMAX_API_RET_FAILED;
	}

	if (sem_init(&semConnectionUtility, 0, 0) == -1) {
		printf("Internal Error!\n");
	return WIMAX_API_RET_FAILED;
	}

	if (sem_init(&semRfState, 0, 0) == -1) {
		printf("Internal Error!\n");
	return WIMAX_API_RET_FAILED;
	}

        if (sem_init(&semConnectCompleted, 0, 0) == -1) {
            printf("Internal Error!\n");
            return WIMAX_API_RET_FAILED;
        }

	wmxStatus = SubscribeDeviceStatusChange(pDeviceID, &IndDeviceUpdateCB);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
      		PrintWmxStatus(wmxStatus);
      		return WIMAX_API_RET_FAILED;
    	}

    return WIMAX_API_RET_SUCCESS;
}

/*
 * Function:     Finalize
 * Description:  Finalize the WiMAX CommonAPI
 */
void Finalize(WIMAX_API_DEVICE_ID_P pDeviceID)
{
	UnsubscribeDeviceStatusChange(pDeviceID);

    	WiMaxDeviceClose(pDeviceID);
    	WiMaxAPIClose(pDeviceID);

	// Let all the call backs get closed before destroying sem
	sem_destroy(&semConnectionUtility);
	sem_destroy(&semRfState);
        sem_destroy(&semConnectCompleted);
	pthread_mutex_destroy(&console_owner_mutex);

}



/*
 * Function:     ResetDevice
 * Description:  Reset the wimax device
 * Return:       0 for success or 1 for failure
 *
 * Note: this will return 1 always for now since not implemented
 */
int ResetDevice(WIMAX_API_DEVICE_ID_P pDeviceID)
{
	WIMAX_API_RET wmxStatus;

	wmxStatus = CmdResetWimaxDevice(pDeviceID);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
        	PrintWmxStatus(wmxStatus);
		return 1;
	}
	return 0;
}

/*
 * Function:     ResetToFactorySettings
 * Description:  Reset to the factory default setting
 * Return:       0 for success or 1 for failure
 */
int ResetToFactorySettings(WIMAX_API_DEVICE_ID_P pDeviceID)
{
	WIMAX_API_RET wmxStatus;
	WIMAX_API_DEVICE_STATUS DeviceStatus;
	WIMAX_API_CONNECTION_PROGRESS_INFO ConnectionProgressInfo;
               
	wmxStatus = GetDeviceStatus(pDeviceID, &DeviceStatus, &ConnectionProgressInfo);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		PrintWmxStatus(wmxStatus);
		return 1;
	}

	if (DeviceStatus != WIMAX_API_DEVICE_STATUS_RF_OFF_SW) {
		printf("WARNING!! The radio must be turned off to reset to factory setting.\n");
		printf("          This operation will erase previously stored scanned results\n");
		printf("          and you will lose the ability to connect to the preferred NSP.\n");
		return 1;
	}
	
	wmxStatus = CmdResetToFactorySettings(pDeviceID);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		PrintWmxStatus(wmxStatus);
		return 1;
	}

	printf("WiMAX system is set to factory settings.\n");
	return 0;
}

/*
 * Function:     GetUserConnectMode
 * Description:  Get the user connection mode
 * Return:       0 for success or 1 for failure
 */
int GetUserConnectMode(WIMAX_API_DEVICE_ID_P pDeviceID)
{
    WIMAX_API_CONNECTION_MODE connectMode;
	WIMAX_API_RET wmxStatus;

    wmxStatus = GetConnectionMode(pDeviceID,&connectMode);
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
int SetUserConnectMode(WIMAX_API_DEVICE_ID_P pDeviceID,
			char *connect_mode, char *scan_mode)
{
	int ret;
	WIMAX_API_RET wmxStatus;
	WIMAX_API_CONNECTION_MODE userConnectMode, currentConnectMode;
	WIMAX_API_DEVICE_STATUS DeviceStatus;
	WIMAX_API_CONNECTION_PROGRESS_INFO ConnectionProgressInfo;

    wmxStatus = GetConnectionMode(pDeviceID, &currentConnectMode);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
        PrintWmxStatus(wmxStatus);
	return 1;
	}

    userConnectMode = currentConnectMode;
    ret = ConvertCharToConnectionMode(connect_mode, scan_mode, &userConnectMode);
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

    if(userConnectMode == currentConnectMode) {
        printf("The specified connect mode is already in place.\n");
        PrintUserConnectionMode(currentConnectMode);
	return 1;
    }

	wmxStatus = SetConnectionMode(pDeviceID,userConnectMode);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		// PrintWmxStatus(wmxStatus);
		if (WIMAX_API_RET_FAILED == wmxStatus) {
			BOOL isEnable;
			wmxStatus = GetConnectedAsCurrentPreferredCapabilityStatus(pDeviceID, &isEnable);
			if(wmxStatus==WIMAX_API_RET_SUCCESS)
			{
				if (isEnable == FALSE)
				{
					printf("Current Connected Network Preferred settings are disabled\n");
					printf("Hence could not set the connect mode to Auto \n");
					printf("Going back to the pprevious connect mode \n");
					wmxStatus = SetConnectionMode(pDeviceID,currentConnectMode);
					if (WIMAX_API_RET_SUCCESS != wmxStatus)
					{
						PrintWmxStatus(wmxStatus);
					}
					else
					{
						PrintUserConnectionMode(currentConnectMode);
					}
					return 1;
				}
				else
				{
					printf("Operation Failed \n");
					return 1;
				}
			}
		}
		PrintWmxStatus(wmxStatus);
		return 1;
	}

    // Unset the preferred NSP
    if(userConnectMode == WIMAX_API_CONNECTION_MANUAL_SCAN_MANUAL_CONNECT) {
	preferred_NSP_ID = 0;
	SetCurrentPreferredProfiles(pDeviceID, &preferred_NSP_ID, 0);
    }
    PrintUserConnectionMode(userConnectMode);
    if (ret == 1 ) {
	wmxStatus =
	    GetDeviceStatus(pDeviceID, &DeviceStatus, &ConnectionProgressInfo);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		PrintWmxStatus(wmxStatus);
	    return 2;
	}
	switch (DeviceStatus) {
    		case WIMAX_API_DEVICE_STATUS_RF_OFF_HW_SW:
	        printf("WARNING: Both HW and SW Radio is OFF.\n");
		break;
		case WIMAX_API_DEVICE_STATUS_RF_OFF_HW:
		printf("WARNING: HW Radio is OFF.\n");
		break;
		case WIMAX_API_DEVICE_STATUS_RF_OFF_SW:
        	printf("WARNING: SW Radio is OFF.\n");
		break;
	default:
	break;
	}
    }
    return 0;
}

/*
 * Function:     GetSystemStatus
 * Description:  Get the WiMAX device status from the GetDeviceStatus API
 * Return:       0 for success or 1 for failure
 */
int GetSystemStatus(WIMAX_API_DEVICE_ID_P pDeviceID)
{
	WIMAX_API_RET wmxStatus;
	WIMAX_API_DEVICE_STATUS DeviceStatus;
	WIMAX_API_CONNECTION_PROGRESS_INFO ConnectionProgressInfo;

	wmxStatus =
	    GetDeviceStatus(pDeviceID, &DeviceStatus, &ConnectionProgressInfo);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		PrintWmxStatus(wmxStatus);
	return 1;
	}

	PrintDeviceStatus(DeviceStatus);
    return 0;
}


/*
 * Function:     GetConnectStatus
 * Description:  Get the current connection status of WiMAX Device
 * Return:       0 for success or 1 for failure
 */
int GetConnectStatus(WIMAX_API_DEVICE_ID_P pDeviceID)
{
	WIMAX_API_RET wmxStatus;
	WIMAX_API_DEVICE_STATUS DeviceStatus;
	WIMAX_API_CONNECTION_PROGRESS_INFO ConnectionProgressInfo;

	wmxStatus =
	    GetDeviceStatus(pDeviceID, &DeviceStatus, &ConnectionProgressInfo);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		PrintWmxStatus(wmxStatus);
	return 1;
	}

	PrintDeviceStatus(DeviceStatus);

    // if connected or idle, display connected NSP info
    if (DeviceStatus == WIMAX_API_DEVICE_STATUS_Data_Connected)
    {
        GetConnNSP(pDeviceID);
        GetConnTime(pDeviceID);
    }

    return 0;
}

/*
 * Function:     GetRfStatus
 * Description:  Get WiMAX radio status
 * Return:       0 for success or 1 for failure
 */
int GetRfStatus(WIMAX_API_DEVICE_ID_P pDeviceID)
{
	WIMAX_API_RET wmxStatus;
	WIMAX_API_DEVICE_STATUS DeviceStatus;
	WIMAX_API_CONNECTION_PROGRESS_INFO ConnectionProgressInfo;

	wmxStatus =
	    GetDeviceStatus(pDeviceID, &DeviceStatus, &ConnectionProgressInfo);
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

int IsNetworkActivated(WIMAX_API_DEVICE_ID_P pDeviceID,
		       WIMAX_API_NSP_INFO_P nspInfo)
{
	WIMAX_API_RET wmxStatus = WIMAX_API_RET_SUCCESS;
	UINT32 numProfileList = MAX_PROFILE;
	int i = 0;
	WIMAX_API_PROFILE_INFO_P  profilelist= (WIMAX_API_PROFILE_INFO_P)
			malloc(sizeof(WIMAX_API_PROFILE_INFO)*MAX_PROFILE);
	memset(profilelist,0,sizeof(WIMAX_API_PROFILE_INFO)*MAX_PROFILE);

	wmxStatus = GetSelectProfileList(pDeviceID,profilelist,&numProfileList);
	if ( wmxStatus != WIMAX_API_RET_SUCCESS )
	{
		PrintWmxStatus(wmxStatus);
		free (profilelist);
		return 0;
	}
	for ( i = 0; i < numProfileList; i++)
	{
        // check the match
        if  ((nspInfo->NSPid & 0xffffff) == profilelist[i].profileID )
        {
            free (profilelist);
            return 1;
        }
    }
	free (profilelist);
	// get the profile list and compare with nspid and return the result
	return 0;

}
int IsNetworkActivatedEx(WIMAX_API_DEVICE_ID_P pDeviceID,
		       WIMAX_API_NSP_INFO_EX_P nspInfo)
{
	WIMAX_API_RET wmxStatus = WIMAX_API_RET_SUCCESS;
	UINT32 numProfileList = MAX_PROFILE;
	int i = 0;
	WIMAX_API_PROFILE_INFO_P  profilelist= (WIMAX_API_PROFILE_INFO_P)
			malloc(sizeof(WIMAX_API_PROFILE_INFO)*MAX_PROFILE);
	memset(profilelist,0,sizeof(WIMAX_API_PROFILE_INFO)*MAX_PROFILE);

	wmxStatus = GetSelectProfileList(pDeviceID,profilelist,&numProfileList);
	if ( wmxStatus != WIMAX_API_RET_SUCCESS )
	{
		PrintWmxStatus(wmxStatus);
		free (profilelist);
		return 0;
	}
	for ( i = 0; i < numProfileList; i++)
	{
        // check the match
		if  ((nspInfo->NSPid & 0xffffff) == profilelist[i].profileID )
		{
			free (profilelist);
			return 1;
		}
	}
	free (profilelist);
	// get the profile list and compare with nspid and return the result
	return 0;

}

int GetNListEx(WIMAX_API_DEVICE_ID_P pDeviceID, CMD_ARGS scan_mode)
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
	wmxStatus = GetDeviceStatus(pDeviceID, &DeviceStatus, &ConnectionProgressInfo);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		PrintWmxStatus(wmxStatus);
		return 2;
	}

	switch(DeviceStatus) {
	case WIMAX_API_DEVICE_STATUS_UnInitialized:  /**<  Device is uninitialized */
	  printf("ERROR: Device not Initialized\n");
	return 2;
	case WIMAX_API_DEVICE_STATUS_RF_OFF_HW_SW:   /**<  Device RF Off(both H/W and S/W) */
	printf
	    ("WARNING: HW and SW Radios are OFF.\nPlease turn ON the HW and SW Radios to perform a scan.\n");
	return 2;
	case WIMAX_API_DEVICE_STATUS_RF_OFF_HW:      /**<  Device RF Off(via H/W switch) */
	printf
	    ("WARNING: HW Radio is OFF.\nPlease turn ON the HW Radio to perform a scan.\n");
	return 2;
	case WIMAX_API_DEVICE_STATUS_RF_OFF_SW:      /**<  Device RF Off(via S/W switch) */
	printf
	    ("WARNING: SW Radio is OFF.\nPlease turn ON the SW Radio to perform a scan.\n");
	return 2;
	case WIMAX_API_DEVICE_STATUS_Ready:          /**<  Device is ready */
	case WIMAX_API_DEVICE_STATUS_Scanning:       /**<  Device is scanning */
	  break;
	case WIMAX_API_DEVICE_STATUS_Connecting:     /**<  Connection in progress */
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



	wmxStatus =
			SubscribeRfTaken(pDeviceID,&IndRFTakenCB);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		PrintWmxStatus(wmxStatus);
		return 2;
	}
	wmxStatus = GetConnectionMode(pDeviceID,&connectMode);
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

			   wmxStatus = SubscribeNetworkSearchEx(pDeviceID,&IndNetworkSearchCBEx );
			   if (WIMAX_API_RET_SUCCESS != wmxStatus) {
				   PrintWmxStatus(wmxStatus);
				   return 2;
			   }
			   /* In Manual mode always scan do not read the cache as we don't know when cache was updated */
			   if (connectMode != WIMAX_API_CONNECTION_MANUAL_SCAN_MANUAL_CONNECT) {
				   pNspInfo = (WIMAX_API_NSP_INFO_EX_P )malloc(MAX_LEN * sizeof(WIMAX_API_NSP_INFO_EX));
				   memset(pNspInfo, 0, sizeof(WIMAX_API_NSP_INFO_EX) * MAX_LEN);
				   wmxStatus = GetNetworkListEx(pDeviceID, pNspInfo, &numOfNSPs);
				   if (WIMAX_API_RET_SUCCESS != wmxStatus) {
					   PrintWmxStatus(wmxStatus);
				/*
					   If the Device is already scanning, it won't allow one more AppSrv will reject it
					   with the Operation Falied error
				*/
					   free(pNspInfo);
					   return 1;
				   }

				   if(numOfNSPs != 0) {
					   for (i = 0; i < numOfNSPs; i++)
					   {
						   printf("\nNetwork found.\n");
						   PrintNSPInfoEx(&pNspInfo[i]);
						   if  (IsNetworkActivatedEx(pDeviceID,&pNspInfo[i]) )
							   printf("\tActivated\n");
						   else
							   printf("\tNot Activated\n");
					   }
					   return 0;
				   }
			   }

			   wmxStatus = CmdNetworkSearch(pDeviceID);

			   if (WIMAX_API_RET_SUCCESS != wmxStatus) {
				   PrintWmxStatus(wmxStatus);
				   if ((DeviceStatus == WIMAX_API_DEVICE_STATUS_Scanning) && (wmxStatus == WIMAX_API_RET_FAILED)) {
					   printf("WARNING: Scanning is in progress\nPlease wait for the current scan to complete.\n");
				   }
				   return 1;
			   }

			   printf("Scanning %2d%% Done ", g_searchProgress);
			   fflush(stdout);
			   do {
				   if (wmxcu_sem_timeout(&semConnectionUtility,5*1000) == 1 )
				   {
					   time_out++;
					   if (pthread_mutex_trylock(&console_owner_mutex) == 0) {
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
						   pthread_mutex_unlock(&console_owner_mutex);
					   }
					   wmxStatus = GetDeviceStatus(pDeviceID, &DeviceStatus, &ConnectionProgressInfo);
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

		   } else if (scan_mode == CMD_SCAN_ARG_WIDE) {

			   wmxStatus =SubscribeNetworkSearchWideScanEx(pDeviceID,
					   &IndNetworkSearchWideScanCBEx);
			   if (WIMAX_API_RET_SUCCESS != wmxStatus) {
				   PrintWmxStatus(wmxStatus);
				   return 2;
			   }

		// Display the warning message:
			   printf("WARNING: Wide scan may take upto 2 minutes... \n");
			   wmxStatus = CmdNetworkSearchWideScan(pDeviceID);
			   if (WIMAX_API_RET_SUCCESS != wmxStatus) {
				   PrintWmxStatus(wmxStatus);
			/*
				   If the Device is already scanning, it won't allow one more AppSrv will reject it
				   with the Operation Falied wrror
			*/
				   if ((DeviceStatus == WIMAX_API_DEVICE_STATUS_Scanning) && (wmxStatus == WIMAX_API_RET_FAILED)) {
					   printf("WARNING: Scanning is in progress\nPlease wait for the current scan to complete.\n ");

				   }
				   return 1;
			   }

			   if (wmxcu_sem_timeout(&semConnectionUtility,120*1000) == 1 )
				   printf("No networks found.\n");
		   }
		   wmxStatus = UnsubscribeRfTaken(pDeviceID);
		   if (WIMAX_API_RET_SUCCESS != wmxStatus) {
			   PrintWmxStatus(wmxStatus);
			   return 2;
		   }
		   wmxStatus = UnsubscribeNetworkSearchEx(pDeviceID);
		   if (WIMAX_API_RET_SUCCESS != wmxStatus) {
			   PrintWmxStatus(wmxStatus);
			   return 2;
		   }
		   wmxStatus = UnsubscribeNetworkSearchWideScanEx(pDeviceID);
		   if (WIMAX_API_RET_SUCCESS != wmxStatus) {
			   PrintWmxStatus(wmxStatus);
			   return 2;
		   }
		   return ret;
}



/*
Function:
GetNetworkList(WIMAX_API_DEVICE_ID_P pDeviceID)

Purpose:
This API casuses the device to perform a scan operation and returns a list of  detected NSPs.
This is a blocking API. It returns to the caller after a single  full scan cycle is completed.

Parameters:
WIMAX_API_DEVICE_ID_P pDeviceID - device info like device index, permission etc
*/
int GetNList(WIMAX_API_DEVICE_ID_P pDeviceID, CMD_ARGS scan_mode)
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
    	wmxStatus = GetDeviceStatus(pDeviceID, &DeviceStatus, &ConnectionProgressInfo);
    	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
        	PrintWmxStatus(wmxStatus);
	return 2;
    	}

	switch(DeviceStatus) {
	case WIMAX_API_DEVICE_STATUS_UnInitialized:  /**<  Device is uninitialized */
	  printf("ERROR: Device not Initialized\n");
	return 2;
	case WIMAX_API_DEVICE_STATUS_RF_OFF_HW_SW:   /**<  Device RF Off(both H/W and S/W) */
	printf
	    ("WARNING: HW and SW Radios are OFF.\nPlease turn ON the HW and SW Radios to perform a scan.\n");
	return 2;
	case WIMAX_API_DEVICE_STATUS_RF_OFF_HW:      /**<  Device RF Off(via H/W switch) */
	printf
	    ("WARNING: HW Radio is OFF.\nPlease turn ON the HW Radio to perform a scan.\n");
	return 2;
	case WIMAX_API_DEVICE_STATUS_RF_OFF_SW:      /**<  Device RF Off(via S/W switch) */
	printf
	    ("WARNING: SW Radio is OFF.\nPlease turn ON the SW Radio to perform a scan.\n");
	return 2;
	case WIMAX_API_DEVICE_STATUS_Ready:          /**<  Device is ready */
	case WIMAX_API_DEVICE_STATUS_Scanning:       /**<  Device is scanning */
	  break;
	case WIMAX_API_DEVICE_STATUS_Connecting:     /**<  Connection in progress */
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


	wmxStatus =
	SubscribeRfTaken(pDeviceID,&IndRFTakenCB);
    	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
      		PrintWmxStatus(wmxStatus);
		return 2;
    	}
 	wmxStatus = GetConnectionMode(pDeviceID,&connectMode);
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
		wmxStatus = SubscribeNetworkSearch(pDeviceID,&IndNetworkSearchCB );
			if (WIMAX_API_RET_SUCCESS != wmxStatus) {
				PrintWmxStatus(wmxStatus);
			return 2;
			}
		/* In Manual mode always scan do not read the cache as we don't know when cache was updated */
		if (connectMode != WIMAX_API_CONNECTION_MANUAL_SCAN_MANUAL_CONNECT) {
        		pNspInfo = (WIMAX_API_NSP_INFO_P )malloc(MAX_LEN * sizeof(WIMAX_API_NSP_INFO));
        		memset(pNspInfo, 0, sizeof(WIMAX_API_NSP_INFO) * MAX_LEN);
        		wmxStatus = GetNetworkList(pDeviceID, pNspInfo, &numOfNSPs);
        		if (WIMAX_API_RET_SUCCESS != wmxStatus) {
            			PrintWmxStatus(wmxStatus);
				/*
				 If the Device is already scanning, it won't allow one more AppSrv will reject it
				 with the Operation Falied error
				*/
        			free(pNspInfo);
		return 1;
        		}

        		if(numOfNSPs != 0) {
            			for (i = 0; i < numOfNSPs; i++)
            			{
						   printf("\nNetwork found.\n");
                			PrintNSPInfo(&pNspInfo[i]);
                			if  (IsNetworkActivated(pDeviceID,&pNspInfo[i]) )
                    				printf("\tActivated\n");
                			else
                    				printf("\tNot Activated\n");
            			}
		return 0;
        		}
  		}

		wmxStatus = CmdNetworkSearch(pDeviceID);

		if (WIMAX_API_RET_SUCCESS != wmxStatus) {
			PrintWmxStatus(wmxStatus);
			if ((DeviceStatus == WIMAX_API_DEVICE_STATUS_Scanning) && (wmxStatus == WIMAX_API_RET_FAILED)) {
					printf("WARNING: Scanning is in progress\nPlease wait for the current scan to complete.\n");
			}
			return 1;
		}

			   printf("Scanning %2d%% Done ", g_searchProgress);
			   fflush(stdout);
			   do {
				   if (wmxcu_sem_timeout(&semConnectionUtility,5*1000) == 1 )
				   {
					   time_out++;
					   if (pthread_mutex_trylock(&console_owner_mutex) == 0) {
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
						   pthread_mutex_unlock(&console_owner_mutex);
					   }
					   wmxStatus = GetDeviceStatus(pDeviceID, &DeviceStatus, &ConnectionProgressInfo);
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

    } else if (scan_mode == CMD_SCAN_ARG_WIDE) {
			   // Get User Connect Mode
			   int userConnectMode;
			   wmxStatus = GetConnectionMode(pDeviceID,&userConnectMode);
			   if (WIMAX_API_RET_SUCCESS != wmxStatus) {
				   PrintWmxStatus(wmxStatus);
				   return 1;
			   }

			   if ((connectMode == WIMAX_API_CONNECTION_SEMI_MANUAL_SCAN_AUTO_CONNECT) ||
				(connectMode == WIMAX_API_CONNECTION_AUTO_SCAN_AUTO_CONNECT) ||
				(connectMode == WIMAX_API_CONNECTION_SEMI_MANUAL_SCAN_MANUAL_CONNECT)) {
				   if (connectMode == WIMAX_API_CONNECTION_SEMI_MANUAL_SCAN_MANUAL_CONNECT) {
					   printf("Changing Scan mode to Manual Scan mode \n");
				   } else {
					   	printf("Changing Scan mode to manual \n");
				   		printf("Changing Connect mode to manual \n");
				   }
				   userConnectMode = WIMAX_API_CONNECTION_MANUAL_SCAN_MANUAL_CONNECT;
				   wmxStatus = SetConnectionMode(pDeviceID,userConnectMode);
				   if (WIMAX_API_RET_SUCCESS != wmxStatus) {
					   PrintWmxStatus(wmxStatus);
					   return 1;
				   }
				}


			   wmxStatus =SubscribeNetworkSearchWideScan(pDeviceID,
					   &IndNetworkSearchWideScanCB);
			   if (WIMAX_API_RET_SUCCESS != wmxStatus) {
				   PrintWmxStatus(wmxStatus);
				   return 2;
			   }


		// Display the warning message:
		printf("WARNING: Wide scan may take upto 2 minutes... \n");
		wmxStatus = CmdNetworkSearchWideScan(pDeviceID);
		if (WIMAX_API_RET_SUCCESS != wmxStatus) {
			PrintWmxStatus(wmxStatus);
			/*
			 If the Device is already scanning, it won't allow one more AppSrv will reject it
			 with the Operation Falied wrror
			*/
			if ((DeviceStatus == WIMAX_API_DEVICE_STATUS_Scanning) && (wmxStatus == WIMAX_API_RET_FAILED)) {
				printf("WARNING: Scanning is in progress\nPlease wait for the current scan to complete.\n ");

			}
            		return 1;
        	}

    		if (wmxcu_sem_timeout(&semConnectionUtility,120*1000) == 1 )
			printf("No networks found.\n");
    	}

	wmxStatus = UnsubscribeRfTaken(pDeviceID);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		PrintWmxStatus(wmxStatus);
	return 2;
	}

	wmxStatus = UnsubscribeNetworkSearch(pDeviceID);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		PrintWmxStatus(wmxStatus);
	return 2;
	}
        wmxStatus = UnsubscribeNetworkSearchWideScan(pDeviceID);
        if (WIMAX_API_RET_SUCCESS != wmxStatus) {
        	PrintWmxStatus(wmxStatus);
	return 2;
    }
    return ret;
        }


void IndDeviceUpdateCB(WIMAX_API_DEVICE_ID_P pDeviceId, WIMAX_API_DEVICE_STATUS systemStatus, WIMAX_API_STATUS_REASON statusReason, WIMAX_API_CONNECTION_PROGRESS_INFO connectionProgressInfo)
{

		g_devState = systemStatus;

		switch(systemStatus)
		{
			case WIMAX_API_DEVICE_STATUS_Ready:
			case WIMAX_API_DEVICE_STATUS_Scanning:
		 	case WIMAX_API_DEVICE_STATUS_Connecting:
			case WIMAX_API_DEVICE_STATUS_Data_Connected:
				sem_post(&semRfState);
				break;

			case WIMAX_API_DEVICE_STATUS_RF_OFF_HW_SW:
				printf("SW and HW Radion is turned off \n");
				sem_post(&semConnectCompleted);
				sem_post(&semConnectionUtility);
				sem_post(&semRfState);
			break;
			case WIMAX_API_DEVICE_STATUS_RF_OFF_HW:
				printf("HW Radio is turned off\n");
				sem_post(&semConnectCompleted);
				sem_post(&semConnectionUtility);
			break;
			case WIMAX_API_DEVICE_STATUS_RF_OFF_SW:
				printf("SW Radio is turned off \n");
				sem_post(&semConnectCompleted);
				sem_post(&semConnectionUtility);
				sem_post(&semRfState);
			break;
			default:
        break;
    }
}

void IndNetworkSearchWideScanCBEx (WIMAX_API_DEVICE_ID_P  pDeviceID,
        					     WIMAX_API_NSP_INFO_EX_P pNspList,
					             UINT32 listSize)
{
    int i;
    // Scan complete arrived.  Display the netwokr list.
    if(pNspList == NULL || listSize < 1)
    {
        printf("No networks found.\n");
    }
    else
    {
        for (i = 0; i < listSize; i++)
        {
            PrintNSPInfoEx(&pNspList[i]);
            if  (IsNetworkActivatedEx(pDeviceID,&pNspList[i]) )
                printf("\tActivated.\n");
            else
                printf("\tNot Activated.\n");
        }
	// Unset the preferred NSP
	preferred_NSP_ID = 0;
	SetCurrentPreferredProfiles(pDeviceID, &preferred_NSP_ID, 0);
    }
    // release the semaphore
	sem_post(&semConnectionUtility);
}



void IndNetworkSearchWideScanCB (WIMAX_API_DEVICE_ID_P  pDeviceID,
        					     WIMAX_API_NSP_INFO_P  pNspList,
					             UINT32 listSize)
{
    int i;
    // Scan complete arrived.  Display the netwokr list.
    if(pNspList == NULL || listSize < 1)
    {
        printf("No networks found.\n");
    }
    else
    {
        for (i = 0; i < listSize; i++)
        {
            PrintNSPInfo(&pNspList[i]);
            if  (IsNetworkActivated(pDeviceID,&pNspList[i]) )
                printf("\tActivated.\n");
            else
                printf("\tNot Activated.\n");
        }
	// Unset the preferred NSP
	preferred_NSP_ID = 0;
	SetCurrentPreferredProfiles(pDeviceID, &preferred_NSP_ID, 0);
    }
    // release the semaphore
	sem_post(&semConnectionUtility);
}

void IndNetworkSearchCBEx(WIMAX_API_DEVICE_ID_P  pDeviceID,
			  WIMAX_API_NSP_INFO_EX_P pNspList,
     UINT32 listSize,UINT32 searchProgress)
{
	int i;

    // Scan complete arrived.  Display the netwokr list.
	if(pNspList == NULL || listSize < 1)
	{
		g_searchProgress = searchProgress;
	 // printf("No networks found.\n");
	}
	else
	{
		pthread_mutex_lock(&console_owner_mutex);
		if (searchProgress == 100 ) {
			for (i = 0; i < listSize; i++)
			{
				g_noNetworksFound = 0;
				printf("\n");
				printf("Network found.\n");
				PrintNSPInfoEx(&pNspList[i]);
				if  (IsNetworkActivatedEx(pDeviceID,&pNspList[i]) )
					printf("\tActivated.\n");
				else
					printf("\tNot Activated.\n");
			}

		} else {
			g_searchProgress = searchProgress;
		}
		pthread_mutex_unlock(&console_owner_mutex);
	}
	if (searchProgress == 100 ) {
		if (g_noNetworksFound == 1) {
			pthread_mutex_lock(&console_owner_mutex);
			printf("\nNo networks found.\n");
			pthread_mutex_unlock(&console_owner_mutex);
		// release the semaphore
			sem_post(&semConnectionUtility);
		} else {
		// release the semaphore
			pthread_mutex_lock(&console_owner_mutex);
			printf("\nScanning operation completed.\n");
			pthread_mutex_unlock(&console_owner_mutex);
			sem_post(&semConnectionUtility);
		}
	}

}



void IndNetworkSearchCB (WIMAX_API_DEVICE_ID_P  pDeviceID,
					     WIMAX_API_NSP_INFO_P  pNspList,
			 UINT32 listSize, UINT32 searchProgress)
{
    int i;

    // Scan complete arrived.  Display the netwokr list.
    if(pNspList == NULL || listSize < 1)
    {
		g_searchProgress = searchProgress;
	 // printf("No networks found.\n");
    }
    else
    {
		pthread_mutex_lock(&console_owner_mutex);
		if (searchProgress == 100 ) {
        for (i = 0; i < listSize; i++)
        {
				g_noNetworksFound = 0;
				printf("\n");
				printf("Network found.\n");
            PrintNSPInfo(&pNspList[i]);
            if  (IsNetworkActivated(pDeviceID,&pNspList[i]) )
                printf("\tActivated.\n");
            else
                printf("\tNot Activated.\n");
        }

		} else {
			g_searchProgress = searchProgress;
    }
		pthread_mutex_unlock(&console_owner_mutex);
	}
	if (searchProgress == 100 ) {
		if (g_noNetworksFound == 1) {
			pthread_mutex_lock(&console_owner_mutex);
			printf("\nNo networks found.\n");
			pthread_mutex_unlock(&console_owner_mutex);
    // release the semaphore
    sem_post(&semConnectionUtility);
		} else {
		// release the semaphore
			pthread_mutex_lock(&console_owner_mutex);
			printf("\nScanning operation completed.\n");
			pthread_mutex_unlock(&console_owner_mutex);
			sem_post(&semConnectionUtility);
		}
	}

}

void IndRFTakenCB (WIMAX_API_DEVICE_ID_P  pDeviceID)
{
	// int i;

    	// Radio is taken away by WiFi
	printf("Could not complete Scan, Radio is taken by WiFi\n");
	printf("Please try scanning later \n");
    // release the semaphore
    sem_post(&semConnectionUtility);
}


/*
 * Function:     GetStats
 * Description:  Get statistics data
 * Return:       0 for success or 1 for failure
 */
int GetStats(WIMAX_API_DEVICE_ID_P pDeviceID)
{
	WIMAX_API_RET wmxStatus;
	WIMAX_API_CONNECTION_STAT Statistics;
	WIMAX_API_DEVICE_STATUS DeviceStatus;
	WIMAX_API_CONNECTION_PROGRESS_INFO ConnectionProgressInfo;

	wmxStatus = GetDeviceStatus(pDeviceID, &DeviceStatus, &ConnectionProgressInfo);
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

	wmxStatus = GetStatistics(pDeviceID, &Statistics);
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
 * Function:     GetDeviceInfo
 * Description:  Retrive the device info
 * Return:
 */
int GetDeviceInfo(WIMAX_API_DEVICE_ID_P pDeviceID)
{
	WIMAX_API_RET wmxStatus = WIMAX_API_RET_SUCCESS;

	WIMAX_API_DEVICE_INFO device_info;
	WIMAX_API_NVM_VERSION nvm_ver;
	WIMAX_API_WMF_COMPLIANCE_VERSION wmf_ver;

	GetDeviceInformation(pDeviceID, &device_info);
	GetWMFComplianceVersion(&wmf_ver);
	GetNVMImageVersion(pDeviceID, &nvm_ver);

	PrintDeviceInfo(&device_info, &wmf_ver, &nvm_ver);

	return 0;
}

/*
 * Function:     GetVersionInfo
 * Description:  Display the version information
 * Return:
 */
int GetVersionInfo(WIMAX_API_DEVICE_ID_P pDeviceID)
{
	WIMAX_API_RET wmxStatus = WIMAX_API_RET_SUCCESS;

	WIMAX_API_DEVICE_INFO device_info;
	WIMAX_API_WMF_COMPLIANCE_VERSION wmf_version;

	wmxStatus = GetDeviceInformation(pDeviceID, &device_info);
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
 * Function:     GetUserLinkStatus
 * Description:  Get the link status
 * Return:       0 for success (connected) or 1 for failure
 */
int GetUserLinkStatus(WIMAX_API_DEVICE_ID_P pDeviceID)
{
	WIMAX_API_RET wmxStatus = WIMAX_API_RET_SUCCESS;
	WIMAX_API_CONNECTED_NSP_INFO ConnectedNSP;
	WIMAX_API_LINK_STATUS_INFO LinkStatus;
	WIMAX_API_CONNECTION_TIME conntime;

	wmxStatus = GetConnectedNSP(pDeviceID, &ConnectedNSP);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		printf("Link Status: Network is not connected.\n");
		return 1;
	}

	wmxStatus = GetLinkStatus(pDeviceID, &LinkStatus);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		PrintWmxStatus(wmxStatus);
	return 1;
	}

	wmxStatus = GetConnectionTime(pDeviceID, &conntime);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		conntime = 0;
	}

	PrintUserLinkStatus(&LinkStatus);
	PrintConnectionTime(conntime);

    return 0;
}

int GetUserLinkStatusEx(WIMAX_API_DEVICE_ID_P pDeviceID)
{
	WIMAX_API_RET wmxStatus = WIMAX_API_RET_SUCCESS;
	WIMAX_API_CONNECTED_NSP_INFO_EX ConnectedNSP;
	WIMAX_API_LINK_STATUS_INFO_EX LinkStatus;
	WIMAX_API_CONNECTION_TIME conntime;

	wmxStatus = GetConnectedNSPEx(pDeviceID, &ConnectedNSP);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		printf("Link Status: Network is not connected.\n");
		return 1;
	}

	wmxStatus = GetLinkStatusEx(pDeviceID, &LinkStatus);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		PrintWmxStatus(wmxStatus);
	return 1;
	}

	wmxStatus = GetConnectionTime(pDeviceID, &conntime);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		conntime = 0;
	}

	PrintUserLinkStatusEx(&LinkStatus);
	PrintConnectionTime(conntime);

    return 0;
}

void IndConnectToNetworkCallback(WIMAX_API_DEVICE_ID_P pDeviceId,
                                 WIMAX_API_NETWORK_CONNECTION_RESP networkConnectionResponse)
{
    switch(networkConnectionResponse)
    {
        case WIMAX_API_CONNECTION_SUCCESS:
		// Set Connected NSP is current preferred NSP
		if (preferred_NSP_ID != 0 ) {
			SetCurrentPreferredProfiles(pDeviceId, &preferred_NSP_ID, 1);
		}
            printf("Connection successful\n");
		break;
        case WIMAX_API_CONNECTION_FAILURE:
            printf("Connection failure\n");
		break;
        default:
            printf("Unknown Connection status\n");
    }
    sem_post(&semConnectCompleted);

}




int ConnectWithProfileID(WIMAX_API_DEVICE_ID_P pDeviceID,
			  char *profileId_str)
{
	WIMAX_API_RET wmxStatus;
	// int bSuccess = 0;
	WIMAX_API_DEVICE_STATUS DeviceStatus;
	WIMAX_API_CONNECTION_PROGRESS_INFO ConnectionProgressInfo;
	WIMAX_API_CONNECTION_MODE connectMode;
	WIMAX_API_NSP_INFO nspInfo;
	WIMAX_API_PROFILE_ID profileId = 0;
    int ret = 0;

	if((profileId_str == NULL)) {
		printf("ERROR: Invalid Parameter - missing Profile ID\n");
		return 1;
	}

	wmxStatus =
	    GetDeviceStatus(pDeviceID, &DeviceStatus, &ConnectionProgressInfo);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		printf("ERROR: Unable to find Device Status - ");
		PrintWmxStatus(wmxStatus);
	return 1;

	}
	wmxStatus = GetConnectionMode(pDeviceID,&connectMode);
    	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
	   PrintWmxStatus(wmxStatus);
	return 1;
	}
	if (connectMode == WIMAX_API_CONNECTION_AUTO_SCAN_AUTO_CONNECT) {
	printf("WARNING: The Profile is setup to Auto Connect and Auto Scan, this command would be deferred\n");
	return 1;
	}

	if (DeviceStatus == WIMAX_API_DEVICE_STATUS_Data_Connected) {
	printf("WARNING: Connection already established!\nPlease disconnect from the current network before attempting to connect.\n");

	return 1;
	}

	if (DeviceStatus != WIMAX_API_DEVICE_STATUS_Ready
	&& DeviceStatus != WIMAX_API_DEVICE_STATUS_Scanning ) {
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
		if (FindNetwork(pDeviceID, profileId, &nspInfo) == 0) {
			printf("ERROR: Attempt to connect Failed. \n");
	    return 1;
		}
	//}
	preferred_NSP_ID = nspInfo.NSPid;
	// Register to connect complete event
	wmxStatus = SubscribeConnectToNetwork (pDeviceID,IndConnectToNetworkCallback);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
	  printf("ERROR: Failed to register callback\n");
	  return 1;
	}

	printf("Connecting to %s Network...\n",nspInfo.NSPName);
	wmxStatus = CmdConnectToNetwork(pDeviceID, nspInfo.NSPName, 0, 0);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
	  printf("ERROR: Connection to %s network not successfull\n", nspInfo.NSPName);
	  return 1;
	}

	if (wmxcu_sem_timeout(&semConnectCompleted,30*1000) == 1 ) {
	    printf("Connection Fail: time out\n");
	    return 1;
	  }

	wmxStatus = UnsubscribeConnectToNetwork (pDeviceID);

	// checking the connection
	//wmxStatus =
	//    GetDeviceStatus(pDeviceID, &DeviceStatus, &ConnectionProgressInfo);
	//if (WIMAX_API_RET_SUCCESS != wmxStatus) {
	//	PrintWmxStatus(wmxStatus);
        //ret = 1;
	//} else {
	//	PrintDeviceStatus(DeviceStatus);
        //ret = 0;
	//}

    return ret;
}

int FindNetwork(WIMAX_API_DEVICE_ID_P pDeviceID, int profileId,
		WIMAX_API_NSP_INFO_P nspInfo)
{
	WIMAX_API_RET wmxStatus = WIMAX_API_RET_SUCCESS;
	UINT32 numProfileList = MAX_PROFILE;
	int i = 0,j =0;
	UINT32 numOfNSPs = MAX_DEVICE;
	WIMAX_API_NSP_INFO_P pNspInfo =
	    (WIMAX_API_NSP_INFO_P )malloc(MAX_LEN *
						sizeof(WIMAX_API_NSP_INFO));
	WIMAX_API_PROFILE_INFO_P profilelist =
	    (WIMAX_API_PROFILE_INFO_P)
			malloc(sizeof(WIMAX_API_PROFILE_INFO)*MAX_PROFILE);
	memset(profilelist, 0,
	       sizeof(WIMAX_API_PROFILE_INFO) * MAX_PROFILE);

	//1. Get the profile list and network list
	wmxStatus =
	    GetSelectProfileList(pDeviceID, profilelist, &numProfileList);
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
			    GetNetworkList(pDeviceID, pNspInfo, &numOfNSPs);
			if (WIMAX_API_RET_SUCCESS != wmxStatus) {
				printf
				    ("ERROR: Could not fetch network list - ");
				PrintWmxStatus(wmxStatus);
				free(pNspInfo);
				free (profilelist);
				return 0;
			}
			if (numOfNSPs == 0) {
				printf
				    ("No available networks.\n");
				free (profilelist);
				free(pNspInfo);
				return 0;
			}
			for (j = 0; j < numOfNSPs; j++) {
				if ((pNspInfo[j].NSPid & 0xffffff) == profileId) {
					// match with nspid, if there copy the nsp name and send it back
					memcpy(nspInfo, &pNspInfo[j],
					       sizeof(WIMAX_API_NSP_INFO));
					free(pNspInfo);
					free (profilelist);
					return 1;
				}
			}
		}
	}
	// return the proper status of this function

	free (profilelist);
	free(pNspInfo);
	// get the profile list and compare with nspid and return the result

	return 0;
}


int ConnectWithNSPInfo(WIMAX_API_DEVICE_ID_P pDeviceID,
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
  char *msg = "Waiting for initial provisioning from server...\nPress 'q' to quit.";
  WIMAX_API_NSP_INFO_P pNspInfo =
    (WIMAX_API_NSP_INFO_P )malloc(MAX_LEN * sizeof(WIMAX_API_NSP_INFO));


  // zero the memory
  memset(pNspInfo, 0, sizeof(WIMAX_API_NSP_INFO) * MAX_LEN);

  do {
    wmxStatus = GetDeviceStatus(pDeviceID, &DeviceStatus, &ConnectionProgressInfo);
    if (WIMAX_API_RET_SUCCESS != wmxStatus) {
      printf("ERROR: Attempt to connect not successfull - ");
      PrintWmxStatus(wmxStatus);
      free(pNspInfo);
	    return 2;
    }

	  if (DeviceStatus == WIMAX_API_DEVICE_STATUS_Data_Connected) {
	    printf("WARNING: Connection already established!\nPlesae disconnect from the current network before attempting to connect\n");
	    free(pNspInfo);
	    return 1;
	  }

	  if (DeviceStatus != WIMAX_API_DEVICE_STATUS_Ready
	      && DeviceStatus != WIMAX_API_DEVICE_STATUS_Scanning ) {
	    printf("ERROR: Attempt to connect not successfull - ");
	    PrintDeviceStatus(DeviceStatus);
	    free(pNspInfo);
	    return 2;
	  }

	wmxStatus = GetConnectionMode(pDeviceID,&connectMode);
    	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
	   PrintWmxStatus(wmxStatus);
	return 2;
	}

	
	wmxStatus =GetCurrentPreferredProfiles(pDeviceID,&CurrentPreferredNSPs,&listsize);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
	   PrintWmxStatus(wmxStatus);
	return 2;
	}
	if(CurrentPreferredNSPs.profileID!=0){
		
		printf("Current Preferred Profile is:\n");	;
		printf("\tID  : %d\n",CurrentPreferredNSPs.profileID);
		printf("\tName: %s\n",CurrentPreferredNSPs.profileName);
	}

	if ((DeviceStatus == WIMAX_API_DEVICE_STATUS_Ready) && connectMode == WIMAX_API_CONNECTION_MANUAL_SCAN_MANUAL_CONNECT)
	{
		printf("In Manual Scan and Manual Connect Mode\nTrying to find the networks ...\n");
		wmxStatus = SubscribeNetworkSearch(pDeviceID,&IndNetworkSearchCB );
    		if (WIMAX_API_RET_SUCCESS != wmxStatus) {
      		PrintWmxStatus(wmxStatus);
		return 2;
    		}
		wmxStatus = CmdNetworkSearch(pDeviceID);
		if (WIMAX_API_RET_SUCCESS != wmxStatus) {
			PrintWmxStatus(wmxStatus);
			return 1;
		}
		  printf("Scanning %2d%% Done ", g_searchProgress);
			   fflush(stdout);
			   do {
				   if (wmxcu_sem_timeout(&semConnectionUtility,5*1000) == 1 )
				   {
					   time_out++;
					   if (pthread_mutex_trylock(&console_owner_mutex) == 0) {
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
						   pthread_mutex_unlock(&console_owner_mutex);
					   }
					   wmxStatus = GetDeviceStatus(pDeviceID, &DeviceStatus, &ConnectionProgressInfo);
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
		
	    wmxStatus = GetNetworkList(pDeviceID, pNspInfo, &numOfNSPs);
	    if (WIMAX_API_RET_SUCCESS != wmxStatus) {
	      printf("ERROR: Attempt to connect not successfull - ");
	      PrintWmxStatus(wmxStatus);
	      free(pNspInfo);
		return 2;
	    
		}
		wmxStatus = UnsubscribeNetworkSearch(pDeviceID);
		if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		PrintWmxStatus(wmxStatus);
		return 2;
		}

	}else if ((DeviceStatus == WIMAX_API_DEVICE_STATUS_Ready) || (DeviceStatus == WIMAX_API_DEVICE_STATUS_Scanning)) {
	    wmxStatus = GetNetworkList(pDeviceID, pNspInfo, &numOfNSPs);
	    if (WIMAX_API_RET_SUCCESS != wmxStatus) {
	      printf("ERROR: Attempt to connect not successfull - ");
	      PrintWmxStatus(wmxStatus);
	      free(pNspInfo);
		return 2;
	    }

	  }
	if (numOfNSPs == 0){
		//numOfNSPs is 0 now - it should be set to MAX
		numOfNSPs=MAX_DEVICE;
		printf("Searching....\n");
		wmxStatus = SubscribeNetworkSearch(pDeviceID,&IndNetworkSearchCB );
    		if (WIMAX_API_RET_SUCCESS != wmxStatus) {
      		PrintWmxStatus(wmxStatus);
		return 2;
    		}
		wmxStatus = CmdNetworkSearch(pDeviceID);
		if (WIMAX_API_RET_SUCCESS != wmxStatus) {
			PrintWmxStatus(wmxStatus);
			return 1;
		}

		if (wmxcu_sem_timeout(&semConnectionUtility,30*1000) == 1 ){

			printf("ERROR: Attempt to connect not successfull\n");
			free(pNspInfo);
			return 2;
		}
		else{
			wmxStatus = GetNetworkList(pDeviceID, pNspInfo, &numOfNSPs);
			if (WIMAX_API_RET_SUCCESS != wmxStatus) {
			printf("ERROR: Attempt to connect not successfull - ");
			PrintWmxStatus(wmxStatus);
			free(pNspInfo);
				return 2;
			}
		}
		wmxStatus = UnsubscribeNetworkSearch(pDeviceID);
		if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		PrintWmxStatus(wmxStatus);
		return 2;
		}

	}
	    if (numOfNSPs == 0) {
	      printf("Attempt to connect not successfull - No available networks\n");
	      free(pNspInfo);
	      return 1;
	    }
	    else {
	      wait = FALSE;
	  }

		// We should not be polling to get an update on the device state but rely on callback..
		// for now we will sleep in between to give the device some time to do work...
		sleep(1);
	} while (wait == TRUE);

	for (i = 0; i < numOfNSPs; i++) {
	  sprintf(tmp_nspID_str,"%d",pNspInfo[i].NSPid);
	  if (!strcmp(tmp_nspID_str,str_nspid)) {
		if ( activate ) {
		  if ( sem_init(&semAPDOactivation,0,0) == -1 )
		    {
			//Semaphore could not be initialized.
		      printf("ERROR: Activation Failed - Internal failure\n");
		      free(pNspInfo);
			return 2;
		    }
		  printf("WARNING: Starting the Activation Process...\n");
		  wmxStatus = RegisterAPDOCallback(pDeviceID);
		  if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		    printf("ERROR: Activation Failed - ");
		    PrintWmxStatus(wmxStatus);
		    free(pNspInfo);
			return 2;
		  }
		  wmxStatus = RegisterPUMACallback(pDeviceID);
		  if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		    printf("ERROR: Activation Failed - ");
		    PrintWmxStatus(wmxStatus);
		    free(pNspInfo);
			return 2;
		  }
		  // copy to global variable to launch again
		  strcpy (g_sznspName,pNspInfo[i].NSPName);
		}

	      preferred_NSP_ID = pNspInfo[i].NSPid;
              // Register to connect complete event
              wmxStatus = SubscribeConnectToNetwork (pDeviceID,IndConnectToNetworkCallback);
              if (WIMAX_API_RET_SUCCESS != wmxStatus) {
                  printf("ERROR: Failed to register callback\n");
                  free(pNspInfo);
                  return 1;
              }

	    printf("Connecting to %s Network...\n",pNspInfo[i].NSPName);
	    wmxStatus = CmdConnectToNetwork(pDeviceID, pNspInfo[i].NSPName, 0, 0);
	    if (WIMAX_API_RET_SUCCESS != wmxStatus) {
	      printf("ERROR: Connection to %s network not successfull\n",pNspInfo[i].NSPName);
	      free(pNspInfo);
		return 1;
	    }
            if (wmxcu_sem_timeout(&semConnectCompleted,30*1000) == 1 )
            {
                printf("Connection Fail: time out\n");
                free(pNspInfo);
                return 1;
            }
	     wmxStatus = UnsubscribeConnectToNetwork (pDeviceID);

	    if  ( activate )
	      {
		// spin the thread
		ret = pthread_create( &userinputthread, NULL, userinfo, (void*) msg);
		if (wmxcu_sem_timeout(&semAPDOactivation,90*1000) == 1 )
		  printf("ERROR: Activation Server Not Responding (Time Out)\n");

		wmxStatus = UnRegisterAPDOCallback(pDeviceID);
		if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		  PrintWmxStatus(wmxStatus);
		  free(pNspInfo);
		    return 2;
		}
		wmxStatus = UnregisterPUMACallback(pDeviceID);
		if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		  PrintWmxStatus(wmxStatus);
		  free(pNspInfo);
		    return 2;
		}
		pthread_cancel(userinputthread);
	      }
	    // checking the connection
	    //wmxStatus = GetDeviceStatus(pDeviceID, &DeviceStatus, &ConnectionProgressInfo);
	    //if (WIMAX_API_RET_SUCCESS != wmxStatus)
	    //  {
	    //PrintWmxStatus(wmxStatus);
	    //  }
	    //else
	    //  {
	    //	PrintDeviceStatus(DeviceStatus);
	    //  }

	    bSuccess = 1;
	  }
	  if ( bSuccess == 1)
	    break;
	}

	if (!bSuccess) {
	  printf("WARNING: Network ID did not match, try issuing a wide scan.\n");
        free(pNspInfo);
        return 1;
    }

    free(pNspInfo);
    return 0;
}

void *userinfo(void *ptr)
{
	int ch = 0;
     	printf("%s \n", (char *)ptr);
	while(ch != 'q' && ch != 'Q')
		ch = getc(stdin);

	sem_post(&semAPDOactivation);
	return (void *) 0;
}

/*
 * Function:     Activate
 * Description:  Connect to un-activated network
 */
int Activate(WIMAX_API_DEVICE_ID_P pDeviceID, char *str_nspid)
{
	if ( str_nspid == NULL  ){
		printf("ERROR: Network ID is not valid\n");
	return 1;
	}

    return ConnectWithNSPInfo(pDeviceID, str_nspid, 1);
}

/*
 * Function:     Deactivate
 * Description:  Deactivate already activated network
 */
int Deactivate(WIMAX_API_DEVICE_ID_P pDeviceID, char *str_nspid)
{
	WIMAX_API_RET wmxStatus = WIMAX_API_RET_SUCCESS;
	int nspid = atoi(str_nspid);
	wmxStatus = CmdDeprovisionProfile(pDeviceID,nspid);
	if  (wmxStatus != WIMAX_API_RET_SUCCESS )
	{
		printf("ERROR: Profile Deactivate unsuccessfull\n");
		PrintWmxStatus(wmxStatus);
        return 1;
	}

    printf("Profile is Deactivated.\n");
    return 0;
}

/*
 * Function:     Disconnect
 * Description:  Disconnect from the currently connected network
 */
int Disconnect(WIMAX_API_DEVICE_ID_P pDeviceID)
{
	WIMAX_API_RET wmxStatus;
    WIMAX_API_DEVICE_STATUS DeviceStatus;
    WIMAX_API_CONNECTION_PROGRESS_INFO ConnectionProgressInfo;
    WIMAX_API_CONNECTION_MODE connectMode;

    wmxStatus = GetDeviceStatus(pDeviceID, &DeviceStatus, &ConnectionProgressInfo);
    if (WIMAX_API_RET_SUCCESS != wmxStatus) {
        PrintWmxStatus(wmxStatus);
	return 2;
	}

    if (DeviceStatus != WIMAX_API_DEVICE_STATUS_Data_Connected) {
        printf("WARNING: Network already disconnected.\n");
	return 1;
        }

    // Get current connection mode
    wmxStatus = GetConnectionMode(pDeviceID,&connectMode);
    if (WIMAX_API_RET_SUCCESS != wmxStatus) {
        PrintWmxStatus(wmxStatus);
	return 2;
	}

    if (connectMode == WIMAX_API_CONNECTION_SEMI_MANUAL_SCAN_AUTO_CONNECT
        || connectMode == WIMAX_API_CONNECTION_AUTO_SCAN_AUTO_CONNECT)
    {
        ConvertCharToConnectionMode(CMD_STR_MODE_ARGS_CONNECT_OPT_MANUAL, NULL, &connectMode);
        wmxStatus = SetConnectionMode(pDeviceID,connectMode);
        if (WIMAX_API_RET_SUCCESS != wmxStatus) {
            PrintWmxStatus(wmxStatus);
            printf("ERROR: Changing connect mode to manual unsuccessfull\n");
            return 2;
        }
        printf("WARNING: Connect mode is now changed to manual\n");
    }

		wmxStatus = CmdDisconnectFromNetwork(pDeviceID);
		if (wmxStatus != WIMAX_API_RET_SUCCESS) {
			PrintWmxStatus(wmxStatus);
	return 1;
    }

	printf("Network Disconnected.\n");
	return 0;
}

/*
 * Function:     RadioOn
 * Description:  Turn on the Radio
 * Return:       0 for success,
                 1 for failure, or
                 2 for non-command related error
 */
int RadioOn(WIMAX_API_DEVICE_ID_P pDeviceID)
{
    	int ret = 0;
	WIMAX_API_RET wmxStatus;
	WIMAX_API_DEVICE_STATUS DeviceStatus;
	WIMAX_API_CONNECTION_PROGRESS_INFO ConnectionProgressInfo;

	wmxStatus = GetDeviceStatus(pDeviceID, &DeviceStatus, &ConnectionProgressInfo);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		PrintWmxStatus(wmxStatus);
		return 2;
	}

	if (DeviceStatus == WIMAX_API_DEVICE_STATUS_RF_OFF_SW) {
		wmxStatus = CmdControlPowerManagement(pDeviceID, WIMAX_API_RF_ON);
		if (WIMAX_API_RET_SUCCESS != wmxStatus) {
			PrintWmxStatus(wmxStatus);
            ret = 1;
		} else {
			// Wait 5 secs to get a confirmation of the updated(desired) device state before declaring success
			if ( !wmxcu_sem_timeout(&semRfState,5*1000)  ) {
				if ( (g_devState == WIMAX_API_DEVICE_STATUS_Ready) ||
				  (g_devState == WIMAX_API_DEVICE_STATUS_Scanning) ||
				  (g_devState ==  WIMAX_API_DEVICE_STATUS_Connecting) ||
                     		  (g_devState ==  WIMAX_API_DEVICE_STATUS_Data_Connected) ) {
					printf("SW Radio is turned ON.\n");
                    			ret = 0;
				}
			}
			else {
        			printf("ERROR: Failed to turn SW Radio ON.\n");
                    		ret = 1;
                	}
            }
	} else if ( DeviceStatus == WIMAX_API_DEVICE_STATUS_RF_OFF_HW_SW ||
		        DeviceStatus == WIMAX_API_DEVICE_STATUS_RF_OFF_HW ) {
        	printf("HW Radio is OFF.\nDisable HW Kill to turn ON the SW Radio.\n");
        	ret = 1;
    	} else if ( DeviceStatus == WIMAX_API_DEVICE_STATUS_UnInitialized ) {
        	printf("ERROR: Turning the SW Radio ON unsuccessfull - Device is UnInitialized.\n");
        	ret = 1;
	} else {
		printf ("HW and SW Radios are ON.\n");
	}
	return ret;
}

/*
 * Function:     RadioOff
 * Description:  Turn off the radio
 * Return:       0 for success,
                 1 for failure, or
                 2 for non-command related error
 */
int RadioOff(WIMAX_API_DEVICE_ID_P pDeviceID)
{
    int ret = 0;
	WIMAX_API_RET wmxStatus;
	WIMAX_API_DEVICE_STATUS DeviceStatus;
	WIMAX_API_CONNECTION_PROGRESS_INFO ConnectionProgressInfo;

	wmxStatus = GetDeviceStatus(pDeviceID, &DeviceStatus, &ConnectionProgressInfo);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		PrintWmxStatus(wmxStatus);
		return 2;
	}

	if (DeviceStatus == WIMAX_API_DEVICE_STATUS_RF_OFF_HW ){
	        printf("HW Radio is OFF.\nDisable HW Kill to turn OFF the SW Radio.\n");
		return 0;
	}
	else if(DeviceStatus == WIMAX_API_DEVICE_STATUS_RF_OFF_SW)
	{
		printf("SW Radio is already turned OFF. \n");
		return 0;
	}
	else if(DeviceStatus == WIMAX_API_DEVICE_STATUS_RF_OFF_HW_SW ){
	        printf("HW and SW Radios are already turned OFF.\n");
		return 0;
	}

	if (DeviceStatus != WIMAX_API_DEVICE_STATUS_UnInitialized) {
		wmxStatus = CmdControlPowerManagement(pDeviceID, WIMAX_API_RF_OFF);
		if (WIMAX_API_RET_SUCCESS != wmxStatus) {
			PrintWmxStatus(wmxStatus);
	    	return 1;
		} else {
			// Wait 5 secs to get a confirmation of the updated(desired) device state before declaring success
			if ( !wmxcu_sem_timeout(&semRfState,5*1000)   ) {
				 if (g_devState == WIMAX_API_DEVICE_STATUS_RF_OFF_SW) {
					// printf("SW Radio is turned OFF\n");
                    			ret = 0;
				}
				else {
        				printf("ERROR: Failed to turn SW Radio OFF.\n");
                    			ret = 1;
                		}
            		}
            		else {
                		printf("ERROR: Failed to turn SW Radio OFF.\n");
                		ret = 1;
            		}
		}
	} else {
        	printf("ERROR: Turning the SW Radion OFF unsuccessfull - Device is UnInitialized.\n");
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
void GetConnNSP(WIMAX_API_DEVICE_ID_P pDeviceID)
{
	WIMAX_API_RET wmxStatus = WIMAX_API_RET_SUCCESS;
	WIMAX_API_CONNECTED_NSP_INFO ConnectedNSP;
	WIMAX_API_LINK_STATUS_INFO LinkStatus;

	wmxStatus = GetLinkStatus(pDeviceID, &LinkStatus);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		PrintWmxStatus(wmxStatus);
		return;
	}

	wmxStatus = GetConnectedNSP(pDeviceID, &ConnectedNSP);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		PrintWmxStatus(wmxStatus);
		return;
	}
	ConnectedNSP.RSSI = LinkStatus.RSSI;
	ConnectedNSP.CINR = LinkStatus.CINR;
	PrintConnectedNSPInfo(&ConnectedNSP);
}

void GetConnNSPEX(WIMAX_API_DEVICE_ID_P pDeviceID)
{
	WIMAX_API_RET wmxStatus = WIMAX_API_RET_SUCCESS;
	WIMAX_API_CONNECTED_NSP_INFO_EX ConnectedNSP;
	WIMAX_API_LINK_STATUS_INFO_EX LinkStatus;

	wmxStatus = GetLinkStatusEx(pDeviceID, &LinkStatus);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		PrintWmxStatus(wmxStatus);
		return;
	}

	wmxStatus = GetConnectedNSPEx(pDeviceID, &ConnectedNSP);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		PrintWmxStatus(wmxStatus);
		return;
	}
	ConnectedNSP.RSSI = LinkStatus.RSSI;
	ConnectedNSP.CINR = LinkStatus.CINR;
	ConnectedNSP.linkQuality = LinkStatus.linkQuality;
	PrintUserLinkStatusEx(&ConnectedNSP);
}


void GetConnTime(WIMAX_API_DEVICE_ID_P pDeviceID)
{
    WIMAX_API_RET wmxStatus = WIMAX_API_RET_SUCCESS;
    WIMAX_API_CONNECTION_TIME connectionTime;

    wmxStatus = GetConnectionTime(pDeviceID, &connectionTime);
    if (WIMAX_API_RET_SUCCESS != wmxStatus) {
        PrintWmxStatus(wmxStatus);
        return;
    }
    PrintConnectionTime(connectionTime);
}

WIMAX_API_RET RegisterAPDOCallback(WIMAX_API_DEVICE_ID_P pDeviceID)
{
	return SubscribeProvisioningOperation(pDeviceID,&IndProvisioningOperationCallBack);
}


WIMAX_API_RET UnRegisterAPDOCallback(WIMAX_API_DEVICE_ID_P pDeviceID)
{
	return UnsubscribeProvisioningOperation(pDeviceID);
}


WIMAX_API_RET RegisterPUMACallback(WIMAX_API_DEVICE_ID_P pDeviceID)
{
	return SubscribePackageUpdate(pDeviceID,&IndPackageUpdateCallBack);
}


WIMAX_API_RET UnregisterPUMACallback(WIMAX_API_DEVICE_ID_P pDeviceID)
{
	return  UnsubscribePackageUpdate(pDeviceID);
}


void IndProvisioningOperationCallBack (WIMAX_API_DEVICE_ID_P  pDeviceID,
				      WIMAX_API_PROV_OPERATION provisoningOperation,
					  WIMAX_API_CONTACT_TYPE contactType)
{
	WIMAX_API_RET wmxStatus = WIMAX_API_RET_SUCCESS;
	int cmd =0;
	int flag  = 0;
	WIMAX_API_CONTACT_INFO_P ContactInfo = NULL;
	UINT32 SizeOfContactList =MAX_PROFILE;
	char browserurl[MAX_SIZE_OF_STRING_BUFFER+MAX_SIZE_OF_STRING_BUFFER] = {0};
	switch(provisoningOperation)
	{
	case WIMAX_API_PROV_OPERATION_CFG_UPDATE_STARTED:
		printf("Provisioning Update Started...\n");
		break;
	case WIMAX_API_PROV_OPERATION_CFG_UPDATE_COMPLETED:
		printf("Provisioning Update Completed.\n");
		// set the event to exit the application
		sem_post(&semAPDOactivation);
		break;
	case WIMAX_API_PROV_OPERATION_CFG_UPDATE_FAILED_NETWORK_DISCONNECT:
		printf("WARNING: Provisioning Update - Network Disconnected. \n");
		// set the event to exit the application
		sem_post(&semAPDOactivation);
		break;
	case WIMAX_API_PROV_OPERATION_CFG_UPDATE_FAILED:
		printf("WARNING: Provisioning  Update unsuccessfull.\n");
		// set the event to exit the application
		sem_post(&semAPDOactivation);
		break;
	case WIMAX_API_PROV_OPERATION_CFG_UPDATE_FAILED_INVALID_PROVISIONING:
		printf("WARNING: Provisioning Update - Invalid Provisioning\n");
		// set the event to exit the application
		sem_post(&semAPDOactivation);
		break;
	case WIMAX_API_PROV_OPERATION_CFG_UPDATE_FAILED_BAD_AUTHENTICATION:
		printf("WARNING: Provisioning Update - Bad Authentication\n");
		// set the event to exit the application
		sem_post(&semAPDOactivation);
		break;
	case WIMAX_API_PROV_OPERATION_CFG_UPDATE_REQUEST_INITIAL_PROVISIONING:
		//printf("Initial provisioning\n");
		printf("The Network is attempting to update the WiMAX connection settings.\
			   These settings are critical for the proper operation of WiMAX.\n \
			   Update the WiMAX connection settings now [Y/N]:?");
		cmd = getchar();
		if  (cmd == 'y' || cmd == 'Y')
		{
			wmxStatus = SetPackageUpdateState(pDeviceID,WIMAX_API_PACKAGE_UPDATE_ACCEPTED);
			if ( wmxStatus != WIMAX_API_RET_SUCCESS )
			{
				PrintWmxStatus(wmxStatus);
				sem_post(&semAPDOactivation);
			}
		}
		else
		{
			wmxStatus = SetPackageUpdateState(pDeviceID,WIMAX_API_PACKAGE_UPDATE_DELAY);
			if ( wmxStatus != WIMAX_API_RET_SUCCESS )
			{
				PrintWmxStatus(wmxStatus);
			}
			sem_post(&semAPDOactivation);
		}
		break;
	case WIMAX_API_PROV_OPERATION_CFG_UPDATE_REQUEST_ONGOING_PROVISIONING:
		printf("Ongoing Provisioning\n");
		/*
		cmd = system("firefox www.intel.com");
		printf("The network is attempting to update the WiMAX connection settings.\
			   These settings are critical for the proper operation of WiMAX.\n	\
			   \r\n\r\nUpdate the WiMAX connection settings now y/n?");
		cmd = getchar();
		if  (cmd == 'y' || cmd == 'Y')
		{
			wmxStatus = SetPackageUpdateState(pDeviceID,WIMAX_API_PACKAGE_UPDATE_ACCEPTED);
			if ( wmxStatus != WIMAX_API_RET_SUCCESS )
			{
				PrintWmxStatus(wmxStatus);
			}
		}
		else
		{
			wmxStatus = SetPackageUpdateState(pDeviceID,WIMAX_API_PACKAGE_UPDATE_DELAY);
			if ( wmxStatus != WIMAX_API_RET_SUCCESS )
			{
				PrintWmxStatus(wmxStatus);
			}
		}
		*/
		break;
	case WIMAX_API_PROV_OPERATION_CFG_UPDATE_TRIGGER_CONTACT:
		ContactInfo = (WIMAX_API_CONTACT_INFO_P)malloc(sizeof (WIMAX_API_CONTACT_INFO)*MAX_PROFILE);
		wmxStatus = GetContactInformation(pDeviceID,g_sznspName,
				ContactInfo,&SizeOfContactList);
		if  (wmxStatus != WIMAX_API_RET_SUCCESS )
		{
			printf("WARNING: Unable to Retrive the Contact Information\n");
		}
		else
		{
			for ( cmd = 0; cmd <SizeOfContactList; cmd++ )
			{
				if  (contactType == ContactInfo[cmd].contactType)
				{
					// TODO:: find the the browser launch idea for all OS ie midinux, Ubunto etc.,
					printf("Launching the URL %s ...\n",ContactInfo[cmd].URI );
					sprintf(browserurl,"firefox %s",ContactInfo[cmd].URI);
					cmd = system(browserurl);
					flag = 1;
					break;
				}
			}
		}
		free (ContactInfo);
		if  ( flag == 0)
			printf("WARNIGN: Unable to to connect to the URL\n");
		sem_post(&semAPDOactivation);

		break;
	case WIMAX_API_PROV_OPERATION_CFG_UPDATE_REQUEST_RESET_PROVISIONING:
		printf("WARNING: Provisioning Update - request to Reset the Provisioning\n");
		break;
	default:
		sem_post(&semAPDOactivation);
		break;
	}
}


void IndPackageUpdateCallBack(WIMAX_API_DEVICE_ID_P  pDeviceID, WIMAX_API_PACK_UPDATE packageUpdate)
{
	char consent;
	WIMAX_API_RET   wmxStatus;
	//WIMAX_API_PACKAGE_INFO_P pPackageINFO;
	WIMAX_API_PACKAGE_INFO packageINFO;
	//char pathName[PATH_MAX]={0};
	//char packageName[NAME_MAX]={0};
	//char execute [PATH_MAX + NAME_MAX]={0};
	switch (packageUpdate)
	{
	case WIMAX_API_PACK_UPDATE_RECEIVED:
		printf("Package Update - Received \n");
		/*printf("Request to download notification received.\n");
		wmxStatus = SetPackageUpdateState(pDeviceID,WIMAX_API_PACKAGE_UPDATE_ACCEPTED);
		if ( wmxStatus != WIMAX_API_RET_SUCCESS )
		{
				PrintWmxStatus(wmxStatus);
		}*/
		break;
	case WIMAX_API_PACK_UPDATE_RECEIVED_LOWER_STACK:
		printf("Package Update - Firmware update Received\n");
		break;
	case WIMAX_API_PACK_UPDATE_RECEIVED_FULL_STACK:
		printf("Package Update - Firmware, SDK and driver updates Received.\n");
		break;

	case WIMAX_API_PACK_UPDATE_RECEIVED_OMA_DM_CLIENT:
		printf("Package Update - OMA-DM client update Received.\n");
		break;

	case  WIMAX_API_PACK_UPDATE_STARTED:
		wmxStatus = GetPackageInformation(pDeviceID, &packageINFO);
		if ( wmxStatus != WIMAX_API_RET_SUCCESS )
		{
					PrintWmxStatus(wmxStatus);
		}
		if((strcmp(foOperationType,SW_UPGRADE_TYPE_DOWNLOAD)==0)||(strcmp(foOperationType,SW_UPGRADE_TYPE_UPDATE)==0))
		{
			printf("Request to install %s downloaded package [Y/N]:",packageINFO.fileName);
			scanf("%c",&consent);
			if((consent=='Y')||(consent=='y'))
			{
				strcat(packageINFO.filePath,"/");

#if 0				// TODO :: IMPORTANT - to be removed
				wmxStatus = InstallAPDOUpdate(pDeviceID,packageINFO.filePath,packageINFO.fileName);

				if ( wmxStatus != WIMAX_API_RET_SUCCESS )
				{
					PrintWmxStatus(wmxStatus);
				}
				//printf("%s\n %s",packageINFO.filePath,packageINFO.fileName);

#endif
				sem_post(&semAPDOupdates);
			}
			else if((consent=='N')||(consent=='n'))
			{

				sem_post(&semAPDOupdates);
			}
		}
		else if(strcmp(foOperationType,SW_UPGRADE_TYPE_DOWNLOAD_AND_UPDATE)==0)
		{
			printf("%s downloaded package will be installed ",packageINFO.fileName);
			strcat(packageINFO.filePath,"/");

#if 0
			wmxStatus = InstallAPDOUpdate(pDeviceID,packageINFO.filePath,packageINFO.fileName);
			if ( wmxStatus != WIMAX_API_RET_SUCCESS )
			{
				PrintWmxStatus(wmxStatus);
			}
#endif
			sem_post(&semAPDOupdates);
		}


		break;/**< Request to install package */
	case WIMAX_API_PACK_UPDATE_COMPLETED:
		printf("Package Update - Successfully Installed.\n");
		sem_post(&semAPDOupdates);
		break;

	case WIMAX_API_PACK_UPDATE_FAILED_NETWORK_DISCONNECTED:
		printf("WARNING: Package Update - Failed to Install - Network Disconnected.\n");
		break;
	case WIMAX_API_PACK_UPDATE_FAILED_INVALID_PACKAGE:
		printf("WARNING: Package Update - Failed to Install - Invalid Package.\n");
		sem_post(&semAPDOupdates);
		break;
	case WIMAX_API_PACK_UPDATE_FAILED_BAD_AUTHENTICATION:
		printf("WARNING: Package Update - Failed to Install - Bad Authentication.\n");
		sem_post(&semAPDOupdates);
		break;
	case  WIMAX_API_PACK_UPDATE_FAILED:
		printf("Package Update - Failed to Install.\n");
		break;
		sem_post(&semAPDOupdates);
	}
}


void RestoreProDB(WIMAX_API_DEVICE_ID_P pDeviceID)
{
	WIMAX_API_RET wmxStatus = WIMAX_API_RET_SUCCESS;
	wmxStatus = CmdRestoreBackupProvisioningDatabase(pDeviceID);
	if ( wmxStatus != WIMAX_API_RET_SUCCESS)
	{
		PrintWmxStatus(wmxStatus);
	}

}


/*
 * Function:     ServiceProviderUnlock
 * Description:  Unlock the device
 * Return:       0 for success or 1 for failure, 2 for misc failure
 */
int ServiceProviderUnlock(WIMAX_API_DEVICE_ID_P pDeviceID, char *unlockcode)
{
	WIMAX_API_RET wmxStatus = WIMAX_API_RET_SUCCESS;
	WIMAX_API_LOCK_STATUS LockStatus = WIMAX_API_DEVICE_UNLOCKED;
	char NSPName[MAX_SIZE_OF_NSP_NAME];

    int length = strlen(unlockcode);
    if (length <= 0) {
        printf("Unlock code is empty\n");
        return 1;
    }

	wmxStatus = GetServiceProviderLockStatus(pDeviceID, &LockStatus,  NSPName);
	if ( wmxStatus == WIMAX_API_RET_SUCCESS) {
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
	wmxStatus = SetServiceProviderUnLock(pDeviceID,unlockcode);
	if  ( wmxStatus != WIMAX_API_RET_SUCCESS )
	{
		PrintWmxStatus(wmxStatus);
        return 1;
	}
	// free(wUnlockcode);
    return 0;
}

/*
 * Function:     GetProfileList
 * Description:  Get the profile list
 * Return:       0 for success or 1 for failure
 */
int GetProfileList(WIMAX_API_DEVICE_ID_P pDeviceID)
{
	WIMAX_API_RET wmxStatus = WIMAX_API_RET_SUCCESS;
	UINT32 numProfileList = MAX_PROFILE;
    int i = 0;

	WIMAX_API_PROFILE_INFO_P  profilelist= (WIMAX_API_PROFILE_INFO_P)
			malloc(sizeof(WIMAX_API_PROFILE_INFO) * MAX_PROFILE);
	memset(profilelist,0,sizeof(WIMAX_API_PROFILE_INFO) * MAX_PROFILE);

	wmxStatus = GetSelectProfileList(pDeviceID, profilelist, &numProfileList);
	if ( wmxStatus != WIMAX_API_RET_SUCCESS )
	{
		PrintWmxStatus(wmxStatus);
		free (profilelist);
	return 1;
	}

    printf("Profile List:\n");
	for ( i = 0; i < numProfileList; i++)
	{
        printf("\tID  : %d\n",profilelist[i].profileID);
        printf("\tName: %s\n",profilelist[i].profileName);
	}

	free (profilelist);
    return 0;
}

/*
 * Function:     installAPDOUpdates
 * Description:  Install available package
 * Return:       0 for success or 1 for failure
 */
int installAPDOupdates(WIMAX_API_DEVICE_ID_P pDeviceID)
{
	char consent = {0};
	char retbuffer[NAME_MAX] = {0};
	WIMAX_API_RET wmxStatus;


	WIMAX_API_DEVICE_STATUS DeviceStatus;
	WIMAX_API_CONNECTION_PROGRESS_INFO ConnectionProgressInfo;

	//Check to see if HW or SW radio is turned off
	wmxStatus = GetDeviceStatus(pDeviceID, &DeviceStatus, &ConnectionProgressInfo);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		PrintWmxStatus(wmxStatus);
		return 1;
	}

	if (DeviceStatus == WIMAX_API_DEVICE_STATUS_RF_OFF_SW )
	{
		printf("WARNING: SW Radio is turned OFF\n");
		return 1;
	}
	else if (DeviceStatus == WIMAX_API_DEVICE_STATUS_RF_OFF_HW_SW )
	{
		printf("WARNING: HW and SW Radios are turned OFF\n ");
		return 1;
	}
	else if (DeviceStatus == WIMAX_API_DEVICE_STATUS_RF_OFF_HW)
	{
		printf("WARNING: HW Radio is turned OFF\n");
		return 1;
	}
	else
	{

#if 0 			// TODO :: IMPORTANT -- to be removed (no FUMO functionality)
			wmxStatus = APDOupdates(pDeviceID,retbuffer,NAME_MAX);
#endif
			RegisterPUMACallback(pDeviceID);
			if(retbuffer[0]!=0)
			{
				strcpy(foOperationType,retbuffer);
			}

			if(strcmp(foOperationType,SW_UPGRADE_TYPE_DOWNLOAD_AND_UPDATE)==0)
				printf("\nPackages are available for Download and Install [Y/N]:");

			else if(strcmp(foOperationType,SW_UPGRADE_TYPE_DOWNLOAD)==0)
				printf("\nPackages are available for Download [Y/N]:");
			else if(strcmp(foOperationType,SW_UPGRADE_TYPE_UPDATE)==0)
				printf("\nPackages are available to Install [Y/N]:");
			else {
				printf("No APDO updates are available at this time.\n");
	    return 1;
			}

			scanf("%c",&consent);
			if((consent=='Y')||(consent=='y'))
			{
					if (sem_init(&semAPDOupdates,0, 0) == -1){
					printf("ERROR: Internal failure\n");
		return 1;
				}

				wmxStatus = SetPackageUpdateState(pDeviceID,WIMAX_API_PACKAGE_UPDATE_ACCEPTED);
				if ( wmxStatus != WIMAX_API_RET_SUCCESS )
				{
						PrintWmxStatus(wmxStatus);
				}
				sem_wait(&semAPDOupdates);

			}
			if((consent=='N')||(consent=='n'))
			{
				wmxStatus = SetPackageUpdateState(pDeviceID,WIMAX_API_PACKAGE_UPDATE_DENIED);
				if ( wmxStatus != WIMAX_API_RET_SUCCESS )
				{
						PrintWmxStatus(wmxStatus);
				}
			}

			wmxStatus = UnregisterPUMACallback(pDeviceID);
			if (WIMAX_API_RET_SUCCESS != wmxStatus) {
				PrintWmxStatus(wmxStatus);
	}
			}

    return 0;
}

void checkforAPDOupdates(WIMAX_API_DEVICE_ID_P pDeviceID)
{
 	char retbuffer[NAME_MAX];

	WIMAX_API_RET wmxStatus;
#if 0
	wmxStatus = APDOupdates(pDeviceID,retbuffer,NAME_MAX);
#endif
	if(wmxStatus==WIMAX_API_RET_SUCCESS)
	{
		if(retbuffer[0]!=0)
		printf("\nAPDO Updates are Available. Please run \"wimaxcu update\"\n\n");
	}


}

/*
 * Function:     GetProvStatus
 * Description:  Retrive the provisioning status
 * Return:       0 for success,
                 1 for general command failure, or
                 2 for non-command related failure
 */
int GetProvStatus(WIMAX_API_DEVICE_ID_P pDeviceID, char *str_nspid)
{
	WIMAX_API_RET wmxStatus = WIMAX_API_RET_SUCCESS;
	WIMAX_API_NSP_INFO_P pNspInfo = NULL;
	UINT32 numOfNSPs = MAX_DEVICE;
	char tmp_nspID_str[MAX_NSP_ID_LEN];
	BOOL found_nsp = FALSE;
	BOOL provStatus = FALSE;
	int i;

	pNspInfo = (WIMAX_API_NSP_INFO_P )malloc(MAX_LEN * sizeof(WIMAX_API_NSP_INFO));
	if (pNspInfo == NULL) {
		printf("ERROR: Internal failure\n");
	return 2;
	}

	// find the nsp name from the given nsp id
	wmxStatus = GetNetworkList(pDeviceID, pNspInfo, &numOfNSPs);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		printf("ERROR: Retriving the Network List was unsuccessfull");
		PrintWmxStatus(wmxStatus);
		free(pNspInfo);
	return 2;
	}

	if (numOfNSPs == 0) {
		printf("WARNING: Cannot find any available network.\nPlease run \"wimaxcu scan\" to update the Network List\n");
		free(pNspInfo);
	return 2;
	}

	for (i = 0; i < numOfNSPs; i++) {
		sprintf(tmp_nspID_str,"%d",pNspInfo[i].NSPid);
		if (strcmp(tmp_nspID_str,str_nspid) == 0) {
			found_nsp = TRUE;
			break;
		}
	}

	if (found_nsp == FALSE) {
		printf("WARNING: Network ID (%s) is not in the current known list.\nVerify the Network ID or run \"wimaxcu scan\" to refresh the network list.\n", str_nspid);
		free(pNspInfo);
	return 2;
	}

	wmxStatus = GetProvisioningStatus(pDeviceID, pNspInfo[i].NSPName, &provStatus);
	if  (wmxStatus != WIMAX_API_RET_SUCCESS ) {
		printf("ERROR: Retriving Provisioning status was unsuccessfull\n");
        free (pNspInfo);
        return 1;
	} else {
		printf("Provision Status: %s(%s) is ", pNspInfo[i].NSPName, str_nspid);
		if(provStatus == TRUE)
			printf("Provisioned.\n");
		else
			printf("Not Provisioned.\n");
	}
	free (pNspInfo);
    return 0;
}


/*
 * Function:     GetSPLockStatus
 * Description:  Get the service provider's device lock status
 * Return:       0 for success or 1 for failure
 */
int GetSPLockStatus(WIMAX_API_DEVICE_ID_P pDeviceID)
{
	WIMAX_API_LOCK_STATUS LockStatus = WIMAX_API_DEVICE_UNLOCKED;
	WIMAX_API_RET wmxStatus = WIMAX_API_RET_SUCCESS;
	char NSPName[MAX_SIZE_OF_NSP_NAME];

	// Get the NSP Name from user
	wmxStatus = GetServiceProviderLockStatus(pDeviceID, &LockStatus,  NSPName);
	if ( wmxStatus == WIMAX_API_RET_SUCCESS) {
		if (LockStatus == WIMAX_API_DEVICE_LOCKED) {
			printf("Lock Status: Device is locked for %s Network\n", NSPName);
		} else {
			printf("Lock Status: Device is unlocked.\n");
		}
	} else {
		PrintWmxStatus(wmxStatus);
        return 1;
    }
    return 0;
}


/*
 * Function:     GetContactInfo
 * Description:  Get the contact info of given NSP
 * Return:       0 for success or 1 for failure
 */
int GetContactInfo(WIMAX_API_DEVICE_ID_P pDeviceID, char *str_nspid)
{
	WIMAX_API_RET wmxStatus = WIMAX_API_RET_SUCCESS;
	WIMAX_API_CONTACT_INFO* pContactInfo = NULL;
	WIMAX_API_NSP_INFO_P pNspInfo = NULL;
	UINT32 SizeOfContactList = MAX_PROFILE;
	UINT32 numOfNSPs = MAX_DEVICE;
	char tmp_nspID_str[MAX_NSP_ID_LEN];
	BOOL found_nsp = FALSE;
	int i, cmd;
    int ret = 0;

	pNspInfo = (WIMAX_API_NSP_INFO_P )malloc(MAX_LEN * sizeof(WIMAX_API_NSP_INFO));
	if (pNspInfo == NULL) {
		printf("ERROR: Internal failure.\n");
	return 1;
	}

	// find the nsp name from the given nsp id
	wmxStatus = GetNetworkList(pDeviceID, pNspInfo, &numOfNSPs);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		printf("ERROR: Retriving the Network list was unsuccessfull");
		PrintWmxStatus(wmxStatus);
	        free(pNspInfo);
	return 1;
	}

	if (numOfNSPs == 0) {
		printf("WARNING: Cannot find any available network.\nPlease run \"wimaxcu scan\" to update the Network List\n");
		free(pNspInfo);
	return 1;
	}

	for (i = 0; i < numOfNSPs; i++) {
		sprintf(tmp_nspID_str,"%d",pNspInfo[i].NSPid);
	  	if (strcmp(tmp_nspID_str,str_nspid) == 0) {
			found_nsp = TRUE;
			break;
		}
	}

	if (found_nsp == FALSE) {
		printf("WARNING: Cannot find the Network ID(%s) in the current known Network list.\nVerify the Network ID or Please run \"wimaxcu scan\" to update the Newtork List.\n", str_nspid);
		free(pNspInfo);
	return 1;
	}

	pContactInfo = (WIMAX_API_CONTACT_INFO_P)malloc(sizeof (WIMAX_API_CONTACT_INFO)*MAX_PROFILE);
	if (pContactInfo == NULL) {
		printf("ERROR: INternal failure\n");
		free(pNspInfo);
	return 1;
	}

	wmxStatus = GetContactInformation(pDeviceID, pNspInfo[i].NSPName, pContactInfo,&SizeOfContactList);
	if  (wmxStatus != WIMAX_API_RET_SUCCESS ) {
		printf("ERROR: Retriving the Contact Information was unsuccessfull\n");
        ret = 1;
	} else {
		printf("%s Contact Information:\n", pNspInfo[i].NSPName);
		if (SizeOfContactList > 0) {
			for ( cmd = 0; cmd <SizeOfContactList; cmd++ ) {
				printf("\tTitle: %s\n", pContactInfo[cmd].textForURI);
				printf("\tURL  : %s\n",pContactInfo[cmd].URI );
			}
            ret = 0;
	} else {
			printf("Contact Information Un-Available.\n");
            ret = 1;
		}
	}

	free (pNspInfo);
	free (pContactInfo);

    return ret;
}

void GetODMInfo(WIMAX_API_DEVICE_ID_P pDeviceID)
{
	int i;
	WIMAX_API_RET wmxStatus;
	WIMAX_API_BINARY_BLOB bin_blob;
	UINT32 bin_blob_size;
	bin_blob_size = sizeof(bin_blob);
	//BinaryBlob = malloc(sizeof(BinaryBlob));
	wmxStatus = GetODMInformation(pDeviceID, bin_blob ,&bin_blob_size);
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

void GetNVMInfo(WIMAX_API_DEVICE_ID_P pDeviceID)
{
	WIMAX_API_NVM_VERSION NVMImageVersion;
	WIMAX_API_RET wmxStatus;
	wmxStatus = GetNVMImageVersion(pDeviceID,&NVMImageVersion);

	if(wmxStatus != WIMAX_API_RET_SUCCESS)
	{
		printf("ERROR: Failed to get NVM image version\n");
		PrintWmxStatus(wmxStatus);
		return 1;
	}

	PrintNVMImageVersion(&NVMImageVersion);

	return 0;
}

void GetIPInterface(WIMAX_API_DEVICE_ID_P pDeviceID)
{
	WIMAX_API_RET wmxStatus;
	WIMAX_API_INTERFACE_INFO InterfaceInfo;
	wmxStatus = GetIPInterfaceIndex(pDeviceID,&InterfaceInfo );
	if(wmxStatus==WIMAX_API_RET_SUCCESS)
	{
		//printf("%s",InterfaceInfo );
	}
}

void SetFastReconnect(WIMAX_API_DEVICE_ID_P pDeviceID,BOOL isEnabled)
{
	WIMAX_API_RET wmxStatus;


	wmxStatus = SetFastReconnectCapabilityStatus(pDeviceID, isEnabled);
	if(wmxStatus==WIMAX_API_RET_SUCCESS)
	{
		if (isEnabled==0)
		printf("Fast Reconnect Disabled\n");
		else
		printf("Fase Reconnect Enabled\n");

	}
	else
	{
		printf("Failed to set Fast Reconnect settings\n");
	}
}

void GetFastReconnect(WIMAX_API_DEVICE_ID_P pDeviceID)
{
	WIMAX_API_RET wmxStatus;
	 BOOL isEnabled;

	wmxStatus = GetFastReconnectCapabilityStatus(pDeviceID,&isEnabled);

	if(wmxStatus==WIMAX_API_RET_SUCCESS)
	{
		if (isEnabled==0)
		printf("Fast Reconnect Disabled\n");
		else if(isEnabled ==1)
		printf("Fase Reconnect Enabled\n");

	}
}

void SetConnectedAsCurrent(WIMAX_API_DEVICE_ID_P pDeviceID,BOOL isEnable)
{
	WIMAX_API_RET wmxStatus;
	wmxStatus = SetConnectedAsCurrentPreferredCapabilityStatus(pDeviceID,isEnable);
	if(wmxStatus==WIMAX_API_RET_SUCCESS)
	{
		if (isEnable==0)
		printf("Current Connected Network Preferred settings are disabled\n");
		else if(isEnable ==1)
		printf("Current Connected Network Preferred settings are enabled\n");

	}
	else
		printf("Failed to set preferred settings\n");

}
void GetConnectedAsCurrent(WIMAX_API_DEVICE_ID_P pDeviceID)
{
	WIMAX_API_RET wmxStatus;
	BOOL isEnable;
	wmxStatus = GetConnectedAsCurrentPreferredCapabilityStatus(pDeviceID, &isEnable);
	if(wmxStatus==WIMAX_API_RET_SUCCESS)
	{
		if (isEnable == FALSE)
		printf("Current Connected Network Preferred settings are disabled\n");
		else
		printf("Current Connected Network Preferred settings are enabled\n");
	}
    else
    {
        printf("Failed to get preferred settings\n");
	}


}

void GetApiExVersion(WIMAX_API_DEVICE_ID_P pDeviceID)
{
	UINT32 WmxApiExVersion;
	WIMAX_API_RET wmxStatus;
	wmxStatus = GetWmxApiExVersion(&WmxApiExVersion);
	if(wmxStatus == WIMAX_API_RET_SUCCESS)
	{
		printf("%d\n",WmxApiExVersion);
	}
}

void SetCoexMode(WIMAX_API_DEVICE_ID_P pDeviceID,WIMAX_API_COEXISTENCE_MODE coexMode)
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
	wmxStatus = SetCoexistenceMode(pDeviceID,coexMode);
	// WSS LINUX START - EVP Specific
#ifdef EVP_SUPPORTS_CM_ONLY
	} else {
		printf("Could not change Coex to XOR Mode\n");
		printf("EVP hardware does not support XOR Mode\n");
		return;
	}
#endif
	// WSS LINUX End
	if(wmxStatus == WIMAX_API_RET_SUCCESS)
	{
		switch(coexMode)
		{
			case MODE_XOR:
				printf("Coex changed to XOR Mode\n");
			break;
			case MODE_CM:
				printf("Coex changed to CM Mode\n");
			break;
		}
	}
	else
		printf("Failed to set the Co-Ex Mode\n");
}


void GetCoexMode(WIMAX_API_DEVICE_ID_P pDeviceID)
{
	WIMAX_API_RET wmxStatus;
	WIMAX_API_COEXISTENCE_MODE CoexMode;
	wmxStatus = GetCoexistenceMode(pDeviceID, &CoexMode);
	if(wmxStatus == WIMAX_API_RET_SUCCESS)
	{
		switch(CoexMode)
		{
			case MODE_XOR:
				printf("Coex is set to MODE_XOR\n");
			break;
			case MODE_CM:
				printf("Coex is set to MODE_CM\n");
			break;
		}
	}
}


void Help()
{
    printf("Usage: wimaxcu [OPTION]\n\n");
    printf("Option: Use on of the following options\n");
    printf("\tactivate <network_id>\t\tactivate a specific network\n");
    printf("\tgetipinterface\t\tDisplays the IP of an interface.[Currently not supported]\n");
    printf("\tupdate\t\tUpdates any APDO related packages. [Currently not supported]\n");
    printf("\tconnect profile <profile_id>\t\tconnect with a specific profile\n");
    printf("\tconnect network <network_id>\t\tconnect with a specific network\n");
    printf("\tconnectmode connect [auto|manual] scan [semi|manual]\t\tdisplay or change the connection/scan mode\n");
    printf("\tdconnect\t\tdisconnect from a network\n");
    printf("\tdeactivate <profile_id>\t\tdeactivate a specific profile\n");
    printf("\tinfo [version|device|stats|contact <network_id>]\t\tdisplay the various information\n");
    printf("\tscan [wide|preferred]\t\tdisplay the available network list\n");
    printf("\tplist\t\tdisplay the profile list\n");
    printf("\treset [factory | device [curently not implemented]]\t\tresets to factory or deivce settings\n");	
    printf("\troff\t\tturn off the radio\n");
    printf("\tron\t\tturn on the radio\n");
    printf("\tstatus [system|connect|link|radio|lock]\t\tdisplay the various status information\n");
    printf("\tgetccap\t\tdisplay the current connected preferred network settings\n");
    printf("\tsetccap [enable|disable]\t\tenable/disable the current connected preferred network settings\n");
    printf("\tsetfastreconnect [enable/disable]\t\tenable/disable the fast reconnect mode.\n");
    printf("\tgetfastreconnect\t\tdisplay the current settings for fast reconnectmode.\n");
    printf("\tunlock <unlock_code>\t\tunlocks the device.\n");
    printf("\thelp\t\tdisplays help\n");
}

void print_callstack_to_file(int sig, siginfo_t *info,
				   void *secret) 
{
	void *trace[16];
  	char **messages = (char **)NULL;
  	int i, trace_size = 0;
	//static int flag=0;
  	ucontext_t *uc = (ucontext_t *)secret;
	FILE *fp;	
	BOOL res;
//	 printf("Came here %d\n", __LINE__);
	char command[MAX_STR_LEN + MAX_FILENAME_LEN];
	 /* Do something useful with siginfo_t */
  	if (sig != SIGINT) {
		syslog(LOG_ERR,"Got signal %d#92", sig);
//		 printf("Came here %d\n", __LINE__);
		return;
	}
	res = GetConfig_LogPath(gcLogFilePathName, MAX_FILENAME_LEN);   
	if (res == FALSE) {
//		 printf("Came here %d\n", __LINE__);
		OSAL_sprintf(gcLogFilePathName, "/tmp");
	}
	strcat(gcLogFilePathName, "/callstack_wimaxcu.log");
	if(OSAL_fopen(&fp, gcLogFilePathName, "a", 0) < 0) {
		syslog(LOG_ERR, "Got signal %d, faulty address is %p, "
		"from %p", sig, info->si_addr, 
		 uc->uc_mcontext.gregs[REG_EIP]);
		syslog(LOG_ERR, "Could not open a file %s to log call stack");
//		printf("Came here %d\n", __LINE__);
		
  		return;
	}
	sprintf(command, "/bin/date > %s",gcLogFilePathName); 
	 //printf("Came here %d\n", __LINE__);
	system(command); 
	fprintf(fp, "==================================================================================\n");
	fprintf(fp, "If Faulty address is in wimaxd excution segment \n");
	fprintf(fp, "Use addr2line to decode the address info into file name and line no\n");
	fprintf(fp, "For Example \n");
	fprintf(fp, "$> sudo addr2line -e /usr/bin/wimaxd 806f5fe \n");
	fprintf(fp, "If Faulty address is in shared object file \n");
	fprintf(fp, "$> sudo objdump -l -d -M intel /usr/lib/libWmxInstrument.so.0 > ./libinstru_dis\n");
	fprintf(fp, "Use the function name and offset to function and search file above for the line no \n");
	fprintf(fp, "==================================================================================\n\n");
	
	fprintf(fp, "Got signal %d, faulty address is %p, "
		"from %p\n", sig, info->si_addr, 
		 uc->uc_mcontext.gregs[REG_EIP]);
	// printf("Came here %d\n", __LINE__);
  	
  	trace_size = backtrace(trace, 16);
  	/* overwrite sigaction with caller's address */
  	trace[1] = (void *) uc->uc_mcontext.gregs[REG_EIP];

  	messages = backtrace_symbols(trace, trace_size);
  	/* skip first stack frame (points here) */
  	fprintf(fp,"[bt] Execution path: \n");	
  	for (i=1; i<trace_size; ++i)
		fprintf(fp, "[bt] %s  \n", messages[i]);
	
	
 	fclose(fp);
	
}

void wimaxcu_stop_signal_handler(int sig)
{
    	// signals are captured
    	syslog(LOG_INFO, ":wimaxcu recieved signal %d", sig);
	Finalize(&DeviceID);
	exit(0);
    	// sleep(20);
}

void wimaxcu_signal_handler(int sig, siginfo_t *info,
				   void *secret) 
{
    // signals are captured
  	static no_of_signals = 0;
	
	if(no_of_signals >= 1)  {
		printf("wimaxcu recieved second signal no %d \n", sig);
		print_callstack_to_file(sig, info, secret);
		exit(0);
	} else {
		printf("wimaxcu recieved first signal no %d \n",sig);
	}

	no_of_signals++;
	printf("Call stack is added to file \n");
	printf("Please check /var/log/wimax folder \n");

 	print_callstack_to_file(sig, info, secret);
	wimaxcu_stop_signal_handler(sig);
	
}

/*
 * Function: main
 * Description: main function
*/
int main(int argc, char *argv[])
{
    int ret = 0;
    WIMAX_API_RET wmxStatus;

	parsed_cmd out_cmd;
	struct sigaction sa;


    // checking user priviledge
	// Disabled permission checking so non-root can run it
    //if (geteuid() != (uid_t) 0) {
//	fprintf(stderr,
//		"ERROR: You do not possess sufficient privileges to perform this action.\n");
//		return 1;
//	}


    // validate user command
    if (validate_cmd(argc, argv, &out_cmd) != 0) {
        	Help();
        	return 1;
    	}

    if (out_cmd.cmd == CMD_HELP) {
        	Help();
	return 0;
    	}

	sa.sa_sigaction = (void *)wimaxcu_signal_handler;
    	sigemptyset (&sa.sa_mask);
    	sa.sa_flags = SA_RESTART | SA_SIGINFO;

    	sigaction(SIGUSR1, &sa, NULL);  

    	signal(SIGINT, wimaxcu_stop_signal_handler);
    	signal(SIGTERM, wimaxcu_stop_signal_handler);
    	signal(SIGPIPE, SIG_IGN);
    	signal(SIGUSR1, SIG_IGN); 

	    memset(&DeviceID, 0, sizeof(WIMAX_API_DEVICE_ID));
	DeviceID.privilege = WIMAX_API_PRIVILEGE_READ_WRITE;

    // Initialize the SDK (CommonAPI)
    wmxStatus = Initialize(&DeviceID);
    if(WIMAX_API_RET_SUCCESS != wmxStatus) {
        printf("ERROR: Make sure WiMAX Network Service is running.\n");
        return 1;
    }
	// Kalyan 5.0.09 merge
	// This delay will allow the Initialize to init everything in its threads
	//sleep(1);
  	// Execute the command
    ret = cmd_handler(&DeviceID, &out_cmd);


    // Finalize the SDK
    	Finalize(&DeviceID);

    return ret;
}

int wmxcu_sem_timeout(sem_t* s,int milliseconds)
{
#define TIMEVAL_TO_TIMESPEC(tv, ts)	{	\
	(ts)->tv_sec = (tv)->tv_sec;	\
	(ts)->tv_nsec = (tv)->tv_usec * 1000; 	\
}

	struct timespec ts;
	struct timeval tv;
	int ret = -1;

 	gettimeofday(&tv, NULL);
	TIMEVAL_TO_TIMESPEC(&tv, &ts);

	// Split the incoming millisecs into seconds and nano-seconds struct as required by the timedjoin method

	ts.tv_sec += (milliseconds / 1000);
	ts.tv_nsec += ((milliseconds % 1000) * 1000 * 1000);	// 1 ms = 1000000 ns
	if (ts.tv_nsec >= 1000000000) {
		ts.tv_nsec -= 1000000000;
		++ts.tv_sec;
	}
	while ((ret = sem_timedwait(s, &ts)) == -1 && errno == EINTR)
 		continue; /* Restart when interrupted by handler */

	if (ret == -1)
	{
		if (errno == ETIMEDOUT)
		{
			 return 1;
		}
		 else
			printf ("ERROR: Internal failure\n");

	 }
	return 0;
}

