#ifndef WPA2DEFS_H
#define WPA2DEFS_H

/* FIX: Consider getting rid of the WPA2 postfix (i.e., use the same names as
 * Microsoft by making these definitions conditional on whether
 * OID_802_11_PMKID is defined. */

#define OID_802_11_CAPABILITY 			0x0d010122
#define OID_802_11_PMKID 			0x0d010123

typedef enum NDIS_802_11_STATUS_TYPE_WPA2 {
	Ndis802_11StatusTypeWPA2_Authentication,
	Ndis802_11StatusTypeWPA2_PMKID_CandidateList = 2,
	Ndis802_11StatusTypeWPA2_MediaStreamMode,
	Ndis802_11StatusTypeWPA2_RadioState,
	Ndis802_11StatusTypeWPA2Max
} NDIS_802_11_STATUS_TYPE_WPA2;

typedef struct _NDIS_802_11_STATUS_INDICATION_WPA2
{
	NDIS_802_11_STATUS_TYPE_WPA2 StatusType;
} NDIS_802_11_STATUS_INDICATION_WPA2, *PNDIS_802_11_STATUS_INDICATION_WPA2;

typedef enum NDIS_802_11_AUTHENTICATION_MODE_WPA2 {
	Ndis802_11WPA2AuthModeOpen,
	Ndis802_11WPA2AuthModeShared,
	Ndis802_11WPA2AuthModeAutoSwitch,
	Ndis802_11WPA2AuthModeWPA,
	Ndis802_11WPA2AuthModeWPAPSK,
	Ndis802_11WPA2AuthModeWPANone,
	Ndis802_11WPA2AuthModeWPA2,
	Ndis802_11WPA2AuthModeWPA2PSK,
	Ndis802_11WPA2AuthModeMax
} NDIS_802_11_AUTHENTICATION_MODE_WPA2, *PNDIS_802_11_AUTHENTICATION_MODE_WPA2;

typedef UCHAR NDIS_802_11_PMKID_VALUE[16];

typedef struct BSSID_INFO {
	NDIS_802_11_MAC_ADDRESS BSSID;
	NDIS_802_11_PMKID_VALUE PMKID;
} BSSID_INFO;

typedef struct NDIS_802_11_PMKID {
	ULONG Length;
	ULONG BSSIDInfoCount;
	BSSID_INFO BSSIDInfo[1];
} NDIS_802_11_PMKID;

typedef struct PMKID_CANDIDATE {
	NDIS_802_11_MAC_ADDRESS BSSID;
	ULONG Flags;
} PMKID_CANDIDATE;

#define NDIS_802_11_PMKID_CANDIDATE_PREAUTH_ENABLED 0x01

typedef struct NDIS_802_11_PMKID_CANDIDATE_LIST {
	ULONG Version;
	ULONG NumCandidates;
	PMKID_CANDIDATE CandidateList[1];
} NDIS_802_11_PMKID_CANDIDATE_LIST;

typedef struct NDIS_802_11_AUTHENTICATION_ENCRYPTION {
	NDIS_802_11_AUTHENTICATION_MODE AuthModeSupported;
	NDIS_802_11_ENCRYPTION_STATUS EncryptStatusSupported;
} NDIS_802_11_AUTHENTICATION_ENCRYPTION;

typedef struct NDIS_802_11_CAPABILITY {
	ULONG Length;
	ULONG Version;
	ULONG NoOfPMKIDs;
	ULONG NoOfAuthEncryptPairSupported;
	NDIS_802_11_AUTHENTICATION_ENCRYPTION
	AuthenticationEncryptionSupported[1];
} NDIS_802_11_CAPABILITY;

#endif /* WPA2DEFS_H */
