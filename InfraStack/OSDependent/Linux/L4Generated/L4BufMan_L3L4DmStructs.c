
/****************************************************************************
*
* Auto generated file
* Version XXX
* Compliant with XXX.bm version XXX
* 11/19/2009 12:56:04 AM
*
*****************************************************************************/


#include "L4BufMan_L3L4DmStructs.h"
#include "L3L4DmStructs.h"





//
// MonitorBuffer
//
L4BUFMAN_Status_t L4BM_Get_MonitorBuffer(MonitorBuffer_type* pMsg, UINT8* buf)
{
	PVOID base_ptr = buf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE, i0 = 0, type = 0;


	L4BM_Init_MonitorBuffer(pMsg);
	BM_MonitorBuffer_Header_Version_GET( base_ptr, pMsg->header.Version );
	BM_MonitorBuffer_Header_Accessibility_GET( base_ptr, pMsg->header.Accessibility );
	BM_MonitorBuffer_Header_Status_GET( base_ptr, pMsg->header.Status );
	BM_MonitorBuffer_Header_Length_GET( base_ptr, listSize );

	if( (INT16)listSize < 0 )
	{
		return L4BUFMAN_ST_FAIL;
	}
	if( (INT16)listSize > 0 )
	{
		UINT32 L3L4_MacState_L3_index = 0;
		UINT32 L3L4_LinkLossOccur_L3_index = 0;
		UINT32 L3L4_DSPS_Management_MSG_index = 0;

		BM_MonitorBuffer_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );

		while( (INT16)listSize > 0 )
		{
			BM_MonitorBuffer_List_GET_TYPE( cur_ptr, cur_bitoff, type );
			BM_MonitorBuffer_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, length, err );
			length -= 4;
			if( type == 4053 )
			{
				pMsg->L3L4_L3MonitorGroupL1_DiagnosticsTpc.Type = (UINT16)type;
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsTpc.BST.FrameNumber );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsTpc.BST.uSecInFrame );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_PowerPerToneCur_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsTpc.dmTpc.PowerPerToneCur );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_PowerPerToneAvg_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsTpc.dmTpc.PowerPerToneAvg );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_PathLoss_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsTpc.dmTpc.PathLoss );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_Headroom_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsTpc.dmTpc.Headroom );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_Reserved_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsTpc.dmTpc.Reserved );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_powerControlMode_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsTpc.dmTpc.powerControlMode );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_isTx_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsTpc.dmTpc.isTx );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_CurrentFrameTxPower_Total_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsTpc.dmTpc.CurrentFrameTxPower.Total );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_CurrentFrameTxPower_NumOfSubchannels_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsTpc.dmTpc.CurrentFrameTxPower.NumOfSubchannels );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_CurrentFrameTxPower_AllocationType_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsTpc.dmTpc.CurrentFrameTxPower.AllocationType );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ExtremePowerValues_MaxPower_Total_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsTpc.dmTpc.ExtremePowerValues.MaxPower.Total );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ExtremePowerValues_MaxPower_NumOfSubchannels_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsTpc.dmTpc.ExtremePowerValues.MaxPower.NumOfSubchannels );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ExtremePowerValues_MaxPower_AllocationType_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsTpc.dmTpc.ExtremePowerValues.MaxPower.AllocationType );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ExtremePowerValues_MinPower_Total_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsTpc.dmTpc.ExtremePowerValues.MinPower.Total );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ExtremePowerValues_MinPower_NumOfSubchannels_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsTpc.dmTpc.ExtremePowerValues.MinPower.NumOfSubchannels );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ExtremePowerValues_MinPower_AllocationType_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsTpc.dmTpc.ExtremePowerValues.MinPower.AllocationType );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_offsetBSperSS_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsTpc.dmTpc.offsetBSperSS );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_offsetSSperSS_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsTpc.dmTpc.offsetSSperSS );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_cqiAckPeriodicRangingNI_valid_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsTpc.dmTpc.ulNoiseAndInterferenceLevel.cqiAckPeriodicRangingNI.valid );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_cqiAckPeriodicRangingNI_level_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsTpc.dmTpc.ulNoiseAndInterferenceLevel.cqiAckPeriodicRangingNI.level );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_puscNI_valid_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsTpc.dmTpc.ulNoiseAndInterferenceLevel.puscNI.valid );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_puscNI_level_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsTpc.dmTpc.ulNoiseAndInterferenceLevel.puscNI.level );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_amcNI_valid_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsTpc.dmTpc.ulNoiseAndInterferenceLevel.amcNI.valid );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_amcNI_level_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsTpc.dmTpc.ulNoiseAndInterferenceLevel.amcNI.level );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_periodicRangingNI_valid_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsTpc.dmTpc.ulNoiseAndInterferenceLevel.periodicRangingNI.valid );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_periodicRangingNI_level_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsTpc.dmTpc.ulNoiseAndInterferenceLevel.periodicRangingNI.level );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_soundingNI_valid_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsTpc.dmTpc.ulNoiseAndInterferenceLevel.soundingNI.valid );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_soundingNI_level_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsTpc.dmTpc.ulNoiseAndInterferenceLevel.soundingNI.level );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_mimoNI_valid_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsTpc.dmTpc.ulNoiseAndInterferenceLevel.mimoNI.valid );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_mimoNI_level_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsTpc.dmTpc.ulNoiseAndInterferenceLevel.mimoNI.level );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_LackOfHeadroomCounter_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsTpc.dmTpc.LackOfHeadroomCounter );
			}
			if( type == 4054 )
			{
				pMsg->L3L4_L3MonitorGroupL1_DiagnosticsPerformance.Type = (UINT16)type;
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsPerformance.BST.FrameNumber );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsPerformance.BST.uSecInFrame );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_MapsStatistics_FchRecievedOK_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsPerformance.dmPhyPerformance.MapsStatistics.FchRecievedOK );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_MapsStatistics_FchFailures_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsPerformance.dmPhyPerformance.MapsStatistics.FchFailures );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_MapsStatistics_NormalDlMapRecievedOK_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsPerformance.dmPhyPerformance.MapsStatistics.NormalDlMapRecievedOK );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_MapsStatistics_NormalDlMapHcsError_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsPerformance.dmPhyPerformance.MapsStatistics.NormalDlMapHcsError );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_MapsStatistics_NormalDlMapCrcError_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsPerformance.dmPhyPerformance.MapsStatistics.NormalDlMapCrcError );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_MapsStatistics_NormalUlMapRecievedOK_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsPerformance.dmPhyPerformance.MapsStatistics.NormalUlMapRecievedOK );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_MapsStatistics_NormalUlMapHcsError_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsPerformance.dmPhyPerformance.MapsStatistics.NormalUlMapHcsError );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_MapsStatistics_NormalUlMapCrcError_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsPerformance.dmPhyPerformance.MapsStatistics.NormalUlMapCrcError );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_MapsStatistics_CompressedMapRecievedOK_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsPerformance.dmPhyPerformance.MapsStatistics.CompressedMapRecievedOK );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_MapsStatistics_CompressedMapCrcError_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsPerformance.dmPhyPerformance.MapsStatistics.CompressedMapCrcError );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_PreamblePCinr_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsPerformance.dmPhyPerformance.l1Measurements.PreamblePCinr );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_PreamblePCinrAnt0_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsPerformance.dmPhyPerformance.l1Measurements.PreamblePCinrAnt0 );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_PreamblePCinrAnt1_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsPerformance.dmPhyPerformance.l1Measurements.PreamblePCinrAnt1 );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_PreamblePCinrStd_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsPerformance.dmPhyPerformance.l1Measurements.PreamblePCinrStd );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_Rssi_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsPerformance.dmPhyPerformance.l1Measurements.Rssi );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_RssiStd_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsPerformance.dmPhyPerformance.l1Measurements.RssiStd );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_MimoStbcPCinr_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsPerformance.dmPhyPerformance.l1Measurements.MimoStbcPCinr );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_MimoStbcPCinrStd_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsPerformance.dmPhyPerformance.l1Measurements.MimoStbcPCinrStd );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_MimoSmPCinr_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsPerformance.dmPhyPerformance.l1Measurements.MimoSmPCinr );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_MimoSmPCinrStd_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsPerformance.dmPhyPerformance.l1Measurements.MimoSmPCinrStd );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_MimoStbcECinr_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsPerformance.dmPhyPerformance.l1Measurements.MimoStbcECinr );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_MimoSmECinr_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsPerformance.dmPhyPerformance.l1Measurements.MimoSmECinr );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_RxAntModeAutoDetect_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsPerformance.dmPhyPerformance.l1Measurements.RxAntModeAutoDetect );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_Reserved8_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsPerformance.dmPhyPerformance.l1Measurements.Reserved8 );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_Reserved16_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsPerformance.dmPhyPerformance.l1Measurements.Reserved16 );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_cqichCount_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsPerformance.dmPhyPerformance.cqichCount );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_TemperatureInCelsius_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsPerformance.dmPhyPerformance.TemperatureInCelsius );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_RxAntMode_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsPerformance.dmPhyPerformance.RxAntMode );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_Reserved_1_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsPerformance.dmPhyPerformance.Reserved_1 );
			}
			if( type == 4055 )
			{
				pMsg->L3L4_L3MonitorGroupL1_DiagnosticsConfiguration.Type = (UINT16)type;
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsConfiguration_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsConfiguration.BST.FrameNumber );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsConfiguration_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsConfiguration.BST.uSecInFrame );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsConfiguration_dmPhyConfiguration_FrequencyOffsetInHz_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsConfiguration.dmPhyConfiguration.FrequencyOffsetInHz );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsConfiguration_dmPhyConfiguration_CenterFrequencyInKHz_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsConfiguration.dmPhyConfiguration.CenterFrequencyInKHz );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsConfiguration_dmPhyConfiguration_transitionGaps_TTG_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsConfiguration.dmPhyConfiguration.transitionGaps.TTG );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsConfiguration_dmPhyConfiguration_transitionGaps_RTG_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsConfiguration.dmPhyConfiguration.transitionGaps.RTG );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsConfiguration_dmPhyConfiguration_RecommendedMIMOMode_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsConfiguration.dmPhyConfiguration.RecommendedMIMOMode );
			}
			if( type == 4050 )
			{
				pMsg->L3L4_L3MonitorGroupBASIC_STATUS.Type = (UINT16)type;
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBASIC_STATUS_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupBASIC_STATUS.BST.FrameNumber );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBASIC_STATUS_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupBASIC_STATUS.BST.uSecInFrame );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBASIC_STATUS_FWMonitorGroupBasicStatus_FCH_byte0_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupBASIC_STATUS.FWMonitorGroupBasicStatus.FCH.byte0 );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBASIC_STATUS_FWMonitorGroupBasicStatus_FCH_byte1_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupBASIC_STATUS.FWMonitorGroupBasicStatus.FCH.byte1 );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBASIC_STATUS_FWMonitorGroupBasicStatus_FCH_byte2_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupBASIC_STATUS.FWMonitorGroupBasicStatus.FCH.byte2 );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBASIC_STATUS_FWMonitorGroupBasicStatus_FCH_validity_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupBASIC_STATUS.FWMonitorGroupBasicStatus.FCH.validity );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBASIC_STATUS_FWMonitorGroupBasicStatus_frameRatio_DlSize_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupBASIC_STATUS.FWMonitorGroupBasicStatus.frameRatio.DlSize );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBASIC_STATUS_FWMonitorGroupBasicStatus_frameRatio_UlSize_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupBASIC_STATUS.FWMonitorGroupBasicStatus.frameRatio.UlSize );
			}
			if( type == 4051 )
			{
				pMsg->L3L4_L3MonitorGroupBURST_STATUS.Type = (UINT16)type;
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBURST_STATUS_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupBURST_STATUS.BST.FrameNumber );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBURST_STATUS_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupBURST_STATUS.BST.uSecInFrame );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBURST_STATUS_FWMonitorGroupBurstStatus_TotalDLPduCRCCount_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupBURST_STATUS.FWMonitorGroupBurstStatus.TotalDLPduCRCCount );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBURST_STATUS_FWMonitorGroupBurstStatus_TotalDLPduCount_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupBURST_STATUS.FWMonitorGroupBurstStatus.TotalDLPduCount );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBURST_STATUS_FWMonitorGroupBurstStatus_UL_PDU_Size_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupBURST_STATUS.FWMonitorGroupBurstStatus.UL_PDU_Size );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBURST_STATUS_FWMonitorGroupBurstStatus_TotalULPDUSize_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupBURST_STATUS.FWMonitorGroupBurstStatus.TotalULPDUSize );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBURST_STATUS_FWMonitorGroupBurstStatus_TotalUlPduCount_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupBURST_STATUS.FWMonitorGroupBurstStatus.TotalUlPduCount );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBURST_STATUS_FWMonitorGroupBurstStatus_UL_SDU_Size_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupBURST_STATUS.FWMonitorGroupBurstStatus.UL_SDU_Size );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBURST_STATUS_FWMonitorGroupBurstStatus_TotalULSDUSize_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupBURST_STATUS.FWMonitorGroupBurstStatus.TotalULSDUSize );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBURST_STATUS_FWMonitorGroupBurstStatus_TotalUlSduCount_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupBURST_STATUS.FWMonitorGroupBurstStatus.TotalUlSduCount );
			}
			if( type == 4063 )
			{
				pMsg->L3L4_L3MonitorGroupPER_CIN_STATUS.Type = (UINT16)type;
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupPER_CIN_STATUS_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupPER_CIN_STATUS.BST.FrameNumber );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupPER_CIN_STATUS_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupPER_CIN_STATUS.BST.uSecInFrame );
				for( i0 = 0; i0 < 16; i0++ )
				{
					BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupPER_CIN_STATUS_Per_CIN_MonitorInfo_L2_perCIN_xDUStatus_PDUInfo_numberOfTxedPDUs_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupPER_CIN_STATUS.Per_CIN_MonitorInfo_L2.perCIN_xDUStatus.PDUInfo[i0].numberOfTxedPDUs );
					BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupPER_CIN_STATUS_Per_CIN_MonitorInfo_L2_perCIN_xDUStatus_PDUInfo_totalBytes_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupPER_CIN_STATUS.Per_CIN_MonitorInfo_L2.perCIN_xDUStatus.PDUInfo[i0].totalBytes );
				}
				for( i0 = 0; i0 < 16; i0++ )
				{
					BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupPER_CIN_STATUS_Per_CIN_MonitorInfo_L2_perCIN_xDUStatus_SDUInfo_numberOfAgedSDUs_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupPER_CIN_STATUS.Per_CIN_MonitorInfo_L2.perCIN_xDUStatus.SDUInfo[i0].numberOfAgedSDUs );
					BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupPER_CIN_STATUS_Per_CIN_MonitorInfo_L2_perCIN_xDUStatus_SDUInfo_totalBytes_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupPER_CIN_STATUS.Per_CIN_MonitorInfo_L2.perCIN_xDUStatus.SDUInfo[i0].totalBytes );
				}
				for( i0 = 0; i0 < 16; i0++ )
				{
					BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupPER_CIN_STATUS_Per_CIN_MonitorInfo_L2_perCIN_BWRStatus_AggregatedBWRInfo_numberOfBWRs_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupPER_CIN_STATUS.Per_CIN_MonitorInfo_L2.perCIN_BWRStatus.AggregatedBWRInfo[i0].numberOfBWRs );
					BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupPER_CIN_STATUS_Per_CIN_MonitorInfo_L2_perCIN_BWRStatus_AggregatedBWRInfo_totalBytes_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupPER_CIN_STATUS.Per_CIN_MonitorInfo_L2.perCIN_BWRStatus.AggregatedBWRInfo[i0].totalBytes );
				}
				for( i0 = 0; i0 < 16; i0++ )
				{
					BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupPER_CIN_STATUS_Per_CIN_MonitorInfo_L2_perCIN_BWRStatus_IncrementalBWRInfo_numberOfBWRs_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupPER_CIN_STATUS.Per_CIN_MonitorInfo_L2.perCIN_BWRStatus.IncrementalBWRInfo[i0].numberOfBWRs );
					BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupPER_CIN_STATUS_Per_CIN_MonitorInfo_L2_perCIN_BWRStatus_IncrementalBWRInfo_totalBytes_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupPER_CIN_STATUS.Per_CIN_MonitorInfo_L2.perCIN_BWRStatus.IncrementalBWRInfo[i0].totalBytes );
				}
				for( i0 = 0; i0 < 16; i0++ )
				{
					BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupPER_CIN_STATUS_Per_CIN_MonitorInfo_L2_perCIN_VQInfo_currentVQInfo_totalBytesPendingInQ_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupPER_CIN_STATUS.Per_CIN_MonitorInfo_L2.perCIN_VQInfo.currentVQInfo[i0].totalBytesPendingInQ );
				}
			}
			if( type == 4064 )
			{
				pMsg->L3L4_L3MonitorGroupSF_AND_QOS_FLOW_MNGMT.Type = (UINT16)type;
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupSF_AND_QOS_FLOW_MNGMT_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupSF_AND_QOS_FLOW_MNGMT.BST.FrameNumber );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupSF_AND_QOS_FLOW_MNGMT_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupSF_AND_QOS_FLOW_MNGMT.BST.uSecInFrame );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupSF_AND_QOS_FLOW_MNGMT_L2_MON_TYPE_SF_AND_QOS_FLOW_MNGMT_HARQBurst_TotalGrantsAmountInBytes_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupSF_AND_QOS_FLOW_MNGMT.L2_MON_TYPE_SF_AND_QOS_FLOW_MNGMT.HARQBurst.TotalGrantsAmountInBytes );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupSF_AND_QOS_FLOW_MNGMT_L2_MON_TYPE_SF_AND_QOS_FLOW_MNGMT_NonHARQBurst_TotalGrantsAmountInBytes_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupSF_AND_QOS_FLOW_MNGMT.L2_MON_TYPE_SF_AND_QOS_FLOW_MNGMT.NonHARQBurst.TotalGrantsAmountInBytes );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupSF_AND_QOS_FLOW_MNGMT_L2_MON_TYPE_SF_AND_QOS_FLOW_MNGMT_UIUC14Burst_TotalGrantsAmountInBytes_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupSF_AND_QOS_FLOW_MNGMT.L2_MON_TYPE_SF_AND_QOS_FLOW_MNGMT.UIUC14Burst.TotalGrantsAmountInBytes );
			}
			if( type == 4066 )
			{
				pMsg->L3L4_L3MonitorGroupL2_LAM_Events.Type = (UINT16)type;
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL2_LAM_Events_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL2_LAM_Events.BST.FrameNumber );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL2_LAM_Events_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL2_LAM_Events.BST.uSecInFrame );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL2_LAM_Events_L2_LAM_Events_MonitorInfo_CQIParams_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL2_LAM_Events.L2_LAM_Events_MonitorInfo.CQIParams.FrameNumber );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL2_LAM_Events_L2_LAM_Events_MonitorInfo_CQIParams_CQI_Measurement_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL2_LAM_Events.L2_LAM_Events_MonitorInfo.CQIParams.CQI_Measurement );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL2_LAM_Events_L2_LAM_Events_MonitorInfo_CQIParams_ChannelID_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL2_LAM_Events.L2_LAM_Events_MonitorInfo.CQIParams.ChannelID );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL2_LAM_Events_L2_LAM_Events_MonitorInfo_CQIParams_IsMIMOReportFlag_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL2_LAM_Events.L2_LAM_Events_MonitorInfo.CQIParams.IsMIMOReportFlag );
			}
			if( type == 4065 )
			{
				pMsg->L3L4_L3MonitorGroupL1_DiagnosticsTpcEvents.Type = (UINT16)type;
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpcEvents_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsTpcEvents.BST.FrameNumber );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpcEvents_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsTpcEvents.BST.uSecInFrame );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpcEvents_dmTpcEvents_TPCModeChange_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_DiagnosticsTpcEvents.dmTpcEvents.TPCModeChange );
			}
			if( type == 4049 )
			{
				pMsg->L3L4_L3MonitorGroupL1_NBS_PSCAN_Results.Type = (UINT16)type;
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_NBS_PSCAN_Results_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_NBS_PSCAN_Results.BST.FrameNumber );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_NBS_PSCAN_Results_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_NBS_PSCAN_Results.BST.uSecInFrame );
				BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_NBS_PSCAN_Results_dmL1NBSPSCANResults_numOfReportedBs_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_NBS_PSCAN_Results.dmL1NBSPSCANResults.numOfReportedBs );
				for( i0 = 0; i0 < (UINT32)pMsg->L3L4_L3MonitorGroupL1_NBS_PSCAN_Results.dmL1NBSPSCANResults.numOfReportedBs; i0++ )
				{
					BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_NBS_PSCAN_Results_dmL1NBSPSCANResults_NBSPSCANResult_PHYLinkID_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_NBS_PSCAN_Results.dmL1NBSPSCANResults.NBSPSCANResult[i0].PHYLinkID );
					BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_NBS_PSCAN_Results_dmL1NBSPSCANResults_NBSPSCANResult_NeighbourBSPreambleCINRMeanReuse1_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_NBS_PSCAN_Results.dmL1NBSPSCANResults.NBSPSCANResult[i0].NeighbourBSPreambleCINRMeanReuse1 );
					BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_NBS_PSCAN_Results_dmL1NBSPSCANResults_NBSPSCANResult_NeighbourBSPreambleCINRMeanReuse3_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_NBS_PSCAN_Results.dmL1NBSPSCANResults.NBSPSCANResult[i0].NeighbourBSPreambleCINRMeanReuse3 );
					BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_NBS_PSCAN_Results_dmL1NBSPSCANResults_NBSPSCANResult_NeighbourBSPreambleRSSIMean_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_NBS_PSCAN_Results.dmL1NBSPSCANResults.NBSPSCANResult[i0].NeighbourBSPreambleRSSIMean );
					BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_NBS_PSCAN_Results_dmL1NBSPSCANResults_NBSPSCANResult_NeighbourBSTimeOffset_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_NBS_PSCAN_Results.dmL1NBSPSCANResults.NBSPSCANResult[i0].NeighbourBSTimeOffset );
					BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_NBS_PSCAN_Results_dmL1NBSPSCANResults_NBSPSCANResult_IntraInterFAFlag_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_NBS_PSCAN_Results.dmL1NBSPSCANResults.NBSPSCANResult[i0].IntraInterFAFlag );
					BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_NBS_PSCAN_Results_dmL1NBSPSCANResults_NBSPSCANResult_MeasurementsValidityFlag_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_L3MonitorGroupL1_NBS_PSCAN_Results.dmL1NBSPSCANResults.NBSPSCANResult[i0].MeasurementsValidityFlag );
				}
			}
			if( type == 4056 )
			{
				pMsg->L3L4_DilloHarqPerfGroup.Type = (UINT16)type;
				BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_DilloHarqPerfGroup.BST.FrameNumber );
				BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_DilloHarqPerfGroup.BST.uSecInFrame );
				BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_HarqPerfComp_NacksSent_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_DilloHarqPerfGroup.HarqPerfComp.NacksSent );
				BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_HarqPerfComp_AcksSent_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_DilloHarqPerfGroup.HarqPerfComp.AcksSent );
				BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_HarqPerfComp_DuplicatesRx_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_DilloHarqPerfGroup.HarqPerfComp.DuplicatesRx );
				BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_HarqPerfComp_BurstsTx_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_DilloHarqPerfGroup.HarqPerfComp.BurstsTx );
				BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_HarqPerfComp_BurstsRx_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_DilloHarqPerfGroup.HarqPerfComp.BurstsRx );
				BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_HarqPerfComp_Reserved_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_DilloHarqPerfGroup.HarqPerfComp.Reserved );
				for( i0 = 0; i0 < 16; i0++ )
				{
					BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_HarqPerfComp_RetransUL_Array_Retrans_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_DilloHarqPerfGroup.HarqPerfComp.RetransUL_Array[i0].Retrans );
				}
				for( i0 = 0; i0 < 16; i0++ )
				{
					BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_HarqPerfComp_RetransDL_Array_Retrans_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_DilloHarqPerfGroup.HarqPerfComp.RetransDL_Array[i0].Retrans );
				}
				BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_HarqPerfComp_DropHarqBurstCount_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_DilloHarqPerfGroup.HarqPerfComp.DropHarqBurstCount );
				for( i0 = 0; i0 < 16; i0++ )
				{
					BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_HarqPerfComp_AgingArrayUL_Retrans_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_DilloHarqPerfGroup.HarqPerfComp.AgingArrayUL[i0].Retrans );
				}
				for( i0 = 0; i0 < 16; i0++ )
				{
					BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_HarqPerfComp_AgingArrayDL_Retrans_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_DilloHarqPerfGroup.HarqPerfComp.AgingArrayDL[i0].Retrans );
				}
			}
			if( type == 4052 )
			{
				pMsg->L3L4_DilloBurstGroup.Type = (UINT16)type;
				BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_DilloBurstGroup.BST.FrameNumber );
				BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_DilloBurstGroup.BST.uSecInFrame );
				for( i0 = 0; i0 < 14; i0++ )
				{
					BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_RxBurstsPerMcs_Array_Bursts_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_DilloBurstGroup.BurstStatComp.RxBurstsPerMcs_Array[i0].Bursts );
				}
				for( i0 = 0; i0 < 10; i0++ )
				{
					BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_TxBurstsPerMcs_Array_Bursts_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_DilloBurstGroup.BurstStatComp.TxBurstsPerMcs_Array[i0].Bursts );
				}
				BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_UL_BurstDataZone_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_DilloBurstGroup.BurstStatComp.UL_BurstDataZone );
				BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_DL_BurstDataFecScheme_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_DilloBurstGroup.BurstStatComp.DL_BurstDataFecScheme );
				BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_UL_BurstDataFecScheme_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_DilloBurstGroup.BurstStatComp.UL_BurstDataFecScheme );
				BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_DL_BurstDataCid_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_DilloBurstGroup.BurstStatComp.DL_BurstDataCid );
				BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_DL_BurstDataDiuc_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_DilloBurstGroup.BurstStatComp.DL_BurstDataDiuc );
				BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_UL_BurstDataUiuc_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_DilloBurstGroup.BurstStatComp.UL_BurstDataUiuc );
				BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_DL_BurstDataRepetition_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_DilloBurstGroup.BurstStatComp.DL_BurstDataRepetition );
				BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_UL_BurstDataRepetition_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_DilloBurstGroup.BurstStatComp.UL_BurstDataRepetition );
				BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_UL_TotalFec_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_DilloBurstGroup.BurstStatComp.UL_TotalFec );
				BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_DL_TotalFec_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_DilloBurstGroup.BurstStatComp.DL_TotalFec );
				BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_FecMode_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_DilloBurstGroup.BurstStatComp.FecMode );
				BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_FecTypeID_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_DilloBurstGroup.BurstStatComp.FecTypeID );
				BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_FecNumberOfError_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_DilloBurstGroup.BurstStatComp.FecNumberOfError );
			}
			if( type == 4185 )
			{
				pMsg->L3L4_MonitorGroupEventCdmaTxAttrib.Type = (UINT16)type;
				BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaTxAttrib_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_MonitorGroupEventCdmaTxAttrib.BST.FrameNumber );
				BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaTxAttrib_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_MonitorGroupEventCdmaTxAttrib.BST.uSecInFrame );
				BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaTxAttrib_CdmaTxAttribComp_FrameContainsCdmaTx_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_MonitorGroupEventCdmaTxAttrib.CdmaTxAttribComp.FrameContainsCdmaTx );
				BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaTxAttrib_CdmaTxAttribComp_FrameRefLow_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_MonitorGroupEventCdmaTxAttrib.CdmaTxAttribComp.FrameRefLow );
				BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaTxAttrib_CdmaTxAttribComp_SymbolsRef_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_MonitorGroupEventCdmaTxAttrib.CdmaTxAttribComp.SymbolsRef );
				BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaTxAttrib_CdmaTxAttribComp_SubChRef_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_MonitorGroupEventCdmaTxAttrib.CdmaTxAttribComp.SubChRef );
				BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaTxAttrib_CdmaTxAttribComp_RangingCode_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_MonitorGroupEventCdmaTxAttrib.CdmaTxAttribComp.RangingCode );
				BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaTxAttrib_CdmaTxAttribComp_Reserved_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_MonitorGroupEventCdmaTxAttrib.CdmaTxAttribComp.Reserved );
			}
			if( type == 4180 )
			{
				pMsg->L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS.Type = (UINT16)type;
				BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS.BST.FrameNumber );
				BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS.BST.uSecInFrame );
				BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_FWL2MonitorGroupRangingTraceEvent_DilloCdmaAttributes_xOffset_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS.FWL2MonitorGroupRangingTraceEvent.DilloCdmaAttributes.xOffset );
				BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_FWL2MonitorGroupRangingTraceEvent_DilloCdmaAttributes_yOffset_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS.FWL2MonitorGroupRangingTraceEvent.DilloCdmaAttributes.yOffset );
				BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_FWL2MonitorGroupRangingTraceEvent_DilloCdmaAttributes_codeNumber_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS.FWL2MonitorGroupRangingTraceEvent.DilloCdmaAttributes.codeNumber );
				BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_FWL2MonitorGroupRangingTraceEvent_DilloCdmaAttributes_frameNumber_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS.FWL2MonitorGroupRangingTraceEvent.DilloCdmaAttributes.frameNumber );
				BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_FWL2MonitorGroupRangingTraceEvent_RangingType_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS.FWL2MonitorGroupRangingTraceEvent.RangingType );
				BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_FWL2MonitorGroupRangingTraceEvent_TimingAdjustment_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS.FWL2MonitorGroupRangingTraceEvent.TimingAdjustment );
				BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_FWL2MonitorGroupRangingTraceEvent_PowerLevelAdjust_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS.FWL2MonitorGroupRangingTraceEvent.PowerLevelAdjust );
				BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_FWL2MonitorGroupRangingTraceEvent_InvitingRetries_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS.FWL2MonitorGroupRangingTraceEvent.InvitingRetries );
				BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_FWL2MonitorGroupRangingTraceEvent_ContentionRetries_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS.FWL2MonitorGroupRangingTraceEvent.ContentionRetries );
				BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_FWL2MonitorGroupRangingTraceEvent_rangingStatus_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS.FWL2MonitorGroupRangingTraceEvent.rangingStatus );
			}
			if( type == 4184 )
			{
				pMsg->L3L4_MonitorGroupEventCdmaBwr.Type = (UINT16)type;
				BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaBwr_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_MonitorGroupEventCdmaBwr.BST.FrameNumber );
				BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaBwr_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_MonitorGroupEventCdmaBwr.BST.uSecInFrame );
				BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaBwr_FWCdmaBwrEvent_TotalNumberOfCdmaBwrInit_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_MonitorGroupEventCdmaBwr.FWCdmaBwrEvent.TotalNumberOfCdmaBwrInit );
				BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaBwr_FWCdmaBwrEvent_TotalNumberOfTxCdmaBwr_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_MonitorGroupEventCdmaBwr.FWCdmaBwrEvent.TotalNumberOfTxCdmaBwr );
			}
			if( type == 4060 )
			{
				pMsg->L3L4_DilloSfAndQosPerformanceGroup.Type = (UINT16)type;
				BM_MonitorBuffer_List_CURRENT_L3L4_DilloSfAndQosPerformanceGroup_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_DilloSfAndQosPerformanceGroup.BST.FrameNumber );
				BM_MonitorBuffer_List_CURRENT_L3L4_DilloSfAndQosPerformanceGroup_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_DilloSfAndQosPerformanceGroup.BST.uSecInFrame );
				BM_MonitorBuffer_List_CURRENT_L3L4_DilloSfAndQosPerformanceGroup_DilloSfAndQosPerformanceComp_TotalBytesThroughputOtaDL_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_DilloSfAndQosPerformanceGroup.DilloSfAndQosPerformanceComp.TotalBytesThroughputOtaDL );
				BM_MonitorBuffer_List_CURRENT_L3L4_DilloSfAndQosPerformanceGroup_DilloSfAndQosPerformanceComp_TotalBytesThroughputOtaUL_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_DilloSfAndQosPerformanceGroup.DilloSfAndQosPerformanceComp.TotalBytesThroughputOtaUL );
			}
			if( type == 4061 )
			{
				pMsg->L3L4_DilloSfAndQosFlowManagementGroup.Type = (UINT16)type;
				BM_MonitorBuffer_List_CURRENT_L3L4_DilloSfAndQosFlowManagementGroup_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_DilloSfAndQosFlowManagementGroup.BST.FrameNumber );
				BM_MonitorBuffer_List_CURRENT_L3L4_DilloSfAndQosFlowManagementGroup_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_DilloSfAndQosFlowManagementGroup.BST.uSecInFrame );
				BM_MonitorBuffer_List_CURRENT_L3L4_DilloSfAndQosFlowManagementGroup_DilloSfAndQosFlowManagementComp_GrantsReceiveSlots_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_DilloSfAndQosFlowManagementGroup.DilloSfAndQosFlowManagementComp.GrantsReceiveSlots );
				BM_MonitorBuffer_List_CURRENT_L3L4_DilloSfAndQosFlowManagementGroup_DilloSfAndQosFlowManagementComp_reserved_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_DilloSfAndQosFlowManagementGroup.DilloSfAndQosFlowManagementComp.reserved );
			}
			if( type == 4059 )
			{
				pMsg->L3L4_DilloPhyConfigurationGroup.Type = (UINT16)type;
				BM_MonitorBuffer_List_CURRENT_L3L4_DilloPhyConfigurationGroup_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_DilloPhyConfigurationGroup.BST.FrameNumber );
				BM_MonitorBuffer_List_CURRENT_L3L4_DilloPhyConfigurationGroup_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_DilloPhyConfigurationGroup.BST.uSecInFrame );
				for( i0 = 0; i0 < 14; i0++ )
				{
					BM_MonitorBuffer_List_CURRENT_L3L4_DilloPhyConfigurationGroup_DilloPhyConfigurationComp_DlMcsAllocationTableNoneMimo_Bursts_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_DilloPhyConfigurationGroup.DilloPhyConfigurationComp.DlMcsAllocationTableNoneMimo[i0].Bursts );
				}
				for( i0 = 0; i0 < 14; i0++ )
				{
					BM_MonitorBuffer_List_CURRENT_L3L4_DilloPhyConfigurationGroup_DilloPhyConfigurationComp_DlMcsAllocationTableMatrixA_Bursts_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_DilloPhyConfigurationGroup.DilloPhyConfigurationComp.DlMcsAllocationTableMatrixA[i0].Bursts );
				}
				for( i0 = 0; i0 < 14; i0++ )
				{
					BM_MonitorBuffer_List_CURRENT_L3L4_DilloPhyConfigurationGroup_DilloPhyConfigurationComp_DlMcsAllocationTableMatrixB_Bursts_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_DilloPhyConfigurationGroup.DilloPhyConfigurationComp.DlMcsAllocationTableMatrixB[i0].Bursts );
				}
				for( i0 = 0; i0 < 10; i0++ )
				{
					BM_MonitorBuffer_List_CURRENT_L3L4_DilloPhyConfigurationGroup_DilloPhyConfigurationComp_UlMcsAllocationTableNoneStc_Bursts_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_DilloPhyConfigurationGroup.DilloPhyConfigurationComp.UlMcsAllocationTableNoneStc[i0].Bursts );
				}
				for( i0 = 0; i0 < 10; i0++ )
				{
					BM_MonitorBuffer_List_CURRENT_L3L4_DilloPhyConfigurationGroup_DilloPhyConfigurationComp_UlMcsAllocationTableStc_Bursts_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_DilloPhyConfigurationGroup.DilloPhyConfigurationComp.UlMcsAllocationTableStc[i0].Bursts );
				}
			}
			if( type == 4062 )
			{
				pMsg->L3L4_DilloMapsGroup.Type = (UINT16)type;
				BM_MonitorBuffer_List_CURRENT_L3L4_DilloMapsGroup_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_DilloMapsGroup.BST.FrameNumber );
				BM_MonitorBuffer_List_CURRENT_L3L4_DilloMapsGroup_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_DilloMapsGroup.BST.uSecInFrame );
				BM_MonitorBuffer_List_CURRENT_L3L4_DilloMapsGroup_DilloMapsComp_TotalNumberOfMaps_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_DilloMapsGroup.DilloMapsComp.TotalNumberOfMaps );
				BM_MonitorBuffer_List_CURRENT_L3L4_DilloMapsGroup_DilloMapsComp_TotalBytesOfMaps_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_DilloMapsGroup.DilloMapsComp.TotalBytesOfMaps );
			}
			if( type == 4101 )
			{
				pMsg->L3L4_BasicStatus_L3.Type = (UINT16)type;
				BM_MonitorBuffer_List_CURRENT_L3L4_BasicStatus_L3_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_BasicStatus_L3.BST.FrameNumber );
				BM_MonitorBuffer_List_CURRENT_L3L4_BasicStatus_L3_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_BasicStatus_L3.BST.uSecInFrame );
				BM_MonitorBuffer_List_CURRENT_L3L4_BasicStatus_L3_BasicStatus_L3_frequency_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_BasicStatus_L3.BasicStatus_L3.frequency );
				BM_MonitorBuffer_List_CURRENT_L3L4_BasicStatus_L3_BasicStatus_L3_ulCidNum_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_BasicStatus_L3.BasicStatus_L3.ulCidNum );
				BM_MonitorBuffer_List_CURRENT_L3L4_BasicStatus_L3_BasicStatus_L3_dlCidNum_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_BasicStatus_L3.BasicStatus_L3.dlCidNum );
				BM_MonitorBuffer_List_CURRENT_L3L4_BasicStatus_L3_BasicStatus_L3_preambleIndex_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_BasicStatus_L3.BasicStatus_L3.preambleIndex );
				BM_MonitorBuffer_List_CURRENT_L3L4_BasicStatus_L3_BasicStatus_L3_bandWidth_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_BasicStatus_L3.BasicStatus_L3.bandWidth );
				for( i0 = 0; i0 < 6; i0++ )
				{
					BM_MonitorBuffer_List_CURRENT_L3L4_BasicStatus_L3_BasicStatus_L3_bsId_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_BasicStatus_L3.BasicStatus_L3.bsId[i0].value );
				}
				for( i0 = 0; i0 < 6; i0++ )
				{
					BM_MonitorBuffer_List_CURRENT_L3L4_BasicStatus_L3_BasicStatus_L3_macAddress_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_BasicStatus_L3.BasicStatus_L3.macAddress[i0].value );
				}
			}
			if( type == 4102 )
			{
				pMsg->L3L4_BurstStatus_L3.Type = (UINT16)type;
				BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_BurstStatus_L3.BST.FrameNumber );
				BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_BurstStatus_L3.BST.uSecInFrame );
				BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_lastDlPduSize_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_BurstStatus_L3.BurstStatus_L3.lastDlPduSize );
				BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_totalDlPdusSize_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_BurstStatus_L3.BurstStatus_L3.totalDlPdusSize );
				BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_dlPduCount_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_BurstStatus_L3.BurstStatus_L3.dlPduCount );
				BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_lastDlSduSize_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_BurstStatus_L3.BurstStatus_L3.lastDlSduSize );
				BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_totalDlSdusSize_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_BurstStatus_L3.BurstStatus_L3.totalDlSdusSize );
				BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_totalUlSduDropCounter_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_BurstStatus_L3.BurstStatus_L3.totalUlSduDropCounter );
				BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_totalDlPdusSizeInLastDlSubFrame_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_BurstStatus_L3.BurstStatus_L3.totalDlPdusSizeInLastDlSubFrame );
				BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_numOfCidInfos_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_BurstStatus_L3.BurstStatus_L3.numOfCidInfos );
				for( i0 = 0; i0 < (UINT32)pMsg->L3L4_BurstStatus_L3.BurstStatus_L3.numOfCidInfos; i0++ )
				{
					BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_burstStatusPerConnection_CID_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_BurstStatus_L3.BurstStatus_L3.burstStatusPerConnection[i0].CID );
					BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_burstStatusPerConnection_CIN_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_BurstStatus_L3.BurstStatus_L3.burstStatusPerConnection[i0].CIN );
					BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_burstStatusPerConnection_totalUlSduRateLimitDropCount_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_BurstStatus_L3.BurstStatus_L3.burstStatusPerConnection[i0].totalUlSduRateLimitDropCount );
					BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_burstStatusPerConnection_rateUlDropPackets_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_BurstStatus_L3.BurstStatus_L3.burstStatusPerConnection[i0].rateUlDropPackets );
					BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_burstStatusPerConnection_totalDlReceivedPdu_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_BurstStatus_L3.BurstStatus_L3.burstStatusPerConnection[i0].totalDlReceivedPdu );
					BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_burstStatusPerConnection_totalUlTransmittedSdu_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_BurstStatus_L3.BurstStatus_L3.burstStatusPerConnection[i0].totalUlTransmittedSdu );
					BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_burstStatusPerConnection_totalOfPduDlBytes_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_BurstStatus_L3.BurstStatus_L3.burstStatusPerConnection[i0].totalOfPduDlBytes );
					BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_burstStatusPerConnection_totalOfSduDlBytes_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_BurstStatus_L3.BurstStatus_L3.burstStatusPerConnection[i0].totalOfSduDlBytes );
				}
			}
			if( type == 4208 )
			{
				pMsg->L3L4_SF_QoS_MonitorInfo_L3.Type = (UINT16)type;
				BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_SF_QoS_MonitorInfo_L3.BST.FrameNumber );
				BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_SF_QoS_MonitorInfo_L3.BST.uSecInFrame );
				BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_numOfCidInfos_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_SF_QoS_MonitorInfo_L3.SF_QoS_MonitorInfo_L3.numOfCidInfos );
				BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_numOfSfCreationSucess_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_SF_QoS_MonitorInfo_L3.SF_QoS_MonitorInfo_L3.numOfSfCreationSucess );
				BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_numOfSfCreationFailure_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_SF_QoS_MonitorInfo_L3.SF_QoS_MonitorInfo_L3.numOfSfCreationFailure );
				BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_numOfSfDeleted_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_SF_QoS_MonitorInfo_L3.SF_QoS_MonitorInfo_L3.numOfSfDeleted );
				for( i0 = 0; i0 < (UINT32)pMsg->L3L4_SF_QoS_MonitorInfo_L3.SF_QoS_MonitorInfo_L3.numOfCidInfos; i0++ )
				{
					BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_sfId_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_SF_QoS_MonitorInfo_L3.SF_QoS_MonitorInfo_L3.channels[i0].sfId );
					BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_maxSustainedTrafficRate_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_SF_QoS_MonitorInfo_L3.SF_QoS_MonitorInfo_L3.channels[i0].maxSustainedTrafficRate );
					BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_maxTrafficBurst_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_SF_QoS_MonitorInfo_L3.SF_QoS_MonitorInfo_L3.channels[i0].maxTrafficBurst );
					BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_toleratedJitter_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_SF_QoS_MonitorInfo_L3.SF_QoS_MonitorInfo_L3.channels[i0].toleratedJitter );
					BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_maximumLatency_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_SF_QoS_MonitorInfo_L3.SF_QoS_MonitorInfo_L3.channels[i0].maximumLatency );
					BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_unsolicitedGrantInterval_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_SF_QoS_MonitorInfo_L3.SF_QoS_MonitorInfo_L3.channels[i0].unsolicitedGrantInterval );
					BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_minReservedTrafficRate_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_SF_QoS_MonitorInfo_L3.SF_QoS_MonitorInfo_L3.channels[i0].minReservedTrafficRate );
					BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_cid_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_SF_QoS_MonitorInfo_L3.SF_QoS_MonitorInfo_L3.channels[i0].cid );
					BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_sfSchedulingType_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_SF_QoS_MonitorInfo_L3.SF_QoS_MonitorInfo_L3.channels[i0].sfSchedulingType );
					BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_qosParamsSetType_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_SF_QoS_MonitorInfo_L3.SF_QoS_MonitorInfo_L3.channels[i0].qosParamsSetType );
					BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_trafficPrio_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_SF_QoS_MonitorInfo_L3.SF_QoS_MonitorInfo_L3.channels[i0].trafficPrio );
					BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_sfSide_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_SF_QoS_MonitorInfo_L3.SF_QoS_MonitorInfo_L3.channels[i0].sfSide );
				}
			}
			if( type == 4209 )
			{
				pMsg->L3L4_Arq_MonitorInfo_L3.Type = (UINT16)type;
				BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Arq_MonitorInfo_L3.BST.FrameNumber );
				BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Arq_MonitorInfo_L3.BST.uSecInFrame );
				BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_numOfCidInfos_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Arq_MonitorInfo_L3.Arq_MonitorInfo_L3.numOfCidInfos );
				for( i0 = 0; i0 < (UINT32)pMsg->L3L4_Arq_MonitorInfo_L3.Arq_MonitorInfo_L3.numOfCidInfos; i0++ )
				{
					BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_arqInfo_sfId_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Arq_MonitorInfo_L3.Arq_MonitorInfo_L3.arqInfo[i0].sfId );
					BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_arqInfo_arqWindowSize_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Arq_MonitorInfo_L3.Arq_MonitorInfo_L3.arqInfo[i0].arqWindowSize );
					BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_arqInfo_arqTransmitterDelay_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Arq_MonitorInfo_L3.Arq_MonitorInfo_L3.arqInfo[i0].arqTransmitterDelay );
					BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_arqInfo_arqReceiverDelay_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Arq_MonitorInfo_L3.Arq_MonitorInfo_L3.arqInfo[i0].arqReceiverDelay );
					BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_arqInfo_arqBlockLifeTime_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Arq_MonitorInfo_L3.Arq_MonitorInfo_L3.arqInfo[i0].arqBlockLifeTime );
					BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_arqInfo_arqSyncLossTimeout_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Arq_MonitorInfo_L3.Arq_MonitorInfo_L3.arqInfo[i0].arqSyncLossTimeout );
					BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_arqInfo_arqRxPurgeTimeout_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Arq_MonitorInfo_L3.Arq_MonitorInfo_L3.arqInfo[i0].arqRxPurgeTimeout );
					BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_arqInfo_arqBlockSize_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Arq_MonitorInfo_L3.Arq_MonitorInfo_L3.arqInfo[i0].arqBlockSize );
					BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_arqInfo_t22_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Arq_MonitorInfo_L3.Arq_MonitorInfo_L3.arqInfo[i0].t22 );
					BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_arqInfo_arqEnable_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Arq_MonitorInfo_L3.Arq_MonitorInfo_L3.arqInfo[i0].arqEnable );
					BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_arqInfo_arqDeliverInOrder_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Arq_MonitorInfo_L3.Arq_MonitorInfo_L3.arqInfo[i0].arqDeliverInOrder );
				}
			}
			if( type == 4211 )
			{
				pMsg->L3L4_Harq_MonitorInfo_L3.Type = (UINT16)type;
				BM_MonitorBuffer_List_CURRENT_L3L4_Harq_MonitorInfo_L3_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Harq_MonitorInfo_L3.BST.FrameNumber );
				BM_MonitorBuffer_List_CURRENT_L3L4_Harq_MonitorInfo_L3_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Harq_MonitorInfo_L3.BST.uSecInFrame );
				BM_MonitorBuffer_List_CURRENT_L3L4_Harq_MonitorInfo_L3_Harq_MonitorInfo_L3_numOfCidInfos_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Harq_MonitorInfo_L3.Harq_MonitorInfo_L3.numOfCidInfos );
				for( i0 = 0; i0 < (UINT32)pMsg->L3L4_Harq_MonitorInfo_L3.Harq_MonitorInfo_L3.numOfCidInfos; i0++ )
				{
					BM_MonitorBuffer_List_CURRENT_L3L4_Harq_MonitorInfo_L3_Harq_MonitorInfo_L3_harqInfo_harqChannelMapping_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Harq_MonitorInfo_L3.Harq_MonitorInfo_L3.harqInfo[i0].harqChannelMapping );
					BM_MonitorBuffer_List_CURRENT_L3L4_Harq_MonitorInfo_L3_Harq_MonitorInfo_L3_harqInfo_harqEnable_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Harq_MonitorInfo_L3.Harq_MonitorInfo_L3.harqInfo[i0].harqEnable );
					BM_MonitorBuffer_List_CURRENT_L3L4_Harq_MonitorInfo_L3_Harq_MonitorInfo_L3_harqInfo_harqisForReorder_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Harq_MonitorInfo_L3.Harq_MonitorInfo_L3.harqInfo[i0].harqisForReorder );
					BM_MonitorBuffer_List_CURRENT_L3L4_Harq_MonitorInfo_L3_Harq_MonitorInfo_L3_harqInfo_sfId_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Harq_MonitorInfo_L3.Harq_MonitorInfo_L3.harqInfo[i0].sfId );
				}
			}
			if( type == 4200 )
			{
				if ( L3L4_MacState_L3_index < 3)
				{
					pMsg->L3L4_MacState_L3[L3L4_MacState_L3_index].Type = (UINT16)type;
					BM_MonitorBuffer_List_CURRENT_L3L4_MacState_L3_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_MacState_L3[L3L4_MacState_L3_index].BST.FrameNumber );
					BM_MonitorBuffer_List_CURRENT_L3L4_MacState_L3_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_MacState_L3[L3L4_MacState_L3_index].BST.uSecInFrame );
					BM_MonitorBuffer_List_CURRENT_L3L4_MacState_L3_MacState_L3_state_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_MacState_L3[L3L4_MacState_L3_index].MacState_L3.state );
				}
				L3L4_MacState_L3_index++;
			}
			if( type == 4201 )
			{
				pMsg->L3L4_NbrCellList_L3.Type = (UINT16)type;
				BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_NbrCellList_L3.BST.FrameNumber );
				BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_NbrCellList_L3.BST.uSecInFrame );
				BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_numOfIntraFASNbrs_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_NbrCellList_L3.NbrCellList_L3.numOfIntraFASNbrs );
				BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_numOfInterFASNbrs_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_NbrCellList_L3.NbrCellList_L3.numOfInterFASNbrs );
				for( i0 = 0; i0 < (UINT32)pMsg->L3L4_NbrCellList_L3.NbrCellList_L3.numOfIntraFASNbrs; i0++ )
				{
					UINT32 i1 = 0;
					BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_intraFaNbrs_rssiMean_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_NbrCellList_L3.NbrCellList_L3.intraFaNbrs[i0].rssiMean );
					BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_intraFaNbrs_cinrMean_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_NbrCellList_L3.NbrCellList_L3.intraFaNbrs[i0].cinrMean );
					BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_intraFaNbrs_preambleId_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_NbrCellList_L3.NbrCellList_L3.intraFaNbrs[i0].preambleId );
					BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_intraFaNbrs_frequency_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_NbrCellList_L3.NbrCellList_L3.intraFaNbrs[i0].frequency );
					BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_intraFaNbrs_bandWidth_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_NbrCellList_L3.NbrCellList_L3.intraFaNbrs[i0].bandWidth );
					for( i1 = 0; i1 < 6; i1++ )
					{
						BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_intraFaNbrs_bsId_value_GET( base_ptr, i0, i1, cur_ptr, cur_bitoff, pMsg->L3L4_NbrCellList_L3.NbrCellList_L3.intraFaNbrs[i0].bsId[i1].value );
					}
				}
				for( i0 = 0; i0 < (UINT32)pMsg->L3L4_NbrCellList_L3.NbrCellList_L3.numOfInterFASNbrs; i0++ )
				{
					UINT32 i1 = 0;
					BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_interFaNbrs_rssiMean_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_NbrCellList_L3.NbrCellList_L3.interFaNbrs[i0].rssiMean );
					BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_interFaNbrs_cinrMean_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_NbrCellList_L3.NbrCellList_L3.interFaNbrs[i0].cinrMean );
					BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_interFaNbrs_preambleId_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_NbrCellList_L3.NbrCellList_L3.interFaNbrs[i0].preambleId );
					BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_interFaNbrs_frequency_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_NbrCellList_L3.NbrCellList_L3.interFaNbrs[i0].frequency );
					BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_interFaNbrs_bandWidth_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_NbrCellList_L3.NbrCellList_L3.interFaNbrs[i0].bandWidth );
					for( i1 = 0; i1 < 6; i1++ )
					{
						BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_interFaNbrs_bsId_value_GET( base_ptr, i0, i1, cur_ptr, cur_bitoff, pMsg->L3L4_NbrCellList_L3.NbrCellList_L3.interFaNbrs[i0].bsId[i1].value );
					}
				}
			}
			if( type == 4203 )
			{
				pMsg->L3L4_NwEntryMsgLatency_L3.Type = (UINT16)type;
				BM_MonitorBuffer_List_CURRENT_L3L4_NwEntryMsgLatency_L3_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_NwEntryMsgLatency_L3.BST.FrameNumber );
				BM_MonitorBuffer_List_CURRENT_L3L4_NwEntryMsgLatency_L3_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_NwEntryMsgLatency_L3.BST.uSecInFrame );
				BM_MonitorBuffer_List_CURRENT_L3L4_NwEntryMsgLatency_L3_NwEntryMsgLatency_L3_initRengLatency_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_NwEntryMsgLatency_L3.NwEntryMsgLatency_L3.initRengLatency );
				BM_MonitorBuffer_List_CURRENT_L3L4_NwEntryMsgLatency_L3_NwEntryMsgLatency_L3_sbcLatency_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_NwEntryMsgLatency_L3.NwEntryMsgLatency_L3.sbcLatency );
				BM_MonitorBuffer_List_CURRENT_L3L4_NwEntryMsgLatency_L3_NwEntryMsgLatency_L3_pkmLatency_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_NwEntryMsgLatency_L3.NwEntryMsgLatency_L3.pkmLatency );
				BM_MonitorBuffer_List_CURRENT_L3L4_NwEntryMsgLatency_L3_NwEntryMsgLatency_L3_regLatency_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_NwEntryMsgLatency_L3.NwEntryMsgLatency_L3.regLatency );
				BM_MonitorBuffer_List_CURRENT_L3L4_NwEntryMsgLatency_L3_NwEntryMsgLatency_L3_dsaLatency_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_NwEntryMsgLatency_L3.NwEntryMsgLatency_L3.dsaLatency );
				BM_MonitorBuffer_List_CURRENT_L3L4_NwEntryMsgLatency_L3_NwEntryMsgLatency_L3_setuUpTime_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_NwEntryMsgLatency_L3.NwEntryMsgLatency_L3.setuUpTime );
			}
			if( type == 4206 )
			{
				pMsg->L3L4_DcdUcdTimeout_L3.Type = (UINT16)type;
				BM_MonitorBuffer_List_CURRENT_L3L4_DcdUcdTimeout_L3_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_DcdUcdTimeout_L3.BST.FrameNumber );
				BM_MonitorBuffer_List_CURRENT_L3L4_DcdUcdTimeout_L3_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_DcdUcdTimeout_L3.BST.uSecInFrame );
				BM_MonitorBuffer_List_CURRENT_L3L4_DcdUcdTimeout_L3_DcdUcdTimeout_L3_countDcdUcdTimeOut_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_DcdUcdTimeout_L3.DcdUcdTimeout_L3.countDcdUcdTimeOut );
			}
			if( type == 4207 )
			{
				pMsg->L3L4_DSxTimers_L3.Type = (UINT16)type;
				BM_MonitorBuffer_List_CURRENT_L3L4_DSxTimers_L3_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_DSxTimers_L3.BST.FrameNumber );
				BM_MonitorBuffer_List_CURRENT_L3L4_DSxTimers_L3_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_DSxTimers_L3.BST.uSecInFrame );
				BM_MonitorBuffer_List_CURRENT_L3L4_DSxTimers_L3_DSxTimers_L3_t7Timeout_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_DSxTimers_L3.DSxTimers_L3.t7Timeout );
				BM_MonitorBuffer_List_CURRENT_L3L4_DSxTimers_L3_DSxTimers_L3_t8Timeout_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_DSxTimers_L3.DSxTimers_L3.t8Timeout );
				BM_MonitorBuffer_List_CURRENT_L3L4_DSxTimers_L3_DSxTimers_L3_t10Timeout_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_DSxTimers_L3.DSxTimers_L3.t10Timeout );
				BM_MonitorBuffer_List_CURRENT_L3L4_DSxTimers_L3_DSxTimers_L3_dsxReqRetries_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_DSxTimers_L3.DSxTimers_L3.dsxReqRetries );
				BM_MonitorBuffer_List_CURRENT_L3L4_DSxTimers_L3_DSxTimers_L3_dsxRspRetries_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_DSxTimers_L3.DSxTimers_L3.dsxRspRetries );
			}
			if( type == 4210 )
			{
				pMsg->L3L4_Phy_L3.Type = (UINT16)type;
				BM_MonitorBuffer_List_CURRENT_L3L4_Phy_L3_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Phy_L3.BST.FrameNumber );
				BM_MonitorBuffer_List_CURRENT_L3L4_Phy_L3_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Phy_L3.BST.uSecInFrame );
				BM_MonitorBuffer_List_CURRENT_L3L4_Phy_L3_Phy_L3_preambleSearchTime_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Phy_L3.Phy_L3.preambleSearchTime );
				BM_MonitorBuffer_List_CURRENT_L3L4_Phy_L3_Phy_L3_numOfPreamble_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Phy_L3.Phy_L3.numOfPreamble );
			}
			if( type == 4213 )
			{
				if ( L3L4_LinkLossOccur_L3_index < 5)
				{
					pMsg->L3L4_LinkLossOccur_L3[L3L4_LinkLossOccur_L3_index].Type = (UINT16)type;
					BM_MonitorBuffer_List_CURRENT_L3L4_LinkLossOccur_L3_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_LinkLossOccur_L3[L3L4_LinkLossOccur_L3_index].BST.FrameNumber );
					BM_MonitorBuffer_List_CURRENT_L3L4_LinkLossOccur_L3_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_LinkLossOccur_L3[L3L4_LinkLossOccur_L3_index].BST.uSecInFrame );
					BM_MonitorBuffer_List_CURRENT_L3L4_LinkLossOccur_L3_LinkLossOccur_L3_occurrenceTime_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_LinkLossOccur_L3[L3L4_LinkLossOccur_L3_index].LinkLossOccur_L3.occurrenceTime );
					BM_MonitorBuffer_List_CURRENT_L3L4_LinkLossOccur_L3_LinkLossOccur_L3_LastLinkLossReason_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_LinkLossOccur_L3[L3L4_LinkLossOccur_L3_index].LinkLossOccur_L3.LastLinkLossReason );
					for( i0 = 0; i0 < 6; i0++ )
					{
						BM_MonitorBuffer_List_CURRENT_L3L4_LinkLossOccur_L3_LinkLossOccur_L3_bsId_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_LinkLossOccur_L3[L3L4_LinkLossOccur_L3_index].LinkLossOccur_L3.bsId[i0].value );
					}
				}
				L3L4_LinkLossOccur_L3_index++;
			}
			if( type == 4252 )
			{
				pMsg->L3L4_Moniter_Scan_Config.Type = (UINT16)type;
				BM_MonitorBuffer_List_CURRENT_L3L4_Moniter_Scan_Config_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Moniter_Scan_Config.BST.FrameNumber );
				BM_MonitorBuffer_List_CURRENT_L3L4_Moniter_Scan_Config_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Moniter_Scan_Config.BST.uSecInFrame );
				BM_MonitorBuffer_List_CURRENT_L3L4_Moniter_Scan_Config_MoniterScanConfig_SetScanParam_NumOfChannels_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Moniter_Scan_Config.MoniterScanConfig.SetScanParam.NumOfChannels );
				for( i0 = 0; i0 < (UINT32)pMsg->L3L4_Moniter_Scan_Config.MoniterScanConfig.SetScanParam.NumOfChannels; i0++ )
				{
					UINT32 i1 = 0;
					BM_MonitorBuffer_List_CURRENT_L3L4_Moniter_Scan_Config_MoniterScanConfig_SetScanParam_Channels_Frequency_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Moniter_Scan_Config.MoniterScanConfig.SetScanParam.Channels[i0].Frequency );
					BM_MonitorBuffer_List_CURRENT_L3L4_Moniter_Scan_Config_MoniterScanConfig_SetScanParam_Channels_ChannelId_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Moniter_Scan_Config.MoniterScanConfig.SetScanParam.Channels[i0].ChannelId );
					BM_MonitorBuffer_List_CURRENT_L3L4_Moniter_Scan_Config_MoniterScanConfig_SetScanParam_Channels_Bandwidth_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Moniter_Scan_Config.MoniterScanConfig.SetScanParam.Channels[i0].Bandwidth );
					BM_MonitorBuffer_List_CURRENT_L3L4_Moniter_Scan_Config_MoniterScanConfig_SetScanParam_Channels_Fft_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Moniter_Scan_Config.MoniterScanConfig.SetScanParam.Channels[i0].Fft );
					for( i1 = 0; i1 < 15; i1++ )
					{
						BM_MonitorBuffer_List_CURRENT_L3L4_Moniter_Scan_Config_MoniterScanConfig_SetScanParam_Channels_Preambles_value_GET( base_ptr, i0, i1, cur_ptr, cur_bitoff, pMsg->L3L4_Moniter_Scan_Config.MoniterScanConfig.SetScanParam.Channels[i0].Preambles[i1].value );
					}
					BM_MonitorBuffer_List_CURRENT_L3L4_Moniter_Scan_Config_MoniterScanConfig_SetScanParam_Channels_Reserved_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Moniter_Scan_Config.MoniterScanConfig.SetScanParam.Channels[i0].Reserved );
				}
			}
			if( type == 4151 )
			{
				if ( L3L4_DSPS_Management_MSG_index < 10)
				{
					pMsg->L3L4_DSPS_Management_MSG[L3L4_DSPS_Management_MSG_index].Type = (UINT16)type;
					BM_MonitorBuffer_List_CURRENT_L3L4_DSPS_Management_MSG_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_DSPS_Management_MSG[L3L4_DSPS_Management_MSG_index].BST.FrameNumber );
					BM_MonitorBuffer_List_CURRENT_L3L4_DSPS_Management_MSG_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_DSPS_Management_MSG[L3L4_DSPS_Management_MSG_index].BST.uSecInFrame );
					pMsg->L3L4_DSPS_Management_MSG[L3L4_DSPS_Management_MSG_index].DSPS_Management_MSG.tlv_length = (UINT16)length;
					for( i0 = 0; i0 < (UINT32)pMsg->L3L4_DSPS_Management_MSG[L3L4_DSPS_Management_MSG_index].DSPS_Management_MSG.tlv_length-8; i0++ )
					{
						BM_MonitorBuffer_List_CURRENT_L3L4_DSPS_Management_MSG_DSPS_Management_MSG_MngmntBufferRun_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_DSPS_Management_MSG[L3L4_DSPS_Management_MSG_index].DSPS_Management_MSG.MngmntBufferRun[i0].value );
					}
				}
				L3L4_DSPS_Management_MSG_index++;
			}
			if( type == 4202 )
			{
				pMsg->L3L4_linkLossStatistics_L3.Type = (UINT16)type;
				BM_MonitorBuffer_List_CURRENT_L3L4_linkLossStatistics_L3_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_linkLossStatistics_L3.BST.FrameNumber );
				BM_MonitorBuffer_List_CURRENT_L3L4_linkLossStatistics_L3_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_linkLossStatistics_L3.BST.uSecInFrame );
				BM_MonitorBuffer_List_CURRENT_L3L4_linkLossStatistics_L3_linkLossStatistics_L3_occurrenceTime_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_linkLossStatistics_L3.linkLossStatistics_L3.occurrenceTime );
				BM_MonitorBuffer_List_CURRENT_L3L4_linkLossStatistics_L3_linkLossStatistics_L3_linkLossLatency_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_linkLossStatistics_L3.linkLossStatistics_L3.linkLossLatency );
				BM_MonitorBuffer_List_CURRENT_L3L4_linkLossStatistics_L3_linkLossStatistics_L3_HoRangingLatency_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_linkLossStatistics_L3.linkLossStatistics_L3.HoRangingLatency );
				for( i0 = 0; i0 < 6; i0++ )
				{
					BM_MonitorBuffer_List_CURRENT_L3L4_linkLossStatistics_L3_linkLossStatistics_L3_bsId_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_linkLossStatistics_L3.linkLossStatistics_L3.bsId[i0].value );
				}
			}
			if( type == 4215 )
			{
				pMsg->L3L4_CoordinateHo_L3.Type = (UINT16)type;
				BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_CoordinateHo_L3.BST.FrameNumber );
				BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_CoordinateHo_L3.BST.uSecInFrame );
				BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_numOfBsInHoReq_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_CoordinateHo_L3.CoordinateHo_L3.numOfBsInHoReq );
				BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_numOfBsInHoRsp_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_CoordinateHo_L3.CoordinateHo_L3.numOfBsInHoRsp );
				BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_HoSuccessCounter_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_CoordinateHo_L3.CoordinateHo_L3.HoSuccessCounter );
				BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_HoFailCounter_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_CoordinateHo_L3.CoordinateHo_L3.HoFailCounter );
				BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_HoAttemptsCounter_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_CoordinateHo_L3.CoordinateHo_L3.HoAttemptsCounter );
				BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_HoRejectsCounter_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_CoordinateHo_L3.CoordinateHo_L3.HoRejectsCounter );
				BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_HoNotRecommendedCounter_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_CoordinateHo_L3.CoordinateHo_L3.HoNotRecommendedCounter );
				BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_numberOfTBSAttempted_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_CoordinateHo_L3.CoordinateHo_L3.numberOfTBSAttempted );
				BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_cancellationWithNormalOperation_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_CoordinateHo_L3.CoordinateHo_L3.cancellationWithNormalOperation );
				BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_cancellationWithReentryProblem_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_CoordinateHo_L3.CoordinateHo_L3.cancellationWithReentryProblem );
				BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_coordHoLatency_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_CoordinateHo_L3.CoordinateHo_L3.coordHoLatency );
				BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_cutOffLatency_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_CoordinateHo_L3.CoordinateHo_L3.cutOffLatency );
				BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_status_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_CoordinateHo_L3.CoordinateHo_L3.status );
				BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_typeId_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_CoordinateHo_L3.CoordinateHo_L3.typeId );
				for( i0 = 0; i0 < (UINT32)pMsg->L3L4_CoordinateHo_L3.CoordinateHo_L3.numOfBsInHoReq; i0++ )
				{
					UINT32 i1 = 0;
					for( i1 = 0; i1 < 6; i1++ )
					{
						BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_hoReqBsList_bsId_value_GET( base_ptr, i0, i1, cur_ptr, cur_bitoff, pMsg->L3L4_CoordinateHo_L3.CoordinateHo_L3.hoReqBsList[i0].bsId[i1].value );
					}
				}
				for( i0 = 0; i0 < (UINT32)pMsg->L3L4_CoordinateHo_L3.CoordinateHo_L3.numOfBsInHoRsp; i0++ )
				{
					UINT32 i1 = 0;
					for( i1 = 0; i1 < 6; i1++ )
					{
						BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_hoRspBsList_bsId_value_GET( base_ptr, i0, i1, cur_ptr, cur_bitoff, pMsg->L3L4_CoordinateHo_L3.CoordinateHo_L3.hoRspBsList[i0].bsId[i1].value );
					}
				}
				BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_HoTriggersCounter_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_CoordinateHo_L3.CoordinateHo_L3.HoTriggersCounter );
			}
			if( type == 4217 )
			{
				pMsg->L3L4_McsIndexTable_L3.Type = (UINT16)type;
				BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_McsIndexTable_L3.BST.FrameNumber );
				BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_McsIndexTable_L3.BST.uSecInFrame );
				BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_McsIndexTable_L3_NumDlburstProfiles_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_McsIndexTable_L3.McsIndexTable_L3.NumDlburstProfiles );
				BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_McsIndexTable_L3_NumUlburstProfiles_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_McsIndexTable_L3.McsIndexTable_L3.NumUlburstProfiles );
				for( i0 = 0; i0 < (UINT32)pMsg->L3L4_McsIndexTable_L3.McsIndexTable_L3.NumDlburstProfiles; i0++ )
				{
					BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_McsIndexTable_L3_DlburstProfiles_intervalUsageCode_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_McsIndexTable_L3.McsIndexTable_L3.DlburstProfiles[i0].intervalUsageCode );
					BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_McsIndexTable_L3_DlburstProfiles_fecType_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_McsIndexTable_L3.McsIndexTable_L3.DlburstProfiles[i0].fecType );
					BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_McsIndexTable_L3_DlburstProfiles_fecRate_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_McsIndexTable_L3.McsIndexTable_L3.DlburstProfiles[i0].fecRate );
					BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_McsIndexTable_L3_DlburstProfiles_modulation_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_McsIndexTable_L3.McsIndexTable_L3.DlburstProfiles[i0].modulation );
				}
				for( i0 = 0; i0 < (UINT32)pMsg->L3L4_McsIndexTable_L3.McsIndexTable_L3.NumUlburstProfiles; i0++ )
				{
					BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_McsIndexTable_L3_UlburstProfiles_intervalUsageCode_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_McsIndexTable_L3.McsIndexTable_L3.UlburstProfiles[i0].intervalUsageCode );
					BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_McsIndexTable_L3_UlburstProfiles_fecType_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_McsIndexTable_L3.McsIndexTable_L3.UlburstProfiles[i0].fecType );
					BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_McsIndexTable_L3_UlburstProfiles_fecRate_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_McsIndexTable_L3.McsIndexTable_L3.UlburstProfiles[i0].fecRate );
					BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_McsIndexTable_L3_UlburstProfiles_modulation_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_McsIndexTable_L3.McsIndexTable_L3.UlburstProfiles[i0].modulation );
				}
			}
			if( type == 4214 )
			{
				pMsg->L3L4_ScanResult_L3.Type = (UINT16)type;
				BM_MonitorBuffer_List_CURRENT_L3L4_ScanResult_L3_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_ScanResult_L3.BST.FrameNumber );
				BM_MonitorBuffer_List_CURRENT_L3L4_ScanResult_L3_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_ScanResult_L3.BST.uSecInFrame );
				BM_MonitorBuffer_List_CURRENT_L3L4_ScanResult_L3_ScanResult_L3_numOfNbrs_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_ScanResult_L3.ScanResult_L3.numOfNbrs );
				for( i0 = 0; i0 < (UINT32)pMsg->L3L4_ScanResult_L3.ScanResult_L3.numOfNbrs; i0++ )
				{
					UINT32 i1 = 0;
					BM_MonitorBuffer_List_CURRENT_L3L4_ScanResult_L3_ScanResult_L3_resultNbrs_phyLinkId_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_ScanResult_L3.ScanResult_L3.resultNbrs[i0].phyLinkId );
					BM_MonitorBuffer_List_CURRENT_L3L4_ScanResult_L3_ScanResult_L3_resultNbrs_frequency_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_ScanResult_L3.ScanResult_L3.resultNbrs[i0].frequency );
					BM_MonitorBuffer_List_CURRENT_L3L4_ScanResult_L3_ScanResult_L3_resultNbrs_phyGrade_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_ScanResult_L3.ScanResult_L3.resultNbrs[i0].phyGrade );
					BM_MonitorBuffer_List_CURRENT_L3L4_ScanResult_L3_ScanResult_L3_resultNbrs_preambleId_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_ScanResult_L3.ScanResult_L3.resultNbrs[i0].preambleId );
					BM_MonitorBuffer_List_CURRENT_L3L4_ScanResult_L3_ScanResult_L3_resultNbrs_bandWidth_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_ScanResult_L3.ScanResult_L3.resultNbrs[i0].bandWidth );
					BM_MonitorBuffer_List_CURRENT_L3L4_ScanResult_L3_ScanResult_L3_resultNbrs_bSValidityIndicator_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_ScanResult_L3.ScanResult_L3.resultNbrs[i0].bSValidityIndicator );
					for( i1 = 0; i1 < 6; i1++ )
					{
						BM_MonitorBuffer_List_CURRENT_L3L4_ScanResult_L3_ScanResult_L3_resultNbrs_bsId_value_GET( base_ptr, i0, i1, cur_ptr, cur_bitoff, pMsg->L3L4_ScanResult_L3.ScanResult_L3.resultNbrs[i0].bsId[i1].value );
					}
				}
			}
			if( type == 4204 )
			{
				pMsg->L3L4_ScanStatus_L3.Type = (UINT16)type;
				BM_MonitorBuffer_List_CURRENT_L3L4_ScanStatus_L3_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_ScanStatus_L3.BST.FrameNumber );
				BM_MonitorBuffer_List_CURRENT_L3L4_ScanStatus_L3_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_ScanStatus_L3.BST.uSecInFrame );
				BM_MonitorBuffer_List_CURRENT_L3L4_ScanStatus_L3_ScanStatus_L3_scanDuration_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_ScanStatus_L3.ScanStatus_L3.scanDuration );
				BM_MonitorBuffer_List_CURRENT_L3L4_ScanStatus_L3_ScanStatus_L3_scanIteration_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_ScanStatus_L3.ScanStatus_L3.scanIteration );
				BM_MonitorBuffer_List_CURRENT_L3L4_ScanStatus_L3_ScanStatus_L3_modeReport_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_ScanStatus_L3.ScanStatus_L3.modeReport );
				BM_MonitorBuffer_List_CURRENT_L3L4_ScanStatus_L3_ScanStatus_L3_periodReport_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_ScanStatus_L3.ScanStatus_L3.periodReport );
				BM_MonitorBuffer_List_CURRENT_L3L4_ScanStatus_L3_ScanStatus_L3_interleavingInterval_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_ScanStatus_L3.ScanStatus_L3.interleavingInterval );
			}
			if( type == 4205 )
			{
				pMsg->L3L4_ConnectionDropCount_L3.Type = (UINT16)type;
				BM_MonitorBuffer_List_CURRENT_L3L4_ConnectionDropCount_L3_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_ConnectionDropCount_L3.BST.FrameNumber );
				BM_MonitorBuffer_List_CURRENT_L3L4_ConnectionDropCount_L3_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_ConnectionDropCount_L3.BST.uSecInFrame );
				BM_MonitorBuffer_List_CURRENT_L3L4_ConnectionDropCount_L3_ConnectionDropCount_L3_counterConnectionDropEvent_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_ConnectionDropCount_L3.ConnectionDropCount_L3.counterConnectionDropEvent );
			}
			if( type == 4212 )
			{
				pMsg->L3L4_IdleConfiguration_L3.Type = (UINT16)type;
				BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_IdleConfiguration_L3.BST.FrameNumber );
				BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_IdleConfiguration_L3.BST.uSecInFrame );
				BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_IdleConfiguration_L3_idleModeTimeout_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_IdleConfiguration_L3.IdleConfiguration_L3.idleModeTimeout );
				BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_IdleConfiguration_L3_pagingCycleReq_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_IdleConfiguration_L3.IdleConfiguration_L3.pagingCycleReq );
				BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_IdleConfiguration_L3_t45Timeout_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_IdleConfiguration_L3.IdleConfiguration_L3.t45Timeout );
				BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_IdleConfiguration_L3_PagingGroupID_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_IdleConfiguration_L3.IdleConfiguration_L3.PagingGroupID );
				BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_IdleConfiguration_L3_PagingCycle_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_IdleConfiguration_L3.IdleConfiguration_L3.PagingCycle );
				BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_IdleConfiguration_L3_PagingOffset_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_IdleConfiguration_L3.IdleConfiguration_L3.PagingOffset );
				BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_IdleConfiguration_L3_RetainInfo_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_IdleConfiguration_L3.IdleConfiguration_L3.RetainInfo );
				BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_IdleConfiguration_L3_dregReqRetries_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_IdleConfiguration_L3.IdleConfiguration_L3.dregReqRetries );
				BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_IdleConfiguration_L3_PagingIntervalLength_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_IdleConfiguration_L3.IdleConfiguration_L3.PagingIntervalLength );
				for( i0 = 0; i0 < 6; i0++ )
				{
					BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_IdleConfiguration_L3_PagingControllerID_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_IdleConfiguration_L3.IdleConfiguration_L3.PagingControllerID[i0].value );
				}
			}
			if( type == 4216 )
			{
				pMsg->L3L4_IdlePerformance_L3.Type = (UINT16)type;
				BM_MonitorBuffer_List_CURRENT_L3L4_IdlePerformance_L3_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_IdlePerformance_L3.BST.FrameNumber );
				BM_MonitorBuffer_List_CURRENT_L3L4_IdlePerformance_L3_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_IdlePerformance_L3.BST.uSecInFrame );
				BM_MonitorBuffer_List_CURRENT_L3L4_IdlePerformance_L3_IdlePerformance_L3_counterInternalTimer_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_IdlePerformance_L3.IdlePerformance_L3.counterInternalTimer );
				BM_MonitorBuffer_List_CURRENT_L3L4_IdlePerformance_L3_IdlePerformance_L3_counterNWInitiated_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_IdlePerformance_L3.IdlePerformance_L3.counterNWInitiated );
				BM_MonitorBuffer_List_CURRENT_L3L4_IdlePerformance_L3_IdlePerformance_L3_counterGroupChange_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_IdlePerformance_L3.IdlePerformance_L3.counterGroupChange );
				BM_MonitorBuffer_List_CURRENT_L3L4_IdlePerformance_L3_IdlePerformance_L3_counterSecuredLu_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_IdlePerformance_L3.IdlePerformance_L3.counterSecuredLu );
				BM_MonitorBuffer_List_CURRENT_L3L4_IdlePerformance_L3_IdlePerformance_L3_counterUnSecuredLu_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_IdlePerformance_L3.IdlePerformance_L3.counterUnSecuredLu );
			}
			if( type == 4103 )
			{
				pMsg->L3L4_Arq_MonitorRxPerformance_L3.Type = (UINT16)type;
				BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Arq_MonitorRxPerformance_L3.BST.FrameNumber );
				BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Arq_MonitorRxPerformance_L3.BST.uSecInFrame );
				BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqResetPerformed_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Arq_MonitorRxPerformance_L3.Arq_MonitorRxPerformance_L3.arqResetPerformed );
				BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_numOfCidPerformance_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Arq_MonitorRxPerformance_L3.Arq_MonitorRxPerformance_L3.numOfCidPerformance );
				for( i0 = 0; i0 < (UINT32)pMsg->L3L4_Arq_MonitorRxPerformance_L3.Arq_MonitorRxPerformance_L3.numOfCidPerformance; i0++ )
				{
					BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqRxPerformance_CID_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Arq_MonitorRxPerformance_L3.Arq_MonitorRxPerformance_L3.arqRxPerformance[i0].CID );
					BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqRxPerformance_CIN_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Arq_MonitorRxPerformance_L3.Arq_MonitorRxPerformance_L3.arqRxPerformance[i0].CIN );
					BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqRxPerformance_numOfDuplicateReceivedBlocks_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Arq_MonitorRxPerformance_L3.Arq_MonitorRxPerformance_L3.arqRxPerformance[i0].numOfDuplicateReceivedBlocks );
					BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqRxPerformance_numOfPurgeTimeouts_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Arq_MonitorRxPerformance_L3.Arq_MonitorRxPerformance_L3.arqRxPerformance[i0].numOfPurgeTimeouts );
					BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqRxPerformance_numOfBlocksLostDueToRxPurgeTimout_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Arq_MonitorRxPerformance_L3.Arq_MonitorRxPerformance_L3.arqRxPerformance[i0].numOfBlocksLostDueToRxPurgeTimout );
					BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqRxPerformance_totalNumOfAcksTxd_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Arq_MonitorRxPerformance_L3.Arq_MonitorRxPerformance_L3.arqRxPerformance[i0].totalNumOfAcksTxd );
					BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqRxPerformance_numOfRxArqResetsReceived_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Arq_MonitorRxPerformance_L3.Arq_MonitorRxPerformance_L3.arqRxPerformance[i0].numOfRxArqResetsReceived );
					BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqRxPerformance_numOfRxArqResetsInitiated_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Arq_MonitorRxPerformance_L3.Arq_MonitorRxPerformance_L3.arqRxPerformance[i0].numOfRxArqResetsInitiated );
					BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqRxPerformance_numOfArqDiscardsReceived_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Arq_MonitorRxPerformance_L3.Arq_MonitorRxPerformance_L3.arqRxPerformance[i0].numOfArqDiscardsReceived );
					BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqRxPerformance_rxThroughput_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Arq_MonitorRxPerformance_L3.Arq_MonitorRxPerformance_L3.arqRxPerformance[i0].rxThroughput );
					BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqRxPerformance_numOfPduLostDueToNoFreeSpaceInReceiver_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Arq_MonitorRxPerformance_L3.Arq_MonitorRxPerformance_L3.arqRxPerformance[i0].numOfPduLostDueToNoFreeSpaceInReceiver );
				}
			}
			if( type == 4106 )
			{
				pMsg->L3L4_Arq_MonitorTxPerformance_L3.Type = (UINT16)type;
				BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Arq_MonitorTxPerformance_L3.BST.FrameNumber );
				BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Arq_MonitorTxPerformance_L3.BST.uSecInFrame );
				BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_numOfCidPerformance_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Arq_MonitorTxPerformance_L3.Arq_MonitorTxPerformance_L3.numOfCidPerformance );
				for( i0 = 0; i0 < (UINT32)pMsg->L3L4_Arq_MonitorTxPerformance_L3.Arq_MonitorTxPerformance_L3.numOfCidPerformance; i0++ )
				{
					BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_CID_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Arq_MonitorTxPerformance_L3.Arq_MonitorTxPerformance_L3.arqTxPerformance[i0].CID );
					BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_CIN_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Arq_MonitorTxPerformance_L3.Arq_MonitorTxPerformance_L3.arqTxPerformance[i0].CIN );
					BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_numOfRetransmittedArqBlocksTotalUL_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Arq_MonitorTxPerformance_L3.Arq_MonitorTxPerformance_L3.arqTxPerformance[i0].numOfRetransmittedArqBlocksTotalUL );
					BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_numOfRetransmittedBlocksUL_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Arq_MonitorTxPerformance_L3.Arq_MonitorTxPerformance_L3.arqTxPerformance[i0].numOfRetransmittedBlocksUL );
					BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_numOfBLTs_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Arq_MonitorTxPerformance_L3.Arq_MonitorTxPerformance_L3.arqTxPerformance[i0].numOfBLTs );
					BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_numOfBlocksLostDueToArqBLT_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Arq_MonitorTxPerformance_L3.Arq_MonitorTxPerformance_L3.arqTxPerformance[i0].numOfBlocksLostDueToArqBLT );
					BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_totalNumOfAcksReceived_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Arq_MonitorTxPerformance_L3.Arq_MonitorTxPerformance_L3.arqTxPerformance[i0].totalNumOfAcksReceived );
					BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_numOfTxArqResetsReceived_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Arq_MonitorTxPerformance_L3.Arq_MonitorTxPerformance_L3.arqTxPerformance[i0].numOfTxArqResetsReceived );
					BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_numOfTxArqResetsInitiated_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Arq_MonitorTxPerformance_L3.Arq_MonitorTxPerformance_L3.arqTxPerformance[i0].numOfTxArqResetsInitiated );
					BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_numOfArqDiscardsTxd_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Arq_MonitorTxPerformance_L3.Arq_MonitorTxPerformance_L3.arqTxPerformance[i0].numOfArqDiscardsTxd );
					BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_txThroughput_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Arq_MonitorTxPerformance_L3.Arq_MonitorTxPerformance_L3.arqTxPerformance[i0].txThroughput );
					BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_numOfSduLostDueToNoFreeSpaceInTransmitter_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Arq_MonitorTxPerformance_L3.Arq_MonitorTxPerformance_L3.arqTxPerformance[i0].numOfSduLostDueToNoFreeSpaceInTransmitter );
				}
			}
			if( type == 4110 )
			{
				pMsg->L3L4_MonitorSfPerformance_L3.Type = (UINT16)type;
				BM_MonitorBuffer_List_CURRENT_L3L4_MonitorSfPerformance_L3_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_MonitorSfPerformance_L3.BST.FrameNumber );
				BM_MonitorBuffer_List_CURRENT_L3L4_MonitorSfPerformance_L3_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_MonitorSfPerformance_L3.BST.uSecInFrame );
				BM_MonitorBuffer_List_CURRENT_L3L4_MonitorSfPerformance_L3_SfPerformance_L3_numOfCidInfos_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_MonitorSfPerformance_L3.SfPerformance_L3.numOfCidInfos );
				for( i0 = 0; i0 < (UINT32)pMsg->L3L4_MonitorSfPerformance_L3.SfPerformance_L3.numOfCidInfos; i0++ )
				{
					BM_MonitorBuffer_List_CURRENT_L3L4_MonitorSfPerformance_L3_SfPerformance_L3_SfPeformancePerConnection_CID_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_MonitorSfPerformance_L3.SfPerformance_L3.SfPeformancePerConnection[i0].CID );
					BM_MonitorBuffer_List_CURRENT_L3L4_MonitorSfPerformance_L3_SfPerformance_L3_SfPeformancePerConnection_CIN_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_MonitorSfPerformance_L3.SfPerformance_L3.SfPeformancePerConnection[i0].CIN );
					BM_MonitorBuffer_List_CURRENT_L3L4_MonitorSfPerformance_L3_SfPerformance_L3_SfPeformancePerConnection_ulIpThroughput_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_MonitorSfPerformance_L3.SfPerformance_L3.SfPeformancePerConnection[i0].ulIpThroughput );
					BM_MonitorBuffer_List_CURRENT_L3L4_MonitorSfPerformance_L3_SfPerformance_L3_SfPeformancePerConnection_dlIpThroughput_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_MonitorSfPerformance_L3.SfPerformance_L3.SfPeformancePerConnection[i0].dlIpThroughput );
				}
			}
			if( type == 4253 )
			{
				pMsg->L3L4_Monitor_Scan_Result.Type = (UINT16)type;
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Result_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_Scan_Result.BST.FrameNumber );
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Result_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_Scan_Result.BST.uSecInFrame );
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Result_MonitorScanResult_AvailableNSPsIdlist_NumOfNSPs_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_Scan_Result.MonitorScanResult.AvailableNSPsIdlist.NumOfNSPs );
				for( i0 = 0; i0 < (UINT32)pMsg->L3L4_Monitor_Scan_Result.MonitorScanResult.AvailableNSPsIdlist.NumOfNSPs; i0++ )
				{
					BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Result_MonitorScanResult_AvailableNSPsIdlist_NSPID_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_Scan_Result.MonitorScanResult.AvailableNSPsIdlist.NSPID[i0].value );
				}
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Result_MonitorScanResult_FullBSIDArr_NumOfBSIDs_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_Scan_Result.MonitorScanResult.FullBSIDArr.NumOfBSIDs );
				for( i0 = 0; i0 < (UINT32)pMsg->L3L4_Monitor_Scan_Result.MonitorScanResult.FullBSIDArr.NumOfBSIDs; i0++ )
				{
					UINT32 i1 = 0;
					for( i1 = 0; i1 < 6; i1++ )
					{
						BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Result_MonitorScanResult_FullBSIDArr_FullBSID_bsID_bsID_value_GET( base_ptr, i0, i1, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_Scan_Result.MonitorScanResult.FullBSIDArr.FullBSID[i0].bsID.bsID[i1].value );
					}
					BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Result_MonitorScanResult_FullBSIDArr_FullBSID_bsID_Reserved_2_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_Scan_Result.MonitorScanResult.FullBSIDArr.FullBSID[i0].bsID.Reserved_2 );
					for( i1 = 0; i1 < 6; i1++ )
					{
						BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Result_MonitorScanResult_FullBSIDArr_FullBSID_bsIDmask_bsIDmask_value_GET( base_ptr, i0, i1, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_Scan_Result.MonitorScanResult.FullBSIDArr.FullBSID[i0].bsIDmask.bsIDmask[i1].value );
					}
					BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Result_MonitorScanResult_FullBSIDArr_FullBSID_bsIDmask_Reserved_2_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_Scan_Result.MonitorScanResult.FullBSIDArr.FullBSID[i0].bsIDmask.Reserved_2 );
				}
			}
			if( type == 4254 )
			{
				pMsg->L3L4_Monitor_Scan_Ind.Type = (UINT16)type;
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Ind_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_Scan_Ind.BST.FrameNumber );
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Ind_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_Scan_Ind.BST.uSecInFrame );
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Ind_MonitorScanInd_ScanStartEndInd_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_Scan_Ind.MonitorScanInd.ScanStartEndInd );
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Ind_MonitorScanInd_Time_wHour_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_Scan_Ind.MonitorScanInd.Time.wHour );
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Ind_MonitorScanInd_Time_wMinute_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_Scan_Ind.MonitorScanInd.Time.wMinute );
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Ind_MonitorScanInd_Time_wSecond_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_Scan_Ind.MonitorScanInd.Time.wSecond );
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Ind_MonitorScanInd_Time_wMilliseconds_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_Scan_Ind.MonitorScanInd.Time.wMilliseconds );
			}
			if( type == 4255 )
			{
				pMsg->L3L4_Monitor_OMA_Session.Type = (UINT16)type;
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_Session_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_OMA_Session.BST.FrameNumber );
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_Session_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_OMA_Session.BST.uSecInFrame );
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_Session_MonitorOMASession_OMAStatusInd_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_OMA_Session.MonitorOMASession.OMAStatusInd );
			}
			if( type == 4256 )
			{
				pMsg->L3L4_Monitor_Operator.Type = (UINT16)type;
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_Operator.BST.FrameNumber );
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_Operator.BST.uSecInFrame );
				for( i0 = 0; i0 < 100; i0++ )
				{
					BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_operatorName_operatorName_BufferByte_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_Operator.MonitorOperator.operatorName.operatorName[i0].BufferByte );
				}
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_pollingInterval_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_Operator.MonitorOperator.pollingInterval );
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Eaps_NumOfEaps_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_Operator.MonitorOperator.Eaps.NumOfEaps );
				for( i0 = 0; i0 < (UINT32)pMsg->L3L4_Monitor_Operator.MonitorOperator.Eaps.NumOfEaps; i0++ )
				{
					UINT32 i1 = 0;
					BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Eaps_EapList_usePrivacy_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_Operator.MonitorOperator.Eaps.EapList[i0].usePrivacy );
					BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Eaps_EapList_vendorId_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_Operator.MonitorOperator.Eaps.EapList[i0].vendorId );
					BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Eaps_EapList_vendorType_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_Operator.MonitorOperator.Eaps.EapList[i0].vendorType );
					BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Eaps_EapList_EAPMethod_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_Operator.MonitorOperator.Eaps.EapList[i0].EAPMethod );
					for( i1 = 0; i1 < 100; i1++ )
					{
						BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Eaps_EapList_EapId_EapId_BufferByte_GET( base_ptr, i0, i1, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_Operator.MonitorOperator.Eaps.EapList[i0].EapId.EapId[i1].BufferByte );
					}
					for( i1 = 0; i1 < 100; i1++ )
					{
						BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Eaps_EapList_provisionedPseudoId_provisionedPseudoId_BufferByte_GET( base_ptr, i0, i1, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_Operator.MonitorOperator.Eaps.EapList[i0].provisionedPseudoId.provisionedPseudoId[i1].BufferByte );
					}
					for( i1 = 0; i1 < 32; i1++ )
					{
						BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Eaps_EapList_EapPassword_EapPassword_BufferByte_GET( base_ptr, i0, i1, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_Operator.MonitorOperator.Eaps.EapList[i0].EapPassword.EapPassword[i1].BufferByte );
					}
					for( i1 = 0; i1 < 100; i1++ )
					{
						BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Eaps_EapList_Realm_Realm_BufferByte_GET( base_ptr, i0, i1, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_Operator.MonitorOperator.Eaps.EapList[i0].Realm.Realm[i1].BufferByte );
					}
					BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Eaps_EapList_encaps_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_Operator.MonitorOperator.Eaps.EapList[i0].encaps );
				}
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Capls_NumOfNaps_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_Operator.MonitorOperator.Capls.NumOfNaps );
				for( i0 = 0; i0 < (UINT32)pMsg->L3L4_Monitor_Operator.MonitorOperator.Capls.NumOfNaps; i0++ )
				{
					UINT32 i1 = 0;
					BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Capls_CaplNapList_priority_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_Operator.MonitorOperator.Capls.CaplNapList[i0].priority );
					for( i1 = 0; i1 < 3; i1++ )
					{
						BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Capls_CaplNapList_NapMember_napID_value_GET( base_ptr, i0, i1, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_Operator.MonitorOperator.Capls.CaplNapList[i0].NapMember.napID[i1].value );
					}
					BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Capls_CaplNapList_NapMember_Reserved_1_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_Operator.MonitorOperator.Capls.CaplNapList[i0].NapMember.Reserved_1 );
				}
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Rapls_NumOfRoamingPartners_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_Operator.MonitorOperator.Rapls.NumOfRoamingPartners );
				for( i0 = 0; i0 < (UINT32)pMsg->L3L4_Monitor_Operator.MonitorOperator.Rapls.NumOfRoamingPartners; i0++ )
				{
					BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Rapls_RaplList_vNspID_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_Operator.MonitorOperator.Rapls.RaplList[i0].vNspID );
					BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Rapls_RaplList_priority_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_Operator.MonitorOperator.Rapls.RaplList[i0].priority );
				}
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Rapls_Any_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_Operator.MonitorOperator.Rapls.Any );
			}
			if( type == 4257 )
			{
				pMsg->L3L4_Monitor_OMAParams.Type = (UINT16)type;
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMAParams_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_OMAParams.BST.FrameNumber );
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMAParams_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_OMAParams.BST.uSecInFrame );
				for( i0 = 0; i0 < 64; i0++ )
				{
					BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMAParams_MonitorOMAParams_DeviceInfo_manufacturer_manufacturer_BufferByte_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_OMAParams.MonitorOMAParams.DeviceInfo.manufacturer.manufacturer[i0].BufferByte );
				}
				for( i0 = 0; i0 < 64; i0++ )
				{
					BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMAParams_MonitorOMAParams_DeviceInfo_model_model_BufferByte_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_OMAParams.MonitorOMAParams.DeviceInfo.model.model[i0].BufferByte );
				}
				for( i0 = 0; i0 < 64; i0++ )
				{
					BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMAParams_MonitorOMAParams_DeviceInfo_devID_devID_BufferByte_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_OMAParams.MonitorOMAParams.DeviceInfo.devID.devID[i0].BufferByte );
				}
				for( i0 = 0; i0 < 64; i0++ )
				{
					BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMAParams_MonitorOMAParams_DeviceDetails_devType_devType_BufferByte_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_OMAParams.MonitorOMAParams.DeviceDetails.devType.devType[i0].BufferByte );
				}
				for( i0 = 0; i0 < 64; i0++ )
				{
					BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMAParams_MonitorOMAParams_DeviceDetails_fwVersion_fwVersion_BufferByte_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_OMAParams.MonitorOMAParams.DeviceDetails.fwVersion.fwVersion[i0].BufferByte );
				}
				for( i0 = 0; i0 < 64; i0++ )
				{
					BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMAParams_MonitorOMAParams_DeviceDetails_swVersion_swVersion_BufferByte_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_OMAParams.MonitorOMAParams.DeviceDetails.swVersion.swVersion[i0].BufferByte );
				}
				for( i0 = 0; i0 < 64; i0++ )
				{
					BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMAParams_MonitorOMAParams_DeviceDetails_hwVersion_hwVersion_BufferByte_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_OMAParams.MonitorOMAParams.DeviceDetails.hwVersion.hwVersion[i0].BufferByte );
				}
			}
			if( type == 4258 )
			{
				pMsg->L3L4_Monitor_OMA_WiMAX_Params.Type = (UINT16)type;
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_OMA_WiMAX_Params.BST.FrameNumber );
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_OMA_WiMAX_Params.BST.uSecInFrame );
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_RadioModule_LenOfRadioModule_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_OMA_WiMAX_Params.MonitorOMAWimaxParams.RadioModule.LenOfRadioModule );
				for( i0 = 0; i0 < (UINT32)pMsg->L3L4_Monitor_OMA_WiMAX_Params.MonitorOMAWimaxParams.RadioModule.LenOfRadioModule; i0++ )
				{
					UINT32 i1 = 0;
					for( i1 = 0; i1 < 64; i1++ )
					{
						BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_fwVersion_fwVersion_BufferByte_GET( base_ptr, i0, i1, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_OMA_WiMAX_Params.MonitorOMAWimaxParams.RadioModule.WmxRadioModuleList[i0].fwVersion.fwVersion[i1].BufferByte );
					}
					for( i1 = 0; i1 < 64; i1++ )
					{
						BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_swVersion_swVersion_BufferByte_GET( base_ptr, i0, i1, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_OMA_WiMAX_Params.MonitorOMAWimaxParams.RadioModule.WmxRadioModuleList[i0].swVersion.swVersion[i1].BufferByte );
					}
					for( i1 = 0; i1 < 64; i1++ )
					{
						BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_hwVersion_hwVersion_BufferByte_GET( base_ptr, i0, i1, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_OMA_WiMAX_Params.MonitorOMAWimaxParams.RadioModule.WmxRadioModuleList[i0].hwVersion.hwVersion[i1].BufferByte );
					}
					for( i1 = 0; i1 < 64; i1++ )
					{
						BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_manufacturer_manufacturer_BufferByte_GET( base_ptr, i0, i1, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_OMA_WiMAX_Params.MonitorOMAWimaxParams.RadioModule.WmxRadioModuleList[i0].manufacturer.manufacturer[i1].BufferByte );
					}
					for( i1 = 0; i1 < 64; i1++ )
					{
						BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_model_model_BufferByte_GET( base_ptr, i0, i1, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_OMA_WiMAX_Params.MonitorOMAWimaxParams.RadioModule.WmxRadioModuleList[i0].model.model[i1].BufferByte );
					}
					for( i1 = 0; i1 < 64; i1++ )
					{
						BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_macAddress_macAddress_BufferByte_GET( base_ptr, i0, i1, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_OMA_WiMAX_Params.MonitorOMAWimaxParams.RadioModule.WmxRadioModuleList[i0].macAddress.macAddress[i1].BufferByte );
					}
					BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_SpLock_lockStatus_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_OMA_WiMAX_Params.MonitorOMAWimaxParams.RadioModule.WmxRadioModuleList[i0].SpLock.lockStatus );
					for( i1 = 0; i1 < 100; i1++ )
					{
						BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_SpLock_operatorName_operatorName_BufferByte_GET( base_ptr, i0, i1, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_OMA_WiMAX_Params.MonitorOMAWimaxParams.RadioModule.WmxRadioModuleList[i0].SpLock.operatorName.operatorName[i1].BufferByte );
					}
					for( i1 = 0; i1 < 176; i1++ )
					{
						BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_SpLock_lockMem_lockMem_BufferByte_GET( base_ptr, i0, i1, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_OMA_WiMAX_Params.MonitorOMAWimaxParams.RadioModule.WmxRadioModuleList[i0].SpLock.lockMem.lockMem[i1].BufferByte );
					}
				}
				for( i0 = 0; i0 < 64; i0++ )
				{
					BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_TerminalEquipment_devType_devType_BufferByte_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_OMA_WiMAX_Params.MonitorOMAWimaxParams.TerminalEquipment.devType.devType[i0].BufferByte );
				}
				for( i0 = 0; i0 < 64; i0++ )
				{
					BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_TerminalEquipment_devID_devID_BufferByte_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_OMA_WiMAX_Params.MonitorOMAWimaxParams.TerminalEquipment.devID.devID[i0].BufferByte );
				}
				for( i0 = 0; i0 < 64; i0++ )
				{
					BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_TerminalEquipment_staticTermEquip_fwVersion_fwVersion_BufferByte_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_OMA_WiMAX_Params.MonitorOMAWimaxParams.TerminalEquipment.staticTermEquip.fwVersion.fwVersion[i0].BufferByte );
				}
				for( i0 = 0; i0 < 64; i0++ )
				{
					BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_TerminalEquipment_staticTermEquip_swVersion_swVersion_BufferByte_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_OMA_WiMAX_Params.MonitorOMAWimaxParams.TerminalEquipment.staticTermEquip.swVersion.swVersion[i0].BufferByte );
				}
				for( i0 = 0; i0 < 64; i0++ )
				{
					BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_TerminalEquipment_staticTermEquip_hwVersion_hwVersion_BufferByte_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_OMA_WiMAX_Params.MonitorOMAWimaxParams.TerminalEquipment.staticTermEquip.hwVersion.hwVersion[i0].BufferByte );
				}
				for( i0 = 0; i0 < 64; i0++ )
				{
					BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_TerminalEquipment_staticTermEquip_manufacturer_manufacturer_BufferByte_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_OMA_WiMAX_Params.MonitorOMAWimaxParams.TerminalEquipment.staticTermEquip.manufacturer.manufacturer[i0].BufferByte );
				}
				for( i0 = 0; i0 < 64; i0++ )
				{
					BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_TerminalEquipment_staticTermEquip_model_model_BufferByte_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_OMA_WiMAX_Params.MonitorOMAWimaxParams.TerminalEquipment.staticTermEquip.model.model[i0].BufferByte );
				}
			}
			if( type == 4259 )
			{
				pMsg->L3L4_Monitor_OMA_FUMO_Params.Type = (UINT16)type;
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_FUMO_Params_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_OMA_FUMO_Params.BST.FrameNumber );
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_FUMO_Params_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_OMA_FUMO_Params.BST.uSecInFrame );
				for( i0 = 0; i0 < 50; i0++ )
				{
					BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_FUMO_Params_MonitorOMAFumoParams_FUMO_pkgName_pkgName_BufferByte_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_OMA_FUMO_Params.MonitorOMAFumoParams.FUMO.pkgName.pkgName[i0].BufferByte );
				}
				for( i0 = 0; i0 < 50; i0++ )
				{
					BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_FUMO_Params_MonitorOMAFumoParams_FUMO_pkgVersion_pkgVersion_BufferByte_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_OMA_FUMO_Params.MonitorOMAFumoParams.FUMO.pkgVersion.pkgVersion[i0].BufferByte );
				}
				for( i0 = 0; i0 < 260; i0++ )
				{
					BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_FUMO_Params_MonitorOMAFumoParams_FUMO_downloadPkgURL_downloadPkgURL_BufferByte_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_OMA_FUMO_Params.MonitorOMAFumoParams.FUMO.downloadPkgURL.downloadPkgURL[i0].BufferByte );
				}
				for( i0 = 0; i0 < 260; i0++ )
				{
					BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_FUMO_Params_MonitorOMAFumoParams_FUMO_downloadAndUpdatePkgURL_downloadAndUpdatePkgURL_BufferByte_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_OMA_FUMO_Params.MonitorOMAFumoParams.FUMO.downloadAndUpdatePkgURL.downloadAndUpdatePkgURL[i0].BufferByte );
				}
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_FUMO_Params_MonitorOMAFumoParams_FUMO_state_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_OMA_FUMO_Params.MonitorOMAFumoParams.FUMO.state );
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_FUMO_Params_MonitorOMAFumoParams_FUMO_fIsAllocated_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_OMA_FUMO_Params.MonitorOMAFumoParams.FUMO.fIsAllocated );
			}
			if( type == 4261 )
			{
				pMsg->L3L4_Monitor_NAI.Type = (UINT16)type;
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_NAI_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_NAI.BST.FrameNumber );
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_NAI_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_NAI.BST.uSecInFrame );
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_NAI_MonitorNAI_NAISize_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_NAI.MonitorNAI.NAISize );
				for( i0 = 0; i0 < (UINT32)pMsg->L3L4_Monitor_NAI.MonitorNAI.NAISize; i0++ )
				{
					BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_NAI_MonitorNAI_NAI_BufferByte_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_NAI.MonitorNAI.NAI[i0].BufferByte );
				}
			}
			if( type == 4262 )
			{
				pMsg->L3L4_Monitor_ActivationStatusChange.Type = (UINT16)type;
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_ActivationStatusChange_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_ActivationStatusChange.BST.FrameNumber );
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_ActivationStatusChange_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_ActivationStatusChange.BST.uSecInFrame );
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_ActivationStatusChange_MonitorActivationStatusChange_ActivationStatusInd_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_ActivationStatusChange.MonitorActivationStatusChange.ActivationStatusInd );
			}
			if( type == 4263 )
			{
				pMsg->L3L4_Monitor_MCP.Type = (UINT16)type;
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_MCP_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_MCP.BST.FrameNumber );
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_MCP_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_MCP.BST.uSecInFrame );
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_MCP_MonitorMCP_LinkLossInd_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_MCP.MonitorMCP.LinkLossInd );
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_MCP_MonitorMCP_ChannelInfoArray_NumOfChannels_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_MCP.MonitorMCP.ChannelInfoArray.NumOfChannels );
				for( i0 = 0; i0 < (UINT32)pMsg->L3L4_Monitor_MCP.MonitorMCP.ChannelInfoArray.NumOfChannels; i0++ )
				{
					UINT32 i1 = 0;
					BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_MCP_MonitorMCP_ChannelInfoArray_Channels_frequency_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_MCP.MonitorMCP.ChannelInfoArray.Channels[i0].frequency );
					BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_MCP_MonitorMCP_ChannelInfoArray_Channels_bw_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_MCP.MonitorMCP.ChannelInfoArray.Channels[i0].bw );
					BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_MCP_MonitorMCP_ChannelInfoArray_Channels_fft_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_MCP.MonitorMCP.ChannelInfoArray.Channels[i0].fft );
					for( i1 = 0; i1 < 15; i1++ )
					{
						BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_MCP_MonitorMCP_ChannelInfoArray_Channels_Preambles_Preambles_value_GET( base_ptr, i0, i1, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_MCP.MonitorMCP.ChannelInfoArray.Channels[i0].Preambles.Preambles[i1].value );
					}
					BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_MCP_MonitorMCP_ChannelInfoArray_Channels_Preambles_Reserved_1_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_MCP.MonitorMCP.ChannelInfoArray.Channels[i0].Preambles.Reserved_1 );
				}
			}
			if( type == 4264 )
			{
				pMsg->L3L4_Monitor_Installation_Ind.Type = (UINT16)type;
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Installation_Ind_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_Installation_Ind.BST.FrameNumber );
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Installation_Ind_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_Installation_Ind.BST.uSecInFrame );
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Installation_Ind_MonitorInstallationInd_MonitorInstallingInd_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_Installation_Ind.MonitorInstallationInd.MonitorInstallingInd );
			}
			if( type == 4265 )
			{
				pMsg->L3L4_Monitor_Recent_Discover_Nap.Type = (UINT16)type;
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_Recent_Discover_Nap.BST.FrameNumber );
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_Recent_Discover_Nap.BST.uSecInFrame );
				for( i0 = 0; i0 < 3; i0++ )
				{
					BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_MonitorRecentDiscoverNap_NapMember_napID_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_Recent_Discover_Nap.MonitorRecentDiscoverNap.NapMember.napID[i0].value );
				}
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_MonitorRecentDiscoverNap_NapMember_Reserved_1_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_Recent_Discover_Nap.MonitorRecentDiscoverNap.NapMember.Reserved_1 );
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_MonitorRecentDiscoverNap_ChannelInfoArray_NumOfChannels_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_Recent_Discover_Nap.MonitorRecentDiscoverNap.ChannelInfoArray.NumOfChannels );
				for( i0 = 0; i0 < (UINT32)pMsg->L3L4_Monitor_Recent_Discover_Nap.MonitorRecentDiscoverNap.ChannelInfoArray.NumOfChannels; i0++ )
				{
					UINT32 i1 = 0;
					BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_MonitorRecentDiscoverNap_ChannelInfoArray_Channels_frequency_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_Recent_Discover_Nap.MonitorRecentDiscoverNap.ChannelInfoArray.Channels[i0].frequency );
					BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_MonitorRecentDiscoverNap_ChannelInfoArray_Channels_bw_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_Recent_Discover_Nap.MonitorRecentDiscoverNap.ChannelInfoArray.Channels[i0].bw );
					BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_MonitorRecentDiscoverNap_ChannelInfoArray_Channels_fft_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_Recent_Discover_Nap.MonitorRecentDiscoverNap.ChannelInfoArray.Channels[i0].fft );
					for( i1 = 0; i1 < 15; i1++ )
					{
						BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_MonitorRecentDiscoverNap_ChannelInfoArray_Channels_Preambles_Preambles_value_GET( base_ptr, i0, i1, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_Recent_Discover_Nap.MonitorRecentDiscoverNap.ChannelInfoArray.Channels[i0].Preambles.Preambles[i1].value );
					}
					BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_MonitorRecentDiscoverNap_ChannelInfoArray_Channels_Preambles_Reserved_1_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_Recent_Discover_Nap.MonitorRecentDiscoverNap.ChannelInfoArray.Channels[i0].Preambles.Reserved_1 );
				}
				for( i0 = 0; i0 < 6; i0++ )
				{
					BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_MonitorRecentDiscoverNap_bsID_bsID_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_Recent_Discover_Nap.MonitorRecentDiscoverNap.bsID.bsID[i0].value );
				}
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_MonitorRecentDiscoverNap_bsID_Reserved_2_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_Recent_Discover_Nap.MonitorRecentDiscoverNap.bsID.Reserved_2 );
			}
			if( type == 4266 )
			{
				pMsg->L3L4_Monitor_Selected_Channel.Type = (UINT16)type;
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Selected_Channel_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_Selected_Channel.BST.FrameNumber );
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Selected_Channel_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_Selected_Channel.BST.uSecInFrame );
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Selected_Channel_MonitorSelectedChannel_ChannelInfoArray_NumOfChannels_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_Selected_Channel.MonitorSelectedChannel.ChannelInfoArray.NumOfChannels );
				for( i0 = 0; i0 < (UINT32)pMsg->L3L4_Monitor_Selected_Channel.MonitorSelectedChannel.ChannelInfoArray.NumOfChannels; i0++ )
				{
					UINT32 i1 = 0;
					BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Selected_Channel_MonitorSelectedChannel_ChannelInfoArray_Channels_frequency_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_Selected_Channel.MonitorSelectedChannel.ChannelInfoArray.Channels[i0].frequency );
					BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Selected_Channel_MonitorSelectedChannel_ChannelInfoArray_Channels_bw_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_Selected_Channel.MonitorSelectedChannel.ChannelInfoArray.Channels[i0].bw );
					BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Selected_Channel_MonitorSelectedChannel_ChannelInfoArray_Channels_fft_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_Selected_Channel.MonitorSelectedChannel.ChannelInfoArray.Channels[i0].fft );
					for( i1 = 0; i1 < 15; i1++ )
					{
						BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Selected_Channel_MonitorSelectedChannel_ChannelInfoArray_Channels_Preambles_Preambles_value_GET( base_ptr, i0, i1, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_Selected_Channel.MonitorSelectedChannel.ChannelInfoArray.Channels[i0].Preambles.Preambles[i1].value );
					}
					BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Selected_Channel_MonitorSelectedChannel_ChannelInfoArray_Channels_Preambles_Reserved_1_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->L3L4_Monitor_Selected_Channel.MonitorSelectedChannel.ChannelInfoArray.Channels[i0].Preambles.Reserved_1 );
				}
			}

			BM_MonitorBuffer_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
			listSize -= length;
			listSize -= 4;
		}
	}

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_Set_MonitorBuffer(UINT8* pBuf, MonitorBuffer_type msg)
{
	PVOID base_ptr = pBuf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE, j = 0, i0 = 0;


	BM_MonitorBuffer_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );
	if( msg.L3L4_L3MonitorGroupL1_DiagnosticsTpc.Type == 4053 )
	{
		BM_MonitorBuffer_List_SET_TYPE( cur_ptr, cur_bitoff, 4053 );
		length = 50;
		BM_MonitorBuffer_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsTpc.BST.FrameNumber );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsTpc.BST.uSecInFrame );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_PowerPerToneCur_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsTpc.dmTpc.PowerPerToneCur );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_PowerPerToneAvg_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsTpc.dmTpc.PowerPerToneAvg );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_PathLoss_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsTpc.dmTpc.PathLoss );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_Headroom_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsTpc.dmTpc.Headroom );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_Reserved_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsTpc.dmTpc.Reserved );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_powerControlMode_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsTpc.dmTpc.powerControlMode );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_isTx_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsTpc.dmTpc.isTx );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_CurrentFrameTxPower_Total_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsTpc.dmTpc.CurrentFrameTxPower.Total );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_CurrentFrameTxPower_NumOfSubchannels_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsTpc.dmTpc.CurrentFrameTxPower.NumOfSubchannels );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_CurrentFrameTxPower_AllocationType_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsTpc.dmTpc.CurrentFrameTxPower.AllocationType );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ExtremePowerValues_MaxPower_Total_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsTpc.dmTpc.ExtremePowerValues.MaxPower.Total );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ExtremePowerValues_MaxPower_NumOfSubchannels_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsTpc.dmTpc.ExtremePowerValues.MaxPower.NumOfSubchannels );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ExtremePowerValues_MaxPower_AllocationType_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsTpc.dmTpc.ExtremePowerValues.MaxPower.AllocationType );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ExtremePowerValues_MinPower_Total_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsTpc.dmTpc.ExtremePowerValues.MinPower.Total );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ExtremePowerValues_MinPower_NumOfSubchannels_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsTpc.dmTpc.ExtremePowerValues.MinPower.NumOfSubchannels );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ExtremePowerValues_MinPower_AllocationType_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsTpc.dmTpc.ExtremePowerValues.MinPower.AllocationType );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_offsetBSperSS_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsTpc.dmTpc.offsetBSperSS );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_offsetSSperSS_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsTpc.dmTpc.offsetSSperSS );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_cqiAckPeriodicRangingNI_valid_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsTpc.dmTpc.ulNoiseAndInterferenceLevel.cqiAckPeriodicRangingNI.valid );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_cqiAckPeriodicRangingNI_level_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsTpc.dmTpc.ulNoiseAndInterferenceLevel.cqiAckPeriodicRangingNI.level );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_puscNI_valid_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsTpc.dmTpc.ulNoiseAndInterferenceLevel.puscNI.valid );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_puscNI_level_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsTpc.dmTpc.ulNoiseAndInterferenceLevel.puscNI.level );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_amcNI_valid_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsTpc.dmTpc.ulNoiseAndInterferenceLevel.amcNI.valid );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_amcNI_level_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsTpc.dmTpc.ulNoiseAndInterferenceLevel.amcNI.level );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_periodicRangingNI_valid_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsTpc.dmTpc.ulNoiseAndInterferenceLevel.periodicRangingNI.valid );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_periodicRangingNI_level_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsTpc.dmTpc.ulNoiseAndInterferenceLevel.periodicRangingNI.level );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_soundingNI_valid_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsTpc.dmTpc.ulNoiseAndInterferenceLevel.soundingNI.valid );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_soundingNI_level_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsTpc.dmTpc.ulNoiseAndInterferenceLevel.soundingNI.level );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_mimoNI_valid_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsTpc.dmTpc.ulNoiseAndInterferenceLevel.mimoNI.valid );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_mimoNI_level_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsTpc.dmTpc.ulNoiseAndInterferenceLevel.mimoNI.level );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_LackOfHeadroomCounter_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsTpc.dmTpc.LackOfHeadroomCounter );
		BM_MonitorBuffer_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.L3L4_L3MonitorGroupL1_DiagnosticsPerformance.Type == 4054 )
	{
		BM_MonitorBuffer_List_SET_TYPE( cur_ptr, cur_bitoff, 4054 );
		length = 108;
		BM_MonitorBuffer_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsPerformance.BST.FrameNumber );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsPerformance.BST.uSecInFrame );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_MapsStatistics_FchRecievedOK_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsPerformance.dmPhyPerformance.MapsStatistics.FchRecievedOK );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_MapsStatistics_FchFailures_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsPerformance.dmPhyPerformance.MapsStatistics.FchFailures );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_MapsStatistics_NormalDlMapRecievedOK_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsPerformance.dmPhyPerformance.MapsStatistics.NormalDlMapRecievedOK );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_MapsStatistics_NormalDlMapHcsError_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsPerformance.dmPhyPerformance.MapsStatistics.NormalDlMapHcsError );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_MapsStatistics_NormalDlMapCrcError_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsPerformance.dmPhyPerformance.MapsStatistics.NormalDlMapCrcError );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_MapsStatistics_NormalUlMapRecievedOK_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsPerformance.dmPhyPerformance.MapsStatistics.NormalUlMapRecievedOK );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_MapsStatistics_NormalUlMapHcsError_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsPerformance.dmPhyPerformance.MapsStatistics.NormalUlMapHcsError );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_MapsStatistics_NormalUlMapCrcError_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsPerformance.dmPhyPerformance.MapsStatistics.NormalUlMapCrcError );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_MapsStatistics_CompressedMapRecievedOK_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsPerformance.dmPhyPerformance.MapsStatistics.CompressedMapRecievedOK );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_MapsStatistics_CompressedMapCrcError_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsPerformance.dmPhyPerformance.MapsStatistics.CompressedMapCrcError );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_PreamblePCinr_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsPerformance.dmPhyPerformance.l1Measurements.PreamblePCinr );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_PreamblePCinrAnt0_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsPerformance.dmPhyPerformance.l1Measurements.PreamblePCinrAnt0 );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_PreamblePCinrAnt1_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsPerformance.dmPhyPerformance.l1Measurements.PreamblePCinrAnt1 );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_PreamblePCinrStd_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsPerformance.dmPhyPerformance.l1Measurements.PreamblePCinrStd );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_Rssi_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsPerformance.dmPhyPerformance.l1Measurements.Rssi );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_RssiStd_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsPerformance.dmPhyPerformance.l1Measurements.RssiStd );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_MimoStbcPCinr_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsPerformance.dmPhyPerformance.l1Measurements.MimoStbcPCinr );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_MimoStbcPCinrStd_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsPerformance.dmPhyPerformance.l1Measurements.MimoStbcPCinrStd );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_MimoSmPCinr_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsPerformance.dmPhyPerformance.l1Measurements.MimoSmPCinr );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_MimoSmPCinrStd_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsPerformance.dmPhyPerformance.l1Measurements.MimoSmPCinrStd );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_MimoStbcECinr_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsPerformance.dmPhyPerformance.l1Measurements.MimoStbcECinr );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_MimoSmECinr_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsPerformance.dmPhyPerformance.l1Measurements.MimoSmECinr );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_RxAntModeAutoDetect_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsPerformance.dmPhyPerformance.l1Measurements.RxAntModeAutoDetect );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_Reserved8_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsPerformance.dmPhyPerformance.l1Measurements.Reserved8 );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_Reserved16_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsPerformance.dmPhyPerformance.l1Measurements.Reserved16 );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_cqichCount_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsPerformance.dmPhyPerformance.cqichCount );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_TemperatureInCelsius_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsPerformance.dmPhyPerformance.TemperatureInCelsius );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_RxAntMode_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsPerformance.dmPhyPerformance.RxAntMode );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_Reserved_1_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsPerformance.dmPhyPerformance.Reserved_1 );
		BM_MonitorBuffer_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.L3L4_L3MonitorGroupL1_DiagnosticsConfiguration.Type == 4055 )
	{
		BM_MonitorBuffer_List_SET_TYPE( cur_ptr, cur_bitoff, 4055 );
		length = 24;
		BM_MonitorBuffer_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsConfiguration_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsConfiguration.BST.FrameNumber );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsConfiguration_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsConfiguration.BST.uSecInFrame );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsConfiguration_dmPhyConfiguration_FrequencyOffsetInHz_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsConfiguration.dmPhyConfiguration.FrequencyOffsetInHz );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsConfiguration_dmPhyConfiguration_CenterFrequencyInKHz_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsConfiguration.dmPhyConfiguration.CenterFrequencyInKHz );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsConfiguration_dmPhyConfiguration_transitionGaps_TTG_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsConfiguration.dmPhyConfiguration.transitionGaps.TTG );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsConfiguration_dmPhyConfiguration_transitionGaps_RTG_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsConfiguration.dmPhyConfiguration.transitionGaps.RTG );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsConfiguration_dmPhyConfiguration_RecommendedMIMOMode_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsConfiguration.dmPhyConfiguration.RecommendedMIMOMode );
		BM_MonitorBuffer_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.L3L4_L3MonitorGroupBASIC_STATUS.Type == 4050 )
	{
		BM_MonitorBuffer_List_SET_TYPE( cur_ptr, cur_bitoff, 4050 );
		length = 16;
		BM_MonitorBuffer_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBASIC_STATUS_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupBASIC_STATUS.BST.FrameNumber );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBASIC_STATUS_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupBASIC_STATUS.BST.uSecInFrame );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBASIC_STATUS_FWMonitorGroupBasicStatus_FCH_byte0_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupBASIC_STATUS.FWMonitorGroupBasicStatus.FCH.byte0 );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBASIC_STATUS_FWMonitorGroupBasicStatus_FCH_byte1_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupBASIC_STATUS.FWMonitorGroupBasicStatus.FCH.byte1 );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBASIC_STATUS_FWMonitorGroupBasicStatus_FCH_byte2_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupBASIC_STATUS.FWMonitorGroupBasicStatus.FCH.byte2 );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBASIC_STATUS_FWMonitorGroupBasicStatus_FCH_validity_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupBASIC_STATUS.FWMonitorGroupBasicStatus.FCH.validity );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBASIC_STATUS_FWMonitorGroupBasicStatus_frameRatio_DlSize_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupBASIC_STATUS.FWMonitorGroupBasicStatus.frameRatio.DlSize );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBASIC_STATUS_FWMonitorGroupBasicStatus_frameRatio_UlSize_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupBASIC_STATUS.FWMonitorGroupBasicStatus.frameRatio.UlSize );
		BM_MonitorBuffer_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.L3L4_L3MonitorGroupBURST_STATUS.Type == 4051 )
	{
		BM_MonitorBuffer_List_SET_TYPE( cur_ptr, cur_bitoff, 4051 );
		length = 40;
		BM_MonitorBuffer_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBURST_STATUS_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupBURST_STATUS.BST.FrameNumber );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBURST_STATUS_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupBURST_STATUS.BST.uSecInFrame );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBURST_STATUS_FWMonitorGroupBurstStatus_TotalDLPduCRCCount_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupBURST_STATUS.FWMonitorGroupBurstStatus.TotalDLPduCRCCount );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBURST_STATUS_FWMonitorGroupBurstStatus_TotalDLPduCount_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupBURST_STATUS.FWMonitorGroupBurstStatus.TotalDLPduCount );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBURST_STATUS_FWMonitorGroupBurstStatus_UL_PDU_Size_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupBURST_STATUS.FWMonitorGroupBurstStatus.UL_PDU_Size );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBURST_STATUS_FWMonitorGroupBurstStatus_TotalULPDUSize_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupBURST_STATUS.FWMonitorGroupBurstStatus.TotalULPDUSize );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBURST_STATUS_FWMonitorGroupBurstStatus_TotalUlPduCount_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupBURST_STATUS.FWMonitorGroupBurstStatus.TotalUlPduCount );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBURST_STATUS_FWMonitorGroupBurstStatus_UL_SDU_Size_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupBURST_STATUS.FWMonitorGroupBurstStatus.UL_SDU_Size );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBURST_STATUS_FWMonitorGroupBurstStatus_TotalULSDUSize_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupBURST_STATUS.FWMonitorGroupBurstStatus.TotalULSDUSize );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBURST_STATUS_FWMonitorGroupBurstStatus_TotalUlSduCount_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupBURST_STATUS.FWMonitorGroupBurstStatus.TotalUlSduCount );
		BM_MonitorBuffer_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.L3L4_L3MonitorGroupPER_CIN_STATUS.Type == 4063 )
	{
		BM_MonitorBuffer_List_SET_TYPE( cur_ptr, cur_bitoff, 4063 );
		length = 584;
		BM_MonitorBuffer_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupPER_CIN_STATUS_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupPER_CIN_STATUS.BST.FrameNumber );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupPER_CIN_STATUS_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupPER_CIN_STATUS.BST.uSecInFrame );
		for( i0 = 0; i0 < 16; i0++ )
		{
			BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupPER_CIN_STATUS_Per_CIN_MonitorInfo_L2_perCIN_xDUStatus_PDUInfo_numberOfTxedPDUs_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupPER_CIN_STATUS.Per_CIN_MonitorInfo_L2.perCIN_xDUStatus.PDUInfo[i0].numberOfTxedPDUs );
			BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupPER_CIN_STATUS_Per_CIN_MonitorInfo_L2_perCIN_xDUStatus_PDUInfo_totalBytes_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupPER_CIN_STATUS.Per_CIN_MonitorInfo_L2.perCIN_xDUStatus.PDUInfo[i0].totalBytes );
		}
		for( i0 = 0; i0 < 16; i0++ )
		{
			BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupPER_CIN_STATUS_Per_CIN_MonitorInfo_L2_perCIN_xDUStatus_SDUInfo_numberOfAgedSDUs_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupPER_CIN_STATUS.Per_CIN_MonitorInfo_L2.perCIN_xDUStatus.SDUInfo[i0].numberOfAgedSDUs );
			BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupPER_CIN_STATUS_Per_CIN_MonitorInfo_L2_perCIN_xDUStatus_SDUInfo_totalBytes_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupPER_CIN_STATUS.Per_CIN_MonitorInfo_L2.perCIN_xDUStatus.SDUInfo[i0].totalBytes );
		}
		for( i0 = 0; i0 < 16; i0++ )
		{
			BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupPER_CIN_STATUS_Per_CIN_MonitorInfo_L2_perCIN_BWRStatus_AggregatedBWRInfo_numberOfBWRs_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupPER_CIN_STATUS.Per_CIN_MonitorInfo_L2.perCIN_BWRStatus.AggregatedBWRInfo[i0].numberOfBWRs );
			BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupPER_CIN_STATUS_Per_CIN_MonitorInfo_L2_perCIN_BWRStatus_AggregatedBWRInfo_totalBytes_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupPER_CIN_STATUS.Per_CIN_MonitorInfo_L2.perCIN_BWRStatus.AggregatedBWRInfo[i0].totalBytes );
		}
		for( i0 = 0; i0 < 16; i0++ )
		{
			BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupPER_CIN_STATUS_Per_CIN_MonitorInfo_L2_perCIN_BWRStatus_IncrementalBWRInfo_numberOfBWRs_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupPER_CIN_STATUS.Per_CIN_MonitorInfo_L2.perCIN_BWRStatus.IncrementalBWRInfo[i0].numberOfBWRs );
			BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupPER_CIN_STATUS_Per_CIN_MonitorInfo_L2_perCIN_BWRStatus_IncrementalBWRInfo_totalBytes_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupPER_CIN_STATUS.Per_CIN_MonitorInfo_L2.perCIN_BWRStatus.IncrementalBWRInfo[i0].totalBytes );
		}
		for( i0 = 0; i0 < 16; i0++ )
		{
			BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupPER_CIN_STATUS_Per_CIN_MonitorInfo_L2_perCIN_VQInfo_currentVQInfo_totalBytesPendingInQ_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupPER_CIN_STATUS.Per_CIN_MonitorInfo_L2.perCIN_VQInfo.currentVQInfo[i0].totalBytesPendingInQ );
		}
		BM_MonitorBuffer_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.L3L4_L3MonitorGroupSF_AND_QOS_FLOW_MNGMT.Type == 4064 )
	{
		BM_MonitorBuffer_List_SET_TYPE( cur_ptr, cur_bitoff, 4064 );
		length = 20;
		BM_MonitorBuffer_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupSF_AND_QOS_FLOW_MNGMT_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupSF_AND_QOS_FLOW_MNGMT.BST.FrameNumber );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupSF_AND_QOS_FLOW_MNGMT_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupSF_AND_QOS_FLOW_MNGMT.BST.uSecInFrame );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupSF_AND_QOS_FLOW_MNGMT_L2_MON_TYPE_SF_AND_QOS_FLOW_MNGMT_HARQBurst_TotalGrantsAmountInBytes_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupSF_AND_QOS_FLOW_MNGMT.L2_MON_TYPE_SF_AND_QOS_FLOW_MNGMT.HARQBurst.TotalGrantsAmountInBytes );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupSF_AND_QOS_FLOW_MNGMT_L2_MON_TYPE_SF_AND_QOS_FLOW_MNGMT_NonHARQBurst_TotalGrantsAmountInBytes_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupSF_AND_QOS_FLOW_MNGMT.L2_MON_TYPE_SF_AND_QOS_FLOW_MNGMT.NonHARQBurst.TotalGrantsAmountInBytes );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupSF_AND_QOS_FLOW_MNGMT_L2_MON_TYPE_SF_AND_QOS_FLOW_MNGMT_UIUC14Burst_TotalGrantsAmountInBytes_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupSF_AND_QOS_FLOW_MNGMT.L2_MON_TYPE_SF_AND_QOS_FLOW_MNGMT.UIUC14Burst.TotalGrantsAmountInBytes );
		BM_MonitorBuffer_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.L3L4_L3MonitorGroupL2_LAM_Events.Type == 4066 )
	{
		BM_MonitorBuffer_List_SET_TYPE( cur_ptr, cur_bitoff, 4066 );
		length = 20;
		BM_MonitorBuffer_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL2_LAM_Events_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL2_LAM_Events.BST.FrameNumber );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL2_LAM_Events_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL2_LAM_Events.BST.uSecInFrame );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL2_LAM_Events_L2_LAM_Events_MonitorInfo_CQIParams_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL2_LAM_Events.L2_LAM_Events_MonitorInfo.CQIParams.FrameNumber );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL2_LAM_Events_L2_LAM_Events_MonitorInfo_CQIParams_CQI_Measurement_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL2_LAM_Events.L2_LAM_Events_MonitorInfo.CQIParams.CQI_Measurement );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL2_LAM_Events_L2_LAM_Events_MonitorInfo_CQIParams_ChannelID_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL2_LAM_Events.L2_LAM_Events_MonitorInfo.CQIParams.ChannelID );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL2_LAM_Events_L2_LAM_Events_MonitorInfo_CQIParams_IsMIMOReportFlag_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL2_LAM_Events.L2_LAM_Events_MonitorInfo.CQIParams.IsMIMOReportFlag );
		BM_MonitorBuffer_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.L3L4_L3MonitorGroupL1_DiagnosticsTpcEvents.Type == 4065 )
	{
		BM_MonitorBuffer_List_SET_TYPE( cur_ptr, cur_bitoff, 4065 );
		length = 12;
		BM_MonitorBuffer_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpcEvents_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsTpcEvents.BST.FrameNumber );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpcEvents_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsTpcEvents.BST.uSecInFrame );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpcEvents_dmTpcEvents_TPCModeChange_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_DiagnosticsTpcEvents.dmTpcEvents.TPCModeChange );
		BM_MonitorBuffer_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.L3L4_L3MonitorGroupL1_NBS_PSCAN_Results.Type == 4049 )
	{
		BM_MonitorBuffer_List_SET_TYPE( cur_ptr, cur_bitoff, 4049 );
		length = L4BM_RoundUp4Bytes((UINT32)(msg.L3L4_L3MonitorGroupL1_NBS_PSCAN_Results.dmL1NBSPSCANResults.numOfReportedBs * 24) + 4) + 8;
		BM_MonitorBuffer_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_NBS_PSCAN_Results_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_NBS_PSCAN_Results.BST.FrameNumber );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_NBS_PSCAN_Results_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_NBS_PSCAN_Results.BST.uSecInFrame );
		BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_NBS_PSCAN_Results_dmL1NBSPSCANResults_numOfReportedBs_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_NBS_PSCAN_Results.dmL1NBSPSCANResults.numOfReportedBs );
		for( i0 = 0; i0 < (UINT32)msg.L3L4_L3MonitorGroupL1_NBS_PSCAN_Results.dmL1NBSPSCANResults.numOfReportedBs; i0++ )
		{
			BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_NBS_PSCAN_Results_dmL1NBSPSCANResults_NBSPSCANResult_PHYLinkID_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_NBS_PSCAN_Results.dmL1NBSPSCANResults.NBSPSCANResult[i0].PHYLinkID );
			BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_NBS_PSCAN_Results_dmL1NBSPSCANResults_NBSPSCANResult_NeighbourBSPreambleCINRMeanReuse1_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_NBS_PSCAN_Results.dmL1NBSPSCANResults.NBSPSCANResult[i0].NeighbourBSPreambleCINRMeanReuse1 );
			BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_NBS_PSCAN_Results_dmL1NBSPSCANResults_NBSPSCANResult_NeighbourBSPreambleCINRMeanReuse3_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_NBS_PSCAN_Results.dmL1NBSPSCANResults.NBSPSCANResult[i0].NeighbourBSPreambleCINRMeanReuse3 );
			BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_NBS_PSCAN_Results_dmL1NBSPSCANResults_NBSPSCANResult_NeighbourBSPreambleRSSIMean_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_NBS_PSCAN_Results.dmL1NBSPSCANResults.NBSPSCANResult[i0].NeighbourBSPreambleRSSIMean );
			BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_NBS_PSCAN_Results_dmL1NBSPSCANResults_NBSPSCANResult_NeighbourBSTimeOffset_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_NBS_PSCAN_Results.dmL1NBSPSCANResults.NBSPSCANResult[i0].NeighbourBSTimeOffset );
			BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_NBS_PSCAN_Results_dmL1NBSPSCANResults_NBSPSCANResult_IntraInterFAFlag_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_NBS_PSCAN_Results.dmL1NBSPSCANResults.NBSPSCANResult[i0].IntraInterFAFlag );
			BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_NBS_PSCAN_Results_dmL1NBSPSCANResults_NBSPSCANResult_MeasurementsValidityFlag_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_L3MonitorGroupL1_NBS_PSCAN_Results.dmL1NBSPSCANResults.NBSPSCANResult[i0].MeasurementsValidityFlag );
		}
		BM_MonitorBuffer_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.L3L4_DilloHarqPerfGroup.Type == 4056 )
	{
		BM_MonitorBuffer_List_SET_TYPE( cur_ptr, cur_bitoff, 4056 );
		length = 150;
		BM_MonitorBuffer_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_DilloHarqPerfGroup.BST.FrameNumber );
		BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_DilloHarqPerfGroup.BST.uSecInFrame );
		BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_HarqPerfComp_NacksSent_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_DilloHarqPerfGroup.HarqPerfComp.NacksSent );
		BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_HarqPerfComp_AcksSent_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_DilloHarqPerfGroup.HarqPerfComp.AcksSent );
		BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_HarqPerfComp_DuplicatesRx_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_DilloHarqPerfGroup.HarqPerfComp.DuplicatesRx );
		BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_HarqPerfComp_BurstsTx_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_DilloHarqPerfGroup.HarqPerfComp.BurstsTx );
		BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_HarqPerfComp_BurstsRx_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_DilloHarqPerfGroup.HarqPerfComp.BurstsRx );
		BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_HarqPerfComp_Reserved_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_DilloHarqPerfGroup.HarqPerfComp.Reserved );
		for( i0 = 0; i0 < 16; i0++ )
		{
			BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_HarqPerfComp_RetransUL_Array_Retrans_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_DilloHarqPerfGroup.HarqPerfComp.RetransUL_Array[i0].Retrans );
		}
		for( i0 = 0; i0 < 16; i0++ )
		{
			BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_HarqPerfComp_RetransDL_Array_Retrans_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_DilloHarqPerfGroup.HarqPerfComp.RetransDL_Array[i0].Retrans );
		}
		BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_HarqPerfComp_DropHarqBurstCount_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_DilloHarqPerfGroup.HarqPerfComp.DropHarqBurstCount );
		for( i0 = 0; i0 < 16; i0++ )
		{
			BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_HarqPerfComp_AgingArrayUL_Retrans_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_DilloHarqPerfGroup.HarqPerfComp.AgingArrayUL[i0].Retrans );
		}
		for( i0 = 0; i0 < 16; i0++ )
		{
			BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_HarqPerfComp_AgingArrayDL_Retrans_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_DilloHarqPerfGroup.HarqPerfComp.AgingArrayDL[i0].Retrans );
		}
		BM_MonitorBuffer_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.L3L4_DilloBurstGroup.Type == 4052 )
	{
		BM_MonitorBuffer_List_SET_TYPE( cur_ptr, cur_bitoff, 4052 );
		length = 82;
		BM_MonitorBuffer_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_DilloBurstGroup.BST.FrameNumber );
		BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_DilloBurstGroup.BST.uSecInFrame );
		for( i0 = 0; i0 < 14; i0++ )
		{
			BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_RxBurstsPerMcs_Array_Bursts_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_DilloBurstGroup.BurstStatComp.RxBurstsPerMcs_Array[i0].Bursts );
		}
		for( i0 = 0; i0 < 10; i0++ )
		{
			BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_TxBurstsPerMcs_Array_Bursts_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_DilloBurstGroup.BurstStatComp.TxBurstsPerMcs_Array[i0].Bursts );
		}
		BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_UL_BurstDataZone_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_DilloBurstGroup.BurstStatComp.UL_BurstDataZone );
		BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_DL_BurstDataFecScheme_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_DilloBurstGroup.BurstStatComp.DL_BurstDataFecScheme );
		BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_UL_BurstDataFecScheme_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_DilloBurstGroup.BurstStatComp.UL_BurstDataFecScheme );
		BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_DL_BurstDataCid_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_DilloBurstGroup.BurstStatComp.DL_BurstDataCid );
		BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_DL_BurstDataDiuc_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_DilloBurstGroup.BurstStatComp.DL_BurstDataDiuc );
		BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_UL_BurstDataUiuc_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_DilloBurstGroup.BurstStatComp.UL_BurstDataUiuc );
		BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_DL_BurstDataRepetition_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_DilloBurstGroup.BurstStatComp.DL_BurstDataRepetition );
		BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_UL_BurstDataRepetition_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_DilloBurstGroup.BurstStatComp.UL_BurstDataRepetition );
		BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_UL_TotalFec_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_DilloBurstGroup.BurstStatComp.UL_TotalFec );
		BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_DL_TotalFec_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_DilloBurstGroup.BurstStatComp.DL_TotalFec );
		BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_FecMode_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_DilloBurstGroup.BurstStatComp.FecMode );
		BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_FecTypeID_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_DilloBurstGroup.BurstStatComp.FecTypeID );
		BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_FecNumberOfError_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_DilloBurstGroup.BurstStatComp.FecNumberOfError );
		BM_MonitorBuffer_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.L3L4_MonitorGroupEventCdmaTxAttrib.Type == 4185 )
	{
		BM_MonitorBuffer_List_SET_TYPE( cur_ptr, cur_bitoff, 4185 );
		length = 20;
		BM_MonitorBuffer_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaTxAttrib_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_MonitorGroupEventCdmaTxAttrib.BST.FrameNumber );
		BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaTxAttrib_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_MonitorGroupEventCdmaTxAttrib.BST.uSecInFrame );
		BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaTxAttrib_CdmaTxAttribComp_FrameContainsCdmaTx_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_MonitorGroupEventCdmaTxAttrib.CdmaTxAttribComp.FrameContainsCdmaTx );
		BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaTxAttrib_CdmaTxAttribComp_FrameRefLow_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_MonitorGroupEventCdmaTxAttrib.CdmaTxAttribComp.FrameRefLow );
		BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaTxAttrib_CdmaTxAttribComp_SymbolsRef_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_MonitorGroupEventCdmaTxAttrib.CdmaTxAttribComp.SymbolsRef );
		BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaTxAttrib_CdmaTxAttribComp_SubChRef_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_MonitorGroupEventCdmaTxAttrib.CdmaTxAttribComp.SubChRef );
		BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaTxAttrib_CdmaTxAttribComp_RangingCode_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_MonitorGroupEventCdmaTxAttrib.CdmaTxAttribComp.RangingCode );
		BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaTxAttrib_CdmaTxAttribComp_Reserved_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_MonitorGroupEventCdmaTxAttrib.CdmaTxAttribComp.Reserved );
		BM_MonitorBuffer_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS.Type == 4180 )
	{
		BM_MonitorBuffer_List_SET_TYPE( cur_ptr, cur_bitoff, 4180 );
		length = 36;
		BM_MonitorBuffer_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS.BST.FrameNumber );
		BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS.BST.uSecInFrame );
		BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_FWL2MonitorGroupRangingTraceEvent_DilloCdmaAttributes_xOffset_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS.FWL2MonitorGroupRangingTraceEvent.DilloCdmaAttributes.xOffset );
		BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_FWL2MonitorGroupRangingTraceEvent_DilloCdmaAttributes_yOffset_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS.FWL2MonitorGroupRangingTraceEvent.DilloCdmaAttributes.yOffset );
		BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_FWL2MonitorGroupRangingTraceEvent_DilloCdmaAttributes_codeNumber_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS.FWL2MonitorGroupRangingTraceEvent.DilloCdmaAttributes.codeNumber );
		BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_FWL2MonitorGroupRangingTraceEvent_DilloCdmaAttributes_frameNumber_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS.FWL2MonitorGroupRangingTraceEvent.DilloCdmaAttributes.frameNumber );
		BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_FWL2MonitorGroupRangingTraceEvent_RangingType_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS.FWL2MonitorGroupRangingTraceEvent.RangingType );
		BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_FWL2MonitorGroupRangingTraceEvent_TimingAdjustment_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS.FWL2MonitorGroupRangingTraceEvent.TimingAdjustment );
		BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_FWL2MonitorGroupRangingTraceEvent_PowerLevelAdjust_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS.FWL2MonitorGroupRangingTraceEvent.PowerLevelAdjust );
		BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_FWL2MonitorGroupRangingTraceEvent_InvitingRetries_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS.FWL2MonitorGroupRangingTraceEvent.InvitingRetries );
		BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_FWL2MonitorGroupRangingTraceEvent_ContentionRetries_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS.FWL2MonitorGroupRangingTraceEvent.ContentionRetries );
		BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_FWL2MonitorGroupRangingTraceEvent_rangingStatus_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS.FWL2MonitorGroupRangingTraceEvent.rangingStatus );
		BM_MonitorBuffer_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.L3L4_MonitorGroupEventCdmaBwr.Type == 4184 )
	{
		BM_MonitorBuffer_List_SET_TYPE( cur_ptr, cur_bitoff, 4184 );
		length = 16;
		BM_MonitorBuffer_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaBwr_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_MonitorGroupEventCdmaBwr.BST.FrameNumber );
		BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaBwr_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_MonitorGroupEventCdmaBwr.BST.uSecInFrame );
		BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaBwr_FWCdmaBwrEvent_TotalNumberOfCdmaBwrInit_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_MonitorGroupEventCdmaBwr.FWCdmaBwrEvent.TotalNumberOfCdmaBwrInit );
		BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaBwr_FWCdmaBwrEvent_TotalNumberOfTxCdmaBwr_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_MonitorGroupEventCdmaBwr.FWCdmaBwrEvent.TotalNumberOfTxCdmaBwr );
		BM_MonitorBuffer_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.L3L4_DilloSfAndQosPerformanceGroup.Type == 4060 )
	{
		BM_MonitorBuffer_List_SET_TYPE( cur_ptr, cur_bitoff, 4060 );
		length = 12;
		BM_MonitorBuffer_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_MonitorBuffer_List_CURRENT_L3L4_DilloSfAndQosPerformanceGroup_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_DilloSfAndQosPerformanceGroup.BST.FrameNumber );
		BM_MonitorBuffer_List_CURRENT_L3L4_DilloSfAndQosPerformanceGroup_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_DilloSfAndQosPerformanceGroup.BST.uSecInFrame );
		BM_MonitorBuffer_List_CURRENT_L3L4_DilloSfAndQosPerformanceGroup_DilloSfAndQosPerformanceComp_TotalBytesThroughputOtaDL_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_DilloSfAndQosPerformanceGroup.DilloSfAndQosPerformanceComp.TotalBytesThroughputOtaDL );
		BM_MonitorBuffer_List_CURRENT_L3L4_DilloSfAndQosPerformanceGroup_DilloSfAndQosPerformanceComp_TotalBytesThroughputOtaUL_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_DilloSfAndQosPerformanceGroup.DilloSfAndQosPerformanceComp.TotalBytesThroughputOtaUL );
		BM_MonitorBuffer_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.L3L4_DilloSfAndQosFlowManagementGroup.Type == 4061 )
	{
		BM_MonitorBuffer_List_SET_TYPE( cur_ptr, cur_bitoff, 4061 );
		length = 12;
		BM_MonitorBuffer_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_MonitorBuffer_List_CURRENT_L3L4_DilloSfAndQosFlowManagementGroup_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_DilloSfAndQosFlowManagementGroup.BST.FrameNumber );
		BM_MonitorBuffer_List_CURRENT_L3L4_DilloSfAndQosFlowManagementGroup_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_DilloSfAndQosFlowManagementGroup.BST.uSecInFrame );
		BM_MonitorBuffer_List_CURRENT_L3L4_DilloSfAndQosFlowManagementGroup_DilloSfAndQosFlowManagementComp_GrantsReceiveSlots_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_DilloSfAndQosFlowManagementGroup.DilloSfAndQosFlowManagementComp.GrantsReceiveSlots );
		BM_MonitorBuffer_List_CURRENT_L3L4_DilloSfAndQosFlowManagementGroup_DilloSfAndQosFlowManagementComp_reserved_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_DilloSfAndQosFlowManagementGroup.DilloSfAndQosFlowManagementComp.reserved );
		BM_MonitorBuffer_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.L3L4_DilloPhyConfigurationGroup.Type == 4059 )
	{
		BM_MonitorBuffer_List_SET_TYPE( cur_ptr, cur_bitoff, 4059 );
		length = 132;
		BM_MonitorBuffer_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_MonitorBuffer_List_CURRENT_L3L4_DilloPhyConfigurationGroup_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_DilloPhyConfigurationGroup.BST.FrameNumber );
		BM_MonitorBuffer_List_CURRENT_L3L4_DilloPhyConfigurationGroup_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_DilloPhyConfigurationGroup.BST.uSecInFrame );
		for( i0 = 0; i0 < 14; i0++ )
		{
			BM_MonitorBuffer_List_CURRENT_L3L4_DilloPhyConfigurationGroup_DilloPhyConfigurationComp_DlMcsAllocationTableNoneMimo_Bursts_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_DilloPhyConfigurationGroup.DilloPhyConfigurationComp.DlMcsAllocationTableNoneMimo[i0].Bursts );
		}
		for( i0 = 0; i0 < 14; i0++ )
		{
			BM_MonitorBuffer_List_CURRENT_L3L4_DilloPhyConfigurationGroup_DilloPhyConfigurationComp_DlMcsAllocationTableMatrixA_Bursts_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_DilloPhyConfigurationGroup.DilloPhyConfigurationComp.DlMcsAllocationTableMatrixA[i0].Bursts );
		}
		for( i0 = 0; i0 < 14; i0++ )
		{
			BM_MonitorBuffer_List_CURRENT_L3L4_DilloPhyConfigurationGroup_DilloPhyConfigurationComp_DlMcsAllocationTableMatrixB_Bursts_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_DilloPhyConfigurationGroup.DilloPhyConfigurationComp.DlMcsAllocationTableMatrixB[i0].Bursts );
		}
		for( i0 = 0; i0 < 10; i0++ )
		{
			BM_MonitorBuffer_List_CURRENT_L3L4_DilloPhyConfigurationGroup_DilloPhyConfigurationComp_UlMcsAllocationTableNoneStc_Bursts_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_DilloPhyConfigurationGroup.DilloPhyConfigurationComp.UlMcsAllocationTableNoneStc[i0].Bursts );
		}
		for( i0 = 0; i0 < 10; i0++ )
		{
			BM_MonitorBuffer_List_CURRENT_L3L4_DilloPhyConfigurationGroup_DilloPhyConfigurationComp_UlMcsAllocationTableStc_Bursts_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_DilloPhyConfigurationGroup.DilloPhyConfigurationComp.UlMcsAllocationTableStc[i0].Bursts );
		}
		BM_MonitorBuffer_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.L3L4_DilloMapsGroup.Type == 4062 )
	{
		BM_MonitorBuffer_List_SET_TYPE( cur_ptr, cur_bitoff, 4062 );
		length = 12;
		BM_MonitorBuffer_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_MonitorBuffer_List_CURRENT_L3L4_DilloMapsGroup_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_DilloMapsGroup.BST.FrameNumber );
		BM_MonitorBuffer_List_CURRENT_L3L4_DilloMapsGroup_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_DilloMapsGroup.BST.uSecInFrame );
		BM_MonitorBuffer_List_CURRENT_L3L4_DilloMapsGroup_DilloMapsComp_TotalNumberOfMaps_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_DilloMapsGroup.DilloMapsComp.TotalNumberOfMaps );
		BM_MonitorBuffer_List_CURRENT_L3L4_DilloMapsGroup_DilloMapsComp_TotalBytesOfMaps_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_DilloMapsGroup.DilloMapsComp.TotalBytesOfMaps );
		BM_MonitorBuffer_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.L3L4_BasicStatus_L3.Type == 4101 )
	{
		BM_MonitorBuffer_List_SET_TYPE( cur_ptr, cur_bitoff, 4101 );
		length = 36;
		BM_MonitorBuffer_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_MonitorBuffer_List_CURRENT_L3L4_BasicStatus_L3_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_BasicStatus_L3.BST.FrameNumber );
		BM_MonitorBuffer_List_CURRENT_L3L4_BasicStatus_L3_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_BasicStatus_L3.BST.uSecInFrame );
		BM_MonitorBuffer_List_CURRENT_L3L4_BasicStatus_L3_BasicStatus_L3_frequency_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_BasicStatus_L3.BasicStatus_L3.frequency );
		BM_MonitorBuffer_List_CURRENT_L3L4_BasicStatus_L3_BasicStatus_L3_ulCidNum_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_BasicStatus_L3.BasicStatus_L3.ulCidNum );
		BM_MonitorBuffer_List_CURRENT_L3L4_BasicStatus_L3_BasicStatus_L3_dlCidNum_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_BasicStatus_L3.BasicStatus_L3.dlCidNum );
		BM_MonitorBuffer_List_CURRENT_L3L4_BasicStatus_L3_BasicStatus_L3_preambleIndex_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_BasicStatus_L3.BasicStatus_L3.preambleIndex );
		BM_MonitorBuffer_List_CURRENT_L3L4_BasicStatus_L3_BasicStatus_L3_bandWidth_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_BasicStatus_L3.BasicStatus_L3.bandWidth );
		for( i0 = 0; i0 < 6; i0++ )
		{
			BM_MonitorBuffer_List_CURRENT_L3L4_BasicStatus_L3_BasicStatus_L3_bsId_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_BasicStatus_L3.BasicStatus_L3.bsId[i0].value );
		}
		for( i0 = 0; i0 < 6; i0++ )
		{
			BM_MonitorBuffer_List_CURRENT_L3L4_BasicStatus_L3_BasicStatus_L3_macAddress_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_BasicStatus_L3.BasicStatus_L3.macAddress[i0].value );
		}
		BM_MonitorBuffer_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.L3L4_BurstStatus_L3.Type == 4102 )
	{
		BM_MonitorBuffer_List_SET_TYPE( cur_ptr, cur_bitoff, 4102 );
		length = (UINT32)(msg.L3L4_BurstStatus_L3.BurstStatus_L3.numOfCidInfos * 32) + 32 + 8;
		BM_MonitorBuffer_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_BurstStatus_L3.BST.FrameNumber );
		BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_BurstStatus_L3.BST.uSecInFrame );
		BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_lastDlPduSize_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_BurstStatus_L3.BurstStatus_L3.lastDlPduSize );
		BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_totalDlPdusSize_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_BurstStatus_L3.BurstStatus_L3.totalDlPdusSize );
		BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_dlPduCount_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_BurstStatus_L3.BurstStatus_L3.dlPduCount );
		BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_lastDlSduSize_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_BurstStatus_L3.BurstStatus_L3.lastDlSduSize );
		BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_totalDlSdusSize_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_BurstStatus_L3.BurstStatus_L3.totalDlSdusSize );
		BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_totalUlSduDropCounter_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_BurstStatus_L3.BurstStatus_L3.totalUlSduDropCounter );
		BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_totalDlPdusSizeInLastDlSubFrame_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_BurstStatus_L3.BurstStatus_L3.totalDlPdusSizeInLastDlSubFrame );
		BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_numOfCidInfos_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_BurstStatus_L3.BurstStatus_L3.numOfCidInfos );
		for( i0 = 0; i0 < (UINT32)msg.L3L4_BurstStatus_L3.BurstStatus_L3.numOfCidInfos; i0++ )
		{
			BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_burstStatusPerConnection_CID_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_BurstStatus_L3.BurstStatus_L3.burstStatusPerConnection[i0].CID );
			BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_burstStatusPerConnection_CIN_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_BurstStatus_L3.BurstStatus_L3.burstStatusPerConnection[i0].CIN );
			BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_burstStatusPerConnection_totalUlSduRateLimitDropCount_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_BurstStatus_L3.BurstStatus_L3.burstStatusPerConnection[i0].totalUlSduRateLimitDropCount );
			BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_burstStatusPerConnection_rateUlDropPackets_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_BurstStatus_L3.BurstStatus_L3.burstStatusPerConnection[i0].rateUlDropPackets );
			BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_burstStatusPerConnection_totalDlReceivedPdu_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_BurstStatus_L3.BurstStatus_L3.burstStatusPerConnection[i0].totalDlReceivedPdu );
			BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_burstStatusPerConnection_totalUlTransmittedSdu_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_BurstStatus_L3.BurstStatus_L3.burstStatusPerConnection[i0].totalUlTransmittedSdu );
			BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_burstStatusPerConnection_totalOfPduDlBytes_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_BurstStatus_L3.BurstStatus_L3.burstStatusPerConnection[i0].totalOfPduDlBytes );
			BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_burstStatusPerConnection_totalOfSduDlBytes_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_BurstStatus_L3.BurstStatus_L3.burstStatusPerConnection[i0].totalOfSduDlBytes );
		}
		BM_MonitorBuffer_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.L3L4_SF_QoS_MonitorInfo_L3.Type == 4208 )
	{
		BM_MonitorBuffer_List_SET_TYPE( cur_ptr, cur_bitoff, 4208 );
		length = (UINT32)(msg.L3L4_SF_QoS_MonitorInfo_L3.SF_QoS_MonitorInfo_L3.numOfCidInfos * 36) + 16 + 8;
		BM_MonitorBuffer_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_SF_QoS_MonitorInfo_L3.BST.FrameNumber );
		BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_SF_QoS_MonitorInfo_L3.BST.uSecInFrame );
		BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_numOfCidInfos_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_SF_QoS_MonitorInfo_L3.SF_QoS_MonitorInfo_L3.numOfCidInfos );
		BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_numOfSfCreationSucess_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_SF_QoS_MonitorInfo_L3.SF_QoS_MonitorInfo_L3.numOfSfCreationSucess );
		BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_numOfSfCreationFailure_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_SF_QoS_MonitorInfo_L3.SF_QoS_MonitorInfo_L3.numOfSfCreationFailure );
		BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_numOfSfDeleted_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_SF_QoS_MonitorInfo_L3.SF_QoS_MonitorInfo_L3.numOfSfDeleted );
		for( i0 = 0; i0 < (UINT32)msg.L3L4_SF_QoS_MonitorInfo_L3.SF_QoS_MonitorInfo_L3.numOfCidInfos; i0++ )
		{
			BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_sfId_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_SF_QoS_MonitorInfo_L3.SF_QoS_MonitorInfo_L3.channels[i0].sfId );
			BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_maxSustainedTrafficRate_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_SF_QoS_MonitorInfo_L3.SF_QoS_MonitorInfo_L3.channels[i0].maxSustainedTrafficRate );
			BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_maxTrafficBurst_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_SF_QoS_MonitorInfo_L3.SF_QoS_MonitorInfo_L3.channels[i0].maxTrafficBurst );
			BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_toleratedJitter_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_SF_QoS_MonitorInfo_L3.SF_QoS_MonitorInfo_L3.channels[i0].toleratedJitter );
			BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_maximumLatency_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_SF_QoS_MonitorInfo_L3.SF_QoS_MonitorInfo_L3.channels[i0].maximumLatency );
			BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_unsolicitedGrantInterval_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_SF_QoS_MonitorInfo_L3.SF_QoS_MonitorInfo_L3.channels[i0].unsolicitedGrantInterval );
			BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_minReservedTrafficRate_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_SF_QoS_MonitorInfo_L3.SF_QoS_MonitorInfo_L3.channels[i0].minReservedTrafficRate );
			BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_cid_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_SF_QoS_MonitorInfo_L3.SF_QoS_MonitorInfo_L3.channels[i0].cid );
			BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_sfSchedulingType_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_SF_QoS_MonitorInfo_L3.SF_QoS_MonitorInfo_L3.channels[i0].sfSchedulingType );
			BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_qosParamsSetType_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_SF_QoS_MonitorInfo_L3.SF_QoS_MonitorInfo_L3.channels[i0].qosParamsSetType );
			BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_trafficPrio_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_SF_QoS_MonitorInfo_L3.SF_QoS_MonitorInfo_L3.channels[i0].trafficPrio );
			BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_sfSide_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_SF_QoS_MonitorInfo_L3.SF_QoS_MonitorInfo_L3.channels[i0].sfSide );
		}
		BM_MonitorBuffer_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.L3L4_Arq_MonitorInfo_L3.Type == 4209 )
	{
		BM_MonitorBuffer_List_SET_TYPE( cur_ptr, cur_bitoff, 4209 );
		length = (UINT32)(msg.L3L4_Arq_MonitorInfo_L3.Arq_MonitorInfo_L3.numOfCidInfos * 40) + 4 + 8;
		BM_MonitorBuffer_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Arq_MonitorInfo_L3.BST.FrameNumber );
		BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Arq_MonitorInfo_L3.BST.uSecInFrame );
		BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_numOfCidInfos_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Arq_MonitorInfo_L3.Arq_MonitorInfo_L3.numOfCidInfos );
		for( i0 = 0; i0 < (UINT32)msg.L3L4_Arq_MonitorInfo_L3.Arq_MonitorInfo_L3.numOfCidInfos; i0++ )
		{
			BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_arqInfo_sfId_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Arq_MonitorInfo_L3.Arq_MonitorInfo_L3.arqInfo[i0].sfId );
			BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_arqInfo_arqWindowSize_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Arq_MonitorInfo_L3.Arq_MonitorInfo_L3.arqInfo[i0].arqWindowSize );
			BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_arqInfo_arqTransmitterDelay_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Arq_MonitorInfo_L3.Arq_MonitorInfo_L3.arqInfo[i0].arqTransmitterDelay );
			BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_arqInfo_arqReceiverDelay_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Arq_MonitorInfo_L3.Arq_MonitorInfo_L3.arqInfo[i0].arqReceiverDelay );
			BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_arqInfo_arqBlockLifeTime_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Arq_MonitorInfo_L3.Arq_MonitorInfo_L3.arqInfo[i0].arqBlockLifeTime );
			BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_arqInfo_arqSyncLossTimeout_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Arq_MonitorInfo_L3.Arq_MonitorInfo_L3.arqInfo[i0].arqSyncLossTimeout );
			BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_arqInfo_arqRxPurgeTimeout_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Arq_MonitorInfo_L3.Arq_MonitorInfo_L3.arqInfo[i0].arqRxPurgeTimeout );
			BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_arqInfo_arqBlockSize_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Arq_MonitorInfo_L3.Arq_MonitorInfo_L3.arqInfo[i0].arqBlockSize );
			BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_arqInfo_t22_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Arq_MonitorInfo_L3.Arq_MonitorInfo_L3.arqInfo[i0].t22 );
			BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_arqInfo_arqEnable_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Arq_MonitorInfo_L3.Arq_MonitorInfo_L3.arqInfo[i0].arqEnable );
			BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_arqInfo_arqDeliverInOrder_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Arq_MonitorInfo_L3.Arq_MonitorInfo_L3.arqInfo[i0].arqDeliverInOrder );
		}
		BM_MonitorBuffer_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.L3L4_Harq_MonitorInfo_L3.Type == 4211 )
	{
		BM_MonitorBuffer_List_SET_TYPE( cur_ptr, cur_bitoff, 4211 );
		length = (UINT32)(msg.L3L4_Harq_MonitorInfo_L3.Harq_MonitorInfo_L3.numOfCidInfos * 8) + 4 + 8;
		BM_MonitorBuffer_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_MonitorBuffer_List_CURRENT_L3L4_Harq_MonitorInfo_L3_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Harq_MonitorInfo_L3.BST.FrameNumber );
		BM_MonitorBuffer_List_CURRENT_L3L4_Harq_MonitorInfo_L3_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Harq_MonitorInfo_L3.BST.uSecInFrame );
		BM_MonitorBuffer_List_CURRENT_L3L4_Harq_MonitorInfo_L3_Harq_MonitorInfo_L3_numOfCidInfos_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Harq_MonitorInfo_L3.Harq_MonitorInfo_L3.numOfCidInfos );
		for( i0 = 0; i0 < (UINT32)msg.L3L4_Harq_MonitorInfo_L3.Harq_MonitorInfo_L3.numOfCidInfos; i0++ )
		{
			BM_MonitorBuffer_List_CURRENT_L3L4_Harq_MonitorInfo_L3_Harq_MonitorInfo_L3_harqInfo_harqChannelMapping_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Harq_MonitorInfo_L3.Harq_MonitorInfo_L3.harqInfo[i0].harqChannelMapping );
			BM_MonitorBuffer_List_CURRENT_L3L4_Harq_MonitorInfo_L3_Harq_MonitorInfo_L3_harqInfo_harqEnable_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Harq_MonitorInfo_L3.Harq_MonitorInfo_L3.harqInfo[i0].harqEnable );
			BM_MonitorBuffer_List_CURRENT_L3L4_Harq_MonitorInfo_L3_Harq_MonitorInfo_L3_harqInfo_harqisForReorder_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Harq_MonitorInfo_L3.Harq_MonitorInfo_L3.harqInfo[i0].harqisForReorder );
			BM_MonitorBuffer_List_CURRENT_L3L4_Harq_MonitorInfo_L3_Harq_MonitorInfo_L3_harqInfo_sfId_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Harq_MonitorInfo_L3.Harq_MonitorInfo_L3.harqInfo[i0].sfId );
		}
		BM_MonitorBuffer_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	for( j = 0; j < 3; j++ )
	{
		if( msg.L3L4_MacState_L3[j].Type == 4200 )
		{
			BM_MonitorBuffer_List_SET_TYPE( cur_ptr, cur_bitoff, 4200 );
			length = 12;
			BM_MonitorBuffer_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
			BM_MonitorBuffer_List_CURRENT_L3L4_MacState_L3_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_MacState_L3[j].BST.FrameNumber );
			BM_MonitorBuffer_List_CURRENT_L3L4_MacState_L3_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_MacState_L3[j].BST.uSecInFrame );
			BM_MonitorBuffer_List_CURRENT_L3L4_MacState_L3_MacState_L3_state_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_MacState_L3[j].MacState_L3.state );
			BM_MonitorBuffer_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
			listSize += 4;
			listSize += length;
		}
	}
	if( msg.L3L4_NbrCellList_L3.Type == 4201 )
	{
		BM_MonitorBuffer_List_SET_TYPE( cur_ptr, cur_bitoff, 4201 );
		length = (UINT32)(msg.L3L4_NbrCellList_L3.NbrCellList_L3.numOfIntraFASNbrs * 16) + (UINT32)(msg.L3L4_NbrCellList_L3.NbrCellList_L3.numOfInterFASNbrs * 16) + 4 + 8;
		BM_MonitorBuffer_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_NbrCellList_L3.BST.FrameNumber );
		BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_NbrCellList_L3.BST.uSecInFrame );
		BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_numOfIntraFASNbrs_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_NbrCellList_L3.NbrCellList_L3.numOfIntraFASNbrs );
		BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_numOfInterFASNbrs_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_NbrCellList_L3.NbrCellList_L3.numOfInterFASNbrs );
		for( i0 = 0; i0 < (UINT32)msg.L3L4_NbrCellList_L3.NbrCellList_L3.numOfIntraFASNbrs; i0++ )
		{
			UINT32 i1 = 0;
			BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_intraFaNbrs_rssiMean_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_NbrCellList_L3.NbrCellList_L3.intraFaNbrs[i0].rssiMean );
			BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_intraFaNbrs_cinrMean_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_NbrCellList_L3.NbrCellList_L3.intraFaNbrs[i0].cinrMean );
			BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_intraFaNbrs_preambleId_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_NbrCellList_L3.NbrCellList_L3.intraFaNbrs[i0].preambleId );
			BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_intraFaNbrs_frequency_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_NbrCellList_L3.NbrCellList_L3.intraFaNbrs[i0].frequency );
			BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_intraFaNbrs_bandWidth_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_NbrCellList_L3.NbrCellList_L3.intraFaNbrs[i0].bandWidth );
			for( i1 = 0; i1 < 6; i1++ )
			{
				BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_intraFaNbrs_bsId_value_SET( base_ptr, i0, i1, cur_ptr, cur_bitoff, msg.L3L4_NbrCellList_L3.NbrCellList_L3.intraFaNbrs[i0].bsId[i1].value );
			}
		}
		for( i0 = 0; i0 < (UINT32)msg.L3L4_NbrCellList_L3.NbrCellList_L3.numOfInterFASNbrs; i0++ )
		{
			UINT32 i1 = 0;
			BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_interFaNbrs_rssiMean_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_NbrCellList_L3.NbrCellList_L3.interFaNbrs[i0].rssiMean );
			BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_interFaNbrs_cinrMean_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_NbrCellList_L3.NbrCellList_L3.interFaNbrs[i0].cinrMean );
			BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_interFaNbrs_preambleId_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_NbrCellList_L3.NbrCellList_L3.interFaNbrs[i0].preambleId );
			BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_interFaNbrs_frequency_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_NbrCellList_L3.NbrCellList_L3.interFaNbrs[i0].frequency );
			BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_interFaNbrs_bandWidth_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_NbrCellList_L3.NbrCellList_L3.interFaNbrs[i0].bandWidth );
			for( i1 = 0; i1 < 6; i1++ )
			{
				BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_interFaNbrs_bsId_value_SET( base_ptr, i0, i1, cur_ptr, cur_bitoff, msg.L3L4_NbrCellList_L3.NbrCellList_L3.interFaNbrs[i0].bsId[i1].value );
			}
		}
		BM_MonitorBuffer_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.L3L4_NwEntryMsgLatency_L3.Type == 4203 )
	{
		BM_MonitorBuffer_List_SET_TYPE( cur_ptr, cur_bitoff, 4203 );
		length = 32;
		BM_MonitorBuffer_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_MonitorBuffer_List_CURRENT_L3L4_NwEntryMsgLatency_L3_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_NwEntryMsgLatency_L3.BST.FrameNumber );
		BM_MonitorBuffer_List_CURRENT_L3L4_NwEntryMsgLatency_L3_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_NwEntryMsgLatency_L3.BST.uSecInFrame );
		BM_MonitorBuffer_List_CURRENT_L3L4_NwEntryMsgLatency_L3_NwEntryMsgLatency_L3_initRengLatency_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_NwEntryMsgLatency_L3.NwEntryMsgLatency_L3.initRengLatency );
		BM_MonitorBuffer_List_CURRENT_L3L4_NwEntryMsgLatency_L3_NwEntryMsgLatency_L3_sbcLatency_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_NwEntryMsgLatency_L3.NwEntryMsgLatency_L3.sbcLatency );
		BM_MonitorBuffer_List_CURRENT_L3L4_NwEntryMsgLatency_L3_NwEntryMsgLatency_L3_pkmLatency_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_NwEntryMsgLatency_L3.NwEntryMsgLatency_L3.pkmLatency );
		BM_MonitorBuffer_List_CURRENT_L3L4_NwEntryMsgLatency_L3_NwEntryMsgLatency_L3_regLatency_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_NwEntryMsgLatency_L3.NwEntryMsgLatency_L3.regLatency );
		BM_MonitorBuffer_List_CURRENT_L3L4_NwEntryMsgLatency_L3_NwEntryMsgLatency_L3_dsaLatency_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_NwEntryMsgLatency_L3.NwEntryMsgLatency_L3.dsaLatency );
		BM_MonitorBuffer_List_CURRENT_L3L4_NwEntryMsgLatency_L3_NwEntryMsgLatency_L3_setuUpTime_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_NwEntryMsgLatency_L3.NwEntryMsgLatency_L3.setuUpTime );
		BM_MonitorBuffer_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.L3L4_DcdUcdTimeout_L3.Type == 4206 )
	{
		BM_MonitorBuffer_List_SET_TYPE( cur_ptr, cur_bitoff, 4206 );
		length = 12;
		BM_MonitorBuffer_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_MonitorBuffer_List_CURRENT_L3L4_DcdUcdTimeout_L3_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_DcdUcdTimeout_L3.BST.FrameNumber );
		BM_MonitorBuffer_List_CURRENT_L3L4_DcdUcdTimeout_L3_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_DcdUcdTimeout_L3.BST.uSecInFrame );
		BM_MonitorBuffer_List_CURRENT_L3L4_DcdUcdTimeout_L3_DcdUcdTimeout_L3_countDcdUcdTimeOut_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_DcdUcdTimeout_L3.DcdUcdTimeout_L3.countDcdUcdTimeOut );
		BM_MonitorBuffer_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.L3L4_DSxTimers_L3.Type == 4207 )
	{
		BM_MonitorBuffer_List_SET_TYPE( cur_ptr, cur_bitoff, 4207 );
		length = 16;
		BM_MonitorBuffer_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_MonitorBuffer_List_CURRENT_L3L4_DSxTimers_L3_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_DSxTimers_L3.BST.FrameNumber );
		BM_MonitorBuffer_List_CURRENT_L3L4_DSxTimers_L3_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_DSxTimers_L3.BST.uSecInFrame );
		BM_MonitorBuffer_List_CURRENT_L3L4_DSxTimers_L3_DSxTimers_L3_t7Timeout_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_DSxTimers_L3.DSxTimers_L3.t7Timeout );
		BM_MonitorBuffer_List_CURRENT_L3L4_DSxTimers_L3_DSxTimers_L3_t8Timeout_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_DSxTimers_L3.DSxTimers_L3.t8Timeout );
		BM_MonitorBuffer_List_CURRENT_L3L4_DSxTimers_L3_DSxTimers_L3_t10Timeout_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_DSxTimers_L3.DSxTimers_L3.t10Timeout );
		BM_MonitorBuffer_List_CURRENT_L3L4_DSxTimers_L3_DSxTimers_L3_dsxReqRetries_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_DSxTimers_L3.DSxTimers_L3.dsxReqRetries );
		BM_MonitorBuffer_List_CURRENT_L3L4_DSxTimers_L3_DSxTimers_L3_dsxRspRetries_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_DSxTimers_L3.DSxTimers_L3.dsxRspRetries );
		BM_MonitorBuffer_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.L3L4_Phy_L3.Type == 4210 )
	{
		BM_MonitorBuffer_List_SET_TYPE( cur_ptr, cur_bitoff, 4210 );
		length = 16;
		BM_MonitorBuffer_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_MonitorBuffer_List_CURRENT_L3L4_Phy_L3_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Phy_L3.BST.FrameNumber );
		BM_MonitorBuffer_List_CURRENT_L3L4_Phy_L3_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Phy_L3.BST.uSecInFrame );
		BM_MonitorBuffer_List_CURRENT_L3L4_Phy_L3_Phy_L3_preambleSearchTime_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Phy_L3.Phy_L3.preambleSearchTime );
		BM_MonitorBuffer_List_CURRENT_L3L4_Phy_L3_Phy_L3_numOfPreamble_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Phy_L3.Phy_L3.numOfPreamble );
		BM_MonitorBuffer_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	for( j = 0; j < 5; j++ )
	{
		if( msg.L3L4_LinkLossOccur_L3[j].Type == 4213 )
		{
			BM_MonitorBuffer_List_SET_TYPE( cur_ptr, cur_bitoff, 4213 );
			length = 20;
			BM_MonitorBuffer_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
			BM_MonitorBuffer_List_CURRENT_L3L4_LinkLossOccur_L3_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_LinkLossOccur_L3[j].BST.FrameNumber );
			BM_MonitorBuffer_List_CURRENT_L3L4_LinkLossOccur_L3_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_LinkLossOccur_L3[j].BST.uSecInFrame );
			BM_MonitorBuffer_List_CURRENT_L3L4_LinkLossOccur_L3_LinkLossOccur_L3_occurrenceTime_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_LinkLossOccur_L3[j].LinkLossOccur_L3.occurrenceTime );
			BM_MonitorBuffer_List_CURRENT_L3L4_LinkLossOccur_L3_LinkLossOccur_L3_LastLinkLossReason_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_LinkLossOccur_L3[j].LinkLossOccur_L3.LastLinkLossReason );
			for( i0 = 0; i0 < 6; i0++ )
			{
				BM_MonitorBuffer_List_CURRENT_L3L4_LinkLossOccur_L3_LinkLossOccur_L3_bsId_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_LinkLossOccur_L3[j].LinkLossOccur_L3.bsId[i0].value );
			}
			BM_MonitorBuffer_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
			listSize += 4;
			listSize += length;
		}
	}
	if( msg.L3L4_Moniter_Scan_Config.Type == 4252 )
	{
		BM_MonitorBuffer_List_SET_TYPE( cur_ptr, cur_bitoff, 4252 );
		length = (UINT32)(msg.L3L4_Moniter_Scan_Config.MoniterScanConfig.SetScanParam.NumOfChannels * 24) + 4 + 8;
		BM_MonitorBuffer_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_MonitorBuffer_List_CURRENT_L3L4_Moniter_Scan_Config_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Moniter_Scan_Config.BST.FrameNumber );
		BM_MonitorBuffer_List_CURRENT_L3L4_Moniter_Scan_Config_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Moniter_Scan_Config.BST.uSecInFrame );
		BM_MonitorBuffer_List_CURRENT_L3L4_Moniter_Scan_Config_MoniterScanConfig_SetScanParam_NumOfChannels_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Moniter_Scan_Config.MoniterScanConfig.SetScanParam.NumOfChannels );
		for( i0 = 0; i0 < (UINT32)msg.L3L4_Moniter_Scan_Config.MoniterScanConfig.SetScanParam.NumOfChannels; i0++ )
		{
			UINT32 i1 = 0;
			BM_MonitorBuffer_List_CURRENT_L3L4_Moniter_Scan_Config_MoniterScanConfig_SetScanParam_Channels_Frequency_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Moniter_Scan_Config.MoniterScanConfig.SetScanParam.Channels[i0].Frequency );
			BM_MonitorBuffer_List_CURRENT_L3L4_Moniter_Scan_Config_MoniterScanConfig_SetScanParam_Channels_ChannelId_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Moniter_Scan_Config.MoniterScanConfig.SetScanParam.Channels[i0].ChannelId );
			BM_MonitorBuffer_List_CURRENT_L3L4_Moniter_Scan_Config_MoniterScanConfig_SetScanParam_Channels_Bandwidth_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Moniter_Scan_Config.MoniterScanConfig.SetScanParam.Channels[i0].Bandwidth );
			BM_MonitorBuffer_List_CURRENT_L3L4_Moniter_Scan_Config_MoniterScanConfig_SetScanParam_Channels_Fft_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Moniter_Scan_Config.MoniterScanConfig.SetScanParam.Channels[i0].Fft );
			for( i1 = 0; i1 < 15; i1++ )
			{
				BM_MonitorBuffer_List_CURRENT_L3L4_Moniter_Scan_Config_MoniterScanConfig_SetScanParam_Channels_Preambles_value_SET( base_ptr, i0, i1, cur_ptr, cur_bitoff, msg.L3L4_Moniter_Scan_Config.MoniterScanConfig.SetScanParam.Channels[i0].Preambles[i1].value );
			}
			BM_MonitorBuffer_List_CURRENT_L3L4_Moniter_Scan_Config_MoniterScanConfig_SetScanParam_Channels_Reserved_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Moniter_Scan_Config.MoniterScanConfig.SetScanParam.Channels[i0].Reserved );
		}
		BM_MonitorBuffer_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	for( j = 0; j < 10; j++ )
	{
		if( msg.L3L4_DSPS_Management_MSG[j].Type == 4151 )
		{
			BM_MonitorBuffer_List_SET_TYPE( cur_ptr, cur_bitoff, 4151 );
			length = (UINT32)msg.L3L4_DSPS_Management_MSG[j].DSPS_Management_MSG.tlv_length-8 + 8;
			BM_MonitorBuffer_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
			BM_MonitorBuffer_List_CURRENT_L3L4_DSPS_Management_MSG_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_DSPS_Management_MSG[j].BST.FrameNumber );
			BM_MonitorBuffer_List_CURRENT_L3L4_DSPS_Management_MSG_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_DSPS_Management_MSG[j].BST.uSecInFrame );
			for( i0 = 0; i0 < (UINT32)msg.L3L4_DSPS_Management_MSG[j].DSPS_Management_MSG.tlv_length-8; i0++ )
			{
				BM_MonitorBuffer_List_CURRENT_L3L4_DSPS_Management_MSG_DSPS_Management_MSG_MngmntBufferRun_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_DSPS_Management_MSG[j].DSPS_Management_MSG.MngmntBufferRun[i0].value );
			}
			BM_MonitorBuffer_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
			listSize += 4;
			listSize += length;
		}
	}
	if( msg.L3L4_linkLossStatistics_L3.Type == 4202 )
	{
		BM_MonitorBuffer_List_SET_TYPE( cur_ptr, cur_bitoff, 4202 );
		length = 28;
		BM_MonitorBuffer_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_MonitorBuffer_List_CURRENT_L3L4_linkLossStatistics_L3_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_linkLossStatistics_L3.BST.FrameNumber );
		BM_MonitorBuffer_List_CURRENT_L3L4_linkLossStatistics_L3_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_linkLossStatistics_L3.BST.uSecInFrame );
		BM_MonitorBuffer_List_CURRENT_L3L4_linkLossStatistics_L3_linkLossStatistics_L3_occurrenceTime_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_linkLossStatistics_L3.linkLossStatistics_L3.occurrenceTime );
		BM_MonitorBuffer_List_CURRENT_L3L4_linkLossStatistics_L3_linkLossStatistics_L3_linkLossLatency_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_linkLossStatistics_L3.linkLossStatistics_L3.linkLossLatency );
		BM_MonitorBuffer_List_CURRENT_L3L4_linkLossStatistics_L3_linkLossStatistics_L3_HoRangingLatency_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_linkLossStatistics_L3.linkLossStatistics_L3.HoRangingLatency );
		for( i0 = 0; i0 < 6; i0++ )
		{
			BM_MonitorBuffer_List_CURRENT_L3L4_linkLossStatistics_L3_linkLossStatistics_L3_bsId_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_linkLossStatistics_L3.linkLossStatistics_L3.bsId[i0].value );
		}
		BM_MonitorBuffer_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.L3L4_CoordinateHo_L3.Type == 4215 )
	{
		BM_MonitorBuffer_List_SET_TYPE( cur_ptr, cur_bitoff, 4215 );
		length = (UINT32)(msg.L3L4_CoordinateHo_L3.CoordinateHo_L3.numOfBsInHoReq * 8) + (UINT32)(msg.L3L4_CoordinateHo_L3.CoordinateHo_L3.numOfBsInHoRsp * 8) + 52 + 8;
		BM_MonitorBuffer_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_CoordinateHo_L3.BST.FrameNumber );
		BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_CoordinateHo_L3.BST.uSecInFrame );
		BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_numOfBsInHoReq_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_CoordinateHo_L3.CoordinateHo_L3.numOfBsInHoReq );
		BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_numOfBsInHoRsp_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_CoordinateHo_L3.CoordinateHo_L3.numOfBsInHoRsp );
		BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_HoSuccessCounter_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_CoordinateHo_L3.CoordinateHo_L3.HoSuccessCounter );
		BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_HoFailCounter_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_CoordinateHo_L3.CoordinateHo_L3.HoFailCounter );
		BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_HoAttemptsCounter_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_CoordinateHo_L3.CoordinateHo_L3.HoAttemptsCounter );
		BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_HoRejectsCounter_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_CoordinateHo_L3.CoordinateHo_L3.HoRejectsCounter );
		BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_HoNotRecommendedCounter_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_CoordinateHo_L3.CoordinateHo_L3.HoNotRecommendedCounter );
		BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_numberOfTBSAttempted_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_CoordinateHo_L3.CoordinateHo_L3.numberOfTBSAttempted );
		BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_cancellationWithNormalOperation_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_CoordinateHo_L3.CoordinateHo_L3.cancellationWithNormalOperation );
		BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_cancellationWithReentryProblem_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_CoordinateHo_L3.CoordinateHo_L3.cancellationWithReentryProblem );
		BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_coordHoLatency_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_CoordinateHo_L3.CoordinateHo_L3.coordHoLatency );
		BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_cutOffLatency_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_CoordinateHo_L3.CoordinateHo_L3.cutOffLatency );
		BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_status_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_CoordinateHo_L3.CoordinateHo_L3.status );
		BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_typeId_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_CoordinateHo_L3.CoordinateHo_L3.typeId );
		for( i0 = 0; i0 < (UINT32)msg.L3L4_CoordinateHo_L3.CoordinateHo_L3.numOfBsInHoReq; i0++ )
		{
			UINT32 i1 = 0;
			for( i1 = 0; i1 < 6; i1++ )
			{
				BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_hoReqBsList_bsId_value_SET( base_ptr, i0, i1, cur_ptr, cur_bitoff, msg.L3L4_CoordinateHo_L3.CoordinateHo_L3.hoReqBsList[i0].bsId[i1].value );
			}
		}
		for( i0 = 0; i0 < (UINT32)msg.L3L4_CoordinateHo_L3.CoordinateHo_L3.numOfBsInHoRsp; i0++ )
		{
			UINT32 i1 = 0;
			for( i1 = 0; i1 < 6; i1++ )
			{
				BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_hoRspBsList_bsId_value_SET( base_ptr, i0, i1, cur_ptr, cur_bitoff, msg.L3L4_CoordinateHo_L3.CoordinateHo_L3.hoRspBsList[i0].bsId[i1].value );
			}
		}
		BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_HoTriggersCounter_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_CoordinateHo_L3.CoordinateHo_L3.HoTriggersCounter );
		BM_MonitorBuffer_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.L3L4_McsIndexTable_L3.Type == 4217 )
	{
		BM_MonitorBuffer_List_SET_TYPE( cur_ptr, cur_bitoff, 4217 );
		length = (UINT32)(msg.L3L4_McsIndexTable_L3.McsIndexTable_L3.NumDlburstProfiles * 4) + (UINT32)(msg.L3L4_McsIndexTable_L3.McsIndexTable_L3.NumUlburstProfiles * 4) + 4 + 8;
		BM_MonitorBuffer_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_McsIndexTable_L3.BST.FrameNumber );
		BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_McsIndexTable_L3.BST.uSecInFrame );
		BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_McsIndexTable_L3_NumDlburstProfiles_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_McsIndexTable_L3.McsIndexTable_L3.NumDlburstProfiles );
		BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_McsIndexTable_L3_NumUlburstProfiles_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_McsIndexTable_L3.McsIndexTable_L3.NumUlburstProfiles );
		for( i0 = 0; i0 < (UINT32)msg.L3L4_McsIndexTable_L3.McsIndexTable_L3.NumDlburstProfiles; i0++ )
		{
			BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_McsIndexTable_L3_DlburstProfiles_intervalUsageCode_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_McsIndexTable_L3.McsIndexTable_L3.DlburstProfiles[i0].intervalUsageCode );
			BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_McsIndexTable_L3_DlburstProfiles_fecType_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_McsIndexTable_L3.McsIndexTable_L3.DlburstProfiles[i0].fecType );
			BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_McsIndexTable_L3_DlburstProfiles_fecRate_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_McsIndexTable_L3.McsIndexTable_L3.DlburstProfiles[i0].fecRate );
			BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_McsIndexTable_L3_DlburstProfiles_modulation_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_McsIndexTable_L3.McsIndexTable_L3.DlburstProfiles[i0].modulation );
		}
		for( i0 = 0; i0 < (UINT32)msg.L3L4_McsIndexTable_L3.McsIndexTable_L3.NumUlburstProfiles; i0++ )
		{
			BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_McsIndexTable_L3_UlburstProfiles_intervalUsageCode_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_McsIndexTable_L3.McsIndexTable_L3.UlburstProfiles[i0].intervalUsageCode );
			BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_McsIndexTable_L3_UlburstProfiles_fecType_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_McsIndexTable_L3.McsIndexTable_L3.UlburstProfiles[i0].fecType );
			BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_McsIndexTable_L3_UlburstProfiles_fecRate_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_McsIndexTable_L3.McsIndexTable_L3.UlburstProfiles[i0].fecRate );
			BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_McsIndexTable_L3_UlburstProfiles_modulation_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_McsIndexTable_L3.McsIndexTable_L3.UlburstProfiles[i0].modulation );
		}
		BM_MonitorBuffer_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.L3L4_ScanResult_L3.Type == 4214 )
	{
		BM_MonitorBuffer_List_SET_TYPE( cur_ptr, cur_bitoff, 4214 );
		length = (UINT32)(msg.L3L4_ScanResult_L3.ScanResult_L3.numOfNbrs * 20) + 4 + 8;
		BM_MonitorBuffer_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_MonitorBuffer_List_CURRENT_L3L4_ScanResult_L3_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_ScanResult_L3.BST.FrameNumber );
		BM_MonitorBuffer_List_CURRENT_L3L4_ScanResult_L3_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_ScanResult_L3.BST.uSecInFrame );
		BM_MonitorBuffer_List_CURRENT_L3L4_ScanResult_L3_ScanResult_L3_numOfNbrs_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_ScanResult_L3.ScanResult_L3.numOfNbrs );
		for( i0 = 0; i0 < (UINT32)msg.L3L4_ScanResult_L3.ScanResult_L3.numOfNbrs; i0++ )
		{
			UINT32 i1 = 0;
			BM_MonitorBuffer_List_CURRENT_L3L4_ScanResult_L3_ScanResult_L3_resultNbrs_phyLinkId_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_ScanResult_L3.ScanResult_L3.resultNbrs[i0].phyLinkId );
			BM_MonitorBuffer_List_CURRENT_L3L4_ScanResult_L3_ScanResult_L3_resultNbrs_frequency_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_ScanResult_L3.ScanResult_L3.resultNbrs[i0].frequency );
			BM_MonitorBuffer_List_CURRENT_L3L4_ScanResult_L3_ScanResult_L3_resultNbrs_phyGrade_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_ScanResult_L3.ScanResult_L3.resultNbrs[i0].phyGrade );
			BM_MonitorBuffer_List_CURRENT_L3L4_ScanResult_L3_ScanResult_L3_resultNbrs_preambleId_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_ScanResult_L3.ScanResult_L3.resultNbrs[i0].preambleId );
			BM_MonitorBuffer_List_CURRENT_L3L4_ScanResult_L3_ScanResult_L3_resultNbrs_bandWidth_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_ScanResult_L3.ScanResult_L3.resultNbrs[i0].bandWidth );
			BM_MonitorBuffer_List_CURRENT_L3L4_ScanResult_L3_ScanResult_L3_resultNbrs_bSValidityIndicator_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_ScanResult_L3.ScanResult_L3.resultNbrs[i0].bSValidityIndicator );
			for( i1 = 0; i1 < 6; i1++ )
			{
				BM_MonitorBuffer_List_CURRENT_L3L4_ScanResult_L3_ScanResult_L3_resultNbrs_bsId_value_SET( base_ptr, i0, i1, cur_ptr, cur_bitoff, msg.L3L4_ScanResult_L3.ScanResult_L3.resultNbrs[i0].bsId[i1].value );
			}
		}
		BM_MonitorBuffer_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.L3L4_ScanStatus_L3.Type == 4204 )
	{
		BM_MonitorBuffer_List_SET_TYPE( cur_ptr, cur_bitoff, 4204 );
		length = 16;
		BM_MonitorBuffer_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_MonitorBuffer_List_CURRENT_L3L4_ScanStatus_L3_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_ScanStatus_L3.BST.FrameNumber );
		BM_MonitorBuffer_List_CURRENT_L3L4_ScanStatus_L3_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_ScanStatus_L3.BST.uSecInFrame );
		BM_MonitorBuffer_List_CURRENT_L3L4_ScanStatus_L3_ScanStatus_L3_scanDuration_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_ScanStatus_L3.ScanStatus_L3.scanDuration );
		BM_MonitorBuffer_List_CURRENT_L3L4_ScanStatus_L3_ScanStatus_L3_scanIteration_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_ScanStatus_L3.ScanStatus_L3.scanIteration );
		BM_MonitorBuffer_List_CURRENT_L3L4_ScanStatus_L3_ScanStatus_L3_modeReport_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_ScanStatus_L3.ScanStatus_L3.modeReport );
		BM_MonitorBuffer_List_CURRENT_L3L4_ScanStatus_L3_ScanStatus_L3_periodReport_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_ScanStatus_L3.ScanStatus_L3.periodReport );
		BM_MonitorBuffer_List_CURRENT_L3L4_ScanStatus_L3_ScanStatus_L3_interleavingInterval_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_ScanStatus_L3.ScanStatus_L3.interleavingInterval );
		BM_MonitorBuffer_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.L3L4_ConnectionDropCount_L3.Type == 4205 )
	{
		BM_MonitorBuffer_List_SET_TYPE( cur_ptr, cur_bitoff, 4205 );
		length = 12;
		BM_MonitorBuffer_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_MonitorBuffer_List_CURRENT_L3L4_ConnectionDropCount_L3_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_ConnectionDropCount_L3.BST.FrameNumber );
		BM_MonitorBuffer_List_CURRENT_L3L4_ConnectionDropCount_L3_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_ConnectionDropCount_L3.BST.uSecInFrame );
		BM_MonitorBuffer_List_CURRENT_L3L4_ConnectionDropCount_L3_ConnectionDropCount_L3_counterConnectionDropEvent_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_ConnectionDropCount_L3.ConnectionDropCount_L3.counterConnectionDropEvent );
		BM_MonitorBuffer_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.L3L4_IdleConfiguration_L3.Type == 4212 )
	{
		BM_MonitorBuffer_List_SET_TYPE( cur_ptr, cur_bitoff, 4212 );
		length = 36;
		BM_MonitorBuffer_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_IdleConfiguration_L3.BST.FrameNumber );
		BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_IdleConfiguration_L3.BST.uSecInFrame );
		BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_IdleConfiguration_L3_idleModeTimeout_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_IdleConfiguration_L3.IdleConfiguration_L3.idleModeTimeout );
		BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_IdleConfiguration_L3_pagingCycleReq_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_IdleConfiguration_L3.IdleConfiguration_L3.pagingCycleReq );
		BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_IdleConfiguration_L3_t45Timeout_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_IdleConfiguration_L3.IdleConfiguration_L3.t45Timeout );
		BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_IdleConfiguration_L3_PagingGroupID_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_IdleConfiguration_L3.IdleConfiguration_L3.PagingGroupID );
		BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_IdleConfiguration_L3_PagingCycle_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_IdleConfiguration_L3.IdleConfiguration_L3.PagingCycle );
		BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_IdleConfiguration_L3_PagingOffset_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_IdleConfiguration_L3.IdleConfiguration_L3.PagingOffset );
		BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_IdleConfiguration_L3_RetainInfo_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_IdleConfiguration_L3.IdleConfiguration_L3.RetainInfo );
		BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_IdleConfiguration_L3_dregReqRetries_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_IdleConfiguration_L3.IdleConfiguration_L3.dregReqRetries );
		BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_IdleConfiguration_L3_PagingIntervalLength_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_IdleConfiguration_L3.IdleConfiguration_L3.PagingIntervalLength );
		for( i0 = 0; i0 < 6; i0++ )
		{
			BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_IdleConfiguration_L3_PagingControllerID_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_IdleConfiguration_L3.IdleConfiguration_L3.PagingControllerID[i0].value );
		}
		BM_MonitorBuffer_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.L3L4_IdlePerformance_L3.Type == 4216 )
	{
		BM_MonitorBuffer_List_SET_TYPE( cur_ptr, cur_bitoff, 4216 );
		length = 28;
		BM_MonitorBuffer_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_MonitorBuffer_List_CURRENT_L3L4_IdlePerformance_L3_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_IdlePerformance_L3.BST.FrameNumber );
		BM_MonitorBuffer_List_CURRENT_L3L4_IdlePerformance_L3_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_IdlePerformance_L3.BST.uSecInFrame );
		BM_MonitorBuffer_List_CURRENT_L3L4_IdlePerformance_L3_IdlePerformance_L3_counterInternalTimer_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_IdlePerformance_L3.IdlePerformance_L3.counterInternalTimer );
		BM_MonitorBuffer_List_CURRENT_L3L4_IdlePerformance_L3_IdlePerformance_L3_counterNWInitiated_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_IdlePerformance_L3.IdlePerformance_L3.counterNWInitiated );
		BM_MonitorBuffer_List_CURRENT_L3L4_IdlePerformance_L3_IdlePerformance_L3_counterGroupChange_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_IdlePerformance_L3.IdlePerformance_L3.counterGroupChange );
		BM_MonitorBuffer_List_CURRENT_L3L4_IdlePerformance_L3_IdlePerformance_L3_counterSecuredLu_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_IdlePerformance_L3.IdlePerformance_L3.counterSecuredLu );
		BM_MonitorBuffer_List_CURRENT_L3L4_IdlePerformance_L3_IdlePerformance_L3_counterUnSecuredLu_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_IdlePerformance_L3.IdlePerformance_L3.counterUnSecuredLu );
		BM_MonitorBuffer_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.L3L4_Arq_MonitorRxPerformance_L3.Type == 4103 )
	{
		BM_MonitorBuffer_List_SET_TYPE( cur_ptr, cur_bitoff, 4103 );
		length = (UINT32)(msg.L3L4_Arq_MonitorRxPerformance_L3.Arq_MonitorRxPerformance_L3.numOfCidPerformance * 44) + 8 + 8;
		BM_MonitorBuffer_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Arq_MonitorRxPerformance_L3.BST.FrameNumber );
		BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Arq_MonitorRxPerformance_L3.BST.uSecInFrame );
		BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqResetPerformed_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Arq_MonitorRxPerformance_L3.Arq_MonitorRxPerformance_L3.arqResetPerformed );
		BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_numOfCidPerformance_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Arq_MonitorRxPerformance_L3.Arq_MonitorRxPerformance_L3.numOfCidPerformance );
		for( i0 = 0; i0 < (UINT32)msg.L3L4_Arq_MonitorRxPerformance_L3.Arq_MonitorRxPerformance_L3.numOfCidPerformance; i0++ )
		{
			BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqRxPerformance_CID_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Arq_MonitorRxPerformance_L3.Arq_MonitorRxPerformance_L3.arqRxPerformance[i0].CID );
			BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqRxPerformance_CIN_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Arq_MonitorRxPerformance_L3.Arq_MonitorRxPerformance_L3.arqRxPerformance[i0].CIN );
			BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqRxPerformance_numOfDuplicateReceivedBlocks_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Arq_MonitorRxPerformance_L3.Arq_MonitorRxPerformance_L3.arqRxPerformance[i0].numOfDuplicateReceivedBlocks );
			BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqRxPerformance_numOfPurgeTimeouts_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Arq_MonitorRxPerformance_L3.Arq_MonitorRxPerformance_L3.arqRxPerformance[i0].numOfPurgeTimeouts );
			BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqRxPerformance_numOfBlocksLostDueToRxPurgeTimout_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Arq_MonitorRxPerformance_L3.Arq_MonitorRxPerformance_L3.arqRxPerformance[i0].numOfBlocksLostDueToRxPurgeTimout );
			BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqRxPerformance_totalNumOfAcksTxd_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Arq_MonitorRxPerformance_L3.Arq_MonitorRxPerformance_L3.arqRxPerformance[i0].totalNumOfAcksTxd );
			BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqRxPerformance_numOfRxArqResetsReceived_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Arq_MonitorRxPerformance_L3.Arq_MonitorRxPerformance_L3.arqRxPerformance[i0].numOfRxArqResetsReceived );
			BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqRxPerformance_numOfRxArqResetsInitiated_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Arq_MonitorRxPerformance_L3.Arq_MonitorRxPerformance_L3.arqRxPerformance[i0].numOfRxArqResetsInitiated );
			BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqRxPerformance_numOfArqDiscardsReceived_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Arq_MonitorRxPerformance_L3.Arq_MonitorRxPerformance_L3.arqRxPerformance[i0].numOfArqDiscardsReceived );
			BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqRxPerformance_rxThroughput_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Arq_MonitorRxPerformance_L3.Arq_MonitorRxPerformance_L3.arqRxPerformance[i0].rxThroughput );
			BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqRxPerformance_numOfPduLostDueToNoFreeSpaceInReceiver_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Arq_MonitorRxPerformance_L3.Arq_MonitorRxPerformance_L3.arqRxPerformance[i0].numOfPduLostDueToNoFreeSpaceInReceiver );
		}
		BM_MonitorBuffer_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.L3L4_Arq_MonitorTxPerformance_L3.Type == 4106 )
	{
		BM_MonitorBuffer_List_SET_TYPE( cur_ptr, cur_bitoff, 4106 );
		length = (UINT32)(msg.L3L4_Arq_MonitorTxPerformance_L3.Arq_MonitorTxPerformance_L3.numOfCidPerformance * 48) + 4 + 8;
		BM_MonitorBuffer_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Arq_MonitorTxPerformance_L3.BST.FrameNumber );
		BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Arq_MonitorTxPerformance_L3.BST.uSecInFrame );
		BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_numOfCidPerformance_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Arq_MonitorTxPerformance_L3.Arq_MonitorTxPerformance_L3.numOfCidPerformance );
		for( i0 = 0; i0 < (UINT32)msg.L3L4_Arq_MonitorTxPerformance_L3.Arq_MonitorTxPerformance_L3.numOfCidPerformance; i0++ )
		{
			BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_CID_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Arq_MonitorTxPerformance_L3.Arq_MonitorTxPerformance_L3.arqTxPerformance[i0].CID );
			BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_CIN_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Arq_MonitorTxPerformance_L3.Arq_MonitorTxPerformance_L3.arqTxPerformance[i0].CIN );
			BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_numOfRetransmittedArqBlocksTotalUL_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Arq_MonitorTxPerformance_L3.Arq_MonitorTxPerformance_L3.arqTxPerformance[i0].numOfRetransmittedArqBlocksTotalUL );
			BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_numOfRetransmittedBlocksUL_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Arq_MonitorTxPerformance_L3.Arq_MonitorTxPerformance_L3.arqTxPerformance[i0].numOfRetransmittedBlocksUL );
			BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_numOfBLTs_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Arq_MonitorTxPerformance_L3.Arq_MonitorTxPerformance_L3.arqTxPerformance[i0].numOfBLTs );
			BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_numOfBlocksLostDueToArqBLT_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Arq_MonitorTxPerformance_L3.Arq_MonitorTxPerformance_L3.arqTxPerformance[i0].numOfBlocksLostDueToArqBLT );
			BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_totalNumOfAcksReceived_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Arq_MonitorTxPerformance_L3.Arq_MonitorTxPerformance_L3.arqTxPerformance[i0].totalNumOfAcksReceived );
			BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_numOfTxArqResetsReceived_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Arq_MonitorTxPerformance_L3.Arq_MonitorTxPerformance_L3.arqTxPerformance[i0].numOfTxArqResetsReceived );
			BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_numOfTxArqResetsInitiated_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Arq_MonitorTxPerformance_L3.Arq_MonitorTxPerformance_L3.arqTxPerformance[i0].numOfTxArqResetsInitiated );
			BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_numOfArqDiscardsTxd_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Arq_MonitorTxPerformance_L3.Arq_MonitorTxPerformance_L3.arqTxPerformance[i0].numOfArqDiscardsTxd );
			BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_txThroughput_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Arq_MonitorTxPerformance_L3.Arq_MonitorTxPerformance_L3.arqTxPerformance[i0].txThroughput );
			BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_numOfSduLostDueToNoFreeSpaceInTransmitter_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Arq_MonitorTxPerformance_L3.Arq_MonitorTxPerformance_L3.arqTxPerformance[i0].numOfSduLostDueToNoFreeSpaceInTransmitter );
		}
		BM_MonitorBuffer_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.L3L4_MonitorSfPerformance_L3.Type == 4110 )
	{
		BM_MonitorBuffer_List_SET_TYPE( cur_ptr, cur_bitoff, 4110 );
		length = (UINT32)(msg.L3L4_MonitorSfPerformance_L3.SfPerformance_L3.numOfCidInfos * 16) + 4 + 8;
		BM_MonitorBuffer_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_MonitorBuffer_List_CURRENT_L3L4_MonitorSfPerformance_L3_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_MonitorSfPerformance_L3.BST.FrameNumber );
		BM_MonitorBuffer_List_CURRENT_L3L4_MonitorSfPerformance_L3_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_MonitorSfPerformance_L3.BST.uSecInFrame );
		BM_MonitorBuffer_List_CURRENT_L3L4_MonitorSfPerformance_L3_SfPerformance_L3_numOfCidInfos_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_MonitorSfPerformance_L3.SfPerformance_L3.numOfCidInfos );
		for( i0 = 0; i0 < (UINT32)msg.L3L4_MonitorSfPerformance_L3.SfPerformance_L3.numOfCidInfos; i0++ )
		{
			BM_MonitorBuffer_List_CURRENT_L3L4_MonitorSfPerformance_L3_SfPerformance_L3_SfPeformancePerConnection_CID_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_MonitorSfPerformance_L3.SfPerformance_L3.SfPeformancePerConnection[i0].CID );
			BM_MonitorBuffer_List_CURRENT_L3L4_MonitorSfPerformance_L3_SfPerformance_L3_SfPeformancePerConnection_CIN_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_MonitorSfPerformance_L3.SfPerformance_L3.SfPeformancePerConnection[i0].CIN );
			BM_MonitorBuffer_List_CURRENT_L3L4_MonitorSfPerformance_L3_SfPerformance_L3_SfPeformancePerConnection_ulIpThroughput_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_MonitorSfPerformance_L3.SfPerformance_L3.SfPeformancePerConnection[i0].ulIpThroughput );
			BM_MonitorBuffer_List_CURRENT_L3L4_MonitorSfPerformance_L3_SfPerformance_L3_SfPeformancePerConnection_dlIpThroughput_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_MonitorSfPerformance_L3.SfPerformance_L3.SfPeformancePerConnection[i0].dlIpThroughput );
		}
		BM_MonitorBuffer_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.L3L4_Monitor_Scan_Result.Type == 4253 )
	{
		BM_MonitorBuffer_List_SET_TYPE( cur_ptr, cur_bitoff, 4253 );
		length = (UINT32)(msg.L3L4_Monitor_Scan_Result.MonitorScanResult.AvailableNSPsIdlist.NumOfNSPs * 4) + 4 + (UINT32)(msg.L3L4_Monitor_Scan_Result.MonitorScanResult.FullBSIDArr.NumOfBSIDs * 16) + 4 + 8;
		BM_MonitorBuffer_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Result_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Monitor_Scan_Result.BST.FrameNumber );
		BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Result_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Monitor_Scan_Result.BST.uSecInFrame );
		BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Result_MonitorScanResult_AvailableNSPsIdlist_NumOfNSPs_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Monitor_Scan_Result.MonitorScanResult.AvailableNSPsIdlist.NumOfNSPs );
		for( i0 = 0; i0 < (UINT32)msg.L3L4_Monitor_Scan_Result.MonitorScanResult.AvailableNSPsIdlist.NumOfNSPs; i0++ )
		{
			BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Result_MonitorScanResult_AvailableNSPsIdlist_NSPID_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Monitor_Scan_Result.MonitorScanResult.AvailableNSPsIdlist.NSPID[i0].value );
		}
		BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Result_MonitorScanResult_FullBSIDArr_NumOfBSIDs_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Monitor_Scan_Result.MonitorScanResult.FullBSIDArr.NumOfBSIDs );
		for( i0 = 0; i0 < (UINT32)msg.L3L4_Monitor_Scan_Result.MonitorScanResult.FullBSIDArr.NumOfBSIDs; i0++ )
		{
			UINT32 i1 = 0;
			for( i1 = 0; i1 < 6; i1++ )
			{
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Result_MonitorScanResult_FullBSIDArr_FullBSID_bsID_bsID_value_SET( base_ptr, i0, i1, cur_ptr, cur_bitoff, msg.L3L4_Monitor_Scan_Result.MonitorScanResult.FullBSIDArr.FullBSID[i0].bsID.bsID[i1].value );
			}
			BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Result_MonitorScanResult_FullBSIDArr_FullBSID_bsID_Reserved_2_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Monitor_Scan_Result.MonitorScanResult.FullBSIDArr.FullBSID[i0].bsID.Reserved_2 );
			for( i1 = 0; i1 < 6; i1++ )
			{
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Result_MonitorScanResult_FullBSIDArr_FullBSID_bsIDmask_bsIDmask_value_SET( base_ptr, i0, i1, cur_ptr, cur_bitoff, msg.L3L4_Monitor_Scan_Result.MonitorScanResult.FullBSIDArr.FullBSID[i0].bsIDmask.bsIDmask[i1].value );
			}
			BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Result_MonitorScanResult_FullBSIDArr_FullBSID_bsIDmask_Reserved_2_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Monitor_Scan_Result.MonitorScanResult.FullBSIDArr.FullBSID[i0].bsIDmask.Reserved_2 );
		}
		BM_MonitorBuffer_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.L3L4_Monitor_Scan_Ind.Type == 4254 )
	{
		BM_MonitorBuffer_List_SET_TYPE( cur_ptr, cur_bitoff, 4254 );
		length = 20;
		BM_MonitorBuffer_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Ind_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Monitor_Scan_Ind.BST.FrameNumber );
		BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Ind_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Monitor_Scan_Ind.BST.uSecInFrame );
		BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Ind_MonitorScanInd_ScanStartEndInd_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Monitor_Scan_Ind.MonitorScanInd.ScanStartEndInd );
		BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Ind_MonitorScanInd_Time_wHour_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Monitor_Scan_Ind.MonitorScanInd.Time.wHour );
		BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Ind_MonitorScanInd_Time_wMinute_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Monitor_Scan_Ind.MonitorScanInd.Time.wMinute );
		BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Ind_MonitorScanInd_Time_wSecond_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Monitor_Scan_Ind.MonitorScanInd.Time.wSecond );
		BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Ind_MonitorScanInd_Time_wMilliseconds_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Monitor_Scan_Ind.MonitorScanInd.Time.wMilliseconds );
		BM_MonitorBuffer_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.L3L4_Monitor_OMA_Session.Type == 4255 )
	{
		BM_MonitorBuffer_List_SET_TYPE( cur_ptr, cur_bitoff, 4255 );
		length = 12;
		BM_MonitorBuffer_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_Session_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Monitor_OMA_Session.BST.FrameNumber );
		BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_Session_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Monitor_OMA_Session.BST.uSecInFrame );
		BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_Session_MonitorOMASession_OMAStatusInd_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Monitor_OMA_Session.MonitorOMASession.OMAStatusInd );
		BM_MonitorBuffer_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.L3L4_Monitor_Operator.Type == 4256 )
	{
		BM_MonitorBuffer_List_SET_TYPE( cur_ptr, cur_bitoff, 4256 );
		length = (UINT32)(msg.L3L4_Monitor_Operator.MonitorOperator.Eaps.NumOfEaps * 352) + 4 + (UINT32)(msg.L3L4_Monitor_Operator.MonitorOperator.Capls.NumOfNaps * 8) + 4 + (UINT32)(msg.L3L4_Monitor_Operator.MonitorOperator.Rapls.NumOfRoamingPartners * 8) + 8 + 104 + 8;
		BM_MonitorBuffer_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Monitor_Operator.BST.FrameNumber );
		BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Monitor_Operator.BST.uSecInFrame );
		for( i0 = 0; i0 < 100; i0++ )
		{
			BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_operatorName_operatorName_BufferByte_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Monitor_Operator.MonitorOperator.operatorName.operatorName[i0].BufferByte );
		}
		BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_pollingInterval_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Monitor_Operator.MonitorOperator.pollingInterval );
		BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Eaps_NumOfEaps_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Monitor_Operator.MonitorOperator.Eaps.NumOfEaps );
		for( i0 = 0; i0 < (UINT32)msg.L3L4_Monitor_Operator.MonitorOperator.Eaps.NumOfEaps; i0++ )
		{
			UINT32 i1 = 0;
			BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Eaps_EapList_usePrivacy_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Monitor_Operator.MonitorOperator.Eaps.EapList[i0].usePrivacy );
			BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Eaps_EapList_vendorId_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Monitor_Operator.MonitorOperator.Eaps.EapList[i0].vendorId );
			BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Eaps_EapList_vendorType_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Monitor_Operator.MonitorOperator.Eaps.EapList[i0].vendorType );
			BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Eaps_EapList_EAPMethod_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Monitor_Operator.MonitorOperator.Eaps.EapList[i0].EAPMethod );
			for( i1 = 0; i1 < 100; i1++ )
			{
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Eaps_EapList_EapId_EapId_BufferByte_SET( base_ptr, i0, i1, cur_ptr, cur_bitoff, msg.L3L4_Monitor_Operator.MonitorOperator.Eaps.EapList[i0].EapId.EapId[i1].BufferByte );
			}
			for( i1 = 0; i1 < 100; i1++ )
			{
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Eaps_EapList_provisionedPseudoId_provisionedPseudoId_BufferByte_SET( base_ptr, i0, i1, cur_ptr, cur_bitoff, msg.L3L4_Monitor_Operator.MonitorOperator.Eaps.EapList[i0].provisionedPseudoId.provisionedPseudoId[i1].BufferByte );
			}
			for( i1 = 0; i1 < 32; i1++ )
			{
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Eaps_EapList_EapPassword_EapPassword_BufferByte_SET( base_ptr, i0, i1, cur_ptr, cur_bitoff, msg.L3L4_Monitor_Operator.MonitorOperator.Eaps.EapList[i0].EapPassword.EapPassword[i1].BufferByte );
			}
			for( i1 = 0; i1 < 100; i1++ )
			{
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Eaps_EapList_Realm_Realm_BufferByte_SET( base_ptr, i0, i1, cur_ptr, cur_bitoff, msg.L3L4_Monitor_Operator.MonitorOperator.Eaps.EapList[i0].Realm.Realm[i1].BufferByte );
			}
			BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Eaps_EapList_encaps_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Monitor_Operator.MonitorOperator.Eaps.EapList[i0].encaps );
		}
		BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Capls_NumOfNaps_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Monitor_Operator.MonitorOperator.Capls.NumOfNaps );
		for( i0 = 0; i0 < (UINT32)msg.L3L4_Monitor_Operator.MonitorOperator.Capls.NumOfNaps; i0++ )
		{
			UINT32 i1 = 0;
			BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Capls_CaplNapList_priority_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Monitor_Operator.MonitorOperator.Capls.CaplNapList[i0].priority );
			for( i1 = 0; i1 < 3; i1++ )
			{
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Capls_CaplNapList_NapMember_napID_value_SET( base_ptr, i0, i1, cur_ptr, cur_bitoff, msg.L3L4_Monitor_Operator.MonitorOperator.Capls.CaplNapList[i0].NapMember.napID[i1].value );
			}
			BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Capls_CaplNapList_NapMember_Reserved_1_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Monitor_Operator.MonitorOperator.Capls.CaplNapList[i0].NapMember.Reserved_1 );
		}
		BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Rapls_NumOfRoamingPartners_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Monitor_Operator.MonitorOperator.Rapls.NumOfRoamingPartners );
		for( i0 = 0; i0 < (UINT32)msg.L3L4_Monitor_Operator.MonitorOperator.Rapls.NumOfRoamingPartners; i0++ )
		{
			BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Rapls_RaplList_vNspID_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Monitor_Operator.MonitorOperator.Rapls.RaplList[i0].vNspID );
			BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Rapls_RaplList_priority_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Monitor_Operator.MonitorOperator.Rapls.RaplList[i0].priority );
		}
		BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Rapls_Any_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Monitor_Operator.MonitorOperator.Rapls.Any );
		BM_MonitorBuffer_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.L3L4_Monitor_OMAParams.Type == 4257 )
	{
		BM_MonitorBuffer_List_SET_TYPE( cur_ptr, cur_bitoff, 4257 );
		length = 456;
		BM_MonitorBuffer_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMAParams_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Monitor_OMAParams.BST.FrameNumber );
		BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMAParams_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Monitor_OMAParams.BST.uSecInFrame );
		for( i0 = 0; i0 < 64; i0++ )
		{
			BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMAParams_MonitorOMAParams_DeviceInfo_manufacturer_manufacturer_BufferByte_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Monitor_OMAParams.MonitorOMAParams.DeviceInfo.manufacturer.manufacturer[i0].BufferByte );
		}
		for( i0 = 0; i0 < 64; i0++ )
		{
			BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMAParams_MonitorOMAParams_DeviceInfo_model_model_BufferByte_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Monitor_OMAParams.MonitorOMAParams.DeviceInfo.model.model[i0].BufferByte );
		}
		for( i0 = 0; i0 < 64; i0++ )
		{
			BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMAParams_MonitorOMAParams_DeviceInfo_devID_devID_BufferByte_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Monitor_OMAParams.MonitorOMAParams.DeviceInfo.devID.devID[i0].BufferByte );
		}
		for( i0 = 0; i0 < 64; i0++ )
		{
			BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMAParams_MonitorOMAParams_DeviceDetails_devType_devType_BufferByte_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Monitor_OMAParams.MonitorOMAParams.DeviceDetails.devType.devType[i0].BufferByte );
		}
		for( i0 = 0; i0 < 64; i0++ )
		{
			BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMAParams_MonitorOMAParams_DeviceDetails_fwVersion_fwVersion_BufferByte_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Monitor_OMAParams.MonitorOMAParams.DeviceDetails.fwVersion.fwVersion[i0].BufferByte );
		}
		for( i0 = 0; i0 < 64; i0++ )
		{
			BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMAParams_MonitorOMAParams_DeviceDetails_swVersion_swVersion_BufferByte_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Monitor_OMAParams.MonitorOMAParams.DeviceDetails.swVersion.swVersion[i0].BufferByte );
		}
		for( i0 = 0; i0 < 64; i0++ )
		{
			BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMAParams_MonitorOMAParams_DeviceDetails_hwVersion_hwVersion_BufferByte_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Monitor_OMAParams.MonitorOMAParams.DeviceDetails.hwVersion.hwVersion[i0].BufferByte );
		}
		BM_MonitorBuffer_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.L3L4_Monitor_OMA_WiMAX_Params.Type == 4258 )
	{
		BM_MonitorBuffer_List_SET_TYPE( cur_ptr, cur_bitoff, 4258 );
		length = (UINT32)(msg.L3L4_Monitor_OMA_WiMAX_Params.MonitorOMAWimaxParams.RadioModule.LenOfRadioModule * 664) + 4 + 448 + 8;
		BM_MonitorBuffer_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Monitor_OMA_WiMAX_Params.BST.FrameNumber );
		BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Monitor_OMA_WiMAX_Params.BST.uSecInFrame );
		BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_RadioModule_LenOfRadioModule_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Monitor_OMA_WiMAX_Params.MonitorOMAWimaxParams.RadioModule.LenOfRadioModule );
		for( i0 = 0; i0 < (UINT32)msg.L3L4_Monitor_OMA_WiMAX_Params.MonitorOMAWimaxParams.RadioModule.LenOfRadioModule; i0++ )
		{
			UINT32 i1 = 0;
			for( i1 = 0; i1 < 64; i1++ )
			{
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_fwVersion_fwVersion_BufferByte_SET( base_ptr, i0, i1, cur_ptr, cur_bitoff, msg.L3L4_Monitor_OMA_WiMAX_Params.MonitorOMAWimaxParams.RadioModule.WmxRadioModuleList[i0].fwVersion.fwVersion[i1].BufferByte );
			}
			for( i1 = 0; i1 < 64; i1++ )
			{
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_swVersion_swVersion_BufferByte_SET( base_ptr, i0, i1, cur_ptr, cur_bitoff, msg.L3L4_Monitor_OMA_WiMAX_Params.MonitorOMAWimaxParams.RadioModule.WmxRadioModuleList[i0].swVersion.swVersion[i1].BufferByte );
			}
			for( i1 = 0; i1 < 64; i1++ )
			{
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_hwVersion_hwVersion_BufferByte_SET( base_ptr, i0, i1, cur_ptr, cur_bitoff, msg.L3L4_Monitor_OMA_WiMAX_Params.MonitorOMAWimaxParams.RadioModule.WmxRadioModuleList[i0].hwVersion.hwVersion[i1].BufferByte );
			}
			for( i1 = 0; i1 < 64; i1++ )
			{
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_manufacturer_manufacturer_BufferByte_SET( base_ptr, i0, i1, cur_ptr, cur_bitoff, msg.L3L4_Monitor_OMA_WiMAX_Params.MonitorOMAWimaxParams.RadioModule.WmxRadioModuleList[i0].manufacturer.manufacturer[i1].BufferByte );
			}
			for( i1 = 0; i1 < 64; i1++ )
			{
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_model_model_BufferByte_SET( base_ptr, i0, i1, cur_ptr, cur_bitoff, msg.L3L4_Monitor_OMA_WiMAX_Params.MonitorOMAWimaxParams.RadioModule.WmxRadioModuleList[i0].model.model[i1].BufferByte );
			}
			for( i1 = 0; i1 < 64; i1++ )
			{
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_macAddress_macAddress_BufferByte_SET( base_ptr, i0, i1, cur_ptr, cur_bitoff, msg.L3L4_Monitor_OMA_WiMAX_Params.MonitorOMAWimaxParams.RadioModule.WmxRadioModuleList[i0].macAddress.macAddress[i1].BufferByte );
			}
			BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_SpLock_lockStatus_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Monitor_OMA_WiMAX_Params.MonitorOMAWimaxParams.RadioModule.WmxRadioModuleList[i0].SpLock.lockStatus );
			for( i1 = 0; i1 < 100; i1++ )
			{
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_SpLock_operatorName_operatorName_BufferByte_SET( base_ptr, i0, i1, cur_ptr, cur_bitoff, msg.L3L4_Monitor_OMA_WiMAX_Params.MonitorOMAWimaxParams.RadioModule.WmxRadioModuleList[i0].SpLock.operatorName.operatorName[i1].BufferByte );
			}
			for( i1 = 0; i1 < 176; i1++ )
			{
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_SpLock_lockMem_lockMem_BufferByte_SET( base_ptr, i0, i1, cur_ptr, cur_bitoff, msg.L3L4_Monitor_OMA_WiMAX_Params.MonitorOMAWimaxParams.RadioModule.WmxRadioModuleList[i0].SpLock.lockMem.lockMem[i1].BufferByte );
			}
		}
		for( i0 = 0; i0 < 64; i0++ )
		{
			BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_TerminalEquipment_devType_devType_BufferByte_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Monitor_OMA_WiMAX_Params.MonitorOMAWimaxParams.TerminalEquipment.devType.devType[i0].BufferByte );
		}
		for( i0 = 0; i0 < 64; i0++ )
		{
			BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_TerminalEquipment_devID_devID_BufferByte_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Monitor_OMA_WiMAX_Params.MonitorOMAWimaxParams.TerminalEquipment.devID.devID[i0].BufferByte );
		}
		for( i0 = 0; i0 < 64; i0++ )
		{
			BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_TerminalEquipment_staticTermEquip_fwVersion_fwVersion_BufferByte_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Monitor_OMA_WiMAX_Params.MonitorOMAWimaxParams.TerminalEquipment.staticTermEquip.fwVersion.fwVersion[i0].BufferByte );
		}
		for( i0 = 0; i0 < 64; i0++ )
		{
			BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_TerminalEquipment_staticTermEquip_swVersion_swVersion_BufferByte_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Monitor_OMA_WiMAX_Params.MonitorOMAWimaxParams.TerminalEquipment.staticTermEquip.swVersion.swVersion[i0].BufferByte );
		}
		for( i0 = 0; i0 < 64; i0++ )
		{
			BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_TerminalEquipment_staticTermEquip_hwVersion_hwVersion_BufferByte_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Monitor_OMA_WiMAX_Params.MonitorOMAWimaxParams.TerminalEquipment.staticTermEquip.hwVersion.hwVersion[i0].BufferByte );
		}
		for( i0 = 0; i0 < 64; i0++ )
		{
			BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_TerminalEquipment_staticTermEquip_manufacturer_manufacturer_BufferByte_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Monitor_OMA_WiMAX_Params.MonitorOMAWimaxParams.TerminalEquipment.staticTermEquip.manufacturer.manufacturer[i0].BufferByte );
		}
		for( i0 = 0; i0 < 64; i0++ )
		{
			BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_TerminalEquipment_staticTermEquip_model_model_BufferByte_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Monitor_OMA_WiMAX_Params.MonitorOMAWimaxParams.TerminalEquipment.staticTermEquip.model.model[i0].BufferByte );
		}
		BM_MonitorBuffer_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.L3L4_Monitor_OMA_FUMO_Params.Type == 4259 )
	{
		BM_MonitorBuffer_List_SET_TYPE( cur_ptr, cur_bitoff, 4259 );
		length = 636;
		BM_MonitorBuffer_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_FUMO_Params_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Monitor_OMA_FUMO_Params.BST.FrameNumber );
		BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_FUMO_Params_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Monitor_OMA_FUMO_Params.BST.uSecInFrame );
		for( i0 = 0; i0 < 50; i0++ )
		{
			BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_FUMO_Params_MonitorOMAFumoParams_FUMO_pkgName_pkgName_BufferByte_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Monitor_OMA_FUMO_Params.MonitorOMAFumoParams.FUMO.pkgName.pkgName[i0].BufferByte );
		}
		for( i0 = 0; i0 < 50; i0++ )
		{
			BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_FUMO_Params_MonitorOMAFumoParams_FUMO_pkgVersion_pkgVersion_BufferByte_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Monitor_OMA_FUMO_Params.MonitorOMAFumoParams.FUMO.pkgVersion.pkgVersion[i0].BufferByte );
		}
		for( i0 = 0; i0 < 260; i0++ )
		{
			BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_FUMO_Params_MonitorOMAFumoParams_FUMO_downloadPkgURL_downloadPkgURL_BufferByte_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Monitor_OMA_FUMO_Params.MonitorOMAFumoParams.FUMO.downloadPkgURL.downloadPkgURL[i0].BufferByte );
		}
		for( i0 = 0; i0 < 260; i0++ )
		{
			BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_FUMO_Params_MonitorOMAFumoParams_FUMO_downloadAndUpdatePkgURL_downloadAndUpdatePkgURL_BufferByte_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Monitor_OMA_FUMO_Params.MonitorOMAFumoParams.FUMO.downloadAndUpdatePkgURL.downloadAndUpdatePkgURL[i0].BufferByte );
		}
		BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_FUMO_Params_MonitorOMAFumoParams_FUMO_state_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Monitor_OMA_FUMO_Params.MonitorOMAFumoParams.FUMO.state );
		BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_FUMO_Params_MonitorOMAFumoParams_FUMO_fIsAllocated_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Monitor_OMA_FUMO_Params.MonitorOMAFumoParams.FUMO.fIsAllocated );
		BM_MonitorBuffer_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.L3L4_Monitor_NAI.Type == 4261 )
	{
		BM_MonitorBuffer_List_SET_TYPE( cur_ptr, cur_bitoff, 4261 );
		length = (UINT32)msg.L3L4_Monitor_NAI.MonitorNAI.NAISize + 4 + 8;
		BM_MonitorBuffer_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_NAI_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Monitor_NAI.BST.FrameNumber );
		BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_NAI_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Monitor_NAI.BST.uSecInFrame );
		BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_NAI_MonitorNAI_NAISize_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Monitor_NAI.MonitorNAI.NAISize );
		for( i0 = 0; i0 < (UINT32)msg.L3L4_Monitor_NAI.MonitorNAI.NAISize; i0++ )
		{
			BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_NAI_MonitorNAI_NAI_BufferByte_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Monitor_NAI.MonitorNAI.NAI[i0].BufferByte );
		}
		BM_MonitorBuffer_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.L3L4_Monitor_ActivationStatusChange.Type == 4262 )
	{
		BM_MonitorBuffer_List_SET_TYPE( cur_ptr, cur_bitoff, 4262 );
		length = 12;
		BM_MonitorBuffer_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_ActivationStatusChange_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Monitor_ActivationStatusChange.BST.FrameNumber );
		BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_ActivationStatusChange_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Monitor_ActivationStatusChange.BST.uSecInFrame );
		BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_ActivationStatusChange_MonitorActivationStatusChange_ActivationStatusInd_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Monitor_ActivationStatusChange.MonitorActivationStatusChange.ActivationStatusInd );
		BM_MonitorBuffer_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.L3L4_Monitor_MCP.Type == 4263 )
	{
		BM_MonitorBuffer_List_SET_TYPE( cur_ptr, cur_bitoff, 4263 );
		length = (UINT32)(msg.L3L4_Monitor_MCP.MonitorMCP.ChannelInfoArray.NumOfChannels * 28) + 4 + 4 + 8;
		BM_MonitorBuffer_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_MCP_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Monitor_MCP.BST.FrameNumber );
		BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_MCP_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Monitor_MCP.BST.uSecInFrame );
		BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_MCP_MonitorMCP_LinkLossInd_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Monitor_MCP.MonitorMCP.LinkLossInd );
		BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_MCP_MonitorMCP_ChannelInfoArray_NumOfChannels_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Monitor_MCP.MonitorMCP.ChannelInfoArray.NumOfChannels );
		for( i0 = 0; i0 < (UINT32)msg.L3L4_Monitor_MCP.MonitorMCP.ChannelInfoArray.NumOfChannels; i0++ )
		{
			UINT32 i1 = 0;
			BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_MCP_MonitorMCP_ChannelInfoArray_Channels_frequency_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Monitor_MCP.MonitorMCP.ChannelInfoArray.Channels[i0].frequency );
			BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_MCP_MonitorMCP_ChannelInfoArray_Channels_bw_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Monitor_MCP.MonitorMCP.ChannelInfoArray.Channels[i0].bw );
			BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_MCP_MonitorMCP_ChannelInfoArray_Channels_fft_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Monitor_MCP.MonitorMCP.ChannelInfoArray.Channels[i0].fft );
			for( i1 = 0; i1 < 15; i1++ )
			{
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_MCP_MonitorMCP_ChannelInfoArray_Channels_Preambles_Preambles_value_SET( base_ptr, i0, i1, cur_ptr, cur_bitoff, msg.L3L4_Monitor_MCP.MonitorMCP.ChannelInfoArray.Channels[i0].Preambles.Preambles[i1].value );
			}
			BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_MCP_MonitorMCP_ChannelInfoArray_Channels_Preambles_Reserved_1_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Monitor_MCP.MonitorMCP.ChannelInfoArray.Channels[i0].Preambles.Reserved_1 );
		}
		BM_MonitorBuffer_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.L3L4_Monitor_Installation_Ind.Type == 4264 )
	{
		BM_MonitorBuffer_List_SET_TYPE( cur_ptr, cur_bitoff, 4264 );
		length = 12;
		BM_MonitorBuffer_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Installation_Ind_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Monitor_Installation_Ind.BST.FrameNumber );
		BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Installation_Ind_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Monitor_Installation_Ind.BST.uSecInFrame );
		BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Installation_Ind_MonitorInstallationInd_MonitorInstallingInd_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Monitor_Installation_Ind.MonitorInstallationInd.MonitorInstallingInd );
		BM_MonitorBuffer_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.L3L4_Monitor_Recent_Discover_Nap.Type == 4265 )
	{
		BM_MonitorBuffer_List_SET_TYPE( cur_ptr, cur_bitoff, 4265 );
		length = (UINT32)(msg.L3L4_Monitor_Recent_Discover_Nap.MonitorRecentDiscoverNap.ChannelInfoArray.NumOfChannels * 28) + 4 + 12 + 8;
		BM_MonitorBuffer_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Monitor_Recent_Discover_Nap.BST.FrameNumber );
		BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Monitor_Recent_Discover_Nap.BST.uSecInFrame );
		for( i0 = 0; i0 < 3; i0++ )
		{
			BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_MonitorRecentDiscoverNap_NapMember_napID_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Monitor_Recent_Discover_Nap.MonitorRecentDiscoverNap.NapMember.napID[i0].value );
		}
		BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_MonitorRecentDiscoverNap_NapMember_Reserved_1_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Monitor_Recent_Discover_Nap.MonitorRecentDiscoverNap.NapMember.Reserved_1 );
		BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_MonitorRecentDiscoverNap_ChannelInfoArray_NumOfChannels_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Monitor_Recent_Discover_Nap.MonitorRecentDiscoverNap.ChannelInfoArray.NumOfChannels );
		for( i0 = 0; i0 < (UINT32)msg.L3L4_Monitor_Recent_Discover_Nap.MonitorRecentDiscoverNap.ChannelInfoArray.NumOfChannels; i0++ )
		{
			UINT32 i1 = 0;
			BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_MonitorRecentDiscoverNap_ChannelInfoArray_Channels_frequency_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Monitor_Recent_Discover_Nap.MonitorRecentDiscoverNap.ChannelInfoArray.Channels[i0].frequency );
			BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_MonitorRecentDiscoverNap_ChannelInfoArray_Channels_bw_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Monitor_Recent_Discover_Nap.MonitorRecentDiscoverNap.ChannelInfoArray.Channels[i0].bw );
			BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_MonitorRecentDiscoverNap_ChannelInfoArray_Channels_fft_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Monitor_Recent_Discover_Nap.MonitorRecentDiscoverNap.ChannelInfoArray.Channels[i0].fft );
			for( i1 = 0; i1 < 15; i1++ )
			{
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_MonitorRecentDiscoverNap_ChannelInfoArray_Channels_Preambles_Preambles_value_SET( base_ptr, i0, i1, cur_ptr, cur_bitoff, msg.L3L4_Monitor_Recent_Discover_Nap.MonitorRecentDiscoverNap.ChannelInfoArray.Channels[i0].Preambles.Preambles[i1].value );
			}
			BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_MonitorRecentDiscoverNap_ChannelInfoArray_Channels_Preambles_Reserved_1_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Monitor_Recent_Discover_Nap.MonitorRecentDiscoverNap.ChannelInfoArray.Channels[i0].Preambles.Reserved_1 );
		}
		for( i0 = 0; i0 < 6; i0++ )
		{
			BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_MonitorRecentDiscoverNap_bsID_bsID_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Monitor_Recent_Discover_Nap.MonitorRecentDiscoverNap.bsID.bsID[i0].value );
		}
		BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_MonitorRecentDiscoverNap_bsID_Reserved_2_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Monitor_Recent_Discover_Nap.MonitorRecentDiscoverNap.bsID.Reserved_2 );
		BM_MonitorBuffer_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.L3L4_Monitor_Selected_Channel.Type == 4266 )
	{
		BM_MonitorBuffer_List_SET_TYPE( cur_ptr, cur_bitoff, 4266 );
		length = (UINT32)(msg.L3L4_Monitor_Selected_Channel.MonitorSelectedChannel.ChannelInfoArray.NumOfChannels * 28) + 4 + 8;
		BM_MonitorBuffer_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Selected_Channel_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Monitor_Selected_Channel.BST.FrameNumber );
		BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Selected_Channel_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Monitor_Selected_Channel.BST.uSecInFrame );
		BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Selected_Channel_MonitorSelectedChannel_ChannelInfoArray_NumOfChannels_SET( base_ptr, cur_ptr, cur_bitoff, msg.L3L4_Monitor_Selected_Channel.MonitorSelectedChannel.ChannelInfoArray.NumOfChannels );
		for( i0 = 0; i0 < (UINT32)msg.L3L4_Monitor_Selected_Channel.MonitorSelectedChannel.ChannelInfoArray.NumOfChannels; i0++ )
		{
			UINT32 i1 = 0;
			BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Selected_Channel_MonitorSelectedChannel_ChannelInfoArray_Channels_frequency_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Monitor_Selected_Channel.MonitorSelectedChannel.ChannelInfoArray.Channels[i0].frequency );
			BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Selected_Channel_MonitorSelectedChannel_ChannelInfoArray_Channels_bw_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Monitor_Selected_Channel.MonitorSelectedChannel.ChannelInfoArray.Channels[i0].bw );
			BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Selected_Channel_MonitorSelectedChannel_ChannelInfoArray_Channels_fft_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Monitor_Selected_Channel.MonitorSelectedChannel.ChannelInfoArray.Channels[i0].fft );
			for( i1 = 0; i1 < 15; i1++ )
			{
				BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Selected_Channel_MonitorSelectedChannel_ChannelInfoArray_Channels_Preambles_Preambles_value_SET( base_ptr, i0, i1, cur_ptr, cur_bitoff, msg.L3L4_Monitor_Selected_Channel.MonitorSelectedChannel.ChannelInfoArray.Channels[i0].Preambles.Preambles[i1].value );
			}
			BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Selected_Channel_MonitorSelectedChannel_ChannelInfoArray_Channels_Preambles_Reserved_1_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.L3L4_Monitor_Selected_Channel.MonitorSelectedChannel.ChannelInfoArray.Channels[i0].Preambles.Reserved_1 );
		}
		BM_MonitorBuffer_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}

	BM_MonitorBuffer_Header_Type_SET( base_ptr, L3_L4_OPCODE_REPORT_MONITOR_EVACUATE );
	BM_MonitorBuffer_Header_Version_SET( base_ptr, msg.header.Version );
	BM_MonitorBuffer_Header_Accessibility_SET( base_ptr, msg.header.Accessibility );
	BM_MonitorBuffer_Header_Status_SET( base_ptr, msg.header.Status );
	BM_MonitorBuffer_Header_Length_SET( base_ptr, listSize );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_generic_Set_MonitorBuffer(UINT8* pBuf, MonitorBuffer_type* msg)
{
	return L4BM_Set_MonitorBuffer(pBuf, *msg);
}
UINT L4BM_GetBufferSize_MonitorBuffer(MonitorBuffer_type msg)
{
	UINT32 length = HEADER_SIZE, j = 0;

	if( msg.L3L4_L3MonitorGroupL1_DiagnosticsTpc.Type == 4053 )
	{
		length += 50;
		length += 4;
	}
	if( msg.L3L4_L3MonitorGroupL1_DiagnosticsPerformance.Type == 4054 )
	{
		length += 108;
		length += 4;
	}
	if( msg.L3L4_L3MonitorGroupL1_DiagnosticsConfiguration.Type == 4055 )
	{
		length += 24;
		length += 4;
	}
	if( msg.L3L4_L3MonitorGroupBASIC_STATUS.Type == 4050 )
	{
		length += 16;
		length += 4;
	}
	if( msg.L3L4_L3MonitorGroupBURST_STATUS.Type == 4051 )
	{
		length += 40;
		length += 4;
	}
	if( msg.L3L4_L3MonitorGroupPER_CIN_STATUS.Type == 4063 )
	{
		length += 584;
		length += 4;
	}
	if( msg.L3L4_L3MonitorGroupSF_AND_QOS_FLOW_MNGMT.Type == 4064 )
	{
		length += 20;
		length += 4;
	}
	if( msg.L3L4_L3MonitorGroupL2_LAM_Events.Type == 4066 )
	{
		length += 20;
		length += 4;
	}
	if( msg.L3L4_L3MonitorGroupL1_DiagnosticsTpcEvents.Type == 4065 )
	{
		length += 12;
		length += 4;
	}
	if( msg.L3L4_L3MonitorGroupL1_NBS_PSCAN_Results.Type == 4049 )
	{
		length += L4BM_RoundUp4Bytes((UINT32)(msg.L3L4_L3MonitorGroupL1_NBS_PSCAN_Results.dmL1NBSPSCANResults.numOfReportedBs * 24) + 4) + 8;
		length += 4;
	}
	if( msg.L3L4_DilloHarqPerfGroup.Type == 4056 )
	{
		length += 150;
		length += 4;
	}
	if( msg.L3L4_DilloBurstGroup.Type == 4052 )
	{
		length += 82;
		length += 4;
	}
	if( msg.L3L4_MonitorGroupEventCdmaTxAttrib.Type == 4185 )
	{
		length += 20;
		length += 4;
	}
	if( msg.L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS.Type == 4180 )
	{
		length += 36;
		length += 4;
	}
	if( msg.L3L4_MonitorGroupEventCdmaBwr.Type == 4184 )
	{
		length += 16;
		length += 4;
	}
	if( msg.L3L4_DilloSfAndQosPerformanceGroup.Type == 4060 )
	{
		length += 12;
		length += 4;
	}
	if( msg.L3L4_DilloSfAndQosFlowManagementGroup.Type == 4061 )
	{
		length += 12;
		length += 4;
	}
	if( msg.L3L4_DilloPhyConfigurationGroup.Type == 4059 )
	{
		length += 132;
		length += 4;
	}
	if( msg.L3L4_DilloMapsGroup.Type == 4062 )
	{
		length += 12;
		length += 4;
	}
	if( msg.L3L4_BasicStatus_L3.Type == 4101 )
	{
		length += 36;
		length += 4;
	}
	if( msg.L3L4_BurstStatus_L3.Type == 4102 )
	{
		length += (UINT32)(msg.L3L4_BurstStatus_L3.BurstStatus_L3.numOfCidInfos * 32) + 32 + 8;
		length += 4;
	}
	if( msg.L3L4_SF_QoS_MonitorInfo_L3.Type == 4208 )
	{
		length += (UINT32)(msg.L3L4_SF_QoS_MonitorInfo_L3.SF_QoS_MonitorInfo_L3.numOfCidInfos * 36) + 16 + 8;
		length += 4;
	}
	if( msg.L3L4_Arq_MonitorInfo_L3.Type == 4209 )
	{
		length += (UINT32)(msg.L3L4_Arq_MonitorInfo_L3.Arq_MonitorInfo_L3.numOfCidInfos * 40) + 4 + 8;
		length += 4;
	}
	if( msg.L3L4_Harq_MonitorInfo_L3.Type == 4211 )
	{
		length += (UINT32)(msg.L3L4_Harq_MonitorInfo_L3.Harq_MonitorInfo_L3.numOfCidInfos * 8) + 4 + 8;
		length += 4;
	}
	for( j = 0; j < 3; j++ )
	{
		if( msg.L3L4_MacState_L3[j].Type == 4200 )
		{
			length += 12;
			length += 4;
		}
	}
	if( msg.L3L4_NbrCellList_L3.Type == 4201 )
	{
		length += (UINT32)(msg.L3L4_NbrCellList_L3.NbrCellList_L3.numOfIntraFASNbrs * 16) + (UINT32)(msg.L3L4_NbrCellList_L3.NbrCellList_L3.numOfInterFASNbrs * 16) + 4 + 8;
		length += 4;
	}
	if( msg.L3L4_NwEntryMsgLatency_L3.Type == 4203 )
	{
		length += 32;
		length += 4;
	}
	if( msg.L3L4_DcdUcdTimeout_L3.Type == 4206 )
	{
		length += 12;
		length += 4;
	}
	if( msg.L3L4_DSxTimers_L3.Type == 4207 )
	{
		length += 16;
		length += 4;
	}
	if( msg.L3L4_Phy_L3.Type == 4210 )
	{
		length += 16;
		length += 4;
	}
	for( j = 0; j < 5; j++ )
	{
		if( msg.L3L4_LinkLossOccur_L3[j].Type == 4213 )
		{
			length += 20;
			length += 4;
		}
	}
	if( msg.L3L4_Moniter_Scan_Config.Type == 4252 )
	{
		length += (UINT32)(msg.L3L4_Moniter_Scan_Config.MoniterScanConfig.SetScanParam.NumOfChannels * 24) + 4 + 8;
		length += 4;
	}
	for( j = 0; j < 10; j++ )
	{
		if( msg.L3L4_DSPS_Management_MSG[j].Type == 4151 )
		{
			length += (UINT32)msg.L3L4_DSPS_Management_MSG[j].DSPS_Management_MSG.tlv_length-8 + 8;
			length += 4;
		}
	}
	if( msg.L3L4_linkLossStatistics_L3.Type == 4202 )
	{
		length += 28;
		length += 4;
	}
	if( msg.L3L4_CoordinateHo_L3.Type == 4215 )
	{
		length += (UINT32)(msg.L3L4_CoordinateHo_L3.CoordinateHo_L3.numOfBsInHoReq * 8) + (UINT32)(msg.L3L4_CoordinateHo_L3.CoordinateHo_L3.numOfBsInHoRsp * 8) + 52 + 8;
		length += 4;
	}
	if( msg.L3L4_McsIndexTable_L3.Type == 4217 )
	{
		length += (UINT32)(msg.L3L4_McsIndexTable_L3.McsIndexTable_L3.NumDlburstProfiles * 4) + (UINT32)(msg.L3L4_McsIndexTable_L3.McsIndexTable_L3.NumUlburstProfiles * 4) + 4 + 8;
		length += 4;
	}
	if( msg.L3L4_ScanResult_L3.Type == 4214 )
	{
		length += (UINT32)(msg.L3L4_ScanResult_L3.ScanResult_L3.numOfNbrs * 20) + 4 + 8;
		length += 4;
	}
	if( msg.L3L4_ScanStatus_L3.Type == 4204 )
	{
		length += 16;
		length += 4;
	}
	if( msg.L3L4_ConnectionDropCount_L3.Type == 4205 )
	{
		length += 12;
		length += 4;
	}
	if( msg.L3L4_IdleConfiguration_L3.Type == 4212 )
	{
		length += 36;
		length += 4;
	}
	if( msg.L3L4_IdlePerformance_L3.Type == 4216 )
	{
		length += 28;
		length += 4;
	}
	if( msg.L3L4_Arq_MonitorRxPerformance_L3.Type == 4103 )
	{
		length += (UINT32)(msg.L3L4_Arq_MonitorRxPerformance_L3.Arq_MonitorRxPerformance_L3.numOfCidPerformance * 44) + 8 + 8;
		length += 4;
	}
	if( msg.L3L4_Arq_MonitorTxPerformance_L3.Type == 4106 )
	{
		length += (UINT32)(msg.L3L4_Arq_MonitorTxPerformance_L3.Arq_MonitorTxPerformance_L3.numOfCidPerformance * 48) + 4 + 8;
		length += 4;
	}
	if( msg.L3L4_MonitorSfPerformance_L3.Type == 4110 )
	{
		length += (UINT32)(msg.L3L4_MonitorSfPerformance_L3.SfPerformance_L3.numOfCidInfos * 16) + 4 + 8;
		length += 4;
	}
	if( msg.L3L4_Monitor_Scan_Result.Type == 4253 )
	{
		length += (UINT32)(msg.L3L4_Monitor_Scan_Result.MonitorScanResult.AvailableNSPsIdlist.NumOfNSPs * 4) + 4 + (UINT32)(msg.L3L4_Monitor_Scan_Result.MonitorScanResult.FullBSIDArr.NumOfBSIDs * 16) + 4 + 8;
		length += 4;
	}
	if( msg.L3L4_Monitor_Scan_Ind.Type == 4254 )
	{
		length += 20;
		length += 4;
	}
	if( msg.L3L4_Monitor_OMA_Session.Type == 4255 )
	{
		length += 12;
		length += 4;
	}
	if( msg.L3L4_Monitor_Operator.Type == 4256 )
	{
		length += (UINT32)(msg.L3L4_Monitor_Operator.MonitorOperator.Eaps.NumOfEaps * 352) + 4 + (UINT32)(msg.L3L4_Monitor_Operator.MonitorOperator.Capls.NumOfNaps * 8) + 4 + (UINT32)(msg.L3L4_Monitor_Operator.MonitorOperator.Rapls.NumOfRoamingPartners * 8) + 8 + 104 + 8;
		length += 4;
	}
	if( msg.L3L4_Monitor_OMAParams.Type == 4257 )
	{
		length += 456;
		length += 4;
	}
	if( msg.L3L4_Monitor_OMA_WiMAX_Params.Type == 4258 )
	{
		length += (UINT32)(msg.L3L4_Monitor_OMA_WiMAX_Params.MonitorOMAWimaxParams.RadioModule.LenOfRadioModule * 664) + 4 + 448 + 8;
		length += 4;
	}
	if( msg.L3L4_Monitor_OMA_FUMO_Params.Type == 4259 )
	{
		length += 636;
		length += 4;
	}
	if( msg.L3L4_Monitor_NAI.Type == 4261 )
	{
		length += (UINT32)msg.L3L4_Monitor_NAI.MonitorNAI.NAISize + 4 + 8;
		length += 4;
	}
	if( msg.L3L4_Monitor_ActivationStatusChange.Type == 4262 )
	{
		length += 12;
		length += 4;
	}
	if( msg.L3L4_Monitor_MCP.Type == 4263 )
	{
		length += (UINT32)(msg.L3L4_Monitor_MCP.MonitorMCP.ChannelInfoArray.NumOfChannels * 28) + 4 + 4 + 8;
		length += 4;
	}
	if( msg.L3L4_Monitor_Installation_Ind.Type == 4264 )
	{
		length += 12;
		length += 4;
	}
	if( msg.L3L4_Monitor_Recent_Discover_Nap.Type == 4265 )
	{
		length += (UINT32)(msg.L3L4_Monitor_Recent_Discover_Nap.MonitorRecentDiscoverNap.ChannelInfoArray.NumOfChannels * 28) + 4 + 12 + 8;
		length += 4;
	}
	if( msg.L3L4_Monitor_Selected_Channel.Type == 4266 )
	{
		length += (UINT32)(msg.L3L4_Monitor_Selected_Channel.MonitorSelectedChannel.ChannelInfoArray.NumOfChannels * 28) + 4 + 8;
		length += 4;
	}

	return length;
}
UINT L4BM_generic_GetBufferSize_MonitorBuffer(MonitorBuffer_type* msg)
{
	return L4BM_GetBufferSize_MonitorBuffer(*msg);
}
UINT L4BM_GetMaxBufferSize_MonitorBuffer( void )
{
	UINT32 length = HEADER_SIZE, j = 0;

	length += 50;
	length += 4;
	length += 108;
	length += 4;
	length += 24;
	length += 4;
	length += 16;
	length += 4;
	length += 40;
	length += 4;
	length += 584;
	length += 4;
	length += 20;
	length += 4;
	length += 20;
	length += 4;
	length += 12;
	length += 4;
	length += L4BM_RoundUp4Bytes((UINT32)(33 * 24) + 4) + 8;
	length += 4;
	length += 150;
	length += 4;
	length += 82;
	length += 4;
	length += 20;
	length += 4;
	length += 36;
	length += 4;
	length += 16;
	length += 4;
	length += 12;
	length += 4;
	length += 12;
	length += 4;
	length += 132;
	length += 4;
	length += 12;
	length += 4;
	length += 36;
	length += 4;
	length += (UINT32)(16 * 32) + 32 + 8;
	length += 4;
	length += (UINT32)(20 * 36) + 16 + 8;
	length += 4;
	length += (UINT32)(20 * 40) + 4 + 8;
	length += 4;
	length += (UINT32)(20 * 8) + 4 + 8;
	length += 4;
	for( j = 0; j < 3; j++ )
	{
		length += 12;
		length += 4;
	}
	length += (UINT32)(32 * 16) + (UINT32)(32 * 16) + 4 + 8;
	length += 4;
	length += 32;
	length += 4;
	length += 12;
	length += 4;
	length += 16;
	length += 4;
	length += 16;
	length += 4;
	for( j = 0; j < 5; j++ )
	{
		length += 20;
		length += 4;
	}
	length += (UINT32)(32 * 24) + 4 + 8;
	length += 4;
	for( j = 0; j < 10; j++ )
	{
		length += (UINT32)1500 + 8;
		length += 4;
	}
	length += 28;
	length += 4;
	length += (UINT32)(10 * 8) + (UINT32)(10 * 8) + 52 + 8;
	length += 4;
	length += (UINT32)(16 * 4) + (UINT32)(16 * 4) + 4 + 8;
	length += 4;
	length += (UINT32)(33 * 20) + 4 + 8;
	length += 4;
	length += 16;
	length += 4;
	length += 12;
	length += 4;
	length += 36;
	length += 4;
	length += 28;
	length += 4;
	length += (UINT32)(16 * 44) + 8 + 8;
	length += 4;
	length += (UINT32)(16 * 48) + 4 + 8;
	length += 4;
	length += (UINT32)(16 * 16) + 4 + 8;
	length += 4;
	length += (UINT32)(10 * 4) + 4 + (UINT32)(10 * 16) + 4 + 8;
	length += 4;
	length += 20;
	length += 4;
	length += 12;
	length += 4;
	length += (UINT32)(70 * 352) + 4 + (UINT32)(70 * 8) + 4 + (UINT32)(70 * 8) + 8 + 104 + 8;
	length += 4;
	length += 456;
	length += 4;
	length += (UINT32)(5 * 664) + 4 + 448 + 8;
	length += 4;
	length += 636;
	length += 4;
	length += (UINT32)356 + 4 + 8;
	length += 4;
	length += 12;
	length += 4;
	length += (UINT32)(500 * 28) + 4 + 4 + 8;
	length += 4;
	length += 12;
	length += 4;
	length += (UINT32)(32 * 28) + 4 + 12 + 8;
	length += 4;
	length += (UINT32)(32 * 28) + 4 + 8;
	length += 4;

	return length;
}
void L4BM_Init_MonitorBuffer(MonitorBuffer_type* pMsg)
{
	UINT32 j = 0;

	pMsg->header.Version = HEADER_VERSION;
	pMsg->header.Accessibility = HEADER_ACCESSIBILITY;
	pMsg->header.Status = HEADER_STATUS;
	pMsg->L3L4_L3MonitorGroupL1_DiagnosticsTpc.Type = INVALID_OPCODE;
	pMsg->L3L4_L3MonitorGroupL1_DiagnosticsPerformance.Type = INVALID_OPCODE;
	pMsg->L3L4_L3MonitorGroupL1_DiagnosticsConfiguration.Type = INVALID_OPCODE;
	pMsg->L3L4_L3MonitorGroupBASIC_STATUS.Type = INVALID_OPCODE;
	pMsg->L3L4_L3MonitorGroupBURST_STATUS.Type = INVALID_OPCODE;
	pMsg->L3L4_L3MonitorGroupPER_CIN_STATUS.Type = INVALID_OPCODE;
	pMsg->L3L4_L3MonitorGroupSF_AND_QOS_FLOW_MNGMT.Type = INVALID_OPCODE;
	pMsg->L3L4_L3MonitorGroupL2_LAM_Events.Type = INVALID_OPCODE;
	pMsg->L3L4_L3MonitorGroupL1_DiagnosticsTpcEvents.Type = INVALID_OPCODE;
	pMsg->L3L4_L3MonitorGroupL1_NBS_PSCAN_Results.Type = INVALID_OPCODE;
	pMsg->L3L4_DilloHarqPerfGroup.Type = INVALID_OPCODE;
	pMsg->L3L4_DilloBurstGroup.Type = INVALID_OPCODE;
	pMsg->L3L4_MonitorGroupEventCdmaTxAttrib.Type = INVALID_OPCODE;
	pMsg->L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS.Type = INVALID_OPCODE;
	pMsg->L3L4_MonitorGroupEventCdmaBwr.Type = INVALID_OPCODE;
	pMsg->L3L4_DilloSfAndQosPerformanceGroup.Type = INVALID_OPCODE;
	pMsg->L3L4_DilloSfAndQosFlowManagementGroup.Type = INVALID_OPCODE;
	pMsg->L3L4_DilloPhyConfigurationGroup.Type = INVALID_OPCODE;
	pMsg->L3L4_DilloMapsGroup.Type = INVALID_OPCODE;
	pMsg->L3L4_BasicStatus_L3.Type = INVALID_OPCODE;
	pMsg->L3L4_BurstStatus_L3.Type = INVALID_OPCODE;
	pMsg->L3L4_SF_QoS_MonitorInfo_L3.Type = INVALID_OPCODE;
	pMsg->L3L4_Arq_MonitorInfo_L3.Type = INVALID_OPCODE;
	pMsg->L3L4_Harq_MonitorInfo_L3.Type = INVALID_OPCODE;
	for( j = 0; j < 3; j++ )
	{
		pMsg->L3L4_MacState_L3[j].Type = INVALID_OPCODE;
	}
	pMsg->L3L4_NbrCellList_L3.Type = INVALID_OPCODE;
	pMsg->L3L4_NwEntryMsgLatency_L3.Type = INVALID_OPCODE;
	pMsg->L3L4_DcdUcdTimeout_L3.Type = INVALID_OPCODE;
	pMsg->L3L4_DSxTimers_L3.Type = INVALID_OPCODE;
	pMsg->L3L4_Phy_L3.Type = INVALID_OPCODE;
	for( j = 0; j < 5; j++ )
	{
		pMsg->L3L4_LinkLossOccur_L3[j].Type = INVALID_OPCODE;
	}
	pMsg->L3L4_Moniter_Scan_Config.Type = INVALID_OPCODE;
	for( j = 0; j < 10; j++ )
	{
		pMsg->L3L4_DSPS_Management_MSG[j].Type = INVALID_OPCODE;
	}
	pMsg->L3L4_linkLossStatistics_L3.Type = INVALID_OPCODE;
	pMsg->L3L4_CoordinateHo_L3.Type = INVALID_OPCODE;
	pMsg->L3L4_McsIndexTable_L3.Type = INVALID_OPCODE;
	pMsg->L3L4_ScanResult_L3.Type = INVALID_OPCODE;
	pMsg->L3L4_ScanStatus_L3.Type = INVALID_OPCODE;
	pMsg->L3L4_ConnectionDropCount_L3.Type = INVALID_OPCODE;
	pMsg->L3L4_IdleConfiguration_L3.Type = INVALID_OPCODE;
	pMsg->L3L4_IdlePerformance_L3.Type = INVALID_OPCODE;
	pMsg->L3L4_Arq_MonitorRxPerformance_L3.Type = INVALID_OPCODE;
	pMsg->L3L4_Arq_MonitorTxPerformance_L3.Type = INVALID_OPCODE;
	pMsg->L3L4_MonitorSfPerformance_L3.Type = INVALID_OPCODE;
	pMsg->L3L4_Monitor_Scan_Result.Type = INVALID_OPCODE;
	pMsg->L3L4_Monitor_Scan_Ind.Type = INVALID_OPCODE;
	pMsg->L3L4_Monitor_OMA_Session.Type = INVALID_OPCODE;
	pMsg->L3L4_Monitor_Operator.Type = INVALID_OPCODE;
	pMsg->L3L4_Monitor_OMAParams.Type = INVALID_OPCODE;
	pMsg->L3L4_Monitor_OMA_WiMAX_Params.Type = INVALID_OPCODE;
	pMsg->L3L4_Monitor_OMA_FUMO_Params.Type = INVALID_OPCODE;
	pMsg->L3L4_Monitor_NAI.Type = INVALID_OPCODE;
	pMsg->L3L4_Monitor_ActivationStatusChange.Type = INVALID_OPCODE;
	pMsg->L3L4_Monitor_MCP.Type = INVALID_OPCODE;
	pMsg->L3L4_Monitor_Installation_Ind.Type = INVALID_OPCODE;
	pMsg->L3L4_Monitor_Recent_Discover_Nap.Type = INVALID_OPCODE;
	pMsg->L3L4_Monitor_Selected_Channel.Type = INVALID_OPCODE;

}
L4bufman_Funcs MonitorBuffer_Funcs = 
{
	(pf_GetL4Command)L4BM_Get_MonitorBuffer,
	(pf_SetL4Command)L4BM_generic_Set_MonitorBuffer,
	(pf_GetBufferSize)L4BM_generic_GetBufferSize_MonitorBuffer,
	(pf_GetMaxBufferSize)L4BM_GetMaxBufferSize_MonitorBuffer,
	(pf_InitL4Command)L4BM_Init_MonitorBuffer
};

