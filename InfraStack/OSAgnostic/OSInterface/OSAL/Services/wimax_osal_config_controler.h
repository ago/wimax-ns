/**************************************************************************
Copyright (c) 2007-2009, Intel Corporation. All rights reserved.

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
#ifndef _REGISTRY_CONTROLLER_H_
#define _REGISTRY_CONTROLLER_H_

#ifndef _lint //disables lint warnings from this file

#include "wimax_osal_basictypes.h"
#include "wimax_osal_config_controler_defines.h"

/*-----------------------------------------------------------------------------

Library: RegistryController
Module:  registry_controller.h

manage all access to the registry


Usage: 
string data;
if (Registry_Controller_GetValue( HKEY_LOCAL_MACHINE, 
"Software\\Armadillo\\SimEngineMngr\\", 
"LogPath", 
data ) )
{
do something with data ...
}



Date              By               Description
------------------------------------------------------------------------------

17.05.2005        Anat Ganor       Created. 
14.08.2006        Avishai Eshet    Adapted to TraceAgent. 

----------------------------------------------------------------------------*/
 
#define MAX_REGISTRY_ANSWER 1024
#define NUM_OF_LED_BLINK_RATE 14
#define NUM_OF_LED_BEHAVIOR 14
#define PRIVILEGE_KEY_SIZE 8
#define MAX_SIZE_OF_NSP_NAME       (128+1)
#define MAX_SIZE_OF_REALM_NAME       1024
#define MAX_SIZE_OF_REALM_REGKEY_PREFIX MAX_SIZE_OF_REALM_NAME*2
#define MAX_FILENAME_LEN			256
#define IP_STR_SIZE					32
#define DEFULT_STR_SIZE             8
#define DEV_ID_PREFIX_SIZE			10
#define DEFAULT_EMPTY_STR				""
#define APDO_SECRET "UgyaIdgh9b8n7ao0sh!?"
#define DEFAULT_TRUE_STR				"True"
#define SYSTEM_FILE_NOT_FOUND		2


#define MAX_ANSWER_SIZE		512

////////////////////////////////////////////////////////////////////////////////////////////////////
//  Purpose: returns the value of an entry in the registry of type REG_DWORD
//
//  Remarks: if the function fails the value is unchanged
//
//  Parameters:                  
//  --------------------------------------------------------------------------------------------
//			name		|		type and Purpose		|-> <-|			Deleted by
//  --------------------------------------------------------------------------------------------
//  hMainKey			 the main key					 [in]			N/A
//						 for example, HKEY_LOCAL_MACHINE
//
//  name_of_subkey		 the name of the sub key		 [in]			N/A
//						 for example "Software\\Armadillo\\svc\\"
//
//  name_of_value		 the name of the entry from		 [in]			N/A
//						 which you want to retrieve the information
//
//	value				 the returned value read from	 [in-out]		N/A
//						 the registry
//
//
//  Return value: false - if name_of_subkey is null or not found 
//						- if name_of_value is null or not found 
//				  true  - success
//
////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL OSAL_ConfigController_GetNumValue(const char* name_of_subkey, const char* name_of_value, UINT32* value);

////////////////////////////////////////////////////////////////////////////////////////////////////
//  Purpose: returns the value of an entry in the registry of type REG_SZ
//
//  Remarks: if the function fails the value is unchanged
//
//  Parameters:                  
//  --------------------------------------------------------------------------------------------
//			name		|		type and Purpose		|-> <-|			Deleted by
//  --------------------------------------------------------------------------------------------
//  hMainKey			 the main key					 [in]			N/A
//						 for example, HKEY_LOCAL_MACHINE
//
//  name_of_subkey		 the name of the sub key		 [in]			N/A
//						 for example "Software\\Armadillo\\svc\\"
//
//  name_of_value		 the name of the entry from		 [in]			N/A
//						 which you want to retrieve the information
//
//	value				 the returned value read from	 [in-out]		N/A
//						 the registry
//
//
//  Return value: false - if name_of_subkey is null or not found 
//						- if name_of_value is null or not found 
//				  true  - success
//s
////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL OSAL_ConfigController_GetStrValue(const char* name_of_subkey, const char* name_of_value, char* value, UINT32 maxSize);
BOOL OSAL_ConfigController_SetStrValue(const char* name_of_subkey, LPSTR name_of_value, char* value);
BOOL OSAL_ConfigController_SetNumValue(const char* name_of_subkey, const char* name_of_value, UINT32 *value);	
BOOL OSAL_ConfigController_GetMultValues(const char* name_of_subkey, OSAL_VALENT *valent,UINT32 num_vals, char* buffer, UINT32 size);

#endif
#endif
