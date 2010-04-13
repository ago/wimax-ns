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

/*
* file name     Osal_TaskTypes.h
* Date:         12/08/2005
* @version      1.0 
* @author       Michael Waksman (michael.waksman@intel.com)
* Description   This file contains OSAL's task's types
* 
* Modified by   Name (Name@intel.com)
* Description:
*
* Modified by   Name (Name@intel.com)
* Description:
*/
#ifndef OSAL_TASK_TYPES_H
#define OSAL_TASK_TYPES_H

#include "TypesProxy.h"


/** 
    Types of tasks
*/
#define VAL 0
#define REF 1
#define MSG 2


/** 
    Type of channel for tasks
*/
#define CTRL 0
#define DATA 1


/** 
    Task parameter big enough to hold pointer    
 */
typedef POINTER_AND_UINT Task_Param;


/** 
    Tasks data
 */
typedef struct
{
    UINT32    taskId;
    Task_Param param1;
    UINT32    param2;
    Task_Param param3;
    UINT32    param4;
} Osal_TaskParams; 


/** 
    Release function to release task's data
 */
typedef void (*Osal_ReleaseFunc)(void *);


/** 
    Return values of Osal task functions
 */
typedef enum 
{
    OSAL_RET_SUCCESS = 0,
    OSAL_RET_ILLEGAL_TARGET,
    OSAL_RET_ILLEGAL_TYPE_HANDLER,
    OSAL_RET_ILLEGAL_POST_TASK_HANDLER,
    OSAL_RET_ILLEGAL_TICK_HANDLER,
    OSAL_RET_POST_FAILED,
    OSAL_RET_ROUTE_FAILED,
	OSAL_RET_RESOURCE_UNAVAILABLE,
	OSAL_RET_DESTINATION_UNAVAILABE
} Osal_Status;

#endif
