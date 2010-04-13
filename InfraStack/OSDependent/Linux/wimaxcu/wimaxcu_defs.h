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

#ifndef __WIMAXCU_DEFS_H__
#define __WIMAXCU_DEFS_H__

#if 0
#include <vector>
#include <string>
#include <map>
#endif

// CU commands...

typedef enum {
	CMD_STATUS,
	CMD_IPINTERFACE,
	CMD_RON,
	CMD_ROFF,
	CMD_SCAN,
	CMD_SCAN_EX,
	CMD_CONNECT,
	CMD_DISCONNECT,
	CMD_MODE,
	CMD_INFO,
	CMD_ACTIVATE,
	CMD_DEACTIVATE,
	CMD_UNLOCK,
	CMD_RESET,
	CMD_PROFILE_LIST,
	// CMD_RESTORE_PROVDB,
	CMD_HELP,
	CMD_UPDATE,
	CMD_SET_FAST_RECONNECT,
	CMD_GET_FAST_RECONNECT,
	CMD_SET_CURRENT_CONNECTED_AS_PREFERRED,
	CMD_GET_CURRENT_CONNECTED_AS_PREFERRED,
	CMD_GET_GET_WMX_API_EX_VERSION,
	CMD_SET_COEX_MODE,
	CMD_GET_COEX_MODE,
	CMD_STOP_SCAN
} WIMAXCU_COMMANDS;

#define CMD_STR_STATUS		"status"
#define CMD_STR_IPINTERFACE	"getipinterface"
#define CMD_STR_RON		    "ron"
#define CMD_STR_ROFF		"roff"
#define CMD_STR_SCAN		"scan"
#define CMD_STR_SCAN_EX		"scanx"
#define CMD_STR_CONNECT		"connect"
#define CMD_STR_DISCONNECT	"dconnect"
#define CMD_STR_MODE		"connectmode"
#define CMD_STR_INFO		"info"
#define CMD_STR_ACTIVATE	"activate"
#define CMD_STR_DEACTIVATE	"deactivate"
#define CMD_STR_UNLOCK		"unlock"
#define CMD_STR_RESET		"reset"
#define CMD_STR_PROFILE_LIST	"plist"
// #define CMD_STR_RESTORE_PROVDB	"restoreprovdb"
#define CMD_STR_HELP		"help"
#define CMD_STR_UPDATE      "update"

#define CMD_STR_SET_FAST_RECONNECT	"setfastreconnect"
#define CMD_STR_GET_FAST_RECONNECT	"getfastreconnect"

#define CMD_STR_GET_CURRENT_CONNECTED_AS_PREFERRED	"getccap"
#define CMD_STR_SET_CURRENT_CONNECTED_AS_PREFERRED	"setccap"

#define CMD_STR_GET_GET_WMX_API_EX_VERSION	"getexversion"

#define CMD_STR_SET_COEX_MODE	"setcoexmode"
#define CMD_STR_GET_COEX_MODE	"getcoexmode"

#define CMD_STR_STOP_SCAN	"stopscan"
typedef enum 
{
	CMD_ARG_INVALID = -1,

	CMD_MODE_ARG_SCAN,		// Important - do not change this value
	CMD_MODE_ARG_CONNECT,

	CMD_STATUS_ARG_SYSTEM,
	CMD_STATUS_ARG_CONNECT ,
	CMD_STATUS_ARG_LINK ,
	CMD_STATUS_ARG_LINK_EX ,
	CMD_STATUS_ARG_RADIO ,
	CMD_STATUS_ARG_LOCK ,
	CMD_STATUS_ARG_PROVISION ,

	CMD_SCAN_ARG_PREFERRED,
	CMD_SCAN_ARG_WIDE,

	CMD_CONNECT_ARG_NETWORK ,
	CMD_CONNECT_ARG_PROFILE,

	CMD_INFO_ARG_DEVICE,
	CMD_INFO_ARG_STATS,
	CMD_INFO_ARG_CONTACT,
	CMD_INFO_ARG_ODM,
	CMD_INFO_ARG_NVM,
    CMD_INFO_ARG_VERSION,

	CMD_RESET_ARG_DEVICE,
	CMD_RESET_ARG_FACTORY,
	
	CMD_ENABLE,
	CMD_DISABLE,

	CMD_MODE_XOR,
	CMD_MODE_CM
} CMD_ARGS;


#define CMD_STR_STATUS_ARGS_SYSTEM		"system"
#define CMD_STR_STATUS_ARGS_CONNECT		"connect"
#define CMD_STR_STATUS_ARGS_LINK		"link"
#define CMD_STR_STATUS_ARGS_LINK_EX		"linkex"
#define CMD_STR_STATUS_ARGS_RADIO		"radio"
#define CMD_STR_STATUS_ARGS_LOCK		"lock"
#define CMD_STR_STATUS_ARGS_PROVISION		"prov"

#define CMD_STR_SCAN_ARGS_PREFERRED		"preferred"
#define CMD_STR_SCAN_ARGS_WIDE			"wide"

#define CMD_STR_CONNECT_ARGS_NETWORK		"network"
#define CMD_STR_CONNECT_ARGS_PROFILE		"profile"

#define CMD_STR_MODE_ARGS_CONNECT		"connect"
#define CMD_STR_MODE_ARGS_CONNECT_OPT_AUTO	"auto"
#define CMD_STR_MODE_ARGS_CONNECT_OPT_MANUAL	"manual"
#define CMD_STR_MODE_ARGS_SCAN			"scan"
#define CMD_STR_MODE_ARGS_SCAN_OPT_AUTO		"auto"
#define CMD_STR_MODE_ARGS_SCAN_OPT_SEMI		"semi"
#define CMD_STR_MODE_ARGS_SCAN_OPT_MANUAL	"manual"

#define CMD_STR_INFO_ARGS_DEVICE		"device"
#define CMD_STR_INFO_ARGS_STATS			"stats"
#define CMD_STR_INFO_ARGS_CONTACT		"contact"
#define CMD_STR_INFO_ARGS_ODM			"odm"
#define CMD_STR_INFO_ARGS_NVM			"nvm"
#define CMD_STR_INFO_ARGS_VERSION       "version"

#define CMD_STR_RESET_ARGS_DEVICE		"device"
#define CMD_STR_RESET_ARGS_FACTORY		"factory"

#define CMD_STR_ARGS_ENABLE		"enable"
#define CMD_STR_ARGS_DISABLE		"disable"

#define CMD_STR_MODE_XOR		"xor"
#define CMD_STR_MODE_CM			"cm"


// /////////////// end command listing ///////////////

// SW/FW Upgrades related consts...

#define SW_UPGRADE_TYPE_DOWNLOAD_AND_UPDATE	"DownloadAndUpdate"
#define SW_UPGRADE_TYPE_DOWNLOAD		"Download"
#define SW_UPGRADE_TYPE_UPDATE			"Update"



typedef char *size_3_string_array[3];

typedef struct 
{
	char *cmd_arg_str;
	CMD_ARGS cmd_arg;
} cmd_arg_map;

struct cu_cmd_specs
{
	char *cmd_text;		// Actual command text like "connect", "scan",...

	WIMAXCU_COMMANDS cmd;		// Integral representation of the command to use in switches...

	int min_args;		// total required arguments including the command . eg wimaxcu scan => 2

	int max_args;		// Maximum allowed optional arguments..

	int variable_arg;

	char *default_arg;	// eg. scan [preferred]

	cmd_arg_map cmd_args[6];	// Maximum number of arguments any of cmds can accept (un-used ones will be either NULL or empty strings)

	size_3_string_array scan_connect_mode_options[2];
	char *cmd_mode_options[2];
	
};

//typedef map<string, struct cu_cmd_specs *> cmd_map;

typedef struct 
{
	WIMAXCU_COMMANDS cmd;	

	CMD_ARGS cmd_arg;		// If applicable like nop in ron/roff 
	
	char *arg_value;		// Whatever supplied by user which dont have any preset value

	char *scan_mode_param;		// If applicable (mode
	char *connect_mode_param;	
}parsed_cmd;

#endif 		// __WIMAXCU_DEFS_H__
