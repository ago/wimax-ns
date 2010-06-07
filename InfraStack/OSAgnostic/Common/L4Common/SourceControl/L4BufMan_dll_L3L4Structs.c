
/****************************************************************************
*
* Auto generated file
* Version XXX
* Compliant with XXX.bm version XXX
* 3/22/2009 10:33:51 AM
*
*****************************************************************************/


#include "L4BufMan_dll_L3L4Structs.h"



L4BUFMANDLL_API void L4BUFMANDLL_BM_GetL4MVersion_Header_Version_GET( UINT8* base_ptr, UINT16* version )
{
	BM_GetL4MVersion_Header_Version_GET( base_ptr, *version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetL4MVersion_Header_Accessibility_GET( UINT8* base_ptr, UINT16* accessibility )
{
	BM_GetL4MVersion_Header_Accessibility_GET( base_ptr, *accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetL4MVersion_Header_Status_GET( UINT8* base_ptr, UINT16* status )
{
	BM_GetL4MVersion_Header_Status_GET( base_ptr, *status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetL4MVersion_Header_Length_GET( UINT8* base_ptr, UINT32* listSize )
{
	BM_GetL4MVersion_Header_Length_GET( base_ptr, *listSize );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetL4MVersion_List_GET_FIRST( UINT8* base_ptr, UINT32* out_diff, UINT32* out_cur_bitoff )
{
	UINT8* out_cur_ptr = base_ptr;
	BM_GetL4MVersion_List_GET_FIRST( base_ptr, out_cur_ptr, *out_cur_bitoff );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetL4MVersion_List_GET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetL4MVersion_List_GET_TYPE( cur_ptr, cur_bitoff, *type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetL4MVersion_List_GET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_length, UINT32 err )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetL4MVersion_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, *out_length, err );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetL4MVersion_List_CURRENT_L4MVersion_VersionMajor_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* VersionMajor )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetL4MVersion_List_CURRENT_L4MVersion_VersionMajor_GET( base_ptr, cur_ptr, cur_bitoff, *VersionMajor );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetL4MVersion_List_CURRENT_L4MVersion_VersionMinor_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* VersionMinor )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetL4MVersion_List_CURRENT_L4MVersion_VersionMinor_GET( base_ptr, cur_ptr, cur_bitoff, *VersionMinor );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetL4MVersion_List_CURRENT_L4MVersion_VersionBranch_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* VersionBranch )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetL4MVersion_List_CURRENT_L4MVersion_VersionBranch_GET( base_ptr, cur_ptr, cur_bitoff, *VersionBranch );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetL4MVersion_List_CURRENT_L4MVersion_Reserved2_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* Reserved2 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetL4MVersion_List_CURRENT_L4MVersion_Reserved2_GET( base_ptr, cur_ptr, cur_bitoff, *Reserved2 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetL4MVersion_List_CURRENT_L4MProductionVersion_VersionMajor_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* VersionMajor )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetL4MVersion_List_CURRENT_L4MProductionVersion_VersionMajor_GET( base_ptr, cur_ptr, cur_bitoff, *VersionMajor );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetL4MVersion_List_CURRENT_L4MProductionVersion_VersionMinor_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* VersionMinor )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetL4MVersion_List_CURRENT_L4MProductionVersion_VersionMinor_GET( base_ptr, cur_ptr, cur_bitoff, *VersionMinor );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetL4MVersion_List_CURRENT_L4MProductionVersion_VersionBranch_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* VersionBranch )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetL4MVersion_List_CURRENT_L4MProductionVersion_VersionBranch_GET( base_ptr, cur_ptr, cur_bitoff, *VersionBranch );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetL4MVersion_List_CURRENT_L4MProductionVersion_Reserved2_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* Reserved2 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetL4MVersion_List_CURRENT_L4MProductionVersion_Reserved2_GET( base_ptr, cur_ptr, cur_bitoff, *Reserved2 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetL4MVersion_List_CURRENT_L4MDnDVersion_VersionMajor_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* VersionMajor )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetL4MVersion_List_CURRENT_L4MDnDVersion_VersionMajor_GET( base_ptr, cur_ptr, cur_bitoff, *VersionMajor );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetL4MVersion_List_CURRENT_L4MDnDVersion_VersionMinor_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* VersionMinor )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetL4MVersion_List_CURRENT_L4MDnDVersion_VersionMinor_GET( base_ptr, cur_ptr, cur_bitoff, *VersionMinor );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetL4MVersion_List_CURRENT_L4MDnDVersion_VersionBranch_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* VersionBranch )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetL4MVersion_List_CURRENT_L4MDnDVersion_VersionBranch_GET( base_ptr, cur_ptr, cur_bitoff, *VersionBranch );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetL4MVersion_List_CURRENT_L4MDnDVersion_Reserved2_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* Reserved2 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetL4MVersion_List_CURRENT_L4MDnDVersion_Reserved2_GET( base_ptr, cur_ptr, cur_bitoff, *Reserved2 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetL4MVersion_List_GET_NEXT( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_diff, UINT32* out_cur_bitoff, UINT32 err )
{
	UINT8* out_cur_ptr = base_ptr;
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetL4MVersion_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, out_cur_ptr, *out_cur_bitoff, err );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetL4MVersion_List_SET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetL4MVersion_List_SET_TYPE( cur_ptr, cur_bitoff, type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetL4MVersion_List_SET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 lenOfLen, UINT32 length )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	lenOfLen = 2;
	BM_GetL4MVersion_List_SET_LENGTH( cur_ptr, cur_bitoff, lenOfLen, length );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetL4MVersion_List_CURRENT_L4MVersion_VersionMajor_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 VersionMajor )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetL4MVersion_List_CURRENT_L4MVersion_VersionMajor_SET( base_ptr, cur_ptr, cur_bitoff, VersionMajor );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetL4MVersion_List_CURRENT_L4MVersion_VersionMinor_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 VersionMinor )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetL4MVersion_List_CURRENT_L4MVersion_VersionMinor_SET( base_ptr, cur_ptr, cur_bitoff, VersionMinor );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetL4MVersion_List_CURRENT_L4MVersion_VersionBranch_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 VersionBranch )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetL4MVersion_List_CURRENT_L4MVersion_VersionBranch_SET( base_ptr, cur_ptr, cur_bitoff, VersionBranch );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetL4MVersion_List_CURRENT_L4MVersion_Reserved2_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 Reserved2 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetL4MVersion_List_CURRENT_L4MVersion_Reserved2_SET( base_ptr, cur_ptr, cur_bitoff, Reserved2 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetL4MVersion_List_CURRENT_L4MProductionVersion_VersionMajor_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 VersionMajor )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetL4MVersion_List_CURRENT_L4MProductionVersion_VersionMajor_SET( base_ptr, cur_ptr, cur_bitoff, VersionMajor );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetL4MVersion_List_CURRENT_L4MProductionVersion_VersionMinor_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 VersionMinor )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetL4MVersion_List_CURRENT_L4MProductionVersion_VersionMinor_SET( base_ptr, cur_ptr, cur_bitoff, VersionMinor );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetL4MVersion_List_CURRENT_L4MProductionVersion_VersionBranch_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 VersionBranch )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetL4MVersion_List_CURRENT_L4MProductionVersion_VersionBranch_SET( base_ptr, cur_ptr, cur_bitoff, VersionBranch );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetL4MVersion_List_CURRENT_L4MProductionVersion_Reserved2_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 Reserved2 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetL4MVersion_List_CURRENT_L4MProductionVersion_Reserved2_SET( base_ptr, cur_ptr, cur_bitoff, Reserved2 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetL4MVersion_List_CURRENT_L4MDnDVersion_VersionMajor_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 VersionMajor )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetL4MVersion_List_CURRENT_L4MDnDVersion_VersionMajor_SET( base_ptr, cur_ptr, cur_bitoff, VersionMajor );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetL4MVersion_List_CURRENT_L4MDnDVersion_VersionMinor_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 VersionMinor )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetL4MVersion_List_CURRENT_L4MDnDVersion_VersionMinor_SET( base_ptr, cur_ptr, cur_bitoff, VersionMinor );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetL4MVersion_List_CURRENT_L4MDnDVersion_VersionBranch_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 VersionBranch )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetL4MVersion_List_CURRENT_L4MDnDVersion_VersionBranch_SET( base_ptr, cur_ptr, cur_bitoff, VersionBranch );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetL4MVersion_List_CURRENT_L4MDnDVersion_Reserved2_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 Reserved2 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetL4MVersion_List_CURRENT_L4MDnDVersion_Reserved2_SET( base_ptr, cur_ptr, cur_bitoff, Reserved2 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetL4MVersion_Header_Type_SET( UINT8* base_ptr, UINT32 opcode )
{
	BM_GetL4MVersion_Header_Type_SET( base_ptr, opcode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetL4MVersion_Header_Version_SET( UINT8* base_ptr, UINT16 version )
{
	BM_GetL4MVersion_Header_Version_SET( base_ptr, version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetL4MVersion_Header_Accessibility_SET( UINT8* base_ptr, UINT16 accessibility )
{
	BM_GetL4MVersion_Header_Accessibility_SET( base_ptr, accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetL4MVersion_Header_Status_SET( UINT8* base_ptr, UINT16 status )
{
	BM_GetL4MVersion_Header_Status_SET( base_ptr, status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetL4MVersion_Header_Length_SET( UINT8* base_ptr, UINT32 len )
{
	BM_GetL4MVersion_Header_Length_SET( base_ptr, len );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportKeyRequest_Header_Version_GET( UINT8* base_ptr, UINT16* version )
{
	BM_ReportKeyRequest_Header_Version_GET( base_ptr, *version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportKeyRequest_Header_Accessibility_GET( UINT8* base_ptr, UINT16* accessibility )
{
	BM_ReportKeyRequest_Header_Accessibility_GET( base_ptr, *accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportKeyRequest_Header_Status_GET( UINT8* base_ptr, UINT16* status )
{
	BM_ReportKeyRequest_Header_Status_GET( base_ptr, *status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportKeyRequest_Header_Type_SET( UINT8* base_ptr, UINT32 opcode )
{
	BM_ReportKeyRequest_Header_Type_SET( base_ptr, opcode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportKeyRequest_Header_Version_SET( UINT8* base_ptr, UINT16 version )
{
	BM_ReportKeyRequest_Header_Version_SET( base_ptr, version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportKeyRequest_Header_Accessibility_SET( UINT8* base_ptr, UINT16 accessibility )
{
	BM_ReportKeyRequest_Header_Accessibility_SET( base_ptr, accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportKeyRequest_Header_Status_SET( UINT8* base_ptr, UINT16 status )
{
	BM_ReportKeyRequest_Header_Status_SET( base_ptr, status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportKeyRequest_Header_Length_SET( UINT8* base_ptr, UINT32 len )
{
	BM_ReportKeyRequest_Header_Length_SET( base_ptr, len );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetScanParameters_Header_Version_GET( UINT8* base_ptr, UINT16* version )
{
	BM_SetScanParameters_Header_Version_GET( base_ptr, *version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetScanParameters_Header_Accessibility_GET( UINT8* base_ptr, UINT16* accessibility )
{
	BM_SetScanParameters_Header_Accessibility_GET( base_ptr, *accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetScanParameters_Header_Status_GET( UINT8* base_ptr, UINT16* status )
{
	BM_SetScanParameters_Header_Status_GET( base_ptr, *status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetScanParameters_Header_Length_GET( UINT8* base_ptr, UINT32* listSize )
{
	BM_SetScanParameters_Header_Length_GET( base_ptr, *listSize );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetScanParameters_List_GET_FIRST( UINT8* base_ptr, UINT32* out_diff, UINT32* out_cur_bitoff )
{
	UINT8* out_cur_ptr = base_ptr;
	BM_SetScanParameters_List_GET_FIRST( base_ptr, out_cur_ptr, *out_cur_bitoff );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetScanParameters_List_GET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetScanParameters_List_GET_TYPE( cur_ptr, cur_bitoff, *type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetScanParameters_List_GET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_length, UINT32 err )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetScanParameters_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, *out_length, err );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetScanParameters_List_CURRENT_ChannelInfoArray_Frequency_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* Frequency )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetScanParameters_List_CURRENT_ChannelInfoArray_Frequency_GET( base_ptr, cur_ptr, cur_bitoff, *Frequency );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetScanParameters_List_CURRENT_ChannelInfoArray_ChannelId_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* ChannelId )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetScanParameters_List_CURRENT_ChannelInfoArray_ChannelId_GET( base_ptr, cur_ptr, cur_bitoff, *ChannelId );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetScanParameters_List_CURRENT_ChannelInfoArray_Bandwidth_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* Bandwidth )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetScanParameters_List_CURRENT_ChannelInfoArray_Bandwidth_GET( base_ptr, cur_ptr, cur_bitoff, *Bandwidth );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetScanParameters_List_CURRENT_ChannelInfoArray_Fft_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* Fft )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetScanParameters_List_CURRENT_ChannelInfoArray_Fft_GET( base_ptr, cur_ptr, cur_bitoff, *Fft );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetScanParameters_List_CURRENT_ChannelInfoArray_Preambles_value_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetScanParameters_List_CURRENT_ChannelInfoArray_Preambles_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetScanParameters_List_CURRENT_ChannelInfoArray_Reserved_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* Reserved )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetScanParameters_List_CURRENT_ChannelInfoArray_Reserved_GET( base_ptr, cur_ptr, cur_bitoff, *Reserved );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetScanParameters_List_CURRENT_ScanPolicy_value_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetScanParameters_List_CURRENT_ScanPolicy_value_GET( base_ptr, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetScanParameters_List_GET_NEXT( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_diff, UINT32* out_cur_bitoff, UINT32 err )
{
	UINT8* out_cur_ptr = base_ptr;
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetScanParameters_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, out_cur_ptr, *out_cur_bitoff, err );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetScanParameters_List_SET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetScanParameters_List_SET_TYPE( cur_ptr, cur_bitoff, type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetScanParameters_List_SET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 lenOfLen, UINT32 length )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	lenOfLen = 2;
	BM_SetScanParameters_List_SET_LENGTH( cur_ptr, cur_bitoff, lenOfLen, length );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetScanParameters_List_CURRENT_ChannelInfoArray_Frequency_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 Frequency )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetScanParameters_List_CURRENT_ChannelInfoArray_Frequency_SET( base_ptr, cur_ptr, cur_bitoff, Frequency );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetScanParameters_List_CURRENT_ChannelInfoArray_ChannelId_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 ChannelId )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetScanParameters_List_CURRENT_ChannelInfoArray_ChannelId_SET( base_ptr, cur_ptr, cur_bitoff, ChannelId );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetScanParameters_List_CURRENT_ChannelInfoArray_Bandwidth_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 Bandwidth )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetScanParameters_List_CURRENT_ChannelInfoArray_Bandwidth_SET( base_ptr, cur_ptr, cur_bitoff, Bandwidth );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetScanParameters_List_CURRENT_ChannelInfoArray_Fft_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 Fft )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetScanParameters_List_CURRENT_ChannelInfoArray_Fft_SET( base_ptr, cur_ptr, cur_bitoff, Fft );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetScanParameters_List_CURRENT_ChannelInfoArray_Preambles_value_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetScanParameters_List_CURRENT_ChannelInfoArray_Preambles_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetScanParameters_List_CURRENT_ChannelInfoArray_Reserved_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 Reserved )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetScanParameters_List_CURRENT_ChannelInfoArray_Reserved_SET( base_ptr, cur_ptr, cur_bitoff, Reserved );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetScanParameters_List_CURRENT_ScanPolicy_value_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetScanParameters_List_CURRENT_ScanPolicy_value_SET( base_ptr, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetScanParameters_Header_Type_SET( UINT8* base_ptr, UINT32 opcode )
{
	BM_SetScanParameters_Header_Type_SET( base_ptr, opcode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetScanParameters_Header_Version_SET( UINT8* base_ptr, UINT16 version )
{
	BM_SetScanParameters_Header_Version_SET( base_ptr, version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetScanParameters_Header_Accessibility_SET( UINT8* base_ptr, UINT16 accessibility )
{
	BM_SetScanParameters_Header_Accessibility_SET( base_ptr, accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetScanParameters_Header_Status_SET( UINT8* base_ptr, UINT16 status )
{
	BM_SetScanParameters_Header_Status_SET( base_ptr, status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetScanParameters_Header_Length_SET( UINT8* base_ptr, UINT32 len )
{
	BM_SetScanParameters_Header_Length_SET( base_ptr, len );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_EnterPowerSaveCommand_Header_Version_GET( UINT8* base_ptr, UINT16* version )
{
	BM_EnterPowerSaveCommand_Header_Version_GET( base_ptr, *version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_EnterPowerSaveCommand_Header_Accessibility_GET( UINT8* base_ptr, UINT16* accessibility )
{
	BM_EnterPowerSaveCommand_Header_Accessibility_GET( base_ptr, *accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_EnterPowerSaveCommand_Header_Status_GET( UINT8* base_ptr, UINT16* status )
{
	BM_EnterPowerSaveCommand_Header_Status_GET( base_ptr, *status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_EnterPowerSaveCommand_Header_Length_GET( UINT8* base_ptr, UINT32* listSize )
{
	BM_EnterPowerSaveCommand_Header_Length_GET( base_ptr, *listSize );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_EnterPowerSaveCommand_List_GET_FIRST( UINT8* base_ptr, UINT32* out_diff, UINT32* out_cur_bitoff )
{
	UINT8* out_cur_ptr = base_ptr;
	BM_EnterPowerSaveCommand_List_GET_FIRST( base_ptr, out_cur_ptr, *out_cur_bitoff );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_EnterPowerSaveCommand_List_GET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_EnterPowerSaveCommand_List_GET_TYPE( cur_ptr, cur_bitoff, *type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_EnterPowerSaveCommand_List_GET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_length, UINT32 err )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_EnterPowerSaveCommand_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, *out_length, err );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_EnterPowerSaveCommand_List_CURRENT_WakeupMode_value_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_EnterPowerSaveCommand_List_CURRENT_WakeupMode_value_GET( base_ptr, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_EnterPowerSaveCommand_List_GET_NEXT( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_diff, UINT32* out_cur_bitoff, UINT32 err )
{
	UINT8* out_cur_ptr = base_ptr;
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_EnterPowerSaveCommand_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, out_cur_ptr, *out_cur_bitoff, err );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_EnterPowerSaveCommand_List_SET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_EnterPowerSaveCommand_List_SET_TYPE( cur_ptr, cur_bitoff, type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_EnterPowerSaveCommand_List_SET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 lenOfLen, UINT32 length )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	lenOfLen = 2;
	BM_EnterPowerSaveCommand_List_SET_LENGTH( cur_ptr, cur_bitoff, lenOfLen, length );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_EnterPowerSaveCommand_List_CURRENT_WakeupMode_value_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_EnterPowerSaveCommand_List_CURRENT_WakeupMode_value_SET( base_ptr, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_EnterPowerSaveCommand_Header_Type_SET( UINT8* base_ptr, UINT32 opcode )
{
	BM_EnterPowerSaveCommand_Header_Type_SET( base_ptr, opcode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_EnterPowerSaveCommand_Header_Version_SET( UINT8* base_ptr, UINT16 version )
{
	BM_EnterPowerSaveCommand_Header_Version_SET( base_ptr, version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_EnterPowerSaveCommand_Header_Accessibility_SET( UINT8* base_ptr, UINT16 accessibility )
{
	BM_EnterPowerSaveCommand_Header_Accessibility_SET( base_ptr, accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_EnterPowerSaveCommand_Header_Status_SET( UINT8* base_ptr, UINT16 status )
{
	BM_EnterPowerSaveCommand_Header_Status_SET( base_ptr, status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_EnterPowerSaveCommand_Header_Length_SET( UINT8* base_ptr, UINT32 len )
{
	BM_EnterPowerSaveCommand_Header_Length_SET( base_ptr, len );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_TLSOperationRequest_Header_Version_GET( UINT8* base_ptr, UINT16* version )
{
	BM_TLSOperationRequest_Header_Version_GET( base_ptr, *version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_TLSOperationRequest_Header_Accessibility_GET( UINT8* base_ptr, UINT16* accessibility )
{
	BM_TLSOperationRequest_Header_Accessibility_GET( base_ptr, *accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_TLSOperationRequest_Header_Status_GET( UINT8* base_ptr, UINT16* status )
{
	BM_TLSOperationRequest_Header_Status_GET( base_ptr, *status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_TLSOperationRequest_Header_Length_GET( UINT8* base_ptr, UINT32* listSize )
{
	BM_TLSOperationRequest_Header_Length_GET( base_ptr, *listSize );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_TLSOperationRequest_List_GET_FIRST( UINT8* base_ptr, UINT32* out_diff, UINT32* out_cur_bitoff )
{
	UINT8* out_cur_ptr = base_ptr;
	BM_TLSOperationRequest_List_GET_FIRST( base_ptr, out_cur_ptr, *out_cur_bitoff );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_TLSOperationRequest_List_GET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_TLSOperationRequest_List_GET_TYPE( cur_ptr, cur_bitoff, *type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_TLSOperationRequest_List_GET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_length, UINT32 err )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_TLSOperationRequest_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, *out_length, err );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_TLSOperationRequest_List_CURRENT_Common_Operation_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* Operation )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_TLSOperationRequest_List_CURRENT_Common_Operation_GET( base_ptr, cur_ptr, cur_bitoff, *Operation );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_TLSOperationRequest_List_CURRENT_Common_LParameter1_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* LParameter1 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_TLSOperationRequest_List_CURRENT_Common_LParameter1_GET( base_ptr, cur_ptr, cur_bitoff, *LParameter1 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_TLSOperationRequest_List_CURRENT_Common_LParameter2_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* LParameter2 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_TLSOperationRequest_List_CURRENT_Common_LParameter2_GET( base_ptr, cur_ptr, cur_bitoff, *LParameter2 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_TLSOperationRequest_List_CURRENT_Common_Context_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* Context )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_TLSOperationRequest_List_CURRENT_Common_Context_GET( base_ptr, cur_ptr, cur_bitoff, *Context );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_TLSOperationRequest_List_CURRENT_Common_Connection_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* Connection )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_TLSOperationRequest_List_CURRENT_Common_Connection_GET( base_ptr, cur_ptr, cur_bitoff, *Connection );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_TLSOperationRequest_List_CURRENT_ExchangeBuffer_ActualLen_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* ActualLen )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_TLSOperationRequest_List_CURRENT_ExchangeBuffer_ActualLen_GET( base_ptr, cur_ptr, cur_bitoff, *ActualLen );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_TLSOperationRequest_List_CURRENT_ExchangeBuffer_BufferArr_value_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_TLSOperationRequest_List_CURRENT_ExchangeBuffer_BufferArr_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_TLSOperationRequest_List_CURRENT_AppOutputBuffer_ActualLen_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* ActualLen )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_TLSOperationRequest_List_CURRENT_AppOutputBuffer_ActualLen_GET( base_ptr, cur_ptr, cur_bitoff, *ActualLen );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_TLSOperationRequest_List_CURRENT_AppOutputBuffer_BufferArr_value_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_TLSOperationRequest_List_CURRENT_AppOutputBuffer_BufferArr_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_TLSOperationRequest_List_GET_NEXT( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_diff, UINT32* out_cur_bitoff, UINT32 err )
{
	UINT8* out_cur_ptr = base_ptr;
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_TLSOperationRequest_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, out_cur_ptr, *out_cur_bitoff, err );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_TLSOperationRequest_List_SET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_TLSOperationRequest_List_SET_TYPE( cur_ptr, cur_bitoff, type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_TLSOperationRequest_List_SET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 lenOfLen, UINT32 length )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	lenOfLen = 2;
	BM_TLSOperationRequest_List_SET_LENGTH( cur_ptr, cur_bitoff, lenOfLen, length );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_TLSOperationRequest_List_CURRENT_Common_Operation_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 Operation )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_TLSOperationRequest_List_CURRENT_Common_Operation_SET( base_ptr, cur_ptr, cur_bitoff, Operation );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_TLSOperationRequest_List_CURRENT_Common_LParameter1_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 LParameter1 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_TLSOperationRequest_List_CURRENT_Common_LParameter1_SET( base_ptr, cur_ptr, cur_bitoff, LParameter1 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_TLSOperationRequest_List_CURRENT_Common_LParameter2_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 LParameter2 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_TLSOperationRequest_List_CURRENT_Common_LParameter2_SET( base_ptr, cur_ptr, cur_bitoff, LParameter2 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_TLSOperationRequest_List_CURRENT_Common_Context_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 Context )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_TLSOperationRequest_List_CURRENT_Common_Context_SET( base_ptr, cur_ptr, cur_bitoff, Context );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_TLSOperationRequest_List_CURRENT_Common_Connection_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 Connection )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_TLSOperationRequest_List_CURRENT_Common_Connection_SET( base_ptr, cur_ptr, cur_bitoff, Connection );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_TLSOperationRequest_List_CURRENT_ExchangeBuffer_ActualLen_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 ActualLen )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_TLSOperationRequest_List_CURRENT_ExchangeBuffer_ActualLen_SET( base_ptr, cur_ptr, cur_bitoff, ActualLen );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_TLSOperationRequest_List_CURRENT_ExchangeBuffer_BufferArr_value_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_TLSOperationRequest_List_CURRENT_ExchangeBuffer_BufferArr_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_TLSOperationRequest_List_CURRENT_AppOutputBuffer_ActualLen_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 ActualLen )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_TLSOperationRequest_List_CURRENT_AppOutputBuffer_ActualLen_SET( base_ptr, cur_ptr, cur_bitoff, ActualLen );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_TLSOperationRequest_List_CURRENT_AppOutputBuffer_BufferArr_value_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_TLSOperationRequest_List_CURRENT_AppOutputBuffer_BufferArr_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_TLSOperationRequest_Header_Type_SET( UINT8* base_ptr, UINT32 opcode )
{
	BM_TLSOperationRequest_Header_Type_SET( base_ptr, opcode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_TLSOperationRequest_Header_Version_SET( UINT8* base_ptr, UINT16 version )
{
	BM_TLSOperationRequest_Header_Version_SET( base_ptr, version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_TLSOperationRequest_Header_Accessibility_SET( UINT8* base_ptr, UINT16 accessibility )
{
	BM_TLSOperationRequest_Header_Accessibility_SET( base_ptr, accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_TLSOperationRequest_Header_Status_SET( UINT8* base_ptr, UINT16 status )
{
	BM_TLSOperationRequest_Header_Status_SET( base_ptr, status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_TLSOperationRequest_Header_Length_SET( UINT8* base_ptr, UINT32 len )
{
	BM_TLSOperationRequest_Header_Length_SET( base_ptr, len );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_RfControl_Header_Version_GET( UINT8* base_ptr, UINT16* version )
{
	BM_RfControl_Header_Version_GET( base_ptr, *version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_RfControl_Header_Accessibility_GET( UINT8* base_ptr, UINT16* accessibility )
{
	BM_RfControl_Header_Accessibility_GET( base_ptr, *accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_RfControl_Header_Status_GET( UINT8* base_ptr, UINT16* status )
{
	BM_RfControl_Header_Status_GET( base_ptr, *status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_RfControl_Header_Length_GET( UINT8* base_ptr, UINT32* listSize )
{
	BM_RfControl_Header_Length_GET( base_ptr, *listSize );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_RfControl_List_GET_FIRST( UINT8* base_ptr, UINT32* out_diff, UINT32* out_cur_bitoff )
{
	UINT8* out_cur_ptr = base_ptr;
	BM_RfControl_List_GET_FIRST( base_ptr, out_cur_ptr, *out_cur_bitoff );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_RfControl_List_GET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_RfControl_List_GET_TYPE( cur_ptr, cur_bitoff, *type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_RfControl_List_GET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_length, UINT32 err )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_RfControl_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, *out_length, err );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_RfControl_List_CURRENT_RfOperation_value_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_RfControl_List_CURRENT_RfOperation_value_GET( base_ptr, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_RfControl_List_GET_NEXT( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_diff, UINT32* out_cur_bitoff, UINT32 err )
{
	UINT8* out_cur_ptr = base_ptr;
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_RfControl_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, out_cur_ptr, *out_cur_bitoff, err );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_RfControl_List_SET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_RfControl_List_SET_TYPE( cur_ptr, cur_bitoff, type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_RfControl_List_SET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 lenOfLen, UINT32 length )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	lenOfLen = 2;
	BM_RfControl_List_SET_LENGTH( cur_ptr, cur_bitoff, lenOfLen, length );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_RfControl_List_CURRENT_RfOperation_value_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_RfControl_List_CURRENT_RfOperation_value_SET( base_ptr, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_RfControl_Header_Type_SET( UINT8* base_ptr, UINT32 opcode )
{
	BM_RfControl_Header_Type_SET( base_ptr, opcode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_RfControl_Header_Version_SET( UINT8* base_ptr, UINT16 version )
{
	BM_RfControl_Header_Version_SET( base_ptr, version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_RfControl_Header_Accessibility_SET( UINT8* base_ptr, UINT16 accessibility )
{
	BM_RfControl_Header_Accessibility_SET( base_ptr, accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_RfControl_Header_Status_SET( UINT8* base_ptr, UINT16 status )
{
	BM_RfControl_Header_Status_SET( base_ptr, status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_RfControl_Header_Length_SET( UINT8* base_ptr, UINT32 len )
{
	BM_RfControl_Header_Length_SET( base_ptr, len );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportEapRestart_Header_Version_GET( UINT8* base_ptr, UINT16* version )
{
	BM_ReportEapRestart_Header_Version_GET( base_ptr, *version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportEapRestart_Header_Accessibility_GET( UINT8* base_ptr, UINT16* accessibility )
{
	BM_ReportEapRestart_Header_Accessibility_GET( base_ptr, *accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportEapRestart_Header_Status_GET( UINT8* base_ptr, UINT16* status )
{
	BM_ReportEapRestart_Header_Status_GET( base_ptr, *status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportEapRestart_Header_Type_SET( UINT8* base_ptr, UINT32 opcode )
{
	BM_ReportEapRestart_Header_Type_SET( base_ptr, opcode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportEapRestart_Header_Version_SET( UINT8* base_ptr, UINT16 version )
{
	BM_ReportEapRestart_Header_Version_SET( base_ptr, version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportEapRestart_Header_Accessibility_SET( UINT8* base_ptr, UINT16 accessibility )
{
	BM_ReportEapRestart_Header_Accessibility_SET( base_ptr, accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportEapRestart_Header_Status_SET( UINT8* base_ptr, UINT16 status )
{
	BM_ReportEapRestart_Header_Status_SET( base_ptr, status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportEapRestart_Header_Length_SET( UINT8* base_ptr, UINT32 len )
{
	BM_ReportEapRestart_Header_Length_SET( base_ptr, len );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportEapRequest_Header_Version_GET( UINT8* base_ptr, UINT16* version )
{
	BM_ReportEapRequest_Header_Version_GET( base_ptr, *version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportEapRequest_Header_Accessibility_GET( UINT8* base_ptr, UINT16* accessibility )
{
	BM_ReportEapRequest_Header_Accessibility_GET( base_ptr, *accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportEapRequest_Header_Status_GET( UINT8* base_ptr, UINT16* status )
{
	BM_ReportEapRequest_Header_Status_GET( base_ptr, *status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportEapRequest_Header_Length_GET( UINT8* base_ptr, UINT32* listSize )
{
	BM_ReportEapRequest_Header_Length_GET( base_ptr, *listSize );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportEapRequest_List_GET_FIRST( UINT8* base_ptr, UINT32* out_diff, UINT32* out_cur_bitoff )
{
	UINT8* out_cur_ptr = base_ptr;
	BM_ReportEapRequest_List_GET_FIRST( base_ptr, out_cur_ptr, *out_cur_bitoff );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportEapRequest_List_GET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportEapRequest_List_GET_TYPE( cur_ptr, cur_bitoff, *type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportEapRequest_List_GET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_length, UINT32 err )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportEapRequest_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, *out_length, err );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportEapRequest_List_CURRENT_EapRequestMessage_ActualLen_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* ActualLen )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportEapRequest_List_CURRENT_EapRequestMessage_ActualLen_GET( base_ptr, cur_ptr, cur_bitoff, *ActualLen );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportEapRequest_List_CURRENT_EapRequestMessage_BufferArr_value_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportEapRequest_List_CURRENT_EapRequestMessage_BufferArr_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportEapRequest_List_GET_NEXT( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_diff, UINT32* out_cur_bitoff, UINT32 err )
{
	UINT8* out_cur_ptr = base_ptr;
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportEapRequest_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, out_cur_ptr, *out_cur_bitoff, err );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportEapRequest_List_SET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportEapRequest_List_SET_TYPE( cur_ptr, cur_bitoff, type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportEapRequest_List_SET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 lenOfLen, UINT32 length )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	lenOfLen = 2;
	BM_ReportEapRequest_List_SET_LENGTH( cur_ptr, cur_bitoff, lenOfLen, length );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportEapRequest_List_CURRENT_EapRequestMessage_ActualLen_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 ActualLen )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportEapRequest_List_CURRENT_EapRequestMessage_ActualLen_SET( base_ptr, cur_ptr, cur_bitoff, ActualLen );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportEapRequest_List_CURRENT_EapRequestMessage_BufferArr_value_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportEapRequest_List_CURRENT_EapRequestMessage_BufferArr_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportEapRequest_Header_Type_SET( UINT8* base_ptr, UINT32 opcode )
{
	BM_ReportEapRequest_Header_Type_SET( base_ptr, opcode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportEapRequest_Header_Version_SET( UINT8* base_ptr, UINT16 version )
{
	BM_ReportEapRequest_Header_Version_SET( base_ptr, version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportEapRequest_Header_Accessibility_SET( UINT8* base_ptr, UINT16 accessibility )
{
	BM_ReportEapRequest_Header_Accessibility_SET( base_ptr, accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportEapRequest_Header_Status_SET( UINT8* base_ptr, UINT16 status )
{
	BM_ReportEapRequest_Header_Status_SET( base_ptr, status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportEapRequest_Header_Length_SET( UINT8* base_ptr, UINT32 len )
{
	BM_ReportEapRequest_Header_Length_SET( base_ptr, len );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportRecentNbrHood_Header_Version_GET( UINT8* base_ptr, UINT16* version )
{
	BM_ReportRecentNbrHood_Header_Version_GET( base_ptr, *version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportRecentNbrHood_Header_Accessibility_GET( UINT8* base_ptr, UINT16* accessibility )
{
	BM_ReportRecentNbrHood_Header_Accessibility_GET( base_ptr, *accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportRecentNbrHood_Header_Status_GET( UINT8* base_ptr, UINT16* status )
{
	BM_ReportRecentNbrHood_Header_Status_GET( base_ptr, *status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportRecentNbrHood_Header_Length_GET( UINT8* base_ptr, UINT32* listSize )
{
	BM_ReportRecentNbrHood_Header_Length_GET( base_ptr, *listSize );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportRecentNbrHood_List_GET_FIRST( UINT8* base_ptr, UINT32* out_diff, UINT32* out_cur_bitoff )
{
	UINT8* out_cur_ptr = base_ptr;
	BM_ReportRecentNbrHood_List_GET_FIRST( base_ptr, out_cur_ptr, *out_cur_bitoff );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportRecentNbrHood_List_GET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportRecentNbrHood_List_GET_TYPE( cur_ptr, cur_bitoff, *type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportRecentNbrHood_List_GET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_length, UINT32 err )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportRecentNbrHood_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, *out_length, err );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportRecentNbrHood_List_CURRENT_ChannelInfoArray_Frequency_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* Frequency )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportRecentNbrHood_List_CURRENT_ChannelInfoArray_Frequency_GET( base_ptr, cur_ptr, cur_bitoff, *Frequency );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportRecentNbrHood_List_CURRENT_ChannelInfoArray_ChannelId_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* ChannelId )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportRecentNbrHood_List_CURRENT_ChannelInfoArray_ChannelId_GET( base_ptr, cur_ptr, cur_bitoff, *ChannelId );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportRecentNbrHood_List_CURRENT_ChannelInfoArray_Bandwidth_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* Bandwidth )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportRecentNbrHood_List_CURRENT_ChannelInfoArray_Bandwidth_GET( base_ptr, cur_ptr, cur_bitoff, *Bandwidth );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportRecentNbrHood_List_CURRENT_ChannelInfoArray_Fft_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* Fft )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportRecentNbrHood_List_CURRENT_ChannelInfoArray_Fft_GET( base_ptr, cur_ptr, cur_bitoff, *Fft );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportRecentNbrHood_List_CURRENT_ChannelInfoArray_Preambles_value_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportRecentNbrHood_List_CURRENT_ChannelInfoArray_Preambles_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportRecentNbrHood_List_CURRENT_ChannelInfoArray_Reserved_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* Reserved )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportRecentNbrHood_List_CURRENT_ChannelInfoArray_Reserved_GET( base_ptr, cur_ptr, cur_bitoff, *Reserved );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportRecentNbrHood_List_GET_NEXT( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_diff, UINT32* out_cur_bitoff, UINT32 err )
{
	UINT8* out_cur_ptr = base_ptr;
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportRecentNbrHood_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, out_cur_ptr, *out_cur_bitoff, err );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportRecentNbrHood_List_SET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportRecentNbrHood_List_SET_TYPE( cur_ptr, cur_bitoff, type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportRecentNbrHood_List_SET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 lenOfLen, UINT32 length )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	lenOfLen = 2;
	BM_ReportRecentNbrHood_List_SET_LENGTH( cur_ptr, cur_bitoff, lenOfLen, length );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportRecentNbrHood_List_CURRENT_ChannelInfoArray_Frequency_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 Frequency )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportRecentNbrHood_List_CURRENT_ChannelInfoArray_Frequency_SET( base_ptr, cur_ptr, cur_bitoff, Frequency );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportRecentNbrHood_List_CURRENT_ChannelInfoArray_ChannelId_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 ChannelId )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportRecentNbrHood_List_CURRENT_ChannelInfoArray_ChannelId_SET( base_ptr, cur_ptr, cur_bitoff, ChannelId );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportRecentNbrHood_List_CURRENT_ChannelInfoArray_Bandwidth_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 Bandwidth )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportRecentNbrHood_List_CURRENT_ChannelInfoArray_Bandwidth_SET( base_ptr, cur_ptr, cur_bitoff, Bandwidth );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportRecentNbrHood_List_CURRENT_ChannelInfoArray_Fft_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 Fft )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportRecentNbrHood_List_CURRENT_ChannelInfoArray_Fft_SET( base_ptr, cur_ptr, cur_bitoff, Fft );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportRecentNbrHood_List_CURRENT_ChannelInfoArray_Preambles_value_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportRecentNbrHood_List_CURRENT_ChannelInfoArray_Preambles_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportRecentNbrHood_List_CURRENT_ChannelInfoArray_Reserved_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 Reserved )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportRecentNbrHood_List_CURRENT_ChannelInfoArray_Reserved_SET( base_ptr, cur_ptr, cur_bitoff, Reserved );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportRecentNbrHood_Header_Type_SET( UINT8* base_ptr, UINT32 opcode )
{
	BM_ReportRecentNbrHood_Header_Type_SET( base_ptr, opcode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportRecentNbrHood_Header_Version_SET( UINT8* base_ptr, UINT16 version )
{
	BM_ReportRecentNbrHood_Header_Version_SET( base_ptr, version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportRecentNbrHood_Header_Accessibility_SET( UINT8* base_ptr, UINT16 accessibility )
{
	BM_ReportRecentNbrHood_Header_Accessibility_SET( base_ptr, accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportRecentNbrHood_Header_Status_SET( UINT8* base_ptr, UINT16 status )
{
	BM_ReportRecentNbrHood_Header_Status_SET( base_ptr, status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportRecentNbrHood_Header_Length_SET( UINT8* base_ptr, UINT32 len )
{
	BM_ReportRecentNbrHood_Header_Length_SET( base_ptr, len );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetLinkStatus_Header_Version_GET( UINT8* base_ptr, UINT16* version )
{
	BM_GetLinkStatus_Header_Version_GET( base_ptr, *version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetLinkStatus_Header_Accessibility_GET( UINT8* base_ptr, UINT16* accessibility )
{
	BM_GetLinkStatus_Header_Accessibility_GET( base_ptr, *accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetLinkStatus_Header_Status_GET( UINT8* base_ptr, UINT16* status )
{
	BM_GetLinkStatus_Header_Status_GET( base_ptr, *status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetLinkStatus_Header_Length_GET( UINT8* base_ptr, UINT32* listSize )
{
	BM_GetLinkStatus_Header_Length_GET( base_ptr, *listSize );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetLinkStatus_List_GET_FIRST( UINT8* base_ptr, UINT32* out_diff, UINT32* out_cur_bitoff )
{
	UINT8* out_cur_ptr = base_ptr;
	BM_GetLinkStatus_List_GET_FIRST( base_ptr, out_cur_ptr, *out_cur_bitoff );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetLinkStatus_List_GET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetLinkStatus_List_GET_TYPE( cur_ptr, cur_bitoff, *type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetLinkStatus_List_GET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_length, UINT32 err )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetLinkStatus_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, *out_length, err );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetLinkStatus_List_CURRENT_LinkStatus_UpLinkSpeed_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* UpLinkSpeed )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetLinkStatus_List_CURRENT_LinkStatus_UpLinkSpeed_GET( base_ptr, cur_ptr, cur_bitoff, *UpLinkSpeed );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetLinkStatus_List_CURRENT_LinkStatus_DownLinkSpeed_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* DownLinkSpeed )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetLinkStatus_List_CURRENT_LinkStatus_DownLinkSpeed_GET( base_ptr, cur_ptr, cur_bitoff, *DownLinkSpeed );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetLinkStatus_List_CURRENT_LinkStatus_CenterFrequency_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* CenterFrequency )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetLinkStatus_List_CURRENT_LinkStatus_CenterFrequency_GET( base_ptr, cur_ptr, cur_bitoff, *CenterFrequency );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetLinkStatus_List_CURRENT_LinkStatus_TxPower_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* TxPower )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetLinkStatus_List_CURRENT_LinkStatus_TxPower_GET( base_ptr, cur_ptr, cur_bitoff, *TxPower );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetLinkStatus_List_CURRENT_LinkStatus_RxRssi_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* RxRssi )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetLinkStatus_List_CURRENT_LinkStatus_RxRssi_GET( base_ptr, cur_ptr, cur_bitoff, *RxRssi );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetLinkStatus_List_CURRENT_LinkStatus_RxCinr_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* RxCinr )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetLinkStatus_List_CURRENT_LinkStatus_RxCinr_GET( base_ptr, cur_ptr, cur_bitoff, *RxCinr );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetLinkStatus_List_CURRENT_LinkStatus_BSID_value_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetLinkStatus_List_CURRENT_LinkStatus_BSID_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetLinkStatus_List_CURRENT_LinkStatus_LinkQuality_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* LinkQuality )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetLinkStatus_List_CURRENT_LinkStatus_LinkQuality_GET( base_ptr, cur_ptr, cur_bitoff, *LinkQuality );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetLinkStatus_List_CURRENT_LinkStatus_Reserved_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* Reserved )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetLinkStatus_List_CURRENT_LinkStatus_Reserved_GET( base_ptr, cur_ptr, cur_bitoff, *Reserved );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetLinkStatus_List_CURRENT_ChannelInfo_Frequency_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* Frequency )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetLinkStatus_List_CURRENT_ChannelInfo_Frequency_GET( base_ptr, cur_ptr, cur_bitoff, *Frequency );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetLinkStatus_List_CURRENT_ChannelInfo_ChannelId_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* ChannelId )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetLinkStatus_List_CURRENT_ChannelInfo_ChannelId_GET( base_ptr, cur_ptr, cur_bitoff, *ChannelId );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetLinkStatus_List_CURRENT_ChannelInfo_Bandwidth_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* Bandwidth )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetLinkStatus_List_CURRENT_ChannelInfo_Bandwidth_GET( base_ptr, cur_ptr, cur_bitoff, *Bandwidth );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetLinkStatus_List_CURRENT_ChannelInfo_Fft_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* Fft )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetLinkStatus_List_CURRENT_ChannelInfo_Fft_GET( base_ptr, cur_ptr, cur_bitoff, *Fft );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetLinkStatus_List_CURRENT_ChannelInfo_Preambles_value_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetLinkStatus_List_CURRENT_ChannelInfo_Preambles_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetLinkStatus_List_CURRENT_ChannelInfo_Reserved_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* Reserved )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetLinkStatus_List_CURRENT_ChannelInfo_Reserved_GET( base_ptr, cur_ptr, cur_bitoff, *Reserved );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetLinkStatus_List_GET_NEXT( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_diff, UINT32* out_cur_bitoff, UINT32 err )
{
	UINT8* out_cur_ptr = base_ptr;
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetLinkStatus_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, out_cur_ptr, *out_cur_bitoff, err );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetLinkStatus_List_SET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetLinkStatus_List_SET_TYPE( cur_ptr, cur_bitoff, type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetLinkStatus_List_SET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 lenOfLen, UINT32 length )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	lenOfLen = 2;
	BM_GetLinkStatus_List_SET_LENGTH( cur_ptr, cur_bitoff, lenOfLen, length );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetLinkStatus_List_CURRENT_LinkStatus_UpLinkSpeed_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 UpLinkSpeed )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetLinkStatus_List_CURRENT_LinkStatus_UpLinkSpeed_SET( base_ptr, cur_ptr, cur_bitoff, UpLinkSpeed );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetLinkStatus_List_CURRENT_LinkStatus_DownLinkSpeed_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 DownLinkSpeed )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetLinkStatus_List_CURRENT_LinkStatus_DownLinkSpeed_SET( base_ptr, cur_ptr, cur_bitoff, DownLinkSpeed );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetLinkStatus_List_CURRENT_LinkStatus_CenterFrequency_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 CenterFrequency )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetLinkStatus_List_CURRENT_LinkStatus_CenterFrequency_SET( base_ptr, cur_ptr, cur_bitoff, CenterFrequency );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetLinkStatus_List_CURRENT_LinkStatus_TxPower_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 TxPower )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetLinkStatus_List_CURRENT_LinkStatus_TxPower_SET( base_ptr, cur_ptr, cur_bitoff, TxPower );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetLinkStatus_List_CURRENT_LinkStatus_RxRssi_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 RxRssi )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetLinkStatus_List_CURRENT_LinkStatus_RxRssi_SET( base_ptr, cur_ptr, cur_bitoff, RxRssi );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetLinkStatus_List_CURRENT_LinkStatus_RxCinr_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 RxCinr )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetLinkStatus_List_CURRENT_LinkStatus_RxCinr_SET( base_ptr, cur_ptr, cur_bitoff, RxCinr );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetLinkStatus_List_CURRENT_LinkStatus_BSID_value_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetLinkStatus_List_CURRENT_LinkStatus_BSID_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetLinkStatus_List_CURRENT_LinkStatus_LinkQuality_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 LinkQuality )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetLinkStatus_List_CURRENT_LinkStatus_LinkQuality_SET( base_ptr, cur_ptr, cur_bitoff, LinkQuality );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetLinkStatus_List_CURRENT_LinkStatus_Reserved_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 Reserved )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetLinkStatus_List_CURRENT_LinkStatus_Reserved_SET( base_ptr, cur_ptr, cur_bitoff, Reserved );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetLinkStatus_List_CURRENT_ChannelInfo_Frequency_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 Frequency )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetLinkStatus_List_CURRENT_ChannelInfo_Frequency_SET( base_ptr, cur_ptr, cur_bitoff, Frequency );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetLinkStatus_List_CURRENT_ChannelInfo_ChannelId_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 ChannelId )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetLinkStatus_List_CURRENT_ChannelInfo_ChannelId_SET( base_ptr, cur_ptr, cur_bitoff, ChannelId );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetLinkStatus_List_CURRENT_ChannelInfo_Bandwidth_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 Bandwidth )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetLinkStatus_List_CURRENT_ChannelInfo_Bandwidth_SET( base_ptr, cur_ptr, cur_bitoff, Bandwidth );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetLinkStatus_List_CURRENT_ChannelInfo_Fft_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 Fft )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetLinkStatus_List_CURRENT_ChannelInfo_Fft_SET( base_ptr, cur_ptr, cur_bitoff, Fft );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetLinkStatus_List_CURRENT_ChannelInfo_Preambles_value_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetLinkStatus_List_CURRENT_ChannelInfo_Preambles_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetLinkStatus_List_CURRENT_ChannelInfo_Reserved_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 Reserved )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetLinkStatus_List_CURRENT_ChannelInfo_Reserved_SET( base_ptr, cur_ptr, cur_bitoff, Reserved );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetLinkStatus_Header_Type_SET( UINT8* base_ptr, UINT32 opcode )
{
	BM_GetLinkStatus_Header_Type_SET( base_ptr, opcode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetLinkStatus_Header_Version_SET( UINT8* base_ptr, UINT16 version )
{
	BM_GetLinkStatus_Header_Version_SET( base_ptr, version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetLinkStatus_Header_Accessibility_SET( UINT8* base_ptr, UINT16 accessibility )
{
	BM_GetLinkStatus_Header_Accessibility_SET( base_ptr, accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetLinkStatus_Header_Status_SET( UINT8* base_ptr, UINT16 status )
{
	BM_GetLinkStatus_Header_Status_SET( base_ptr, status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetLinkStatus_Header_Length_SET( UINT8* base_ptr, UINT32 len )
{
	BM_GetLinkStatus_Header_Length_SET( base_ptr, len );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetD2HChannelMask_Header_Version_GET( UINT8* base_ptr, UINT16* version )
{
	BM_SetD2HChannelMask_Header_Version_GET( base_ptr, *version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetD2HChannelMask_Header_Accessibility_GET( UINT8* base_ptr, UINT16* accessibility )
{
	BM_SetD2HChannelMask_Header_Accessibility_GET( base_ptr, *accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetD2HChannelMask_Header_Status_GET( UINT8* base_ptr, UINT16* status )
{
	BM_SetD2HChannelMask_Header_Status_GET( base_ptr, *status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetD2HChannelMask_Header_Length_GET( UINT8* base_ptr, UINT32* listSize )
{
	BM_SetD2HChannelMask_Header_Length_GET( base_ptr, *listSize );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetD2HChannelMask_List_GET_FIRST( UINT8* base_ptr, UINT32* out_diff, UINT32* out_cur_bitoff )
{
	UINT8* out_cur_ptr = base_ptr;
	BM_SetD2HChannelMask_List_GET_FIRST( base_ptr, out_cur_ptr, *out_cur_bitoff );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetD2HChannelMask_List_GET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetD2HChannelMask_List_GET_TYPE( cur_ptr, cur_bitoff, *type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetD2HChannelMask_List_GET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_length, UINT32 err )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetD2HChannelMask_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, *out_length, err );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetD2HChannelMask_List_CURRENT_D2HChannelMask_DataChannelSwitch_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* DataChannelSwitch )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetD2HChannelMask_List_CURRENT_D2HChannelMask_DataChannelSwitch_GET( base_ptr, cur_ptr, cur_bitoff, *DataChannelSwitch );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetD2HChannelMask_List_CURRENT_D2HChannelMask_DiagnosticsChannelSwitch_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* DiagnosticsChannelSwitch )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetD2HChannelMask_List_CURRENT_D2HChannelMask_DiagnosticsChannelSwitch_GET( base_ptr, cur_ptr, cur_bitoff, *DiagnosticsChannelSwitch );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetD2HChannelMask_List_CURRENT_D2HChannelMask_Reserved_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* Reserved )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetD2HChannelMask_List_CURRENT_D2HChannelMask_Reserved_GET( base_ptr, cur_ptr, cur_bitoff, *Reserved );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetD2HChannelMask_List_GET_NEXT( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_diff, UINT32* out_cur_bitoff, UINT32 err )
{
	UINT8* out_cur_ptr = base_ptr;
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetD2HChannelMask_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, out_cur_ptr, *out_cur_bitoff, err );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetD2HChannelMask_List_SET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetD2HChannelMask_List_SET_TYPE( cur_ptr, cur_bitoff, type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetD2HChannelMask_List_SET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 lenOfLen, UINT32 length )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	lenOfLen = 2;
	BM_SetD2HChannelMask_List_SET_LENGTH( cur_ptr, cur_bitoff, lenOfLen, length );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetD2HChannelMask_List_CURRENT_D2HChannelMask_DataChannelSwitch_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 DataChannelSwitch )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetD2HChannelMask_List_CURRENT_D2HChannelMask_DataChannelSwitch_SET( base_ptr, cur_ptr, cur_bitoff, DataChannelSwitch );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetD2HChannelMask_List_CURRENT_D2HChannelMask_DiagnosticsChannelSwitch_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 DiagnosticsChannelSwitch )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetD2HChannelMask_List_CURRENT_D2HChannelMask_DiagnosticsChannelSwitch_SET( base_ptr, cur_ptr, cur_bitoff, DiagnosticsChannelSwitch );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetD2HChannelMask_List_CURRENT_D2HChannelMask_Reserved_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 Reserved )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetD2HChannelMask_List_CURRENT_D2HChannelMask_Reserved_SET( base_ptr, cur_ptr, cur_bitoff, Reserved );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetD2HChannelMask_Header_Type_SET( UINT8* base_ptr, UINT32 opcode )
{
	BM_SetD2HChannelMask_Header_Type_SET( base_ptr, opcode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetD2HChannelMask_Header_Version_SET( UINT8* base_ptr, UINT16 version )
{
	BM_SetD2HChannelMask_Header_Version_SET( base_ptr, version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetD2HChannelMask_Header_Accessibility_SET( UINT8* base_ptr, UINT16 accessibility )
{
	BM_SetD2HChannelMask_Header_Accessibility_SET( base_ptr, accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetD2HChannelMask_Header_Status_SET( UINT8* base_ptr, UINT16 status )
{
	BM_SetD2HChannelMask_Header_Status_SET( base_ptr, status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetD2HChannelMask_Header_Length_SET( UINT8* base_ptr, UINT32 len )
{
	BM_SetD2HChannelMask_Header_Length_SET( base_ptr, len );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ScanCommand_Header_Version_GET( UINT8* base_ptr, UINT16* version )
{
	BM_ScanCommand_Header_Version_GET( base_ptr, *version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ScanCommand_Header_Accessibility_GET( UINT8* base_ptr, UINT16* accessibility )
{
	BM_ScanCommand_Header_Accessibility_GET( base_ptr, *accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ScanCommand_Header_Status_GET( UINT8* base_ptr, UINT16* status )
{
	BM_ScanCommand_Header_Status_GET( base_ptr, *status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ScanCommand_Header_Length_GET( UINT8* base_ptr, UINT32* listSize )
{
	BM_ScanCommand_Header_Length_GET( base_ptr, *listSize );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ScanCommand_List_GET_FIRST( UINT8* base_ptr, UINT32* out_diff, UINT32* out_cur_bitoff )
{
	UINT8* out_cur_ptr = base_ptr;
	BM_ScanCommand_List_GET_FIRST( base_ptr, out_cur_ptr, *out_cur_bitoff );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ScanCommand_List_GET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ScanCommand_List_GET_TYPE( cur_ptr, cur_bitoff, *type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ScanCommand_List_GET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_length, UINT32 err )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ScanCommand_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, *out_length, err );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ScanCommand_List_CURRENT_DoScanCommand_value_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ScanCommand_List_CURRENT_DoScanCommand_value_GET( base_ptr, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ScanCommand_List_CURRENT_CoexPriority_value_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ScanCommand_List_CURRENT_CoexPriority_value_GET( base_ptr, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ScanCommand_List_GET_NEXT( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_diff, UINT32* out_cur_bitoff, UINT32 err )
{
	UINT8* out_cur_ptr = base_ptr;
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ScanCommand_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, out_cur_ptr, *out_cur_bitoff, err );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ScanCommand_List_SET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ScanCommand_List_SET_TYPE( cur_ptr, cur_bitoff, type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ScanCommand_List_SET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 lenOfLen, UINT32 length )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	lenOfLen = 2;
	BM_ScanCommand_List_SET_LENGTH( cur_ptr, cur_bitoff, lenOfLen, length );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ScanCommand_List_CURRENT_DoScanCommand_value_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ScanCommand_List_CURRENT_DoScanCommand_value_SET( base_ptr, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ScanCommand_List_CURRENT_CoexPriority_value_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ScanCommand_List_CURRENT_CoexPriority_value_SET( base_ptr, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ScanCommand_Header_Type_SET( UINT8* base_ptr, UINT32 opcode )
{
	BM_ScanCommand_Header_Type_SET( base_ptr, opcode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ScanCommand_Header_Version_SET( UINT8* base_ptr, UINT16 version )
{
	BM_ScanCommand_Header_Version_SET( base_ptr, version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ScanCommand_Header_Accessibility_SET( UINT8* base_ptr, UINT16 accessibility )
{
	BM_ScanCommand_Header_Accessibility_SET( base_ptr, accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ScanCommand_Header_Status_SET( UINT8* base_ptr, UINT16 status )
{
	BM_ScanCommand_Header_Status_SET( base_ptr, status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ScanCommand_Header_Length_SET( UINT8* base_ptr, UINT32 len )
{
	BM_ScanCommand_Header_Length_SET( base_ptr, len );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SPLockStatusInfo_Header_Version_GET( UINT8* base_ptr, UINT16* version )
{
	BM_SPLockStatusInfo_Header_Version_GET( base_ptr, *version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SPLockStatusInfo_Header_Accessibility_GET( UINT8* base_ptr, UINT16* accessibility )
{
	BM_SPLockStatusInfo_Header_Accessibility_GET( base_ptr, *accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SPLockStatusInfo_Header_Status_GET( UINT8* base_ptr, UINT16* status )
{
	BM_SPLockStatusInfo_Header_Status_GET( base_ptr, *status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SPLockStatusInfo_Header_Length_GET( UINT8* base_ptr, UINT32* listSize )
{
	BM_SPLockStatusInfo_Header_Length_GET( base_ptr, *listSize );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SPLockStatusInfo_List_GET_FIRST( UINT8* base_ptr, UINT32* out_diff, UINT32* out_cur_bitoff )
{
	UINT8* out_cur_ptr = base_ptr;
	BM_SPLockStatusInfo_List_GET_FIRST( base_ptr, out_cur_ptr, *out_cur_bitoff );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SPLockStatusInfo_List_GET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SPLockStatusInfo_List_GET_TYPE( cur_ptr, cur_bitoff, *type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SPLockStatusInfo_List_GET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_length, UINT32 err )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SPLockStatusInfo_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, *out_length, err );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SPLockStatusInfo_List_CURRENT_SPLockStatus_value_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SPLockStatusInfo_List_CURRENT_SPLockStatus_value_GET( base_ptr, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SPLockStatusInfo_List_CURRENT_LockedToNSPNameInfo_ActualLen_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* ActualLen )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SPLockStatusInfo_List_CURRENT_LockedToNSPNameInfo_ActualLen_GET( base_ptr, cur_ptr, cur_bitoff, *ActualLen );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SPLockStatusInfo_List_CURRENT_LockedToNSPNameInfo_BufferArr_value_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SPLockStatusInfo_List_CURRENT_LockedToNSPNameInfo_BufferArr_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SPLockStatusInfo_List_GET_NEXT( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_diff, UINT32* out_cur_bitoff, UINT32 err )
{
	UINT8* out_cur_ptr = base_ptr;
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SPLockStatusInfo_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, out_cur_ptr, *out_cur_bitoff, err );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SPLockStatusInfo_List_SET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SPLockStatusInfo_List_SET_TYPE( cur_ptr, cur_bitoff, type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SPLockStatusInfo_List_SET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 lenOfLen, UINT32 length )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	lenOfLen = 2;
	BM_SPLockStatusInfo_List_SET_LENGTH( cur_ptr, cur_bitoff, lenOfLen, length );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SPLockStatusInfo_List_CURRENT_SPLockStatus_value_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SPLockStatusInfo_List_CURRENT_SPLockStatus_value_SET( base_ptr, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SPLockStatusInfo_List_CURRENT_LockedToNSPNameInfo_ActualLen_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 ActualLen )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SPLockStatusInfo_List_CURRENT_LockedToNSPNameInfo_ActualLen_SET( base_ptr, cur_ptr, cur_bitoff, ActualLen );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SPLockStatusInfo_List_CURRENT_LockedToNSPNameInfo_BufferArr_value_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SPLockStatusInfo_List_CURRENT_LockedToNSPNameInfo_BufferArr_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SPLockStatusInfo_Header_Type_SET( UINT8* base_ptr, UINT32 opcode )
{
	BM_SPLockStatusInfo_Header_Type_SET( base_ptr, opcode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SPLockStatusInfo_Header_Version_SET( UINT8* base_ptr, UINT16 version )
{
	BM_SPLockStatusInfo_Header_Version_SET( base_ptr, version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SPLockStatusInfo_Header_Accessibility_SET( UINT8* base_ptr, UINT16 accessibility )
{
	BM_SPLockStatusInfo_Header_Accessibility_SET( base_ptr, accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SPLockStatusInfo_Header_Status_SET( UINT8* base_ptr, UINT16 status )
{
	BM_SPLockStatusInfo_Header_Status_SET( base_ptr, status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SPLockStatusInfo_Header_Length_SET( UINT8* base_ptr, UINT32 len )
{
	BM_SPLockStatusInfo_Header_Length_SET( base_ptr, len );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetMediaStatus_Header_Version_GET( UINT8* base_ptr, UINT16* version )
{
	BM_GetMediaStatus_Header_Version_GET( base_ptr, *version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetMediaStatus_Header_Accessibility_GET( UINT8* base_ptr, UINT16* accessibility )
{
	BM_GetMediaStatus_Header_Accessibility_GET( base_ptr, *accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetMediaStatus_Header_Status_GET( UINT8* base_ptr, UINT16* status )
{
	BM_GetMediaStatus_Header_Status_GET( base_ptr, *status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetMediaStatus_Header_Length_GET( UINT8* base_ptr, UINT32* listSize )
{
	BM_GetMediaStatus_Header_Length_GET( base_ptr, *listSize );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetMediaStatus_List_GET_FIRST( UINT8* base_ptr, UINT32* out_diff, UINT32* out_cur_bitoff )
{
	UINT8* out_cur_ptr = base_ptr;
	BM_GetMediaStatus_List_GET_FIRST( base_ptr, out_cur_ptr, *out_cur_bitoff );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetMediaStatus_List_GET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetMediaStatus_List_GET_TYPE( cur_ptr, cur_bitoff, *type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetMediaStatus_List_GET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_length, UINT32 err )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetMediaStatus_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, *out_length, err );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetMediaStatus_List_CURRENT_MediaStatus_value_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetMediaStatus_List_CURRENT_MediaStatus_value_GET( base_ptr, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetMediaStatus_List_GET_NEXT( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_diff, UINT32* out_cur_bitoff, UINT32 err )
{
	UINT8* out_cur_ptr = base_ptr;
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetMediaStatus_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, out_cur_ptr, *out_cur_bitoff, err );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetMediaStatus_List_SET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetMediaStatus_List_SET_TYPE( cur_ptr, cur_bitoff, type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetMediaStatus_List_SET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 lenOfLen, UINT32 length )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	lenOfLen = 2;
	BM_GetMediaStatus_List_SET_LENGTH( cur_ptr, cur_bitoff, lenOfLen, length );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetMediaStatus_List_CURRENT_MediaStatus_value_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetMediaStatus_List_CURRENT_MediaStatus_value_SET( base_ptr, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetMediaStatus_Header_Type_SET( UINT8* base_ptr, UINT32 opcode )
{
	BM_GetMediaStatus_Header_Type_SET( base_ptr, opcode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetMediaStatus_Header_Version_SET( UINT8* base_ptr, UINT16 version )
{
	BM_GetMediaStatus_Header_Version_SET( base_ptr, version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetMediaStatus_Header_Accessibility_SET( UINT8* base_ptr, UINT16 accessibility )
{
	BM_GetMediaStatus_Header_Accessibility_SET( base_ptr, accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetMediaStatus_Header_Status_SET( UINT8* base_ptr, UINT16 status )
{
	BM_GetMediaStatus_Header_Status_SET( base_ptr, status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetMediaStatus_Header_Length_SET( UINT8* base_ptr, UINT32 len )
{
	BM_GetMediaStatus_Header_Length_SET( base_ptr, len );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetState_Header_Version_GET( UINT8* base_ptr, UINT16* version )
{
	BM_GetState_Header_Version_GET( base_ptr, *version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetState_Header_Accessibility_GET( UINT8* base_ptr, UINT16* accessibility )
{
	BM_GetState_Header_Accessibility_GET( base_ptr, *accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetState_Header_Status_GET( UINT8* base_ptr, UINT16* status )
{
	BM_GetState_Header_Status_GET( base_ptr, *status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetState_Header_Length_GET( UINT8* base_ptr, UINT32* listSize )
{
	BM_GetState_Header_Length_GET( base_ptr, *listSize );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetState_List_GET_FIRST( UINT8* base_ptr, UINT32* out_diff, UINT32* out_cur_bitoff )
{
	UINT8* out_cur_ptr = base_ptr;
	BM_GetState_List_GET_FIRST( base_ptr, out_cur_ptr, *out_cur_bitoff );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetState_List_GET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetState_List_GET_TYPE( cur_ptr, cur_bitoff, *type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetState_List_GET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_length, UINT32 err )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetState_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, *out_length, err );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetState_List_CURRENT_SystemState_value_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetState_List_CURRENT_SystemState_value_GET( base_ptr, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetState_List_CURRENT_ConnectProgress_value_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetState_List_CURRENT_ConnectProgress_value_GET( base_ptr, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetState_List_CURRENT_RFStatus_SwRFSwitch_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* SwRFSwitch )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetState_List_CURRENT_RFStatus_SwRFSwitch_GET( base_ptr, cur_ptr, cur_bitoff, *SwRFSwitch );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetState_List_CURRENT_RFStatus_HwRFSwitch_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* HwRFSwitch )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetState_List_CURRENT_RFStatus_HwRFSwitch_GET( base_ptr, cur_ptr, cur_bitoff, *HwRFSwitch );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetState_List_CURRENT_RFStatus_Reserved_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* Reserved )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetState_List_CURRENT_RFStatus_Reserved_GET( base_ptr, cur_ptr, cur_bitoff, *Reserved );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetState_List_CURRENT_LastReason_value_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetState_List_CURRENT_LastReason_value_GET( base_ptr, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetState_List_GET_NEXT( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_diff, UINT32* out_cur_bitoff, UINT32 err )
{
	UINT8* out_cur_ptr = base_ptr;
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetState_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, out_cur_ptr, *out_cur_bitoff, err );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetState_List_SET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetState_List_SET_TYPE( cur_ptr, cur_bitoff, type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetState_List_SET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 lenOfLen, UINT32 length )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	lenOfLen = 2;
	BM_GetState_List_SET_LENGTH( cur_ptr, cur_bitoff, lenOfLen, length );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetState_List_CURRENT_SystemState_value_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetState_List_CURRENT_SystemState_value_SET( base_ptr, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetState_List_CURRENT_ConnectProgress_value_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetState_List_CURRENT_ConnectProgress_value_SET( base_ptr, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetState_List_CURRENT_RFStatus_SwRFSwitch_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 SwRFSwitch )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetState_List_CURRENT_RFStatus_SwRFSwitch_SET( base_ptr, cur_ptr, cur_bitoff, SwRFSwitch );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetState_List_CURRENT_RFStatus_HwRFSwitch_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 HwRFSwitch )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetState_List_CURRENT_RFStatus_HwRFSwitch_SET( base_ptr, cur_ptr, cur_bitoff, HwRFSwitch );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetState_List_CURRENT_RFStatus_Reserved_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 Reserved )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetState_List_CURRENT_RFStatus_Reserved_SET( base_ptr, cur_ptr, cur_bitoff, Reserved );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetState_List_CURRENT_LastReason_value_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetState_List_CURRENT_LastReason_value_SET( base_ptr, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetState_Header_Type_SET( UINT8* base_ptr, UINT32 opcode )
{
	BM_GetState_Header_Type_SET( base_ptr, opcode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetState_Header_Version_SET( UINT8* base_ptr, UINT16 version )
{
	BM_GetState_Header_Version_SET( base_ptr, version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetState_Header_Accessibility_SET( UINT8* base_ptr, UINT16 accessibility )
{
	BM_GetState_Header_Accessibility_SET( base_ptr, accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetState_Header_Status_SET( UINT8* base_ptr, UINT16 status )
{
	BM_GetState_Header_Status_SET( base_ptr, status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetState_Header_Length_SET( UINT8* base_ptr, UINT32 len )
{
	BM_GetState_Header_Length_SET( base_ptr, len );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetScanResults_Header_Version_GET( UINT8* base_ptr, UINT16* version )
{
	BM_GetScanResults_Header_Version_GET( base_ptr, *version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetScanResults_Header_Accessibility_GET( UINT8* base_ptr, UINT16* accessibility )
{
	BM_GetScanResults_Header_Accessibility_GET( base_ptr, *accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetScanResults_Header_Status_GET( UINT8* base_ptr, UINT16* status )
{
	BM_GetScanResults_Header_Status_GET( base_ptr, *status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetScanResults_Header_Length_GET( UINT8* base_ptr, UINT32* listSize )
{
	BM_GetScanResults_Header_Length_GET( base_ptr, *listSize );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetScanResults_List_GET_FIRST( UINT8* base_ptr, UINT32* out_diff, UINT32* out_cur_bitoff )
{
	UINT8* out_cur_ptr = base_ptr;
	BM_GetScanResults_List_GET_FIRST( base_ptr, out_cur_ptr, *out_cur_bitoff );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetScanResults_List_GET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetScanResults_List_GET_TYPE( cur_ptr, cur_bitoff, *type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetScanResults_List_GET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_length, UINT32 err )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetScanResults_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, *out_length, err );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetScanResults_List_CURRENT_ScanStatus_value_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetScanResults_List_CURRENT_ScanStatus_value_GET( base_ptr, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetScanResults_List_CURRENT_ScanResultList_Get_Rssi_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* Rssi )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetScanResults_List_CURRENT_ScanResultList_Get_Rssi_GET( base_ptr, cur_ptr, cur_bitoff, *Rssi );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetScanResults_List_CURRENT_ScanResultList_Get_Cinr_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* Cinr )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetScanResults_List_CURRENT_ScanResultList_Get_Cinr_GET( base_ptr, cur_ptr, cur_bitoff, *Cinr );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetScanResults_List_CURRENT_ScanResultList_Get_BsIdmask_value_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetScanResults_List_CURRENT_ScanResultList_Get_BsIdmask_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetScanResults_List_CURRENT_ScanResultList_Get_BsId_value_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetScanResults_List_CURRENT_ScanResultList_Get_BsId_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetScanResults_List_CURRENT_ScanResultList_Get_ChannelId_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* ChannelId )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetScanResults_List_CURRENT_ScanResultList_Get_ChannelId_GET( base_ptr, cur_ptr, cur_bitoff, *ChannelId );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetScanResults_List_CURRENT_ScanResultList_Get_PreambleId_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* PreambleId )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetScanResults_List_CURRENT_ScanResultList_Get_PreambleId_GET( base_ptr, cur_ptr, cur_bitoff, *PreambleId );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetScanResults_List_CURRENT_ScanResultList_Get_LinkGrade_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* LinkGrade )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetScanResults_List_CURRENT_ScanResultList_Get_LinkGrade_GET( base_ptr, cur_ptr, cur_bitoff, *LinkGrade );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetScanResults_List_CURRENT_ScanResultList_Get_LinkQuality_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* LinkQuality )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetScanResults_List_CURRENT_ScanResultList_Get_LinkQuality_GET( base_ptr, cur_ptr, cur_bitoff, *LinkQuality );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetScanResults_List_GET_NEXT( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_diff, UINT32* out_cur_bitoff, UINT32 err )
{
	UINT8* out_cur_ptr = base_ptr;
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetScanResults_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, out_cur_ptr, *out_cur_bitoff, err );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetScanResults_List_SET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetScanResults_List_SET_TYPE( cur_ptr, cur_bitoff, type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetScanResults_List_SET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 lenOfLen, UINT32 length )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	lenOfLen = 2;
	BM_GetScanResults_List_SET_LENGTH( cur_ptr, cur_bitoff, lenOfLen, length );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetScanResults_List_CURRENT_ScanStatus_value_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetScanResults_List_CURRENT_ScanStatus_value_SET( base_ptr, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetScanResults_List_CURRENT_ScanResultList_Get_Rssi_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 Rssi )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetScanResults_List_CURRENT_ScanResultList_Get_Rssi_SET( base_ptr, cur_ptr, cur_bitoff, Rssi );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetScanResults_List_CURRENT_ScanResultList_Get_Cinr_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 Cinr )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetScanResults_List_CURRENT_ScanResultList_Get_Cinr_SET( base_ptr, cur_ptr, cur_bitoff, Cinr );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetScanResults_List_CURRENT_ScanResultList_Get_BsIdmask_value_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetScanResults_List_CURRENT_ScanResultList_Get_BsIdmask_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetScanResults_List_CURRENT_ScanResultList_Get_BsId_value_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetScanResults_List_CURRENT_ScanResultList_Get_BsId_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetScanResults_List_CURRENT_ScanResultList_Get_ChannelId_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 ChannelId )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetScanResults_List_CURRENT_ScanResultList_Get_ChannelId_SET( base_ptr, cur_ptr, cur_bitoff, ChannelId );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetScanResults_List_CURRENT_ScanResultList_Get_PreambleId_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 PreambleId )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetScanResults_List_CURRENT_ScanResultList_Get_PreambleId_SET( base_ptr, cur_ptr, cur_bitoff, PreambleId );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetScanResults_List_CURRENT_ScanResultList_Get_LinkGrade_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 LinkGrade )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetScanResults_List_CURRENT_ScanResultList_Get_LinkGrade_SET( base_ptr, cur_ptr, cur_bitoff, LinkGrade );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetScanResults_List_CURRENT_ScanResultList_Get_LinkQuality_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 LinkQuality )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetScanResults_List_CURRENT_ScanResultList_Get_LinkQuality_SET( base_ptr, cur_ptr, cur_bitoff, LinkQuality );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetScanResults_Header_Type_SET( UINT8* base_ptr, UINT32 opcode )
{
	BM_GetScanResults_Header_Type_SET( base_ptr, opcode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetScanResults_Header_Version_SET( UINT8* base_ptr, UINT16 version )
{
	BM_GetScanResults_Header_Version_SET( base_ptr, version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetScanResults_Header_Accessibility_SET( UINT8* base_ptr, UINT16 accessibility )
{
	BM_GetScanResults_Header_Accessibility_SET( base_ptr, accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetScanResults_Header_Status_SET( UINT8* base_ptr, UINT16 status )
{
	BM_GetScanResults_Header_Status_SET( base_ptr, status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetScanResults_Header_Length_SET( UINT8* base_ptr, UINT32 len )
{
	BM_GetScanResults_Header_Length_SET( base_ptr, len );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportEMSKRelatedKeys_Header_Version_GET( UINT8* base_ptr, UINT16* version )
{
	BM_ReportEMSKRelatedKeys_Header_Version_GET( base_ptr, *version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportEMSKRelatedKeys_Header_Accessibility_GET( UINT8* base_ptr, UINT16* accessibility )
{
	BM_ReportEMSKRelatedKeys_Header_Accessibility_GET( base_ptr, *accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportEMSKRelatedKeys_Header_Status_GET( UINT8* base_ptr, UINT16* status )
{
	BM_ReportEMSKRelatedKeys_Header_Status_GET( base_ptr, *status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportEMSKRelatedKeys_Header_Length_GET( UINT8* base_ptr, UINT32* listSize )
{
	BM_ReportEMSKRelatedKeys_Header_Length_GET( base_ptr, *listSize );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportEMSKRelatedKeys_List_GET_FIRST( UINT8* base_ptr, UINT32* out_diff, UINT32* out_cur_bitoff )
{
	UINT8* out_cur_ptr = base_ptr;
	BM_ReportEMSKRelatedKeys_List_GET_FIRST( base_ptr, out_cur_ptr, *out_cur_bitoff );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportEMSKRelatedKeys_List_GET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportEMSKRelatedKeys_List_GET_TYPE( cur_ptr, cur_bitoff, *type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportEMSKRelatedKeys_List_GET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_length, UINT32 err )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportEMSKRelatedKeys_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, *out_length, err );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportEMSKRelatedKeys_List_CURRENT_BEK_BEKKeyBufferArr_value_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportEMSKRelatedKeys_List_CURRENT_BEK_BEKKeyBufferArr_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportEMSKRelatedKeys_List_GET_NEXT( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_diff, UINT32* out_cur_bitoff, UINT32 err )
{
	UINT8* out_cur_ptr = base_ptr;
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportEMSKRelatedKeys_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, out_cur_ptr, *out_cur_bitoff, err );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportEMSKRelatedKeys_List_SET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportEMSKRelatedKeys_List_SET_TYPE( cur_ptr, cur_bitoff, type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportEMSKRelatedKeys_List_SET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 lenOfLen, UINT32 length )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	lenOfLen = 2;
	BM_ReportEMSKRelatedKeys_List_SET_LENGTH( cur_ptr, cur_bitoff, lenOfLen, length );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportEMSKRelatedKeys_List_CURRENT_BEK_BEKKeyBufferArr_value_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportEMSKRelatedKeys_List_CURRENT_BEK_BEKKeyBufferArr_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportEMSKRelatedKeys_Header_Type_SET( UINT8* base_ptr, UINT32 opcode )
{
	BM_ReportEMSKRelatedKeys_Header_Type_SET( base_ptr, opcode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportEMSKRelatedKeys_Header_Version_SET( UINT8* base_ptr, UINT16 version )
{
	BM_ReportEMSKRelatedKeys_Header_Version_SET( base_ptr, version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportEMSKRelatedKeys_Header_Accessibility_SET( UINT8* base_ptr, UINT16 accessibility )
{
	BM_ReportEMSKRelatedKeys_Header_Accessibility_SET( base_ptr, accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportEMSKRelatedKeys_Header_Status_SET( UINT8* base_ptr, UINT16 status )
{
	BM_ReportEMSKRelatedKeys_Header_Status_SET( base_ptr, status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportEMSKRelatedKeys_Header_Length_SET( UINT8* base_ptr, UINT32 len )
{
	BM_ReportEMSKRelatedKeys_Header_Length_SET( base_ptr, len );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportScanResults_Header_Version_GET( UINT8* base_ptr, UINT16* version )
{
	BM_ReportScanResults_Header_Version_GET( base_ptr, *version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportScanResults_Header_Accessibility_GET( UINT8* base_ptr, UINT16* accessibility )
{
	BM_ReportScanResults_Header_Accessibility_GET( base_ptr, *accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportScanResults_Header_Status_GET( UINT8* base_ptr, UINT16* status )
{
	BM_ReportScanResults_Header_Status_GET( base_ptr, *status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportScanResults_Header_Length_GET( UINT8* base_ptr, UINT32* listSize )
{
	BM_ReportScanResults_Header_Length_GET( base_ptr, *listSize );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportScanResults_List_GET_FIRST( UINT8* base_ptr, UINT32* out_diff, UINT32* out_cur_bitoff )
{
	UINT8* out_cur_ptr = base_ptr;
	BM_ReportScanResults_List_GET_FIRST( base_ptr, out_cur_ptr, *out_cur_bitoff );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportScanResults_List_GET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportScanResults_List_GET_TYPE( cur_ptr, cur_bitoff, *type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportScanResults_List_GET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_length, UINT32 err )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportScanResults_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, *out_length, err );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportScanResults_List_CURRENT_ScanStatus_value_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportScanResults_List_CURRENT_ScanStatus_value_GET( base_ptr, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportScanResults_List_CURRENT_ScanResultList_Report_Rssi_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* Rssi )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportScanResults_List_CURRENT_ScanResultList_Report_Rssi_GET( base_ptr, cur_ptr, cur_bitoff, *Rssi );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportScanResults_List_CURRENT_ScanResultList_Report_Cinr_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* Cinr )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportScanResults_List_CURRENT_ScanResultList_Report_Cinr_GET( base_ptr, cur_ptr, cur_bitoff, *Cinr );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportScanResults_List_CURRENT_ScanResultList_Report_BsIdmask_value_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportScanResults_List_CURRENT_ScanResultList_Report_BsIdmask_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportScanResults_List_CURRENT_ScanResultList_Report_BsId_value_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportScanResults_List_CURRENT_ScanResultList_Report_BsId_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportScanResults_List_CURRENT_ScanResultList_Report_ChannelId_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* ChannelId )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportScanResults_List_CURRENT_ScanResultList_Report_ChannelId_GET( base_ptr, cur_ptr, cur_bitoff, *ChannelId );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportScanResults_List_CURRENT_ScanResultList_Report_PreambleId_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* PreambleId )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportScanResults_List_CURRENT_ScanResultList_Report_PreambleId_GET( base_ptr, cur_ptr, cur_bitoff, *PreambleId );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportScanResults_List_CURRENT_ScanResultList_Report_LinkGrade_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* LinkGrade )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportScanResults_List_CURRENT_ScanResultList_Report_LinkGrade_GET( base_ptr, cur_ptr, cur_bitoff, *LinkGrade );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportScanResults_List_CURRENT_ScanResultList_Report_LinkQuality_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* LinkQuality )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportScanResults_List_CURRENT_ScanResultList_Report_LinkQuality_GET( base_ptr, cur_ptr, cur_bitoff, *LinkQuality );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportScanResults_List_GET_NEXT( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_diff, UINT32* out_cur_bitoff, UINT32 err )
{
	UINT8* out_cur_ptr = base_ptr;
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportScanResults_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, out_cur_ptr, *out_cur_bitoff, err );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportScanResults_List_SET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportScanResults_List_SET_TYPE( cur_ptr, cur_bitoff, type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportScanResults_List_SET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 lenOfLen, UINT32 length )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	lenOfLen = 2;
	BM_ReportScanResults_List_SET_LENGTH( cur_ptr, cur_bitoff, lenOfLen, length );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportScanResults_List_CURRENT_ScanStatus_value_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportScanResults_List_CURRENT_ScanStatus_value_SET( base_ptr, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportScanResults_List_CURRENT_ScanResultList_Report_Rssi_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 Rssi )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportScanResults_List_CURRENT_ScanResultList_Report_Rssi_SET( base_ptr, cur_ptr, cur_bitoff, Rssi );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportScanResults_List_CURRENT_ScanResultList_Report_Cinr_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 Cinr )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportScanResults_List_CURRENT_ScanResultList_Report_Cinr_SET( base_ptr, cur_ptr, cur_bitoff, Cinr );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportScanResults_List_CURRENT_ScanResultList_Report_BsIdmask_value_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportScanResults_List_CURRENT_ScanResultList_Report_BsIdmask_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportScanResults_List_CURRENT_ScanResultList_Report_BsId_value_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportScanResults_List_CURRENT_ScanResultList_Report_BsId_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportScanResults_List_CURRENT_ScanResultList_Report_ChannelId_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 ChannelId )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportScanResults_List_CURRENT_ScanResultList_Report_ChannelId_SET( base_ptr, cur_ptr, cur_bitoff, ChannelId );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportScanResults_List_CURRENT_ScanResultList_Report_PreambleId_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 PreambleId )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportScanResults_List_CURRENT_ScanResultList_Report_PreambleId_SET( base_ptr, cur_ptr, cur_bitoff, PreambleId );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportScanResults_List_CURRENT_ScanResultList_Report_LinkGrade_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 LinkGrade )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportScanResults_List_CURRENT_ScanResultList_Report_LinkGrade_SET( base_ptr, cur_ptr, cur_bitoff, LinkGrade );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportScanResults_List_CURRENT_ScanResultList_Report_LinkQuality_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 LinkQuality )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportScanResults_List_CURRENT_ScanResultList_Report_LinkQuality_SET( base_ptr, cur_ptr, cur_bitoff, LinkQuality );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportScanResults_Header_Type_SET( UINT8* base_ptr, UINT32 opcode )
{
	BM_ReportScanResults_Header_Type_SET( base_ptr, opcode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportScanResults_Header_Version_SET( UINT8* base_ptr, UINT16 version )
{
	BM_ReportScanResults_Header_Version_SET( base_ptr, version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportScanResults_Header_Accessibility_SET( UINT8* base_ptr, UINT16 accessibility )
{
	BM_ReportScanResults_Header_Accessibility_SET( base_ptr, accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportScanResults_Header_Status_SET( UINT8* base_ptr, UINT16 status )
{
	BM_ReportScanResults_Header_Status_SET( base_ptr, status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportScanResults_Header_Length_SET( UINT8* base_ptr, UINT32 len )
{
	BM_ReportScanResults_Header_Length_SET( base_ptr, len );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetMonitorFilterTable_Header_Version_GET( UINT8* base_ptr, UINT16* version )
{
	BM_SetMonitorFilterTable_Header_Version_GET( base_ptr, *version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetMonitorFilterTable_Header_Accessibility_GET( UINT8* base_ptr, UINT16* accessibility )
{
	BM_SetMonitorFilterTable_Header_Accessibility_GET( base_ptr, *accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetMonitorFilterTable_Header_Status_GET( UINT8* base_ptr, UINT16* status )
{
	BM_SetMonitorFilterTable_Header_Status_GET( base_ptr, *status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetMonitorFilterTable_Header_Length_GET( UINT8* base_ptr, UINT32* listSize )
{
	BM_SetMonitorFilterTable_Header_Length_GET( base_ptr, *listSize );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetMonitorFilterTable_List_GET_FIRST( UINT8* base_ptr, UINT32* out_diff, UINT32* out_cur_bitoff )
{
	UINT8* out_cur_ptr = base_ptr;
	BM_SetMonitorFilterTable_List_GET_FIRST( base_ptr, out_cur_ptr, *out_cur_bitoff );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetMonitorFilterTable_List_GET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetMonitorFilterTable_List_GET_TYPE( cur_ptr, cur_bitoff, *type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetMonitorFilterTable_List_GET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_length, UINT32 err )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetMonitorFilterTable_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, *out_length, err );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetMonitorFilterTable_List_CURRENT_MonitorFilterTable_FilterTable_value_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetMonitorFilterTable_List_CURRENT_MonitorFilterTable_FilterTable_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetMonitorFilterTable_List_GET_NEXT( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_diff, UINT32* out_cur_bitoff, UINT32 err )
{
	UINT8* out_cur_ptr = base_ptr;
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetMonitorFilterTable_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, out_cur_ptr, *out_cur_bitoff, err );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetMonitorFilterTable_List_SET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetMonitorFilterTable_List_SET_TYPE( cur_ptr, cur_bitoff, type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetMonitorFilterTable_List_SET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 lenOfLen, UINT32 length )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	lenOfLen = 2;
	BM_SetMonitorFilterTable_List_SET_LENGTH( cur_ptr, cur_bitoff, lenOfLen, length );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetMonitorFilterTable_List_CURRENT_MonitorFilterTable_FilterTable_value_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetMonitorFilterTable_List_CURRENT_MonitorFilterTable_FilterTable_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetMonitorFilterTable_Header_Type_SET( UINT8* base_ptr, UINT32 opcode )
{
	BM_SetMonitorFilterTable_Header_Type_SET( base_ptr, opcode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetMonitorFilterTable_Header_Version_SET( UINT8* base_ptr, UINT16 version )
{
	BM_SetMonitorFilterTable_Header_Version_SET( base_ptr, version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetMonitorFilterTable_Header_Accessibility_SET( UINT8* base_ptr, UINT16 accessibility )
{
	BM_SetMonitorFilterTable_Header_Accessibility_SET( base_ptr, accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetMonitorFilterTable_Header_Status_SET( UINT8* base_ptr, UINT16 status )
{
	BM_SetMonitorFilterTable_Header_Status_SET( base_ptr, status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetMonitorFilterTable_Header_Length_SET( UINT8* base_ptr, UINT32 len )
{
	BM_SetMonitorFilterTable_Header_Length_SET( base_ptr, len );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetEapSuccess_Header_Version_GET( UINT8* base_ptr, UINT16* version )
{
	BM_SetEapSuccess_Header_Version_GET( base_ptr, *version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetEapSuccess_Header_Accessibility_GET( UINT8* base_ptr, UINT16* accessibility )
{
	BM_SetEapSuccess_Header_Accessibility_GET( base_ptr, *accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetEapSuccess_Header_Status_GET( UINT8* base_ptr, UINT16* status )
{
	BM_SetEapSuccess_Header_Status_GET( base_ptr, *status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetEapSuccess_Header_Type_SET( UINT8* base_ptr, UINT32 opcode )
{
	BM_SetEapSuccess_Header_Type_SET( base_ptr, opcode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetEapSuccess_Header_Version_SET( UINT8* base_ptr, UINT16 version )
{
	BM_SetEapSuccess_Header_Version_SET( base_ptr, version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetEapSuccess_Header_Accessibility_SET( UINT8* base_ptr, UINT16 accessibility )
{
	BM_SetEapSuccess_Header_Accessibility_SET( base_ptr, accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetEapSuccess_Header_Status_SET( UINT8* base_ptr, UINT16 status )
{
	BM_SetEapSuccess_Header_Status_SET( base_ptr, status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetEapSuccess_Header_Length_SET( UINT8* base_ptr, UINT32 len )
{
	BM_SetEapSuccess_Header_Length_SET( base_ptr, len );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CmdCoexProcessEnd_Header_Version_GET( UINT8* base_ptr, UINT16* version )
{
	BM_CmdCoexProcessEnd_Header_Version_GET( base_ptr, *version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CmdCoexProcessEnd_Header_Accessibility_GET( UINT8* base_ptr, UINT16* accessibility )
{
	BM_CmdCoexProcessEnd_Header_Accessibility_GET( base_ptr, *accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CmdCoexProcessEnd_Header_Status_GET( UINT8* base_ptr, UINT16* status )
{
	BM_CmdCoexProcessEnd_Header_Status_GET( base_ptr, *status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CmdCoexProcessEnd_Header_Type_SET( UINT8* base_ptr, UINT32 opcode )
{
	BM_CmdCoexProcessEnd_Header_Type_SET( base_ptr, opcode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CmdCoexProcessEnd_Header_Version_SET( UINT8* base_ptr, UINT16 version )
{
	BM_CmdCoexProcessEnd_Header_Version_SET( base_ptr, version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CmdCoexProcessEnd_Header_Accessibility_SET( UINT8* base_ptr, UINT16 accessibility )
{
	BM_CmdCoexProcessEnd_Header_Accessibility_SET( base_ptr, accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CmdCoexProcessEnd_Header_Status_SET( UINT8* base_ptr, UINT16 status )
{
	BM_CmdCoexProcessEnd_Header_Status_SET( base_ptr, status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CmdCoexProcessEnd_Header_Length_SET( UINT8* base_ptr, UINT32 len )
{
	BM_CmdCoexProcessEnd_Header_Length_SET( base_ptr, len );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetD2HChannelMask_Header_Version_GET( UINT8* base_ptr, UINT16* version )
{
	BM_GetD2HChannelMask_Header_Version_GET( base_ptr, *version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetD2HChannelMask_Header_Accessibility_GET( UINT8* base_ptr, UINT16* accessibility )
{
	BM_GetD2HChannelMask_Header_Accessibility_GET( base_ptr, *accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetD2HChannelMask_Header_Status_GET( UINT8* base_ptr, UINT16* status )
{
	BM_GetD2HChannelMask_Header_Status_GET( base_ptr, *status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetD2HChannelMask_Header_Length_GET( UINT8* base_ptr, UINT32* listSize )
{
	BM_GetD2HChannelMask_Header_Length_GET( base_ptr, *listSize );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetD2HChannelMask_List_GET_FIRST( UINT8* base_ptr, UINT32* out_diff, UINT32* out_cur_bitoff )
{
	UINT8* out_cur_ptr = base_ptr;
	BM_GetD2HChannelMask_List_GET_FIRST( base_ptr, out_cur_ptr, *out_cur_bitoff );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetD2HChannelMask_List_GET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetD2HChannelMask_List_GET_TYPE( cur_ptr, cur_bitoff, *type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetD2HChannelMask_List_GET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_length, UINT32 err )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetD2HChannelMask_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, *out_length, err );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetD2HChannelMask_List_CURRENT_D2HChannelMask_DataChannelSwitch_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* DataChannelSwitch )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetD2HChannelMask_List_CURRENT_D2HChannelMask_DataChannelSwitch_GET( base_ptr, cur_ptr, cur_bitoff, *DataChannelSwitch );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetD2HChannelMask_List_CURRENT_D2HChannelMask_DiagnosticsChannelSwitch_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* DiagnosticsChannelSwitch )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetD2HChannelMask_List_CURRENT_D2HChannelMask_DiagnosticsChannelSwitch_GET( base_ptr, cur_ptr, cur_bitoff, *DiagnosticsChannelSwitch );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetD2HChannelMask_List_CURRENT_D2HChannelMask_Reserved_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* Reserved )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetD2HChannelMask_List_CURRENT_D2HChannelMask_Reserved_GET( base_ptr, cur_ptr, cur_bitoff, *Reserved );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetD2HChannelMask_List_GET_NEXT( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_diff, UINT32* out_cur_bitoff, UINT32 err )
{
	UINT8* out_cur_ptr = base_ptr;
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetD2HChannelMask_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, out_cur_ptr, *out_cur_bitoff, err );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetD2HChannelMask_List_SET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetD2HChannelMask_List_SET_TYPE( cur_ptr, cur_bitoff, type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetD2HChannelMask_List_SET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 lenOfLen, UINT32 length )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	lenOfLen = 2;
	BM_GetD2HChannelMask_List_SET_LENGTH( cur_ptr, cur_bitoff, lenOfLen, length );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetD2HChannelMask_List_CURRENT_D2HChannelMask_DataChannelSwitch_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 DataChannelSwitch )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetD2HChannelMask_List_CURRENT_D2HChannelMask_DataChannelSwitch_SET( base_ptr, cur_ptr, cur_bitoff, DataChannelSwitch );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetD2HChannelMask_List_CURRENT_D2HChannelMask_DiagnosticsChannelSwitch_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 DiagnosticsChannelSwitch )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetD2HChannelMask_List_CURRENT_D2HChannelMask_DiagnosticsChannelSwitch_SET( base_ptr, cur_ptr, cur_bitoff, DiagnosticsChannelSwitch );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetD2HChannelMask_List_CURRENT_D2HChannelMask_Reserved_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 Reserved )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetD2HChannelMask_List_CURRENT_D2HChannelMask_Reserved_SET( base_ptr, cur_ptr, cur_bitoff, Reserved );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetD2HChannelMask_Header_Type_SET( UINT8* base_ptr, UINT32 opcode )
{
	BM_GetD2HChannelMask_Header_Type_SET( base_ptr, opcode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetD2HChannelMask_Header_Version_SET( UINT8* base_ptr, UINT16 version )
{
	BM_GetD2HChannelMask_Header_Version_SET( base_ptr, version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetD2HChannelMask_Header_Accessibility_SET( UINT8* base_ptr, UINT16 accessibility )
{
	BM_GetD2HChannelMask_Header_Accessibility_SET( base_ptr, accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetD2HChannelMask_Header_Status_SET( UINT8* base_ptr, UINT16 status )
{
	BM_GetD2HChannelMask_Header_Status_SET( base_ptr, status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetD2HChannelMask_Header_Length_SET( UINT8* base_ptr, UINT32 len )
{
	BM_GetD2HChannelMask_Header_Length_SET( base_ptr, len );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_Header_Version_GET( UINT8* base_ptr, UINT16* version )
{
	BM_SetPreInitConfiguration_Header_Version_GET( base_ptr, *version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_Header_Accessibility_GET( UINT8* base_ptr, UINT16* accessibility )
{
	BM_SetPreInitConfiguration_Header_Accessibility_GET( base_ptr, *accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_Header_Status_GET( UINT8* base_ptr, UINT16* status )
{
	BM_SetPreInitConfiguration_Header_Status_GET( base_ptr, *status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_Header_Length_GET( UINT8* base_ptr, UINT32* listSize )
{
	BM_SetPreInitConfiguration_Header_Length_GET( base_ptr, *listSize );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_GET_FIRST( UINT8* base_ptr, UINT32* out_diff, UINT32* out_cur_bitoff )
{
	UINT8* out_cur_ptr = base_ptr;
	BM_SetPreInitConfiguration_List_GET_FIRST( base_ptr, out_cur_ptr, *out_cur_bitoff );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_GET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_GET_TYPE( cur_ptr, cur_bitoff, *type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_GET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_length, UINT32 err )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, *out_length, err );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_PrivilegeKeyConfigComp_Key_value_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_PrivilegeKeyConfigComp_Key_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_LedOperationalConfigComp_NvmOverride_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* NvmOverride )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_LedOperationalConfigComp_NvmOverride_GET( base_ptr, cur_ptr, cur_bitoff, *NvmOverride );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_LedOperationalConfigComp_ledBehavior_Led0Scheme_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* Led0Scheme )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_LedOperationalConfigComp_ledBehavior_Led0Scheme_GET( base_ptr, i0, cur_ptr, cur_bitoff, *Led0Scheme );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_LedOperationalConfigComp_ledBehavior_Led1Scheme_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* Led1Scheme )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_LedOperationalConfigComp_ledBehavior_Led1Scheme_GET( base_ptr, i0, cur_ptr, cur_bitoff, *Led1Scheme );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_LedOperationalConfigComp_powerSaveInfo_ledBlinkRate_onPeriod_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* onPeriod )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_LedOperationalConfigComp_powerSaveInfo_ledBlinkRate_onPeriod_GET( base_ptr, cur_ptr, cur_bitoff, *onPeriod );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_LedOperationalConfigComp_powerSaveInfo_ledBlinkRate_offPeriod_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* offPeriod )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_LedOperationalConfigComp_powerSaveInfo_ledBlinkRate_offPeriod_GET( base_ptr, cur_ptr, cur_bitoff, *offPeriod );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_LedOperationalConfigComp_powerSaveInfo_powerSaveMode_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* powerSaveMode )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_LedOperationalConfigComp_powerSaveInfo_powerSaveMode_GET( base_ptr, cur_ptr, cur_bitoff, *powerSaveMode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_LedOperationalConfigComp_powerSaveInfo_ledTimeInterval_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* ledTimeInterval )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_LedOperationalConfigComp_powerSaveInfo_ledTimeInterval_GET( base_ptr, cur_ptr, cur_bitoff, *ledTimeInterval );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_LedOperationalConfigComp_numOfLeds_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* numOfLeds )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_LedOperationalConfigComp_numOfLeds_GET( base_ptr, cur_ptr, cur_bitoff, *numOfLeds );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_LedOperationalConfigComp_blinkingRate_onPeriod_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* onPeriod )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_LedOperationalConfigComp_blinkingRate_onPeriod_GET( base_ptr, i0, cur_ptr, cur_bitoff, *onPeriod );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_LedOperationalConfigComp_blinkingRate_offPeriod_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* offPeriod )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_LedOperationalConfigComp_blinkingRate_offPeriod_GET( base_ptr, i0, cur_ptr, cur_bitoff, *offPeriod );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_LedOperationalConfigComp_reserved_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* reserved )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_LedOperationalConfigComp_reserved_GET( base_ptr, cur_ptr, cur_bitoff, *reserved );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_LimitMaxTxPowerConfigComp_LimitMaxTxPower_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* LimitMaxTxPower )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_LimitMaxTxPowerConfigComp_LimitMaxTxPower_GET( base_ptr, cur_ptr, cur_bitoff, *LimitMaxTxPower );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_IdleParametersConfigComp_IdleTimeout_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* IdleTimeout )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_IdleParametersConfigComp_IdleTimeout_GET( base_ptr, cur_ptr, cur_bitoff, *IdleTimeout );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_IdleParametersConfigComp_IdlePagingInterval_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* IdlePagingInterval )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_IdleParametersConfigComp_IdlePagingInterval_GET( base_ptr, cur_ptr, cur_bitoff, *IdlePagingInterval );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_IdleParameterTimeoutConfigComp_IdleTimeout_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* IdleTimeout )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_IdleParameterTimeoutConfigComp_IdleTimeout_GET( base_ptr, cur_ptr, cur_bitoff, *IdleTimeout );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_IdleParameterPagingIntervalConfigComp_PagingInterval_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* PagingInterval )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_IdleParameterPagingIntervalConfigComp_PagingInterval_GET( base_ptr, cur_ptr, cur_bitoff, *PagingInterval );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_IdleParameterIdleEntrySuspendConfigComp_IdleEntrySuspend_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* IdleEntrySuspend )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_IdleParameterIdleEntrySuspendConfigComp_IdleEntrySuspend_GET( base_ptr, cur_ptr, cur_bitoff, *IdleEntrySuspend );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_IdleParameterFullNeSuspendConfigComp_FullNeSuspend_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* FullNeSuspend )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_IdleParameterFullNeSuspendConfigComp_FullNeSuspend_GET( base_ptr, cur_ptr, cur_bitoff, *FullNeSuspend );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_LinkDownTimerConfigComp_LinkDown_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* LinkDown )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_LinkDownTimerConfigComp_LinkDown_GET( base_ptr, cur_ptr, cur_bitoff, *LinkDown );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_ArqSupportConfigComp_GeneralState_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* GeneralState )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_ArqSupportConfigComp_GeneralState_GET( base_ptr, cur_ptr, cur_bitoff, *GeneralState );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_ArqSupportConfigComp_Reserved1_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* Reserved1 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_ArqSupportConfigComp_Reserved1_GET( base_ptr, cur_ptr, cur_bitoff, *Reserved1 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_ArqSupportConfigComp_Reserved2_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* Reserved2 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_ArqSupportConfigComp_Reserved2_GET( base_ptr, cur_ptr, cur_bitoff, *Reserved2 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_LoopBackConfigComp_OperationMode_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* OperationMode )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_LoopBackConfigComp_OperationMode_GET( base_ptr, cur_ptr, cur_bitoff, *OperationMode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_LoopBackConfigComp_Reserved1_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* Reserved1 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_LoopBackConfigComp_Reserved1_GET( base_ptr, cur_ptr, cur_bitoff, *Reserved1 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_LoopBackConfigComp_Reserved2_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* Reserved2 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_LoopBackConfigComp_Reserved2_GET( base_ptr, cur_ptr, cur_bitoff, *Reserved2 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_ResetOnAssertConfigComp_GeneralState_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* GeneralState )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_ResetOnAssertConfigComp_GeneralState_GET( base_ptr, cur_ptr, cur_bitoff, *GeneralState );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_ResetOnAssertConfigComp_Reserved1_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* Reserved1 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_ResetOnAssertConfigComp_Reserved1_GET( base_ptr, cur_ptr, cur_bitoff, *Reserved1 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_ResetOnAssertConfigComp_Reserved2_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* Reserved2 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_ResetOnAssertConfigComp_Reserved2_GET( base_ptr, cur_ptr, cur_bitoff, *Reserved2 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_WatchDogTimerConfigComp_GeneralState_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* GeneralState )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_WatchDogTimerConfigComp_GeneralState_GET( base_ptr, cur_ptr, cur_bitoff, *GeneralState );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_WatchDogTimerConfigComp_Reserved1_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* Reserved1 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_WatchDogTimerConfigComp_Reserved1_GET( base_ptr, cur_ptr, cur_bitoff, *Reserved1 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_WatchDogTimerConfigComp_Reserved2_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* Reserved2 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_WatchDogTimerConfigComp_Reserved2_GET( base_ptr, cur_ptr, cur_bitoff, *Reserved2 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_SlowClockConfigComp_GeneralState_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* GeneralState )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_SlowClockConfigComp_GeneralState_GET( base_ptr, cur_ptr, cur_bitoff, *GeneralState );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_SlowClockConfigComp_Reserved1_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* Reserved1 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_SlowClockConfigComp_Reserved1_GET( base_ptr, cur_ptr, cur_bitoff, *Reserved1 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_SlowClockConfigComp_Reserved2_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* Reserved2 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_SlowClockConfigComp_Reserved2_GET( base_ptr, cur_ptr, cur_bitoff, *Reserved2 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_SelectivePLIParametersConfigComp_EnableSelectivePLIs_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* EnableSelectivePLIs )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_SelectivePLIParametersConfigComp_EnableSelectivePLIs_GET( base_ptr, cur_ptr, cur_bitoff, *EnableSelectivePLIs );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_SelectivePLIParametersConfigComp_DelayedSelectivePLI_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* DelayedSelectivePLI )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_SelectivePLIParametersConfigComp_DelayedSelectivePLI_GET( base_ptr, cur_ptr, cur_bitoff, *DelayedSelectivePLI );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_SelectivePLIParametersConfigComp_ConsecutivePLIToReceive_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* ConsecutivePLIToReceive )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_SelectivePLIParametersConfigComp_ConsecutivePLIToReceive_GET( base_ptr, cur_ptr, cur_bitoff, *ConsecutivePLIToReceive );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_SelectivePLIParametersConfigComp_Reserved1_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* Reserved1 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_SelectivePLIParametersConfigComp_Reserved1_GET( base_ptr, cur_ptr, cur_bitoff, *Reserved1 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_HarqParametersConfigComp_HarqCategory_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* HarqCategory )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_HarqParametersConfigComp_HarqCategory_GET( base_ptr, cur_ptr, cur_bitoff, *HarqCategory );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_HarqParametersConfigComp_Reserved1_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* Reserved1 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_HarqParametersConfigComp_Reserved1_GET( base_ptr, cur_ptr, cur_bitoff, *Reserved1 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_HarqParametersConfigComp_Reserved2_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* Reserved2 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_HarqParametersConfigComp_Reserved2_GET( base_ptr, cur_ptr, cur_bitoff, *Reserved2 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_D2HDataFormatConfigComp_DataFormatMem_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, DataFormat* DataFormatMem )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_D2HDataFormatConfigComp_DataFormatMem_GET( base_ptr, cur_ptr, cur_bitoff, *DataFormatMem );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_D2HDataFormatConfigComp_Reserved1_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* Reserved1 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_D2HDataFormatConfigComp_Reserved1_GET( base_ptr, cur_ptr, cur_bitoff, *Reserved1 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_D2HDataFormatConfigComp_Reserved2_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* Reserved2 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_D2HDataFormatConfigComp_Reserved2_GET( base_ptr, cur_ptr, cur_bitoff, *Reserved2 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_DLHostReorderConfigComp_DLHostReorder_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* DLHostReorder )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_DLHostReorderConfigComp_DLHostReorder_GET( base_ptr, cur_ptr, cur_bitoff, *DLHostReorder );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_DLHostReorderConfigComp_Reserved1_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* Reserved1 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_DLHostReorderConfigComp_Reserved1_GET( base_ptr, cur_ptr, cur_bitoff, *Reserved1 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_DLHostReorderConfigComp_Reserved2_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* Reserved2 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_DLHostReorderConfigComp_Reserved2_GET( base_ptr, cur_ptr, cur_bitoff, *Reserved2 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_PaddingPerCSConfigComp_CSType_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* CSType )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_PaddingPerCSConfigComp_CSType_GET( base_ptr, cur_ptr, cur_bitoff, *CSType );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_PaddingPerCSConfigComp_PaddingSize_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* PaddingSize )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_PaddingPerCSConfigComp_PaddingSize_GET( base_ptr, cur_ptr, cur_bitoff, *PaddingSize );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_PaddingPerCSConfigComp_Reserved_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* Reserved )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_PaddingPerCSConfigComp_Reserved_GET( base_ptr, cur_ptr, cur_bitoff, *Reserved );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_GET_NEXT( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_diff, UINT32* out_cur_bitoff, UINT32 err )
{
	UINT8* out_cur_ptr = base_ptr;
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, out_cur_ptr, *out_cur_bitoff, err );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_SET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_SET_TYPE( cur_ptr, cur_bitoff, type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_SET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 lenOfLen, UINT32 length )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	lenOfLen = 2;
	BM_SetPreInitConfiguration_List_SET_LENGTH( cur_ptr, cur_bitoff, lenOfLen, length );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_PrivilegeKeyConfigComp_Key_value_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_PrivilegeKeyConfigComp_Key_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_LedOperationalConfigComp_NvmOverride_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 NvmOverride )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_LedOperationalConfigComp_NvmOverride_SET( base_ptr, cur_ptr, cur_bitoff, NvmOverride );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_LedOperationalConfigComp_ledBehavior_Led0Scheme_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 Led0Scheme )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_LedOperationalConfigComp_ledBehavior_Led0Scheme_SET( base_ptr, i0, cur_ptr, cur_bitoff, Led0Scheme );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_LedOperationalConfigComp_ledBehavior_Led1Scheme_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 Led1Scheme )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_LedOperationalConfigComp_ledBehavior_Led1Scheme_SET( base_ptr, i0, cur_ptr, cur_bitoff, Led1Scheme );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_LedOperationalConfigComp_powerSaveInfo_ledBlinkRate_onPeriod_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 onPeriod )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_LedOperationalConfigComp_powerSaveInfo_ledBlinkRate_onPeriod_SET( base_ptr, cur_ptr, cur_bitoff, onPeriod );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_LedOperationalConfigComp_powerSaveInfo_ledBlinkRate_offPeriod_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 offPeriod )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_LedOperationalConfigComp_powerSaveInfo_ledBlinkRate_offPeriod_SET( base_ptr, cur_ptr, cur_bitoff, offPeriod );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_LedOperationalConfigComp_powerSaveInfo_powerSaveMode_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 powerSaveMode )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_LedOperationalConfigComp_powerSaveInfo_powerSaveMode_SET( base_ptr, cur_ptr, cur_bitoff, powerSaveMode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_LedOperationalConfigComp_powerSaveInfo_ledTimeInterval_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 ledTimeInterval )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_LedOperationalConfigComp_powerSaveInfo_ledTimeInterval_SET( base_ptr, cur_ptr, cur_bitoff, ledTimeInterval );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_LedOperationalConfigComp_numOfLeds_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 numOfLeds )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_LedOperationalConfigComp_numOfLeds_SET( base_ptr, cur_ptr, cur_bitoff, numOfLeds );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_LedOperationalConfigComp_blinkingRate_onPeriod_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 onPeriod )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_LedOperationalConfigComp_blinkingRate_onPeriod_SET( base_ptr, i0, cur_ptr, cur_bitoff, onPeriod );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_LedOperationalConfigComp_blinkingRate_offPeriod_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 offPeriod )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_LedOperationalConfigComp_blinkingRate_offPeriod_SET( base_ptr, i0, cur_ptr, cur_bitoff, offPeriod );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_LedOperationalConfigComp_reserved_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 reserved )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_LedOperationalConfigComp_reserved_SET( base_ptr, cur_ptr, cur_bitoff, reserved );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_LimitMaxTxPowerConfigComp_LimitMaxTxPower_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 LimitMaxTxPower )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_LimitMaxTxPowerConfigComp_LimitMaxTxPower_SET( base_ptr, cur_ptr, cur_bitoff, LimitMaxTxPower );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_IdleParametersConfigComp_IdleTimeout_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 IdleTimeout )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_IdleParametersConfigComp_IdleTimeout_SET( base_ptr, cur_ptr, cur_bitoff, IdleTimeout );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_IdleParametersConfigComp_IdlePagingInterval_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 IdlePagingInterval )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_IdleParametersConfigComp_IdlePagingInterval_SET( base_ptr, cur_ptr, cur_bitoff, IdlePagingInterval );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_IdleParameterTimeoutConfigComp_IdleTimeout_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 IdleTimeout )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_IdleParameterTimeoutConfigComp_IdleTimeout_SET( base_ptr, cur_ptr, cur_bitoff, IdleTimeout );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_IdleParameterPagingIntervalConfigComp_PagingInterval_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 PagingInterval )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_IdleParameterPagingIntervalConfigComp_PagingInterval_SET( base_ptr, cur_ptr, cur_bitoff, PagingInterval );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_IdleParameterIdleEntrySuspendConfigComp_IdleEntrySuspend_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 IdleEntrySuspend )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_IdleParameterIdleEntrySuspendConfigComp_IdleEntrySuspend_SET( base_ptr, cur_ptr, cur_bitoff, IdleEntrySuspend );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_IdleParameterFullNeSuspendConfigComp_FullNeSuspend_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 FullNeSuspend )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_IdleParameterFullNeSuspendConfigComp_FullNeSuspend_SET( base_ptr, cur_ptr, cur_bitoff, FullNeSuspend );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_LinkDownTimerConfigComp_LinkDown_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 LinkDown )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_LinkDownTimerConfigComp_LinkDown_SET( base_ptr, cur_ptr, cur_bitoff, LinkDown );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_ArqSupportConfigComp_GeneralState_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 GeneralState )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_ArqSupportConfigComp_GeneralState_SET( base_ptr, cur_ptr, cur_bitoff, GeneralState );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_ArqSupportConfigComp_Reserved1_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 Reserved1 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_ArqSupportConfigComp_Reserved1_SET( base_ptr, cur_ptr, cur_bitoff, Reserved1 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_ArqSupportConfigComp_Reserved2_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 Reserved2 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_ArqSupportConfigComp_Reserved2_SET( base_ptr, cur_ptr, cur_bitoff, Reserved2 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_LoopBackConfigComp_OperationMode_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 OperationMode )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_LoopBackConfigComp_OperationMode_SET( base_ptr, cur_ptr, cur_bitoff, OperationMode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_LoopBackConfigComp_Reserved1_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 Reserved1 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_LoopBackConfigComp_Reserved1_SET( base_ptr, cur_ptr, cur_bitoff, Reserved1 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_LoopBackConfigComp_Reserved2_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 Reserved2 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_LoopBackConfigComp_Reserved2_SET( base_ptr, cur_ptr, cur_bitoff, Reserved2 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_ResetOnAssertConfigComp_GeneralState_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 GeneralState )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_ResetOnAssertConfigComp_GeneralState_SET( base_ptr, cur_ptr, cur_bitoff, GeneralState );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_ResetOnAssertConfigComp_Reserved1_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 Reserved1 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_ResetOnAssertConfigComp_Reserved1_SET( base_ptr, cur_ptr, cur_bitoff, Reserved1 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_ResetOnAssertConfigComp_Reserved2_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 Reserved2 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_ResetOnAssertConfigComp_Reserved2_SET( base_ptr, cur_ptr, cur_bitoff, Reserved2 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_WatchDogTimerConfigComp_GeneralState_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 GeneralState )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_WatchDogTimerConfigComp_GeneralState_SET( base_ptr, cur_ptr, cur_bitoff, GeneralState );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_WatchDogTimerConfigComp_Reserved1_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 Reserved1 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_WatchDogTimerConfigComp_Reserved1_SET( base_ptr, cur_ptr, cur_bitoff, Reserved1 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_WatchDogTimerConfigComp_Reserved2_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 Reserved2 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_WatchDogTimerConfigComp_Reserved2_SET( base_ptr, cur_ptr, cur_bitoff, Reserved2 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_SlowClockConfigComp_GeneralState_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 GeneralState )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_SlowClockConfigComp_GeneralState_SET( base_ptr, cur_ptr, cur_bitoff, GeneralState );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_SlowClockConfigComp_Reserved1_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 Reserved1 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_SlowClockConfigComp_Reserved1_SET( base_ptr, cur_ptr, cur_bitoff, Reserved1 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_SlowClockConfigComp_Reserved2_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 Reserved2 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_SlowClockConfigComp_Reserved2_SET( base_ptr, cur_ptr, cur_bitoff, Reserved2 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_SelectivePLIParametersConfigComp_EnableSelectivePLIs_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 EnableSelectivePLIs )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_SelectivePLIParametersConfigComp_EnableSelectivePLIs_SET( base_ptr, cur_ptr, cur_bitoff, EnableSelectivePLIs );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_SelectivePLIParametersConfigComp_DelayedSelectivePLI_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 DelayedSelectivePLI )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_SelectivePLIParametersConfigComp_DelayedSelectivePLI_SET( base_ptr, cur_ptr, cur_bitoff, DelayedSelectivePLI );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_SelectivePLIParametersConfigComp_ConsecutivePLIToReceive_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 ConsecutivePLIToReceive )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_SelectivePLIParametersConfigComp_ConsecutivePLIToReceive_SET( base_ptr, cur_ptr, cur_bitoff, ConsecutivePLIToReceive );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_SelectivePLIParametersConfigComp_Reserved1_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 Reserved1 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_SelectivePLIParametersConfigComp_Reserved1_SET( base_ptr, cur_ptr, cur_bitoff, Reserved1 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_HarqParametersConfigComp_HarqCategory_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 HarqCategory )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_HarqParametersConfigComp_HarqCategory_SET( base_ptr, cur_ptr, cur_bitoff, HarqCategory );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_HarqParametersConfigComp_Reserved1_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 Reserved1 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_HarqParametersConfigComp_Reserved1_SET( base_ptr, cur_ptr, cur_bitoff, Reserved1 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_HarqParametersConfigComp_Reserved2_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 Reserved2 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_HarqParametersConfigComp_Reserved2_SET( base_ptr, cur_ptr, cur_bitoff, Reserved2 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_D2HDataFormatConfigComp_DataFormatMem_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, DataFormat DataFormatMem )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_D2HDataFormatConfigComp_DataFormatMem_SET( base_ptr, cur_ptr, cur_bitoff, DataFormatMem );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_D2HDataFormatConfigComp_Reserved1_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 Reserved1 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_D2HDataFormatConfigComp_Reserved1_SET( base_ptr, cur_ptr, cur_bitoff, Reserved1 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_D2HDataFormatConfigComp_Reserved2_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 Reserved2 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_D2HDataFormatConfigComp_Reserved2_SET( base_ptr, cur_ptr, cur_bitoff, Reserved2 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_DLHostReorderConfigComp_DLHostReorder_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 DLHostReorder )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_DLHostReorderConfigComp_DLHostReorder_SET( base_ptr, cur_ptr, cur_bitoff, DLHostReorder );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_DLHostReorderConfigComp_Reserved1_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 Reserved1 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_DLHostReorderConfigComp_Reserved1_SET( base_ptr, cur_ptr, cur_bitoff, Reserved1 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_DLHostReorderConfigComp_Reserved2_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 Reserved2 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_DLHostReorderConfigComp_Reserved2_SET( base_ptr, cur_ptr, cur_bitoff, Reserved2 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_PaddingPerCSConfigComp_CSType_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 CSType )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_PaddingPerCSConfigComp_CSType_SET( base_ptr, cur_ptr, cur_bitoff, CSType );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_PaddingPerCSConfigComp_PaddingSize_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 PaddingSize )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_PaddingPerCSConfigComp_PaddingSize_SET( base_ptr, cur_ptr, cur_bitoff, PaddingSize );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_List_CURRENT_PaddingPerCSConfigComp_Reserved_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 Reserved )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetPreInitConfiguration_List_CURRENT_PaddingPerCSConfigComp_Reserved_SET( base_ptr, cur_ptr, cur_bitoff, Reserved );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_Header_Type_SET( UINT8* base_ptr, UINT32 opcode )
{
	BM_SetPreInitConfiguration_Header_Type_SET( base_ptr, opcode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_Header_Version_SET( UINT8* base_ptr, UINT16 version )
{
	BM_SetPreInitConfiguration_Header_Version_SET( base_ptr, version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_Header_Accessibility_SET( UINT8* base_ptr, UINT16 accessibility )
{
	BM_SetPreInitConfiguration_Header_Accessibility_SET( base_ptr, accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_Header_Status_SET( UINT8* base_ptr, UINT16 status )
{
	BM_SetPreInitConfiguration_Header_Status_SET( base_ptr, status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetPreInitConfiguration_Header_Length_SET( UINT8* base_ptr, UINT32 len )
{
	BM_SetPreInitConfiguration_Header_Length_SET( base_ptr, len );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceGET_Header_Version_GET( UINT8* base_ptr, UINT16* version )
{
	BM_CheckL3L4InterfaceGET_Header_Version_GET( base_ptr, *version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceGET_Header_Accessibility_GET( UINT8* base_ptr, UINT16* accessibility )
{
	BM_CheckL3L4InterfaceGET_Header_Accessibility_GET( base_ptr, *accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceGET_Header_Status_GET( UINT8* base_ptr, UINT16* status )
{
	BM_CheckL3L4InterfaceGET_Header_Status_GET( base_ptr, *status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceGET_Header_Length_GET( UINT8* base_ptr, UINT32* listSize )
{
	BM_CheckL3L4InterfaceGET_Header_Length_GET( base_ptr, *listSize );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceGET_List_GET_FIRST( UINT8* base_ptr, UINT32* out_diff, UINT32* out_cur_bitoff )
{
	UINT8* out_cur_ptr = base_ptr;
	BM_CheckL3L4InterfaceGET_List_GET_FIRST( base_ptr, out_cur_ptr, *out_cur_bitoff );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceGET_List_GET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_CheckL3L4InterfaceGET_List_GET_TYPE( cur_ptr, cur_bitoff, *type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceGET_List_GET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_length, UINT32 err )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_CheckL3L4InterfaceGET_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, *out_length, err );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceGET_List_CURRENT_value_value_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_CheckL3L4InterfaceGET_List_CURRENT_value_value_GET( base_ptr, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceGET_List_GET_NEXT( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_diff, UINT32* out_cur_bitoff, UINT32 err )
{
	UINT8* out_cur_ptr = base_ptr;
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_CheckL3L4InterfaceGET_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, out_cur_ptr, *out_cur_bitoff, err );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceGET_List_SET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_CheckL3L4InterfaceGET_List_SET_TYPE( cur_ptr, cur_bitoff, type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceGET_List_SET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 lenOfLen, UINT32 length )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	lenOfLen = 2;
	BM_CheckL3L4InterfaceGET_List_SET_LENGTH( cur_ptr, cur_bitoff, lenOfLen, length );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceGET_List_CURRENT_value_value_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_CheckL3L4InterfaceGET_List_CURRENT_value_value_SET( base_ptr, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceGET_Header_Type_SET( UINT8* base_ptr, UINT32 opcode )
{
	BM_CheckL3L4InterfaceGET_Header_Type_SET( base_ptr, opcode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceGET_Header_Version_SET( UINT8* base_ptr, UINT16 version )
{
	BM_CheckL3L4InterfaceGET_Header_Version_SET( base_ptr, version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceGET_Header_Accessibility_SET( UINT8* base_ptr, UINT16 accessibility )
{
	BM_CheckL3L4InterfaceGET_Header_Accessibility_SET( base_ptr, accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceGET_Header_Status_SET( UINT8* base_ptr, UINT16 status )
{
	BM_CheckL3L4InterfaceGET_Header_Status_SET( base_ptr, status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceGET_Header_Length_SET( UINT8* base_ptr, UINT32 len )
{
	BM_CheckL3L4InterfaceGET_Header_Length_SET( base_ptr, len );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportSII_Header_Version_GET( UINT8* base_ptr, UINT16* version )
{
	BM_ReportSII_Header_Version_GET( base_ptr, *version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportSII_Header_Accessibility_GET( UINT8* base_ptr, UINT16* accessibility )
{
	BM_ReportSII_Header_Accessibility_GET( base_ptr, *accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportSII_Header_Status_GET( UINT8* base_ptr, UINT16* status )
{
	BM_ReportSII_Header_Status_GET( base_ptr, *status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportSII_Header_Length_GET( UINT8* base_ptr, UINT32* listSize )
{
	BM_ReportSII_Header_Length_GET( base_ptr, *listSize );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportSII_List_GET_FIRST( UINT8* base_ptr, UINT32* out_diff, UINT32* out_cur_bitoff )
{
	UINT8* out_cur_ptr = base_ptr;
	BM_ReportSII_List_GET_FIRST( base_ptr, out_cur_ptr, *out_cur_bitoff );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportSII_List_GET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportSII_List_GET_TYPE( cur_ptr, cur_bitoff, *type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportSII_List_GET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_length, UINT32 err )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportSII_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, *out_length, err );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportSII_List_CURRENT_NSPIDList_NspIdListLength_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* NspIdListLength )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportSII_List_CURRENT_NSPIDList_NspIdListLength_GET( base_ptr, cur_ptr, cur_bitoff, *NspIdListLength );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportSII_List_CURRENT_NSPIDList_NspIdListData_value_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportSII_List_CURRENT_NSPIDList_NspIdListData_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportSII_List_CURRENT_NSPVerboseNameList_NspVerboseListLength_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* NspVerboseListLength )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportSII_List_CURRENT_NSPVerboseNameList_NspVerboseListLength_GET( base_ptr, cur_ptr, cur_bitoff, *NspVerboseListLength );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportSII_List_CURRENT_NSPVerboseNameList_NspVerboseListData_value_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportSII_List_CURRENT_NSPVerboseNameList_NspVerboseListData_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportSII_List_CURRENT_Realm_RealmLength_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* RealmLength )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportSII_List_CURRENT_Realm_RealmLength_GET( base_ptr, cur_ptr, cur_bitoff, *RealmLength );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportSII_List_CURRENT_Realm_RealmData_value_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportSII_List_CURRENT_Realm_RealmData_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportSII_List_GET_NEXT( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_diff, UINT32* out_cur_bitoff, UINT32 err )
{
	UINT8* out_cur_ptr = base_ptr;
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportSII_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, out_cur_ptr, *out_cur_bitoff, err );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportSII_List_SET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportSII_List_SET_TYPE( cur_ptr, cur_bitoff, type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportSII_List_SET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 lenOfLen, UINT32 length )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	lenOfLen = 2;
	BM_ReportSII_List_SET_LENGTH( cur_ptr, cur_bitoff, lenOfLen, length );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportSII_List_CURRENT_NSPIDList_NspIdListLength_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 NspIdListLength )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportSII_List_CURRENT_NSPIDList_NspIdListLength_SET( base_ptr, cur_ptr, cur_bitoff, NspIdListLength );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportSII_List_CURRENT_NSPIDList_NspIdListData_value_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportSII_List_CURRENT_NSPIDList_NspIdListData_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportSII_List_CURRENT_NSPVerboseNameList_NspVerboseListLength_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 NspVerboseListLength )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportSII_List_CURRENT_NSPVerboseNameList_NspVerboseListLength_SET( base_ptr, cur_ptr, cur_bitoff, NspVerboseListLength );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportSII_List_CURRENT_NSPVerboseNameList_NspVerboseListData_value_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportSII_List_CURRENT_NSPVerboseNameList_NspVerboseListData_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportSII_List_CURRENT_Realm_RealmLength_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 RealmLength )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportSII_List_CURRENT_Realm_RealmLength_SET( base_ptr, cur_ptr, cur_bitoff, RealmLength );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportSII_List_CURRENT_Realm_RealmData_value_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportSII_List_CURRENT_Realm_RealmData_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportSII_Header_Type_SET( UINT8* base_ptr, UINT32 opcode )
{
	BM_ReportSII_Header_Type_SET( base_ptr, opcode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportSII_Header_Version_SET( UINT8* base_ptr, UINT16 version )
{
	BM_ReportSII_Header_Version_SET( base_ptr, version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportSII_Header_Accessibility_SET( UINT8* base_ptr, UINT16 accessibility )
{
	BM_ReportSII_Header_Accessibility_SET( base_ptr, accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportSII_Header_Status_SET( UINT8* base_ptr, UINT16 status )
{
	BM_ReportSII_Header_Status_SET( base_ptr, status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportSII_Header_Length_SET( UINT8* base_ptr, UINT32 len )
{
	BM_ReportSII_Header_Length_SET( base_ptr, len );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_TerminateCommand_Header_Version_GET( UINT8* base_ptr, UINT16* version )
{
	BM_TerminateCommand_Header_Version_GET( base_ptr, *version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_TerminateCommand_Header_Accessibility_GET( UINT8* base_ptr, UINT16* accessibility )
{
	BM_TerminateCommand_Header_Accessibility_GET( base_ptr, *accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_TerminateCommand_Header_Status_GET( UINT8* base_ptr, UINT16* status )
{
	BM_TerminateCommand_Header_Status_GET( base_ptr, *status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_TerminateCommand_Header_Type_SET( UINT8* base_ptr, UINT32 opcode )
{
	BM_TerminateCommand_Header_Type_SET( base_ptr, opcode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_TerminateCommand_Header_Version_SET( UINT8* base_ptr, UINT16 version )
{
	BM_TerminateCommand_Header_Version_SET( base_ptr, version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_TerminateCommand_Header_Accessibility_SET( UINT8* base_ptr, UINT16 accessibility )
{
	BM_TerminateCommand_Header_Accessibility_SET( base_ptr, accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_TerminateCommand_Header_Status_SET( UINT8* base_ptr, UINT16 status )
{
	BM_TerminateCommand_Header_Status_SET( base_ptr, status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_TerminateCommand_Header_Length_SET( UINT8* base_ptr, UINT32 len )
{
	BM_TerminateCommand_Header_Length_SET( base_ptr, len );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReadyForPowerSave_Header_Version_GET( UINT8* base_ptr, UINT16* version )
{
	BM_ReadyForPowerSave_Header_Version_GET( base_ptr, *version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReadyForPowerSave_Header_Accessibility_GET( UINT8* base_ptr, UINT16* accessibility )
{
	BM_ReadyForPowerSave_Header_Accessibility_GET( base_ptr, *accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReadyForPowerSave_Header_Status_GET( UINT8* base_ptr, UINT16* status )
{
	BM_ReadyForPowerSave_Header_Status_GET( base_ptr, *status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReadyForPowerSave_Header_Type_SET( UINT8* base_ptr, UINT32 opcode )
{
	BM_ReadyForPowerSave_Header_Type_SET( base_ptr, opcode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReadyForPowerSave_Header_Version_SET( UINT8* base_ptr, UINT16 version )
{
	BM_ReadyForPowerSave_Header_Version_SET( base_ptr, version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReadyForPowerSave_Header_Accessibility_SET( UINT8* base_ptr, UINT16 accessibility )
{
	BM_ReadyForPowerSave_Header_Accessibility_SET( base_ptr, accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReadyForPowerSave_Header_Status_SET( UINT8* base_ptr, UINT16 status )
{
	BM_ReadyForPowerSave_Header_Status_SET( base_ptr, status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReadyForPowerSave_Header_Length_SET( UINT8* base_ptr, UINT32 len )
{
	BM_ReadyForPowerSave_Header_Length_SET( base_ptr, len );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_Disconnect_Header_Version_GET( UINT8* base_ptr, UINT16* version )
{
	BM_Disconnect_Header_Version_GET( base_ptr, *version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_Disconnect_Header_Accessibility_GET( UINT8* base_ptr, UINT16* accessibility )
{
	BM_Disconnect_Header_Accessibility_GET( base_ptr, *accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_Disconnect_Header_Status_GET( UINT8* base_ptr, UINT16* status )
{
	BM_Disconnect_Header_Status_GET( base_ptr, *status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_Disconnect_Header_Type_SET( UINT8* base_ptr, UINT32 opcode )
{
	BM_Disconnect_Header_Type_SET( base_ptr, opcode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_Disconnect_Header_Version_SET( UINT8* base_ptr, UINT16 version )
{
	BM_Disconnect_Header_Version_SET( base_ptr, version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_Disconnect_Header_Accessibility_SET( UINT8* base_ptr, UINT16 accessibility )
{
	BM_Disconnect_Header_Accessibility_SET( base_ptr, accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_Disconnect_Header_Status_SET( UINT8* base_ptr, UINT16 status )
{
	BM_Disconnect_Header_Status_SET( base_ptr, status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_Disconnect_Header_Length_SET( UINT8* base_ptr, UINT32 len )
{
	BM_Disconnect_Header_Length_SET( base_ptr, len );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_Connect_Header_Version_GET( UINT8* base_ptr, UINT16* version )
{
	BM_Connect_Header_Version_GET( base_ptr, *version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_Connect_Header_Accessibility_GET( UINT8* base_ptr, UINT16* accessibility )
{
	BM_Connect_Header_Accessibility_GET( base_ptr, *accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_Connect_Header_Status_GET( UINT8* base_ptr, UINT16* status )
{
	BM_Connect_Header_Status_GET( base_ptr, *status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_Connect_Header_Length_GET( UINT8* base_ptr, UINT32* listSize )
{
	BM_Connect_Header_Length_GET( base_ptr, *listSize );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_Connect_List_GET_FIRST( UINT8* base_ptr, UINT32* out_diff, UINT32* out_cur_bitoff )
{
	UINT8* out_cur_ptr = base_ptr;
	BM_Connect_List_GET_FIRST( base_ptr, out_cur_ptr, *out_cur_bitoff );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_Connect_List_GET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_Connect_List_GET_TYPE( cur_ptr, cur_bitoff, *type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_Connect_List_GET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_length, UINT32 err )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_Connect_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, *out_length, err );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_Connect_List_CURRENT_BSCritieria_BSID_Criterion_value_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_Connect_List_CURRENT_BSCritieria_BSID_Criterion_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_Connect_List_CURRENT_BSCritieria_BSID_Criterion_Mask_value_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_Connect_List_CURRENT_BSCritieria_BSID_Criterion_Mask_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_Connect_List_CURRENT_THCriteria_RssiTH_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* RssiTH )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_Connect_List_CURRENT_THCriteria_RssiTH_GET( base_ptr, cur_ptr, cur_bitoff, *RssiTH );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_Connect_List_CURRENT_THCriteria_CinrTH_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* CinrTH )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_Connect_List_CURRENT_THCriteria_CinrTH_GET( base_ptr, cur_ptr, cur_bitoff, *CinrTH );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_Connect_List_CURRENT_ConnectionMode_value_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_Connect_List_CURRENT_ConnectionMode_value_GET( base_ptr, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_Connect_List_CURRENT_ConnectFlags_VisitedNspId_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* VisitedNspId )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_Connect_List_CURRENT_ConnectFlags_VisitedNspId_GET( base_ptr, cur_ptr, cur_bitoff, *VisitedNspId );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_Connect_List_CURRENT_ConnectFlags_RequestRealm_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* RequestRealm )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_Connect_List_CURRENT_ConnectFlags_RequestRealm_GET( base_ptr, cur_ptr, cur_bitoff, *RequestRealm );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_Connect_List_CURRENT_ConnectFlags_SIQ_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* SIQ )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_Connect_List_CURRENT_ConnectFlags_SIQ_GET( base_ptr, cur_ptr, cur_bitoff, *SIQ );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_Connect_List_CURRENT_ConnectFlags_Reserved1_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* Reserved1 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_Connect_List_CURRENT_ConnectFlags_Reserved1_GET( base_ptr, cur_ptr, cur_bitoff, *Reserved1 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_Connect_List_CURRENT_ConnectFlags_Reserved2_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* Reserved2 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_Connect_List_CURRENT_ConnectFlags_Reserved2_GET( base_ptr, cur_ptr, cur_bitoff, *Reserved2 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_Connect_List_CURRENT_CoexPriority_value_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_Connect_List_CURRENT_CoexPriority_value_GET( base_ptr, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_Connect_List_GET_NEXT( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_diff, UINT32* out_cur_bitoff, UINT32 err )
{
	UINT8* out_cur_ptr = base_ptr;
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_Connect_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, out_cur_ptr, *out_cur_bitoff, err );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_Connect_List_SET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_Connect_List_SET_TYPE( cur_ptr, cur_bitoff, type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_Connect_List_SET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 lenOfLen, UINT32 length )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	lenOfLen = 2;
	BM_Connect_List_SET_LENGTH( cur_ptr, cur_bitoff, lenOfLen, length );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_Connect_List_CURRENT_BSCritieria_BSID_Criterion_value_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_Connect_List_CURRENT_BSCritieria_BSID_Criterion_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_Connect_List_CURRENT_BSCritieria_BSID_Criterion_Mask_value_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_Connect_List_CURRENT_BSCritieria_BSID_Criterion_Mask_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_Connect_List_CURRENT_THCriteria_RssiTH_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 RssiTH )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_Connect_List_CURRENT_THCriteria_RssiTH_SET( base_ptr, cur_ptr, cur_bitoff, RssiTH );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_Connect_List_CURRENT_THCriteria_CinrTH_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 CinrTH )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_Connect_List_CURRENT_THCriteria_CinrTH_SET( base_ptr, cur_ptr, cur_bitoff, CinrTH );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_Connect_List_CURRENT_ConnectionMode_value_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_Connect_List_CURRENT_ConnectionMode_value_SET( base_ptr, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_Connect_List_CURRENT_ConnectFlags_VisitedNspId_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 VisitedNspId )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_Connect_List_CURRENT_ConnectFlags_VisitedNspId_SET( base_ptr, cur_ptr, cur_bitoff, VisitedNspId );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_Connect_List_CURRENT_ConnectFlags_RequestRealm_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 RequestRealm )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_Connect_List_CURRENT_ConnectFlags_RequestRealm_SET( base_ptr, cur_ptr, cur_bitoff, RequestRealm );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_Connect_List_CURRENT_ConnectFlags_SIQ_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 SIQ )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_Connect_List_CURRENT_ConnectFlags_SIQ_SET( base_ptr, cur_ptr, cur_bitoff, SIQ );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_Connect_List_CURRENT_ConnectFlags_Reserved1_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 Reserved1 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_Connect_List_CURRENT_ConnectFlags_Reserved1_SET( base_ptr, cur_ptr, cur_bitoff, Reserved1 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_Connect_List_CURRENT_ConnectFlags_Reserved2_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 Reserved2 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_Connect_List_CURRENT_ConnectFlags_Reserved2_SET( base_ptr, cur_ptr, cur_bitoff, Reserved2 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_Connect_List_CURRENT_CoexPriority_value_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_Connect_List_CURRENT_CoexPriority_value_SET( base_ptr, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_Connect_Header_Type_SET( UINT8* base_ptr, UINT32 opcode )
{
	BM_Connect_Header_Type_SET( base_ptr, opcode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_Connect_Header_Version_SET( UINT8* base_ptr, UINT16 version )
{
	BM_Connect_Header_Version_SET( base_ptr, version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_Connect_Header_Accessibility_SET( UINT8* base_ptr, UINT16 accessibility )
{
	BM_Connect_Header_Accessibility_SET( base_ptr, accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_Connect_Header_Status_SET( UINT8* base_ptr, UINT16 status )
{
	BM_Connect_Header_Status_SET( base_ptr, status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_Connect_Header_Length_SET( UINT8* base_ptr, UINT32 len )
{
	BM_Connect_Header_Length_SET( base_ptr, len );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CmdCoexProcessStart_Header_Version_GET( UINT8* base_ptr, UINT16* version )
{
	BM_CmdCoexProcessStart_Header_Version_GET( base_ptr, *version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CmdCoexProcessStart_Header_Accessibility_GET( UINT8* base_ptr, UINT16* accessibility )
{
	BM_CmdCoexProcessStart_Header_Accessibility_GET( base_ptr, *accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CmdCoexProcessStart_Header_Status_GET( UINT8* base_ptr, UINT16* status )
{
	BM_CmdCoexProcessStart_Header_Status_GET( base_ptr, *status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CmdCoexProcessStart_Header_Length_GET( UINT8* base_ptr, UINT32* listSize )
{
	BM_CmdCoexProcessStart_Header_Length_GET( base_ptr, *listSize );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CmdCoexProcessStart_List_GET_FIRST( UINT8* base_ptr, UINT32* out_diff, UINT32* out_cur_bitoff )
{
	UINT8* out_cur_ptr = base_ptr;
	BM_CmdCoexProcessStart_List_GET_FIRST( base_ptr, out_cur_ptr, *out_cur_bitoff );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CmdCoexProcessStart_List_GET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_CmdCoexProcessStart_List_GET_TYPE( cur_ptr, cur_bitoff, *type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CmdCoexProcessStart_List_GET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_length, UINT32 err )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_CmdCoexProcessStart_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, *out_length, err );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CmdCoexProcessStart_List_CURRENT_ProcessType_State_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* State )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_CmdCoexProcessStart_List_CURRENT_ProcessType_State_GET( base_ptr, cur_ptr, cur_bitoff, *State );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CmdCoexProcessStart_List_GET_NEXT( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_diff, UINT32* out_cur_bitoff, UINT32 err )
{
	UINT8* out_cur_ptr = base_ptr;
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_CmdCoexProcessStart_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, out_cur_ptr, *out_cur_bitoff, err );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CmdCoexProcessStart_List_SET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_CmdCoexProcessStart_List_SET_TYPE( cur_ptr, cur_bitoff, type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CmdCoexProcessStart_List_SET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 lenOfLen, UINT32 length )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	lenOfLen = 2;
	BM_CmdCoexProcessStart_List_SET_LENGTH( cur_ptr, cur_bitoff, lenOfLen, length );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CmdCoexProcessStart_List_CURRENT_ProcessType_State_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 State )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_CmdCoexProcessStart_List_CURRENT_ProcessType_State_SET( base_ptr, cur_ptr, cur_bitoff, State );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CmdCoexProcessStart_Header_Type_SET( UINT8* base_ptr, UINT32 opcode )
{
	BM_CmdCoexProcessStart_Header_Type_SET( base_ptr, opcode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CmdCoexProcessStart_Header_Version_SET( UINT8* base_ptr, UINT16 version )
{
	BM_CmdCoexProcessStart_Header_Version_SET( base_ptr, version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CmdCoexProcessStart_Header_Accessibility_SET( UINT8* base_ptr, UINT16 accessibility )
{
	BM_CmdCoexProcessStart_Header_Accessibility_SET( base_ptr, accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CmdCoexProcessStart_Header_Status_SET( UINT8* base_ptr, UINT16 status )
{
	BM_CmdCoexProcessStart_Header_Status_SET( base_ptr, status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CmdCoexProcessStart_Header_Length_SET( UINT8* base_ptr, UINT32 len )
{
	BM_CmdCoexProcessStart_Header_Length_SET( base_ptr, len );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_InitCommand_Header_Version_GET( UINT8* base_ptr, UINT16* version )
{
	BM_InitCommand_Header_Version_GET( base_ptr, *version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_InitCommand_Header_Accessibility_GET( UINT8* base_ptr, UINT16* accessibility )
{
	BM_InitCommand_Header_Accessibility_GET( base_ptr, *accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_InitCommand_Header_Status_GET( UINT8* base_ptr, UINT16* status )
{
	BM_InitCommand_Header_Status_GET( base_ptr, *status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_InitCommand_Header_Type_SET( UINT8* base_ptr, UINT32 opcode )
{
	BM_InitCommand_Header_Type_SET( base_ptr, opcode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_InitCommand_Header_Version_SET( UINT8* base_ptr, UINT16 version )
{
	BM_InitCommand_Header_Version_SET( base_ptr, version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_InitCommand_Header_Accessibility_SET( UINT8* base_ptr, UINT16 accessibility )
{
	BM_InitCommand_Header_Accessibility_SET( base_ptr, accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_InitCommand_Header_Status_SET( UINT8* base_ptr, UINT16 status )
{
	BM_InitCommand_Header_Status_SET( base_ptr, status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_InitCommand_Header_Length_SET( UINT8* base_ptr, UINT32 len )
{
	BM_InitCommand_Header_Length_SET( base_ptr, len );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetEapKey_Header_Version_GET( UINT8* base_ptr, UINT16* version )
{
	BM_SetEapKey_Header_Version_GET( base_ptr, *version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetEapKey_Header_Accessibility_GET( UINT8* base_ptr, UINT16* accessibility )
{
	BM_SetEapKey_Header_Accessibility_GET( base_ptr, *accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetEapKey_Header_Status_GET( UINT8* base_ptr, UINT16* status )
{
	BM_SetEapKey_Header_Status_GET( base_ptr, *status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetEapKey_Header_Length_GET( UINT8* base_ptr, UINT32* listSize )
{
	BM_SetEapKey_Header_Length_GET( base_ptr, *listSize );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetEapKey_List_GET_FIRST( UINT8* base_ptr, UINT32* out_diff, UINT32* out_cur_bitoff )
{
	UINT8* out_cur_ptr = base_ptr;
	BM_SetEapKey_List_GET_FIRST( base_ptr, out_cur_ptr, *out_cur_bitoff );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetEapKey_List_GET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetEapKey_List_GET_TYPE( cur_ptr, cur_bitoff, *type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetEapKey_List_GET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_length, UINT32 err )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetEapKey_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, *out_length, err );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetEapKey_List_CURRENT_EapKeyValid_value_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetEapKey_List_CURRENT_EapKeyValid_value_GET( base_ptr, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetEapKey_List_CURRENT_EapKeyMsk_EapKeyMskArr_value_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetEapKey_List_CURRENT_EapKeyMsk_EapKeyMskArr_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetEapKey_List_GET_NEXT( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_diff, UINT32* out_cur_bitoff, UINT32 err )
{
	UINT8* out_cur_ptr = base_ptr;
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetEapKey_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, out_cur_ptr, *out_cur_bitoff, err );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetEapKey_List_SET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetEapKey_List_SET_TYPE( cur_ptr, cur_bitoff, type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetEapKey_List_SET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 lenOfLen, UINT32 length )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	lenOfLen = 2;
	BM_SetEapKey_List_SET_LENGTH( cur_ptr, cur_bitoff, lenOfLen, length );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetEapKey_List_CURRENT_EapKeyValid_value_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetEapKey_List_CURRENT_EapKeyValid_value_SET( base_ptr, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetEapKey_List_CURRENT_EapKeyMsk_EapKeyMskArr_value_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetEapKey_List_CURRENT_EapKeyMsk_EapKeyMskArr_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetEapKey_Header_Type_SET( UINT8* base_ptr, UINT32 opcode )
{
	BM_SetEapKey_Header_Type_SET( base_ptr, opcode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetEapKey_Header_Version_SET( UINT8* base_ptr, UINT16 version )
{
	BM_SetEapKey_Header_Version_SET( base_ptr, version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetEapKey_Header_Accessibility_SET( UINT8* base_ptr, UINT16 accessibility )
{
	BM_SetEapKey_Header_Accessibility_SET( base_ptr, accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetEapKey_Header_Status_SET( UINT8* base_ptr, UINT16 status )
{
	BM_SetEapKey_Header_Status_SET( base_ptr, status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetEapKey_Header_Length_SET( UINT8* base_ptr, UINT32 len )
{
	BM_SetEapKey_Header_Length_SET( base_ptr, len );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceSET_Header_Version_GET( UINT8* base_ptr, UINT16* version )
{
	BM_CheckL3L4InterfaceSET_Header_Version_GET( base_ptr, *version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceSET_Header_Accessibility_GET( UINT8* base_ptr, UINT16* accessibility )
{
	BM_CheckL3L4InterfaceSET_Header_Accessibility_GET( base_ptr, *accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceSET_Header_Status_GET( UINT8* base_ptr, UINT16* status )
{
	BM_CheckL3L4InterfaceSET_Header_Status_GET( base_ptr, *status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceSET_Header_Length_GET( UINT8* base_ptr, UINT32* listSize )
{
	BM_CheckL3L4InterfaceSET_Header_Length_GET( base_ptr, *listSize );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceSET_List_GET_FIRST( UINT8* base_ptr, UINT32* out_diff, UINT32* out_cur_bitoff )
{
	UINT8* out_cur_ptr = base_ptr;
	BM_CheckL3L4InterfaceSET_List_GET_FIRST( base_ptr, out_cur_ptr, *out_cur_bitoff );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceSET_List_GET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_CheckL3L4InterfaceSET_List_GET_TYPE( cur_ptr, cur_bitoff, *type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceSET_List_GET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_length, UINT32 err )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_CheckL3L4InterfaceSET_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, *out_length, err );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceSET_List_CURRENT_value_value_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_CheckL3L4InterfaceSET_List_CURRENT_value_value_GET( base_ptr, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceSET_List_GET_NEXT( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_diff, UINT32* out_cur_bitoff, UINT32 err )
{
	UINT8* out_cur_ptr = base_ptr;
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_CheckL3L4InterfaceSET_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, out_cur_ptr, *out_cur_bitoff, err );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceSET_List_SET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_CheckL3L4InterfaceSET_List_SET_TYPE( cur_ptr, cur_bitoff, type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceSET_List_SET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 lenOfLen, UINT32 length )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	lenOfLen = 2;
	BM_CheckL3L4InterfaceSET_List_SET_LENGTH( cur_ptr, cur_bitoff, lenOfLen, length );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceSET_List_CURRENT_value_value_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_CheckL3L4InterfaceSET_List_CURRENT_value_value_SET( base_ptr, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceSET_Header_Type_SET( UINT8* base_ptr, UINT32 opcode )
{
	BM_CheckL3L4InterfaceSET_Header_Type_SET( base_ptr, opcode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceSET_Header_Version_SET( UINT8* base_ptr, UINT16 version )
{
	BM_CheckL3L4InterfaceSET_Header_Version_SET( base_ptr, version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceSET_Header_Accessibility_SET( UINT8* base_ptr, UINT16 accessibility )
{
	BM_CheckL3L4InterfaceSET_Header_Accessibility_SET( base_ptr, accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceSET_Header_Status_SET( UINT8* base_ptr, UINT16 status )
{
	BM_CheckL3L4InterfaceSET_Header_Status_SET( base_ptr, status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceSET_Header_Length_SET( UINT8* base_ptr, UINT32 len )
{
	BM_CheckL3L4InterfaceSET_Header_Length_SET( base_ptr, len );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MOC_Broadcast_Header_Version_GET( UINT8* base_ptr, UINT16* version )
{
	BM_MOC_Broadcast_Header_Version_GET( base_ptr, *version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MOC_Broadcast_Header_Accessibility_GET( UINT8* base_ptr, UINT16* accessibility )
{
	BM_MOC_Broadcast_Header_Accessibility_GET( base_ptr, *accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MOC_Broadcast_Header_Status_GET( UINT8* base_ptr, UINT16* status )
{
	BM_MOC_Broadcast_Header_Status_GET( base_ptr, *status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MOC_Broadcast_Header_Type_SET( UINT8* base_ptr, UINT32 opcode )
{
	BM_MOC_Broadcast_Header_Type_SET( base_ptr, opcode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MOC_Broadcast_Header_Version_SET( UINT8* base_ptr, UINT16 version )
{
	BM_MOC_Broadcast_Header_Version_SET( base_ptr, version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MOC_Broadcast_Header_Accessibility_SET( UINT8* base_ptr, UINT16 accessibility )
{
	BM_MOC_Broadcast_Header_Accessibility_SET( base_ptr, accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MOC_Broadcast_Header_Status_SET( UINT8* base_ptr, UINT16 status )
{
	BM_MOC_Broadcast_Header_Status_SET( base_ptr, status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MOC_Broadcast_Header_Length_SET( UINT8* base_ptr, UINT32 len )
{
	BM_MOC_Broadcast_Header_Length_SET( base_ptr, len );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetCoexMode_Header_Version_GET( UINT8* base_ptr, UINT16* version )
{
	BM_SetCoexMode_Header_Version_GET( base_ptr, *version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetCoexMode_Header_Accessibility_GET( UINT8* base_ptr, UINT16* accessibility )
{
	BM_SetCoexMode_Header_Accessibility_GET( base_ptr, *accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetCoexMode_Header_Status_GET( UINT8* base_ptr, UINT16* status )
{
	BM_SetCoexMode_Header_Status_GET( base_ptr, *status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetCoexMode_Header_Length_GET( UINT8* base_ptr, UINT32* listSize )
{
	BM_SetCoexMode_Header_Length_GET( base_ptr, *listSize );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetCoexMode_List_GET_FIRST( UINT8* base_ptr, UINT32* out_diff, UINT32* out_cur_bitoff )
{
	UINT8* out_cur_ptr = base_ptr;
	BM_SetCoexMode_List_GET_FIRST( base_ptr, out_cur_ptr, *out_cur_bitoff );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetCoexMode_List_GET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetCoexMode_List_GET_TYPE( cur_ptr, cur_bitoff, *type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetCoexMode_List_GET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_length, UINT32 err )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetCoexMode_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, *out_length, err );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetCoexMode_List_CURRENT_CoexistenceModeType_value_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetCoexMode_List_CURRENT_CoexistenceModeType_value_GET( base_ptr, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetCoexMode_List_GET_NEXT( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_diff, UINT32* out_cur_bitoff, UINT32 err )
{
	UINT8* out_cur_ptr = base_ptr;
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetCoexMode_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, out_cur_ptr, *out_cur_bitoff, err );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetCoexMode_List_SET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetCoexMode_List_SET_TYPE( cur_ptr, cur_bitoff, type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetCoexMode_List_SET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 lenOfLen, UINT32 length )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	lenOfLen = 2;
	BM_SetCoexMode_List_SET_LENGTH( cur_ptr, cur_bitoff, lenOfLen, length );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetCoexMode_List_CURRENT_CoexistenceModeType_value_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetCoexMode_List_CURRENT_CoexistenceModeType_value_SET( base_ptr, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetCoexMode_Header_Type_SET( UINT8* base_ptr, UINT32 opcode )
{
	BM_SetCoexMode_Header_Type_SET( base_ptr, opcode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetCoexMode_Header_Version_SET( UINT8* base_ptr, UINT16 version )
{
	BM_SetCoexMode_Header_Version_SET( base_ptr, version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetCoexMode_Header_Accessibility_SET( UINT8* base_ptr, UINT16 accessibility )
{
	BM_SetCoexMode_Header_Accessibility_SET( base_ptr, accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetCoexMode_Header_Status_SET( UINT8* base_ptr, UINT16 status )
{
	BM_SetCoexMode_Header_Status_SET( base_ptr, status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetCoexMode_Header_Length_SET( UINT8* base_ptr, UINT32 len )
{
	BM_SetCoexMode_Header_Length_SET( base_ptr, len );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceREPORT_Header_Version_GET( UINT8* base_ptr, UINT16* version )
{
	BM_CheckL3L4InterfaceREPORT_Header_Version_GET( base_ptr, *version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceREPORT_Header_Accessibility_GET( UINT8* base_ptr, UINT16* accessibility )
{
	BM_CheckL3L4InterfaceREPORT_Header_Accessibility_GET( base_ptr, *accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceREPORT_Header_Status_GET( UINT8* base_ptr, UINT16* status )
{
	BM_CheckL3L4InterfaceREPORT_Header_Status_GET( base_ptr, *status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceREPORT_Header_Length_GET( UINT8* base_ptr, UINT32* listSize )
{
	BM_CheckL3L4InterfaceREPORT_Header_Length_GET( base_ptr, *listSize );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceREPORT_List_GET_FIRST( UINT8* base_ptr, UINT32* out_diff, UINT32* out_cur_bitoff )
{
	UINT8* out_cur_ptr = base_ptr;
	BM_CheckL3L4InterfaceREPORT_List_GET_FIRST( base_ptr, out_cur_ptr, *out_cur_bitoff );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceREPORT_List_GET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_CheckL3L4InterfaceREPORT_List_GET_TYPE( cur_ptr, cur_bitoff, *type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceREPORT_List_GET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_length, UINT32 err )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_CheckL3L4InterfaceREPORT_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, *out_length, err );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceREPORT_List_CURRENT_value_value_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_CheckL3L4InterfaceREPORT_List_CURRENT_value_value_GET( base_ptr, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceREPORT_List_GET_NEXT( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_diff, UINT32* out_cur_bitoff, UINT32 err )
{
	UINT8* out_cur_ptr = base_ptr;
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_CheckL3L4InterfaceREPORT_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, out_cur_ptr, *out_cur_bitoff, err );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceREPORT_List_SET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_CheckL3L4InterfaceREPORT_List_SET_TYPE( cur_ptr, cur_bitoff, type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceREPORT_List_SET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 lenOfLen, UINT32 length )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	lenOfLen = 2;
	BM_CheckL3L4InterfaceREPORT_List_SET_LENGTH( cur_ptr, cur_bitoff, lenOfLen, length );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceREPORT_List_CURRENT_value_value_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_CheckL3L4InterfaceREPORT_List_CURRENT_value_value_SET( base_ptr, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceREPORT_Header_Type_SET( UINT8* base_ptr, UINT32 opcode )
{
	BM_CheckL3L4InterfaceREPORT_Header_Type_SET( base_ptr, opcode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceREPORT_Header_Version_SET( UINT8* base_ptr, UINT16 version )
{
	BM_CheckL3L4InterfaceREPORT_Header_Version_SET( base_ptr, version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceREPORT_Header_Accessibility_SET( UINT8* base_ptr, UINT16 accessibility )
{
	BM_CheckL3L4InterfaceREPORT_Header_Accessibility_SET( base_ptr, accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceREPORT_Header_Status_SET( UINT8* base_ptr, UINT16 status )
{
	BM_CheckL3L4InterfaceREPORT_Header_Status_SET( base_ptr, status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceREPORT_Header_Length_SET( UINT8* base_ptr, UINT32 len )
{
	BM_CheckL3L4InterfaceREPORT_Header_Length_SET( base_ptr, len );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetTraceSeverityTable_Header_Version_GET( UINT8* base_ptr, UINT16* version )
{
	BM_SetTraceSeverityTable_Header_Version_GET( base_ptr, *version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetTraceSeverityTable_Header_Accessibility_GET( UINT8* base_ptr, UINT16* accessibility )
{
	BM_SetTraceSeverityTable_Header_Accessibility_GET( base_ptr, *accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetTraceSeverityTable_Header_Status_GET( UINT8* base_ptr, UINT16* status )
{
	BM_SetTraceSeverityTable_Header_Status_GET( base_ptr, *status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetTraceSeverityTable_Header_Length_GET( UINT8* base_ptr, UINT32* listSize )
{
	BM_SetTraceSeverityTable_Header_Length_GET( base_ptr, *listSize );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetTraceSeverityTable_List_GET_FIRST( UINT8* base_ptr, UINT32* out_diff, UINT32* out_cur_bitoff )
{
	UINT8* out_cur_ptr = base_ptr;
	BM_SetTraceSeverityTable_List_GET_FIRST( base_ptr, out_cur_ptr, *out_cur_bitoff );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetTraceSeverityTable_List_GET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetTraceSeverityTable_List_GET_TYPE( cur_ptr, cur_bitoff, *type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetTraceSeverityTable_List_GET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_length, UINT32 err )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetTraceSeverityTable_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, *out_length, err );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetTraceSeverityTable_List_CURRENT_TraceSeverityTable_SeverityTable_value_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetTraceSeverityTable_List_CURRENT_TraceSeverityTable_SeverityTable_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetTraceSeverityTable_List_GET_NEXT( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_diff, UINT32* out_cur_bitoff, UINT32 err )
{
	UINT8* out_cur_ptr = base_ptr;
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetTraceSeverityTable_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, out_cur_ptr, *out_cur_bitoff, err );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetTraceSeverityTable_List_SET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetTraceSeverityTable_List_SET_TYPE( cur_ptr, cur_bitoff, type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetTraceSeverityTable_List_SET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 lenOfLen, UINT32 length )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	lenOfLen = 2;
	BM_SetTraceSeverityTable_List_SET_LENGTH( cur_ptr, cur_bitoff, lenOfLen, length );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetTraceSeverityTable_List_CURRENT_TraceSeverityTable_SeverityTable_value_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SetTraceSeverityTable_List_CURRENT_TraceSeverityTable_SeverityTable_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetTraceSeverityTable_Header_Type_SET( UINT8* base_ptr, UINT32 opcode )
{
	BM_SetTraceSeverityTable_Header_Type_SET( base_ptr, opcode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetTraceSeverityTable_Header_Version_SET( UINT8* base_ptr, UINT16 version )
{
	BM_SetTraceSeverityTable_Header_Version_SET( base_ptr, version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetTraceSeverityTable_Header_Accessibility_SET( UINT8* base_ptr, UINT16 accessibility )
{
	BM_SetTraceSeverityTable_Header_Accessibility_SET( base_ptr, accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetTraceSeverityTable_Header_Status_SET( UINT8* base_ptr, UINT16 status )
{
	BM_SetTraceSeverityTable_Header_Status_SET( base_ptr, status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetTraceSeverityTable_Header_Length_SET( UINT8* base_ptr, UINT32 len )
{
	BM_SetTraceSeverityTable_Header_Length_SET( base_ptr, len );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportBsInfo_Header_Version_GET( UINT8* base_ptr, UINT16* version )
{
	BM_ReportBsInfo_Header_Version_GET( base_ptr, *version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportBsInfo_Header_Accessibility_GET( UINT8* base_ptr, UINT16* accessibility )
{
	BM_ReportBsInfo_Header_Accessibility_GET( base_ptr, *accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportBsInfo_Header_Status_GET( UINT8* base_ptr, UINT16* status )
{
	BM_ReportBsInfo_Header_Status_GET( base_ptr, *status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportBsInfo_Header_Length_GET( UINT8* base_ptr, UINT32* listSize )
{
	BM_ReportBsInfo_Header_Length_GET( base_ptr, *listSize );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportBsInfo_List_GET_FIRST( UINT8* base_ptr, UINT32* out_diff, UINT32* out_cur_bitoff )
{
	UINT8* out_cur_ptr = base_ptr;
	BM_ReportBsInfo_List_GET_FIRST( base_ptr, out_cur_ptr, *out_cur_bitoff );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportBsInfo_List_GET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportBsInfo_List_GET_TYPE( cur_ptr, cur_bitoff, *type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportBsInfo_List_GET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_length, UINT32 err )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportBsInfo_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, *out_length, err );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportBsInfo_List_CURRENT_BSID_FullBSID_value_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportBsInfo_List_CURRENT_BSID_FullBSID_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportBsInfo_List_CURRENT_BSID_Reserved_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* Reserved )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportBsInfo_List_CURRENT_BSID_Reserved_GET( base_ptr, cur_ptr, cur_bitoff, *Reserved );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportBsInfo_List_CURRENT_NspChangeCount_NspChangeCount_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* NspChangeCount )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportBsInfo_List_CURRENT_NspChangeCount_NspChangeCount_GET( base_ptr, cur_ptr, cur_bitoff, *NspChangeCount );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportBsInfo_List_CURRENT_NspChangeCount_Reserved1_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* Reserved1 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportBsInfo_List_CURRENT_NspChangeCount_Reserved1_GET( base_ptr, cur_ptr, cur_bitoff, *Reserved1 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportBsInfo_List_CURRENT_NspChangeCount_Reserved2_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* Reserved2 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportBsInfo_List_CURRENT_NspChangeCount_Reserved2_GET( base_ptr, cur_ptr, cur_bitoff, *Reserved2 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportBsInfo_List_GET_NEXT( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_diff, UINT32* out_cur_bitoff, UINT32 err )
{
	UINT8* out_cur_ptr = base_ptr;
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportBsInfo_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, out_cur_ptr, *out_cur_bitoff, err );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportBsInfo_List_SET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportBsInfo_List_SET_TYPE( cur_ptr, cur_bitoff, type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportBsInfo_List_SET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 lenOfLen, UINT32 length )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	lenOfLen = 2;
	BM_ReportBsInfo_List_SET_LENGTH( cur_ptr, cur_bitoff, lenOfLen, length );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportBsInfo_List_CURRENT_BSID_FullBSID_value_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportBsInfo_List_CURRENT_BSID_FullBSID_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportBsInfo_List_CURRENT_BSID_Reserved_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 Reserved )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportBsInfo_List_CURRENT_BSID_Reserved_SET( base_ptr, cur_ptr, cur_bitoff, Reserved );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportBsInfo_List_CURRENT_NspChangeCount_NspChangeCount_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 NspChangeCount )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportBsInfo_List_CURRENT_NspChangeCount_NspChangeCount_SET( base_ptr, cur_ptr, cur_bitoff, NspChangeCount );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportBsInfo_List_CURRENT_NspChangeCount_Reserved1_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 Reserved1 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportBsInfo_List_CURRENT_NspChangeCount_Reserved1_SET( base_ptr, cur_ptr, cur_bitoff, Reserved1 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportBsInfo_List_CURRENT_NspChangeCount_Reserved2_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 Reserved2 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportBsInfo_List_CURRENT_NspChangeCount_Reserved2_SET( base_ptr, cur_ptr, cur_bitoff, Reserved2 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportBsInfo_Header_Type_SET( UINT8* base_ptr, UINT32 opcode )
{
	BM_ReportBsInfo_Header_Type_SET( base_ptr, opcode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportBsInfo_Header_Version_SET( UINT8* base_ptr, UINT16 version )
{
	BM_ReportBsInfo_Header_Version_SET( base_ptr, version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportBsInfo_Header_Accessibility_SET( UINT8* base_ptr, UINT16 accessibility )
{
	BM_ReportBsInfo_Header_Accessibility_SET( base_ptr, accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportBsInfo_Header_Status_SET( UINT8* base_ptr, UINT16 status )
{
	BM_ReportBsInfo_Header_Status_SET( base_ptr, status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportBsInfo_Header_Length_SET( UINT8* base_ptr, UINT32 len )
{
	BM_ReportBsInfo_Header_Length_SET( base_ptr, len );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetEapFail_Header_Version_GET( UINT8* base_ptr, UINT16* version )
{
	BM_SetEapFail_Header_Version_GET( base_ptr, *version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetEapFail_Header_Accessibility_GET( UINT8* base_ptr, UINT16* accessibility )
{
	BM_SetEapFail_Header_Accessibility_GET( base_ptr, *accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetEapFail_Header_Status_GET( UINT8* base_ptr, UINT16* status )
{
	BM_SetEapFail_Header_Status_GET( base_ptr, *status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetEapFail_Header_Type_SET( UINT8* base_ptr, UINT32 opcode )
{
	BM_SetEapFail_Header_Type_SET( base_ptr, opcode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetEapFail_Header_Version_SET( UINT8* base_ptr, UINT16 version )
{
	BM_SetEapFail_Header_Version_SET( base_ptr, version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetEapFail_Header_Accessibility_SET( UINT8* base_ptr, UINT16 accessibility )
{
	BM_SetEapFail_Header_Accessibility_SET( base_ptr, accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetEapFail_Header_Status_SET( UINT8* base_ptr, UINT16 status )
{
	BM_SetEapFail_Header_Status_SET( base_ptr, status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SetEapFail_Header_Length_SET( UINT8* base_ptr, UINT32 len )
{
	BM_SetEapFail_Header_Length_SET( base_ptr, len );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ResetDeviceCommand_Header_Version_GET( UINT8* base_ptr, UINT16* version )
{
	BM_ResetDeviceCommand_Header_Version_GET( base_ptr, *version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ResetDeviceCommand_Header_Accessibility_GET( UINT8* base_ptr, UINT16* accessibility )
{
	BM_ResetDeviceCommand_Header_Accessibility_GET( base_ptr, *accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ResetDeviceCommand_Header_Status_GET( UINT8* base_ptr, UINT16* status )
{
	BM_ResetDeviceCommand_Header_Status_GET( base_ptr, *status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ResetDeviceCommand_Header_Length_GET( UINT8* base_ptr, UINT32* listSize )
{
	BM_ResetDeviceCommand_Header_Length_GET( base_ptr, *listSize );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ResetDeviceCommand_List_GET_FIRST( UINT8* base_ptr, UINT32* out_diff, UINT32* out_cur_bitoff )
{
	UINT8* out_cur_ptr = base_ptr;
	BM_ResetDeviceCommand_List_GET_FIRST( base_ptr, out_cur_ptr, *out_cur_bitoff );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ResetDeviceCommand_List_GET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ResetDeviceCommand_List_GET_TYPE( cur_ptr, cur_bitoff, *type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ResetDeviceCommand_List_GET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_length, UINT32 err )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ResetDeviceCommand_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, *out_length, err );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ResetDeviceCommand_List_CURRENT_ResetDevice_value_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ResetDeviceCommand_List_CURRENT_ResetDevice_value_GET( base_ptr, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ResetDeviceCommand_List_GET_NEXT( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_diff, UINT32* out_cur_bitoff, UINT32 err )
{
	UINT8* out_cur_ptr = base_ptr;
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ResetDeviceCommand_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, out_cur_ptr, *out_cur_bitoff, err );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ResetDeviceCommand_List_SET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ResetDeviceCommand_List_SET_TYPE( cur_ptr, cur_bitoff, type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ResetDeviceCommand_List_SET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 lenOfLen, UINT32 length )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	lenOfLen = 2;
	BM_ResetDeviceCommand_List_SET_LENGTH( cur_ptr, cur_bitoff, lenOfLen, length );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ResetDeviceCommand_List_CURRENT_ResetDevice_value_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ResetDeviceCommand_List_CURRENT_ResetDevice_value_SET( base_ptr, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ResetDeviceCommand_Header_Type_SET( UINT8* base_ptr, UINT32 opcode )
{
	BM_ResetDeviceCommand_Header_Type_SET( base_ptr, opcode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ResetDeviceCommand_Header_Version_SET( UINT8* base_ptr, UINT16 version )
{
	BM_ResetDeviceCommand_Header_Version_SET( base_ptr, version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ResetDeviceCommand_Header_Accessibility_SET( UINT8* base_ptr, UINT16 accessibility )
{
	BM_ResetDeviceCommand_Header_Accessibility_SET( base_ptr, accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ResetDeviceCommand_Header_Status_SET( UINT8* base_ptr, UINT16 status )
{
	BM_ResetDeviceCommand_Header_Status_SET( base_ptr, status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ResetDeviceCommand_Header_Length_SET( UINT8* base_ptr, UINT32 len )
{
	BM_ResetDeviceCommand_Header_Length_SET( base_ptr, len );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MOC_Response_Header_Version_GET( UINT8* base_ptr, UINT16* version )
{
	BM_MOC_Response_Header_Version_GET( base_ptr, *version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MOC_Response_Header_Accessibility_GET( UINT8* base_ptr, UINT16* accessibility )
{
	BM_MOC_Response_Header_Accessibility_GET( base_ptr, *accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MOC_Response_Header_Status_GET( UINT8* base_ptr, UINT16* status )
{
	BM_MOC_Response_Header_Status_GET( base_ptr, *status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MOC_Response_Header_Type_SET( UINT8* base_ptr, UINT32 opcode )
{
	BM_MOC_Response_Header_Type_SET( base_ptr, opcode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MOC_Response_Header_Version_SET( UINT8* base_ptr, UINT16 version )
{
	BM_MOC_Response_Header_Version_SET( base_ptr, version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MOC_Response_Header_Accessibility_SET( UINT8* base_ptr, UINT16 accessibility )
{
	BM_MOC_Response_Header_Accessibility_SET( base_ptr, accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MOC_Response_Header_Status_SET( UINT8* base_ptr, UINT16 status )
{
	BM_MOC_Response_Header_Status_SET( base_ptr, status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MOC_Response_Header_Length_SET( UINT8* base_ptr, UINT32 len )
{
	BM_MOC_Response_Header_Length_SET( base_ptr, len );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetStatistics_Header_Version_GET( UINT8* base_ptr, UINT16* version )
{
	BM_GetStatistics_Header_Version_GET( base_ptr, *version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetStatistics_Header_Accessibility_GET( UINT8* base_ptr, UINT16* accessibility )
{
	BM_GetStatistics_Header_Accessibility_GET( base_ptr, *accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetStatistics_Header_Status_GET( UINT8* base_ptr, UINT16* status )
{
	BM_GetStatistics_Header_Status_GET( base_ptr, *status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetStatistics_Header_Length_GET( UINT8* base_ptr, UINT32* listSize )
{
	BM_GetStatistics_Header_Length_GET( base_ptr, *listSize );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetStatistics_List_GET_FIRST( UINT8* base_ptr, UINT32* out_diff, UINT32* out_cur_bitoff )
{
	UINT8* out_cur_ptr = base_ptr;
	BM_GetStatistics_List_GET_FIRST( base_ptr, out_cur_ptr, *out_cur_bitoff );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetStatistics_List_GET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetStatistics_List_GET_TYPE( cur_ptr, cur_bitoff, *type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetStatistics_List_GET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_length, UINT32 err )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetStatistics_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, *out_length, err );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetStatistics_List_CURRENT_TimeStamp_value_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetStatistics_List_CURRENT_TimeStamp_value_GET( base_ptr, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetStatistics_List_CURRENT_StatisticsCommon_TotalRxBytes_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* TotalRxBytes )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetStatistics_List_CURRENT_StatisticsCommon_TotalRxBytes_GET( base_ptr, cur_ptr, cur_bitoff, *TotalRxBytes );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetStatistics_List_CURRENT_StatisticsCommon_TotalTxBytes_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* TotalTxBytes )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetStatistics_List_CURRENT_StatisticsCommon_TotalTxBytes_GET( base_ptr, cur_ptr, cur_bitoff, *TotalTxBytes );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetStatistics_List_CURRENT_StatisticsCommon_TotalRxPackets_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* TotalRxPackets )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetStatistics_List_CURRENT_StatisticsCommon_TotalRxPackets_GET( base_ptr, cur_ptr, cur_bitoff, *TotalRxPackets );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetStatistics_List_CURRENT_StatisticsCommon_TotalTxPackets_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* TotalTxPackets )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetStatistics_List_CURRENT_StatisticsCommon_TotalTxPackets_GET( base_ptr, cur_ptr, cur_bitoff, *TotalTxPackets );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetStatistics_List_GET_NEXT( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_diff, UINT32* out_cur_bitoff, UINT32 err )
{
	UINT8* out_cur_ptr = base_ptr;
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetStatistics_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, out_cur_ptr, *out_cur_bitoff, err );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetStatistics_List_SET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetStatistics_List_SET_TYPE( cur_ptr, cur_bitoff, type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetStatistics_List_SET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 lenOfLen, UINT32 length )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	lenOfLen = 2;
	BM_GetStatistics_List_SET_LENGTH( cur_ptr, cur_bitoff, lenOfLen, length );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetStatistics_List_CURRENT_TimeStamp_value_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetStatistics_List_CURRENT_TimeStamp_value_SET( base_ptr, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetStatistics_List_CURRENT_StatisticsCommon_TotalRxBytes_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 TotalRxBytes )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetStatistics_List_CURRENT_StatisticsCommon_TotalRxBytes_SET( base_ptr, cur_ptr, cur_bitoff, TotalRxBytes );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetStatistics_List_CURRENT_StatisticsCommon_TotalTxBytes_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 TotalTxBytes )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetStatistics_List_CURRENT_StatisticsCommon_TotalTxBytes_SET( base_ptr, cur_ptr, cur_bitoff, TotalTxBytes );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetStatistics_List_CURRENT_StatisticsCommon_TotalRxPackets_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 TotalRxPackets )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetStatistics_List_CURRENT_StatisticsCommon_TotalRxPackets_SET( base_ptr, cur_ptr, cur_bitoff, TotalRxPackets );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetStatistics_List_CURRENT_StatisticsCommon_TotalTxPackets_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 TotalTxPackets )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetStatistics_List_CURRENT_StatisticsCommon_TotalTxPackets_SET( base_ptr, cur_ptr, cur_bitoff, TotalTxPackets );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetStatistics_Header_Type_SET( UINT8* base_ptr, UINT32 opcode )
{
	BM_GetStatistics_Header_Type_SET( base_ptr, opcode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetStatistics_Header_Version_SET( UINT8* base_ptr, UINT16 version )
{
	BM_GetStatistics_Header_Version_SET( base_ptr, version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetStatistics_Header_Accessibility_SET( UINT8* base_ptr, UINT16 accessibility )
{
	BM_GetStatistics_Header_Accessibility_SET( base_ptr, accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetStatistics_Header_Status_SET( UINT8* base_ptr, UINT16 status )
{
	BM_GetStatistics_Header_Status_SET( base_ptr, status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetStatistics_Header_Length_SET( UINT8* base_ptr, UINT32 len )
{
	BM_GetStatistics_Header_Length_SET( base_ptr, len );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetDeviceInfo_Header_Version_GET( UINT8* base_ptr, UINT16* version )
{
	BM_GetDeviceInfo_Header_Version_GET( base_ptr, *version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetDeviceInfo_Header_Accessibility_GET( UINT8* base_ptr, UINT16* accessibility )
{
	BM_GetDeviceInfo_Header_Accessibility_GET( base_ptr, *accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetDeviceInfo_Header_Status_GET( UINT8* base_ptr, UINT16* status )
{
	BM_GetDeviceInfo_Header_Status_GET( base_ptr, *status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetDeviceInfo_Header_Length_GET( UINT8* base_ptr, UINT32* listSize )
{
	BM_GetDeviceInfo_Header_Length_GET( base_ptr, *listSize );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetDeviceInfo_List_GET_FIRST( UINT8* base_ptr, UINT32* out_diff, UINT32* out_cur_bitoff )
{
	UINT8* out_cur_ptr = base_ptr;
	BM_GetDeviceInfo_List_GET_FIRST( base_ptr, out_cur_ptr, *out_cur_bitoff );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetDeviceInfo_List_GET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetDeviceInfo_List_GET_TYPE( cur_ptr, cur_bitoff, *type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetDeviceInfo_List_GET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_length, UINT32 err )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetDeviceInfo_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, *out_length, err );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetDeviceInfo_List_CURRENT_VersionsStrings_ActualLen_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* ActualLen )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetDeviceInfo_List_CURRENT_VersionsStrings_ActualLen_GET( base_ptr, cur_ptr, cur_bitoff, *ActualLen );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetDeviceInfo_List_CURRENT_VersionsStrings_BufferArr_value_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetDeviceInfo_List_CURRENT_VersionsStrings_BufferArr_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetDeviceInfo_List_CURRENT_DeviceDetails_ModelType_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* ModelType )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetDeviceInfo_List_CURRENT_DeviceDetails_ModelType_GET( base_ptr, cur_ptr, cur_bitoff, *ModelType );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetDeviceInfo_List_CURRENT_DeviceDetails_ModelTypeStringLength_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* ModelTypeStringLength )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetDeviceInfo_List_CURRENT_DeviceDetails_ModelTypeStringLength_GET( base_ptr, cur_ptr, cur_bitoff, *ModelTypeStringLength );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetDeviceInfo_List_CURRENT_DeviceDetails_ModelTypeString_value_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetDeviceInfo_List_CURRENT_DeviceDetails_ModelTypeString_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetDeviceInfo_List_CURRENT_DeviceDetails_ManufacturerId_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* ManufacturerId )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetDeviceInfo_List_CURRENT_DeviceDetails_ManufacturerId_GET( base_ptr, cur_ptr, cur_bitoff, *ManufacturerId );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetDeviceInfo_List_CURRENT_DeviceDetails_ManufacturerIdStringLength_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* ManufacturerIdStringLength )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetDeviceInfo_List_CURRENT_DeviceDetails_ManufacturerIdStringLength_GET( base_ptr, cur_ptr, cur_bitoff, *ManufacturerIdStringLength );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetDeviceInfo_List_CURRENT_DeviceDetails_ManufacturerIdString_value_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetDeviceInfo_List_CURRENT_DeviceDetails_ManufacturerIdString_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetDeviceInfo_List_CURRENT_DeviceDetails_NvmProductStringLength_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* NvmProductStringLength )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetDeviceInfo_List_CURRENT_DeviceDetails_NvmProductStringLength_GET( base_ptr, cur_ptr, cur_bitoff, *NvmProductStringLength );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetDeviceInfo_List_CURRENT_DeviceDetails_NvmProductString_value_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetDeviceInfo_List_CURRENT_DeviceDetails_NvmProductString_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetDeviceInfo_List_CURRENT_DeviceDetails_Nonce_value_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetDeviceInfo_List_CURRENT_DeviceDetails_Nonce_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetDeviceInfo_List_CURRENT_DeviceDetails_MacAddress_value_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetDeviceInfo_List_CURRENT_DeviceDetails_MacAddress_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetDeviceInfo_List_CURRENT_DeviceDetails_Reserved2_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* Reserved2 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetDeviceInfo_List_CURRENT_DeviceDetails_Reserved2_GET( base_ptr, cur_ptr, cur_bitoff, *Reserved2 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetDeviceInfo_List_CURRENT_OdmInformation_OdmInformation_value_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetDeviceInfo_List_CURRENT_OdmInformation_OdmInformation_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetDeviceInfo_List_CURRENT_NvmInformation_GeneralImageVersion_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* GeneralImageVersion )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetDeviceInfo_List_CURRENT_NvmInformation_GeneralImageVersion_GET( base_ptr, cur_ptr, cur_bitoff, *GeneralImageVersion );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetDeviceInfo_List_CURRENT_NvmInformation_ContentVersion_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* ContentVersion )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetDeviceInfo_List_CURRENT_NvmInformation_ContentVersion_GET( base_ptr, cur_ptr, cur_bitoff, *ContentVersion );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetDeviceInfo_List_CURRENT_NvmManufacturer_NvmManufacturerIdStringLength_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* NvmManufacturerIdStringLength )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetDeviceInfo_List_CURRENT_NvmManufacturer_NvmManufacturerIdStringLength_GET( base_ptr, cur_ptr, cur_bitoff, *NvmManufacturerIdStringLength );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetDeviceInfo_List_CURRENT_NvmManufacturer_NvmManufacturerIdString_value_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetDeviceInfo_List_CURRENT_NvmManufacturer_NvmManufacturerIdString_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetDeviceInfo_List_GET_NEXT( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_diff, UINT32* out_cur_bitoff, UINT32 err )
{
	UINT8* out_cur_ptr = base_ptr;
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetDeviceInfo_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, out_cur_ptr, *out_cur_bitoff, err );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetDeviceInfo_List_SET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetDeviceInfo_List_SET_TYPE( cur_ptr, cur_bitoff, type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetDeviceInfo_List_SET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 lenOfLen, UINT32 length )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	lenOfLen = 2;
	BM_GetDeviceInfo_List_SET_LENGTH( cur_ptr, cur_bitoff, lenOfLen, length );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetDeviceInfo_List_CURRENT_VersionsStrings_ActualLen_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 ActualLen )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetDeviceInfo_List_CURRENT_VersionsStrings_ActualLen_SET( base_ptr, cur_ptr, cur_bitoff, ActualLen );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetDeviceInfo_List_CURRENT_VersionsStrings_BufferArr_value_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetDeviceInfo_List_CURRENT_VersionsStrings_BufferArr_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetDeviceInfo_List_CURRENT_DeviceDetails_ModelType_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 ModelType )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetDeviceInfo_List_CURRENT_DeviceDetails_ModelType_SET( base_ptr, cur_ptr, cur_bitoff, ModelType );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetDeviceInfo_List_CURRENT_DeviceDetails_ModelTypeStringLength_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 ModelTypeStringLength )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetDeviceInfo_List_CURRENT_DeviceDetails_ModelTypeStringLength_SET( base_ptr, cur_ptr, cur_bitoff, ModelTypeStringLength );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetDeviceInfo_List_CURRENT_DeviceDetails_ModelTypeString_value_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetDeviceInfo_List_CURRENT_DeviceDetails_ModelTypeString_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetDeviceInfo_List_CURRENT_DeviceDetails_ManufacturerId_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 ManufacturerId )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetDeviceInfo_List_CURRENT_DeviceDetails_ManufacturerId_SET( base_ptr, cur_ptr, cur_bitoff, ManufacturerId );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetDeviceInfo_List_CURRENT_DeviceDetails_ManufacturerIdStringLength_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 ManufacturerIdStringLength )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetDeviceInfo_List_CURRENT_DeviceDetails_ManufacturerIdStringLength_SET( base_ptr, cur_ptr, cur_bitoff, ManufacturerIdStringLength );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetDeviceInfo_List_CURRENT_DeviceDetails_ManufacturerIdString_value_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetDeviceInfo_List_CURRENT_DeviceDetails_ManufacturerIdString_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetDeviceInfo_List_CURRENT_DeviceDetails_NvmProductStringLength_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 NvmProductStringLength )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetDeviceInfo_List_CURRENT_DeviceDetails_NvmProductStringLength_SET( base_ptr, cur_ptr, cur_bitoff, NvmProductStringLength );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetDeviceInfo_List_CURRENT_DeviceDetails_NvmProductString_value_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetDeviceInfo_List_CURRENT_DeviceDetails_NvmProductString_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetDeviceInfo_List_CURRENT_DeviceDetails_Nonce_value_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetDeviceInfo_List_CURRENT_DeviceDetails_Nonce_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetDeviceInfo_List_CURRENT_DeviceDetails_MacAddress_value_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetDeviceInfo_List_CURRENT_DeviceDetails_MacAddress_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetDeviceInfo_List_CURRENT_DeviceDetails_Reserved2_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 Reserved2 )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetDeviceInfo_List_CURRENT_DeviceDetails_Reserved2_SET( base_ptr, cur_ptr, cur_bitoff, Reserved2 );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetDeviceInfo_List_CURRENT_OdmInformation_OdmInformation_value_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetDeviceInfo_List_CURRENT_OdmInformation_OdmInformation_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetDeviceInfo_List_CURRENT_NvmInformation_GeneralImageVersion_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 GeneralImageVersion )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetDeviceInfo_List_CURRENT_NvmInformation_GeneralImageVersion_SET( base_ptr, cur_ptr, cur_bitoff, GeneralImageVersion );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetDeviceInfo_List_CURRENT_NvmInformation_ContentVersion_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 ContentVersion )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetDeviceInfo_List_CURRENT_NvmInformation_ContentVersion_SET( base_ptr, cur_ptr, cur_bitoff, ContentVersion );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetDeviceInfo_List_CURRENT_NvmManufacturer_NvmManufacturerIdStringLength_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 NvmManufacturerIdStringLength )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetDeviceInfo_List_CURRENT_NvmManufacturer_NvmManufacturerIdStringLength_SET( base_ptr, cur_ptr, cur_bitoff, NvmManufacturerIdStringLength );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetDeviceInfo_List_CURRENT_NvmManufacturer_NvmManufacturerIdString_value_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetDeviceInfo_List_CURRENT_NvmManufacturer_NvmManufacturerIdString_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetDeviceInfo_Header_Type_SET( UINT8* base_ptr, UINT32 opcode )
{
	BM_GetDeviceInfo_Header_Type_SET( base_ptr, opcode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetDeviceInfo_Header_Version_SET( UINT8* base_ptr, UINT16 version )
{
	BM_GetDeviceInfo_Header_Version_SET( base_ptr, version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetDeviceInfo_Header_Accessibility_SET( UINT8* base_ptr, UINT16 accessibility )
{
	BM_GetDeviceInfo_Header_Accessibility_SET( base_ptr, accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetDeviceInfo_Header_Status_SET( UINT8* base_ptr, UINT16 status )
{
	BM_GetDeviceInfo_Header_Status_SET( base_ptr, status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetDeviceInfo_Header_Length_SET( UINT8* base_ptr, UINT32 len )
{
	BM_GetDeviceInfo_Header_Length_SET( base_ptr, len );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CmdMonitorControl_Header_Version_GET( UINT8* base_ptr, UINT16* version )
{
	BM_CmdMonitorControl_Header_Version_GET( base_ptr, *version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CmdMonitorControl_Header_Accessibility_GET( UINT8* base_ptr, UINT16* accessibility )
{
	BM_CmdMonitorControl_Header_Accessibility_GET( base_ptr, *accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CmdMonitorControl_Header_Status_GET( UINT8* base_ptr, UINT16* status )
{
	BM_CmdMonitorControl_Header_Status_GET( base_ptr, *status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CmdMonitorControl_Header_Length_GET( UINT8* base_ptr, UINT32* listSize )
{
	BM_CmdMonitorControl_Header_Length_GET( base_ptr, *listSize );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CmdMonitorControl_List_GET_FIRST( UINT8* base_ptr, UINT32* out_diff, UINT32* out_cur_bitoff )
{
	UINT8* out_cur_ptr = base_ptr;
	BM_CmdMonitorControl_List_GET_FIRST( base_ptr, out_cur_ptr, *out_cur_bitoff );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CmdMonitorControl_List_GET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_CmdMonitorControl_List_GET_TYPE( cur_ptr, cur_bitoff, *type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CmdMonitorControl_List_GET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_length, UINT32 err )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_CmdMonitorControl_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, *out_length, err );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CmdMonitorControl_List_CURRENT_MonitorMode_value_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_CmdMonitorControl_List_CURRENT_MonitorMode_value_GET( base_ptr, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CmdMonitorControl_List_GET_NEXT( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_diff, UINT32* out_cur_bitoff, UINT32 err )
{
	UINT8* out_cur_ptr = base_ptr;
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_CmdMonitorControl_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, out_cur_ptr, *out_cur_bitoff, err );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CmdMonitorControl_List_SET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_CmdMonitorControl_List_SET_TYPE( cur_ptr, cur_bitoff, type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CmdMonitorControl_List_SET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 lenOfLen, UINT32 length )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	lenOfLen = 2;
	BM_CmdMonitorControl_List_SET_LENGTH( cur_ptr, cur_bitoff, lenOfLen, length );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CmdMonitorControl_List_CURRENT_MonitorMode_value_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_CmdMonitorControl_List_CURRENT_MonitorMode_value_SET( base_ptr, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CmdMonitorControl_Header_Type_SET( UINT8* base_ptr, UINT32 opcode )
{
	BM_CmdMonitorControl_Header_Type_SET( base_ptr, opcode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CmdMonitorControl_Header_Version_SET( UINT8* base_ptr, UINT16 version )
{
	BM_CmdMonitorControl_Header_Version_SET( base_ptr, version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CmdMonitorControl_Header_Accessibility_SET( UINT8* base_ptr, UINT16 accessibility )
{
	BM_CmdMonitorControl_Header_Accessibility_SET( base_ptr, accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CmdMonitorControl_Header_Status_SET( UINT8* base_ptr, UINT16 status )
{
	BM_CmdMonitorControl_Header_Status_SET( base_ptr, status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CmdMonitorControl_Header_Length_SET( UINT8* base_ptr, UINT32 len )
{
	BM_CmdMonitorControl_Header_Length_SET( base_ptr, len );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetMonitorFilterTable_Header_Version_GET( UINT8* base_ptr, UINT16* version )
{
	BM_GetMonitorFilterTable_Header_Version_GET( base_ptr, *version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetMonitorFilterTable_Header_Accessibility_GET( UINT8* base_ptr, UINT16* accessibility )
{
	BM_GetMonitorFilterTable_Header_Accessibility_GET( base_ptr, *accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetMonitorFilterTable_Header_Status_GET( UINT8* base_ptr, UINT16* status )
{
	BM_GetMonitorFilterTable_Header_Status_GET( base_ptr, *status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetMonitorFilterTable_Header_Length_GET( UINT8* base_ptr, UINT32* listSize )
{
	BM_GetMonitorFilterTable_Header_Length_GET( base_ptr, *listSize );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetMonitorFilterTable_List_GET_FIRST( UINT8* base_ptr, UINT32* out_diff, UINT32* out_cur_bitoff )
{
	UINT8* out_cur_ptr = base_ptr;
	BM_GetMonitorFilterTable_List_GET_FIRST( base_ptr, out_cur_ptr, *out_cur_bitoff );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetMonitorFilterTable_List_GET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetMonitorFilterTable_List_GET_TYPE( cur_ptr, cur_bitoff, *type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetMonitorFilterTable_List_GET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_length, UINT32 err )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetMonitorFilterTable_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, *out_length, err );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetMonitorFilterTable_List_CURRENT_MonitorFilterTable_FilterTable_value_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetMonitorFilterTable_List_CURRENT_MonitorFilterTable_FilterTable_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetMonitorFilterTable_List_GET_NEXT( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_diff, UINT32* out_cur_bitoff, UINT32 err )
{
	UINT8* out_cur_ptr = base_ptr;
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetMonitorFilterTable_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, out_cur_ptr, *out_cur_bitoff, err );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetMonitorFilterTable_List_SET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetMonitorFilterTable_List_SET_TYPE( cur_ptr, cur_bitoff, type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetMonitorFilterTable_List_SET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 lenOfLen, UINT32 length )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	lenOfLen = 2;
	BM_GetMonitorFilterTable_List_SET_LENGTH( cur_ptr, cur_bitoff, lenOfLen, length );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetMonitorFilterTable_List_CURRENT_MonitorFilterTable_FilterTable_value_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetMonitorFilterTable_List_CURRENT_MonitorFilterTable_FilterTable_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetMonitorFilterTable_Header_Type_SET( UINT8* base_ptr, UINT32 opcode )
{
	BM_GetMonitorFilterTable_Header_Type_SET( base_ptr, opcode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetMonitorFilterTable_Header_Version_SET( UINT8* base_ptr, UINT16 version )
{
	BM_GetMonitorFilterTable_Header_Version_SET( base_ptr, version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetMonitorFilterTable_Header_Accessibility_SET( UINT8* base_ptr, UINT16 accessibility )
{
	BM_GetMonitorFilterTable_Header_Accessibility_SET( base_ptr, accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetMonitorFilterTable_Header_Status_SET( UINT8* base_ptr, UINT16 status )
{
	BM_GetMonitorFilterTable_Header_Status_SET( base_ptr, status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetMonitorFilterTable_Header_Length_SET( UINT8* base_ptr, UINT32 len )
{
	BM_GetMonitorFilterTable_Header_Length_SET( base_ptr, len );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetTraceSeverityTable_Header_Version_GET( UINT8* base_ptr, UINT16* version )
{
	BM_GetTraceSeverityTable_Header_Version_GET( base_ptr, *version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetTraceSeverityTable_Header_Accessibility_GET( UINT8* base_ptr, UINT16* accessibility )
{
	BM_GetTraceSeverityTable_Header_Accessibility_GET( base_ptr, *accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetTraceSeverityTable_Header_Status_GET( UINT8* base_ptr, UINT16* status )
{
	BM_GetTraceSeverityTable_Header_Status_GET( base_ptr, *status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetTraceSeverityTable_Header_Length_GET( UINT8* base_ptr, UINT32* listSize )
{
	BM_GetTraceSeverityTable_Header_Length_GET( base_ptr, *listSize );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetTraceSeverityTable_List_GET_FIRST( UINT8* base_ptr, UINT32* out_diff, UINT32* out_cur_bitoff )
{
	UINT8* out_cur_ptr = base_ptr;
	BM_GetTraceSeverityTable_List_GET_FIRST( base_ptr, out_cur_ptr, *out_cur_bitoff );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetTraceSeverityTable_List_GET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetTraceSeverityTable_List_GET_TYPE( cur_ptr, cur_bitoff, *type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetTraceSeverityTable_List_GET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_length, UINT32 err )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetTraceSeverityTable_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, *out_length, err );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetTraceSeverityTable_List_CURRENT_TraceSeverityTable_SeverityTable_value_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetTraceSeverityTable_List_CURRENT_TraceSeverityTable_SeverityTable_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetTraceSeverityTable_List_GET_NEXT( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_diff, UINT32* out_cur_bitoff, UINT32 err )
{
	UINT8* out_cur_ptr = base_ptr;
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetTraceSeverityTable_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, out_cur_ptr, *out_cur_bitoff, err );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetTraceSeverityTable_List_SET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetTraceSeverityTable_List_SET_TYPE( cur_ptr, cur_bitoff, type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetTraceSeverityTable_List_SET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 lenOfLen, UINT32 length )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	lenOfLen = 2;
	BM_GetTraceSeverityTable_List_SET_LENGTH( cur_ptr, cur_bitoff, lenOfLen, length );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetTraceSeverityTable_List_CURRENT_TraceSeverityTable_SeverityTable_value_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_GetTraceSeverityTable_List_CURRENT_TraceSeverityTable_SeverityTable_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetTraceSeverityTable_Header_Type_SET( UINT8* base_ptr, UINT32 opcode )
{
	BM_GetTraceSeverityTable_Header_Type_SET( base_ptr, opcode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetTraceSeverityTable_Header_Version_SET( UINT8* base_ptr, UINT16 version )
{
	BM_GetTraceSeverityTable_Header_Version_SET( base_ptr, version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetTraceSeverityTable_Header_Accessibility_SET( UINT8* base_ptr, UINT16 accessibility )
{
	BM_GetTraceSeverityTable_Header_Accessibility_SET( base_ptr, accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetTraceSeverityTable_Header_Status_SET( UINT8* base_ptr, UINT16 status )
{
	BM_GetTraceSeverityTable_Header_Status_SET( base_ptr, status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_GetTraceSeverityTable_Header_Length_SET( UINT8* base_ptr, UINT32 len )
{
	BM_GetTraceSeverityTable_Header_Length_SET( base_ptr, len );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceCMD_Header_Version_GET( UINT8* base_ptr, UINT16* version )
{
	BM_CheckL3L4InterfaceCMD_Header_Version_GET( base_ptr, *version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceCMD_Header_Accessibility_GET( UINT8* base_ptr, UINT16* accessibility )
{
	BM_CheckL3L4InterfaceCMD_Header_Accessibility_GET( base_ptr, *accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceCMD_Header_Status_GET( UINT8* base_ptr, UINT16* status )
{
	BM_CheckL3L4InterfaceCMD_Header_Status_GET( base_ptr, *status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceCMD_Header_Length_GET( UINT8* base_ptr, UINT32* listSize )
{
	BM_CheckL3L4InterfaceCMD_Header_Length_GET( base_ptr, *listSize );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceCMD_List_GET_FIRST( UINT8* base_ptr, UINT32* out_diff, UINT32* out_cur_bitoff )
{
	UINT8* out_cur_ptr = base_ptr;
	BM_CheckL3L4InterfaceCMD_List_GET_FIRST( base_ptr, out_cur_ptr, *out_cur_bitoff );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceCMD_List_GET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_CheckL3L4InterfaceCMD_List_GET_TYPE( cur_ptr, cur_bitoff, *type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceCMD_List_GET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_length, UINT32 err )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_CheckL3L4InterfaceCMD_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, *out_length, err );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceCMD_List_CURRENT_value_value_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_CheckL3L4InterfaceCMD_List_CURRENT_value_value_GET( base_ptr, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceCMD_List_GET_NEXT( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_diff, UINT32* out_cur_bitoff, UINT32 err )
{
	UINT8* out_cur_ptr = base_ptr;
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_CheckL3L4InterfaceCMD_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, out_cur_ptr, *out_cur_bitoff, err );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceCMD_List_SET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_CheckL3L4InterfaceCMD_List_SET_TYPE( cur_ptr, cur_bitoff, type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceCMD_List_SET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 lenOfLen, UINT32 length )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	lenOfLen = 2;
	BM_CheckL3L4InterfaceCMD_List_SET_LENGTH( cur_ptr, cur_bitoff, lenOfLen, length );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceCMD_List_CURRENT_value_value_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_CheckL3L4InterfaceCMD_List_CURRENT_value_value_SET( base_ptr, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceCMD_Header_Type_SET( UINT8* base_ptr, UINT32 opcode )
{
	BM_CheckL3L4InterfaceCMD_Header_Type_SET( base_ptr, opcode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceCMD_Header_Version_SET( UINT8* base_ptr, UINT16 version )
{
	BM_CheckL3L4InterfaceCMD_Header_Version_SET( base_ptr, version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceCMD_Header_Accessibility_SET( UINT8* base_ptr, UINT16 accessibility )
{
	BM_CheckL3L4InterfaceCMD_Header_Accessibility_SET( base_ptr, accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceCMD_Header_Status_SET( UINT8* base_ptr, UINT16 status )
{
	BM_CheckL3L4InterfaceCMD_Header_Status_SET( base_ptr, status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_CheckL3L4InterfaceCMD_Header_Length_SET( UINT8* base_ptr, UINT32 len )
{
	BM_CheckL3L4InterfaceCMD_Header_Length_SET( base_ptr, len );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportState_Header_Version_GET( UINT8* base_ptr, UINT16* version )
{
	BM_ReportState_Header_Version_GET( base_ptr, *version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportState_Header_Accessibility_GET( UINT8* base_ptr, UINT16* accessibility )
{
	BM_ReportState_Header_Accessibility_GET( base_ptr, *accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportState_Header_Status_GET( UINT8* base_ptr, UINT16* status )
{
	BM_ReportState_Header_Status_GET( base_ptr, *status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportState_Header_Length_GET( UINT8* base_ptr, UINT32* listSize )
{
	BM_ReportState_Header_Length_GET( base_ptr, *listSize );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportState_List_GET_FIRST( UINT8* base_ptr, UINT32* out_diff, UINT32* out_cur_bitoff )
{
	UINT8* out_cur_ptr = base_ptr;
	BM_ReportState_List_GET_FIRST( base_ptr, out_cur_ptr, *out_cur_bitoff );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportState_List_GET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportState_List_GET_TYPE( cur_ptr, cur_bitoff, *type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportState_List_GET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_length, UINT32 err )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportState_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, *out_length, err );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportState_List_CURRENT_ReportStateReason_value_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportState_List_CURRENT_ReportStateReason_value_GET( base_ptr, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportState_List_CURRENT_SystemState_value_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportState_List_CURRENT_SystemState_value_GET( base_ptr, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportState_List_CURRENT_LinkStatus_UpLinkSpeed_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* UpLinkSpeed )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportState_List_CURRENT_LinkStatus_UpLinkSpeed_GET( base_ptr, cur_ptr, cur_bitoff, *UpLinkSpeed );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportState_List_CURRENT_LinkStatus_DownLinkSpeed_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* DownLinkSpeed )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportState_List_CURRENT_LinkStatus_DownLinkSpeed_GET( base_ptr, cur_ptr, cur_bitoff, *DownLinkSpeed );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportState_List_CURRENT_LinkStatus_CenterFrequency_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* CenterFrequency )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportState_List_CURRENT_LinkStatus_CenterFrequency_GET( base_ptr, cur_ptr, cur_bitoff, *CenterFrequency );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportState_List_CURRENT_LinkStatus_TxPower_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* TxPower )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportState_List_CURRENT_LinkStatus_TxPower_GET( base_ptr, cur_ptr, cur_bitoff, *TxPower );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportState_List_CURRENT_LinkStatus_RxRssi_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* RxRssi )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportState_List_CURRENT_LinkStatus_RxRssi_GET( base_ptr, cur_ptr, cur_bitoff, *RxRssi );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportState_List_CURRENT_LinkStatus_RxCinr_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* RxCinr )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportState_List_CURRENT_LinkStatus_RxCinr_GET( base_ptr, cur_ptr, cur_bitoff, *RxCinr );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportState_List_CURRENT_LinkStatus_BSID_value_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportState_List_CURRENT_LinkStatus_BSID_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportState_List_CURRENT_LinkStatus_LinkQuality_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* LinkQuality )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportState_List_CURRENT_LinkStatus_LinkQuality_GET( base_ptr, cur_ptr, cur_bitoff, *LinkQuality );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportState_List_CURRENT_LinkStatus_Reserved_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* Reserved )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportState_List_CURRENT_LinkStatus_Reserved_GET( base_ptr, cur_ptr, cur_bitoff, *Reserved );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportState_List_CURRENT_MediaStatus_value_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportState_List_CURRENT_MediaStatus_value_GET( base_ptr, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportState_List_CURRENT_ConnectProgress_value_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportState_List_CURRENT_ConnectProgress_value_GET( base_ptr, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportState_List_CURRENT_RFStatus_SwRFSwitch_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* SwRFSwitch )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportState_List_CURRENT_RFStatus_SwRFSwitch_GET( base_ptr, cur_ptr, cur_bitoff, *SwRFSwitch );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportState_List_CURRENT_RFStatus_HwRFSwitch_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* HwRFSwitch )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportState_List_CURRENT_RFStatus_HwRFSwitch_GET( base_ptr, cur_ptr, cur_bitoff, *HwRFSwitch );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportState_List_CURRENT_RFStatus_Reserved_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* Reserved )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportState_List_CURRENT_RFStatus_Reserved_GET( base_ptr, cur_ptr, cur_bitoff, *Reserved );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportState_List_CURRENT_ChannelInfo_Frequency_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* Frequency )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportState_List_CURRENT_ChannelInfo_Frequency_GET( base_ptr, cur_ptr, cur_bitoff, *Frequency );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportState_List_CURRENT_ChannelInfo_ChannelId_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* ChannelId )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportState_List_CURRENT_ChannelInfo_ChannelId_GET( base_ptr, cur_ptr, cur_bitoff, *ChannelId );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportState_List_CURRENT_ChannelInfo_Bandwidth_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* Bandwidth )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportState_List_CURRENT_ChannelInfo_Bandwidth_GET( base_ptr, cur_ptr, cur_bitoff, *Bandwidth );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportState_List_CURRENT_ChannelInfo_Fft_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* Fft )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportState_List_CURRENT_ChannelInfo_Fft_GET( base_ptr, cur_ptr, cur_bitoff, *Fft );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportState_List_CURRENT_ChannelInfo_Preambles_value_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportState_List_CURRENT_ChannelInfo_Preambles_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportState_List_CURRENT_ChannelInfo_Reserved_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8* Reserved )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportState_List_CURRENT_ChannelInfo_Reserved_GET( base_ptr, cur_ptr, cur_bitoff, *Reserved );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportState_List_GET_NEXT( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_diff, UINT32* out_cur_bitoff, UINT32 err )
{
	UINT8* out_cur_ptr = base_ptr;
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportState_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, out_cur_ptr, *out_cur_bitoff, err );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportState_List_SET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportState_List_SET_TYPE( cur_ptr, cur_bitoff, type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportState_List_SET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 lenOfLen, UINT32 length )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	lenOfLen = 2;
	BM_ReportState_List_SET_LENGTH( cur_ptr, cur_bitoff, lenOfLen, length );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportState_List_CURRENT_ReportStateReason_value_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportState_List_CURRENT_ReportStateReason_value_SET( base_ptr, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportState_List_CURRENT_SystemState_value_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportState_List_CURRENT_SystemState_value_SET( base_ptr, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportState_List_CURRENT_LinkStatus_UpLinkSpeed_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 UpLinkSpeed )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportState_List_CURRENT_LinkStatus_UpLinkSpeed_SET( base_ptr, cur_ptr, cur_bitoff, UpLinkSpeed );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportState_List_CURRENT_LinkStatus_DownLinkSpeed_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 DownLinkSpeed )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportState_List_CURRENT_LinkStatus_DownLinkSpeed_SET( base_ptr, cur_ptr, cur_bitoff, DownLinkSpeed );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportState_List_CURRENT_LinkStatus_CenterFrequency_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 CenterFrequency )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportState_List_CURRENT_LinkStatus_CenterFrequency_SET( base_ptr, cur_ptr, cur_bitoff, CenterFrequency );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportState_List_CURRENT_LinkStatus_TxPower_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 TxPower )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportState_List_CURRENT_LinkStatus_TxPower_SET( base_ptr, cur_ptr, cur_bitoff, TxPower );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportState_List_CURRENT_LinkStatus_RxRssi_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 RxRssi )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportState_List_CURRENT_LinkStatus_RxRssi_SET( base_ptr, cur_ptr, cur_bitoff, RxRssi );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportState_List_CURRENT_LinkStatus_RxCinr_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 RxCinr )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportState_List_CURRENT_LinkStatus_RxCinr_SET( base_ptr, cur_ptr, cur_bitoff, RxCinr );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportState_List_CURRENT_LinkStatus_BSID_value_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportState_List_CURRENT_LinkStatus_BSID_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportState_List_CURRENT_LinkStatus_LinkQuality_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 LinkQuality )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportState_List_CURRENT_LinkStatus_LinkQuality_SET( base_ptr, cur_ptr, cur_bitoff, LinkQuality );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportState_List_CURRENT_LinkStatus_Reserved_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 Reserved )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportState_List_CURRENT_LinkStatus_Reserved_SET( base_ptr, cur_ptr, cur_bitoff, Reserved );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportState_List_CURRENT_MediaStatus_value_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportState_List_CURRENT_MediaStatus_value_SET( base_ptr, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportState_List_CURRENT_ConnectProgress_value_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportState_List_CURRENT_ConnectProgress_value_SET( base_ptr, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportState_List_CURRENT_RFStatus_SwRFSwitch_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 SwRFSwitch )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportState_List_CURRENT_RFStatus_SwRFSwitch_SET( base_ptr, cur_ptr, cur_bitoff, SwRFSwitch );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportState_List_CURRENT_RFStatus_HwRFSwitch_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 HwRFSwitch )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportState_List_CURRENT_RFStatus_HwRFSwitch_SET( base_ptr, cur_ptr, cur_bitoff, HwRFSwitch );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportState_List_CURRENT_RFStatus_Reserved_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 Reserved )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportState_List_CURRENT_RFStatus_Reserved_SET( base_ptr, cur_ptr, cur_bitoff, Reserved );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportState_List_CURRENT_ChannelInfo_Frequency_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 Frequency )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportState_List_CURRENT_ChannelInfo_Frequency_SET( base_ptr, cur_ptr, cur_bitoff, Frequency );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportState_List_CURRENT_ChannelInfo_ChannelId_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 ChannelId )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportState_List_CURRENT_ChannelInfo_ChannelId_SET( base_ptr, cur_ptr, cur_bitoff, ChannelId );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportState_List_CURRENT_ChannelInfo_Bandwidth_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 Bandwidth )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportState_List_CURRENT_ChannelInfo_Bandwidth_SET( base_ptr, cur_ptr, cur_bitoff, Bandwidth );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportState_List_CURRENT_ChannelInfo_Fft_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 Fft )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportState_List_CURRENT_ChannelInfo_Fft_SET( base_ptr, cur_ptr, cur_bitoff, Fft );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportState_List_CURRENT_ChannelInfo_Preambles_value_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportState_List_CURRENT_ChannelInfo_Preambles_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportState_List_CURRENT_ChannelInfo_Reserved_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT8 Reserved )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ReportState_List_CURRENT_ChannelInfo_Reserved_SET( base_ptr, cur_ptr, cur_bitoff, Reserved );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportState_Header_Type_SET( UINT8* base_ptr, UINT32 opcode )
{
	BM_ReportState_Header_Type_SET( base_ptr, opcode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportState_Header_Version_SET( UINT8* base_ptr, UINT16 version )
{
	BM_ReportState_Header_Version_SET( base_ptr, version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportState_Header_Accessibility_SET( UINT8* base_ptr, UINT16 accessibility )
{
	BM_ReportState_Header_Accessibility_SET( base_ptr, accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportState_Header_Status_SET( UINT8* base_ptr, UINT16 status )
{
	BM_ReportState_Header_Status_SET( base_ptr, status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportState_Header_Length_SET( UINT8* base_ptr, UINT32 len )
{
	BM_ReportState_Header_Length_SET( base_ptr, len );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SPLockRequest_Header_Version_GET( UINT8* base_ptr, UINT16* version )
{
	BM_SPLockRequest_Header_Version_GET( base_ptr, *version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SPLockRequest_Header_Accessibility_GET( UINT8* base_ptr, UINT16* accessibility )
{
	BM_SPLockRequest_Header_Accessibility_GET( base_ptr, *accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SPLockRequest_Header_Status_GET( UINT8* base_ptr, UINT16* status )
{
	BM_SPLockRequest_Header_Status_GET( base_ptr, *status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SPLockRequest_Header_Length_GET( UINT8* base_ptr, UINT32* listSize )
{
	BM_SPLockRequest_Header_Length_GET( base_ptr, *listSize );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SPLockRequest_List_GET_FIRST( UINT8* base_ptr, UINT32* out_diff, UINT32* out_cur_bitoff )
{
	UINT8* out_cur_ptr = base_ptr;
	BM_SPLockRequest_List_GET_FIRST( base_ptr, out_cur_ptr, *out_cur_bitoff );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SPLockRequest_List_GET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SPLockRequest_List_GET_TYPE( cur_ptr, cur_bitoff, *type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SPLockRequest_List_GET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_length, UINT32 err )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SPLockRequest_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, *out_length, err );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SPLockRequest_List_CURRENT_SPLockUnlockCodeReq_ActualLen_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* ActualLen )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SPLockRequest_List_CURRENT_SPLockUnlockCodeReq_ActualLen_GET( base_ptr, cur_ptr, cur_bitoff, *ActualLen );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SPLockRequest_List_CURRENT_SPLockUnlockCodeReq_BufferArr_value_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SPLockRequest_List_CURRENT_SPLockUnlockCodeReq_BufferArr_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SPLockRequest_List_GET_NEXT( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_diff, UINT32* out_cur_bitoff, UINT32 err )
{
	UINT8* out_cur_ptr = base_ptr;
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SPLockRequest_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, out_cur_ptr, *out_cur_bitoff, err );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SPLockRequest_List_SET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SPLockRequest_List_SET_TYPE( cur_ptr, cur_bitoff, type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SPLockRequest_List_SET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 lenOfLen, UINT32 length )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	lenOfLen = 2;
	BM_SPLockRequest_List_SET_LENGTH( cur_ptr, cur_bitoff, lenOfLen, length );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SPLockRequest_List_CURRENT_SPLockUnlockCodeReq_ActualLen_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 ActualLen )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SPLockRequest_List_CURRENT_SPLockUnlockCodeReq_ActualLen_SET( base_ptr, cur_ptr, cur_bitoff, ActualLen );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SPLockRequest_List_CURRENT_SPLockUnlockCodeReq_BufferArr_value_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SPLockRequest_List_CURRENT_SPLockUnlockCodeReq_BufferArr_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SPLockRequest_Header_Type_SET( UINT8* base_ptr, UINT32 opcode )
{
	BM_SPLockRequest_Header_Type_SET( base_ptr, opcode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SPLockRequest_Header_Version_SET( UINT8* base_ptr, UINT16 version )
{
	BM_SPLockRequest_Header_Version_SET( base_ptr, version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SPLockRequest_Header_Accessibility_SET( UINT8* base_ptr, UINT16 accessibility )
{
	BM_SPLockRequest_Header_Accessibility_SET( base_ptr, accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SPLockRequest_Header_Status_SET( UINT8* base_ptr, UINT16 status )
{
	BM_SPLockRequest_Header_Status_SET( base_ptr, status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SPLockRequest_Header_Length_SET( UINT8* base_ptr, UINT32 len )
{
	BM_SPLockRequest_Header_Length_SET( base_ptr, len );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_DebugLoopback_Header_Version_GET( UINT8* base_ptr, UINT16* version )
{
	BM_DebugLoopback_Header_Version_GET( base_ptr, *version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_DebugLoopback_Header_Accessibility_GET( UINT8* base_ptr, UINT16* accessibility )
{
	BM_DebugLoopback_Header_Accessibility_GET( base_ptr, *accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_DebugLoopback_Header_Status_GET( UINT8* base_ptr, UINT16* status )
{
	BM_DebugLoopback_Header_Status_GET( base_ptr, *status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_DebugLoopback_Header_Type_SET( UINT8* base_ptr, UINT32 opcode )
{
	BM_DebugLoopback_Header_Type_SET( base_ptr, opcode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_DebugLoopback_Header_Version_SET( UINT8* base_ptr, UINT16 version )
{
	BM_DebugLoopback_Header_Version_SET( base_ptr, version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_DebugLoopback_Header_Accessibility_SET( UINT8* base_ptr, UINT16 accessibility )
{
	BM_DebugLoopback_Header_Accessibility_SET( base_ptr, accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_DebugLoopback_Header_Status_SET( UINT8* base_ptr, UINT16 status )
{
	BM_DebugLoopback_Header_Status_SET( base_ptr, status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_DebugLoopback_Header_Length_SET( UINT8* base_ptr, UINT32 len )
{
	BM_DebugLoopback_Header_Length_SET( base_ptr, len );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportAltAccept_Header_Version_GET( UINT8* base_ptr, UINT16* version )
{
	BM_ReportAltAccept_Header_Version_GET( base_ptr, *version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportAltAccept_Header_Accessibility_GET( UINT8* base_ptr, UINT16* accessibility )
{
	BM_ReportAltAccept_Header_Accessibility_GET( base_ptr, *accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportAltAccept_Header_Status_GET( UINT8* base_ptr, UINT16* status )
{
	BM_ReportAltAccept_Header_Status_GET( base_ptr, *status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportAltAccept_Header_Type_SET( UINT8* base_ptr, UINT32 opcode )
{
	BM_ReportAltAccept_Header_Type_SET( base_ptr, opcode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportAltAccept_Header_Version_SET( UINT8* base_ptr, UINT16 version )
{
	BM_ReportAltAccept_Header_Version_SET( base_ptr, version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportAltAccept_Header_Accessibility_SET( UINT8* base_ptr, UINT16 accessibility )
{
	BM_ReportAltAccept_Header_Accessibility_SET( base_ptr, accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportAltAccept_Header_Status_SET( UINT8* base_ptr, UINT16 status )
{
	BM_ReportAltAccept_Header_Status_SET( base_ptr, status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ReportAltAccept_Header_Length_SET( UINT8* base_ptr, UINT32 len )
{
	BM_ReportAltAccept_Header_Length_SET( base_ptr, len );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ModeOfOperationCommand_Header_Version_GET( UINT8* base_ptr, UINT16* version )
{
	BM_ModeOfOperationCommand_Header_Version_GET( base_ptr, *version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ModeOfOperationCommand_Header_Accessibility_GET( UINT8* base_ptr, UINT16* accessibility )
{
	BM_ModeOfOperationCommand_Header_Accessibility_GET( base_ptr, *accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ModeOfOperationCommand_Header_Status_GET( UINT8* base_ptr, UINT16* status )
{
	BM_ModeOfOperationCommand_Header_Status_GET( base_ptr, *status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ModeOfOperationCommand_Header_Length_GET( UINT8* base_ptr, UINT32* listSize )
{
	BM_ModeOfOperationCommand_Header_Length_GET( base_ptr, *listSize );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ModeOfOperationCommand_List_GET_FIRST( UINT8* base_ptr, UINT32* out_diff, UINT32* out_cur_bitoff )
{
	UINT8* out_cur_ptr = base_ptr;
	BM_ModeOfOperationCommand_List_GET_FIRST( base_ptr, out_cur_ptr, *out_cur_bitoff );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ModeOfOperationCommand_List_GET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ModeOfOperationCommand_List_GET_TYPE( cur_ptr, cur_bitoff, *type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ModeOfOperationCommand_List_GET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_length, UINT32 err )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ModeOfOperationCommand_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, *out_length, err );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ModeOfOperationCommand_List_CURRENT_ModeOfOperation_value_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ModeOfOperationCommand_List_CURRENT_ModeOfOperation_value_GET( base_ptr, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ModeOfOperationCommand_List_GET_NEXT( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_diff, UINT32* out_cur_bitoff, UINT32 err )
{
	UINT8* out_cur_ptr = base_ptr;
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ModeOfOperationCommand_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, out_cur_ptr, *out_cur_bitoff, err );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ModeOfOperationCommand_List_SET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ModeOfOperationCommand_List_SET_TYPE( cur_ptr, cur_bitoff, type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ModeOfOperationCommand_List_SET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 lenOfLen, UINT32 length )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	lenOfLen = 2;
	BM_ModeOfOperationCommand_List_SET_LENGTH( cur_ptr, cur_bitoff, lenOfLen, length );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ModeOfOperationCommand_List_CURRENT_ModeOfOperation_value_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_ModeOfOperationCommand_List_CURRENT_ModeOfOperation_value_SET( base_ptr, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ModeOfOperationCommand_Header_Type_SET( UINT8* base_ptr, UINT32 opcode )
{
	BM_ModeOfOperationCommand_Header_Type_SET( base_ptr, opcode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ModeOfOperationCommand_Header_Version_SET( UINT8* base_ptr, UINT16 version )
{
	BM_ModeOfOperationCommand_Header_Version_SET( base_ptr, version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ModeOfOperationCommand_Header_Accessibility_SET( UINT8* base_ptr, UINT16 accessibility )
{
	BM_ModeOfOperationCommand_Header_Accessibility_SET( base_ptr, accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ModeOfOperationCommand_Header_Status_SET( UINT8* base_ptr, UINT16 status )
{
	BM_ModeOfOperationCommand_Header_Status_SET( base_ptr, status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_ModeOfOperationCommand_Header_Length_SET( UINT8* base_ptr, UINT32 len )
{
	BM_ModeOfOperationCommand_Header_Length_SET( base_ptr, len );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MOC_Request_Header_Version_GET( UINT8* base_ptr, UINT16* version )
{
	BM_MOC_Request_Header_Version_GET( base_ptr, *version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MOC_Request_Header_Accessibility_GET( UINT8* base_ptr, UINT16* accessibility )
{
	BM_MOC_Request_Header_Accessibility_GET( base_ptr, *accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MOC_Request_Header_Status_GET( UINT8* base_ptr, UINT16* status )
{
	BM_MOC_Request_Header_Status_GET( base_ptr, *status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MOC_Request_Header_Type_SET( UINT8* base_ptr, UINT32 opcode )
{
	BM_MOC_Request_Header_Type_SET( base_ptr, opcode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MOC_Request_Header_Version_SET( UINT8* base_ptr, UINT16 version )
{
	BM_MOC_Request_Header_Version_SET( base_ptr, version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MOC_Request_Header_Accessibility_SET( UINT8* base_ptr, UINT16 accessibility )
{
	BM_MOC_Request_Header_Accessibility_SET( base_ptr, accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MOC_Request_Header_Status_SET( UINT8* base_ptr, UINT16 status )
{
	BM_MOC_Request_Header_Status_SET( base_ptr, status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_MOC_Request_Header_Length_SET( UINT8* base_ptr, UINT32 len )
{
	BM_MOC_Request_Header_Length_SET( base_ptr, len );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SendEapResponse_Header_Version_GET( UINT8* base_ptr, UINT16* version )
{
	BM_SendEapResponse_Header_Version_GET( base_ptr, *version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SendEapResponse_Header_Accessibility_GET( UINT8* base_ptr, UINT16* accessibility )
{
	BM_SendEapResponse_Header_Accessibility_GET( base_ptr, *accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SendEapResponse_Header_Status_GET( UINT8* base_ptr, UINT16* status )
{
	BM_SendEapResponse_Header_Status_GET( base_ptr, *status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SendEapResponse_Header_Length_GET( UINT8* base_ptr, UINT32* listSize )
{
	BM_SendEapResponse_Header_Length_GET( base_ptr, *listSize );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SendEapResponse_List_GET_FIRST( UINT8* base_ptr, UINT32* out_diff, UINT32* out_cur_bitoff )
{
	UINT8* out_cur_ptr = base_ptr;
	BM_SendEapResponse_List_GET_FIRST( base_ptr, out_cur_ptr, *out_cur_bitoff );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SendEapResponse_List_GET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SendEapResponse_List_GET_TYPE( cur_ptr, cur_bitoff, *type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SendEapResponse_List_GET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_length, UINT32 err )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SendEapResponse_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, *out_length, err );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SendEapResponse_List_CURRENT_EapResponseMessage_ActualLen_GET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16* ActualLen )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SendEapResponse_List_CURRENT_EapResponseMessage_ActualLen_GET( base_ptr, cur_ptr, cur_bitoff, *ActualLen );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SendEapResponse_List_CURRENT_EapResponseMessage_BufferArr_value_GET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8* value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SendEapResponse_List_CURRENT_EapResponseMessage_BufferArr_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, *value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SendEapResponse_List_GET_NEXT( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32* out_diff, UINT32* out_cur_bitoff, UINT32 err )
{
	UINT8* out_cur_ptr = base_ptr;
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SendEapResponse_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, out_cur_ptr, *out_cur_bitoff, err );
	*out_diff = (UINT)(out_cur_ptr - base_ptr);
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SendEapResponse_List_SET_TYPE( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 type )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SendEapResponse_List_SET_TYPE( cur_ptr, cur_bitoff, type );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SendEapResponse_List_SET_LENGTH( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT32 lenOfLen, UINT32 length )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	lenOfLen = 2;
	BM_SendEapResponse_List_SET_LENGTH( cur_ptr, cur_bitoff, lenOfLen, length );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SendEapResponse_List_CURRENT_EapResponseMessage_ActualLen_SET( UINT8* base_ptr, UINT32 diff, UINT32 cur_bitoff, UINT16 ActualLen )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SendEapResponse_List_CURRENT_EapResponseMessage_ActualLen_SET( base_ptr, cur_ptr, cur_bitoff, ActualLen );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SendEapResponse_List_CURRENT_EapResponseMessage_BufferArr_value_SET( UINT8* base_ptr, UINT32 i0, UINT32 diff, UINT32 cur_bitoff, UINT8 value )
{
   UINT8* cur_ptr = NULL;
   if(base_ptr != NULL)
   {
       cur_ptr = (UINT8*)(base_ptr + diff);
   }
	BM_SendEapResponse_List_CURRENT_EapResponseMessage_BufferArr_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, value );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SendEapResponse_Header_Type_SET( UINT8* base_ptr, UINT32 opcode )
{
	BM_SendEapResponse_Header_Type_SET( base_ptr, opcode );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SendEapResponse_Header_Version_SET( UINT8* base_ptr, UINT16 version )
{
	BM_SendEapResponse_Header_Version_SET( base_ptr, version );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SendEapResponse_Header_Accessibility_SET( UINT8* base_ptr, UINT16 accessibility )
{
	BM_SendEapResponse_Header_Accessibility_SET( base_ptr, accessibility );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SendEapResponse_Header_Status_SET( UINT8* base_ptr, UINT16 status )
{
	BM_SendEapResponse_Header_Status_SET( base_ptr, status );
}
L4BUFMANDLL_API void L4BUFMANDLL_BM_SendEapResponse_Header_Length_SET( UINT8* base_ptr, UINT32 len )
{
	BM_SendEapResponse_Header_Length_SET( base_ptr, len );
}
