#pragma once
#include "stdafx.h"

/// Encryption type
typedef enum 
{
	eUnknownAlg, 
	eNoWep, 
	eWep40bit, 
	eWep104bit,
	eCkip40bit, 
	eCkip104bit,
	eTkip,
	eCcmp
} INTEL_ALGORITHM;

EXTERN_C HRESULT GetOidData (long oid, char *pBuffer, int *pLength, bool bEnable);
EXTERN_C HRESULT GetOidDataAuthModeCcx (char *pBuffer, int *pLength);
EXTERN_C HRESULT GetOidEncEAPPacketStatus (INTEL_ALGORITHM alg, char *pBuffer, int *pLength);
EXTERN_C HRESULT RegisterProfileService (char *buffer, int *pLength, bool bEnable);