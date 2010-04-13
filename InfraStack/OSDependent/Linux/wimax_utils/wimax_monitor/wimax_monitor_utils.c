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
#include "wimax_monitor_utils.h"
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <pthread.h>


pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;


void PRINT_OUTPUT(char * output, char * result)
{
  printf("%-50s%10s\n", output, result);
}

void PRINT_LINE(char * head, char * msg, ... )
{
  va_list arglist;
  time_t now;
  struct tm local;
  char new_msg[256] = {0};
  
  pthread_mutex_lock(&mut);

  va_start(arglist, msg);
  vsnprintf(new_msg, 256, msg, arglist);
  va_end(arglist);

  if(head != NULL) {
    now = time(NULL);
    localtime_r(&now, &local);
    
    printf("[%04d/%02d/%02d %02d:%02d:%02d]  %-10s%s\n",
	   local.tm_year+1900, local.tm_mon+1, local.tm_mday,
	   local.tm_hour, local.tm_min, local.tm_sec,
	   head,
	   new_msg);
  }
  else { // no head and time info with 1 tab
    printf("\t%s\n",new_msg);
  }
  pthread_mutex_unlock(&mut);
}


void PrintWmxDeviceStatus(wmx_DeviceStatus_t deviceStatus)
{
  switch (deviceStatus) {
  case DeviceStatus_UnInitialized:
    PRINT_OUT("Device Status: UnInitialized");
    break;
  case DeviceStatus_RF_OFF_HW_SW:
    PRINT_OUT("Device Status: HW SW Radio OFF");
    break;
  case DeviceStatus_RF_OFF_HW:
    PRINT_OUT("Device Status: HW Radio OFF");
    break;
  case DeviceStatus_RF_OFF_SW:
    PRINT_OUT("Device Status: SW Radio OFF");
    break;
  case DeviceStatus_Ready:
    PRINT_OUT("Device Status: Ready");
    break;
  case DeviceStatus_Scanning:
    PRINT_OUT("Device Status: Scanning");
    break;
  case DeviceStatus_Connecting:
    PRINT_OUT("Device Status: Connecting");
    break;
  case DeviceStatus_Data_Connected:
    PRINT_OUT("Device Status: Data Connected");
    break;
  default:
    PRINT_OUT("Device Status: Unknown");
  }
}

void PrintWmxConnectionProgressInfo(wmx_ConnectionProgressInfo_t connectionProgressInfo)
{
  switch(connectionProgressInfo) {
  case DeviceConnectionProgress_Ranging:
    PRINT_OUT("Connection Progress: Ranging");
    break;
  case DeviceConnectionProgress_SBC:
    PRINT_OUT("Connection Progress: SBC");
    break;
  case DeviceConnectionProgress_EAP_authentication_Device:
    PRINT_OUT("Connection Progress: EAP Auth (Device)");
    break;
  case DeviceConnectionProgress_EAP_authentication_User:
    PRINT_OUT("Connection Progress: EAP Auth (User)");
    break;
  case DeviceConnectionProgress_3_way_handshake:
    PRINT_OUT("Connection Progress: 3 way Handshake");
    break;
  case DeviceConnectionProgress_Registration:
    PRINT_OUT("Connection Progress: Registration");
    break;
  case DeviceConnectionProgress_De_registration:
    PRINT_OUT("Connection Progress: De-Registration");
    break;
  case DeviceConnectionProgress_Registered:
    PRINT_OUT("Connection Progress: Registered");
    break;
  default:
    PRINT_OUT("Connection Progress: Unknown");
  }
}


void PrintWmxSystemState (wmx_SystemState_t systemState)
{
  switch (systemState) {
  case UnInitialized:
    PRINT_OUT("System State: UnInitialized");
    break;
  case Config:
    PRINT_OUT("System State: Config");
    break;
  case Initialized:
    PRINT_OUT("System State: Initialized");
    break;
  case Production:
    PRINT_OUT("System State: Production");
    break;
  case RfOff:
    PRINT_OUT("System State: Radio Off");
    break;
  case Ready:
    PRINT_OUT("System State: Ready");
    break;
  case Scan:
    PRINT_OUT("System State: Scan");
    break;
  case Connecting:
    PRINT_OUT("System State: Connecting");
    break;
  case WimaxConnected:
    PRINT_OUT("System State: WiMAX Connected");
    break;
  case DataPathConnected:
    PRINT_OUT("System State: Data Path Connected");
    break;
  case Idle:
    PRINT_OUT("System State: Idle");
    break;
  case Disconnecting:
    PRINT_OUT("System State: Disconnecting");
    break;
  case RfShutDown:
    PRINT_OUT("System State: Radio Shutdown");
    break;
  case UnknownState:
    PRINT_OUT("System State: Unknown State");
    break;
  default:
    PRINT_OUT("System State: Unknown");
    break;
  }
}

void PrintWmxConnectProgressInfo( wmx_ConnectProgressInfo_t connectProgressInfo)
{
  switch (connectProgressInfo) {
  case NotApplicable:
    PRINT_OUT("Connect Progress Info: Not Applicable");
    break;
  case Ranging:
    PRINT_OUT("Connect Progress Info: Ranging");
    break;
  case SBC:
    PRINT_OUT("Connect Progress Info: SBC");
    break;
  case EAPAuthentication:
    PRINT_OUT("Connect Progress Info: EAP Authenticaton");
    break;
  case ThreeWayHandshake:
    PRINT_OUT("Connect Progress Info: 3 Way Handshake");
    break;
  case Registration:
    PRINT_OUT("Connect Progress Info: Registration");
    break;
  default:
    PRINT_OUT("Connect Progress Info: Unknown");
    break;
  }
}

void PrintWmxRfSwitchesStatus(wmx_RfSwitchesStatus_t rfSwitchesStatus ) 
{
  switch(rfSwitchesStatus.swRfStatus) {
  case Off:
    PRINT_OUT("SW Radio: Off");
    break;
  case On:
    PRINT_OUT("SW Radio: On");
    break;
  default:
    PRINT_OUT("SW Radio: Unknown");
    break;
  }

  switch(rfSwitchesStatus.hwRfStatus) {
  case Off:
    PRINT_OUT("HW Radio: Off");
    break;
  case On:
    PRINT_OUT("HW Radio: On");
    break;
  default:
    PRINT_OUT("HW Radio: Unknown");
    break;
  }
}

void PrintWmxStateReason(wmx_StateReason_t stateReason)
{
  switch (stateReason) {
  case StateReasonNormal:
    PRINT_OUT("State Reason: Normal");
    break;
  case StateReasonFailToConnectToNW:
    PRINT_OUT("State Reason: Fail to Connect to Network");
    break;
  case StateReasonFailToConnectRanging:
    PRINT_OUT("State Reason: Fail to Connect - Ranging");
    break;
  case StateReasonFailToConnectSBC:
    PRINT_OUT("State Reason: Fail to Connect - SBC");
    break;
  case StateReasonFailToConnectEAPAuth:
    PRINT_OUT("State Reason: Fail to Connect - EAP Auth");
    break;
  case StateReasonFailToConnect3WayHandshake:
    PRINT_OUT("State Reason: Fail to Connect - 3 Way Handshake");
    break;
  case StateReasonFailToConnectREG:
    PRINT_OUT("State Reason: Fail to Connect - Registration");
    break;
  case StateReasonFailToConnectDatapath:
    PRINT_OUT("State Reason: Fail to Connect - Data Path");
    break;
  case StateReasonFailToConnectCoexNoRF:
    PRINT_OUT("State Reason: Fail to Connect - Coex No RF");
    break;
  case StateReasonDisconnectDreg:
    PRINT_OUT("State Reason: Disconnect - DeRegistration");
    break;
  case StateReasonDisconnectAbort:
    PRINT_OUT("State Reason: Disconnect - Abort");
    break;
  case StateReasonDisconnectReset:
    PRINT_OUT("State Reason: Disconnect - Reset");
    break;
  case StateReasonDisconnectDrop:
    PRINT_OUT("State Reason: Disconnect - Drop");
    break;
  case StateReasonSplockValidationFailed:
    PRINT_OUT("State Reason: SP Lock Validation Fail");
    break;
  case StateReasonDisconnectSecurity:
    PRINT_OUT("State Reason: Disconnect - Security");
    break;
  case StateReasonResetHwWdt:
    PRINT_OUT("State Reason: Reset HW WDT");
    break;
  case StateReasonResetSwWdt:
    PRINT_OUT("State Reason: Reset SW WDT");
    break;
  case StateReasonResetAssert:
    PRINT_OUT("State Reason: Reset Assert");
    break;
  case StateReasonResetThermal:
    PRINT_OUT("State Reason: Reset Thermal");
    break;
  case StateReasonResetRfKill:
    PRINT_OUT("State Reason: Reset RF Kill");
    break;
  case StateReasonResetCoExistence:
    PRINT_OUT("State Reason: Reset CoExistence");
    break;
  case StateReasonResetHost:
    PRINT_OUT("State Reason: Reset Host");
    break;
  case StateReasonDisconnectProtocolError:
    PRINT_OUT("State Reason: Disconnect Protocol Error");
    break;
	case StateReasonFWRequestDevReset:
	PRINT_OUT("State Reason: FW Request Device Reset");
	break;
	case StateReasonFWRequestFuncReset:
	PRINT_OUT("State Reason: FW Request Function Reset");
	break;
  default:
    PRINT_OUT("State Reason: Unknown");
    break;
  }
}

void PrintWmxUserLinkStatus(wmx_UserLinkStatus_t userLinkStatus) 
{
  int hour, min, second = 0;
  PRINT_OUT("RSSI: %d", userLinkStatus.rssi);
  PRINT_OUT("CINR: %d", userLinkStatus.cinr);
  PRINT_OUT("Frequency: %d", userLinkStatus.frequency);
  PRINT_OUT("Power: %d", userLinkStatus.power);
  PRINT_OUT("Link Quality: %d", userLinkStatus.linkQuality);
  hour = userLinkStatus.time / 3600;
  min = ((int)userLinkStatus.time % 3600) / 60;
  second = (int)userLinkStatus.time % 60;
  PRINT_OUT("Connection Time: %02d:%02d:%02d", hour, min, second);
  PRINT_OUT("Up Link Speed: %lf", userLinkStatus.upLinkSpeed);
  PRINT_OUT("Down Link Speed: %lf", userLinkStatus.downLinkSpeed);
  PRINT_OUT("BS ID: %c%c%c%c%c%c", userLinkStatus.bsId[0],userLinkStatus.bsId[1],userLinkStatus.bsId[2],
	    userLinkStatus.bsId[3],userLinkStatus.bsId[4],userLinkStatus.bsId[5]);
}


void PrintWmxMediaStatus(wmx_MediaStatus_t mediaStatus)
{
  switch(mediaStatus) {
  case LinkUp:
    PRINT_OUT("Media Status: Link Up");
    break;
  case LinkDown:
    PRINT_OUT("Media Status: Link Down");
    break;
  case LinkRenew:
    PRINT_OUT("Media Status: Link Renew");
    break;
  default:
    PRINT_OUT("Media Status: Unknown");
    break;
  }
}

