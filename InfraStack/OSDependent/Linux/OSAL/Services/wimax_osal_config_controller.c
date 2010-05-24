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

#include "wimax_osal_primitives.h"
#include "wimax_osal_string.h"
#include "wimax_osal_config_controler.h"
#include "wimax_osal_config_controler_defines.h"
#include "wimax_osal_trace.h"
#include "XmlParser.h"
#include <pthread.h>


static pthread_mutex_t g_configmutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t g_swapfilemutex = PTHREAD_MUTEX_INITIALIZER;


BOOL OSAL_ConfigController_GetNumValue(const char *ignore, const char *config_name, UINT32 * value)
{
	BOOL result = FALSE;
	BOOL bXmlRead;
	pXmlElement xmlRoot, xmlTopElement, xmlTargetElement;
	const char *target_data;

	BOOL bDnDOutputQuery = FALSE;

	if (config_name == NULL) {
		return result;
	}

	if ( strcasecmp(config_name, OSAL_KEY_ENTRY_DND_OUTPUT_MODE) == 0)
	{
		bDnDOutputQuery = TRUE;
	}

	pthread_mutex_lock(&g_configmutex);

	// Open Config XML file
	xmlRoot = CreateEmptyXmlData();

  
	bXmlRead = ReadXmlFile(xmlRoot, CONFIG_XMLFILE);
	if (!bXmlRead) {
		OSALTRACE(OSAL_ERROR, ("cannot read config xml file"));
		pthread_mutex_unlock(&g_configmutex);
		return result;
	}

	// Find "config_name"
	xmlTopElement = FindChild(xmlRoot, CONFIG_INTEL_WIMAX);
	xmlTargetElement = FindChild(xmlTopElement, config_name);
	if (xmlTargetElement != NULL) {
		target_data = GetElementInnerText(xmlTargetElement);
		if (target_data != NULL) {
			// Copy to the value
			*value = (UINT32) atoi(target_data);
			result = TRUE;
		}
	}

	if ( bDnDOutputQuery )
	{
		OSALTRACE(OSAL_DEBUG, ("Result of query is %d, and value is %d.", result, result ? *value : -1));
	}

	// Close XML
	FreeXmlData(xmlRoot);

	pthread_mutex_unlock(&g_configmutex);

	return result;
}

BOOL OSAL_ConfigController_SetNumValue(const char *ignore, const char *config_name, UINT32 *value)
{
    BOOL result = FALSE;
    BOOL bXmlRead, bSetInnerText, bXmlWrite;
    pXmlElement xmlRoot, xmlTopElement, xmlTargetElement;
    char buf[16] = {0};

    if (config_name == NULL) {
        return result;
    }

    pthread_mutex_lock(&g_configmutex);

    // Open Config XML file
    xmlRoot = CreateEmptyXmlData();


    bXmlRead = ReadXmlFile(xmlRoot, CONFIG_XMLFILE);
    if (!bXmlRead) {
		OSALTRACE(OSAL_ERROR, ("cannot read config xml file"));
		pthread_mutex_unlock(&g_configmutex);

        return result;
    }

    // Find "config_name"
    xmlTopElement = FindChild(xmlRoot, CONFIG_INTEL_WIMAX);
    xmlTargetElement = FindChild(xmlTopElement, config_name);
    if (xmlTargetElement != NULL) {
	//convert integer to string
	snprintf(buf, sizeof(buf), "%d", *value);
        bSetInnerText = SetElementInnerText(xmlTargetElement, buf);
        if(bSetInnerText == TRUE) {
            // write to XML file
            bXmlWrite = WriteXmlFile(xmlTopElement, CONFIG_XMLFILE_TMP);
            if(bXmlWrite == TRUE) {
                result = TRUE;
			}
			else {
				OSALTRACE(OSAL_ERROR, ("cannot write config xml file"));
				result = FALSE;
			}
		}
	}


    // Close XML
    FreeXmlData(xmlRoot);
	//swap the file
	pthread_mutex_lock(&g_swapfilemutex);
	rename(CONFIG_XMLFILE_TMP,CONFIG_XMLFILE);
	pthread_mutex_unlock(&g_swapfilemutex);
	pthread_mutex_unlock(&g_configmutex);


    return result;
}

BOOL OSAL_ConfigController_GetStrValue(const char *ignore, const char *config_name, char* value,UINT32 maxsize)
{
	BOOL result = FALSE;
	BOOL bXmlRead;
	pXmlElement xmlRoot, xmlTopElement, xmlTargetElement;
	const char *target_data;
	UINT32 data_size=0;

	if (config_name == NULL) {
		return result;
	}

	pthread_mutex_lock(&g_configmutex);
	
	// Open Config XML file
	xmlRoot = CreateEmptyXmlData();

	bXmlRead = ReadXmlFile(xmlRoot, CONFIG_XMLFILE);

	if (!bXmlRead) {
		OSALTRACE(OSAL_ERROR, ("cannot read config xml file"));
		pthread_mutex_unlock(&g_configmutex);
		return result;
	}
	// Find "config_name"
	xmlTopElement = FindChild(xmlRoot, CONFIG_INTEL_WIMAX);
	xmlTargetElement = FindChild(xmlTopElement, config_name);
	if (xmlTargetElement != NULL) 
	{
		target_data = GetElementInnerText(xmlTargetElement);
		data_size = strlen(target_data)+1;
		if (target_data != NULL)
		{
			if(data_size > maxsize -1){
				// Copy to the value
				memcpy(value, target_data, maxsize-1);
				// Added by Kalyan to make the value as a complete string 
				// and to avoid problems with strlen, strcpy on value without \0
				value[maxsize-1] = '\0';
			}
			else {
				memcpy(value, target_data, data_size);
			}
			result = TRUE;
			}
	}

	// Close XML
	FreeXmlData(xmlRoot);

	pthread_mutex_unlock(&g_configmutex);

	return result;
}

BOOL OSAL_ConfigController_SetStrValue(const char *ignore, LPSTR config_name, char *value)
{
    BOOL result = FALSE;
    BOOL bXmlRead, bSetInnerText, bXmlWrite;
    pXmlElement xmlRoot, xmlTopElement, xmlTargetElement;

    if (config_name == NULL) {
        return result;
    }

    pthread_mutex_lock(&g_configmutex);

    // Open Config XML file
    xmlRoot = CreateEmptyXmlData();

    bXmlRead = ReadXmlFile(xmlRoot, CONFIG_XMLFILE);

    if (!bXmlRead) {
		OSALTRACE(OSAL_ERROR, ("cannot read config xml file"));
		pthread_mutex_unlock(&g_configmutex);
        return result;
    }

    // Find "config_name"
    xmlTopElement = FindChild(xmlRoot, CONFIG_INTEL_WIMAX);
    xmlTargetElement = FindChild(xmlTopElement, config_name);
    if (xmlTargetElement != NULL) {
        bSetInnerText = SetElementInnerText(xmlTargetElement, value);
        if(bSetInnerText == TRUE) {
            // write to XML file
            bXmlWrite = WriteXmlFile(xmlTopElement, CONFIG_XMLFILE);
            if(bXmlWrite == TRUE) {
                result = TRUE;
            }
			else {
				OSALTRACE(OSAL_ERROR, ("cannot write config xml file"));
				result = FALSE;
        }
    }
	}


    // Close XML
    FreeXmlData(xmlRoot);

    //swap the file
	pthread_mutex_lock(&g_swapfilemutex);
	rename(CONFIG_XMLFILE_TMP,CONFIG_XMLFILE);
	pthread_mutex_unlock(&g_swapfilemutex);

    pthread_mutex_unlock(&g_configmutex);

    return result;
}

char *GetConfig_RootPath(void)
{
	int rc;
	static char answer[MAX_REGISTRY_ANSWER];
	char *rootPath = DEFAULT_ROOT_PATH;

    rc = OSAL_ConfigController_GetStrValue("ignore", KEY_ENTRY_ROOT_PATH, answer,MAX_REGISTRY_ANSWER);
	if (TRUE == rc) {
		rootPath = answer;
	}

	return rootPath;

}

BOOL GetConfig_NetworkConfigPath(char * configpath, int bufsize)
{
    int ret;
    char answer[MAX_REGISTRY_ANSWER] = {0};
    char *path = DEFAULT_NETWORK_CONFIG_PATH;

	if (configpath == NULL || bufsize <= 0) {
        return FALSE;
    }                     
    
    ret = OSAL_ConfigController_GetStrValue ("ignore", KEY_ENTRY_NETWORK_CONFIG_PATH, answer,MAX_REGISTRY_ANSWER);
    if (TRUE == ret) {
        path = answer;
    }
    
    OSAL_strcpy_s(configpath, bufsize, path);
       
    return TRUE;
}   

BOOL GetConfig_LogPath(char * logpath, int bufsize)
{   
    int ret;
    char answer[MAX_REGISTRY_ANSWER];
    char *path = DEFAULT_LOG_PATH;
    
	if (logpath == NULL || bufsize <= 0) {
        return FALSE;         
    }
    
    ret = OSAL_ConfigController_GetStrValue ("ignore", KEY_ENTRY_LOG_PATH, answer,MAX_REGISTRY_ANSWER);
    if (TRUE == ret) {
        path = answer;
    }
                           
    OSAL_strcpy_s(logpath, bufsize, path);   
    
    return TRUE;    
}         

BOOL GetConifg_InstrumentationLibName(char *libpath, int bufsize)
{
    if (libpath == NULL || bufsize <= 0)
    {
        return FALSE;
    }                     

    return OSAL_ConfigController_GetStrValue ("ignore", KEY_ENTRY_INSTRUMENTATION_LIB_NAME, libpath, bufsize);
}

BOOL OSAL_ConfigController_GetMultValues(const char* name_of_subkey, OSAL_VALENT *valent,UINT32 num_vals, char* buffer, UINT32 size)
{
	// TODO::OSAL-WORK::NON-CRITICAL BUT IMPORTANT - OSAL_ConfigController_GetMultValues - to be implementation
	return FALSE;	
}
