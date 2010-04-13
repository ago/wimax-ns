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
#include "wimax_osal_primitives.h"
#include "L4ConfigurationManager.h"

#include "Act.h"


static OSAL_dynlib_t p_inst_lib = NULL;

extern agent_Initialize pfn_DnDAgent_Initialize;
extern agent_Finalize pfn_DnDAgent_Finalize;
extern agent_Start pfn_DnDAgent_Start;
extern agent_Stop pfn_DnDAgent_Stop;
extern agent_EventHandler pfn_DnDAgent_EventHandler;

extern agent_Initialize pfn_MOCMsgProxy_Initialize;
extern agent_Finalize pfn_MOCMsgProxy_Finalize;
extern agent_Start pfn_MOCMsgProxy_Start;
extern agent_Stop pfn_MOCMsgProxy_Stop;
extern agent_EventHandler pfn_MOCMsgProxy_EventHandler;

APPSRV_INIT_ST LoadInstrumentationModule()
{
	char inst_lib_full_path[MAX_PATH];
	BOOL bTmpRet;

	bTmpRet = L4Configurations_getInstrumentationLibName(inst_lib_full_path);

	if ( !bTmpRet || inst_lib_full_path[0] == '\0' )
		return INIT_CONFIG_FAIL;

	if ( (p_inst_lib = OSAL_load_lib(inst_lib_full_path)) == NULL ) 
		return INIT_CONFIG_FAIL;

	if ( ( (pfn_DnDAgent_Initialize = (agent_Initialize)OSAL_find_symbol(p_inst_lib, "DnDAgent_Initialize")) == NULL) 
		|| ( (pfn_DnDAgent_Finalize = (agent_Finalize)OSAL_find_symbol(p_inst_lib, "DnDAgent_Finalize")) == NULL) 
		|| ( (pfn_DnDAgent_Start = (agent_Start)OSAL_find_symbol(p_inst_lib, "DnDAgent_Start")) == NULL) 
		||  ( (pfn_DnDAgent_Stop = (agent_Stop)OSAL_find_symbol(p_inst_lib, "DnDAgent_Stop")) == NULL) 
		||  ( (pfn_DnDAgent_EventHandler = (agent_EventHandler)OSAL_find_symbol(p_inst_lib, "DnDAgent_EventHandler")) == NULL) 
		|| ( (pfn_MOCMsgProxy_Initialize = (agent_Initialize)OSAL_find_symbol(p_inst_lib, "MocMsgProxy_Initialize")) == NULL) 
		|| ( (pfn_MOCMsgProxy_Finalize = (agent_Finalize)OSAL_find_symbol(p_inst_lib, "MocMsgProxy_Finalize")) == NULL) 
		|| ( (pfn_MOCMsgProxy_Start = (agent_Start)OSAL_find_symbol(p_inst_lib, "MocMsgProxy_Start")) == NULL) 
		||  ( (pfn_MOCMsgProxy_Stop = (agent_Stop)OSAL_find_symbol(p_inst_lib, "MocMsgProxy_Stop")) == NULL) 
		||  ( (pfn_MOCMsgProxy_EventHandler = (agent_EventHandler)OSAL_find_symbol(p_inst_lib, "MocMsgProxy_EventHandler")) == NULL) )
	{		
		TRACE(TR_MOD_ACT, TR_SEV_ALERT, "Loading instrumentation module has failed");
		return INIT_CONFIG_FAIL;
	}
	
	return INIT_SUCCESS;
}


void UnloadInstrumentationModule()
{

	if ( p_inst_lib != NULL )		
	{
		OSAL_close_lib(p_inst_lib);
		p_inst_lib = NULL;
	}
	
	pfn_DnDAgent_Initialize = NULL;
	pfn_DnDAgent_Finalize = NULL;
	pfn_DnDAgent_Start = NULL;
	pfn_DnDAgent_Stop = NULL;
	pfn_DnDAgent_EventHandler = NULL;
	pfn_MOCMsgProxy_Initialize = NULL;
	pfn_MOCMsgProxy_Finalize = NULL;
	pfn_MOCMsgProxy_Start = NULL;
	pfn_MOCMsgProxy_Stop = NULL;
	pfn_MOCMsgProxy_EventHandler = NULL;
}


