
#include "L4BufMan_dll_L4Common.h"
#include "L4Common.h"



L4BUFMANDLL_API void L4BUFMANDLL_BM_Header_Version_GET( UINT8* base_ptr, UINT16 version )
{
	BM_L3L4CompleteHeader_Version_GET( base_ptr, version );
}

L4BUFMANDLL_API void L4BUFMANDLL_BM_Header_Accessibility_GET( UINT8* base_ptr, UINT16 accessibility )
{
	BM_L3L4CompleteHeader_Accessibility_GET( base_ptr, accessibility );
}

L4BUFMANDLL_API void L4BUFMANDLL_BM_Header_Status_GET( UINT8* base_ptr, UINT16 status )
{
	BM_L3L4CompleteHeader_Status_GET( base_ptr, status );
}

L4BUFMANDLL_API void L4BUFMANDLL_BM_Header_Version_SET( UINT8* base_ptr, UINT16 version )
{
	BM_L3L4CompleteHeader_Version_SET( base_ptr, version );
}

L4BUFMANDLL_API void L4BUFMANDLL_BM_Header_Accessibility_SET( UINT8* base_ptr, UINT16 accessibility )
{
	BM_L3L4CompleteHeader_Accessibility_SET( base_ptr, accessibility );
}

L4BUFMANDLL_API void L4BUFMANDLL_BM_Header_Status_SET( UINT8* base_ptr, UINT16 status )
{
	BM_L3L4CompleteHeader_Status_SET( base_ptr, status );
}

