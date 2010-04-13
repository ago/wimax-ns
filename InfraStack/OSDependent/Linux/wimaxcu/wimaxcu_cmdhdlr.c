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

#include <stdio.h>
#include <string.h>

#include "wimaxcu_defs.h"
#include "wimaxcu.h"
#include "wimaxcu_util.h"

// ////////////////////////////////////////////////////////////////////
//
// Define the array listing the specifics of various cu commands...


static struct cu_cmd_specs cu_commands[] =
{
	// Status
	{ 	CMD_STR_STATUS, CMD_STATUS,
		0 /* min args */, 2 /* max/allowed args */, 0, CMD_STR_STATUS_ARGS_SYSTEM /* default arg */,
		{
			{ CMD_STR_STATUS_ARGS_SYSTEM, CMD_STATUS_ARG_SYSTEM },
			{ CMD_STR_STATUS_ARGS_CONNECT,	CMD_STATUS_ARG_CONNECT },
			{ CMD_STR_STATUS_ARGS_LINK, CMD_STATUS_ARG_LINK },
			{ CMD_STR_STATUS_ARGS_LINK_EX, CMD_STATUS_ARG_LINK_EX },
			{ CMD_STR_STATUS_ARGS_RADIO, CMD_STATUS_ARG_RADIO },
			{ CMD_STR_STATUS_ARGS_LOCK, CMD_STATUS_ARG_LOCK },
			{ CMD_STR_STATUS_ARGS_PROVISION, CMD_STATUS_ARG_PROVISION }
		}
	},
	// Ip Interface Index
	{ CMD_STR_IPINTERFACE, CMD_IPINTERFACE, 0, 0, 0, ""},

	// Radio on
	{ CMD_STR_RON, CMD_RON, 0, 0, 0, ""},

	// Radio off
	{ CMD_STR_ROFF, CMD_ROFF, 0, 0, 0, "" } ,

	// Scan
	{
		CMD_STR_SCAN, CMD_SCAN, 0, 1, 0, CMD_STR_SCAN_ARGS_PREFERRED,
		{
			{ CMD_STR_SCAN_ARGS_PREFERRED, CMD_SCAN_ARG_PREFERRED },
			{ CMD_STR_SCAN_ARGS_WIDE, CMD_SCAN_ARG_WIDE }
		}
	 },

	// ScanEx
	{
		CMD_STR_SCAN_EX, CMD_SCAN_EX, 0, 1, 0, CMD_STR_SCAN_ARGS_PREFERRED,
		{
			{ CMD_STR_SCAN_ARGS_PREFERRED, CMD_SCAN_ARG_PREFERRED },
			{ CMD_STR_SCAN_ARGS_WIDE, CMD_SCAN_ARG_WIDE }
		}
	 },

	// Connect
	{
		CMD_STR_CONNECT, CMD_CONNECT, 2, 2, 0, "",
		{
			{ CMD_STR_CONNECT_ARGS_NETWORK,	CMD_CONNECT_ARG_NETWORK },
			{ CMD_STR_CONNECT_ARGS_PROFILE,	CMD_CONNECT_ARG_PROFILE }
		}
	 },

	// Disconnect
	{ CMD_STR_DISCONNECT, CMD_DISCONNECT, 0, 0, 0, "" },

	// Mode (connect, scan)
	{
		CMD_STR_MODE, CMD_MODE, 0, 4, 0, "" ,
		{
			{ CMD_STR_MODE_ARGS_SCAN, CMD_MODE_ARG_SCAN },
			{ CMD_STR_MODE_ARGS_CONNECT, CMD_MODE_ARG_CONNECT }
		},
		// Scan/connect mode options
		{
			{
			CMD_STR_MODE_ARGS_SCAN_OPT_AUTO,
			CMD_STR_MODE_ARGS_SCAN_OPT_SEMI,
			CMD_STR_MODE_ARGS_SCAN_OPT_MANUAL
			},
			{
			CMD_STR_MODE_ARGS_CONNECT_OPT_AUTO,
			CMD_STR_MODE_ARGS_CONNECT_OPT_MANUAL,
			""
			}
		},

	},

	// Info
	{
		CMD_STR_INFO, CMD_INFO, 0, 2, 0, CMD_STR_INFO_ARGS_VERSION ,
		{
			{ CMD_STR_INFO_ARGS_DEVICE, CMD_INFO_ARG_DEVICE },
			{ CMD_STR_INFO_ARGS_STATS, CMD_INFO_ARG_STATS },
			{ CMD_STR_INFO_ARGS_CONTACT, CMD_INFO_ARG_CONTACT },
			{CMD_STR_INFO_ARGS_ODM, CMD_INFO_ARG_ODM},
			{CMD_STR_INFO_ARGS_NVM, CMD_INFO_ARG_NVM},
            {CMD_STR_INFO_ARGS_VERSION, CMD_INFO_ARG_VERSION},
			}
		
	
	},

	//Set Fast Reconnect
	{ 
		CMD_STR_SET_FAST_RECONNECT, CMD_SET_FAST_RECONNECT, 1, 2, 0, "",
		{
			{CMD_STR_ARGS_ENABLE, CMD_ENABLE},
			{CMD_STR_ARGS_DISABLE, CMD_DISABLE},
		}
	},
	//Get Fast Reconnect
	{CMD_STR_GET_FAST_RECONNECT, CMD_GET_FAST_RECONNECT, 0, 0, 0, ""},
		
	//Set Current Connected Network Preferred settings....
	{ 
		CMD_STR_SET_CURRENT_CONNECTED_AS_PREFERRED, CMD_SET_CURRENT_CONNECTED_AS_PREFERRED, 1, 2, 0, "",
		{
			{CMD_STR_ARGS_ENABLE, CMD_ENABLE},
			{CMD_STR_ARGS_DISABLE, CMD_DISABLE},
		}
	 },
	//Get Current Connected Network Preferred settings....
	{CMD_STR_GET_CURRENT_CONNECTED_AS_PREFERRED, CMD_GET_CURRENT_CONNECTED_AS_PREFERRED, 0, 0, 0, ""},
	//Get WiMAX API Ex Version
	{CMD_STR_GET_GET_WMX_API_EX_VERSION, CMD_GET_GET_WMX_API_EX_VERSION, 0, 0, 0, ""},

	//Set Co-Ex ModeOfOperation
	{ 
		CMD_STR_SET_COEX_MODE,CMD_SET_COEX_MODE, 1, 2, 0, "",
		{
			{CMD_STR_MODE_XOR, CMD_MODE_XOR},
			{CMD_STR_MODE_CM, CMD_MODE_CM},
		}
	 },

	
	//Get Co-Ex Mode
	{CMD_STR_GET_COEX_MODE, CMD_GET_COEX_MODE, 0, 0, 0, ""},

	// Activate
	{ CMD_STR_ACTIVATE, CMD_ACTIVATE, 1, 1, 1, "" },

	// DeActivate
	{ CMD_STR_DEACTIVATE, CMD_DEACTIVATE, 1, 1, 1, "" },

	// Unlock
	{ CMD_STR_UNLOCK, CMD_UNLOCK, 1, 1, 1, "" },

	// Reset
	{
		CMD_STR_RESET, CMD_RESET, 1, 1, 0, "" ,
		{
			{ CMD_STR_RESET_ARGS_DEVICE, CMD_RESET_ARG_DEVICE },
			{ CMD_STR_RESET_ARGS_FACTORY, CMD_RESET_ARG_FACTORY }
		}
	},

	// Profile list
	{ CMD_STR_PROFILE_LIST, CMD_PROFILE_LIST, 0, 0, 0, "" },

	// Restore provisioning db
	// { CMD_STR_RESTORE_PROVDB, CMD_RESTORE_PROVDB, 0, 0, 0, "" },

	// Help.
	{ CMD_STR_HELP, CMD_HELP, 0, 0, 0, "" }	,

	// Update.
	{ CMD_STR_UPDATE, CMD_UPDATE, 0, 0, 0, "" },
	
	//StopScan
	{ CMD_STR_STOP_SCAN, CMD_STOP_SCAN, 0, 0, 0, "" }
};


static int find_string(char **strings, int size_strings, char *to_find)
{
	int index = 0;

	if ( !size_strings || strings == NULL || to_find == NULL || !strlen(to_find) )
		return -1;

	for (; index < size_strings; index++)
		if ( strings[index] && !strcmp(strings[index], to_find) )
			return index;

	return -1;

}

static CMD_ARGS get_cmd_arg(cmd_arg_map arg_map[], int map_size, char* cmd_arg_to_find)
{
	int index = 0;

	CMD_ARGS ret_cmd_arg = CMD_ARG_INVALID;

	if ( !map_size || arg_map == NULL || cmd_arg_to_find == NULL || !strlen(cmd_arg_to_find) )
		return ret_cmd_arg;

	for ( index = 0; index < map_size; index++)
		if ( arg_map[index].cmd_arg_str && !strcmp(arg_map[index].cmd_arg_str, cmd_arg_to_find) )
			return (ret_cmd_arg = arg_map[index].cmd_arg);

	return ret_cmd_arg;

}

int validate_cmd(int argc, char* argv[], parsed_cmd* validated_cmd)
{
 	char* cmd = NULL;
	int num_args;
	char **cmd_args = NULL;

	struct cu_cmd_specs *cmd_spec = NULL;
	char *cmd_arg_str = NULL, *arg_value = NULL;
	int cmd_arg = -1 ;
	int b_return = -1;
	char *scan_mode_param = NULL, *connect_mode_param = NULL;
	register int i;


	if ( validated_cmd == NULL )
		return -1;

	// Process the cmd line first.
	num_args = argc - 2;	// start from whats being passed after "wimaxcu cmd"
	if ( num_args >= 0 )
		cmd = argv[1];
	if ( num_args >= 1 )
		cmd_args = &argv[2];


	// Check if -
	//	some cmd is specified and is valid and
	if (cmd == NULL )
		goto exit_usage;

	// Check if cmd text is valid...
	for ( i=0; i < sizeof(cu_commands)/sizeof(struct cu_cmd_specs); i++)
	{
		if ( !strcmp(cmd, cu_commands[i].cmd_text) )
		{
			cmd_spec = &cu_commands[i];
			break;
		}
	}

	//  If proper # of arguments are being passed..
	// 	if no cmd arg supplied and there are no defaults.
	if ( (i == sizeof(cu_commands)/sizeof(struct cu_cmd_specs) ) ||
	     ( (cmd_spec->min_args == 1) && !num_args  && !cmd_spec->default_arg )
	     || ( (cmd_spec->min_args > num_args) || (num_args > cmd_spec->max_args) )
           )
	{
		// invalid cmd specified or in-sufficient number of arguments passed...
		goto exit_usage;
	}


	// Validate cmd args if any...
	if (!cmd_spec->variable_arg )
	{
		if ( (num_args >= 1) ||
			( /* (cmd_spec->min_args == 1) && */ cmd_spec->default_arg  && strlen(cmd_spec->default_arg) ) )
		{
			if (num_args < 1)
				cmd_arg_str = cmd_spec->default_arg;
			else
				cmd_arg_str = cmd_args[0];

			// Validate the cmd argument...
			if ( (cmd_arg = get_cmd_arg(cmd_spec->cmd_args, sizeof(cmd_spec->cmd_args)/sizeof(cmd_arg_map), cmd_arg_str)) == CMD_ARG_INVALID )
				goto exit_usage;

		}
	}
	if (num_args >= 1 )
	{
		// Record the user supplied value to a command argument (eg. wimaxcu connect network "123")
			arg_value = cmd_args[num_args-1];
	}

	// Exception cases in certain cmds like status prov mandatory-arg or connectmode...

	switch (cmd_spec->cmd)
	{
		case CMD_STATUS:
			if ( ((cmd_arg == CMD_STATUS_ARG_PROVISION) && (num_args != 2 )) ||
				( (cmd_arg != CMD_STATUS_ARG_PROVISION) && (num_args > 1)) )
				goto exit_usage;
			break;

		case CMD_INFO:
			if ( ((cmd_arg == CMD_INFO_ARG_CONTACT) && (num_args != 2 )) ||
				( (cmd_arg != CMD_INFO_ARG_CONTACT) && (num_args > 1)) )
				goto exit_usage;
			break;

		case CMD_MODE:
			if ( num_args >= 1)
			{
				if ( (num_args != 2) && (num_args != 4) )
					goto exit_usage;

				if ( find_string(cmd_spec->scan_connect_mode_options[cmd_arg],
						sizeof(cmd_spec->scan_connect_mode_options[cmd_arg])/sizeof(char *), cmd_args[1]) == -1 )
					goto exit_usage;
				if (cmd_arg == CMD_MODE_ARG_SCAN)
					scan_mode_param = cmd_args[1];
				else
					connect_mode_param = cmd_args[1];

				if (num_args == 4)
				{
					// Make sure we are not passed the same arg twice...
					if ( !strcmp(cmd_arg_str, cmd_args[2]) )
						goto exit_usage;

					if ( (cmd_arg = get_cmd_arg(cmd_spec->cmd_args,
								sizeof(cmd_spec->cmd_args)/sizeof(cmd_arg_map),
								cmd_args[2])) == CMD_ARG_INVALID)
						goto exit_usage;

					if ( find_string(cmd_spec->scan_connect_mode_options[cmd_arg],
						sizeof(cmd_spec->scan_connect_mode_options[cmd_arg])/sizeof(char *), cmd_args[3]) == -1 )
						goto exit_usage;
					if (cmd_arg == CMD_MODE_ARG_SCAN)
						scan_mode_param = cmd_args[3];
					else
						connect_mode_param = cmd_args[3];
				}
			}
			break;

		default:
			break;
	} // end switch


	// Everything looks ok with the cmd...fill in the validated cmd struct and return
	validated_cmd->cmd = cmd_spec->cmd;
	validated_cmd->cmd_arg = (CMD_ARGS)cmd_arg;
	validated_cmd->arg_value = arg_value;
	validated_cmd->scan_mode_param = scan_mode_param;
	validated_cmd->connect_mode_param = connect_mode_param;

	b_return = 0;
exit_usage:

	return b_return;
}


#if 1

int cmd_handler(WIMAX_API_DEVICE_ID_P p_device_id,
		parsed_cmd * valid_cmd)
{
    int ret = 0;
	if ( (valid_cmd == NULL) || (p_device_id == NULL) )
	return 1;

	wimaxcu_check_for_apdo_updates(p_device_id);

    switch (valid_cmd->cmd) {
		case CMD_STATUS:
	switch (valid_cmd->cmd_arg) {
				case CMD_STATUS_ARG_SYSTEM:
	    ret = wimaxcu_get_system_status(p_device_id);
					break;

				case CMD_STATUS_ARG_CONNECT:
	    ret = wimaxcu_get_connect_status(p_device_id);
					break;

				case CMD_STATUS_ARG_LINK:
	    ret = wimaxcu_get_user_link_status(p_device_id);
					break;
				case CMD_STATUS_ARG_LINK_EX:
	    ret = wimaxcu_get_user_link_status_ex(p_device_id);
					break;
				case CMD_STATUS_ARG_RADIO:
	    ret = wimaxcu_get_rf_status(p_device_id);
					break;

				case CMD_STATUS_ARG_LOCK:
	    ret = wimaxcu_get_sp_lock_status(p_device_id);
					break;

				case CMD_STATUS_ARG_PROVISION:
	    ret = wimaxcu_get_prov_status(p_device_id, valid_cmd->arg_value);
					break;

				default:
        ret = 1;
					break;
			}
			break;

		case CMD_GET_GET_WMX_API_EX_VERSION:
			wimaxcu_get_api_ex_version(p_device_id);
			break;

		case CMD_GET_COEX_MODE:
			wimaxcu_get_coex_mode(p_device_id);
			break;

		case CMD_SET_COEX_MODE:
			if(strcmp(valid_cmd->arg_value,"xor")==0)
			wimaxcu_set_coex_mode(p_device_id,MODE_XOR);
			else if(strcmp(valid_cmd->arg_value,"cm")==0)
			wimaxcu_set_coex_mode(p_device_id,MODE_CM);
			break;

		case CMD_IPINTERFACE:
			wimaxcu_get_ip_interface(p_device_id);
			break;

		case CMD_SET_FAST_RECONNECT:
			if(strcmp(valid_cmd->arg_value,"enable")==0)
			wimaxcu_set_fast_reconnect(p_device_id, 1);
			else
			if(strcmp(valid_cmd->arg_value,"disable")==0)
			wimaxcu_set_fast_reconnect(p_device_id, 0);
		break;

		case CMD_GET_FAST_RECONNECT:
			wimaxcu_get_fast_reconnect(p_device_id);
		break;
		
		case CMD_SET_CURRENT_CONNECTED_AS_PREFERRED:
			if(strcmp(valid_cmd->arg_value,"enable")==0)
			wimaxcu_set_connected_as_current(p_device_id,1);
			else
			if(strcmp(valid_cmd->arg_value,"disable")==0)
			wimaxcu_set_connected_as_current(p_device_id, 0);
		break;

		case CMD_GET_CURRENT_CONNECTED_AS_PREFERRED:
			wimaxcu_get_connected_as_current(p_device_id);
		break;

		case CMD_RON:
	ret = wimaxcu_set_radio_on(p_device_id);
			break;

		case CMD_ROFF:
	ret = wimaxcu_set_radio_off(p_device_id);
			break;

		case CMD_SCAN:
	ret = wimaxcu_get_network_list(p_device_id, valid_cmd->cmd_arg);
			break;

		case CMD_SCAN_EX:
	ret = wimaxcu_get_network_list_ex(p_device_id, valid_cmd->cmd_arg);
			break;

		case CMD_CONNECT:
	switch (valid_cmd->cmd_arg) {
				case CMD_CONNECT_ARG_NETWORK:
	    ret = wimaxcu_connect_with_nsp_info(p_device_id, valid_cmd->arg_value, 0);
					break;
				case CMD_CONNECT_ARG_PROFILE:
	    ret = wimaxcu_connect_with_profile_id(p_device_id, valid_cmd->arg_value);
					break;
				default:
					break;
			}
			break;

		case CMD_DISCONNECT:
	ret = wimaxcu_disconnect(p_device_id);
			break;

		case CMD_MODE:
			if ( valid_cmd->cmd_arg == CMD_ARG_INVALID)
	    ret = wimaxcu_get_user_connect_mode(p_device_id);
			else
	    ret = wimaxcu_set_user_connect_mode(p_device_id, valid_cmd->connect_mode_param,
			       valid_cmd->scan_mode_param);
			break;

		case CMD_INFO:
	switch (valid_cmd->cmd_arg) {
				case CMD_INFO_ARG_DEVICE:
	    ret = wimaxcu_get_device_info(p_device_id);
					break;
				case CMD_INFO_ARG_STATS:
	    ret = wimaxcu_get_stats(p_device_id);
					break;
				case CMD_INFO_ARG_CONTACT:
	    ret = wimaxcu_get_contact_info(p_device_id, valid_cmd->arg_value);
					break;
				case CMD_INFO_ARG_ODM:
	     			wimaxcu_get_odm_info(p_device_id);
					break;
				case CMD_INFO_ARG_NVM:
	    			wimaxcu_get_nvm_info(p_device_id);
					break;
                case CMD_INFO_ARG_VERSION:
                    wimaxcu_get_version_info(p_device_id);
                    break;
				default:
					break;
			}
			break;

		case CMD_ACTIVATE:
	ret = wimaxcu_activate(p_device_id, valid_cmd->arg_value);
			break;

		case CMD_DEACTIVATE:
	ret = wimaxcu_deactivate(p_device_id, valid_cmd->arg_value);
			break;

		case CMD_UNLOCK:
	ret = wimaxcu_service_provider_unlock(p_device_id, valid_cmd->arg_value);
			break;

		case CMD_RESET:
	switch (valid_cmd->cmd_arg) {
				case CMD_RESET_ARG_DEVICE:
	    ret = wimaxcu_reset_device(p_device_id);
					break;
				case CMD_RESET_ARG_FACTORY:
	    ret = wimaxcu_restore_factory_settings(p_device_id);
					break;
				default:
					break;
			}
			break;

		case CMD_PROFILE_LIST:
	ret = wimaxcu_get_profile_list(p_device_id);
			break;

// 		case CMD_RESTORE_PROVDB:
// 			RestoreProDB(p_device_id);
// 			break;

    case CMD_UPDATE:
        ret = wimaxcu_install_apdo_updates(p_device_id);
        break;

		case CMD_HELP:
        		wimaxcu_main_help();
			break;
		case CMD_STOP_SCAN:
			ret = wimaxcu_stop_scan(p_device_id);
			break;
		

	} // end switch

    return ret;

}

#endif


#if 0

int main (int argc, char *argv[])
{
	int isvalid = 0;

	parsed_cmd out_cmd;

	isvalid = validate_cmd(argc, argv, &out_cmd);

	printf("Command is %s.\n", !isvalid ? "valid" : "not valid");

	if ( !isvalid )
	{
		printf("Argument to cmd is %d\n", out_cmd.cmd_arg);
	}


	return 0;
}

#endif
