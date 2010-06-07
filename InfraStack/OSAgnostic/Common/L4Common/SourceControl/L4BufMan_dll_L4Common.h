
#ifndef _L4BUFMAN_DLL_L4COMMON_H
#define _L4BUFMAN_DLL_L4COMMON_H


#include "L4BufMan_L4Common.h"


#ifdef L4BUFMANDLL_EXPORTS
	#define L4BUFMANDLL_API __declspec(dllexport)
#else
	#define L4BUFMANDLL_API __declspec(dllimport)
#endif


L4BUFMANDLL_API void L4BUFMANDLL_BM_Header_Version_GET( UINT8* base_ptr, UINT16 version );
L4BUFMANDLL_API void L4BUFMANDLL_BM_Header_Accessibility_GET( UINT8* base_ptr, UINT16 accessibility );
L4BUFMANDLL_API void L4BUFMANDLL_BM_Header_Status_GET( UINT8* base_ptr, UINT16 status );

L4BUFMANDLL_API void L4BUFMANDLL_BM_Header_Version_SET( UINT8* base_ptr, UINT16 version );
L4BUFMANDLL_API void L4BUFMANDLL_BM_Header_Accessibility_SET( UINT8* base_ptr, UINT16 accessibility );
L4BUFMANDLL_API void L4BUFMANDLL_BM_Header_Status_SET( UINT8* base_ptr, UINT16 status );




#endif //_L4BUFMAN_DLL_L4COMMON_H
