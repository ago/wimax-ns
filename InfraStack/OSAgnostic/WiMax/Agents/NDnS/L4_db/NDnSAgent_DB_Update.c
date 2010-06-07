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
#include "NDnSAgent_Monitor.h"
#include "wimax_osal_config_controler.h"
#include "wimax_osal_services_cmn.h"
#include "wimax_osal_crypt_services.h"
#include "L4ConfigurationManager.h"
#include "NDnSAgent_Utils.h"

//This file includes methods for handling all different APDO command - set, get, update and add

///<summary>
/// updates a bandwidth value
///</summary>
wmx_Status_t l4db_UpdateBwValue(wmx_pBW_t	pBW,
								void		*pInValue,
								int		*pBufferSize,
								wmx_pAPDOType_t pAPDOType,
								apdo_DbCmd_t	cmd)
{
	char				buff[BUFF_SIZE];
	int					intArg;
	wmx_Status_t		rc = WMX_ST_FAIL;

	switch(cmd)
	{
		case APDO_AddCmd:
		case APDO_UpdateCmd:

			if(APDO_String == *pAPDOType)
			{
				OSAL_strcpy_s(buff, BUFF_SIZE, (const char *)pInValue);
			}

			else if(APDO_Integer == *pAPDOType)
			{
				OSAL_sprintf_s(buff, sizeof(buff) - 1, "%d", *(int *)pInValue);				
			}

			else
			{
				rc = WMX_ST_WRONG_ARGUMENT;
				break;
			}

			rc = ConvertToBandWidth( buff, pBW);
			break;

		case APDO_GetCmd:

			ConvertBandWidthToStr(*pBW, buff, BUFF_SIZE);
			OSAL_sscanf_s(buff, "%d", &intArg);
			rc = l4db_SetIntegerValueNew(&intArg, pBufferSize, pInValue, pAPDOType, cmd);
			break;

		case APDO_DeleteCmd:
			*pBW = 0;
			rc = WMX_ST_OK ;
			break;
	}

	return rc;
}



///<summary>
/// updates an FFT value
///</summary>
wmx_Status_t l4db_UpdateFftValue(wmx_pFFT_t pFft,
								 void *pInValue,
								 wmx_pAPDOType_t pAPDOType,
								 apdo_DbCmd_t cmd)
{
	char			buff[BUFF_SIZE];
	wmx_Status_t	rc = WMX_ST_FAIL;

	switch(cmd)
	{
		case APDO_AddCmd:
		case APDO_UpdateCmd:
			
			// set the FFT
			if(APDO_Integer == *pAPDOType)
			{
				OSAL_sprintf_s(buff,sizeof(buff) - 1, "%d", *(int *)pInValue);
			}
			else if(APDO_String == *pAPDOType)
			{
				OSAL_strcpy_s(buff, BUFF_SIZE, (char*)pInValue);
			}
			else
			{
				rc = WMX_ST_WRONG_ARGUMENT;
				break;
			}
			
			rc = ConvertToFFT(buff, pFft);
			break;

		case APDO_GetCmd:

			ConvertFFTtoStr(*pFft, buff, BUFF_SIZE);
			OSAL_sscanf_s(buff, "%d", pInValue);
			*pAPDOType = APDO_Integer;
			rc = WMX_ST_OK ;
			break;

		case APDO_DeleteCmd:
			*pFft = L4DB_INVALID_INDEX;
			rc = WMX_ST_OK ;
			break;
		}

	return rc;
}

///<summary>
/// updates preambles value
///</summary>
wmx_Status_t l4db_UpdatePreamblesValue(wmx_Preambles_t preambles,
									   void *pInValue,
									   int  *pBufferSize,
									   wmx_pAPDOType_t pAPDOType,
									   apdo_DbCmd_t cmd)
{
	wmx_Status_t	rc = WMX_ST_FAIL;

	switch(cmd)
	{
	case APDO_AddCmd:
	case APDO_UpdateCmd:

		if(APDO_String == *pAPDOType)
		{
			ConvertToPreamblesBitmap(preambles, pInValue);
			rc = WMX_ST_OK ;
		}
		break;

	case APDO_GetCmd:
		// check if we have space for the ASCII value and for the null
		if(*pBufferSize >= ARRAY_SIZE(preambles) * 2 + 1)
		{
			ConvertPreamblesBitmapToStr(preambles, (char *)pInValue);
			*pAPDOType = APDO_String;
			rc = WMX_ST_OK ;
		}
		break;

	case APDO_DeleteCmd:

		memset(preambles, 0, sizeof(preambles));
		rc = WMX_ST_OK ;
		break;
	}

	return rc;
}


///<summary>
/// updates duplex mode value
///</summary>
wmx_Status_t l4db_UpdateDuplexModeValue(wmx_pDuplexMode_t pDuplexMode,
										void			  *pInValue,
										int 			  *pBufferSize,
										wmx_pAPDOType_t	   pAPDOType,
										apdo_DbCmd_t	   cmd)
{
	wmx_Status_t	rc = WMX_ST_FAIL;
	int				intVal;

	switch(cmd)
	{
	case APDO_AddCmd:
	case APDO_UpdateCmd:

		if(APDO_String == *pAPDOType)
		{
			intVal = atoi((const char*) pInValue);
			*pAPDOType = APDO_Integer;
		}

		else if(APDO_Integer == *pAPDOType)
		{
			intVal = *((int*)pInValue);
		}

		else
		{
			rc = WMX_ST_WRONG_ARGUMENT;
			break;
		}
		
		if((intVal >=0) && (intVal <=255))
		{
			rc = l4db_SetIntegerValueNew((int *)pDuplexMode, pBufferSize
			, &intVal, pAPDOType, cmd);
		}
		else
		{
			rc = WMX_ST_WRONG_ARGUMENT;
		}
		break;

	case APDO_GetCmd:

			rc = l4db_SetIntegerValueNew((int *)pDuplexMode, pBufferSize
				, (int *)pInValue, pAPDOType, cmd);

			*pAPDOType = APDO_Integer;

		break;
	case APDO_DeleteCmd:

		*pDuplexMode = (wmx_DuplexMode_t)L4DB_INVALID_INDEX;
		rc = WMX_ST_OK ;
		break;
	}
	return rc;
}


///<summary>
/// updates the priority value
///</summary>
wmx_Status_t l4db_UpdatePriorityValue(wmx_pPriority_t	 pPriority,
										void			 *pInValue,
										int 			 *pBufferSize,
										wmx_pAPDOType_t	  pAPDOType,
										apdo_DbCmd_t	  cmd)
{
	wmx_Status_t	rc = WMX_ST_FAIL;
	int				intVal;

	switch(cmd)
	{
	case APDO_AddCmd:
	case APDO_UpdateCmd:

		if(APDO_String == *pAPDOType)
		{
			intVal = atoi((char*)pInValue);
			*pAPDOType = APDO_Integer;
		}

		else if(APDO_Integer == *pAPDOType)
		{
			intVal = *((int*)pInValue);
		}

		else
		{
			rc = WMX_ST_WRONG_ARGUMENT;
			break;
		}

		if((intVal >=0) && (intVal <=255))
		{
			rc = l4db_SetIntegerValueNew((int *)pPriority, pBufferSize
				, (int *)&intVal, pAPDOType, cmd);
		}
		else
		{
			rc = WMX_ST_WRONG_ARGUMENT;
		}

		break;

	case APDO_GetCmd:

			rc = l4db_SetIntegerValueNew((int *)pPriority, pBufferSize
				, (int *)pInValue, pAPDOType, cmd);

			*pAPDOType = APDO_Integer;
		break;
	case APDO_DeleteCmd:

		*pPriority = (wmx_Priority_t)L4DB_INVALID_INDEX;
		rc = WMX_ST_OK ;
		break;
	}
	return rc;
}


///<summary>
/// updates the any value
///</summary>
wmx_Status_t l4db_UpdateAnyValue(pAny_t			  pAny,
								void			 *pInValue,
								int 			 *pBufferSize,
								wmx_pAPDOType_t	  pAPDOType,
								apdo_DbCmd_t	  cmd)
{
	wmx_Status_t	rc = WMX_ST_FAIL;
	int				intVal;

	switch(cmd)
	{
	case APDO_AddCmd:
	case APDO_UpdateCmd:

		if(APDO_String == *pAPDOType)
		{
			intVal = atoi((char*)pInValue);
			*pAPDOType = APDO_Integer;
		}

		else if(APDO_Integer == *pAPDOType)
		{
			intVal = *((int*)pInValue);
		}

		else
		{
			rc = WMX_ST_WRONG_ARGUMENT;
			break;
		}

		if((intVal >=0) && (intVal <=3))
		{
			rc = l4db_SetIntegerValueNew((int *)pAny, pBufferSize
				, (int *)&intVal, pAPDOType, cmd);
		}
		else
		{
			rc = WMX_ST_WRONG_ARGUMENT;
		}

		break;

	case APDO_GetCmd:

		rc = l4db_SetIntegerValueNew((int *)pAny, pBufferSize
			, (int *)pInValue, pAPDOType, cmd);

		*pAPDOType = APDO_Integer;
		break;
	case APDO_DeleteCmd:

		*pAny = (Any_t)L4DB_INVALID_INDEX;
		rc = WMX_ST_OK ;
		break;
	}
	return rc;
}

///<summary>
/// updates the select policy value
///</summary>
wmx_Status_t l4db_UpdateSelectPolicyValue(pSelectPolicy_t			  pSelectPolicy,
										void			 *pInValue,
										int 			 *pBufferSize,
										wmx_pAPDOType_t	  pAPDOType,
										apdo_DbCmd_t	  cmd)
{
	wmx_Status_t	rc = WMX_ST_FAIL;
	int				intVal;

	switch(cmd)
	{
	case APDO_AddCmd:
	case APDO_UpdateCmd:

		if(APDO_String == *pAPDOType)
		{
			intVal = atoi((char*)pInValue);
			*pAPDOType = APDO_Integer;
		}

		else if(APDO_Integer == *pAPDOType)
		{
			intVal = *((int*)pInValue);
		}

		else
		{
			rc = WMX_ST_WRONG_ARGUMENT;
			break;
		}

		if((intVal >=0) && (intVal <=3))
		{
			rc = l4db_SetIntegerValueNew((int *)pSelectPolicy, pBufferSize
				, (int *)&intVal, pAPDOType, cmd);
		}
		else
		{
			rc = WMX_ST_WRONG_ARGUMENT;
		}

		break;

	case APDO_GetCmd:

		rc = l4db_SetIntegerValueNew((int *)pSelectPolicy, pBufferSize
			, (int *)pInValue, pAPDOType, cmd);

		*pAPDOType = APDO_Integer;
		break;
	case APDO_DeleteCmd:

		*pSelectPolicy = (SelectPolicy_t)L4DB_INVALID_INDEX;
		rc = WMX_ST_OK ;
		break;
	}
	return rc;
}

///<summary>
/// updates a channel info using a given APDO path according to the APDO command type
///</summary>
wmx_Status_t l4db_UpdateChannelInfoFromPath(pChannelPlan_t pChannelPlan,
											char			*psPath,
											void			*pInValue,
											int				*pBufferSize,
											wmx_pAPDOType_t pAPDOType,
											apdo_DbCmd_t	cmd)

{
	char				* psToken;
	char				* psTokenValue;
	char				* nextpath;
	pChannelInfo_t		pChannel = NULL;
	wmx_Status_t		rc = WMX_ST_DATA_UNAVAILABLE;
	int					i;
	BOOL				allocated = FALSE, addSeperator = FALSE;
	size_t				tempStrLen = 0;

	if((NULL == pChannelPlan) || (NULL == pInValue))
	{
		return rc;
	}

	if(NULL != psPath)
	{
		//get the unique entry name
		nextpath = l4db_GetTokensFromPath(psPath, &psToken, &psTokenValue);

		if(NULL != psToken)
		{
			//find a channel info with the matching unique name
			pChannel = l4db_GetChannelInfo(pChannelPlan, psToken);

			// allocate new
			if((NULL == pChannel) && (APDO_AddCmd == cmd))
			{
				pChannel = l4db_AllocChannelInfo(pChannelPlan, psToken);
				allocated = TRUE;
			}

			if(NULL != pChannel)
			{
				if(NULL != nextpath)
				{	
					nextpath = l4db_GetTokensFromPath(nextpath, &psToken, &psTokenValue);

					//set \ get the values for the relevant tokens
					if((NULL != psToken) && (NULL == nextpath))
					{
						//channel id
						if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_ID))
						{
							rc = l4db_SetStringValueNew(pChannel->id,sizeof(pChannel->id), (char*)pInValue, 
								 pBufferSize, pAPDOType, cmd);
						}

						//first frequency
						if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_FIRST_FREQ))
						{
							rc = l4db_SetIntegerValueNew((int*)&pChannel->firstFreq, 
								pBufferSize, pInValue, pAPDOType, cmd);
						}

						//last frequency
						else if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_LAST_FREQ))
						{
							rc = l4db_SetIntegerValueNew((int*)&pChannel->lastFreq, 
								pBufferSize, pInValue, pAPDOType, cmd);
						} 

						//next frequency step
						else if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_NEXT_FREQ_STEP))
						{
							rc = l4db_SetIntegerValueNew((int*)&pChannel->nextFreq, 
								pBufferSize, pInValue, pAPDOType, cmd);
						} 

						//bandwidth
						else if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_BW))
						{
							rc = l4db_UpdateBwValue(&pChannel->bw, pInValue, pBufferSize, 
								pAPDOType, cmd);
						}

						//FFT size
						else if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_FFT_SIZE))
						{
							rc = l4db_UpdateFftValue(&pChannel->fft, pInValue,
								pAPDOType, cmd);
						}

						//preambles
						else if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_PREAMBLES))
						{
							rc = l4db_UpdatePreamblesValue(pChannel->preambleBitmap, pInValue,
								pBufferSize, pAPDOType, cmd);
						}

						//duplex mode
						else if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_DUPLEX_MODE))
						{
							rc = l4db_UpdateDuplexModeValue(&pChannel->duplexMode, pInValue, 
								pBufferSize, pAPDOType, cmd);
						}
					}

					//init the channel info if it has been allocated and we had an error
					if((WMX_ST_OK != rc) && (TRUE == allocated))
					{
						l4db_InitChannelInfo(pChannel);
					}
				}
				else//our path is empty
				{
					rc = WMX_ST_OK;

					//if get cmd, get the names of all the nodes children, separated by /
					if(APDO_GetCmd == cmd)
					{
						rc = l4db_SetStringValueNew(CHANNEL_INFO_CHILDREN_STR, strlen(CHANNEL_INFO_CHILDREN_STR) + 1,
							(char*)pInValue, pBufferSize, pAPDOType, cmd);

						*pAPDOType = APDO_Node;
					}
					else if(APDO_DeleteCmd == cmd)//we need to "delete" our node
					{

						l4db_InitChannelInfo(pChannel);//init the channel
					}
				}
			}
		}
	} 
	else //our path is empty
	{
		rc = WMX_ST_OK;

		//if get cmd, get the names of all the nodes children, separated by /
		if(APDO_GetCmd == cmd)
		{
			((char*)pInValue)[0] = '\0';

			for(i = 0 ; i< WMX_CHANNELS_MAX_NUM ; i++)
			{
				tempStrLen = OSAL_strnlen(pChannelPlan->channels[i].tagName, MAX_TAG_NAME_SIZE);
				if(0 != tempStrLen && MAX_TAG_NAME_SIZE != tempStrLen)
				{
					if(TRUE == addSeperator)
					{
						OSAL_strcat_s(pInValue, *pBufferSize, L4DB_XML_TOKEN_SEPERATOR);
					}
					else
					{
						//the first time we want to copy and not concatenate
						OSAL_strcpy_s(pInValue, *pBufferSize, pChannelPlan->channels[i].tagName);
						addSeperator = TRUE;
						continue;
					}

					OSAL_strcat_s(pInValue, *pBufferSize, pChannelPlan->channels[i].tagName);
				}
			}
			*pAPDOType = APDO_Node;
		}
		else if(APDO_DeleteCmd == cmd)//we need to "delete" our node
		{
			for(i = 0 ; i< WMX_NSP_IDS_MAX_NUM ; i++)
			{
				l4db_InitChannelInfo(&pChannelPlan->channels[i]);//init all channels
			}
		}
	}
	return rc;
}
///<summary>
/// updates a channel plan using a given APDO path according to the APDO command type
///</summary>
wmx_Status_t l4db_UpdateChannelPlanFromPath(pChannelPlan_t pChannelPlan,
											char	*psPath,
											void	*pInValue,
											int     *pBufferSize,
											wmx_pAPDOType_t pAPDOType,
											apdo_DbCmd_t cmd)

{
	char				* psToken;
	char				* psTokenValue;
	char				* nextpath;
	wmx_Status_t		rc = WMX_ST_DATA_UNAVAILABLE;

	if((NULL == pChannelPlan) || (NULL == pInValue))
	{
		return rc;
	}

	if(NULL != psPath)
	{
		nextpath = l4db_GetTokensFromPath(psPath, &psToken, &psTokenValue);

		if(NULL != psToken)
		{
			if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_ENTRIES))
			{
				rc = l4db_UpdateChannelInfoFromPath(pChannelPlan, nextpath, pInValue, pBufferSize, pAPDOType, cmd);
			}

			else if(NULL == nextpath)
			{
				//default bandwidth
				if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_BW))
				{
					rc = l4db_UpdateBwValue(&pChannelPlan->bw, pInValue, pBufferSize, pAPDOType, cmd);
				} 
				//default duplex mode
				else if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_DUPLEX_MODE))
				{
					rc = l4db_UpdateDuplexModeValue(&pChannelPlan->duplexMode, pInValue, pBufferSize, pAPDOType, cmd);
				}
				//default FFT size
				else if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_FFT_SIZE))
				{
					rc = l4db_UpdateFftValue(&pChannelPlan->fft, pInValue,
						pAPDOType, cmd);
				}
			}
		}
		else // we don't have token, check if this is a delete command, if so, "delete" the node
		{
			if(cmd == APDO_DeleteCmd)
			{
				l4db_InitChannelPlan(pChannelPlan);
			}

			rc = WMX_ST_OK ;
		}
	}
	else //our path is empty
	{
		rc = WMX_ST_OK;

		//if get cmd, get the names of all the nodes children, separated by /
		if(APDO_GetCmd == cmd)
		{
			rc = l4db_SetStringValueNew(CHANNEL_PLAN_CHILDREN_STR, strlen(CHANNEL_PLAN_CHILDREN_STR) + 1,
				(char*)pInValue, pBufferSize, pAPDOType, cmd);

			*pAPDOType = APDO_Node;
		}
		else if(APDO_DeleteCmd == cmd)//we need to "delete" our node
		{
			l4db_InitChannelPlan(pChannelPlan);//init the channel plan
		}
	}
	return rc;
}






///<summary>
/// updates a channel refs using a given APDO path according to the APDO command type
///</summary>
wmx_Status_t l4db_UpdateChannelsRefsFromPath(pChPlanRefId_t pChannelsRefs,
											char			*psPath,
											void			*pInValue,
											int				*pBufferSize,
											wmx_pAPDOType_t pAPDOType,
											apdo_DbCmd_t	cmd)

{
	char				* psToken;
	char				* psTokenValue;
	char				* nextpath;
	pChPlanRefId_t		pRef = NULL;
	wmx_Status_t		rc = WMX_ST_DATA_UNAVAILABLE;
	int					i;
	BOOL				allocated = FALSE, addSeperator = FALSE;
	size_t				tempStrLen = 0;

	if((NULL == pChannelsRefs) || (NULL == pInValue))
	{
		return rc;
	}

	if(NULL != psPath)
	{
		//get the unique entry name
		nextpath = l4db_GetTokensFromPath(psPath, &psToken, &psTokenValue);

		if(NULL != psToken)
		{
			//find a channel ref with the matching unique name
			pRef = l4db_GetChannelRef(pChannelsRefs, psToken);

			// allocate new
			if((NULL == pRef) && (APDO_AddCmd == cmd))
			{
				pRef = l4db_AllocChannelRef(pChannelsRefs, psToken);
				allocated = TRUE;
			}

			if(NULL != pRef)
			{
				if(NULL != nextpath)
				{	
					nextpath = l4db_GetTokensFromPath(nextpath, &psToken, &psTokenValue);

					//set \ get the values for the relevant tokens
					if((NULL != psToken) && (NULL == nextpath))
					{
						//channel id
						if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_REF_ID))
						{
							rc = l4db_SetStringValueNew(pRef->id, sizeof(pRef->id),
								(char *)pInValue, pBufferSize, pAPDOType, cmd);
						}
					}

					//init the channel ref if it has been allocated and we had an error
					if((WMX_ST_OK != rc) && (TRUE == allocated))
					{
						l4db_InitChannelRef(pRef);
					}
				}
				else//our path is empty
				{
					rc = WMX_ST_OK;

					//if get cmd, get the names of all the nodes children, separated by /
					if(APDO_GetCmd == cmd)
					{
						rc = l4db_SetStringValueNew(L4DB_XML_TOKEN_REF_ID, strlen(L4DB_XML_TOKEN_REF_ID) + 1,
							(char*)pInValue, pBufferSize, pAPDOType, cmd);

						*pAPDOType = APDO_Node;
					}
					else if(APDO_DeleteCmd == cmd)//we need to "delete" our node
					{

						l4db_InitChannelRef(pRef);//init the channel
					}
				}
			}
		}
	} 
	else //our path is empty
	{
		rc = WMX_ST_OK;

		//if get cmd, get the names of all the nodes children, separated by /
		if(APDO_GetCmd == cmd)
		{
			((char*)pInValue)[0] = '\0';
			*pAPDOType = APDO_Node;

			for(i = 0 ; i< WMX_CHANNELS_MAX_NUM ; i++)
			{
				tempStrLen = OSAL_strnlen(pChannelsRefs[i].tagName, MAX_TAG_NAME_SIZE);
				if(0 != tempStrLen && MAX_TAG_NAME_SIZE != tempStrLen)
				{
					if(TRUE == addSeperator)
					{
						OSAL_strcat_s(pInValue, *pBufferSize, L4DB_XML_TOKEN_SEPERATOR);
					}
					else
					{
						//the first time we want to copy and not concatenate
						OSAL_strcpy_s(pInValue, *pBufferSize, pChannelsRefs[i].tagName);
						addSeperator = TRUE;
						continue;
					}

					OSAL_strcat_s(pInValue, *pBufferSize, pChannelsRefs[i].tagName);
				}
			}
		}
		else if(APDO_DeleteCmd == cmd)//we need to "delete" our node
		{
			for(i = 0 ; i< WMX_NSP_IDS_MAX_NUM ; i++)
			{
				l4db_InitChannelRef(&pChannelsRefs[i]);//init all channels
			}
		}
	}
	return rc;
}
///<summary>
/// updates the list of H NSPs using a given APDO path according to the APDO command type
///</summary>
wmx_Status_t l4db_UpdateHnspsFromPath(pHomeNsp_t	pHnsps,
									  char			*psPath,
									  void			*pInValue,
									  int 			*pBufferSize,
									  wmx_pAPDOType_t pAPDOType,
									  apdo_DbCmd_t	cmd,
									  char*			nspTagName)
{
	char				* psToken;
	char				* psTokenValue;
	char				* nextpath;
	pHomeNsp_t			pHnsp;
	wmx_Status_t		rc = WMX_ST_DATA_UNAVAILABLE;
	int					invalidIndex = L4DB_INVALID_INDEX;
	wmx_APDOType_t		newApdoType;
	int					i;
	BOOL				allocated = FALSE, addSeperator = FALSE;
	size_t				tempStrLen = 0;

	if((NULL == pHnsps) || (NULL == pInValue))
	{
		return rc;
	}

	if(NULL != psPath)
	{
		//get the H_NSPs unique name
		nextpath = l4db_GetTokensFromPath(psPath, &psToken, &psTokenValue);

		if(NULL != psToken)
		{
			//search if we have this unique id
			pHnsp = l4db_GetHnsp(pHnsps, psToken);

			// allocate new
			if((NULL == pHnsp) && (APDO_AddCmd == cmd))
			{
				pHnsp = l4db_AllocHnsp(pHnsps, psToken);
				allocated = TRUE;
			}

			if(NULL != pHnsp)
			{
				if(NULL != nextpath)
				{
					nextpath = l4db_GetTokensFromPath(nextpath, &psToken, &psTokenValue);

					if((NULL != psToken) && (NULL == nextpath))
					{
						//nsp id
						if((FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_H_NSP_ID)) ||
						   (FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_H_NSP_ID_DASH)))							
						{
							switch(cmd)
							{
								case APDO_AddCmd:
								case APDO_UpdateCmd:
									
									//verify that it is legal to add this NSP ID
									if(TRUE == l4db_IsLegalToAddNspId(*(int*)pInValue, pHnsp->tagName, nspTagName))
									{
										rc = l4db_SetIntegerValueNew((int*)&pHnsp->nspId, pBufferSize, (int*)pInValue, pAPDOType, cmd);
									}
									else
									{
										rc = WMX_ST_FAIL;
										TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4db_UpdateHnspsFromPath: illegal NSP ID %d", (int*)&pHnsp->nspId);
									}
									break;

								case APDO_GetCmd:

									rc = l4db_SetIntegerValueNew((int*)&pHnsp->nspId, pBufferSize, (int*)pInValue, pAPDOType, cmd);
									break;

								case APDO_DeleteCmd:
									//we don't want the NSP ID to be zero, deleting it means to set it to -1
									newApdoType = APDO_Integer;
									rc = l4db_SetIntegerValueNew((int*)&pHnsp->nspId, pBufferSize, &invalidIndex, &newApdoType, APDO_UpdateCmd);
									break;
							}
						}
					}
				}
				else//our path is empty
				{
					rc = WMX_ST_OK;

					//if get cmd, get the names of all the nodes children, separated by /
					if(APDO_GetCmd == cmd)
					{
						rc = l4db_SetStringValueNew(H_NSP_CHILDREN_STR, strlen(H_NSP_CHILDREN_STR) + 1,
							(char*)pInValue, pBufferSize, pAPDOType, cmd);

						*pAPDOType = APDO_Node;
					}
					else if(APDO_DeleteCmd == cmd)//we need to "delete" our node
					{
						l4db_InitHnsp(pHnsp);//init all Home NSPs
					}
				}
				//init the h_nsp if it has been allocated but an error has occured
				if((WMX_ST_OK != rc) && (TRUE == allocated))
				{
					l4db_InitHnsp(pHnsp);
				}
			}
		}
	}
	else//our path is empty
	{
		rc = WMX_ST_OK;

		//if get cmd, get the names of all the nodes children, separated by /
		if(APDO_GetCmd == cmd)
		{
			((char*)pInValue)[0] = '\0';

			for(i = 0 ; i< WMX_NSP_IDS_MAX_NUM ; i++)
			{
				tempStrLen = OSAL_strnlen(pHnsps[i].tagName, MAX_TAG_NAME_SIZE);
				if(0 != tempStrLen && MAX_TAG_NAME_SIZE != tempStrLen)
				{
					if(TRUE == addSeperator)
					{
						OSAL_strcat_s(pInValue, *pBufferSize, L4DB_XML_TOKEN_SEPERATOR);
					}
					else
					{
						//the first time we want to copy and not concatenate
						OSAL_strcpy_s(pInValue, *pBufferSize, pHnsps[i].tagName);
						addSeperator = TRUE;
						continue;
					}

					OSAL_strcat_s(pInValue, *pBufferSize, pHnsps[i].tagName);
				}
			}
			*pAPDOType = APDO_Node;
		}
		else if(APDO_DeleteCmd == cmd)//we need to "delete" our node
		{
			for(i = 0 ; i< WMX_NSP_IDS_MAX_NUM ; i++)
			{
				l4db_InitHnsp(&pHnsps[i]);//init all Home NSPs
			}
		}
	}
	return rc;
}

///<summary>
/// updates CAPL entries data using a given APDO path according to the APDO command type
///</summary>
wmx_Status_t l4db_UpdateCaplEntryFromPath(pL4db_Nap_t	pNaps,
										  char			*psPath,
										  void			*pInValue,
										  int			*pBufferSize,
										  wmx_pAPDOType_t pAPDOType,
										  apdo_DbCmd_t	 cmd,
										  char *		 nspTagName)
{
	char				* psToken;
	char				* psTokenValue;
	char				* nextpath;
	pL4db_Nap_t			pNap = NULL;
	int					i;
	wmx_NAPid_t			napID;
	wmx_Status_t		rc = WMX_ST_DATA_UNAVAILABLE;
	BOOL				allocated = FALSE, addSeperator = FALSE;
	char				buff[BUFF_SIZE];
	size_t				tempStrLen = 0;

	if((NULL == pNaps) || (NULL == pInValue))
	{
		return rc;
	}

	//get the enrty's unique name
	if(NULL != psPath)
	{
		nextpath = l4db_GetTokensFromPath(psPath, &psToken, &psTokenValue);

		if(NULL != psToken)
		{
			pNap = l4db_GetCaplNapInfo(pNaps, psToken);

			// allocate new
			if((NULL == pNap) && (APDO_AddCmd == cmd))
			{
				pNap = l4db_AllocCaplNap(pNaps, psToken);
				allocated = TRUE;
			}

			if(NULL != pNap)
			{
				if(NULL != nextpath)
				{
					nextpath = l4db_GetTokensFromPath(nextpath, &psToken, &psTokenValue);

					if(NULL != psToken)
					{
						if(NULL == nextpath)
						{
							//NAP ID
							if((FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_NAP_ID)) ||
							   (FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_NAP_ID_DASH)))
							{

								switch(cmd)
								{
								case APDO_AddCmd:
								case APDO_UpdateCmd:

									if(APDO_Integer == *pAPDOType)
									{
										l4db_ConvertNapIdIntToNapIdType(napID,*(int *)pInValue);
									}

									else if(APDO_String == *pAPDOType)
									{
										l4db_ConvertNapIdStrToNapIdType(napID, (char*)pInValue);
										*pAPDOType = APDO_Integer;
									}

									else
									{
										rc = WMX_ST_WRONG_ARGUMENT;
										break;
									}

									//verify that it is legal to add this NAP ID
									if(TRUE == l4db_IsLegalToAddNapId(napID, pNap->tagName, nspTagName))
									{
										memcpy(pNap->napID, napID, sizeof(pNap->napID));
										rc = WMX_ST_OK;
									}
									else
									{
										rc = WMX_ST_FAIL;
										l4db_ConvertNapIdToStr(pInValue, buff);
										TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, 
												"l4db_UpdateCaplEntryFromPath: illegal NAP ID %s", buff);
									}
									break;

								case APDO_GetCmd:
									l4db_ConvertNapIdTypeToNapIdInt(pNap->napID, pInValue);
									*pAPDOType = APDO_Integer;
									rc = WMX_ST_OK;
									break;

								case APDO_DeleteCmd:

									l4db_SetNapidEmpty(napID);
									memcpy(&pNap->napID, napID, sizeof(pNap->napID));
									rc = WMX_ST_OK;
									break;
								
								}
							}

							//priority
							else if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_PRIORITY))
							{
								rc = l4db_UpdatePriorityValue(&pNap->priority, pInValue, pBufferSize, pAPDOType, cmd);
							}
						}

						//channel plan
						if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_CH_PLAN_REF_IDS))
						{
							rc = l4db_UpdateChannelsRefsFromPath(pNap->channelPlanRefIds, nextpath,
								pInValue, pBufferSize, pAPDOType, cmd);
						}
					}
				}
				else//our path is empty
				{
					rc = WMX_ST_OK;

					//we have to return all the entries' unique names separated by /
					if(APDO_GetCmd == cmd)
					{
						rc = l4db_SetStringValueNew(NAP_ENTRY_CHILDREN_STR, strlen(NAP_ENTRY_CHILDREN_STR) + 1,
							(char*)pInValue, pBufferSize, pAPDOType, cmd);

						*pAPDOType = APDO_Node;
					}
					else if(APDO_DeleteCmd == cmd)//we need to "delete" our nodes
					{
						l4db_InitNap(pNap); //init all roaming infos
					}
				}
				//if the NAP has been allocated and error occurred, free it
				if((WMX_ST_OK != rc) && (TRUE == allocated))
				{
					l4db_InitNap(pNap);
				}
			}
		}
	}
	else //our path is empty
	{
		rc = WMX_ST_OK;

		//we have to return all the entries' unique names separated by /
		if(APDO_GetCmd == cmd)
		{
			((char*)pInValue)[0] = '\0';
			*pAPDOType = APDO_Node;

			for(i = 0 ; i < WMX_NAPS_MAX_NUM ; i++)
			{
				tempStrLen = OSAL_strnlen(pNaps[i].tagName, MAX_TAG_NAME_SIZE);
				if(0 != tempStrLen && MAX_TAG_NAME_SIZE != tempStrLen)
				{
					if(TRUE == addSeperator)
					{
						OSAL_strcat_s(pInValue, *pBufferSize, L4DB_XML_TOKEN_SEPERATOR);
					}
					else
					{
						//the first time we want to copy and not concatenate
						OSAL_strcpy_s(pInValue, *pBufferSize, pNaps[i].tagName);
						addSeperator = TRUE;
						continue;
					}

					OSAL_strcat_s(pInValue, *pBufferSize, pNaps[i].tagName);
				}
			}

		}
		else if(APDO_DeleteCmd == cmd)//we need to "delete" our nodes
		{
			for(i = 0 ; i < WMX_NAPS_MAX_NUM ; i++)
			{
				l4db_InitNap(&pNaps[i]); //init all roaming infos
			}
		}
	}
	return rc;
}
///<summary>
/// updates CAPL data using a given APDO path according to the APDO command type
///</summary>
wmx_Status_t l4db_UpdateCaplFromPath(pCapl_t	pCapl,
									 char		*psPath,
									 void		*pInValue,
									 int		*pBufferSize,
									 wmx_pAPDOType_t pAPDOType,
									 apdo_DbCmd_t cmd,
									 char *			nspTagName)
{
	char				* psToken;
	char				* psTokenValue;
	char				* nextpath;
	wmx_Status_t		rc = WMX_ST_DATA_UNAVAILABLE;

	if((NULL == pCapl) || (NULL == pInValue))
	{
		return rc;
	}

	if(NULL != psPath)
	{
		nextpath = l4db_GetTokensFromPath(psPath, &psToken, &psTokenValue);

		if(NULL != psToken)
		{
			//entry
			if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_ENTRIES))
			{
				rc = l4db_UpdateCaplEntryFromPath(pCapl->naps, nextpath, pInValue, pBufferSize, pAPDOType, cmd, nspTagName);
			}
			//any
			else if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_ANY))
			{
				if(NULL == nextpath)
				{
					rc = l4db_UpdateAnyValue(&pCapl->any, pInValue, pBufferSize, pAPDOType, cmd);
				}
			}
			//select policy
			else if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_SELECT_POLICY))
			{
				if(NULL == nextpath)
				{
					rc = l4db_UpdateSelectPolicyValue(&pCapl->selectPolicy, pInValue, pBufferSize, pAPDOType, cmd);
				}
			}
		}
	}

	else//our path is empty
	{
		rc = WMX_ST_OK;

		//we need to return all the nodes children separated by /
		if(APDO_GetCmd == cmd)
		{
			rc = l4db_SetStringValueNew(CAPL_RAPL_CHILDREN_STR, strlen(CAPL_RAPL_CHILDREN_STR) + 1,
				(char*)pInValue, pBufferSize, pAPDOType, cmd);

			*pAPDOType = APDO_Node;
		}
		else if(APDO_DeleteCmd == cmd)
		{
			l4db_InitCapl(pCapl);
		}
	}
	return rc;
} 

///<summary>
/// updates roaming infos using a given APDO path according to the APDO command type
///</summary>
wmx_Status_t l4db_UpdateRaplEntryFromPath(pRoamingPartnerInfo_t	pRoamingInfos,
										  char					*psPath,
										  void					*pInValue,
										  int					*pBufferSize,
										  wmx_pAPDOType_t		pAPDOType,
										  apdo_DbCmd_t			cmd)
{
	char					* psToken;
	char					* psTokenValue;
	char					* nextpath;
	pRoamingPartnerInfo_t	pRoamingInfo = NULL;
	wmx_Status_t			rc = WMX_ST_DATA_UNAVAILABLE;
	int						invalidIndex = L4DB_INVALID_INDEX;
	int						i;
	wmx_APDOType_t			newApdoType;
	BOOL					allocated = FALSE, addSeperator = FALSE;
	size_t					tempStrLen = 0;

	if((NULL == pRoamingInfos) || (NULL == pInValue))
	{
		return rc;
	}

	
	if(NULL != psPath)
	{
		//get the enrty's unique name
		nextpath = l4db_GetTokensFromPath(psPath, &psToken, &psTokenValue);

		if(NULL != psToken)
		{
			pRoamingInfo = l4db_GetRoamingInfo(pRoamingInfos, psToken);

			// allocate new
			if((NULL == pRoamingInfo) && (APDO_AddCmd == cmd))
			{
				pRoamingInfo = l4db_AllocRoamingInfo(pRoamingInfos, psToken);
				allocated = TRUE;
			}

			if(NULL != pRoamingInfo)
			{
				if(NULL != nextpath)
				{
					nextpath = l4db_GetTokensFromPath(nextpath, &psToken, &psTokenValue);

					if((NULL !=psToken) && (NULL == nextpath))
					{
						//V_NSP ID
						if((FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_V_NSP_ID)) ||
						   (FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_V_NSP_ID_DASH)))							
						{
							switch(cmd)
							{
							case APDO_AddCmd:
							case APDO_GetCmd:
							case APDO_UpdateCmd:

								rc = l4db_SetIntegerValueNew((int*)&pRoamingInfo->vNspID, pBufferSize,
									(int *)pInValue, pAPDOType, cmd);
								break;

							case APDO_DeleteCmd:
								//we don't want the v nsp id to be zero, deleting it means to set it to -1
								newApdoType = APDO_Integer;
								rc = l4db_SetIntegerValueNew((int*)&pRoamingInfo->vNspID, pBufferSize, &invalidIndex, &newApdoType, APDO_UpdateCmd);
								break;
							}
						}

						//priority
						if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_PRIORITY))
						{
							rc = l4db_UpdatePriorityValue(&pRoamingInfo->priority, pInValue, pBufferSize, pAPDOType, cmd);
						}
					}
				}
				else //our path is empty
				{
					rc = WMX_ST_OK;

					//we have to return all the entries' unique names separated by /
					if(APDO_GetCmd == cmd)
					{
						rc = l4db_SetStringValueNew(ROAMING_INFO_CHILDREN_STR, strlen(ROAMING_INFO_CHILDREN_STR) + 1,
							(char*)pInValue, pBufferSize, pAPDOType, cmd);

						*pAPDOType = APDO_Node;
					}
					else if(APDO_DeleteCmd == cmd)//we need to "delete" our nodes
					{
						l4db_InitRoamingInfo(pRoamingInfo); //init all roaming infos
					}
				}

				//init the roaming info if it has been allocated and an error has occurred
				if((WMX_ST_OK != rc) && (TRUE == allocated))
				{
					l4db_InitRoamingInfo(pRoamingInfo);
				}
			}
		}
	}
	else //our path is empty
	{
		rc = WMX_ST_OK;

		//we have to return all the entries' unique names separated by /
		if(APDO_GetCmd == cmd)
		{
			((char *)pInValue)[0] = '\0';
			*pAPDOType = APDO_Node;

			for(i = 0 ; i < MAX_ROAMING_PARTNERS ; i++)
			{
				tempStrLen = OSAL_strnlen(pRoamingInfos[i].tagName, MAX_TAG_NAME_SIZE);
				if(0 != tempStrLen && MAX_TAG_NAME_SIZE != tempStrLen)
				{
					if(TRUE == addSeperator)
					{
						OSAL_strcat_s(pInValue, *pBufferSize, L4DB_XML_TOKEN_SEPERATOR);
					}
					else
					{
						//the first time we want to copy and not concatenate
						OSAL_strcpy_s(pInValue, *pBufferSize, pRoamingInfos[i].tagName);
						addSeperator = TRUE;
						continue;
					}

					OSAL_strcat_s(pInValue, *pBufferSize, pRoamingInfos[i].tagName);
				}
			}
		}
		else if(APDO_DeleteCmd == cmd)//we need to "delete" our nodes
		{
			for(i = 0 ; i < MAX_ROAMING_PARTNERS ; i++)
			{
				l4db_InitRoamingInfo(&pRoamingInfos[i]); //init all roaming infos
			}
		}
	}
	return rc;
}
///<summary>
/// updates RAPL data using a given APDO path according to the APDO command type
///</summary>
wmx_Status_t l4db_UpdateRaplFromPath(pRapl_t pRapl,
									 char	*psPath,
									 void	*pInValue,
									 int	*pBufferSize,
									 wmx_pAPDOType_t pAPDOType,
									 apdo_DbCmd_t cmd)
{
	char					* psToken;
	char					* psTokenValue;
	char					* nextpath;
	wmx_Status_t			rc = WMX_ST_DATA_UNAVAILABLE;

	if((NULL == pRapl) || (NULL == pInValue))
	{
		return rc;
	}

	if(NULL != psPath)
	{
		nextpath = l4db_GetTokensFromPath(psPath, &psToken, &psTokenValue);

		if(NULL != psToken)
		{
			//entry
			if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_ENTRIES))
			{
				rc = l4db_UpdateRaplEntryFromPath(pRapl->roamingPartners, nextpath, pInValue, pBufferSize, pAPDOType, cmd);
			}
			//any
			else if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_ANY))
			{
				if(NULL == nextpath)
				{
					rc = l4db_UpdateAnyValue(&pRapl->any, pInValue, pBufferSize, pAPDOType, cmd);
				}
			}
			//select policy
			else if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_SELECT_POLICY))
			{
				if(NULL == nextpath)
				{
					rc = l4db_UpdateSelectPolicyValue(&pRapl->selectPolicy, pInValue, pBufferSize, pAPDOType, cmd);
				}
			}
		}
	}
	else//our path is empty
	{
		rc = WMX_ST_OK;

		//we need to return all the nodes children separated by /
		if(APDO_GetCmd == cmd)
		{
			rc = l4db_SetStringValueNew(CAPL_RAPL_CHILDREN_STR, strlen(CAPL_RAPL_CHILDREN_STR) + 1,
				(char*)pInValue, pBufferSize, pAPDOType, cmd);

			*pAPDOType = APDO_Node;
		}
		else if(APDO_DeleteCmd == cmd)
		{
			l4db_InitRapl(pRapl);
		}
	}
	return rc;
}
/// <summary>
/// Updates Network paramter from path
/// </summary>
/// <param name="pNSP">(IN) pointer to NSP </param>
/// <param name="psPath">(IN) the path of command </param>
/// <param name="psInValue">(IN \ OUT) buffer of value </param>
/// <param name="APDOType">(IN \ OUT) buffer type </param>
/// <param name="cmd">(IN) command (get/update/delete/add) </param>
/// <returns>wmx_Status_t </returns>
wmx_Status_t l4db_UpdateNetworkParmFromPath(pNwParams_t			pNwParams,
											char				*psPath,
											void				*pInValue,
											int					*pBufferSize,
											wmx_pAPDOType_t		pAPDOType,
											apdo_DbCmd_t		cmd,
											char *				nspTagName)
{
	char			* psToken;
	char			* psTokenValue;
	char			* nextpath;
	wmx_Status_t	rc = WMX_ST_DATA_UNAVAILABLE;

	if((NULL == pNwParams) || (NULL == pInValue))
	{
		return rc;
	}

	if(NULL != psPath)
	{
		// get next token
		nextpath = l4db_GetTokensFromPath(psPath, &psToken, &psTokenValue);

		if(NULL != psToken)
		{
			//home NSPs
			if((FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_H_NSP)) ||
			   (FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_H_NSP_DASH)))
			{
				rc = l4db_UpdateHnspsFromPath(pNwParams->hNsps, nextpath, pInValue, pBufferSize, pAPDOType, cmd, nspTagName);
			}

			//CAPL information
			else if (FALSE == l4db_CompareString(psToken,L4DB_XML_TOKEN_CAPL))
			{
				rc = l4db_UpdateCaplFromPath(&pNwParams->capl, nextpath, pInValue, pBufferSize, pAPDOType, cmd, nspTagName);
			}

			else if (FALSE == l4db_CompareString(psToken,L4DB_XML_TOKEN_RAPL))
			{
				rc = l4db_UpdateRaplFromPath(&pNwParams->rapl, nextpath, pInValue, pBufferSize, pAPDOType, cmd);

			}

			//channel plan
			else if (FALSE == l4db_CompareString(psToken,L4DB_XML_TOKEN_CHANNEL_PLAN))
			{
				rc = l4db_UpdateChannelPlanFromPath(&pNwParams->channelPlan, nextpath, pInValue, 
					pBufferSize, pAPDOType, cmd);
			}

			//operator name
			else if (FALSE == l4db_CompareString(psToken,L4DB_XML_TOKEN_OPERATOR_NAME))
			{
				if(NULL == nextpath)
				{
					rc =l4db_SetStringValueNew(pNwParams->provisionedName, sizeof(pNwParams->provisionedName) ,
						(char *)pInValue, pBufferSize, pAPDOType, cmd);
				}
			}

			else if (FALSE == l4db_CompareString(psToken,L4DB_XML_TOKEN_SERVER_ID))
			{
				if(NULL == nextpath)
				{
					TRACE(TR_MOD_APDO_AGENT, TR_SEV_DEBUG, "before update ServerID entry");
					rc =l4db_SetStringValueNew(pNwParams->serverID, sizeof(pNwParams->serverID),
						(char *)pInValue, pBufferSize, pAPDOType, cmd);

					TRACE(TR_MOD_APDO_AGENT, TR_SEV_DEBUG, "after update ServerID entry. server id =%s", pNwParams->serverID);
				}
			}

			//polling interval
			else if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_POLLING_INTERVAL))
			{
				if(NULL == nextpath)
				{
					rc = l4db_SetIntegerValueNew(&pNwParams->pollingInterval, pBufferSize, pInValue, pAPDOType, cmd);
				}
			}

			// polling attempts
			else if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_POLLING_ATTEMPTS))
			{
				if(NULL == nextpath)
				{
					rc = l4db_SetIntegerValueNew(&pNwParams->pollingAttempts, pBufferSize, pInValue, pAPDOType, cmd);
				}
			}
		}
	}
	else //our path is empty
	{
		rc = WMX_ST_OK;

		//we need to return all the nodes children separated by /
		if(APDO_GetCmd == cmd)
		{
			rc = l4db_SetStringValueNew(NW_PARAMS_CHILDREN_STR, strlen(NW_PARAMS_CHILDREN_STR) + 1,
										(char*)pInValue, pBufferSize, pAPDOType, cmd);

			*pAPDOType = APDO_Node;
		}
		else if(APDO_DeleteCmd == cmd)
		{
			l4db_InitNwParams(pNwParams);
		}
	}
	return rc;
}


///<summary>
/// updates all contacts info using a given APDO path according to the APDO command type
///</summary>
wmx_Status_t l4db_UpdateContactsFromPath(pContactsInfo_t pContacts,
										 char			*psPath, 
										 void			*pInValue,
										 int 			*pBufferSize,
										 wmx_pAPDOType_t pAPDOType,
										 apdo_DbCmd_t	cmd)
{
	char*				psToken;
	char*				psTokenValue;
	char*				nextpath;
	wmx_Status_t		rc = WMX_ST_DATA_UNAVAILABLE;
	pContactsInfo_t		pContact;
	BOOL				allocated = FALSE, addSeperator = FALSE;
	int					i;
	size_t				tempStrLen = 0;

	if((NULL == pContacts) || (NULL == pInValue))
	{
		return rc;
	}

	if(NULL != psPath)
	{
		// get next token
		nextpath = l4db_GetTokensFromPath(psPath, &psToken, &psTokenValue);

		if(NULL != psToken)
		{
			pContact = l4db_GetContactInfo(pContacts, psToken);

			if(NULL == pContact && (APDO_AddCmd == cmd))
			{
				pContact = l4db_AllocContactInfo(pContacts, psToken);
				allocated = TRUE;
			}

			if(NULL != pContact)
			{
				if(NULL != nextpath)
				{
					nextpath = l4db_GetTokensFromPath(nextpath, &psToken, &psTokenValue);

					if((NULL != psToken) && (NULL == nextpath))
					{
						//uri type
						if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_TYPE))
						{
							if(NULL == nextpath)
							{
								rc = l4db_SetIntegerValueNew((int*)&pContact->uriType, pBufferSize, (int*)pInValue, pAPDOType, cmd);
							}
						}
						
						//uri
						else if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_URI))
						{
							if(NULL == nextpath)
							{
								rc = l4db_SetStringValueNew(pContact->uri, sizeof(pContact->uri), (char*)pInValue,
									pBufferSize, pAPDOType, cmd);
							}
						}

						//text
						else if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_TEXT))
						{
							if(NULL == nextpath)
							{
								rc = l4db_SetStringValueNew(pContact->text, sizeof(pContact->text), (char*)pInValue,
									pBufferSize, pAPDOType, cmd);
							}
						}

						//trigger
						else if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_TRIGGER))
						{
							// Return ok on this node as long as l4db is static instead of dynamic
							rc = WMX_ST_OK;
							/*if ((NULL == nextpath) && (APDO_GetCmd == cmd))
							{						
								rc = l4db_SetStringValueNew("Trigger", sizeof("Trigger"), (char*)pInValue,
									pBufferSize, pAPDOType, cmd);
							}*/
						}						
					}
				}
				else//our path is empty
				{
					rc = WMX_ST_OK;

					//we need to return all the nodes children separated by /
					if(APDO_GetCmd == cmd)
					{
						*pAPDOType = APDO_String;
						rc = l4db_SetStringValueNew(CONTACT_INFO_CHILDREN_STR, strlen(CONTACT_INFO_CHILDREN_STR) + 1,
													(char*)pInValue, pBufferSize, pAPDOType, cmd);

						*pAPDOType = APDO_Node;
					}
					else if(APDO_DeleteCmd == cmd)//"delete" the relevant node
					{
						l4db_InitContactInfo(pContact); //init the specified contact
					}
				}
				//init the contact if it has been allocated and an error has occurred
				if((WMX_ST_OK != rc) && (TRUE == allocated))
				{
					l4db_InitContactInfo(pContact);
				}
			}
		}
	}
	else //our path is empty
	{
		rc = WMX_ST_OK;

		//we need to return all the nodes children separated by /
		if(APDO_GetCmd == cmd)
		{
			((char*)pInValue)[0] = '\0';
			*pAPDOType = APDO_Node;

			//get all the unique name tags under the contacts node
			for(i = 0 ; i < MAX_NUM_OF_CONTACTS ; i++)
			{
				tempStrLen = OSAL_strnlen(pContacts[i].tagName, MAX_TAG_NAME_SIZE);
				if(0 != tempStrLen && MAX_TAG_NAME_SIZE != tempStrLen)
				{
					if(TRUE == addSeperator)
					{
						OSAL_strcat_s(pInValue, *pBufferSize, L4DB_XML_TOKEN_SEPERATOR);
					}
					else
					{
						//the first time we want to copy and not concatenate
						OSAL_strcpy_s(pInValue, *pBufferSize, pContacts[i].tagName);
						addSeperator = TRUE;
						continue;
					}

					OSAL_strcat_s(pInValue, *pBufferSize, pContacts[i].tagName);
				}
			}
		}
		else if(APDO_DeleteCmd == cmd)//"delete" the relevant node
		{
			for(i = 0 ; i < WMX_URI_MAX_NUM ; i++)
			{
				l4db_InitContactInfo(&pContacts[i]); //init all contacts under the contacts node
			}
		}
	}
	return rc;
}

///<summary>
/// updates Certs using a given APDO path according to the APDO command type
///</summary>	
wmx_Status_t l4db_UpdateCertsFromPath(pCert_t		pCerts,
									  char			*psPath,
									  void			*pInValue,
									  int 			*pBufferSize,
									  wmx_pAPDOType_t	pAPDOType,
									  apdo_DbCmd_t	cmd)
{
	char		* psToken;
	char		* psTokenValue;
	char		* nextpath;
	pCert_t		pCert;
	wmx_Status_t rc = WMX_ST_DATA_UNAVAILABLE;
	int			i;
	BOOL		allocated = FALSE, addSeperator = FALSE;
	size_t		tempStrLen = 0;

	if((NULL == pCerts) || (NULL == pInValue))	
	{
		return rc;
	}

	if(NULL != psPath)
	{
		//get the entry's unique name
		nextpath = l4db_GetTokensFromPath(psPath, &psToken, &psTokenValue);

		if(NULL != psToken)
		{
			pCert = l4db_GetCert(pCerts, psToken);

			if((NULL == pCert) && (APDO_AddCmd == cmd))
			{
				pCert = l4db_AllocCert(pCerts, psToken);
				allocated = TRUE;
			}

			if(NULL != pCert)
			{
				if(NULL != nextpath)
				{
					nextpath = l4db_GetTokensFromPath(nextpath, &psToken, &psTokenValue);

					if((NULL != psToken) && (NULL == nextpath))
					{
						//cert type
						if ((FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_CERT_TYPE)) ||
							(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_CERT_TYPE_DASH)))
						{
							rc = l4db_SetStringValueNew((char*)&pCert->certType, sizeof(pCert->certType), 
								(char*)pInValue, pBufferSize, pAPDOType, cmd);
						}

						//ser num 
						else if ((FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_SER_NUM)) ||
							(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_SER_NUM_DASH)))
						{
							rc = l4db_SetStringValueNew((char*)&pCert->serNum, sizeof(pCert->serNum), 
								(char*)pInValue, pBufferSize, pAPDOType, cmd);
						}

						else if (FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_ISSUER))
							
						{
							rc = l4db_SetStringValueNew((char*)&pCert->issuer, sizeof(pCert->issuer), 
								(char*)pInValue, pBufferSize, pAPDOType, cmd);
						}

						////thumb print
						//else if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_THUMB_PRINT))
						//{
						//	rc = l4db_SetIntegerValueNew((int*)&pCert->thumbPrint, pBufferSize, 
						//		(int*)pInValue, pAPDOType, cmd);
						//}
					}
				}
				else // our path is empty
				{
					rc = WMX_ST_OK;

					//get command - we need to return all children's name separated by /
					if(APDO_GetCmd == cmd)
					{
						rc = l4db_SetStringValueNew(CERT_CHILDREN_STR, strlen(CERT_CHILDREN_STR) + 1,
							(char*)pInValue, pBufferSize, pAPDOType, cmd);

						*pAPDOType = APDO_Node;
					}
					//we need to "delete" our node
					else if(APDO_DeleteCmd == cmd)
					{
						l4db_InitCertInfo(pCert);//init the cert node
					}
				}
				//init the cert if it has been allocated and an error occurred
				if((WMX_ST_OK != rc) && (TRUE == allocated))
				{
					l4db_InitCertInfo(pCert);
				}
			} 
		}
	}
	else // our path is empty
	{
		rc = WMX_ST_OK;

		//get command - we need to return all children's name separated by /
		if(APDO_GetCmd == cmd)
		{
			*pAPDOType = APDO_Node;
			((char*)pInValue)[0] = '\0';

			for(i = 0 ; i < MAX_NUM_OF_CERTS ; i++)
			{
				tempStrLen = OSAL_strnlen(pCerts[i].tagName, MAX_TAG_NAME_SIZE);
				if(0 != tempStrLen && MAX_TAG_NAME_SIZE != tempStrLen)
				{
					if(TRUE == addSeperator)
					{
						OSAL_strcat_s(pInValue, *pBufferSize, L4DB_XML_TOKEN_SEPERATOR);
					}
					else
					{
						//the first time we want to copy and not concatenate
						OSAL_strcpy_s(pInValue, *pBufferSize, pCerts[i].tagName);
						addSeperator = TRUE;
						continue;
					}

					OSAL_strcat_s(pInValue, *pBufferSize, pCerts[i].tagName);	
				}
			}
		}
		//we need to "delete" our node
		else if(APDO_DeleteCmd == cmd)
		{
			for(i = 0 ; i < MAX_NUM_OF_CERTS ; i++)
			{
				l4db_InitCertInfo(&pCerts[i]);//init all certs under this node
			}
		}
	}
	return rc;
}
///<summary>
/// updates srv realms using a given APDO path according to the APDO command type - NOT SUPPORTED NOW
///</summary>	
wmx_Status_t l4db_UpdateSrvRealmsFromPath(pSrvRealm_t		pSrvRealms,
										  char				*psPath,
										  void				*pInValue,
										  int				*pBufferSize,
										  wmx_pAPDOType_t	pAPDOType,
										  apdo_DbCmd_t		cmd)
{
	char		* psToken;
	char		* psTokenValue;
	char		* nextpath;
	pSrvRealm_t	pSrvRealm;
	wmx_Status_t rc = WMX_ST_DATA_UNAVAILABLE;
	int			i;
	BOOL		allocated = FALSE, addSeperator = FALSE;
	size_t		tempStrLen = 0;

	if((NULL == pSrvRealms) || (NULL == pInValue))	
	{
		return rc;
	}

	if(NULL != psPath)
	{
		//get the entry's unique name
		nextpath = l4db_GetTokensFromPath(psPath, &psToken, &psTokenValue);

		if(NULL != psToken)
		{
			pSrvRealm = l4db_GetSrvRealm(pSrvRealms, psToken);

			if((NULL == pSrvRealm) && (APDO_AddCmd == cmd))
			{
				pSrvRealm = l4db_AllocSrvRealm(pSrvRealms, psToken);
				allocated = TRUE;
			}

			if(NULL != pSrvRealm)
			{
				if(NULL != nextpath)
				{
					nextpath = l4db_GetTokensFromPath(nextpath, &psToken, &psTokenValue);

					if((NULL != psToken) && (NULL == nextpath))
					{
						if ((FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_SERVER_REALM)) ||
							(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_SERVER_REALM_DASH)))
						{
							rc = l4db_SetStringValueNew(pSrvRealm->srvRealm, sizeof(pSrvRealm->srvRealm),
								(char*)pInValue, pBufferSize, pAPDOType, cmd);
						}
					}
				}
				else //our path is empty
				{
					rc = WMX_ST_OK;

					//if this is an add \ update command, we have already handled it
					//if this a get cmd - we need return all the children separated by '/'
					if(APDO_GetCmd == cmd)
					{
						rc = l4db_SetStringValueNew(L4DB_XML_TOKEN_SERVER_REALM_DASH, strlen(L4DB_XML_TOKEN_SERVER_REALM_DASH) + 1,
							(char*)pInValue, pBufferSize, pAPDOType, cmd);
					}
					else if(APDO_DeleteCmd == cmd) //"delete" our node
					{
						l4db_InitSrvRealm(pSrvRealm); //init the srv realm
					}
				}
				//init the srv realm if it has been allocated and an error has occurred
				if((WMX_ST_OK != rc) && (TRUE == allocated))
				{
					l4db_InitSrvRealm(pSrvRealm);
				}
			}
		}
	}
	else //our path is empty
	{
		rc = WMX_ST_OK;

		//get command - we need to return all children's name separated by /
		if(APDO_GetCmd == cmd)
		{
			*pAPDOType = APDO_Node;
			((char*)pInValue)[0] = '\0';

			//get all unique names under the srv realms node
			for(i = 0 ; i < MAX_NUM_OF_SRV_REALMS ; i++)
			{
				tempStrLen = OSAL_strnlen(pSrvRealms[i].tagName, MAX_TAG_NAME_SIZE);
				if(0 != tempStrLen && MAX_TAG_NAME_SIZE != tempStrLen)
				{
					if(TRUE == addSeperator)
					{
						OSAL_strcat_s(pInValue, *pBufferSize, L4DB_XML_TOKEN_SEPERATOR);
					}
					else
					{
						//the first time we want to copy and not concatenate
						OSAL_strcpy_s(pInValue, *pBufferSize, pSrvRealms[i].tagName);
						addSeperator = TRUE;
						continue;
					}

					OSAL_strcat_s(pInValue, *pBufferSize, pSrvRealms[i].tagName);
				}
			}
		}
		//we need to "delete" our node
		else if(APDO_DeleteCmd == cmd)
		{
			for(i = 0 ; i < MAX_NUM_OF_SRV_REALMS ; i++)
			{
				l4db_InitSrvRealm(&pSrvRealms[i]); //init all srv realms under this node
			}
		}
	}
	return rc;
}
///<summary>
/// updates an EAP info using a given APDO path according to the APDO command type
///</summary>	
wmx_Status_t l4db_UpdateEapInfoFromPath(pEAP_t pEap,
										char *psPath,
										void	*pInValue,
										int  *pBufferSize,
										wmx_pAPDOType_t pAPDOType,
										apdo_DbCmd_t cmd)
{
	char		* psToken;
	char		* psTokenValue;
	char		* nextpath;
	wmx_Status_t rc = WMX_ST_DATA_UNAVAILABLE;
	wmx_EapType_t	eapType;

	if((NULL == pEap) || (NULL == pInValue))
	{
		return rc;
	}

	if(NULL != psPath)
	{
		// get next token
		nextpath = l4db_GetTokensFromPath(psPath, &psToken, &psTokenValue);

		if(NULL == nextpath)
		{
			if(NULL != psToken)
			{
				//EAP type
				if((FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_EAP_TYPE)) ||
				   (FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_EAP_TYPE_DASH)))					
				{
					if(((APDO_AddCmd == cmd) || (APDO_UpdateCmd == cmd)) && 
						(APDO_String == *pAPDOType))
					{
						eapType = l4db_ConvertToEapTypeEnum((char*)pInValue);
					
						if(L4DB_INVALID_INDEX != eapType) //we received an integer as a string
						{
							rc = l4db_SetIntegerValueNew((int*)&pEap->EAPMethod, pBufferSize, 
									(int*)pInValue, pAPDOType, cmd);
						}
						else
						{
							*pAPDOType = APDO_Integer;
							rc = l4db_SetIntegerValueNew((int*)&pEap->EAPMethod, pBufferSize, 
									(int*)&eapType, pAPDOType, cmd);
						}
					}
					else
					{
						rc = l4db_SetIntegerValueNew((int*)&pEap->EAPMethod, pBufferSize, 
								(int*)pInValue, pAPDOType, cmd);
					}
				}

				//vendor id
				else if ((FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_VENDOR_ID)) ||
					(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_VENDOR_ID_DASH)))
				{
					rc = l4db_SetIntegerValueNew((int*)&pEap->vendorId, pBufferSize, (int*)pInValue, pAPDOType, cmd);
				}

				//vendor type
				else if ((FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_VENDOR_TYPE)) ||
						(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_VENDOR_TYPE_DASH)))
				{
					rc = l4db_SetIntegerValueNew((int*)&pEap->vendorType, pBufferSize, (int*)pInValue, pAPDOType, cmd);
				}

				//user id
				else if ((FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_USER_IDENTITY)) ||
					(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_USER_IDENTITY_DASH)))
				{

						rc = l4db_SetStringValueNew(pEap->id, sizeof(pEap->id),
							(char *)pInValue, pBufferSize, pAPDOType, cmd);
				}

				//pseudo user id
				else if ((FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_PROVISIONED_PSEUDO_ID)) ||
					(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_PROVISIONED_PSEUDO_ID_DASH)))
				{

					rc = l4db_SetStringValueNew(pEap->provisionedPseudoId, sizeof(pEap->provisionedPseudoId),
						(char *)pInValue, pBufferSize, pAPDOType, cmd);
				}

				//password
				//assume that the information retrive in clear text
				else if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_PASSWORD))
				{
					if(NULL == pEap->Password)
					{
						return WMX_ST_FAIL;
					}
					switch(cmd)
					{
						case APDO_UpdateCmd:   
						case APDO_AddCmd:     // DB Add command
							if (NULL == pInValue ||	*pBufferSize > MAX_EAP_PASSWORD_SIZE)
							{
								rc = WMX_ST_FAIL;
							}
							else
							{
								OSAL_Crypt_SetEncryptedPassword(pEap->Password, (char *)pInValue);
								rc = WMX_ST_OK;
							}
							break;

						case APDO_GetCmd:
							TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4db_UpdateEapInfoFromPath: Get command to password return null ");
							OSAL_strncpy_s((char *)pInValue, *pBufferSize, "\0", MAX_EAP_PASSWORD_SIZE);
							*pAPDOType = APDO_String;
							*pBufferSize = 0;
							rc = WMX_ST_OK;
							break;

						case APDO_DeleteCmd:    // DB delete command
							{
								if('\0' == pEap->Password[0])
								{
									rc = WMX_ST_DATA_UNAVAILABLE;
								}
								else
								{
									char path[MAX_REGISTRY_ANSWER];

									OSAL_BuildFullPath(pEap->Password, path, MAX_REGISTRY_ANSWER);
									remove(path);
									pEap->Password[0] = '\0';
									rc = WMX_ST_OK;
								}
							}							
							break;
					}
				}

				//realm
				else if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_REALM))
				{
					rc = l4db_SetStringValueNew(pEap->realm, sizeof(pEap->realm),
							(char *)pInValue, pBufferSize, pAPDOType, cmd);
				}

				//use pseudo
				else if ((FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_USE_PRIVACY)) ||
					(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_USE_PRIVACY_DASH)))	
				{
					rc = l4db_SetBoolValueNew(&pEap->usePrivacy, pBufferSize, (BOOL*)pInValue, pAPDOType, cmd);
				}

				//Encaps
				else if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_ENCAPS))
				{
					rc = l4db_SetIntegerValueNew((int*)&pEap->encaps, pBufferSize, (int*)pInValue, pAPDOType, cmd);					
				}

				//VFY_SRV_Realm
				else if ((FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_VFY_SERVER_REALM)) ||
				         (FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_VFY_SERVER_REALM_DASH)))
				{
					rc = l4db_SetBoolValueNew(&pEap->vfySrvRealm, pBufferSize, (BOOL*)pInValue, pAPDOType, cmd);
				}
			}
		}
		
		//srv realms 
		if ((FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_SERVER_REALMS)) ||
			(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_SERVER_REALMS_DASH))) 
		{
			rc = l4db_UpdateSrvRealmsFromPath(pEap->srvRealms, nextpath, pInValue, pBufferSize, pAPDOType, cmd);
		}

		//cert
		if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_CERT))
		{
			rc = l4db_UpdateCertsFromPath(pEap->certs, nextpath, pInValue, pBufferSize, pAPDOType, cmd);
		}
	}
	else //our path is empty
	{
		rc = WMX_ST_OK;

		//get command - we need to return all children's name separated by /
		if(APDO_GetCmd == cmd)
		{
			rc = l4db_SetStringValueNew(EAP_CHILDREN_STR, strlen(EAP_CHILDREN_STR) + 1,
				(char*)pInValue, pBufferSize, pAPDOType, cmd);

			*pAPDOType = APDO_Node;
		}
		//we need to "delete" our node
		else if(APDO_DeleteCmd == cmd)
		{
			l4db_InitEapInfo(pEap);
		}
	}
	return rc;
}
///<summary>
/// updates the primary subscription parameters using a given APDO path according to the APDO command type
///</summary>
wmx_Status_t l4db_UpdateSubscriberInfoFromPath(pSubscriberInfo_t	pPrimarySubsc,
											   char				*psPath,
											   void				*pInValue,
											   int				*pBufferSize,
											   wmx_pAPDOType_t	pAPDOType,
											   apdo_DbCmd_t		cmd)
{
	char		* psToken;
	char		* psTokenValue;
	char		* nextpath;
	pEAP_t		pEap;
	int			i;
	wmx_Status_t rc = WMX_ST_DATA_UNAVAILABLE;
	BOOL		allocated = FALSE, addSeperator = FALSE;
	size_t		tempStrLen = 0;

	if((NULL == pPrimarySubsc) || (NULL == pInValue))
	{
		return rc;
	}

	if(NULL != psPath)
	{
		nextpath = l4db_GetTokensFromPath(psPath, &psToken, &psTokenValue);

		if(NULL != psToken)
		{
			if(NULL == nextpath)
			{
				//Name
				if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_NAME))
				{
					rc = l4db_SetStringValueNew(pPrimarySubsc->name, sizeof(pPrimarySubsc->name),
						(char*)pInValue, pBufferSize, pAPDOType, cmd);
				}

				//Activated
				else if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_ACTIVATED))
				{
					rc = l4db_SetBoolValueNew(&pPrimarySubsc->activated, pBufferSize, 
						(BOOL*)pInValue, pAPDOType, cmd);
					
					if(WMX_ST_OK == rc)
					{
						wmx_PopulateActivationStatusChangeMonitor((BOOL*)pInValue);
					}
				}
			}

			//EAP
			if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_EAP))
			{
				//get the EAP's entry unique name
				if(NULL != nextpath)
				{
					nextpath = l4db_GetTokensFromPath(nextpath, &psToken, &psTokenValue);

					if(NULL != psToken)
					{
						pEap = l4db_GetEap(pPrimarySubsc->eapInfo, psToken);

						//allocate an EAP entry if necessary 
						if((NULL == pEap) && (APDO_AddCmd == cmd))
						{
							pEap = l4db_AllocEap(pPrimarySubsc->eapInfo, psToken);
							allocated = TRUE;
						}

						if(NULL != pEap)
						{
							rc = l4db_UpdateEapInfoFromPath(pEap, nextpath, pInValue,
								pBufferSize, pAPDOType, cmd);

							//init the eap if it has been allocated and an error occurred
							if((WMX_ST_OK != rc) && (TRUE == allocated))
							{
								l4db_InitEapInfo(pEap);
							}
						}
					}
				}
				else//our path is empty
				{
					rc = WMX_ST_OK;
					//get command, we should return all the children
					if(APDO_GetCmd == cmd)
					{
						*pAPDOType = APDO_Node;
						((char*)pInValue)[0] = '\0';

						for(i = 0 ; i < MAX_NUM_OF_EAP_METHODS ; i++)
						{
							tempStrLen = OSAL_strnlen(pPrimarySubsc->eapInfo[i].tagName, MAX_TAG_NAME_SIZE);
							if(0 != tempStrLen && MAX_TAG_NAME_SIZE != tempStrLen)
							{
								if(TRUE == addSeperator)
								{
									OSAL_strcat_s(pInValue, *pBufferSize, L4DB_XML_TOKEN_SEPERATOR);
								}
								else
								{
									//the first time we want to copy and not concatenate
									OSAL_strcpy_s(pInValue, *pBufferSize, pPrimarySubsc->eapInfo[i].tagName);
									addSeperator = TRUE;
									continue;
								}
								OSAL_strcat_s(pInValue, *pBufferSize, pPrimarySubsc->eapInfo[i].tagName);
							}
						}
					}
					else if(APDO_DeleteCmd == cmd)//delete command, we should "delete" our node
					{
						for(i = 0 ; i < MAX_NUM_OF_EAP_METHODS ; i++)
						{
							l4db_InitEapInfo(&pPrimarySubsc->eapInfo[i]);
						}
					}
				}
			}
		}
	}
	//we don't have a path
	else
	{
		rc = WMX_ST_OK;

		//get command - we need to return all children's name separated by /
		if(APDO_GetCmd == cmd)
		{
			rc = l4db_SetStringValueNew(SUBSC_CHILDREN_STR, strlen(SUBSC_CHILDREN_STR) + 1,
										(char*)pInValue, pBufferSize, pAPDOType, cmd);

			*pAPDOType = APDO_Node;
		}

		//we need to "delete" our node
		else if(APDO_DeleteCmd == cmd)
		{
			l4db_InitPrimarySubscription(pPrimarySubsc);
		}
	}
	return rc;
}

///<summary>
/// updates the other subscription parameters using a given APDO path according to the APDO command type
///</summary>
wmx_Status_t l4db_UpdateOtherSubscFromPath(pOtherSubsInfo_t	pOtherSubsc,
										   char				*psPath,
										   void				*pInValue,
										   int				*pBufferSize,
										   wmx_pAPDOType_t	pAPDOType,
										   apdo_DbCmd_t		cmd)
{
	char			* psToken;
	char			* psTokenValue;
	char			* nextpath;
	pOtherSubsInfo_t pSubscriber;
	wmx_Status_t	rc = WMX_ST_DATA_UNAVAILABLE;
	int				i;
	BOOL			allocatedOtherSubsc = FALSE, addSeperator = FALSE;
	size_t			tempStrLen = 0;

	if((NULL == pOtherSubsc) || (NULL == pInValue))
	{
		return rc;
	}

	if(NULL != psPath)
	{
		//get the unique name of this other subscription
		nextpath = l4db_GetTokensFromPath(psPath, &psToken, &psTokenValue);

		if(NULL != psToken)
		{
			pSubscriber = l4db_GetOtherSubsc(pOtherSubsc, psToken);

			//allocate a new "other subscription" if needed
			if((NULL == pSubscriber) && (APDO_AddCmd == cmd))
			{
				pSubscriber = l4db_AllocOtherSubsc(pOtherSubsc, psToken);
				allocatedOtherSubsc = TRUE;
			}

			if(NULL != pSubscriber)
			{
				if(NULL != nextpath)
				{
					rc = l4db_UpdateSubscriberInfoFromPath(&pOtherSubsc->subscriberInfo, nextpath, pInValue, pBufferSize, pAPDOType, cmd);
				}

				else //our nextPath is empty
				{
					rc = WMX_ST_OK;

					//get command - we need to return all children's name separated by /
					if(APDO_GetCmd == cmd)
					{
						rc = l4db_SetStringValueNew(SUBSC_CHILDREN_STR, strlen(SUBSC_CHILDREN_STR) + 1,
													(char*)pInValue, pBufferSize, pAPDOType, cmd);

						*pAPDOType = APDO_Node;
					}
					//we need to "delete" our node
					else if(APDO_DeleteCmd == cmd)
					{
						l4db_InitOtherSubscription(pSubscriber);
					}
				}

				//init the other subscriber if it has been allocated and an error occurred
				if((WMX_ST_OK != rc) && (TRUE == allocatedOtherSubsc))
				{
					l4db_InitOtherSubscription(pSubscriber);
				}
			}
		}
	}
	//we don't have a path
	else
	{
		rc = WMX_ST_OK;

		//get command - we need to return all children's name separated by /
		if(APDO_GetCmd == cmd)
		{
			*pAPDOType = APDO_Node;
			addSeperator = FALSE;

			//get all the unique names under the other subscription tag
			for(i = 0 ; i < WMX_NSP_SUBSCRIBERS_MAX_NUM ; i++)
			{
				tempStrLen = OSAL_strnlen(pOtherSubsc[i].tagName, MAX_TAG_NAME_SIZE);
				if(0 != tempStrLen && MAX_TAG_NAME_SIZE != tempStrLen)
				{
					if(TRUE == addSeperator)
					{
						OSAL_strcat_s(pInValue, *pBufferSize, L4DB_XML_TOKEN_SEPERATOR);
					}
					else
					{
						//the first time, we want to perform strcpy and not concatenate
						OSAL_strcpy_s(pInValue, *pBufferSize, pOtherSubsc[i].tagName);
						addSeperator = TRUE;
						continue;
					}

					OSAL_strcat_s(pInValue, *pBufferSize, pOtherSubsc[i].tagName);
				}
			}
		}
		//we need to "delete" our node
		else if(APDO_DeleteCmd == cmd)
		{
			for(i = 0 ; i < WMX_NSP_SUBSCRIBERS_MAX_NUM ; i++)
			{
				l4db_InitOtherSubscription(pOtherSubsc); //init all other subscriptions
			}
		}
	}
	return rc;
}



///<summary>
/// updates subscription parameters using a given APDO path according to the APDO command type
///</summary>
wmx_Status_t l4db_UpdateSubscriptionParamsFromPath(pSubscriptionParams_t	pSubscParams,
												   char						*psPath,
												   void						*pInValue,
												   int					*pBufferSize,
												   wmx_pAPDOType_t			pAPDOType,
												   apdo_DbCmd_t				cmd)
{
	char		* psToken;
	char		* psTokenValue;
	char		* nextpath;
	wmx_Status_t rc = WMX_ST_DATA_UNAVAILABLE;

	if((NULL == pSubscParams) || (NULL == pInValue))
	{
		return rc;
	}

	if(NULL != psPath)
	{
		// get next token
		nextpath = l4db_GetTokensFromPath(psPath, &psToken, &psTokenValue);

		if(NULL != psToken)
		{
			//Primary subscription
			if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_PRIMARY))
			{
				rc = l4db_UpdateSubscriberInfoFromPath(&pSubscParams->primary, nextpath, pInValue, pBufferSize, pAPDOType, cmd);
			}

			//other subscriptions
			else if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_OTHER_SUBSCRIPTIONS))
			{
				rc = l4db_UpdateOtherSubscFromPath(pSubscParams->other, nextpath, pInValue, pBufferSize, pAPDOType, cmd);
			}
		}
	}
	else //we don't have a path
	{
		rc = WMX_ST_OK;

		//get command - we need to return all children's name separated by /
		if(APDO_GetCmd == cmd)
		{
			rc = l4db_SetStringValueNew(SUBSC_PARAMS_CHILDREN_STR, strlen(SUBSC_PARAMS_CHILDREN_STR) + 1,
				(char*)pInValue, pBufferSize, pAPDOType, cmd);

			*pAPDOType = APDO_Node;
		}
		//we need to "delete" our node
		else if(APDO_DeleteCmd == cmd)
		{
			l4db_InitSubscriptionParams(pSubscParams);
		}
	}
	return rc;
}

///<summary>
/// updates the dev info using a given APDO path according to the APDO command type
///</summary>
wmx_Status_t l4db_UpdateDevInfoFromPath(char			*psPath,
										void			*pInValue,
										int				*pBufferSize,
										wmx_pAPDOType_t	 pAPDOType,
										apdo_DbCmd_t	cmd)
{
	char		* psToken;
	char		* psTokenValue;
	char		* nextpath;
	wmx_Status_t rc = WMX_ST_DATA_UNAVAILABLE;
	pDevInfo_t pDevInfo;
	pWimax_t   pWimax;
	char devIDPrefix[DEV_ID_PREFIX_SIZE] = {0};
	char tempDevID[MAX_DEV_ID_SIZE] = {0};
	BOOL res;

	if(NULL == pInValue)
	{
		return rc;
	}

	pDevInfo = l4db_GetDevInfo();
	pWimax = l4db_GetWimax();

	if(NULL != psPath)
	{
		// get next token
		nextpath = l4db_GetTokensFromPath(psPath, &psToken, &psTokenValue);

		if(NULL != psToken)
		{
			if(NULL == nextpath)
			{
				if(APDO_GetCmd == cmd)
				{
					//device id - for now this is taken from the first wimax radio module
					if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_DEV_ID))
					{
						// MZUR - TODO after fix nvm return this link
						/*if(pWimax->wmxRadioModulesSize > 0)
						{
							rc = l4db_SetStringValueNew(pWimax->radioModules[0].macAddress,
														sizeof(pWimax->radioModules[0].macAddress),
														(char *)pInValue, pBufferSize, pAPDOType, cmd);
						}*/


						// Read value of prefix from registry key if exists
						L4Configurations_getAPDODevIdPrefix(devIDPrefix);
							
						OSAL_strncpy_s(tempDevID, MAX_DEV_ID_SIZE, devIDPrefix, OSAL_strnlen(devIDPrefix, DEV_ID_PREFIX_SIZE));
						OSAL_strncat_s(tempDevID, MAX_DEV_ID_SIZE, pDevInfo->devID, 
								OSAL_strnlen(pDevInfo->devID, MAX_DEV_ID_SIZE - OSAL_strnlen(devIDPrefix, DEV_ID_PREFIX_SIZE)));						

						rc = l4db_SetStringValueNew(tempDevID, sizeof(tempDevID), 
							(char *)pInValue, pBufferSize, pAPDOType, cmd);
					}

					//manufacturer
					else if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_MAN))
					{
						//Read value from registry key if possible, otherwise set to default
						res = L4Configurations_getApdoDevInfoManID(pDevInfo->manufacturer);

						rc = l4db_SetStringValueNew(pDevInfo->manufacturer, sizeof(pDevInfo->manufacturer),
							(char *)pInValue, pBufferSize, pAPDOType, cmd);
					}

					//model
					else if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_MOD))
					{
						// Read value from registry key if possible, otherwise set to default
						res = L4Configurations_getApdoDevInfoModel(pDevInfo->model);					


						rc = l4db_SetStringValueNew(pDevInfo->model, sizeof(pDevInfo->model),
							(char *)pInValue, pBufferSize, pAPDOType, cmd);
					}
				}
			}
		}
	}
	else //we don't have a path
	{
		rc = WMX_ST_OK;

		//get command - we need to return all children's name separated by /
		if(APDO_GetCmd == cmd)
		{
			rc = l4db_SetStringValueNew(DEV_INFO_CHILDREN_STR, strlen(DEV_INFO_CHILDREN_STR) + 1,
				(char*)pInValue, pBufferSize, pAPDOType, cmd);

			*pAPDOType = APDO_Node;
		}
	}
	return rc;
}


///<summary>
/// updates the dev cap using a given APDO path according to the APDO command type
///</summary>
wmx_Status_t l4db_UpdateDevCapFromPath(char			*psPath,
										void			*pInValue,
										int				*pBufferSize,
										wmx_pAPDOType_t	 pAPDOType,
										apdo_DbCmd_t	cmd)
{
	char		* psToken;
	char		* psTokenValue;
	char		* nextpath;
	wmx_Status_t rc = WMX_ST_DATA_UNAVAILABLE;
	pDevDetail_t pDevDetail;
	pDevInfo_t	 pDevInfo;
	BOOL		 boolVal, finished = FALSE;
	pWimax_t	pWimax;

	if(NULL == pInValue)
	{
		return rc;
	}

	pDevDetail = l4db_GetDevDetail();
	pDevInfo = l4db_GetDevInfo();
	pWimax = l4db_GetWimax();

	if(APDO_GetCmd == cmd) //this node allows only get
	{
		if(NULL != psPath)
		{
			// get next token
			nextpath = l4db_GetTokensFromPath(psPath, &psToken, &psTokenValue);

			if(NULL != psToken)
			{
				if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_IP_CAP))
				{
					if(NULL != nextpath)
					{
						nextpath = l4db_GetTokensFromPath(nextpath, &psToken, &psTokenValue);

						if(NULL != psToken)
						{
							if(NULL == nextpath)
							{
								//IP v4
								if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_IPV4))
								{
									boolVal = TRUE;
									finished = TRUE;
								}

								//CM IP v4
								else if((FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_IPV6)) ||
										(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_CMIPV4)) ||
										(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_CMIPV6)))
								{
									boolVal = FALSE;
									finished = TRUE;
								}

								if(TRUE == finished)
								{
									rc = l4db_SetBoolValueNew(&boolVal, pBufferSize, (BOOL*)pInValue, pAPDOType, cmd);
								}
							}
						}
					}
					else //our path is empty
					{
						rc = WMX_ST_OK;

						//get command - we need to return all children's name separated by /
						rc = l4db_SetStringValueNew(IP_CAP_CHILDREN_STR, strlen(IP_CAP_CHILDREN_STR) + 1,
							(char*)pInValue, pBufferSize, pAPDOType, cmd);

						*pAPDOType = APDO_Node;
					}
				}
				else if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_UPDATE_METHODS))
				{
					if(NULL != nextpath)
					{
						nextpath = l4db_GetTokensFromPath(nextpath, &psToken, &psTokenValue);

						if(NULL != psToken)
						{
							if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_SERVER_INIT))
							{
								if(NULL == nextpath)
								{
									boolVal = TRUE;
									rc = l4db_SetBoolValueNew(&boolVal, pBufferSize, (BOOL*)pInValue, pAPDOType, cmd);
								}
							}
							else if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_CLIENT_INIT))
							{
								if(NULL != nextpath)
								{
									nextpath = l4db_GetTokensFromPath(nextpath, &psToken, &psTokenValue);

									if(NULL != psToken)
									{
										if(NULL == nextpath)
										{
											// Only get is available for these MOs
											if (cmd != APDO_GetCmd)
											{
												return WMX_ST_FAIL;
											}

											//polling supported
											if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_POLLING_SUPPORTED))
											{
												boolVal = TRUE;
												rc = l4db_SetBoolValueNew(&boolVal, pBufferSize, (BOOL*)pInValue, pAPDOType, cmd);
											}

											//polling interval
											else if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_POLLING_INTERVAL))
											{												
												rc = l4db_SetIntegerValueNew((int*)&pWimax->devCap.updateMethods.clientInitiated.pollingInterval, 
													pBufferSize, (int*)pInValue, pAPDOType, cmd);
											}

											//polling attempts
											else if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_POLLING_ATTEMPTS))
											{												
												rc = l4db_SetIntegerValueNew((int*)&pWimax->devCap.updateMethods.clientInitiated.pollingAttempts, 
													pBufferSize, (int*)pInValue, pAPDOType, cmd);
											}
										}
									}
								}
								else //our path is empty
								{
									rc = WMX_ST_OK;

									//get command - we need to return all children's name separated by /
									rc = l4db_SetStringValueNew(CLIENT_INIT_CHILDREN_STR, strlen(CLIENT_INIT_CHILDREN_STR) + 1,
										(char*)pInValue, pBufferSize, pAPDOType, cmd);

									*pAPDOType = APDO_Node;
								}
							}
						}
					}
					else //our path is empty
					{
						rc = WMX_ST_OK;

						//get command - we need to return all children's name separated by /
						rc = l4db_SetStringValueNew(UPDATE_METHODS_CHILDREN_STR, strlen(UPDATE_METHODS_CHILDREN_STR) + 1,
							(char*)pInValue, pBufferSize, pAPDOType, cmd);

						*pAPDOType = APDO_Node;
					}
				}
			}
		}
		else //we don't have a path
		{
			rc = WMX_ST_OK;

			//get command - we need to return all children's name separated by /
			rc = l4db_SetStringValueNew(DEV_CAP_CHILDREN_STR, strlen(DEV_CAP_CHILDREN_STR) + 1,
				(char*)pInValue, pBufferSize, pAPDOType, cmd);

			*pAPDOType = APDO_Node;
		}
	}
	return rc;
}

///<summary>
/// updates the dev detail URI using a given APDO path according to the APDO command type
///</summary>
wmx_Status_t l4db_UpdateDevDetailURIFromPath(char			*psPath,
											 void			*pInValue,
											 int				*pBufferSize,
											 wmx_pAPDOType_t	 pAPDOType,
											 apdo_DbCmd_t	cmd)
{
	wmx_Status_t rc = WMX_ST_DATA_UNAVAILABLE;
	pDevDetail_t pDevDetail;
	char		* psToken;
	char		* psTokenValue;
	char		* nextpath;

	if(NULL == pInValue)
	{
		return rc;
	}

	pDevDetail = l4db_GetDevDetail();

	if(NULL != psPath)
	{
		// get next token
		nextpath = l4db_GetTokensFromPath(psPath, &psToken, &psTokenValue);

		if(NULL != psToken)
		{
			if(NULL == nextpath)
			{
				if(APDO_GetCmd == cmd)
				{
					// MaxDepth
					if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_URI_MAX_DEPTH))
					{			
						rc = l4db_SetStringValueNew(pDevDetail->uri.MaxDepth, sizeof(pDevDetail->uri.MaxDepth),
							(char *)pInValue, pBufferSize, pAPDOType, cmd);
					}
					// MaxTotLen
					else if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_URI_MAX_TOT_LEN))
					{
						rc = l4db_SetStringValueNew(pDevDetail->uri.MaxTotLen, sizeof(pDevDetail->uri.MaxTotLen),
							(char *)pInValue, pBufferSize, pAPDOType, cmd);
					}
					// MaxSegLen
					else if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_URI_MAX_SEG_LEN))
					{
						rc = l4db_SetStringValueNew(pDevDetail->uri.MaxSegLen, sizeof(pDevDetail->uri.MaxSegLen),
							(char *)pInValue, pBufferSize, pAPDOType, cmd);
					}
				}
			}
		}
	}
	else //we don't have a path
	{
		rc = WMX_ST_OK;

		//get command - we need to return all children's name separated by /
		if(APDO_GetCmd == cmd)
		{
			rc = l4db_SetStringValueNew(DEV_DETAIL_URI_CHILDREN_STR, strlen(DEV_DETAIL_URI_CHILDREN_STR) + 1,
				(char*)pInValue, pBufferSize, pAPDOType, cmd);

			*pAPDOType = APDO_Node;
		}
	}
	return rc;
}

///<summary>
/// updates the dev detail Ext using a given APDO path according to the APDO command type
///</summary>
wmx_Status_t l4db_UpdateDevDetailExtFromPath(char			*psPath,
										  void			*pInValue,
										  int				*pBufferSize,
										  wmx_pAPDOType_t	 pAPDOType,
										  apdo_DbCmd_t	cmd)
{
	wmx_Status_t rc = WMX_ST_DATA_UNAVAILABLE;
	pDevDetailExt_t pDevDetailEx;
	char		* psToken;
	char		* psTokenValue;
	char		* nextpath;

	if(NULL == pInValue)
	{
		return rc;
	}

	pDevDetailEx = l4db_GetDevDetailEx();

	if(NULL != psPath)
	{
		// get next token
		nextpath = l4db_GetTokensFromPath(psPath, &psToken, &psTokenValue);

		if(NULL != psToken)
		{
			if(NULL == nextpath)
			{
				if(APDO_GetCmd == cmd)
				{
					//SwV2
					if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_SWV2))
					{		
						L4Configurations_getApdoFumoSwv2String(pDevDetailEx->SwV2);

						// If there is a no string to replace the swv2 string in the registry use default.
						if (OSAL_stricmp(DEFAULT_EMPTY_STR, pDevDetailEx->SwV2) == 0)
						{
							l4db_BuildVersionString(pDevDetailEx->SwV2);
						}

						rc = l4db_SetStringValueNew(pDevDetailEx->SwV2, sizeof(pDevDetailEx->SwV2),
							(char *)pInValue, pBufferSize, pAPDOType, cmd);
					}
				}
			}
		}
	}
	else //we don't have a path
	{
		rc = WMX_ST_OK;

		//get command - we need to return all children's name separated by /
		if(APDO_GetCmd == cmd)
		{
			rc = l4db_SetStringValueNew(DEV_DETAIL_EXT_CHILDREN_STR, strlen(DEV_DETAIL_EXT_CHILDREN_STR) + 1,
				(char*)pInValue, pBufferSize, pAPDOType, cmd);

			*pAPDOType = APDO_Node;
		}
	}
	return rc;
}

///<summary>
/// updates the dev detail using a given APDO path according to the APDO command type
///</summary>
wmx_Status_t l4db_UpdateDevDetailFromPath(char			*psPath,
									   void			*pInValue,
									   int				*pBufferSize,
									   wmx_pAPDOType_t	 pAPDOType,
									   apdo_DbCmd_t	cmd)
{
	char		* psToken;
	char		* psTokenValue;
	char		* nextpath;
	wmx_Status_t rc = WMX_ST_DATA_UNAVAILABLE;
	pDevDetail_t pDevDetail;
	pDevInfo_t	 pDevInfo;
	pWimax_t pWimax;
	pWmxRadioModule_t  pWmxRadioMod;
	BOOL res;
	
	if(NULL == pInValue)
	{
		return rc;
	}

	pDevDetail = l4db_GetDevDetail();
	pDevInfo = l4db_GetDevInfo();
	pWimax = l4db_GetWimax();	
	// In current version we only use one entry of radio module
	pWmxRadioMod = &pWimax->radioModules[0];

	if(NULL != psPath)
	{
		// get next token
		nextpath = l4db_GetTokensFromPath(psPath, &psToken, &psTokenValue);

		if(NULL != psToken)
		{
			if(NULL == nextpath)
			{
				if(APDO_GetCmd == cmd)
				{
					//device type
					if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_DEV_TYP))
					{
						//Read value from registry key if possible, otherwise set to default
						res = L4Configurations_getApdoDevDetailsDevType(pDevDetail->devType);
						
						rc = l4db_SetStringValueNew(pDevDetail->devType, sizeof(pDevDetail->devType),
							(char *)pInValue, pBufferSize, pAPDOType, cmd);
					}

					//oem == devInfo->man
					else if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_OEM))
					{
						rc = l4db_SetStringValueNew(pDevInfo->manufacturer, sizeof(pDevInfo->manufacturer),
							(char *)pInValue, pBufferSize, pAPDOType, cmd);
					}

					//sw version
					else if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_SW_VERSION))
					{
						// If device type is laptop we need to return the same string as RadioModule\SwV
						if (( FALSE == (OSAL_stricmp (L4DB_DEV_TYPE_CONST,pDevDetail->devType))) || 
							( FALSE == (OSAL_stricmp (L4DB_DEV_TYPE_UPPER_CONST,pDevDetail->devType))) ||
							( FALSE == (OSAL_stricmp ("Null",pDevDetail->devType))))
						{
							OSAL_strncpy_s(pDevDetail->swVersion, sizeof(pDevDetail->swVersion), 
								pWmxRadioMod->productVersions.swVersion, sizeof(pWmxRadioMod->productVersions.swVersion));							
						}
						else // Device is not laptop - try to read from registry
						{
							//Read value from registry key if possible, otherwise set to default
							res = L4Configurations_getApdoDevDetailsSwV(pDevDetail->swVersion);

						}	
						rc = l4db_SetStringValueNew(pDevDetail->swVersion, sizeof(pDevDetail->swVersion),
							(char *)pInValue, pBufferSize, pAPDOType, cmd);
					}

					//hw version
					else if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_HW_VERSION))
					{
						//Read value from registry key if possible, otherwise set to default
						res = L4Configurations_getApdoDevDetailsHwV(pDevDetail->hwVersion);

						rc = l4db_SetStringValueNew(pDevDetail->hwVersion, sizeof(pDevDetail->hwVersion),
							(char *)pInValue, pBufferSize, pAPDOType, cmd);
					}

					//fw version
					else if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_FW_VERSION))
					{
						res = L4Configurations_getApdoDevDetailsFwV(pDevDetail->fwVersion);

						rc = l4db_SetStringValueNew(pDevDetail->fwVersion, sizeof(pDevDetail->fwVersion),
							(char *)pInValue, pBufferSize, pAPDOType, cmd);
					}
					//large object
					else if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_LRG_OBJ))
					{
						rc = l4db_SetStringValueNew(pDevDetail->lrgObj, sizeof(pDevDetail->lrgObj),  
							(char*)pInValue, pBufferSize, pAPDOType, cmd);
					}				
					// Ext 
					else if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_EXT))
					{
						rc = l4db_UpdateDevDetailExtFromPath(nextpath, pInValue, pBufferSize, pAPDOType, cmd);
					}
					// URI
					else if (FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_URI))
					{
						rc = l4db_UpdateDevDetailURIFromPath(nextpath, pInValue, pBufferSize, pAPDOType, cmd);
					}
				}
			}
			else
			{
				// Ext 
				if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_EXT))
				{
					rc = l4db_UpdateDevDetailExtFromPath(nextpath, pInValue, pBufferSize, pAPDOType, cmd);
				}
				// URI
				else if (FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_URI))
				{
					rc = l4db_UpdateDevDetailURIFromPath(nextpath, pInValue, pBufferSize, pAPDOType, cmd);
				}
			}
		}
	}
	else //we don't have a path
	{
		rc = WMX_ST_OK;

		//get command - we need to return all children's name separated by /
		if(APDO_GetCmd == cmd)
		{
			rc = l4db_SetStringValueNew(DEV_DETAIL_CHILDREN_STR, strlen(DEV_DETAIL_CHILDREN_STR) + 1,
				(char*)pInValue, pBufferSize, pAPDOType, cmd);

			*pAPDOType = APDO_Node;
		}
	}
	return rc;
}



///<summary>
/// updates the terminal equipment using a given APDO path according to the APDO command type
///</summary>
wmx_Status_t l4db_UpdateTerminalEquipFromPath(pTerminalEquipment_t pTerminalEquip,
											  char				   *psPath,
											  void			       *pInValue,
											  int				   *pBufferSize,
											  wmx_pAPDOType_t	   pAPDOType,
											  apdo_DbCmd_t	       cmd)
{
	char		* psToken;
	char		* psTokenValue;
	char		* nextpath;
	wmx_Status_t rc = WMX_ST_DATA_UNAVAILABLE;
	BOOL res;

	if((NULL == pTerminalEquip) || (NULL == pInValue))
	{
		return rc;
	}

	if(NULL != psPath)
	{
		// get next token
		nextpath = l4db_GetTokensFromPath(psPath, &psToken, &psTokenValue);

		if(NULL != psToken)
		{
			if(NULL == nextpath)
			{
				if(APDO_GetCmd == cmd)
				{
					//device id
					if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_TERMINAL_DEV_ID))
					{
						//Read value from registry key if possible, otherwise set to default
						res = L4Configurations_getApdoTerminalEquipmentDevID(pTerminalEquip->devId);

						rc = l4db_SetStringValueNew(pTerminalEquip->devId, sizeof(pTerminalEquip->devId),
							(char *)pInValue, pBufferSize, pAPDOType, cmd);
					}

					//device type = const = laptop
					else if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_DEV_TYP))
					{
						res = L4Configurations_getApdoTerminalEquipmentDevType(pTerminalEquip->devType);

						rc = l4db_SetStringValueNew(L4DB_DEV_TYPE_CONST, sizeof(L4DB_DEV_TYPE_CONST),
							(char *)pInValue, pBufferSize, pAPDOType, cmd);
					}

					//sw version
					else if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_SW_VERSION))
					{						
						OSAL_GetOSVersion(pTerminalEquip->productVersions.swVersion);

						rc = l4db_SetStringValueNew(pTerminalEquip->productVersions.swVersion, 
													sizeof(pTerminalEquip->productVersions.swVersion),
													(char *)pInValue, pBufferSize, pAPDOType, cmd);
					}

					//hw version
					else if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_HW_VERSION))
					{
						//Read value from registry key if possible, otherwise set to default
						res = L4Configurations_getApdoTerminalEquipmentHwV(pTerminalEquip->productVersions.hwVersion);

						rc = l4db_SetStringValueNew(pTerminalEquip->productVersions.hwVersion, 
													sizeof(pTerminalEquip->productVersions.hwVersion),
													(char *)pInValue, pBufferSize, pAPDOType, cmd);
					}

					//fw version
					else if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_FW_VERSION))
					{
						//Read value from registry key if possible, otherwise set to default
						res = L4Configurations_getApdoTerminalEquipmentFwV(pTerminalEquip->productVersions.fwVersion);

						rc = l4db_SetStringValueNew(pTerminalEquip->productVersions.fwVersion, 
													sizeof(pTerminalEquip->productVersions.fwVersion),
													(char *)pInValue, pBufferSize, pAPDOType, cmd);
					}
					//man
					else if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_MAN))
					{						
						//Read value from registry key if possible, otherwise set to default
						res = L4Configurations_getApdoTerminalEquipmentManID(pTerminalEquip->productVersions.manufacturer);

						rc = l4db_SetStringValueNew(pTerminalEquip->productVersions.manufacturer, 
							sizeof(pTerminalEquip->productVersions.manufacturer),
							(char*)pInValue, pBufferSize, pAPDOType, cmd);
					}
					//mod
					else if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_MOD))
					{
						//Read value from registry key if possible, otherwise set to default
						res = L4Configurations_getApdoTerminalEquipmentModel(pTerminalEquip->productVersions.model);

						rc = l4db_SetStringValueNew(pTerminalEquip->productVersions.model, 
							sizeof(pTerminalEquip->productVersions.model),
							(char *)pInValue, pBufferSize, pAPDOType, cmd);
					}
				}
			}
		}
	}
	else //we don't have a path
	{
		rc = WMX_ST_OK;

		//get command - we need to return all children's name separated by /
		if(APDO_GetCmd == cmd)
		{
			rc = l4db_SetStringValueNew(TERM_EQUIP_CHILDREN_STR, strlen(TERM_EQUIP_CHILDREN_STR) + 1,
				(char*)pInValue, pBufferSize, pAPDOType, cmd);

			*pAPDOType = APDO_Node;
		}
	}
	return rc;
}




///<summary>
/// updates a wimax radio module node using a given APDO path according to the APDO command type
///</summary>
wmx_Status_t l4db_UpdateWmxRadioModuleFromPath(pWmxRadioModule_t  pWmxRadioMod,
											  char				   *psPath,
											  void			       *pInValue,
											  int				   *pBufferSize,
											  wmx_pAPDOType_t	   pAPDOType,
											  apdo_DbCmd_t	       cmd)
{
	char		* psToken;
	char		* psTokenValue;
	char		* nextpath;
	char		*verStr = "0";
	wmx_Status_t rc = WMX_ST_DATA_UNAVAILABLE;

	if((NULL == pWmxRadioMod) || (NULL == pInValue))
	{
		return rc;
	}

	if(NULL != psPath)
	{
		// get next token
		nextpath = l4db_GetTokensFromPath(psPath, &psToken, &psTokenValue);

		if(NULL != psToken)
		{

			//manufacturer
			if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_MAN))
			{
				if((NULL == nextpath) && (APDO_GetCmd == cmd)) //only get is allowed
				{
					rc = l4db_SetStringValueNew(pWmxRadioMod->productVersions.manufacturer, 
												sizeof(pWmxRadioMod->productVersions.manufacturer),
												(char *)pInValue, pBufferSize, pAPDOType, cmd);
				}
			}

			//model
			else if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_MOD))
			{
				if((NULL == nextpath) && (APDO_GetCmd == cmd)) //only get is allowed
				{
					rc = l4db_SetStringValueNew(pWmxRadioMod->productVersions.model, 
											sizeof(pWmxRadioMod->productVersions.model),
											(char *)pInValue, pBufferSize, pAPDOType, cmd);
				}
			}

			//sw version
			else if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_SW_VERSION))
			{
				if((NULL == nextpath)) //&& (APDO_GetCmd == cmd)) //only get is allowed
				{
					rc = l4db_SetStringValueNew(pWmxRadioMod->productVersions.swVersion, 
											sizeof(pWmxRadioMod->productVersions.swVersion),
											(char *)pInValue, pBufferSize, pAPDOType, cmd);
				}
			}

			//hw version
			else if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_HW_VERSION))
			{
				if((NULL == nextpath) && (APDO_GetCmd == cmd)) //only get is allowed
				{
					rc = l4db_SetStringValueNew(pWmxRadioMod->productVersions.hwVersion, 
											sizeof(pWmxRadioMod->productVersions.hwVersion),
											(char *)pInValue, pBufferSize, pAPDOType, cmd);
				}
			}

			//fw version
			else if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_FW_VERSION))
			{
				if((NULL == nextpath) && (APDO_GetCmd == cmd)) //only get is allowed
				{
					rc = l4db_SetStringValueNew(pWmxRadioMod->productVersions.fwVersion, 
											sizeof(pWmxRadioMod->productVersions.fwVersion),
											(char *)pInValue, pBufferSize, pAPDOType, cmd);
				}
			}

			//mac address
			else if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_MAC_ADDRESS))
			{
				if((NULL == nextpath) && (APDO_GetCmd == cmd)) //only get is allowed
				{
					rc = l4db_SetStringValueNew(pWmxRadioMod->macAddress, 
											sizeof(pWmxRadioMod->macAddress),
											(char *)pInValue, pBufferSize, pAPDOType, cmd);
				}
			}

			//SP lock
			else if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_SP_LOCK))
			{
				if(NULL != nextpath)
				{
					nextpath = l4db_GetTokensFromPath(nextpath, &psToken, &psTokenValue);

					if(NULL != psToken)
					{
						//lock status
						if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_LOCK_STATUS))
						{
							rc = l4db_SetBoolValueNew(&pWmxRadioMod->spLock.lockStatus, pBufferSize, 
														(BOOL*)pInValue, pAPDOType, cmd);
						}
						//operator
						else if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_OPERATOR))
						{
							rc = l4db_SetStringValueNew(pWmxRadioMod->spLock.operatorName, 
								sizeof(pWmxRadioMod->spLock.operatorName) ,
								(char *)pInValue, pBufferSize, pAPDOType, cmd);
						}

						//version number - constant = 0 
						else if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_VER_NUM))
						{
							if(APDO_GetCmd == cmd) //only get command is allowed
							{
								rc = l4db_SetStringValueNew(verStr, sizeof(verStr), (char *)pInValue, 
															pBufferSize, pAPDOType, cmd);
							}
						}


						//lock
						else if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_LOCK))
						{
							rc = l4db_SetStringValueNew(pWmxRadioMod->spLock.lock, 
								sizeof(pWmxRadioMod->spLock.lock),
								(char *)pInValue, pBufferSize, pAPDOType, cmd);
						}
					}
				}
				else //our path is empty
				{
					rc = WMX_ST_OK;

					//get command - we need to return all children's name separated by /
					if(APDO_GetCmd == cmd)
					{
						rc = l4db_SetStringValueNew(SP_LOCK_CHILDREN_STR, strlen(SP_LOCK_CHILDREN_STR) + 1,
													(char*)pInValue, pBufferSize, pAPDOType, cmd);

						*pAPDOType = APDO_Node;
					}
				}
			}
		}
	}
	else //we don't have a path
	{
		rc = WMX_ST_OK;

		//get command - we need to return all children's name separated by /
		if(APDO_GetCmd == cmd)
		{
			rc = l4db_SetStringValueNew(WMX_RADIO_MOD_CHILDREN_STR, strlen(WMX_RADIO_MOD_CHILDREN_STR) + 1,
										(char*)pInValue, pBufferSize, pAPDOType, cmd);

			*pAPDOType = APDO_Node;
		}
	}
	return rc;
}

///<summary>
/// updates the wimax node using a given APDO path according to the APDO command type
///</summary>
wmx_Status_t l4db_UpdateWimaxFromPath(char				   *psPath,
									  void			       *pInValue,
									  int				   *pBufferSize,
									  wmx_pAPDOType_t	   pAPDOType,
									  apdo_DbCmd_t	       cmd)
{
	char		* psToken;
	char		* psTokenValue;
	char		* nextpath;
	int			i;
	wmx_Status_t rc = WMX_ST_DATA_UNAVAILABLE;
	pWimax_t	pWimax;
	pWmxRadioModule_t pWmxRadioModule;
	BOOL		addSeperator = FALSE;
	size_t		tempStrLen = 0;

	if(NULL == pInValue)
	{
		return rc;
	}

	pWimax = l4db_GetWimax();

	if(NULL != psPath)
	{
		// get next token
		nextpath = l4db_GetTokensFromPath(psPath, &psToken, &psTokenValue);

		if(NULL != psToken)
		{
			//wimax radio module
			if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_WMX_RADIO_MODULE))
			{
				//get the unique name 
				if(NULL != nextpath)
				{
					nextpath = l4db_GetTokensFromPath(nextpath, &psToken, &psTokenValue);

					if(NULL != psToken)
					{
						pWmxRadioModule = l4db_GetWmxRadioModule(pWimax->radioModules, 
																pWimax->wmxRadioModulesSize,
																psToken);
						
						if(NULL != pWmxRadioModule)
						{
							rc = l4db_UpdateWmxRadioModuleFromPath(pWmxRadioModule, nextpath, 
																	pInValue, pBufferSize, pAPDOType, cmd);
						}
					}
				}
				else 
				{
					rc = WMX_ST_OK;
					//get command, we should return all the children
					if(APDO_GetCmd == cmd)
					{
						*pAPDOType = APDO_Node;
						((char*)pInValue)[0] = '\0';

						for(i = 0 ; i < MAX_NUM_OF_WIMAX_RADIO_MOD ; i++)
						{
							tempStrLen = OSAL_strnlen(pWimax->radioModules[i].tagName, MAX_TAG_NAME_SIZE);
							if(0 != tempStrLen && MAX_TAG_NAME_SIZE != tempStrLen)
							{
								if(TRUE == addSeperator)
								{
									OSAL_strcat_s(pInValue, *pBufferSize, L4DB_XML_TOKEN_SEPERATOR);
								}
								else
								{
									//the first time we want to copy and not concatenate
									OSAL_strcpy_s(pInValue, *pBufferSize, pWimax->radioModules[i].tagName);
									addSeperator = TRUE;
									continue;
								}
								OSAL_strcat_s(pInValue, *pBufferSize, pWimax->radioModules[i].tagName);
							}
						}
					}
				}
			}

			//Terminal Equipment
			else if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_TERM_EQUIP))
			{
				rc = l4db_UpdateTerminalEquipFromPath(&pWimax->terminalEquipment, nextpath, pInValue, 
														pBufferSize, pAPDOType, cmd);
			}
		
			//to wimax ref - this is a const "./WiMAXSUPP"
			else if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_TO_WIMAX_REF))
			{			
				if((NULL == nextpath) && (APDO_GetCmd == cmd))
				{
					rc = l4db_SetStringValueNew(L4DB_WMX_REF_CONST, strlen(L4DB_WMX_REF_CONST) + 1,
								(char*)pInValue, pBufferSize, pAPDOType, cmd);
				}
			}

			//Dev Cap
			else if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_DEV_CAP))
			{
				rc = l4db_UpdateDevCapFromPath(nextpath, pInValue, pBufferSize, pAPDOType, cmd);
			}
		}
	}
	else //we don't have a path
	{
		rc = WMX_ST_OK;

		//get command - we need to return all children's name separated by /
		if(APDO_GetCmd == cmd)
		{
			rc = l4db_SetStringValueNew(WIMAX_CHILDREN_STR, strlen(WIMAX_CHILDREN_STR) + 1,
				(char*)pInValue, pBufferSize, pAPDOType, cmd);

			*pAPDOType = APDO_Node;
		}
	}
	return rc;
}
/// <summary>
/// Run add/get/delete/update command using input path. This is interface function for upper layers
/// </summary>
/// <param name="psPath">(IN)  the path of command</param>
/// <param name="psValue">(IN) pointer for value</param>
/// <param name="cmd">(IN) command (get/update/delete/add)</param>
/// <returns>wmx_Status_t </returns>
wmx_Status_t l4db_UpdateOperatorFromPath(char			*psPath,
										void			*psValue,
										int			*pBufferSize,
										wmx_pAPDOType_t pAPDOType,
										apdo_DbCmd_t	cmd)
{
	char				* psToken;
	char				* psTokenValue;
	char				* nextpath;
	wmx_Status_t		rc = WMX_ST_DATA_UNAVAILABLE;
	pProvisionedNsp_t	pNsp = NULL;
	int					i;
	pProvisionedNsp_t	pOperators;
	BOOL				addSeperator = FALSE, allocatedNsp = FALSE;
	size_t				tempStrLen = 0;

	if(NULL == psValue)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "l4db_UpdateOperatorFromPath: psPath or psValue are NULL");
		return WMX_ST_FAIL;
	}

	//get the operator's unique id
	if( NULL != psPath)
	{
		nextpath = l4db_GetTokensFromPath(psPath, &psToken, &psTokenValue);

		if(NULL != psToken)
		{
			//search for the specified NSP
			pNsp = l4db_GetProvisionedNspByTagName(psToken);

			//if the NSP doesn't exist, allocate it
			if((NULL == pNsp) && (APDO_AddCmd == cmd))
			{
				pNsp = l4db_AllocNsp(psToken);
				allocatedNsp = TRUE;
			}

			if(NULL == pNsp)
			{
				return rc;
			}
			else
			{
				rc = WMX_ST_OK;
			}
		}

		//get one of the tags of a specific NSP
		if(nextpath && *nextpath)
		{
			nextpath = l4db_GetTokensFromPath(nextpath, &psToken, &psTokenValue);

			if(NULL != psToken)
			{
				rc = WMX_ST_DATA_UNAVAILABLE;
				
				//network parameters
				if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_NETWORK_PARM))
				{
					rc = l4db_UpdateNetworkParmFromPath(&pNsp->nwParams, nextpath, psValue, pBufferSize, pAPDOType, cmd, pNsp->tagName);
				}
				//subscription parameters
				else if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_SUBSCRIPTION_PARAM))
				{
					rc = l4db_UpdateSubscriptionParamsFromPath(&pNsp->subscriptionParams, nextpath, psValue,
						pBufferSize, pAPDOType, cmd);
				}
				//contacts
				else if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_CONTACTS))
				{
					rc = l4db_UpdateContactsFromPath(pNsp->contacts, nextpath, psValue, pBufferSize, pAPDOType, cmd);
				}

				//to ip ref - this is a const "./IP"
				else if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_TO_IP_REF))
				{
					if((NULL == nextpath) && (APDO_GetCmd == cmd))
					{
						rc = l4db_SetStringValueNew(L4DB_IP_REF_CONST, strlen(L4DB_IP_REF_CONST) + 1,
							(char*)psValue, pBufferSize, pAPDOType, cmd);				
					}
					else
					{
						rc = WMX_ST_DATA_UNAVAILABLE;
					}
				}
			}
		}
		else // we don't have a path.
		{
			//Get command - this isn't a leaf, we should return a string with all the children's name separated by /
			if(APDO_GetCmd == cmd) 
			{
				rc = l4db_SetStringValueNew(OPERATOR_CHILDREN_STR, strlen(OPERATOR_CHILDREN_STR) + 1,
					(char*)psValue, pBufferSize, pAPDOType, cmd);

				*pAPDOType = APDO_Node;
			}
			//we should "delete" our NSP
			else if(APDO_DeleteCmd == cmd) 
			{
				l4db_InitNsp(pNsp);
				rc = WMX_ST_OK;
			}
			//if this is an update \ add command, we already handled it because we allocated 
			//an NSP with the given tag name
		}

		if((WMX_ST_OK != rc) && (TRUE == allocatedNsp))
		{
			//init the NSP which we allocated, an error has occurred
			l4db_InitNsp(pNsp);
		}
	}
	else // we don't have a path.
	{
		pOperators = l4db_GetOperatorNode();
		rc = WMX_ST_OK;

		//Get command - this isn't a leaf, we should return a string with all the children's name separated by /
		if(APDO_GetCmd == cmd) 
		{
			*pAPDOType = APDO_Node;

			((char*)psValue)[0] = '\0';

			for(i = 0 ; i < WMX_NSPS_MAX_NUM ; i++)
			{
				tempStrLen = OSAL_strnlen(pOperators[i].tagName, MAX_TAG_NAME_SIZE);
				if(0 != tempStrLen && MAX_TAG_NAME_SIZE != tempStrLen)
				{
					if(TRUE == addSeperator)
					{
						OSAL_strcat_s(psValue, *pBufferSize, L4DB_XML_TOKEN_SEPERATOR);
					}
					else
					{
						//the first time we want to copy and not concatenate
						OSAL_strcpy_s(psValue, *pBufferSize, pOperators[i].tagName);	
						addSeperator = TRUE;
						continue;
					}

					OSAL_strcat_s(psValue, *pBufferSize, pOperators[i].tagName);	
				}
			}
		}
		//we should "delete" our NSP
		else if(APDO_DeleteCmd == cmd) 
		{
			for(i = 0; i < WMX_NSPS_MAX_NUM ; i++)
			{
				l4db_InitNsp(&pOperators[i]);
			}
		}
		//if this is an update \ add command, we already handled it because we allocated 
		//an NSP with the given tag name
	}	
	return rc; 
}



/// <summary>
/// Update the WiMAXSupp node
/// </summary>
wmx_Status_t l4db_UpdateWmxSuppFromPath(char			*psPath,
										void			*pInValue,
										int			*pBufferSize,
										wmx_pAPDOType_t pAPDOType,
										apdo_DbCmd_t	cmd)
{
	char		* psToken;
	char		* psTokenValue;
	char		* nextpath;
	wmx_Status_t rc = WMX_ST_DATA_UNAVAILABLE;

	if(NULL == pInValue)
	{
		return rc;
	}

	if(NULL != psPath)
	{
		// get next token
		nextpath = l4db_GetTokensFromPath(psPath, &psToken, &psTokenValue);

		if(NULL != psToken)
		{
				//operator
				if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_OPERATOR))
				{
					rc = l4db_UpdateOperatorFromPath(nextpath, pInValue , pBufferSize, pAPDOType, cmd);
				}
		}
	}
	else //we don't have a path
	{
		rc = WMX_ST_OK;

		//get command - we need to return all children's name separated by /
		if(APDO_GetCmd == cmd)
		{
			rc = l4db_SetStringValueNew(L4DB_XML_TOKEN_OPERATOR, strlen(L4DB_XML_TOKEN_OPERATOR) + 1,
										(char*)pInValue, pBufferSize, pAPDOType, cmd);

			*pAPDOType = APDO_Node;
		}
	}
	return rc;
}
///<summary>
/// updates the state value
///</summary>
wmx_Status_t l4db_UpdateFumoStateValue(pDownloadState_t pDownloadState, void *pInValue,
								wmx_pAPDOType_t pAPDOType, apdo_DbCmd_t cmd)
{
	char			buff[BUFF_SIZE];
	wmx_Status_t	rc = WMX_ST_FAIL;

	switch(cmd)
	{
	case APDO_AddCmd:
	case APDO_UpdateCmd:
		// set the state
		if(APDO_Integer == *pAPDOType)
		{
			OSAL_sprintf_s(buff,sizeof(buff) - 1, "%d", *(int *)pInValue);
		}
		else if(APDO_String == *pAPDOType)
		{
			OSAL_strcpy_s(buff, BUFF_SIZE, (char*)pInValue);
		}
		else
		{
			rc = WMX_ST_WRONG_ARGUMENT;
			break;
		}

		rc = ConvertToDownloadState(buff, pDownloadState);
		break;

	case APDO_GetCmd:

		ConvertDownloadStateToStr(*pDownloadState, buff, BUFF_SIZE);		
		OSAL_sscanf_s(buff, "%d", pInValue);
		*pAPDOType = APDO_Integer;
		rc = WMX_ST_OK ;
		break;

	case APDO_DeleteCmd:
		*pDownloadState = L4DB_INVALID_INDEX;
		rc = WMX_ST_OK ;
		break;
	}

	return rc;
}

/// <summary>
/// Run add/get/delete/update command using input path. This is interface function for upper layers
/// </summary>
/// <param name="psPath">(IN)  the path of command</param>
/// <param name="psValue">(IN) pointer for value</param>
/// <param name="cmd">(IN) command (get/update/delete/add)</param>
/// <returns>wmx_Status_t </returns>
wmx_Status_t l4db_UpdateFumoFromPath(char			*psPath,
									 void			*psValue,
									 int			*pBufferSize,
									 wmx_pAPDOType_t pAPDOType,
									 apdo_DbCmd_t	cmd)
{
	char				* psToken;
	char				* psTokenValue;
	char				* nextpath;
	wmx_Status_t		rc = WMX_ST_DATA_UNAVAILABLE;	
	int					i;
	pFumoParams_t		pFumoNode = NULL;
	BOOL				addSeperator = FALSE, allocatedNsp = FALSE;
	size_t				tempStrLen = 0;

	if(NULL == psValue)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "l4db_UpdateFumoFromPath: psPath or psValue are NULL");
		return WMX_ST_FAIL;
	}

	if( NULL != psPath)
	{
		nextpath = l4db_GetTokensFromPath(psPath, &psToken, &psTokenValue);

		if(NULL != psToken)
		{
			// Get specific Fumo node if exists
			pFumoNode = l4db_GetFumoParamsNodeByTagName(psToken);
			
			//if the Fumo node doesn't exist, allocate it
			if((NULL == pFumoNode) && (APDO_AddCmd == cmd))
			{
				pFumoNode = l4db_AllocFumoNode(psToken);
				allocatedNsp = TRUE;
			}

			if(NULL == pFumoNode)
			{
				return rc;
			}
			else
			{
				rc = WMX_ST_OK;
			}
		}

		//get one of the tags of a specific node
		if(nextpath && *nextpath)
		{
			nextpath = l4db_GetTokensFromPath(nextpath, &psToken, &psTokenValue);

			if(NULL != psToken)
			{
				// pkg name
				if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_PKG_NAME))
				{
					// This is a leaf make sure the path ends
					if(NULL == nextpath)
					{
						rc = l4db_SetStringValueNew(pFumoNode->pkgName, sizeof(pFumoNode->pkgName), 
							(char*)psValue, pBufferSize, pAPDOType, cmd);
					}
					else
					{
						rc = WMX_ST_DATA_UNAVAILABLE;
					}
				}						

				// pkg version
				if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_PKG_VERSION))
				{
					// This is a leaf make sure the path ends
					if(NULL == nextpath)
					{
						rc = l4db_SetStringValueNew(pFumoNode->pkgVersion, sizeof(pFumoNode->pkgVersion), 
							(char*)psValue, pBufferSize, pAPDOType, cmd);
					}
					else
					{
						rc = WMX_ST_DATA_UNAVAILABLE;
					}
				}

				// Download and update
				if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_DOWNLOAD_AND_UPDATE))
				{
					nextpath = l4db_GetTokensFromPath(nextpath, &psToken, &psTokenValue);

					if(NULL != psToken)
					{
						if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_PKG_URL))
						{
							// This is a leaf make sure the path ends
							if(NULL == nextpath)
							{								
								rc = l4db_SetStringValueNew(pFumoNode->downloadAndUpdatePkgURL, 
									sizeof(pFumoNode->downloadAndUpdatePkgURL), (char*)psValue, 
									pBufferSize, pAPDOType, cmd);
							}
							else
							{
								rc = WMX_ST_DATA_UNAVAILABLE;
							}
						}						
					}					
				}

				// Download
				if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_DOWNLOAD))
				{
					nextpath = l4db_GetTokensFromPath(nextpath, &psToken, &psTokenValue);

					if(NULL != psToken)
					{
						if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_PKG_URL))
						{
							// This is a leaf make sure the path ends
							if(NULL == nextpath)
							{
								rc = l4db_SetStringValueNew(pFumoNode->downloadPkgURL, 
									sizeof(pFumoNode->downloadPkgURL), (char*)psValue, 
									pBufferSize, pAPDOType, cmd);
							}
							else
							{
								rc = WMX_ST_DATA_UNAVAILABLE;
							}
						}						
					}					
				}

				// State
				if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_STATE))
				{
					// This is a leaf make sure the path ends
					if(NULL == nextpath)
					{
						rc = l4db_UpdateFumoStateValue(&pFumoNode->state, psValue, pAPDOType, cmd); 						
					}
					else
					{
						rc = WMX_ST_DATA_UNAVAILABLE;
					}
				}


			}
		}
		else // we don't have a path.
		{			
			//Get command - this isn't a leaf, we should return a string with all the children's name separated by /
			if(APDO_GetCmd == cmd) 
			{
				rc = l4db_SetStringValueNew(FUMO_CHILDREN_STR, strlen(FUMO_CHILDREN_STR) + 1,
					(char*)psValue, pBufferSize, pAPDOType, cmd);

				*pAPDOType = APDO_Node;
			}
			//we should "delete" our NSP
			else if(APDO_DeleteCmd == cmd) 
			{
				if (pFumoNode!=NULL)
				{
					l4db_InitFumoNode(pFumoNode);
				}
				rc = WMX_ST_OK;
			}
			//if this is an update \ add command, we already handled it because we allocated 
			//an NSP with the given tag name
		}

		if((WMX_ST_OK != rc) && (TRUE == allocatedNsp))
		{
			//init the Fumo node which we allocated, an error has occurred
			l4db_InitFumoNode(pFumoNode);
		}
	}
	else // we don't have a path.
	{
		pFumoNode = l4db_GetFumoNode();
		rc = WMX_ST_OK;

		//Get command - this isn't a leaf, we should return a string with all the children's name separated by /
		if(APDO_GetCmd == cmd) 
		{
			*pAPDOType = APDO_Node;

			((char*)psValue)[0] = '\0';

			for(i = 0 ; i < WMX_FUMO_NODES_MAX_NUM; i++)
			{
				tempStrLen = OSAL_strnlen(pFumoNode[i].tagName, MAX_TAG_NAME_SIZE);
				if(0 != tempStrLen && MAX_TAG_NAME_SIZE != tempStrLen)
				{
					if(TRUE == addSeperator)
					{
						OSAL_strcat_s(psValue, *pBufferSize, L4DB_XML_TOKEN_SEPERATOR);
					}
					else
					{
						//the first time we want to copy and not concatenate
						OSAL_strcpy_s(psValue, *pBufferSize, pFumoNode[i].tagName);	
						addSeperator = TRUE;
						continue;
					}

					OSAL_strcat_s(psValue, *pBufferSize, pFumoNode[i].tagName);	
				}
			}
		}
		//we should "delete" our NSP
		else if(APDO_DeleteCmd == cmd) 
		{
			for(i = 0; i < WMX_FUMO_NODES_MAX_NUM ; i++)
			{
				l4db_InitFumoNode(&pFumoNode[i]);
			}
		}
		//if this is an update \ add command, we already handled it because we allocated 
		//an NSP with the given tag name
	}	
	return rc; 	
}

/// <summary>
/// Run add/get/delete/update command using input path. This is interface function for upper layers
/// </summary>
/// <param name="psPath">(IN)  the path of command</param>
/// <param name="psValue">(IN) pointer for value</param>
/// <param name="cmd">(IN) command (get/update/delete/add)</param>
/// <returns>wmx_Status_t </returns>
wmx_Status_t l4db_UpdateApdoInternalFromPath(char			*psPath,
									 void			*pInValue,
									 int			*pBufferSize,
									 wmx_pAPDOType_t pAPDOType,
									 apdo_DbCmd_t	cmd)
{
	char* psToken;
	char* psTokenValue;
	char* nextpath;
	wmx_Status_t rc = WMX_ST_DATA_UNAVAILABLE;
	pAPDOInternalParams_t pAPDOInternal;

	if(NULL == pInValue)
	{
		return rc;
	}

	pAPDOInternal = l4db_GetAPDOInternalParams();

	if(NULL != psPath)
	{
		// get next token
		nextpath = l4db_GetTokensFromPath(psPath, &psToken, &psTokenValue);

		if(NULL != psToken)
		{
			// NSPsToDMAcc
			if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_NSPS_TO_DMACC))
			{				
				rc = l4db_UpdateNSPsToDMAccFromPath(nextpath, pInValue , pBufferSize, pAPDOType, cmd);
			}	
			else if (FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_BOOTSTRAP_INFO))
			{
				rc = l4db_UpdateBootstrapInfoFromPath(nextpath, pInValue , pBufferSize, pAPDOType, cmd);
			}
		}
	}
	else //we don't have a path
	{
		rc = WMX_ST_OK;

		//get command - we need to return all children's name separated by /
		if(APDO_GetCmd == cmd)
		{
			rc = l4db_SetStringValueNew(APDO_INTERNAL_CHILDREN_STR, strlen(APDO_INTERNAL_CHILDREN_STR) + 1,
				(char*)pInValue, pBufferSize, pAPDOType, cmd);

			*pAPDOType = APDO_Node;
		}
	}
	return rc;
}

/// <summary>
/// Run add/get/delete/update command using input path. This is interface function for upper layers
/// </summary>
/// <param name="psPath">(IN)  the path of command</param>
/// <param name="psValue">(IN) pointer for value</param>
/// <param name="cmd">(IN) command (get/update/delete/add)</param>
/// <returns>wmx_Status_t </returns>
wmx_Status_t l4db_UpdateNSPsToDMAccFromPath(char			*psPath,
											 void			*pInValue,
											 int			*pBufferSize,
											 wmx_pAPDOType_t pAPDOType,
											 apdo_DbCmd_t	cmd)
{
	char* psToken;
	char* psTokenValue;
	char* nextpath;
	int	i;
	wmx_Status_t rc = WMX_ST_DATA_UNAVAILABLE;	
	pAPDOInternalParams_t pAPDOInternal;
	pNSPToDMAcc_t pNSPsToDMAcc;
	BOOL addSeperator = FALSE;
	size_t	tempStrLen = 0;

	if(NULL == pInValue)
	{
		return rc;
	}

	pAPDOInternal = l4db_GetAPDOInternalParams();

	if(NULL != psPath)
	{
		// get next token
		nextpath = l4db_GetTokensFromPath(psPath, &psToken, &psTokenValue);

		if(NULL != psToken)
		{
			pNSPsToDMAcc = l4db_GetNSPsToDMAccStruct(pAPDOInternal, psToken);

			if(NULL != pNSPsToDMAcc)
			{
				// get next token
				nextpath = l4db_GetTokensFromPath(nextpath, &psToken, &psTokenValue);

				// To-DMAcc
				if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_TO_DM_ACCOUNT))
				{
					rc = l4db_SetStringValueNew(pNSPsToDMAcc->toDMAcc, sizeof(pNSPsToDMAcc->toDMAcc),
						(char*)pInValue, pBufferSize, pAPDOType, cmd);

				}
			}
		}
	}
	else 
	{
		rc = WMX_ST_OK;
		//get command, we should return all the children
		if(APDO_GetCmd == cmd)
		{
			*pAPDOType = APDO_Node;
			((char*)pInValue)[0] = '\0';

			for(i=0; i<WMX_NSPS_TO_DMACC_NODES_MAX_NUM; i++)
			{
				tempStrLen = OSAL_strnlen(pAPDOInternal->nspsToDmAcc[i].tagName, MAX_TAG_NAME_SIZE);
				if(0 != tempStrLen && MAX_TAG_NAME_SIZE != tempStrLen)
				{
					if(TRUE == addSeperator)
					{
						OSAL_strcat_s(pInValue, *pBufferSize, L4DB_XML_TOKEN_SEPERATOR);
					}
					else
					{
						//the first time we want to copy and not concatenate
						OSAL_strcpy_s(pInValue, *pBufferSize, pAPDOInternal->nspsToDmAcc[i].tagName);
						addSeperator = TRUE;
						continue;
					}
					OSAL_strcat_s(pInValue, *pBufferSize, pAPDOInternal->nspsToDmAcc[i].tagName);
				}
			}
		}
	}
	return rc;
}

/// <summary>
/// Run add/get/delete/update command using input path. This is interface function for upper layers
/// </summary>
/// <param name="psPath">(IN)  the path of command</param>
/// <param name="psValue">(IN) pointer for value</param>
/// <param name="cmd">(IN) command (get/update/delete/add)</param>
/// <returns>wmx_Status_t </returns>
wmx_Status_t l4db_UpdateBootstrapInfoFromPath(char			*psPath,
											 void			*pInValue,
											 int			*pBufferSize,
											 wmx_pAPDOType_t pAPDOType,
											 apdo_DbCmd_t	cmd)
{
	char* psToken;
	char* psTokenValue;
	char* nextpath;
	int	i;
	wmx_Status_t rc = WMX_ST_DATA_UNAVAILABLE;	
	pAPDOInternalParams_t pAPDOInternal;
	pBootstrapInfo_t pBootstrapInfo;
	BOOL addSeperator = FALSE;
	size_t	tempStrLen = 0;

	if(NULL == pInValue)
	{
		return rc;
	}

	pAPDOInternal = l4db_GetAPDOInternalParams();

	if(NULL != psPath)
	{
		// get next token
		nextpath = l4db_GetTokensFromPath(psPath, &psToken, &psTokenValue);

		if(NULL != psToken)
		{
			pBootstrapInfo = l4db_GetBootstrapInfoStruct(pAPDOInternal, psToken);

			if(NULL != pBootstrapInfo)
			{
				// get next token
				nextpath = l4db_GetTokensFromPath(nextpath, &psToken, &psTokenValue);

				// ServerID
				if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_SERVER_ID))
				{
					rc = l4db_SetStringValueNew(pBootstrapInfo->serverID, sizeof(pBootstrapInfo->serverID),
						(char*)pInValue, pBufferSize, pAPDOType, cmd);
				}
				// ServerUserName
				else if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_SERVER_USER_NAME))
				{
					rc = l4db_SetStringValueNew(pBootstrapInfo->serverUserName, sizeof(pBootstrapInfo->serverUserName),
						(char*)pInValue, pBufferSize, pAPDOType, cmd);
				}
				// server url
				else if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_SERVER_URL))
				{
					rc = l4db_SetStringValueNew(pBootstrapInfo->serverURL, sizeof(pBootstrapInfo->serverURL),
						(char*)pInValue, pBufferSize, pAPDOType, cmd);
				}
				// client user name
				else if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_CLIENT_USER_NAME))
				{
					rc = l4db_SetStringValueNew(pBootstrapInfo->clientUserName, sizeof(pBootstrapInfo->clientUserName),
						(char*)pInValue, pBufferSize, pAPDOType, cmd);
				}
				// PortNbr
				else if(FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_PORT_NUMBER))
				{
					rc = l4db_SetStringValueNew(pBootstrapInfo->portNbr, sizeof(pBootstrapInfo->portNbr),
						(char*)pInValue, pBufferSize, pAPDOType, cmd);
				}
			}
		}
	}
	else 
	{
		rc = WMX_ST_OK;
		//get command, we should return all the children
		if(APDO_GetCmd == cmd)
		{
			*pAPDOType = APDO_Node;
			((char*)pInValue)[0] = '\0';

			for(i=0; i<WMX_NSPS_TO_DMACC_NODES_MAX_NUM; i++)
			{
				tempStrLen = OSAL_strnlen(pAPDOInternal->nspsToDmAcc[i].tagName, MAX_TAG_NAME_SIZE);
				if(0 != tempStrLen && MAX_TAG_NAME_SIZE != tempStrLen)
				{
					if(TRUE == addSeperator)
					{
						OSAL_strcat_s(pInValue, *pBufferSize, L4DB_XML_TOKEN_SEPERATOR);
					}
					else
					{
						//the first time we want to copy and not concatenate
						OSAL_strcpy_s(pInValue, *pBufferSize, pAPDOInternal->nspsToDmAcc[i].tagName);
						addSeperator = TRUE;
						continue;
					}
					OSAL_strcat_s(pInValue, *pBufferSize, pAPDOInternal->nspsToDmAcc[i].tagName);
				}
			}
		}
	}
	return rc;
}

//////////////////////////////////////////////////////////////////////////
/// <summary>
/// Run add/get/delete/update command using input path. This is interface function for upper layers
/// </summary>
/// <param name="psPath">(IN)  the path of command</param>
/// <param name="psValue">(IN) pointer for value</param>
/// <param name="cmd">(IN) command (get/update/delete/add)</param>
/// <returns>wmx_Status_t </returns>
wmx_Status_t l4db_RunCmdFromPath(char			*psPath,
								 void			*psValue,
								 int			*pBufferSize,
								 wmx_pAPDOType_t pAPDOType,
								 apdo_DbCmd_t	cmd)
{
	char				* psToken;
	char				* psTokenValue;
	char				* nextpath;
	wmx_Status_t		rc = WMX_ST_DATA_UNAVAILABLE;
	wmx_APDOType_t		apdoType;
	char				pathbuff[BUFF_SIZE];
	int					length;

	if((NULL == psPath) || (NULL == psValue))
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "l4db_RunCmdFromPath: psPath or psValue are NULL");
		return WMX_ST_FAIL;
	}

	// The path which we got from the user can be lost and we need to modify it.
	// Our solution is to copy it on the stack.
	apdoType = APDO_String;
	length = (UINT32)OSAL_strnlen(psPath, MAX_STRING_VALIDATE);
	rc = l4db_SetStringValueNew(pathbuff, sizeof(pathbuff), psPath, &length, &apdoType, APDO_AddCmd);

	rc = WMX_ST_DATA_UNAVAILABLE;

	nextpath = l4db_GetTokensFromPath(pathbuff, &psToken, &psTokenValue);

	// Root token
	if (psToken && (FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_ROOT)))
	{
		if (nextpath == NULL)
		{		
			//get command - we need to return all children's name separated by 
			if(APDO_GetCmd == cmd)
			{			
				rc = l4db_SetStringValueNew(ROOT_CHILDREN_STR, strlen(ROOT_CHILDREN_STR) + 1,
					(char*)psValue, pBufferSize, pAPDOType, cmd);

				*pAPDOType = APDO_Node;
			}

			return rc;
		}
		else
		{
			// Ignore the L4DB_XML_TOKEN_ROOT			
			nextpath = l4db_GetTokensFromPath(nextpath, &psToken, &psTokenValue);
		}

	}

	//a WiMAXSupp token
	if(psToken && (FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_WMX_SUPP)))
	{
		rc = l4db_UpdateWmxSuppFromPath(nextpath, psValue , pBufferSize, pAPDOType, cmd);
	}

	//a dev info token
	else if(psToken && (FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_DEV_INFO)))
	{
		rc = l4db_UpdateDevInfoFromPath(nextpath, psValue , pBufferSize, pAPDOType, cmd);
	}

	//a dev detail token
	else if(psToken && (FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_DEV_DETAIL)))
	{
		rc = l4db_UpdateDevDetailFromPath(nextpath, psValue , pBufferSize, pAPDOType, cmd);
	}

	//a wimax token
	else if(psToken && (FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_WIMAX)))
	{
		rc = l4db_UpdateWimaxFromPath(nextpath, psValue , pBufferSize, pAPDOType, cmd);
	}

	// a FUMO token
	else if (psToken && (FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_FUMO)))
	{
		rc = l4db_UpdateFumoFromPath(nextpath, psValue , pBufferSize, pAPDOType, cmd);
	}		

	// ApdoInternal
	else if (psToken && (FALSE == l4db_CompareString(psToken, L4DB_XML_TOKEN_APDO_INTERNAL)))
	{
		rc = l4db_UpdateApdoInternalFromPath(nextpath, psValue , pBufferSize, pAPDOType, cmd);
	}		

	return rc; 
}