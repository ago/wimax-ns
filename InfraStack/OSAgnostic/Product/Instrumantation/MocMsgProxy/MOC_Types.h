/*************************************************************************
**                                                                      **
**                  I N T E L ( ENVARA ) P R O P R I E T A R Y          **
**                                                                      **
**     COPYRIGHT (c)  2005 BY  INTEL  CORPORATION.  ALL RIGHTS          **
**     RESERVED.   NO  PART  OF THIS PROGRAM  OR  PUBLICATION  MAY      **
**     BE  REPRODUCED,   TRANSMITTED,   TRANSCRIBED,   STORED  IN  A    **
**     RETRIEVAL SYSTEM, OR TRANSLATED INTO ANY LANGUAGE OR COMPUTER    **
**     LANGUAGE IN ANY FORM OR BY ANY MEANS, ELECTRONIC, MECHANICAL,    **
**     MAGNETIC,  OPTICAL,  CHEMICAL, MANUAL, OR OTHERWISE,  WITHOUT    **
**     THE PRIOR WRITTEN PERMISSION OF INTEL  CORPORATION.              **
**                                                                      **
*************************************************************************/
/**
* @file         MOC_Types.h
* @brief        This file contains the types MOC exports
* @author       Michael Waksman (michael.waksman@intel.com)
* @version      1.0
* @date         15/7/2005
* 
*/
#ifndef _MOC_TYPES_H
#define _MOC_TYPES_H

#include "TypesProxy.h"
#include "Osal_TaskTypes.h"

/** 
    Those values are returned by the MOC methods 
*/
typedef enum 
{
    MOC_RET_SUCCESS = OSAL_RET_SUCCESS,
    MOC_RET_RESOURCE_UNAVAILABLE,
    MOC_RET_INVALID_TASK_ID,
    MOC_RET_TASK_TYPE_MISMATCH_TASK_UNIQUE_ID,
	MOC_RET_ILLEGAL_TASK_TYPE
} MOC_Status;


/** 
    This type is necessary for MOC task handler
*/
typedef Task_Param MOC_Param;


/**
    This is a MOC task handler
*/
typedef void  (*MOC_Handler)(MOC_Param, UINT32, MOC_Param, UINT32);  

/** 
    This structures holds MOC task information
*/
typedef  Osal_TaskParams MOC_TaskParams;

/** 
    This is the prototype of function used to release data of MOC tasks     
*/
typedef Osal_ReleaseFunc MOC_ReleaseFunc;

/* type forward declaration */
struct MOC_MessageHeader;

#endif

