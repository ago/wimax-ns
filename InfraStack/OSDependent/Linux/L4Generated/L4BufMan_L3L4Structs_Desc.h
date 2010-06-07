
/****************************************************************************
*
* Auto generated file
* Version XXX
* Compliant with XXX.bm version XXX
* 11/19/2009 12:55:59 AM
*
*****************************************************************************/

#ifndef _L4BUFMAN_L3L4STRUCTS_DESC_H
#define _L4BUFMAN_L3L4STRUCTS_DESC_H


#include "TypesProxy.h"
#include "L3L4Structs.h"
#include "L4BufMan_L4Common_Desc.h"




#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct L4MVersion_tlv_struct
{
	UINT16 Type;
	UINT16 VersionMajor;
	UINT16 VersionMinor;
	UINT16 VersionBranch;
	UINT16 Reserved2;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct L4MVersion_tlv_struct L4MVersion_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct TLSOperationDescriptor_tlv_struct
{
	UINT16 Type;
	UINT32 Operation;
	UINT32 LParameter1;
	UINT32 LParameter2;
	UINT32 Context;
	UINT32 Connection;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct TLSOperationDescriptor_tlv_struct TLSOperationDescriptor_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct ExchangeBuffer_tlv_struct
{
	UINT16 Type;
	UINT16 ActualLen;
	Uint8_type BufferArr[3000];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct ExchangeBuffer_tlv_struct ExchangeBuffer_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct AppOutputBuffer_tlv_struct
{
	UINT16 Type;
	UINT16 ActualLen;
	Uint8_type BufferArr[3000];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct AppOutputBuffer_tlv_struct AppOutputBuffer_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct ChannelInfoArray_tlv_struct
{
	UINT16 Type;
	UINT32 Frequency;
	UINT16 ChannelId;
	UINT8 Bandwidth;
	UINT8 Fft;
	Uint8_type Preambles[15];
	UINT8 Reserved;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct ChannelInfoArray_tlv_struct ChannelInfoArray_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct BSCritieria_tlv_struct
{
	UINT16 Type;
	Uint8_type BSID_Criterion[6];
	Uint8_type BSID_Criterion_Mask[6];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct BSCritieria_tlv_struct BSCritieria_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct THCriteria_tlv_struct
{
	UINT16 Type;
	UINT32 RssiTH;
	UINT32 CinrTH;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct THCriteria_tlv_struct THCriteria_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct ConnectFlags_tlv_struct
{
	UINT16 Type;
	UINT32 VisitedNspId;
	UINT8 RequestRealm;
	UINT8 SIQ;
	UINT8 Reserved1;
	UINT8 Reserved2;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct ConnectFlags_tlv_struct ConnectFlags_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct EapRequestMessage_tlv_struct
{
	UINT16 Type;
	UINT16 ActualLen;
	Uint8_type BufferArr[1400];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct EapRequestMessage_tlv_struct EapRequestMessage_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct LinkStatus_tlv_struct
{
	UINT16 Type;
	UINT32 UpLinkSpeed;
	UINT32 DownLinkSpeed;
	UINT32 CenterFrequency;
	UINT8 TxPower;
	UINT8 RxRssi;
	UINT8 RxCinr;
	Uint8_type BSID[6];
	UINT8 LinkQuality;
	UINT16 Reserved;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct LinkStatus_tlv_struct LinkStatus_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct D2HChannelMask_tlv_struct
{
	UINT16 Type;
	UINT8 DataChannelSwitch;
	UINT8 DiagnosticsChannelSwitch;
	UINT16 Reserved;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct D2HChannelMask_tlv_struct D2HChannelMask_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct LockedToNSPNameInfo_tlv_struct
{
	UINT16 Type;
	UINT16 ActualLen;
	Uint8_type BufferArr[256];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct LockedToNSPNameInfo_tlv_struct LockedToNSPNameInfo_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct RFStatus_tlv_struct
{
	UINT16 Type;
	UINT8 SwRFSwitch;
	UINT8 HwRFSwitch;
	UINT16 Reserved;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct RFStatus_tlv_struct RFStatus_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct ScanResultList_tlv_struct
{
	UINT16 Type;
	UINT8 Rssi;
	UINT8 Cinr;
	Uint8_type BsIdmask[6];
	Uint8_type BsId[6];
	UINT16 ChannelId;
	UINT16 PreambleId;
	UINT8 LinkGrade;
	UINT8 LinkQuality;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct ScanResultList_tlv_struct ScanResultList_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct BEKKeyBuffer_tlv_struct
{
	UINT16 Type;
	Uint8_type BEKKeyBufferArr[16];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct BEKKeyBuffer_tlv_struct BEKKeyBuffer_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct MonitorFilterTable_tlv_struct
{
	UINT16 Type;
	Uint8_type FilterTable[256];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct MonitorFilterTable_tlv_struct MonitorFilterTable_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct PrivilegeKeyConfigComp_tlv_struct
{
	UINT16 Type;
	Uint8_type Key[4];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct PrivilegeKeyConfigComp_tlv_struct PrivilegeKeyConfigComp_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct LedBehaviorScheme_struct
{
	UINT8 Led0Scheme;
	UINT8 Led1Scheme;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct LedBehaviorScheme_struct LedBehaviorScheme_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct usrIndLedBlinkRate_struct
{
	UINT8 onPeriod;
	UINT8 offPeriod;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct usrIndLedBlinkRate_struct usrIndLedBlinkRate_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct usrIndPowerSaveInfo_struct
{
	usrIndLedBlinkRate_type ledBlinkRate;
	UINT8 powerSaveMode;
	UINT32 ledTimeInterval;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct usrIndPowerSaveInfo_struct usrIndPowerSaveInfo_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct LedOperationalConfigComp_tlv_struct
{
	UINT16 Type;
	UINT8 NvmOverride;
	LedBehaviorScheme_type ledBehavior[14];
	usrIndPowerSaveInfo_type powerSaveInfo;
	UINT8 numOfLeds;
	usrIndLedBlinkRate_type blinkingRate[13];
	UINT8 reserved;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct LedOperationalConfigComp_tlv_struct LedOperationalConfigComp_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct LimitMaxTxPowerConfigComp_tlv_struct
{
	UINT16 Type;
	UINT32 LimitMaxTxPower;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct LimitMaxTxPowerConfigComp_tlv_struct LimitMaxTxPowerConfigComp_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct IdleParametersConfigComp_tlv_struct
{
	UINT16 Type;
	UINT32 IdleTimeout;
	UINT32 IdlePagingInterval;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct IdleParametersConfigComp_tlv_struct IdleParametersConfigComp_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct IdleParameterTimeoutConfigComp_tlv_struct
{
	UINT16 Type;
	UINT32 IdleTimeout;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct IdleParameterTimeoutConfigComp_tlv_struct IdleParameterTimeoutConfigComp_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct IdleParameterPagingIntervalConfigComp_tlv_struct
{
	UINT16 Type;
	UINT32 PagingInterval;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct IdleParameterPagingIntervalConfigComp_tlv_struct IdleParameterPagingIntervalConfigComp_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct IdleParameterIdleEntrySuspendConfigComp_tlv_struct
{
	UINT16 Type;
	UINT32 IdleEntrySuspend;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct IdleParameterIdleEntrySuspendConfigComp_tlv_struct IdleParameterIdleEntrySuspendConfigComp_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct IdleParameterFullNeSuspendConfigComp_tlv_struct
{
	UINT16 Type;
	UINT32 FullNeSuspend;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct IdleParameterFullNeSuspendConfigComp_tlv_struct IdleParameterFullNeSuspendConfigComp_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct LinkDownTimerConfigComp_tlv_struct
{
	UINT16 Type;
	UINT32 LinkDown;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct LinkDownTimerConfigComp_tlv_struct LinkDownTimerConfigComp_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct ArqSupportConfigComp_tlv_struct
{
	UINT16 Type;
	UINT8 GeneralState;
	UINT8 Reserved1;
	UINT16 Reserved2;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct ArqSupportConfigComp_tlv_struct ArqSupportConfigComp_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct LoopBackConfigComp_tlv_struct
{
	UINT16 Type;
	UINT8 OperationMode;
	UINT8 Reserved1;
	UINT16 Reserved2;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct LoopBackConfigComp_tlv_struct LoopBackConfigComp_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct ResetOnAssertConfigComp_tlv_struct
{
	UINT16 Type;
	UINT8 GeneralState;
	UINT8 Reserved1;
	UINT16 Reserved2;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct ResetOnAssertConfigComp_tlv_struct ResetOnAssertConfigComp_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct WatchDogTimerConfigComp_tlv_struct
{
	UINT16 Type;
	UINT8 GeneralState;
	UINT8 Reserved1;
	UINT16 Reserved2;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct WatchDogTimerConfigComp_tlv_struct WatchDogTimerConfigComp_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct SlowClockConfigComp_tlv_struct
{
	UINT16 Type;
	UINT8 GeneralState;
	UINT8 Reserved1;
	UINT16 Reserved2;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct SlowClockConfigComp_tlv_struct SlowClockConfigComp_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct SelectivePLIParametersConfigComp_tlv_struct
{
	UINT16 Type;
	UINT8 EnableSelectivePLIs;
	UINT8 DelayedSelectivePLI;
	UINT8 ConsecutivePLIToReceive;
	UINT8 Reserved1;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct SelectivePLIParametersConfigComp_tlv_struct SelectivePLIParametersConfigComp_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct HarqParametersConfigComp_tlv_struct
{
	UINT16 Type;
	UINT8 HarqCategory;
	UINT8 Reserved1;
	UINT16 Reserved2;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct HarqParametersConfigComp_tlv_struct HarqParametersConfigComp_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct D2HDataFormatConfigComp_tlv_struct
{
	UINT16 Type;
	DataFormat DataFormatMem;
	UINT8 Reserved1;
	UINT16 Reserved2;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct D2HDataFormatConfigComp_tlv_struct D2HDataFormatConfigComp_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct DLHostReorderConfigComp_tlv_struct
{
	UINT16 Type;
	UINT8 DLHostReorder;
	UINT8 Reserved1;
	UINT16 Reserved2;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct DLHostReorderConfigComp_tlv_struct DLHostReorderConfigComp_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct PaddingPerCSConfigComp_tlv_struct
{
	UINT16 Type;
	UINT8 CSType;
	UINT8 PaddingSize;
	UINT16 Reserved;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct PaddingPerCSConfigComp_tlv_struct PaddingPerCSConfigComp_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct NSPIDList_tlv_struct
{
	UINT16 Type;
	UINT32 NspIdListLength;
	Uint8_type NspIdListData[512];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct NSPIDList_tlv_struct NSPIDList_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct NSPVerboseNameList_tlv_struct
{
	UINT16 Type;
	UINT32 NspVerboseListLength;
	Uint8_type NspVerboseListData[1024];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct NSPVerboseNameList_tlv_struct NSPVerboseNameList_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct Realm_tlv_struct
{
	UINT16 Type;
	UINT32 RealmLength;
	Uint8_type RealmData[512];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct Realm_tlv_struct Realm_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct CoexState_tlv_struct
{
	UINT16 Type;
	UINT32 State;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct CoexState_tlv_struct CoexState_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct EapKeyMsk_tlv_struct
{
	UINT16 Type;
	Uint8_type EapKeyMskArr[64];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct EapKeyMsk_tlv_struct EapKeyMsk_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct TraceSeverityTable_tlv_struct
{
	UINT16 Type;
	Uint8_type SeverityTable[256];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct TraceSeverityTable_tlv_struct TraceSeverityTable_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct BSID_tlv_struct
{
	UINT16 Type;
	Uint8_type FullBSID[6];
	UINT16 Reserved;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct BSID_tlv_struct BSID_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct NspChangeCount_tlv_struct
{
	UINT16 Type;
	UINT8 NspChangeCount;
	UINT8 Reserved1;
	UINT16 Reserved2;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct NspChangeCount_tlv_struct NspChangeCount_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct StatisticsCommon_tlv_struct
{
	UINT16 Type;
	UINT32 TotalRxBytes;
	UINT32 TotalTxBytes;
	UINT32 TotalRxPackets;
	UINT32 TotalTxPackets;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct StatisticsCommon_tlv_struct StatisticsCommon_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct VersionsStrings_tlv_struct
{
	UINT16 Type;
	UINT16 ActualLen;
	Uint8_type BufferArr[100];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct VersionsStrings_tlv_struct VersionsStrings_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct DeviceDetails_tlv_struct
{
	UINT16 Type;
	UINT32 ModelType;
	UINT32 ModelTypeStringLength;
	Uint8_type ModelTypeString[124];
	UINT32 ManufacturerId;
	UINT32 ManufacturerIdStringLength;
	Uint8_type ManufacturerIdString[124];
	UINT32 NvmProductStringLength;
	Uint8_type NvmProductString[124];
	Uint8_type Nonce[8];
	Uint8_type MacAddress[6];
	UINT16 Reserved2;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct DeviceDetails_tlv_struct DeviceDetails_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct OdmInformation_tlv_struct
{
	UINT16 Type;
	Uint8_type OdmInformation[108];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct OdmInformation_tlv_struct OdmInformation_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct NvmInformation_tlv_struct
{
	UINT16 Type;
	UINT16 GeneralImageVersion;
	UINT16 ContentVersion;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct NvmInformation_tlv_struct NvmInformation_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct NvmManufacturer_tlv_struct
{
	UINT16 Type;
	UINT32 NvmManufacturerIdStringLength;
	Uint8_type NvmManufacturerIdString[124];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct NvmManufacturer_tlv_struct NvmManufacturer_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct DevicePID_tlv_struct
{
	UINT16 Type;
	UINT16 PID;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct DevicePID_tlv_struct DevicePID_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct SPLockUnlockCodeReq_tlv_struct
{
	UINT16 Type;
	UINT16 ActualLen;
	Uint8_type BufferArr[32];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct SPLockUnlockCodeReq_tlv_struct SPLockUnlockCodeReq_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct EapResponseMessage_tlv_struct
{
	UINT16 Type;
	UINT16 ActualLen;
	Uint8_type BufferArr[1400];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct EapResponseMessage_tlv_struct EapResponseMessage_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct GetL4MVersion_struct
{
	L3L4Header_type header;
	L4MVersion_tlv_type L4MVersion;
	L4MVersion_tlv_type L4MProductionVersion;
	L4MVersion_tlv_type L4MDnDVersion;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct GetL4MVersion_struct GetL4MVersion_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct ReportKeyRequest_struct
{
	L3L4Header_type header;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct ReportKeyRequest_struct ReportKeyRequest_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct TLSOperationRequest_struct
{
	L3L4Header_type header;
	TLSOperationDescriptor_tlv_type Common;
	ExchangeBuffer_tlv_type ExchangeBuffer;
	AppOutputBuffer_tlv_type AppOutputBuffer;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct TLSOperationRequest_struct TLSOperationRequest_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct SetScanParameters_struct
{
	L3L4Header_type header;
	ChannelInfoArray_tlv_type ChannelInfoArray[32];
	Uint32_tlv_type ScanPolicy;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct SetScanParameters_struct SetScanParameters_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct Connect_struct
{
	L3L4Header_type header;
	BSCritieria_tlv_type BSCritieria;
	THCriteria_tlv_type THCriteria;
	Uint32_tlv_type ConnectionMode;
	ConnectFlags_tlv_type ConnectFlags;
	Uint32_tlv_type CoexPriority;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct Connect_struct Connect_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct MOC_Request_struct
{
	L3L4Header_type header;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct MOC_Request_struct MOC_Request_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct RfControl_struct
{
	L3L4Header_type header;
	Uint32_tlv_type RfOperation;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct RfControl_struct RfControl_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct ReportEapRestart_struct
{
	L3L4Header_type header;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct ReportEapRestart_struct ReportEapRestart_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct ReportEapRequest_struct
{
	L3L4Header_type header;
	EapRequestMessage_tlv_type EapRequestMessage;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct ReportEapRequest_struct ReportEapRequest_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct ReportRecentNbrHood_struct
{
	L3L4Header_type header;
	ChannelInfoArray_tlv_type ChannelInfoArray[33];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct ReportRecentNbrHood_struct ReportRecentNbrHood_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct GetLinkStatus_struct
{
	L3L4Header_type header;
	LinkStatus_tlv_type LinkStatus;
	ChannelInfoArray_tlv_type ChannelInfo;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct GetLinkStatus_struct GetLinkStatus_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct SetD2HChannelMask_struct
{
	L3L4Header_type header;
	D2HChannelMask_tlv_type D2HChannelMask;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct SetD2HChannelMask_struct SetD2HChannelMask_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct EnterPowerSaveCommand_struct
{
	L3L4Header_type header;
	Uint32_tlv_type WakeupMode;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct EnterPowerSaveCommand_struct EnterPowerSaveCommand_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct SPLockStatusInfo_struct
{
	L3L4Header_type header;
	Uint32_tlv_type SPLockStatus;
	LockedToNSPNameInfo_tlv_type LockedToNSPNameInfo;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct SPLockStatusInfo_struct SPLockStatusInfo_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct GetMediaStatus_struct
{
	L3L4Header_type header;
	Uint32_tlv_type MediaStatus;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct GetMediaStatus_struct GetMediaStatus_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct GetState_struct
{
	L3L4Header_type header;
	Uint32_tlv_type SystemState;
	Uint32_tlv_type ConnectProgress;
	RFStatus_tlv_type RFStatus;
	Uint32_tlv_type LastReason;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct GetState_struct GetState_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct GetScanResults_struct
{
	L3L4Header_type header;
	Uint32_tlv_type ScanStatus;
	ScanResultList_tlv_type ScanResultList_Get[33];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct GetScanResults_struct GetScanResults_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct ReportEMSKRelatedKeys_struct
{
	L3L4Header_type header;
	BEKKeyBuffer_tlv_type BEK;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct ReportEMSKRelatedKeys_struct ReportEMSKRelatedKeys_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct ReportScanResults_struct
{
	L3L4Header_type header;
	Uint32_tlv_type ScanStatus;
	ScanResultList_tlv_type ScanResultList_Report[33];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct ReportScanResults_struct ReportScanResults_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct SetMonitorFilterTable_struct
{
	L3L4Header_type header;
	MonitorFilterTable_tlv_type MonitorFilterTable;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct SetMonitorFilterTable_struct SetMonitorFilterTable_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct CmdCoexProcessEnd_struct
{
	L3L4Header_type header;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct CmdCoexProcessEnd_struct CmdCoexProcessEnd_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct GetD2HChannelMask_struct
{
	L3L4Header_type header;
	D2HChannelMask_tlv_type D2HChannelMask;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct GetD2HChannelMask_struct GetD2HChannelMask_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct SetPreInitConfiguration_struct
{
	L3L4Header_type header;
	PrivilegeKeyConfigComp_tlv_type PrivilegeKeyConfigComp;
	LedOperationalConfigComp_tlv_type LedOperationalConfigComp;
	LimitMaxTxPowerConfigComp_tlv_type LimitMaxTxPowerConfigComp;
	IdleParametersConfigComp_tlv_type IdleParametersConfigComp;
	IdleParameterTimeoutConfigComp_tlv_type IdleParameterTimeoutConfigComp;
	IdleParameterPagingIntervalConfigComp_tlv_type IdleParameterPagingIntervalConfigComp;
	IdleParameterIdleEntrySuspendConfigComp_tlv_type IdleParameterIdleEntrySuspendConfigComp;
	IdleParameterFullNeSuspendConfigComp_tlv_type IdleParameterFullNeSuspendConfigComp;
	LinkDownTimerConfigComp_tlv_type LinkDownTimerConfigComp;
	ArqSupportConfigComp_tlv_type ArqSupportConfigComp;
	LoopBackConfigComp_tlv_type LoopBackConfigComp;
	ResetOnAssertConfigComp_tlv_type ResetOnAssertConfigComp;
	WatchDogTimerConfigComp_tlv_type WatchDogTimerConfigComp;
	SlowClockConfigComp_tlv_type SlowClockConfigComp;
	SelectivePLIParametersConfigComp_tlv_type SelectivePLIParametersConfigComp;
	HarqParametersConfigComp_tlv_type HarqParametersConfigComp;
	D2HDataFormatConfigComp_tlv_type D2HDataFormatConfigComp;
	DLHostReorderConfigComp_tlv_type DLHostReorderConfigComp;
	PaddingPerCSConfigComp_tlv_type PaddingPerCSConfigComp;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct SetPreInitConfiguration_struct SetPreInitConfiguration_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct CheckL3L4InterfaceGET_struct
{
	L3L4Header_type header;
	Uint32_tlv_type value;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct CheckL3L4InterfaceGET_struct CheckL3L4InterfaceGET_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct ReportSII_struct
{
	L3L4Header_type header;
	NSPIDList_tlv_type NSPIDList;
	NSPVerboseNameList_tlv_type NSPVerboseNameList;
	Realm_tlv_type Realm;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct ReportSII_struct ReportSII_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct ScanCommand_struct
{
	L3L4Header_type header;
	Uint32_tlv_type DoScanCommand;
	Uint32_tlv_type CoexPriority;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct ScanCommand_struct ScanCommand_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct TerminateCommand_struct
{
	L3L4Header_type header;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct TerminateCommand_struct TerminateCommand_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct ReadyForPowerSave_struct
{
	L3L4Header_type header;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct ReadyForPowerSave_struct ReadyForPowerSave_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct Disconnect_struct
{
	L3L4Header_type header;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct Disconnect_struct Disconnect_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct SetEapSuccess_struct
{
	L3L4Header_type header;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct SetEapSuccess_struct SetEapSuccess_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct CmdCoexProcessStart_struct
{
	L3L4Header_type header;
	CoexState_tlv_type ProcessType;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct CmdCoexProcessStart_struct CmdCoexProcessStart_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct InitCommand_struct
{
	L3L4Header_type header;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct InitCommand_struct InitCommand_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct SetEapKey_struct
{
	L3L4Header_type header;
	Uint32_tlv_type EapKeyValid;
	EapKeyMsk_tlv_type EapKeyMsk;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct SetEapKey_struct SetEapKey_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct CheckL3L4InterfaceSET_struct
{
	L3L4Header_type header;
	Uint32_tlv_type value;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct CheckL3L4InterfaceSET_struct CheckL3L4InterfaceSET_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct MOC_Broadcast_struct
{
	L3L4Header_type header;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct MOC_Broadcast_struct MOC_Broadcast_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct SetCoexMode_struct
{
	L3L4Header_type header;
	Uint32_tlv_type CoexistenceModeType;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct SetCoexMode_struct SetCoexMode_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct SetTraceSeverityTable_struct
{
	L3L4Header_type header;
	TraceSeverityTable_tlv_type TraceSeverityTable;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct SetTraceSeverityTable_struct SetTraceSeverityTable_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct ReportBsInfo_struct
{
	L3L4Header_type header;
	BSID_tlv_type BSID;
	NspChangeCount_tlv_type NspChangeCount;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct ReportBsInfo_struct ReportBsInfo_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct SetEapFail_struct
{
	L3L4Header_type header;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct SetEapFail_struct SetEapFail_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct MOC_Response_struct
{
	L3L4Header_type header;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct MOC_Response_struct MOC_Response_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct GetStatistics_struct
{
	L3L4Header_type header;
	Uint32_tlv_type TimeStamp;
	StatisticsCommon_tlv_type StatisticsCommon;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct GetStatistics_struct GetStatistics_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct GetDeviceInfo_struct
{
	L3L4Header_type header;
	VersionsStrings_tlv_type VersionsStrings;
	DeviceDetails_tlv_type DeviceDetails;
	OdmInformation_tlv_type OdmInformation;
	NvmInformation_tlv_type NvmInformation;
	NvmManufacturer_tlv_type NvmManufacturer;
	DevicePID_tlv_type DevicePID;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct GetDeviceInfo_struct GetDeviceInfo_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct CmdMonitorControl_struct
{
	L3L4Header_type header;
	Uint32_tlv_type MonitorMode;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct CmdMonitorControl_struct CmdMonitorControl_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct CheckL3L4InterfaceREPORT_struct
{
	L3L4Header_type header;
	Uint32_tlv_type value;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct CheckL3L4InterfaceREPORT_struct CheckL3L4InterfaceREPORT_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct GetMonitorFilterTable_struct
{
	L3L4Header_type header;
	MonitorFilterTable_tlv_type MonitorFilterTable;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct GetMonitorFilterTable_struct GetMonitorFilterTable_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct GetTraceSeverityTable_struct
{
	L3L4Header_type header;
	TraceSeverityTable_tlv_type TraceSeverityTable;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct GetTraceSeverityTable_struct GetTraceSeverityTable_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct ResetDeviceCommand_struct
{
	L3L4Header_type header;
	Uint32_tlv_type ResetDevice;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct ResetDeviceCommand_struct ResetDeviceCommand_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct CheckL3L4InterfaceCMD_struct
{
	L3L4Header_type header;
	Uint32_tlv_type value;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct CheckL3L4InterfaceCMD_struct CheckL3L4InterfaceCMD_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct ReportState_struct
{
	L3L4Header_type header;
	Uint32_tlv_type ReportStateReason;
	Uint32_tlv_type SystemState;
	LinkStatus_tlv_type LinkStatus;
	Uint32_tlv_type MediaStatus;
	Uint32_tlv_type ConnectProgress;
	RFStatus_tlv_type RFStatus;
	ChannelInfoArray_tlv_type ChannelInfo;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct ReportState_struct ReportState_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct SPLockRequest_struct
{
	L3L4Header_type header;
	SPLockUnlockCodeReq_tlv_type SPLockUnlockCodeReq;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct SPLockRequest_struct SPLockRequest_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct DebugLoopback_struct
{
	L3L4Header_type header;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct DebugLoopback_struct DebugLoopback_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct ReportAltAccept_struct
{
	L3L4Header_type header;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct ReportAltAccept_struct ReportAltAccept_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct ModeOfOperationCommand_struct
{
	L3L4Header_type header;
	Uint32_tlv_type ModeOfOperation;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct ModeOfOperationCommand_struct ModeOfOperationCommand_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct SendEapResponse_struct
{
	L3L4Header_type header;
	EapResponseMessage_tlv_type EapResponseMessage;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct SendEapResponse_struct SendEapResponse_type;



#endif //_L4BUFMAN_L3L4STRUCTS_DESC_H
