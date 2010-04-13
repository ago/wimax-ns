
/****************************************************************************
*
* Auto generated file
* Version XXX
* Compliant with XXX.bm version XXX
* 11/19/2009 12:56:04 AM
*
*****************************************************************************/

#ifndef _L4BUFMAN_L3L4DMSTRUCTS_H
#define _L4BUFMAN_L3L4DMSTRUCTS_H


#include "L4BufMan_L3L4DmStructs_Desc.h"
#include "L4BufMan_L4Common.h"





//
// MonitorBuffer
//
L4BUFMAN_Status_t L4BM_Get_MonitorBuffer(MonitorBuffer_type* pMsg, UINT8* buf);
L4BUFMAN_Status_t L4BM_Set_MonitorBuffer(UINT8* pBuf, MonitorBuffer_type msg);
UINT L4BM_GetBufferSize_MonitorBuffer(MonitorBuffer_type msg);
UINT L4BM_GetMaxBufferSize_MonitorBuffer( void );
void L4BM_Init_MonitorBuffer(MonitorBuffer_type* pMsg);
extern L4bufman_Funcs MonitorBuffer_Funcs;



#endif //_L4BUFMAN_L3L4DMSTRUCTS_H
