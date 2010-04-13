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
#include "WrappersCommon.h"
#include "iWmxSDK.h"
#include "wmxSDK_Nds_3.h"
#include "wmxSDK_Nds_2.h"
#include "wmxSDK_Nds_Cmn.h"
#include "wimax_monitor_utils.h"

#include <unistd.h>
#include <sys/types.h>

BOOL isNDnS_Initialized = FALSE;


void CB_DeviceStatusUpdate( wmx_DeviceStatus_t deviceStatus, 
			    wmx_ConnectionProgressInfo_t connectionProgressInfo)
{
  PRINT_MSG("DEVICE STATUS UPDATE ARRIVED");
  PrintWmxDeviceStatus(deviceStatus);
  PrintWmxConnectionProgressInfo(connectionProgressInfo);
}

void CB_SystemStateUpdate( wmx_SystemState_t systemState,
			     wmx_StateReason_t stateReason,
			     wmx_UserLinkStatus_t userLinkStatus,
			     wmx_MediaStatus_t mediaStatus,
			     wmx_ConnectProgressInfo_t connectProgressInfo,
			     wmx_RfSwitchesStatus_t rfSwitchesStatus) 
{
  PRINT_MSG("SYSTEM STATE UPDATE ARRIVED");
  PrintWmxSystemState (systemState);
  PrintWmxConnectProgressInfo(connectProgressInfo);
  PrintWmxRfSwitchesStatus(rfSwitchesStatus ) ;
  PrintWmxStateReason(stateReason);
  if(systemState == DataPathConnected || systemState == Idle) {
    PrintWmxMediaStatus(mediaStatus);
    PrintWmxUserLinkStatus(userLinkStatus);
  }
}

void IndRFTakenCB ()
{
    // Radio is taken away by WiFi
    PRINT_MSG("SWI UPDATE ARRIVED");
    PRINT_OUT("RADIO Status: Radio is taken by WiFi");
}

BOOL Init_NDnS()
{
  if (WMX_ST_OK != wmxNds_Init()) {
    return FALSE;
  }

  if (WMX_ST_OK != wmx_RegisterDeviceStatusUpdateCB(CB_DeviceStatusUpdate)) {
    wmxNds_Finalize();
    return FALSE;
  }

  if (WMX_ST_OK != wmx_RegisterUserSystemStateUpdateCB(CB_SystemStateUpdate)) {
    wmx_UnregisterDeviceStatusUpdateCB();
    wmxNds_Finalize();
    return FALSE;
  }
  if (WMX_ST_OK != wmx_RegisterRfTakenCB(IndRFTakenCB)) {
    wmx_UnregisterUserSystemStateUpdateCB();
    wmx_UnregisterDeviceStatusUpdateCB();
    wmxNds_Finalize();
    return FALSE;
  }

  isNDnS_Initialized = TRUE;
  return TRUE;
}


void Fini_NDnS()
{
  isNDnS_Initialized = FALSE;
  wmx_UnregisterUserSystemStateUpdateCB();
  wmx_UnregisterDeviceStatusUpdateCB();
  wmx_UnregisterRfTakenCB();
  wmxNds_Finalize();
}


void UpdateDeviceStatus()
{
  wmx_Status_t wmxStatus;
  wmx_DeviceStatus_t deviceStatus;
  wmx_ConnectionProgressInfo_t connectionProgressInfo;

  wmxStatus = wmx_GetDeviceStatus(&deviceStatus, &connectionProgressInfo);
  if (wmxStatus != WMX_ST_OK) {
    PRINT_ERROR("Failed to update the device status");
    return;
  }
  
  PRINT_MSG("UPDATE CURRENT DEVICE STATUS");
  PrintWmxDeviceStatus(deviceStatus);
  PrintWmxConnectionProgressInfo(connectionProgressInfo);
}

void UpdateSystemState()
{
  wmx_Status_t wmxStatus;
  wmx_SystemState_t systemState;
  wmx_ConnectProgressInfo_t connectProgressInfo;
  wmx_RfSwitchesStatus_t rfSwitchesStatus;
  
  wmxStatus = wmx_GetSystemState(&systemState, &connectProgressInfo, &rfSwitchesStatus );
  if (wmxStatus != WMX_ST_OK) {
    PRINT_ERROR("Failed to update the system state");
    return;
  }
  
  PRINT_MSG("UPDATE CURRENT SYSTEM STATE");
  PrintWmxSystemState (systemState);
  PrintWmxConnectProgressInfo(connectProgressInfo);
  PrintWmxRfSwitchesStatus(rfSwitchesStatus ) ;
}

void CtrlStatusUpdate(wmx_CtrlStatus_t ctrlStatus) 
{
  switch(ctrlStatus) {
  case NOT_READY:
    PRINT_MSG("WIMAX DAEMON IS NOT READY");
    break;
  case READY:
    PRINT_MSG("WIMAX DAEMON IS READY");
    if (isNDnS_Initialized == TRUE) {
      Fini_NDnS();
    }
    Init_NDnS();

    UpdateDeviceStatus();
    UpdateSystemState();

    break;
  case DRIVER_DISCONNECTED:
    PRINT_MSG("DRIVER DISCONNECTED");
    break;
  default:
    PRINT_MSG("CTRL STATUS UNKNOWN");
    break;

  }
}

wmx_Status_t Initialize()
{
  wmx_Status_t wmxStatus;
  wmxStatus = wmxSDK_Init();
  if (wmxStatus != WMX_ST_OK) {
    PRINT_ERROR("Failed to initialize the SDK");
    return wmxStatus;
  }

  wmxStatus = wmxSDK_RegisterCtrlStatusUpdatesCB(CtrlStatusUpdate);
  if (wmxStatus != WMX_ST_OK) {
    PRINT_ERROR("Failed to register Ctrl Status CB");
    wmxSDK_Finalize();
    return wmxStatus;
  }

  CtrlStatusUpdate(wmxSDK_GetCtrlStatus());
  
  return wmxStatus;
}


void Finalize()
{
  wmx_Status_t wmxStatus;

  if (isNDnS_Initialized) {
      Fini_NDnS();
  }
  
  wmxStatus = wmxSDK_UnregisterCtrlStatusUpdatesCB(CtrlStatusUpdate);
  if (wmxStatus != WMX_ST_OK) {
    PRINT_WARNING("Failed to unregister Ctrl Status CB");
    return;
  }

  wmxSDK_Finalize();
  PRINT_DONE("SDK Finalization");
}


/*
 * Function: main
 * Description: main function
*/
int main(int argc, char *argv[])
{
    // int ret = 0;
    int scan_ret = 0;
    char input;
    
    wmx_Status_t wmxStatus;

    if (geteuid() != (uid_t) 0) {
        fprintf(stderr,
                "ERROR: You do not have sufficient privileges to perform this command.\n");
        return 1;
    }

    // Connect to wimax daemon via SDK
    wmxStatus = Initialize();
    if(WMX_ST_OK != wmxStatus) {
      PRINT_ERROR("Init Failed. Is wimaxd running???");
      return 1;
    }

    for( ; ;)
    {
        scan_ret = scanf("%c",&input);

        if((input=='Q')||(input=='q'))
        {
            // Finalize the SDK
            Finalize();
            printf("Goodbye!\n");
            break;
        }
        else {
            printf("Enter 'q' for exit\n");
        }
    }

    return 0;
}
