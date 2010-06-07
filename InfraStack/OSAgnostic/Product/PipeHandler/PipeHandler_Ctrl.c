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
#include "PipeHandler_Ctrl.h"
#include "PipeHandlerInternal.h"

#include "CommonServices.h"
#include "PipeServices_Ctrl.h"
#include "Services_Ctrl.h"
#include "Messenger.h"
#include "TraceModule.h"
#include "L4ConfigurationManager.h"

//OSAL
#include "wimax_osal_primitives.h"
#include "wimax_osal_event_logger.h"

extern OSAL_critical_section lockInitCount;	
static int pipehandler_numOfInits = 0;
static BOOL isInitialized = FALSE;

EXTERN_C EXPORT void PIPE_HANDLER_Finalize()
{
	TRACE(TR_MOD_ALL, TR_SEV_ALL, "PIPE_HANDLER_Finalize(IN). pipehandler_numOfInits=%d", pipehandler_numOfInits);

	OSAL_enter_critical_section(&lockInitCount);

	if (pipehandler_numOfInits > 0) // protect agains redundant PIPE_HANDLER_Finalize() calls
	{
		if (LAST_INIT == --pipehandler_numOfInits) // finalize gate keeper
		{
			PIPE_HANDLER_FiniConnectivity();
			PipeServices_Fini();
			Services_Fini();
			isInitialized = FALSE;
		}
	}

	OSAL_exit_critical_section(&lockInitCount);	
	
	TRACE(TR_MOD_ALL, TR_SEV_ALL, "PIPE_HANDLER_Finalize(OUT)");
}

EXTERN_C EXPORT BOOL PIPE_HANDLER_Init()
{
	BOOL isSuccess = TRUE;

	TRACE(TR_MOD_ALL, TR_SEV_ALL, "PIPE_HANDLER_Init(IN). pipehandler_numOfInits=%d",pipehandler_numOfInits);
	OSAL_enter_critical_section(&lockInitCount);
	if (FIRST_INIT == ++pipehandler_numOfInits) // init gate keeper
	{		
		if ((!Services_Init()) || (!PipeServices_Init()) || (PIPE_HANDLER_InitConnectivity() != L5_RESULT_OK))
		{
			isSuccess = FALSE;
			PIPE_HANDLER_Finalize();
		}
		else
		{
			isInitialized = TRUE;
		}
	}	
	OSAL_exit_critical_section(&lockInitCount);

	TRACE(TR_MOD_ALL, TR_SEV_ALL, "PIPE_HANDLER_Init(OUT)");
	
	return isSuccess;
}

BOOL PIPE_HANDLER_IsInitialized()
{
	BOOL tempIsInitialized;

	OSAL_enter_critical_section(&lockInitCount);
	tempIsInitialized = isInitialized;
	OSAL_exit_critical_section(&lockInitCount);

	return tempIsInitialized;
}
