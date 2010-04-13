
/****************************************************************************
*
* Auto generated file
* Version XXX
* Compliant with XXX.bm version XXX
* 3/22/2009 10:35:12 AM
*
*****************************************************************************/


#include "L4BufMan_dll_L3L4DmStructs.h"



L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_Header_Version_GET( UINT8* base_ptr, UINT16* version )
{
	BM_MonitorBuffer_Header_Version_GET( base_ptr, *version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_Header_Accessibility_GET( UINT8* base_ptr, UINT16* accessibility )
{
	BM_MonitorBuffer_Header_Accessibility_GET( base_ptr, *accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_Header_Status_GET( UINT8* base_ptr, UINT16* status )
{
	BM_MonitorBuffer_Header_Status_GET( base_ptr, *status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_Header_Length_GET( UINT8* base_ptr, UINT32* listSize )
{
	BM_MonitorBuffer_Header_Length_GET( base_ptr, *listSize );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_GET_FIRST( UINT8* base_ptr, UINT32* out_diff, UINT32* out_cur_bitoff )
{
	UINT8* out_cur_ptr = base_ptr;
	BM_MonitorBuffer_List_GET_FIRST( base_ptr, out_cur_ptr, *out_cur_bitoff );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_GET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_GET_TYPE( cur_ptr, cur_bitoff, *type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_GET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_length, UINT32 err )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, *out_length, err );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_BST_FrameNumber_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, *FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_BST_uSecInFrame_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, *uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_PowerPerToneCur_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, INT16* PowerPerToneCur )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_PowerPerToneCur_GET( base_ptr, cur_ptr, cur_bitoff, *PowerPerToneCur );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_PowerPerToneAvg_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, INT16* PowerPerToneAvg )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_PowerPerToneAvg_GET( base_ptr, cur_ptr, cur_bitoff, *PowerPerToneAvg );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_PathLoss_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* PathLoss )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_PathLoss_GET( base_ptr, cur_ptr, cur_bitoff, *PathLoss );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_Headroom_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* Headroom )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_Headroom_GET( base_ptr, cur_ptr, cur_bitoff, *Headroom );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_Reserved_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* Reserved )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_Reserved_GET( base_ptr, cur_ptr, cur_bitoff, *Reserved );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_powerControlMode_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* powerControlMode )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_powerControlMode_GET( base_ptr, cur_ptr, cur_bitoff, *powerControlMode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_isTx_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* isTx )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_isTx_GET( base_ptr, cur_ptr, cur_bitoff, *isTx );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_CurrentFrameTxPower_Total_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, INT16* Total )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_CurrentFrameTxPower_Total_GET( base_ptr, cur_ptr, cur_bitoff, *Total );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_CurrentFrameTxPower_NumOfSubchannels_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* NumOfSubchannels )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_CurrentFrameTxPower_NumOfSubchannels_GET( base_ptr, cur_ptr, cur_bitoff, *NumOfSubchannels );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_CurrentFrameTxPower_AllocationType_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* AllocationType )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_CurrentFrameTxPower_AllocationType_GET( base_ptr, cur_ptr, cur_bitoff, *AllocationType );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ExtremePowerValues_MaxPower_Total_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, INT16* Total )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ExtremePowerValues_MaxPower_Total_GET( base_ptr, cur_ptr, cur_bitoff, *Total );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ExtremePowerValues_MaxPower_NumOfSubchannels_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* NumOfSubchannels )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ExtremePowerValues_MaxPower_NumOfSubchannels_GET( base_ptr, cur_ptr, cur_bitoff, *NumOfSubchannels );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ExtremePowerValues_MaxPower_AllocationType_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* AllocationType )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ExtremePowerValues_MaxPower_AllocationType_GET( base_ptr, cur_ptr, cur_bitoff, *AllocationType );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ExtremePowerValues_MinPower_Total_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, INT16* Total )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ExtremePowerValues_MinPower_Total_GET( base_ptr, cur_ptr, cur_bitoff, *Total );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ExtremePowerValues_MinPower_NumOfSubchannels_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* NumOfSubchannels )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ExtremePowerValues_MinPower_NumOfSubchannels_GET( base_ptr, cur_ptr, cur_bitoff, *NumOfSubchannels );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ExtremePowerValues_MinPower_AllocationType_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* AllocationType )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ExtremePowerValues_MinPower_AllocationType_GET( base_ptr, cur_ptr, cur_bitoff, *AllocationType );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_offsetBSperSS_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, INT16* offsetBSperSS )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_offsetBSperSS_GET( base_ptr, cur_ptr, cur_bitoff, *offsetBSperSS );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_offsetSSperSS_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, INT16* offsetSSperSS )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_offsetSSperSS_GET( base_ptr, cur_ptr, cur_bitoff, *offsetSSperSS );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_cqiAckPeriodicRangingNI_valid_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* valid )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_cqiAckPeriodicRangingNI_valid_GET( base_ptr, cur_ptr, cur_bitoff, *valid );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_cqiAckPeriodicRangingNI_level_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* level )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_cqiAckPeriodicRangingNI_level_GET( base_ptr, cur_ptr, cur_bitoff, *level );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_puscNI_valid_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* valid )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_puscNI_valid_GET( base_ptr, cur_ptr, cur_bitoff, *valid );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_puscNI_level_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* level )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_puscNI_level_GET( base_ptr, cur_ptr, cur_bitoff, *level );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_amcNI_valid_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* valid )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_amcNI_valid_GET( base_ptr, cur_ptr, cur_bitoff, *valid );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_amcNI_level_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* level )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_amcNI_level_GET( base_ptr, cur_ptr, cur_bitoff, *level );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_periodicRangingNI_valid_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* valid )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_periodicRangingNI_valid_GET( base_ptr, cur_ptr, cur_bitoff, *valid );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_periodicRangingNI_level_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* level )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_periodicRangingNI_level_GET( base_ptr, cur_ptr, cur_bitoff, *level );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_soundingNI_valid_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* valid )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_soundingNI_valid_GET( base_ptr, cur_ptr, cur_bitoff, *valid );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_soundingNI_level_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* level )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_soundingNI_level_GET( base_ptr, cur_ptr, cur_bitoff, *level );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_mimoNI_valid_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* valid )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_mimoNI_valid_GET( base_ptr, cur_ptr, cur_bitoff, *valid );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_mimoNI_level_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* level )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_mimoNI_level_GET( base_ptr, cur_ptr, cur_bitoff, *level );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_LackOfHeadroomCounter_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* LackOfHeadroomCounter )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_LackOfHeadroomCounter_GET( base_ptr, cur_ptr, cur_bitoff, *LackOfHeadroomCounter );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_BST_FrameNumber_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, *FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_BST_uSecInFrame_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, *uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_MapsStatistics_FchRecievedOK_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* FchRecievedOK )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_MapsStatistics_FchRecievedOK_GET( base_ptr, cur_ptr, cur_bitoff, *FchRecievedOK );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_MapsStatistics_FchFailures_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* FchFailures )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_MapsStatistics_FchFailures_GET( base_ptr, cur_ptr, cur_bitoff, *FchFailures );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_MapsStatistics_NormalDlMapRecievedOK_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* NormalDlMapRecievedOK )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_MapsStatistics_NormalDlMapRecievedOK_GET( base_ptr, cur_ptr, cur_bitoff, *NormalDlMapRecievedOK );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_MapsStatistics_NormalDlMapHcsError_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* NormalDlMapHcsError )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_MapsStatistics_NormalDlMapHcsError_GET( base_ptr, cur_ptr, cur_bitoff, *NormalDlMapHcsError );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_MapsStatistics_NormalDlMapCrcError_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* NormalDlMapCrcError )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_MapsStatistics_NormalDlMapCrcError_GET( base_ptr, cur_ptr, cur_bitoff, *NormalDlMapCrcError );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_MapsStatistics_NormalUlMapRecievedOK_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* NormalUlMapRecievedOK )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_MapsStatistics_NormalUlMapRecievedOK_GET( base_ptr, cur_ptr, cur_bitoff, *NormalUlMapRecievedOK );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_MapsStatistics_NormalUlMapHcsError_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* NormalUlMapHcsError )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_MapsStatistics_NormalUlMapHcsError_GET( base_ptr, cur_ptr, cur_bitoff, *NormalUlMapHcsError );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_MapsStatistics_NormalUlMapCrcError_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* NormalUlMapCrcError )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_MapsStatistics_NormalUlMapCrcError_GET( base_ptr, cur_ptr, cur_bitoff, *NormalUlMapCrcError );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_MapsStatistics_CompressedMapRecievedOK_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* CompressedMapRecievedOK )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_MapsStatistics_CompressedMapRecievedOK_GET( base_ptr, cur_ptr, cur_bitoff, *CompressedMapRecievedOK );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_MapsStatistics_CompressedMapCrcError_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* CompressedMapCrcError )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_MapsStatistics_CompressedMapCrcError_GET( base_ptr, cur_ptr, cur_bitoff, *CompressedMapCrcError );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_PreamblePCinr_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, INT* PreamblePCinr )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_PreamblePCinr_GET( base_ptr, cur_ptr, cur_bitoff, *PreamblePCinr );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_PreamblePCinrAnt0_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, INT* PreamblePCinrAnt0 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_PreamblePCinrAnt0_GET( base_ptr, cur_ptr, cur_bitoff, *PreamblePCinrAnt0 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_PreamblePCinrAnt1_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, INT* PreamblePCinrAnt1 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_PreamblePCinrAnt1_GET( base_ptr, cur_ptr, cur_bitoff, *PreamblePCinrAnt1 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_PreamblePCinrStd_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, INT* PreamblePCinrStd )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_PreamblePCinrStd_GET( base_ptr, cur_ptr, cur_bitoff, *PreamblePCinrStd );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_Rssi_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, INT* Rssi )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_Rssi_GET( base_ptr, cur_ptr, cur_bitoff, *Rssi );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_RssiStd_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, INT* RssiStd )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_RssiStd_GET( base_ptr, cur_ptr, cur_bitoff, *RssiStd );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_MimoStbcPCinr_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, INT* MimoStbcPCinr )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_MimoStbcPCinr_GET( base_ptr, cur_ptr, cur_bitoff, *MimoStbcPCinr );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_MimoStbcPCinrStd_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, INT* MimoStbcPCinrStd )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_MimoStbcPCinrStd_GET( base_ptr, cur_ptr, cur_bitoff, *MimoStbcPCinrStd );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_MimoSmPCinr_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, INT* MimoSmPCinr )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_MimoSmPCinr_GET( base_ptr, cur_ptr, cur_bitoff, *MimoSmPCinr );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_MimoSmPCinrStd_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, INT* MimoSmPCinrStd )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_MimoSmPCinrStd_GET( base_ptr, cur_ptr, cur_bitoff, *MimoSmPCinrStd );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_MimoStbcECinr_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, INT* MimoStbcECinr )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_MimoStbcECinr_GET( base_ptr, cur_ptr, cur_bitoff, *MimoStbcECinr );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_MimoSmECinr_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, INT* MimoSmECinr )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_MimoSmECinr_GET( base_ptr, cur_ptr, cur_bitoff, *MimoSmECinr );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_RxAntModeAutoDetect_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, eRF_RX_ANT_MODE* RxAntModeAutoDetect )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_RxAntModeAutoDetect_GET( base_ptr, cur_ptr, cur_bitoff, *RxAntModeAutoDetect );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_Reserved8_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* Reserved8 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_Reserved8_GET( base_ptr, cur_ptr, cur_bitoff, *Reserved8 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_Reserved16_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* Reserved16 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_Reserved16_GET( base_ptr, cur_ptr, cur_bitoff, *Reserved16 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_cqichCount_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* cqichCount )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_cqichCount_GET( base_ptr, cur_ptr, cur_bitoff, *cqichCount );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_TemperatureInCelsius_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, INT16* TemperatureInCelsius )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_TemperatureInCelsius_GET( base_ptr, cur_ptr, cur_bitoff, *TemperatureInCelsius );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_RxAntMode_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, eRF_RX_ANT_MODE* RxAntMode )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_RxAntMode_GET( base_ptr, cur_ptr, cur_bitoff, *RxAntMode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_Reserved_1_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* Reserved_1 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_Reserved_1_GET( base_ptr, cur_ptr, cur_bitoff, *Reserved_1 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsConfiguration_BST_FrameNumber_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsConfiguration_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, *FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsConfiguration_BST_uSecInFrame_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsConfiguration_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, *uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsConfiguration_dmPhyConfiguration_FrequencyOffsetInHz_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, INT* FrequencyOffsetInHz )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsConfiguration_dmPhyConfiguration_FrequencyOffsetInHz_GET( base_ptr, cur_ptr, cur_bitoff, *FrequencyOffsetInHz );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsConfiguration_dmPhyConfiguration_CenterFrequencyInKHz_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* CenterFrequencyInKHz )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsConfiguration_dmPhyConfiguration_CenterFrequencyInKHz_GET( base_ptr, cur_ptr, cur_bitoff, *CenterFrequencyInKHz );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsConfiguration_dmPhyConfiguration_transitionGaps_TTG_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* TTG )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsConfiguration_dmPhyConfiguration_transitionGaps_TTG_GET( base_ptr, cur_ptr, cur_bitoff, *TTG );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsConfiguration_dmPhyConfiguration_transitionGaps_RTG_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* RTG )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsConfiguration_dmPhyConfiguration_transitionGaps_RTG_GET( base_ptr, cur_ptr, cur_bitoff, *RTG );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsConfiguration_dmPhyConfiguration_RecommendedMIMOMode_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* RecommendedMIMOMode )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsConfiguration_dmPhyConfiguration_RecommendedMIMOMode_GET( base_ptr, cur_ptr, cur_bitoff, *RecommendedMIMOMode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBASIC_STATUS_BST_FrameNumber_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBASIC_STATUS_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, *FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBASIC_STATUS_BST_uSecInFrame_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBASIC_STATUS_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, *uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBASIC_STATUS_FWMonitorGroupBasicStatus_FCH_byte0_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* byte0 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBASIC_STATUS_FWMonitorGroupBasicStatus_FCH_byte0_GET( base_ptr, cur_ptr, cur_bitoff, *byte0 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBASIC_STATUS_FWMonitorGroupBasicStatus_FCH_byte1_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* byte1 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBASIC_STATUS_FWMonitorGroupBasicStatus_FCH_byte1_GET( base_ptr, cur_ptr, cur_bitoff, *byte1 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBASIC_STATUS_FWMonitorGroupBasicStatus_FCH_byte2_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* byte2 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBASIC_STATUS_FWMonitorGroupBasicStatus_FCH_byte2_GET( base_ptr, cur_ptr, cur_bitoff, *byte2 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBASIC_STATUS_FWMonitorGroupBasicStatus_FCH_validity_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, MonitorValidity* validity )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBASIC_STATUS_FWMonitorGroupBasicStatus_FCH_validity_GET( base_ptr, cur_ptr, cur_bitoff, *validity );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBASIC_STATUS_FWMonitorGroupBasicStatus_frameRatio_DlSize_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* DlSize )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBASIC_STATUS_FWMonitorGroupBasicStatus_frameRatio_DlSize_GET( base_ptr, cur_ptr, cur_bitoff, *DlSize );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBASIC_STATUS_FWMonitorGroupBasicStatus_frameRatio_UlSize_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* UlSize )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBASIC_STATUS_FWMonitorGroupBasicStatus_frameRatio_UlSize_GET( base_ptr, cur_ptr, cur_bitoff, *UlSize );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBURST_STATUS_BST_FrameNumber_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBURST_STATUS_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, *FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBURST_STATUS_BST_uSecInFrame_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBURST_STATUS_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, *uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBURST_STATUS_FWMonitorGroupBurstStatus_TotalDLPduCRCCount_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* TotalDLPduCRCCount )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBURST_STATUS_FWMonitorGroupBurstStatus_TotalDLPduCRCCount_GET( base_ptr, cur_ptr, cur_bitoff, *TotalDLPduCRCCount );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBURST_STATUS_FWMonitorGroupBurstStatus_TotalDLPduCount_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* TotalDLPduCount )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBURST_STATUS_FWMonitorGroupBurstStatus_TotalDLPduCount_GET( base_ptr, cur_ptr, cur_bitoff, *TotalDLPduCount );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBURST_STATUS_FWMonitorGroupBurstStatus_UL_PDU_Size_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* UL_PDU_Size )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBURST_STATUS_FWMonitorGroupBurstStatus_UL_PDU_Size_GET( base_ptr, cur_ptr, cur_bitoff, *UL_PDU_Size );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBURST_STATUS_FWMonitorGroupBurstStatus_TotalULPDUSize_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* TotalULPDUSize )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBURST_STATUS_FWMonitorGroupBurstStatus_TotalULPDUSize_GET( base_ptr, cur_ptr, cur_bitoff, *TotalULPDUSize );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBURST_STATUS_FWMonitorGroupBurstStatus_TotalUlPduCount_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* TotalUlPduCount )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBURST_STATUS_FWMonitorGroupBurstStatus_TotalUlPduCount_GET( base_ptr, cur_ptr, cur_bitoff, *TotalUlPduCount );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBURST_STATUS_FWMonitorGroupBurstStatus_UL_SDU_Size_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* UL_SDU_Size )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBURST_STATUS_FWMonitorGroupBurstStatus_UL_SDU_Size_GET( base_ptr, cur_ptr, cur_bitoff, *UL_SDU_Size );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBURST_STATUS_FWMonitorGroupBurstStatus_TotalULSDUSize_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* TotalULSDUSize )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBURST_STATUS_FWMonitorGroupBurstStatus_TotalULSDUSize_GET( base_ptr, cur_ptr, cur_bitoff, *TotalULSDUSize );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBURST_STATUS_FWMonitorGroupBurstStatus_TotalUlSduCount_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* TotalUlSduCount )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBURST_STATUS_FWMonitorGroupBurstStatus_TotalUlSduCount_GET( base_ptr, cur_ptr, cur_bitoff, *TotalUlSduCount );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupPER_CIN_STATUS_BST_FrameNumber_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupPER_CIN_STATUS_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, *FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupPER_CIN_STATUS_BST_uSecInFrame_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupPER_CIN_STATUS_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, *uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupPER_CIN_STATUS_Per_CIN_MonitorInfo_L2_perCIN_xDUStatus_PDUInfo_numberOfTxedPDUs_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* numberOfTxedPDUs )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupPER_CIN_STATUS_Per_CIN_MonitorInfo_L2_perCIN_xDUStatus_PDUInfo_numberOfTxedPDUs_GET( base_ptr, i0, cur_ptr, cur_bitoff, *numberOfTxedPDUs );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupPER_CIN_STATUS_Per_CIN_MonitorInfo_L2_perCIN_xDUStatus_PDUInfo_totalBytes_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* totalBytes )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupPER_CIN_STATUS_Per_CIN_MonitorInfo_L2_perCIN_xDUStatus_PDUInfo_totalBytes_GET( base_ptr, i0, cur_ptr, cur_bitoff, *totalBytes );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupPER_CIN_STATUS_Per_CIN_MonitorInfo_L2_perCIN_xDUStatus_SDUInfo_numberOfAgedSDUs_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* numberOfAgedSDUs )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupPER_CIN_STATUS_Per_CIN_MonitorInfo_L2_perCIN_xDUStatus_SDUInfo_numberOfAgedSDUs_GET( base_ptr, i0, cur_ptr, cur_bitoff, *numberOfAgedSDUs );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupPER_CIN_STATUS_Per_CIN_MonitorInfo_L2_perCIN_xDUStatus_SDUInfo_totalBytes_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* totalBytes )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupPER_CIN_STATUS_Per_CIN_MonitorInfo_L2_perCIN_xDUStatus_SDUInfo_totalBytes_GET( base_ptr, i0, cur_ptr, cur_bitoff, *totalBytes );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupPER_CIN_STATUS_Per_CIN_MonitorInfo_L2_perCIN_BWRStatus_AggregatedBWRInfo_numberOfBWRs_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* numberOfBWRs )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupPER_CIN_STATUS_Per_CIN_MonitorInfo_L2_perCIN_BWRStatus_AggregatedBWRInfo_numberOfBWRs_GET( base_ptr, i0, cur_ptr, cur_bitoff, *numberOfBWRs );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupPER_CIN_STATUS_Per_CIN_MonitorInfo_L2_perCIN_BWRStatus_AggregatedBWRInfo_totalBytes_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* totalBytes )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupPER_CIN_STATUS_Per_CIN_MonitorInfo_L2_perCIN_BWRStatus_AggregatedBWRInfo_totalBytes_GET( base_ptr, i0, cur_ptr, cur_bitoff, *totalBytes );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupPER_CIN_STATUS_Per_CIN_MonitorInfo_L2_perCIN_BWRStatus_IncrementalBWRInfo_numberOfBWRs_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* numberOfBWRs )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupPER_CIN_STATUS_Per_CIN_MonitorInfo_L2_perCIN_BWRStatus_IncrementalBWRInfo_numberOfBWRs_GET( base_ptr, i0, cur_ptr, cur_bitoff, *numberOfBWRs );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupPER_CIN_STATUS_Per_CIN_MonitorInfo_L2_perCIN_BWRStatus_IncrementalBWRInfo_totalBytes_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* totalBytes )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupPER_CIN_STATUS_Per_CIN_MonitorInfo_L2_perCIN_BWRStatus_IncrementalBWRInfo_totalBytes_GET( base_ptr, i0, cur_ptr, cur_bitoff, *totalBytes );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupPER_CIN_STATUS_Per_CIN_MonitorInfo_L2_perCIN_VQInfo_currentVQInfo_totalBytesPendingInQ_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* totalBytesPendingInQ )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupPER_CIN_STATUS_Per_CIN_MonitorInfo_L2_perCIN_VQInfo_currentVQInfo_totalBytesPendingInQ_GET( base_ptr, i0, cur_ptr, cur_bitoff, *totalBytesPendingInQ );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupSF_AND_QOS_FLOW_MNGMT_BST_FrameNumber_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupSF_AND_QOS_FLOW_MNGMT_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, *FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupSF_AND_QOS_FLOW_MNGMT_BST_uSecInFrame_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupSF_AND_QOS_FLOW_MNGMT_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, *uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupSF_AND_QOS_FLOW_MNGMT_L2_MON_TYPE_SF_AND_QOS_FLOW_MNGMT_HARQBurst_TotalGrantsAmountInBytes_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* TotalGrantsAmountInBytes )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupSF_AND_QOS_FLOW_MNGMT_L2_MON_TYPE_SF_AND_QOS_FLOW_MNGMT_HARQBurst_TotalGrantsAmountInBytes_GET( base_ptr, cur_ptr, cur_bitoff, *TotalGrantsAmountInBytes );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupSF_AND_QOS_FLOW_MNGMT_L2_MON_TYPE_SF_AND_QOS_FLOW_MNGMT_NonHARQBurst_TotalGrantsAmountInBytes_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* TotalGrantsAmountInBytes )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupSF_AND_QOS_FLOW_MNGMT_L2_MON_TYPE_SF_AND_QOS_FLOW_MNGMT_NonHARQBurst_TotalGrantsAmountInBytes_GET( base_ptr, cur_ptr, cur_bitoff, *TotalGrantsAmountInBytes );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupSF_AND_QOS_FLOW_MNGMT_L2_MON_TYPE_SF_AND_QOS_FLOW_MNGMT_UIUC14Burst_TotalGrantsAmountInBytes_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* TotalGrantsAmountInBytes )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupSF_AND_QOS_FLOW_MNGMT_L2_MON_TYPE_SF_AND_QOS_FLOW_MNGMT_UIUC14Burst_TotalGrantsAmountInBytes_GET( base_ptr, cur_ptr, cur_bitoff, *TotalGrantsAmountInBytes );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL2_LAM_Events_BST_FrameNumber_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL2_LAM_Events_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, *FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL2_LAM_Events_BST_uSecInFrame_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL2_LAM_Events_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, *uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL2_LAM_Events_L2_LAM_Events_MonitorInfo_CQIParams_FrameNumber_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL2_LAM_Events_L2_LAM_Events_MonitorInfo_CQIParams_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, *FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL2_LAM_Events_L2_LAM_Events_MonitorInfo_CQIParams_CQI_Measurement_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, INT* CQI_Measurement )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL2_LAM_Events_L2_LAM_Events_MonitorInfo_CQIParams_CQI_Measurement_GET( base_ptr, cur_ptr, cur_bitoff, *CQI_Measurement );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL2_LAM_Events_L2_LAM_Events_MonitorInfo_CQIParams_ChannelID_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* ChannelID )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL2_LAM_Events_L2_LAM_Events_MonitorInfo_CQIParams_ChannelID_GET( base_ptr, cur_ptr, cur_bitoff, *ChannelID );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL2_LAM_Events_L2_LAM_Events_MonitorInfo_CQIParams_IsMIMOReportFlag_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* IsMIMOReportFlag )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL2_LAM_Events_L2_LAM_Events_MonitorInfo_CQIParams_IsMIMOReportFlag_GET( base_ptr, cur_ptr, cur_bitoff, *IsMIMOReportFlag );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpcEvents_BST_FrameNumber_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpcEvents_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, *FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpcEvents_BST_uSecInFrame_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpcEvents_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, *uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpcEvents_dmTpcEvents_TPCModeChange_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* TPCModeChange )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpcEvents_dmTpcEvents_TPCModeChange_GET( base_ptr, cur_ptr, cur_bitoff, *TPCModeChange );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_NBS_PSCAN_Results_BST_FrameNumber_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_NBS_PSCAN_Results_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, *FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_NBS_PSCAN_Results_BST_uSecInFrame_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_NBS_PSCAN_Results_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, *uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_NBS_PSCAN_Results_dmL1NBSPSCANResults_numOfReportedBs_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* numOfReportedBs )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_NBS_PSCAN_Results_dmL1NBSPSCANResults_numOfReportedBs_GET( base_ptr, cur_ptr, cur_bitoff, *numOfReportedBs );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_NBS_PSCAN_Results_dmL1NBSPSCANResults_NBSPSCANResult_PHYLinkID_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* PHYLinkID )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_NBS_PSCAN_Results_dmL1NBSPSCANResults_NBSPSCANResult_PHYLinkID_GET( base_ptr, i0, cur_ptr, cur_bitoff, *PHYLinkID );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_NBS_PSCAN_Results_dmL1NBSPSCANResults_NBSPSCANResult_NeighbourBSPreambleCINRMeanReuse1_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, INT* NeighbourBSPreambleCINRMeanReuse1 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_NBS_PSCAN_Results_dmL1NBSPSCANResults_NBSPSCANResult_NeighbourBSPreambleCINRMeanReuse1_GET( base_ptr, i0, cur_ptr, cur_bitoff, *NeighbourBSPreambleCINRMeanReuse1 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_NBS_PSCAN_Results_dmL1NBSPSCANResults_NBSPSCANResult_NeighbourBSPreambleCINRMeanReuse3_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, INT* NeighbourBSPreambleCINRMeanReuse3 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_NBS_PSCAN_Results_dmL1NBSPSCANResults_NBSPSCANResult_NeighbourBSPreambleCINRMeanReuse3_GET( base_ptr, i0, cur_ptr, cur_bitoff, *NeighbourBSPreambleCINRMeanReuse3 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_NBS_PSCAN_Results_dmL1NBSPSCANResults_NBSPSCANResult_NeighbourBSPreambleRSSIMean_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, INT* NeighbourBSPreambleRSSIMean )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_NBS_PSCAN_Results_dmL1NBSPSCANResults_NBSPSCANResult_NeighbourBSPreambleRSSIMean_GET( base_ptr, i0, cur_ptr, cur_bitoff, *NeighbourBSPreambleRSSIMean );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_NBS_PSCAN_Results_dmL1NBSPSCANResults_NBSPSCANResult_NeighbourBSTimeOffset_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, INT* NeighbourBSTimeOffset )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_NBS_PSCAN_Results_dmL1NBSPSCANResults_NBSPSCANResult_NeighbourBSTimeOffset_GET( base_ptr, i0, cur_ptr, cur_bitoff, *NeighbourBSTimeOffset );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_NBS_PSCAN_Results_dmL1NBSPSCANResults_NBSPSCANResult_IntraInterFAFlag_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* IntraInterFAFlag )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_NBS_PSCAN_Results_dmL1NBSPSCANResults_NBSPSCANResult_IntraInterFAFlag_GET( base_ptr, i0, cur_ptr, cur_bitoff, *IntraInterFAFlag );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_NBS_PSCAN_Results_dmL1NBSPSCANResults_NBSPSCANResult_MeasurementsValidityFlag_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* MeasurementsValidityFlag )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_NBS_PSCAN_Results_dmL1NBSPSCANResults_NBSPSCANResult_MeasurementsValidityFlag_GET( base_ptr, i0, cur_ptr, cur_bitoff, *MeasurementsValidityFlag );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_BST_FrameNumber_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, *FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_BST_uSecInFrame_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, *uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_HarqPerfComp_NacksSent_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* NacksSent )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_HarqPerfComp_NacksSent_GET( base_ptr, cur_ptr, cur_bitoff, *NacksSent );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_HarqPerfComp_AcksSent_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* AcksSent )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_HarqPerfComp_AcksSent_GET( base_ptr, cur_ptr, cur_bitoff, *AcksSent );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_HarqPerfComp_DuplicatesRx_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* DuplicatesRx )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_HarqPerfComp_DuplicatesRx_GET( base_ptr, cur_ptr, cur_bitoff, *DuplicatesRx );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_HarqPerfComp_BurstsTx_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* BurstsTx )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_HarqPerfComp_BurstsTx_GET( base_ptr, cur_ptr, cur_bitoff, *BurstsTx );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_HarqPerfComp_BurstsRx_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* BurstsRx )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_HarqPerfComp_BurstsRx_GET( base_ptr, cur_ptr, cur_bitoff, *BurstsRx );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_HarqPerfComp_Reserved_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* Reserved )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_HarqPerfComp_Reserved_GET( base_ptr, cur_ptr, cur_bitoff, *Reserved );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_HarqPerfComp_RetransUL_Array_Retrans_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT16* Retrans )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_HarqPerfComp_RetransUL_Array_Retrans_GET( base_ptr, i0, cur_ptr, cur_bitoff, *Retrans );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_HarqPerfComp_RetransDL_Array_Retrans_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT16* Retrans )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_HarqPerfComp_RetransDL_Array_Retrans_GET( base_ptr, i0, cur_ptr, cur_bitoff, *Retrans );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_HarqPerfComp_DropHarqBurstCount_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* DropHarqBurstCount )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_HarqPerfComp_DropHarqBurstCount_GET( base_ptr, cur_ptr, cur_bitoff, *DropHarqBurstCount );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_HarqPerfComp_AgingArrayUL_Retrans_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT16* Retrans )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_HarqPerfComp_AgingArrayUL_Retrans_GET( base_ptr, i0, cur_ptr, cur_bitoff, *Retrans );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_HarqPerfComp_AgingArrayDL_Retrans_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT16* Retrans )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_HarqPerfComp_AgingArrayDL_Retrans_GET( base_ptr, i0, cur_ptr, cur_bitoff, *Retrans );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BST_FrameNumber_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, *FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BST_uSecInFrame_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, *uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_RxBurstsPerMcs_Array_Bursts_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT16* Bursts )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_RxBurstsPerMcs_Array_Bursts_GET( base_ptr, i0, cur_ptr, cur_bitoff, *Bursts );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_TxBurstsPerMcs_Array_Bursts_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT16* Bursts )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_TxBurstsPerMcs_Array_Bursts_GET( base_ptr, i0, cur_ptr, cur_bitoff, *Bursts );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_UL_BurstDataZone_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* UL_BurstDataZone )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_UL_BurstDataZone_GET( base_ptr, cur_ptr, cur_bitoff, *UL_BurstDataZone );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_DL_BurstDataFecScheme_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* DL_BurstDataFecScheme )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_DL_BurstDataFecScheme_GET( base_ptr, cur_ptr, cur_bitoff, *DL_BurstDataFecScheme );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_UL_BurstDataFecScheme_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* UL_BurstDataFecScheme )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_UL_BurstDataFecScheme_GET( base_ptr, cur_ptr, cur_bitoff, *UL_BurstDataFecScheme );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_DL_BurstDataCid_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* DL_BurstDataCid )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_DL_BurstDataCid_GET( base_ptr, cur_ptr, cur_bitoff, *DL_BurstDataCid );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_DL_BurstDataDiuc_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* DL_BurstDataDiuc )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_DL_BurstDataDiuc_GET( base_ptr, cur_ptr, cur_bitoff, *DL_BurstDataDiuc );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_UL_BurstDataUiuc_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* UL_BurstDataUiuc )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_UL_BurstDataUiuc_GET( base_ptr, cur_ptr, cur_bitoff, *UL_BurstDataUiuc );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_DL_BurstDataRepetition_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* DL_BurstDataRepetition )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_DL_BurstDataRepetition_GET( base_ptr, cur_ptr, cur_bitoff, *DL_BurstDataRepetition );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_UL_BurstDataRepetition_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* UL_BurstDataRepetition )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_UL_BurstDataRepetition_GET( base_ptr, cur_ptr, cur_bitoff, *UL_BurstDataRepetition );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_UL_TotalFec_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* UL_TotalFec )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_UL_TotalFec_GET( base_ptr, cur_ptr, cur_bitoff, *UL_TotalFec );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_DL_TotalFec_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* DL_TotalFec )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_DL_TotalFec_GET( base_ptr, cur_ptr, cur_bitoff, *DL_TotalFec );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_FecMode_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* FecMode )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_FecMode_GET( base_ptr, cur_ptr, cur_bitoff, *FecMode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_FecTypeID_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* FecTypeID )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_FecTypeID_GET( base_ptr, cur_ptr, cur_bitoff, *FecTypeID );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_FecNumberOfError_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* FecNumberOfError )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_FecNumberOfError_GET( base_ptr, cur_ptr, cur_bitoff, *FecNumberOfError );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaTxAttrib_BST_FrameNumber_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaTxAttrib_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, *FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaTxAttrib_BST_uSecInFrame_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaTxAttrib_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, *uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaTxAttrib_CdmaTxAttribComp_FrameContainsCdmaTx_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* FrameContainsCdmaTx )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaTxAttrib_CdmaTxAttribComp_FrameContainsCdmaTx_GET( base_ptr, cur_ptr, cur_bitoff, *FrameContainsCdmaTx );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaTxAttrib_CdmaTxAttribComp_FrameRefLow_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* FrameRefLow )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaTxAttrib_CdmaTxAttribComp_FrameRefLow_GET( base_ptr, cur_ptr, cur_bitoff, *FrameRefLow );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaTxAttrib_CdmaTxAttribComp_SymbolsRef_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* SymbolsRef )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaTxAttrib_CdmaTxAttribComp_SymbolsRef_GET( base_ptr, cur_ptr, cur_bitoff, *SymbolsRef );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaTxAttrib_CdmaTxAttribComp_SubChRef_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* SubChRef )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaTxAttrib_CdmaTxAttribComp_SubChRef_GET( base_ptr, cur_ptr, cur_bitoff, *SubChRef );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaTxAttrib_CdmaTxAttribComp_RangingCode_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* RangingCode )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaTxAttrib_CdmaTxAttribComp_RangingCode_GET( base_ptr, cur_ptr, cur_bitoff, *RangingCode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaTxAttrib_CdmaTxAttribComp_Reserved_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* Reserved )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaTxAttrib_CdmaTxAttribComp_Reserved_GET( base_ptr, cur_ptr, cur_bitoff, *Reserved );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_BST_FrameNumber_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, *FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_BST_uSecInFrame_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, *uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_FWL2MonitorGroupRangingTraceEvent_DilloCdmaAttributes_xOffset_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* xOffset )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_FWL2MonitorGroupRangingTraceEvent_DilloCdmaAttributes_xOffset_GET( base_ptr, cur_ptr, cur_bitoff, *xOffset );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_FWL2MonitorGroupRangingTraceEvent_DilloCdmaAttributes_yOffset_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* yOffset )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_FWL2MonitorGroupRangingTraceEvent_DilloCdmaAttributes_yOffset_GET( base_ptr, cur_ptr, cur_bitoff, *yOffset );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_FWL2MonitorGroupRangingTraceEvent_DilloCdmaAttributes_codeNumber_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* codeNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_FWL2MonitorGroupRangingTraceEvent_DilloCdmaAttributes_codeNumber_GET( base_ptr, cur_ptr, cur_bitoff, *codeNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_FWL2MonitorGroupRangingTraceEvent_DilloCdmaAttributes_frameNumber_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* frameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_FWL2MonitorGroupRangingTraceEvent_DilloCdmaAttributes_frameNumber_GET( base_ptr, cur_ptr, cur_bitoff, *frameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_FWL2MonitorGroupRangingTraceEvent_RangingType_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, ERangingMode* RangingType )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_FWL2MonitorGroupRangingTraceEvent_RangingType_GET( base_ptr, cur_ptr, cur_bitoff, *RangingType );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_FWL2MonitorGroupRangingTraceEvent_TimingAdjustment_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, INT* TimingAdjustment )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_FWL2MonitorGroupRangingTraceEvent_TimingAdjustment_GET( base_ptr, cur_ptr, cur_bitoff, *TimingAdjustment );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_FWL2MonitorGroupRangingTraceEvent_PowerLevelAdjust_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, INT* PowerLevelAdjust )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_FWL2MonitorGroupRangingTraceEvent_PowerLevelAdjust_GET( base_ptr, cur_ptr, cur_bitoff, *PowerLevelAdjust );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_FWL2MonitorGroupRangingTraceEvent_InvitingRetries_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* InvitingRetries )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_FWL2MonitorGroupRangingTraceEvent_InvitingRetries_GET( base_ptr, cur_ptr, cur_bitoff, *InvitingRetries );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_FWL2MonitorGroupRangingTraceEvent_ContentionRetries_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* ContentionRetries )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_FWL2MonitorGroupRangingTraceEvent_ContentionRetries_GET( base_ptr, cur_ptr, cur_bitoff, *ContentionRetries );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_FWL2MonitorGroupRangingTraceEvent_rangingStatus_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, EDMRangingRspStatus* rangingStatus )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_FWL2MonitorGroupRangingTraceEvent_rangingStatus_GET( base_ptr, cur_ptr, cur_bitoff, *rangingStatus );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaBwr_BST_FrameNumber_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaBwr_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, *FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaBwr_BST_uSecInFrame_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaBwr_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, *uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaBwr_FWCdmaBwrEvent_TotalNumberOfCdmaBwrInit_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* TotalNumberOfCdmaBwrInit )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaBwr_FWCdmaBwrEvent_TotalNumberOfCdmaBwrInit_GET( base_ptr, cur_ptr, cur_bitoff, *TotalNumberOfCdmaBwrInit );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaBwr_FWCdmaBwrEvent_TotalNumberOfTxCdmaBwr_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* TotalNumberOfTxCdmaBwr )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaBwr_FWCdmaBwrEvent_TotalNumberOfTxCdmaBwr_GET( base_ptr, cur_ptr, cur_bitoff, *TotalNumberOfTxCdmaBwr );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloSfAndQosPerformanceGroup_BST_FrameNumber_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloSfAndQosPerformanceGroup_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, *FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloSfAndQosPerformanceGroup_BST_uSecInFrame_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloSfAndQosPerformanceGroup_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, *uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloSfAndQosPerformanceGroup_DilloSfAndQosPerformanceComp_TotalBytesThroughputOtaDL_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* TotalBytesThroughputOtaDL )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloSfAndQosPerformanceGroup_DilloSfAndQosPerformanceComp_TotalBytesThroughputOtaDL_GET( base_ptr, cur_ptr, cur_bitoff, *TotalBytesThroughputOtaDL );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloSfAndQosPerformanceGroup_DilloSfAndQosPerformanceComp_TotalBytesThroughputOtaUL_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* TotalBytesThroughputOtaUL )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloSfAndQosPerformanceGroup_DilloSfAndQosPerformanceComp_TotalBytesThroughputOtaUL_GET( base_ptr, cur_ptr, cur_bitoff, *TotalBytesThroughputOtaUL );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloSfAndQosFlowManagementGroup_BST_FrameNumber_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloSfAndQosFlowManagementGroup_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, *FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloSfAndQosFlowManagementGroup_BST_uSecInFrame_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloSfAndQosFlowManagementGroup_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, *uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloSfAndQosFlowManagementGroup_DilloSfAndQosFlowManagementComp_GrantsReceiveSlots_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* GrantsReceiveSlots )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloSfAndQosFlowManagementGroup_DilloSfAndQosFlowManagementComp_GrantsReceiveSlots_GET( base_ptr, cur_ptr, cur_bitoff, *GrantsReceiveSlots );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloSfAndQosFlowManagementGroup_DilloSfAndQosFlowManagementComp_reserved_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* reserved )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloSfAndQosFlowManagementGroup_DilloSfAndQosFlowManagementComp_reserved_GET( base_ptr, cur_ptr, cur_bitoff, *reserved );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloPhyConfigurationGroup_BST_FrameNumber_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloPhyConfigurationGroup_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, *FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloPhyConfigurationGroup_BST_uSecInFrame_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloPhyConfigurationGroup_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, *uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloPhyConfigurationGroup_DilloPhyConfigurationComp_DlMcsAllocationTableNoneMimo_Bursts_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT16* Bursts )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloPhyConfigurationGroup_DilloPhyConfigurationComp_DlMcsAllocationTableNoneMimo_Bursts_GET( base_ptr, i0, cur_ptr, cur_bitoff, *Bursts );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloPhyConfigurationGroup_DilloPhyConfigurationComp_DlMcsAllocationTableMatrixA_Bursts_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT16* Bursts )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloPhyConfigurationGroup_DilloPhyConfigurationComp_DlMcsAllocationTableMatrixA_Bursts_GET( base_ptr, i0, cur_ptr, cur_bitoff, *Bursts );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloPhyConfigurationGroup_DilloPhyConfigurationComp_DlMcsAllocationTableMatrixB_Bursts_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT16* Bursts )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloPhyConfigurationGroup_DilloPhyConfigurationComp_DlMcsAllocationTableMatrixB_Bursts_GET( base_ptr, i0, cur_ptr, cur_bitoff, *Bursts );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloPhyConfigurationGroup_DilloPhyConfigurationComp_UlMcsAllocationTableNoneStc_Bursts_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT16* Bursts )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloPhyConfigurationGroup_DilloPhyConfigurationComp_UlMcsAllocationTableNoneStc_Bursts_GET( base_ptr, i0, cur_ptr, cur_bitoff, *Bursts );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloPhyConfigurationGroup_DilloPhyConfigurationComp_UlMcsAllocationTableStc_Bursts_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT16* Bursts )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloPhyConfigurationGroup_DilloPhyConfigurationComp_UlMcsAllocationTableStc_Bursts_GET( base_ptr, i0, cur_ptr, cur_bitoff, *Bursts );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloMapsGroup_BST_FrameNumber_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloMapsGroup_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, *FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloMapsGroup_BST_uSecInFrame_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloMapsGroup_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, *uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloMapsGroup_DilloMapsComp_TotalNumberOfMaps_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* TotalNumberOfMaps )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloMapsGroup_DilloMapsComp_TotalNumberOfMaps_GET( base_ptr, cur_ptr, cur_bitoff, *TotalNumberOfMaps );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloMapsGroup_DilloMapsComp_TotalBytesOfMaps_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* TotalBytesOfMaps )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloMapsGroup_DilloMapsComp_TotalBytesOfMaps_GET( base_ptr, cur_ptr, cur_bitoff, *TotalBytesOfMaps );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_BasicStatus_L3_BST_FrameNumber_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_BasicStatus_L3_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, *FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_BasicStatus_L3_BST_uSecInFrame_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_BasicStatus_L3_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, *uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_BasicStatus_L3_BasicStatus_L3_frequency_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* frequency )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_BasicStatus_L3_BasicStatus_L3_frequency_GET( base_ptr, cur_ptr, cur_bitoff, *frequency );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_BasicStatus_L3_BasicStatus_L3_ulCidNum_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* ulCidNum )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_BasicStatus_L3_BasicStatus_L3_ulCidNum_GET( base_ptr, cur_ptr, cur_bitoff, *ulCidNum );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_BasicStatus_L3_BasicStatus_L3_dlCidNum_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* dlCidNum )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_BasicStatus_L3_BasicStatus_L3_dlCidNum_GET( base_ptr, cur_ptr, cur_bitoff, *dlCidNum );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_BasicStatus_L3_BasicStatus_L3_preambleIndex_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* preambleIndex )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_BasicStatus_L3_BasicStatus_L3_preambleIndex_GET( base_ptr, cur_ptr, cur_bitoff, *preambleIndex );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_BasicStatus_L3_BasicStatus_L3_bandWidth_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, E_BandWidth* bandWidth )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_BasicStatus_L3_BasicStatus_L3_bandWidth_GET( base_ptr, cur_ptr, cur_bitoff, *bandWidth );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_BasicStatus_L3_BasicStatus_L3_bsId_value_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_BasicStatus_L3_BasicStatus_L3_bsId_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_BasicStatus_L3_BasicStatus_L3_macAddress_value_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_BasicStatus_L3_BasicStatus_L3_macAddress_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BST_FrameNumber_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, *FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BST_uSecInFrame_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, *uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_lastDlPduSize_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* lastDlPduSize )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_lastDlPduSize_GET( base_ptr, cur_ptr, cur_bitoff, *lastDlPduSize );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_totalDlPdusSize_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* totalDlPdusSize )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_totalDlPdusSize_GET( base_ptr, cur_ptr, cur_bitoff, *totalDlPdusSize );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_dlPduCount_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* dlPduCount )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_dlPduCount_GET( base_ptr, cur_ptr, cur_bitoff, *dlPduCount );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_lastDlSduSize_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* lastDlSduSize )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_lastDlSduSize_GET( base_ptr, cur_ptr, cur_bitoff, *lastDlSduSize );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_totalDlSdusSize_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* totalDlSdusSize )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_totalDlSdusSize_GET( base_ptr, cur_ptr, cur_bitoff, *totalDlSdusSize );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_totalUlSduDropCounter_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* totalUlSduDropCounter )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_totalUlSduDropCounter_GET( base_ptr, cur_ptr, cur_bitoff, *totalUlSduDropCounter );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_totalDlPdusSizeInLastDlSubFrame_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* totalDlPdusSizeInLastDlSubFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_totalDlPdusSizeInLastDlSubFrame_GET( base_ptr, cur_ptr, cur_bitoff, *totalDlPdusSizeInLastDlSubFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_numOfCidInfos_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* numOfCidInfos )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_numOfCidInfos_GET( base_ptr, cur_ptr, cur_bitoff, *numOfCidInfos );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_burstStatusPerConnection_CID_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* CID )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_burstStatusPerConnection_CID_GET( base_ptr, i0, cur_ptr, cur_bitoff, *CID );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_burstStatusPerConnection_CIN_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* CIN )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_burstStatusPerConnection_CIN_GET( base_ptr, i0, cur_ptr, cur_bitoff, *CIN );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_burstStatusPerConnection_totalUlSduRateLimitDropCount_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* totalUlSduRateLimitDropCount )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_burstStatusPerConnection_totalUlSduRateLimitDropCount_GET( base_ptr, i0, cur_ptr, cur_bitoff, *totalUlSduRateLimitDropCount );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_burstStatusPerConnection_rateUlDropPackets_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* rateUlDropPackets )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_burstStatusPerConnection_rateUlDropPackets_GET( base_ptr, i0, cur_ptr, cur_bitoff, *rateUlDropPackets );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_burstStatusPerConnection_totalDlReceivedPdu_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* totalDlReceivedPdu )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_burstStatusPerConnection_totalDlReceivedPdu_GET( base_ptr, i0, cur_ptr, cur_bitoff, *totalDlReceivedPdu );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_burstStatusPerConnection_totalUlTransmittedSdu_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* totalUlTransmittedSdu )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_burstStatusPerConnection_totalUlTransmittedSdu_GET( base_ptr, i0, cur_ptr, cur_bitoff, *totalUlTransmittedSdu );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_burstStatusPerConnection_totalOfPduDlBytes_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* totalOfPduDlBytes )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_burstStatusPerConnection_totalOfPduDlBytes_GET( base_ptr, i0, cur_ptr, cur_bitoff, *totalOfPduDlBytes );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_burstStatusPerConnection_totalOfSduDlBytes_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* totalOfSduDlBytes )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_burstStatusPerConnection_totalOfSduDlBytes_GET( base_ptr, i0, cur_ptr, cur_bitoff, *totalOfSduDlBytes );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_BST_FrameNumber_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, *FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_BST_uSecInFrame_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, *uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_numOfCidInfos_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* numOfCidInfos )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_numOfCidInfos_GET( base_ptr, cur_ptr, cur_bitoff, *numOfCidInfos );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_numOfSfCreationSucess_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* numOfSfCreationSucess )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_numOfSfCreationSucess_GET( base_ptr, cur_ptr, cur_bitoff, *numOfSfCreationSucess );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_numOfSfCreationFailure_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* numOfSfCreationFailure )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_numOfSfCreationFailure_GET( base_ptr, cur_ptr, cur_bitoff, *numOfSfCreationFailure );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_numOfSfDeleted_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* numOfSfDeleted )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_numOfSfDeleted_GET( base_ptr, cur_ptr, cur_bitoff, *numOfSfDeleted );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_sfId_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* sfId )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_sfId_GET( base_ptr, i0, cur_ptr, cur_bitoff, *sfId );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_maxSustainedTrafficRate_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* maxSustainedTrafficRate )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_maxSustainedTrafficRate_GET( base_ptr, i0, cur_ptr, cur_bitoff, *maxSustainedTrafficRate );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_maxTrafficBurst_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* maxTrafficBurst )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_maxTrafficBurst_GET( base_ptr, i0, cur_ptr, cur_bitoff, *maxTrafficBurst );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_toleratedJitter_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* toleratedJitter )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_toleratedJitter_GET( base_ptr, i0, cur_ptr, cur_bitoff, *toleratedJitter );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_maximumLatency_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* maximumLatency )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_maximumLatency_GET( base_ptr, i0, cur_ptr, cur_bitoff, *maximumLatency );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_unsolicitedGrantInterval_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* unsolicitedGrantInterval )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_unsolicitedGrantInterval_GET( base_ptr, i0, cur_ptr, cur_bitoff, *unsolicitedGrantInterval );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_minReservedTrafficRate_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* minReservedTrafficRate )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_minReservedTrafficRate_GET( base_ptr, i0, cur_ptr, cur_bitoff, *minReservedTrafficRate );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_cid_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT16* cid )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_cid_GET( base_ptr, i0, cur_ptr, cur_bitoff, *cid );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_sfSchedulingType_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, SFSchedulingType* sfSchedulingType )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_sfSchedulingType_GET( base_ptr, i0, cur_ptr, cur_bitoff, *sfSchedulingType );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_qosParamsSetType_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, E_QoSParamsSetType* qosParamsSetType )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_qosParamsSetType_GET( base_ptr, i0, cur_ptr, cur_bitoff, *qosParamsSetType );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_trafficPrio_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* trafficPrio )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_trafficPrio_GET( base_ptr, i0, cur_ptr, cur_bitoff, *trafficPrio );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_sfSide_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, E_SfSide* sfSide )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_sfSide_GET( base_ptr, i0, cur_ptr, cur_bitoff, *sfSide );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_BST_FrameNumber_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, *FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_BST_uSecInFrame_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, *uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_numOfCidInfos_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* numOfCidInfos )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_numOfCidInfos_GET( base_ptr, cur_ptr, cur_bitoff, *numOfCidInfos );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_arqInfo_sfId_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* sfId )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_arqInfo_sfId_GET( base_ptr, i0, cur_ptr, cur_bitoff, *sfId );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_arqInfo_arqWindowSize_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* arqWindowSize )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_arqInfo_arqWindowSize_GET( base_ptr, i0, cur_ptr, cur_bitoff, *arqWindowSize );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_arqInfo_arqTransmitterDelay_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* arqTransmitterDelay )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_arqInfo_arqTransmitterDelay_GET( base_ptr, i0, cur_ptr, cur_bitoff, *arqTransmitterDelay );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_arqInfo_arqReceiverDelay_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* arqReceiverDelay )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_arqInfo_arqReceiverDelay_GET( base_ptr, i0, cur_ptr, cur_bitoff, *arqReceiverDelay );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_arqInfo_arqBlockLifeTime_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* arqBlockLifeTime )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_arqInfo_arqBlockLifeTime_GET( base_ptr, i0, cur_ptr, cur_bitoff, *arqBlockLifeTime );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_arqInfo_arqSyncLossTimeout_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* arqSyncLossTimeout )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_arqInfo_arqSyncLossTimeout_GET( base_ptr, i0, cur_ptr, cur_bitoff, *arqSyncLossTimeout );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_arqInfo_arqRxPurgeTimeout_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* arqRxPurgeTimeout )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_arqInfo_arqRxPurgeTimeout_GET( base_ptr, i0, cur_ptr, cur_bitoff, *arqRxPurgeTimeout );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_arqInfo_arqBlockSize_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* arqBlockSize )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_arqInfo_arqBlockSize_GET( base_ptr, i0, cur_ptr, cur_bitoff, *arqBlockSize );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_arqInfo_t22_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* t22 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_arqInfo_t22_GET( base_ptr, i0, cur_ptr, cur_bitoff, *t22 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_arqInfo_arqEnable_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* arqEnable )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_arqInfo_arqEnable_GET( base_ptr, i0, cur_ptr, cur_bitoff, *arqEnable );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_arqInfo_arqDeliverInOrder_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* arqDeliverInOrder )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_arqInfo_arqDeliverInOrder_GET( base_ptr, i0, cur_ptr, cur_bitoff, *arqDeliverInOrder );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Harq_MonitorInfo_L3_BST_FrameNumber_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Harq_MonitorInfo_L3_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, *FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Harq_MonitorInfo_L3_BST_uSecInFrame_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Harq_MonitorInfo_L3_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, *uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Harq_MonitorInfo_L3_Harq_MonitorInfo_L3_numOfCidInfos_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* numOfCidInfos )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Harq_MonitorInfo_L3_Harq_MonitorInfo_L3_numOfCidInfos_GET( base_ptr, cur_ptr, cur_bitoff, *numOfCidInfos );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Harq_MonitorInfo_L3_Harq_MonitorInfo_L3_harqInfo_harqChannelMapping_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT16* harqChannelMapping )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Harq_MonitorInfo_L3_Harq_MonitorInfo_L3_harqInfo_harqChannelMapping_GET( base_ptr, i0, cur_ptr, cur_bitoff, *harqChannelMapping );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Harq_MonitorInfo_L3_Harq_MonitorInfo_L3_harqInfo_harqEnable_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* harqEnable )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Harq_MonitorInfo_L3_Harq_MonitorInfo_L3_harqInfo_harqEnable_GET( base_ptr, i0, cur_ptr, cur_bitoff, *harqEnable );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Harq_MonitorInfo_L3_Harq_MonitorInfo_L3_harqInfo_harqisForReorder_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* harqisForReorder )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Harq_MonitorInfo_L3_Harq_MonitorInfo_L3_harqInfo_harqisForReorder_GET( base_ptr, i0, cur_ptr, cur_bitoff, *harqisForReorder );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Harq_MonitorInfo_L3_Harq_MonitorInfo_L3_harqInfo_sfId_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* sfId )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Harq_MonitorInfo_L3_Harq_MonitorInfo_L3_harqInfo_sfId_GET( base_ptr, i0, cur_ptr, cur_bitoff, *sfId );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MacState_L3_BST_FrameNumber_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MacState_L3_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, *FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MacState_L3_BST_uSecInFrame_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MacState_L3_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, *uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MacState_L3_MacState_L3_state_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, E_MacState* state )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MacState_L3_MacState_L3_state_GET( base_ptr, cur_ptr, cur_bitoff, *state );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_BST_FrameNumber_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, *FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_BST_uSecInFrame_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, *uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_numOfIntraFASNbrs_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* numOfIntraFASNbrs )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_numOfIntraFASNbrs_GET( base_ptr, cur_ptr, cur_bitoff, *numOfIntraFASNbrs );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_numOfInterFASNbrs_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* numOfInterFASNbrs )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_numOfInterFASNbrs_GET( base_ptr, cur_ptr, cur_bitoff, *numOfInterFASNbrs );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_intraFaNbrs_rssiMean_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, INT16* rssiMean )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_intraFaNbrs_rssiMean_GET( base_ptr, i0, cur_ptr, cur_bitoff, *rssiMean );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_intraFaNbrs_cinrMean_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, INT16* cinrMean )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_intraFaNbrs_cinrMean_GET( base_ptr, i0, cur_ptr, cur_bitoff, *cinrMean );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_intraFaNbrs_preambleId_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* preambleId )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_intraFaNbrs_preambleId_GET( base_ptr, i0, cur_ptr, cur_bitoff, *preambleId );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_intraFaNbrs_frequency_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* frequency )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_intraFaNbrs_frequency_GET( base_ptr, i0, cur_ptr, cur_bitoff, *frequency );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_intraFaNbrs_bandWidth_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, E_BandWidth* bandWidth )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_intraFaNbrs_bandWidth_GET( base_ptr, i0, cur_ptr, cur_bitoff, *bandWidth );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_intraFaNbrs_bsId_value_GET( UINT8* base_ptr, UINT32 i0, UINT32 i1, UINT32 diff, UINT32 cur_bitoff, UINT8* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_intraFaNbrs_bsId_value_GET( base_ptr, i0, i1, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_interFaNbrs_rssiMean_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, INT16* rssiMean )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_interFaNbrs_rssiMean_GET( base_ptr, i0, cur_ptr, cur_bitoff, *rssiMean );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_interFaNbrs_cinrMean_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, INT16* cinrMean )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_interFaNbrs_cinrMean_GET( base_ptr, i0, cur_ptr, cur_bitoff, *cinrMean );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_interFaNbrs_preambleId_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* preambleId )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_interFaNbrs_preambleId_GET( base_ptr, i0, cur_ptr, cur_bitoff, *preambleId );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_interFaNbrs_frequency_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* frequency )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_interFaNbrs_frequency_GET( base_ptr, i0, cur_ptr, cur_bitoff, *frequency );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_interFaNbrs_bandWidth_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, E_BandWidth* bandWidth )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_interFaNbrs_bandWidth_GET( base_ptr, i0, cur_ptr, cur_bitoff, *bandWidth );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_interFaNbrs_bsId_value_GET( UINT8* base_ptr, UINT32 i0, UINT32 i1, UINT32 diff, UINT32 cur_bitoff, UINT8* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_interFaNbrs_bsId_value_GET( base_ptr, i0, i1, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_NwEntryMsgLatency_L3_BST_FrameNumber_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_NwEntryMsgLatency_L3_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, *FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_NwEntryMsgLatency_L3_BST_uSecInFrame_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_NwEntryMsgLatency_L3_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, *uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_NwEntryMsgLatency_L3_NwEntryMsgLatency_L3_initRengLatency_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* initRengLatency )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_NwEntryMsgLatency_L3_NwEntryMsgLatency_L3_initRengLatency_GET( base_ptr, cur_ptr, cur_bitoff, *initRengLatency );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_NwEntryMsgLatency_L3_NwEntryMsgLatency_L3_sbcLatency_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* sbcLatency )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_NwEntryMsgLatency_L3_NwEntryMsgLatency_L3_sbcLatency_GET( base_ptr, cur_ptr, cur_bitoff, *sbcLatency );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_NwEntryMsgLatency_L3_NwEntryMsgLatency_L3_pkmLatency_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* pkmLatency )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_NwEntryMsgLatency_L3_NwEntryMsgLatency_L3_pkmLatency_GET( base_ptr, cur_ptr, cur_bitoff, *pkmLatency );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_NwEntryMsgLatency_L3_NwEntryMsgLatency_L3_regLatency_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* regLatency )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_NwEntryMsgLatency_L3_NwEntryMsgLatency_L3_regLatency_GET( base_ptr, cur_ptr, cur_bitoff, *regLatency );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_NwEntryMsgLatency_L3_NwEntryMsgLatency_L3_dsaLatency_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* dsaLatency )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_NwEntryMsgLatency_L3_NwEntryMsgLatency_L3_dsaLatency_GET( base_ptr, cur_ptr, cur_bitoff, *dsaLatency );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_NwEntryMsgLatency_L3_NwEntryMsgLatency_L3_setuUpTime_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* setuUpTime )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_NwEntryMsgLatency_L3_NwEntryMsgLatency_L3_setuUpTime_GET( base_ptr, cur_ptr, cur_bitoff, *setuUpTime );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DcdUcdTimeout_L3_BST_FrameNumber_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DcdUcdTimeout_L3_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, *FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DcdUcdTimeout_L3_BST_uSecInFrame_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DcdUcdTimeout_L3_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, *uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DcdUcdTimeout_L3_DcdUcdTimeout_L3_countDcdUcdTimeOut_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* countDcdUcdTimeOut )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DcdUcdTimeout_L3_DcdUcdTimeout_L3_countDcdUcdTimeOut_GET( base_ptr, cur_ptr, cur_bitoff, *countDcdUcdTimeOut );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DSxTimers_L3_BST_FrameNumber_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DSxTimers_L3_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, *FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DSxTimers_L3_BST_uSecInFrame_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DSxTimers_L3_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, *uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DSxTimers_L3_DSxTimers_L3_t7Timeout_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* t7Timeout )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DSxTimers_L3_DSxTimers_L3_t7Timeout_GET( base_ptr, cur_ptr, cur_bitoff, *t7Timeout );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DSxTimers_L3_DSxTimers_L3_t8Timeout_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* t8Timeout )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DSxTimers_L3_DSxTimers_L3_t8Timeout_GET( base_ptr, cur_ptr, cur_bitoff, *t8Timeout );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DSxTimers_L3_DSxTimers_L3_t10Timeout_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* t10Timeout )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DSxTimers_L3_DSxTimers_L3_t10Timeout_GET( base_ptr, cur_ptr, cur_bitoff, *t10Timeout );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DSxTimers_L3_DSxTimers_L3_dsxReqRetries_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* dsxReqRetries )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DSxTimers_L3_DSxTimers_L3_dsxReqRetries_GET( base_ptr, cur_ptr, cur_bitoff, *dsxReqRetries );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DSxTimers_L3_DSxTimers_L3_dsxRspRetries_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* dsxRspRetries )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DSxTimers_L3_DSxTimers_L3_dsxRspRetries_GET( base_ptr, cur_ptr, cur_bitoff, *dsxRspRetries );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Phy_L3_BST_FrameNumber_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Phy_L3_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, *FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Phy_L3_BST_uSecInFrame_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Phy_L3_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, *uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Phy_L3_Phy_L3_preambleSearchTime_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* preambleSearchTime )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Phy_L3_Phy_L3_preambleSearchTime_GET( base_ptr, cur_ptr, cur_bitoff, *preambleSearchTime );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Phy_L3_Phy_L3_numOfPreamble_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* numOfPreamble )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Phy_L3_Phy_L3_numOfPreamble_GET( base_ptr, cur_ptr, cur_bitoff, *numOfPreamble );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_LinkLossOccur_L3_BST_FrameNumber_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_LinkLossOccur_L3_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, *FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_LinkLossOccur_L3_BST_uSecInFrame_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_LinkLossOccur_L3_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, *uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_LinkLossOccur_L3_LinkLossOccur_L3_occurrenceTime_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* occurrenceTime )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_LinkLossOccur_L3_LinkLossOccur_L3_occurrenceTime_GET( base_ptr, cur_ptr, cur_bitoff, *occurrenceTime );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_LinkLossOccur_L3_LinkLossOccur_L3_LastLinkLossReason_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, E_LinkLossReason* LastLinkLossReason )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_LinkLossOccur_L3_LinkLossOccur_L3_LastLinkLossReason_GET( base_ptr, cur_ptr, cur_bitoff, *LastLinkLossReason );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_LinkLossOccur_L3_LinkLossOccur_L3_bsId_value_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_LinkLossOccur_L3_LinkLossOccur_L3_bsId_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Moniter_Scan_Config_BST_FrameNumber_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Moniter_Scan_Config_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, *FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Moniter_Scan_Config_BST_uSecInFrame_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Moniter_Scan_Config_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, *uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Moniter_Scan_Config_MoniterScanConfig_SetScanParam_NumOfChannels_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* NumOfChannels )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Moniter_Scan_Config_MoniterScanConfig_SetScanParam_NumOfChannels_GET( base_ptr, cur_ptr, cur_bitoff, *NumOfChannels );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Moniter_Scan_Config_MoniterScanConfig_SetScanParam_Channels_Frequency_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* Frequency )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Moniter_Scan_Config_MoniterScanConfig_SetScanParam_Channels_Frequency_GET( base_ptr, i0, cur_ptr, cur_bitoff, *Frequency );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Moniter_Scan_Config_MoniterScanConfig_SetScanParam_Channels_ChannelId_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT16* ChannelId )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Moniter_Scan_Config_MoniterScanConfig_SetScanParam_Channels_ChannelId_GET( base_ptr, i0, cur_ptr, cur_bitoff, *ChannelId );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Moniter_Scan_Config_MoniterScanConfig_SetScanParam_Channels_Bandwidth_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* Bandwidth )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Moniter_Scan_Config_MoniterScanConfig_SetScanParam_Channels_Bandwidth_GET( base_ptr, i0, cur_ptr, cur_bitoff, *Bandwidth );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Moniter_Scan_Config_MoniterScanConfig_SetScanParam_Channels_Fft_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* Fft )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Moniter_Scan_Config_MoniterScanConfig_SetScanParam_Channels_Fft_GET( base_ptr, i0, cur_ptr, cur_bitoff, *Fft );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Moniter_Scan_Config_MoniterScanConfig_SetScanParam_Channels_Preambles_value_GET( UINT8* base_ptr, UINT32 i0, UINT32 i1, UINT32 diff, UINT32 cur_bitoff, UINT8* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Moniter_Scan_Config_MoniterScanConfig_SetScanParam_Channels_Preambles_value_GET( base_ptr, i0, i1, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Moniter_Scan_Config_MoniterScanConfig_SetScanParam_Channels_Reserved_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* Reserved )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Moniter_Scan_Config_MoniterScanConfig_SetScanParam_Channels_Reserved_GET( base_ptr, i0, cur_ptr, cur_bitoff, *Reserved );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DSPS_Management_MSG_BST_FrameNumber_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DSPS_Management_MSG_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, *FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DSPS_Management_MSG_BST_uSecInFrame_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DSPS_Management_MSG_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, *uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DSPS_Management_MSG_DSPS_Management_MSG_MngmntBufferRun_value_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DSPS_Management_MSG_DSPS_Management_MSG_MngmntBufferRun_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_linkLossStatistics_L3_BST_FrameNumber_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_linkLossStatistics_L3_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, *FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_linkLossStatistics_L3_BST_uSecInFrame_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_linkLossStatistics_L3_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, *uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_linkLossStatistics_L3_linkLossStatistics_L3_occurrenceTime_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* occurrenceTime )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_linkLossStatistics_L3_linkLossStatistics_L3_occurrenceTime_GET( base_ptr, cur_ptr, cur_bitoff, *occurrenceTime );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_linkLossStatistics_L3_linkLossStatistics_L3_linkLossLatency_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* linkLossLatency )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_linkLossStatistics_L3_linkLossStatistics_L3_linkLossLatency_GET( base_ptr, cur_ptr, cur_bitoff, *linkLossLatency );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_linkLossStatistics_L3_linkLossStatistics_L3_HoRangingLatency_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* HoRangingLatency )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_linkLossStatistics_L3_linkLossStatistics_L3_HoRangingLatency_GET( base_ptr, cur_ptr, cur_bitoff, *HoRangingLatency );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_linkLossStatistics_L3_linkLossStatistics_L3_bsId_value_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_linkLossStatistics_L3_linkLossStatistics_L3_bsId_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_BST_FrameNumber_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, *FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_BST_uSecInFrame_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, *uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_numOfBsInHoReq_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* numOfBsInHoReq )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_numOfBsInHoReq_GET( base_ptr, cur_ptr, cur_bitoff, *numOfBsInHoReq );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_numOfBsInHoRsp_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* numOfBsInHoRsp )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_numOfBsInHoRsp_GET( base_ptr, cur_ptr, cur_bitoff, *numOfBsInHoRsp );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_HoSuccessCounter_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* HoSuccessCounter )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_HoSuccessCounter_GET( base_ptr, cur_ptr, cur_bitoff, *HoSuccessCounter );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_HoFailCounter_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* HoFailCounter )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_HoFailCounter_GET( base_ptr, cur_ptr, cur_bitoff, *HoFailCounter );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_HoTriggersCounter_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* HoTriggersCounter )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_HoTriggersCounter_GET( base_ptr, cur_ptr, cur_bitoff, *HoTriggersCounter );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_HoRejectsCounter_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* HoRejectsCounter )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_HoRejectsCounter_GET( base_ptr, cur_ptr, cur_bitoff, *HoRejectsCounter );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_HoNotRecommendedCounter_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* HoNotRecommendedCounter )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_HoNotRecommendedCounter_GET( base_ptr, cur_ptr, cur_bitoff, *HoNotRecommendedCounter );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_numberOfTBSAttempted_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* numberOfTBSAttempted )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_numberOfTBSAttempted_GET( base_ptr, cur_ptr, cur_bitoff, *numberOfTBSAttempted );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_cancellationWithNormalOperation_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* cancellationWithNormalOperation )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_cancellationWithNormalOperation_GET( base_ptr, cur_ptr, cur_bitoff, *cancellationWithNormalOperation );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_cancellationWithReentryProblem_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* cancellationWithReentryProblem )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_cancellationWithReentryProblem_GET( base_ptr, cur_ptr, cur_bitoff, *cancellationWithReentryProblem );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_coordHoLatency_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* coordHoLatency )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_coordHoLatency_GET( base_ptr, cur_ptr, cur_bitoff, *coordHoLatency );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_cutOffLatency_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* cutOffLatency )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_cutOffLatency_GET( base_ptr, cur_ptr, cur_bitoff, *cutOffLatency );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_status_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, E_HOStatus* status )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_status_GET( base_ptr, cur_ptr, cur_bitoff, *status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_typeId_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, E_HOTypeId* typeId )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_typeId_GET( base_ptr, cur_ptr, cur_bitoff, *typeId );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_hoReqBsList_bsId_value_GET( UINT8* base_ptr, UINT32 i0, UINT32 i1, UINT32 diff, UINT32 cur_bitoff, UINT8* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_hoReqBsList_bsId_value_GET( base_ptr, i0, i1, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_hoRspBsList_bsId_value_GET( UINT8* base_ptr, UINT32 i0, UINT32 i1, UINT32 diff, UINT32 cur_bitoff, UINT8* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_hoRspBsList_bsId_value_GET( base_ptr, i0, i1, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_BST_FrameNumber_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, *FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_BST_uSecInFrame_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, *uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_McsIndexTable_L3_NumDlburstProfiles_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* NumDlburstProfiles )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_McsIndexTable_L3_NumDlburstProfiles_GET( base_ptr, cur_ptr, cur_bitoff, *NumDlburstProfiles );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_McsIndexTable_L3_NumUlburstProfiles_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* NumUlburstProfiles )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_McsIndexTable_L3_NumUlburstProfiles_GET( base_ptr, cur_ptr, cur_bitoff, *NumUlburstProfiles );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_McsIndexTable_L3_DlburstProfiles_intervalUsageCode_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* intervalUsageCode )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_McsIndexTable_L3_DlburstProfiles_intervalUsageCode_GET( base_ptr, i0, cur_ptr, cur_bitoff, *intervalUsageCode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_McsIndexTable_L3_DlburstProfiles_fecType_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, FecType* fecType )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_McsIndexTable_L3_DlburstProfiles_fecType_GET( base_ptr, i0, cur_ptr, cur_bitoff, *fecType );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_McsIndexTable_L3_DlburstProfiles_fecRate_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, FecRate* fecRate )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_McsIndexTable_L3_DlburstProfiles_fecRate_GET( base_ptr, i0, cur_ptr, cur_bitoff, *fecRate );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_McsIndexTable_L3_DlburstProfiles_modulation_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, Modulation* modulation )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_McsIndexTable_L3_DlburstProfiles_modulation_GET( base_ptr, i0, cur_ptr, cur_bitoff, *modulation );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_McsIndexTable_L3_UlburstProfiles_intervalUsageCode_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* intervalUsageCode )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_McsIndexTable_L3_UlburstProfiles_intervalUsageCode_GET( base_ptr, i0, cur_ptr, cur_bitoff, *intervalUsageCode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_McsIndexTable_L3_UlburstProfiles_fecType_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, FecType* fecType )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_McsIndexTable_L3_UlburstProfiles_fecType_GET( base_ptr, i0, cur_ptr, cur_bitoff, *fecType );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_McsIndexTable_L3_UlburstProfiles_fecRate_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, FecRate* fecRate )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_McsIndexTable_L3_UlburstProfiles_fecRate_GET( base_ptr, i0, cur_ptr, cur_bitoff, *fecRate );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_McsIndexTable_L3_UlburstProfiles_modulation_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, Modulation* modulation )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_McsIndexTable_L3_UlburstProfiles_modulation_GET( base_ptr, i0, cur_ptr, cur_bitoff, *modulation );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_ScanResult_L3_BST_FrameNumber_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_ScanResult_L3_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, *FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_ScanResult_L3_BST_uSecInFrame_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_ScanResult_L3_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, *uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_ScanResult_L3_ScanResult_L3_numOfNbrs_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* numOfNbrs )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_ScanResult_L3_ScanResult_L3_numOfNbrs_GET( base_ptr, cur_ptr, cur_bitoff, *numOfNbrs );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_ScanResult_L3_ScanResult_L3_resultNbrs_phyLinkId_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* phyLinkId )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_ScanResult_L3_ScanResult_L3_resultNbrs_phyLinkId_GET( base_ptr, i0, cur_ptr, cur_bitoff, *phyLinkId );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_ScanResult_L3_ScanResult_L3_resultNbrs_frequency_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* frequency )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_ScanResult_L3_ScanResult_L3_resultNbrs_frequency_GET( base_ptr, i0, cur_ptr, cur_bitoff, *frequency );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_ScanResult_L3_ScanResult_L3_resultNbrs_phyGrade_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, INT16* phyGrade )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_ScanResult_L3_ScanResult_L3_resultNbrs_phyGrade_GET( base_ptr, i0, cur_ptr, cur_bitoff, *phyGrade );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_ScanResult_L3_ScanResult_L3_resultNbrs_preambleId_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* preambleId )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_ScanResult_L3_ScanResult_L3_resultNbrs_preambleId_GET( base_ptr, i0, cur_ptr, cur_bitoff, *preambleId );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_ScanResult_L3_ScanResult_L3_resultNbrs_bandWidth_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, E_BandWidth* bandWidth )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_ScanResult_L3_ScanResult_L3_resultNbrs_bandWidth_GET( base_ptr, i0, cur_ptr, cur_bitoff, *bandWidth );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_ScanResult_L3_ScanResult_L3_resultNbrs_bSValidityIndicator_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, ECellStatus* bSValidityIndicator )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_ScanResult_L3_ScanResult_L3_resultNbrs_bSValidityIndicator_GET( base_ptr, i0, cur_ptr, cur_bitoff, *bSValidityIndicator );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_ScanResult_L3_ScanResult_L3_resultNbrs_bsId_value_GET( UINT8* base_ptr, UINT32 i0, UINT32 i1, UINT32 diff, UINT32 cur_bitoff, UINT8* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_ScanResult_L3_ScanResult_L3_resultNbrs_bsId_value_GET( base_ptr, i0, i1, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_ScanStatus_L3_BST_FrameNumber_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_ScanStatus_L3_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, *FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_ScanStatus_L3_BST_uSecInFrame_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_ScanStatus_L3_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, *uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_ScanStatus_L3_ScanStatus_L3_scanDuration_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* scanDuration )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_ScanStatus_L3_ScanStatus_L3_scanDuration_GET( base_ptr, cur_ptr, cur_bitoff, *scanDuration );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_ScanStatus_L3_ScanStatus_L3_scanIteration_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* scanIteration )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_ScanStatus_L3_ScanStatus_L3_scanIteration_GET( base_ptr, cur_ptr, cur_bitoff, *scanIteration );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_ScanStatus_L3_ScanStatus_L3_modeReport_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* modeReport )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_ScanStatus_L3_ScanStatus_L3_modeReport_GET( base_ptr, cur_ptr, cur_bitoff, *modeReport );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_ScanStatus_L3_ScanStatus_L3_periodReport_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* periodReport )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_ScanStatus_L3_ScanStatus_L3_periodReport_GET( base_ptr, cur_ptr, cur_bitoff, *periodReport );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_ScanStatus_L3_ScanStatus_L3_interleavingInterval_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* interleavingInterval )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_ScanStatus_L3_ScanStatus_L3_interleavingInterval_GET( base_ptr, cur_ptr, cur_bitoff, *interleavingInterval );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_ConnectionDropCount_L3_BST_FrameNumber_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_ConnectionDropCount_L3_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, *FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_ConnectionDropCount_L3_BST_uSecInFrame_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_ConnectionDropCount_L3_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, *uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_ConnectionDropCount_L3_ConnectionDropCount_L3_counterConnectionDropEvent_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* counterConnectionDropEvent )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_ConnectionDropCount_L3_ConnectionDropCount_L3_counterConnectionDropEvent_GET( base_ptr, cur_ptr, cur_bitoff, *counterConnectionDropEvent );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_BST_FrameNumber_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, *FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_BST_uSecInFrame_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, *uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_IdleConfiguration_L3_idleModeTimeout_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* idleModeTimeout )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_IdleConfiguration_L3_idleModeTimeout_GET( base_ptr, cur_ptr, cur_bitoff, *idleModeTimeout );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_IdleConfiguration_L3_pagingCycleReq_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* pagingCycleReq )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_IdleConfiguration_L3_pagingCycleReq_GET( base_ptr, cur_ptr, cur_bitoff, *pagingCycleReq );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_IdleConfiguration_L3_t45Timeout_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* t45Timeout )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_IdleConfiguration_L3_t45Timeout_GET( base_ptr, cur_ptr, cur_bitoff, *t45Timeout );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_IdleConfiguration_L3_PagingGroupID_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* PagingGroupID )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_IdleConfiguration_L3_PagingGroupID_GET( base_ptr, cur_ptr, cur_bitoff, *PagingGroupID );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_IdleConfiguration_L3_PagingCycle_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* PagingCycle )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_IdleConfiguration_L3_PagingCycle_GET( base_ptr, cur_ptr, cur_bitoff, *PagingCycle );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_IdleConfiguration_L3_PagingOffset_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* PagingOffset )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_IdleConfiguration_L3_PagingOffset_GET( base_ptr, cur_ptr, cur_bitoff, *PagingOffset );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_IdleConfiguration_L3_RetainInfo_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* RetainInfo )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_IdleConfiguration_L3_RetainInfo_GET( base_ptr, cur_ptr, cur_bitoff, *RetainInfo );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_IdleConfiguration_L3_dregReqRetries_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* dregReqRetries )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_IdleConfiguration_L3_dregReqRetries_GET( base_ptr, cur_ptr, cur_bitoff, *dregReqRetries );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_IdleConfiguration_L3_PagingIntervalLength_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* PagingIntervalLength )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_IdleConfiguration_L3_PagingIntervalLength_GET( base_ptr, cur_ptr, cur_bitoff, *PagingIntervalLength );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_IdleConfiguration_L3_PagingControllerID_value_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_IdleConfiguration_L3_PagingControllerID_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_IdlePerformance_L3_BST_FrameNumber_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_IdlePerformance_L3_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, *FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_IdlePerformance_L3_BST_uSecInFrame_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_IdlePerformance_L3_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, *uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_IdlePerformance_L3_IdlePerformance_L3_counterInternalTimer_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* counterInternalTimer )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_IdlePerformance_L3_IdlePerformance_L3_counterInternalTimer_GET( base_ptr, cur_ptr, cur_bitoff, *counterInternalTimer );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_IdlePerformance_L3_IdlePerformance_L3_counterNWInitiated_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* counterNWInitiated )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_IdlePerformance_L3_IdlePerformance_L3_counterNWInitiated_GET( base_ptr, cur_ptr, cur_bitoff, *counterNWInitiated );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_IdlePerformance_L3_IdlePerformance_L3_counterGroupChange_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* counterGroupChange )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_IdlePerformance_L3_IdlePerformance_L3_counterGroupChange_GET( base_ptr, cur_ptr, cur_bitoff, *counterGroupChange );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_IdlePerformance_L3_IdlePerformance_L3_counterSecuredLu_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* counterSecuredLu )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_IdlePerformance_L3_IdlePerformance_L3_counterSecuredLu_GET( base_ptr, cur_ptr, cur_bitoff, *counterSecuredLu );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_IdlePerformance_L3_IdlePerformance_L3_counterUnSecuredLu_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* counterUnSecuredLu )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_IdlePerformance_L3_IdlePerformance_L3_counterUnSecuredLu_GET( base_ptr, cur_ptr, cur_bitoff, *counterUnSecuredLu );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_BST_FrameNumber_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, *FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_BST_uSecInFrame_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, *uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqResetPerformed_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* arqResetPerformed )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqResetPerformed_GET( base_ptr, cur_ptr, cur_bitoff, *arqResetPerformed );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_numOfCidPerformance_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* numOfCidPerformance )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_numOfCidPerformance_GET( base_ptr, cur_ptr, cur_bitoff, *numOfCidPerformance );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqRxPerformance_CID_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* CID )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqRxPerformance_CID_GET( base_ptr, i0, cur_ptr, cur_bitoff, *CID );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqRxPerformance_CIN_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* CIN )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqRxPerformance_CIN_GET( base_ptr, i0, cur_ptr, cur_bitoff, *CIN );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqRxPerformance_numOfDuplicateReceivedBlocks_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* numOfDuplicateReceivedBlocks )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqRxPerformance_numOfDuplicateReceivedBlocks_GET( base_ptr, i0, cur_ptr, cur_bitoff, *numOfDuplicateReceivedBlocks );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqRxPerformance_numOfPurgeTimeouts_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* numOfPurgeTimeouts )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqRxPerformance_numOfPurgeTimeouts_GET( base_ptr, i0, cur_ptr, cur_bitoff, *numOfPurgeTimeouts );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqRxPerformance_numOfBlocksLostDueToRxPurgeTimout_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* numOfBlocksLostDueToRxPurgeTimout )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqRxPerformance_numOfBlocksLostDueToRxPurgeTimout_GET( base_ptr, i0, cur_ptr, cur_bitoff, *numOfBlocksLostDueToRxPurgeTimout );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqRxPerformance_totalNumOfAcksTxd_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* totalNumOfAcksTxd )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqRxPerformance_totalNumOfAcksTxd_GET( base_ptr, i0, cur_ptr, cur_bitoff, *totalNumOfAcksTxd );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqRxPerformance_numOfRxArqResetsReceived_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* numOfRxArqResetsReceived )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqRxPerformance_numOfRxArqResetsReceived_GET( base_ptr, i0, cur_ptr, cur_bitoff, *numOfRxArqResetsReceived );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqRxPerformance_numOfRxArqResetsInitiated_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* numOfRxArqResetsInitiated )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqRxPerformance_numOfRxArqResetsInitiated_GET( base_ptr, i0, cur_ptr, cur_bitoff, *numOfRxArqResetsInitiated );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqRxPerformance_numOfArqDiscardsReceived_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* numOfArqDiscardsReceived )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqRxPerformance_numOfArqDiscardsReceived_GET( base_ptr, i0, cur_ptr, cur_bitoff, *numOfArqDiscardsReceived );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqRxPerformance_rxThroughput_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* rxThroughput )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqRxPerformance_rxThroughput_GET( base_ptr, i0, cur_ptr, cur_bitoff, *rxThroughput );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqRxPerformance_numOfPduLostDueToNoFreeSpaceInReceiver_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* numOfPduLostDueToNoFreeSpaceInReceiver )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqRxPerformance_numOfPduLostDueToNoFreeSpaceInReceiver_GET( base_ptr, i0, cur_ptr, cur_bitoff, *numOfPduLostDueToNoFreeSpaceInReceiver );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_BST_FrameNumber_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, *FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_BST_uSecInFrame_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, *uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_numOfCidPerformance_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* numOfCidPerformance )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_numOfCidPerformance_GET( base_ptr, cur_ptr, cur_bitoff, *numOfCidPerformance );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_CID_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* CID )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_CID_GET( base_ptr, i0, cur_ptr, cur_bitoff, *CID );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_CIN_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* CIN )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_CIN_GET( base_ptr, i0, cur_ptr, cur_bitoff, *CIN );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_numOfRetransmittedArqBlocksTotalUL_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* numOfRetransmittedArqBlocksTotalUL )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_numOfRetransmittedArqBlocksTotalUL_GET( base_ptr, i0, cur_ptr, cur_bitoff, *numOfRetransmittedArqBlocksTotalUL );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_numOfRetransmittedBlocksUL_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* numOfRetransmittedBlocksUL )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_numOfRetransmittedBlocksUL_GET( base_ptr, i0, cur_ptr, cur_bitoff, *numOfRetransmittedBlocksUL );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_numOfBLTs_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* numOfBLTs )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_numOfBLTs_GET( base_ptr, i0, cur_ptr, cur_bitoff, *numOfBLTs );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_numOfBlocksLostDueToArqBLT_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* numOfBlocksLostDueToArqBLT )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_numOfBlocksLostDueToArqBLT_GET( base_ptr, i0, cur_ptr, cur_bitoff, *numOfBlocksLostDueToArqBLT );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_totalNumOfAcksReceived_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* totalNumOfAcksReceived )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_totalNumOfAcksReceived_GET( base_ptr, i0, cur_ptr, cur_bitoff, *totalNumOfAcksReceived );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_numOfTxArqResetsReceived_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* numOfTxArqResetsReceived )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_numOfTxArqResetsReceived_GET( base_ptr, i0, cur_ptr, cur_bitoff, *numOfTxArqResetsReceived );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_numOfTxArqResetsInitiated_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* numOfTxArqResetsInitiated )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_numOfTxArqResetsInitiated_GET( base_ptr, i0, cur_ptr, cur_bitoff, *numOfTxArqResetsInitiated );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_numOfArqDiscardsTxd_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* numOfArqDiscardsTxd )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_numOfArqDiscardsTxd_GET( base_ptr, i0, cur_ptr, cur_bitoff, *numOfArqDiscardsTxd );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_txThroughput_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* txThroughput )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_txThroughput_GET( base_ptr, i0, cur_ptr, cur_bitoff, *txThroughput );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_numOfSduLostDueToNoFreeSpaceInTransmitter_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* numOfSduLostDueToNoFreeSpaceInTransmitter )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_numOfSduLostDueToNoFreeSpaceInTransmitter_GET( base_ptr, i0, cur_ptr, cur_bitoff, *numOfSduLostDueToNoFreeSpaceInTransmitter );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MonitorSfPerformance_L3_BST_FrameNumber_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MonitorSfPerformance_L3_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, *FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MonitorSfPerformance_L3_BST_uSecInFrame_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MonitorSfPerformance_L3_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, *uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MonitorSfPerformance_L3_SfPerformance_L3_numOfCidInfos_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* numOfCidInfos )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MonitorSfPerformance_L3_SfPerformance_L3_numOfCidInfos_GET( base_ptr, cur_ptr, cur_bitoff, *numOfCidInfos );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MonitorSfPerformance_L3_SfPerformance_L3_SfPeformancePerConnection_CID_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* CID )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MonitorSfPerformance_L3_SfPerformance_L3_SfPeformancePerConnection_CID_GET( base_ptr, i0, cur_ptr, cur_bitoff, *CID );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MonitorSfPerformance_L3_SfPerformance_L3_SfPeformancePerConnection_CIN_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* CIN )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MonitorSfPerformance_L3_SfPerformance_L3_SfPeformancePerConnection_CIN_GET( base_ptr, i0, cur_ptr, cur_bitoff, *CIN );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MonitorSfPerformance_L3_SfPerformance_L3_SfPeformancePerConnection_ulIpThroughput_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* ulIpThroughput )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MonitorSfPerformance_L3_SfPerformance_L3_SfPeformancePerConnection_ulIpThroughput_GET( base_ptr, i0, cur_ptr, cur_bitoff, *ulIpThroughput );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MonitorSfPerformance_L3_SfPerformance_L3_SfPeformancePerConnection_dlIpThroughput_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* dlIpThroughput )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MonitorSfPerformance_L3_SfPerformance_L3_SfPeformancePerConnection_dlIpThroughput_GET( base_ptr, i0, cur_ptr, cur_bitoff, *dlIpThroughput );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Result_BST_FrameNumber_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Result_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, *FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Result_BST_uSecInFrame_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Result_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, *uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Result_MonitorScanResult_AvailableNSPsIdlist_NumOfNSPs_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* NumOfNSPs )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Result_MonitorScanResult_AvailableNSPsIdlist_NumOfNSPs_GET( base_ptr, cur_ptr, cur_bitoff, *NumOfNSPs );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Result_MonitorScanResult_AvailableNSPsIdlist_NSPID_value_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Result_MonitorScanResult_AvailableNSPsIdlist_NSPID_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Result_MonitorScanResult_FullBSIDArr_NumOfBSIDs_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* NumOfBSIDs )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Result_MonitorScanResult_FullBSIDArr_NumOfBSIDs_GET( base_ptr, cur_ptr, cur_bitoff, *NumOfBSIDs );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Result_MonitorScanResult_FullBSIDArr_FullBSID_bsID_bsID_value_GET( UINT8* base_ptr, UINT32 i0, UINT32 i1, UINT32 diff, UINT32 cur_bitoff, UINT8* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Result_MonitorScanResult_FullBSIDArr_FullBSID_bsID_bsID_value_GET( base_ptr, i0, i1, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Result_MonitorScanResult_FullBSIDArr_FullBSID_bsID_Reserved_2_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT16* Reserved_2 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Result_MonitorScanResult_FullBSIDArr_FullBSID_bsID_Reserved_2_GET( base_ptr, i0, cur_ptr, cur_bitoff, *Reserved_2 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Result_MonitorScanResult_FullBSIDArr_FullBSID_bsIDmask_bsIDmask_value_GET( UINT8* base_ptr, UINT32 i0, UINT32 i1, UINT32 diff, UINT32 cur_bitoff, UINT8* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Result_MonitorScanResult_FullBSIDArr_FullBSID_bsIDmask_bsIDmask_value_GET( base_ptr, i0, i1, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Result_MonitorScanResult_FullBSIDArr_FullBSID_bsIDmask_Reserved_2_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT16* Reserved_2 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Result_MonitorScanResult_FullBSIDArr_FullBSID_bsIDmask_Reserved_2_GET( base_ptr, i0, cur_ptr, cur_bitoff, *Reserved_2 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Ind_BST_FrameNumber_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Ind_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, *FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Ind_BST_uSecInFrame_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Ind_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, *uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Ind_MonitorScanInd_ScanStartEndInd_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, BM_StartEndInd* ScanStartEndInd )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Ind_MonitorScanInd_ScanStartEndInd_GET( base_ptr, cur_ptr, cur_bitoff, *ScanStartEndInd );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Ind_MonitorScanInd_Time_wHour_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* wHour )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Ind_MonitorScanInd_Time_wHour_GET( base_ptr, cur_ptr, cur_bitoff, *wHour );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Ind_MonitorScanInd_Time_wMinute_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* wMinute )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Ind_MonitorScanInd_Time_wMinute_GET( base_ptr, cur_ptr, cur_bitoff, *wMinute );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Ind_MonitorScanInd_Time_wSecond_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* wSecond )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Ind_MonitorScanInd_Time_wSecond_GET( base_ptr, cur_ptr, cur_bitoff, *wSecond );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Ind_MonitorScanInd_Time_wMilliseconds_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* wMilliseconds )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Ind_MonitorScanInd_Time_wMilliseconds_GET( base_ptr, cur_ptr, cur_bitoff, *wMilliseconds );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_Session_BST_FrameNumber_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_Session_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, *FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_Session_BST_uSecInFrame_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_Session_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, *uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_Session_MonitorOMASession_OMAStatusInd_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, BME_OMAStatus* OMAStatusInd )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_Session_MonitorOMASession_OMAStatusInd_GET( base_ptr, cur_ptr, cur_bitoff, *OMAStatusInd );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_BST_FrameNumber_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, *FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_BST_uSecInFrame_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, *uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_operatorName_operatorName_BufferByte_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* BufferByte )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_operatorName_operatorName_BufferByte_GET( base_ptr, i0, cur_ptr, cur_bitoff, *BufferByte );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_pollingInterval_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* pollingInterval )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_pollingInterval_GET( base_ptr, cur_ptr, cur_bitoff, *pollingInterval );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Eaps_NumOfEaps_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* NumOfEaps )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Eaps_NumOfEaps_GET( base_ptr, cur_ptr, cur_bitoff, *NumOfEaps );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Eaps_EapList_usePrivacy_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* usePrivacy )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Eaps_EapList_usePrivacy_GET( base_ptr, i0, cur_ptr, cur_bitoff, *usePrivacy );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Eaps_EapList_vendorId_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* vendorId )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Eaps_EapList_vendorId_GET( base_ptr, i0, cur_ptr, cur_bitoff, *vendorId );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Eaps_EapList_vendorType_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* vendorType )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Eaps_EapList_vendorType_GET( base_ptr, i0, cur_ptr, cur_bitoff, *vendorType );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Eaps_EapList_EAPMethod_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, BM_EAPType* EAPMethod )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Eaps_EapList_EAPMethod_GET( base_ptr, i0, cur_ptr, cur_bitoff, *EAPMethod );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Eaps_EapList_EapId_EapId_BufferByte_GET( UINT8* base_ptr, UINT32 i0, UINT32 i1, UINT32 diff, UINT32 cur_bitoff, UINT8* BufferByte )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Eaps_EapList_EapId_EapId_BufferByte_GET( base_ptr, i0, i1, cur_ptr, cur_bitoff, *BufferByte );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Eaps_EapList_provisionedPseudoId_provisionedPseudoId_BufferByte_GET( UINT8* base_ptr, UINT32 i0, UINT32 i1, UINT32 diff, UINT32 cur_bitoff, UINT8* BufferByte )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Eaps_EapList_provisionedPseudoId_provisionedPseudoId_BufferByte_GET( base_ptr, i0, i1, cur_ptr, cur_bitoff, *BufferByte );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Eaps_EapList_EapPassword_EapPassword_BufferByte_GET( UINT8* base_ptr, UINT32 i0, UINT32 i1, UINT32 diff, UINT32 cur_bitoff, UINT8* BufferByte )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Eaps_EapList_EapPassword_EapPassword_BufferByte_GET( base_ptr, i0, i1, cur_ptr, cur_bitoff, *BufferByte );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Eaps_EapList_Realm_Realm_BufferByte_GET( UINT8* base_ptr, UINT32 i0, UINT32 i1, UINT32 diff, UINT32 cur_bitoff, UINT8* BufferByte )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Eaps_EapList_Realm_Realm_BufferByte_GET( base_ptr, i0, i1, cur_ptr, cur_bitoff, *BufferByte );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Eaps_EapList_encaps_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, BM_EAPType* encaps )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Eaps_EapList_encaps_GET( base_ptr, i0, cur_ptr, cur_bitoff, *encaps );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Capls_NumOfNaps_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* NumOfNaps )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Capls_NumOfNaps_GET( base_ptr, cur_ptr, cur_bitoff, *NumOfNaps );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Capls_CaplNapList_priority_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* priority )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Capls_CaplNapList_priority_GET( base_ptr, i0, cur_ptr, cur_bitoff, *priority );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Capls_CaplNapList_NapMember_napID_value_GET( UINT8* base_ptr, UINT32 i0, UINT32 i1, UINT32 diff, UINT32 cur_bitoff, UINT8* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Capls_CaplNapList_NapMember_napID_value_GET( base_ptr, i0, i1, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Capls_CaplNapList_NapMember_Reserved_1_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* Reserved_1 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Capls_CaplNapList_NapMember_Reserved_1_GET( base_ptr, i0, cur_ptr, cur_bitoff, *Reserved_1 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Rapls_NumOfRoamingPartners_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* NumOfRoamingPartners )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Rapls_NumOfRoamingPartners_GET( base_ptr, cur_ptr, cur_bitoff, *NumOfRoamingPartners );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Rapls_RaplList_vNspID_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* vNspID )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Rapls_RaplList_vNspID_GET( base_ptr, i0, cur_ptr, cur_bitoff, *vNspID );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Rapls_RaplList_priority_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* priority )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Rapls_RaplList_priority_GET( base_ptr, i0, cur_ptr, cur_bitoff, *priority );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Rapls_Any_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, BME_Any* Any )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Rapls_Any_GET( base_ptr, cur_ptr, cur_bitoff, *Any );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMAParams_BST_FrameNumber_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMAParams_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, *FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMAParams_BST_uSecInFrame_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMAParams_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, *uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMAParams_MonitorOMAParams_DeviceInfo_manufacturer_manufacturer_BufferByte_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* BufferByte )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMAParams_MonitorOMAParams_DeviceInfo_manufacturer_manufacturer_BufferByte_GET( base_ptr, i0, cur_ptr, cur_bitoff, *BufferByte );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMAParams_MonitorOMAParams_DeviceInfo_model_model_BufferByte_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* BufferByte )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMAParams_MonitorOMAParams_DeviceInfo_model_model_BufferByte_GET( base_ptr, i0, cur_ptr, cur_bitoff, *BufferByte );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMAParams_MonitorOMAParams_DeviceInfo_devID_devID_BufferByte_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* BufferByte )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMAParams_MonitorOMAParams_DeviceInfo_devID_devID_BufferByte_GET( base_ptr, i0, cur_ptr, cur_bitoff, *BufferByte );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMAParams_MonitorOMAParams_DeviceDetails_devType_devType_BufferByte_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* BufferByte )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMAParams_MonitorOMAParams_DeviceDetails_devType_devType_BufferByte_GET( base_ptr, i0, cur_ptr, cur_bitoff, *BufferByte );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMAParams_MonitorOMAParams_DeviceDetails_fwVersion_fwVersion_BufferByte_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* BufferByte )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMAParams_MonitorOMAParams_DeviceDetails_fwVersion_fwVersion_BufferByte_GET( base_ptr, i0, cur_ptr, cur_bitoff, *BufferByte );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMAParams_MonitorOMAParams_DeviceDetails_swVersion_swVersion_BufferByte_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* BufferByte )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMAParams_MonitorOMAParams_DeviceDetails_swVersion_swVersion_BufferByte_GET( base_ptr, i0, cur_ptr, cur_bitoff, *BufferByte );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMAParams_MonitorOMAParams_DeviceDetails_hwVersion_hwVersion_BufferByte_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* BufferByte )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMAParams_MonitorOMAParams_DeviceDetails_hwVersion_hwVersion_BufferByte_GET( base_ptr, i0, cur_ptr, cur_bitoff, *BufferByte );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_BST_FrameNumber_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, *FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_BST_uSecInFrame_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, *uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_RadioModule_LenOfRadioModule_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* LenOfRadioModule )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_RadioModule_LenOfRadioModule_GET( base_ptr, cur_ptr, cur_bitoff, *LenOfRadioModule );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_fwVersion_fwVersion_BufferByte_GET( UINT8* base_ptr, UINT32 i0, UINT32 i1, UINT32 diff, UINT32 cur_bitoff, UINT8* BufferByte )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_fwVersion_fwVersion_BufferByte_GET( base_ptr, i0, i1, cur_ptr, cur_bitoff, *BufferByte );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_swVersion_swVersion_BufferByte_GET( UINT8* base_ptr, UINT32 i0, UINT32 i1, UINT32 diff, UINT32 cur_bitoff, UINT8* BufferByte )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_swVersion_swVersion_BufferByte_GET( base_ptr, i0, i1, cur_ptr, cur_bitoff, *BufferByte );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_hwVersion_hwVersion_BufferByte_GET( UINT8* base_ptr, UINT32 i0, UINT32 i1, UINT32 diff, UINT32 cur_bitoff, UINT8* BufferByte )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_hwVersion_hwVersion_BufferByte_GET( base_ptr, i0, i1, cur_ptr, cur_bitoff, *BufferByte );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_manufacturer_manufacturer_BufferByte_GET( UINT8* base_ptr, UINT32 i0, UINT32 i1, UINT32 diff, UINT32 cur_bitoff, UINT8* BufferByte )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_manufacturer_manufacturer_BufferByte_GET( base_ptr, i0, i1, cur_ptr, cur_bitoff, *BufferByte );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_model_model_BufferByte_GET( UINT8* base_ptr, UINT32 i0, UINT32 i1, UINT32 diff, UINT32 cur_bitoff, UINT8* BufferByte )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_model_model_BufferByte_GET( base_ptr, i0, i1, cur_ptr, cur_bitoff, *BufferByte );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_macAddress_macAddress_BufferByte_GET( UINT8* base_ptr, UINT32 i0, UINT32 i1, UINT32 diff, UINT32 cur_bitoff, UINT8* BufferByte )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_macAddress_macAddress_BufferByte_GET( base_ptr, i0, i1, cur_ptr, cur_bitoff, *BufferByte );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_SpLock_lockStatus_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* lockStatus )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_SpLock_lockStatus_GET( base_ptr, i0, cur_ptr, cur_bitoff, *lockStatus );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_SpLock_operatorName_operatorName_BufferByte_GET( UINT8* base_ptr, UINT32 i0, UINT32 i1, UINT32 diff, UINT32 cur_bitoff, UINT8* BufferByte )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_SpLock_operatorName_operatorName_BufferByte_GET( base_ptr, i0, i1, cur_ptr, cur_bitoff, *BufferByte );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_SpLock_lockMem_lockMem_BufferByte_GET( UINT8* base_ptr, UINT32 i0, UINT32 i1, UINT32 diff, UINT32 cur_bitoff, UINT8* BufferByte )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_SpLock_lockMem_lockMem_BufferByte_GET( base_ptr, i0, i1, cur_ptr, cur_bitoff, *BufferByte );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_TerminalEquipment_devType_devType_BufferByte_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* BufferByte )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_TerminalEquipment_devType_devType_BufferByte_GET( base_ptr, i0, cur_ptr, cur_bitoff, *BufferByte );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_TerminalEquipment_devID_devID_BufferByte_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* BufferByte )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_TerminalEquipment_devID_devID_BufferByte_GET( base_ptr, i0, cur_ptr, cur_bitoff, *BufferByte );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_TerminalEquipment_staticTermEquip_fwVersion_fwVersion_BufferByte_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* BufferByte )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_TerminalEquipment_staticTermEquip_fwVersion_fwVersion_BufferByte_GET( base_ptr, i0, cur_ptr, cur_bitoff, *BufferByte );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_TerminalEquipment_staticTermEquip_swVersion_swVersion_BufferByte_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* BufferByte )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_TerminalEquipment_staticTermEquip_swVersion_swVersion_BufferByte_GET( base_ptr, i0, cur_ptr, cur_bitoff, *BufferByte );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_TerminalEquipment_staticTermEquip_hwVersion_hwVersion_BufferByte_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* BufferByte )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_TerminalEquipment_staticTermEquip_hwVersion_hwVersion_BufferByte_GET( base_ptr, i0, cur_ptr, cur_bitoff, *BufferByte );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_TerminalEquipment_staticTermEquip_manufacturer_manufacturer_BufferByte_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* BufferByte )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_TerminalEquipment_staticTermEquip_manufacturer_manufacturer_BufferByte_GET( base_ptr, i0, cur_ptr, cur_bitoff, *BufferByte );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_TerminalEquipment_staticTermEquip_model_model_BufferByte_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* BufferByte )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_TerminalEquipment_staticTermEquip_model_model_BufferByte_GET( base_ptr, i0, cur_ptr, cur_bitoff, *BufferByte );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_FUMO_Params_BST_FrameNumber_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_FUMO_Params_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, *FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_FUMO_Params_BST_uSecInFrame_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_FUMO_Params_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, *uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_FUMO_Params_MonitorOMAFumoParams_FUMO_pkgName_pkgName_BufferByte_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* BufferByte )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_FUMO_Params_MonitorOMAFumoParams_FUMO_pkgName_pkgName_BufferByte_GET( base_ptr, i0, cur_ptr, cur_bitoff, *BufferByte );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_FUMO_Params_MonitorOMAFumoParams_FUMO_pkgVersion_pkgVersion_BufferByte_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* BufferByte )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_FUMO_Params_MonitorOMAFumoParams_FUMO_pkgVersion_pkgVersion_BufferByte_GET( base_ptr, i0, cur_ptr, cur_bitoff, *BufferByte );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_FUMO_Params_MonitorOMAFumoParams_FUMO_downloadPkgURL_downloadPkgURL_BufferByte_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* BufferByte )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_FUMO_Params_MonitorOMAFumoParams_FUMO_downloadPkgURL_downloadPkgURL_BufferByte_GET( base_ptr, i0, cur_ptr, cur_bitoff, *BufferByte );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_FUMO_Params_MonitorOMAFumoParams_FUMO_downloadAndUpdatePkgURL_downloadAndUpdatePkgURL_BufferByte_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* BufferByte )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_FUMO_Params_MonitorOMAFumoParams_FUMO_downloadAndUpdatePkgURL_downloadAndUpdatePkgURL_BufferByte_GET( base_ptr, i0, cur_ptr, cur_bitoff, *BufferByte );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_FUMO_Params_MonitorOMAFumoParams_FUMO_state_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, DOWNLOAD_STATE* state )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_FUMO_Params_MonitorOMAFumoParams_FUMO_state_GET( base_ptr, cur_ptr, cur_bitoff, *state );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_FUMO_Params_MonitorOMAFumoParams_FUMO_fIsAllocated_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* fIsAllocated )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_FUMO_Params_MonitorOMAFumoParams_FUMO_fIsAllocated_GET( base_ptr, cur_ptr, cur_bitoff, *fIsAllocated );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_NAI_BST_FrameNumber_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_NAI_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, *FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_NAI_BST_uSecInFrame_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_NAI_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, *uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_NAI_MonitorNAI_NAISize_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* NAISize )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_NAI_MonitorNAI_NAISize_GET( base_ptr, cur_ptr, cur_bitoff, *NAISize );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_NAI_MonitorNAI_NAI_BufferByte_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* BufferByte )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_NAI_MonitorNAI_NAI_BufferByte_GET( base_ptr, i0, cur_ptr, cur_bitoff, *BufferByte );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_ActivationStatusChange_BST_FrameNumber_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_ActivationStatusChange_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, *FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_ActivationStatusChange_BST_uSecInFrame_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_ActivationStatusChange_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, *uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_ActivationStatusChange_MonitorActivationStatusChange_ActivationStatusInd_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* ActivationStatusInd )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_ActivationStatusChange_MonitorActivationStatusChange_ActivationStatusInd_GET( base_ptr, cur_ptr, cur_bitoff, *ActivationStatusInd );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_MCP_BST_FrameNumber_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_MCP_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, *FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_MCP_BST_uSecInFrame_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_MCP_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, *uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_MCP_MonitorMCP_LinkLossInd_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, BME_LinkLossInd* LinkLossInd )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_MCP_MonitorMCP_LinkLossInd_GET( base_ptr, cur_ptr, cur_bitoff, *LinkLossInd );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_MCP_MonitorMCP_ChannelInfoArray_NumOfChannels_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* NumOfChannels )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_MCP_MonitorMCP_ChannelInfoArray_NumOfChannels_GET( base_ptr, cur_ptr, cur_bitoff, *NumOfChannels );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_MCP_MonitorMCP_ChannelInfoArray_Channels_frequency_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* frequency )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_MCP_MonitorMCP_ChannelInfoArray_Channels_frequency_GET( base_ptr, i0, cur_ptr, cur_bitoff, *frequency );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_MCP_MonitorMCP_ChannelInfoArray_Channels_bw_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, BME_BW* bw )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_MCP_MonitorMCP_ChannelInfoArray_Channels_bw_GET( base_ptr, i0, cur_ptr, cur_bitoff, *bw );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_MCP_MonitorMCP_ChannelInfoArray_Channels_fft_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, BME_FFT* fft )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_MCP_MonitorMCP_ChannelInfoArray_Channels_fft_GET( base_ptr, i0, cur_ptr, cur_bitoff, *fft );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_MCP_MonitorMCP_ChannelInfoArray_Channels_Preambles_Preambles_value_GET( UINT8* base_ptr, UINT32 i0, UINT32 i1, UINT32 diff, UINT32 cur_bitoff, UINT8* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_MCP_MonitorMCP_ChannelInfoArray_Channels_Preambles_Preambles_value_GET( base_ptr, i0, i1, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_MCP_MonitorMCP_ChannelInfoArray_Channels_Preambles_Reserved_1_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* Reserved_1 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_MCP_MonitorMCP_ChannelInfoArray_Channels_Preambles_Reserved_1_GET( base_ptr, i0, cur_ptr, cur_bitoff, *Reserved_1 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Installation_Ind_BST_FrameNumber_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Installation_Ind_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, *FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Installation_Ind_BST_uSecInFrame_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Installation_Ind_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, *uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Installation_Ind_MonitorInstallationInd_MonitorInstallingInd_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, BME_MonitorInstallingInd* MonitorInstallingInd )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Installation_Ind_MonitorInstallationInd_MonitorInstallingInd_GET( base_ptr, cur_ptr, cur_bitoff, *MonitorInstallingInd );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_BST_FrameNumber_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, *FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_BST_uSecInFrame_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, *uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_MonitorRecentDiscoverNap_NapMember_napID_value_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_MonitorRecentDiscoverNap_NapMember_napID_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_MonitorRecentDiscoverNap_NapMember_Reserved_1_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* Reserved_1 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_MonitorRecentDiscoverNap_NapMember_Reserved_1_GET( base_ptr, cur_ptr, cur_bitoff, *Reserved_1 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_MonitorRecentDiscoverNap_ChannelInfoArray_NumOfChannels_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* NumOfChannels )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_MonitorRecentDiscoverNap_ChannelInfoArray_NumOfChannels_GET( base_ptr, cur_ptr, cur_bitoff, *NumOfChannels );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_MonitorRecentDiscoverNap_ChannelInfoArray_Channels_frequency_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* frequency )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_MonitorRecentDiscoverNap_ChannelInfoArray_Channels_frequency_GET( base_ptr, i0, cur_ptr, cur_bitoff, *frequency );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_MonitorRecentDiscoverNap_ChannelInfoArray_Channels_bw_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, BME_BW* bw )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_MonitorRecentDiscoverNap_ChannelInfoArray_Channels_bw_GET( base_ptr, i0, cur_ptr, cur_bitoff, *bw );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_MonitorRecentDiscoverNap_ChannelInfoArray_Channels_fft_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, BME_FFT* fft )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_MonitorRecentDiscoverNap_ChannelInfoArray_Channels_fft_GET( base_ptr, i0, cur_ptr, cur_bitoff, *fft );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_MonitorRecentDiscoverNap_ChannelInfoArray_Channels_Preambles_Preambles_value_GET( UINT8* base_ptr, UINT32 i0, UINT32 i1, UINT32 diff, UINT32 cur_bitoff, UINT8* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_MonitorRecentDiscoverNap_ChannelInfoArray_Channels_Preambles_Preambles_value_GET( base_ptr, i0, i1, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_MonitorRecentDiscoverNap_ChannelInfoArray_Channels_Preambles_Reserved_1_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* Reserved_1 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_MonitorRecentDiscoverNap_ChannelInfoArray_Channels_Preambles_Reserved_1_GET( base_ptr, i0, cur_ptr, cur_bitoff, *Reserved_1 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_MonitorRecentDiscoverNap_bsID_bsID_value_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_MonitorRecentDiscoverNap_bsID_bsID_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_MonitorRecentDiscoverNap_bsID_Reserved_2_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* Reserved_2 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_MonitorRecentDiscoverNap_bsID_Reserved_2_GET( base_ptr, cur_ptr, cur_bitoff, *Reserved_2 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Selected_Channel_BST_FrameNumber_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Selected_Channel_BST_FrameNumber_GET( base_ptr, cur_ptr, cur_bitoff, *FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Selected_Channel_BST_uSecInFrame_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Selected_Channel_BST_uSecInFrame_GET( base_ptr, cur_ptr, cur_bitoff, *uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Selected_Channel_MonitorSelectedChannel_ChannelInfoArray_NumOfChannels_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* NumOfChannels )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Selected_Channel_MonitorSelectedChannel_ChannelInfoArray_NumOfChannels_GET( base_ptr, cur_ptr, cur_bitoff, *NumOfChannels );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Selected_Channel_MonitorSelectedChannel_ChannelInfoArray_Channels_frequency_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32* frequency )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Selected_Channel_MonitorSelectedChannel_ChannelInfoArray_Channels_frequency_GET( base_ptr, i0, cur_ptr, cur_bitoff, *frequency );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Selected_Channel_MonitorSelectedChannel_ChannelInfoArray_Channels_bw_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, BME_BW* bw )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Selected_Channel_MonitorSelectedChannel_ChannelInfoArray_Channels_bw_GET( base_ptr, i0, cur_ptr, cur_bitoff, *bw );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Selected_Channel_MonitorSelectedChannel_ChannelInfoArray_Channels_fft_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, BME_FFT* fft )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Selected_Channel_MonitorSelectedChannel_ChannelInfoArray_Channels_fft_GET( base_ptr, i0, cur_ptr, cur_bitoff, *fft );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Selected_Channel_MonitorSelectedChannel_ChannelInfoArray_Channels_Preambles_Preambles_value_GET( UINT8* base_ptr, UINT32 i0, UINT32 i1, UINT32 diff, UINT32 cur_bitoff, UINT8* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Selected_Channel_MonitorSelectedChannel_ChannelInfoArray_Channels_Preambles_Preambles_value_GET( base_ptr, i0, i1, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Selected_Channel_MonitorSelectedChannel_ChannelInfoArray_Channels_Preambles_Reserved_1_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* Reserved_1 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Selected_Channel_MonitorSelectedChannel_ChannelInfoArray_Channels_Preambles_Reserved_1_GET( base_ptr, i0, cur_ptr, cur_bitoff, *Reserved_1 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_GET_NEXT( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_diff, UINT32* out_cur_bitoff, UINT32 err )
{
	UINT8* out_cur_ptr = base_ptr;
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, out_cur_ptr, *out_cur_bitoff, err );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_SET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_SET_TYPE( cur_ptr, cur_bitoff, type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_SET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 lenOfLen, UINT32 length )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	lenOfLen = 2;
	BM_MonitorBuffer_List_SET_LENGTH( cur_ptr, cur_bitoff, lenOfLen, length );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_BST_FrameNumber_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_BST_uSecInFrame_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_PowerPerToneCur_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, INT16 PowerPerToneCur )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_PowerPerToneCur_SET( base_ptr, cur_ptr, cur_bitoff, PowerPerToneCur );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_PowerPerToneAvg_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, INT16 PowerPerToneAvg )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_PowerPerToneAvg_SET( base_ptr, cur_ptr, cur_bitoff, PowerPerToneAvg );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_PathLoss_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 PathLoss )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_PathLoss_SET( base_ptr, cur_ptr, cur_bitoff, PathLoss );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_Headroom_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 Headroom )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_Headroom_SET( base_ptr, cur_ptr, cur_bitoff, Headroom );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_Reserved_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 Reserved )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_Reserved_SET( base_ptr, cur_ptr, cur_bitoff, Reserved );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_powerControlMode_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 powerControlMode )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_powerControlMode_SET( base_ptr, cur_ptr, cur_bitoff, powerControlMode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_isTx_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 isTx )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_isTx_SET( base_ptr, cur_ptr, cur_bitoff, isTx );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_CurrentFrameTxPower_Total_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, INT16 Total )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_CurrentFrameTxPower_Total_SET( base_ptr, cur_ptr, cur_bitoff, Total );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_CurrentFrameTxPower_NumOfSubchannels_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 NumOfSubchannels )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_CurrentFrameTxPower_NumOfSubchannels_SET( base_ptr, cur_ptr, cur_bitoff, NumOfSubchannels );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_CurrentFrameTxPower_AllocationType_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 AllocationType )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_CurrentFrameTxPower_AllocationType_SET( base_ptr, cur_ptr, cur_bitoff, AllocationType );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ExtremePowerValues_MaxPower_Total_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, INT16 Total )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ExtremePowerValues_MaxPower_Total_SET( base_ptr, cur_ptr, cur_bitoff, Total );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ExtremePowerValues_MaxPower_NumOfSubchannels_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 NumOfSubchannels )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ExtremePowerValues_MaxPower_NumOfSubchannels_SET( base_ptr, cur_ptr, cur_bitoff, NumOfSubchannels );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ExtremePowerValues_MaxPower_AllocationType_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 AllocationType )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ExtremePowerValues_MaxPower_AllocationType_SET( base_ptr, cur_ptr, cur_bitoff, AllocationType );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ExtremePowerValues_MinPower_Total_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, INT16 Total )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ExtremePowerValues_MinPower_Total_SET( base_ptr, cur_ptr, cur_bitoff, Total );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ExtremePowerValues_MinPower_NumOfSubchannels_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 NumOfSubchannels )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ExtremePowerValues_MinPower_NumOfSubchannels_SET( base_ptr, cur_ptr, cur_bitoff, NumOfSubchannels );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ExtremePowerValues_MinPower_AllocationType_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 AllocationType )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ExtremePowerValues_MinPower_AllocationType_SET( base_ptr, cur_ptr, cur_bitoff, AllocationType );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_offsetBSperSS_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, INT16 offsetBSperSS )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_offsetBSperSS_SET( base_ptr, cur_ptr, cur_bitoff, offsetBSperSS );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_offsetSSperSS_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, INT16 offsetSSperSS )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_offsetSSperSS_SET( base_ptr, cur_ptr, cur_bitoff, offsetSSperSS );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_cqiAckPeriodicRangingNI_valid_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 valid )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_cqiAckPeriodicRangingNI_valid_SET( base_ptr, cur_ptr, cur_bitoff, valid );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_cqiAckPeriodicRangingNI_level_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 level )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_cqiAckPeriodicRangingNI_level_SET( base_ptr, cur_ptr, cur_bitoff, level );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_puscNI_valid_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 valid )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_puscNI_valid_SET( base_ptr, cur_ptr, cur_bitoff, valid );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_puscNI_level_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 level )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_puscNI_level_SET( base_ptr, cur_ptr, cur_bitoff, level );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_amcNI_valid_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 valid )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_amcNI_valid_SET( base_ptr, cur_ptr, cur_bitoff, valid );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_amcNI_level_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 level )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_amcNI_level_SET( base_ptr, cur_ptr, cur_bitoff, level );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_periodicRangingNI_valid_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 valid )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_periodicRangingNI_valid_SET( base_ptr, cur_ptr, cur_bitoff, valid );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_periodicRangingNI_level_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 level )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_periodicRangingNI_level_SET( base_ptr, cur_ptr, cur_bitoff, level );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_soundingNI_valid_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 valid )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_soundingNI_valid_SET( base_ptr, cur_ptr, cur_bitoff, valid );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_soundingNI_level_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 level )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_soundingNI_level_SET( base_ptr, cur_ptr, cur_bitoff, level );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_mimoNI_valid_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 valid )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_mimoNI_valid_SET( base_ptr, cur_ptr, cur_bitoff, valid );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_mimoNI_level_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 level )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_ulNoiseAndInterferenceLevel_mimoNI_level_SET( base_ptr, cur_ptr, cur_bitoff, level );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_LackOfHeadroomCounter_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 LackOfHeadroomCounter )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpc_dmTpc_LackOfHeadroomCounter_SET( base_ptr, cur_ptr, cur_bitoff, LackOfHeadroomCounter );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_BST_FrameNumber_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_BST_uSecInFrame_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_MapsStatistics_FchRecievedOK_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 FchRecievedOK )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_MapsStatistics_FchRecievedOK_SET( base_ptr, cur_ptr, cur_bitoff, FchRecievedOK );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_MapsStatistics_FchFailures_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 FchFailures )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_MapsStatistics_FchFailures_SET( base_ptr, cur_ptr, cur_bitoff, FchFailures );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_MapsStatistics_NormalDlMapRecievedOK_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 NormalDlMapRecievedOK )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_MapsStatistics_NormalDlMapRecievedOK_SET( base_ptr, cur_ptr, cur_bitoff, NormalDlMapRecievedOK );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_MapsStatistics_NormalDlMapHcsError_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 NormalDlMapHcsError )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_MapsStatistics_NormalDlMapHcsError_SET( base_ptr, cur_ptr, cur_bitoff, NormalDlMapHcsError );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_MapsStatistics_NormalDlMapCrcError_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 NormalDlMapCrcError )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_MapsStatistics_NormalDlMapCrcError_SET( base_ptr, cur_ptr, cur_bitoff, NormalDlMapCrcError );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_MapsStatistics_NormalUlMapRecievedOK_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 NormalUlMapRecievedOK )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_MapsStatistics_NormalUlMapRecievedOK_SET( base_ptr, cur_ptr, cur_bitoff, NormalUlMapRecievedOK );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_MapsStatistics_NormalUlMapHcsError_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 NormalUlMapHcsError )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_MapsStatistics_NormalUlMapHcsError_SET( base_ptr, cur_ptr, cur_bitoff, NormalUlMapHcsError );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_MapsStatistics_NormalUlMapCrcError_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 NormalUlMapCrcError )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_MapsStatistics_NormalUlMapCrcError_SET( base_ptr, cur_ptr, cur_bitoff, NormalUlMapCrcError );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_MapsStatistics_CompressedMapRecievedOK_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 CompressedMapRecievedOK )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_MapsStatistics_CompressedMapRecievedOK_SET( base_ptr, cur_ptr, cur_bitoff, CompressedMapRecievedOK );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_MapsStatistics_CompressedMapCrcError_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 CompressedMapCrcError )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_MapsStatistics_CompressedMapCrcError_SET( base_ptr, cur_ptr, cur_bitoff, CompressedMapCrcError );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_PreamblePCinr_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, INT PreamblePCinr )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_PreamblePCinr_SET( base_ptr, cur_ptr, cur_bitoff, PreamblePCinr );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_PreamblePCinrAnt0_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, INT PreamblePCinrAnt0 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_PreamblePCinrAnt0_SET( base_ptr, cur_ptr, cur_bitoff, PreamblePCinrAnt0 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_PreamblePCinrAnt1_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, INT PreamblePCinrAnt1 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_PreamblePCinrAnt1_SET( base_ptr, cur_ptr, cur_bitoff, PreamblePCinrAnt1 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_PreamblePCinrStd_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, INT PreamblePCinrStd )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_PreamblePCinrStd_SET( base_ptr, cur_ptr, cur_bitoff, PreamblePCinrStd );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_Rssi_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, INT Rssi )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_Rssi_SET( base_ptr, cur_ptr, cur_bitoff, Rssi );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_RssiStd_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, INT RssiStd )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_RssiStd_SET( base_ptr, cur_ptr, cur_bitoff, RssiStd );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_MimoStbcPCinr_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, INT MimoStbcPCinr )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_MimoStbcPCinr_SET( base_ptr, cur_ptr, cur_bitoff, MimoStbcPCinr );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_MimoStbcPCinrStd_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, INT MimoStbcPCinrStd )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_MimoStbcPCinrStd_SET( base_ptr, cur_ptr, cur_bitoff, MimoStbcPCinrStd );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_MimoSmPCinr_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, INT MimoSmPCinr )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_MimoSmPCinr_SET( base_ptr, cur_ptr, cur_bitoff, MimoSmPCinr );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_MimoSmPCinrStd_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, INT MimoSmPCinrStd )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_MimoSmPCinrStd_SET( base_ptr, cur_ptr, cur_bitoff, MimoSmPCinrStd );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_MimoStbcECinr_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, INT MimoStbcECinr )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_MimoStbcECinr_SET( base_ptr, cur_ptr, cur_bitoff, MimoStbcECinr );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_MimoSmECinr_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, INT MimoSmECinr )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_MimoSmECinr_SET( base_ptr, cur_ptr, cur_bitoff, MimoSmECinr );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_RxAntModeAutoDetect_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, eRF_RX_ANT_MODE RxAntModeAutoDetect )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_RxAntModeAutoDetect_SET( base_ptr, cur_ptr, cur_bitoff, RxAntModeAutoDetect );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_Reserved8_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 Reserved8 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_Reserved8_SET( base_ptr, cur_ptr, cur_bitoff, Reserved8 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_Reserved16_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 Reserved16 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_l1Measurements_Reserved16_SET( base_ptr, cur_ptr, cur_bitoff, Reserved16 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_cqichCount_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 cqichCount )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_cqichCount_SET( base_ptr, cur_ptr, cur_bitoff, cqichCount );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_TemperatureInCelsius_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, INT16 TemperatureInCelsius )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_TemperatureInCelsius_SET( base_ptr, cur_ptr, cur_bitoff, TemperatureInCelsius );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_RxAntMode_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, eRF_RX_ANT_MODE RxAntMode )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_RxAntMode_SET( base_ptr, cur_ptr, cur_bitoff, RxAntMode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_Reserved_1_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 Reserved_1 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsPerformance_dmPhyPerformance_Reserved_1_SET( base_ptr, cur_ptr, cur_bitoff, Reserved_1 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsConfiguration_BST_FrameNumber_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsConfiguration_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsConfiguration_BST_uSecInFrame_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsConfiguration_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsConfiguration_dmPhyConfiguration_FrequencyOffsetInHz_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, INT FrequencyOffsetInHz )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsConfiguration_dmPhyConfiguration_FrequencyOffsetInHz_SET( base_ptr, cur_ptr, cur_bitoff, FrequencyOffsetInHz );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsConfiguration_dmPhyConfiguration_CenterFrequencyInKHz_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 CenterFrequencyInKHz )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsConfiguration_dmPhyConfiguration_CenterFrequencyInKHz_SET( base_ptr, cur_ptr, cur_bitoff, CenterFrequencyInKHz );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsConfiguration_dmPhyConfiguration_transitionGaps_TTG_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 TTG )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsConfiguration_dmPhyConfiguration_transitionGaps_TTG_SET( base_ptr, cur_ptr, cur_bitoff, TTG );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsConfiguration_dmPhyConfiguration_transitionGaps_RTG_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 RTG )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsConfiguration_dmPhyConfiguration_transitionGaps_RTG_SET( base_ptr, cur_ptr, cur_bitoff, RTG );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsConfiguration_dmPhyConfiguration_RecommendedMIMOMode_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 RecommendedMIMOMode )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsConfiguration_dmPhyConfiguration_RecommendedMIMOMode_SET( base_ptr, cur_ptr, cur_bitoff, RecommendedMIMOMode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBASIC_STATUS_BST_FrameNumber_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBASIC_STATUS_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBASIC_STATUS_BST_uSecInFrame_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBASIC_STATUS_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBASIC_STATUS_FWMonitorGroupBasicStatus_FCH_byte0_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 byte0 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBASIC_STATUS_FWMonitorGroupBasicStatus_FCH_byte0_SET( base_ptr, cur_ptr, cur_bitoff, byte0 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBASIC_STATUS_FWMonitorGroupBasicStatus_FCH_byte1_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 byte1 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBASIC_STATUS_FWMonitorGroupBasicStatus_FCH_byte1_SET( base_ptr, cur_ptr, cur_bitoff, byte1 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBASIC_STATUS_FWMonitorGroupBasicStatus_FCH_byte2_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 byte2 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBASIC_STATUS_FWMonitorGroupBasicStatus_FCH_byte2_SET( base_ptr, cur_ptr, cur_bitoff, byte2 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBASIC_STATUS_FWMonitorGroupBasicStatus_FCH_validity_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, MonitorValidity validity )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBASIC_STATUS_FWMonitorGroupBasicStatus_FCH_validity_SET( base_ptr, cur_ptr, cur_bitoff, validity );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBASIC_STATUS_FWMonitorGroupBasicStatus_frameRatio_DlSize_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 DlSize )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBASIC_STATUS_FWMonitorGroupBasicStatus_frameRatio_DlSize_SET( base_ptr, cur_ptr, cur_bitoff, DlSize );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBASIC_STATUS_FWMonitorGroupBasicStatus_frameRatio_UlSize_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 UlSize )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBASIC_STATUS_FWMonitorGroupBasicStatus_frameRatio_UlSize_SET( base_ptr, cur_ptr, cur_bitoff, UlSize );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBURST_STATUS_BST_FrameNumber_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBURST_STATUS_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBURST_STATUS_BST_uSecInFrame_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBURST_STATUS_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBURST_STATUS_FWMonitorGroupBurstStatus_TotalDLPduCRCCount_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 TotalDLPduCRCCount )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBURST_STATUS_FWMonitorGroupBurstStatus_TotalDLPduCRCCount_SET( base_ptr, cur_ptr, cur_bitoff, TotalDLPduCRCCount );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBURST_STATUS_FWMonitorGroupBurstStatus_TotalDLPduCount_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 TotalDLPduCount )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBURST_STATUS_FWMonitorGroupBurstStatus_TotalDLPduCount_SET( base_ptr, cur_ptr, cur_bitoff, TotalDLPduCount );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBURST_STATUS_FWMonitorGroupBurstStatus_UL_PDU_Size_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 UL_PDU_Size )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBURST_STATUS_FWMonitorGroupBurstStatus_UL_PDU_Size_SET( base_ptr, cur_ptr, cur_bitoff, UL_PDU_Size );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBURST_STATUS_FWMonitorGroupBurstStatus_TotalULPDUSize_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 TotalULPDUSize )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBURST_STATUS_FWMonitorGroupBurstStatus_TotalULPDUSize_SET( base_ptr, cur_ptr, cur_bitoff, TotalULPDUSize );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBURST_STATUS_FWMonitorGroupBurstStatus_TotalUlPduCount_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 TotalUlPduCount )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBURST_STATUS_FWMonitorGroupBurstStatus_TotalUlPduCount_SET( base_ptr, cur_ptr, cur_bitoff, TotalUlPduCount );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBURST_STATUS_FWMonitorGroupBurstStatus_UL_SDU_Size_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 UL_SDU_Size )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBURST_STATUS_FWMonitorGroupBurstStatus_UL_SDU_Size_SET( base_ptr, cur_ptr, cur_bitoff, UL_SDU_Size );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBURST_STATUS_FWMonitorGroupBurstStatus_TotalULSDUSize_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 TotalULSDUSize )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBURST_STATUS_FWMonitorGroupBurstStatus_TotalULSDUSize_SET( base_ptr, cur_ptr, cur_bitoff, TotalULSDUSize );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBURST_STATUS_FWMonitorGroupBurstStatus_TotalUlSduCount_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 TotalUlSduCount )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupBURST_STATUS_FWMonitorGroupBurstStatus_TotalUlSduCount_SET( base_ptr, cur_ptr, cur_bitoff, TotalUlSduCount );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupPER_CIN_STATUS_BST_FrameNumber_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupPER_CIN_STATUS_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupPER_CIN_STATUS_BST_uSecInFrame_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupPER_CIN_STATUS_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupPER_CIN_STATUS_Per_CIN_MonitorInfo_L2_perCIN_xDUStatus_PDUInfo_numberOfTxedPDUs_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 numberOfTxedPDUs )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupPER_CIN_STATUS_Per_CIN_MonitorInfo_L2_perCIN_xDUStatus_PDUInfo_numberOfTxedPDUs_SET( base_ptr, i0, cur_ptr, cur_bitoff, numberOfTxedPDUs );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupPER_CIN_STATUS_Per_CIN_MonitorInfo_L2_perCIN_xDUStatus_PDUInfo_totalBytes_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 totalBytes )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupPER_CIN_STATUS_Per_CIN_MonitorInfo_L2_perCIN_xDUStatus_PDUInfo_totalBytes_SET( base_ptr, i0, cur_ptr, cur_bitoff, totalBytes );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupPER_CIN_STATUS_Per_CIN_MonitorInfo_L2_perCIN_xDUStatus_SDUInfo_numberOfAgedSDUs_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 numberOfAgedSDUs )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupPER_CIN_STATUS_Per_CIN_MonitorInfo_L2_perCIN_xDUStatus_SDUInfo_numberOfAgedSDUs_SET( base_ptr, i0, cur_ptr, cur_bitoff, numberOfAgedSDUs );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupPER_CIN_STATUS_Per_CIN_MonitorInfo_L2_perCIN_xDUStatus_SDUInfo_totalBytes_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 totalBytes )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupPER_CIN_STATUS_Per_CIN_MonitorInfo_L2_perCIN_xDUStatus_SDUInfo_totalBytes_SET( base_ptr, i0, cur_ptr, cur_bitoff, totalBytes );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupPER_CIN_STATUS_Per_CIN_MonitorInfo_L2_perCIN_BWRStatus_AggregatedBWRInfo_numberOfBWRs_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 numberOfBWRs )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupPER_CIN_STATUS_Per_CIN_MonitorInfo_L2_perCIN_BWRStatus_AggregatedBWRInfo_numberOfBWRs_SET( base_ptr, i0, cur_ptr, cur_bitoff, numberOfBWRs );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupPER_CIN_STATUS_Per_CIN_MonitorInfo_L2_perCIN_BWRStatus_AggregatedBWRInfo_totalBytes_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 totalBytes )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupPER_CIN_STATUS_Per_CIN_MonitorInfo_L2_perCIN_BWRStatus_AggregatedBWRInfo_totalBytes_SET( base_ptr, i0, cur_ptr, cur_bitoff, totalBytes );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupPER_CIN_STATUS_Per_CIN_MonitorInfo_L2_perCIN_BWRStatus_IncrementalBWRInfo_numberOfBWRs_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 numberOfBWRs )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupPER_CIN_STATUS_Per_CIN_MonitorInfo_L2_perCIN_BWRStatus_IncrementalBWRInfo_numberOfBWRs_SET( base_ptr, i0, cur_ptr, cur_bitoff, numberOfBWRs );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupPER_CIN_STATUS_Per_CIN_MonitorInfo_L2_perCIN_BWRStatus_IncrementalBWRInfo_totalBytes_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 totalBytes )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupPER_CIN_STATUS_Per_CIN_MonitorInfo_L2_perCIN_BWRStatus_IncrementalBWRInfo_totalBytes_SET( base_ptr, i0, cur_ptr, cur_bitoff, totalBytes );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupPER_CIN_STATUS_Per_CIN_MonitorInfo_L2_perCIN_VQInfo_currentVQInfo_totalBytesPendingInQ_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 totalBytesPendingInQ )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupPER_CIN_STATUS_Per_CIN_MonitorInfo_L2_perCIN_VQInfo_currentVQInfo_totalBytesPendingInQ_SET( base_ptr, i0, cur_ptr, cur_bitoff, totalBytesPendingInQ );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupSF_AND_QOS_FLOW_MNGMT_BST_FrameNumber_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupSF_AND_QOS_FLOW_MNGMT_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupSF_AND_QOS_FLOW_MNGMT_BST_uSecInFrame_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupSF_AND_QOS_FLOW_MNGMT_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupSF_AND_QOS_FLOW_MNGMT_L2_MON_TYPE_SF_AND_QOS_FLOW_MNGMT_HARQBurst_TotalGrantsAmountInBytes_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 TotalGrantsAmountInBytes )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupSF_AND_QOS_FLOW_MNGMT_L2_MON_TYPE_SF_AND_QOS_FLOW_MNGMT_HARQBurst_TotalGrantsAmountInBytes_SET( base_ptr, cur_ptr, cur_bitoff, TotalGrantsAmountInBytes );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupSF_AND_QOS_FLOW_MNGMT_L2_MON_TYPE_SF_AND_QOS_FLOW_MNGMT_NonHARQBurst_TotalGrantsAmountInBytes_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 TotalGrantsAmountInBytes )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupSF_AND_QOS_FLOW_MNGMT_L2_MON_TYPE_SF_AND_QOS_FLOW_MNGMT_NonHARQBurst_TotalGrantsAmountInBytes_SET( base_ptr, cur_ptr, cur_bitoff, TotalGrantsAmountInBytes );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupSF_AND_QOS_FLOW_MNGMT_L2_MON_TYPE_SF_AND_QOS_FLOW_MNGMT_UIUC14Burst_TotalGrantsAmountInBytes_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 TotalGrantsAmountInBytes )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupSF_AND_QOS_FLOW_MNGMT_L2_MON_TYPE_SF_AND_QOS_FLOW_MNGMT_UIUC14Burst_TotalGrantsAmountInBytes_SET( base_ptr, cur_ptr, cur_bitoff, TotalGrantsAmountInBytes );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL2_LAM_Events_BST_FrameNumber_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL2_LAM_Events_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL2_LAM_Events_BST_uSecInFrame_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL2_LAM_Events_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL2_LAM_Events_L2_LAM_Events_MonitorInfo_CQIParams_FrameNumber_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL2_LAM_Events_L2_LAM_Events_MonitorInfo_CQIParams_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL2_LAM_Events_L2_LAM_Events_MonitorInfo_CQIParams_CQI_Measurement_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, INT CQI_Measurement )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL2_LAM_Events_L2_LAM_Events_MonitorInfo_CQIParams_CQI_Measurement_SET( base_ptr, cur_ptr, cur_bitoff, CQI_Measurement );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL2_LAM_Events_L2_LAM_Events_MonitorInfo_CQIParams_ChannelID_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 ChannelID )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL2_LAM_Events_L2_LAM_Events_MonitorInfo_CQIParams_ChannelID_SET( base_ptr, cur_ptr, cur_bitoff, ChannelID );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL2_LAM_Events_L2_LAM_Events_MonitorInfo_CQIParams_IsMIMOReportFlag_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 IsMIMOReportFlag )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL2_LAM_Events_L2_LAM_Events_MonitorInfo_CQIParams_IsMIMOReportFlag_SET( base_ptr, cur_ptr, cur_bitoff, IsMIMOReportFlag );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpcEvents_BST_FrameNumber_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpcEvents_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpcEvents_BST_uSecInFrame_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpcEvents_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpcEvents_dmTpcEvents_TPCModeChange_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 TPCModeChange )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_DiagnosticsTpcEvents_dmTpcEvents_TPCModeChange_SET( base_ptr, cur_ptr, cur_bitoff, TPCModeChange );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_NBS_PSCAN_Results_BST_FrameNumber_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_NBS_PSCAN_Results_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_NBS_PSCAN_Results_BST_uSecInFrame_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_NBS_PSCAN_Results_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_NBS_PSCAN_Results_dmL1NBSPSCANResults_numOfReportedBs_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 numOfReportedBs )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_NBS_PSCAN_Results_dmL1NBSPSCANResults_numOfReportedBs_SET( base_ptr, cur_ptr, cur_bitoff, numOfReportedBs );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_NBS_PSCAN_Results_dmL1NBSPSCANResults_NBSPSCANResult_PHYLinkID_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 PHYLinkID )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_NBS_PSCAN_Results_dmL1NBSPSCANResults_NBSPSCANResult_PHYLinkID_SET( base_ptr, i0, cur_ptr, cur_bitoff, PHYLinkID );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_NBS_PSCAN_Results_dmL1NBSPSCANResults_NBSPSCANResult_NeighbourBSPreambleCINRMeanReuse1_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, INT NeighbourBSPreambleCINRMeanReuse1 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_NBS_PSCAN_Results_dmL1NBSPSCANResults_NBSPSCANResult_NeighbourBSPreambleCINRMeanReuse1_SET( base_ptr, i0, cur_ptr, cur_bitoff, NeighbourBSPreambleCINRMeanReuse1 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_NBS_PSCAN_Results_dmL1NBSPSCANResults_NBSPSCANResult_NeighbourBSPreambleCINRMeanReuse3_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, INT NeighbourBSPreambleCINRMeanReuse3 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_NBS_PSCAN_Results_dmL1NBSPSCANResults_NBSPSCANResult_NeighbourBSPreambleCINRMeanReuse3_SET( base_ptr, i0, cur_ptr, cur_bitoff, NeighbourBSPreambleCINRMeanReuse3 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_NBS_PSCAN_Results_dmL1NBSPSCANResults_NBSPSCANResult_NeighbourBSPreambleRSSIMean_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, INT NeighbourBSPreambleRSSIMean )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_NBS_PSCAN_Results_dmL1NBSPSCANResults_NBSPSCANResult_NeighbourBSPreambleRSSIMean_SET( base_ptr, i0, cur_ptr, cur_bitoff, NeighbourBSPreambleRSSIMean );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_NBS_PSCAN_Results_dmL1NBSPSCANResults_NBSPSCANResult_NeighbourBSTimeOffset_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, INT NeighbourBSTimeOffset )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_NBS_PSCAN_Results_dmL1NBSPSCANResults_NBSPSCANResult_NeighbourBSTimeOffset_SET( base_ptr, i0, cur_ptr, cur_bitoff, NeighbourBSTimeOffset );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_NBS_PSCAN_Results_dmL1NBSPSCANResults_NBSPSCANResult_IntraInterFAFlag_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 IntraInterFAFlag )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_NBS_PSCAN_Results_dmL1NBSPSCANResults_NBSPSCANResult_IntraInterFAFlag_SET( base_ptr, i0, cur_ptr, cur_bitoff, IntraInterFAFlag );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_NBS_PSCAN_Results_dmL1NBSPSCANResults_NBSPSCANResult_MeasurementsValidityFlag_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 MeasurementsValidityFlag )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_L3MonitorGroupL1_NBS_PSCAN_Results_dmL1NBSPSCANResults_NBSPSCANResult_MeasurementsValidityFlag_SET( base_ptr, i0, cur_ptr, cur_bitoff, MeasurementsValidityFlag );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_BST_FrameNumber_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_BST_uSecInFrame_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_HarqPerfComp_NacksSent_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 NacksSent )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_HarqPerfComp_NacksSent_SET( base_ptr, cur_ptr, cur_bitoff, NacksSent );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_HarqPerfComp_AcksSent_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 AcksSent )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_HarqPerfComp_AcksSent_SET( base_ptr, cur_ptr, cur_bitoff, AcksSent );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_HarqPerfComp_DuplicatesRx_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 DuplicatesRx )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_HarqPerfComp_DuplicatesRx_SET( base_ptr, cur_ptr, cur_bitoff, DuplicatesRx );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_HarqPerfComp_BurstsTx_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 BurstsTx )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_HarqPerfComp_BurstsTx_SET( base_ptr, cur_ptr, cur_bitoff, BurstsTx );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_HarqPerfComp_BurstsRx_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 BurstsRx )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_HarqPerfComp_BurstsRx_SET( base_ptr, cur_ptr, cur_bitoff, BurstsRx );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_HarqPerfComp_Reserved_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 Reserved )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_HarqPerfComp_Reserved_SET( base_ptr, cur_ptr, cur_bitoff, Reserved );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_HarqPerfComp_RetransUL_Array_Retrans_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT16 Retrans )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_HarqPerfComp_RetransUL_Array_Retrans_SET( base_ptr, i0, cur_ptr, cur_bitoff, Retrans );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_HarqPerfComp_RetransDL_Array_Retrans_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT16 Retrans )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_HarqPerfComp_RetransDL_Array_Retrans_SET( base_ptr, i0, cur_ptr, cur_bitoff, Retrans );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_HarqPerfComp_DropHarqBurstCount_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 DropHarqBurstCount )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_HarqPerfComp_DropHarqBurstCount_SET( base_ptr, cur_ptr, cur_bitoff, DropHarqBurstCount );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_HarqPerfComp_AgingArrayUL_Retrans_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT16 Retrans )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_HarqPerfComp_AgingArrayUL_Retrans_SET( base_ptr, i0, cur_ptr, cur_bitoff, Retrans );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_HarqPerfComp_AgingArrayDL_Retrans_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT16 Retrans )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloHarqPerfGroup_HarqPerfComp_AgingArrayDL_Retrans_SET( base_ptr, i0, cur_ptr, cur_bitoff, Retrans );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BST_FrameNumber_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BST_uSecInFrame_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_RxBurstsPerMcs_Array_Bursts_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT16 Bursts )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_RxBurstsPerMcs_Array_Bursts_SET( base_ptr, i0, cur_ptr, cur_bitoff, Bursts );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_TxBurstsPerMcs_Array_Bursts_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT16 Bursts )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_TxBurstsPerMcs_Array_Bursts_SET( base_ptr, i0, cur_ptr, cur_bitoff, Bursts );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_UL_BurstDataZone_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 UL_BurstDataZone )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_UL_BurstDataZone_SET( base_ptr, cur_ptr, cur_bitoff, UL_BurstDataZone );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_DL_BurstDataFecScheme_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 DL_BurstDataFecScheme )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_DL_BurstDataFecScheme_SET( base_ptr, cur_ptr, cur_bitoff, DL_BurstDataFecScheme );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_UL_BurstDataFecScheme_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 UL_BurstDataFecScheme )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_UL_BurstDataFecScheme_SET( base_ptr, cur_ptr, cur_bitoff, UL_BurstDataFecScheme );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_DL_BurstDataCid_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 DL_BurstDataCid )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_DL_BurstDataCid_SET( base_ptr, cur_ptr, cur_bitoff, DL_BurstDataCid );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_DL_BurstDataDiuc_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 DL_BurstDataDiuc )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_DL_BurstDataDiuc_SET( base_ptr, cur_ptr, cur_bitoff, DL_BurstDataDiuc );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_UL_BurstDataUiuc_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 UL_BurstDataUiuc )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_UL_BurstDataUiuc_SET( base_ptr, cur_ptr, cur_bitoff, UL_BurstDataUiuc );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_DL_BurstDataRepetition_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 DL_BurstDataRepetition )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_DL_BurstDataRepetition_SET( base_ptr, cur_ptr, cur_bitoff, DL_BurstDataRepetition );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_UL_BurstDataRepetition_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 UL_BurstDataRepetition )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_UL_BurstDataRepetition_SET( base_ptr, cur_ptr, cur_bitoff, UL_BurstDataRepetition );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_UL_TotalFec_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 UL_TotalFec )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_UL_TotalFec_SET( base_ptr, cur_ptr, cur_bitoff, UL_TotalFec );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_DL_TotalFec_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 DL_TotalFec )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_DL_TotalFec_SET( base_ptr, cur_ptr, cur_bitoff, DL_TotalFec );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_FecMode_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 FecMode )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_FecMode_SET( base_ptr, cur_ptr, cur_bitoff, FecMode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_FecTypeID_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 FecTypeID )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_FecTypeID_SET( base_ptr, cur_ptr, cur_bitoff, FecTypeID );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_FecNumberOfError_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 FecNumberOfError )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloBurstGroup_BurstStatComp_FecNumberOfError_SET( base_ptr, cur_ptr, cur_bitoff, FecNumberOfError );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaTxAttrib_BST_FrameNumber_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaTxAttrib_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaTxAttrib_BST_uSecInFrame_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaTxAttrib_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaTxAttrib_CdmaTxAttribComp_FrameContainsCdmaTx_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 FrameContainsCdmaTx )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaTxAttrib_CdmaTxAttribComp_FrameContainsCdmaTx_SET( base_ptr, cur_ptr, cur_bitoff, FrameContainsCdmaTx );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaTxAttrib_CdmaTxAttribComp_FrameRefLow_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 FrameRefLow )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaTxAttrib_CdmaTxAttribComp_FrameRefLow_SET( base_ptr, cur_ptr, cur_bitoff, FrameRefLow );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaTxAttrib_CdmaTxAttribComp_SymbolsRef_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 SymbolsRef )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaTxAttrib_CdmaTxAttribComp_SymbolsRef_SET( base_ptr, cur_ptr, cur_bitoff, SymbolsRef );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaTxAttrib_CdmaTxAttribComp_SubChRef_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 SubChRef )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaTxAttrib_CdmaTxAttribComp_SubChRef_SET( base_ptr, cur_ptr, cur_bitoff, SubChRef );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaTxAttrib_CdmaTxAttribComp_RangingCode_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 RangingCode )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaTxAttrib_CdmaTxAttribComp_RangingCode_SET( base_ptr, cur_ptr, cur_bitoff, RangingCode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaTxAttrib_CdmaTxAttribComp_Reserved_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 Reserved )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaTxAttrib_CdmaTxAttribComp_Reserved_SET( base_ptr, cur_ptr, cur_bitoff, Reserved );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_BST_FrameNumber_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_BST_uSecInFrame_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_FWL2MonitorGroupRangingTraceEvent_DilloCdmaAttributes_xOffset_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 xOffset )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_FWL2MonitorGroupRangingTraceEvent_DilloCdmaAttributes_xOffset_SET( base_ptr, cur_ptr, cur_bitoff, xOffset );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_FWL2MonitorGroupRangingTraceEvent_DilloCdmaAttributes_yOffset_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 yOffset )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_FWL2MonitorGroupRangingTraceEvent_DilloCdmaAttributes_yOffset_SET( base_ptr, cur_ptr, cur_bitoff, yOffset );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_FWL2MonitorGroupRangingTraceEvent_DilloCdmaAttributes_codeNumber_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 codeNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_FWL2MonitorGroupRangingTraceEvent_DilloCdmaAttributes_codeNumber_SET( base_ptr, cur_ptr, cur_bitoff, codeNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_FWL2MonitorGroupRangingTraceEvent_DilloCdmaAttributes_frameNumber_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 frameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_FWL2MonitorGroupRangingTraceEvent_DilloCdmaAttributes_frameNumber_SET( base_ptr, cur_ptr, cur_bitoff, frameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_FWL2MonitorGroupRangingTraceEvent_RangingType_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, ERangingMode RangingType )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_FWL2MonitorGroupRangingTraceEvent_RangingType_SET( base_ptr, cur_ptr, cur_bitoff, RangingType );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_FWL2MonitorGroupRangingTraceEvent_TimingAdjustment_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, INT TimingAdjustment )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_FWL2MonitorGroupRangingTraceEvent_TimingAdjustment_SET( base_ptr, cur_ptr, cur_bitoff, TimingAdjustment );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_FWL2MonitorGroupRangingTraceEvent_PowerLevelAdjust_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, INT PowerLevelAdjust )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_FWL2MonitorGroupRangingTraceEvent_PowerLevelAdjust_SET( base_ptr, cur_ptr, cur_bitoff, PowerLevelAdjust );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_FWL2MonitorGroupRangingTraceEvent_InvitingRetries_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 InvitingRetries )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_FWL2MonitorGroupRangingTraceEvent_InvitingRetries_SET( base_ptr, cur_ptr, cur_bitoff, InvitingRetries );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_FWL2MonitorGroupRangingTraceEvent_ContentionRetries_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 ContentionRetries )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_FWL2MonitorGroupRangingTraceEvent_ContentionRetries_SET( base_ptr, cur_ptr, cur_bitoff, ContentionRetries );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_FWL2MonitorGroupRangingTraceEvent_rangingStatus_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, EDMRangingRspStatus rangingStatus )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEVENT_L2_RNGING_PARAMETERS_FWL2MonitorGroupRangingTraceEvent_rangingStatus_SET( base_ptr, cur_ptr, cur_bitoff, rangingStatus );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaBwr_BST_FrameNumber_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaBwr_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaBwr_BST_uSecInFrame_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaBwr_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaBwr_FWCdmaBwrEvent_TotalNumberOfCdmaBwrInit_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 TotalNumberOfCdmaBwrInit )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaBwr_FWCdmaBwrEvent_TotalNumberOfCdmaBwrInit_SET( base_ptr, cur_ptr, cur_bitoff, TotalNumberOfCdmaBwrInit );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaBwr_FWCdmaBwrEvent_TotalNumberOfTxCdmaBwr_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 TotalNumberOfTxCdmaBwr )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MonitorGroupEventCdmaBwr_FWCdmaBwrEvent_TotalNumberOfTxCdmaBwr_SET( base_ptr, cur_ptr, cur_bitoff, TotalNumberOfTxCdmaBwr );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloSfAndQosPerformanceGroup_BST_FrameNumber_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloSfAndQosPerformanceGroup_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloSfAndQosPerformanceGroup_BST_uSecInFrame_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloSfAndQosPerformanceGroup_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloSfAndQosPerformanceGroup_DilloSfAndQosPerformanceComp_TotalBytesThroughputOtaDL_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 TotalBytesThroughputOtaDL )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloSfAndQosPerformanceGroup_DilloSfAndQosPerformanceComp_TotalBytesThroughputOtaDL_SET( base_ptr, cur_ptr, cur_bitoff, TotalBytesThroughputOtaDL );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloSfAndQosPerformanceGroup_DilloSfAndQosPerformanceComp_TotalBytesThroughputOtaUL_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 TotalBytesThroughputOtaUL )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloSfAndQosPerformanceGroup_DilloSfAndQosPerformanceComp_TotalBytesThroughputOtaUL_SET( base_ptr, cur_ptr, cur_bitoff, TotalBytesThroughputOtaUL );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloSfAndQosFlowManagementGroup_BST_FrameNumber_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloSfAndQosFlowManagementGroup_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloSfAndQosFlowManagementGroup_BST_uSecInFrame_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloSfAndQosFlowManagementGroup_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloSfAndQosFlowManagementGroup_DilloSfAndQosFlowManagementComp_GrantsReceiveSlots_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 GrantsReceiveSlots )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloSfAndQosFlowManagementGroup_DilloSfAndQosFlowManagementComp_GrantsReceiveSlots_SET( base_ptr, cur_ptr, cur_bitoff, GrantsReceiveSlots );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloSfAndQosFlowManagementGroup_DilloSfAndQosFlowManagementComp_reserved_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 reserved )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloSfAndQosFlowManagementGroup_DilloSfAndQosFlowManagementComp_reserved_SET( base_ptr, cur_ptr, cur_bitoff, reserved );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloPhyConfigurationGroup_BST_FrameNumber_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloPhyConfigurationGroup_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloPhyConfigurationGroup_BST_uSecInFrame_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloPhyConfigurationGroup_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloPhyConfigurationGroup_DilloPhyConfigurationComp_DlMcsAllocationTableNoneMimo_Bursts_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT16 Bursts )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloPhyConfigurationGroup_DilloPhyConfigurationComp_DlMcsAllocationTableNoneMimo_Bursts_SET( base_ptr, i0, cur_ptr, cur_bitoff, Bursts );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloPhyConfigurationGroup_DilloPhyConfigurationComp_DlMcsAllocationTableMatrixA_Bursts_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT16 Bursts )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloPhyConfigurationGroup_DilloPhyConfigurationComp_DlMcsAllocationTableMatrixA_Bursts_SET( base_ptr, i0, cur_ptr, cur_bitoff, Bursts );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloPhyConfigurationGroup_DilloPhyConfigurationComp_DlMcsAllocationTableMatrixB_Bursts_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT16 Bursts )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloPhyConfigurationGroup_DilloPhyConfigurationComp_DlMcsAllocationTableMatrixB_Bursts_SET( base_ptr, i0, cur_ptr, cur_bitoff, Bursts );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloPhyConfigurationGroup_DilloPhyConfigurationComp_UlMcsAllocationTableNoneStc_Bursts_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT16 Bursts )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloPhyConfigurationGroup_DilloPhyConfigurationComp_UlMcsAllocationTableNoneStc_Bursts_SET( base_ptr, i0, cur_ptr, cur_bitoff, Bursts );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloPhyConfigurationGroup_DilloPhyConfigurationComp_UlMcsAllocationTableStc_Bursts_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT16 Bursts )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloPhyConfigurationGroup_DilloPhyConfigurationComp_UlMcsAllocationTableStc_Bursts_SET( base_ptr, i0, cur_ptr, cur_bitoff, Bursts );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloMapsGroup_BST_FrameNumber_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloMapsGroup_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloMapsGroup_BST_uSecInFrame_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloMapsGroup_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloMapsGroup_DilloMapsComp_TotalNumberOfMaps_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 TotalNumberOfMaps )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloMapsGroup_DilloMapsComp_TotalNumberOfMaps_SET( base_ptr, cur_ptr, cur_bitoff, TotalNumberOfMaps );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DilloMapsGroup_DilloMapsComp_TotalBytesOfMaps_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 TotalBytesOfMaps )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DilloMapsGroup_DilloMapsComp_TotalBytesOfMaps_SET( base_ptr, cur_ptr, cur_bitoff, TotalBytesOfMaps );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_BasicStatus_L3_BST_FrameNumber_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_BasicStatus_L3_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_BasicStatus_L3_BST_uSecInFrame_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_BasicStatus_L3_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_BasicStatus_L3_BasicStatus_L3_frequency_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 frequency )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_BasicStatus_L3_BasicStatus_L3_frequency_SET( base_ptr, cur_ptr, cur_bitoff, frequency );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_BasicStatus_L3_BasicStatus_L3_ulCidNum_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 ulCidNum )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_BasicStatus_L3_BasicStatus_L3_ulCidNum_SET( base_ptr, cur_ptr, cur_bitoff, ulCidNum );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_BasicStatus_L3_BasicStatus_L3_dlCidNum_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 dlCidNum )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_BasicStatus_L3_BasicStatus_L3_dlCidNum_SET( base_ptr, cur_ptr, cur_bitoff, dlCidNum );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_BasicStatus_L3_BasicStatus_L3_preambleIndex_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 preambleIndex )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_BasicStatus_L3_BasicStatus_L3_preambleIndex_SET( base_ptr, cur_ptr, cur_bitoff, preambleIndex );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_BasicStatus_L3_BasicStatus_L3_bandWidth_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, E_BandWidth bandWidth )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_BasicStatus_L3_BasicStatus_L3_bandWidth_SET( base_ptr, cur_ptr, cur_bitoff, bandWidth );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_BasicStatus_L3_BasicStatus_L3_bsId_value_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_BasicStatus_L3_BasicStatus_L3_bsId_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_BasicStatus_L3_BasicStatus_L3_macAddress_value_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_BasicStatus_L3_BasicStatus_L3_macAddress_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BST_FrameNumber_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BST_uSecInFrame_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_lastDlPduSize_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 lastDlPduSize )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_lastDlPduSize_SET( base_ptr, cur_ptr, cur_bitoff, lastDlPduSize );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_totalDlPdusSize_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 totalDlPdusSize )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_totalDlPdusSize_SET( base_ptr, cur_ptr, cur_bitoff, totalDlPdusSize );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_dlPduCount_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 dlPduCount )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_dlPduCount_SET( base_ptr, cur_ptr, cur_bitoff, dlPduCount );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_lastDlSduSize_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 lastDlSduSize )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_lastDlSduSize_SET( base_ptr, cur_ptr, cur_bitoff, lastDlSduSize );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_totalDlSdusSize_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 totalDlSdusSize )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_totalDlSdusSize_SET( base_ptr, cur_ptr, cur_bitoff, totalDlSdusSize );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_totalUlSduDropCounter_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 totalUlSduDropCounter )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_totalUlSduDropCounter_SET( base_ptr, cur_ptr, cur_bitoff, totalUlSduDropCounter );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_totalDlPdusSizeInLastDlSubFrame_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 totalDlPdusSizeInLastDlSubFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_totalDlPdusSizeInLastDlSubFrame_SET( base_ptr, cur_ptr, cur_bitoff, totalDlPdusSizeInLastDlSubFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_numOfCidInfos_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 numOfCidInfos )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_numOfCidInfos_SET( base_ptr, cur_ptr, cur_bitoff, numOfCidInfos );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_burstStatusPerConnection_CID_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 CID )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_burstStatusPerConnection_CID_SET( base_ptr, i0, cur_ptr, cur_bitoff, CID );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_burstStatusPerConnection_CIN_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 CIN )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_burstStatusPerConnection_CIN_SET( base_ptr, i0, cur_ptr, cur_bitoff, CIN );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_burstStatusPerConnection_totalUlSduRateLimitDropCount_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 totalUlSduRateLimitDropCount )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_burstStatusPerConnection_totalUlSduRateLimitDropCount_SET( base_ptr, i0, cur_ptr, cur_bitoff, totalUlSduRateLimitDropCount );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_burstStatusPerConnection_rateUlDropPackets_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 rateUlDropPackets )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_burstStatusPerConnection_rateUlDropPackets_SET( base_ptr, i0, cur_ptr, cur_bitoff, rateUlDropPackets );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_burstStatusPerConnection_totalDlReceivedPdu_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 totalDlReceivedPdu )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_burstStatusPerConnection_totalDlReceivedPdu_SET( base_ptr, i0, cur_ptr, cur_bitoff, totalDlReceivedPdu );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_burstStatusPerConnection_totalUlTransmittedSdu_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 totalUlTransmittedSdu )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_burstStatusPerConnection_totalUlTransmittedSdu_SET( base_ptr, i0, cur_ptr, cur_bitoff, totalUlTransmittedSdu );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_burstStatusPerConnection_totalOfPduDlBytes_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 totalOfPduDlBytes )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_burstStatusPerConnection_totalOfPduDlBytes_SET( base_ptr, i0, cur_ptr, cur_bitoff, totalOfPduDlBytes );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_burstStatusPerConnection_totalOfSduDlBytes_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 totalOfSduDlBytes )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_BurstStatus_L3_BurstStatus_L3_burstStatusPerConnection_totalOfSduDlBytes_SET( base_ptr, i0, cur_ptr, cur_bitoff, totalOfSduDlBytes );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_BST_FrameNumber_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_BST_uSecInFrame_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_numOfCidInfos_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 numOfCidInfos )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_numOfCidInfos_SET( base_ptr, cur_ptr, cur_bitoff, numOfCidInfos );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_numOfSfCreationSucess_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 numOfSfCreationSucess )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_numOfSfCreationSucess_SET( base_ptr, cur_ptr, cur_bitoff, numOfSfCreationSucess );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_numOfSfCreationFailure_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 numOfSfCreationFailure )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_numOfSfCreationFailure_SET( base_ptr, cur_ptr, cur_bitoff, numOfSfCreationFailure );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_numOfSfDeleted_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 numOfSfDeleted )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_numOfSfDeleted_SET( base_ptr, cur_ptr, cur_bitoff, numOfSfDeleted );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_sfId_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 sfId )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_sfId_SET( base_ptr, i0, cur_ptr, cur_bitoff, sfId );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_maxSustainedTrafficRate_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 maxSustainedTrafficRate )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_maxSustainedTrafficRate_SET( base_ptr, i0, cur_ptr, cur_bitoff, maxSustainedTrafficRate );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_maxTrafficBurst_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 maxTrafficBurst )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_maxTrafficBurst_SET( base_ptr, i0, cur_ptr, cur_bitoff, maxTrafficBurst );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_toleratedJitter_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 toleratedJitter )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_toleratedJitter_SET( base_ptr, i0, cur_ptr, cur_bitoff, toleratedJitter );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_maximumLatency_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 maximumLatency )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_maximumLatency_SET( base_ptr, i0, cur_ptr, cur_bitoff, maximumLatency );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_unsolicitedGrantInterval_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 unsolicitedGrantInterval )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_unsolicitedGrantInterval_SET( base_ptr, i0, cur_ptr, cur_bitoff, unsolicitedGrantInterval );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_minReservedTrafficRate_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 minReservedTrafficRate )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_minReservedTrafficRate_SET( base_ptr, i0, cur_ptr, cur_bitoff, minReservedTrafficRate );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_cid_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT16 cid )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_cid_SET( base_ptr, i0, cur_ptr, cur_bitoff, cid );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_sfSchedulingType_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, SFSchedulingType sfSchedulingType )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_sfSchedulingType_SET( base_ptr, i0, cur_ptr, cur_bitoff, sfSchedulingType );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_qosParamsSetType_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, E_QoSParamsSetType qosParamsSetType )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_qosParamsSetType_SET( base_ptr, i0, cur_ptr, cur_bitoff, qosParamsSetType );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_trafficPrio_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 trafficPrio )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_trafficPrio_SET( base_ptr, i0, cur_ptr, cur_bitoff, trafficPrio );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_sfSide_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, E_SfSide sfSide )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_SF_QoS_MonitorInfo_L3_SF_QoS_MonitorInfo_L3_channels_sfSide_SET( base_ptr, i0, cur_ptr, cur_bitoff, sfSide );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_BST_FrameNumber_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_BST_uSecInFrame_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_numOfCidInfos_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 numOfCidInfos )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_numOfCidInfos_SET( base_ptr, cur_ptr, cur_bitoff, numOfCidInfos );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_arqInfo_sfId_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 sfId )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_arqInfo_sfId_SET( base_ptr, i0, cur_ptr, cur_bitoff, sfId );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_arqInfo_arqWindowSize_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 arqWindowSize )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_arqInfo_arqWindowSize_SET( base_ptr, i0, cur_ptr, cur_bitoff, arqWindowSize );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_arqInfo_arqTransmitterDelay_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 arqTransmitterDelay )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_arqInfo_arqTransmitterDelay_SET( base_ptr, i0, cur_ptr, cur_bitoff, arqTransmitterDelay );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_arqInfo_arqReceiverDelay_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 arqReceiverDelay )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_arqInfo_arqReceiverDelay_SET( base_ptr, i0, cur_ptr, cur_bitoff, arqReceiverDelay );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_arqInfo_arqBlockLifeTime_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 arqBlockLifeTime )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_arqInfo_arqBlockLifeTime_SET( base_ptr, i0, cur_ptr, cur_bitoff, arqBlockLifeTime );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_arqInfo_arqSyncLossTimeout_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 arqSyncLossTimeout )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_arqInfo_arqSyncLossTimeout_SET( base_ptr, i0, cur_ptr, cur_bitoff, arqSyncLossTimeout );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_arqInfo_arqRxPurgeTimeout_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 arqRxPurgeTimeout )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_arqInfo_arqRxPurgeTimeout_SET( base_ptr, i0, cur_ptr, cur_bitoff, arqRxPurgeTimeout );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_arqInfo_arqBlockSize_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 arqBlockSize )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_arqInfo_arqBlockSize_SET( base_ptr, i0, cur_ptr, cur_bitoff, arqBlockSize );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_arqInfo_t22_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 t22 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_arqInfo_t22_SET( base_ptr, i0, cur_ptr, cur_bitoff, t22 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_arqInfo_arqEnable_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 arqEnable )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_arqInfo_arqEnable_SET( base_ptr, i0, cur_ptr, cur_bitoff, arqEnable );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_arqInfo_arqDeliverInOrder_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 arqDeliverInOrder )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorInfo_L3_Arq_MonitorInfo_L3_arqInfo_arqDeliverInOrder_SET( base_ptr, i0, cur_ptr, cur_bitoff, arqDeliverInOrder );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Harq_MonitorInfo_L3_BST_FrameNumber_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Harq_MonitorInfo_L3_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Harq_MonitorInfo_L3_BST_uSecInFrame_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Harq_MonitorInfo_L3_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Harq_MonitorInfo_L3_Harq_MonitorInfo_L3_numOfCidInfos_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 numOfCidInfos )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Harq_MonitorInfo_L3_Harq_MonitorInfo_L3_numOfCidInfos_SET( base_ptr, cur_ptr, cur_bitoff, numOfCidInfos );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Harq_MonitorInfo_L3_Harq_MonitorInfo_L3_harqInfo_harqChannelMapping_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT16 harqChannelMapping )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Harq_MonitorInfo_L3_Harq_MonitorInfo_L3_harqInfo_harqChannelMapping_SET( base_ptr, i0, cur_ptr, cur_bitoff, harqChannelMapping );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Harq_MonitorInfo_L3_Harq_MonitorInfo_L3_harqInfo_harqEnable_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 harqEnable )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Harq_MonitorInfo_L3_Harq_MonitorInfo_L3_harqInfo_harqEnable_SET( base_ptr, i0, cur_ptr, cur_bitoff, harqEnable );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Harq_MonitorInfo_L3_Harq_MonitorInfo_L3_harqInfo_harqisForReorder_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 harqisForReorder )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Harq_MonitorInfo_L3_Harq_MonitorInfo_L3_harqInfo_harqisForReorder_SET( base_ptr, i0, cur_ptr, cur_bitoff, harqisForReorder );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Harq_MonitorInfo_L3_Harq_MonitorInfo_L3_harqInfo_sfId_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 sfId )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Harq_MonitorInfo_L3_Harq_MonitorInfo_L3_harqInfo_sfId_SET( base_ptr, i0, cur_ptr, cur_bitoff, sfId );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MacState_L3_BST_FrameNumber_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MacState_L3_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MacState_L3_BST_uSecInFrame_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MacState_L3_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MacState_L3_MacState_L3_state_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, E_MacState state )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MacState_L3_MacState_L3_state_SET( base_ptr, cur_ptr, cur_bitoff, state );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_BST_FrameNumber_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_BST_uSecInFrame_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_numOfIntraFASNbrs_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 numOfIntraFASNbrs )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_numOfIntraFASNbrs_SET( base_ptr, cur_ptr, cur_bitoff, numOfIntraFASNbrs );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_numOfInterFASNbrs_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 numOfInterFASNbrs )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_numOfInterFASNbrs_SET( base_ptr, cur_ptr, cur_bitoff, numOfInterFASNbrs );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_intraFaNbrs_rssiMean_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, INT16 rssiMean )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_intraFaNbrs_rssiMean_SET( base_ptr, i0, cur_ptr, cur_bitoff, rssiMean );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_intraFaNbrs_cinrMean_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, INT16 cinrMean )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_intraFaNbrs_cinrMean_SET( base_ptr, i0, cur_ptr, cur_bitoff, cinrMean );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_intraFaNbrs_preambleId_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 preambleId )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_intraFaNbrs_preambleId_SET( base_ptr, i0, cur_ptr, cur_bitoff, preambleId );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_intraFaNbrs_frequency_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 frequency )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_intraFaNbrs_frequency_SET( base_ptr, i0, cur_ptr, cur_bitoff, frequency );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_intraFaNbrs_bandWidth_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, E_BandWidth bandWidth )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_intraFaNbrs_bandWidth_SET( base_ptr, i0, cur_ptr, cur_bitoff, bandWidth );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_intraFaNbrs_bsId_value_SET( UINT8* base_ptr, UINT32 i0, UINT32 i1, UINT32 diff, UINT32 cur_bitoff, UINT8 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_intraFaNbrs_bsId_value_SET( base_ptr, i0, i1, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_interFaNbrs_rssiMean_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, INT16 rssiMean )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_interFaNbrs_rssiMean_SET( base_ptr, i0, cur_ptr, cur_bitoff, rssiMean );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_interFaNbrs_cinrMean_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, INT16 cinrMean )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_interFaNbrs_cinrMean_SET( base_ptr, i0, cur_ptr, cur_bitoff, cinrMean );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_interFaNbrs_preambleId_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 preambleId )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_interFaNbrs_preambleId_SET( base_ptr, i0, cur_ptr, cur_bitoff, preambleId );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_interFaNbrs_frequency_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 frequency )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_interFaNbrs_frequency_SET( base_ptr, i0, cur_ptr, cur_bitoff, frequency );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_interFaNbrs_bandWidth_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, E_BandWidth bandWidth )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_interFaNbrs_bandWidth_SET( base_ptr, i0, cur_ptr, cur_bitoff, bandWidth );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_interFaNbrs_bsId_value_SET( UINT8* base_ptr, UINT32 i0, UINT32 i1, UINT32 diff, UINT32 cur_bitoff, UINT8 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_NbrCellList_L3_NbrCellList_L3_interFaNbrs_bsId_value_SET( base_ptr, i0, i1, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_NwEntryMsgLatency_L3_BST_FrameNumber_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_NwEntryMsgLatency_L3_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_NwEntryMsgLatency_L3_BST_uSecInFrame_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_NwEntryMsgLatency_L3_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_NwEntryMsgLatency_L3_NwEntryMsgLatency_L3_initRengLatency_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 initRengLatency )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_NwEntryMsgLatency_L3_NwEntryMsgLatency_L3_initRengLatency_SET( base_ptr, cur_ptr, cur_bitoff, initRengLatency );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_NwEntryMsgLatency_L3_NwEntryMsgLatency_L3_sbcLatency_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 sbcLatency )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_NwEntryMsgLatency_L3_NwEntryMsgLatency_L3_sbcLatency_SET( base_ptr, cur_ptr, cur_bitoff, sbcLatency );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_NwEntryMsgLatency_L3_NwEntryMsgLatency_L3_pkmLatency_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 pkmLatency )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_NwEntryMsgLatency_L3_NwEntryMsgLatency_L3_pkmLatency_SET( base_ptr, cur_ptr, cur_bitoff, pkmLatency );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_NwEntryMsgLatency_L3_NwEntryMsgLatency_L3_regLatency_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 regLatency )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_NwEntryMsgLatency_L3_NwEntryMsgLatency_L3_regLatency_SET( base_ptr, cur_ptr, cur_bitoff, regLatency );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_NwEntryMsgLatency_L3_NwEntryMsgLatency_L3_dsaLatency_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 dsaLatency )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_NwEntryMsgLatency_L3_NwEntryMsgLatency_L3_dsaLatency_SET( base_ptr, cur_ptr, cur_bitoff, dsaLatency );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_NwEntryMsgLatency_L3_NwEntryMsgLatency_L3_setuUpTime_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 setuUpTime )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_NwEntryMsgLatency_L3_NwEntryMsgLatency_L3_setuUpTime_SET( base_ptr, cur_ptr, cur_bitoff, setuUpTime );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DcdUcdTimeout_L3_BST_FrameNumber_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DcdUcdTimeout_L3_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DcdUcdTimeout_L3_BST_uSecInFrame_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DcdUcdTimeout_L3_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DcdUcdTimeout_L3_DcdUcdTimeout_L3_countDcdUcdTimeOut_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 countDcdUcdTimeOut )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DcdUcdTimeout_L3_DcdUcdTimeout_L3_countDcdUcdTimeOut_SET( base_ptr, cur_ptr, cur_bitoff, countDcdUcdTimeOut );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DSxTimers_L3_BST_FrameNumber_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DSxTimers_L3_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DSxTimers_L3_BST_uSecInFrame_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DSxTimers_L3_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DSxTimers_L3_DSxTimers_L3_t7Timeout_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 t7Timeout )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DSxTimers_L3_DSxTimers_L3_t7Timeout_SET( base_ptr, cur_ptr, cur_bitoff, t7Timeout );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DSxTimers_L3_DSxTimers_L3_t8Timeout_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 t8Timeout )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DSxTimers_L3_DSxTimers_L3_t8Timeout_SET( base_ptr, cur_ptr, cur_bitoff, t8Timeout );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DSxTimers_L3_DSxTimers_L3_t10Timeout_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 t10Timeout )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DSxTimers_L3_DSxTimers_L3_t10Timeout_SET( base_ptr, cur_ptr, cur_bitoff, t10Timeout );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DSxTimers_L3_DSxTimers_L3_dsxReqRetries_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 dsxReqRetries )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DSxTimers_L3_DSxTimers_L3_dsxReqRetries_SET( base_ptr, cur_ptr, cur_bitoff, dsxReqRetries );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DSxTimers_L3_DSxTimers_L3_dsxRspRetries_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 dsxRspRetries )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DSxTimers_L3_DSxTimers_L3_dsxRspRetries_SET( base_ptr, cur_ptr, cur_bitoff, dsxRspRetries );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Phy_L3_BST_FrameNumber_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Phy_L3_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Phy_L3_BST_uSecInFrame_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Phy_L3_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Phy_L3_Phy_L3_preambleSearchTime_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 preambleSearchTime )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Phy_L3_Phy_L3_preambleSearchTime_SET( base_ptr, cur_ptr, cur_bitoff, preambleSearchTime );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Phy_L3_Phy_L3_numOfPreamble_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 numOfPreamble )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Phy_L3_Phy_L3_numOfPreamble_SET( base_ptr, cur_ptr, cur_bitoff, numOfPreamble );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_LinkLossOccur_L3_BST_FrameNumber_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_LinkLossOccur_L3_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_LinkLossOccur_L3_BST_uSecInFrame_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_LinkLossOccur_L3_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_LinkLossOccur_L3_LinkLossOccur_L3_occurrenceTime_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 occurrenceTime )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_LinkLossOccur_L3_LinkLossOccur_L3_occurrenceTime_SET( base_ptr, cur_ptr, cur_bitoff, occurrenceTime );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_LinkLossOccur_L3_LinkLossOccur_L3_LastLinkLossReason_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, E_LinkLossReason LastLinkLossReason )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_LinkLossOccur_L3_LinkLossOccur_L3_LastLinkLossReason_SET( base_ptr, cur_ptr, cur_bitoff, LastLinkLossReason );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_LinkLossOccur_L3_LinkLossOccur_L3_bsId_value_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_LinkLossOccur_L3_LinkLossOccur_L3_bsId_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Moniter_Scan_Config_BST_FrameNumber_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Moniter_Scan_Config_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Moniter_Scan_Config_BST_uSecInFrame_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Moniter_Scan_Config_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Moniter_Scan_Config_MoniterScanConfig_SetScanParam_NumOfChannels_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 NumOfChannels )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Moniter_Scan_Config_MoniterScanConfig_SetScanParam_NumOfChannels_SET( base_ptr, cur_ptr, cur_bitoff, NumOfChannels );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Moniter_Scan_Config_MoniterScanConfig_SetScanParam_Channels_Frequency_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 Frequency )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Moniter_Scan_Config_MoniterScanConfig_SetScanParam_Channels_Frequency_SET( base_ptr, i0, cur_ptr, cur_bitoff, Frequency );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Moniter_Scan_Config_MoniterScanConfig_SetScanParam_Channels_ChannelId_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT16 ChannelId )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Moniter_Scan_Config_MoniterScanConfig_SetScanParam_Channels_ChannelId_SET( base_ptr, i0, cur_ptr, cur_bitoff, ChannelId );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Moniter_Scan_Config_MoniterScanConfig_SetScanParam_Channels_Bandwidth_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 Bandwidth )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Moniter_Scan_Config_MoniterScanConfig_SetScanParam_Channels_Bandwidth_SET( base_ptr, i0, cur_ptr, cur_bitoff, Bandwidth );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Moniter_Scan_Config_MoniterScanConfig_SetScanParam_Channels_Fft_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 Fft )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Moniter_Scan_Config_MoniterScanConfig_SetScanParam_Channels_Fft_SET( base_ptr, i0, cur_ptr, cur_bitoff, Fft );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Moniter_Scan_Config_MoniterScanConfig_SetScanParam_Channels_Preambles_value_SET( UINT8* base_ptr, UINT32 i0, UINT32 i1, UINT32 diff, UINT32 cur_bitoff, UINT8 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Moniter_Scan_Config_MoniterScanConfig_SetScanParam_Channels_Preambles_value_SET( base_ptr, i0, i1, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Moniter_Scan_Config_MoniterScanConfig_SetScanParam_Channels_Reserved_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 Reserved )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Moniter_Scan_Config_MoniterScanConfig_SetScanParam_Channels_Reserved_SET( base_ptr, i0, cur_ptr, cur_bitoff, Reserved );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DSPS_Management_MSG_BST_FrameNumber_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DSPS_Management_MSG_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DSPS_Management_MSG_BST_uSecInFrame_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DSPS_Management_MSG_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_DSPS_Management_MSG_DSPS_Management_MSG_MngmntBufferRun_value_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_DSPS_Management_MSG_DSPS_Management_MSG_MngmntBufferRun_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_linkLossStatistics_L3_BST_FrameNumber_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_linkLossStatistics_L3_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_linkLossStatistics_L3_BST_uSecInFrame_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_linkLossStatistics_L3_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_linkLossStatistics_L3_linkLossStatistics_L3_occurrenceTime_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 occurrenceTime )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_linkLossStatistics_L3_linkLossStatistics_L3_occurrenceTime_SET( base_ptr, cur_ptr, cur_bitoff, occurrenceTime );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_linkLossStatistics_L3_linkLossStatistics_L3_linkLossLatency_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 linkLossLatency )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_linkLossStatistics_L3_linkLossStatistics_L3_linkLossLatency_SET( base_ptr, cur_ptr, cur_bitoff, linkLossLatency );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_linkLossStatistics_L3_linkLossStatistics_L3_HoRangingLatency_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 HoRangingLatency )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_linkLossStatistics_L3_linkLossStatistics_L3_HoRangingLatency_SET( base_ptr, cur_ptr, cur_bitoff, HoRangingLatency );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_linkLossStatistics_L3_linkLossStatistics_L3_bsId_value_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_linkLossStatistics_L3_linkLossStatistics_L3_bsId_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_BST_FrameNumber_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_BST_uSecInFrame_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_numOfBsInHoReq_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 numOfBsInHoReq )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_numOfBsInHoReq_SET( base_ptr, cur_ptr, cur_bitoff, numOfBsInHoReq );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_numOfBsInHoRsp_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 numOfBsInHoRsp )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_numOfBsInHoRsp_SET( base_ptr, cur_ptr, cur_bitoff, numOfBsInHoRsp );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_HoSuccessCounter_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 HoSuccessCounter )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_HoSuccessCounter_SET( base_ptr, cur_ptr, cur_bitoff, HoSuccessCounter );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_HoFailCounter_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 HoFailCounter )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_HoFailCounter_SET( base_ptr, cur_ptr, cur_bitoff, HoFailCounter );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_HoTriggersCounter_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 HoTriggersCounter )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_HoTriggersCounter_SET( base_ptr, cur_ptr, cur_bitoff, HoTriggersCounter );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_HoRejectsCounter_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 HoRejectsCounter )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_HoRejectsCounter_SET( base_ptr, cur_ptr, cur_bitoff, HoRejectsCounter );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_HoNotRecommendedCounter_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 HoNotRecommendedCounter )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_HoNotRecommendedCounter_SET( base_ptr, cur_ptr, cur_bitoff, HoNotRecommendedCounter );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_numberOfTBSAttempted_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 numberOfTBSAttempted )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_numberOfTBSAttempted_SET( base_ptr, cur_ptr, cur_bitoff, numberOfTBSAttempted );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_cancellationWithNormalOperation_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 cancellationWithNormalOperation )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_cancellationWithNormalOperation_SET( base_ptr, cur_ptr, cur_bitoff, cancellationWithNormalOperation );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_cancellationWithReentryProblem_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 cancellationWithReentryProblem )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_cancellationWithReentryProblem_SET( base_ptr, cur_ptr, cur_bitoff, cancellationWithReentryProblem );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_coordHoLatency_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 coordHoLatency )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_coordHoLatency_SET( base_ptr, cur_ptr, cur_bitoff, coordHoLatency );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_cutOffLatency_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 cutOffLatency )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_cutOffLatency_SET( base_ptr, cur_ptr, cur_bitoff, cutOffLatency );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_status_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, E_HOStatus status )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_status_SET( base_ptr, cur_ptr, cur_bitoff, status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_typeId_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, E_HOTypeId typeId )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_typeId_SET( base_ptr, cur_ptr, cur_bitoff, typeId );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_hoReqBsList_bsId_value_SET( UINT8* base_ptr, UINT32 i0, UINT32 i1, UINT32 diff, UINT32 cur_bitoff, UINT8 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_hoReqBsList_bsId_value_SET( base_ptr, i0, i1, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_hoRspBsList_bsId_value_SET( UINT8* base_ptr, UINT32 i0, UINT32 i1, UINT32 diff, UINT32 cur_bitoff, UINT8 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_CoordinateHo_L3_CoordinateHo_L3_hoRspBsList_bsId_value_SET( base_ptr, i0, i1, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_BST_FrameNumber_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_BST_uSecInFrame_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_McsIndexTable_L3_NumDlburstProfiles_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 NumDlburstProfiles )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_McsIndexTable_L3_NumDlburstProfiles_SET( base_ptr, cur_ptr, cur_bitoff, NumDlburstProfiles );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_McsIndexTable_L3_NumUlburstProfiles_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 NumUlburstProfiles )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_McsIndexTable_L3_NumUlburstProfiles_SET( base_ptr, cur_ptr, cur_bitoff, NumUlburstProfiles );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_McsIndexTable_L3_DlburstProfiles_intervalUsageCode_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 intervalUsageCode )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_McsIndexTable_L3_DlburstProfiles_intervalUsageCode_SET( base_ptr, i0, cur_ptr, cur_bitoff, intervalUsageCode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_McsIndexTable_L3_DlburstProfiles_fecType_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, FecType fecType )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_McsIndexTable_L3_DlburstProfiles_fecType_SET( base_ptr, i0, cur_ptr, cur_bitoff, fecType );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_McsIndexTable_L3_DlburstProfiles_fecRate_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, FecRate fecRate )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_McsIndexTable_L3_DlburstProfiles_fecRate_SET( base_ptr, i0, cur_ptr, cur_bitoff, fecRate );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_McsIndexTable_L3_DlburstProfiles_modulation_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, Modulation modulation )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_McsIndexTable_L3_DlburstProfiles_modulation_SET( base_ptr, i0, cur_ptr, cur_bitoff, modulation );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_McsIndexTable_L3_UlburstProfiles_intervalUsageCode_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 intervalUsageCode )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_McsIndexTable_L3_UlburstProfiles_intervalUsageCode_SET( base_ptr, i0, cur_ptr, cur_bitoff, intervalUsageCode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_McsIndexTable_L3_UlburstProfiles_fecType_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, FecType fecType )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_McsIndexTable_L3_UlburstProfiles_fecType_SET( base_ptr, i0, cur_ptr, cur_bitoff, fecType );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_McsIndexTable_L3_UlburstProfiles_fecRate_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, FecRate fecRate )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_McsIndexTable_L3_UlburstProfiles_fecRate_SET( base_ptr, i0, cur_ptr, cur_bitoff, fecRate );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_McsIndexTable_L3_UlburstProfiles_modulation_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, Modulation modulation )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_McsIndexTable_L3_McsIndexTable_L3_UlburstProfiles_modulation_SET( base_ptr, i0, cur_ptr, cur_bitoff, modulation );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_ScanResult_L3_BST_FrameNumber_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_ScanResult_L3_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_ScanResult_L3_BST_uSecInFrame_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_ScanResult_L3_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_ScanResult_L3_ScanResult_L3_numOfNbrs_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 numOfNbrs )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_ScanResult_L3_ScanResult_L3_numOfNbrs_SET( base_ptr, cur_ptr, cur_bitoff, numOfNbrs );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_ScanResult_L3_ScanResult_L3_resultNbrs_phyLinkId_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 phyLinkId )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_ScanResult_L3_ScanResult_L3_resultNbrs_phyLinkId_SET( base_ptr, i0, cur_ptr, cur_bitoff, phyLinkId );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_ScanResult_L3_ScanResult_L3_resultNbrs_frequency_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 frequency )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_ScanResult_L3_ScanResult_L3_resultNbrs_frequency_SET( base_ptr, i0, cur_ptr, cur_bitoff, frequency );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_ScanResult_L3_ScanResult_L3_resultNbrs_phyGrade_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, INT16 phyGrade )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_ScanResult_L3_ScanResult_L3_resultNbrs_phyGrade_SET( base_ptr, i0, cur_ptr, cur_bitoff, phyGrade );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_ScanResult_L3_ScanResult_L3_resultNbrs_preambleId_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 preambleId )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_ScanResult_L3_ScanResult_L3_resultNbrs_preambleId_SET( base_ptr, i0, cur_ptr, cur_bitoff, preambleId );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_ScanResult_L3_ScanResult_L3_resultNbrs_bandWidth_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, E_BandWidth bandWidth )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_ScanResult_L3_ScanResult_L3_resultNbrs_bandWidth_SET( base_ptr, i0, cur_ptr, cur_bitoff, bandWidth );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_ScanResult_L3_ScanResult_L3_resultNbrs_bSValidityIndicator_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, ECellStatus bSValidityIndicator )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_ScanResult_L3_ScanResult_L3_resultNbrs_bSValidityIndicator_SET( base_ptr, i0, cur_ptr, cur_bitoff, bSValidityIndicator );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_ScanResult_L3_ScanResult_L3_resultNbrs_bsId_value_SET( UINT8* base_ptr, UINT32 i0, UINT32 i1, UINT32 diff, UINT32 cur_bitoff, UINT8 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_ScanResult_L3_ScanResult_L3_resultNbrs_bsId_value_SET( base_ptr, i0, i1, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_ScanStatus_L3_BST_FrameNumber_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_ScanStatus_L3_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_ScanStatus_L3_BST_uSecInFrame_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_ScanStatus_L3_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_ScanStatus_L3_ScanStatus_L3_scanDuration_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 scanDuration )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_ScanStatus_L3_ScanStatus_L3_scanDuration_SET( base_ptr, cur_ptr, cur_bitoff, scanDuration );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_ScanStatus_L3_ScanStatus_L3_scanIteration_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 scanIteration )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_ScanStatus_L3_ScanStatus_L3_scanIteration_SET( base_ptr, cur_ptr, cur_bitoff, scanIteration );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_ScanStatus_L3_ScanStatus_L3_modeReport_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 modeReport )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_ScanStatus_L3_ScanStatus_L3_modeReport_SET( base_ptr, cur_ptr, cur_bitoff, modeReport );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_ScanStatus_L3_ScanStatus_L3_periodReport_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 periodReport )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_ScanStatus_L3_ScanStatus_L3_periodReport_SET( base_ptr, cur_ptr, cur_bitoff, periodReport );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_ScanStatus_L3_ScanStatus_L3_interleavingInterval_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 interleavingInterval )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_ScanStatus_L3_ScanStatus_L3_interleavingInterval_SET( base_ptr, cur_ptr, cur_bitoff, interleavingInterval );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_ConnectionDropCount_L3_BST_FrameNumber_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_ConnectionDropCount_L3_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_ConnectionDropCount_L3_BST_uSecInFrame_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_ConnectionDropCount_L3_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_ConnectionDropCount_L3_ConnectionDropCount_L3_counterConnectionDropEvent_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 counterConnectionDropEvent )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_ConnectionDropCount_L3_ConnectionDropCount_L3_counterConnectionDropEvent_SET( base_ptr, cur_ptr, cur_bitoff, counterConnectionDropEvent );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_BST_FrameNumber_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_BST_uSecInFrame_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_IdleConfiguration_L3_idleModeTimeout_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 idleModeTimeout )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_IdleConfiguration_L3_idleModeTimeout_SET( base_ptr, cur_ptr, cur_bitoff, idleModeTimeout );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_IdleConfiguration_L3_pagingCycleReq_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 pagingCycleReq )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_IdleConfiguration_L3_pagingCycleReq_SET( base_ptr, cur_ptr, cur_bitoff, pagingCycleReq );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_IdleConfiguration_L3_t45Timeout_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 t45Timeout )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_IdleConfiguration_L3_t45Timeout_SET( base_ptr, cur_ptr, cur_bitoff, t45Timeout );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_IdleConfiguration_L3_PagingGroupID_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 PagingGroupID )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_IdleConfiguration_L3_PagingGroupID_SET( base_ptr, cur_ptr, cur_bitoff, PagingGroupID );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_IdleConfiguration_L3_PagingCycle_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 PagingCycle )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_IdleConfiguration_L3_PagingCycle_SET( base_ptr, cur_ptr, cur_bitoff, PagingCycle );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_IdleConfiguration_L3_PagingOffset_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 PagingOffset )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_IdleConfiguration_L3_PagingOffset_SET( base_ptr, cur_ptr, cur_bitoff, PagingOffset );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_IdleConfiguration_L3_RetainInfo_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 RetainInfo )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_IdleConfiguration_L3_RetainInfo_SET( base_ptr, cur_ptr, cur_bitoff, RetainInfo );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_IdleConfiguration_L3_dregReqRetries_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 dregReqRetries )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_IdleConfiguration_L3_dregReqRetries_SET( base_ptr, cur_ptr, cur_bitoff, dregReqRetries );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_IdleConfiguration_L3_PagingIntervalLength_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 PagingIntervalLength )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_IdleConfiguration_L3_PagingIntervalLength_SET( base_ptr, cur_ptr, cur_bitoff, PagingIntervalLength );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_IdleConfiguration_L3_PagingControllerID_value_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_IdleConfiguration_L3_IdleConfiguration_L3_PagingControllerID_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_IdlePerformance_L3_BST_FrameNumber_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_IdlePerformance_L3_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_IdlePerformance_L3_BST_uSecInFrame_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_IdlePerformance_L3_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_IdlePerformance_L3_IdlePerformance_L3_counterInternalTimer_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 counterInternalTimer )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_IdlePerformance_L3_IdlePerformance_L3_counterInternalTimer_SET( base_ptr, cur_ptr, cur_bitoff, counterInternalTimer );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_IdlePerformance_L3_IdlePerformance_L3_counterNWInitiated_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 counterNWInitiated )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_IdlePerformance_L3_IdlePerformance_L3_counterNWInitiated_SET( base_ptr, cur_ptr, cur_bitoff, counterNWInitiated );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_IdlePerformance_L3_IdlePerformance_L3_counterGroupChange_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 counterGroupChange )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_IdlePerformance_L3_IdlePerformance_L3_counterGroupChange_SET( base_ptr, cur_ptr, cur_bitoff, counterGroupChange );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_IdlePerformance_L3_IdlePerformance_L3_counterSecuredLu_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 counterSecuredLu )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_IdlePerformance_L3_IdlePerformance_L3_counterSecuredLu_SET( base_ptr, cur_ptr, cur_bitoff, counterSecuredLu );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_IdlePerformance_L3_IdlePerformance_L3_counterUnSecuredLu_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 counterUnSecuredLu )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_IdlePerformance_L3_IdlePerformance_L3_counterUnSecuredLu_SET( base_ptr, cur_ptr, cur_bitoff, counterUnSecuredLu );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_BST_FrameNumber_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_BST_uSecInFrame_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqResetPerformed_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 arqResetPerformed )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqResetPerformed_SET( base_ptr, cur_ptr, cur_bitoff, arqResetPerformed );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_numOfCidPerformance_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 numOfCidPerformance )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_numOfCidPerformance_SET( base_ptr, cur_ptr, cur_bitoff, numOfCidPerformance );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqRxPerformance_CID_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 CID )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqRxPerformance_CID_SET( base_ptr, i0, cur_ptr, cur_bitoff, CID );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqRxPerformance_CIN_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 CIN )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqRxPerformance_CIN_SET( base_ptr, i0, cur_ptr, cur_bitoff, CIN );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqRxPerformance_numOfDuplicateReceivedBlocks_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 numOfDuplicateReceivedBlocks )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqRxPerformance_numOfDuplicateReceivedBlocks_SET( base_ptr, i0, cur_ptr, cur_bitoff, numOfDuplicateReceivedBlocks );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqRxPerformance_numOfPurgeTimeouts_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 numOfPurgeTimeouts )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqRxPerformance_numOfPurgeTimeouts_SET( base_ptr, i0, cur_ptr, cur_bitoff, numOfPurgeTimeouts );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqRxPerformance_numOfBlocksLostDueToRxPurgeTimout_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 numOfBlocksLostDueToRxPurgeTimout )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqRxPerformance_numOfBlocksLostDueToRxPurgeTimout_SET( base_ptr, i0, cur_ptr, cur_bitoff, numOfBlocksLostDueToRxPurgeTimout );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqRxPerformance_totalNumOfAcksTxd_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 totalNumOfAcksTxd )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqRxPerformance_totalNumOfAcksTxd_SET( base_ptr, i0, cur_ptr, cur_bitoff, totalNumOfAcksTxd );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqRxPerformance_numOfRxArqResetsReceived_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 numOfRxArqResetsReceived )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqRxPerformance_numOfRxArqResetsReceived_SET( base_ptr, i0, cur_ptr, cur_bitoff, numOfRxArqResetsReceived );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqRxPerformance_numOfRxArqResetsInitiated_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 numOfRxArqResetsInitiated )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqRxPerformance_numOfRxArqResetsInitiated_SET( base_ptr, i0, cur_ptr, cur_bitoff, numOfRxArqResetsInitiated );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqRxPerformance_numOfArqDiscardsReceived_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 numOfArqDiscardsReceived )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqRxPerformance_numOfArqDiscardsReceived_SET( base_ptr, i0, cur_ptr, cur_bitoff, numOfArqDiscardsReceived );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqRxPerformance_rxThroughput_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 rxThroughput )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqRxPerformance_rxThroughput_SET( base_ptr, i0, cur_ptr, cur_bitoff, rxThroughput );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqRxPerformance_numOfPduLostDueToNoFreeSpaceInReceiver_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 numOfPduLostDueToNoFreeSpaceInReceiver )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorRxPerformance_L3_Arq_MonitorRxPerformance_L3_arqRxPerformance_numOfPduLostDueToNoFreeSpaceInReceiver_SET( base_ptr, i0, cur_ptr, cur_bitoff, numOfPduLostDueToNoFreeSpaceInReceiver );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_BST_FrameNumber_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_BST_uSecInFrame_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_numOfCidPerformance_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 numOfCidPerformance )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_numOfCidPerformance_SET( base_ptr, cur_ptr, cur_bitoff, numOfCidPerformance );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_CID_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 CID )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_CID_SET( base_ptr, i0, cur_ptr, cur_bitoff, CID );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_CIN_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 CIN )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_CIN_SET( base_ptr, i0, cur_ptr, cur_bitoff, CIN );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_numOfRetransmittedArqBlocksTotalUL_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 numOfRetransmittedArqBlocksTotalUL )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_numOfRetransmittedArqBlocksTotalUL_SET( base_ptr, i0, cur_ptr, cur_bitoff, numOfRetransmittedArqBlocksTotalUL );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_numOfRetransmittedBlocksUL_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 numOfRetransmittedBlocksUL )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_numOfRetransmittedBlocksUL_SET( base_ptr, i0, cur_ptr, cur_bitoff, numOfRetransmittedBlocksUL );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_numOfBLTs_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 numOfBLTs )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_numOfBLTs_SET( base_ptr, i0, cur_ptr, cur_bitoff, numOfBLTs );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_numOfBlocksLostDueToArqBLT_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 numOfBlocksLostDueToArqBLT )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_numOfBlocksLostDueToArqBLT_SET( base_ptr, i0, cur_ptr, cur_bitoff, numOfBlocksLostDueToArqBLT );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_totalNumOfAcksReceived_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 totalNumOfAcksReceived )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_totalNumOfAcksReceived_SET( base_ptr, i0, cur_ptr, cur_bitoff, totalNumOfAcksReceived );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_numOfTxArqResetsReceived_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 numOfTxArqResetsReceived )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_numOfTxArqResetsReceived_SET( base_ptr, i0, cur_ptr, cur_bitoff, numOfTxArqResetsReceived );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_numOfTxArqResetsInitiated_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 numOfTxArqResetsInitiated )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_numOfTxArqResetsInitiated_SET( base_ptr, i0, cur_ptr, cur_bitoff, numOfTxArqResetsInitiated );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_numOfArqDiscardsTxd_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 numOfArqDiscardsTxd )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_numOfArqDiscardsTxd_SET( base_ptr, i0, cur_ptr, cur_bitoff, numOfArqDiscardsTxd );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_txThroughput_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 txThroughput )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_txThroughput_SET( base_ptr, i0, cur_ptr, cur_bitoff, txThroughput );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_numOfSduLostDueToNoFreeSpaceInTransmitter_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 numOfSduLostDueToNoFreeSpaceInTransmitter )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Arq_MonitorTxPerformance_L3_Arq_MonitorTxPerformance_L3_arqTxPerformance_numOfSduLostDueToNoFreeSpaceInTransmitter_SET( base_ptr, i0, cur_ptr, cur_bitoff, numOfSduLostDueToNoFreeSpaceInTransmitter );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MonitorSfPerformance_L3_BST_FrameNumber_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MonitorSfPerformance_L3_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MonitorSfPerformance_L3_BST_uSecInFrame_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MonitorSfPerformance_L3_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MonitorSfPerformance_L3_SfPerformance_L3_numOfCidInfos_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 numOfCidInfos )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MonitorSfPerformance_L3_SfPerformance_L3_numOfCidInfos_SET( base_ptr, cur_ptr, cur_bitoff, numOfCidInfos );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MonitorSfPerformance_L3_SfPerformance_L3_SfPeformancePerConnection_CID_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 CID )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MonitorSfPerformance_L3_SfPerformance_L3_SfPeformancePerConnection_CID_SET( base_ptr, i0, cur_ptr, cur_bitoff, CID );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MonitorSfPerformance_L3_SfPerformance_L3_SfPeformancePerConnection_CIN_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 CIN )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MonitorSfPerformance_L3_SfPerformance_L3_SfPeformancePerConnection_CIN_SET( base_ptr, i0, cur_ptr, cur_bitoff, CIN );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MonitorSfPerformance_L3_SfPerformance_L3_SfPeformancePerConnection_ulIpThroughput_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 ulIpThroughput )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MonitorSfPerformance_L3_SfPerformance_L3_SfPeformancePerConnection_ulIpThroughput_SET( base_ptr, i0, cur_ptr, cur_bitoff, ulIpThroughput );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_MonitorSfPerformance_L3_SfPerformance_L3_SfPeformancePerConnection_dlIpThroughput_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 dlIpThroughput )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_MonitorSfPerformance_L3_SfPerformance_L3_SfPeformancePerConnection_dlIpThroughput_SET( base_ptr, i0, cur_ptr, cur_bitoff, dlIpThroughput );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Result_BST_FrameNumber_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Result_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Result_BST_uSecInFrame_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Result_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Result_MonitorScanResult_AvailableNSPsIdlist_NumOfNSPs_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 NumOfNSPs )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Result_MonitorScanResult_AvailableNSPsIdlist_NumOfNSPs_SET( base_ptr, cur_ptr, cur_bitoff, NumOfNSPs );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Result_MonitorScanResult_AvailableNSPsIdlist_NSPID_value_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Result_MonitorScanResult_AvailableNSPsIdlist_NSPID_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Result_MonitorScanResult_FullBSIDArr_NumOfBSIDs_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 NumOfBSIDs )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Result_MonitorScanResult_FullBSIDArr_NumOfBSIDs_SET( base_ptr, cur_ptr, cur_bitoff, NumOfBSIDs );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Result_MonitorScanResult_FullBSIDArr_FullBSID_bsID_bsID_value_SET( UINT8* base_ptr, UINT32 i0, UINT32 i1, UINT32 diff, UINT32 cur_bitoff, UINT8 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Result_MonitorScanResult_FullBSIDArr_FullBSID_bsID_bsID_value_SET( base_ptr, i0, i1, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Result_MonitorScanResult_FullBSIDArr_FullBSID_bsID_Reserved_2_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT16 Reserved_2 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Result_MonitorScanResult_FullBSIDArr_FullBSID_bsID_Reserved_2_SET( base_ptr, i0, cur_ptr, cur_bitoff, Reserved_2 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Result_MonitorScanResult_FullBSIDArr_FullBSID_bsIDmask_bsIDmask_value_SET( UINT8* base_ptr, UINT32 i0, UINT32 i1, UINT32 diff, UINT32 cur_bitoff, UINT8 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Result_MonitorScanResult_FullBSIDArr_FullBSID_bsIDmask_bsIDmask_value_SET( base_ptr, i0, i1, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Result_MonitorScanResult_FullBSIDArr_FullBSID_bsIDmask_Reserved_2_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT16 Reserved_2 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Result_MonitorScanResult_FullBSIDArr_FullBSID_bsIDmask_Reserved_2_SET( base_ptr, i0, cur_ptr, cur_bitoff, Reserved_2 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Ind_BST_FrameNumber_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Ind_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Ind_BST_uSecInFrame_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Ind_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Ind_MonitorScanInd_ScanStartEndInd_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, BM_StartEndInd ScanStartEndInd )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Ind_MonitorScanInd_ScanStartEndInd_SET( base_ptr, cur_ptr, cur_bitoff, ScanStartEndInd );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Ind_MonitorScanInd_Time_wHour_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 wHour )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Ind_MonitorScanInd_Time_wHour_SET( base_ptr, cur_ptr, cur_bitoff, wHour );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Ind_MonitorScanInd_Time_wMinute_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 wMinute )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Ind_MonitorScanInd_Time_wMinute_SET( base_ptr, cur_ptr, cur_bitoff, wMinute );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Ind_MonitorScanInd_Time_wSecond_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 wSecond )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Ind_MonitorScanInd_Time_wSecond_SET( base_ptr, cur_ptr, cur_bitoff, wSecond );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Ind_MonitorScanInd_Time_wMilliseconds_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 wMilliseconds )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Scan_Ind_MonitorScanInd_Time_wMilliseconds_SET( base_ptr, cur_ptr, cur_bitoff, wMilliseconds );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_Session_BST_FrameNumber_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_Session_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_Session_BST_uSecInFrame_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_Session_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_Session_MonitorOMASession_OMAStatusInd_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, BME_OMAStatus OMAStatusInd )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_Session_MonitorOMASession_OMAStatusInd_SET( base_ptr, cur_ptr, cur_bitoff, OMAStatusInd );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_BST_FrameNumber_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_BST_uSecInFrame_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_operatorName_operatorName_BufferByte_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 BufferByte )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_operatorName_operatorName_BufferByte_SET( base_ptr, i0, cur_ptr, cur_bitoff, BufferByte );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_pollingInterval_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 pollingInterval )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_pollingInterval_SET( base_ptr, cur_ptr, cur_bitoff, pollingInterval );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Eaps_NumOfEaps_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 NumOfEaps )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Eaps_NumOfEaps_SET( base_ptr, cur_ptr, cur_bitoff, NumOfEaps );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Eaps_EapList_usePrivacy_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 usePrivacy )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Eaps_EapList_usePrivacy_SET( base_ptr, i0, cur_ptr, cur_bitoff, usePrivacy );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Eaps_EapList_vendorId_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 vendorId )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Eaps_EapList_vendorId_SET( base_ptr, i0, cur_ptr, cur_bitoff, vendorId );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Eaps_EapList_vendorType_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 vendorType )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Eaps_EapList_vendorType_SET( base_ptr, i0, cur_ptr, cur_bitoff, vendorType );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Eaps_EapList_EAPMethod_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, BM_EAPType EAPMethod )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Eaps_EapList_EAPMethod_SET( base_ptr, i0, cur_ptr, cur_bitoff, EAPMethod );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Eaps_EapList_EapId_EapId_BufferByte_SET( UINT8* base_ptr, UINT32 i0, UINT32 i1, UINT32 diff, UINT32 cur_bitoff, UINT8 BufferByte )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Eaps_EapList_EapId_EapId_BufferByte_SET( base_ptr, i0, i1, cur_ptr, cur_bitoff, BufferByte );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Eaps_EapList_provisionedPseudoId_provisionedPseudoId_BufferByte_SET( UINT8* base_ptr, UINT32 i0, UINT32 i1, UINT32 diff, UINT32 cur_bitoff, UINT8 BufferByte )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Eaps_EapList_provisionedPseudoId_provisionedPseudoId_BufferByte_SET( base_ptr, i0, i1, cur_ptr, cur_bitoff, BufferByte );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Eaps_EapList_EapPassword_EapPassword_BufferByte_SET( UINT8* base_ptr, UINT32 i0, UINT32 i1, UINT32 diff, UINT32 cur_bitoff, UINT8 BufferByte )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Eaps_EapList_EapPassword_EapPassword_BufferByte_SET( base_ptr, i0, i1, cur_ptr, cur_bitoff, BufferByte );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Eaps_EapList_Realm_Realm_BufferByte_SET( UINT8* base_ptr, UINT32 i0, UINT32 i1, UINT32 diff, UINT32 cur_bitoff, UINT8 BufferByte )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Eaps_EapList_Realm_Realm_BufferByte_SET( base_ptr, i0, i1, cur_ptr, cur_bitoff, BufferByte );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Eaps_EapList_encaps_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, BM_EAPType encaps )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Eaps_EapList_encaps_SET( base_ptr, i0, cur_ptr, cur_bitoff, encaps );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Capls_NumOfNaps_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 NumOfNaps )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Capls_NumOfNaps_SET( base_ptr, cur_ptr, cur_bitoff, NumOfNaps );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Capls_CaplNapList_priority_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 priority )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Capls_CaplNapList_priority_SET( base_ptr, i0, cur_ptr, cur_bitoff, priority );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Capls_CaplNapList_NapMember_napID_value_SET( UINT8* base_ptr, UINT32 i0, UINT32 i1, UINT32 diff, UINT32 cur_bitoff, UINT8 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Capls_CaplNapList_NapMember_napID_value_SET( base_ptr, i0, i1, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Capls_CaplNapList_NapMember_Reserved_1_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 Reserved_1 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Capls_CaplNapList_NapMember_Reserved_1_SET( base_ptr, i0, cur_ptr, cur_bitoff, Reserved_1 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Rapls_NumOfRoamingPartners_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 NumOfRoamingPartners )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Rapls_NumOfRoamingPartners_SET( base_ptr, cur_ptr, cur_bitoff, NumOfRoamingPartners );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Rapls_RaplList_vNspID_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 vNspID )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Rapls_RaplList_vNspID_SET( base_ptr, i0, cur_ptr, cur_bitoff, vNspID );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Rapls_RaplList_priority_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 priority )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Rapls_RaplList_priority_SET( base_ptr, i0, cur_ptr, cur_bitoff, priority );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Rapls_Any_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, BME_Any Any )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Operator_MonitorOperator_Rapls_Any_SET( base_ptr, cur_ptr, cur_bitoff, Any );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMAParams_BST_FrameNumber_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMAParams_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMAParams_BST_uSecInFrame_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMAParams_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMAParams_MonitorOMAParams_DeviceInfo_manufacturer_manufacturer_BufferByte_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 BufferByte )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMAParams_MonitorOMAParams_DeviceInfo_manufacturer_manufacturer_BufferByte_SET( base_ptr, i0, cur_ptr, cur_bitoff, BufferByte );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMAParams_MonitorOMAParams_DeviceInfo_model_model_BufferByte_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 BufferByte )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMAParams_MonitorOMAParams_DeviceInfo_model_model_BufferByte_SET( base_ptr, i0, cur_ptr, cur_bitoff, BufferByte );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMAParams_MonitorOMAParams_DeviceInfo_devID_devID_BufferByte_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 BufferByte )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMAParams_MonitorOMAParams_DeviceInfo_devID_devID_BufferByte_SET( base_ptr, i0, cur_ptr, cur_bitoff, BufferByte );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMAParams_MonitorOMAParams_DeviceDetails_devType_devType_BufferByte_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 BufferByte )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMAParams_MonitorOMAParams_DeviceDetails_devType_devType_BufferByte_SET( base_ptr, i0, cur_ptr, cur_bitoff, BufferByte );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMAParams_MonitorOMAParams_DeviceDetails_fwVersion_fwVersion_BufferByte_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 BufferByte )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMAParams_MonitorOMAParams_DeviceDetails_fwVersion_fwVersion_BufferByte_SET( base_ptr, i0, cur_ptr, cur_bitoff, BufferByte );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMAParams_MonitorOMAParams_DeviceDetails_swVersion_swVersion_BufferByte_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 BufferByte )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMAParams_MonitorOMAParams_DeviceDetails_swVersion_swVersion_BufferByte_SET( base_ptr, i0, cur_ptr, cur_bitoff, BufferByte );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMAParams_MonitorOMAParams_DeviceDetails_hwVersion_hwVersion_BufferByte_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 BufferByte )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMAParams_MonitorOMAParams_DeviceDetails_hwVersion_hwVersion_BufferByte_SET( base_ptr, i0, cur_ptr, cur_bitoff, BufferByte );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_BST_FrameNumber_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_BST_uSecInFrame_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_RadioModule_LenOfRadioModule_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 LenOfRadioModule )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_RadioModule_LenOfRadioModule_SET( base_ptr, cur_ptr, cur_bitoff, LenOfRadioModule );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_fwVersion_fwVersion_BufferByte_SET( UINT8* base_ptr, UINT32 i0, UINT32 i1, UINT32 diff, UINT32 cur_bitoff, UINT8 BufferByte )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_fwVersion_fwVersion_BufferByte_SET( base_ptr, i0, i1, cur_ptr, cur_bitoff, BufferByte );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_swVersion_swVersion_BufferByte_SET( UINT8* base_ptr, UINT32 i0, UINT32 i1, UINT32 diff, UINT32 cur_bitoff, UINT8 BufferByte )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_swVersion_swVersion_BufferByte_SET( base_ptr, i0, i1, cur_ptr, cur_bitoff, BufferByte );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_hwVersion_hwVersion_BufferByte_SET( UINT8* base_ptr, UINT32 i0, UINT32 i1, UINT32 diff, UINT32 cur_bitoff, UINT8 BufferByte )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_hwVersion_hwVersion_BufferByte_SET( base_ptr, i0, i1, cur_ptr, cur_bitoff, BufferByte );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_manufacturer_manufacturer_BufferByte_SET( UINT8* base_ptr, UINT32 i0, UINT32 i1, UINT32 diff, UINT32 cur_bitoff, UINT8 BufferByte )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_manufacturer_manufacturer_BufferByte_SET( base_ptr, i0, i1, cur_ptr, cur_bitoff, BufferByte );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_model_model_BufferByte_SET( UINT8* base_ptr, UINT32 i0, UINT32 i1, UINT32 diff, UINT32 cur_bitoff, UINT8 BufferByte )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_model_model_BufferByte_SET( base_ptr, i0, i1, cur_ptr, cur_bitoff, BufferByte );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_macAddress_macAddress_BufferByte_SET( UINT8* base_ptr, UINT32 i0, UINT32 i1, UINT32 diff, UINT32 cur_bitoff, UINT8 BufferByte )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_macAddress_macAddress_BufferByte_SET( base_ptr, i0, i1, cur_ptr, cur_bitoff, BufferByte );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_SpLock_lockStatus_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 lockStatus )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_SpLock_lockStatus_SET( base_ptr, i0, cur_ptr, cur_bitoff, lockStatus );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_SpLock_operatorName_operatorName_BufferByte_SET( UINT8* base_ptr, UINT32 i0, UINT32 i1, UINT32 diff, UINT32 cur_bitoff, UINT8 BufferByte )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_SpLock_operatorName_operatorName_BufferByte_SET( base_ptr, i0, i1, cur_ptr, cur_bitoff, BufferByte );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_SpLock_lockMem_lockMem_BufferByte_SET( UINT8* base_ptr, UINT32 i0, UINT32 i1, UINT32 diff, UINT32 cur_bitoff, UINT8 BufferByte )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_SpLock_lockMem_lockMem_BufferByte_SET( base_ptr, i0, i1, cur_ptr, cur_bitoff, BufferByte );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_TerminalEquipment_devType_devType_BufferByte_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 BufferByte )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_TerminalEquipment_devType_devType_BufferByte_SET( base_ptr, i0, cur_ptr, cur_bitoff, BufferByte );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_TerminalEquipment_devID_devID_BufferByte_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 BufferByte )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_TerminalEquipment_devID_devID_BufferByte_SET( base_ptr, i0, cur_ptr, cur_bitoff, BufferByte );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_TerminalEquipment_staticTermEquip_fwVersion_fwVersion_BufferByte_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 BufferByte )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_TerminalEquipment_staticTermEquip_fwVersion_fwVersion_BufferByte_SET( base_ptr, i0, cur_ptr, cur_bitoff, BufferByte );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_TerminalEquipment_staticTermEquip_swVersion_swVersion_BufferByte_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 BufferByte )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_TerminalEquipment_staticTermEquip_swVersion_swVersion_BufferByte_SET( base_ptr, i0, cur_ptr, cur_bitoff, BufferByte );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_TerminalEquipment_staticTermEquip_hwVersion_hwVersion_BufferByte_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 BufferByte )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_TerminalEquipment_staticTermEquip_hwVersion_hwVersion_BufferByte_SET( base_ptr, i0, cur_ptr, cur_bitoff, BufferByte );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_TerminalEquipment_staticTermEquip_manufacturer_manufacturer_BufferByte_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 BufferByte )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_TerminalEquipment_staticTermEquip_manufacturer_manufacturer_BufferByte_SET( base_ptr, i0, cur_ptr, cur_bitoff, BufferByte );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_TerminalEquipment_staticTermEquip_model_model_BufferByte_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 BufferByte )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_WiMAX_Params_MonitorOMAWimaxParams_TerminalEquipment_staticTermEquip_model_model_BufferByte_SET( base_ptr, i0, cur_ptr, cur_bitoff, BufferByte );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_FUMO_Params_BST_FrameNumber_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_FUMO_Params_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_FUMO_Params_BST_uSecInFrame_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_FUMO_Params_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_FUMO_Params_MonitorOMAFumoParams_FUMO_pkgName_pkgName_BufferByte_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 BufferByte )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_FUMO_Params_MonitorOMAFumoParams_FUMO_pkgName_pkgName_BufferByte_SET( base_ptr, i0, cur_ptr, cur_bitoff, BufferByte );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_FUMO_Params_MonitorOMAFumoParams_FUMO_pkgVersion_pkgVersion_BufferByte_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 BufferByte )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_FUMO_Params_MonitorOMAFumoParams_FUMO_pkgVersion_pkgVersion_BufferByte_SET( base_ptr, i0, cur_ptr, cur_bitoff, BufferByte );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_FUMO_Params_MonitorOMAFumoParams_FUMO_downloadPkgURL_downloadPkgURL_BufferByte_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 BufferByte )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_FUMO_Params_MonitorOMAFumoParams_FUMO_downloadPkgURL_downloadPkgURL_BufferByte_SET( base_ptr, i0, cur_ptr, cur_bitoff, BufferByte );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_FUMO_Params_MonitorOMAFumoParams_FUMO_downloadAndUpdatePkgURL_downloadAndUpdatePkgURL_BufferByte_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 BufferByte )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_FUMO_Params_MonitorOMAFumoParams_FUMO_downloadAndUpdatePkgURL_downloadAndUpdatePkgURL_BufferByte_SET( base_ptr, i0, cur_ptr, cur_bitoff, BufferByte );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_FUMO_Params_MonitorOMAFumoParams_FUMO_state_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, DOWNLOAD_STATE state )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_FUMO_Params_MonitorOMAFumoParams_FUMO_state_SET( base_ptr, cur_ptr, cur_bitoff, state );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_FUMO_Params_MonitorOMAFumoParams_FUMO_fIsAllocated_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 fIsAllocated )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_OMA_FUMO_Params_MonitorOMAFumoParams_FUMO_fIsAllocated_SET( base_ptr, cur_ptr, cur_bitoff, fIsAllocated );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_NAI_BST_FrameNumber_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_NAI_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_NAI_BST_uSecInFrame_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_NAI_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_NAI_MonitorNAI_NAISize_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 NAISize )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_NAI_MonitorNAI_NAISize_SET( base_ptr, cur_ptr, cur_bitoff, NAISize );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_NAI_MonitorNAI_NAI_BufferByte_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 BufferByte )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_NAI_MonitorNAI_NAI_BufferByte_SET( base_ptr, i0, cur_ptr, cur_bitoff, BufferByte );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_ActivationStatusChange_BST_FrameNumber_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_ActivationStatusChange_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_ActivationStatusChange_BST_uSecInFrame_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_ActivationStatusChange_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_ActivationStatusChange_MonitorActivationStatusChange_ActivationStatusInd_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 ActivationStatusInd )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_ActivationStatusChange_MonitorActivationStatusChange_ActivationStatusInd_SET( base_ptr, cur_ptr, cur_bitoff, ActivationStatusInd );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_MCP_BST_FrameNumber_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_MCP_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_MCP_BST_uSecInFrame_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_MCP_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_MCP_MonitorMCP_LinkLossInd_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, BME_LinkLossInd LinkLossInd )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_MCP_MonitorMCP_LinkLossInd_SET( base_ptr, cur_ptr, cur_bitoff, LinkLossInd );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_MCP_MonitorMCP_ChannelInfoArray_NumOfChannels_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 NumOfChannels )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_MCP_MonitorMCP_ChannelInfoArray_NumOfChannels_SET( base_ptr, cur_ptr, cur_bitoff, NumOfChannels );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_MCP_MonitorMCP_ChannelInfoArray_Channels_frequency_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 frequency )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_MCP_MonitorMCP_ChannelInfoArray_Channels_frequency_SET( base_ptr, i0, cur_ptr, cur_bitoff, frequency );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_MCP_MonitorMCP_ChannelInfoArray_Channels_bw_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, BME_BW bw )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_MCP_MonitorMCP_ChannelInfoArray_Channels_bw_SET( base_ptr, i0, cur_ptr, cur_bitoff, bw );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_MCP_MonitorMCP_ChannelInfoArray_Channels_fft_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, BME_FFT fft )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_MCP_MonitorMCP_ChannelInfoArray_Channels_fft_SET( base_ptr, i0, cur_ptr, cur_bitoff, fft );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_MCP_MonitorMCP_ChannelInfoArray_Channels_Preambles_Preambles_value_SET( UINT8* base_ptr, UINT32 i0, UINT32 i1, UINT32 diff, UINT32 cur_bitoff, UINT8 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_MCP_MonitorMCP_ChannelInfoArray_Channels_Preambles_Preambles_value_SET( base_ptr, i0, i1, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_MCP_MonitorMCP_ChannelInfoArray_Channels_Preambles_Reserved_1_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 Reserved_1 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_MCP_MonitorMCP_ChannelInfoArray_Channels_Preambles_Reserved_1_SET( base_ptr, i0, cur_ptr, cur_bitoff, Reserved_1 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Installation_Ind_BST_FrameNumber_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Installation_Ind_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Installation_Ind_BST_uSecInFrame_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Installation_Ind_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Installation_Ind_MonitorInstallationInd_MonitorInstallingInd_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, BME_MonitorInstallingInd MonitorInstallingInd )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Installation_Ind_MonitorInstallationInd_MonitorInstallingInd_SET( base_ptr, cur_ptr, cur_bitoff, MonitorInstallingInd );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_BST_FrameNumber_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_BST_uSecInFrame_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_MonitorRecentDiscoverNap_NapMember_napID_value_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_MonitorRecentDiscoverNap_NapMember_napID_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_MonitorRecentDiscoverNap_NapMember_Reserved_1_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 Reserved_1 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_MonitorRecentDiscoverNap_NapMember_Reserved_1_SET( base_ptr, cur_ptr, cur_bitoff, Reserved_1 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_MonitorRecentDiscoverNap_ChannelInfoArray_NumOfChannels_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 NumOfChannels )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_MonitorRecentDiscoverNap_ChannelInfoArray_NumOfChannels_SET( base_ptr, cur_ptr, cur_bitoff, NumOfChannels );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_MonitorRecentDiscoverNap_ChannelInfoArray_Channels_frequency_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 frequency )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_MonitorRecentDiscoverNap_ChannelInfoArray_Channels_frequency_SET( base_ptr, i0, cur_ptr, cur_bitoff, frequency );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_MonitorRecentDiscoverNap_ChannelInfoArray_Channels_bw_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, BME_BW bw )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_MonitorRecentDiscoverNap_ChannelInfoArray_Channels_bw_SET( base_ptr, i0, cur_ptr, cur_bitoff, bw );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_MonitorRecentDiscoverNap_ChannelInfoArray_Channels_fft_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, BME_FFT fft )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_MonitorRecentDiscoverNap_ChannelInfoArray_Channels_fft_SET( base_ptr, i0, cur_ptr, cur_bitoff, fft );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_MonitorRecentDiscoverNap_ChannelInfoArray_Channels_Preambles_Preambles_value_SET( UINT8* base_ptr, UINT32 i0, UINT32 i1, UINT32 diff, UINT32 cur_bitoff, UINT8 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_MonitorRecentDiscoverNap_ChannelInfoArray_Channels_Preambles_Preambles_value_SET( base_ptr, i0, i1, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_MonitorRecentDiscoverNap_ChannelInfoArray_Channels_Preambles_Reserved_1_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 Reserved_1 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_MonitorRecentDiscoverNap_ChannelInfoArray_Channels_Preambles_Reserved_1_SET( base_ptr, i0, cur_ptr, cur_bitoff, Reserved_1 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_MonitorRecentDiscoverNap_bsID_bsID_value_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_MonitorRecentDiscoverNap_bsID_bsID_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_MonitorRecentDiscoverNap_bsID_Reserved_2_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 Reserved_2 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Recent_Discover_Nap_MonitorRecentDiscoverNap_bsID_Reserved_2_SET( base_ptr, cur_ptr, cur_bitoff, Reserved_2 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Selected_Channel_BST_FrameNumber_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 FrameNumber )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Selected_Channel_BST_FrameNumber_SET( base_ptr, cur_ptr, cur_bitoff, FrameNumber );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Selected_Channel_BST_uSecInFrame_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 uSecInFrame )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Selected_Channel_BST_uSecInFrame_SET( base_ptr, cur_ptr, cur_bitoff, uSecInFrame );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Selected_Channel_MonitorSelectedChannel_ChannelInfoArray_NumOfChannels_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 NumOfChannels )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Selected_Channel_MonitorSelectedChannel_ChannelInfoArray_NumOfChannels_SET( base_ptr, cur_ptr, cur_bitoff, NumOfChannels );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Selected_Channel_MonitorSelectedChannel_ChannelInfoArray_Channels_frequency_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT32 frequency )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Selected_Channel_MonitorSelectedChannel_ChannelInfoArray_Channels_frequency_SET( base_ptr, i0, cur_ptr, cur_bitoff, frequency );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Selected_Channel_MonitorSelectedChannel_ChannelInfoArray_Channels_bw_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, BME_BW bw )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Selected_Channel_MonitorSelectedChannel_ChannelInfoArray_Channels_bw_SET( base_ptr, i0, cur_ptr, cur_bitoff, bw );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Selected_Channel_MonitorSelectedChannel_ChannelInfoArray_Channels_fft_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, BME_FFT fft )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Selected_Channel_MonitorSelectedChannel_ChannelInfoArray_Channels_fft_SET( base_ptr, i0, cur_ptr, cur_bitoff, fft );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Selected_Channel_MonitorSelectedChannel_ChannelInfoArray_Channels_Preambles_Preambles_value_SET( UINT8* base_ptr, UINT32 i0, UINT32 i1, UINT32 diff, UINT32 cur_bitoff, UINT8 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Selected_Channel_MonitorSelectedChannel_ChannelInfoArray_Channels_Preambles_Preambles_value_SET( base_ptr, i0, i1, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Selected_Channel_MonitorSelectedChannel_ChannelInfoArray_Channels_Preambles_Reserved_1_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 Reserved_1 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_MonitorBuffer_List_CURRENT_L3L4_Monitor_Selected_Channel_MonitorSelectedChannel_ChannelInfoArray_Channels_Preambles_Reserved_1_SET( base_ptr, i0, cur_ptr, cur_bitoff, Reserved_1 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_Header_Type_SET( UINT8* base_ptr, UINT32 opcode )
{
	BM_MonitorBuffer_Header_Type_SET( base_ptr, opcode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_Header_Version_SET( UINT8* base_ptr, UINT16 version )
{
	BM_MonitorBuffer_Header_Version_SET( base_ptr, version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_Header_Accessibility_SET( UINT8* base_ptr, UINT16 accessibility )
{
	BM_MonitorBuffer_Header_Accessibility_SET( base_ptr, accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_Header_Status_SET( UINT8* base_ptr, UINT16 status )
{
	BM_MonitorBuffer_Header_Status_SET( base_ptr, status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MonitorBuffer_Header_Length_SET( UINT8* base_ptr, UINT32 len )
{
	BM_MonitorBuffer_Header_Length_SET( base_ptr, len );
}
