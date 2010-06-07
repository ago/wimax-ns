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
#include "NDnS_TinyFSM.h"

BOOL FSM_Init(pTinyFSM_t fsm)
{
	OSAL_init_critical_section( &(fsm->csLock) );
	if (0 != OSAL_create_event(&fsm->hWaitingStateEvent, TRUE, FALSE, NULL))// Auto reset
	{
		OSAL_delete_critical_section(&fsm->csLock);
		return FALSE;
	}
	fsm->state = 0;
	fsm->previousState = 0;
	memset(fsm->waitingStates, -1, MAX_STATES_COUNT * sizeof(long));
	//fsm->waitingState = -1;
	fsm->isInitialized = TRUE;

	return TRUE;
}

void FSM_Finalize(pTinyFSM_t fsm)
{
	fsm->isInitialized = FALSE;
	if (fsm->hWaitingStateEvent != NULL)
	{
		OSAL_delete_event(fsm->hWaitingStateEvent);
		fsm->hWaitingStateEvent = NULL;
	}
	if (&fsm->csLock != NULL /*&& &fsm->csLock.DebugInfo != 0x00000000 */)		// @@@ : JSS : Remove unwanted field reference inside of critical section
		OSAL_delete_critical_section(&fsm->csLock);
}

// [Oran] This is a patch for fast reconnect.
// It should be removed once the Act no longer restarts the ND&S during device error
BOOL FSM_InitNoReset(pTinyFSM_t fsm)
{
	OSAL_init_critical_section(&fsm->csLock);
	if (0 != OSAL_create_event(&fsm->hWaitingStateEvent, TRUE, FALSE, NULL)) // Auto reset
	{
		if (&fsm->csLock != NULL /* && &fsm->csLock.DebugInfo != 0x00000000 */)    	// @@@ : JSS : Remove unwanted field reference inside of critical section
			OSAL_delete_critical_section(&fsm->csLock);
		return FALSE;
	}	
	memset(fsm->waitingStates, -1, MAX_STATES_COUNT * sizeof(long));
	fsm->isInitialized = TRUE;

	return TRUE;
}

// get the current state
int FSM_GetState(pTinyFSM_t fsm)
{
	int state;

	OSAL_enter_critical_section(&fsm->csLock);
	state = fsm->state;
	OSAL_exit_critical_section(&fsm->csLock);

	return state;
}

// get the previous state
int FSM_GetPreviousState(pTinyFSM_t fsm)
{
	int state;

	OSAL_enter_critical_section(&fsm->csLock);
	state = fsm->previousState;
	OSAL_exit_critical_section(&fsm->csLock);

	return state;
}

// move to a new state
void FSM_SetState(pTinyFSM_t fsm, int state)
{
	int i;
	long lState = (long)state;
	long checkedState;

	OSAL_enter_critical_section(&fsm->csLock);
	fsm->previousState = fsm->state;
	fsm->state = state;
	for (i = 0; i < MAX_STATES_COUNT; ++i)
	{
		checkedState = OSAL_atomic_compareExchange(&fsm->waitingStates[i], lState, lState);
		if (checkedState < 0)
		{
			break;
		}

		if (checkedState == lState)
		{
			OSAL_set_event(fsm->hWaitingStateEvent);
			break;
		}
	}

	OSAL_exit_critical_section(&fsm->csLock);
}

// move to a new state ONLY if the current state is equal to the source state parameter
BOOL FSM_SetStateIfEqual(pTinyFSM_t fsm, int sourcState, int targetState)
{
	long lState = (long)targetState;
	long checkedState;
	BOOL result = FALSE;
	int i;

	OSAL_enter_critical_section(&fsm->csLock);
	if (fsm->state == sourcState)
	{
		fsm->previousState = fsm->state;
		fsm->state = targetState;
		for (i = 0; i < MAX_STATES_COUNT; ++i)
		{
			checkedState = OSAL_atomic_compareExchange(&fsm->waitingStates[i], lState, lState);
			if (checkedState < 0)
			{
				break;
			}

			if (checkedState == lState)
			{
				OSAL_set_event(fsm->hWaitingStateEvent);
				break;
			}
		}
		result = TRUE;
	}
	OSAL_exit_critical_section(&fsm->csLock);

	return result;
}

// move to a new state ONLY if the current state is NOT equal to the source state parameter
BOOL FSM_SetStateIfNotEqual(pTinyFSM_t fsm, int sourcState, int targetState)
{
	long lState = (long)targetState;
	long checkedState;
	BOOL result = FALSE;
	int i;

	OSAL_enter_critical_section(&fsm->csLock);
	if (fsm->state != sourcState)
	{
		fsm->previousState = fsm->state;
		fsm->state = targetState;
		for (i = 0; i < MAX_STATES_COUNT; ++i)
		{
			checkedState = OSAL_atomic_compareExchange(&fsm->waitingStates[i], lState, lState);
			if (checkedState < 0)
			{
				break;
			}

			if (checkedState == lState)
			{
				OSAL_set_event(fsm->hWaitingStateEvent);
				break;
			}
		}
		result = TRUE;
	}
	OSAL_exit_critical_section(&fsm->csLock);

	return result;
}

// wait until a certain state is reached
BOOL FSM_WaitForState(pTinyFSM_t fsm, int state, UINT32 timeout)
{	
	// we allow only one wait at a time
	if (OSAL_atomic_compareExchange(&fsm->waitingStates[0], (long)state, -1) < 0)
	{
		BOOL ret = TRUE;				

		OSAL_enter_critical_section(&fsm->csLock);
		OSAL_reset_event(fsm->hWaitingStateEvent);
		if (fsm->state == state)
		{
			OSAL_exit_critical_section(&fsm->csLock);
		}
		else
		{
			OSAL_exit_critical_section(&fsm->csLock);
			if (OSAL_wait_event(fsm->hWaitingStateEvent, timeout) != WAIT_OBJECT_0)
			{
				ret = FALSE;
			}
		}
		OSAL_atomic_exchange(&fsm->waitingStates[0], -1);

		return ret;
	}
	return FALSE;
}

// wait until one of the specified states is reached
BOOL FSM_WaitForMultipleStates(pTinyFSM_t fsm, int* states, int statesCount, UINT32 timeout)
{	
	int i;
	BOOL error = FALSE;
	BOOL found = FALSE;

	if (statesCount < 1 || statesCount > MAX_STATES_COUNT || states == NULL)
	{
		return FALSE;
	}

	for (i = 0; i < statesCount; ++i)
	{
		if (OSAL_atomic_compareExchange(&fsm->waitingStates[i], (long)(states[i]), -1) >= 0)
		{
			error = TRUE;
			break;
		}
	}

	// we allow only one wait at a time
	if (!error)
	{
		BOOL ret = TRUE;				

		OSAL_enter_critical_section(&fsm->csLock);
		OSAL_reset_event(fsm->hWaitingStateEvent);
		
		for (i = 0; i < statesCount; ++i)
		{
			if (fsm->state == states[i])
			{
				found = TRUE;
				OSAL_exit_critical_section(&fsm->csLock);
			}
		}

		if (!found)
		{
			OSAL_exit_critical_section(&fsm->csLock);
			if (OSAL_wait_event(fsm->hWaitingStateEvent, timeout) != WAIT_OBJECT_0)
			{
				ret = FALSE;
			}
		}
		
		for (i = statesCount - 1; i >= 0; --i)
		{
			OSAL_atomic_exchange(&fsm->waitingStates[i], -1);			
		}

		return ret;
	}
	return FALSE;
}
