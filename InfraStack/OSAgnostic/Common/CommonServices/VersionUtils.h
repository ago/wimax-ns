
#ifndef _VERSION_UTILS_H
#define _VERSION_UTILS_H

#include "CommonServices.h"
#include "wimax_osal_types.h"

#define VER_STR_LEN 42

//
// MessageId: MSG_VERSION_ERROR
//
// MessageText:
//
//  AppSrv event:%n
//  Version validation failed for module %1.%n
//  Severity: %2%n
//  Module version: %3%n
//  Expected version: %4%n
//
#define MSG_VERSION_ERROR                0x80000003L


typedef enum _VERSION_RESULT
{	
	VER_SUCCESS = 0, // Success
	VER_SUCCESS_INVALID_MINOR,
	VER_FAIL_INVALID_MAJOR,	
	VER_FAIL_MODULE_ID_NOT_FOUND,
	VER_FAIL_UNKNOWN_ERROR
} VERSION_RESULT;


#define SET_VERSION(version, verMajor, verMinor, verBuild, verRevision, verBranch) \
{(version).major = verMajor; \
	(version).minor = verMinor; \
	(version).build = verBuild; \
	(version).revision = verRevision; \
	(version).branch = verBranch; }


/// <summary>
/// Type definition for a struct containing the version numbers of a module / interface. 
/// </summary>
#pragma pack( push, 1 )
typedef struct _wmx_Version_t
{
	UINT32	major;
	UINT32	minor;
	UINT32	build;
	UINT32	revision;
	UINT32	branch;
} wmx_Version_t, *wmx_pVersion_t;

typedef char* wmx_ModuleName_t;
typedef char* wmx_pVersionStr_t;
typedef size_t wmx_VersionStrLen_t;

#pragma pack( push, 1 )
typedef struct _wmx_VersionEntry_t
{
	wmx_ModuleName_t moduleName;
	wmx_Version_t version;
} wmx_VersionEntry_t, *wmx_pVersionEntry_t;


BOOL VersionUtils_Init();
void VersionUtils_Fini();

EXTERN_C EXPORT BOOL IsVersionValidationEnabled();
EXPORT void GetVersionString(char *str, wmx_Version_t version);
EXPORT void GetFullVersionString(char *str, wmx_Version_t version);
EXTERN_C EXPORT VERSION_RESULT ValidateVersion(wmx_ModuleName_t moduleName, wmx_Version_t actualVersion, wmx_Version_t expectedVersion);


#endif // _VERSION_UTILS_H