/*
 * SeqApi.h
 *
 *  Created on: 2023. 1. 5.
 *      Author: poweryhs
 */

#ifndef ASW_M1_SEQ_SEQAPI_H_
#define ASW_M1_SEQ_SEQAPI_H_

/*============================================================================
    Includes
============================================================================*/
#include "../AswCommon.h"

/*============================================================================
    Macros
============================================================================*/

/*============================================================================
    Enumerations
============================================================================*/

/*============================================================================
    Data Structures
============================================================================*/

/*============================================================================
    Global variables
============================================================================*/

/*============================================================================
    Function Prototypes
============================================================================*/
void SeqApi_RunSeqMainIsrCtr(void);
void SeqApi_RunSeqMainTask100us(void);
void SeqApi_RunSeqMainTask1ms(void);
void SeqApi_RunSeqMainTask10ms(void);
void SeqApi_RunSeqMainTask100ms(void);

INTERNAL_STATE SeqApi_GetInternalMainState(void);
Uint16 SeqApi_GetInternalSubState(void);
void SeqApi_SetInternalMainState(INTERNAL_STATE MainState);
void SeqApi_SetInternalSubState(Uint16 SubState);



#endif /* ASW_M1_SEQ_SEQAPI_H_ */
