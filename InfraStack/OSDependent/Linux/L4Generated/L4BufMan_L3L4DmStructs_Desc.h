
/****************************************************************************
*
* Auto generated file
* Version XXX
* Compliant with XXX.bm version XXX
* 11/19/2009 12:56:04 AM
*
*****************************************************************************/

#ifndef _L4BUFMAN_L3L4DMSTRUCTS_DESC_H
#define _L4BUFMAN_L3L4DMSTRUCTS_DESC_H


#include "TypesProxy.h"
#include "L3L4DmStructs.h"
#include "L4BufMan_L4Common_Desc.h"




#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct BSTComplete_struct
{
	UINT32 FrameNumber;
	UINT32 uSecInFrame;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct BSTComplete_struct BSTComplete_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct PowerCharacteristics_struct
{
	INT16 Total;
	UINT8 NumOfSubchannels;
	UINT8 AllocationType;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct PowerCharacteristics_struct PowerCharacteristics_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct PowerStatistics_struct
{
	PowerCharacteristics_type MaxPower;
	PowerCharacteristics_type MinPower;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct PowerStatistics_struct PowerStatistics_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct ULNoiseAndInterferenceLevel_struct
{
	UINT8 valid;
	UINT8 level;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct ULNoiseAndInterferenceLevel_struct ULNoiseAndInterferenceLevel_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct ULNoiseAndInterferenceRegions_struct
{
	ULNoiseAndInterferenceLevel_type cqiAckPeriodicRangingNI;
	ULNoiseAndInterferenceLevel_type puscNI;
	ULNoiseAndInterferenceLevel_type amcNI;
	ULNoiseAndInterferenceLevel_type periodicRangingNI;
	ULNoiseAndInterferenceLevel_type soundingNI;
	ULNoiseAndInterferenceLevel_type mimoNI;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct ULNoiseAndInterferenceRegions_struct ULNoiseAndInterferenceRegions_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct dmTpc_struct
{
	INT16 PowerPerToneCur;
	INT16 PowerPerToneAvg;
	UINT16 PathLoss;
	UINT16 Headroom;
	UINT16 Reserved;
	UINT8 powerControlMode;
	UINT8 isTx;
	PowerCharacteristics_type CurrentFrameTxPower;
	PowerStatistics_type ExtremePowerValues;
	INT16 offsetBSperSS;
	INT16 offsetSSperSS;
	ULNoiseAndInterferenceRegions_type ulNoiseAndInterferenceLevel;
	UINT16 LackOfHeadroomCounter;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct dmTpc_struct dmTpc_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct L3L4_L3MonitorGroupL1_DiagnosticsTpc_tlv_struct
{
	UINT16 Type;
	BSTComplete_type BST;
	dmTpc_type dmTpc;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct L3L4_L3MonitorGroupL1_DiagnosticsTpc_tlv_struct L3L4_L3MonitorGroupL1_DiagnosticsTpc_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct MapsStatistics_struct
{
	UINT32 FchRecievedOK;
	UINT32 FchFailures;
	UINT32 NormalDlMapRecievedOK;
	UINT32 NormalDlMapHcsError;
	UINT32 NormalDlMapCrcError;
	UINT32 NormalUlMapRecievedOK;
	UINT32 NormalUlMapHcsError;
	UINT32 NormalUlMapCrcError;
	UINT32 CompressedMapRecievedOK;
	UINT32 CompressedMapCrcError;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct MapsStatistics_struct MapsStatistics_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct L1Measurements_struct
{
	INT PreamblePCinr;
	INT PreamblePCinrAnt0;
	INT PreamblePCinrAnt1;
	INT PreamblePCinrStd;
	INT Rssi;
	INT RssiStd;
	INT MimoStbcPCinr;
	INT MimoStbcPCinrStd;
	INT MimoSmPCinr;
	INT MimoSmPCinrStd;
	INT MimoStbcECinr;
	INT MimoSmECinr;
	eRF_RX_ANT_MODE RxAntModeAutoDetect;
	UINT32 Reserved8;
	UINT32 Reserved16;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct L1Measurements_struct L1Measurements_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct dmPhyPerformance_struct
{
	MapsStatistics_type MapsStatistics;
	L1Measurements_type l1Measurements;
	UINT32 cqichCount;
	INT16 TemperatureInCelsius;
	eRF_RX_ANT_MODE RxAntMode;
	UINT8 Reserved_1;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct dmPhyPerformance_struct dmPhyPerformance_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct L3L4_L3MonitorGroupL1_DiagnosticsPerformance_tlv_struct
{
	UINT16 Type;
	BSTComplete_type BST;
	dmPhyPerformance_type dmPhyPerformance;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct L3L4_L3MonitorGroupL1_DiagnosticsPerformance_tlv_struct L3L4_L3MonitorGroupL1_DiagnosticsPerformance_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct TransitionGapsComp_struct
{
	UINT16 TTG;
	UINT16 RTG;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct TransitionGapsComp_struct TransitionGapsComp_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct dmPhyConfiguration_struct
{
	INT FrequencyOffsetInHz;
	UINT32 CenterFrequencyInKHz;
	TransitionGapsComp_type transitionGaps;
	UINT8 RecommendedMIMOMode;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct dmPhyConfiguration_struct dmPhyConfiguration_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct L3L4_L3MonitorGroupL1_DiagnosticsConfiguration_tlv_struct
{
	UINT16 Type;
	BSTComplete_type BST;
	dmPhyConfiguration_type dmPhyConfiguration;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct L3L4_L3MonitorGroupL1_DiagnosticsConfiguration_tlv_struct L3L4_L3MonitorGroupL1_DiagnosticsConfiguration_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct FchBuffer_struct
{
	UINT8 byte0;
	UINT8 byte1;
	UINT8 byte2;
	MonitorValidity validity;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct FchBuffer_struct FchBuffer_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct FrameRatio_struct
{
	UINT8 DlSize;
	UINT8 UlSize;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct FrameRatio_struct FrameRatio_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct FW_MON_TYPE_BASIC_STATUS_struct
{
	FchBuffer_type FCH;
	FrameRatio_type frameRatio;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct FW_MON_TYPE_BASIC_STATUS_struct FW_MON_TYPE_BASIC_STATUS_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct L3L4_L3MonitorGroupBASIC_STATUS_tlv_struct
{
	UINT16 Type;
	BSTComplete_type BST;
	FW_MON_TYPE_BASIC_STATUS_type FWMonitorGroupBasicStatus;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct L3L4_L3MonitorGroupBASIC_STATUS_tlv_struct L3L4_L3MonitorGroupBASIC_STATUS_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct FW_MON_TYPE_BURST_STATUS_struct
{
	UINT32 TotalDLPduCRCCount;
	UINT32 TotalDLPduCount;
	UINT32 UL_PDU_Size;
	UINT32 TotalULPDUSize;
	UINT32 TotalUlPduCount;
	UINT32 UL_SDU_Size;
	UINT32 TotalULSDUSize;
	UINT32 TotalUlSduCount;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct FW_MON_TYPE_BURST_STATUS_struct FW_MON_TYPE_BURST_STATUS_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct L3L4_L3MonitorGroupBURST_STATUS_tlv_struct
{
	UINT16 Type;
	BSTComplete_type BST;
	FW_MON_TYPE_BURST_STATUS_type FWMonitorGroupBurstStatus;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct L3L4_L3MonitorGroupBURST_STATUS_tlv_struct L3L4_L3MonitorGroupBURST_STATUS_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct PDUInfo_struct
{
	UINT32 numberOfTxedPDUs;
	UINT32 totalBytes;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct PDUInfo_struct PDUInfo_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct SDUInfo_struct
{
	UINT32 numberOfAgedSDUs;
	UINT32 totalBytes;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct SDUInfo_struct SDUInfo_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct PerCIN_xDUStatus_struct
{
	PDUInfo_type PDUInfo[16];
	SDUInfo_type SDUInfo[16];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct PerCIN_xDUStatus_struct PerCIN_xDUStatus_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct BWRInfo_struct
{
	UINT32 numberOfBWRs;
	UINT32 totalBytes;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct BWRInfo_struct BWRInfo_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct PerCIN_BWRStatus_struct
{
	BWRInfo_type AggregatedBWRInfo[16];
	BWRInfo_type IncrementalBWRInfo[16];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct PerCIN_BWRStatus_struct PerCIN_BWRStatus_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct VQInfo_struct
{
	UINT32 totalBytesPendingInQ;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct VQInfo_struct VQInfo_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct PerCIN_VQInfo_struct
{
	VQInfo_type currentVQInfo[16];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct PerCIN_VQInfo_struct PerCIN_VQInfo_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct PER_CIN_MonitorInfo_L2_struct
{
	PerCIN_xDUStatus_type perCIN_xDUStatus;
	PerCIN_BWRStatus_type perCIN_BWRStatus;
	PerCIN_VQInfo_type perCIN_VQInfo;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct PER_CIN_MonitorInfo_L2_struct PER_CIN_MonitorInfo_L2_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct L3L4_L3MonitorGroupPER_CIN_STATUS_tlv_struct
{
	UINT16 Type;
	BSTComplete_type BST;
	PER_CIN_MonitorInfo_L2_type Per_CIN_MonitorInfo_L2;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct L3L4_L3MonitorGroupPER_CIN_STATUS_tlv_struct L3L4_L3MonitorGroupPER_CIN_STATUS_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct Grant_Info_struct
{
	UINT32 TotalGrantsAmountInBytes;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct Grant_Info_struct Grant_Info_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct L2_MON_TYPE_SF_AND_QOS_FLOW_MNGMT_struct
{
	Grant_Info_type HARQBurst;
	Grant_Info_type NonHARQBurst;
	Grant_Info_type UIUC14Burst;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct L2_MON_TYPE_SF_AND_QOS_FLOW_MNGMT_struct L2_MON_TYPE_SF_AND_QOS_FLOW_MNGMT_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct L3L4_L3MonitorGroupSF_AND_QOS_FLOW_MNGMT_tlv_struct
{
	UINT16 Type;
	BSTComplete_type BST;
	L2_MON_TYPE_SF_AND_QOS_FLOW_MNGMT_type L2_MON_TYPE_SF_AND_QOS_FLOW_MNGMT;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct L3L4_L3MonitorGroupSF_AND_QOS_FLOW_MNGMT_tlv_struct L3L4_L3MonitorGroupSF_AND_QOS_FLOW_MNGMT_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct CQIParams_struct
{
	UINT32 FrameNumber;
	INT CQI_Measurement;
	UINT8 ChannelID;
	UINT8 IsMIMOReportFlag;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct CQIParams_struct CQIParams_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct L2_LAM_Events_MonitorInfo_struct
{
	CQIParams_type CQIParams;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct L2_LAM_Events_MonitorInfo_struct L2_LAM_Events_MonitorInfo_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct L3L4_L3MonitorGroupL2_LAM_Events_tlv_struct
{
	UINT16 Type;
	BSTComplete_type BST;
	L2_LAM_Events_MonitorInfo_type L2_LAM_Events_MonitorInfo;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct L3L4_L3MonitorGroupL2_LAM_Events_tlv_struct L3L4_L3MonitorGroupL2_LAM_Events_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct dmTpcEvents_struct
{
	UINT8 TPCModeChange;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct dmTpcEvents_struct dmTpcEvents_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct L3L4_L3MonitorGroupL1_DiagnosticsTpcEvents_tlv_struct
{
	UINT16 Type;
	BSTComplete_type BST;
	dmTpcEvents_type dmTpcEvents;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct L3L4_L3MonitorGroupL1_DiagnosticsTpcEvents_tlv_struct L3L4_L3MonitorGroupL1_DiagnosticsTpcEvents_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct dmL1NBSPSCANResult_struct
{
	UINT32 PHYLinkID;
	INT NeighbourBSPreambleCINRMeanReuse1;
	INT NeighbourBSPreambleCINRMeanReuse3;
	INT NeighbourBSPreambleRSSIMean;
	INT NeighbourBSTimeOffset;
	UINT8 IntraInterFAFlag;
	UINT8 MeasurementsValidityFlag;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct dmL1NBSPSCANResult_struct dmL1NBSPSCANResult_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct dmL1NBSPSCANResults_struct
{
	UINT8 numOfReportedBs;
	dmL1NBSPSCANResult_type NBSPSCANResult[33];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct dmL1NBSPSCANResults_struct dmL1NBSPSCANResults_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct L3L4_L3MonitorGroupL1_NBS_PSCAN_Results_tlv_struct
{
	UINT16 Type;
	BSTComplete_type BST;
	dmL1NBSPSCANResults_type dmL1NBSPSCANResults;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct L3L4_L3MonitorGroupL1_NBS_PSCAN_Results_tlv_struct L3L4_L3MonitorGroupL1_NBS_PSCAN_Results_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct RetransComp_struct
{
	UINT16 Retrans;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct RetransComp_struct RetransComp_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct HarqPerfComp_struct
{
	UINT16 NacksSent;
	UINT16 AcksSent;
	UINT16 DuplicatesRx;
	UINT16 BurstsTx;
	UINT16 BurstsRx;
	UINT16 Reserved;
	RetransComp_type RetransUL_Array[16];
	RetransComp_type RetransDL_Array[16];
	UINT16 DropHarqBurstCount;
	RetransComp_type AgingArrayUL[16];
	RetransComp_type AgingArrayDL[16];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct HarqPerfComp_struct HarqPerfComp_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct L3L4_DilloHarqPerfGroup_tlv_struct
{
	UINT16 Type;
	BSTComplete_type BST;
	HarqPerfComp_type HarqPerfComp;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct L3L4_DilloHarqPerfGroup_tlv_struct L3L4_DilloHarqPerfGroup_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct BurstsComp_struct
{
	UINT16 Bursts;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct BurstsComp_struct BurstsComp_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct BurstStatComp_struct
{
	BurstsComp_type RxBurstsPerMcs_Array[14];
	BurstsComp_type TxBurstsPerMcs_Array[10];
	UINT16 UL_BurstDataZone;
	UINT16 DL_BurstDataFecScheme;
	UINT16 UL_BurstDataFecScheme;
	UINT16 DL_BurstDataCid;
	UINT16 DL_BurstDataDiuc;
	UINT16 UL_BurstDataUiuc;
	UINT16 DL_BurstDataRepetition;
	UINT16 UL_BurstDataRepetition;
	UINT16 UL_TotalFec;
	UINT16 DL_TotalFec;
	UINT16 FecMode;
	UINT16 FecTypeID;
	UINT16 FecNumberOfError;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct BurstStatComp_struct BurstStatComp_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct L3L4_DilloBurstGroup_tlv_struct
{
	UINT16 Type;
	BSTComplete_type BST;
	BurstStatComp_type BurstStatComp;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct L3L4_DilloBurstGroup_tlv_struct L3L4_DilloBurstGroup_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct CdmaTxAttribComp_struct
{
	UINT16 FrameContainsCdmaTx;
	UINT16 FrameRefLow;
	UINT16 SymbolsRef;
	UINT16 SubChRef;
	UINT16 RangingCode;
	UINT16 Reserved;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct CdmaTxAttribComp_struct CdmaTxAttribComp_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct L3L4_DilloCdmaTxAttribGroup_tlv_struct
{
	UINT16 Type;
	BSTComplete_type BST;
	CdmaTxAttribComp_type CdmaTxAttribComp;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct L3L4_DilloCdmaTxAttribGroup_tlv_struct L3L4_DilloCdmaTxAttribGroup_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct CdmaAttributes_struct
{
	UINT8 xOffset;
	UINT8 yOffset;
	UINT8 codeNumber;
	UINT8 frameNumber;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct CdmaAttributes_struct CdmaAttributes_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct FW_L2_MON_TYPE_RANGING_PARAMETERS_struct
{
	CdmaAttributes_type DilloCdmaAttributes;
	ERangingMode RangingType;
	INT TimingAdjustment;
	INT PowerLevelAdjust;
	UINT32 InvitingRetries;
	UINT32 ContentionRetries;
	EDMRangingRspStatus rangingStatus;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct FW_L2_MON_TYPE_RANGING_PARAMETERS_struct FW_L2_MON_TYPE_RANGING_PARAMETERS_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_tlv_struct
{
	UINT16 Type;
	BSTComplete_type BST;
	FW_L2_MON_TYPE_RANGING_PARAMETERS_type FWL2MonitorGroupRangingTraceEvent;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_tlv_struct L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct FW_MON_TYPE_CDMA_BWR_struct
{
	UINT32 TotalNumberOfCdmaBwrInit;
	UINT32 TotalNumberOfTxCdmaBwr;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct FW_MON_TYPE_CDMA_BWR_struct FW_MON_TYPE_CDMA_BWR_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct L3L4_MonitorGroupEventCdmaBwr_tlv_struct
{
	UINT16 Type;
	BSTComplete_type BST;
	FW_MON_TYPE_CDMA_BWR_type FWCdmaBwrEvent;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct L3L4_MonitorGroupEventCdmaBwr_tlv_struct L3L4_MonitorGroupEventCdmaBwr_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct DilloSfAndQosPerformanceComp_struct
{
	UINT16 TotalBytesThroughputOtaDL;
	UINT16 TotalBytesThroughputOtaUL;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct DilloSfAndQosPerformanceComp_struct DilloSfAndQosPerformanceComp_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct L3L4_DilloSfAndQosPerformanceGroup_tlv_struct
{
	UINT16 Type;
	BSTComplete_type BST;
	DilloSfAndQosPerformanceComp_type DilloSfAndQosPerformanceComp;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct L3L4_DilloSfAndQosPerformanceGroup_tlv_struct L3L4_DilloSfAndQosPerformanceGroup_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct DilloSfAndQosFlowManagementComp_struct
{
	UINT16 GrantsReceiveSlots;
	UINT16 reserved;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct DilloSfAndQosFlowManagementComp_struct DilloSfAndQosFlowManagementComp_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct L3L4_DilloSfAndQosFlowManagementGroup_tlv_struct
{
	UINT16 Type;
	BSTComplete_type BST;
	DilloSfAndQosFlowManagementComp_type DilloSfAndQosFlowManagementComp;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct L3L4_DilloSfAndQosFlowManagementGroup_tlv_struct L3L4_DilloSfAndQosFlowManagementGroup_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct DilloPhyConfigurationComp_struct
{
	BurstsComp_type DlMcsAllocationTableNoneMimo[14];
	BurstsComp_type DlMcsAllocationTableMatrixA[14];
	BurstsComp_type DlMcsAllocationTableMatrixB[14];
	BurstsComp_type UlMcsAllocationTableNoneStc[10];
	BurstsComp_type UlMcsAllocationTableStc[10];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct DilloPhyConfigurationComp_struct DilloPhyConfigurationComp_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct L3L4_DilloPhyConfigurationGroup_tlv_struct
{
	UINT16 Type;
	BSTComplete_type BST;
	DilloPhyConfigurationComp_type DilloPhyConfigurationComp;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct L3L4_DilloPhyConfigurationGroup_tlv_struct L3L4_DilloPhyConfigurationGroup_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct DilloMapsComp_struct
{
	UINT16 TotalNumberOfMaps;
	UINT16 TotalBytesOfMaps;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct DilloMapsComp_struct DilloMapsComp_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct L3L4_DilloMapsGroup_tlv_struct
{
	UINT16 Type;
	BSTComplete_type BST;
	DilloMapsComp_type DilloMapsComp;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct L3L4_DilloMapsGroup_tlv_struct L3L4_DilloMapsGroup_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct BasicStatus_L3_struct
{
	UINT32 frequency;
	UINT32 ulCidNum;
	UINT32 dlCidNum;
	UINT8 preambleIndex;
	E_BandWidth bandWidth;
	Uint8_type bsId[6];
	Uint8_type macAddress[6];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct BasicStatus_L3_struct BasicStatus_L3_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct L3L4_BasicStatus_L3_tlv_struct
{
	UINT16 Type;
	BSTComplete_type BST;
	BasicStatus_L3_type BasicStatus_L3;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct L3L4_BasicStatus_L3_tlv_struct L3L4_BasicStatus_L3_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct BurstStatusPerConnection_struct
{
	UINT32 CID;
	UINT32 CIN;
	UINT32 totalUlSduRateLimitDropCount;
	UINT32 rateUlDropPackets;
	UINT32 totalDlReceivedPdu;
	UINT32 totalUlTransmittedSdu;
	UINT32 totalOfPduDlBytes;
	UINT32 totalOfSduDlBytes;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct BurstStatusPerConnection_struct BurstStatusPerConnection_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct BurstStatus_L3_struct
{
	UINT32 lastDlPduSize;
	UINT32 totalDlPdusSize;
	UINT32 dlPduCount;
	UINT32 lastDlSduSize;
	UINT32 totalDlSdusSize;
	UINT32 totalUlSduDropCounter;
	UINT32 totalDlPdusSizeInLastDlSubFrame;
	UINT32 numOfCidInfos;
	BurstStatusPerConnection_type burstStatusPerConnection[16];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct BurstStatus_L3_struct BurstStatus_L3_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct L3L4_BurstStatus_L3_tlv_struct
{
	UINT16 Type;
	BSTComplete_type BST;
	BurstStatus_L3_type BurstStatus_L3;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct L3L4_BurstStatus_L3_tlv_struct L3L4_BurstStatus_L3_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct CidInformation_struct
{
	UINT32 sfId;
	UINT32 maxSustainedTrafficRate;
	UINT32 maxTrafficBurst;
	UINT32 toleratedJitter;
	UINT32 maximumLatency;
	UINT32 unsolicitedGrantInterval;
	UINT32 minReservedTrafficRate;
	UINT16 cid;
	SFSchedulingType sfSchedulingType;
	E_QoSParamsSetType qosParamsSetType;
	UINT8 trafficPrio;
	E_SfSide sfSide;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct CidInformation_struct CidInformation_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct SF_QoS_MonitorInfo_L3_struct
{
	UINT8 numOfCidInfos;
	UINT32 numOfSfCreationSucess;
	UINT32 numOfSfCreationFailure;
	UINT32 numOfSfDeleted;
	CidInformation_type channels[20];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct SF_QoS_MonitorInfo_L3_struct SF_QoS_MonitorInfo_L3_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct L3L4_SF_QoS_MonitorInfo_L3_tlv_struct
{
	UINT16 Type;
	BSTComplete_type BST;
	SF_QoS_MonitorInfo_L3_type SF_QoS_MonitorInfo_L3;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct L3L4_SF_QoS_MonitorInfo_L3_tlv_struct L3L4_SF_QoS_MonitorInfo_L3_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct ArqInfo_struct
{
	UINT32 sfId;
	UINT32 arqWindowSize;
	UINT32 arqTransmitterDelay;
	UINT32 arqReceiverDelay;
	UINT32 arqBlockLifeTime;
	UINT32 arqSyncLossTimeout;
	UINT32 arqRxPurgeTimeout;
	UINT32 arqBlockSize;
	UINT32 t22;
	UINT8 arqEnable;
	UINT8 arqDeliverInOrder;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct ArqInfo_struct ArqInfo_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct Arq_MonitorInfo_L3_struct
{
	UINT8 numOfCidInfos;
	ArqInfo_type arqInfo[20];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct Arq_MonitorInfo_L3_struct Arq_MonitorInfo_L3_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct L3L4_Arq_MonitorInfo_L3_tlv_struct
{
	UINT16 Type;
	BSTComplete_type BST;
	Arq_MonitorInfo_L3_type Arq_MonitorInfo_L3;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct L3L4_Arq_MonitorInfo_L3_tlv_struct L3L4_Arq_MonitorInfo_L3_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct HarqInfo_struct
{
	UINT16 harqChannelMapping;
	UINT8 harqEnable;
	UINT8 harqisForReorder;
	UINT32 sfId;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct HarqInfo_struct HarqInfo_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct Harq_MonitorInfo_L3_struct
{
	UINT8 numOfCidInfos;
	HarqInfo_type harqInfo[20];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct Harq_MonitorInfo_L3_struct Harq_MonitorInfo_L3_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct L3L4_Harq_MonitorInfo_L3_tlv_struct
{
	UINT16 Type;
	BSTComplete_type BST;
	Harq_MonitorInfo_L3_type Harq_MonitorInfo_L3;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct L3L4_Harq_MonitorInfo_L3_tlv_struct L3L4_Harq_MonitorInfo_L3_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct MacState_L3_struct
{
	E_MacState state;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct MacState_L3_struct MacState_L3_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct L3L4_MacState_L3_tlv_struct
{
	UINT16 Type;
	BSTComplete_type BST;
	MacState_L3_type MacState_L3;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct L3L4_MacState_L3_tlv_struct L3L4_MacState_L3_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct MetricsInfo_struct
{
	INT16 rssiMean;
	INT16 cinrMean;
	UINT8 preambleId;
	UINT32 frequency;
	E_BandWidth bandWidth;
	Uint8_type bsId[6];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct MetricsInfo_struct MetricsInfo_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct NbrCellList_L3_struct
{
	UINT8 numOfIntraFASNbrs;
	UINT8 numOfInterFASNbrs;
	MetricsInfo_type intraFaNbrs[32];
	MetricsInfo_type interFaNbrs[32];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct NbrCellList_L3_struct NbrCellList_L3_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct L3L4_NbrCellList_L3_tlv_struct
{
	UINT16 Type;
	BSTComplete_type BST;
	NbrCellList_L3_type NbrCellList_L3;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct L3L4_NbrCellList_L3_tlv_struct L3L4_NbrCellList_L3_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct NwEntryMsgLatency_L3_struct
{
	UINT32 initRengLatency;
	UINT32 sbcLatency;
	UINT32 pkmLatency;
	UINT32 regLatency;
	UINT32 dsaLatency;
	UINT32 setuUpTime;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct NwEntryMsgLatency_L3_struct NwEntryMsgLatency_L3_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct L3L4_NwEntryMsgLatency_L3_tlv_struct
{
	UINT16 Type;
	BSTComplete_type BST;
	NwEntryMsgLatency_L3_type NwEntryMsgLatency_L3;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct L3L4_NwEntryMsgLatency_L3_tlv_struct L3L4_NwEntryMsgLatency_L3_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct DcdUcdTimeout_L3_struct
{
	UINT32 countDcdUcdTimeOut;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct DcdUcdTimeout_L3_struct DcdUcdTimeout_L3_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct L3L4_DcdUcdTimeout_L3_tlv_struct
{
	UINT16 Type;
	BSTComplete_type BST;
	DcdUcdTimeout_L3_type DcdUcdTimeout_L3;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct L3L4_DcdUcdTimeout_L3_tlv_struct L3L4_DcdUcdTimeout_L3_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct DSxTimers_L3_struct
{
	UINT16 t7Timeout;
	UINT16 t8Timeout;
	UINT16 t10Timeout;
	UINT8 dsxReqRetries;
	UINT8 dsxRspRetries;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct DSxTimers_L3_struct DSxTimers_L3_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct L3L4_DSxTimers_L3_tlv_struct
{
	UINT16 Type;
	BSTComplete_type BST;
	DSxTimers_L3_type DSxTimers_L3;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct L3L4_DSxTimers_L3_tlv_struct L3L4_DSxTimers_L3_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct Phy_L3_struct
{
	UINT32 preambleSearchTime;
	UINT32 numOfPreamble;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct Phy_L3_struct Phy_L3_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct L3L4_Phy_L3_tlv_struct
{
	UINT16 Type;
	BSTComplete_type BST;
	Phy_L3_type Phy_L3;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct L3L4_Phy_L3_tlv_struct L3L4_Phy_L3_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct LinkLossOccur_L3_struct
{
	UINT32 occurrenceTime;
	E_LinkLossReason LastLinkLossReason;
	Uint8_type bsId[6];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct LinkLossOccur_L3_struct LinkLossOccur_L3_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct L3L4_LinkLossOccur_L3_tlv_struct
{
	UINT16 Type;
	BSTComplete_type BST;
	LinkLossOccur_L3_type LinkLossOccur_L3;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct L3L4_LinkLossOccur_L3_tlv_struct L3L4_LinkLossOccur_L3_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct ChannelInfoArray_struct
{
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
typedef struct ChannelInfoArray_struct ChannelInfoArray_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct SetScanParam_struct
{
	UINT32 NumOfChannels;
	ChannelInfoArray_type Channels[32];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct SetScanParam_struct SetScanParam_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct MoniterScanConfig_struct
{
	SetScanParam_type SetScanParam;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct MoniterScanConfig_struct MoniterScanConfig_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct L3L4_Moniter_Scan_Config_tlv_struct
{
	UINT16 Type;
	BSTComplete_type BST;
	MoniterScanConfig_type MoniterScanConfig;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct L3L4_Moniter_Scan_Config_tlv_struct L3L4_Moniter_Scan_Config_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct DSPS_Management_MSG_struct
{
	UINT16 tlv_length;
	Uint8_type MngmntBufferRun[1500];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct DSPS_Management_MSG_struct DSPS_Management_MSG_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct L3L4_DSPS_Management_MSG_tlv_struct
{
	UINT16 Type;
	BSTComplete_type BST;
	DSPS_Management_MSG_type DSPS_Management_MSG;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct L3L4_DSPS_Management_MSG_tlv_struct L3L4_DSPS_Management_MSG_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct linkLossStatistics_L3_struct
{
	UINT32 occurrenceTime;
	UINT32 linkLossLatency;
	UINT32 HoRangingLatency;
	Uint8_type bsId[6];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct linkLossStatistics_L3_struct linkLossStatistics_L3_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct L3L4_linkLossStatistics_L3_tlv_struct
{
	UINT16 Type;
	BSTComplete_type BST;
	linkLossStatistics_L3_type linkLossStatistics_L3;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct L3L4_linkLossStatistics_L3_tlv_struct L3L4_linkLossStatistics_L3_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct BsInfo_struct
{
	Uint8_type bsId[6];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct BsInfo_struct BsInfo_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct CoordinateHo_L3_struct
{
	UINT8 numOfBsInHoReq;
	UINT8 numOfBsInHoRsp;
	UINT32 HoSuccessCounter;
	UINT32 HoFailCounter;
	UINT32 HoAttemptsCounter;
	UINT32 HoRejectsCounter;
	UINT32 HoNotRecommendedCounter;
	UINT32 numberOfTBSAttempted;
	UINT32 cancellationWithNormalOperation;
	UINT32 cancellationWithReentryProblem;
	UINT32 coordHoLatency;
	UINT32 cutOffLatency;
	E_HOStatus status;
	E_HOTypeId typeId;
	BsInfo_type hoReqBsList[10];
	BsInfo_type hoRspBsList[10];
	UINT32 HoTriggersCounter;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct CoordinateHo_L3_struct CoordinateHo_L3_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct L3L4_CoordinateHo_L3_tlv_struct
{
	UINT16 Type;
	BSTComplete_type BST;
	CoordinateHo_L3_type CoordinateHo_L3;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct L3L4_CoordinateHo_L3_tlv_struct L3L4_CoordinateHo_L3_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct BmBurstProfile_struct
{
	UINT8 intervalUsageCode;
	FecType fecType;
	FecRate fecRate;
	Modulation modulation;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct BmBurstProfile_struct BmBurstProfile_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct McsIndexTable_L3_struct
{
	UINT8 NumDlburstProfiles;
	UINT8 NumUlburstProfiles;
	BmBurstProfile_type DlburstProfiles[16];
	BmBurstProfile_type UlburstProfiles[16];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct McsIndexTable_L3_struct McsIndexTable_L3_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct L3L4_McsIndexTable_L3_tlv_struct
{
	UINT16 Type;
	BSTComplete_type BST;
	McsIndexTable_L3_type McsIndexTable_L3;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct L3L4_McsIndexTable_L3_tlv_struct L3L4_McsIndexTable_L3_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct MetricsScanInfo_struct
{
	UINT32 phyLinkId;
	UINT32 frequency;
	INT16 phyGrade;
	UINT8 preambleId;
	E_BandWidth bandWidth;
	ECellStatus bSValidityIndicator;
	Uint8_type bsId[6];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct MetricsScanInfo_struct MetricsScanInfo_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct ScanResult_L3_struct
{
	UINT8 numOfNbrs;
	MetricsScanInfo_type resultNbrs[33];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct ScanResult_L3_struct ScanResult_L3_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct L3L4_ScanResult_L3_tlv_struct
{
	UINT16 Type;
	BSTComplete_type BST;
	ScanResult_L3_type ScanResult_L3;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct L3L4_ScanResult_L3_tlv_struct L3L4_ScanResult_L3_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct ScanStatus_L3_struct
{
	UINT8 scanDuration;
	UINT8 scanIteration;
	UINT8 modeReport;
	UINT8 periodReport;
	UINT8 interleavingInterval;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct ScanStatus_L3_struct ScanStatus_L3_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct L3L4_ScanStatus_L3_tlv_struct
{
	UINT16 Type;
	BSTComplete_type BST;
	ScanStatus_L3_type ScanStatus_L3;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct L3L4_ScanStatus_L3_tlv_struct L3L4_ScanStatus_L3_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct ConnectionDropCount_L3_struct
{
	UINT32 counterConnectionDropEvent;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct ConnectionDropCount_L3_struct ConnectionDropCount_L3_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct L3L4_ConnectionDropCount_L3_tlv_struct
{
	UINT16 Type;
	BSTComplete_type BST;
	ConnectionDropCount_L3_type ConnectionDropCount_L3;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct L3L4_ConnectionDropCount_L3_tlv_struct L3L4_ConnectionDropCount_L3_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct IdleConfiguration_L3_struct
{
	UINT32 idleModeTimeout;
	UINT16 pagingCycleReq;
	UINT16 t45Timeout;
	UINT16 PagingGroupID;
	UINT16 PagingCycle;
	UINT16 PagingOffset;
	UINT8 RetainInfo;
	UINT8 dregReqRetries;
	UINT8 PagingIntervalLength;
	Uint8_type PagingControllerID[6];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct IdleConfiguration_L3_struct IdleConfiguration_L3_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct L3L4_IdleConfiguration_L3_tlv_struct
{
	UINT16 Type;
	BSTComplete_type BST;
	IdleConfiguration_L3_type IdleConfiguration_L3;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct L3L4_IdleConfiguration_L3_tlv_struct L3L4_IdleConfiguration_L3_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct IdlePerformance_L3_struct
{
	UINT32 counterInternalTimer;
	UINT32 counterNWInitiated;
	UINT32 counterGroupChange;
	UINT32 counterSecuredLu;
	UINT32 counterUnSecuredLu;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct IdlePerformance_L3_struct IdlePerformance_L3_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct L3L4_IdlePerformance_L3_tlv_struct
{
	UINT16 Type;
	BSTComplete_type BST;
	IdlePerformance_L3_type IdlePerformance_L3;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct L3L4_IdlePerformance_L3_tlv_struct L3L4_IdlePerformance_L3_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct ArqRxPerformance_struct
{
	UINT32 CID;
	UINT32 CIN;
	UINT32 numOfDuplicateReceivedBlocks;
	UINT32 numOfPurgeTimeouts;
	UINT32 numOfBlocksLostDueToRxPurgeTimout;
	UINT32 totalNumOfAcksTxd;
	UINT32 numOfRxArqResetsReceived;
	UINT32 numOfRxArqResetsInitiated;
	UINT32 numOfArqDiscardsReceived;
	UINT32 rxThroughput;
	UINT32 numOfPduLostDueToNoFreeSpaceInReceiver;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct ArqRxPerformance_struct ArqRxPerformance_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct Arq_MonitorRxPerformance_L3_struct
{
	UINT32 arqResetPerformed;
	UINT32 numOfCidPerformance;
	ArqRxPerformance_type arqRxPerformance[16];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct Arq_MonitorRxPerformance_L3_struct Arq_MonitorRxPerformance_L3_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct L3L4_Arq_MonitorRxPerformance_L3_tlv_struct
{
	UINT16 Type;
	BSTComplete_type BST;
	Arq_MonitorRxPerformance_L3_type Arq_MonitorRxPerformance_L3;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct L3L4_Arq_MonitorRxPerformance_L3_tlv_struct L3L4_Arq_MonitorRxPerformance_L3_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct ArqTxPerformance_struct
{
	UINT32 CID;
	UINT32 CIN;
	UINT32 numOfRetransmittedArqBlocksTotalUL;
	UINT32 numOfRetransmittedBlocksUL;
	UINT32 numOfBLTs;
	UINT32 numOfBlocksLostDueToArqBLT;
	UINT32 totalNumOfAcksReceived;
	UINT32 numOfTxArqResetsReceived;
	UINT32 numOfTxArqResetsInitiated;
	UINT32 numOfArqDiscardsTxd;
	UINT32 txThroughput;
	UINT32 numOfSduLostDueToNoFreeSpaceInTransmitter;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct ArqTxPerformance_struct ArqTxPerformance_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct Arq_MonitorTxPerformance_L3_struct
{
	UINT32 numOfCidPerformance;
	ArqTxPerformance_type arqTxPerformance[16];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct Arq_MonitorTxPerformance_L3_struct Arq_MonitorTxPerformance_L3_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct L3L4_Arq_MonitorTxPerformance_L3_tlv_struct
{
	UINT16 Type;
	BSTComplete_type BST;
	Arq_MonitorTxPerformance_L3_type Arq_MonitorTxPerformance_L3;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct L3L4_Arq_MonitorTxPerformance_L3_tlv_struct L3L4_Arq_MonitorTxPerformance_L3_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct SfPeformancePerConnection_struct
{
	UINT32 CID;
	UINT32 CIN;
	UINT32 ulIpThroughput;
	UINT32 dlIpThroughput;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct SfPeformancePerConnection_struct SfPeformancePerConnection_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct SfPerformance_L3_struct
{
	UINT32 numOfCidInfos;
	SfPeformancePerConnection_type SfPeformancePerConnection[16];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct SfPerformance_L3_struct SfPerformance_L3_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct L3L4_MonitorSfPerformance_L3_tlv_struct
{
	UINT16 Type;
	BSTComplete_type BST;
	SfPerformance_L3_type SfPerformance_L3;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct L3L4_MonitorSfPerformance_L3_tlv_struct L3L4_MonitorSfPerformance_L3_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct AvailableNSPsIdlist_struct
{
	UINT32 NumOfNSPs;
	Uint32_type NSPID[10];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct AvailableNSPsIdlist_struct AvailableNSPsIdlist_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct bsIDMember_struct
{
	Uint8_type bsID[6];
	UINT16 Reserved_2;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct bsIDMember_struct bsIDMember_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct bsIDmaskMember_struct
{
	Uint8_type bsIDmask[6];
	UINT16 Reserved_2;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct bsIDmaskMember_struct bsIDmaskMember_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct FullBSID_struct
{
	bsIDMember_type bsID;
	bsIDmaskMember_type bsIDmask;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct FullBSID_struct FullBSID_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct FullBSIDArr_struct
{
	UINT32 NumOfBSIDs;
	FullBSID_type FullBSID[10];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct FullBSIDArr_struct FullBSIDArr_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct MonitorScanResult_struct
{
	AvailableNSPsIdlist_type AvailableNSPsIdlist;
	FullBSIDArr_type FullBSIDArr;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct MonitorScanResult_struct MonitorScanResult_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct L3L4_Monitor_Scan_Result_tlv_struct
{
	UINT16 Type;
	BSTComplete_type BST;
	MonitorScanResult_type MonitorScanResult;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct L3L4_Monitor_Scan_Result_tlv_struct L3L4_Monitor_Scan_Result_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct Time_struct
{
	UINT16 wHour;
	UINT16 wMinute;
	UINT16 wSecond;
	UINT16 wMilliseconds;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct Time_struct Time_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct MonitorScanInd_struct
{
	BM_StartEndInd ScanStartEndInd;
	Time_type Time;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct MonitorScanInd_struct MonitorScanInd_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct L3L4_Monitor_Scan_Ind_tlv_struct
{
	UINT16 Type;
	BSTComplete_type BST;
	MonitorScanInd_type MonitorScanInd;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct L3L4_Monitor_Scan_Ind_tlv_struct L3L4_Monitor_Scan_Ind_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct MonitorOMASession_struct
{
	BME_OMAStatus OMAStatusInd;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct MonitorOMASession_struct MonitorOMASession_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct L3L4_Monitor_OMA_Session_tlv_struct
{
	UINT16 Type;
	BSTComplete_type BST;
	MonitorOMASession_type MonitorOMASession;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct L3L4_Monitor_OMA_Session_tlv_struct L3L4_Monitor_OMA_Session_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct BufferString_struct
{
	UINT8 BufferByte;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct BufferString_struct BufferString_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct operatorNameMember_struct
{
	BufferString_type operatorName[100];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct operatorNameMember_struct operatorNameMember_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct EapIdMember_struct
{
	BufferString_type EapId[100];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct EapIdMember_struct EapIdMember_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct provisionedPseudoIdMember_struct
{
	BufferString_type provisionedPseudoId[100];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct provisionedPseudoIdMember_struct provisionedPseudoIdMember_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct EapPasswordMember_struct
{
	BufferString_type EapPassword[32];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct EapPasswordMember_struct EapPasswordMember_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct RealmMember_struct
{
	BufferString_type Realm[100];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct RealmMember_struct RealmMember_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct EapMember_struct
{
	UINT32 usePrivacy;
	UINT32 vendorId;
	UINT32 vendorType;
	BM_EAPType EAPMethod;
	EapIdMember_type EapId;
	provisionedPseudoIdMember_type provisionedPseudoId;
	EapPasswordMember_type EapPassword;
	RealmMember_type Realm;
	BM_EAPType encaps;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct EapMember_struct EapMember_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct Eaps_struct
{
	UINT32 NumOfEaps;
	EapMember_type EapList[70];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct Eaps_struct Eaps_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct NapMember_struct
{
	Uint8_type napID[3];
	UINT8 Reserved_1;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct NapMember_struct NapMember_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct CaplNapMember_struct
{
	UINT32 priority;
	NapMember_type NapMember;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct CaplNapMember_struct CaplNapMember_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct CaplMember_struct
{
	UINT32 NumOfNaps;
	CaplNapMember_type CaplNapList[70];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct CaplMember_struct CaplMember_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct RoamingPartnerInfo_struct
{
	UINT32 vNspID;
	UINT32 priority;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct RoamingPartnerInfo_struct RoamingPartnerInfo_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct RaplMember_struct
{
	UINT32 NumOfRoamingPartners;
	RoamingPartnerInfo_type RaplList[70];
	BME_Any Any;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct RaplMember_struct RaplMember_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct MonitorOperator_struct
{
	operatorNameMember_type operatorName;
	UINT32 pollingInterval;
	Eaps_type Eaps;
	CaplMember_type Capls;
	RaplMember_type Rapls;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct MonitorOperator_struct MonitorOperator_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct L3L4_Monitor_Operator_tlv_struct
{
	UINT16 Type;
	BSTComplete_type BST;
	MonitorOperator_type MonitorOperator;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct L3L4_Monitor_Operator_tlv_struct L3L4_Monitor_Operator_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct manufacturerMember_struct
{
	BufferString_type manufacturer[64];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct manufacturerMember_struct manufacturerMember_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct modelMember_struct
{
	BufferString_type model[64];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct modelMember_struct modelMember_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct devIDMember_struct
{
	BufferString_type devID[64];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct devIDMember_struct devIDMember_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct DeviceInfoMember_struct
{
	manufacturerMember_type manufacturer;
	modelMember_type model;
	devIDMember_type devID;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct DeviceInfoMember_struct DeviceInfoMember_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct devTypeMember_struct
{
	BufferString_type devType[64];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct devTypeMember_struct devTypeMember_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct fwVersionMember_struct
{
	BufferString_type fwVersion[64];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct fwVersionMember_struct fwVersionMember_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct swVersionMember_struct
{
	BufferString_type swVersion[64];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct swVersionMember_struct swVersionMember_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct hwVersionMember_struct
{
	BufferString_type hwVersion[64];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct hwVersionMember_struct hwVersionMember_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct DeviceDetailsMember_struct
{
	devTypeMember_type devType;
	fwVersionMember_type fwVersion;
	swVersionMember_type swVersion;
	hwVersionMember_type hwVersion;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct DeviceDetailsMember_struct DeviceDetailsMember_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct MonitorOMAParams_struct
{
	DeviceInfoMember_type DeviceInfo;
	DeviceDetailsMember_type DeviceDetails;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct MonitorOMAParams_struct MonitorOMAParams_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct L3L4_Monitor_OMAParams_tlv_struct
{
	UINT16 Type;
	BSTComplete_type BST;
	MonitorOMAParams_type MonitorOMAParams;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct L3L4_Monitor_OMAParams_tlv_struct L3L4_Monitor_OMAParams_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct macAddressMember_struct
{
	BufferString_type macAddress[64];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct macAddressMember_struct macAddressMember_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct lockMember_struct
{
	BufferString_type lockMem[176];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct lockMember_struct lockMember_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct SpLockMember_struct
{
	UINT32 lockStatus;
	operatorNameMember_type operatorName;
	lockMember_type lockMem;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct SpLockMember_struct SpLockMember_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct WmxRadioModuleMember_struct
{
	fwVersionMember_type fwVersion;
	swVersionMember_type swVersion;
	hwVersionMember_type hwVersion;
	manufacturerMember_type manufacturer;
	modelMember_type model;
	macAddressMember_type macAddress;
	SpLockMember_type SpLock;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct WmxRadioModuleMember_struct WmxRadioModuleMember_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct RadioModuleMember_struct
{
	UINT32 LenOfRadioModule;
	WmxRadioModuleMember_type WmxRadioModuleList[5];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct RadioModuleMember_struct RadioModuleMember_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct staticTermEquipMember_struct
{
	fwVersionMember_type fwVersion;
	swVersionMember_type swVersion;
	hwVersionMember_type hwVersion;
	manufacturerMember_type manufacturer;
	modelMember_type model;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct staticTermEquipMember_struct staticTermEquipMember_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct TerminalEquipmentMember_struct
{
	devTypeMember_type devType;
	devIDMember_type devID;
	staticTermEquipMember_type staticTermEquip;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct TerminalEquipmentMember_struct TerminalEquipmentMember_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct MonitorOMAWimaxParams_struct
{
	RadioModuleMember_type RadioModule;
	TerminalEquipmentMember_type TerminalEquipment;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct MonitorOMAWimaxParams_struct MonitorOMAWimaxParams_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct L3L4_Monitor_OMA_WiMAX_Params_tlv_struct
{
	UINT16 Type;
	BSTComplete_type BST;
	MonitorOMAWimaxParams_type MonitorOMAWimaxParams;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct L3L4_Monitor_OMA_WiMAX_Params_tlv_struct L3L4_Monitor_OMA_WiMAX_Params_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct pkgNameMember_struct
{
	BufferString_type pkgName[50];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct pkgNameMember_struct pkgNameMember_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct pkgVersionMember_struct
{
	BufferString_type pkgVersion[50];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct pkgVersionMember_struct pkgVersionMember_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct downloadPkgURLMember_struct
{
	BufferString_type downloadPkgURL[260];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct downloadPkgURLMember_struct downloadPkgURLMember_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct downloadAndUpdatePkgURLMember_struct
{
	BufferString_type downloadAndUpdatePkgURL[260];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct downloadAndUpdatePkgURLMember_struct downloadAndUpdatePkgURLMember_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct FUMOMember_struct
{
	pkgNameMember_type pkgName;
	pkgVersionMember_type pkgVersion;
	downloadPkgURLMember_type downloadPkgURL;
	downloadAndUpdatePkgURLMember_type downloadAndUpdatePkgURL;
	DOWNLOAD_STATE state;
	UINT32 fIsAllocated;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct FUMOMember_struct FUMOMember_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct MonitorOMAFumoParams_struct
{
	FUMOMember_type FUMO;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct MonitorOMAFumoParams_struct MonitorOMAFumoParams_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct L3L4_Monitor_OMA_FUMO_Params_tlv_struct
{
	UINT16 Type;
	BSTComplete_type BST;
	MonitorOMAFumoParams_type MonitorOMAFumoParams;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct L3L4_Monitor_OMA_FUMO_Params_tlv_struct L3L4_Monitor_OMA_FUMO_Params_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct MonitorNAI_struct
{
	UINT32 NAISize;
	BufferString_type NAI[356];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct MonitorNAI_struct MonitorNAI_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct L3L4_Monitor_NAI_tlv_struct
{
	UINT16 Type;
	BSTComplete_type BST;
	MonitorNAI_type MonitorNAI;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct L3L4_Monitor_NAI_tlv_struct L3L4_Monitor_NAI_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct MonitorActivationStatusChange_struct
{
	UINT32 ActivationStatusInd;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct MonitorActivationStatusChange_struct MonitorActivationStatusChange_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct L3L4_Monitor_ActivationStatusChange_tlv_struct
{
	UINT16 Type;
	BSTComplete_type BST;
	MonitorActivationStatusChange_type MonitorActivationStatusChange;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct L3L4_Monitor_ActivationStatusChange_tlv_struct L3L4_Monitor_ActivationStatusChange_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct PreamblesMember_struct
{
	Uint8_type Preambles[15];
	UINT8 Reserved_1;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct PreamblesMember_struct PreamblesMember_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct ChannelMember_struct
{
	UINT32 frequency;
	BME_BW bw;
	BME_FFT fft;
	PreamblesMember_type Preambles;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct ChannelMember_struct ChannelMember_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct ChannelInfoArr_struct
{
	UINT32 NumOfChannels;
	ChannelMember_type Channels[500];
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct ChannelInfoArr_struct ChannelInfoArr_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct MonitorMCP_struct
{
	BME_LinkLossInd LinkLossInd;
	ChannelInfoArr_type ChannelInfoArray;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct MonitorMCP_struct MonitorMCP_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct L3L4_Monitor_MCP_tlv_struct
{
	UINT16 Type;
	BSTComplete_type BST;
	MonitorMCP_type MonitorMCP;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct L3L4_Monitor_MCP_tlv_struct L3L4_Monitor_MCP_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct MonitorInstallationInd_struct
{
	BME_MonitorInstallingInd MonitorInstallingInd;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct MonitorInstallationInd_struct MonitorInstallationInd_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct L3L4_Monitor_Installation_Ind_tlv_struct
{
	UINT16 Type;
	BSTComplete_type BST;
	MonitorInstallationInd_type MonitorInstallationInd;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct L3L4_Monitor_Installation_Ind_tlv_struct L3L4_Monitor_Installation_Ind_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct MonitorRecentDiscoverNap_struct
{
	NapMember_type NapMember;
	ChannelInfoArr_type ChannelInfoArray;
	bsIDMember_type bsID;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct MonitorRecentDiscoverNap_struct MonitorRecentDiscoverNap_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct L3L4_Monitor_Recent_Discover_Nap_tlv_struct
{
	UINT16 Type;
	BSTComplete_type BST;
	MonitorRecentDiscoverNap_type MonitorRecentDiscoverNap;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct L3L4_Monitor_Recent_Discover_Nap_tlv_struct L3L4_Monitor_Recent_Discover_Nap_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct MonitorSelectedChannel_struct
{
	ChannelInfoArr_type ChannelInfoArray;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct MonitorSelectedChannel_struct MonitorSelectedChannel_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct L3L4_Monitor_Selected_Channel_tlv_struct
{
	UINT16 Type;
	BSTComplete_type BST;
	MonitorSelectedChannel_type MonitorSelectedChannel;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct L3L4_Monitor_Selected_Channel_tlv_struct L3L4_Monitor_Selected_Channel_tlv_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct MonitorBuffer_struct
{
	L3L4Header_type header;
	L3L4_L3MonitorGroupL1_DiagnosticsTpc_tlv_type L3L4_L3MonitorGroupL1_DiagnosticsTpc;
	L3L4_L3MonitorGroupL1_DiagnosticsPerformance_tlv_type L3L4_L3MonitorGroupL1_DiagnosticsPerformance;
	L3L4_L3MonitorGroupL1_DiagnosticsConfiguration_tlv_type L3L4_L3MonitorGroupL1_DiagnosticsConfiguration;
	L3L4_L3MonitorGroupBASIC_STATUS_tlv_type L3L4_L3MonitorGroupBASIC_STATUS;
	L3L4_L3MonitorGroupBURST_STATUS_tlv_type L3L4_L3MonitorGroupBURST_STATUS;
	L3L4_L3MonitorGroupPER_CIN_STATUS_tlv_type L3L4_L3MonitorGroupPER_CIN_STATUS;
	L3L4_L3MonitorGroupSF_AND_QOS_FLOW_MNGMT_tlv_type L3L4_L3MonitorGroupSF_AND_QOS_FLOW_MNGMT;
	L3L4_L3MonitorGroupL2_LAM_Events_tlv_type L3L4_L3MonitorGroupL2_LAM_Events;
	L3L4_L3MonitorGroupL1_DiagnosticsTpcEvents_tlv_type L3L4_L3MonitorGroupL1_DiagnosticsTpcEvents;
	L3L4_L3MonitorGroupL1_NBS_PSCAN_Results_tlv_type L3L4_L3MonitorGroupL1_NBS_PSCAN_Results;
	L3L4_DilloHarqPerfGroup_tlv_type L3L4_DilloHarqPerfGroup;
	L3L4_DilloBurstGroup_tlv_type L3L4_DilloBurstGroup;
	L3L4_DilloCdmaTxAttribGroup_tlv_type L3L4_MonitorGroupEventCdmaTxAttrib;
	L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_tlv_type L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS;
	L3L4_MonitorGroupEventCdmaBwr_tlv_type L3L4_MonitorGroupEventCdmaBwr;
	L3L4_DilloSfAndQosPerformanceGroup_tlv_type L3L4_DilloSfAndQosPerformanceGroup;
	L3L4_DilloSfAndQosFlowManagementGroup_tlv_type L3L4_DilloSfAndQosFlowManagementGroup;
	L3L4_DilloPhyConfigurationGroup_tlv_type L3L4_DilloPhyConfigurationGroup;
	L3L4_DilloMapsGroup_tlv_type L3L4_DilloMapsGroup;
	L3L4_BasicStatus_L3_tlv_type L3L4_BasicStatus_L3;
	L3L4_BurstStatus_L3_tlv_type L3L4_BurstStatus_L3;
	L3L4_SF_QoS_MonitorInfo_L3_tlv_type L3L4_SF_QoS_MonitorInfo_L3;
	L3L4_Arq_MonitorInfo_L3_tlv_type L3L4_Arq_MonitorInfo_L3;
	L3L4_Harq_MonitorInfo_L3_tlv_type L3L4_Harq_MonitorInfo_L3;
	L3L4_MacState_L3_tlv_type L3L4_MacState_L3[3];
	L3L4_NbrCellList_L3_tlv_type L3L4_NbrCellList_L3;
	L3L4_NwEntryMsgLatency_L3_tlv_type L3L4_NwEntryMsgLatency_L3;
	L3L4_DcdUcdTimeout_L3_tlv_type L3L4_DcdUcdTimeout_L3;
	L3L4_DSxTimers_L3_tlv_type L3L4_DSxTimers_L3;
	L3L4_Phy_L3_tlv_type L3L4_Phy_L3;
	L3L4_LinkLossOccur_L3_tlv_type L3L4_LinkLossOccur_L3[5];
	L3L4_Moniter_Scan_Config_tlv_type L3L4_Moniter_Scan_Config;
	L3L4_DSPS_Management_MSG_tlv_type L3L4_DSPS_Management_MSG[10];
	L3L4_linkLossStatistics_L3_tlv_type L3L4_linkLossStatistics_L3;
	L3L4_CoordinateHo_L3_tlv_type L3L4_CoordinateHo_L3;
	L3L4_McsIndexTable_L3_tlv_type L3L4_McsIndexTable_L3;
	L3L4_ScanResult_L3_tlv_type L3L4_ScanResult_L3;
	L3L4_ScanStatus_L3_tlv_type L3L4_ScanStatus_L3;
	L3L4_ConnectionDropCount_L3_tlv_type L3L4_ConnectionDropCount_L3;
	L3L4_IdleConfiguration_L3_tlv_type L3L4_IdleConfiguration_L3;
	L3L4_IdlePerformance_L3_tlv_type L3L4_IdlePerformance_L3;
	L3L4_Arq_MonitorRxPerformance_L3_tlv_type L3L4_Arq_MonitorRxPerformance_L3;
	L3L4_Arq_MonitorTxPerformance_L3_tlv_type L3L4_Arq_MonitorTxPerformance_L3;
	L3L4_MonitorSfPerformance_L3_tlv_type L3L4_MonitorSfPerformance_L3;
	L3L4_Monitor_Scan_Result_tlv_type L3L4_Monitor_Scan_Result;
	L3L4_Monitor_Scan_Ind_tlv_type L3L4_Monitor_Scan_Ind;
	L3L4_Monitor_OMA_Session_tlv_type L3L4_Monitor_OMA_Session;
	L3L4_Monitor_Operator_tlv_type L3L4_Monitor_Operator;
	L3L4_Monitor_OMAParams_tlv_type L3L4_Monitor_OMAParams;
	L3L4_Monitor_OMA_WiMAX_Params_tlv_type L3L4_Monitor_OMA_WiMAX_Params;
	L3L4_Monitor_OMA_FUMO_Params_tlv_type L3L4_Monitor_OMA_FUMO_Params;
	L3L4_Monitor_NAI_tlv_type L3L4_Monitor_NAI;
	L3L4_Monitor_ActivationStatusChange_tlv_type L3L4_Monitor_ActivationStatusChange;
	L3L4_Monitor_MCP_tlv_type L3L4_Monitor_MCP;
	L3L4_Monitor_Installation_Ind_tlv_type L3L4_Monitor_Installation_Ind;
	L3L4_Monitor_Recent_Discover_Nap_tlv_type L3L4_Monitor_Recent_Discover_Nap;
	L3L4_Monitor_Selected_Channel_tlv_type L3L4_Monitor_Selected_Channel;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct MonitorBuffer_struct MonitorBuffer_type;



#endif //_L4BUFMAN_L3L4DMSTRUCTS_DESC_H
