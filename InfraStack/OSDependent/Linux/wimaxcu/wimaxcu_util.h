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
#ifndef WIMAXCU_UTIL_H
#define WIMAXCU_UTIL_H


#define MAX_STATE_NAME 256

typedef enum _CU_CONNECT_MODE
{
    CONNECT_AUTO, 
    CONNECT_MANUAL,
    SCAN_AUTO,
    SCAN_SEMI,    
    SCAN_MANUAL
} CU_CONNECT_MODE;




size_t wchar2char(char *dest, const wchar_t * src);
size_t char2wchar(wchar_t * dest, const char *src);


void PrintWmxStatus(WIMAX_API_RET wmxStatus);

void PrintDeviceStatus(WIMAX_API_DEVICE_STATUS DeviceStatus);

void PrintUserConnectionMode(WIMAX_API_CONNECTION_MODE connectMode);

void PrintUserLinkStatus(WIMAX_API_LINK_STATUS_INFO_P puserLinkStatus);

void PrintUserLinkStatusEx(WIMAX_API_LINK_STATUS_INFO_EX_P puserLinkStatus);

void PrintConnectedNSPInfo(WIMAX_API_CONNECTED_NSP_INFO_P pConnectedNSP);
void PrintConnectedNSPInfoEx(WIMAX_API_CONNECTED_NSP_INFO_EX_P pConnectedNSP);

void PrintNSPInfo(WIMAX_API_NSP_INFO_P pNspInfo);

void PrintNSPInfoEx(WIMAX_API_NSP_INFO_EX_P pNspInfo);

void PrintDeviceInfo(WIMAX_API_DEVICE_INFO_P pdevice_info,
		     WIMAX_API_WMF_COMPLIANCE_VERSION_P pwmf_ver,
		     WIMAX_API_NVM_VERSION_P pnvm_ver);

int ConvertCharToConnectionMode(char *connect_mode,char* scan_mode,
                                WIMAX_API_CONNECTION_MODE_P userConnectMode);

int ConvertCharToConnectMode( WIMAX_API_DEVICE_ID_P pDeviceID,
                             char *connect_mode,char* scan_mode,
			     WIMAX_API_CONNECTION_MODE_P userConnectMode);
void PrintProfile( WIMAX_API_PROFILE_INFO_P profile);

void PrintConnectionTime(WIMAX_API_CONNECTION_TIME ConnectionTime);   

void PrintNVMImageVersion( WIMAX_API_NVM_VERSION_P pnvm_ver);

int ConvertRSSI(UINT8 raw_rssi);

int ConvertCINR(UINT8 raw_cinr);

int ConvertTXPower(UINT8 raw_power);

char * PrintSignalQuality(UINT8 raw_cinr);

void PrintVersionInfo(WIMAX_API_DEVICE_INFO_P pdevice_info,
		      WIMAX_API_WMF_COMPLIANCE_VERSION_P pwmf_version);


#endif // MINICU_UTIL.H
