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
//////////////////////////////////////////////////////////////////////////
// Headers

// Project
#include "PipeHandlerInternal.h"
#include "EventSubscribers.h"

#include "CommonServices.h"
#include "L5Common.h"	
#include "L4ConfigurationManager.h"
#include "TraceModule.h"
#include "L5OpCodes.h"


//OSAL
#include "wimax_osal_primitives.h"
#include "wimax_osal_string.h"

#define THREAD_SLEEP_TIME 700
#define TIMEOUT 10000
#define MAX_STR_SIZE 32
// locations in events array
#define FINALIZE_CALLED 0
#define ACTION_REQUIRED 1
////////////////////////
// temp
tpfnMessagesHandler pfnMessagesHandler;
////////////////////////

//static LPCTSTR KEY_ENTRY_IP_ADDRESS		= L"SdkIpAddress";
//static LPCTSTR KEY_ENTRY_PORT_NUM		= L"SdkPortNum";

static char ipAddress[MAX_STR_SIZE] = "127.0.0.1";
static UINT32 portNum = 1234; 

static L5_CONNECTION l5ConnID = NULL;
static OSAL_event_t hThreadCreatedEvent = NULL;
static OSAL_event_t hConnectCalledEvent = NULL;
static OSAL_event_t hEvents[2];
static OSAL_thread_t gkThread = NULL;	// thread handle
static OSAL_critical_section lockIsConnected;		// @@@ : JSS : Replaced CRITICAL_SECTION
static OSAL_critical_section lockConnParams;
static wmx_CtrlStatus_t isConnected;
static DRIVER_STATUS driverStatus = DRIVER_DOWN;
static BOOL isInitialized = FALSE;
static List *eventsSubsList = NULL;
static BOOL firstRun = TRUE;
static BOOL isOverrideConnParams = FALSE;
static L5_RESULT l5status = L5_RESULT_ALREADY_DISCONNECTED;
static L5_RESULT returnedL5status = L5_RESULT_ALREADY_DISCONNECTED;
static BOOL isRestartRequired = FALSE;
static LONG numOfInits = 0;
static int clientCount = 0;

// methods declarations
void PIPE_HANDLER_EventHandler(L5_CONNECTION Conn, L5_EVENT eEvent, void *pvEventData, void *pvUserContext);
void PIPE_HANDLER_SetCtrlStatus(wmx_CtrlStatus_t status, L5_RESULT l5ConnStatus);
void PIPE_HANDLER_Finalize();
void UnblockInitFunc();
void ReadConnParamsFromRegistry();


void PIPE_HANDLER_InitCriticalSections()
{
	OSAL_init_critical_section(&lockIsConnected);
	OSAL_init_critical_section(&lockConnParams);
}

void PIPE_HANDLER_FinalizeCriticalSections()
{
	OSAL_delete_critical_section(&lockIsConnected);
	OSAL_delete_critical_section(&lockConnParams);
}

DRIVER_STATUS PIPE_HANDLER_GetDriverState()
{
	L5_RESULT res;
	void *responseBuffer = NULL;
	UINT32 responseSize;
	UINT32 responseID; 
	DRIVER_STATUS driverStatus = DRIVER_DOWN;

	responseSize = 0;	

	res = PIPE_HANDLER_SendReceiveL5(l5ConnID, L5_TARGET_ACT, 
										ACT_OPCODE_GET_DRIVER_STATE, 
										NULL, 0 , 
										&responseID, 
										responseBuffer, 
										&responseSize );	

	TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_NOTICE, "PIPE_HANDLER_SendReceiveL5 returned %d",res);
	if (responseID == DRIVER_UP)
	{
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_INFO, "Driver is up");
		driverStatus = DRIVER_UP;
	}
	else
	{
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_INFO, "Driver is down");
		driverStatus = DRIVER_DOWN;
	}

	return driverStatus;
}

// this is the main thread of the gate keeper.
// it's responsible to manage the connection and keep it alive.
void PIPE_HANDLER_ThreadProc(LPVOID lpParam)
{
	L5_RESULT templ5status;
	UINT32 res;
	DRIVER_STATUS driverStatus;

	UNREFERENCED_PARAMETER(lpParam);
	
	TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_INFO, "ConnGateKeeper - thread entered.");
	for (;;)
	{
		OSAL_enter_critical_section(&lockConnParams);
		// Connect L5 and through it to AppSrv. Gain L5ConnID.
		templ5status = PIPE_HANDLER_ConnectInternal( ipAddress, 
			portNum,
			L5_TARGET_DYNAMIC,
			pfnMessagesHandler, 
			PIPE_HANDLER_EventHandler,
			NULL,
			TRUE,
			&l5ConnID	);		

		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_INFO, "ConnGateKeeper - PIPE_HANDLER_ConnectInternal returned - %d", templ5status);
		// if we couldn't create L5 connection, wait a little and try again
		if (templ5status != L5_RESULT_OK)
		{		
			if (isInitialized)
			{			
				PIPE_HANDLER_SetCtrlStatus(NOT_READY, templ5status);
			}
			else // this should happen during the first iteration of the loop
			{	 // while the Init() function is still inside the lock (allows the first client's Connect call to return with a true value)
				isConnected = NOT_READY;
				l5status = templ5status;
			}
			//TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_INFO, (L"PIPE_HANDLER_ThreadProc - connection status set to NOT_READY, L5_RESULT: %d", templ5status));
			UnblockInitFunc();
			OSAL_reset_event(hEvents[ACTION_REQUIRED]);
			OSAL_set_event(hConnectCalledEvent);
			OSAL_exit_critical_section(&lockConnParams);
			if (isRestartRequired)
			{	
				TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_INFO, "ConnGateKeeper - thread is about to exit");
				break; // exit loop and end thread
			}
			OSAL_sleep(THREAD_SLEEP_TIME);
			continue;
		}
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_INFO, "ConnGateKeeper connected.");

		if (isInitialized)
		{
			PIPE_HANDLER_SetCtrlStatus(READY, templ5status);
		}
		else // this should happen during the first iteration of the loop
		{	 // while the Init() function is still inside the lock (allows the first client's Connect call to succeed)
			isConnected = DRIVER_DISCONNECTED;
			l5status = templ5status;
		}
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_NOTICE, "PIPE_HANDLER_ThreadProc - connection status set to READY, L5_RESULT: %d", templ5status);

		driverStatus = PIPE_HANDLER_GetDriverState();
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_NOTICE, "PIPE_HANDLER_GetDriverState=%d",driverStatus);

		UnblockInitFunc(); // unblock the Init() function, in case it's waiting
		
		OSAL_reset_event(hEvents[ACTION_REQUIRED]);
		OSAL_set_event(hConnectCalledEvent);
		OSAL_exit_critical_section(&lockConnParams);

		switch(driverStatus)
		{
		case DRIVER_DOWN:
			TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_NOTICE, "PIPE_HANDLER_ThreadProc - SendEventToSubscribers NOT_READY");
			PIPE_HANDLER_SetCtrlStatus(NOT_READY, templ5status);
			SendEventToSubscribers(eventsSubsList, NOT_READY);
			{
				//L5_RESULT dummyStatus;
				//if(PIPE_HANDLER_IsConnected(&dummyStatus))
				//{
					OSAL_set_event(hEvents[ACTION_REQUIRED]);
				//}
			}
			break;

		case DRIVER_UP:
			TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_NOTICE, "PIPE_HANDLER_ThreadProc - SendEventToSubscribers READY");
			PIPE_HANDLER_SetCtrlStatus(READY, templ5status);
			SendEventToSubscribers(eventsSubsList, READY);	
			break;
		}
		
		res = OSAL_multiple_wait_event(2, hEvents, FALSE, INFINITE);
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_INFO, "PIPE_HANDLER_ThreadProc - end waiting");
		// clean start				
		PIPE_HANDLER_SetCtrlStatus(NOT_READY, L5_RESULT_ALREADY_DISCONNECTED); // no matter why we are not waiting anymore, the status here is NOT READY
		
		if (l5ConnID != NULL)
		{
			PIPE_HANDLER_DisconnectInternal(l5ConnID, TRUE);
			l5ConnID = NULL;
		}
		// clean end
		switch(res)
		{
		case WAIT_TIMEOUT:
			TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_CRITICAL, "PIPE_HANDLER_ThreadProc - Time Out");
		case WAIT_OBJECT_0 + 0:			// Finalize has been called		
		case WAIT_OBJECT_0 + 1:			// the state of the hActionRequired is signaled
			if (!isRestartRequired)
			{
				TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_NOTICE, "PIPE_HANDLER_ThreadProc - SendEventToSubscribers NOT_READY");
				SendEventToSubscribers(eventsSubsList, NOT_READY);
			}
			else
			{	
				TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_INFO, "ConnGateKeeper at the end - thread is about to exit");				
				return;// 0;
			}
			break;
		case WAIT_IO_COMPLETION: //The wait was ended by one or more user-mode asynchronous procedure calls (APC) queued to the thread.			
			return;// 0;					
		default: //WAIT_FAILED			
			TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_ALERT, "PIPE_HANDLER_ThreadProc - Wait Failed!");
			ASSERT();
			break;
		}
	}

	TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_INFO, "ConnGateKeeper - thread exiting...");
	return;// 0;	
}


wmx_Status_t PIPE_HANDLER_SetConnParams(char *szHostName, int nPort)
{
	wmx_Status_t retValue = WMX_ST_FAIL;
	UINT32 res;
	
	//////////////////////////// for debug
	//WCHAR tempIpAddress2[32];
	//size_t numOfChars;
	//mbstowcs_s(&numOfChars, tempIpAddress2, sizeof(tempIpAddress2)/2, szHostName, 31);
	//TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_CRITICAL, (L"PIPE_HANDLER_SetConnParams - start - IP: %ws, port: %d", tempIpAddress2, nPort));
	////////////////////////////

	if (!PIPE_HANDLER_IsInitialized())
	{
		return WMX_ST_MODULE_NOT_INITIALIZED;
	}

	OSAL_enter_critical_section(&lockConnParams);	
	if ((OSAL_strnlen(szHostName, MAX_STR_SIZE) < MAX_STR_SIZE) && (nPort >= 0))
	{
		OSAL_strcpy_s(ipAddress, MAX_STR_SIZE - 1, szHostName);		
		portNum = (UINT32)nPort;
		isOverrideConnParams = TRUE;
		OSAL_reset_event(hConnectCalledEvent);
		OSAL_set_event(hEvents[ACTION_REQUIRED]);
		retValue = WMX_ST_OK;
	}	
	OSAL_exit_critical_section(&lockConnParams);

	if ((isInitialized) && (retValue == WMX_ST_OK))
	{ // if the gate keeper is active - wait for the change of the params to take effect		
		res = OSAL_wait_event(hConnectCalledEvent, TIMEOUT);
		switch(res)
		{
		case WAIT_TIMEOUT:			
		case WAIT_ABANDONED:		// the event has been freed
		case WAIT_OBJECT_0:			// the state of the event is signaled			
			break;						
		default: //WAIT_FAILED			
			ASSERT();
			break;
		}		
	}	
	
	return retValue;
}


// init the gate keeper
L5_RESULT PIPE_HANDLER_InitConnectivity()
{
	L5_RESULT tempL5status = L5_RESULT_OK;		
	UINT32 res;	

	//OSAL_enter_critical_section(&lockIsConnected);
	if (isInitialized) // check this value again to ensure all corners are covered
	{
		//OSAL_exit_critical_section(&lockIsConnected);
		return tempL5status;
	}

	l5ConnID = NULL;
	firstRun = TRUE;
	isRestartRequired = FALSE;

	// Remark - init services moved

	TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_INFO, "Init start.");

	if (!isOverrideConnParams)
	{
		ReadConnParamsFromRegistry();
	}

	AllocSubscribersList(&eventsSubsList);

	OSAL_create_event(&hEvents[ACTION_REQUIRED] , FALSE, FALSE, NULL);	
	if (hEvents[ACTION_REQUIRED] == NULL)
	{
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_ERR, "Initialize Failed: Creation of ConnGateKeeper event - Failed!");
		CleanSubscribersList(&eventsSubsList);
		//OSAL_exit_critical_section(&lockIsConnected);
		return L5_RESULT_CREATE_EVENT_FAILED;
	}

	OSAL_create_event(&hThreadCreatedEvent , TRUE, FALSE, NULL);
	if (hThreadCreatedEvent == NULL)
	{
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_ERR, "Initialize Failed: Creation of ConnGateKeeper event - Failed!");
		CleanSubscribersList(&eventsSubsList);
		OSAL_delete_event(hEvents[ACTION_REQUIRED]);
		//OSAL_exit_critical_section(&lockIsConnected);
		return L5_RESULT_CREATE_EVENT_FAILED;
	}

	OSAL_create_event(&hConnectCalledEvent , FALSE, FALSE, NULL);
	if (hConnectCalledEvent == NULL)
	{
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_ERR, "Initialize Failed: Creation of ConnGateKeeper event - Failed!");
		CleanSubscribersList(&eventsSubsList);
		OSAL_delete_event(hEvents[ACTION_REQUIRED]);
		OSAL_delete_event(hThreadCreatedEvent);
		hEvents[ACTION_REQUIRED] = NULL;
		hThreadCreatedEvent = NULL;
		//OSAL_exit_critical_section(&lockIsConnected);
		return L5_RESULT_CREATE_EVENT_FAILED;
	}
	
	OSAL_create_event(&hEvents[FINALIZE_CALLED] , FALSE, FALSE, NULL);
	if (hEvents[FINALIZE_CALLED] == NULL)
	{
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_ERR, "Initialize Failed: Creation of ConnGateKeeper event - Failed!");
		CleanSubscribersList(&eventsSubsList);
		OSAL_delete_event(hEvents[ACTION_REQUIRED]);
		OSAL_delete_event(hThreadCreatedEvent);
		OSAL_delete_event(hConnectCalledEvent);
		hConnectCalledEvent = NULL;
		hEvents[ACTION_REQUIRED] = NULL;
		hThreadCreatedEvent = NULL;
		//OSAL_exit_critical_section(&lockIsConnected);
		return L5_RESULT_CREATE_EVENT_FAILED;
	}	

	OSAL_create_thread(PIPE_HANDLER_ThreadProc, NULL, &gkThread );
	if( NULL == gkThread )
	{
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_ERR, "Initialize Failed: Creation of ConnGateKeeper thread - Failed!");
		CleanSubscribersList(&eventsSubsList);
		OSAL_delete_event(hEvents[ACTION_REQUIRED]);
		OSAL_delete_event(hThreadCreatedEvent);
		OSAL_delete_event(hConnectCalledEvent);
		hConnectCalledEvent = NULL;
		hEvents[ACTION_REQUIRED] = NULL;
		hThreadCreatedEvent = NULL;
		//OSAL_exit_critical_section(&lockIsConnected);
		return L5_RESULT_CREATE_EVENT_FAILED;
	}

	res = OSAL_wait_event(hThreadCreatedEvent, TIMEOUT); // wait for the thread to be created		
	switch(res)
	{
	case WAIT_OBJECT_0:			// the state of the event is signaled		
		break;	
	case WAIT_TIMEOUT:
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_CRITICAL, "Timeout while waiting for the thread to be created during Init()");
		break;
	case WAIT_ABANDONED:		// the event has been freed
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_CRITICAL, "WaitAbandoned while waiting for the thread to be created during Init()");
		break;
	default: //WAIT_FAILED		
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_ALERT, "Wait during Init() Failed!");
		ASSERT();
		break;
	}
	// if we got here it means that the thread has been created successfully or timeout elapsed
	isInitialized = TRUE;

	//OSAL_exit_critical_section(&lockIsConnected);
	
	return tempL5status;
}



// finalize the gate keeper
void PIPE_HANDLER_FiniConnectivity()
{
	if (isInitialized)
	{
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_INFO, "Shutdown start.");
		isInitialized = FALSE;		
		isRestartRequired = TRUE;

		//wmxTerminateThread(hEvents[0], &gkThread, TR_MOD_L5_CONNECTOR);
		OSAL_set_event(hEvents[0]);
		OSAL_timedjoin_thread(gkThread , SHUTDOWN_TIMEOUT, NULL);		

		if (hConnectCalledEvent != NULL)
		{
			OSAL_set_event(hConnectCalledEvent);
		}		

		CleanSubscribersList(&eventsSubsList);
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_INFO, "After subcriber list cleanup.");
		if (hEvents[ACTION_REQUIRED] != NULL)
		{
			OSAL_delete_event(hEvents[ACTION_REQUIRED]);	
			hEvents[ACTION_REQUIRED] = NULL;
		}
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_INFO, "After deleting action-required event.");
		if (hThreadCreatedEvent != NULL)
		{
			OSAL_delete_event(hThreadCreatedEvent);
			hThreadCreatedEvent = NULL;
		}
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_INFO, "After deleting thread-created event.");
		if (hConnectCalledEvent != NULL)
		{
			OSAL_delete_event(hConnectCalledEvent);		
			hConnectCalledEvent = NULL;
		}
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_INFO, "After deleting Connect-Called event.");
		if (hEvents[FINALIZE_CALLED] != NULL)
		{
			OSAL_delete_event(hEvents[FINALIZE_CALLED]);		
			hEvents[FINALIZE_CALLED] = NULL;
		}
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_INFO, "After deleting finalize-called event.");

		l5ConnID = NULL;

		// Remark - Fini services moved
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_INFO, "Shutdown completed.");
	}
}


// register a callback for device connection status events
wmx_Status_t PIPE_HANDLER_RegisterCtrlStatusUpdatesCB(wmx_pCtrlStatusUpdateCB_t ctrlStatusUpdateCB)
{
	if (!PIPE_HANDLER_IsInitialized())
	{
		return WMX_ST_MODULE_NOT_INITIALIZED;
	}
	
	if ((ctrlStatusUpdateCB != NULL) && (eventsSubsList != NULL) && (AddSubscriber(eventsSubsList, ctrlStatusUpdateCB) != NULL))
	{
		return WMX_ST_OK;
	}
	return WMX_ST_CALLBACK_NOT_REGISTERED;
}


// unregister a callback for device connection status events
wmx_Status_t PIPE_HANDLER_UnregisterCtrlStatusUpdatesCB(wmx_pCtrlStatusUpdateCB_t ctrlStatusUpdateCB)
{
	if (!PIPE_HANDLER_IsInitialized())
	{
		return WMX_ST_MODULE_NOT_INITIALIZED;
	}
	
	if ((ctrlStatusUpdateCB != NULL) && (eventsSubsList != NULL) && (RemoveSubscriber(eventsSubsList, ctrlStatusUpdateCB) == TRUE))
	{
		return WMX_ST_OK;
	}	

	return WMX_ST_CALLBACK_NOT_REGISTERED;
}


void UnblockInitFunc()
{
	if (firstRun)
	{
		OSAL_set_event(hThreadCreatedEvent); // unblock the Init() function, in case it's waiting
		firstRun = FALSE;
	}
}


void PIPE_HANDLER_ResetConnection()
{	
	PIPE_HANDLER_SetCtrlStatus(NOT_READY, L5_RESULT_ALREADY_DISCONNECTED); // no matter why we are not waiting anymore, the status here is NOT READY
	
	OSAL_enter_critical_section(&lockConnParams);	
	OSAL_set_event(hEvents[ACTION_REQUIRED]);
	OSAL_exit_critical_section(&lockConnParams);
}


// set the status of the connection
void PIPE_HANDLER_SetCtrlStatus(wmx_CtrlStatus_t status, L5_RESULT l5ConnStatus)
{
	OSAL_enter_critical_section(&lockIsConnected);
	isConnected = status;
	l5status = l5ConnStatus;
	OSAL_exit_critical_section(&lockIsConnected);
}


wmx_CtrlStatus_t PIPE_HANDLER_GetCtrlStatusInternal(L5_RESULT *status)
{
	wmx_CtrlStatus_t tempIsConnected;
	UINT32 res;	

	////////////////////////// part 1
	// TODO: test - maybe this behavior is not necessary

	// in case the gate keeper is disconnected - this will ensure we will wait at least one iteration
	OSAL_enter_critical_section(&lockConnParams);
	OSAL_reset_event(hConnectCalledEvent);
	OSAL_exit_critical_section(&lockConnParams);
	//////////////////////////

	// get current connection status
	OSAL_enter_critical_section(&lockIsConnected);	
	tempIsConnected = isConnected;		
	*status = l5status;
	OSAL_exit_critical_section(&lockIsConnected);

	////////////////////////// part 2
	// TODO: test - maybe this behavior is not necessary

	// if not connected, we want to wait at least one iteration of gate keeper thread,
	// to make sure at least one connection attempt to AppSrv was made since we started this function.
	if (tempIsConnected != READY)
	{
		res = OSAL_wait_event(hConnectCalledEvent, THREAD_SLEEP_TIME);
		
		// get connection status after one iteration
		OSAL_enter_critical_section(&lockIsConnected);	
		tempIsConnected = isConnected;		
		*status = l5status;
		OSAL_exit_critical_section(&lockIsConnected);
	}
	//////////////////////////	

	return tempIsConnected;
}


wmx_CtrlStatus_t PIPE_HANDLER_GetCtrlStatus()
{
	L5_RESULT tempStatus;
	wmx_CtrlStatus_t retValue;

	if (!PIPE_HANDLER_IsInitialized())
	{
		return NOT_READY;
	}
	
	retValue = PIPE_HANDLER_GetCtrlStatusInternal(&tempStatus);	

	return retValue;
}


// return the status of the connection to AppSrv
BOOL PIPE_HANDLER_IsConnected(L5_RESULT *status)
{	
	/*if (!PIPE_HANDLER_IsInitialized())
	{
		return NOT_READY;
	}*/

	if (PIPE_HANDLER_GetCtrlStatusInternal(status) == NOT_READY)
	{		
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_DEBUG, "PIPE_HANDLER_IsConnected = FALSE.");		
		return FALSE;
	}
	else
	{
		//////////////////
		// debug
		/*if (*status == L5_RESULT_OK)
		{
			ASSERT();
		}*/
		//////////////////
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_DEBUG, "PIPE_HANDLER_IsConnected = TRUE.");		
		return TRUE;		
	}	
}


void ReadConnParamsFromRegistry()
{
	char tempIpAddress[32];
	UINT32 tempPortNum;

	tempIpAddress[0] = '\0';
	if ( L4Configurations_getSdkIpAddress(tempIpAddress) && tempIpAddress[0] )
	{
		OSAL_strcpy_s(ipAddress, 32, tempIpAddress);	// set the global that is being used..
	}
	L4Configurations_getSdkPortNum(&tempPortNum);
	portNum = tempPortNum;		
}


// used to notify the gate keeper when external Connect or SendReceive fail
void PIPE_HANDLER_ReportError()
{
	L5_RESULT status;

	TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_INFO, "Error reported to ConnGateKeeper by a PipeHandler client.");
	if (PIPE_HANDLER_IsConnected(&status))
	{
		PIPE_HANDLER_ResetConnection();
	}
}


void PIPE_HANDLER_EventHandler( 
	L5_CONNECTION Conn,
	L5_EVENT eEvent,
	void *pvEventData,
	void *pvUserContext )
{
	L5_RESULT eventReason;	

	UNREFERENCED_PARAMETER(eEvent);
	UNREFERENCED_PARAMETER(Conn);
	UNREFERENCED_PARAMETER(pvEventData);
	UNREFERENCED_PARAMETER(pvUserContext);

	switch(eEvent)
	{
	case L5_EVENT_DISCONNECTED:
	case L5_EVENT_DRIVER_DISCONNECTED:
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_INFO, "Got disconnect event!");
		if (PIPE_HANDLER_IsConnected(&eventReason)) // we can receive disconnection events only when we are connected
		{
			eventReason = *(L5_RESULT*)pvEventData;
			if (eventReason != L5_RESULT_USER_REQUESTED_DISCONNECT)
			{
				PIPE_HANDLER_ResetConnection();
			}
		}
		break;

	case L5_EVENT_DRIVER_CONNECTED:
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_INFO, "Got driver connected event!");
		PIPE_HANDLER_SetCtrlStatus(READY, L5_RESULT_OK);
		SendEventToSubscribers(eventsSubsList, READY);	
		break;
/*
	case L5_EVENT_DRIVER_DISCONNECTED:
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_INFO, "Got driver disconnected event!");
		PIPE_HANDLER_SetCtrlStatus(DRIVER_DISCONNECTED, L5_RESULT_OK);
		SendEventToSubscribers(eventsSubsList, DRIVER_DISCONNECTED);	
		break;
*/
	}

	/*
	if (eEvent == L5_EVENT_DISCONNECTED)
	{
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_INFO, "Got disconnect event!");
		if (PIPE_HANDLER_IsConnected(&eventReason)) // we can receive disconnection events only when we are connected
		{
			eventReason = *(L5_RESULT*)pvEventData;
			if (eventReason != L5_RESULT_USER_REQUESTED_DISCONNECT)
			{
				PIPE_HANDLER_ResetConnection();
			}
		}
	}
	*/
}


char *PIPE_HANDLER_GetIpAddress()
{
	return ipAddress;
}


UINT32 PIPE_HANDLER_GetPortNum()
{
	return portNum;
}


L5_RESULT PIPE_HANDLER_GetLastL5Status()
{
	return l5status;
}


wmx_Version_t PIPE_HANDLER_GetVersion()
{
	wmx_Version_t ver;

	SET_VERSION(ver, PIPE_HANDLER_MAJOR, PIPE_HANDLER_MINOR, PIPE_HANDLER_BUILD, PIPE_HANDLER_REVISION, PIPE_HANDLER_BRANCH);
	return ver;
}
