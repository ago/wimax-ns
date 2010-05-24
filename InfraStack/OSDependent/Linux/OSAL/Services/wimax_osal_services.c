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

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <crtdbg.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>

#include "wimax_osal_types.h"
#include "wimax_osal_primitives.h"
#include "wimax_osal_string.h"
#include "wimax_osal_services_cmn.h"
#include "wimax_osal_ip_services.h"
#include "wimax_osal_config_controler.h"
#include "wimax_osal_trace.h"

#include "L4ConfigurationManager.h"

int linkup_redundant = 0;
char * g_ifacename = NULL;

#define TRACE(x, y, z, ...)

#define		OSAL_DEFUALT_STR_LEN	1024		// temporary (will go away)

void *ManageIPThread(void *param);

void OSAL_BuildFullPath(char* src, char* dstFull, int nSizeFull)
{
	char pRootPath[OSAL_DEFUALT_STR_LEN] = {0};
	int len =0;

	// IMPORTANT 

	// TODO::OSAL-WORK::IMPORTANT - BuildFullPath - Creates backwork dependency and not suitable for Linux
	// This needs some caution as the default root path may not be suitable 
	// for all the purposes this method could be employed in 

	// Like for eg. we ideally want the NDnS related stuff to be under 
	// {prefix}/share/wimax folder


	if(!dstFull)
		return;

	dstFull[0]=0;

	// WiMAX DB file is updated by wimaxd. The current location /usr/share/wimax is read-only.
	// Moving WiMAX DB to /var/lib/wimax
	if (!strncmp(src, "WiMAX_DB.bin", OSAL_DEFUALT_STR_LEN) || !strncmp(src, "WiMAX_Def.bin", OSAL_DEFUALT_STR_LEN)) {
		strcpy(pRootPath, PKG_LOCALSTATE_DIR);
	}
	else {
		strcpy(pRootPath, PKG_DATA_DIR);
	}

	if(pRootPath[0])
	{
		len = strlen(pRootPath);

		// Put a '/' at the end and then append the incoming file name. 
		if ( pRootPath[len-1] != '/' )
			pRootPath[len] = '/';
	
		OSAL_strcpy_s(dstFull, nSizeFull, pRootPath);
		OSAL_strcat_s(dstFull, nSizeFull, src);
	}
}

BOOL OSAL_writeData (BYTE *buf, UINT32 bufSize, const char *fileName)
{
	FILE *stream;
	size_t numOfBytesWritten = 0;
	BOOL rc = TRUE;

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ALERT, "OSAL_writeData start writing file");
	if((stream = fopen(fileName, "w" )) == NULL)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ALERT, "db_WriteData - open file failed!, Stream: %d ", stream);
		return FALSE;
	}

	numOfBytesWritten = fwrite(buf, sizeof( BYTE ), bufSize, stream );
	if(numOfBytesWritten < bufSize)
	{
		fclose(stream);
		free(buf);
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "db_WriteData : num of written bytes is incorrect");
	}

	if(fflush(stream))
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_CRITICAL, "db_WriteData : fflush failed");
		rc = FALSE;
	}
	if(fclose(stream))
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_CRITICAL, "OSAL_witeData : fclose failed");
		rc = FALSE;
	}
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ALERT, "OSAL_writeData end writing file");
	return rc;
}

BOOL OSAL_readData (const char *fileName, BYTE *buf, size_t *bufSize)
{
	FILE *hFile = NULL;
	long fileSize = 0;
	BOOL rc = TRUE;

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ALERT, "OSAL_ReadData start reading file");
	if((hFile = fopen(fileName, "r")) == NULL)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ALERT, "OSAL_ReadData - open file failed!, Handle: %d ", hFile);
		return FALSE;
	}

	// Get file size
	fseek(hFile, 0, SEEK_END);
	fileSize = ftell(hFile);
	fseek(hFile, 0, SEEK_SET);

	if( (*bufSize < (size_t)fileSize) || (NULL == buf) )
	{
		fclose(hFile);
		*bufSize = fileSize;
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "OSAL_ReadData: the input buffer is not big enough");
		return FALSE;
	}

	*bufSize = fread(buf, sizeof(BYTE), fileSize, hFile);

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "OSAL_ReadData : fileSize = %d", fileSize);

	if(fclose(hFile))
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_CRITICAL, "OSAL_ReadData : fclose failed");
		rc = FALSE;
	}

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ALERT, "OSAL_ReadData end reading file");
	return rc;
}

//This function is to read if obfuscation is enabled or disabled.
int OSAL_GetObfuscateConfig()
{
	
	UINT32 Obfuscate_or_not = 0;	// allow obfuscation by default
	BOOL res;
	
	OSALTRACE(OSAL_DEBUG, ("Enter OSAL_GetObfuscateConfig"));
	res = OSAL_ConfigController_GetNumValue("ignore", KEY_ENTRY_OBFUSCATE, &Obfuscate_or_not);
	if ( (res == TRUE) && (Obfuscate_or_not != 0) ) 
	{
		OSALTRACE(OSAL_DEBUG, ("Obfuscation is disabled"));
		//return 0;
	}

	return Obfuscate_or_not;
}


// Method to renew or do the needful with IP handling. 
//
// Parameters - mediaStatus
// Possible values: (TODO:: need actual value for the following)
//	1. LinkUp = 1
//	2. LinkDown = 2
//	3. LinkRenew = 3

typedef enum 
{
	LinkUp = 1,
	LinkDown,
	LinkRenew
} LinkIndication;

UINT32 OSAL_RenewIP( UINT32 mediaStatus )
{
	// TODO::OSAL-WORK::IMPORTANT BUT NON-CRITICIAL -  OSAL_RenewIP - 
	UINT32 renew_IP_or_not = 1;	// allow renewing by default
	BOOL res;
	pthread_t ipMgmtThread;
	pthread_attr_t attr;


#ifndef _WIMAX_SDK_
	// TODO:Change the TRACE log level to OSAL_DEBUG as soon as 
	// dhcp renew has stabilized
	OSALTRACE(OSAL_DEBUG, ("Entering OSAL_RenewIP"));

	if (mediaStatus == LinkUp)
	{
		// TODO: Change the TRACE log level to OSAL_DEBUG as soon as 
		// dhcp renew has stabilized	
		OSALTRACE(OSAL_DEBUG, ("media status is LinkUp"));
	}
	else if (mediaStatus == LinkDown)
	{
		//TODO: Change the TRACE log level to OSAL_DEBUG as soon as 
		// dhcp renew has stabilized
		OSALTRACE(OSAL_DEBUG, ("media status is LinkDown"));
	}
	else if (mediaStatus == LinkRenew)
	{
		// TODO: Change the TRACE log level to OSAL_DEBUG as soon as 
		// dhcp renew has stabilized
		OSALTRACE(OSAL_DEBUG, ("media status is LinkRenew"));
	}
	else
	{
		OSALTRACE(OSAL_ERROR, ("Unkown media status reported"));
		OSALTRACE(OSAL_ERROR, ("Exiting OSAL_RenewIP - Error"));
		return -1;
	}

	res = OSAL_ConfigController_GetNumValue("ignore", KEY_ENTRY_IP_RENEW, &renew_IP_or_not);
	if ( (res == TRUE) && (renew_IP_or_not != 1) ) 
	{
		OSALTRACE(OSAL_ERROR, ("IP renewal is disabled"));
		OSALTRACE(OSAL_ERROR, ("Exiting OSAL_RenewIP - Error"));
		return 0;
	}


	// Step 1: Spawn a new thread and pass the param name. 
	// Step 2: Thread func to do the needful based on the link state (releaseing IP, leaseing IP or renewing the lease on the IP)
	// TODO: Change the TRACE log level to OSAL_DEBUG as soon as 
	// dhcp renew has stabilized
	OSALTRACE(OSAL_DEBUG, ("Creating thread to manage IP"));

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	pthread_create(&ipMgmtThread,&attr, ManageIPThread, (void *)mediaStatus);
	// return OSAL_create_thread(ManageIPThread, (void *)mediaStatus, &ipMgmtThread);

#endif 
	// Change the TRACE log level to OSAL_DEBUG as soon as 
	// dhcp renew has stabilized
	OSALTRACE(OSAL_DEBUG, ("Exiting OSAL_RenewIP - Success"));

	return 0;	// Whats the convention??
}


void *ManageIPThread(void *param)
{
#define DHCP_RENEW_FILE_NAME "dhcp_renew.sh"

	char file_name[MAX_FILENAME_LEN + 10]; // 10 more chacters to add interface name	
	int len = 0;
	char interface_name[DEFULT_STR_SIZE];
	int result;
	LinkIndication indication = (LinkIndication)param;

	OSALTRACE(OSAL_ERROR, ("Enter"));

	strcpy(file_name, PKG_DATA_DIR);
	len = strlen(file_name);
	
	if(file_name[len-1] != '/') {
		strcat(file_name,"/");
	} 
	
	strcat(file_name, DHCP_RENEW_FILE_NAME);	
	
	interface_name[0] = '\0';

	result = L4Configurations_getInterfaceName(interface_name);
	if ( !result || (interface_name[0] == '\0') )
	{
		OSALTRACE(OSAL_ERROR, ("Failed to get interface name"));
		return 0;
	}

	strcat (file_name ," ");
	
	if(linkup_redundant == 0)
	{
		if (indication == LinkUp) 
		{
			linkup_redundant = 1;
		}
	}
	else
	{
		if (indication == LinkDown) 
		{
			linkup_redundant = 0;
			OSALTRACE(OSAL_ERROR, ("link down"));
		}
		else if (indication == LinkUp)
		{
			OSALTRACE(OSAL_ERROR, ("redundant link up so no need to call script qutting thread"));
			return 0;
		}
		else	
		{
			//Don Nothing
			OSALTRACE(OSAL_DEBUG, ("link renew"));
		}
	}

	switch (indication)
	{
		case LinkUp:
    			strcat (file_name ,"lease");
			break;

		case LinkDown: 
			strcat (file_name ,"release");
			break;

		case LinkRenew:
			strcat (file_name ,"renew");
			break;

		default:
			OSALTRACE(OSAL_ERROR, ("Invalid link indication passed"));
			return 0;
	}
	strcat (file_name ," ");
	strcat(file_name, interface_name);
	
	OSALTRACE(OSAL_ERROR, ("About to launch dhcp script %s.", file_name));

	result = system(file_name);


	if(result != 0)
		OSALTRACE(OSAL_ERROR, ("Unable to renew the IP address"));
	OSALTRACE(OSAL_DEBUG, ("Success Done in IP renew thread exit"));


	// TODO: Change the TRACE log level to OSAL_DEBUG as soon as 
	// dhcp renew has stabilized
	OSALTRACE(OSAL_DEBUG, ("Success Done in IP renew thread exit"));
 
	return 0;
}

BOOL OSAL_GetOSVersion(char *version)
{
	if ( version == NULL )
		return FALSE;

	// Assumption buffer has sufficient size in it...
	strcpy(version, "Linux");
	
	return TRUE;
}


BOOL IsIPAddReady()
{

 	int fd;
 	struct ifreq ifr;
	char *ip_str = NULL;
	
 	fd = socket(AF_INET, SOCK_DGRAM, 0);

 	ifr.ifr_addr.sa_family = AF_INET;

 	strncpy(ifr.ifr_name, "wmx0", IFNAMSIZ-1);

 	ioctl(fd, SIOCGIFADDR, &ifr);

 	close(fd);


 	ip_str = inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr);

	if ( !strcasecmp(ip_str, "0.0.0.0") )
		return FALSE;
 
	return TRUE;

}


UINT32 GetHostName(char *hostName, UINT32 hostNameBufSize)
{
	if (hostName == NULL ){
		OSALTRACE(OSAL_ERROR, ("Error: Input parameter hostName(null)."));
		return -1;
	}

	FILE *fp = NULL;
	static char buffer[512];
	char tag[64];

        // hope this size will be OK for one line to read from the fileOB
        char line[1000];
        char *linep=line;

	int found = 0;


	fp = fopen("/etc/resolv.conf", "r");

	if ( fp == NULL)
	{

		OSALTRACE(OSAL_ERROR, ("failed to open resolver config file."));
		return -1;
	}

	while ( ((*linep=getc(fp)) != EOF) && !found )
	{
		if (*linep++ == '\n')
		{
			*linep = '\0';
			sscanf(line, "%s %s", tag, buffer);
			if (tag[0] && (!strcmp(tag, "search") || !strcmp(tag, "domain") ) ) {
				found = 1;
				break;
			}
			linep = line;
		}
	}

	fclose(fp);

	if ( found )
	{
		strcpy(hostName,buffer);
		OSALTRACE(OSAL_DEBUG, ("DHCP domain is  %s.", buffer));
	}
	else
	{
		OSALTRACE(OSAL_ERROR, ("Could not find dhcp domain in resolv.conf."));
		return -1;
	}

	return !found;
}


BOOL OSAL_FindDeviceFileName(char * deviceName)
{
	// TODO::OSAL-WORK::NON-CRITICAL but important - OSAL_FindDeviceFileName 
	// This is very Windows centric function and there is not good way to 
	// get the device interface or device information in Linux (userspace).
	// Recommend to use command line to get the device interface.
	// Return failure presently do not hurt
	return FALSE;
}

