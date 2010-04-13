
/****************************************************************************
*
* Auto generated file
* Version XXX
* Compliant with XXX.bm version XXX
* 11/19/2009 12:55:59 AM
*
*****************************************************************************/

#ifndef _L4BUFMAN_L3L4STRUCTS_H
#define _L4BUFMAN_L3L4STRUCTS_H


#include "L4BufMan_L3L4Structs_Desc.h"
#include "L4BufMan_L4Common.h"





//
// GetL4MVersion
//
L4BUFMAN_Status_t L4BM_Get_GetL4MVersion(GetL4MVersion_type* pMsg, UINT8* buf);
L4BUFMAN_Status_t L4BM_Set_GetL4MVersion(UINT8* pBuf, GetL4MVersion_type msg);
UINT L4BM_GetBufferSize_GetL4MVersion(GetL4MVersion_type msg);
UINT L4BM_GetMaxBufferSize_GetL4MVersion( void );
void L4BM_Init_GetL4MVersion(GetL4MVersion_type* pMsg);
extern L4bufman_Funcs GetL4MVersion_Funcs;


//
// ReportKeyRequest
//
L4BUFMAN_Status_t L4BM_Get_ReportKeyRequest(ReportKeyRequest_type* pMsg, UINT8* buf);
L4BUFMAN_Status_t L4BM_Set_ReportKeyRequest(UINT8* pBuf, ReportKeyRequest_type msg);
UINT L4BM_GetBufferSize_ReportKeyRequest(ReportKeyRequest_type msg);
UINT L4BM_GetMaxBufferSize_ReportKeyRequest( void );
void L4BM_Init_ReportKeyRequest(ReportKeyRequest_type* pMsg);
extern L4bufman_Funcs ReportKeyRequest_Funcs;


//
// TLSOperationRequest
//
L4BUFMAN_Status_t L4BM_Get_TLSOperationRequest(TLSOperationRequest_type* pMsg, UINT8* buf);
L4BUFMAN_Status_t L4BM_Set_TLSOperationRequest(UINT8* pBuf, TLSOperationRequest_type msg);
UINT L4BM_GetBufferSize_TLSOperationRequest(TLSOperationRequest_type msg);
UINT L4BM_GetMaxBufferSize_TLSOperationRequest( void );
void L4BM_Init_TLSOperationRequest(TLSOperationRequest_type* pMsg);
extern L4bufman_Funcs TLSOperationRequest_Funcs;


//
// SetScanParameters
//
L4BUFMAN_Status_t L4BM_Get_SetScanParameters(SetScanParameters_type* pMsg, UINT8* buf);
L4BUFMAN_Status_t L4BM_Set_SetScanParameters(UINT8* pBuf, SetScanParameters_type msg);
UINT L4BM_GetBufferSize_SetScanParameters(SetScanParameters_type msg);
UINT L4BM_GetMaxBufferSize_SetScanParameters( void );
void L4BM_Init_SetScanParameters(SetScanParameters_type* pMsg);
extern L4bufman_Funcs SetScanParameters_Funcs;


//
// Connect
//
L4BUFMAN_Status_t L4BM_Get_Connect(Connect_type* pMsg, UINT8* buf);
L4BUFMAN_Status_t L4BM_Set_Connect(UINT8* pBuf, Connect_type msg);
UINT L4BM_GetBufferSize_Connect(Connect_type msg);
UINT L4BM_GetMaxBufferSize_Connect( void );
void L4BM_Init_Connect(Connect_type* pMsg);
extern L4bufman_Funcs Connect_Funcs;


//
// MOC_Request
//
L4BUFMAN_Status_t L4BM_Get_MOC_Request(MOC_Request_type* pMsg, UINT8* buf);
L4BUFMAN_Status_t L4BM_Set_MOC_Request(UINT8* pBuf, MOC_Request_type msg);
UINT L4BM_GetBufferSize_MOC_Request(MOC_Request_type msg);
UINT L4BM_GetMaxBufferSize_MOC_Request( void );
void L4BM_Init_MOC_Request(MOC_Request_type* pMsg);
extern L4bufman_Funcs MOC_Request_Funcs;


//
// RfControl
//
L4BUFMAN_Status_t L4BM_Get_RfControl(RfControl_type* pMsg, UINT8* buf);
L4BUFMAN_Status_t L4BM_Set_RfControl(UINT8* pBuf, RfControl_type msg);
UINT L4BM_GetBufferSize_RfControl(RfControl_type msg);
UINT L4BM_GetMaxBufferSize_RfControl( void );
void L4BM_Init_RfControl(RfControl_type* pMsg);
extern L4bufman_Funcs RfControl_Funcs;


//
// ReportEapRestart
//
L4BUFMAN_Status_t L4BM_Get_ReportEapRestart(ReportEapRestart_type* pMsg, UINT8* buf);
L4BUFMAN_Status_t L4BM_Set_ReportEapRestart(UINT8* pBuf, ReportEapRestart_type msg);
UINT L4BM_GetBufferSize_ReportEapRestart(ReportEapRestart_type msg);
UINT L4BM_GetMaxBufferSize_ReportEapRestart( void );
void L4BM_Init_ReportEapRestart(ReportEapRestart_type* pMsg);
extern L4bufman_Funcs ReportEapRestart_Funcs;


//
// ReportEapRequest
//
L4BUFMAN_Status_t L4BM_Get_ReportEapRequest(ReportEapRequest_type* pMsg, UINT8* buf);
L4BUFMAN_Status_t L4BM_Set_ReportEapRequest(UINT8* pBuf, ReportEapRequest_type msg);
UINT L4BM_GetBufferSize_ReportEapRequest(ReportEapRequest_type msg);
UINT L4BM_GetMaxBufferSize_ReportEapRequest( void );
void L4BM_Init_ReportEapRequest(ReportEapRequest_type* pMsg);
extern L4bufman_Funcs ReportEapRequest_Funcs;


//
// ReportRecentNbrHood
//
L4BUFMAN_Status_t L4BM_Get_ReportRecentNbrHood(ReportRecentNbrHood_type* pMsg, UINT8* buf);
L4BUFMAN_Status_t L4BM_Set_ReportRecentNbrHood(UINT8* pBuf, ReportRecentNbrHood_type msg);
UINT L4BM_GetBufferSize_ReportRecentNbrHood(ReportRecentNbrHood_type msg);
UINT L4BM_GetMaxBufferSize_ReportRecentNbrHood( void );
void L4BM_Init_ReportRecentNbrHood(ReportRecentNbrHood_type* pMsg);
extern L4bufman_Funcs ReportRecentNbrHood_Funcs;


//
// GetLinkStatus
//
L4BUFMAN_Status_t L4BM_Get_GetLinkStatus(GetLinkStatus_type* pMsg, UINT8* buf);
L4BUFMAN_Status_t L4BM_Set_GetLinkStatus(UINT8* pBuf, GetLinkStatus_type msg);
UINT L4BM_GetBufferSize_GetLinkStatus(GetLinkStatus_type msg);
UINT L4BM_GetMaxBufferSize_GetLinkStatus( void );
void L4BM_Init_GetLinkStatus(GetLinkStatus_type* pMsg);
extern L4bufman_Funcs GetLinkStatus_Funcs;


//
// SetD2HChannelMask
//
L4BUFMAN_Status_t L4BM_Get_SetD2HChannelMask(SetD2HChannelMask_type* pMsg, UINT8* buf);
L4BUFMAN_Status_t L4BM_Set_SetD2HChannelMask(UINT8* pBuf, SetD2HChannelMask_type msg);
UINT L4BM_GetBufferSize_SetD2HChannelMask(SetD2HChannelMask_type msg);
UINT L4BM_GetMaxBufferSize_SetD2HChannelMask( void );
void L4BM_Init_SetD2HChannelMask(SetD2HChannelMask_type* pMsg);
extern L4bufman_Funcs SetD2HChannelMask_Funcs;


//
// EnterPowerSaveCommand
//
L4BUFMAN_Status_t L4BM_Get_EnterPowerSaveCommand(EnterPowerSaveCommand_type* pMsg, UINT8* buf);
L4BUFMAN_Status_t L4BM_Set_EnterPowerSaveCommand(UINT8* pBuf, EnterPowerSaveCommand_type msg);
UINT L4BM_GetBufferSize_EnterPowerSaveCommand(EnterPowerSaveCommand_type msg);
UINT L4BM_GetMaxBufferSize_EnterPowerSaveCommand( void );
void L4BM_Init_EnterPowerSaveCommand(EnterPowerSaveCommand_type* pMsg);
extern L4bufman_Funcs EnterPowerSaveCommand_Funcs;


//
// SPLockStatusInfo
//
L4BUFMAN_Status_t L4BM_Get_SPLockStatusInfo(SPLockStatusInfo_type* pMsg, UINT8* buf);
L4BUFMAN_Status_t L4BM_Set_SPLockStatusInfo(UINT8* pBuf, SPLockStatusInfo_type msg);
UINT L4BM_GetBufferSize_SPLockStatusInfo(SPLockStatusInfo_type msg);
UINT L4BM_GetMaxBufferSize_SPLockStatusInfo( void );
void L4BM_Init_SPLockStatusInfo(SPLockStatusInfo_type* pMsg);
extern L4bufman_Funcs SPLockStatusInfo_Funcs;


//
// GetMediaStatus
//
L4BUFMAN_Status_t L4BM_Get_GetMediaStatus(GetMediaStatus_type* pMsg, UINT8* buf);
L4BUFMAN_Status_t L4BM_Set_GetMediaStatus(UINT8* pBuf, GetMediaStatus_type msg);
UINT L4BM_GetBufferSize_GetMediaStatus(GetMediaStatus_type msg);
UINT L4BM_GetMaxBufferSize_GetMediaStatus( void );
void L4BM_Init_GetMediaStatus(GetMediaStatus_type* pMsg);
extern L4bufman_Funcs GetMediaStatus_Funcs;


//
// GetState
//
L4BUFMAN_Status_t L4BM_Get_GetState(GetState_type* pMsg, UINT8* buf);
L4BUFMAN_Status_t L4BM_Set_GetState(UINT8* pBuf, GetState_type msg);
UINT L4BM_GetBufferSize_GetState(GetState_type msg);
UINT L4BM_GetMaxBufferSize_GetState( void );
void L4BM_Init_GetState(GetState_type* pMsg);
extern L4bufman_Funcs GetState_Funcs;


//
// GetScanResults
//
L4BUFMAN_Status_t L4BM_Get_GetScanResults(GetScanResults_type* pMsg, UINT8* buf);
L4BUFMAN_Status_t L4BM_Set_GetScanResults(UINT8* pBuf, GetScanResults_type msg);
UINT L4BM_GetBufferSize_GetScanResults(GetScanResults_type msg);
UINT L4BM_GetMaxBufferSize_GetScanResults( void );
void L4BM_Init_GetScanResults(GetScanResults_type* pMsg);
extern L4bufman_Funcs GetScanResults_Funcs;


//
// ReportEMSKRelatedKeys
//
L4BUFMAN_Status_t L4BM_Get_ReportEMSKRelatedKeys(ReportEMSKRelatedKeys_type* pMsg, UINT8* buf);
L4BUFMAN_Status_t L4BM_Set_ReportEMSKRelatedKeys(UINT8* pBuf, ReportEMSKRelatedKeys_type msg);
UINT L4BM_GetBufferSize_ReportEMSKRelatedKeys(ReportEMSKRelatedKeys_type msg);
UINT L4BM_GetMaxBufferSize_ReportEMSKRelatedKeys( void );
void L4BM_Init_ReportEMSKRelatedKeys(ReportEMSKRelatedKeys_type* pMsg);
extern L4bufman_Funcs ReportEMSKRelatedKeys_Funcs;


//
// ReportScanResults
//
L4BUFMAN_Status_t L4BM_Get_ReportScanResults(ReportScanResults_type* pMsg, UINT8* buf);
L4BUFMAN_Status_t L4BM_Set_ReportScanResults(UINT8* pBuf, ReportScanResults_type msg);
UINT L4BM_GetBufferSize_ReportScanResults(ReportScanResults_type msg);
UINT L4BM_GetMaxBufferSize_ReportScanResults( void );
void L4BM_Init_ReportScanResults(ReportScanResults_type* pMsg);
extern L4bufman_Funcs ReportScanResults_Funcs;


//
// SetMonitorFilterTable
//
L4BUFMAN_Status_t L4BM_Get_SetMonitorFilterTable(SetMonitorFilterTable_type* pMsg, UINT8* buf);
L4BUFMAN_Status_t L4BM_Set_SetMonitorFilterTable(UINT8* pBuf, SetMonitorFilterTable_type msg);
UINT L4BM_GetBufferSize_SetMonitorFilterTable(SetMonitorFilterTable_type msg);
UINT L4BM_GetMaxBufferSize_SetMonitorFilterTable( void );
void L4BM_Init_SetMonitorFilterTable(SetMonitorFilterTable_type* pMsg);
extern L4bufman_Funcs SetMonitorFilterTable_Funcs;


//
// CmdCoexProcessEnd
//
L4BUFMAN_Status_t L4BM_Get_CmdCoexProcessEnd(CmdCoexProcessEnd_type* pMsg, UINT8* buf);
L4BUFMAN_Status_t L4BM_Set_CmdCoexProcessEnd(UINT8* pBuf, CmdCoexProcessEnd_type msg);
UINT L4BM_GetBufferSize_CmdCoexProcessEnd(CmdCoexProcessEnd_type msg);
UINT L4BM_GetMaxBufferSize_CmdCoexProcessEnd( void );
void L4BM_Init_CmdCoexProcessEnd(CmdCoexProcessEnd_type* pMsg);
extern L4bufman_Funcs CmdCoexProcessEnd_Funcs;


//
// GetD2HChannelMask
//
L4BUFMAN_Status_t L4BM_Get_GetD2HChannelMask(GetD2HChannelMask_type* pMsg, UINT8* buf);
L4BUFMAN_Status_t L4BM_Set_GetD2HChannelMask(UINT8* pBuf, GetD2HChannelMask_type msg);
UINT L4BM_GetBufferSize_GetD2HChannelMask(GetD2HChannelMask_type msg);
UINT L4BM_GetMaxBufferSize_GetD2HChannelMask( void );
void L4BM_Init_GetD2HChannelMask(GetD2HChannelMask_type* pMsg);
extern L4bufman_Funcs GetD2HChannelMask_Funcs;


//
// SetPreInitConfiguration
//
L4BUFMAN_Status_t L4BM_Get_SetPreInitConfiguration(SetPreInitConfiguration_type* pMsg, UINT8* buf);
L4BUFMAN_Status_t L4BM_Set_SetPreInitConfiguration(UINT8* pBuf, SetPreInitConfiguration_type msg);
UINT L4BM_GetBufferSize_SetPreInitConfiguration(SetPreInitConfiguration_type msg);
UINT L4BM_GetMaxBufferSize_SetPreInitConfiguration( void );
void L4BM_Init_SetPreInitConfiguration(SetPreInitConfiguration_type* pMsg);
extern L4bufman_Funcs SetPreInitConfiguration_Funcs;


//
// CheckL3L4InterfaceGET
//
L4BUFMAN_Status_t L4BM_Get_CheckL3L4InterfaceGET(CheckL3L4InterfaceGET_type* pMsg, UINT8* buf);
L4BUFMAN_Status_t L4BM_Set_CheckL3L4InterfaceGET(UINT8* pBuf, CheckL3L4InterfaceGET_type msg);
UINT L4BM_GetBufferSize_CheckL3L4InterfaceGET(CheckL3L4InterfaceGET_type msg);
UINT L4BM_GetMaxBufferSize_CheckL3L4InterfaceGET( void );
void L4BM_Init_CheckL3L4InterfaceGET(CheckL3L4InterfaceGET_type* pMsg);
extern L4bufman_Funcs CheckL3L4InterfaceGET_Funcs;


//
// ReportSII
//
L4BUFMAN_Status_t L4BM_Get_ReportSII(ReportSII_type* pMsg, UINT8* buf);
L4BUFMAN_Status_t L4BM_Set_ReportSII(UINT8* pBuf, ReportSII_type msg);
UINT L4BM_GetBufferSize_ReportSII(ReportSII_type msg);
UINT L4BM_GetMaxBufferSize_ReportSII( void );
void L4BM_Init_ReportSII(ReportSII_type* pMsg);
extern L4bufman_Funcs ReportSII_Funcs;


//
// ScanCommand
//
L4BUFMAN_Status_t L4BM_Get_ScanCommand(ScanCommand_type* pMsg, UINT8* buf);
L4BUFMAN_Status_t L4BM_Set_ScanCommand(UINT8* pBuf, ScanCommand_type msg);
UINT L4BM_GetBufferSize_ScanCommand(ScanCommand_type msg);
UINT L4BM_GetMaxBufferSize_ScanCommand( void );
void L4BM_Init_ScanCommand(ScanCommand_type* pMsg);
extern L4bufman_Funcs ScanCommand_Funcs;


//
// TerminateCommand
//
L4BUFMAN_Status_t L4BM_Get_TerminateCommand(TerminateCommand_type* pMsg, UINT8* buf);
L4BUFMAN_Status_t L4BM_Set_TerminateCommand(UINT8* pBuf, TerminateCommand_type msg);
UINT L4BM_GetBufferSize_TerminateCommand(TerminateCommand_type msg);
UINT L4BM_GetMaxBufferSize_TerminateCommand( void );
void L4BM_Init_TerminateCommand(TerminateCommand_type* pMsg);
extern L4bufman_Funcs TerminateCommand_Funcs;


//
// ReadyForPowerSave
//
L4BUFMAN_Status_t L4BM_Get_ReadyForPowerSave(ReadyForPowerSave_type* pMsg, UINT8* buf);
L4BUFMAN_Status_t L4BM_Set_ReadyForPowerSave(UINT8* pBuf, ReadyForPowerSave_type msg);
UINT L4BM_GetBufferSize_ReadyForPowerSave(ReadyForPowerSave_type msg);
UINT L4BM_GetMaxBufferSize_ReadyForPowerSave( void );
void L4BM_Init_ReadyForPowerSave(ReadyForPowerSave_type* pMsg);
extern L4bufman_Funcs ReadyForPowerSave_Funcs;


//
// Disconnect
//
L4BUFMAN_Status_t L4BM_Get_Disconnect(Disconnect_type* pMsg, UINT8* buf);
L4BUFMAN_Status_t L4BM_Set_Disconnect(UINT8* pBuf, Disconnect_type msg);
UINT L4BM_GetBufferSize_Disconnect(Disconnect_type msg);
UINT L4BM_GetMaxBufferSize_Disconnect( void );
void L4BM_Init_Disconnect(Disconnect_type* pMsg);
extern L4bufman_Funcs Disconnect_Funcs;


//
// SetEapSuccess
//
L4BUFMAN_Status_t L4BM_Get_SetEapSuccess(SetEapSuccess_type* pMsg, UINT8* buf);
L4BUFMAN_Status_t L4BM_Set_SetEapSuccess(UINT8* pBuf, SetEapSuccess_type msg);
UINT L4BM_GetBufferSize_SetEapSuccess(SetEapSuccess_type msg);
UINT L4BM_GetMaxBufferSize_SetEapSuccess( void );
void L4BM_Init_SetEapSuccess(SetEapSuccess_type* pMsg);
extern L4bufman_Funcs SetEapSuccess_Funcs;


//
// CmdCoexProcessStart
//
L4BUFMAN_Status_t L4BM_Get_CmdCoexProcessStart(CmdCoexProcessStart_type* pMsg, UINT8* buf);
L4BUFMAN_Status_t L4BM_Set_CmdCoexProcessStart(UINT8* pBuf, CmdCoexProcessStart_type msg);
UINT L4BM_GetBufferSize_CmdCoexProcessStart(CmdCoexProcessStart_type msg);
UINT L4BM_GetMaxBufferSize_CmdCoexProcessStart( void );
void L4BM_Init_CmdCoexProcessStart(CmdCoexProcessStart_type* pMsg);
extern L4bufman_Funcs CmdCoexProcessStart_Funcs;


//
// InitCommand
//
L4BUFMAN_Status_t L4BM_Get_InitCommand(InitCommand_type* pMsg, UINT8* buf);
L4BUFMAN_Status_t L4BM_Set_InitCommand(UINT8* pBuf, InitCommand_type msg);
UINT L4BM_GetBufferSize_InitCommand(InitCommand_type msg);
UINT L4BM_GetMaxBufferSize_InitCommand( void );
void L4BM_Init_InitCommand(InitCommand_type* pMsg);
extern L4bufman_Funcs InitCommand_Funcs;


//
// SetEapKey
//
L4BUFMAN_Status_t L4BM_Get_SetEapKey(SetEapKey_type* pMsg, UINT8* buf);
L4BUFMAN_Status_t L4BM_Set_SetEapKey(UINT8* pBuf, SetEapKey_type msg);
UINT L4BM_GetBufferSize_SetEapKey(SetEapKey_type msg);
UINT L4BM_GetMaxBufferSize_SetEapKey( void );
void L4BM_Init_SetEapKey(SetEapKey_type* pMsg);
extern L4bufman_Funcs SetEapKey_Funcs;


//
// CheckL3L4InterfaceSET
//
L4BUFMAN_Status_t L4BM_Get_CheckL3L4InterfaceSET(CheckL3L4InterfaceSET_type* pMsg, UINT8* buf);
L4BUFMAN_Status_t L4BM_Set_CheckL3L4InterfaceSET(UINT8* pBuf, CheckL3L4InterfaceSET_type msg);
UINT L4BM_GetBufferSize_CheckL3L4InterfaceSET(CheckL3L4InterfaceSET_type msg);
UINT L4BM_GetMaxBufferSize_CheckL3L4InterfaceSET( void );
void L4BM_Init_CheckL3L4InterfaceSET(CheckL3L4InterfaceSET_type* pMsg);
extern L4bufman_Funcs CheckL3L4InterfaceSET_Funcs;


//
// MOC_Broadcast
//
L4BUFMAN_Status_t L4BM_Get_MOC_Broadcast(MOC_Broadcast_type* pMsg, UINT8* buf);
L4BUFMAN_Status_t L4BM_Set_MOC_Broadcast(UINT8* pBuf, MOC_Broadcast_type msg);
UINT L4BM_GetBufferSize_MOC_Broadcast(MOC_Broadcast_type msg);
UINT L4BM_GetMaxBufferSize_MOC_Broadcast( void );
void L4BM_Init_MOC_Broadcast(MOC_Broadcast_type* pMsg);
extern L4bufman_Funcs MOC_Broadcast_Funcs;


//
// SetCoexMode
//
L4BUFMAN_Status_t L4BM_Get_SetCoexMode(SetCoexMode_type* pMsg, UINT8* buf);
L4BUFMAN_Status_t L4BM_Set_SetCoexMode(UINT8* pBuf, SetCoexMode_type msg);
UINT L4BM_GetBufferSize_SetCoexMode(SetCoexMode_type msg);
UINT L4BM_GetMaxBufferSize_SetCoexMode( void );
void L4BM_Init_SetCoexMode(SetCoexMode_type* pMsg);
extern L4bufman_Funcs SetCoexMode_Funcs;


//
// SetTraceSeverityTable
//
L4BUFMAN_Status_t L4BM_Get_SetTraceSeverityTable(SetTraceSeverityTable_type* pMsg, UINT8* buf);
L4BUFMAN_Status_t L4BM_Set_SetTraceSeverityTable(UINT8* pBuf, SetTraceSeverityTable_type msg);
UINT L4BM_GetBufferSize_SetTraceSeverityTable(SetTraceSeverityTable_type msg);
UINT L4BM_GetMaxBufferSize_SetTraceSeverityTable( void );
void L4BM_Init_SetTraceSeverityTable(SetTraceSeverityTable_type* pMsg);
extern L4bufman_Funcs SetTraceSeverityTable_Funcs;


//
// ReportBsInfo
//
L4BUFMAN_Status_t L4BM_Get_ReportBsInfo(ReportBsInfo_type* pMsg, UINT8* buf);
L4BUFMAN_Status_t L4BM_Set_ReportBsInfo(UINT8* pBuf, ReportBsInfo_type msg);
UINT L4BM_GetBufferSize_ReportBsInfo(ReportBsInfo_type msg);
UINT L4BM_GetMaxBufferSize_ReportBsInfo( void );
void L4BM_Init_ReportBsInfo(ReportBsInfo_type* pMsg);
extern L4bufman_Funcs ReportBsInfo_Funcs;


//
// SetEapFail
//
L4BUFMAN_Status_t L4BM_Get_SetEapFail(SetEapFail_type* pMsg, UINT8* buf);
L4BUFMAN_Status_t L4BM_Set_SetEapFail(UINT8* pBuf, SetEapFail_type msg);
UINT L4BM_GetBufferSize_SetEapFail(SetEapFail_type msg);
UINT L4BM_GetMaxBufferSize_SetEapFail( void );
void L4BM_Init_SetEapFail(SetEapFail_type* pMsg);
extern L4bufman_Funcs SetEapFail_Funcs;


//
// MOC_Response
//
L4BUFMAN_Status_t L4BM_Get_MOC_Response(MOC_Response_type* pMsg, UINT8* buf);
L4BUFMAN_Status_t L4BM_Set_MOC_Response(UINT8* pBuf, MOC_Response_type msg);
UINT L4BM_GetBufferSize_MOC_Response(MOC_Response_type msg);
UINT L4BM_GetMaxBufferSize_MOC_Response( void );
void L4BM_Init_MOC_Response(MOC_Response_type* pMsg);
extern L4bufman_Funcs MOC_Response_Funcs;


//
// GetStatistics
//
L4BUFMAN_Status_t L4BM_Get_GetStatistics(GetStatistics_type* pMsg, UINT8* buf);
L4BUFMAN_Status_t L4BM_Set_GetStatistics(UINT8* pBuf, GetStatistics_type msg);
UINT L4BM_GetBufferSize_GetStatistics(GetStatistics_type msg);
UINT L4BM_GetMaxBufferSize_GetStatistics( void );
void L4BM_Init_GetStatistics(GetStatistics_type* pMsg);
extern L4bufman_Funcs GetStatistics_Funcs;


//
// GetDeviceInfo
//
L4BUFMAN_Status_t L4BM_Get_GetDeviceInfo(GetDeviceInfo_type* pMsg, UINT8* buf);
L4BUFMAN_Status_t L4BM_Set_GetDeviceInfo(UINT8* pBuf, GetDeviceInfo_type msg);
UINT L4BM_GetBufferSize_GetDeviceInfo(GetDeviceInfo_type msg);
UINT L4BM_GetMaxBufferSize_GetDeviceInfo( void );
void L4BM_Init_GetDeviceInfo(GetDeviceInfo_type* pMsg);
extern L4bufman_Funcs GetDeviceInfo_Funcs;


//
// CmdMonitorControl
//
L4BUFMAN_Status_t L4BM_Get_CmdMonitorControl(CmdMonitorControl_type* pMsg, UINT8* buf);
L4BUFMAN_Status_t L4BM_Set_CmdMonitorControl(UINT8* pBuf, CmdMonitorControl_type msg);
UINT L4BM_GetBufferSize_CmdMonitorControl(CmdMonitorControl_type msg);
UINT L4BM_GetMaxBufferSize_CmdMonitorControl( void );
void L4BM_Init_CmdMonitorControl(CmdMonitorControl_type* pMsg);
extern L4bufman_Funcs CmdMonitorControl_Funcs;


//
// CheckL3L4InterfaceREPORT
//
L4BUFMAN_Status_t L4BM_Get_CheckL3L4InterfaceREPORT(CheckL3L4InterfaceREPORT_type* pMsg, UINT8* buf);
L4BUFMAN_Status_t L4BM_Set_CheckL3L4InterfaceREPORT(UINT8* pBuf, CheckL3L4InterfaceREPORT_type msg);
UINT L4BM_GetBufferSize_CheckL3L4InterfaceREPORT(CheckL3L4InterfaceREPORT_type msg);
UINT L4BM_GetMaxBufferSize_CheckL3L4InterfaceREPORT( void );
void L4BM_Init_CheckL3L4InterfaceREPORT(CheckL3L4InterfaceREPORT_type* pMsg);
extern L4bufman_Funcs CheckL3L4InterfaceREPORT_Funcs;


//
// GetMonitorFilterTable
//
L4BUFMAN_Status_t L4BM_Get_GetMonitorFilterTable(GetMonitorFilterTable_type* pMsg, UINT8* buf);
L4BUFMAN_Status_t L4BM_Set_GetMonitorFilterTable(UINT8* pBuf, GetMonitorFilterTable_type msg);
UINT L4BM_GetBufferSize_GetMonitorFilterTable(GetMonitorFilterTable_type msg);
UINT L4BM_GetMaxBufferSize_GetMonitorFilterTable( void );
void L4BM_Init_GetMonitorFilterTable(GetMonitorFilterTable_type* pMsg);
extern L4bufman_Funcs GetMonitorFilterTable_Funcs;


//
// GetTraceSeverityTable
//
L4BUFMAN_Status_t L4BM_Get_GetTraceSeverityTable(GetTraceSeverityTable_type* pMsg, UINT8* buf);
L4BUFMAN_Status_t L4BM_Set_GetTraceSeverityTable(UINT8* pBuf, GetTraceSeverityTable_type msg);
UINT L4BM_GetBufferSize_GetTraceSeverityTable(GetTraceSeverityTable_type msg);
UINT L4BM_GetMaxBufferSize_GetTraceSeverityTable( void );
void L4BM_Init_GetTraceSeverityTable(GetTraceSeverityTable_type* pMsg);
extern L4bufman_Funcs GetTraceSeverityTable_Funcs;


//
// ResetDeviceCommand
//
L4BUFMAN_Status_t L4BM_Get_ResetDeviceCommand(ResetDeviceCommand_type* pMsg, UINT8* buf);
L4BUFMAN_Status_t L4BM_Set_ResetDeviceCommand(UINT8* pBuf, ResetDeviceCommand_type msg);
UINT L4BM_GetBufferSize_ResetDeviceCommand(ResetDeviceCommand_type msg);
UINT L4BM_GetMaxBufferSize_ResetDeviceCommand( void );
void L4BM_Init_ResetDeviceCommand(ResetDeviceCommand_type* pMsg);
extern L4bufman_Funcs ResetDeviceCommand_Funcs;


//
// CheckL3L4InterfaceCMD
//
L4BUFMAN_Status_t L4BM_Get_CheckL3L4InterfaceCMD(CheckL3L4InterfaceCMD_type* pMsg, UINT8* buf);
L4BUFMAN_Status_t L4BM_Set_CheckL3L4InterfaceCMD(UINT8* pBuf, CheckL3L4InterfaceCMD_type msg);
UINT L4BM_GetBufferSize_CheckL3L4InterfaceCMD(CheckL3L4InterfaceCMD_type msg);
UINT L4BM_GetMaxBufferSize_CheckL3L4InterfaceCMD( void );
void L4BM_Init_CheckL3L4InterfaceCMD(CheckL3L4InterfaceCMD_type* pMsg);
extern L4bufman_Funcs CheckL3L4InterfaceCMD_Funcs;


//
// ReportState
//
L4BUFMAN_Status_t L4BM_Get_ReportState(ReportState_type* pMsg, UINT8* buf);
L4BUFMAN_Status_t L4BM_Set_ReportState(UINT8* pBuf, ReportState_type msg);
UINT L4BM_GetBufferSize_ReportState(ReportState_type msg);
UINT L4BM_GetMaxBufferSize_ReportState( void );
void L4BM_Init_ReportState(ReportState_type* pMsg);
extern L4bufman_Funcs ReportState_Funcs;


//
// SPLockRequest
//
L4BUFMAN_Status_t L4BM_Get_SPLockRequest(SPLockRequest_type* pMsg, UINT8* buf);
L4BUFMAN_Status_t L4BM_Set_SPLockRequest(UINT8* pBuf, SPLockRequest_type msg);
UINT L4BM_GetBufferSize_SPLockRequest(SPLockRequest_type msg);
UINT L4BM_GetMaxBufferSize_SPLockRequest( void );
void L4BM_Init_SPLockRequest(SPLockRequest_type* pMsg);
extern L4bufman_Funcs SPLockRequest_Funcs;


//
// DebugLoopback
//
L4BUFMAN_Status_t L4BM_Get_DebugLoopback(DebugLoopback_type* pMsg, UINT8* buf);
L4BUFMAN_Status_t L4BM_Set_DebugLoopback(UINT8* pBuf, DebugLoopback_type msg);
UINT L4BM_GetBufferSize_DebugLoopback(DebugLoopback_type msg);
UINT L4BM_GetMaxBufferSize_DebugLoopback( void );
void L4BM_Init_DebugLoopback(DebugLoopback_type* pMsg);
extern L4bufman_Funcs DebugLoopback_Funcs;


//
// ReportAltAccept
//
L4BUFMAN_Status_t L4BM_Get_ReportAltAccept(ReportAltAccept_type* pMsg, UINT8* buf);
L4BUFMAN_Status_t L4BM_Set_ReportAltAccept(UINT8* pBuf, ReportAltAccept_type msg);
UINT L4BM_GetBufferSize_ReportAltAccept(ReportAltAccept_type msg);
UINT L4BM_GetMaxBufferSize_ReportAltAccept( void );
void L4BM_Init_ReportAltAccept(ReportAltAccept_type* pMsg);
extern L4bufman_Funcs ReportAltAccept_Funcs;


//
// ModeOfOperationCommand
//
L4BUFMAN_Status_t L4BM_Get_ModeOfOperationCommand(ModeOfOperationCommand_type* pMsg, UINT8* buf);
L4BUFMAN_Status_t L4BM_Set_ModeOfOperationCommand(UINT8* pBuf, ModeOfOperationCommand_type msg);
UINT L4BM_GetBufferSize_ModeOfOperationCommand(ModeOfOperationCommand_type msg);
UINT L4BM_GetMaxBufferSize_ModeOfOperationCommand( void );
void L4BM_Init_ModeOfOperationCommand(ModeOfOperationCommand_type* pMsg);
extern L4bufman_Funcs ModeOfOperationCommand_Funcs;


//
// SendEapResponse
//
L4BUFMAN_Status_t L4BM_Get_SendEapResponse(SendEapResponse_type* pMsg, UINT8* buf);
L4BUFMAN_Status_t L4BM_Set_SendEapResponse(UINT8* pBuf, SendEapResponse_type msg);
UINT L4BM_GetBufferSize_SendEapResponse(SendEapResponse_type msg);
UINT L4BM_GetMaxBufferSize_SendEapResponse( void );
void L4BM_Init_SendEapResponse(SendEapResponse_type* pMsg);
extern L4bufman_Funcs SendEapResponse_Funcs;



#endif //_L4BUFMAN_L3L4STRUCTS_H
