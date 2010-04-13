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
#ifndef _NDNS_TINY_FSM_H
#define _NDNS_TINY_FSM_H

#include "wimax_osal_primitives.h"

#define MAX_STATES_COUNT	20
///////////////////////////////////
// types declarations
#pragma pack( push, 1 )
typedef struct _TinyFSM_t
{
	OSAL_critical_section csLock;
	OSAL_event_t hWaitingStateEvent;

	BOOL isInitialized;
	int state;	
	int previousState;
	long waitingStates[MAX_STATES_COUNT];	
} TinyFSM_t, *pTinyFSM_t;
#pragma pack( pop )

//////////////////////////////////
// funcations declarations

BOOL FSM_Init(pTinyFSM_t fsm);
void FSM_Finalize(pTinyFSM_t fsm);

// [Oran] This is a patch for fast reconnect.
// It should be removed once the Act no longer restarts the ND&S during device error
BOOL FSM_InitNoReset(pTinyFSM_t fsm);

// get the current state
int FSM_GetState(pTinyFSM_t fsm);
// get the previous state
int FSM_GetPreviousState(pTinyFSM_t fsm);
// move to a new state
void FSM_SetState(pTinyFSM_t fsm, int state);
// move to a new state ONLY if the current state is equal to the source state parameter
BOOL FSM_SetStateIfEqual(pTinyFSM_t fsm, int sourcState, int targetState);
// move to a new state ONLY if the current state is NOT equal to the source state parameter
BOOL FSM_SetStateIfNotEqual(pTinyFSM_t fsm, int sourcState, int targetState);
// wait until a certain state is reached
BOOL FSM_WaitForState(pTinyFSM_t fsm, int state, UINT32 timeout);
// wait until one of the specified states is reached
BOOL FSM_WaitForMultipleStates(pTinyFSM_t fsm, int* states, int statesCount, UINT32 timeout);

#endif // _NDNS_TINY_FSM_H