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
#include "FormatConversions.h"
#include "stdio.h"
#include "wmxSDK_Sup_Defines.h"
#include "wmxSDK_Nds_3.h"

void strlower(char *target, const char *source, UINT32 targetLen)
{
	UINT32 i;

	for ( i = 0; i < targetLen && source[i] ; i++)
	{
		target[i] = (char)tolower(source[i]);
	}
	target[i] = '\0';
}

wmx_UserConnectMode_t ConvertToConnectMode(const char* val)
{
	char lowerVal[MAX_FILENAME_LEN];
	strlower(lowerVal, val, MAX_FILENAME_LEN);	
	if (0 == strcmp(lowerVal, "semimanscanmanconnect"))
	{
		return UserSemiManScanManConnect;
	} 
	else if (0 == strcmp(lowerVal, "semimanscanautoconnect"))
	{
		return UserSemiManScanAutoConnect;
	}
	else if (0 == strcmp(lowerVal, "autoscanmanconnect"))
	{
		return UserAutoScanManConnect;
	}
	else if (0 == strcmp(lowerVal, "autoscanautoconnect"))
	{
		return UserAutoScanAutoConnect;
	}
	else
	{
		return UserManScanManConnect;
	}
}
 void ConvertConnectModeToStr(wmx_UserConnectMode_t val, char * dst, int size)
{
	if(val == UserSemiManScanManConnect)
	{
		OSAL_strcpy_s(dst, size, "SemiManScanManConnect");
	}
	else if(val == UserSemiManScanAutoConnect)
	{
		OSAL_strcpy_s(dst, size, "SemiManScanAutoConnect");
	}
	else if(val == UserAutoScanManConnect)
	{
		OSAL_strcpy_s(dst, size, "AutoScanManConnect");
	}
	else if(val == UserAutoScanAutoConnect)
	{
		OSAL_strcpy_s(dst, size, "AutoScanAutoConnect");
	}
	else // UserManScanManConnect
	{
		OSAL_strcpy_s(dst, size, "ManScanManConnect");
	}
 }

wmx_UserConnectMode_t ConvertToRoamingMode(const char* val)
{
	char lowerVal[MAX_FILENAME_LEN];
	strlower(lowerVal, val, MAX_FILENAME_LEN);
	if (0 == strcmp(lowerVal, "enable"))
	{
		return UserEnableRoaming;
	} 
	else
	{
		return UserDisableRoaming;
	}
}
void ConvertRoamingModeToStr(wmx_UserConnectMode_t val, char * dst, int size)
{
	if(val == UserEnableRoaming)
	{
		OSAL_strcpy_s(dst, size, "Enable");
	}
	else
	{
		OSAL_strcpy_s(dst, size, "Disable");
	}
}

wmx_RssiThreshold_t ConvertToRssiTH(const char* val)
{
	return (wmx_RssiThreshold_t)atoi(val);
}
wmx_CinrThreshold_t ConvertToCinrTH(const char* val)
{
	return (wmx_CinrThreshold_t)atoi(val);
}
wmx_ChannelID_t ConvertToChannelID(const char* val)
{
	if(!val)
		return 0;

	return (wmx_ChannelID_t)atoi(val);
}
wmx_Frequency_t ConvertToFrequency(const char* val)
{
	if(!val)
		return 0;

	return atoi(val);
}

 wmx_Status_t ConvertToBandWidth(const char* val,wmx_pBW_t pBWtype)
{
	wmx_Status_t rc = WMX_ST_OK;

	if(!val || !pBWtype)
		return WMX_ST_FAIL;

	else if (0 == OSAL_CAPI_strncmp(val, "3500",strlen("3500")))
	{
		*pBWtype = BW_3_5;
	}
	else if (0 == OSAL_CAPI_strncmp(val, "5000",strlen("5000")))
	{
		*pBWtype = BW_5;
	}
	else if (0 == OSAL_CAPI_strncmp(val, "7000",strlen("7000")))
	{
		*pBWtype = BW_7;
	}
	else if (0 == OSAL_CAPI_strncmp(val, "8750",strlen("8750")))
	{
		*pBWtype = BW_8_75;
	}
	else if (0 == OSAL_CAPI_strncmp(val, "10000",strlen("10000")))
	{
		*pBWtype = BW_10;
	}
	else if(0 == OSAL_CAPI_strncmp(val, "-1", strlen("-1")))
	{
		*pBWtype = (wmx_BW_t)L4DB_INVALID_INDEX;
	}
	else
	{
		rc= WMX_ST_WRONG_ARGUMENT;
	}

	return rc;
}

void ConvertBandWidthToStr(wmx_BW_t bwt, char * dst, int size)
{
	switch(bwt)
	{
		case BW_3_5: 
			OSAL_strcpy_s(dst, size, "3500");
		break;

		case BW_5: 
			OSAL_strcpy_s(dst, size, "5000");
		break;

		case BW_7: 
			OSAL_strcpy_s(dst, size, "7000");
		break;

		case BW_8_75: 
			OSAL_strcpy_s(dst, size, "8750");
		break;

		case BW_10: 
			OSAL_strcpy_s(dst, size, "10000");
		break;

		default:
			OSAL_strcpy_s(dst, size, "-1");
	}
}

 wmx_Status_t ConvertToFFT(const char* val, wmx_pFFT_t pFFT)
{
	wmx_Status_t rc = WMX_ST_OK;

	if(!val || !pFFT)
		return WMX_ST_FAIL;

	if (0 == strcmp(val, "512"))
	{
		*pFFT = FFT_512;
	} 
	else if(0 == strcmp(val, "1024"))
	{
		*pFFT = FFT_1024;
	}
	else if(0 == strncmp(val, "-1", strlen("-1")))
	{
		*pFFT = (wmx_FFT_t)L4DB_INVALID_INDEX;
	}
	else
	{
		rc = WMX_ST_WRONG_ARGUMENT;
	}

	return rc;
}

void ConvertFFTtoStr(wmx_FFT_t fft, char * dst, int size)
{
	switch(fft)
	{
		//case FFT_0: 
		//	fftString ="0" ;
		//break;
		case FFT_512: 
			OSAL_strcpy_s(dst, size, "512") ;
		break;

		case FFT_1024: 
			OSAL_strcpy_s(dst, size, "1024") ;
		break;

		default:
			OSAL_strcpy_s(dst, size, "-1") ;
	}
}

wmx_Status_t ConvertToDownloadState(const char* val,  pDownloadState_t pDownloadState)
{
	wmx_Status_t rc = WMX_ST_OK;

	if(!val || !pDownloadState)
		return WMX_ST_FAIL;

	if (0 == strcmp(val, "10"))
	{
		*pDownloadState = dsDownloadIdle;
	} 
	else if(0 == strcmp(val, "20"))
	{
		*pDownloadState = dsDownloadFailed;
	}
	else if(0 == strcmp(val, "30"))
	{
		*pDownloadState = dsDownloadProgressing;
	}
	else if(0 == strcmp(val, "40"))
	{
		*pDownloadState = dsDownloadComplete;
	}
	else if(0 == strcmp(val, "50"))
	{
		*pDownloadState = dsReadyToUpdate;
	}
	else if(0 == strcmp(val, "60"))
	{
		*pDownloadState = dsUpdateProgressing;
	}
	else if(0 == strcmp(val, "70"))
	{
		*pDownloadState = dsUpdateFailedHaveData;
	}
	else if(0 == strcmp(val, "80"))
	{
		*pDownloadState = dsUpdateFailedNoData;
	}
	else if(0 == strcmp(val, "90"))
	{
		*pDownloadState = dsUpdateSuccessfulHaveData;
	}
	else if(0 == strcmp(val, "100"))
	{
		*pDownloadState = dsUpdateSuccessfulNoData;
	}
	else
	{
		rc = WMX_ST_WRONG_ARGUMENT;
	}	

	return rc;
}

void ConvertDownloadStateToStr(DownloadState_t downloadState, char * dst, int size)
{
	switch(downloadState)
	{
		case dsDownloadIdle:
			OSAL_strcpy_s(dst, size, "10");
			break;
		case dsDownloadFailed:
			OSAL_strcpy_s(dst, size, "20");
			break;
		case dsDownloadProgressing:
			OSAL_strcpy_s(dst, size, "30");
			break;
		case dsDownloadComplete:
			OSAL_strcpy_s(dst, size, "40");
			break;
		case dsReadyToUpdate:
			OSAL_strcpy_s(dst, size, "50");
			break;
		case dsUpdateProgressing:
			OSAL_strcpy_s(dst, size, "60");
			break;
		case dsUpdateFailedHaveData:
			OSAL_strcpy_s(dst, size, "70");
			break;
		case dsUpdateFailedNoData:
			OSAL_strcpy_s(dst, size, "80");
			break;
		case dsUpdateSuccessfulHaveData:
			OSAL_strcpy_s(dst, size, "90");
			break;
		case dsUpdateSuccessfulNoData:
			OSAL_strcpy_s(dst, size, "100");
			break;		
		default:
			OSAL_strcpy_s(dst, size, "-1") ;
	}
}

wmx_MaxTxPower_t ConvertToMaxTxPower(const char* val)
{
	return (wmx_MaxTxPower_t)atoi(val);
}
void ConvertToPreamblesBitmap(wmx_pPreambles_t preambles, const char* val)
{
	// A 114 bit map specifying the supported preambles
	// "ffffffffffffffffffffffffffffff" -> [ff][ff][ff][ff][ff][ff][ff][ff][ff][ff][ff][ff][ff][ff][ff]
	// "0102030405060708090a0b0c0d0e0f" -> [01][02][03][04][05][06][07][08][09][0a][0b][0c][0d][0e][0f]
	char nextPreamble[3];
	int i,j;
	UINT32 dwNextBits;
	memset(nextPreamble,0,sizeof(nextPreamble));

	for(i=0,j=0;i<15;i++)
	{
		nextPreamble[0] = val[j];
		j++;
		nextPreamble[1] = val[j];
		j++;
		OSAL_sscanf_s(nextPreamble,"%x",&dwNextBits);
		preambles[i] = (UINT8)dwNextBits;
	}
}

void ConvertPreamblesBitmapToStr(wmx_pPreambles_t preambles, char* dst)
{
	// A 114 bit map specifying the supported preambles
	// [ff][ff][ff][ff][ff][ff][ff][ff][ff][ff][ff][ff][ff][ff][ff] -> "ffffffffffffffffffffffffffffff" 
	// [01][02][03][04][05][06][07][08][09][0a][0b][0c][0d][0e][0f] -> "0102030405060708090a0b0c0d0e0f"
	char nextPreamble[3];
	int i,j;
	memset(nextPreamble,0,sizeof(nextPreamble));

	
	for(i=0,j=0;i<15;i++)
	{
		OSAL_sprintf_s(&dst[j],3,"%02x",preambles[i]);
		j += 2;
	}
}

UINT32 ConvertToSLA(const char* val)
{
	return (UINT32)atoi(val);
}
wmx_LinkSpeed_t ConvertToLinkSpeed(const char* val)
{
	return (wmx_LinkSpeed_t)atof(val);
}


wmx_Status_t ConvertToPsPolicy(const char* val, pPreferredScanPolicy_t pPolicy)
{
	wmx_Status_t rc = WMX_ST_OK;

	if(!val || !pPolicy)
	{
		return WMX_ST_FAIL;
	}

	if (0 == strcmp(val, "FirstRecent"))
	{
		*pPolicy = FirstRecent;
	} 
	else
	{
		rc = WMX_ST_WRONG_ARGUMENT;
	}

	return rc;
}
void ConvertPsPolicyToStr(PreferredScanPolicy_t policy, char * dst, int size)
{
	switch(policy)
	{
		case FirstRecent: 
			OSAL_strcpy_s(dst, size, "FirstRecent");
			break;

		default:
			OSAL_strcpy_s(dst, size, "-1");
	}
}
//wmx_Status_t ConvertToCertType(const char* val, pCertType_t pCertType)
//{
//	wmx_Status_t rc = WMX_ST_OK;
//
//	if(!val || !pCertType)
//	{
//		return WMX_ST_FAIL;
//	}
//
//	if (0 == strcmp(val, "Device"))
//	{
//		*pCertType = Device;
//	} 
//	//else if(0 == strcmp(val, "CA")) //NOT SUPPORTED NOW
//	//{
//	//	*pCertType = CA;
//	//}
//	else if(0 == strcmp(val, "-1"))
//	{
//		*pCertType = (CertType_t)L4DB_INVALID_INDEX;
//	}
//	else
//	{
//		rc = WMX_ST_WRONG_ARGUMENT;
//	}
//
//	return rc;
//}
//void ConvertCertTypeToStr(CertType_t certType, char * dst, int size)
//{
//	switch(certType)
//	{
//	case Device: 
//		OSAL_strcpy_s(dst, size, "Device");
//		break;
//
//	//case CA: //NOT SUPPORTED NOW
//	//	OSAL_strcpy_s(dst, size, "CA");
//	//	break;
//
//	default:
//		OSAL_strcpy_s(dst, size, "-1");
//	}
//}
void l4db_ConvertToEapTypeStr(wmx_EapType_t eapType, char * eapTypeStr)
{
	switch(eapType)
	{
	case WMX_EAP_TLS:
		OSAL_strcpy_s(eapTypeStr, MAX_EAP_METHOD_SIZE, "EAP_TLS");
		break;

	case WMX_EAP_TTLS:
		OSAL_strcpy_s(eapTypeStr, MAX_EAP_METHOD_SIZE, "EAP_TTLS");
		break;
	case WMX_EAP_AKA:
		OSAL_strcpy_s(eapTypeStr, MAX_EAP_METHOD_SIZE, "EAP_AKA");
		break;
	case WMX_PLAIN_MSCHAPv2:
		OSAL_strcpy_s(eapTypeStr, MAX_EAP_METHOD_SIZE, "PLAIN_MSCHAPv2");
		break;
	case WMX_EAP_MSCHAPv2: // Sivanne - remove
		OSAL_strcpy_s(eapTypeStr, MAX_EAP_METHOD_SIZE, "EAP_MSCHAPv2");
		break;
	default:
		eapTypeStr[0] = '\0';
	}
}

wmx_EapType_t l4db_ConvertToEapTypeEnum(char * eapTypeStr)
{
	if(0 == strcmp(eapTypeStr, "EAP_TLS"))
	{
		return WMX_EAP_TLS;
	}
	if(0 == strcmp(eapTypeStr, "EAP_TTLS"))
	{
		return WMX_EAP_TTLS;
	}
	if(0 == strcmp(eapTypeStr, "EAP_AKA"))
	{
		return WMX_EAP_AKA;
	}
	if(0 == strcmp(eapTypeStr, "PLAIN_MSCHAPv2"))
	{
		return WMX_PLAIN_MSCHAPv2;
	}
	if(0 == strcmp(eapTypeStr, "EAP_MSCHAPv2")) // Sivanne - remove
	{
		return WMX_EAP_MSCHAPv2;
	}

	return L4DB_INVALID_INDEX;
}
wmx_Status_t ConvertToAnyType(char * anyStr, pAny_t pAny)
{
	wmx_Status_t rc = WMX_ST_OK;

	if(FALSE == anyStr || FALSE == pAny)
		return WMX_ST_FAIL;

	if (0 == strcmp(anyStr, "Reserved"))
	{
		*pAny = Reserved;
	} 
	else if(0 == strcmp(anyStr, "OnlyList"))
	{
		*pAny = OnlyList;
	}
	else if(0 == strcmp(anyStr, "ListFirst"))
	{
		*pAny = ListFirst;
	}
	else if(0 == strcmp(anyStr, "Any"))
	{
		*pAny = Any;
	}
	else
	{
		rc = WMX_ST_WRONG_ARGUMENT;
	}

	return rc;
}

void ConvertToAnyStr(Any_t any, char * anyStr, int size)
{
	switch(any)
	{
	case Reserved: 
		OSAL_strcpy_s(anyStr, size, "Reserved") ;
		break;

	case OnlyList: 
		OSAL_strcpy_s(anyStr, size, "OnlyList") ;
		break;

	case ListFirst: 
		OSAL_strcpy_s(anyStr, size, "ListFirst") ;
		break;

	case Any: 
		OSAL_strcpy_s(anyStr, size, "Any") ;
		break;

	default:
		OSAL_strcpy_s(anyStr, size, "-1") ;
	}
}

wmx_Status_t ConvertToSelectPolicyType(char * selectPolicyStr, pSelectPolicy_t pSelectPolicy)
{
	wmx_Status_t rc = WMX_ST_OK;

	if(FALSE == selectPolicyStr || FALSE == pSelectPolicy)
		return WMX_ST_FAIL;
	
	if (0 == strcmp(selectPolicyStr, "Reserved"))
	{
		*pSelectPolicy = spReserved;
	} 
	else if(0 == strcmp(selectPolicyStr, "Strict"))
	{
		*pSelectPolicy = spStrict;
	}
	else if(0 == strcmp(selectPolicyStr, "PartiallyFlexible"))
	{
		*pSelectPolicy = spPartiallyFlexible;
	}
	else if(0 == strcmp(selectPolicyStr, "FullyFlexible"))
	{
		*pSelectPolicy = spFullyFlexible;
	}
	else
	{
		rc = WMX_ST_WRONG_ARGUMENT;
	}

	return rc;
}

void ConvertToSelectPolicyStr(SelectPolicy_t selectPolicy, char * selectPolicyStr, int size)
{
	switch(selectPolicy)
	{
	case spReserved: 
		OSAL_strcpy_s(selectPolicyStr, size, "Reserved") ;
		break;
	case spStrict: 
		OSAL_strcpy_s(selectPolicyStr, size, "Strict") ;
		break;
	case spPartiallyFlexible: 
		OSAL_strcpy_s(selectPolicyStr, size, "PartiallyFlexible") ;
		break;
	case spFullyFlexible: 
		OSAL_strcpy_s(selectPolicyStr, size, "FullyFlexible") ;
		break;
	default:
		OSAL_strcpy_s(selectPolicyStr, size, "-1") ;
	}
}

void wmxNds_ScanStatusToUserScanStatus(wmx_pUserScanStatus_t userScanStatus, wmx_ScanStatus_t scanStatus)
{
	switch( scanStatus )
	{
	case ScanSuccessful:
		*userScanStatus = UserScanSuccessful;
		break;

	case ScanExhausted:
		*userScanStatus = UserScanExhausted;
		break;

	case ScanStopped:
		*userScanStatus = UserScanStopped;
		break;

	case ScanFailed:
		*userScanStatus = UserScanStopped;
		break;

	default:
		*userScanStatus = UserScanFailed;
		break;
	}
}

void wmxNds_ConnectStatusToUserConnectStatus(wmx_pUserConnectStatus_t userConnectStatus, wmx_ConnectStatus_t connectStatus)
{
	switch( connectStatus )
	{
	case ConnectSuccessful:
		*userConnectStatus = UserConnectSuccessful;
		break;

	case ConnectCancelled:
		*userConnectStatus = UserConnectCancelled;
		break;

	case ConnectFailed:
		*userConnectStatus = UserConnectFailed;
		break;

	default:
		*userConnectStatus = UserConnectFailed;
		break;
	}
}

void wmxNds_BsIdMaskToStr(wmx_BsIdType_t bsIdType, char *str, int strLength)
{
	switch (bsIdType)
	{
		case FULL_BSID:
			OSAL_strncpy_s(str, strLength, "Full BSID", 20);
			break;
		case FULL_NAP:
			OSAL_strncpy_s(str, strLength, "Full BSID, only NAP part", 20);
			break;
		case COMPRESSED_BSID:
			OSAL_strncpy_s(str, strLength, "Compressed BSID", 20);
			break;
		case COMPRESSED_NAP:
			OSAL_strncpy_s(str, strLength, "Compressed BSID, only NAP part", 30);
			break;
	}
}

wmx_EapMathod_t wmx_EapTypeToDS_EapType(wmx_EapType_t eapType)
{
	switch (eapType)
	{
		case WMX_EAP_TLS:
			return SWC_EAP_TYPE_TLS;
			break;
		case WMX_EAP_TTLS:
			return SWC_EAP_TYPE_TTLS;
			break;
		case WMX_EAP_AKA:
			return SWC_EAP_TYPE_AKA;
			break;
		case WMX_PLAIN_MSCHAPv2:
			return SWC_PHASE2_METHOD_MSCHAPV2;
			break;
		case WMX_EAP_MSCHAPv2:
			return SWC_PHASE2_METHOD_EAP_MSCHAPV2;
			break;
		default:
			return SWC_EAP_TYPE_NONE;
			break;
	}
}

// shallow conversion (ignore channel ranges) of the L4DB version of the channel info into the wmx version
BOOL wmxNds_DBChannelInfoToWmxChannelInfo(wmx_pChannelInfo_t target, UINT32 *targetMaxCount, pChannelInfo_t source, UINT32 sourceCount)
{
	UINT32 i;

	if (*targetMaxCount < sourceCount)
	{
		return FALSE;
	}

	for (i = 0; i < sourceCount; ++i)
	{
		// this isn't a real ID becuase we don't save it on our DB.
		// We don't mind becuase we build the channels for connect command and not scan result
		target[i].channelID = (wmx_ChannelID_t)i;
		target[i].bw = source[i].bw;
		target[i].fft = source[i].fft;
		target[i].frequency = source[i].firstFreq;
		OSAL_memcpy_s(target[i].preambleBitmap, PREAMBLES_LENGTH, source[i].preambleBitmap, PREAMBLES_LENGTH);
	}

	*targetMaxCount = sourceCount;

	return TRUE;
}

// shallow conversion (ignore channel ranges) of the wmx version of the channel info into the L4DB version
BOOL wmxNds_WmxChannelInfoToDBChannelInfo(pChannelInfo_t target, UINT32 *targetMaxCount, wmx_pChannelInfo_t source, UINT32 sourceCount, BOOL isFoundInNbrAdv)
{
	UINT32 i;

	if (*targetMaxCount < sourceCount)
	{
		return FALSE;
	}

	for (i = 0; i < sourceCount; ++i)
	{
		OSAL_itoa_s((int)source[i].channelID, target[i].id, MAX_REF_ID_NAME_SIZE, 10);
		target[i].bw = source[i].bw;
		target[i].fft = source[i].fft;
		target[i].firstFreq = target[i].lastFreq = source[i].frequency;
		target[i].nextFreq = 0;
		target[i].duplexMode = 0;
		target[i].ttl = L4DB_MAX_TTL;
		target[i].lastFoundInNbrAdv = isFoundInNbrAdv;		
		OSAL_memcpy_s(target[i].preambleBitmap, PREAMBLES_LENGTH, source[i].preambleBitmap, PREAMBLES_LENGTH);
	}

	*targetMaxCount = sourceCount;

	return TRUE;
}

void DeviceStatusToStr(wmx_DeviceStatus_t deviceStatus, char * deviceStatusStr, size_t size)
{
	switch(deviceStatus)
	{
	case DeviceStatus_UnInitialized:
		OSAL_strcpy_s(deviceStatusStr, size, "UnInitialized");
		break;

	case DeviceStatus_RF_OFF_HW_SW:
		OSAL_strcpy_s(deviceStatusStr, size, "RF_OFF_HW_SW");
		break;
	case DeviceStatus_RF_OFF_HW:
		OSAL_strcpy_s(deviceStatusStr, size, "RF_OFF_HW");
		break;
	case DeviceStatus_RF_OFF_SW:
		OSAL_strcpy_s(deviceStatusStr, size, "RF_OFF_SW");
		break;
	case DeviceStatus_Ready:
		OSAL_strcpy_s(deviceStatusStr, size, "Ready");
		break;
	case DeviceStatus_Scanning:
		OSAL_strcpy_s(deviceStatusStr, size, "Scanning");
		break;
	case DeviceStatus_Connecting:
		OSAL_strcpy_s(deviceStatusStr, size, "Connecting");
		break;
	case DeviceStatus_Data_Connected:
		OSAL_strcpy_s(deviceStatusStr, size, "Connected");
		break;
	default:
		deviceStatusStr[0] = '\0';
	}
}

void ConnectionProgressToStr(wmx_ConnectionProgressInfo_t connProgresss, char * connProgressStr, size_t size)
{
	switch(connProgresss)
	{
	case DeviceConnectionProgress_Ranging:
		OSAL_strcpy_s(connProgressStr, size, "UnInitialized");
		break;

	case DeviceConnectionProgress_SBC:
		OSAL_strcpy_s(connProgressStr, size, "SBC");
		break;
	case DeviceConnectionProgress_EAP_authentication_Device:
		OSAL_strcpy_s(connProgressStr, size, "EAP_authentication_Device");
		break;
	case DeviceConnectionProgress_EAP_authentication_User:
		OSAL_strcpy_s(connProgressStr, size, "EAP_authentication_User");
		break;
	case DeviceConnectionProgress_3_way_handshake:
		OSAL_strcpy_s(connProgressStr, size, "3_way_handshake");
		break;
	case DeviceConnectionProgress_Registration:
		OSAL_strcpy_s(connProgressStr, size, "Registration");
		break;
	case DeviceConnectionProgress_De_registration:
		OSAL_strcpy_s(connProgressStr, size, "De_registration");
		break;
	case DeviceConnectionProgress_Registered:
		OSAL_strcpy_s(connProgressStr, size, "Registered");
		break;
	default:
		connProgressStr[0] = L'\0';
	}
}