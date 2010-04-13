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

THIS SOARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
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
#ifndef _WIMAX_CU_H
#define _WIMAX_CU_H

#include <pthread.h>
#include <unistd.h>
#include <limits.h>
#include <sys/time.h>
#include <semaphore.h>
#include <sys/types.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

#include "WiMaxAPI.h"
#include "WiMaxAPIEx.h"
#include "WiMaxTypesEx.h"
#include "CoexAPI.h"
#include "wimaxcu_defs.h"
#include "wimaxcu_util.h"
#define _XOPEN_SOURCE 600
#define MAX_LEN 80
#define WMX_SF_STATUS_MAX_NUM 100
#define VERSION_SDK_STR_MAX_SIZE 255
#define MAX_CONNECT_MODE_SIZE 10

#define MAX_PROFILE			32
#define MAX_DEVICE			32
#define MAX_LEN				80
#define WMX_SF_STATUS_MAX_NUM		100
#define VERSION_SDK_STR_MAX_SIZE	255
#define MAX_NSP_ID_LEN                  40

// used in Scan process
// Waits SCAN_TIMEOUT_IN_10SEC_ITREATIONS * 10 sec before time out
// Default value is SCAN_TIMEOUT_IN_10SEC_ITREATIONS 30 = 300 sec = 5 min
// can be modified depending upon the no of frequencies available
#define SCAN_TIMEOUT_IN_10SEC_ITREATIONS 60
	
extern sem_t g_semConnectionUtility;
extern sem_t g_semAPDOactivation;
extern sem_t g_semAPDOupdates;
extern sem_t g_semRfState;
extern sem_t g_semConnectCompleted;
extern pthread_mutex_t g_console_owner_mutex;

extern UINT32 g_preferred_NSP_ID;
extern WIMAX_API_DEVICE_STATUS g_devState;


extern char g_sznspName[MAX_SIZE_OF_NSP_NAME];
extern char g_foOperationType[NAME_MAX];

extern int g_noNetworksFound;
extern int g_searchProgress;


int wmxcu_sem_timeout(sem_t* s,int milliseconds);
void *user_info(void *ptr);
int validate_cmd(int argc, char* argv[], parsed_cmd* validated_cmd);
int cmd_handler(WIMAX_API_DEVICE_ID_P p_device_id, parsed_cmd *valid_cmd);
WIMAX_API_RET wimaxcu_initialize(WIMAX_API_DEVICE_ID_P p_device_id);
void wimaxcu_finalize(WIMAX_API_DEVICE_ID_P p_device_id);
int wimaxcu_get_user_connect_mode(WIMAX_API_DEVICE_ID_P p_device_id);
int wimaxcu_set_user_connect_mode(WIMAX_API_DEVICE_ID_P p_device_id,char *connect_mode, char *scan_mode);
int wimaxcu_get_connect_status(WIMAX_API_DEVICE_ID_P p_device_id);
int wimaxcu_get_system_status(WIMAX_API_DEVICE_ID_P p_device_id);
void wimaxcu_get_info(WIMAX_API_DEVICE_ID_P p_device_id,const char * info_type);
int wimaxcu_get_rf_status(WIMAX_API_DEVICE_ID_P p_device_id);
int wimaxcu_get_network_list(WIMAX_API_DEVICE_ID_P p_device_id, CMD_ARGS scan_mode);
int wimaxcu_get_network_list_ex(WIMAX_API_DEVICE_ID_P p_device_id, CMD_ARGS scan_mode);
void wimaxcu_get_api_ex_version(WIMAX_API_DEVICE_ID_P p_device_id);
void wimaxcu_get_ip_interface(WIMAX_API_DEVICE_ID_P p_device_id);
void wimaxcu_set_fast_reconnect(WIMAX_API_DEVICE_ID_P p_device_id,BOOL isEnabled);
void wimaxcu_get_fast_reconnect(WIMAX_API_DEVICE_ID_P p_device_id);
void wimaxcu_get_connected_as_current(WIMAX_API_DEVICE_ID_P p_device_id);
void wimaxcu_get_coex_mode(WIMAX_API_DEVICE_ID_P p_device_id);
void wimaxcu_set_coex_mode(WIMAX_API_DEVICE_ID_P p_device_id,WIMAX_API_COEXISTENCE_MODE coexMode);
void wimaxcu_get_odm_info(WIMAX_API_DEVICE_ID_P p_device_id);
void wimaxcu_get_nvm_info(WIMAX_API_DEVICE_ID_P p_device_id);
void wimaxcu_set_connected_as_current(WIMAX_API_DEVICE_ID_P p_device_id,BOOL isEnable);
int wimaxcu_get_device_info(WIMAX_API_DEVICE_ID_P p_device_id);
int wimaxcu_get_user_link_status(WIMAX_API_DEVICE_ID_P p_device_id);
int wimaxcu_get_user_link_status_ex(WIMAX_API_DEVICE_ID_P p_device_id);
int wimaxcu_get_stats(WIMAX_API_DEVICE_ID_P p_device_id);
int wimaxcu_connect_with_nsp_info(WIMAX_API_DEVICE_ID_P p_device_id, char *str_nspid, int activate);
int wimaxcu_connect_with_profile_id(WIMAX_API_DEVICE_ID_P p_device_id,  char * profileId_str);
int wimaxcu_activate(WIMAX_API_DEVICE_ID_P p_device_id, char *str_nspid);
int wimaxcu_disconnect(WIMAX_API_DEVICE_ID_P p_device_id);
int wimaxcu_set_radio_on(WIMAX_API_DEVICE_ID_P p_device_id);
int wimaxcu_set_radio_off(WIMAX_API_DEVICE_ID_P p_device_id);
void wimaxcu_main_help();
// void usage();
void wimaxcu_get_conn_nsp(WIMAX_API_DEVICE_ID_P p_device_id);
void wimaxcu_get_conn_time(WIMAX_API_DEVICE_ID_P p_device_id);
int wimaxcu_service_provider_unlock(WIMAX_API_DEVICE_ID_P p_device_id,char *unlockcode);
int wimaxcu_get_profile_list(WIMAX_API_DEVICE_ID_P p_device_id);
int wimaxcu_get_prov_status(WIMAX_API_DEVICE_ID_P p_device_id, char * str_nspid);
int wimaxcu_get_sp_lock_status(WIMAX_API_DEVICE_ID_P p_device_id);
int wimaxcu_get_contact_info(WIMAX_API_DEVICE_ID_P p_device_id, char * str_nspid);
int wimaxcu_find_network(WIMAX_API_DEVICE_ID_P p_device_id,
	int profileId, WIMAX_API_NSP_INFO_P nspInfo );

int wimaxcu_reset_device(WIMAX_API_DEVICE_ID_P p_device_id);
int wimaxcu_reset_to_factory_settings(WIMAX_API_DEVICE_ID_P p_device_id);

WIMAX_API_RET register_apdo_cb(WIMAX_API_DEVICE_ID_P p_device_id);
WIMAX_API_RET unregister_apdo_cb(WIMAX_API_DEVICE_ID_P p_device_id);
WIMAX_API_RET register_puma_cb(WIMAX_API_DEVICE_ID_P p_device_id);
WIMAX_API_RET unregister_puma_cb(WIMAX_API_DEVICE_ID_P p_device_id);

int wimaxcu_install_apdo_updates(WIMAX_API_DEVICE_ID_P p_device_id);
void wimaxcu_check_for_apdo_updates(WIMAX_API_DEVICE_ID_P p_device_id);
void wimaxcu_check_for_apdo_updates(WIMAX_API_DEVICE_ID_P p_device_id);
void wimaxcu_apdo_client_test(WIMAX_API_DEVICE_ID_P p_device_id);
void user_system_state_update_cb(WIMAX_API_DEVICE_ID_P pDeviceId, WIMAX_API_DEVICE_STATUS deviceStatus, WIMAX_API_STATUS_REASON statusReason, WIMAX_API_CONNECTION_PROGRESS_INFO connectionProgressInfo);

void ind_device_update_cb(WIMAX_API_DEVICE_ID_P pDeviceId, WIMAX_API_DEVICE_STATUS systemStatus, WIMAX_API_STATUS_REASON statusReason, WIMAX_API_CONNECTION_PROGRESS_INFO connectionProgressInfo);


void ind_provisioning_operation_cb (WIMAX_API_DEVICE_ID_P 
					  p_device_id,
					  WIMAX_API_PROV_OPERATION
					  provisoningOperation,
					  WIMAX_API_CONTACT_TYPE contactType);

void ind_package_update_cb(WIMAX_API_DEVICE_ID_P p_device_id, WIMAX_API_PACK_UPDATE packageUpdate);

void ind_network_search_wide_scan_cb_ex (WIMAX_API_DEVICE_ID_P 
					  p_device_id,
					  WIMAX_API_NSP_INFO_EX_P pNspList,
					  UINT32 listSize);
void ind_network_search_cb_ex (WIMAX_API_DEVICE_ID_P 
					  p_device_id,
					  WIMAX_API_NSP_INFO_EX_P pNspList,
			 UINT32 listSize, UINT32 searchProgress);


void ind_network_search_wide_scan_cb (WIMAX_API_DEVICE_ID_P 
					  p_device_id,
					  WIMAX_API_NSP_INFO_P pNspList,
					  UINT32 listSize);
void ind_network_search_cb (WIMAX_API_DEVICE_ID_P 
					  p_device_id,
					  WIMAX_API_NSP_INFO_P pNspList,
			 UINT32 listSize, UINT32 searchProgress);

void ind_rf_taken_cb (WIMAX_API_DEVICE_ID_P  p_device_id);

int wimaxcu_is_network_activated(WIMAX_API_DEVICE_ID_P p_device_id,
				WIMAX_API_NSP_INFO_P nspInfo);
int wimaxcu_is_network_activated_ex(WIMAX_API_DEVICE_ID_P p_device_id,
				WIMAX_API_NSP_INFO_EX_P nspInfo);

void wimaxcu_restore_pro_db(WIMAX_API_DEVICE_ID_P p_device_id);
int wimaxcu_restore_factory_settings(WIMAX_API_DEVICE_ID_P p_device_id);
int wimaxcu_deactivate(WIMAX_API_DEVICE_ID_P p_device_id, char *str_nspid);


#endif
