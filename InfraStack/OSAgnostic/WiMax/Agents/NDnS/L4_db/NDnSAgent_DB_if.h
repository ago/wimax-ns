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
#ifndef _NDNS_AGENT_DB_IF_
#define _NDNS_AGENT_DB_IF_

#include "wmxSDK_Apdo_Cmn.h"
#include "wmxSDK_Apdo_Utils.h"
#include "wmxSDK_Msc_2.h"
#include "L3L4Structs.h"
#include "wmxSDK_Nds_InternalStructs.h"

// For file open/close/write
#include <stdio.h>
#include <wchar.h>
//#include <share.h>		// @@@ : JSS : Remove (windows specific)

// General defines
#define WiMAX_DEF_DB		"WiMAX_Def.xml" 
#define WiMAX_DEF_ENC_DB		"WiMAX_Def.bin" 

#define WiMAX_DB		"WiMAX_DB.xml" 
#define WiMAX_ENC_DB		"WiMAX_DB.bin" 

#define NDNS_DSIM_CONFIG_FILE "WiMAX_DB_dSim.xml"
#define NDNS_DSIM_ENC_CONFIG_FILE "WiMAX_DB_dSim.bin"

#define UNRECOGNIZED_OPERATOR "Unrecognized Operator"
#define	UNRECOGNIZED_OPERATOR_LEN OSAL_strnlen(UNRECOGNIZED_OPERATOR, WMX_NSP_NAME_MAX_SIZE)

#define ARRAY_SIZE(A)   (sizeof(A)/sizeof(A[0])) 
#define L4DB_INVALID_INDEX			(-1)
#define DEFAULT_TIME 0

#define MAX_NUM_OF_RECENT_NSPS			6
#define MAX_ROAMING_PARTNERS			70		//TODO - change this when there is a real definition
#define MAX_REALM_SIZE					100		//TODO - change this when there is a real definition
#define MAX_NUM_OF_EAP_METHODS			4		//TODO - change this when there is a real definition
#define MAX_REASON_TEXT_SIZE			100		//TODO - change this when there is a real definition
#define MAX_NUM_OF_CERTS				5		//TODO - change this when there is a real definition
#define	MAX_FILE_NAME_SIZE				50		//TODO - change this when there is a real definition
#define	MAX_NUM_OF_DISCOVERED_NSPS		33		//TODO - change this when there is a real definition
#define MAX_TAG_NAME_SIZE				96		//TODO - change this when there is a real definition
#define MAX_NUM_OF_SRV_REALMS			10		//TODO - change this when there is a real definition
#define MAX_NUM_OF_DISCOVERED_NAPS		50		//TODO - change this when there is a real definition
#define BUFF_SIZE						256
#define MAX_INT_TAG_NAME_SIZE			4
#define MAX_NUM_OF_CONTACTS				5
#define MAX_MAN_NAME_SIZE				WMX_MANUFACTURER_NAME_MAX_LENGTH
#define MAX_MOD_NAME_SIZE				WMX_MODEL_TYPE_NAME_MAX_LENGTH
#define MAX_VERSION_SIZE				WMX_DEVICE_VERSION_MAX_LENGTH
#define MAX_DEV_ID_SIZE					64
#define MAX_DEV_TYPE_SIZE				64
#define MAX_REF_ID_NAME_SIZE            64
#define MAX_NUM_OF_WIMAX_RADIO_MOD		5
#define MAX_LOCK_SIZE					176 // a calc considering the nsp name / realm + macaddress len + command + sha256
#define WMX_FUMO_NODES_MAX_NUM			5
#define WMX_NSPS_TO_DMACC_NODES_MAX_NUM	WMX_NSPS_MAX_NUM*5
#define MAX_CHANNEL_INFO_ID_SIZE		64
#define MAX_CERT_TYPE_SIZE				64
#define MAX_SER_NUM_SIZE				32
#define MAX_ISSUER_SIZE					32
#define MAX_SERVER_ID_SIZE				32
#define MAX_USER_NAME_SIZE				32
#define MAX_PORT_NUMBER_SIZE			10
#define MAX_SERVER_URL_SIZE					256
#define MAX_DEV_DETAIL_URI_FIELD_SIZE	5
#define MAX_BOOL_VAL_SIZE				6
#define L4DB_MAX_TTL					10	// max time to live for detected NAP
#define MAX_NUM_OF_CONFIGURATIONS       10

#define MAX_TAG_NAME_DEFAULT			"DEFAULT"		//TODO: - change this when there is a real definition


//	Platform Noise Mitigation defines
#define PNM_STATUS_NOT_CONNECTED 0
#define PNM_STATUS_CONNECTED 1


//	Size of this field is add of all field sizes + '-' characters
#define MAX_SWV2_NAME_SIZE MAX_MAN_NAME_SIZE*3 + MAX_MOD_NAME_SIZE*3 + MAX_VERSION_SIZE*3 + 6				

#define DEFAULT_RADIO_MODULE_NODE "0"
#define DEFAULT_RADIO_MODULE_MAN "Intel"
#define DEFAULT_DEV_TYPE "Laptop"

#define DEFAULT_DEV_INFO_MAN "IntelBasedLaptop"
#define DEFAULT_DEV_INFO_MOD "IntelGenericMod"

#define DEFAULT_TRUE_LOWER "true"

#define UPDATER_FILE_NAME "WiMaxUpdateManager.exe"
#define C_L4DB_EMPTY_STRING ""

typedef enum _Any_t
{
	Reserved = 0x1,
	OnlyList,
	ListFirst,
	Any
}Any_t, * pAny_t;

typedef enum _SelectPolicy_t
{
	spReserved = 0x0,
	spStrict,
	spPartiallyFlexible,
	spFullyFlexible
}SelectPolicy_t, * pSelectPolicy_t;

/// <summary>
/// An enum which specifies all the commit statuses available.
/// </summary>
typedef enum _CommitStatus_t
{
	CommitStart = 0x0,
	CommitEnd
}CommitStatus_t, * pCommitStatus_t;
/// <summary>
/// The signature defintion of a L4db_pCommitCB_t callback function. 
/// Once registered, this callback function will be called when a commit process is started \ ends.
/// </summary>
/// <param name="status">(IN) the status of the commit process.</param>
typedef void ( *L4db_pCommitCB_t)(CommitStatus_t status);
/// <summary>
/// An enum which specifies the possible certificates' type
/// </summary>
//typedef enum _CertType_t
//{
//	Device = 0x1,
//	CA
//}CertType_t, *pCertType_t;

/// <summary>
/// An enum which specifies all possible preffered policies
/// </summary>
typedef enum _PreferredScanPolicy_t
{
	FirstRecent = 0x0,  
	FirstHome,
	OtherRecent,
	OtherHome
}PreferredScanPolicy_t, * pPreferredScanPolicy_t;

/// <summary>
/// An enum which describes the different NSP categories
/// </summary>
typedef enum _NspCategory_t
{
	Home = 0x1, //provisioned and activated
	NotHome, //provisioned but not activated
	NotProvisioned //not provisioned
}NspCategory_t, * pNspCategory_t;

/// <summary>
/// Type definitions for variables that are fields of the wmx_NAP_t struct. 
/// </summary>
typedef UINT32	wmx_Priority_t, *wmx_pPriority_t;

/// <summary>
/// A struct which holds all a single channel info
/// </summary>
typedef struct _ChannelInfo_t
{
	char				id[MAX_REF_ID_NAME_SIZE];
	wmx_Frequency_t		firstFreq;
	wmx_Frequency_t		lastFreq;
	wmx_NextFreqStep_t	nextFreq;			// the next freq in KHZ
	wmx_BW_t			bw;					// 3.5Mhz, 5.0MHz, 7.5Mhz, 8.75Mhz, 10Mhz, 14Mhz and 20Mhz
	wmx_FFT_t			fft;
	UINT32				ttl;	
	wmx_DuplexMode_t	duplexMode;	
	wmx_Preambles_t		preambleBitmap;		// A 114 bit map specifying the supported preambles
	BOOL				lastFoundInNbrAdv; // TRUE if the channel was returned in the last Nbrhood; Turned to false in aging
	char				tagName[MAX_TAG_NAME_SIZE];
}ChannelInfo_t, *pChannelInfo_t;

/// <summary>
/// A struct which holds a full channel plan
/// </summary>
typedef struct _ChannelPlan_t
{	
	UINT32					channelsSize;
	wmx_BW_t				bw;					// 3.5Mhz, 5.0MHz, 7.5Mhz, 8.75Mhz, 10Mhz, 14Mhz and 20Mhz
	wmx_FFT_t				fft;
	wmx_DuplexMode_t		duplexMode;			//0-255
	ChannelInfo_t			channels[WMX_CHANNELS_MAX_NUM];
	wmx_LinkQuality_t		linkQuality[WMX_CHANNELS_MAX_NUM];
	//UINT8					DummyForCompilerHappy;
}ChannelPlan_t, *pChannelPlan_t;

/// <summary>
/// A struct which holds a reference to a channel id
/// </summary>
typedef struct _ChPlanRefId_t
{
	char	tagName[MAX_TAG_NAME_SIZE];
	char	id[MAX_REF_ID_NAME_SIZE];
}ChPlanRefId_t, * pChPlanRefId_t;

typedef struct _L4db_Nap_t 
{
	wmx_NAPid_t				napID;
	UINT8					DummyCompilerHappy;
	wmx_Priority_t			priority;
	ChPlanRefId_t			channelPlanRefIds[WMX_CHANNELS_MAX_NUM];
	UINT32					channelRefsSize;
	ChannelPlan_t			discoveredChannelPlan;
	UINT32					changeCount;
	char					tagName[MAX_TAG_NAME_SIZE];
}L4db_Nap_t, * pL4db_Nap_t ;
/// <summary>
/// A struct which describes a CAPL
/// </summary>
typedef struct _Capl_t 
{
	L4db_Nap_t		naps[WMX_NAPS_MAX_NUM];
	UINT32			napsSize;
	Any_t			any;//specifies if NAPs not from the CAPL can be used too
	SelectPolicy_t  selectPolicy;
}Capl_t, *pCapl_t;

/// <summary>
/// A struct which holds the information for a specific roaming partner
/// </summary>
typedef struct _RoamingPartnerInfo_t
{
	wmx_NSPid_t			vNspID;
	wmx_Priority_t		priority;
	char				vRealm16g[MAX_REALM_SIZE];
	char				tagName[MAX_TAG_NAME_SIZE];
}RoamingPartnerInfo_t, *pRoamingPartnerInfo_t;

/// <summary>
/// A struct which holds the RAPL information
/// </summary>
typedef	struct _Rapl_t 
{
	RoamingPartnerInfo_t	roamingPartners[MAX_ROAMING_PARTNERS];
	UINT32					roamingPartnersSize;
	Any_t					any;  //specifies if NSPs not from the RAPL can be used too
	SelectPolicy_t			selectPolicy;
}Rapl_t, *pRapl_t;

/// <summary>
/// A struct which holds the link loss parameters
/// </summary>
typedef struct _LinkLossParameters_t
{
	UINT32	time;
	int	repetition;
}LinkLossParameters_t, *pLinkLossParameters_t;

typedef struct _RecentNSP_t
{	
	wmx_NSPid_t		recentNspID;	
	wmx_NAPid_t		lastConnectedNapIDs[WMX_NAPS_MAX_NUM];
	UINT8			DummyForCompilerHappy;
	UINT32			numOfConnectedNapIDs;
}RecentNSP_t, *pRecentNSP_t;

typedef struct _Profile_t
{	
	wmx_NSPid_t		nspID;	
	wmx_NAPid_t		napID;
	ChannelPlan_t	channelPlan;
}Profile_t, *pProfile_t;

/// <summary>
/// A struct which holds the igeneral NDnS settings
/// </summary>
typedef struct _NdsSettings_t
{
	wmx_RfStatus_t			swRfState;
	wmx_UserConnectMode_t	connectMode;
	BOOL					allowAutoActivate;
	BOOL					allowFastReconnect;	
	BOOL					setPreferredNspOnConnect;
	RecentNSP_t				lastConnectedNSP;	
	LinkLossParameters_t	shortLinkLossParams;
	LinkLossParameters_t	longLinkLossParams;
	wmx_UserRoamingMode_t	roamingMode;	
	UINT32					unprovisionedProfilesSize;
	wmx_THCriteria_t		thCriteria;
	char					WMFComplianceVersion[MAX_VERSION_SIZE];
	wmx_NSPid_t				currentPreferredNSP;
	Profile_t				unprovisionedProfiles[MAX_NUM_OF_RECENT_NSPS];
}NdsSettings_t, * pNdsSettings_t;

/// <summary>
/// A struct which holds the device certificates details
/// </summary>
typedef struct _DeviceCertificates_t
{
	char	rootCert[MAX_FILE_NAME_SIZE];
	char	clientCert[MAX_FILE_NAME_SIZE];
	char	privateKey[MAX_FILE_NAME_SIZE]; 
}DeviceCertificates_t, *pDeviceCertificates_t;

// TODO MZur consider move enum
/// <summary>
/// An enum which discribes different download states - for FUMO use
/// </summary>
typedef enum _DownloadState_t
{
	dsDownloadIdle = 10,
	dsDownloadFailed = 20,
	dsDownloadProgressing = 30,
	dsDownloadComplete = 40,
	dsReadyToUpdate = 50,
	dsUpdateProgressing = 60,
	dsUpdateFailedHaveData = 70,
	dsUpdateFailedNoData = 80,
	dsUpdateSuccessfulHaveData = 90,
	dsUpdateSuccessfulNoData = 100
}DownloadState_t, * pDownloadState_t;

typedef enum _FumoOperation_t
{	
	foDownload = 1,
	foUpdate,
	foDownloadAndUpdate
}FumoOperation_t, * pFumoOperation_t;

/// <summary>
/// A struct which holds the FUMO internal parameters
/// </summary>
typedef struct _FumoInternalParams_t
{	
	char				pkgPath[MAX_APDO_PATH];
	char				pkgFileName[MAX_APDO_PATH];
	char				fumoNodePath[MAX_APDO_PATH];
	FumoOperation_t		fumoOperation;
}FumoInternalParams_t, *pFumoInternalParams_t;

/// <summary>
/// A struct which holds the FUMO parameters
/// </summary>
typedef struct _FumoParams_t
{	
	char				pkgName[MAX_FILE_NAME_SIZE];
	char				pkgVersion[MAX_FILE_NAME_SIZE];
	char				downloadPkgURL[MAX_PATH];
	char				downloadAndUpdatePkgURL[MAX_PATH];
	DownloadState_t		state;
	char				tagName[MAX_TAG_NAME_SIZE];
	BOOL				fIsAllocated;
}FumoParams_t, *pFumoParams_t;

typedef enum _FUMOInstallStatus_t
{	
	isIdle,
	isInitiateInstall
}FUMOInstallStatus_t, * pFUMOInstallStatus_t;


/// <summary>
/// A struct which holds the change count information for a specific NAP
/// </summary>
typedef struct _ChangeCount_t
{
	wmx_NAPid_t		napId;
	UINT32			changeCount;
}ChangeCount_t, *pChangeCount_t;

/// <summary>
/// A struct which holds the information for an H_NSP
/// </summary>
typedef struct _HomeNsp_t
{
	wmx_NSPid_t		nspId;
	char			tagName[MAX_TAG_NAME_SIZE];
}HomeNsp_t, * pHomeNsp_t;

/// <summary>
/// A struct which holds the network parameters
/// </summary>
typedef struct _NwParams_t
{
	UINT32				hNspsSize;
	Capl_t				capl;
	Rapl_t				rapl;
	ChannelPlan_t		channelPlan;
	int					pollingInterval;
	int					pollingAttempts;
	char				provisionedName[WMX_NSP_NAME_MAX_SIZE];
	char				name16g[WMX_NSP_NAME_MAX_SIZE];//operator name obtained from 16g
	HomeNsp_t			hNsps[WMX_NSP_IDS_MAX_NUM];
	CHAR				serverID[MAX_SERVER_ID_SIZE];
}NwParams_t, * pNwParams_t;

/// <summary>
/// A struct which holds a certificate information
/// </summary>
typedef struct _Cert_t 
{
	//CertType_t		certType;	//specifies the type of certificate
	char				certType[MAX_CERT_TYPE_SIZE];
	CHAR				serNum[MAX_SER_NUM_SIZE];
	CHAR				issuer[MAX_ISSUER_SIZE];
	//UINT32			thumbPrint;	//NOT SUPPORTED NOW
	char			tagName[MAX_TAG_NAME_SIZE];
}Cert_t , * pCert_t;

/// <summary>
/// A struct which holds the SRV realm
/// </summary>
typedef struct _SrvRealm_t
{
	char	srvRealm[WMX_NSP_REALM_MAX_SIZE];
	char	tagName[MAX_TAG_NAME_SIZE];
} SrvRealm_t, *pSrvRealm_t;

/// <summary>
/// A struct which holds the EAP information
/// </summary>
typedef struct _EAP_t
{
	wmx_EapType_t	EAPMethod;
	UINT32			vendorId;
	UINT32			vendorType;
	char			id[WMX_SUBSCRIBER_ID_MAX_SIZE]; //user's id
	char			provisionedPseudoId[WMX_SUBSCRIBER_ID_MAX_SIZE];
	char			Password[MAX_EAP_PASSWORD_SIZE];//PASSWORD is the password that is used in EAP Authentication
	char			realm[WMX_NSP_REALM_MAX_SIZE];//specifies the override realm that is sent in the EAP identity response packet
	UINT32			encaps;
	BOOL			vfySrvRealm; 
	BOOL			usePrivacy;
	SrvRealm_t		srvRealms[MAX_NUM_OF_SRV_REALMS];// if vfySrvRealm is set to 1, then zero or more instances of SRV Realm String may be present
	UINT32			srvRealmsSize; 
	Cert_t			certs[MAX_NUM_OF_CERTS];//For those EAP types, that use certificates, these are the allowed user certificates
	UINT32			certsSize;
	char			tagName[MAX_TAG_NAME_SIZE];
}EAP_t, *pEAP_t;

/// <summary>
/// A struct which holds the primary subscription information
/// </summary>
typedef struct _SubscriberInfo_t
{
	char					name[WMX_SUBSCRIBER_NAME_MAX_SIZE];
	BOOL					activated;
	EAP_t					eapInfo[MAX_NUM_OF_EAP_METHODS];
	UINT32					eapInfoSize;
}SubscriberInfo_t, * pSubscriberInfo_t;

/// <summary>
/// A struct which holds other subscription information
/// </summary>
typedef struct _OtherSubsInfo_t
{
	SubscriberInfo_t subscriberInfo;
	char			 tagName[MAX_TAG_NAME_SIZE];
}OtherSubsInfo_t, * pOtherSubsInfo_t;

/// <summary>
/// A struct which holds all subscription information
/// </summary>
typedef struct _SubscriptionParams_t
{
	SubscriberInfo_t		primary;
	OtherSubsInfo_t			other[WMX_NSP_SUBSCRIBERS_MAX_NUM];
	UINT32					otherSize;
}SubscriptionParams_t, * pSubscriptionParams_t;

/// <summary>
/// A struct which holds a specific contact info
/// </summary>
typedef struct _ContactsInfo_t
{
	char	uri[WMX_URI_MAX_SIZE];
	UINT32	uriType; //TODO - don't forget to validate the values 0-255
	char	text[MAX_REASON_TEXT_SIZE];
	char	tagName[MAX_TAG_NAME_SIZE];
}ContactsInfo_t, * pContactsInfo_t;

/// <summary>
/// a struct which holds data for a provisioned NSP. It Contains discovered data as well 
/// </summary>
typedef struct _Provisioned_Nsp_t
{	
	NwParams_t				nwParams;	
	SubscriptionParams_t	subscriptionParams;
	ContactsInfo_t			contacts[MAX_NUM_OF_CONTACTS];
	UINT32					contactsSize;
	char					tagName[MAX_TAG_NAME_SIZE];
	BOOL					fIsAllocated;
} ProvisionedNsp_t, *pProvisionedNsp_t;

/// <summary>
/// A struct which holds the discovered data per NSP
/// </summary>
typedef struct _DiscoveredNsp_t
{
	wmx_NSPid_t		 nspID;
	wmx_NAPid_t		 naps[MAX_NUM_OF_DISCOVERED_NAPS];
	UINT32			 napsSize;
	char			 name[WMX_NSP_NAME_MAX_SIZE];
	char			 visitedRealm[MAX_REALM_SIZE];
}DiscoveredNsp_t, *pDiscoveredNsp_t;

/// <summary>
/// A struct which holds only .16g discovered data per NSP
/// </summary>
typedef struct _NspInfo_16G
{	
	wmx_NSPid_t		nspID;
	char			name[WMX_NSP_NAME_MAX_SIZE];
	char			visitedRealm[MAX_REALM_SIZE];
}NspInfo_16G, *pNspInfo_16G;

/// <summary>
/// A struct which holds all discovered data per a specific NAP
/// </summary>
typedef struct _DiscoveredNap_t
{	
	NspInfo_16G			nspInfo[MAX_NUM_OF_DISCOVERED_NSPS];
	UINT32				nspInfoSize;
	UINT32				changeCount;
	ChannelPlan_t		channelPlan;	
	BOOL				isLastDetected;
	wmx_NAPid_t			napID;
}DiscoveredNap_t, *pDiscoveredNap_t;

typedef struct _SpLock_t
{
	BOOL lockStatus;
	char operatorName[WMX_NSP_NAME_MAX_SIZE];
	char lock[MAX_LOCK_SIZE];
}SpLock_t, *pSpLock_t;

typedef struct _ProductVersions_t
{
	char fwVersion[MAX_VERSION_SIZE];						// == WMX_DEVICE_VERSION_MAX_LENGTH
	char hwVersion[MAX_VERSION_SIZE];						// == WMX_DEVICE_VERSION_MAX_LENGTH
	char swVersion[MAX_VERSION_SIZE];						// == WMX_DEVICE_VERSION_MAX_LENGTH
	char manufacturer[MAX_MAN_NAME_SIZE];					// == WMX_MANUFACTURER_NAME_MAX_LENGTH
	char model[MAX_MOD_NAME_SIZE];							// == WMX_MODEL_TYPE_NAME_MAX_LENGTH
}ProductVersions_t, *pProductVersions_t;

typedef struct _WmxRadioModule_t
{
	SpLock_t	spLock;
	ProductVersions_t productVersions;
	char		macAddress[MAX_DEV_ID_SIZE];
	char		tagName[MAX_TAG_NAME_SIZE];
}WmxRadioModule_t, *pWmxRadioModule_t;

typedef struct _StaticWmxDetails_t
{
	WmxRadioModule_t	wmxRadioModules[MAX_NUM_OF_WIMAX_RADIO_MOD];
	UINT32				wmxRadioModulesSize;
	ProductVersions_t staticTermEquip;
}StaticWmxDetails_t, *pStaticWmxDetails_t;

typedef enum _apdo_DbCmd_t
{
	APDO_AddCmd = 0,     // DB Add command
	APDO_UpdateCmd ,    // DB update command
	APDO_GetCmd,         // DB Get command
	APDO_DeleteCmd       // DB delete command

} apdo_DbCmd_t, *apdo_pDbCmd_t;

typedef struct _BootstrapInfo_t
{
	char	serverID[MAX_SERVER_ID_SIZE];
	char	serverUserName[WMX_SUBSCRIBER_ID_MAX_SIZE];
	char	clientUserName[WMX_SUBSCRIBER_ID_MAX_SIZE];
	char	portNbr[MAX_PORT_NUMBER_SIZE];
	char	serverURL[MAX_SERVER_URL_SIZE];
	char	tagName[MAX_TAG_NAME_SIZE];
}BootstrapInfo_t, *pBootstrapInfo_t;

typedef struct _ClientInitiated_t
{
	BOOL pollingSupported;
	int pollingInterval;
	int pollingAttempts;
}ClientInitiated_t, *pClientInitiated_t;

typedef struct _UpdateMethods_t
{
	ClientInitiated_t clientInitiated;		

}UpdateMethods_t, *pUpdateMethods_t;

typedef struct _DevCAP_t
{
	UpdateMethods_t updateMethods;

}DevCAP_t, *pDevCAP_t;

typedef struct _TerminalEquipment_t
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
	DevCAP_t			devCap;

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
}DevDetail_t, *pDevDetail_t;



// Platform Noise Mitigation parameters:
typedef struct _pnm_t
{
	UINT32	m_dwChannelNumber;	
		UINT32	m_dwCenterFrequency;	//			phase 1
		UINT32	m_dwFrequencySpread; 	// (BW)		phase 1;    According to the L3L4 ENUM
	UINT32	m_dwNoisePower;
		UINT32	m_dwSignalToNoiseRatio;	//	(CINR)	phase 1
		UINT32	m_dwRSSI;				//			phase 1
			// The transmitter connect status:		
	UINT32	m_dwConnectStatus;			//			phase 1
	UINT32	m_dwBitError;
	UINT32	m_reserved;					// reserved
}pnm_t, PNM_COMMDEV_CHANNEL_INFO, *PPNM_COMMDEV_CHANNEL_INFO;



/// <summary>
/// Init the DB
/// </summary>
/// <returns>wmx_Status_t </returns>
wmx_Status_t L4db_Init();
/// <summary>
/// clean the DB
/// </summary>
/// <returns>wmx_Status_t </returns>
wmx_Status_t L4db_Clean();
/// <summary>
/// DeInit the DB
/// </summary>
/// <returns>wmx_Status_t </returns>
wmx_Status_t L4db_DeInit();
/// <summary>
/// Gets APDO info according to a given APDO path
/// </summary>
wmx_Status_t L4db_GetAPDOinfo( wmx_APDOPath_t pAPDOPath, void *pValue, wmx_pAPDOType_t pAPDOType );
/// <summary>
/// adds APDO info according to a given APDO path
/// </summary>
wmx_Status_t L4db_AddAPDOinfo( wmx_APDOPath_t pAPDOPath, void *pValue, wmx_APDOType_t APDOType );
/// <summary>
/// Updates APDO info according to a given APDO path
/// </summary>
wmx_Status_t L4db_UpdateAPDOinfo( wmx_APDOPath_t pAPDOPath, void *pValue, wmx_APDOType_t APDOType );
/// <summary>
/// deletes APDO info according to a given APDO path
/// </summary>
wmx_Status_t L4db_DeleteAPDOinfo( wmx_APDOPath_t pAPDOPath );
/// <summary>
/// The function runs over all the channels in the channel plan and returns the index of the first
/// channel that has full preambles (or the length of the channel plan in case of no results)
/// </summary>
UINT32 L4db_GetFirstChannelWithFullPreambles(pChannelInfo_t channelList, UINT32 numChannels);
/// <summary>
/// Remove the duplicated channels in the last detected channels list
/// </summary>
wmx_Status_t L4db_DeleteDuplicatedChannelsInDetectedChannels(wmx_NAPid_t napID, BOOL isComparePreambles);
/// <summary>
/// Remove the channels that differ only in the preambles property in the last detected channels list
/// </summary>
wmx_Status_t L4db_DeleteDuplicatedChannelsInAllDetectedChannels(BOOL isComparePreambles);
/// <summary>
/// Add the given channel info list to the last detected channel plan and purge the last channels with the same preambles
/// </summary>
wmx_Status_t L4db_AddNeighborAdvChannels(UINT32 numOfChannelInfos, pChannelInfo_t pChannelInfoList);
/// <summary>
/// Get the data of a provisioned NSP including last detected discovered data 
/// </summary>
/// <param name="NSPid">(IN) NSP id </param>
/// <param name="pNSP">(OUT) the NSP data </param>
/// <returns>WMX_ST_OK if successful. WMX_ST_FAIL if the specified nspID is not provisioned </returns>
wmx_Status_t L4db_GetProvisionedNsp(wmx_NSPid_t nspID, pProvisionedNsp_t pNsp);
/// <summary>
/// Get the data of a provisioned NSP including discovered data 
/// </summary>
/// <param name="NSPid">(IN) NSP id </param>
/// <param name="pNSP">(OUT) the NSP data </param>
/// <returns>WMX_ST_OK if successful. WMX_ST_FAIL if the specified nspID is not provisioned </returns>
wmx_Status_t L4db_GetProvisionedNspEx(wmx_NSPid_t nspID, pProvisionedNsp_t pNsp, BOOL onlyLastDetected);

/// <summary>
/// Resturns TRUE is the given nspID has an unprovisioned profile 
/// </summary>
/// <param name="NSPid">(IN) NSP id </param>
BOOL L4db_IsUnprovisionedProfile(wmx_NSPid_t nspID);

/// <summary>
/// Resturns the boolean value of the polling interval support. 
/// </summary>
BOOL L4db_GetPollingIntervalSupported();

/// <summary>
/// Converts a provisioned NSP structure to the interface's structure
/// </summary>
/// <param name="provisionedNsp">(IN)the provisioned NSP </param>
/// <param name="pNspIf">(OUT) the NSP iterface structure to be filled </param>
void L4db_ConvertNspToInterface(pProvisionedNsp_t pProvisionedNsp, wmx_pNSP_t pNspIf);
/// <summary>
///Gets an NSP ID for each provisioned NSP
///</summary>
/// <param name="pNspIds">(OUT)  an array of NSP IDs allocated by the user </param>
/// <param name="nNspsSize">(IN)  the size of the array allocated by the user
///			                     (OUT)The actual number of elements returned \ that should be allocated in the 
///                               pNsps' array.</param>
/// <returns>WMX_ST_OK if successful.
///		If the actual number of elements is higher than the number of elements allocated, 
///     the API will return WMX_ST_BUFFER_TOO_SHORT</returns>
wmx_Status_t L4db_GetProvisionedNspIds(wmx_pNSPid_t pNspIds, UINT32 * nNspIdsSize);
/// <summary>
/// Gets the operator's name received from provisioning and 16g
/// </summary>
/// <param name="nspID">(IN)  the ID of the requested NSP</param>
/// <param name="provisionedName">(OUT) the NSP name received through provisioning. This should be allocated by the user</param>
/// <param name="nProvisionedNameSize">(IN)  the size of provisionedName allocated by the user
///			                           (OUT)The actual number of elements returned \ should be allocated in the provisionedName.</param>
/// <param name="name16g">(OUT) the NSP name received through 16g. This should be allocated by the user</param>
/// <param name="n16gNameSize">(IN)  the size of name16g allocated by the user
///			                (OUT)The actual number of elements returned \ that should be allocated in the name16g.</param>
/// <returns>WMX_ST_OK if successful.
///		If the actual number of elements is higher than the number of elements allocated, 
///     the API will return WMX_ST_BUFFER_TOO_SHORT</returns>
wmx_Status_t L4db_GetNspName(wmx_NSPid_t nspID, char * provisionedName, UINT32 * nProvisionedNameSize, char * name16g, UINT32 * n16gNameSize);
/// <summary>
/// Gets one of the IDs of the NSP which has the name nspName. 
/// If a 16g name exists, we will look it up first. 
///</summary>
/// <param name="nspName">(IN)  The requested NSP name </param>
/// <returns>L4DB_INVALID_INDEX if the name doesn't exist and its nspID otherwise</returns>
wmx_NSPid_t L4db_GetNspId(char * nspName);
/// <summary>
/// Gets the category of the given NSP ID
/// </summary>
/// <param name="nspID">(IN)the requested NSP ID </param>
/// <returns>NspCategory - the NSP's category</returns>
NspCategory_t L4db_GetNspCategory(wmx_NSPid_t nspID);
/// <summary>
//get the pNwParams per NSP ID
/// </summary>
///<param name="nspID">(IN)  wmx_NSPid_t nspID - the NSP ID.</param>
///<param name="pNwParams">(OUT) the pNwParams per the NSP</param>
/// <returns>TRUE is found a NSP per the NSP ID</returns>
wmx_Status_t L4db_GetNwParamsPerNsp(wmx_NSPid_t nspID, pNwParams_t pNwParams);

/// <summary>
/// Checks if this is the last NSP we were connected to
/// </summary>
/// <param name="pNspID">(IN) NSP ID to check </param>
/// <returns>TRUE is this is the recent NSP</returns>
BOOL L4db_IsRecentNsp(wmx_pNSPid_t pNspID);

/// <summary>
/// Returns TRUE if this NAP was used for connection by the recent NSP
/// </summary>
/// <param name="napId">(IN) the NAP </param>
/// <returns>TRUE if this NAP was used</returns>
BOOL L4db_IsRecentNAP(wmx_NAPid_t napId);


/// <summary>
/// return TRUE if a recent NAP was retreived
/// </summary>
/// <param name="napId">(OUT) the NAP </param>
/// <returns>TRUE if a NAP was returned</returns>
BOOL L4db_GetRecentNAP(wmx_NAPid_t napId);

/// <summary>
/// Gets the recent NSP we were connected to
/// </summary>
/// <param name="pNspID">(OUT) the recent NSP </param>
/// <returns>WMX_ST_OK if successful.</returns>
wmx_Status_t L4db_GetRecentNsp(wmx_pNSPid_t pNspID);

/// <summary>
/// Checks if a NAP ID is empty
/// </summary>
/// <param name="napID">(IN) NAP ID</param>
/// <returns>TRUE if empty.</returns>
BOOL L4db_IsNapidEmpty(wmx_NAPid_t napID);

/// <summary>
/// Get an array with the unprovisioned profiles IDs
/// </summary>
/// <param name="unprovisionedProfiles">(OUT)  an array of unprovisioned profilew. The array should be allocated be the user </param>
/// <param name="unprovisionedProfilesSize">(IN)  the size of the array allocated by the user
///			                     (OUT)The actual number of elements returned \ that should be allocated in the 
///                               unprovisionedProfiles array.</param>
/// <returns>WMX_ST_OK if successful.
///		If the actual number of elements is higher than the number of elements allocated, 
///     the API will return WMX_ST_BUFFER_TOO_SHORT</returns>
wmx_Status_t L4db_GetUnprovisionedProfilesList(pProfile_t unprovisionedProfiles, UINT32 *unprovisionedProfilesSize);

wmx_Status_t L4db_GetUnprovisionedProfilePerNspID(wmx_NSPid_t nspId, pProfile_t pUnprovisioned);
wmx_Status_t L4db_GetProvisionedPerNspID(wmx_NSPid_t nspId, pProvisionedNsp_t pProvisioned);

UINT32 L4db_GetMaxDetectedChannelPerNap(wmx_NAPid_t napId);

wmx_Status_t L4db_GetDetectedChannelPerNap(wmx_NAPid_t napId,
										   pChannelPlan_t pChannelPlan);

wmx_Status_t L4db_AddChannelPlanToUnprovisionedProfile(wmx_NSPid_t nspID);

wmx_Status_t L4db_AddUnprovisionedProfile(wmx_NSPid_t nspID);

/// <summary>
/// find the max possible size of detected channel list of all the NAPs
/// <param name="pChannelInfoListSize">(OUT) contain the the number of detected channels of all the NAPs </param name>
/// </summary>
wmx_Status_t L4db_GetMaxDetectedChannels(UINT32 *pChannelInfoListSize);

/// <summary>
/// Updates the Current Preferred Nsp
/// </summary>
/// <returns>wmx_Status_t </returns>
wmx_Status_t L4db_GetCurrentPreferredNsp(wmx_pNSPid_t pCurrentPreferredNspID);
wmx_Status_t L4db_SetCurrentPreferredNsp(wmx_NSPid_t currentPreferredNspID);

BOOL L4db_IsCurrentPreferredNSP(wmx_NSPid_t nspId);

/// <summary>
/// Updates username and password nodes in the EAP.
/// finds the EAP entry with MSCHAPv2 (if any).
/// </summary>
/// <param name="node">(IN)The EAP node need to be changed </param>
/// <param name="nodeValue">(IN)The new value of the node  </param>
/// <returns>wmx_Status_t </returns>
wmx_Status_t L4db_SetEapNode(wmx_NSPid_t nspID, 
							 char *username,
							 char *password);

wmx_Status_t L4db_SetConnectedNap(wmx_NAPid_t napID);
/// <summary>
/// Updates the connected NSP
/// </summary>
/// <param name="nspID">(IN)  the NSP ID we are connected to </param>
/// <returns>wmx_Status_t </returns>
wmx_Status_t L4db_SetConnectedNsp(wmx_NSPid_t nspID);
wmx_Status_t l4db_DeAllocUnprovisionedNSP(wmx_NSPid_t nspID);
wmx_Status_t L4db_DeProvisionNsp(wmx_NSPid_t nspID);
/// <summary>
/// Gets the NDnS general settings
/// </summary>
/// <param name="settings">(OUT)  a pointer to the struct to be filled with the NDnS settings </param>
/// <returns>wmx_Status_t </returns>
wmx_Status_t L4db_GetNdsSettings(pNdsSettings_t pSettings);
/// <summary>
/// Sets the NDnS general settings
/// </summary>
/// <param name="settings">(IN)  a pointer to a struct of the NDnS general settings </param>
/// <returns>wmx_Status_t </returns>
wmx_Status_t L4db_SetNdsSettings(NdsSettings_t settings);

/// <summary>
/// Prints the discovered NAPs list
/// </summary>
void L4db_PrintDiscoveredNAPsList();

/// <summary>
/// Sets the discovered NAP Information for a specific NAP ID
/// </summary>
/// <param name="napInfo">(IN) the discovered NAP info to be updated.
/// if the nap Id already exists, its data will be overriden</param>
/// <returns>wmx_Status_t </returns>
wmx_Status_t L4db_SetDiscoveredNapInfo(pDiscoveredNap_t napInfo, wmx_pNAP_t pNAPs);
/// <summary>
/// Gets the discovered NAP Information, received from .16g or scanning process, for a specific NAP ID
/// </summary>
/// <param name="napID">(IN)  the nap ID for which we request NAP info for </param>
/// <param name="pDiscoveredNap">(OUT) a discovered nap struct</param>
/// <returns>wmx_Status_t</returns>
wmx_Status_t L4db_GetDiscoveredNapInfo(wmx_NAPid_t napID, pDiscoveredNap_t pDiscoveredNap);
/// <summary>
/// Resets the Last detected NAPs so they become "old detected" NAPS
/// </summary>
/// <returns>wmx_Status_t</returns>
wmx_Status_t L4db_ResetLastDetectedNaps();
/// <summary>
/// Decrease the TTL value of all detected channels
/// </summary>
/// <returns>wmx_Status_t</returns>
wmx_Status_t L4db_DecreaseTtlForAllDetectedChannels();
/// <summary>
/// change the detection status of a specified nap
/// </summary>
/// <returns>wmx_Status_t</returns>
wmx_Status_t L4db_SetDetectedNapFlag(wmx_pNAPid_t napID, BOOL status);
/// <summary>
///Gets the Nap ids of all the last detected NAPs
///</summary>
/// <param name="pNapIds">(OUT)  an array of NAP IDs allocated by the user </param>
/// <param name="nNapIdsSize">(IN)  the size of the array allocated by the user
///			                     (OUT)The actual number of elements returned \ that should be allocated in the 
///                               pNapIds' array.</param>
/// <returns>WMX_ST_OK if successful.
///		If the actual number of elements is higher than the number of elements allocated, 
///     the API will return WMX_ST_BUFFER_TOO_SHORT</returns>
wmx_Status_t L4db_GetLastDetectedNapIds(wmx_NAPid_t * pNapIds, UINT32 * nNapIdsSize);
/// <summary>
///Gets the Nap ids of all the old detected NAPs
///</summary>
/// <param name="pNapIds">(OUT)  an array of NAP IDs allocated by the user </param>
/// <param name="nNapIdsSize">(IN)  the size of the array allocated by the user
///			                     (OUT)The actual number of elements returned \ that should be allocated in the 
///                               pNapIds' array.</param>
/// <returns>WMX_ST_OK if successful.
///		If the actual number of elements is higher than the number of elements allocated, 
///     the API will return WMX_ST_BUFFER_TOO_SHORT</returns>
wmx_Status_t L4db_GetOldDetectedNapIds(wmx_NAPid_t * pNapIds, UINT32 * nNapIdsSize);
/// <summary>
/// Gets the detected info for a given NAP
/// </summary>
/// <returns>wmx_Status_t</returns>
wmx_Status_t L4DB_GetNon16gDetectedNapInfo(wmx_NAPid_t napID, pDiscoveredNap_t nap, BOOL onlyLastDetected);
/// <summary>
/// Gets a NAPs Information for a specified NSP. This API gets both provisioned and discovered information
/// </summary>
/// <param name="nspID">(IN)  the nsp ID for which we request NAP info for </param>
/// <param name="pNaps">(OUT) an array of NAPs</param>
/// <param name="nNapsSize">(IN)  the size of pNaps allocate by the user
///                         (OUT) the actual number of elemnts returned \ that should be allocated in pNaps</param>
/// <returns>WMX_ST_OK if successful.
///		If the actual number of elements is higher than the number of elements allocated, 
///     the API will return WMX_ST_BUFFER_TOO_SHORT</returns>

/// <summary>
/// Return the list of NAPs that didn't pass the link quality threshold
/// </summary>
wmx_Status_t GetNapsBeneathThreshold(UINT32 *numOfNaps, wmx_pNAP_t napsBeneathThreshold);

wmx_Status_t GetApdoOperatorConfigurations(wmx_pApdoOperatorConfigurations_t pConfigurations);
wmx_Status_t L4db_GetNapsInfo(wmx_NSPid_t nspID, pL4db_Nap_t pNaps, UINT32 * nNapsSize);
/// <summary>
/// Gets an array of all NAP ID's an their change counts
/// </summary>
/// <param name="pChangeCounts">(OUT)  the array of change counts allocated by the user</param>
/// <param name="nChangeCountsSize">(IN)  the size of changeCounts allocate by the user
///                                 (OUT) the actual number of elemnts returned \ that should be allocated in changeCounts</param>
/// <returns>WMX_ST_OK if successful.
///		If the actual number of elements is higher than the number of elements allocated, 
///     the API will return WMX_ST_BUFFER_TOO_SHORT</returns>
wmx_Status_t L4db_GetNapChangeCountList(pChangeCount_t changeCounts, UINT32 * nChangeCountsSize);
/// <summary>
/// Gets the NSP IDs related to the given NAP ID. This includes NSPs which we discovered 
/// through 16g. One NSP ID is given per NSP
/// </summary>
/// <param name="napID">(IN)  the requested NAP ID</param>
/// <param name="pNspIds">(OUT)  an array of NAP IDs to be filled by this API</param>
/// <param name="nNspIdsSize">(IN)  the size of pNspIds allocate by the user
///                                 (OUT) the actual number of elemnts returned \ that should be allocated in pNspIds</param>
/// <returns>WMX_ST_OK if successful.
///		If the actual number of elements is higher than the number of elements allocated, 
///     the API will return WMX_ST_BUFFER_TOO_SHORT</returns>
wmx_Status_t L4db_ConvertNap2Nsps(wmx_BSid_t bsID, wmx_BsIdType_t napIdType, wmx_pNSPid_t pNspIds, UINT32 * nNspIdsSize);
/// <summary>
/// Sets the user connection mode
/// </summary>
wmx_Status_t L4db_SetConnectMode(wmx_UserConnectMode_t newVal);
/// <summary>
/// Gets the user connection mode
/// </summary>
wmx_UserConnectMode_t L4db_GetConnectMode();
/// <summary>
/// Sets the fast reconnect status
/// </summary>
wmx_Status_t L4db_SetFastReconnectStatus(BOOL isEnabled);
/// <summary>
/// Gets the fast reconnect status
/// </summary>
BOOL L4db_GetFastReconnectStatus();
/// <summary>
/// Sets the allow auto activate flag
/// </summary>
void L4db_SetAllowAutoActivate(BOOL val);
/// <summary>
/// Gets the allow auto activate flag
/// </summary>
BOOL L4db_GetAllowAutoActivate();
/// <summary>
/// sets the short link loss parameters
/// </summary>
void L4db_SetShortLinkLossParams(LinkLossParameters_t linkLossParams);
/// <summary>
/// gets the short link loss parameters
/// </summary>
LinkLossParameters_t L4db_GetShortLinkLossParams();
/// <summary>
/// sets the long link loss parameters
/// </summary>
void L4db_SetLongLinkLossParams(LinkLossParameters_t linkLossParams);
/// <summary>
/// gets the long link loss parameters
/// </summary>
LinkLossParameters_t L4db_GetLongLinkLossParams();
/// <summary>
/// Sets the last rf state
/// </summary>
wmx_Status_t L4db_SetSwRfState(wmx_RfStatus_t newState);
/// <summary>
/// Gets the last rf state
/// </summary>
wmx_RfStatus_t L4db_GetSwRfState();
/// <summary>
/// Sets the SetPreferredNspOnConnect state
/// </summary>
wmx_Status_t L4db_SetSetPreferredNspOnConnectState(BOOL newState);
/// <summary>
/// Gets the SetPreferredNspOnConnect state
/// </summary>
BOOL L4db_GetSetPreferredNspOnConnectState();
/// <summary>
/// Sets the TH criteria
/// </summary>
void L4db_SetThCriteria(wmx_THCriteria_t newVal);
/// <summary>
/// Gets the TH criteria
/// </summary>
wmx_THCriteria_t L4db_GetThCriteria();
// Reset the NAPs beneath threshold list
void ResetNAPsBeneathThreshold();
// Store the NAPs beneath threshold
void AddNAPsBeneathThreshold(UINT32 numOfNAPs, wmx_pNAP_t pNaps);
// Sort NAPs by the RSSI and CINR
void SortNaps(wmx_pNAP_t pNaps, UINT32 numOfNaps);
/// <summary>
/// Gets the current connection time
/// </summary>
UINT32 L4db_GetConnectionTime();
/// <summary>
/// Set the current connection time
/// </summary>
void L4db_SetConnectionTime(UINT32 connectionTime);
/// <summary>
/// Sets Roaming mode per the specified NSP
/// </summary>
wmx_Status_t L4db_SetRoamingMode(wmx_UserRoamingMode_t newVal);
/// <summary>
/// Gets Roaming mode per the specified NSP
/// </summary>
wmx_Status_t L4db_GetRoamingMode(wmx_pUserRoamingMode_t pVal);
/// <summary>
/// Sets the NDnS general settings
/// </summary>
/// <param name="bandRange">(OUT)  a pointer to a channelPlan struct to filled with the band range data</param>
/// <returns>wmx_Status_t </returns>
wmx_Status_t L4db_GetBandRange(pChannelPlan_t pBandRange);
/// <summary>
/// Sets the NDnS general settings
/// </summary>
/// <param name="bandRange">(IN)  a pointer to a channelPlan struct with the band range data
/// NOTE: each channel in the ChannelPlan_t struct should be given a tag name</param>
/// <returns>wmx_Status_t </returns>
wmx_Status_t L4db_SetBandRange(pChannelPlan_t pBandRange);
/// <summary>
/// Gets the device certificates
/// </summary>
/// <param name="pDeviceCerts">(OUT) a pointer to a device certificates struct</param>
/// <returns>wmx_Status_t </returns>
wmx_Status_t L4db_GetDeviceCertificates(pDeviceCertificates_t pDeviceCerts);

wmx_Status_t L4db_GetDevDetailParam(pDevDetail_t pDevDetail);

wmx_Status_t L4db_GetDevinfo(pDevInfo_t pDevInfo);
/// <summary>
/// Gets the preferred scan policy
/// </summary>
/// <returns>wmx_Status_t </returns>
wmx_Status_t L4db_SetPreferredScanPolicy(PreferredScanPolicy_t policy);
/// <summary>
/// Gets the preferred scan policy
/// </summary>
/// <returns>wmx_Status_t </returns>
PreferredScanPolicy_t L4db_GetPreferredScanPolicy();
/// <summary>
/// Gets the version of the L4db
/// </summary>
/// <returns>wmx_Status_t </returns>
int L4db_GetDbVersion();
/// <summary>
/// Gets the current NAI counter
/// </summary>
/// <returns>wmx_Status_t </returns>
UINT32 L4db_GetNaiCounter();//TODO - remove this

/// <summary>
/// Gets the current NAI counter
/// </summary>
/// <returns>wmx_Status_t </returns>
void L4db_SetNaiCounter(UINT32 val); //TODO - remove this

/// <summary>
/// Gets all the raoming patners of a specified NSP
/// </summary>
/// <param name="hNspID">(IN)  the ID of the home NSP</param>
/// <param name="roamingPartners">(OUT)in array of roaming partners info allocated by the user</param>
/// <param name="nRoamingPartnersSize">(IN)  the size of roamingPartners allocate by the user
///                                 (OUT) the actual number of elemnts returned \ that should be allocated in roamingPartners</param>
/// <returns>WMX_ST_OK if successful.
///		If the actual number of elements is higher than the number of elements allocated, 
///     the API will return WMX_ST_BUFFER_TOO_SHORT</returns>
wmx_Status_t L4db_GetRoamingPartners(wmx_NSPid_t hNspID, pRoamingPartnerInfo_t pRoamingPartners, UINT32 * nRoamingPartnersSize);
/// <summary>
/// Starts an "atomic" operation. the following sequence of APIs will be treated as an atom
/// </summary>
/// <returns>wmx_Status_t </returns>
wmx_Status_t L4db_StartAtomic();
/// <summary>
/// Ends an "atomic" operation and starts a commit process in the database.
/// </summary>
/// <returns>wmx_Status_t </returns>
wmx_Status_t L4db_EndAtomic();
/// <summary>
/// Sets the callback method for handling the status of a commit process
/// </summary>
/// <param name="pCallback">(IN) the commit status callback method</param>
/// <returns>wmx_Status_t </returns>
wmx_Status_t L4db_RegisterCommitCB(L4db_pCommitCB_t pCallback);
/// <summary>
/// Save data base into XML file
/// </summary>
/// <param name="pwsFileNamee">(IN) name of file to be save
/// <returns>wmx_Status_t </returns>
wmx_Status_t L4db_SaveToFile(const char *pwsFileNamee);
/// <summary>
/// restore data base from XML file
/// </summary>
/// <param name="pwsFileNamee">(IN) name of file to restore from
/// <returns>wmx_Status_t </returns>
wmx_Status_t L4db_RestoreFromFile(const char *pwsFileName);

/// <summary>
/// restore data base from default XML file
/// </summary>
/// <returns>wmx_Status_t </returns>
wmx_Status_t L4db_RestoreFromDefaults();

/// <summary>
/// sets the device's general details - this API is used to initialize 
/// general device and terminal charecaristics which are known on during start up of AppSrv
/// </summary>
// wmx_Status_t L4db_SetGeneralSettings(pStaticWmxDetails_t pGeneralSettings);

/// <summary>
/// sets the SP lock details
/// </summary>
wmx_Status_t L4db_SetSpLock(char * wmxRadioModTagName, pSpLock_t pSpLock);

/// <summary>
/// sets the SP lock details
/// </summary>
wmx_Status_t L4db_GetSpLock(char * wmxRadioModTagName, pSpLock_t pSpLock);

///THIS IS A PATCH - THIS SHOULD BE REMOVED IN THE FUTURE
wmx_Status_t L4db_AddNapPatch(wmx_NAPid_t napID);

// The following functions are for FUMO process 
wmx_Status_t L4db_GetWimaxNode(pWimax_t Wimax);
wmx_Status_t L4db_GetFumoNode(pFumoParams_t FumoParams);
wmx_Status_t L4db_GetFumoInternalInfo(pFumoInternalParams_t pFumoInternalParams);
wmx_Status_t L4db_SetFumoInternalFumoNodePath(char* fumoNodePath);
wmx_Status_t L4db_SetFumoInternalPackagePath(char* pkgPath);
wmx_Status_t L4db_SetFumoInternalPackageFileName(char* pkgFileName);
wmx_Status_t L4db_SetFumoInternalFumoOperation(FumoOperation_t op);

/// <summary>
/// Gets the default realm
/// </summary>
/// <param name="defaultRealm">(OUT)  a pointer to the string of the default realm </param>
/// <returns>wmx_Status_t </returns>
wmx_Status_t L4db_GetDefaultRealm(char* defaultRealm);
/// <summary>
/// Update relevant L4db fields from NVM values
/// </summary>
/// <returns>wmx_Status_t </returns>
wmx_Status_t L4db_UpdateFromNVM();

wmx_Status_t L4db_SetInstallStatus(FUMOInstallStatus_t status);

wmx_Status_t L4db_GetBEK(wmx_pBEKBuffer_t pBEK );
wmx_Status_t L4db_SetBEK(wmx_pBEKBuffer_t pBEK );

wmx_Status_t L4db_DeleteDuplicatedChannels(UINT32 *numOfChannelInfos, pChannelInfo_t pChannelInfoList, BOOL isComparePreambles);

/// <summary>
/// Channel priority comparison function for quicksort accourding to the TTL and all the structures elements
/// </summary>
int l4db_CompareChannelInfoByAge(const void * elem1, const void * elem2);

wmx_Status_t L4db_GetChannelsPerProvisionedNsp(wmx_NSPid_t currentPreferredNspId,
											   pChannelInfo_t pChannelInfoList,
											   UINT32 *nChannelInfoListSize);

wmx_Status_t L4db_GetMaxChannelsPerProvisionedNsp(wmx_NSPid_t nspId,
												 UINT32 *pChannelInfoListSize);

wmx_Status_t L4db_GetAllDiscoveredNapsInfoList(pDiscoveredNap_t pDiscoveredNapList, UINT32 *numOfNaps);

wmx_Status_t L4db_UpdatePackageVersion();
wmx_Status_t L4db_GetInstallationInfo(char* installVersion, size_t versionSize);
wmx_Status_t L4db_SetVersionDefault();
wmx_Status_t L4db_GetToDMAccByTagName(char tagName[MAX_TAG_NAME_SIZE], char toDmAcc[MAX_ACCOUNT_NAME_SIZE]);
wmx_Status_t L4db_GetContactInfoByPath( pContactsInfo_t contactInfo, char* path );
wmx_Status_t L4db_WMFComplianceVersion(char* WMFComplianceVersion, UINT32 WMFComplianceVersionLen);
wmx_Status_t L4db_PNMUpdate(wmx_pSystemStateUpdate systemStateUpdate, BOOL* channelChanged);
wmx_Status_t L4db_GetPNM(PPNM_COMMDEV_CHANNEL_INFO bufferOut, UINT32 *bufferSize);
#endif //_NDNS_AGENT_DB_IF_
