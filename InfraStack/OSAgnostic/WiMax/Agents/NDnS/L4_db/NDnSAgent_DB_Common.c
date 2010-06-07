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
#include "NDnSAgent_DB_Internal.h"
#include "wimax_osal_config_controler.h"
#include "L4ConfigurationManager.h"
#include "wimax_osal_services_cmn.h"

//This file includes the following method groups:
//		1. Init for all of the different structs
//		2. Alloc for "tag named" structs ((Allocates by setting a tag name))
//		3. Get for "tag named" structs ((Gets a struct according to its tag name)).
//		4. NAP ID handling methods
//		5. Generic methods to set different APDO type values.

int l4db_CompareString(const char *str1, const char *str2)
{
	int status=0;
	if(!str1 || !str2)
		return -1;
	else
	{
		if ((status = strcmp(str1, str2))==0)
		{
			//TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "l4db_CompareString: compared between 2 strings and got TRUE");
		}
		else 
		{
			//TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4db_CompareString: compared between 2 strings and got not the same.");
		}
		return status;
	}
		
}

/// <summary>
/// Returns true if the nspId exists in the DB and one of the subscribers is activated
/// </summary>
BOOL l4db_IsHomeNsp(wmx_NSPid_t nspID)
{
	pProvisionedNsp_t pFoundNsp;
	int i;	
	size_t tempStrLen = 0;

	//check if this NSP is provisioned
	pFoundNsp = l4db_GetProvisionedNspById(nspID);

	if(NULL == pFoundNsp)
	{
		//this NSP ID isn't provisioned		
		return FALSE;
	}

	//check if this is a home NSP == provisioned but not activated
	//check the primary subscription
	if(TRUE == pFoundNsp->subscriptionParams.primary.activated)
	{		
		return TRUE;
	}

	//check the other subscriptions
	for(i = 0 ; i < WMX_NSP_SUBSCRIBERS_MAX_NUM ; i++)
	{
		tempStrLen = OSAL_strnlen(pFoundNsp->subscriptionParams.other[i].tagName, MAX_TAG_NAME_SIZE);
		if(0 != tempStrLen && MAX_TAG_NAME_SIZE != tempStrLen)
		{
			if(TRUE == pFoundNsp->subscriptionParams.other[i].subscriberInfo.activated)
			{				
				return TRUE;
			}
		}
	}

	// Non of the subscribers was activated
	return FALSE;
}

// Copy the src NAP ID to the dst NAP ID
void l4db_CopyNapID(wmx_NAPid_t srcNapID, wmx_pNAPid_t pDstNapID)
{
	if (pDstNapID != NULL)
	{
		OSAL_memcpy_s(pDstNapID, sizeof(wmx_NAPid_t), srcNapID, sizeof(wmx_NAPid_t));
	}
}


/// <summary>
/// Sets the NAP ID to an empty one
/// </summary>
BOOL l4db_SetNapidEmpty(wmx_NAPid_t napID)
{
	BOOL rc = FALSE;

	if(napID)
	{
		napID[0] = (UINT8)L4DB_INVALID_INDEX;
		napID[1] = (UINT8)L4DB_INVALID_INDEX;
		napID[2] = (UINT8)L4DB_INVALID_INDEX;
		
		rc = TRUE;
	}
	return rc;
}



/// <summary>
/// Checks if two NAP IDs are equal
/// </summary>
BOOL l4db_IsNapidEqualEx(wmx_NAPid_t napID1,wmx_NAPid_t napID2, wmx_BsIdType_t napIdType)
{
	BOOL rc = FALSE;

	if(napID1 && napID2)
	{
		switch(napIdType)
		{
		case COMPRESSED_BSID:		
		case COMPRESSED_NAP:
			rc = (napID1[2] == napID2[2]);
			break;
		case FULL_BSID:		   
		case FULL_NAP:		  
		default:
			rc = ((napID1[0] == napID2[0]) &&
				(napID1[1] == napID2[1])&&
				(napID1[2] == napID2[2]));
			break;
		}
	}
	return rc;
}


/// <summary>
/// Checks if FULL two NAP IDs are equal
/// </summary>
BOOL l4db_IsNapidEqual(wmx_NAPid_t napID1,wmx_NAPid_t napID2)
{
	return l4db_IsNapidEqualEx(napID1, napID2, FULL_NAP);
}

/// <summary>
/// Converts NAPId int to a NAPId type
/// </summary>
/// <returns>void</returns>
void l4db_ConvertNapIdIntToNapIdType(wmx_NAPid_t pNapId,int IntNapId)
{
	UINT32 napID;

	if(NULL == pNapId)
	{
		return;
	}

	napID = IntNapId;

	pNapId[2] = (UINT8)(napID & 0xff);
	napID >>= 8;
	pNapId[1] = (UINT8)(napID & 0xff);

	napID >>= 8;
	pNapId[0] = (UINT8)(napID & 0xff);

}
/// <summary>
/// Converts NAPId type to a NAPId int
/// </summary>
/// <returns>void</returns>
void l4db_ConvertNapIdTypeToNapIdInt(wmx_NAPid_t pNapId, int * IntNapId)
{
	if(NULL == pNapId)
	{
		return;
	}

	*IntNapId = 0;

	*IntNapId |= pNapId[0];
	*IntNapId <<= 8;

	*IntNapId |= pNapId[1];
	*IntNapId <<= 8;

	*IntNapId |= pNapId[2];
}

/// <summary>
/// Converts NAPId string to NAPId
/// </summary>
/// <returns>void</returns>
void l4db_ConvertNapIdStrToNapIdType(wmx_NAPid_t pNapId, const char *str)
{
	UINT32 napID;

	if((NULL == pNapId) || (NULL == str))
	{
		return;
	}

	OSAL_sscanf_s(str, "%x", &napID);
	l4db_ConvertNapIdIntToNapIdType(pNapId,napID);
}
/// <summary>
/// Converts NAPId value to string
/// </summary>
/// <returns>void</returns>
void l4db_ConvertNapIdToStr(wmx_NAPid_t pNapId, char *str)
{
	UINT32 napID;


	if((NULL == pNapId) || (NULL == str))
	{
		return;
	}

	napID = 0;

	napID = pNapId[0];
	napID <<= 8;
	napID |= pNapId[1];
	napID <<= 8;
	napID |= pNapId[2];

	OSAL_itoa_s(napID, str, 10, 16);

}


/// <summary>
/// Converts a bollean value from string to BOOL
/// </summary>
UINT8 l4db_ConvertToBoolVal(const char* val)
{
	if((FALSE == l4db_CompareString(val, L4DB_XML_TRUE_STR)) ||
		(FALSE == l4db_CompareString(val, L4DB_XML_ONE_STR)))
	{
		return TRUE;
	} 
	else
	{
		return FALSE;
	}
}

/// <summary>
/// Returns TRUE if the NSP ID== NAP ID bit is set
/// </summary>
/// <param name="napID">(IN) napID to check</<param>
BOOL l4db_TestNapIdNspIdBit(wmx_BSid_t bsID)
{
	if ((bsID[4] & 0x80) > 0) // The msb of the 4th byte
	{
		return TRUE;
	}
	
	return FALSE;
}

/// <summary>
/// Returns TRUE if the NAP ID== NSP ID bit is set and the IDs are equal
/// </summary>
/// <param name="napID">(IN) napID to compare</<param>
/// <param name="nspID">(IN) nspID to compare</<param>
BOOL l4db_CompareNapIdNspId(wmx_BSid_t bsID, wmx_NSPid_t nspID)
{
	int napIdInt;

	if (l4db_TestNapIdNspIdBit(bsID) == TRUE)
	{
		l4db_ConvertNapIdTypeToNapIdInt(bsID, &napIdInt); // Take only the first 3 bytes

		if (nspID == (wmx_NSPid_t)napIdInt)
		{
			return TRUE;
		}
	}

	return FALSE;
}

/// <summary>
/// Copy string value from psDst to psSrc or otherwise according to cmd
/// </summary>
/// <param name="psDst">first string
/// <param name="len">length of buffer to copy to
/// <param name="psSrc">second string
/// <param name="pBufferSize"> INOUT pointer for second string length. 
//    If it's get command the function will set the length of the output string. If command is != GET the parm can be NULL
/// <param name="APDOType"> should be APDO_String!!!!
/// <param name="cmd"> if cmd is "GET" we will copy SRC->DST otherwise we will copy DST->SRC
/// <returns>wmx_Status_t</returns>
wmx_Status_t l4db_SetStringValueNew(char *pDBData,
									size_t DbLen,
									char *psSrc,
									int *pSrcSize, 
									wmx_pAPDOType_t pAPDOType,
									apdo_DbCmd_t cmd)
{
	wmx_Status_t rc = WMX_ST_FAIL;

	if((NULL == pDBData) || (NULL == psSrc))
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4db_SetStringValueNew pDBData or str are NULL");
		return WMX_ST_FAIL;
	}

	switch(cmd)
	{
	case APDO_AddCmd:     // DB Add command
	case APDO_UpdateCmd:    // DB update command

		if(NULL == pAPDOType)
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4db_SetStringValueNew pAPDOType is NULL");
			return WMX_ST_FAIL;
		}
		if (APDO_String != *pAPDOType)
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4db_SetStringValueNew pAPDOType is not an APDO_String");
			return WMX_ST_FAIL;
		}
		if(DbLen <= (size_t)OSAL_strnlen(psSrc, MAX_STRING_VALIDATE))//TODO - change this after we stop passing dummystrlen
		{
			//buffer is to small
			return WMX_ST_FAIL;
		}

		OSAL_strncpy_s(pDBData, DbLen, psSrc, *pSrcSize);
		pDBData[DbLen -1 ]= '\0';
		rc = WMX_ST_OK;
		break;

	case APDO_GetCmd:    // DB get command

		if((NULL == pAPDOType) || (NULL == pSrcSize))
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4db_SetStringValueNew pAPDOType or pSrcSize are NULL");
			return WMX_ST_FAIL;
		}
		OSAL_strncpy_s(psSrc, *pSrcSize, pDBData, DbLen);
		psSrc[*pSrcSize -1 ]='\0';
		*pSrcSize = (UINT32)OSAL_strnlen(psSrc, MAX_STRING_VALIDATE);
		*pAPDOType = APDO_String;
		rc = WMX_ST_OK;
		break;

	case APDO_DeleteCmd:    // DB delete command

		pDBData[0] = '\0';
		rc = WMX_ST_OK;
		break;
	}
	return rc;
}

/// <summary>
/// According of command will copy string->int or int->string
/// </summary>
/// <param name="psDst"> String value
/// <param name="pdwInt"> pointer to int value
/// <param name="pDstSize"> INOUT pointer for second string length. 
//    If it's get command the function will set the length of the output string. If command is != GET the parm can be NULL
/// <param name="cmd"> if cmd is "GET" we will copy psDst->pdwInt otherwise we will copy pdwInt->psDst
/// <returns>wmx_Status_t</returns>
wmx_Status_t l4db_SetIntegerValueNew(int *pDBData,
									 int *pDstSize,
									 int *pdwInData,
									 wmx_pAPDOType_t pAPDOType,
									 apdo_DbCmd_t cmd)
{
	int sizeOfArg = sizeof(int);
	wmx_Status_t rc = WMX_ST_FAIL;

	if((NULL == pDBData) || (NULL == pdwInData))
	{			
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4db_SetIntegerValueNew pDBData or pdwInData are NULL");
		return rc;
	}

	switch(cmd)
	{
	case APDO_AddCmd:     // DB Add command
	case APDO_UpdateCmd:    // DB update command

		if((NULL == pAPDOType) || ((*pAPDOType != APDO_Integer) && (*pAPDOType != APDO_String)))
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4db_SetIntegerValueNew pAPDOType is NULL or not APDO_Integer");
			return rc;
		}

		if(*pAPDOType == APDO_Integer)
		{
			*pDBData = *pdwInData;
		}
		else //redbend support only strings
		{
			*pDBData = atoi((char*)pdwInData);
		}

		rc = WMX_ST_OK;
		break;

	case APDO_GetCmd:    // DB get command

		if((NULL == pAPDOType) || (NULL == pDstSize))
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4db_SetIntegerValueNew pAPDOType or pDstSrcSize are NULL");
			return rc;
		}
		if(*pDstSize >= sizeOfArg)
		{
			*pAPDOType = APDO_Integer;
			*pDstSize = sizeOfArg;
			*pdwInData = *pDBData;
			rc = WMX_ST_OK;
		}
		break;

	case APDO_DeleteCmd:    // DB delete command
		*pDBData = 0;
		rc = WMX_ST_OK;
		break;
	}
	return rc;
}

/// <summary>
/// According of command will copy string->double or double->string
/// </summary>
/// <param name="psDst"> String value
/// <param name="pDstSize"> INOUT pointer for second string length. 
//    If it's get command the function will set the length of the output string. If command is != GET the parm can be NULL
/// <param name="pdwDouble"> pointer to double value
/// <param name="cmd"> if cmd is "GET" we will copy psDst->pdwDouble otherwise we will copy pdwDouble->psDst
/// <returns>wmx_Status_t</returns>
wmx_Status_t l4db_SetDoubleValueNew(double	*pDBData,
									int		*pDstSize,
									double	* pdwInData,
									wmx_pAPDOType_t pAPDOType,
									apdo_DbCmd_t cmd)
{
	int sizeOfArg = sizeof(double);
	wmx_Status_t rc = WMX_ST_FAIL;

	if((NULL == pDBData) || (NULL == pdwInData))
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4db_SetDoubleValueNew pDBData or pdwInData are NULL");
		return rc;
	}

	switch(cmd)
	{
		case APDO_AddCmd:     // DB Add command
		case APDO_UpdateCmd:    // DB update command

			if((NULL == pAPDOType) || (*pAPDOType != APDO_Double))
			{
				TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4db_SetDoubleValueNew pAPDOType is NULL or not APDO_Double");
				return rc;
			}

			*pDBData = *pdwInData;
			rc = WMX_ST_OK;
			break;

		case APDO_GetCmd:    // DB get command

			if((NULL == pAPDOType) || (NULL == pDstSize))
			{
				TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4db_SetDoubleValueNew pAPDOType or pDstSize are NULL");
				return rc;
			}
			if(*pDstSize >= sizeOfArg)
			{
				*pAPDOType = APDO_Double;
				*pDstSize = sizeOfArg;
				*pdwInData = *pDBData;
				rc = WMX_ST_OK;
			}
			break;

		case APDO_DeleteCmd:    // DB delete command
			*pDBData = 0;
			rc = WMX_ST_OK;
			break;
	}
	return rc;

}

/// <summary>
/// According of command will copy string->bool or bool->string
/// </summary>
/// <param name="psDst"> String value
/// <param name="pDstSize"> INOUT pointer for second string length. 
//    If it's get command the function will set the length of the output string. If command is != GET the parm can be NULL
/// <param name="pdwBool"> pointer to BOOL value
/// <param name="cmd"> if cmd is "GET" we will copy psDst->pdwBool otherwise we will copy pdwBool->psDst
/// <returns>wmx_Status_t</returns>
wmx_Status_t l4db_SetBoolValueNew(BOOL *pDBData,
								  int   *pDstSize,
								  BOOL* pdwInData,
								  wmx_pAPDOType_t pAPDOType,
								  apdo_DbCmd_t cmd)
{
	int sizeOfArg = sizeof(BOOL);
	wmx_Status_t rc = WMX_ST_FAIL;

	if((NULL == pDBData) || (NULL == pdwInData))
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4db_SetBoolValueNew pDBData or pdwInData are NULL");
		return rc;
	}

	switch(cmd)
	{
		case APDO_AddCmd:     // DB Add command
		case APDO_UpdateCmd:    // DB update commandm

			if((NULL == pAPDOType) || ((*pAPDOType != APDO_Bool) && (*pAPDOType != APDO_String)))
			{
				TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4db_SetBoolValueNew pAPDOType is NULL or not APDO_Bool");
				return rc;
			}

			if(*pAPDOType == APDO_Bool)
			{
				*pDBData = *pdwInData;
			}
			else
			{
				*pDBData = l4db_ConvertToBoolVal((const char *)pdwInData);
			}

			rc = WMX_ST_OK;
			break;

		case APDO_GetCmd:    // DB get command
				
				if((NULL == pAPDOType) || (NULL == pDstSize))
				{
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4db_SetBoolValueNew pAPDOType or pDstSize are NULL");
					return rc;
				}
				if(*pDstSize >= sizeOfArg)
				{
					*pAPDOType = APDO_Bool;
					*pDstSize = sizeOfArg;
					*pdwInData = *pDBData;
					rc = WMX_ST_OK;
				}
				break;

		case APDO_DeleteCmd:    // DB delete command
			*pDBData = 0;
			rc = WMX_ST_OK;
			break;
	}
	return rc;
}

/// <summary>
/// According of command will copy string->double or double->string
/// </summary>
/// <param name="psDst"> String value
/// <param name="pDstSize"> INOUT pointer for second string length. 
//    If it's get command the function will set the length of the output string. If command is != GET the parm can be NULL
/// <param name="pdwDouble"> pointer to double value
/// <param name="cmd"> if cmd is "GET" we will copy psDst->pdwDouble otherwise we will copy pdwDouble->psDst
/// <returns>pointer for wmx_pNSPFullData_t which we allocated or NULL if error </returns>
wmx_Status_t l4db_SetFloatValueNew(float	*pDBData,
								   int		*pDstSize,
								   float	* pdwInData,
								   wmx_pAPDOType_t pAPDOType,
								   apdo_DbCmd_t cmd)
{
	int sizeOfArg = sizeof(float);
	wmx_Status_t rc = WMX_ST_FAIL;

	if((NULL == pDBData) || (NULL == pdwInData))
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4db_SetFloatValueNew pDBData or pdwInData are NULL");
		return rc;
	}

	switch(cmd)
	{
		case APDO_AddCmd:     // DB Add command
		case APDO_UpdateCmd:    // DB update command

			if((NULL == pAPDOType) || (*pAPDOType != APDO_Bool))
			{
				TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4db_SetFloatValueNew pAPDOType is NULL or not APDO_Float");
				return rc;
			}

			*pDBData = *pdwInData;
			rc = WMX_ST_OK;
			break;

		case APDO_GetCmd:    // DB get command
			
			if((NULL == pAPDOType) || (NULL == pDstSize))
			{
				TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4db_SetFloatValueNew pAPDOType or pDstSize are NULL");
				return rc;
			}

			if(*pDstSize >= sizeOfArg)
			{
				*pAPDOType = APDO_Float;
				*pDstSize = sizeOfArg;
				*pdwInData = *pDBData;
				rc = WMX_ST_OK;
			}
			break;

		case APDO_DeleteCmd:    // DB delete command
			*pDBData = 0;
			rc = WMX_ST_OK;
			break;
	}
	return rc;
}


/// <summary>
/// Converts UINT32 value to BOOL string
/// </summary>
/// <returns>pointer to "True" or "False" string</returns>
void l4db_GetBoolStr(BOOL value, char * boolStr)
{
	if(TRUE == value)
	{
		OSAL_strcpy_s(boolStr, strlen(L4DB_XML_TRUE_STR) + 1, L4DB_XML_TRUE_STR);
	}
	else
	{
		OSAL_strcpy_s(boolStr, strlen(L4DB_XML_FALSE_STR) + 1, L4DB_XML_FALSE_STR);
	}
}


/// <summary>
/// Get tokens from input path
/// </summary>
/// <param name="psPath">(IN) pointer to current place in path
/// <param name="psToken">(OUT) output of token string (if we found)
/// <param name="psTokenValue">(OUT) output of token value (if we found)
/// <returns>pointer for next place in path </returns>
char* l4db_GetTokensFromPath(IN char *psPath, 
							  char** psToken,
							  char** psTokenValue)
{
	// here is example of valid path
	// "/NSP/2/NetworkParameters/NSP_name=Sprint/"
	int i = 0;
	char* nextPath = NULL;

	if((NULL == psToken) || (NULL == psTokenValue))
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4db_GetTokensFromPath psToken or psTokenValue are NULL");
		return nextPath;
	}
	*psToken = C_L4DB_EMPTY_STRING;
	*psTokenValue = C_L4DB_EMPTY_STRING;

	if(NULL == psPath)
	{
		return NULL;
	}

	while(psPath[i] == '/') 
	{
		i++;
	}

	// Set the token pointer
	*psToken = &psPath[i];

	while(psPath[i] && (psPath[i] != '/'))
	{
		if(psPath[i] == '=')
		{
			// we found valType
			psPath[i] = '\0';
			i++;
			// set value of token value
			*psTokenValue = &psPath[i];
		}
		i++;
	}
	if(psPath[i] == '/')
	{
		psPath[i] = '\0';
		i++;
		nextPath = &psPath[i];
	}

	if((NULL != nextPath) && (0 == nextPath[0]))
	{
		nextPath = NULL;
	}

	return nextPath;
}

/// <summary>
/// Init a channel info with default values
/// </summary>
void l4db_InitChannelInfo(pChannelInfo_t pChannelInfo)
{
	//init the tag name
	pChannelInfo->tagName[0] = '\0';
    pChannelInfo->id[0] = '\0';
	pChannelInfo->bw = L4DB_INVALID_INDEX;
	pChannelInfo->duplexMode = (wmx_DuplexMode_t)L4DB_INVALID_INDEX;
	pChannelInfo->fft = (UINT32)L4DB_INVALID_INDEX;
	pChannelInfo->firstFreq = (UINT32)L4DB_INVALID_INDEX;
	pChannelInfo->lastFreq = (UINT32)L4DB_INVALID_INDEX;
	pChannelInfo->nextFreq = 10000; //(wmx_NextFreqStep_t)L4DB_INVALID_INDEX;
	pChannelInfo->ttl = 0;
	pChannelInfo->lastFoundInNbrAdv = FALSE;

	memset(pChannelInfo->preambleBitmap, 0xFF, PREAMBLES_LENGTH);
}
/// <summary>
/// Init a channel plan with default values
/// </summary>
void l4db_InitChannelPlan(pChannelPlan_t pChannelPlan)
{
	int i;

	for(i = 0 ; i < WMX_CHANNELS_MAX_NUM ; i++)
	{
		l4db_InitChannelInfo(&pChannelPlan->channels[i]);
	}
	for(i = 0 ; i < WMX_CHANNELS_MAX_NUM ; i++)
	{
		pChannelPlan->linkQuality[i] = 0;
	}
	pChannelPlan->bw = L4DB_INVALID_INDEX;
	pChannelPlan->fft = L4DB_INVALID_INDEX;
	pChannelPlan->duplexMode = (wmx_DuplexMode_t)L4DB_INVALID_INDEX;
	pChannelPlan->channelsSize = 0;
}
/// <summary>
/// Init a channel ref with default values
/// </summary>
void l4db_InitChannelRef(pChPlanRefId_t pChannelRef)
{
	pChannelRef->id[0] = '\0';
	pChannelRef->tagName[0] = '\0';
}
/// <summary>
/// Init a NAP with default values
/// </summary>
void l4db_InitNap(pL4db_Nap_t pNap)
{
	int i;

	//set the NAP id to an empty Id
	l4db_SetNapidEmpty((wmx_pNAPid_t)&pNap->napID);

	//init the priority
	pNap->priority = (wmx_Priority_t)L4DB_INVALID_INDEX;
	
	//init the tag name
	pNap->tagName[0] = '\0';

	//init the change count
	pNap->changeCount = (UINT32)L4DB_INVALID_INDEX;

	//init the channel plan
	for(i = 0 ; i < WMX_CHANNELS_MAX_NUM ; i++)
	{
		l4db_InitChannelRef(&pNap->channelPlanRefIds[i]);
	}
	
	pNap->channelRefsSize = 0;

	//init the channel plan
	l4db_InitChannelPlan(&pNap->discoveredChannelPlan);
}

/// <summary>
/// Init a roaming info with default values
/// </summary>
void l4db_InitRoamingInfo(pRoamingPartnerInfo_t pRoamingInfo)
{
	//init the tag name
	pRoamingInfo->tagName[0] = '\0';

	//init the V_NSP ID
	pRoamingInfo->vNspID = (wmx_NSPid_t)L4DB_INVALID_INDEX;
	pRoamingInfo->priority = (wmx_Priority_t)L4DB_INVALID_INDEX;
}

/// <summary>
/// Init an srv realm with default values - NOT SUPPORTED NOW
/// </summary>
void l4db_InitSrvRealm(pSrvRealm_t pSrvRealm)
{
	//init the tag name
	pSrvRealm->tagName[0] = '\0';
	pSrvRealm->srvRealm[0] = '\0';
}

/// <summary>
/// Init a cert info with default values
/// </summary>
void l4db_InitCertInfo(pCert_t	pCert)
{
	//init the tag name
	pCert->tagName[0] = '\0';

	//pCert->certType = L4DB_INVALID_INDEX;
	pCert->certType[0] = '\0'; 
	pCert->serNum[0] = '\0';
	pCert->issuer[0] = '\0';
	//pCert->thumbPrint = (UINT32)L4DB_INVALID_INDEX; //NOT SUPPORTED NOW
}

/// <summary>
/// Init an EAP info with default values
/// </summary>
void l4db_InitEapInfo(pEAP_t pEap)
{
	int i;

	pEap->tagName[0] = '\0'; 

	pEap->id[0] = '\0';

	pEap->provisionedPseudoId[0] = '\0';

	pEap->vendorId = (UINT32)L4DB_INVALID_INDEX;

	pEap->vendorType = (UINT32)L4DB_INVALID_INDEX;

	pEap->EAPMethod = (UINT32)L4DB_INVALID_INDEX;

	pEap->encaps = (UINT32)L4DB_INVALID_INDEX;

	pEap->id[0] = '\0';

	pEap->Password[0] = '\0';

	pEap->realm[0] = '\0';

	pEap->usePrivacy = FALSE;

	pEap->vfySrvRealm = L4DB_INVALID_INDEX; 

	//init the srv realms - NOT SUPPORTED NOW
	for(i = 0 ; i < MAX_NUM_OF_SRV_REALMS ; i++)
	{
		l4db_InitSrvRealm(&pEap->srvRealms[i]);
	}

	pEap->srvRealmsSize = 0;

	for(i = 0 ; i < MAX_NUM_OF_CERTS ; i++)
	{
		l4db_InitCertInfo(&pEap->certs[i]);
	}

	pEap->certsSize = 0;
}

/// <summary>
/// Init a primary subscription info with default values
/// </summary>
void l4db_InitPrimarySubscription(pSubscriberInfo_t pSubscriptionInfo)
{
	int i;

	pSubscriptionInfo->name[0] = '\0';

	pSubscriptionInfo->activated = FALSE;

	for(i = 0 ; i < MAX_NUM_OF_EAP_METHODS ; i++)
	{
		l4db_InitEapInfo(&pSubscriptionInfo->eapInfo[i]);
	}

	pSubscriptionInfo->eapInfoSize = 0;
}

/// <summary>
/// Init a primary subscription info with default values
/// </summary>
void l4db_InitOtherSubscription(pOtherSubsInfo_t pSubscriptionInfo)
{
	int i;

	//init the tag name
	pSubscriptionInfo->tagName[0] = '\0';

	pSubscriptionInfo->subscriberInfo.name[0] = '\0';

	pSubscriptionInfo->subscriberInfo.activated = FALSE;

	//init the EAP entries
	for(i = 0 ; i < MAX_NUM_OF_EAP_METHODS ; i++)
	{
		l4db_InitEapInfo(&pSubscriptionInfo->subscriberInfo.eapInfo[i]);
	}

	pSubscriptionInfo->subscriberInfo.eapInfoSize = 0;
}

/// <summary>
/// Init the subscription parameters
/// </summary>
void l4db_InitSubscriptionParams(pSubscriptionParams_t pSubscriptionParams)
{
	int i;

	l4db_InitPrimarySubscription(&pSubscriptionParams->primary);

	//init the other subscription
	for(i = 0 ; i < WMX_NSP_SUBSCRIBERS_MAX_NUM ; i++)
	{
		l4db_InitOtherSubscription(&pSubscriptionParams->other[i]);
	}

	pSubscriptionParams->otherSize = 0;
}

/// <summary>
/// Init HNSP with default values
/// </summary>
void l4db_InitHnsp(pHomeNsp_t pHnsp)
{
	//set the H NSP ID's to an invalid value
	pHnsp->nspId = (wmx_NSPid_t) L4DB_INVALID_INDEX;
	pHnsp->tagName[0] = '\0';
}
/// <summary>
/// Init RAPL params with default values
/// </summary>
void l4db_InitRapl(pRapl_t pRapl)
{
	int i;

	for(i = 0 ; i < MAX_ROAMING_PARTNERS ; i++)
	{
		l4db_InitRoamingInfo(&pRapl->roamingPartners[i]);
	}

	pRapl->roamingPartnersSize = 0;
	pRapl->any = ListFirst;
	pRapl->selectPolicy = spStrict;
}
/// <summary>
/// Init capl with default values
/// </summary>
void l4db_InitCapl(pCapl_t pCapl)
{
	int i;

	for(i = 0 ; i < WMX_NAPS_MAX_NUM ; i++)
	{
		l4db_InitNap(&pCapl->naps[i]);
	}

	pCapl->napsSize = 0;
	pCapl->any = ListFirst;
	pCapl->selectPolicy = spStrict;
}
/// <summary>
/// Init NW params with default values
/// </summary>
void l4db_InitNwParams(pNwParams_t pNwParams)
{
	int i;

	//sets the NSPs names to be an empty string
	pNwParams->provisionedName[0] = '\0';
	pNwParams->name16g[0] = '\0';
	pNwParams->serverID[0] = '\0';

	//Init H NSPs
	for(i = 0 ; i < WMX_NSP_IDS_MAX_NUM ; i++)
	{
		l4db_InitHnsp(&	pNwParams->hNsps[i]);
	}

	pNwParams->hNspsSize = 0;

	//init the default channel plan
	l4db_InitChannelPlan(&pNwParams->channelPlan);

	//init the CAPL
	l4db_InitCapl(&pNwParams->capl);

	//init the RAPL
	l4db_InitRapl(&pNwParams->rapl);

	//init the polling interval
	pNwParams->pollingInterval = -1; //the device SHALL perform ONLY ONE client initiated management session to the 
									 //OMA-DM server, following the time the device obtains an IP address from the operator�s network.

	pNwParams->pollingAttempts = 10; // If polling attempts will be enabled we use this value to do 10 retries for client initiated.
}

/// <summary>
/// Init one Contact info with default values
/// </summary>
void l4db_InitContactInfo(pContactsInfo_t pContactInfo)
{
	pContactInfo->uri[0] = '\0';

	pContactInfo->text[0] = '\0';

	pContactInfo->tagName[0] = '\0';

	pContactInfo->uriType = (UINT32)L4DB_INVALID_INDEX;
}

/// <summary>
/// Init pNSP with default values
/// </summary>
void l4db_InitNsp(pProvisionedNsp_t pNsp)
{
	int i;

	memset(pNsp, 0x0, sizeof(*pNsp));

	//state the this NSP has been initialized
	pNsp->fIsAllocated = TRUE;

	pNsp->tagName[0] = '\0';

	l4db_InitNwParams(&pNsp->nwParams);

	//init the contacts
	for(i = 0 ; i < MAX_NUM_OF_CONTACTS ; i++)
	{
		l4db_InitContactInfo(&pNsp->contacts[i]);
	}

	//init the primary subscription info
	l4db_InitPrimarySubscription(&pNsp->subscriptionParams.primary);

	//init the other subscription
	for(i = 0 ; i < WMX_NSP_SUBSCRIBERS_MAX_NUM ; i++)
	{
		l4db_InitOtherSubscription(&pNsp->subscriptionParams.other[i]);
	}

	pNsp->subscriptionParams.otherSize = 0;
}


/// <summary>
/// Init a 16g NSP info struct
/// </summary>
void l4db_InitNsp16gInfo(pNspInfo_16G pNsp16gInfo)
{
	pNsp16gInfo->name[0] = '\0';
	pNsp16gInfo->nspID = (wmx_NSPid_t)L4DB_INVALID_INDEX;
	pNsp16gInfo->visitedRealm[0] = '\0';
}

/// <summary>
/// Init a discovered NAP
/// </summary>
void l4db_InitDiscoveredNap(pDiscoveredNap_t pNap)
{
	int i;

	//set the NAP ID to be an empty ID
	l4db_SetNapidEmpty((wmx_pNAPid_t)&pNap->napID);

	pNap->isLastDetected = FALSE;	

	//set all NSP IDs to an invalid index
	for(i = 0 ; i < ARRAY_SIZE(pNap->nspInfo) ; i++)
	{
		l4db_InitNsp16gInfo(&pNap->nspInfo[i]);
	}

	//init the change count
	pNap->changeCount = (UINT32)L4DB_INVALID_INDEX;

	pNap->nspInfoSize = 0;	

	//init the channel plan
	l4db_InitChannelPlan(&pNap->channelPlan);
}


/// <summary>
/// Init the general Nds settings
/// </summary>
void l4db_InitGeneralSettings(pNdsSettings_t pSettings)
{
	int i;

	//Init the unprovisioned profiles
	for(i = 0 ; i < MAX_NUM_OF_RECENT_NSPS ; i++)
	{		
		pSettings->unprovisionedProfiles[i].nspID = (wmx_NSPid_t)L4DB_INVALID_INDEX;
		l4db_SetNapidEmpty((wmx_pNAPid_t)&pSettings->unprovisionedProfiles[i].napID);
		l4db_InitChannelPlan((pChannelPlan_t)&pSettings->unprovisionedProfiles[i].channelPlan);
	}

	//set the recent NSP size to zero
	pSettings->unprovisionedProfilesSize = 0;

	pSettings->lastConnectedNSP.recentNspID = (wmx_NSPid_t)L4DB_INVALID_INDEX;
	pSettings->lastConnectedNSP.numOfConnectedNapIDs = 0;

	//init the link loss params
	pSettings->longLinkLossParams.repetition = L4DB_INVALID_INDEX;
	pSettings->longLinkLossParams.time = (UINT32)L4DB_INVALID_INDEX;
	pSettings->shortLinkLossParams.repetition = L4DB_INVALID_INDEX;
	pSettings->shortLinkLossParams.time = (UINT32)L4DB_INVALID_INDEX;

	//set default values
	pSettings->connectMode = UserManScanManConnect;
	pSettings->swRfState   = Off;
	pSettings->allowAutoActivate = FALSE;
	pSettings->allowFastReconnect = TRUE;
	pSettings->thCriteria.cinrTH = (wmx_CinrThreshold_t)L4DB_INVALID_INDEX;
	pSettings->thCriteria.rssiTH = (wmx_RssiThreshold_t)L4DB_INVALID_INDEX;	
	pSettings->roamingMode = UserEnableRoaming;
	pSettings->currentPreferredNSP = (wmx_NSPid_t)L4DB_INVALID_INDEX;
	pSettings->setPreferredNspOnConnect = FALSE;
}

/// <summary>
/// Init the device certificates
/// </summary>
void l4db_InitDeviceCerts(pDeviceCertificates_t pDeviceCerts)
{
	pDeviceCerts->clientCert[0] = '\0';
	pDeviceCerts->privateKey[0] = '\0';
	pDeviceCerts->rootCert[0] = '\0';
}

/// <summary>
/// Init the dev detail struct
/// </summary>
void l4db_InitDevDetail(pDevDetail_t pDevDetail)
{
	BOOL res;
	// Nardimon - add get devtype from registry
	OSAL_strncpy_s(pDevDetail->devType, (sizeof(char)*MAX_DEV_TYPE_SIZE),"Nothing", (7*sizeof(char)));
	res = L4Configurations_getApdoDevDetailsDevType(pDevDetail->devType);
	if (!res || strcmp(pDevDetail->devType, "Nothing"))
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "---- DevType RegPatch ---- l4db_InitDevDetail - L4Configurations_getApdoDevDetailsDevType returned [%d]. with value [%s]. Using default - Laptop ---- DevType RegPatch ---- ",res,pDevDetail->devType);
		OSAL_strncpy_s(pDevDetail->devType, (sizeof(char)*MAX_DEV_TYPE_SIZE),"Laptop", (6*sizeof(char)));
	}
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "---- DevType RegPatch ---- l4db_InitDevDetail - L4Configurations_getApdoDevDetailsDevType returned [%d]. with Value [%s] ---- DevType RegPatch ---- ",res,pDevDetail->devType);
	pDevDetail->fwVersion[0] = '\0';
	pDevDetail->swVersion[0] = '\0';
	pDevDetail->hwVersion[0] = '\0';		
	pDevDetail->ext.SwV2[0] = '\0';
	OSAL_strncpy_s(pDevDetail->uri.MaxDepth, MAX_DEV_DETAIL_URI_FIELD_SIZE, "0", 2);
	OSAL_strncpy_s(pDevDetail->uri.MaxTotLen, MAX_DEV_DETAIL_URI_FIELD_SIZE, "0", 2);
	OSAL_strncpy_s(pDevDetail->uri.MaxSegLen, MAX_DEV_DETAIL_URI_FIELD_SIZE, "0", 2);
	OSAL_strncpy_s(pDevDetail->lrgObj, MAX_BOOL_VAL_SIZE, L4DB_XML_FALSE_STR, OSAL_strnlen(L4DB_XML_FALSE_STR, MAX_BOOL_VAL_SIZE - 1));
}

/// <summary>
/// Init the dev info struct
/// </summary>
void l4db_InitDevInfo(pDevInfo_t pDevInfo)
{
	OSAL_memcpy_s(pDevInfo->manufacturer, MAX_MAN_NAME_SIZE, DEFAULT_DEV_INFO_MAN, 
		sizeof(DEFAULT_DEV_INFO_MAN));	
	OSAL_memcpy_s(pDevInfo->model, MAX_MOD_NAME_SIZE, DEFAULT_DEV_INFO_MOD, 
		sizeof(DEFAULT_DEV_INFO_MOD));	
	
	pDevInfo->devID[0] = '\0';
}

/// <summary>
/// Init the dev info struct
/// </summary>
void l4db_InitWimaxRadioModule(pWmxRadioModule_t pWmxRadioModule)
{
	pWmxRadioModule->tagName[0] = '\0';
	pWmxRadioModule->productVersions.fwVersion[0] = '\0';
	pWmxRadioModule->productVersions.swVersion[0] = '\0';
	pWmxRadioModule->productVersions.hwVersion[0] = '\0';
	pWmxRadioModule->macAddress[0] = '\0';
	pWmxRadioModule->productVersions.manufacturer[0] = '\0';
	pWmxRadioModule->productVersions.model[0] = '\0';

	//SPLock
	pWmxRadioModule->spLock.lockStatus = TRUE;
	pWmxRadioModule->spLock.operatorName[0] = '\0';
	pWmxRadioModule->spLock.lock[0] = '\0';
}

/// <summary>
/// Init the wimax struct
/// </summary>
void l4db_InitWimax(pWimax_t pWimax)
{
	int i;
	BOOL res;

	for(i = 0 ; i < MAX_NUM_OF_WIMAX_RADIO_MOD ; i++)
	{
		l4db_InitWimaxRadioModule(&pWimax->radioModules[i]);
	}

	// Init with one default radio module	
	OSAL_strncpy_s(pWimax->radioModules[0].tagName, MAX_TAG_NAME_SIZE, DEFAULT_RADIO_MODULE_NODE, 
		strlen(DEFAULT_RADIO_MODULE_NODE));
	
	pWimax->radioModules[0].productVersions.manufacturer[0] = '\0';
	pWimax->radioModules[0].macAddress[0] = '\0';
	pWimax->radioModules[0].productVersions.model[0] = '\0';

	pWimax->wmxRadioModulesSize = 1;

	pWimax->terminalEquipment.devId[0] = '\0';
	OSAL_strncpy_s(pWimax->terminalEquipment.devType, MAX_DEV_TYPE_SIZE, DEFAULT_DEV_TYPE, sizeof(DEFAULT_DEV_TYPE));	

	pWimax->terminalEquipment.productVersions.fwVersion[0] = '\0';	
	pWimax->terminalEquipment.productVersions.hwVersion[0] = '\0';
	pWimax->terminalEquipment.productVersions.manufacturer[0] = '\0';
	pWimax->terminalEquipment.productVersions.model[0] = '\0';
	
	
	pWimax->devCap.updateMethods.clientInitiated.pollingSupported = TRUE;
	pWimax->devCap.updateMethods.clientInitiated.pollingInterval = 1;
	pWimax->devCap.updateMethods.clientInitiated.pollingAttempts = 10;

	// Init SW version with OS version
	res = OSAL_GetOSVersion(pWimax->terminalEquipment.productVersions.swVersion);	

	if (!res)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4db_InitWimax - Failed to build OS version string.");
	}
}

/// <summary>
/// Init the FUMO section
/// </summary>
void l4db_InitFumoNode(pFumoParams_t pFumoParams)
{
	memset(pFumoParams, 0x0, sizeof(*pFumoParams));

	//state the this NSP has been initialized
	pFumoParams->fIsAllocated = TRUE;
	pFumoParams->tagName[0] = '\0';


	// MZUR TODO Completer init
	pFumoParams->pkgName[0] = '\0';
	pFumoParams->pkgVersion[0] = '\0';
	pFumoParams->downloadAndUpdatePkgURL[0] = '\0';
	pFumoParams->downloadPkgURL[0] = '\0';

	pFumoParams->state = dsDownloadIdle;

}

/// <summary>
/// Init the FUMO internal section
/// </summary>
void l4db_InitFumoInternalNode(pFumoInternalParams_t pFumoInternalParams)
{
	pFumoInternalParams->fumoNodePath[0] = '\0';
	pFumoInternalParams->pkgFileName[0] = '\0';
	pFumoInternalParams->pkgPath[0] = '\0';
	pFumoInternalParams->fumoOperation = 0;

}

/// <summary>
/// Init the APDO internal parameters section
/// </summary>
void l4db_InitAPDOInternalParametersNode(pAPDOInternalParams_t pAPDOInternalParams)
{
	int i;

	l4db_InitFumoInternalNode(&pAPDOInternalParams->fumoInternal);
	pAPDOInternalParams->defaultRealm[0] = '\0';
	pAPDOInternalParams->installStatus = isIdle;
	pAPDOInternalParams->bek[0] = '\0';

	//init all entries in NSPsToDmAcc
	for(i=0; i<ARRAY_SIZE(pAPDOInternalParams->nspsToDmAcc); i++)
	{
		pAPDOInternalParams->nspsToDmAcc[i].tagName[0] = '\0';
		pAPDOInternalParams->nspsToDmAcc[i].toDMAcc[0] = '\0'; 
	}

	//init all entries in apdo operator configurations
	for(i=0; i<MAX_NUM_OF_CONFIGURATIONS; i++)
	{
		OSAL_strncpy_s(pAPDOInternalParams->configurations[i].nspTagName, MAX_SIZE_OF_NSP_NAME, 
			L4DB_XML_APDO_CONFIG_UNAVAILABLE, strlen(L4DB_XML_APDO_CONFIG_UNAVAILABLE));
		pAPDOInternalParams->configurations[i].preProvBStrap = FALSE; 
		pAPDOInternalParams->configurations[i].pollingInterval = FALSE;
		pAPDOInternalParams->configurations[i].blockUDP = TRUE;
		pAPDOInternalParams->configurations[i].pollingAttempts = FALSE;
		pAPDOInternalParams->configurations[i].disableOTAP = FALSE;
		pAPDOInternalParams->configurations[i].disablePseudoNAI = FALSE;
	}
	for (i=0; i<ARRAY_SIZE(pAPDOInternalParams->bootstrapInfo); i++)
	{
		pAPDOInternalParams->bootstrapInfo[i].tagName[0] = '\0';
		pAPDOInternalParams->bootstrapInfo[i].serverID[0] = '\0';
		pAPDOInternalParams->bootstrapInfo[i].serverUserName[0] = '\0';
		pAPDOInternalParams->bootstrapInfo[i].clientUserName[0] = '\0';
		pAPDOInternalParams->bootstrapInfo[i].portNbr[0] = '\0';
		pAPDOInternalParams->bootstrapInfo[i].serverURL[0] = '\0';
	}
}

/// <summary>
/// Converts and RF state to a string
/// </summary>
/// <returns>pointer to "On" or "Off" string</returns>
char* l4db_GetRfStateStr(wmx_RfStatus_t state)
{
	if (state == On)
		return L4DB_XML_ON_STR;
	else
		return L4DB_XML_OFF_STR;		
}


/// <summary>
/// Converts and RF state str to an RF state type
/// </summary>
/// <returns>wmx_RfStatus_t</returns>
wmx_RfStatus_t l4db_GetRfStateFromStr(const char* psState)
{
	wmx_RfStatus_t state;

	if(FALSE == l4db_CompareString(psState,L4DB_XML_ON_STR))
		state = On;
	else
		state = Off;

	return state;
}

/// <summary>
/// Dealloc NSP from the DB
/// </summary>
/// <param name="serverId">(IN) server ID
/// <returns>pointer for wmx_pNSPFullData_t which we found or NULL </returns>
wmx_Status_t l4db_DeAllocNsp(wmx_NSPid_t nspID)
{
	pProvisionedNsp_t pFoundNsp = NULL;

	pFoundNsp = l4db_GetProvisionedNspById(nspID);

	if(NULL != pFoundNsp)
	{
		l4db_InitNsp(pFoundNsp);
	}

	return WMX_ST_OK;
}

/// <summary>
/// Gets the channel info which has the given tag name 
/// </summary>
pChannelInfo_t	l4db_GetChannelInfo(pChannelPlan_t pChannelPlan, char * tagName)
{	
	int i;
	pChannelInfo_t pFoundChannelInfo = NULL;

	if((NULL == pChannelPlan) || (NULL == tagName))
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4db_GetChannelInfo pChannelPlan or tagName are NULL");
		return pFoundChannelInfo;
	}

	for(i = 0 ; i < WMX_CHANNELS_MAX_NUM ; i++)
	{
		if(FALSE == l4db_CompareString(tagName, pChannelPlan->channels[i].tagName))
		{
			pFoundChannelInfo = &pChannelPlan->channels[i];
			break;
		}
	}

	return pFoundChannelInfo;
}

/// <summary>
/// Gets the channel ref which has the given tag name 
/// </summary>
pChPlanRefId_t	l4db_GetChannelRef(pChPlanRefId_t pChannelRefs, char * tagName)
{	
	int i;
	pChPlanRefId_t pFoundChannelRef = NULL;

	if((NULL == pChannelRefs) || (NULL == tagName))
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4db_GetChannelRef pChannelRef or tagName are NULL");
		return pFoundChannelRef;
	}

	for(i = 0 ; i < WMX_CHANNELS_MAX_NUM ; i++)
	{
		if(FALSE == l4db_CompareString(tagName, pChannelRefs[i].tagName))
		{
			pFoundChannelRef = &pChannelRefs[i];
			break;
		}
	}

	return pFoundChannelRef;
}

/// <summary>
/// Gets the NAP info for the NAP which has the given tag name
/// </summary>
pL4db_Nap_t l4db_GetCaplNapInfo(pL4db_Nap_t pNaps, char * tagName)
{
	int i;
	pL4db_Nap_t pFoundNapInfo = NULL;

	if((NULL == pNaps) || (NULL == tagName))
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4db_GetCaplNapInfo pNaps or tagName are NULL");
		return pFoundNapInfo;
	}


	for(i = 0 ; i < WMX_NAPS_MAX_NUM ; i++)
	{
		if(FALSE == l4db_CompareString(tagName, pNaps[i].tagName))
		{
			pFoundNapInfo = &pNaps[i];
			break;
		}
	}

	return pFoundNapInfo;
}
/// <summary>
/// Gets the home NSP which has the given tag
/// </summary>
pHomeNsp_t l4db_GetHnsp(pHomeNsp_t pHnsps, char * tagName)
{
	int i;
	pHomeNsp_t pFoundHnsp = NULL;

	if((NULL == pHnsps) || (NULL == tagName))
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4db_GetHnsp pHnsps or tagName are NULL");
		return pFoundHnsp;
	}

	for(i = 0 ; i < WMX_NSP_IDS_MAX_NUM ; i++)
	{
		if(FALSE == l4db_CompareString(tagName, pHnsps[i].tagName))
		{
			pFoundHnsp = &pHnsps[i];
			break;
		}
	}

	return pFoundHnsp;
}
/// <summary>
/// Gets the contact info which has the given tag
/// </summary>
pContactsInfo_t l4db_GetContactInfo(pContactsInfo_t pContacts, char * tagName)
{
	int i;
	pContactsInfo_t pFoundContact = NULL;

	if((NULL == pContacts) || (NULL == tagName))
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4db_GetContactInfo: pContacts or tagName are NULL");
		return pFoundContact;
	}

	for(i = 0 ; i < MAX_NUM_OF_CONTACTS ; i++)
	{
		if(FALSE == l4db_CompareString(tagName, pContacts[i].tagName))
		{
			pFoundContact = &pContacts[i];
			break;
		}
	}

	return pFoundContact;
}
/// <summary>
/// Gets the srv realm which has the given tag - 	NOT SUPPORTED NOW
/// </summary>
pSrvRealm_t l4db_GetSrvRealm(pSrvRealm_t psrvRealms, char * tagName)
{
	int i;
	pSrvRealm_t pFoundSrvRealm = NULL;
	
	if((NULL == psrvRealms) || (NULL == tagName))
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4db_GetSrvRealm psrvRealms or tagName are NULL");
		return pFoundSrvRealm;
	}

	for(i = 0 ; i < MAX_NUM_OF_SRV_REALMS ; i++)
	{
		if(FALSE == l4db_CompareString(tagName, psrvRealms[i].tagName))
		{
			pFoundSrvRealm = &psrvRealms[i];
			break;
		}
	}

	return pFoundSrvRealm;
}

/// <summary>
/// Gets the EAP entry which has the given tag name 
/// </summary>
pEAP_t l4db_GetEap(pEAP_t pEaps, char * tagName)
{
	int i;
	pEAP_t pFoundEap = NULL;

	if((NULL == pEaps) || (NULL == tagName))
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4db_GetEap pEaps or tagName are NULL");
		return pFoundEap;
	}

	for(i = 0 ; i < MAX_NUM_OF_EAP_METHODS ; i++)
	{
		if(FALSE == l4db_CompareString(tagName, pEaps[i].tagName))
		{
			pFoundEap = &pEaps[i];
			break;
		}
	}

	return pFoundEap;
}

/// <summary>
/// Gets the other subscription entry which has the given tag name
/// </summary>
pOtherSubsInfo_t l4db_GetOtherSubsc(pOtherSubsInfo_t pSubscribers, char * tagName)
{
	int i;
	pOtherSubsInfo_t pFoundSubsc = NULL;

	if((NULL == pSubscribers) || (NULL == tagName))
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4db_GetOtherSubsc pSubscribers or tagName are NULL");
		return pFoundSubsc;
	}

	for(i = 0 ; i < WMX_NSP_SUBSCRIBERS_MAX_NUM ; i++)
	{
		if(FALSE == l4db_CompareString(tagName, pSubscribers[i].tagName))
		{
			pFoundSubsc = &pSubscribers[i];
			break;
		}
	}

	return pFoundSubsc;
}
/// <summary>
/// Gets the cert info which has the given tag name 
/// </summary>
pCert_t l4db_GetCert(pCert_t pCerts, char * tagName)
{
	int i;
	pCert_t pFoundCert = NULL;

	if((NULL == pCerts) || (NULL == tagName))
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4db_GetCert pCerts or tagName are NULL");
		return pFoundCert;
	}

	for(i = 0 ; i < MAX_NUM_OF_CERTS ; i++)
	{
		if(FALSE == l4db_CompareString(tagName, pCerts[i].tagName))
		{
			pFoundCert = &pCerts[i];
			break;
		}
	}

	return pFoundCert;
}
/// <summary>
/// Gets the roaming info which has the given tag name 
/// </summary>
pRoamingPartnerInfo_t l4db_GetRoamingInfo(pRoamingPartnerInfo_t pRoamingInfos, char * tagName)
{
	int i;
	pRoamingPartnerInfo_t pFoundRoamingInfo = NULL;

	if((NULL == pRoamingInfos) || (NULL == tagName))
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4db_GetRoamingInfo pRoamingInfos or tagName are NULL");
		return pFoundRoamingInfo;
	}

	for(i = 0 ; i < MAX_ROAMING_PARTNERS ; i++)
	{
		if(FALSE == l4db_CompareString(tagName, pRoamingInfos[i].tagName))
		{
			pFoundRoamingInfo = &pRoamingInfos[i];
			break;
		}
	}

	return pFoundRoamingInfo;
}

/// <summary>
/// Gets the wimax radio module which has the given tag name 
/// </summary>
pWmxRadioModule_t l4db_GetWmxRadioModule(pWmxRadioModule_t pWmxRadioModules, UINT32 size, char * tagName)
{
	UINT32 i;
	pWmxRadioModule_t pFoundWmxRadioModule = NULL;

	if((NULL == pWmxRadioModules) || (NULL == tagName))
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4db_GetWmxRadioModule pWmxRadioModules or tagName are NULL");
		return pFoundWmxRadioModule;
	}

	for(i = 0 ; i < size ; i++)
	{
		if(FALSE == l4db_CompareString(tagName, pWmxRadioModules[i].tagName))
		{
			pFoundWmxRadioModule = &pWmxRadioModules[i];
			break;
		}
	}

	return pFoundWmxRadioModule;
}

/// <summary>
/// Gets the NSPs in the NSPsToDMAcc list which has the given tag name 
/// </summary>
pNSPToDMAcc_t l4db_GetNSPsToDMAccStruct(pAPDOInternalParams_t pApdoInternal, char* tagName)
{
	UINT32 i;
	pNSPToDMAcc_t pFoundNSP = NULL;

	if((NULL == pApdoInternal) || (NULL == tagName))
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4db_GetNSPsToDMAccStruct pApdoInternal or tagName are NULL");
		return pFoundNSP;
	}

	for(i=0; i<WMX_NSPS_TO_DMACC_NODES_MAX_NUM; i++)
	{
		if(FALSE == l4db_CompareString(tagName, pApdoInternal->nspsToDmAcc[i].tagName))
		{
			pFoundNSP = &pApdoInternal->nspsToDmAcc[i];
			break;
		}
	}

	return pFoundNSP;
}

/// <summary>
/// Gets the bootstrap info of the suitable nsp
/// </summary>
pBootstrapInfo_t l4db_GetBootstrapInfoStruct(pAPDOInternalParams_t pApdoInternal, char* tagName)
{
	UINT32 i;
	pBootstrapInfo_t pFoundInfo = NULL;

	if((NULL == pApdoInternal) || (NULL == tagName))
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4db_GetBootstrapInfoStruct pApdoInternal or tagName are NULL");
		return pFoundInfo;
	}

	for(i=0; i<WMX_NSPS_MAX_NUM; i++)
	{
		if(FALSE == l4db_CompareString(tagName, pApdoInternal->bootstrapInfo[i].tagName))
		{
			pFoundInfo = &pApdoInternal->bootstrapInfo[i];
			break;
		}
	}

	return pFoundInfo;
}

/// Alloc Channel Info
/// </summary>
/// <param name="pChannelPlan">(IN) a channel plan to search in </<param>
/// <param name="tagName">(IN) the channel's tagName </<param>
/// <returns>pointer for pChannelInfo_t which has been allocated or NULL if there is no space </returns>
pChannelInfo_t l4db_AllocChannelInfo(pChannelPlan_t pChannelPlan, char *  tagName)
{
	int i;
	pChannelInfo_t pFoundChannelInfo = NULL;

	if(NULL == pChannelPlan)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4db_AllocChannelInfo: pChannelPlan is NULL");
		return pFoundChannelInfo;
	}


	for(i = 0 ; i< WMX_CHANNELS_MAX_NUM ; i++)
	{
		if(FALSE == l4db_CompareString(pChannelPlan->channels[i].tagName, C_L4DB_EMPTY_STRING))
		{
			OSAL_strcpy_s(pChannelPlan->channels[i].tagName, MAX_TAG_NAME_SIZE, tagName);
			pFoundChannelInfo = &pChannelPlan->channels[i];
			break;
		}
	}

	if (pFoundChannelInfo != NULL)
	{
		pChannelPlan->channelsSize++;
	}
	return pFoundChannelInfo;
}



/// <summary>
/// Alloc Channel Ref
/// </summary>
/// <param name="pChannelRef">(IN) a channel refs to search in </<param>
/// <param name="tagName">(IN) the channel's tagName </<param>
/// <returns>pointer for pChannelInfo_t which has been allocated or NULL if there is no space </returns>
pChPlanRefId_t l4db_AllocChannelRef(pChPlanRefId_t pChannelRefs, char *  tagName)
{
	int i;
	pChPlanRefId_t pFoundChannelRef = NULL;

	if(NULL == pChannelRefs)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4db_AllocChannelInfo: pChannelRef is NULL");
		return pFoundChannelRef;
	}


	for(i = 0 ; i< WMX_CHANNELS_MAX_NUM ; i++)
	{
		if(FALSE == l4db_CompareString(pChannelRefs[i].tagName, C_L4DB_EMPTY_STRING))
		{
			OSAL_strcpy_s(pChannelRefs[i].tagName, MAX_TAG_NAME_SIZE, tagName);
			pFoundChannelRef = &pChannelRefs[i];
			break;
		}
	}

	return pFoundChannelRef;
}


/// <summary>
/// Alloc H_NSP info
/// </summary>
/// <param name="pHnsp">(IN) an array of Hnsps </<param>
/// <param name="tagName">(IN) the H_NSP's tagName </<param>
/// <returns>a pointer to a home nsp which has been allocated or NULL if there is not enough space </returns>
pHomeNsp_t l4db_AllocHnsp(pHomeNsp_t pHnsps, char * tagName)
{
	int i;
	pHomeNsp_t pFoundHnsp = NULL;

	if(NULL == pHnsps)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4db_AllocHnsp: pHnsps is NULL");
		return pFoundHnsp;
	}

	for(i = 0 ; i < WMX_NSP_IDS_MAX_NUM ; i++)
	{
		if(FALSE == l4db_CompareString(pHnsps[i].tagName, C_L4DB_EMPTY_STRING))
		{
			OSAL_strcpy_s(pHnsps[i].tagName, MAX_TAG_NAME_SIZE, tagName);
			pFoundHnsp = &pHnsps[i];
			break;
		}
	}

	return pFoundHnsp;
}

/// <summary>
/// Alloc a NAP in the CAPL
/// </summary>
/// <param name="pNaps">(IN) an array of Naps </<param>
/// <param name="tagName">(IN) the NAP's tagName </<param>
/// <returns>a pointer to the NAP which has been allocated or NULL if there is not enough space </returns>
pL4db_Nap_t l4db_AllocCaplNap(pL4db_Nap_t pNaps, char * tagName)
{
	int i;
	pL4db_Nap_t pFoundNap = NULL;

	if(NULL == pNaps)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4db_AllocCaplNap: pNaps is NULL");
		return pFoundNap;
	}

	for(i = 0 ; i < WMX_NAPS_MAX_NUM ; i++)
	{
		if(FALSE == l4db_CompareString(pNaps[i].tagName, C_L4DB_EMPTY_STRING))
		{
			OSAL_strcpy_s(pNaps[i].tagName, MAX_TAG_NAME_SIZE, tagName);
			pFoundNap = &pNaps[i];
			break;
		}
	}

	return pFoundNap;
}

/// <summary>
/// Alloc a NSPToDMAcc node in the NSPsToDMAcc array
/// </summary>
/// <param name="pNSPToDMAcc">(IN) an array of NSPToDMAcc </<param>
/// <param name="tagName">(IN) the NSP's tagName </<param>
/// <returns>a pointer to the NSPToDMAcc which has been allocated or NULL if there is not enough space </returns>
pNSPToDMAcc_t l4db_AllocNSPToDMAcc(pNSPToDMAcc_t pNSPsToDMAcc, char* tagName)
{
	int i;
	pNSPToDMAcc_t pFoundNSPToDMAcc = NULL;

	if ((NULL == pNSPsToDMAcc) || (tagName == NULL))
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4db_AllocNSPsToDMAcc: pNSPsToDMAcc is NULL");
		return pFoundNSPToDMAcc;
	}

	for(i=0; i<WMX_NSPS_TO_DMACC_NODES_MAX_NUM; i++)
	{
		if(FALSE == l4db_CompareString(pNSPsToDMAcc[i].tagName, C_L4DB_EMPTY_STRING))
		{
			OSAL_strcpy_s(pNSPsToDMAcc[i].tagName, MAX_TAG_NAME_SIZE, tagName);
			pFoundNSPToDMAcc = &pNSPsToDMAcc[i];
			break;
		}
	}

	return pFoundNSPToDMAcc;
}

pBootstrapInfo_t l4db_AllocBootstrapInfo(pBootstrapInfo_t pBootstrapInfo, char* tagName)
{
	int i;
	pBootstrapInfo_t pFoundInfo = NULL;

	if(NULL == pBootstrapInfo)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4db_AllocBootstrapInfo: pBootstrapInfo is NULL");
		return pFoundInfo;
	}

	for(i=0; i<WMX_NSPS_MAX_NUM; i++)
	{
		if(FALSE == l4db_CompareString(pBootstrapInfo[i].tagName, C_L4DB_EMPTY_STRING))
		{
			OSAL_strcpy_s(pBootstrapInfo[i].tagName, MAX_TAG_NAME_SIZE, tagName);
			pFoundInfo = &pBootstrapInfo[i];
			break;
		}
	}

	return pFoundInfo;
}

/// <summary>
/// Alloc a URI
/// </summary>
/// <param name="pUris">(IN) an array of Naps </<param>
/// <param name="tagName">(IN) the URI's tagName </<param>
/// <returns>a pointer to the URI which has been allocated or NULL if there is not enough space </returns>
pContactsInfo_t l4db_AllocContactInfo(pContactsInfo_t pContacts, char * tagName)
{
	int i;
	pContactsInfo_t pFoundContact = NULL;

	if(NULL == pContacts)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4db_AllocUri: pUris is NULL");
		return pFoundContact;
	}

	for(i = 0 ; i < WMX_URI_MAX_NUM ; i++)
	{
		if(FALSE == l4db_CompareString(pContacts[i].tagName, C_L4DB_EMPTY_STRING))
		{
			OSAL_strcpy_s(pContacts[i].tagName, MAX_TAG_NAME_SIZE, tagName);
			pFoundContact = &pContacts[i];
			break;
		}
	}

	return pFoundContact;
}


/// <summary>
/// Alloc an srv realm
/// </summary>
/// <param name="pSrvRealms">(IN) an array of Naps </<param>
/// <param name="tagName">(IN) the srv realm's tagName </<param>
/// <returns>a pointer to the srv realm which has been allocated or NULL if there is not enough space </returns>
pSrvRealm_t l4db_AllocSrvRealm(pSrvRealm_t pSrvRealms, char * tagName)
{
	int i;
	pSrvRealm_t pFoundSrvRealm = NULL;

	if(NULL == pSrvRealms)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4db_AllocSrvRealm: pSrvRealms is NULL");
		return pFoundSrvRealm;
	}

	for(i = 0 ; i < MAX_NUM_OF_SRV_REALMS ; i++)
	{
		if(FALSE == l4db_CompareString(pSrvRealms[i].tagName, C_L4DB_EMPTY_STRING))
		{
			OSAL_strcpy_s(pSrvRealms[i].tagName, MAX_TAG_NAME_SIZE, tagName);
			pFoundSrvRealm = &pSrvRealms[i];
			break;
		}
	}

	return pFoundSrvRealm;
}

/// <summary>
/// Alloc a cert
/// </summary>
/// <param name="pCerts">(IN) an array of certs </<param>
/// <param name="tagName">(IN) the cert's tagName </<param>
/// <returns>a pointer to the cert which has been allocated or NULL if there is not enough space </returns>
pCert_t l4db_AllocCert(pCert_t pCerts, char * tagName)
{
	int i;
	pCert_t pFoundCert = NULL;

	if(NULL == pCerts)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4db_AllocCert: pCerts is NULL");
		return pFoundCert;
	}


	for(i = 0 ; i < MAX_NUM_OF_CERTS ; i++)
	{
		if(FALSE == l4db_CompareString(pCerts[i].tagName, C_L4DB_EMPTY_STRING))
		{
			OSAL_strcpy_s(pCerts[i].tagName, MAX_TAG_NAME_SIZE, tagName);
			pFoundCert = &pCerts[i];
			break;
		}
	}

	return pFoundCert;
}

/// <summary>
/// Alloc an EAP entry
/// </summary>
/// <param name="pEaps">(IN) an array of EAPs </<param>
/// <param name="tagName">(IN) the EAP's tagName </<param>
/// <returns>a pointer to the EAP which has been allocated or NULL if there is not enough space </returns>
pEAP_t l4db_AllocEap(pEAP_t pEaps, char * tagName)
{
	int i;
	pEAP_t pFoundEap = NULL;

	if(NULL == pEaps)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4db_AllocEap: pEaps is NULL");
		return pFoundEap;
	}

	for(i = 0 ; i < MAX_EAP_METHOD_SIZE ; i++)
	{
		if(FALSE == l4db_CompareString(pEaps[i].tagName, C_L4DB_EMPTY_STRING))
		{
			OSAL_strcpy_s(pEaps[i].tagName, MAX_TAG_NAME_SIZE, tagName);
			pFoundEap = &pEaps[i];
			break;
		}
	}

	return pFoundEap;
}

/// <summary>
/// Alloc an other subscription
/// </summary>
/// <param name="pSubscribers">(IN) an array of other subscriptions </<param>
/// <param name="tagName">(IN) the other subscription's tagName </<param>
/// <returns>a pointer to the other subscription which has been allocated or NULL if there is not enough space </returns>
pOtherSubsInfo_t l4db_AllocOtherSubsc(pOtherSubsInfo_t pSubscribers, char * tagName)
{
	int i;
	pOtherSubsInfo_t pFoundSubsc = NULL;

	if(NULL == pSubscribers)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4db_AllocOtherSubsc: pSubscribers is NULL");
		return pFoundSubsc;
	}

	for(i = 0 ; i < WMX_NSP_SUBSCRIBERS_MAX_NUM ; i++)
	{
		if(FALSE == l4db_CompareString(pSubscribers[i].tagName, C_L4DB_EMPTY_STRING))
		{
			OSAL_strcpy_s(pSubscribers[i].tagName, MAX_TAG_NAME_SIZE, tagName);
			pFoundSubsc = &pSubscribers[i];
			break;
		}
	}

	return pFoundSubsc;
}
/// <summary>
/// Alloc an NSP
/// </summary>
/// <param name="tagName">(IN) the NSP's tagName </<param>
/// <returns>a pointer to the NSP which has been allocated or NULL if there is not enough space </returns>
pProvisionedNsp_t l4db_AllocNsp(char * tagName)
{
	pProvisionedNsp_t pNsp = l4db_GetEmptyNsp();
	
	if(NULL != pNsp)
	{
		OSAL_strcpy_s(pNsp->tagName, MAX_TAG_NAME_SIZE, tagName);
		l4db_AddNSPToNSPsToDMAccStruct(pNsp->tagName);
	}
	else
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4db_AllocNsp: unable to allocate a new NSP in the L4db");
	}

	return pNsp;
}
/// <summary>
/// Alloc a roaming info subscription
/// </summary>
/// <param name="pRoamingInfos">(IN) an array of roaming infos</<param>
/// <param name="tagName">(IN) the other roaming info's tagName </<param>
/// <returns>a pointer to the roaming info which has been allocated or NULL if there is not enough space </returns>
pRoamingPartnerInfo_t l4db_AllocRoamingInfo(pRoamingPartnerInfo_t pRoamingInfos, char * tagName)
{
	int i;
	pRoamingPartnerInfo_t pFoundRoamingInfo = NULL;

	if(NULL == pRoamingInfos)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4db_AllocRoamingInfo: pRoamingInfos is NULL");
		return pFoundRoamingInfo;
	}

	for(i = 0 ; i < MAX_ROAMING_PARTNERS ; i++)
	{
		if(FALSE == l4db_CompareString(pRoamingInfos[i].tagName, C_L4DB_EMPTY_STRING))
		{
			OSAL_strcpy_s(pRoamingInfos[i].tagName, MAX_TAG_NAME_SIZE, tagName);
			pFoundRoamingInfo = &pRoamingInfos[i];
			break;
		}
	}

	return pFoundRoamingInfo;
}


/// <summary>
/// Alloc a Fumo node
/// </summary>
/// <param name="tagName">(IN) The new node tagName </<param>
/// <returns>a pointer to the node which has been allocated or NULL if there is not enough space </returns>
pFumoParams_t l4db_AllocFumoNode(char * tagName)
{
	pFumoParams_t pFumoNode = l4db_GetEmptyFumoNode();	

	if(NULL != pFumoNode)
	{
		OSAL_strcpy_s(pFumoNode->tagName, MAX_TAG_NAME_SIZE, tagName);
	}
	else
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4db_AllocFumoNode: unable to allocate a new Fumo node in the L4db");
	}

	return pFumoNode;
}

/// <summary>
/// Copy a channle plan with ordering its array elements
/// </summary>
/// <param name="pDest">(OUT) the destionation channel plan </<param>
/// <param name="src">(IN) the source channel plan </<param>
void l4db_CopyChannelPlan(pChannelPlan_t pDest, pChannelPlan_t pSrc)
{
	int i;
	UINT32 size = 0;
	size_t tempStrLen = 0;

	//TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "l4db_CopyChannelPlan(IN)");

	pDest->bw = pSrc->bw;
	pDest->duplexMode = pSrc->duplexMode;
	pDest->fft = pSrc->fft;

	//copy allocated channels to the des
	for(i = 0 ; i < WMX_CHANNELS_MAX_NUM ; i++)
	{
		tempStrLen = OSAL_strnlen(pSrc->channels[i].tagName, MAX_TAG_NAME_SIZE);
		if(0 != tempStrLen && MAX_TAG_NAME_SIZE != tempStrLen)
		{
			memcpy(&pDest->channels[size], &pSrc->channels[i], sizeof(pDest->channels[size]));
			memcpy(&pDest->linkQuality[size], &pSrc->linkQuality[i], sizeof(pDest->linkQuality[size]));
			size++;
		}
	}

	//update the number elements in the channels array
	pDest->channelsSize = size;

	//TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "l4db_CopyChannelPlan(OUT)");
}

/// <summary>
/// Copy a channle plan with ordering its array elements
/// </summary>
/// <param name="pDest">(OUT) the destionation channel plan </<param>
/// <param name="src">(IN) the source channel plan </<param>
void l4db_CopyChannelPlanWithInit(pChannelPlan_t pDest, pChannelPlan_t pSrc)
{
	UINT32 i;

	//add tag names to the allocated channels and copy them
	for(i = 0 ; i < pSrc->channelsSize ; i++)
	{
		l4db_CreateChannelTagName(pSrc->channels[i].tagName, i);
		memcpy(&pDest->channels[i], &pSrc->channels[i], sizeof(pDest->channels[i]));
	}

	pDest->bw = pSrc->bw;
	pDest->fft = pSrc->fft;
	pDest->duplexMode = pSrc->duplexMode;
	pDest->channelsSize = pSrc->channelsSize;

	//init the other channels
	for(i = pSrc->channelsSize ; i < WMX_CHANNELS_MAX_NUM ; i++)
	{
		l4db_InitChannelInfo(&pDest->channels[i]);
	}
}

/// <summary>
/// Copy a channels ref array 
/// </summary>
/// <param name="pDest">(OUT) the destionation channel ref </<param>
/// <param name="src">(IN) the source channel ref </<param>
void l4db_CopyChannelsRefs(pL4db_Nap_t pDest, pL4db_Nap_t pSrc)
{
	int i;
	UINT32 size = 0;
	size_t tempStrLen = 0;

	//copy allocated channels to the des
	for(i = 0 ; i < WMX_CHANNELS_MAX_NUM ; i++)
	{
		tempStrLen = OSAL_strnlen(pSrc->channelPlanRefIds[i].tagName, MAX_TAG_NAME_SIZE);
		if(0 != tempStrLen && MAX_TAG_NAME_SIZE != tempStrLen)
		{
			memcpy(&pDest->channelPlanRefIds[size], &pSrc->channelPlanRefIds[i], sizeof(pDest->channelPlanRefIds[size]));
			size++;
		}
	}

	//update the number elements in the channels array
	pDest->channelRefsSize = size;
}

BOOL l4db_ValidateChannel(pChannelInfo_t channel)
{
	if((channel->firstFreq % 250) != 0)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "Channel with invalid frequency of %u found. Discarding channel", channel->firstFreq);
		return FALSE;
	}
	return TRUE;
}

// The function returns TRUE if the channels are equal. Compare the preambles if requested.
BOOL l4db_IsChannelsEqual(pChannelInfo_t pCh1, pChannelInfo_t pCh2, BOOL isComparePreambles)
{
	BOOL res = FALSE;
	UINT32 i;

	if (pCh1 != NULL &&
		pCh2 != NULL)
	{
		if (pCh1->bw == pCh2->bw &&
			pCh1->fft == pCh2->fft &&
			pCh1->firstFreq == pCh2->firstFreq &&
			pCh1->lastFreq == pCh2->lastFreq &&
			(pCh1->firstFreq + pCh1->nextFreq >= pCh1->lastFreq || //if this is true - no need to compare the nextFreq
			pCh1->nextFreq == pCh2->nextFreq)) // nextFreq causes the generation of a new channel
		{
			if (pCh1->firstFreq + pCh1->nextFreq >= pCh1->lastFreq)
			{
			//TODO: [Oran] finish
			}
			if (isComparePreambles)
			{
				for (i = 0; i < PREAMBLES_LENGTH; ++i)
				{
					if (pCh1->preambleBitmap[i] != pCh2->preambleBitmap[i])
					{
						break;
					}
				}
				if (i == PREAMBLES_LENGTH) // all preambles are equal
				{
					res = TRUE;
				}
			}
			else
			{			
				res = TRUE;
			}
		}
	}

	return res;
}

void l4db_AddChannelsNoDuplicates(pChannelInfo_t pDest, wmx_LinkQuality_t pDestlinkQuality[WMX_CHANNELS_MAX_NUM], UINT32 *destSize, pChannelInfo_t pSrc, UINT32 srcSize, wmx_LinkQuality_t pSrcLinkQuality[WMX_CHANNELS_MAX_NUM], BOOL isComparePreambles)
{
	UINT32 i, j;	


	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "l4db_AddChannelsNoDuplicates [IN]");
	// Copy the dest channels that were not copied yet (that do not appear in the Src NbrAdv)
	for (i = 0; i < srcSize; i++)
	{
		if(!l4db_ValidateChannel(&pSrc[i]))
		{
			continue;
		}

		for (j = 0; j < *destSize; j++)
		{
			if (l4db_IsChannelsEqual(&(pDest[j]), &(pSrc[i]), isComparePreambles))
			{
				TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "l4db_AddChannelsNoDuplicates :frequency = %d, src link quality = %d, dst link quality = %d", pSrc[i].firstFreq, pSrcLinkQuality[i], pDestlinkQuality[j]);
				pDestlinkQuality[j] = pSrcLinkQuality[i];
				TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "l4db_AddChannelsNoDuplicates :pDest[j].ttl = [%d], pSrc[i]=[%d]",pDest[j].ttl , pSrc[i].ttl);
				pDest[j].ttl = pSrc[i].ttl;
				
				break;
			}
		}

		if (j == *destSize)
		{
			
			if (*destSize == WMX_CHANNELS_MAX_NUM)
			{
				break; // There is no place for more channels
			}
			// New channel to add					
			pDest[j] = pSrc[i];			
			pDestlinkQuality[j] = pSrcLinkQuality[i];
			(*destSize)++;

		}
	}
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "l4db_AddChannelsNoDuplicates [OUT]");
}

/// <summary>
/// Merge the channel plans. Keep the order so the NbrAdv are first and then the by TTL order. Assumes that the TTL
/// of the source that is not from NbrAdv is lower then the destination's TTL. (the Src is older channels)
/// </summary>
/// <param name="pDest">(IN, OUT) the destination channel plan </<param>
/// <param name="pSrc">(IN) the source channel plan </<param>
void l4db_MergeChannelPlans(pChannelPlan_t pDest, pChannelPlan_t pSrc, BOOL isComparePreambles)
{
	UINT32 srcIndex, destIndex, tmpIndex;
	pChannelPlan_t pDestLocal, pSrcLocal;
	ChannelPlan_t tmpChannelPlan;
	UINT32 i =0;
	// Args validation
	if (pSrc == NULL ||
		pDest == NULL)
	{
		return;
	}

	if (pDest->channelsSize == 0 || pSrc->channelsSize == 0)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ALERT, "l4db_MergeChannelPlans: pDest->channelsSize = %d, pSrc->channelsSize = %d", 
			pDest->channelsSize, pSrc->channelsSize);
		return;
	}

	pDestLocal = malloc (pDest->channelsSize * sizeof(ChannelPlan_t));
	if (pDestLocal == NULL)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ALERT, "l4db_MergeChannelPlans: malloc returned NULL");
		return;
	}
	pDestLocal->channelsSize = pDest->channelsSize;
	pDestLocal->bw = pDest->bw;
//	pDestLocal->DummyForCompilerHappy = pDest->DummyForCompilerHappy;
	pDestLocal->duplexMode = pDest->duplexMode;
	pDestLocal->fft = pDest->fft;
	pSrcLocal = malloc (pSrc->channelsSize * sizeof(ChannelPlan_t));
	if (pSrcLocal == NULL)
	{
		free(pDestLocal);
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ALERT, "l4db_MergeChannelPlans: malloc returned NULL");
		return;
	}
	pSrcLocal->channelsSize = pSrc->channelsSize;
	pSrcLocal->bw = pSrc->bw;
//	pSrcLocal->DummyForCompilerHappy = pSrc->DummyForCompilerHappy;
	pSrcLocal->duplexMode = pSrc->duplexMode;
	pSrcLocal->fft = pSrc->fft;

	srcIndex = destIndex = tmpIndex = 0;

	for (i=0 ; i < pSrc->channelsSize ; i ++)
	{
		OSAL_memcpy_s(&pSrcLocal->channels[i].bw, sizeof(wmx_BW_t),&pSrc->channels[i].bw ,sizeof(wmx_BW_t));
		OSAL_memcpy_s(&pSrcLocal->channels[i].duplexMode, sizeof(wmx_DuplexMode_t),&pSrc->channels[i].duplexMode ,sizeof(wmx_DuplexMode_t));
		OSAL_memcpy_s(&pSrcLocal->channels[i].fft, sizeof(wmx_FFT_t),&pSrc->channels[i].fft ,sizeof(wmx_FFT_t));
		OSAL_memcpy_s(&pSrcLocal->channels[i].firstFreq, sizeof(wmx_Frequency_t),&pSrc->channels[i].firstFreq ,sizeof(wmx_Frequency_t));
		OSAL_memcpy_s(&pSrcLocal->channels[i].id, (sizeof(CHAR)*MAX_REF_ID_NAME_SIZE),&pSrc->channels[i].id ,(sizeof(CHAR)*MAX_REF_ID_NAME_SIZE));
		OSAL_memcpy_s(&pSrcLocal->channels[i].lastFoundInNbrAdv, sizeof(BOOL),&pSrc->channels[i].lastFoundInNbrAdv ,sizeof(BOOL));
		OSAL_memcpy_s(&pSrcLocal->channels[i].lastFreq, sizeof(wmx_Frequency_t),&pSrc->channels[i].lastFreq ,sizeof(wmx_Frequency_t));
		OSAL_memcpy_s(&pSrcLocal->channels[i].nextFreq, sizeof(wmx_NextFreqStep_t),&pSrc->channels[i].nextFreq ,sizeof(wmx_NextFreqStep_t));
		OSAL_memcpy_s(&pSrcLocal->channels[i].preambleBitmap, sizeof(wmx_Preambles_t),&pSrc->channels[i].preambleBitmap ,sizeof(wmx_Preambles_t));
		OSAL_memcpy_s(&pSrcLocal->channels[i].tagName, (sizeof(CHAR)*MAX_TAG_NAME_SIZE),&pSrc->channels[i] .tagName,(sizeof(CHAR)*MAX_TAG_NAME_SIZE));
		OSAL_memcpy_s(&pSrcLocal->channels[i].ttl, sizeof(UINT32),&pSrc->channels[i].ttl,sizeof(UINT32));
		OSAL_memcpy_s(&pSrcLocal->linkQuality[i], sizeof(UINT32),&pSrc->linkQuality[i],sizeof(UINT32));
	}

	for (i=0 ; i < pDest->channelsSize ; i ++)
	{
		OSAL_memcpy_s(&pDestLocal->channels[i].bw, sizeof(wmx_BW_t),&pDest->channels[i].bw ,sizeof(wmx_BW_t));
		OSAL_memcpy_s(&pDestLocal->channels[i].duplexMode, sizeof(wmx_DuplexMode_t),&pDest->channels[i].duplexMode ,sizeof(wmx_DuplexMode_t));
		OSAL_memcpy_s(&pDestLocal->channels[i].fft, sizeof(wmx_FFT_t),&pDest->channels[i].fft ,sizeof(wmx_FFT_t));
		OSAL_memcpy_s(&pDestLocal->channels[i].firstFreq, sizeof(wmx_Frequency_t),&pDest->channels[i].firstFreq ,sizeof(wmx_Frequency_t));
		OSAL_memcpy_s(&pDestLocal->channels[i].id, (sizeof(CHAR)*MAX_REF_ID_NAME_SIZE),&pDest->channels[i].id ,(sizeof(CHAR)*MAX_REF_ID_NAME_SIZE));
		OSAL_memcpy_s(&pDestLocal->channels[i].lastFoundInNbrAdv, sizeof(BOOL),&pDest->channels[i].lastFoundInNbrAdv ,sizeof(BOOL));
		OSAL_memcpy_s(&pDestLocal->channels[i].lastFreq, sizeof(wmx_Frequency_t),&pDest->channels[i].lastFreq ,sizeof(wmx_Frequency_t));
		OSAL_memcpy_s(&pDestLocal->channels[i].nextFreq, sizeof(wmx_NextFreqStep_t),&pDest->channels[i].nextFreq ,sizeof(wmx_NextFreqStep_t));
		OSAL_memcpy_s(&pDestLocal->channels[i].preambleBitmap, sizeof(wmx_Preambles_t),&pDest->channels[i].preambleBitmap ,sizeof(wmx_Preambles_t));
		OSAL_memcpy_s(&pDestLocal->channels[i].tagName, (sizeof(CHAR)*MAX_TAG_NAME_SIZE),&pDest->channels[i] .tagName,(sizeof(CHAR)*MAX_TAG_NAME_SIZE));
		OSAL_memcpy_s(&pDestLocal->channels[i].ttl, sizeof(UINT32),&pDest->channels[i].ttl,sizeof(UINT32));
		OSAL_memcpy_s(&pDestLocal->linkQuality[i], sizeof(UINT32),&pDest->linkQuality[i],sizeof(UINT32));
	}


	// Copy the NbrAdv channels of the dest
	while (	destIndex < pDestLocal->channelsSize && 
			pDestLocal->channels[destIndex].lastFoundInNbrAdv == TRUE	)
	{
		if(l4db_ValidateChannel(&pDestLocal->channels[destIndex]))
		{	
			//OSAL_memcpy_s(&tmpChannelPlan.channels[tmpIndex], sizeof(ChannelInfo_t),&pDest->channels[destIndex] ,sizeof(ChannelInfo_t));
			OSAL_memcpy_s(&tmpChannelPlan.channels[tmpIndex].bw, sizeof(wmx_BW_t),&pDestLocal->channels[destIndex].bw ,sizeof(wmx_BW_t));
			OSAL_memcpy_s(&tmpChannelPlan.channels[tmpIndex].duplexMode, sizeof(wmx_DuplexMode_t),&pDestLocal->channels[destIndex].duplexMode ,sizeof(wmx_DuplexMode_t));
			OSAL_memcpy_s(&tmpChannelPlan.channels[tmpIndex].fft, sizeof(wmx_FFT_t),&pDestLocal->channels[destIndex].fft ,sizeof(wmx_FFT_t));
			OSAL_memcpy_s(&tmpChannelPlan.channels[tmpIndex].firstFreq, sizeof(wmx_Frequency_t),&pDestLocal->channels[destIndex].firstFreq ,sizeof(wmx_Frequency_t));
			OSAL_memcpy_s(&tmpChannelPlan.channels[tmpIndex].id, (sizeof(CHAR)*MAX_REF_ID_NAME_SIZE),&pDestLocal->channels[destIndex].id ,(sizeof(CHAR)*MAX_REF_ID_NAME_SIZE));
			OSAL_memcpy_s(&tmpChannelPlan.channels[tmpIndex].lastFoundInNbrAdv, sizeof(BOOL),&pDestLocal->channels[destIndex].lastFoundInNbrAdv ,sizeof(BOOL));
			OSAL_memcpy_s(&tmpChannelPlan.channels[tmpIndex].lastFreq, sizeof(wmx_Frequency_t),&pDestLocal->channels[destIndex].lastFreq ,sizeof(wmx_Frequency_t));
			OSAL_memcpy_s(&tmpChannelPlan.channels[tmpIndex].nextFreq, sizeof(wmx_NextFreqStep_t),&pDestLocal->channels[destIndex].nextFreq ,sizeof(wmx_NextFreqStep_t));
			OSAL_memcpy_s(&tmpChannelPlan.channels[tmpIndex].preambleBitmap, sizeof(wmx_Preambles_t),&pDestLocal->channels[destIndex].preambleBitmap ,sizeof(wmx_Preambles_t));
			OSAL_memcpy_s(&tmpChannelPlan.channels[tmpIndex].tagName, (sizeof(CHAR)*MAX_TAG_NAME_SIZE),&pDestLocal->channels[destIndex] .tagName,(sizeof(CHAR)*MAX_TAG_NAME_SIZE));
			OSAL_memcpy_s(&tmpChannelPlan.channels[tmpIndex].ttl, sizeof(UINT32),&pDestLocal->channels[destIndex] .ttl,sizeof(UINT32));
			OSAL_memcpy_s(&tmpChannelPlan.linkQuality[tmpIndex], sizeof(UINT32),&pDestLocal->linkQuality[destIndex],sizeof(UINT32));
			//tmpChannelPlan.channels[tmpIndex] = pDest->channels[destIndex];
			destIndex++;
			tmpIndex++;
		}
	}

	// Copy the NbrAdv channels of the source
	while (	srcIndex < pSrcLocal->channelsSize && 
			pSrcLocal->channels[srcIndex].lastFoundInNbrAdv == TRUE	)
	{
		if(l4db_ValidateChannel(&pSrcLocal->channels[srcIndex]))
		{		
			//OSAL_memcpy_s(&tmpChannelPlan.channels[tmpIndex], sizeof(ChannelInfo_t),&pSrc->channels[srcIndex] ,sizeof(ChannelInfo_t));
			OSAL_memcpy_s(&tmpChannelPlan.channels[tmpIndex].bw, sizeof(wmx_BW_t),&pSrcLocal->channels[srcIndex].bw ,sizeof(wmx_BW_t));
			OSAL_memcpy_s(&tmpChannelPlan.channels[tmpIndex].duplexMode, sizeof(wmx_DuplexMode_t),&pSrcLocal->channels[srcIndex].duplexMode ,sizeof(wmx_DuplexMode_t));
			OSAL_memcpy_s(&tmpChannelPlan.channels[tmpIndex].fft, sizeof(wmx_FFT_t),&pSrcLocal->channels[srcIndex].fft ,sizeof(wmx_FFT_t));
			OSAL_memcpy_s(&tmpChannelPlan.channels[tmpIndex].firstFreq, sizeof(wmx_Frequency_t),&pSrcLocal->channels[srcIndex].firstFreq ,sizeof(wmx_Frequency_t));
			OSAL_memcpy_s(&tmpChannelPlan.channels[tmpIndex].id, (sizeof(CHAR)*MAX_REF_ID_NAME_SIZE),&pSrcLocal->channels[srcIndex].id ,(sizeof(CHAR)*MAX_REF_ID_NAME_SIZE));
			OSAL_memcpy_s(&tmpChannelPlan.channels[tmpIndex].lastFoundInNbrAdv, sizeof(BOOL),&pSrcLocal->channels[srcIndex].lastFoundInNbrAdv ,sizeof(BOOL));
			OSAL_memcpy_s(&tmpChannelPlan.channels[tmpIndex].lastFreq, sizeof(wmx_Frequency_t),&pSrcLocal->channels[srcIndex].lastFreq ,sizeof(wmx_Frequency_t));
			OSAL_memcpy_s(&tmpChannelPlan.channels[tmpIndex].nextFreq, sizeof(wmx_NextFreqStep_t),&pSrcLocal->channels[srcIndex].nextFreq ,sizeof(wmx_NextFreqStep_t));
			OSAL_memcpy_s(&tmpChannelPlan.channels[tmpIndex].preambleBitmap, sizeof(wmx_Preambles_t),&pSrcLocal->channels[srcIndex].preambleBitmap ,sizeof(wmx_Preambles_t));
			OSAL_memcpy_s(&tmpChannelPlan.channels[tmpIndex].tagName, (sizeof(CHAR)*MAX_TAG_NAME_SIZE),&pSrcLocal->channels[srcIndex] .tagName,(sizeof(CHAR)*MAX_TAG_NAME_SIZE));
			OSAL_memcpy_s(&tmpChannelPlan.channels[tmpIndex].ttl, sizeof(UINT32),&pSrcLocal->channels[srcIndex] .ttl,sizeof(UINT32));
			OSAL_memcpy_s(&tmpChannelPlan.linkQuality[tmpIndex], sizeof(UINT32),&pSrcLocal->linkQuality[srcIndex],sizeof(UINT32));
			//tmpChannelPlan.channels[tmpIndex] = pSrc->channels[srcIndex];
			srcIndex++;
			tmpIndex++;
		}
	}

	// Copy the rest of the Src channels (the ones that are after the NbrAdv)
	l4db_AddChannelsNoDuplicates(tmpChannelPlan.channels,
		tmpChannelPlan.linkQuality,
		&tmpIndex,
		pSrcLocal->channels + srcIndex,
		pSrcLocal->channelsSize - srcIndex,
		pSrcLocal->linkQuality + srcIndex,
		isComparePreambles);


	/*L4db_PrintDiscoveredNAPsList();
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4db_MergeChannelPlans -- > After first l4db_AddChannelsNoDuplicates");*/
	

	// Copy the dest channels that were not copied yet (that do not appear in the Src NbrAdv)
	l4db_AddChannelsNoDuplicates(tmpChannelPlan.channels,
		tmpChannelPlan.linkQuality,
		&tmpIndex,
		pDestLocal->channels + destIndex,
		pDestLocal->channelsSize - destIndex,
		pDestLocal->linkQuality + destIndex,
		isComparePreambles);

	/*L4db_PrintDiscoveredNAPsList();
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4db_MergeChannelPlans -- > After second l4db_AddChannelsNoDuplicates");*/
	// Copy the result to the Dest array
	if (tmpIndex > 0)
	{	
		for (i=0 ; i < tmpIndex ; i++)
		{
			OSAL_memcpy_s(&pDest->channels[i].bw, sizeof(wmx_BW_t),&tmpChannelPlan.channels[i].bw ,sizeof(wmx_BW_t));
			OSAL_memcpy_s(&pDest->channels[i].duplexMode, sizeof(wmx_DuplexMode_t),&tmpChannelPlan.channels[i].duplexMode ,sizeof(wmx_DuplexMode_t));
			OSAL_memcpy_s(&pDest->channels[i].fft, sizeof(wmx_FFT_t),&tmpChannelPlan.channels[i].fft ,sizeof(wmx_FFT_t));
			OSAL_memcpy_s(&pDest->channels[i].firstFreq, sizeof(wmx_Frequency_t),&tmpChannelPlan.channels[i].firstFreq ,sizeof(wmx_Frequency_t));
			OSAL_memcpy_s(&pDest->channels[i].id, (sizeof(CHAR)*MAX_REF_ID_NAME_SIZE),&tmpChannelPlan.channels[i].id ,(sizeof(CHAR)*MAX_REF_ID_NAME_SIZE));
			OSAL_memcpy_s(&pDest->channels[i].lastFoundInNbrAdv, sizeof(BOOL),&tmpChannelPlan.channels[i].lastFoundInNbrAdv ,sizeof(BOOL));
			OSAL_memcpy_s(&pDest->channels[i].lastFreq, sizeof(wmx_Frequency_t),&tmpChannelPlan.channels[i].lastFreq ,sizeof(wmx_Frequency_t));
			OSAL_memcpy_s(&pDest->channels[i].nextFreq, sizeof(wmx_NextFreqStep_t),&tmpChannelPlan.channels[i].nextFreq ,sizeof(wmx_NextFreqStep_t));
			OSAL_memcpy_s(&pDest->channels[i].preambleBitmap, sizeof(wmx_Preambles_t),&tmpChannelPlan.channels[i].preambleBitmap ,sizeof(wmx_Preambles_t));
			OSAL_memcpy_s(&pDest->channels[i].tagName, (sizeof(CHAR)*MAX_TAG_NAME_SIZE),&tmpChannelPlan.channels[i] .tagName,(sizeof(CHAR)*MAX_TAG_NAME_SIZE));
			OSAL_memcpy_s(&pDest->channels[i].ttl, sizeof(UINT32),&tmpChannelPlan.channels[i].ttl,sizeof(UINT32));
			OSAL_memcpy_s(&pDest->linkQuality[i], sizeof(UINT32),&tmpChannelPlan.linkQuality[i],sizeof(UINT32));
			//OSAL_memcpy_s (&pDest->channels[i], sizeof(ChannelInfo_t), &tmpChannelPlan.channels[i], sizeof(ChannelInfo_t));
			/*OSAL_memcpy_s(&(pDest->channels), WMX_CHANNELS_MAX_NUM * sizeof(ChannelInfo_t), 
				&(tmpChannelPlan.channels), WMX_CHANNELS_MAX_NUM * sizeof(ChannelInfo_t));*/
		}
		
		pDest->channelsSize = tmpIndex;
	}
	free(pSrcLocal);
	free(pDestLocal);
}

/// <summary>
/// Copy an eap info with ordering its array elements
/// </summary>
/// <param name="pDest">(OUT) the destionation  </<param>
/// <param name="src">(IN) the source  </<param>
void l4db_CopyEapInfo(pEAP_t pDest, pEAP_t pSrc)
{
	int i;
	UINT32 size = 0;
	size_t tempStrLen = 0;

	//copy the tagName
	OSAL_strcpy_s(pDest->tagName, MAX_TAG_NAME_SIZE, pSrc->tagName);

	//copy the EAP method
	pDest->EAPMethod = pSrc->EAPMethod;

	//copy the vendor id
	pDest->vendorId = pSrc->vendorId;

	//copy the vendor type
	pDest->vendorType = pSrc->vendorType;

	//copy user name
	OSAL_strcpy_s(pDest->id, WMX_SUBSCRIBER_ID_MAX_SIZE, pSrc->id);

	//copy the pseudo id
	OSAL_strcpy_s(pDest->provisionedPseudoId, WMX_SUBSCRIBER_ID_MAX_SIZE, pSrc->provisionedPseudoId);

	//copy the password
	OSAL_strcpy_s(pDest->Password, MAX_EAP_PASSWORD_SIZE, pSrc->Password);

	//copy the realm
	OSAL_strcpy_s(pDest->realm, MAX_REALM_SIZE, pSrc->realm);

	//copy use pseudo
	pDest->usePrivacy = pSrc->usePrivacy;

	//copy encaps
	pDest->encaps = pSrc->encaps;

	//copy vfy srv realms - NOT SUPPORTED NOW
	//pDest->vfySrvRealm = pSrc->vfySrvRealm;

	//copy the srv realms - NOT SUPPORTED NOW
	//for(i = 0 ; i < MAX_NUM_OF_SRV_REALMS ; i++)
	//{
	//	if(0 != strlen(pSrc->srvRealms[i].tagName))
	//	{
	//		memcpy(&pDest->srvRealms[size], &pSrc->srvRealms[i], sizeof(pDest->srvRealms[size]));
	//		size++;
	//	}
	//}

	//pDest->srvRealmsSize = size;
	//size = 0;

	//copy the certs
	for(i = 0 ; i < MAX_NUM_OF_CERTS ; i++)
	{
		tempStrLen = OSAL_strnlen(pSrc->certs[i].tagName, MAX_TAG_NAME_SIZE);
		if(0 != tempStrLen && MAX_TAG_NAME_SIZE  != tempStrLen)
		{
			memcpy(&pDest->certs[size], &pSrc->certs[i], sizeof(pDest->certs[size]));
			size++;
		}
	}

	pDest->certsSize = size;
}

/// <summary>
/// Copy a subscription params with ordering its array elements
/// </summary>
/// <param name="pDest">(OUT) the destionation  </<param>
/// <param name="src">(IN) the source  </<param>
void l4db_CopySubscriptionParams(pSubscriptionParams_t pDest, pSubscriptionParams_t pSrc)
{

	int i, j;
	UINT32 eapsSize = 0, otherSize = 0;
	size_t tempStrLen = 0;

	//copy the primary
	//name
	OSAL_strcpy_s(pDest->primary.name, WMX_SUBSCRIBER_NAME_MAX_SIZE, pSrc->primary.name);

	//activated
	pDest->primary.activated = pSrc->primary.activated;

	//eap info
	for(i = 0 ; i < MAX_NUM_OF_EAP_METHODS ; i++)
	{
		tempStrLen = OSAL_strnlen(pSrc->primary.eapInfo[i].tagName, MAX_TAG_NAME_SIZE);
		if(0 != tempStrLen && MAX_TAG_NAME_SIZE != tempStrLen)
		{
			l4db_CopyEapInfo(&pDest->primary.eapInfo[eapsSize], &pSrc->primary.eapInfo[i]);
			eapsSize++;
		}
	}

	pDest->primary.eapInfoSize = eapsSize;
	eapsSize = 0;
	
	//other subscriptions
	for(i = 0 ; i < WMX_NSP_SUBSCRIBERS_MAX_NUM ; i++)
	{
		tempStrLen = OSAL_strnlen(pSrc->other[i].tagName, MAX_TAG_NAME_SIZE);
		if(0 != tempStrLen && MAX_TAG_NAME_SIZE != tempStrLen)
		{
			//copy the tag name
			OSAL_strcpy_s(pDest->other[otherSize].tagName, MAX_TAG_NAME_SIZE, pSrc->other[i].tagName);

			//copy the name
			//name
			OSAL_strcpy_s(pDest->other[otherSize].subscriberInfo.name, WMX_SUBSCRIBER_NAME_MAX_SIZE,  pSrc->other[i].subscriberInfo.name);

			//activated
			pDest->other[otherSize].subscriberInfo.activated =  pSrc->other[i].subscriberInfo.activated;

			//Eap
			for(j = 0 ; j < MAX_NUM_OF_EAP_METHODS ; j++)
			{
				tempStrLen= OSAL_strnlen(pSrc->other[i].subscriberInfo.eapInfo[j].tagName, MAX_TAG_NAME_SIZE);
				if(0 != tempStrLen && MAX_TAG_NAME_SIZE != tempStrLen)
				{
					l4db_CopyEapInfo(&pDest->other[otherSize].subscriberInfo.eapInfo[eapsSize], &pSrc->other[i].subscriberInfo.eapInfo[j]);
					eapsSize++;
				}
			}
			pDest->other[otherSize].subscriberInfo.eapInfoSize = eapsSize;

			otherSize++;
		}
	}

	pDest->otherSize = otherSize;
}
/// <summary>
/// Copy a nw params with ordering its array elements
/// </summary>
/// <param name="pDest">(OUT) the destionation  </<param>
/// <param name="src">(IN) the source  </<param>
void l4db_CopyNwParams(pNwParams_t pDest, pNwParams_t pSrc)
{
	int i, j;
	UINT32 size = 0, innerSize = 0;
	size_t tempStrLen = 0;

	//copy the provisioned name
	OSAL_strcpy_s(pDest->provisionedName, WMX_NSP_NAME_MAX_SIZE, pSrc->provisionedName);

	// copy the server ID
	OSAL_strcpy_s(pDest->serverID, MAX_SERVER_ID_SIZE, pSrc->serverID);

	//copy the capl
	pDest->capl.any = pSrc->capl.any;

	for(i = 0 ; i < WMX_NAPS_MAX_NUM ; i++)
	{
		tempStrLen = OSAL_strnlen(pSrc->capl.naps[i].tagName, MAX_TAG_NAME_SIZE + 1);
		if(0 != tempStrLen && (MAX_TAG_NAME_SIZE + 1) != tempStrLen)
		{
			for(j = 0 ; j < WMX_CHANNELS_MAX_NUM ; j++)
			{
				tempStrLen = OSAL_strnlen(pSrc->capl.naps[i].channelPlanRefIds[j].tagName, MAX_TAG_NAME_SIZE);
				if(0 != tempStrLen && MAX_TAG_NAME_SIZE != tempStrLen)
				{
					memcpy(&pDest->capl.naps[size].channelPlanRefIds[innerSize], 
							&pSrc->capl.naps[i].channelPlanRefIds[j], 
							sizeof(pDest->capl.naps[size].channelPlanRefIds[innerSize]));
					innerSize++;
				}
			}

			//update the number of entries in the rapl
			pDest->capl.naps[size].channelRefsSize = innerSize;

			memcpy(pDest->capl.naps[size].napID, 
					pSrc->capl.naps[i].napID, 
					sizeof(pDest->capl.naps[size].napID));

			pDest->capl.naps[size].priority = pSrc->capl.naps[i].priority;

			OSAL_strcpy_s(pDest->capl.naps[size].tagName, MAX_TAG_NAME_SIZE, pSrc->capl.naps[i].tagName);
			size++;
		}
	}

	//update the number of entries in the capl
	pDest->capl.napsSize = size;
	size = 0;

	//copy the rapl
	pDest->rapl.any = pSrc->rapl.any;

	for(i = 0 ; i < MAX_ROAMING_PARTNERS ; i++)
	{
		tempStrLen = OSAL_strnlen(pSrc->rapl.roamingPartners[i].tagName, MAX_TAG_NAME_SIZE);
		if(0 != tempStrLen && MAX_TAG_NAME_SIZE != tempStrLen)
		{
			memcpy(&pDest->rapl.roamingPartners[size], &pSrc->rapl.roamingPartners[i], sizeof(pDest->rapl.roamingPartners[size]));
			size++;
		}
	}

	//update the number of entries in the rapl
	pDest->rapl.roamingPartnersSize = size;
	size = 0;

	//copy the channel plan
	l4db_CopyChannelPlan(&pDest->channelPlan, &pSrc->channelPlan);

	//copy the hNsps
	for(i = 0 ; i < WMX_NSP_IDS_MAX_NUM ; i++)
	{
		tempStrLen = OSAL_strnlen(pSrc->hNsps[i].tagName, MAX_TAG_NAME_SIZE);
		if(0 != tempStrLen && MAX_TAG_NAME_SIZE != tempStrLen)
		{
			pDest->hNsps[size].nspId = pSrc->hNsps[i].nspId;
			size++;
		}
	}

	//update the number of elements in the hNsps array
	pDest->hNspsSize = size;

	//copy the polling interval
	pDest->pollingInterval = pSrc->pollingInterval;
	pDest->pollingAttempts = pSrc->pollingAttempts;
}

/// <summary>
/// Copy an NSP with ordering its array elements
/// </summary>
/// <param name="pDest">(OUT) the destionation  </<param>
/// <param name="src">(IN) the source </<param>
void l4db_CopyProvisionedNsp(pProvisionedNsp_t pDest, pProvisionedNsp_t pSrc)
{
	int i;
	int size = 0;
	size_t tempStrLen = 0;

	//copy the tag name
	OSAL_strcpy_s(pDest->tagName, MAX_TAG_NAME_SIZE, pSrc->tagName);

	//copy the nw params
	l4db_CopyNwParams(&pDest->nwParams, &pSrc->nwParams);

	//copy subscription params
	l4db_CopySubscriptionParams(&pDest->subscriptionParams, &pSrc->subscriptionParams);

	//copy the contacts
	for(i = 0 ; i < MAX_NUM_OF_CONTACTS ; i++)
	{
		tempStrLen = OSAL_strnlen(pSrc->contacts[i].tagName, MAX_TAG_NAME_SIZE);
		if(0 != tempStrLen && MAX_TAG_NAME_SIZE != tempStrLen)
		{
			memcpy(&pDest->contacts[size], &pSrc->contacts[i], sizeof(pDest->contacts[size]));
			size++;
		}
	}

	pDest->contactsSize = size;
}

/// <summary>
/// Copy a discovered nap
/// </summary>
/// <param name="pDest">(OUT) the destionation  </<param>
/// <param name="src">(IN) the source </<param>
void l4db_CopyDiscoveredNap(pL4db_Nap_t dst, pDiscoveredNap_t src)
{
	memcpy(dst->napID, src->napID, sizeof(dst->napID));
	dst->changeCount = src->changeCount;
	l4db_CopyChannelPlan(&dst->discoveredChannelPlan, &src->channelPlan);
}

/// <summary>
/// Copy a provisioned nap
/// </summary>
/// <param name="pDest">(OUT) the destionation  </<param>
/// <param name="src">(IN) the source </<param>
void l4db_CopyProvisionedNap(pL4db_Nap_t dst, pL4db_Nap_t src)
{
	memcpy(dst->napID, src->napID, sizeof(dst->napID));
	OSAL_strcpy_s(dst->tagName, MAX_TAG_NAME_SIZE, src->tagName);
	dst->priority = src->priority;
	l4db_CopyChannelsRefs(dst, src);
}
/// <summary>
/// creates a channel's dummy tag name
/// </summary>
/// <param name="tagName">(OUT) the tag name to be created  </<param>
/// <param name="channelIndex">(IN) the index in the channel array</<param>
void l4db_CreateChannelTagName(char * tagName, int channelIndex)
{
	OSAL_strcpy_s(tagName, 3, C_L4DB_EMPTY_STRING);//L4DB_CHANNEL_TAG_NAME_PREFIX);
	OSAL_itoa_s(channelIndex, tagName, MAX_TAG_NAME_SIZE - strlen(C_L4DB_EMPTY_STRING), 10);

	tagName[3] = '\0';
}
/// <summary>
/// checks if it is legal to add the given NAP ID to the DB. If it already exists in this NSP
/// under a different tag name, it is illegal
/// </summary>
/// <param name="napID">(IN) the requested NAP ID </param>
/// <param name="napTagName">(IN) the nap's tag name </param>
/// <param name="nspTagName">(IN) the nsp's tag name </param>
/// <returns>TRUE is legal and FALSE otherwise </returns>
BOOL l4db_IsLegalToAddNapId(wmx_NAPid_t napID, char * napTagName, char * nspTagName)
{
	int i;
	pProvisionedNsp_t pFoundNsp;

	//get our NSP
	pFoundNsp = l4db_GetProvisionedNspByTagName(nspTagName);

	if(NULL == pFoundNsp)
	{
		return TRUE; //the NSP doesn't exist yet, therefore this addition is legal
	}

	for(i = 0 ; i < WMX_NAPS_MAX_NUM ; i++)
	{
		if(TRUE == l4db_IsNapidEqual(napID, pFoundNsp->nwParams.capl.naps[i].napID))
		{
			//if their tag names aren't equal, this addition is illegal
			if(TRUE == l4db_CompareString(napTagName, pFoundNsp->nwParams.capl.naps[i].tagName))
			{
				return FALSE;
			}
		}
	}
	return TRUE;
}

int l4db_CompareNapRSSIandCINR(const void * elem1, const void * elem2)
{
	wmx_pNAP_t nap1, nap2;

	nap1 = (wmx_pNAP_t)elem1;
	nap2 = (wmx_pNAP_t)elem2;

	if (nap1->bestCINR > nap2->bestCINR ||
		(nap1->bestCINR == nap2->bestCINR && nap1->bestRssi > nap2->bestRssi))
	{
		return 1;
	}
	else if(nap1->bestCINR < nap2->bestCINR ||
			(nap1->bestCINR == nap2->bestCINR && nap1->bestRssi < nap2->bestRssi))
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

int l4db_CompareNapPriority(const void * elem1, const void * elem2)
{
	int compareResult = 0;
	pL4db_Nap_t nap1, nap2;

	nap1 = (pL4db_Nap_t)elem1;
	nap2 = (pL4db_Nap_t)elem2;

	if(nap1->priority > nap2->priority)
	{
		compareResult = 1;
	}
	else if(nap1->priority < nap2->priority)
	{
		compareResult = -1;
	}

	return compareResult;
}
//compare the channels by the ttl and if they equal compare the boolean lastFoundInNbrAdv
int l4db_CompareChannelInfoByAge(const void * elem1, const void * elem2)
{

	pChannelInfo_t ChannelInfo1, ChannelInfo2;
	int compareResult = 0;

	ChannelInfo1 = (pChannelInfo_t)elem1;
	ChannelInfo2 = (pChannelInfo_t)elem2;

	//The sorting is by the lastFoundInNbrAdv and then by the ttl	
	if(TRUE == ChannelInfo1->lastFoundInNbrAdv && FALSE == ChannelInfo2->lastFoundInNbrAdv)
	{
		compareResult = -1;
	}
	else 
	{
		if(FALSE == ChannelInfo1->lastFoundInNbrAdv && TRUE == ChannelInfo2->lastFoundInNbrAdv)
		{
			compareResult = 1;
		}
		else 
		{
			if(ChannelInfo1->ttl  > ChannelInfo2->ttl)
			{
				compareResult = -1;
			} 
			else if(ChannelInfo1->ttl < ChannelInfo2->ttl)
			{
				compareResult = 1;
			}			
		}
	}
	return compareResult;
}


/// <summary>
// This function builds the parameter as a concatenation between the following:
//	./WiMAX/WiMAXRadioModule/0/Man
//  -
//	./WiMAX/WiMAXRadioModule/0/Mod
//  -
//  ./WiMAX/WiMAXRadioModule/0/SwV
//  -
//  ./DevDetail/SwV
//  -
//  ./WiMAX/TerminalEquipment/SwV
//  -
//	./WiMAX/TerminalEquipment/Man
/// </summary>
void l4db_BuildVersionString(char pVersion[MAX_SWV2_NAME_SIZE])
{
	pWmxRadioModule_t pRadioModule;
	pTerminalEquipment_t pTermEquipment;
	pDevDetail_t pDevDetail;
	pDevInfo_t pDevInfo;
	BOOL res;
	char fixSpecialCharacters[MAX_REGISTRY_ANSWER] = DEFAULT_TRUE_LOWER;
		
	pRadioModule = l4db_GetWmxRadioModuleStruct(0);
	pTermEquipment = l4db_GetTeminalEquipmentStruct();
	pDevDetail = l4db_GetDevDetail();
	pDevInfo = l4db_GetDevInfo();
	
	pVersion[0] = '\0';
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "l4db_InitWimax - pDevDetail->devType = [%s].",pDevDetail->devType);
	if (( FALSE == (OSAL_stricmp ("",pDevDetail->devType))) || ( FALSE == (OSAL_stricmp ("Null",pDevDetail->devType))))
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "l4db_InitWimax - using default Laptop pDevDetail->devType = [%s].",pDevDetail->devType);
		OSAL_strncpy_s(pDevDetail->devType, (sizeof(char)*MAX_DEV_TYPE_SIZE),"Laptop", (6*sizeof(char)));
	}

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "l4db_InitWimax - after copy pDevDetail->devType = [%s].",pDevDetail->devType);
	if (( FALSE == (OSAL_stricmp (L4DB_DEV_TYPE_CONST,pDevDetail->devType))) || ( FALSE == (OSAL_stricmp (L4DB_DEV_TYPE_UPPER_CONST,pDevDetail->devType))) || ( FALSE == (OSAL_stricmp ("",pDevDetail->devType)))){
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "l4db_InitWimax - building SWV2 for Laptop.");
		// V5 SWV2 
		OSAL_strncat_s(pVersion, MAX_SWV2_NAME_SIZE,  pDevDetail->devType, OSAL_strnlen(pDevDetail->devType, MAX_DEV_TYPE_SIZE));
		OSAL_strncat_s(pVersion, MAX_SWV2_NAME_SIZE, L4DB_XML_TOKEN_DASH, strlen(L4DB_XML_TOKEN_DASH));
		OSAL_strncat_s(pVersion, MAX_SWV2_NAME_SIZE, pRadioModule->productVersions.manufacturer, OSAL_strnlen(pRadioModule->productVersions.manufacturer, MAX_MAN_NAME_SIZE));
		OSAL_strncat_s(pVersion, MAX_SWV2_NAME_SIZE, L4DB_XML_TOKEN_DASH, strlen(L4DB_XML_TOKEN_DASH));
		OSAL_strncat_s(pVersion, MAX_SWV2_NAME_SIZE, pRadioModule->productVersions.model, OSAL_strnlen(pRadioModule->productVersions.model, MAX_MOD_NAME_SIZE));
		OSAL_strncat_s(pVersion, MAX_SWV2_NAME_SIZE, L4DB_XML_TOKEN_DASH, strlen(L4DB_XML_TOKEN_DASH));
		OSAL_strncat_s(pVersion, MAX_SWV2_NAME_SIZE, pRadioModule->productVersions.swVersion, OSAL_strnlen(pRadioModule->productVersions.swVersion, MAX_VERSION_SIZE));
		OSAL_strncat_s(pVersion, MAX_SWV2_NAME_SIZE, L4DB_XML_TOKEN_DASH, strlen(L4DB_XML_TOKEN_DASH));
		OSAL_strncat_s(pVersion, MAX_SWV2_NAME_SIZE, pTermEquipment->productVersions.manufacturer, OSAL_strnlen(pTermEquipment->productVersions.manufacturer, WMX_MANUFACTURER_NAME_MAX_LENGTH));
		OSAL_strncat_s(pVersion, MAX_SWV2_NAME_SIZE, L4DB_XML_TOKEN_DASH, strlen(L4DB_XML_TOKEN_DASH));
		OSAL_strncat_s(pVersion, MAX_SWV2_NAME_SIZE, pRadioModule->productVersions.swVersion, OSAL_strnlen(pRadioModule->productVersions.swVersion, MAX_VERSION_SIZE));
		OSAL_strncat_s(pVersion, MAX_SWV2_NAME_SIZE, L4DB_XML_TOKEN_DASH, strlen(L4DB_XML_TOKEN_DASH));
		// Init SW version with OS version
		res = OSAL_GetOSVersion(pTermEquipment->productVersions.swVersion);	

		if (!res)
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4db_InitWimax - Failed to build OS version string.");
		}
		OSAL_strncat_s(pVersion, MAX_SWV2_NAME_SIZE, pTermEquipment->productVersions.swVersion, OSAL_strnlen(pTermEquipment->productVersions.swVersion, MAX_VERSION_SIZE));
		//OSAL_strncat_s(pVersion, MAX_SWV2_NAME_SIZE, L4DB_XML_TOKEN_DASH, strlen(L4DB_XML_TOKEN_DASH));

		////V4 swv2
		//OSAL_strncat_s(pVersion, MAX_SWV2_NAME_SIZE, pRadioModule->productVersions.manufacturer, OSAL_strnlen(pRadioModule->productVersions.manufacturer, MAX_MAN_NAME_SIZE));
		//OSAL_strncat_s(pVersion, MAX_SWV2_NAME_SIZE, L4DB_XML_TOKEN_DASH, strlen(L4DB_XML_TOKEN_DASH));
		//OSAL_strncat_s(pVersion, MAX_SWV2_NAME_SIZE, pRadioModule->productVersions.model, OSAL_strnlen(pRadioModule->productVersions.model, MAX_MOD_NAME_SIZE));
		//OSAL_strncat_s(pVersion, MAX_SWV2_NAME_SIZE, L4DB_XML_TOKEN_DASH, strlen(L4DB_XML_TOKEN_DASH));
		//OSAL_strncat_s(pVersion, MAX_SWV2_NAME_SIZE, pRadioModule->productVersions.swVersion, OSAL_strnlen(pRadioModule->productVersions.swVersion, MAX_VERSION_SIZE));
		//OSAL_strncat_s(pVersion, MAX_SWV2_NAME_SIZE, L4DB_XML_TOKEN_DASH, strlen(L4DB_XML_TOKEN_DASH));
		//OSAL_strncat_s(pVersion, MAX_SWV2_NAME_SIZE, pDevDetail->swVersion, OSAL_strnlen(pDevDetail->swVersion, MAX_VERSION_SIZE));
		//OSAL_strncat_s(pVersion, MAX_SWV2_NAME_SIZE, L4DB_XML_TOKEN_DASH, strlen(L4DB_XML_TOKEN_DASH));
		//
		//// Init SW version with OS version
		//res = l4db_GetOSVersion(pTermEquipment->productVersions.swVersion);	

		//if (!res)
		//{
		//	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4db_InitWimax - Failed to build OS version string.");
		//}
		//OSAL_strncat_s(pVersion, MAX_SWV2_NAME_SIZE, pTermEquipment->productVersions.swVersion, OSAL_strnlen(pTermEquipment->productVersions.swVersion, MAX_VERSION_SIZE));
		//OSAL_strncat_s(pVersion, MAX_SWV2_NAME_SIZE, L4DB_XML_TOKEN_DASH, strlen(L4DB_XML_TOKEN_DASH));
		//OSAL_strncat_s(pVersion, MAX_SWV2_NAME_SIZE, pTermEquipment->productVersions.manufacturer, OSAL_strnlen(pTermEquipment->productVersions.manufacturer, MAX_MAN_NAME_SIZE));
		
	}else {
		// Not Laptop Device
		// V5 SWV2 
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "l4db_InitWimax - building SWV2 for non Laptop.");
		OSAL_strncat_s(pVersion, MAX_SWV2_NAME_SIZE,  pDevDetail->devType, OSAL_strnlen(pDevDetail->devType, MAX_DEV_TYPE_SIZE));
		OSAL_strncat_s(pVersion, MAX_SWV2_NAME_SIZE, L4DB_XML_TOKEN_DASH, strlen(L4DB_XML_TOKEN_DASH));
		OSAL_strncat_s(pVersion, MAX_SWV2_NAME_SIZE, pRadioModule->productVersions.manufacturer, OSAL_strnlen(pRadioModule->productVersions.manufacturer, MAX_MAN_NAME_SIZE));
		OSAL_strncat_s(pVersion, MAX_SWV2_NAME_SIZE, L4DB_XML_TOKEN_DASH, strlen(L4DB_XML_TOKEN_DASH));
		OSAL_strncat_s(pVersion, MAX_SWV2_NAME_SIZE, pRadioModule->productVersions.model, OSAL_strnlen(pRadioModule->productVersions.model, MAX_MOD_NAME_SIZE));
		OSAL_strncat_s(pVersion, MAX_SWV2_NAME_SIZE, L4DB_XML_TOKEN_DASH, strlen(L4DB_XML_TOKEN_DASH));
		OSAL_strncat_s(pVersion, MAX_SWV2_NAME_SIZE, pRadioModule->productVersions.swVersion, OSAL_strnlen(pRadioModule->productVersions.swVersion, MAX_VERSION_SIZE));
		OSAL_strncat_s(pVersion, MAX_SWV2_NAME_SIZE, L4DB_XML_TOKEN_DASH, strlen(L4DB_XML_TOKEN_DASH));
		OSAL_strncat_s(pVersion, MAX_SWV2_NAME_SIZE, pDevInfo->manufacturer, OSAL_strnlen(pDevInfo->manufacturer, MAX_MAN_NAME_SIZE));
		OSAL_strncat_s(pVersion, MAX_SWV2_NAME_SIZE, L4DB_XML_TOKEN_DASH, strlen(L4DB_XML_TOKEN_DASH));
		OSAL_strncat_s(pVersion, MAX_SWV2_NAME_SIZE, pDevInfo->model, OSAL_strnlen(pDevInfo->model, MAX_MOD_NAME_SIZE));
		OSAL_strncat_s(pVersion, MAX_SWV2_NAME_SIZE, L4DB_XML_TOKEN_DASH, strlen(L4DB_XML_TOKEN_DASH));
		OSAL_strncat_s(pVersion, MAX_SWV2_NAME_SIZE,  pDevDetail->swVersion, OSAL_strnlen(pDevDetail->swVersion, MAX_VERSION_SIZE));
		OSAL_strncat_s(pVersion, MAX_SWV2_NAME_SIZE, L4DB_XML_TOKEN_DASH, strlen(L4DB_XML_TOKEN_DASH));
		// Init SW version with OS version
		res = OSAL_GetOSVersion(pTermEquipment->productVersions.swVersion);	
		if (!res)
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4db_InitWimax - Failed to build OS version string.");
		}
		OSAL_strncat_s(pVersion, MAX_SWV2_NAME_SIZE, pTermEquipment->productVersions.swVersion, OSAL_strnlen(pTermEquipment->productVersions.swVersion, MAX_VERSION_SIZE));
		//OSAL_strncat_s(pVersion, MAX_SWV2_NAME_SIZE, L4DB_XML_TOKEN_DASH, strlen(L4DB_XML_TOKEN_DASH));
	}
	L4Configurations_getAPDOFixSpecialCharacters(fixSpecialCharacters);
		
	// Default if no registry is to do special characters fix. only if key exist and false we won't do fix
	if (OSAL_stricmp(DEFAULT_TRUE_LOWER, fixSpecialCharacters) == 0)		
	{
		l4db_RemoveSpecialCharacters(pVersion);
	}	
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "l4db_InitWimax - swv2 = [%s].",pVersion);
}

/// <summary>
// This function recieves a string and removes special characters and spaces
/// </summary>
void l4db_RemoveSpecialCharacters(char* string)
{
	UINT32 i;
	UINT32 currCharIndex = 0;	
	char currChar;
	size_t tempStrLen = 0;

	tempStrLen = OSAL_strnlen(string, MAX_STRING_VALIDATE);

	if((MAX_STRING_VALIDATE) != tempStrLen)
	{
		for (i=0; i<tempStrLen; i++)
		{
			currChar = string[i];
			if (0 == OSAL_CAPI_strncmp(&currChar, ":", 1))
			{			
				OSAL_memcpy_s(&string[currCharIndex], 1, L4DB_XML_TOKEN_DOT, 1); 
				currCharIndex++;
			}
			// Skip the following special characters 
			else if ((0 != OSAL_CAPI_strncmp(&currChar, "/", 1)) &&
				(0 != OSAL_CAPI_strncmp(&currChar, "(", 1)) &&
				(0 != OSAL_CAPI_strncmp(&currChar, "\\", 1)) &&
				(0 != OSAL_CAPI_strncmp(&currChar, ")", 1)) &&
				(0 != OSAL_CAPI_strncmp(&currChar, "+", 1)) &&
				(0 != OSAL_CAPI_strncmp(&currChar, " ", 1)))	
			{					
				OSAL_memcpy_s(&string[currCharIndex], 1, &string[i], 1); 
				currCharIndex++;
			}			
		}	
	}
	string[currCharIndex] = '\0';
}

