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
#ifndef _WMX_SDK_DND_IF_H
#define _WMX_SDK_DND_IF_H

#include "wmxSDK_DnD_Cmn.h"


/// <summary>
/// Gets the trace string and parameters of the next trace in the L4. Returns -1 in the string size when the buffer is finished.
/// </summary>
///
/// <param name="retString">[OUT]A NULL terminated string. Memory is allocated by the user.</param>
/// <param name="nRetStringSize">[IN,OUT]The size of the allocated buffer in bytes. Returns the actual null terminated string size returned.
///  0 returned means this is an internal trace and nothing will be returned in retString for this trace
///  -1 returned means we've reached the end of the trace buffer</param>
/// <param name="internalTimestamp">[OUT] The trace's internal timestamp. 0 if it doesn't exist.</param>
/// <param name="severity">[OUT] The trace severity</param>
/// <param name="subsys">[OUT] The trace's syb system</param>
/// <param name="module">[OUT] The trace's module</param>
/// <param name="overrun">[OUT] A NULL terminated string (size 10) representing whether an overrun occured or not.</param>
/// <param name="fileName">[OUT] The filaname at which the trace occured.</param>
/// <param name="lineNum">[OUT] The linenum at which the trace occured.</param>
/// <param name="rawData">[OUT] The returned string of the trace. Memory allocation by the user.</param>
/// <param name="nRawDataSize">[IN,OUT] The size of the allocated buffer. The actual size of the buffer will be returned.
///  If the size of the allocated buffer is too small this will be set to the size required and an error will be issued.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
typedef wmx_Status_t (WMX_EXT_CALL_CONV * wmxDnD_GetNextTrace)( 	char * retString, 
																   INT32 * nRetStringSize,	
																   UINT32 * internalTimestamp,
																   UINT32 * severity, 
																   UINT32 * subsys, 
																   UINT32 * module, 
																   char overrun[], 
																   char * fileName, 
																   UINT32 * lineNum, 
																   char * rawData,
																   UINT32 * nRawDataSize);


/// <summary>
/// The Init API causes the followings:
/// - The Wrapper will save the CB given by the User
/// - Init the Pipe Handler
/// - Init the thread reading files
/// - Load the TRC files to the memory (they should be located along side with the Wrapper
/// </summary>
/// <param name="useMonitor">[IN]TRUE if uses Monitors and FALSE otherwise</param>
/// <param name="useTrace">[IN]TRUE if uses Traces and FALSE otherwise</param>
/// <param name="isOnlineMode">[IN]TRUE if uses Online mode and FALSE for Offline mode</param>
/// <param name="filesPrefix">[IN]The IP address of the AppSrv. If parameter is NULL the address will be read from the registry</param>
/// <param name="appSrvIpAdd">[IN]The IP address of the AppSrv. If parameter is NULL the address will be read from the registry</param>
/// <param name="offlineFilesPath">[IN]The directory of the Offline files. IF parameter is NULL or Directory doesn't exist in Offline mode an error will be issued and Init will fail</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxDnD_Init(BOOL useMonitor, BOOL useTrace, BOOL isOnlineMode , const WCHAR *filesPrefix, const char *appSrvIpAdd, const WCHAR *offlineFilesPath );

/// <summary>
/// The Init API causes the followings:
/// - The Wrapper will save the CB given by the User
/// - Init the Pipe Handler
/// - Init the thread reading files
/// - Load the TRC files to the memory (they should be located along side with the Wrapper
/// </summary>
/// <param name="useMonitor">[IN]TRUE if uses Monitors and FALSE otherwise</param>
/// <param name="useTrace">[IN]TRUE if uses Traces and FALSE otherwise</param>
/// <param name="isOnlineMode">[IN]TRUE if uses Online mode and FALSE for Offline mode</param>
/// <param name="traceFilesPrefix">[IN]The prefix of the traces files.</param>
/// <param name="monitorFilesPrefix">[IN]The prefix of the monitors files.</param>
/// <param name="appSrvIpAdd">[IN]The IP address of the AppSrv. If parameter is NULL the address will be read from the registry</param>
/// <param name="offlineFilesPath">[IN]The directory of the Offline files. IF parameter is NULL or Directory doesn't exist in Offline mode an error will be issued and Init will fail</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxDnD_InitEx(BOOL useMonitor, BOOL useTrace, BOOL isOnlineMode , const WCHAR *traceFilesPrefix, const WCHAR *monitorFilesPrefix, const char *appSrvIpAdd, const WCHAR *offlineFilesPath );

/// <summary>
/// Finalizes the use of the Pipe Handler
/// </summary>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxDnD_Finalize();

/// <summary>
/// Gets the next message from the device.
/// The wrapper will only return requested types (Monitor/Trace) -
/// according to the init parameters
/// </summary>
///
/// <param name="pMsgBuff">[OUT]The returned buffer - An L4 formatted buffer. The user should allocate the buffer.</param>
/// <param name="nMsgBuffMaxSize">[IN,OUT]The buffer's allocated size as input. Actual size returned as output. If no message is found a zero will be returned</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxDnD_GetMessage(char * pMsgBuff, UINT32 * nMsgBuffSize);

/// <summary>
/// Gets the next trace message from the device.
/// The wrapper will only return requested types (Monitor/Trace) -
/// according to the init parameters
/// </summary>
///
/// <param name="pMsgBuff">[OUT]The returned buffer - An L4 formatted buffer. The user should allocate the buffer.</param>
/// <param name="nMsgBuffMaxSize">[IN,OUT]The buffer's allocated size as input. Actual size returned as output. If no message is found a zero will be returned</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxDnD_GetTraceMessage(char * pMsgBuff, UINT32 * nMsgBuffSize);

/// <summary>
/// Gets the next monitor message from the device.
/// The wrapper will only return requested types (Monitor/Trace) -
/// according to the init parameters
/// </summary>
///
/// <param name="pMsgBuff">[OUT]The returned buffer - An L4 formatted buffer. The user should allocate the buffer.</param>
/// <param name="nMsgBuffMaxSize">[IN,OUT]The buffer's allocated size as input. Actual size returned as output. If no message is found a zero will be returned</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxDnD_GetMonitorMessage(char * pMsgBuff, UINT32 * nMsgBuffSize);


/// <summary>
/// Causes the DnD Agent to start writing DnD files 
/// </summary>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxDnD_EnableFileWriting();


/// <summary>
/// Causes the DnD Agent to stop writing DnD files
/// </summary>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxDnD_DisableFileWriting();

/// <summary>
/// Causes the DnD wrapper to read data from the place where the DnD Agent is currently writing to.
/// </summary>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxDnD_SyncFileReading();

/// <summary>
/// Causes the DnD wrapper to read data from the place where the DnD Agent is currently writing to.
/// </summary>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxDnD_SyncTraceFileReading();

/// <summary>
/// Causes the DnD wrapper to read data from the place where the DnD Agent is currently writing to.
/// </summary>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxDnD_SyncMonitorFileReading();

/// <summary>
/// Sets the directory at which the DnD files will be stored.
/// </summary>
///
/// <param name="filesPath">[IN] The full path to the directory at which the DnD files should be stored</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxDnD_SetOnlineFilesRootPath( const WCHAR * filesPath );


/// <summary>
/// Gets the directory at which the DnD files are stored.
/// </summary>

/// <param name="pFilesPath">[OUT] The full path to the directory at which the DnD files are stored.</param>
/// <param name="nfilesMaxPathLength">[IN] The maximum size in WCHAR (short) of the full path.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxDnD_GetFullPathToOnlineFiles( WCHAR * pFilesPath, UINT32 nfilesMaxPathLength );

/// <summary>
/// Configures the Device to start sending Monitors up. Messages sent up are
/// according to last filtering request.
/// </summary>
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxDnD_MonitorON();

/// <summary>
/// Configures the Device to stop sending Monitors up. The Current filtering will be
/// saved by the device, which means that if a MonitorON is sent later again, the device
/// will only send up relevant monitor messages which are set by the last filtering
/// </summary>

/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxDnD_MonitorOFF();

/// <summary>
/// Sets the monitor filtering which is sent to the device.
/// The filtering should include the rate in frames for each periooic and event groups (The indexes for the groups are pre-defined).
/// The device will send up the groups according to the rate for each group (every x frames)
/// For event groups send rate 0 or 1. No error will be returned if rate is larger than 1 for events and the group might not be sent up.
/// </summary>
///
/// <param name="pMonitorFilterBuff">[IN] The buffer of the monitor filtering. The buffer should include rates in frames for all groups.</param>
/// <param name="nMonitorFilterBuffSize">[IN] The size of the buffer in bytes.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxDnD_SetMonitorFilter( char * pMonitorFilterBuff, UINT32 nMonitorFilterBuffSize );

/// <summary>
/// Gets the monitor filtering which is currently set in the device.
/// </summary>
///
/// <param name="pMonitorFilterBuff">[OUT] The buffer of the monitor filtering. The buffer includes rates in frames for each group.</param>
/// <param name="nMonitorFilterBuffSize">[OUT] The size of the buffer in bytes.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxDnD_GetMonitorFilter( char * pMonitorFilterBuff, UINT32 * nMonitorFilterBuffSize );

/// <summary>
/// Sets the trace filterting which is sent to the device.
/// The filtering should include severities for each module (the indexes for the modules are pre-defined)
/// The device will send all traces in the certain module with the severity specified and larger severities.
/// </summary>
///
/// <param name="pTraceFilterBuff">[IN] The buffer of the trace filtering.The buffer should include the severity for all modules.</param>
/// <param name="nMonitorFilterArrSize">[IN] The size of the buffer in bytes</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxDnD_SetTraceFilter(char * pTraceFilterBuff, UINT32 nTraceFilterBuffSize);

/// <summary>
/// Gets the trace filterting which is currently set in the device.
/// </summary>
///
/// <param name="pTraceFilterBuff">[OUT] The buffer of the trace filtering.The buffer includes the severity for each module.</param>
/// <param name="nMonitorFilterArrSize">[OUT] The size of the buffer in bytes</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxDnD_GetTraceFilter(char * pTraceFilterBuff, UINT32 * nTraceFilterBuffSize);

/// <summary>
/// Gets the current file index that the DnDWrapper reads.
/// </summary>
///
/// <param name="nCurrentFileIndex">[OUT] The index of the file that the DnDWrapper currently reads.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxDnD_GetCurrentFileIndex(UINT32 * nCurrentFileIndex);

/// <summary>
/// Gets the current trace file index that the DnDWrapper reads.
/// </summary>
///
/// <param name="nCurrentFileIndex">[OUT] The index of the trace file that the DnDWrapper currently reads.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxDnD_GetCurrentTraceFileIndex(UINT32 * nCurrentFileIndex);

/// <summary>
/// Gets the current monitor file index that the DnDWrapper reads.
/// </summary>
///
/// <param name="nCurrentFileIndex">[OUT] The index of the monitor file that the DnDWrapper currently reads.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxDnD_GetCurrentMonitorFileIndex(UINT32 * nCurrentFileIndex);

/// <summary>
/// Sets a new configuration to the wrapper (If user in interested in Trace/Monitors).
/// </summary>
///
/// <param name="useMonitor">[IN]Is the user interested in Monitors</param>
/// <param name="useTrace">[IN] Is the user interested in Traces</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxDnD_SetConfiguration(BOOL useMonitor, BOOL useTrace);

/// <summary>
/// Gets the current configuration currently set to the wrapper (If user in interested in Trace/Monitors).
/// </summary>
///
/// <param name="useMonitor">[OUT]Did the user currently request monitors</param>
/// <param name="useTrace">[OUT] Did the user currently request traces</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxDnD_GetConfiguration(BOOL * useMonitor, BOOL * useTrace);

/// <summary>
/// Returns the GetNext function which gets the info of each trace. Returns the full BS timestamp of the trace.  
/// </summary>
///
/// <param name="pL4Buff">[IN] The trace buffer</param>
/// <param name="msbTimestamp">[OUT] The returned BS Timer - 32 Bits MSB</param>
/// <param name="lsbTimestamp">[OUT] The returned BS Timer - 32 Bits LSB</param>
/// <param name="pFunc">[OUT] The returned parser function</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxDnD_InitTraceParseFunc(char * pL4Buff, UINT32 * msbTimestamp, UINT32 * lsbTimeStamp, wmxDnD_GetNextTrace * pFunc);

/// <summary>
/// Registers for a connection with the device status event (Connected/Disconnected) 
/// </summary>
///
/// <param name="pEventsCB">[IN]The CB to be run when the connection status with the device is changed</param>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxDnD_RegisterCtrlStatusUpdatesCB(wmx_pCtrlStatusUpdateCB_t pEventsCB);


/// <summary>
/// This API allows the user to unregister for device connection events.
/// </summary>
///
/// <param name="pEventsCB">(IN) A pointer to the application function to be called upon device connection status change.</param>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxDnD_UnregisterCtrlStatusUpdatesCB(wmx_pCtrlStatusUpdateCB_t pEventsCB);


/// <summary>
/// Gets the connection status to the device 
/// </summary>
///
/// <returns>An enum indicating whether the device is Connected or Disconnected</returns>
wmx_CtrlStatus_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxDnD_GetCtrlStatus();


/// <summary>
/// Gets the Wrapper's version.
/// </summary>
///
/// <param name="version">[OUT]The version of the wrapper in struct format</param>
/// <param name="versionStr">[OUT]The version of the wrapper in string format. Buffer allocation by the user. If the allocated buffer is too short an WMX_ST_BUFFER_TOO_SHORT error will be issued</param>
/// <param name="verMaxLen">[IN]The length of the allocated buffer.</param>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxDnD_GetVersion(wmx_pVersion_t version, wmx_pVersionStr_t versionStr, wmx_VersionStrLen_t verMaxLen);

#endif // _WMX_SDK_DND_IF_H
