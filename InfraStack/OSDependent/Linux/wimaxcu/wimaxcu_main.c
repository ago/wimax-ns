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

/* 
* File : wimaxcu_main.c
* Description : File conatins source for Intialization and Finalization 
* routines and misc commands 
*/
#include "wimaxcu.h"
#include "wimaxcu_util.h"


#include <signal.h>
#include <execinfo.h>
#include <sys/types.h>
#include <sys/syslog.h>
#include <unistd.h>
#include <dirent.h>
#include <ctype.h>
// Globals...

//static sem_t semWideScan;
sem_t g_semConnectionUtility;
sem_t g_semAPDOactivation;
sem_t g_semAPDOupdates;
sem_t g_semRfState;
sem_t g_semConnectCompleted;
pthread_mutex_t g_console_owner_mutex;
// static BOOL g_UpaterLaunched = FALSE;

//int gbl_stopscan_called=0;

WIMAX_API_DEVICE_STATUS g_devState;

char g_sznspName[MAX_SIZE_OF_NSP_NAME];
char g_foOperationType[NAME_MAX];
// for user command for activation
// time out sem function
int wmxcu_sem_timeout(sem_t * s, int milliseconds);

int g_noNetworksFound = 1;
int g_searchProgress = 0;



WIMAX_API_DEVICE_ID gbl_device_id;

// Set preferred NSP
UINT32 g_preferred_NSP_ID = 0;
/*
 * Function:     wimaxcu_reset_device
 * Description:  Reset the wimax device
 * Return:       0 for success or 1 for failure
 *
 * Note: this will return 1 always for now since not implemented
 */
int wimaxcu_reset_device(WIMAX_API_DEVICE_ID_P p_device_id)
{
	WIMAX_API_RET wmxStatus;

	wmxStatus = CmdResetWimaxDevice(p_device_id);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		PrintWmxStatus(wmxStatus);
		return 1;
	}

	printf("This feature is not implemented yet.\n");
	return 1;
}

/*
 * Function:     wimaxcu_restore_factory_settings
 * Description:  Reset to the factory default setting
 * Return:       0 for success or 1 for failure
 */
int wimaxcu_restore_factory_settings(WIMAX_API_DEVICE_ID_P p_device_id)
{
	WIMAX_API_RET wmxStatus;
	WIMAX_API_DEVICE_STATUS DeviceStatus;
	WIMAX_API_CONNECTION_PROGRESS_INFO ConnectionProgressInfo;
               
	wmxStatus = GetDeviceStatus(p_device_id, &DeviceStatus, &ConnectionProgressInfo);
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
	
	wmxStatus = CmdResetToFactorySettings(p_device_id);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		PrintWmxStatus(wmxStatus);
		return 1;
	}

	printf("WiMAX system is set to factory settings.\n");
	return 0;
}

/*
 * Function:	ind_device_update_cb
 * Description: This a callback function. this function is called by 
		CommonAPI when the device status is changed 
 * Return:	Nothing
 */

void ind_device_update_cb(WIMAX_API_DEVICE_ID_P pDeviceId,
			  WIMAX_API_DEVICE_STATUS systemStatus,
			  WIMAX_API_STATUS_REASON statusReason,
			  WIMAX_API_CONNECTION_PROGRESS_INFO
			  connectionProgressInfo)
{

	g_devState = systemStatus;

	switch (systemStatus) {
	case WIMAX_API_DEVICE_STATUS_Ready:
	case WIMAX_API_DEVICE_STATUS_Scanning:
	case WIMAX_API_DEVICE_STATUS_Connecting:
	case WIMAX_API_DEVICE_STATUS_Data_Connected:
		sem_post(&g_semRfState);
		break;

	case WIMAX_API_DEVICE_STATUS_RF_OFF_HW_SW:
		printf("SW and HW Radion is turned off \n");
		sem_post(&g_semConnectCompleted);
		sem_post(&g_semConnectionUtility);
		sem_post(&g_semRfState);
		break;
	case WIMAX_API_DEVICE_STATUS_RF_OFF_HW:
		printf("HW Radio is turned off\n");
		sem_post(&g_semConnectCompleted);
		sem_post(&g_semConnectionUtility);
		break;
	case WIMAX_API_DEVICE_STATUS_RF_OFF_SW:
		printf("SW Radio is turned off \n");
		sem_post(&g_semConnectCompleted);
		sem_post(&g_semConnectionUtility);
		sem_post(&g_semRfState);
		break;
	default:
		break;
	}
}

/*
 * Function:	ind_rf_taken_cb
 * Description: This a callback function. this function is called by 
		CommonAPI when the radio ia taken away by WiFi 
 * Return:	Nothing
 */
void ind_rf_taken_cb(WIMAX_API_DEVICE_ID_P p_device_id)
{
	// int i;

	// Radio is taken away by WiFi
	printf("Could not complete Scan, Radio is taken by WiFi\n");
	printf("Please try scanning later \n");
	// release the semaphore
	sem_post(&g_semConnectionUtility);
}

/*
 * Function:     Initialize
 * Description:  Initialize the WiMAX CommonAPI
 */
WIMAX_API_RET wimaxcu_initialize(WIMAX_API_DEVICE_ID_P p_device_id)
{
	WIMAX_API_RET wmxStatus;
	WIMAX_API_HW_DEVICE_ID HwDeviceIdList[MAX_DEVICE];
	UINT32 numDevice = MAX_DEVICE;

	memset(HwDeviceIdList, 0, sizeof(WIMAX_API_HW_DEVICE_ID) * MAX_DEVICE);

	// open the Common API and initialize iwmax sdk, agents
	wmxStatus = WiMaxAPIOpen(p_device_id);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		return wmxStatus;
	}

	// get the list of the device before open the device
	wmxStatus = GetListDevice(p_device_id,
				  (WIMAX_API_HW_DEVICE_ID_P) HwDeviceIdList,
				  &numDevice);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		return wmxStatus;
	}

	p_device_id->deviceIndex = HwDeviceIdList[0].deviceIndex;

	// Open the device to get the permission
	wmxStatus = WiMaxDeviceOpen(p_device_id);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		return wmxStatus;
	}
	if (pthread_mutex_init(&g_console_owner_mutex, NULL) != 0) {
		printf("Internal Error!\n");
		return WIMAX_API_RET_FAILED;
	}

	if (sem_init(&g_semConnectionUtility, 0, 0) == -1) {
		printf("Internal Error!\n");
		return WIMAX_API_RET_FAILED;
	}

	if (sem_init(&g_semRfState, 0, 0) == -1) {
		printf("Internal Error!\n");
		return WIMAX_API_RET_FAILED;
	}

	if (sem_init(&g_semConnectCompleted, 0, 0) == -1) {
		printf("Internal Error!\n");
		return WIMAX_API_RET_FAILED;
	}

	wmxStatus =
	    SubscribeDeviceStatusChange(p_device_id, &ind_device_update_cb);
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
void wimaxcu_finalize(WIMAX_API_DEVICE_ID_P p_device_id)
{
	UnsubscribeDeviceStatusChange(p_device_id);

	WiMaxDeviceClose(p_device_id);
	WiMaxAPIClose(p_device_id);

	// Let all the call backs get closed before destroying sem
	sem_destroy(&g_semConnectionUtility);
	sem_destroy(&g_semRfState);
	sem_destroy(&g_semConnectCompleted);
	pthread_mutex_destroy(&g_console_owner_mutex);

}

/*
 * Function:     wimaxcu_main_help
 * Description:  Displays the help 
*/

void wimaxcu_main_help()
{
    printf("Usage: wimaxcu [OPTION]\n\n");
    printf("Option: Use on of the following options\n");
    printf("\tactivate <network_id>\t\tactivate a specific network\n");
    //printf("\tgetipinterface\t\tDisplays the IP of an interface.[Currently not supported]\n");
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
    printf("\tstopscan\t\tStops user initiated scan.\n");
    printf("\thelp\t\tdisplays help\n");
}


void wimaxcu_stop(int sig)
{
	wimaxcu_finalize(&gbl_device_id);
	exit(0);
}
void wimaxcu_stop_signal_handler(int sig)
{
	WIMAX_API_RET wmxStatus;
    	// signals are captured
    	syslog(LOG_INFO, ":wimaxcu recieved signal %d", sig);
	//printf("wimaxcu recieved signal %d\n", sig);
	printf("interrupt (ctrl+c) within two seconds to exit wimaxcu\n");
	wmxStatus = CmdStopScan(&gbl_device_id);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		printf("ERROR: Failed to stop scanning.\n");
		return;
	}
	(void)signal(SIGINT,wimaxcu_stop);
	
}

/*
 * Function: main
 * Description: main function calls functions for intialization and 
 * command verification, excution and finalization
*/
int main(int argc, char *argv[])
{
	int ret = 0;
	WIMAX_API_RET wmxStatus;
	
	parsed_cmd out_cmd;

	//checking user priviledge
	//Disabled permission checking so non-root can run it
	//      if (geteuid() != (uid_t) 0) {
	//              fprintf(stderr,
	//                      "ERROR: You do not possess sufficient privileges to perform this action.\n");
	//              return 1;
	//      }

	// validate user command
	if (validate_cmd(argc, argv, &out_cmd) != 0) {
		wimaxcu_main_help();
		return 1;
	}
	// If user requested to diplay the help
	if (out_cmd.cmd == CMD_HELP) {
		wimaxcu_main_help();
		return 0;
	}
	memset(&gbl_device_id, 0, sizeof(WIMAX_API_DEVICE_ID));
	// Request for READ_WRITE Permissions
	// TODO: Kalyan Can we request for permissions based on the command?
	// For example for status Read permission is sufficient.
	gbl_device_id.privilege = WIMAX_API_PRIVILEGE_READ_WRITE;

	//Signal to handle Ctrl+C
	signal(SIGINT, wimaxcu_stop_signal_handler);
	signal(SIGTERM, wimaxcu_stop_signal_handler);

	// Initialize the SDK (CommonAPI)
	wmxStatus = wimaxcu_initialize(&gbl_device_id);
	if (WIMAX_API_RET_SUCCESS != wmxStatus) {
		printf("ERROR: Make sure WiMAX Network Service is running.\n");
		return 1;
	}
	// Kalyan 5.0.09 merge
	// This delay will allow the Initialize to init everything in its threads
	// sleep(1);
	// Execute the command
	ret = cmd_handler(&gbl_device_id, &out_cmd);
	// Finalize the SDK
	wimaxcu_finalize(&gbl_device_id);

	return ret;
}

/*
 * Function: wmxcu_sem_timeout
 * Description: This function converts the time in milliseconds to 
 * to the time format required for sem_timed_wait
 * 
 * Return values: 0 if sempahore is claimed -1 if timedout
*/
int wmxcu_sem_timeout(sem_t * s, int milliseconds)
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
		continue;	/* Restart when interrupted by handler */

	if (ret == -1) {
		if (errno == ETIMEDOUT) {
			return 1;
		} else
			printf("ERROR: Internal failure\n");

	}
	return 0;
}
