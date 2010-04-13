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
* @file         MOC_Utils.h
* @brief        This file contains functions to process MOC task id
* @author       Michael Waksman (michael.waksman@intel.com)
* @version      1.0
* @date         15/7/2005
* 
* @version		1.01 18/12/2005 YarivB added 'TaskDeleted' field.
*
* @todo			change all taskId accessors to bitman.
*
* @note			important: any changes in this file should be synchronized with Tools group!
*/
#ifndef _MOC_UTILS_H
#define _MOC_UTILS_H

/************************************* Includes *******************************************/

#include "TypesProxy.h"
#include "MOC_Types.h"


/************************************* Defines ********************************************/

/** 
    Number of priorities supported
 */
#define NUMBER_OF_ASYNCHRONIC_PRIORITIES    4U
#define SYNC_PRIORITY_INDEX		NUMBER_OF_ASYNCHRONIC_PRIORITIES

/** 
    The following are the necessary shifts which are needed to get to the offset where the 
    relevant field should be placed
 */
#define MOC_TASK_INDEX_SHIFT            0
#define MOC_TASK_ZONE_SHIFT             5
#define MOC_TASK_TARGET_SHIFT           12
#define MOC_TASK_PRIORITY_SHIFT         16
#define MOC_TASK_TYPE_SHIFT             19
#define MOC_TASK_CHANNEL_SHIFT          21
#define MOC_TASK_RESERVE_SHIFT          22
#define MOC_TASK_PIGGYBACK_SHIFT        24
#define MOC_TASK_STREAMSTATUS_SHIFT		30


/** 
    The following are the necessary masks which are need to get the 
    relevant field.
*/
#define MOC_TASK_INDEX_MASK             (0x1fU << MOC_TASK_INDEX_SHIFT)
#define MOC_TASK_ZONE_MASK              (0x7fU << MOC_TASK_ZONE_SHIFT)
#define MOC_TASK_TARGET_MASK            (0xfU << MOC_TASK_TARGET_SHIFT)
#define MOC_TASK_PRIORITY_MASK          (0x7U << MOC_TASK_PRIORITY_SHIFT)
#define MOC_TASK_TYPE_MASK              (0x3U  << MOC_TASK_TYPE_SHIFT)
#define MOC_TASK_CHANNEL_MASK           (0x1U  << MOC_TASK_CHANNEL_SHIFT)
#define MOC_TASK_RESERVE_MASK           (0x3U  << MOC_TASK_RESERVE_SHIFT)
#define MOC_TASK_PIGGYBACK_MASK         (0xffU << MOC_TASK_PIGGYBACK_SHIFT)
#define MOC_TASK_STREAMSTATUS_MASK		(0x3U  << MOC_TASK_STREAMSTATUS_SHIFT)

#define MOC_TASK_FLUSH_MASK				(MOC_TASK_INDEX_MASK | MOC_TASK_ZONE_MASK)

/**
	The following are definitions for stream messages status, will be put in the tui at the 2 MSB (30,31)
**/
#define STREAM_ACK 0 // 00
#define STREAM_MSG 1 // 01
#define STREAM_END 2 // 10

/************************************* Functions **************************************/

/** 
    Getting task's index
    This is MACRO due to some driver usage which requires that
 */
#define MOC_GetTaskIndex(taskId) (((taskId) & MOC_TASK_INDEX_MASK) >> MOC_TASK_INDEX_SHIFT)

/** 
    Getting task's zone
*/
static INLINE UINT32 MOC_GetTaskZone(UINT32 taskId)
{
    return (taskId & MOC_TASK_ZONE_MASK) >> MOC_TASK_ZONE_SHIFT;
}

/** 
    Test for a task to be a flush task
*/
#define MOC_IsFlushTask(taskID)				((taskID & MOC_TASK_FLUSH_MASK) == MOC_TASK_FLUSH_MASK)

/** 
    Building Flush taskID based on destination task ID
	A new taskID has the same priority, target, etc. (except not zone and index)
*/
#define MOC_BuildFlushTaskID(origTaskID)	(origTaskID | MOC_TASK_FLUSH_MASK)

/** 
    Getting task's target
*/
static INLINE UINT32 MOC_GetTaskTarget(UINT32 taskId)
{
    return (taskId & MOC_TASK_TARGET_MASK) >> MOC_TASK_TARGET_SHIFT;
}

/** 
    Getting task's type
*/
static INLINE UINT32 MOC_GetTaskType(UINT32 taskId)
{
    return (taskId & MOC_TASK_TYPE_MASK) >> MOC_TASK_TYPE_SHIFT;
}

/** 
    Getting task's priority
*/
static INLINE UINT32 MOC_GetTaskPriority(UINT32 taskId)
{
    return (taskId & MOC_TASK_PRIORITY_MASK) >> MOC_TASK_PRIORITY_SHIFT;
}

/** 
    Getting task's piggyback (user area)
*/
static INLINE UINT32 MOC_GetTaskPiggyback(UINT32 taskId)
{
    return (taskId & MOC_TASK_PIGGYBACK_MASK) >> MOC_TASK_PIGGYBACK_SHIFT;
}

/** 
    Getting task's stream status 
*/
static INLINE UINT32 MOC_GetTaskStreamStatus(UINT32 taskId)
{
	return (taskId & MOC_TASK_STREAMSTATUS_MASK) >> MOC_TASK_STREAMSTATUS_SHIFT;
}

/** 
Setting task's index 
*/
static INLINE UINT32 MOC_SetTaskIndex(UINT32 taskId, UINT8 type)
{
	return ((type << MOC_TASK_INDEX_SHIFT) | (taskId & ~MOC_TASK_INDEX_MASK));
}

/** 
Setting task's type 
*/
static INLINE UINT32 MOC_SetTaskType(UINT32 taskId, UINT8 type)
{
	return ((type << MOC_TASK_TYPE_SHIFT) | (taskId & ~MOC_TASK_TYPE_MASK));
}
/** 
Setting task's target 
*/


#define MOC_SetTaskTarget(taskId,target)	(((target) << MOC_TASK_TARGET_SHIFT) | ((taskId) & ~MOC_TASK_TARGET_MASK))


/** 
    Setting task's priority
*/
#define MOC_SetTaskPriority(taskId, priority)	(((priority) << MOC_TASK_PRIORITY_SHIFT) | ((taskId) & ~MOC_TASK_PRIORITY_MASK))

/** 
    Setting task's piggyback (user area)
*/
static INLINE UINT32 MOC_SetTaskPiggyback(UINT32 taskId, UINT8 piggyback)
{
    return ((piggyback << MOC_TASK_PIGGYBACK_SHIFT) | (taskId & ~MOC_TASK_PIGGYBACK_MASK));
}

/** 
    Getting task's channel flag (may be either CTRL or DATA)
*/
static INLINE UINT32 MOC_GetTaskChannel(UINT32 taskId)
{
    return (taskId & MOC_TASK_CHANNEL_MASK) >> MOC_TASK_CHANNEL_SHIFT;
}

/** 
	Setting task's channel flag (may be either CTRL or DATA)
*/
static INLINE UINT32 MOC_SetTaskChannel(UINT32 taskId, UINT8 channel)
{
	return ((channel << MOC_TASK_CHANNEL_SHIFT) | (taskId & ~MOC_TASK_CHANNEL_MASK));
}

/** 
    Setting task's stream status
*/
static INLINE UINT32 MOC_SetTaskStreamStatus(UINT32 taskId, UINT8 streamStatus)
{
    return ((streamStatus << MOC_TASK_STREAMSTATUS_SHIFT) | (taskId & ~MOC_TASK_STREAMSTATUS_MASK));
}


/** 
    Building a task id from its fields.
    This is MACRO due to some driver usage which requires that   
 */
#define MOC_BuildTaskId(index, zone, target, priority, type, channel)						\
     ( ((index) << MOC_TASK_INDEX_SHIFT) | ((zone) <<  MOC_TASK_ZONE_SHIFT) |               \
	   ((target) << MOC_TASK_TARGET_SHIFT) | ((priority) <<  MOC_TASK_PRIORITY_SHIFT) |     \
	   ((type) << MOC_TASK_TYPE_SHIFT) | ((channel) << MOC_TASK_CHANNEL_SHIFT))



#endif
