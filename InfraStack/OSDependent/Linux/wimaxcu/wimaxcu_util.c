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
#include <stdio.h>
#include <wchar.h>
#include <string.h>

#include "wimaxcu_defs.h"
#include "wimaxcu.h"
#include "wimaxcu_util.h"

static char * SIGNAL_QUALITY_EXCELLENT = "Excellent";
static char * SIGNAL_QUALITY_VERY_GOOD = "Very Good";
static char * SIGNAL_QUALITY_GOOD = "Good";
static char * SIGNAL_QUALITY_FAIR = "Fair";
static char * SIGNAL_QUALITY_POOR = "Poor";
static char * SIGNAL_QUALITY_NONE = "None";

// convert wide char to char
// Make sure destination is cleared before this function is called by callee
size_t wchar2char(char *dest, const wchar_t * src)
{
    size_t ret;
    mbstate_t mbstate;
    const wchar_t *wcsSrc = src;

    if (dest == NULL || src == NULL)
        return -1;

    memset((void *)&mbstate, 0, sizeof(mbstate));

    ret = wcsrtombs(dest, &wcsSrc, wcslen(src), &mbstate);

    return ret;
}

// convert char to wide char
// Make sure destination is cleared before this function is called by callee
size_t char2wchar(wchar_t * dest, const char *src)
{
    size_t ret;
    mbstate_t mbstate;
    const char *csSrc = src;

    if (dest == NULL || src == NULL)
        return -1;

    memset((void *)&mbstate, 0, sizeof(mbstate));

    ret = mbsrtowcs(dest, &csSrc, strlen(src), &mbstate);

    return ret;
}


/***************************************************************************
 *   Print Wmx Status WIMAX_API_RET
 ***************************************************************************/
void PrintWmxStatus(WIMAX_API_RET wmxStatus)
{
	//printf("WiMAX Status: ");
	switch (wmxStatus) {

	case WIMAX_API_RET_FIRST_COMMON_ERROR:
		printf("Common Error.\n");
		break;

	case WIMAX_API_RET_SUCCESS:
		printf("Success.\n");
		break;

	case WIMAX_API_RET_FAILED:
		printf("Operation Failed.\n");
		break;

#if 0
	case WIMAX_API_RET_TIMED_OUT:
		printf("Timed out. Check the card in place.");
		break;
#endif

	case WIMAX_API_RET_BUFFER_SIZE_TOO_SMALL:
		printf("Buffer is too small.\n");
		break;

	case WIMAX_API_RET_PERMISSON_DENIED:
		printf("Permission Denied.\n");
		break;

	case WIMAX_API_RET_INVALID_DEVICE:
		printf("Invalid Device\n");
		break;

	case WIMAX_API_RET_INVALID_PARAMETER:
		printf("Invalid Parameter(s).\n");
		break;

	case WIMAX_API_RET_ALREADY_CONNECTED:
		printf("Already connected.\n");
		break;

	case WIMAX_API_RET_LINK_NOT_CONNECTED:
		printf("Link not connected.\n");
		break;

	case WIMAX_API_RET_NETWORK_PROHIBITED:
		printf("Operation is prohibited.\n");
		break;

	case WIMAX_API_RET_INTEL_NO_RF:
		printf("RF is taken away by WiFi.\n");
		break;

	case WIMAX_API_RET_DEVICE_MISSING:
		printf("Device is missing.\n");
		break;

	case WIMAX_API_RET_INVALID_PROFILE:
		printf("Invalid profile.\n");
		break;

	case WIMAX_API_RET_ROAMING_NOT_ALLOWED:
		printf("Roaming is not allowed.\n");
		break;

	case WIMAX_API_RET_CONNECTION_IN_PROGRESS:
		printf("Connection in progress.\n");
		break;

	case WIMAX_API_RET_LAST_COMMON_ERROR:
		printf("Last common error.\n");
		break;

	default:
		printf("Unknown Error\n");
		break;
	}
}


/***************************************************************************
 *   Print Device Status WIMAX_API_DEVICE_STATUS
 ***************************************************************************/
void PrintDeviceStatus(WIMAX_API_DEVICE_STATUS DeviceStatus)
{
	//printf("Device Status: ");
	switch (DeviceStatus) {
	case WIMAX_API_DEVICE_STATUS_UnInitialized:
		printf("Device - Not Initialized.\n");
		break;

	case WIMAX_API_DEVICE_STATUS_RF_OFF_HW_SW:
		printf("Both HW and SW Radios are OFF.\n");
		break;

	case WIMAX_API_DEVICE_STATUS_RF_OFF_HW:
		printf("HW Radio is OFF.\n");
		break;

	case WIMAX_API_DEVICE_STATUS_RF_OFF_SW:
		printf("SW Radio is OFF.\n");
		break;

	case WIMAX_API_DEVICE_STATUS_Ready:
		printf("Ready.\n");
		break;

	case WIMAX_API_DEVICE_STATUS_Scanning:
		printf("Scanning...\n");
		break;

	case WIMAX_API_DEVICE_STATUS_Connecting:
		printf("Connecting...\n");
		break;

	case WIMAX_API_DEVICE_STATUS_Data_Connected:
		printf("Connected.\n");
		break;

	default:
		printf("Unknown state\n");
		break;
	}
}

/***************************************************************************
 *   Print WIMAX_API_CONNECTION_MODE
 ***************************************************************************/
void PrintUserConnectionMode(WIMAX_API_CONNECTION_MODE connectMode)
{
	printf("Connection and Scan Mode:\n");
	switch (connectMode) {
	case WIMAX_API_CONNECTION_SEMI_MANUAL_SCAN_MANUAL_CONNECT:
		printf("\tConnection:   manual\n");
        printf("\tScan:         semi-manual\n");
		break;

	case WIMAX_API_CONNECTION_SEMI_MANUAL_SCAN_AUTO_CONNECT:
        printf("\tConnection:   auto\n");
        printf("\tScan:         semi-manual\n");
        break;

	case WIMAX_API_CONNECTION_AUTO_SCAN_MANUAL_CONNECT:
        printf("\tConnection:   manual\n");
        printf("\tScan:         auto\n");
        break;

	case WIMAX_API_CONNECTION_AUTO_SCAN_AUTO_CONNECT:
        printf("\tConnection:   auto\n");
        printf("\tScan:         auto\n");
		break;

	case WIMAX_API_CONNECTION_MANUAL_SCAN_MANUAL_CONNECT:
		printf("\tConnection:   manual\n");
        printf("\tScan:         manual\n");
        break;

	default:
        printf("\tConnection:   unknown\n");
        printf("\tScan:         unknown\n");
		break;
	}
}


/***************************************************************************
 *   Print User Link Status
 ***************************************************************************/
void PrintUserLinkStatus(WIMAX_API_LINK_STATUS_INFO_P userLinkStatus)
{
	printf("Link Status:\n");
	printf("\tFrequency : %d KHz\n", userLinkStatus->centerFrequency);
	printf("\tSignal    : %s\n", PrintSignalQuality(userLinkStatus->CINR));
	printf("\tRSSI      : %d dBm\n", ConvertRSSI(userLinkStatus->RSSI));
	printf("\tCINR      : %d dB\n", ConvertCINR(userLinkStatus->CINR));
	printf("\tAvg TX PWR: %d dBm\n", ConvertTXPower(userLinkStatus->txPWR));
	printf("\tBS ID     : %02X:%02X:%02X:%02X:%02X:%02X\n", 
           userLinkStatus->bsId[0], userLinkStatus->bsId[1], userLinkStatus->bsId[2], 
           userLinkStatus->bsId[3], userLinkStatus->bsId[4], userLinkStatus->bsId[5]);
}

void PrintUserLinkStatusEx(WIMAX_API_LINK_STATUS_INFO_EX_P puserLinkStatus)
{
	printf("Link Status:\n");
	printf("\tFrequency : %d KHz\n", puserLinkStatus->centerFrequency);
	printf("\tLink Quality: %d \n", puserLinkStatus->linkQuality/100);
	printf("\tSignal    : %s\n", PrintSignalQuality(puserLinkStatus->CINR));
	printf("\tRSSI      : %d dBm\n", ConvertRSSI(puserLinkStatus->RSSI));
	printf("\tCINR      : %d dB\n", ConvertCINR(puserLinkStatus->CINR));
	printf("\tAvg TX PWR: %d dBm\n", ConvertTXPower(puserLinkStatus->txPWR));
	printf("\tBS ID     : %02X:%02X:%02X:%02X:%02X:%02X\n", 
           puserLinkStatus->bsId[0], puserLinkStatus->bsId[1], puserLinkStatus->bsId[2], 
           puserLinkStatus->bsId[3], puserLinkStatus->bsId[4], puserLinkStatus->bsId[5]);
}



/***************************************************************************
 *   Convert user input to Connection Mode
 ***************************************************************************/
int ConvertCharToConnectionMode (char *connect_mode, char* scan_mode,
                              WIMAX_API_CONNECTION_MODE* userConnectMode)
{
    CU_CONNECT_MODE cur_conn;
    CU_CONNECT_MODE cur_scan;
    
    // Get the current connection mode
    switch (*userConnectMode) {
        case WIMAX_API_CONNECTION_SEMI_MANUAL_SCAN_MANUAL_CONNECT:
            cur_scan = SCAN_SEMI;
            cur_conn = CONNECT_MANUAL;
            break;

        case WIMAX_API_CONNECTION_SEMI_MANUAL_SCAN_AUTO_CONNECT:
            cur_scan = SCAN_SEMI;
            cur_conn = CONNECT_AUTO;
            break;

        case WIMAX_API_CONNECTION_AUTO_SCAN_MANUAL_CONNECT:
            cur_scan = SCAN_AUTO;
            cur_conn = CONNECT_MANUAL;
            break;

        case WIMAX_API_CONNECTION_AUTO_SCAN_AUTO_CONNECT:
            cur_scan = SCAN_AUTO;
            cur_conn = CONNECT_AUTO;
            break;

        case WIMAX_API_CONNECTION_MANUAL_SCAN_MANUAL_CONNECT:
            cur_scan = SCAN_MANUAL;
            cur_conn = CONNECT_MANUAL;
            break;

        default:
            return -1;
            break;
    }
     // Update the connection mode with user input
    if (connect_mode != NULL)
    {
        if (strcasecmp(connect_mode, "manual") == 0)
        {
            cur_conn = CONNECT_MANUAL;
        }
	else if (strcasecmp(connect_mode, "auto") == 0)
        {
            cur_conn = CONNECT_AUTO;
        }
        else
        {
            return -1;
        }
    }
          
    if (scan_mode != NULL)
    {
        if (strcasecmp(scan_mode, "manual") == 0)
        {
            cur_scan = SCAN_MANUAL;
        }
        else if (strcasecmp(scan_mode, "semi") == 0)
        {
            cur_scan = SCAN_SEMI;
        }
        else if (strcasecmp(scan_mode, "auto") == 0)
        {
            cur_scan = SCAN_AUTO;
        }
        else
        {
            return -1;
        }                 
    }      
    
    // Find the correct connection mode
    if ((cur_scan == SCAN_AUTO) && (cur_conn == CONNECT_AUTO))
    {
        // WSS LINUX - currently this mode is not supported by SDK.
        //*userConnectMode = WIMAX_API_CONNECTION_AUTO_SCAN_AUTO_CONNECT;      
        return -2;
    } 
    else if ((cur_scan == SCAN_SEMI) && (cur_conn == CONNECT_AUTO))
    {
        *userConnectMode = WIMAX_API_CONNECTION_SEMI_MANUAL_SCAN_AUTO_CONNECT;      
    }
    else if ((cur_scan == SCAN_AUTO) && (cur_conn == CONNECT_MANUAL))
    {
        *userConnectMode = WIMAX_API_CONNECTION_AUTO_SCAN_MANUAL_CONNECT;      
    }
    else if ((cur_scan == SCAN_SEMI) && (cur_conn == CONNECT_MANUAL))
    {
        *userConnectMode = WIMAX_API_CONNECTION_SEMI_MANUAL_SCAN_MANUAL_CONNECT;      
    }
    else if ((cur_scan == SCAN_MANUAL) && (cur_conn == CONNECT_MANUAL))
    {
        *userConnectMode = WIMAX_API_CONNECTION_MANUAL_SCAN_MANUAL_CONNECT;      
    } 
    else if ((cur_scan == SCAN_MANUAL) && (cur_conn == CONNECT_AUTO))
    {
        return -2;
    } 
    else
    {
        return -1;
    }
    if (cur_conn == CONNECT_AUTO)
	return 1;
    return 0;
}

/***************************************************************************
 *   Print Connected NSP Info WIMAX_API_CONNECTED_NSP_INFO
 ***************************************************************************/
void PrintConnectedNSPInfo(WIMAX_API_CONNECTED_NSP_INFO_P pConnectedNSP)
{
	printf("Network Info: \n");
    	printf("\tID       : %d\n", pConnectedNSP->NSPid);
    
    	printf("\tName     : %s", pConnectedNSP->NSPName);
    	printf("\n");   
	
    	printf("\tRealm    : %s",  pConnectedNSP->NSPRealm);
    	printf("\n");   
    
	printf("\tSignal   : %s\n", PrintSignalQuality(pConnectedNSP->CINR));
	printf("\tRSSI     : %d dBm\n", ConvertRSSI(pConnectedNSP->RSSI));
    	printf("\tCINR     : %d dB\n", ConvertCINR(pConnectedNSP->CINR));
       	printf("\tActivated: ");   
	if (pConnectedNSP->activated)
		printf("Yes\n");
	else
		printf("No\n");
	
    	printf("\tNetwork Type  : ");
	switch (pConnectedNSP->networkType) {
	case WIMAX_API_HOME:
		printf("Home network\n");
		break;
	case WIMAX_API_PARTNER:
		printf("Partner network\n");
		break;
	case WIMAX_API_ROAMING_PARTNER:
		printf("Roaming partner network\n");
		break;
	default:
		printf("Unknown Network\n");
		break;
	}

}
/***************************************************************************
 *   Print Connected NSP Info WIMAX_API_CONNECTED_NSP_INFO
 ***************************************************************************/
void PrintConnectedNSPInfoEx(WIMAX_API_CONNECTED_NSP_INFO_EX_P pConnectedNSP)
{
	printf("Network Info: \n");
    	printf("\tID       : %ld\n", pConnectedNSP->NSPid);
    
    	printf("\tName     : %s", pConnectedNSP->NSPName);
    	printf("\n");   
	
    	printf("\tRealm    : %s",  pConnectedNSP->NSPRealm);
    	printf("\n");   
    
	printf("\tSignal   : %s\n", PrintSignalQuality(pConnectedNSP->CINR));
	printf("\tRSSI     : %d dBm\n", ConvertRSSI(pConnectedNSP->RSSI));
    	printf("\tCINR     : %d dB\n", ConvertCINR(pConnectedNSP->CINR));
       	printf("\tActivated: ");   
	if (pConnectedNSP->activated)
		printf("Yes\n");
	else
		printf("No\n");
	
    	printf("\tNetwork Type  : ");
	switch (pConnectedNSP->networkType) {
	case WIMAX_API_HOME:
		printf("Home network\n");
		break;
	case WIMAX_API_PARTNER:
		printf("Partner network\n");
		break;
	case WIMAX_API_ROAMING_PARTNER:
		printf("Roaming partner network\n");
		break;
	default:
		printf("Unknown Network\n");
		break;
	}

}

/***************************************************************************
 *   Print NSP Info WIMAX_API_CONNECTED_NSP_INFO
 ***************************************************************************/
void PrintNSPInfo(WIMAX_API_NSP_INFO_P pNspInfo)
{
	printf("NSP : %s\n", pNspInfo->NSPName);
	printf("\tID          : %u\n", pNspInfo->NSPid);
	printf("\tSignal      : %s\n", PrintSignalQuality(pNspInfo->CINR));
	printf("\tRSSI        : %d dBm\n", ConvertRSSI(pNspInfo->RSSI));
	printf("\tCINR        : %d dB\n", ConvertCINR(pNspInfo->CINR));
	printf("\tNetwork Type: ");
	switch (pNspInfo->networkType) {
	case WIMAX_API_HOME:
		printf("Home Network\n");
		break;
	case WIMAX_API_PARTNER:
		printf("Partner Network\n");
		break;
	case WIMAX_API_ROAMING_PARTNER:
		printf("Roaming Partner Network\n");
		break;
	case WIMAX_API_UNKNOWN:
		printf("Unknown Network\n");
		break;
	default:
		printf("Unknown Network\n");
		break;
	}
}

void PrintNSPInfoEx(WIMAX_API_NSP_INFO_EX_P pNspInfo)
{
	printf("NSP : %s\n", pNspInfo->NSPName);
	printf("\tID          : %u\n", pNspInfo->NSPid);
	printf("\tSignal      : %s\n", PrintSignalQuality(pNspInfo->CINR));
	printf("\tLink Quality: %d\n", pNspInfo->CINR/100);
	printf("\tRSSI        : %d dBm\n", ConvertRSSI(pNspInfo->RSSI));
	printf("\tCINR        : %d dB\n", ConvertCINR(pNspInfo->CINR));
	printf("\tNetwork Type: ");
	switch (pNspInfo->networkType) {
	case WIMAX_API_HOME:
		printf("Home Network\n");
		break;
	case WIMAX_API_PARTNER:
		printf("Partner Network\n");
		break;
	case WIMAX_API_ROAMING_PARTNER:
		printf("Roaming Partner Network\n");
		break;
	case WIMAX_API_UNKNOWN:
		printf("Unknown Network\n");
		break;
	default:
		printf("Unknown Network\n");
		break;
	}
}

/***************************************************************************
 *   Print Device Information WIMAX_API_DEVICE_INFO
 ***************************************************************************/
void PrintDeviceInfo(WIMAX_API_DEVICE_INFO_P pdevice_info,
		     WIMAX_API_WMF_COMPLIANCE_VERSION_P pwmf_ver,
		     WIMAX_API_NVM_VERSION_P pnvm_ver)
{
	printf("WiMAX Device Information\n");
	printf("\tManufacturer      : %s\n", pdevice_info->vendorName);
	printf("\tHW Model          : %s\n", pdevice_info->hwVersion.name);
	printf("\tHW Version        : %s\n", pdevice_info->hwVersion.version);
	printf("\tSW Pkg Version    : %s\n", pdevice_info->swVersion.version);
	printf("\tMAC Address       : %02X:%02X:%02X:%02X:%02X:%02X\n",
	       pdevice_info->macAddress[0], pdevice_info->macAddress[1],
	       pdevice_info->macAddress[2], pdevice_info->macAddress[3],
	       pdevice_info->macAddress[4], pdevice_info->macAddress[5]);
	if(pdevice_info->vendorSpecificInfoIncl) {
		printf("\tVendor Info    : %s\n",  pdevice_info->vendorSpecificInfo);
	}
	printf("\tWMF Comp. Version : %s\n", pwmf_ver->version);
	PrintNVMImageVersion(pnvm_ver);
}

/***************************************************************************
 *   Print Profile Information WIMAX_API_PROFILE_INFO
 ***************************************************************************/
void PrintProfile(WIMAX_API_PROFILE_INFO_P profile)
{
	printf("Profile Name : %s\n",profile->profileName);
	printf("\tProfile ID : %d\n",profile->profileID);
}

/***************************************************************************
 *   Print Connection Time
 ***************************************************************************/
void PrintConnectionTime(WIMAX_API_CONNECTION_TIME ConnectionTime)
{
    int hour, min, second = 0;
    if (ConnectionTime != 0)  
    {
        hour = ConnectionTime / 3600;
        min = ((int)ConnectionTime % 3600) / 60;
        second = (int)ConnectionTime % 60;
	printf("\tConnection Time: %02d:%02d:%02d\n", hour, min, second);
    }
}

/***************************************************************************
 *   Print NVM Image Version
 ***************************************************************************/
void PrintNVMImageVersion(WIMAX_API_NVM_VERSION_P pnvm_ver)
{
	printf("NVM Image Version\n");
	printf("\tGeneral Img Ver   : %d\n", pnvm_ver->GeneralImageVersion);
	printf("\tContent Version   : %d\n", pnvm_ver->ContentVersion);
}

/***************************************************************************
 *   Convert RSSI to real RSSI value
 ***************************************************************************/
int ConvertRSSI(UINT8 raw_rssi)
{
	return (int)raw_rssi - 123;
}

/***************************************************************************
 *   Convert CINR to real CINR value
 ***************************************************************************/
int ConvertCINR(UINT8 raw_cinr)
{
	return (int)raw_cinr - 10;
}

/***************************************************************************
 *   Convert TX Power to real TX Power value
 ***************************************************************************/
int ConvertTXPower(UINT8 raw_power)
{
	double power = (double)raw_power;
	return power * 0.5 - 84;
}

/***************************************************************************
 *   Print Signal Quality
 *	 - Signal Quality is based on CINR
 *   - Excellent : > 36
 *   - Very Good : > 28
 *   - Good      : > 20
 *   - Fair      : > 12
 *   - Poor      : > 5
 *   Note: Map -5dB to 25dB as 1% to 99% in linear way
 *         Any value below -5dB is considered as "OOZ" or very edgy coverage
 *         Any value above 25dB is conidered as excellent quality
 ***************************************************************************/
char * PrintSignalQuality(UINT8 raw_cinr)
{
	char * signal_quality;
	if (raw_cinr >= 36)
		signal_quality = SIGNAL_QUALITY_EXCELLENT;
	else if (raw_cinr > 28)
		signal_quality = SIGNAL_QUALITY_VERY_GOOD;
	else if (raw_cinr > 20)
		signal_quality = SIGNAL_QUALITY_GOOD;
	else if (raw_cinr > 12)
		signal_quality = SIGNAL_QUALITY_FAIR;
	else if (raw_cinr > 5)
		signal_quality = SIGNAL_QUALITY_POOR;
	else
		signal_quality = SIGNAL_QUALITY_NONE;
	
	return signal_quality;
}

/***************************************************************************
 *   Print WiMAX Version Information
 *   - Aligned with WMF Cert version
 ***************************************************************************/
void PrintVersionInfo(WIMAX_API_DEVICE_INFO_P pdevice_info,
		      WIMAX_API_WMF_COMPLIANCE_VERSION_P pwmf_version)
{
	printf("WiMAX Version Information\n");
	printf("\tHW Model Name:          %s\n", pdevice_info->hwVersion.name);
	printf("\tWMF Compliance Version: %s\n", pwmf_version->version);
	printf("\tSW Package Version:     %s\n", pdevice_info->swVersion.version);
}

