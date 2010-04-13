// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the UDAPIDLL_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// UDAPIDLL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
//#ifdef UDAPIDLL_EXPORTS
//#define UDAPIDLL_API __declspec(dllexport)
//#else
//#define UDAPIDLL_API __declspec(dllimport)
//#endif

#include "UDapiCommonDefines.h"

#ifdef __cplusplus
extern "C"
#endif
{
// UDapi_Callback is invoked with any data received from the Upper Driver
extern int (*UDapi_Callback)(UINT32 handle, unsigned char * pBuf, unsigned int pBufSize);

// UDapi_AlertsCallback is invoked when an error occurs with the socket to Upper Driver
extern int (*UDapi_AlertsCallback)(UINT32 handle, UDAPI_ERROR_CODE errorCode);

//Init returns Handle (0xFFFFFFFF when fail)
UINT32 UDapi_Init(int (*UDapi_Callback)(UINT32 handle, unsigned char * pBuf, unsigned int pBufSize),
								  int (*UDapi_AlertsCallback)(UINT32 handle, UDAPI_ERROR_CODE errorCode));

UDAPI_ERROR_CODE UDapi_Finalize(UINT32 handle); // optional - opposite of UDapi_Init()


UDAPI_ERROR_CODE UDapi_Connect(UINT32 handle, const char *ipAddr, u_short portNum);


UDAPI_ERROR_CODE UDapi_Send(UINT32 handle, unsigned char * pBuf, unsigned int pBufSize);


UDAPI_ERROR_CODE UDapi_Disconnect(UINT32 handle);
}