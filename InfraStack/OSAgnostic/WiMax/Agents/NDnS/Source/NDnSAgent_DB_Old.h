/*************************************************************************
**                                                                      **
**                  I N T E L ( ENVARA ) P R O P R I E T A R Y          **
**                                                                      **
**     COPYRIGHT (c)  2007 BY  INTEL  CORPORATION.  ALL RIGHTS          **
**     RESERVED.   NO  PART  OF THIS PROGRAM  OR  PUBLICATION  MAY      **
**     BE  REPRODUCED,   TRANSMITTED,   TRANSCRIBED,   STORED  IN  A    **
**     RETRIEVAL SYSTEM, OR TRANSLATED INTO ANY LANGUAGE OR COMPUTER    **
**     LANGUAGE IN ANY FORM OR BY ANY MEANS, ELECTRONIC, MECHANICAL,    **
**     MAGNETIC,  OPTICAL,  CHEMICAL, MANUAL, OR OTHERWISE,  WITHOUT    **
**     THE PRIOR WRITTEN PERMISSION OF INTEL  CORPORATION.              **
**                                                                      **
*************************************************************************/

/// <summary>
/// Description:
/// ------------
///	This H file includes the interfaces and defines of NDS agent DB
/// </summary>
///
///
///	<summary>
/// Change History:
/// ---------------
///
///  Date              By               	Description
/// ------------------------------------------------------------------------------
///  
///  24.05.2006        Sharon Amir			Created. 
///
/// ----------------------------------------------------------------------------*/
/// </summary>

#ifndef _NDS_AGENT_DB_
#define _NDS_AGENT_DB_
#include "NDnSAgent_Internals.h"
#include "wmxSDK_Nds_InternalStructs.h"
#include "wmxSDK_Apdo_Cmn.h"
#include "wmxSDK_Apdo_Utils.h"
#include "wmxSDK_Msc_2.h"
 
// General defines
#define ARRAY_SIZE(A)   (sizeof(A)/sizeof(A[0])) 
#define NDS_DB_INVALID_INDEX			(-1)
#define DEFAULT_TIME 0

// XML common string definitions 
#define APDO_XML_TRUE_STR "True"
#define APDO_XML_FALSE_STR "False"
#define APDO_XML_ON_STR "On"
#define APDO_XML_OFF_STR "Off"
#define APDO_XML_DISABLE "Disable"
#define APDO_XML_ENABLE  "Enable"
#define APDO_XML_MANUAL  "Manual"
#define APDO_XML_AUTO    "Auto"

// XML L4 string definitions 
#define APDO_XML_TOKEN_NDS_AGENT                  "NDS_Agent"
#define APDO_XML_TOKEN_NDS_CONFIGURATION          "NDS_Configuration"
#define APDO_XML_TOKEN_NDS_LAST_RF_STATE          "LastRfState"
#define APDO_XML_TOKEN_NDS_LAST_NSP               "LastNsp"
#define APDO_XML_TOKEN_NDS_THCRITERIA             "THCriteria"
#define APDO_XML_TOKEN_NDS_RSSI_THRESHOLD         "RssiThreshold"
#define APDO_XML_TOKEN_NDS_CINR_THRESHOLD         "CinrThreshold"
#define APDO_XML_TOKEN_NDS_LAST_NSP               "LastNsp"
#define APDO_XML_TOKEN_USER_CONNECTING_MODE       "UserConnectingMode"
#define APDO_XML_TOKEN_USER_ROAMING_MODE          "UserRoamingMode"
#define APDO_XML_ATTR_SERVER_ID                   "ServerId"
#define APDO_XML_ATTR_SUBSCRIBER_ID               "SubscriberId"
#define APDO_XML_ATTR_CHANNEL_ID                  "ChannelId"
#define APDO_XML_ATTR_NAP_ID                      "NAPId"
#define APDO_XML_TOKEN_NSP                        "NSP"
#define APDO_XML_TOKEN_NETWORK_PARM               "NetworkParameters"
#define APDO_XML_TOKEN_NSP_NAME                   "NSP_name"
#define APDO_XML_TOKEN_NSP_REALM                  "NSP_realm"
#define APDO_XML_TOKEN_ACTIVATION_FLAG            "NSP_activation_flag"
#define APDO_XML_TOKEN_APDO_VERSION               "NSP_APDO_package_version"
#define APDO_XML_TOKEN_NSP_IDS                    "NSP_IDs"
#define APDO_XML_TOKEN_NSP_ID                     "NSP_ID"
#define APDO_XML_TOKEN_CHANNEL_PLAN               "ChannelPlan"
#define APDO_XML_TOKEN_CHANNEL_INFO               "ChannelInfo"
#define APDO_XML_TOKEN_FREQ                       "Frequency"
#define APDO_XML_TOKEN_BANDWIDTH                  "BandWidth"
#define APDO_XML_TOKEN_FFT                        "fft"
#define APDO_XML_TOKEN_PREAMBLES                  "Preambles"
#define APDO_XML_TOKEN_CAPL                       "CAPL"
#define APDO_XML_TOKEN_CAPL_INFO                  "CAPLInfo"
#define APDO_XML_TOKEN_SUBSCRIPTION_PARAM         "SubscriptionParameters"
#define APDO_XML_TOKEN_SUBSCRIBER_INFO            "SubscriberInfo"
#define APDO_XML_TOKEN_SUBSCRIBER_NAME            "SubscriberName"
#define APDO_XML_TOKEN_CREDENTIALS                "Credentials"
#define APDO_XML_TOKEN_EAP_METHOD                 "EAPMethod"
#define APDO_XML_TOKEN_ROOT_CERT                  "RootCert"
#define APDO_XML_TOKEN_CLIENT_CERT                "ClientCert"
#define APDO_XML_TOKEN_PRIVATE_KEY                "PrivateKey"
#define APDO_XML_TOKEN_PRIVATE_KEY_PASSWORD		  "PrivateKeyPassword"
#define APDO_XML_TOKEN_EXT_TLS                    "ExternalTLS"						
#define APDO_XML_TOKEN_IDENTITY                   "Identity"
#define APDO_XML_TOKEN_OUTER_IDENTITY             "OuterIdentity"
#define APDO_XML_TOKEN_PHASE_2_METHOD             "Phase2Method"
#define APDO_XML_TOKEN_PASSWORD                   "Password"
#define APDO_XML_TOKEN_SLA                        "SLA"
#define APDO_XML_TOKEN_LEVEL                      "Level"
#define APDO_XML_TOKEN_UP_LINK_SPEED              "UpLinkSpeed"
#define APDO_XML_TOKEN_DOWN_LINK_SPEED            "DownLinkSpeed"

// Device Connection status
typedef enum _apdo_DbCmd_t
{
	APDO_AddCmd = 0,     // DB Add command
	APDO_UpdateCmd ,    // DB update command
	APDO_GetCmd,         // DB Get command
	APDO_DeleteCmd       // DB delete command
	
} apdo_DbCmd_t, *apdo_pDbCmd_t;

////////////////////
// NDS DB Interface
////////////////////
/// <summary>
/// Init the DB
/// </summary>
/// <returns>wmx_Status_t </returns>
wmx_Status_t	NdsDB_Init(void);
/// <summary>
/// Get SLA from input nspid
/// </summary>
/// <param name="NSPid">(IN) NSP id
/// <param name="pSLA">(OUT) the SLA data
/// <returns>wmx_Status_t </returns>
wmx_Status_t	NdsDB_GetSLA(IN wmx_NSPid_t NSPid, OUT wmx_pSLA_t pSLA);
/// <summary>
/// Get NSP data from nspid
/// </summary>
/// <param name="NSPid">(IN) NSP id
/// <param name="pNSP">(OUT) the NSP data
/// <returns>wmx_Status_t </returns>
wmx_Status_t	NdsDB_GetNSP(IN wmx_NSPid_t NSPid, OUT wmx_pNSPFullData_t pNSP);
/// <summary>
/// Get Get Provision NSPs Full data
/// </summary>
/// <param name="pNSPArrSize">(INOUT) NSP array size as input and size of provision data as output
/// <param name="pNSP">(OUT) array of provision NSPs
/// <returns>wmx_Status_t </returns>
wmx_Status_t	NdsDB_GetProvisionNSPsFull(UINT32 *pNSPArrSize,  wmx_pNSPFullData_t pNSP);
/// <summary>
/// Get Get Provision NSPs reduced data
/// </summary>
/// <param name="pNSPArrSize">(INOUT) NSP array size as input and size of provision data as output
/// <param name="pNspIDs">(OUT) array of provision NSP IDs
/// <returns>wmx_Status_t </returns>
wmx_Status_t	NdsDB_GetProvisionNSPs(UINT32 *pNSPArrSize,  wmx_pNSPid_t pNspIDs);
/// <summary>
/// Save data base into XML file
/// </summary>
/// <param name="pwsFileNamee">(IN) name of file to be save
/// <returns>wmx_Status_t </returns>
wmx_Status_t	NdsDB_SaveToFile(const WCHAR *pwsFileNamee);
/// <summary>
/// restore data base from XML file
/// </summary>
/// <param name="pwsFileNamee">(IN) name of file to restore from
/// <returns>wmx_Status_t </returns>
wmx_Status_t	NdsDB_RestoreFromFile(const WCHAR *pwsFileName);
/// <summary>
/// De provision NSP
/// </summary>
/// <param name="serverId">(IN) serverid to de-provision
/// <returns>wmx_Status_t </returns>
wmx_Status_t	NdsDB_DeProvisionNSP(wmx_NSPServerId_t serverId);
/// <summary>
/// Get Last connected NSP
/// </summary>
/// <param name="pLastNsp">(OUT) last connected NSP or NDS_DB_INVALID_INDEX if not connected
/// <returns>wmx_Status_t </returns>
wmx_Status_t NdsDB_GetLastConnectedNSP(wmx_pNSPid_t pLastNsp);
/// <summary>
/// Set Last connected NSP
/// </summary>
/// <param name="NSPid">(IN) last connected NSP
/// <returns>wmx_Status_t </returns>
wmx_Status_t NdsDB_SetLastConnectedNSP(wmx_NSPid_t NSPid);
/// <summary>
/// Get Last connected NSP from the temp storage
/// </summary>
/// <param name="pLastNsp">(OUT) last connected NSP or NDS_DB_INVALID_INDEX if not connected
/// <returns>wmx_Status_t </returns>
wmx_Status_t NdsDB_GetLastConnectedNSPTemp(wmx_pNSPid_t pLastNspTemp);
/// <summary>
/// Set Last connected NSP in a temp storage
/// </summary>
/// <param name="NSPid">(IN) last connected NSP
/// <returns>wmx_Status_t </returns>
wmx_Status_t NdsDB_SetLastConnectedNSPTemp(wmx_NSPid_t NSPidTemp);

// Interfaces for NAP <-> NSP conversions 
/// <summary>
/// Convert NSP to NAPs array
/// </summary>
/// <returns>wmx_Status_t </returns>
wmx_Status_t NdsDB_NSP2NAP(wmx_NSPid_t NSPid, UINT32 *pNAPArrSize, wmx_pNAP_t pNAP);
/// <summary>
/// Convert NAP to NSPs array
/// </summary>
/// <returns>wmx_Status_t </returns>
wmx_Status_t NdsDB_NAP2NSP(wmx_NAPid_t NAPid, UINT32 *pNSPArrSize,  wmx_pNSPFullData_t pNSP);

/// <summary>
/// Set/Get RoamingMode from DB
/// </summary>
/// <returns>wmx_Status_t </returns>
wmx_Status_t NdsDB_SetRoamingMode(wmx_UserRoamingMode_t newVal);
wmx_UserRoamingMode_t NdsDB_GetRoamingMode();

/// <summary>
/// Set/Get ConnectMode from DB
/// </summary>
/// <returns>wmx_Status_t </returns>
wmx_Status_t NdsDB_SetConnectMode(wmx_UserConnectMode_t newVal);
wmx_UserConnectMode_t NdsDB_GetConnectMode();

time_t NdsDB_GetConnectionTime();
void NdsDB_SetConnectionTime(time_t connectionTime);

/// <summary>
/// Set/Get Sw Rf State from DB
/// </summary>
/// <returns>wmx_Status_t </returns>
wmx_Status_t NdsDB_SetSwRfState(wmx_RfStatus_t newState);
wmx_RfStatus_t NdsDB_GetSwRfState();

/// <summary>
/// Run add/get/delete/update command using input path. This is interface function for upper layers
/// </summary>
/// <param name="psPath">(IN)  the path of command
/// <param name="psValue">(IN) pointer for value
/// <param name="cmd">(IN) command (get/update/delete/add)
/// <returns>wmx_Status_t </returns>
wmx_Status_t ndsDB_RunCmdFromPath(	char	*psPath,
									void	*psValue,
									UINT32   *pBufferSize,
									wmx_pAPDOType_t pAPDOType,
									apdo_DbCmd_t cmd);

wmx_Status_t wmx_GetAPDOinfo( wmx_APDOPath_t pAPDOPath, void *pValue, wmx_pAPDOType_t pAPDOType );
wmx_Status_t wmx_AddAPDOinfo( wmx_APDOPath_t pAPDOPath, void *pValue, wmx_APDOType_t APDOType );
wmx_Status_t wmx_UpdateAPDOinfo( wmx_APDOPath_t pAPDOPath, void *pValue, wmx_APDOType_t APDOType );
wmx_Status_t wmx_DeleteAPDOinfo( wmx_APDOPath_t pAPDOPath );
wmx_Status_t wmx_AddNapToFirstNspPatch(wmx_NAPid_t	napID,wmx_pNSP_t pOutNSP);

#endif //_NDS_AGENT_DB_