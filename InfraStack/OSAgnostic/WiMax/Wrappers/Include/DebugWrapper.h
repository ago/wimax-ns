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
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the DEBUGWRAPPER_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// DEBUGWRAPPER_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
/*#ifdef DEBUGWRAPPER_EXPORTS
#define DEBUGWRAPPER_API __declspec(dllexport)
#else
#define DEBUGWRAPPER_API __declspec(dllimport)
#endif*/
#ifndef _DEBUG_WRAPPER_H_
#define _DEBUG_WRAPPER_H_


#ifdef ORANGE_WRAPPER_EXPORTS
#define DEBUGWRAPPER_API __declspec(dllexport)
#else
#define DEBUGWRAPPER_API __declspec(dllimport)
#endif



#include "DebugWrapperCommon.h"

wmx_Status_t DEBUGWRAPPER_API WMX_EXT_CALL_CONV wmxOrngDebug_Init(const char * TUIsFileName);
void DEBUGWRAPPER_API WMX_EXT_CALL_CONV wmxOrngDebug_Finalize();

wmx_Status_t DEBUGWRAPPER_API WMX_EXT_CALL_CONV wmx_OpenDilloStream(MetricStreamsCallback pCallBackFunc);
wmx_Status_t DEBUGWRAPPER_API WMX_EXT_CALL_CONV wmx_CloseDilloStream();

wmx_Status_t DEBUGWRAPPER_API WMX_EXT_CALL_CONV wmx_OpenMonitorStream(MetricStreamsCallback pCallBackFunc);
wmx_Status_t DEBUGWRAPPER_API WMX_EXT_CALL_CONV wmx_CloseMonitorStream();

wmx_Status_t DEBUGWRAPPER_API WMX_EXT_CALL_CONV wmx_MonitorFilter(unsigned int type, unsigned int rate);

/*
wmx_Status_t DEBUGWRAPPER_API WMX_EXT_CALL_CONV wmx_Connect();
wmx_Status_t DEBUGWRAPPER_API WMX_EXT_CALL_CONV wmx_ExternalSync(int externalSync);
wmx_Status_t DEBUGWRAPPER_API WMX_EXT_CALL_CONV wmx_Control(UINT val);
*/

wmx_Status_t DEBUGWRAPPER_API WMX_EXT_CALL_CONV wmx_Peek8(UINT32 address, UINT8* outVal);
wmx_Status_t DEBUGWRAPPER_API WMX_EXT_CALL_CONV wmx_Peek16(UINT32 address, UINT16* outVal);
wmx_Status_t DEBUGWRAPPER_API WMX_EXT_CALL_CONV wmx_Peek32(UINT32 address, UINT32* outVal);
wmx_Status_t DEBUGWRAPPER_API WMX_EXT_CALL_CONV wmx_PeekBuffer(UINT32 address, UINT32 length, UINT8* outVal);

wmx_Status_t DEBUGWRAPPER_API WMX_EXT_CALL_CONV wmx_Poke8(UINT32 address, UINT8 value);
wmx_Status_t DEBUGWRAPPER_API WMX_EXT_CALL_CONV wmx_Poke16(UINT32 address, UINT16 value);
wmx_Status_t DEBUGWRAPPER_API WMX_EXT_CALL_CONV wmx_Poke32(UINT32 address, UINT32 value);
wmx_Status_t DEBUGWRAPPER_API WMX_EXT_CALL_CONV wmx_PokeBuffer(UINT32 address, UINT32 length, const UINT8* buf);

#endif // _DEBUG_WRAPPER_H_
