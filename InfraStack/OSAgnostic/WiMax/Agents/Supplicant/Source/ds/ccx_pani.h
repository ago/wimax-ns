#ifndef CCX_PANI_H
#define CCX_PANI_H

#ifdef CONFIG_CCX
#ifdef CONFIG_CCX_NAC

typedef unsigned int PA_STATUS;

#define PA_SUCCESS         (PA_STATUS) 1
/* high bit set for errors */
/* add support for 64 bits */
/* i.e 32 bit == 0x80000000*/
#define PA_ERROR           ((~((PA_STATUS) 0)) ^ (~((PA_STATUS) 0) >> 1))

#define PA_NOTINSTALLED             (1 | PA_ERROR)
#define PA_NOTRUNNINGDISABLED       (2 | PA_ERROR)
#define PA_NOTRUNNINGMANUAL         (3 | PA_ERROR)
#define PA_NOTRUNNINGAUTO           (4 | PA_ERROR)
#define PA_INVALID_NETTRANS_ID      (5 | PA_ERROR)
#define PA_INVALID_PARAMETER        (6 | PA_ERROR)
#define PA_INVALID_SESSION_ID       (7 | PA_ERROR)
#define PA_SESSIONID_ALREADY_EXIST  (8 | PA_ERROR)
#define PA_INVALID_ASYNC_PATH       (9 | PA_ERROR)
#define PA_INVALID_ASYNC_NAME       (10 | PA_ERROR)
#define PA_MAX_NETTRANS_EXCEEDED    (11 | PA_ERROR)
#define PA_INVALID_NETTRANS_EVENT   (12 | PA_ERROR)
#define PA_INTERNAL_ERROR           (13 | PA_ERROR)


/* byte align the structure */
#ifdef _MSC_VER
#pragma pack(push, 1)
#endif /* _MSC_VER */

typedef struct tagASYNC_EVENT_INTERFACE
{
   char *pszDynamicLibraryPath;  /* utf8 */
   char *pszAsyncEventFuncName;
} STRUCT_PACKED ASYNC_EVENT, *PASYNC_EVENT;

typedef enum
{
	CONNINFO_IP = 1,
	CONNINFO_MAC = 2
} CONNECTION_INFO_TYPE;

typedef struct tagSESSION_EVENT_INFO
{
	unsigned int uSize;
	unsigned int uiSessionId; 
	CONNECTION_INFO_TYPE ConnInfoType;
	void  *pConnInfo;
} STRUCT_PACKED SESSION_EVENT_INFO, *PSESSION_EVENT_INFO;

typedef struct tagIP_SESSION_INFO
{
	unsigned int uiNadIPAddr;
	unsigned short uiPort;
} STRUCT_PACKED IP_SESSION_INFO, *PIP_SESSION_INFO;

#define MACADDR_LENGTH 6

typedef struct tagMAC_SESSION_INFO
{
	unsigned char MacAddrLocal[MACADDR_LENGTH];
	unsigned char MacAddrRemote[MACADDR_LENGTH];
} STRUCT_PACKED MAC_SESSION_INFO, *PMAC_SESSION_INFO;

#ifdef _MSC_VER
#pragma pack(pop)
#endif /* _MSC_VER */

#ifdef _WIN32
#ifdef PANI_EXPORTS
#define PANI_API __declspec(dllexport)
#else
#define PANI_API __declspec(dllimport)
#endif
#else
#define PANI_API
#endif

#ifdef __cplusplus
extern "C"
{
#endif

PANI_API PA_STATUS RegisterNetTrans(const ASYNC_EVENT *pAsyncStart,
				    const char * pDescriptiveString,
                                    unsigned int* pNetTransId,
                                    unsigned int* pNetTransMask);
typedef PA_STATUS (*RegisterNetTransFn)(const ASYNC_EVENT *pAsyncStart,
					const char *pDescriptiveString,
					unsigned int *pNetTransId,
					unsigned int *pNetTransMask);

PANI_API PA_STATUS UnregisterNetTrans(unsigned int uNetTransId);
typedef PA_STATUS (*UnregisterNetTransFn)(unsigned int uNetTransId);

PANI_API PA_STATUS NetTransEvent(unsigned int uNetTransId,
                                 unsigned int uEvent,
                                 void *pInData,
                                 unsigned int uInDataLength,
                                 void *pResult,
                                 unsigned int uResultSize);
typedef PA_STATUS (*NetTransEventFn)(unsigned int uNetTransId,
				     unsigned int uEvent,
				     void *pInData,
				     unsigned int uInDataLength,
				     void *pResult,
				     unsigned int uResultSize);

#ifdef __cplusplus
}
#endif

#ifdef _WIN32
#ifdef PANI_EXPORTS
#define PANI_API  __declspec(dllexport)
#else
#define PANI_API  __declspec(dllimport)
#endif
#else 
#define PANI_API
#endif

typedef unsigned int EAPTLV_STATUS ;

#define EAPTLV_SUCCESS         (EAPTLV_STATUS) 1
/* high bit set for errors */
/* add support for 64 bits */
#define EAPTLV_ERROR    ((~((EAPTLV_STATUS) 0)) ^ (~((EAPTLV_STATUS) 0) >> 1))

#define EAPTLV_INVALIDTLVTYPE           (1 | EAPTLV_ERROR)
#define EAPTLV_INVALIDVSTLV             (2 | EAPTLV_ERROR)
#define EAPTLV_INVALIDSESSIONID         (3 | EAPTLV_ERROR)
#define EAPTLV_BUFTOOSMALL              (4 | EAPTLV_ERROR)
#define EAPTLV_INVALIDPARAMETER         (5 | EAPTLV_ERROR)
#define EAPTLV_NO_MEMORY                (6 | EAPTLV_ERROR)
#define EAPTLV_INTERNAL_ERROR           (7 | EAPTLV_ERROR)


#ifdef _MSC_VER
#pragma pack(push, 1)
#endif /* _MSC_VER */

typedef void OUTPUTBUF;

typedef struct tagINPUTBUF
{
	unsigned int uSize;
	unsigned int uSessionId;
	unsigned int EAPTLVType;
	void *pNetTransBuf;
} STRUCT_PACKED INPUTBUF, *PINPUTBUF;

#ifdef _MSC_VER
#pragma pack(pop)
#endif /* _MSC_VER */


#ifdef __cplusplus
extern "C"
{
#endif
    
PANI_API EAPTLV_STATUS EapTlvHandlePacket(void *pWorkBuf, 
                                          const void *pInTlv,
                                          unsigned int uInTlvLen,
                                          void *pOutTlv,
                                          unsigned int *puOutBufSize);
typedef EAPTLV_STATUS (*EapTlvHandlePacketFn)(void *pWorkBuf, 
					      const void *pInTlv,
					      unsigned int uInTlvLen,
					      void *pOutTlv,
					      unsigned int *puOutBufSize);
PANI_API EAPTLV_STATUS EapTlvInitialize(void);
typedef EAPTLV_STATUS (*EapTlvInitializeFn)(void);
PANI_API EAPTLV_STATUS EapTlvBegin(void **ppWorkBuf,
				   const INPUTBUF *pInputBuf);
typedef EAPTLV_STATUS (*EapTlvBeginFn)(void **ppWorkBuf,
				       const INPUTBUF *pInputBuf);
PANI_API EAPTLV_STATUS EapTlvEnd(void *pWorkBuf, OUTPUTBUF *pOutputBuf);
typedef EAPTLV_STATUS (*EapTlvEndFn)(void *pWorkBuf, OUTPUTBUF *pOutputBuf);
PANI_API EAPTLV_STATUS EapTlvUninitialize(void);
typedef EAPTLV_STATUS (*EapTlvUninitializeFn)(void);

#ifdef __cplusplus
}
#endif

#endif /* CONFIG_CCX_NAC */
#endif /* CONFIG_CCX */

#endif /* CCX_PANI_H */
