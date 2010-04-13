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
#ifndef _NDNS_AGENT_DB_INTERNAL_
#define _NDNS_AGENT_DB_INTERNAL_


#include "NDnSAgent_Internals.h"
#include "NDnSAgent_DB_if.h"
#include "wmxSDK_Nds_InternalStructs.h"
#include "wmxSDK_Apdo_Cmn.h"
#include "wmxSDK_Apdo_Utils.h"
#include "wmxSDK_Msc_2.h"
#include "TraceModule.h"
#include "XmlParser.h"

#define VERSION_FILE_NAME "Ver_info.bin"
#define VERSION_SECTION_MAX_SIZE 5 // this const is for each one of the strings constructing the version for xxx.yyy.zzz
							   // this value should be 3
// XML common string definitions 
#define L4DB_XML_TRUE_STR	"True"
#define L4DB_XML_FALSE_STR	"False"
#define L4DB_XML_ONE_STR	"1"
#define L4DB_XML_ZERO_STR	"0"
#define L4DB_XML_ON_STR		"On"
#define L4DB_XML_OFF_STR	"Off"
#define L4DB_XML_DISABLE	"Disable"
#define L4DB_XML_ENABLE		"Enable"
#define L4DB_XML_MANUAL		"Manual"
#define L4DB_XML_AUTO		 "Auto"
#define L4DB_XML_APDO_CONFIG_UNAVAILABLE "Unavailable"

// XML L4 string definitions 
#define L4DB_XML_TOKEN_INTERNAL_DATA			  "InternalData"
#define L4DB_XML_TOKEN_INTERNAL_STATES	          "InternalStates"
#define L4DB_XML_TOKEN_NDS_LAST_RF_STATE          "LastRfState"
#define L4DB_XML_TOKEN_NDS_SET_PREFERRED_NSP_ON_CONNECT          "setPreferredNspOnConnect"
#define L4DB_XML_TOKEN_NDS_LAST_NSP               "LastNsp"
#define L4DB_XML_TOKEN_NDS_THCRITERIA             "THCriteria"
#define L4DB_XML_TOKEN_NDS_RSSI_THRESHOLD         "RssiThreshold"
#define L4DB_XML_TOKEN_NDS_CINR_THRESHOLD         "CinrThreshold"
#define	L4DB_XML_TOKEN_ALLOW_AUTO_ACTIVATE		  "AllowAutoActivate"
#define	L4DB_XML_TOKEN_ALLOW_FAST_RECONNECT		  "AllowFastReconnect"
#define L4DB_XML_TOKEN_UNPROVISIONED_PROFILES	  "UnprovisionedProfiles"
#define L4DB_XML_TOKEN_UNPROVISIONED_PROFILE	  "UnprovisionedProfile"
#define L4DB_XML_TOKEN_LAST_CONNETED_NSPS		  "LastConnectedNsps"
#define L4DB_XML_TOKEN_LAST_CONNETED_NSP_ID		  "LastConnectedNspID"
#define L4DB_XML_TOKEN_LAST_CONNETED_NAP_IDS	  "LastConnectedNapIDs"
#define L4DB_XML_TOKEN_NDS_LAST_NSP               "LastNsp"
#define L4DB_XML_TOKEN_USER_CONNECTING_MODE       "UserConnectingMode"
#define L4DB_XML_TOKEN_ROAMING_MODE               "RoamingMode"
#define L4DB_XML_TOKEN_CURRENT_PREFERRED_NSP      "CurrentPreferredNSP"
#define L4DB_XML_TOKEN_NAP_ID                     "NAP_ID"
#define L4DB_XML_TOKEN_NAP_ID_DASH                "NAP-ID"
#define L4DB_XML_TOKEN_NSP_ID_DASH                "NSP-ID"
#define L4DB_XML_TOKEN_OPERATOR					  "Operator"
#define L4DB_XML_TOKEN_WMX_SUPP					  "WiMAXSupp"
#define L4DB_XML_TOKEN_NSP                        "NSP"
#define L4DB_XML_TOKEN_NAP						  "NAP"
#define L4DB_XML_TOKEN_PROFILE					  "Profile"
#define L4DB_XML_TOKEN_NETWORK_PARM               "NetworkParameters"
#define L4DB_XML_TOKEN_REALM                      "REALM"
#define L4DB_XML_TOKEN_CHANNEL_PLAN               "ChannelPlan"
#define L4DB_XML_TOKEN_PREAMBLES                  "Preambles"
#define L4DB_XML_TOKEN_H_NSP                      "H_NSP"
#define L4DB_XML_TOKEN_H_NSP_DASH                 "H-NSP"
#define L4DB_XML_TOKEN_H_NSP_ID					  "H_NSP_ID"
#define L4DB_XML_TOKEN_H_NSP_ID_DASH			  "H-NSP-ID"
#define L4DB_XML_TOKEN_V_NSP_ID					  "V_NSP_ID"
#define L4DB_XML_TOKEN_V_NSP_ID_DASH			  "V-NSP-ID"
#define L4DB_XML_TOKEN_VISITED_REALM              "VisitedRealm"
#define L4DB_XML_TOKEN_RAPL                       "RAPL"
#define L4DB_XML_TOKEN_CAPL                       "CAPL"
#define L4DB_XML_TOKEN_CAPL_INFO                  "CAPLInfo"
#define L4DB_XML_TOKEN_SUBSCRIPTION_PARAM         "SubscriptionParameters"
#define L4DB_XML_TOKEN_EAP_TYPE	                  "METHOD_TYPE"
#define L4DB_XML_TOKEN_EAP_TYPE_DASH              "METHOD-TYPE"
#define L4DB_XML_TOKEN_VENDOR_ID	              "VENDOR_ID"
#define L4DB_XML_TOKEN_VENDOR_ID_DASH             "VENDOR-ID"
#define L4DB_XML_TOKEN_VENDOR_TYPE	              "VENDOR_TYPE"
#define L4DB_XML_TOKEN_VENDOR_TYPE_DASH           "VENDOR-TYPE"
#define L4DB_XML_TOKEN_USE_PRIVACY				  "USE_PRIVACY"
#define L4DB_XML_TOKEN_USE_PRIVACY_DASH			  "USE-PRIVACY"
#define L4DB_XML_TOKEN_EAP		                  "EAP"
#define L4DB_XML_TOKEN_ROOT_CERT                  "RootCert"
#define L4DB_XML_TOKEN_CLIENT_CERT                "ClientCert"
#define L4DB_XML_TOKEN_PRIVATE_KEY                "PrivateKey"
#define L4DB_XML_TOKEN_PASSWORD                   "PASSWORD"
#define L4DB_XML_TOKEN_IS_ENCRYPTED_PASSWORD	  "Encrypted"
#define L4DB_XML_TOKEN_WIDE_SCAN_PARAMS			  "WideScanParameters"
#define L4DB_XML_TOKEN_LINK_LOSS_PARAMS			  "LinkLossParameters"
#define L4DB_XML_TOKEN_DISCOVERED_NAP_INFO		  "DiscoveredNaps"
#define L4DB_XML_TOKEN_DEVICE_CERTIFICATES		  "DeviceCertificates"
#define L4DB_XML_TOKEN_DB_VERSION				  "L4_DbVersion"
#define L4DB_XML_TOKEN_SHORT_LINK_LOSS			  "ShortLinkLoss"
#define L4DB_XML_TOKEN_LONG_LINK_LOSS			  "LongLinkLoss"
#define L4DB_XML_TOKEN_TIMER					  "Timer"
#define L4DB_XML_TOKEN_REPETITION				  "Repetition"
#define L4DB_XML_TOKEN_ENTRIES				      "Entries"
#define L4DB_XML_TOKEN_ANY						  "Any"
#define L4DB_XML_TOKEN_SELECT_POLICY			  "SelectPolicy"
#define L4DB_XML_TOKEN_ID						  "Id"
#define L4DB_XML_TOKEN_BW				          "BW"
#define L4DB_XML_TOKEN_FFT_SIZE				      "FFTSize"
#define L4DB_XML_TOKEN_DUPLEX_MODE				  "DuplexMode"
#define L4DB_XML_TOKEN_CHANNEL_INDEX			  "ChannelIndex"
#define L4DB_XML_TOKEN_NEXT_FREQ_STEP			  "NextFreqStep"
#define L4DB_XML_TOKEN_FIRST_FREQ			      "FirstFreq"
#define L4DB_XML_TOKEN_LAST_FREQ			      "LastFreq"
#define L4DB_XML_TOKEN_CONTACTS					  "Contacts"
#define L4DB_XML_TOKEN_OPERATOR_NAME			  "OperatorName"
#define L4DB_XML_TOKEN_PRIORITY					  "Priority"
#define L4DB_XML_TOKEN_TYPE						  "Type"
#define L4DB_XML_TOKEN_URIS						  "URIs"
#define L4DB_XML_TOKEN_URI						  "URI"
#define L4DB_XML_TOKEN_TRIGGER					  "Trigger"
#define L4DB_XML_TOKEN_TEXT						  "Text"
#define L4DB_XML_TOKEN_PRIMARY			          "Primary"
#define L4DB_XML_TOKEN_USER_IDENTITY			  "USER_IDENTITY"
#define L4DB_XML_TOKEN_USER_IDENTITY_DASH		  "USER-IDENTITY"
#define L4DB_XML_TOKEN_NAME						  "Name"
#define L4DB_XML_TOKEN_OTHER_SUBSCRIPTIONS        "OtherSubscriptions"
#define L4DB_XML_TOKEN_ACTIVATED		          "Activated"
#define L4DB_XML_TOKEN_PROVISIONED_PSEUDO_ID	  "PROVISIONED_PSEUDO_IDENTITY"
#define L4DB_XML_TOKEN_PROVISIONED_PSEUDO_ID_DASH "PROVISIONED-PSEUDO-IDENTITY"
#define L4DB_XML_TOKEN_ENCAPS					  "ENCAPS"
#define L4DB_XML_TOKEN_VFY_SERVER_REALM			  "VFY_SERVER_REALM"
#define L4DB_XML_TOKEN_VFY_SERVER_REALM_DASH	  "VFY-SERVER-REALM"
#define L4DB_XML_TOKEN_SERVER_REALMS			  "SERVER_REALMS"
#define L4DB_XML_TOKEN_SERVER_REALMS_DASH		  "SERVER-REALMS"
#define L4DB_XML_TOKEN_SERVER_REALM				  "SERVER_REALM"
#define L4DB_XML_TOKEN_SERVER_REALM_DASH		  "SERVER-REALM"
#define L4DB_XML_TOKEN_CERT                       "CERT"
#define L4DB_XML_TOKEN_CERT_TYPE                  "CERT_TYPE"
#define L4DB_XML_TOKEN_CERT_TYPE_DASH             "CERT-TYPE"
#define L4DB_XML_TOKEN_SER_NUM                    "SER_NUM"
#define L4DB_XML_TOKEN_SER_NUM_DASH               "SER-NUM"
#define L4DB_XML_TOKEN_ISSUER                     "ISSUER"
#define L4DB_XML_TOKEN_THUMB_PRINT                "ThumbPrint"
#define L4DB_XML_TOKEN_CHANGE_COUNT				  "ChangeCount"
#define L4DB_XML_TOKEN_DETECTED_CHANNELS		  "DetectedChannels"
#define L4DB_XML_TOKEN_DETECTED_CHANNEL_ID		  "DetectedChannelID"
#define L4DB_XML_TOKEN_PS_POLICY				  "PreferredScanPolicy"
#define L4DB_XML_TOKEN_POLLING_ATTEMPTS			  "PollingAttempts"
#define L4DB_XML_TOKEN_CH_PLAN_REF_IDS			  "ChPlanRefIds"
#define L4DB_XML_TOKEN_REF_ID					  "RefId"
#define L4DB_XML_TOKEN_LAST_DETECTED			  "LastDetected"
#define L4DB_XML_TOKEN_TTL						  "TTL"
#define L4DB_XML_TOKEN_DEV_INFO				      "DevInfo"
#define L4DB_XML_TOKEN_DEV_ID				      "DevId"
#define L4DB_XML_TOKEN_TERMINAL_DEV_ID			  "DevID"
#define L4DB_XML_TOKEN_MAN						  "Man"
#define L4DB_XML_TOKEN_MOD						  "Mod"
#define L4DB_XML_TOKEN_DEV_DETAIL				  "DevDetail"
#define L4DB_XML_TOKEN_SW_VERSION				  "SwV"
#define L4DB_XML_TOKEN_HW_VERSION				  "HwV"
#define L4DB_XML_TOKEN_FW_VERSION				  "FwV"
#define L4DB_XML_TOKEN_DEV_TYP					  "DevTyp"
#define L4DB_XML_TOKEN_OEM						  "OEM"
#define L4DB_XML_TOKEN_LRG_OBJ					  "LrgObj"
#define L4DB_XML_TOKEN_DEV_CAP					  "DevCap"
#define L4DB_XML_TOKEN_IP_CAP					  "IPCap"
#define L4DB_XML_TOKEN_IPV4						  "IPv4"
#define L4DB_XML_TOKEN_IPV6						  "IPv6"
#define L4DB_XML_TOKEN_CMIPV4					  "CMIPv4"
#define L4DB_XML_TOKEN_CMIPV6					  "CMIPv6"
#define L4DB_XML_TOKEN_UPDATE_METHODS			  "UpdateMethods"
#define L4DB_XML_TOKEN_SERVER_INIT				  "ServerInitiated"
#define L4DB_XML_TOKEN_CLIENT_INIT				  "ClientInitiated"
#define L4DB_XML_TOKEN_POLLING_SUPPORTED		  "PollingSupported"
#define L4DB_XML_TOKEN_MAC_ADDRESS				  "MACAddress"
#define L4DB_XML_TOKEN_SP_LOCK					  "SPLock"
#define L4DB_XML_TOKEN_LOCK_STATUS				  "LockStatus"
#define L4DB_XML_TOKEN_LOCK						  "Lock"
#define L4DB_XML_TOKEN_VER_NUM					  "VerNbr"
#define L4DB_XML_TOKEN_WMX_RADIO_MODULE			  "WiMAXRadioModule"
#define L4DB_XML_TOKEN_TERM_EQUIP				  "TerminalEquipment"
#define L4DB_XML_TOKEN_TO_WIMAX_REF				  "TO-WiMAX-REF"
#define L4DB_XML_TOKEN_TO_IP_REF				  "To-IP-REF"
#define L4DB_XML_TOKEN_DEV_CAP					  "DevCap"
#define L4DB_XML_TOKEN_WIMAX					  "WiMAX"
#define L4DB_XML_TOKEN_NAI_COUNTER				  "NaiCounter" //TODO - REMOVE THIS

#define L4DB_XML_TOKEN_ROOT						  "."
#define L4DB_XML_TOKEN_SEPERATOR				  "/"
//#define L4DB_CHANNEL_TAG_NAME_PREFIX			  "ch"
#define L4DB_TAG_NAME_PREFIX					  "x"
#define L4DB_WMX_REF_CONST						  "./WiMAXSupp"
#define L4DB_IP_REF_CONST						  "./IP"
#define L4DB_DEV_TYPE_CONST						  "laptop"
#define L4DB_DEV_TYPE_UPPER_CONST						  "Laptop"
#define L4DB_XML_TOKEN_TO_DM_ACCOUNT 			  "To-DMAcc"
#define L4DB_XML_TOKEN_APDO_OPERAOTR_CONFIGURATIONS "ApdoOperatorConfigurations"
#define L4DB_XML_TOKEN_PRE_PROVISIONS_BSTRAP		"PreProvBStrap"
#define L4DB_XML_TOKEN_DISABLE_OTAP					"DisableOTAP"
#define L4DB_XML_TOKEN_DISABLE_PSEUDO_NAI			"DisablePseudoNAI"
#define L4DB_XML_TOKEN_POLLING_INTERVAL				"PollingInterval"
#define L4DB_XML_TOKEN_BLOCK_UDP				    "BlockUDP"
#define L4DB_XML_TOKEN_FUMO						  "FUMO"
#define L4DB_XML_TOKEN_APDO_INTERNAL			  "APDOInternal"
#define L4DB_XML_TOKEN_FUMO_INTERNAL			  "FUMOInternal"
#define L4DB_XML_TOKEN_DEFAULT_REALM			  "DefaultRealm"
#define L4DB_XML_TOKEN_DEFAULT_BEK				  "DefaultBEK"
#define L4DB_XML_TOKEN_FW_UPDATE				  "FwUpdate"
#define L4DB_XML_TOKEN_PKG_NAME					  "PkgName"
#define L4DB_XML_TOKEN_PKG_VERSION				  "PkgVersion"
#define L4DB_XML_TOKEN_DOWNLOAD_AND_UPDATE		  "DownloadAndUpdate"
#define L4DB_XML_TOKEN_DOWNLOAD					  "Download"
#define L4DB_XML_TOKEN_PKG_URL					  "PkgURL"
#define L4DB_XML_TOKEN_PKG_PATH					  "PkgPath"
#define L4DB_XML_TOKEN_PKG_FILE_NAME			  "PkgFileName"
#define L4DB_XML_TOKEN_FUMO_NODE_PATH			  "FumoNodePath"
#define L4DB_XML_TOKEN_FUMO_OPERATION			  "FumoOperation"
#define L4DB_XML_TOKEN_STATE					  "State"
#define L4DB_XML_TOKEN_EXT						  "Ext"
#define L4DB_XML_TOKEN_SWV2						  "SwV2"
#define L4DB_XML_TOKEN_DASH						  "-"
#define L4DB_XML_TOKEN_DOT						  "."
#define L4DB_XML_TOKEN_LINE						  "_"
#define L4DB_XML_TOKEN_APDO_INTERNAL			  "APDOInternal"
#define L4DB_XML_TOKEN_NSPS_TO_DMACC			  "NSPsToDMAcc"
#define L4DB_XML_TOKEN_BOOTSTRAP_INFO			  "BootstrapInfo"
#define L4DB_XML_TOKEN_SERVER_ID				  "ServerID"
#define L4DB_XML_TOKEN_SERVER_URL				  "ServerURL"
#define L4DB_XML_TOKEN_SERVER_USER_NAME			  "ServerUserName"
#define L4DB_XML_TOKEN_CLIENT_USER_NAME			  "ClientUserName"
#define L4DB_XML_TOKEN_PORT_NUMBER				  "PortNbr"
#define L4DB_XML_TOKEN_URI_MAX_DEPTH			  "MaxDepth"
#define L4DB_XML_TOKEN_URI_MAX_TOT_LEN			  "MaxTotLen"
#define L4DB_XML_TOKEN_URI_MAX_SEG_LEN			  "MaxSegLen"

//xml nodes' children str
#define CHANNEL_INFO_CHILDREN_STR		"Id/FirstFreq/LastFreq/NextFreqStep/Preambles/BW/FFTSize/DuplexMode"
#define CHANNEL_PLAN_CHILDREN_STR		"Entries/BW/FFTSize/DuplexMode"
#define H_NSP_CHILDREN_STR				"H-NSP-ID"
#define NAP_ENTRY_CHILDREN_STR			"NAP-ID/Priority/ChPlanRefIds"		
#define CAPL_RAPL_CHILDREN_STR			"Entries/Any/SelectPolicy"
#define ROAMING_INFO_CHILDREN_STR		"V-NSP-ID/Priority"	
#define NW_PARAMS_CHILDREN_STR			"H-NSP/CAPL/RAPL/ChannelPlan/OperatorName/PollingInterval/ServerID"			
#define CONTACT_INFO_CHILDREN_STR		"Type/URI/Text/Trigger"
#define CERT_CHILDREN_STR				L4DB_XML_TOKEN_CERT_TYPE_DASH
#define EAP_CHILDREN_STR				"METHOD-TYPE/VENDOR-ID/VENDOR-TYPE/USER-IDENTITY/PROVISIONED-PSEUDO-IDENTITY/PASSWORD/REALM/USE-PRIVACY/ENCAPS/CERT/VFY-SERVER-REALM/SERVER-REALMS"
#define SUBSC_CHILDREN_STR				"EAP/Name/Activated"
#define SUBSC_PARAMS_CHILDREN_STR		"Primary/OtherSubscriptions"
#define DEV_INFO_CHILDREN_STR			"DevId/Man/Mod"
#define DEV_DETAIL_CHILDREN_STR			"DevTyp/OEM/SwV/HwV/FwV/Ext/URI/LrgObj"
#define DEV_DETAIL_URI_CHILDREN_STR		"MaxDepth/MaxTotLen/MaxSegLen"
#define DEV_DETAIL_EXT_CHILDREN_STR		"SwV2"
#define DEV_CAP_CHILDREN_STR			"IPCap/UpdateMethods"
#define IP_CAP_CHILDREN_STR				"IPv4/IPv6/CMIPv4/CMIPv6"
#define UPDATE_METHODS_CHILDREN_STR     "ServerInitiated/ClientInitiated"
#define CLIENT_INIT_CHILDREN_STR		"PollingSupported/PollingInterval"
#define TERM_EQUIP_CHILDREN_STR			"DevTyp/SwV/HwV/FwV/DevID/Man/Mod"
#define SP_LOCK_CHILDREN_STR			"LockStatus/Operator/VerNbr/Lock"
#define WMX_RADIO_MOD_CHILDREN_STR		"Man/Mod/SwV/HwV/FwV/MACAddress/SPLock"
#define WIMAX_CHILDREN_STR				"WiMAXRadioModule/TerminalEquipment/TO-WiMAX-REF/DevCap"
#define OPERATOR_CHILDREN_STR			"To-DMAcc/NetworkParameters/SubscriptionParameters/Contacts/To-IP-REF"
#define FUMO_CHILDREN_STR				"PkgName/PkgVersion/Update/Download/DownloadAndUpdate/State"
#define APDO_INTERNAL_CHILDREN_STR		"NSPsToDMAcc/BootstrapInfo"
#define ROOT_CHILDREN_STR				"WiMAXSupp/DevInfo/WiMAX/DevDetail/FUMO"

#define MAX_NAME_LEN 30
#define MAX_ARCHITECTURE_NAME_LEN 10

#define L4DB_NBR_ADV		"Neighbor advertisment"
#define L4DB_SCAN_RESULTS	"Scan results"

/*typedef struct _TerminalEquipment_t
{
	char devId[MAX_DEV_ID_SIZE];
	char devType[MAX_DEV_TYPE_SIZE];
	ProductVersions_t productVersions;

}TerminalEquipment_t, *pTerminalEquipment_t;

typedef struct _Wimax_t
{
	WmxRadioModule_t	radioModules[MAX_NUM_OF_WIMAX_RADIO_MOD];
	UINT32				wmxRadioModulesSize;
	TerminalEquipment_t terminalEquipment;
}Wimax_t, *pWimax_t;

typedef struct _DevInfo_t
{	
	char manufacturer[MAX_MAN_NAME_SIZE];
	char model[MAX_MOD_NAME_SIZE];
	char devID[MAX_DEV_ID_SIZE];
}DevInfo_t, *pDevInfo_t;

typedef struct _DevDetailExt_t
{
	// This field is a concatenation between other field. 
	//	./WiMAX/WiMAXRadioModule/0/Man
	//  -
    //	./WiMAX/WiMAXRadioModule/0/Mod
	//  -
	//  ./WiMAX/WiMAXRadioModule/0/SwV
	//  -
    //  ./DevDetail/SwV
	//  -
    //  ./WiMAX/TerminalEquipment/SwV
	//  -
    //	./WiMAX/TerminalEquipment/Man
    //  -
	//	./WiMAX/TerminalEquipment/Mod
	//	Size of this field is add of all field sizes + '-' characters
	char	SwV2[MAX_SWV2_NAME_SIZE];
}DevDetailExt_t, *pDevDetailExt_t;

typedef struct _DevDetailURI_t
{
	char MaxDepth[MAX_DEV_DETAIL_URI_FIELD_SIZE]; // Maximum tree depth supported by the device.
	char MaxTotLen[MAX_DEV_DETAIL_URI_FIELD_SIZE]; // Maximum total URI length supported by the device.
	char MaxSegLen[MAX_DEV_DETAIL_URI_FIELD_SIZE]; // Maximum URI segment length supported by the device.
}DevDetailURI_t, *pDevDetailURI_t;

typedef struct _DevDetail_t
{
	char				devType[MAX_DEV_TYPE_SIZE];
	char				fwVersion[MAX_VERSION_SIZE];
	char				swVersion[MAX_VERSION_SIZE];
	char				hwVersion[MAX_VERSION_SIZE];
	DevDetailExt_t		ext;
	DevDetailURI_t		uri;
	char				lrgObj[MAX_BOOL_VAL_SIZE];
}DevDetail_t, *pDevDetail_t;*/

typedef struct _NSPToDMAcc_t
{
	char	toDMAcc[MAX_ACCOUNT_NAME_SIZE];
	char	tagName[MAX_TAG_NAME_SIZE];
}NSPToDMAcc_t, *pNSPToDMAcc_t;

typedef struct _APDOInternalParams_t
{
	FumoInternalParams_t	fumoInternal;
	char					defaultRealm[WMX_NSP_REALM_MAX_SIZE];
	FUMOInstallStatus_t		installStatus;
	char					bek[BEK_LENGTH];
	NSPToDMAcc_t			nspsToDmAcc[WMX_NSPS_TO_DMACC_NODES_MAX_NUM];
	BootstrapInfo_t			bootstrapInfo[WMX_NSPS_MAX_NUM];
	wmx_ApdoOperatorConfigurations_t configurations[MAX_NUM_OF_CONFIGURATIONS];
}APDOInternalParams_t, *pAPDOInternalParams_t;

typedef struct _TempScanResults_t
{
	wmx_NAP_t NAPsBeneathThreshold[WMX_NAPS_MAX_NUM]; // Holds information of NAPs and their channels that didn't pass the threshold
	BOOL isValid[WMX_NAPS_MAX_NUM];
	UINT32 NAPsBeneathThresholdCount;
	UINT32 totalNAPsCount;
} TempScanResults_t, *pTempScanResults_t;

// the main structure of the L4db
typedef struct _L4db_Context
{
	ProvisionedNsp_t		nsps[WMX_NSPS_MAX_NUM];
	NdsSettings_t			generalSettings;
	ChannelPlan_t			wideScanParams;
	DeviceCertificates_t	deviceCerts;
	DiscoveredNap_t			discoveredNaps[MAX_NUM_OF_DISCOVERED_NAPS];
	int						l4dbVersion;
	PreferredScanPolicy_t	preferredScanPolicy;
	UINT32					connectionTime;
	DevInfo_t				devInfo;
	Wimax_t					wimax;
	DevDetail_t				devDetail;
	UINT32					naiCounter; //TODO - remove this
	FumoParams_t			fumoNodes[WMX_FUMO_NODES_MAX_NUM];	
	APDOInternalParams_t	apdoInternalParams;	
	TempScanResults_t		tempScanResults;
	pnm_t					platformNoiseMitigation;			// Platform Noise Mitigation parameters:
} L4db_Context, * pL4db_Context;


/// <summary>
/// Run add/get/delete/update command using input path. This is interface function for upper layers
/// </summary>
/// <param name="psPath">(IN)  the path of command
/// <param name="psValue">(IN) pointer for value
/// <param name="cmd">(IN) command (get/update/delete/add)
/// <returns>wmx_Status_t </returns>
wmx_Status_t l4db_RunCmdFromPath(char	*psPath,
								  void	*psValue,
								  int   *pBufferSize,
								  wmx_pAPDOType_t pAPDOType,
								  apdo_DbCmd_t cmd);

int l4db_CompareString(const char *str1, const char *str2);

BOOL l4db_IsHomeNsp(wmx_NSPid_t nspID);

BOOL L4db_IsNapidEmpty(wmx_NAPid_t napID);

BOOL l4db_SetNapidEmpty(wmx_NAPid_t napID);

BOOL l4db_IsNapidEqualEx(wmx_NAPid_t napID1,wmx_NAPid_t napID2, wmx_BsIdType_t napIdType);

BOOL l4db_IsNapidEqual(wmx_NAPid_t napID1,wmx_pNAPid_t napID2);

UINT8 l4db_ConvertToBoolVal(const char* val);

BOOL l4db_TestNapIdNspIdBit(wmx_BSid_t bsID);

BOOL l4db_CompareNapIdNspId(wmx_BSid_t bsID, wmx_NSPid_t nspID);

void l4db_GetBoolStr(BOOL value, char * boolStr);

wmx_Status_t l4db_SetStringValueNew(char	*pDBData, size_t DbLen, char *psSrc,int   *pSrcSize, wmx_pAPDOType_t pAPDOType, apdo_DbCmd_t cmd);

wmx_Status_t l4db_SetIntegerValueNew(int *pDBData, int *pDstSize, int *pdwInData, wmx_pAPDOType_t pAPDOType, apdo_DbCmd_t cmd);

wmx_Status_t l4db_SetDoubleValueNew(double	*pDBData, int   *pDstSize, double* pdwInData, wmx_pAPDOType_t pAPDOType, apdo_DbCmd_t cmd);

wmx_Status_t l4db_SetBoolValueNew(BOOL *pDBData, int   *pDstSize,BOOL* pdwInData, wmx_pAPDOType_t pAPDOType, apdo_DbCmd_t cmd);

wmx_Status_t l4db_SetFloatValueNew(float	*pDBData,int   *pDstSize,float* pdwInData, wmx_pAPDOType_t pAPDOType,apdo_DbCmd_t cmd);

void l4db_ConvertNapIdStrToNapIdType(wmx_NAPid_t pNapId,const char *str);

void l4db_ConvertNapIdIntToNapIdType(wmx_NAPid_t pNapId,int IntNapId);

void l4db_ConvertNapIdTypeToNapIdInt(wmx_NAPid_t pNapId, int * IntNapId);

void l4db_ConvertNapIdToStr(wmx_NAPid_t pNapId,char *str);

char* l4db_GetTokensFromPath(IN char *psPath, char** psToken, char** psTokenValue);

wmx_RfStatus_t l4db_GetRfStateFromStr(const char* psState);

char* l4db_GetRfStateStr(wmx_RfStatus_t state);

/// <summary>
/// Init a channel info with default values
/// </summary>
void l4db_InitChannelInfo(pChannelInfo_t pChannelInfo);

/// <summary>
/// Init a channel plan with default values
/// </summary>
void l4db_InitChannelPlan(pChannelPlan_t pChannelPlan);

/// <summary>
/// Init a channel ref with default values
/// </summary>
void l4db_InitChannelRef(pChPlanRefId_t pChannelRef);

/// <summary>
/// Init RAPL params with default values
/// </summary>
void l4db_InitRapl(pRapl_t pRapl);


/// <summary>
/// Init capl with default values
/// </summary>
void l4db_InitCapl(pCapl_t pCapl);

/// <summary>
/// Init NW params with default values
/// </summary>
void l4db_InitNwParams(pNwParams_t pNwParams);
/// <summary>
/// Init one Contact info with default values
/// </summary>
void l4db_InitContactInfo(pContactsInfo_t pContactInfo);

/// <summary>
/// Init the reason in the contact info with default values
/// </summary>
void l4db_InitReasonInfo(pContactsInfo_t pContactInfo);

/// <summary>
/// Init pNSP with default values
/// </summary>
void l4db_InitNsp(pProvisionedNsp_t pNsp);

/// <summary>
/// Init a discovered NAP
/// </summary>
void l4db_InitDiscoveredNap(pDiscoveredNap_t pNap);

/// <summary>
/// Init the general Nds settings
/// </summary>
void l4db_InitGeneralSettings(pNdsSettings_t pSettings);
/// <summary>
/// Init the subscription parameters
/// </summary>
void l4db_InitSubscriptionParams(pSubscriptionParams_t pSubscriptionParams);
/// <summary>
/// Init a primary subscription info with default values
/// </summary>
void l4db_InitOtherSubscription(pOtherSubsInfo_t pSubscriptionInfo);
/// <summary>
/// Init a primary subscription info with default values
/// </summary>
void l4db_InitPrimarySubscription(pSubscriberInfo_t pSubscriptionInfo);

/// <summary>
/// Init an srv realm with default values
/// </summary>
void l4db_InitSrvRealm(pSrvRealm_t pSrvRealm);
/// <summary>
/// Init a cert info with default values
/// </summary>
void l4db_InitCertInfo(pCert_t	pCert);
/// <summary>
/// Init an EAP info with default values
/// </summary>
void l4db_InitEapInfo(pEAP_t pEap);

/// <summary>
/// Init a roaming info with default values
/// </summary>
void l4db_InitRoamingInfo(pRoamingPartnerInfo_t pRoamingInfo);

/// <summary>
/// Init a NAP with default values
/// </summary>
void l4db_InitNap(pL4db_Nap_t pNap);
/// <summary>
/// Init HNSP with default values
/// </summary>
void l4db_InitHnsp(pHomeNsp_t pHnsp);
/// <summary>
/// Init the device certificates
/// </summary>
void l4db_InitDeviceCerts(pDeviceCertificates_t pDeviceCerts);
/// <summary>
/// Init the dev detail struct
/// </summary>
void l4db_InitDevDetail(pDevDetail_t pDevDetail);

/// <summary>
/// Init the dev info struct
/// </summary>
void l4db_InitDevInfo(pDevInfo_t pDevInfo);

/// <summary>
/// gets a pointer to the wimax_t struct kept in the db
/// </summary>
pWimax_t l4db_GetWimax();

/// <summary>
/// gets a pointer to the APDOInternalParams_t struct kept in the db
/// </summary>
pAPDOInternalParams_t l4db_GetAPDOInternalParams();

/// <summary>
/// Init the wimax struct
/// </summary>
void l4db_InitWimax(pWimax_t pWimax);

/// <summary>
/// Init the FUMO section
/// </summary>
void l4db_InitFumoNode(pFumoParams_t pFumoParams);

/// <summary>
/// Init the FUMO Internal node
/// </summary>
void l4db_InitFumoInternalNode(pFumoInternalParams_t pFumoInternalParams);

/// <summary>
/// Init the APDO internal parameters section
/// </summary>
void l4db_InitAPDOInternalParametersNode(pAPDOInternalParams_t pAPDOInternalParams);

/// <summary>
/// gets a pointer to a provisioned NSP which has the specified NSP ID. 
/// NOTE: this method doesn't copy the Provisioned NSP found 
/// </summary>
/// <param name="nspID">(IN) the requested NSP ID </param>
/// <param name="pNsps">(IN) an array of provisioned NSPs </param>
/// <returns>pointer to ProvisionedNsp_t which we found or NULL </returns>
pProvisionedNsp_t l4db_GetProvisionedNspById(wmx_NSPid_t nspID);

wmx_Status_t l4db_RestoreInternalStatesFromFile(pXmlElement pXml, pNdsSettings_t pSettings);

wmx_Status_t l4db_RestoreOperatorsFromFile(pXmlElement pXml);

wmx_Status_t l4db_RestoreDevInfoFromFile(pXmlElement pXml);

wmx_Status_t l4db_RestoreWmxFromFile(pXmlElement pXml);

wmx_Status_t l4db_RestoreDevDetailUriFromFile(pXmlElement pXml, pDevDetailURI_t pDevDetailURI);

wmx_Status_t l4db_RestoreDevDetailFromFile(pXmlElement pXml);

wmx_Status_t l4db_RestoreWmxSuppFromFile(pXmlElement pXml);

wmx_Status_t l4db_RestoreWideScanParamsFromFile(pXmlElement pXml, pChannelPlan_t pChannelPlan);

wmx_Status_t l4db_RestoreLinkLossParamsFromFile(pXmlElement pXml,
												pLinkLossParameters_t pShortLinkLossParams,
												pLinkLossParameters_t pLongLinkLossParams);

wmx_Status_t l4db_RestoreDiscoveredNapInfoFromFile(pXmlElement pXml, pDiscoveredNap_t pNapsInfo);

wmx_Status_t l4db_RestoreProfilesFromFile(pXmlElement pXml, pProfile_t pProfilesInfo, UINT32 *pNumOfProfiles);

wmx_Status_t l4db_RestoreDbVersionFromFile(pXmlElement pXml);

wmx_Status_t l4db_RestoreDeviceCertificatesFromFile(pXmlElement pXml, pDeviceCertificates_t pDeviceCerts);

wmx_Status_t l4db_RestoreFumoFromFile(pXmlElement pXml);

wmx_Status_t l4db_RestoreAPDOIntenalParamsFromFile(pXmlElement pXml, pAPDOInternalParams_t pAPDOInternalParams);

wmx_Status_t l4db_RestoreFumoIntenalFromFile(pXmlElement pXml, pFumoInternalParams_t pFumoInternalParams);

wmx_Status_t l4db_RestoreNSPsToDMAccFromFile(pXmlElement pXml, pNSPToDMAcc_t pNSPsToDMAcc);

wmx_Status_t l4db_RestoreBootstrapInfoFromFile(pXmlElement pXml, pBootstrapInfo_t pBootstrapInfo);
wmx_Status_t l4db_RestoreApdoOperatorConfigurationsFromFile(pXmlElement pXml, wmx_pApdoOperatorConfigurations_t pApdoOperatorConfigurations);
wmx_Status_t l4db_RestoreChannelPlanFromFile(pXmlElement pXml, pChannelPlan_t pChannelPlan);

pProvisionedNsp_t l4db_GetEmptyNsp();

pProvisionedNsp_t l4db_GetProvisionedNspByTagName(char * tagName);

pDevInfo_t l4db_GetDevInfo();

pTerminalEquipment_t l4db_GetTeminalEquipmentStruct();

pWmxRadioModule_t l4db_GetWmxRadioModuleStruct(UINT32 index);

pDevDetailExt_t l4db_GetDevDetailEx();

pDevDetail_t l4db_GetDevDetail();

wmx_Status_t l4db_DeAllocNsp(wmx_NSPid_t nspID);

pChannelInfo_t	l4db_GetChannelInfo(pChannelPlan_t pChannelPlan, char * tagName);

pChPlanRefId_t	l4db_GetChannelRef(pChPlanRefId_t pChannelRef, char * tagName);

pL4db_Nap_t l4db_GetCaplNapInfo(pL4db_Nap_t pNaps, char * tagName);

pHomeNsp_t l4db_GetHnsp(pHomeNsp_t pHnsps, char * tagName);

pContactsInfo_t l4db_GetContactInfo(pContactsInfo_t pContacts, char * tagName);

pSrvRealm_t l4db_GetSrvRealm(pSrvRealm_t psrvRealms, char * tagName);

pEAP_t l4db_GetEap(pEAP_t pEaps, char * tagName);

pOtherSubsInfo_t l4db_GetOtherSubsc(pOtherSubsInfo_t pSubscribers, char * tagName);

pCert_t l4db_GetCert(pCert_t pCerts, char * tagName);

pRoamingPartnerInfo_t l4db_GetRoamingInfo(pRoamingPartnerInfo_t pRoamingInfos, char * tagName);

pWmxRadioModule_t l4db_GetWmxRadioModule(pWmxRadioModule_t pWmxRadioModules, UINT32 size,char * tagName);

pNSPToDMAcc_t l4db_GetNSPsToDMAccStruct(pAPDOInternalParams_t pApdoInternal, char* tagName);

pBootstrapInfo_t l4db_GetBootstrapInfoStruct(pAPDOInternalParams_t pApdoInternal, char* tagName);
wmx_pApdoOperatorConfigurations_t l4db_GetApdoOperatorConfigurationsStruct (pAPDOInternalParams_t pApdoInternal, char* tagName);
pFumoParams_t l4db_GetEmptyFumoNode();

pFumoParams_t l4db_GetFumoParamsNodeByTagName(char * tagName);

pChannelInfo_t l4db_AllocChannelInfo(pChannelPlan_t pChannelPlan, char *  tagName);

pChPlanRefId_t l4db_AllocChannelRef(pChPlanRefId_t pChannelRefs, char *  tagName);

pHomeNsp_t l4db_AllocHnsp(pHomeNsp_t pHnsps, char * tagName);

pL4db_Nap_t l4db_AllocCaplNap(pL4db_Nap_t pNaps, char * tagName);

pNSPToDMAcc_t l4db_AllocNSPToDMAcc(pNSPToDMAcc_t pNSPsToDMAcc, char* tagName);

pBootstrapInfo_t l4db_AllocBootstrapInfo(pBootstrapInfo_t pBootstrapInfo, char* tagName);
wmx_pApdoOperatorConfigurations_t l4db_AllocApdoOperatorConfigurations(wmx_pApdoOperatorConfigurations_t wmx_pApdoOperatorConfigurations, char* tagName);
pContactsInfo_t l4db_AllocContactInfo(pContactsInfo_t pContacts, char * tagName);

pSrvRealm_t l4db_AllocSrvRealm(pSrvRealm_t pSrvRealms, char * tagName);

pCert_t l4db_AllocCert(pCert_t pCerts, char * tagName);

pEAP_t l4db_AllocEap(pEAP_t pEaps, char * tagName);

pOtherSubsInfo_t l4db_AllocOtherSubsc(pOtherSubsInfo_t pSubscribers, char * tagName);

pProvisionedNsp_t l4db_AllocNsp(char * tagName);

pRoamingPartnerInfo_t l4db_AllocRoamingInfo(pRoamingPartnerInfo_t pRoamingInfos, char * tagName);

pFumoParams_t l4db_AllocFumoNode(char * tagName);

/// <summary>
/// Add an operator node to the XML structure
/// </summary>
/// <param name="parentXmlData">(IN) the node's parent XML node</param>
/// <param name="pNsps">(IN) an array of NSPs data structure</param>
void l4db_AddOperatorToXml(pXmlElement parentXmlData, pProvisionedNsp_t pNsps);


/// <summary>
/// Add an ApdoOperatorConfiguration node to the XML structure
/// </summary>
/// <param name="parentXmlData">(IN) the node's parent XML node</param>
/// <param name="configurationNode">(IN) an array of wmx_pApdoOperatorConfigurations_t data structure</param>
void l4db_AddApdoOperatorConfigurationToXml(pXmlElement parentXmlData, wmx_ApdoOperatorConfigurations_t configurationNode[MAX_NUM_OF_CONFIGURATIONS]);

/// <summary>
/// Add the internal states node to the XML structure
/// </summary>
/// <param name="parentXmlData">(IN) the node's parent XML node</param>
/// <param name="settings">(IN) the internal states data structure </param>
void l4db_AddInternalStatesToXml(pXmlElement parentXmlData, pNdsSettings_t pSettings);

/// <summary>
/// Add the device certificates node to the XML structure
/// </summary>
/// <param name="parentXmlData">(IN) the node's parent XML node</param>
/// <param name="deviceCertificates">(IN) the device certificate data structure </param>
void l4db_AddDeviceCertificatesToXml(pXmlElement parentXmlData, DeviceCertificates_t deviceCertificates);

/// <summary>
/// Add the link loss parameters node to the XML structure
/// </summary>
/// <param name="parentXmlData">(IN) the node's parent XML node</param>
/// <param name="shortLinkLossParams">(IN) the short link loss data structure </param>
/// <param name="longLinkLossParams">(IN) the long link loss data structure </param>
void l4db_AddLinkLossParamsToXml(pXmlElement parentXmlData, 
								 LinkLossParameters_t shortLinkLossParams,
								 LinkLossParameters_t longLinkLossParams);

/// <summary>
/// Add a wide scan parameters node to the XML structure
/// </summary>
/// <param name="parentXmlData">(IN) the node's parent XML node</param>
/// <param name="wideScanParams">(IN) the channel plan data structure </param>
void l4db_AddWideScanParamsToXml(pXmlElement parentXmlData, pChannelPlan_t pWideScanParams);

/// <summary>
/// Add a db version node to the XML structure
/// </summary>
/// <param name="parentXmlData">(IN) the node's parent XML node</param>
/// <param name="l4dbversion">(IN) the db version</param>
void l4db_AddDbVersionToXml(pXmlElement parentXmlData, int l4dbversion);

/// <summary>
/// Add a nai counter node to the XML structure
/// </summary>
/// <param name="parentXmlData">(IN) the node's parent XML node</param>
/// <param name="naiCounter">(IN) the db version</param>
void l4db_AddNaiCounterToXml(pXmlElement parentXmlData, UINT32 naiCounter);

/// <summary>
/// Add the dev info node to the XML structure
/// </summary>
/// <param name="parentXmlData">(IN) the node's parent XML node</param>
/// <param name="pDevInfo">(IN) the dev info data structure</param>
void l4db_AddDevInfoToXml(pXmlElement parentXmlData, pDevInfo_t pDevInfo);

/// <summary>
/// Add the dev detail uri node to the XML structure
/// </summary>
/// <param name="parentXmlData">(IN) the node's parent XML node</param>
/// <param name="pDevDetailUri">(IN) the dev detail uri data structure</param>
void l4db_AddDevDetailUriToXml(pXmlElement parentXmlData, pDevDetailURI_t pDevDetailUri);

/// <summary>
/// Add the dev detail node to the XML structure
/// </summary>
/// <param name="parentXmlData">(IN) the node's parent XML node</param>
/// <param name="pDevDetail">(IN) the dev detail data structure</param>
void l4db_AddDevDetailToXml(pXmlElement parentXmlData, pDevDetail_t pDevDetail);

/// <summary>
/// Add the wimax node to the XML structure
/// </summary>
/// <param name="parentXmlData">(IN) the node's parent XML node</param>
/// <param name="pDevDetail">(IN) the wimax data structure</param>
void l4db_AddWmxToXml(pXmlElement parentXmlData, pWimax_t pWimax);

/// <summary>
/// Add the wimax supp node to the XML structure
/// </summary>
/// <param name="parentXmlData">(IN) the node's parent XML node</param>
/// <param name="pNsps">(IN) a pointer to the array of NSPs</param>
void l4db_AddWmxSuppToXml(pXmlElement parentXmlData, pProvisionedNsp_t pNsps);
/// <summary>
/// Add a preferred scan policy node to the XML structure
/// </summary>
/// <param name="parentXmlData">(IN) the node's parent XML node</param>
/// <param name="policy">(IN) the preferred scan policy</param>
void l4db_AddPsPolicyToXml(pXmlElement parentXmlData, PreferredScanPolicy_t policy);

/// <summary>
/// Add the other nap info node to the XML structure
/// </summary>
/// <param name="parentXmlData">(IN) the node's parent XML node</param>
/// <param name="pNaps">(IN) an array of discovered naps data structure</param>
void l4db_AddOtherNapInfoToXml(pXmlElement parentXmlData, pDiscoveredNap_t pNaps);

/// <summary>
/// Add channel plan node to the XML structure
/// </summary>
/// <param name="parentXmlData">(IN) the node's parent XML node</param>
/// <param name="pChannelPlan">(IN) a pChannelPlan_t struct to add</param>
void l4db_AddChannelPlanToXml(pXmlElement parentXmlData, pChannelPlan_t pChannelPlan);

/// <summary>
/// Add a fumo node to the XML structure
/// </summary>
/// <param name="parentXmlData">(IN) the node's parent XML node</param>
/// <param name="pNsps">(IN) an array of Fumo nodes data structure</param>
void l4db_AddFumoToXml(pXmlElement parentXmlData, pFumoParams_t pFumoNodes);

/// <summary>
/// Add an internal parameters node to the XML structure
/// </summary>
/// <param name="parentXmlData">(IN) the node's parent XML node</param>
/// <param name="internalParamsNode">(IN) Internal parameters node data structure</param>
void l4db_AddInternalAPDOParamsToXml(pXmlElement parentXmlData, APDOInternalParams_t apdoInternalParamsNode);

/// <summary>
/// Add a fumo internal node to the XML structure
/// </summary>
/// <param name="parentXmlData">(IN) the node's parent XML node</param>
/// <param name="fumoNode">(IN) Fumo internal node data structure</param>
void l4db_AddFumoInternalToXml(pXmlElement parentXmlData, FumoInternalParams_t fumoNode);


/// Copy a channle plan with ordering its array elements
/// </summary>
/// <param name="pDest">(OUT) the destionation channel plan </<param>
/// <param name="src">(IN) the source channel plan </<param>
void l4db_CopyChannelPlan(pChannelPlan_t pDest, pChannelPlan_t pSrc);

/// <summary>
/// Copy a channle plan with ordering its array elements
/// </summary>
/// <param name="pDest">(OUT) the destionation channel plan </<param>
/// <param name="src">(IN) the source channel plan </<param>
void l4db_CopyChannelPlanWithInit(pChannelPlan_t pDest, pChannelPlan_t pSrc);

/// <summary>
/// Copy a channels ref array 
/// </summary>
/// <param name="pDest">(OUT) the destionation channel ref </<param>
/// <param name="src">(IN) the source channel ref </<param>
void l4db_CopyChannelsRefs(pL4db_Nap_t pDest, pL4db_Nap_t pSrc);

/// Merge the Src channel plan to the dest channel plan
void l4db_MergeChannelPlans(pChannelPlan_t pDest, pChannelPlan_t pSrc, BOOL isComparePreambles);

/// <summary>
/// Copy an NSP with ordering its array elements
/// </summary>
/// <param name="pDest">(OUT) the destionation  </<param>
/// <param name="src">(IN) the source </<param>
void l4db_CopyProvisionedNsp(pProvisionedNsp_t pDest, pProvisionedNsp_t pSrc);

/// Copy a discovered nap
/// </summary>
/// <param name="pDest">(OUT) the destionation  </<param>
/// <param name="src">(IN) the source </<param>
void l4db_CopyDiscoveredNap(pL4db_Nap_t dst, pDiscoveredNap_t src);

/// <summary>
/// Copy a provisioned nap
/// </summary>
/// <param name="pDest">(OUT) the destionation  </<param>
/// <param name="src">(IN) the source </<param>
void l4db_CopyProvisionedNap(pL4db_Nap_t dst, pL4db_Nap_t src);
/// <summary>
/// creates a channel's dummy tag name
/// </summary>
/// <param name="tagName">(OUT) the tag name to be created  </<param>
/// <param name="channelIndex">(IN) the index in the channel array</<param>
void l4db_CreateChannelTagName(char * tagName, int channelIndex);

/// <summary>
/// checks if it is legal to add the given NSP ID to the DB. If irt exists in another NSP
/// or in the same NSP with a different tag name, it is illegal
/// </summary>
/// <param name="nspID">(IN) the requested NSP ID </param>
/// <param name="nspIdTagName">(IN) the nsp ID's tag name </param>
/// <param name="nspTagName">(IN) the nsp's tag name </param>
/// <returns>TRUE is legal and FALSE otherwise </returns>
BOOL l4db_IsLegalToAddNspId(wmx_NSPid_t nspID, char * nspIdTagName, char * nspTagName);

/// <summary>
/// checks if it is legal to add the given NAP ID to the DB. If it already exists in this NSP
/// under a different tag name, it is illegal
/// </summary>
/// <param name="napID">(IN) the requested NAP ID </param>
/// <param name="napTagName">(IN) the nap's tag name </param>
/// <param name="nspTagName">(IN) the nsp's tag name </param>
/// <returns>TRUE is legal and FALSE otherwise </returns>
BOOL l4db_IsLegalToAddNapId(wmx_NAPid_t napID, char * napTagName, char * nspTagName);

/// <summary>
/// gets a pointer to the NSP nodes in the db
/// </summary>
pProvisionedNsp_t l4db_GetOperatorNode();

/// <summary>
/// NAP RSSI and CINR comparison function for quicksort
/// </summary>
int l4db_CompareNapRSSIandCINR(const void * elem1, const void * elem2);

/// <summary>
/// NAP priority comparison function for quicksort
/// </summary>
int l4db_CompareNapPriority(const void * elem1, const void * elem2);

/// <summary>
/// Channel comparison function
/// </summary>
BOOL l4db_IsChannelsEqual(pChannelInfo_t pCh1, pChannelInfo_t pCh2, BOOL isComparePreambles);

/// <summary>
/// gets a pointer to the NSP nodes in the db
/// </summary>
pProvisionedNsp_t l4db_GetOperatorNode();
/// <summary>
/// gets a pointer to the FUMO node in the db
/// </summary>
pFumoParams_t l4db_GetFumoNode();

//populate the Monitor values in case that needed
//void PopulateMonitorVal();

// This function builds a version string with the concatination of other files in the db as following:
//	./WiMAX/WiMAXRadioModule/0/Man
//  -
//	./WiMAX/WiMAXRadioModule/0/Mod
//  -
//  ./WiMAX/WiMAXRadioModule/0/SwV
//  -
//  ./DevDetail/SwV
//  -
//  ./WiMAX/TerminalEquipment/SwV
//  -
//	./WiMAX/TerminalEquipment/Man
//  -
//	./WiMAX/TerminalEquipment/Mod
void l4db_BuildVersionString(char pVersion[MAX_SWV2_NAME_SIZE]);

/// <summary>
/// This function takes the nsp name and makes sure there is an enrty for that name in the NSPsToDMAcc list.
/// </summary>
wmx_Status_t l4db_AddNSPToNSPsToDMAccStruct(char tagName[MAX_TAG_NAME_SIZE]);

/// <summary>
/// This function takes the nsp name and makes sure there is an enrty for that name in the NSPsToDMAcc list.
/// </summary>
wmx_Status_t l4db_AddNSPToApdoOperaotrConfigurationsStruct(char tagName[MAX_TAG_NAME_SIZE]);

/// <summary>
// This function recieves a string and replaces special characters with spaces
/// </summary>
void l4db_RemoveSpecialCharacters(char* string);


/// <summary>
/// Run add/get/delete/update command using input path. This is interface function for upper layers
/// </summary>
/// <param name="psPath">(IN)  the path of command</param>
/// <param name="psValue">(IN) pointer for value</param>
/// <param name="cmd">(IN) command (get/update/delete/add)</param>
/// <returns>wmx_Status_t </returns>
wmx_Status_t l4db_UpdateNSPsToDMAccFromPath(char			*psPath,
											void			*pInValue,
											int			*pBufferSize,
											wmx_pAPDOType_t pAPDOType,
											apdo_DbCmd_t	cmd);
wmx_Status_t L4db_GetApdoOperatorsConfigurations( wmx_pApdoOperatorConfigurations_t pConfigurations );

/// <summary>
/// Run add/get/delete/update command using input path. This is interface function for upper layers
/// </summary>
/// <param name="psPath">(IN)  the path of command</param>
/// <param name="psValue">(IN) pointer for value</param>
/// <param name="cmd">(IN) command (get/update/delete/add)</param>
/// <returns>wmx_Status_t </returns>
wmx_Status_t l4db_UpdateBootstrapInfoFromPath(char			*psPath,
											  void			*pInValue,
											  int			*pBufferSize,
											  wmx_pAPDOType_t pAPDOType,
											  apdo_DbCmd_t	cmd);

/// <summary>
/// Sort the channels according to link quality in decreasing order in a NAP scan result descriptor
/// </summary>
/// <param name="pNap">(IN/OUT) pointer to NAP descriptor</param>
/// <param name="startPos">(IN) index of channel array to start the sorting from</param>
/// <param name="endPos">(IN) last index of channel array to sort</param>
/// <returns>wmx_Status_t </returns>
wmx_Status_t L4db_SortNapChannels(wmx_pNAP_t pNap, UINT32 startPos, UINT32 endPos);
wmx_Status_t L4db_SortDiscoveredNapChannels(DiscoveredNap_t pNap[MAX_NUM_OF_DISCOVERED_NAPS], UINT32 startPos, UINT32 endPos);



// Internally used to update the DB upon channel change that might changed.
wmx_Status_t L4db_PNMUpdateIfChannelChanged(wmx_pSystemStateUpdate systemStateUpdate, BOOL* channelChanged);
wmx_Status_t L4db_SetPNM(pnm_t NPM_DB, BOOL * pIsDifferantAndUpdated);

#endif //_NDNS_AGENT_DB_INTERNAL_