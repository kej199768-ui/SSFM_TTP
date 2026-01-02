/*
 * SeqMain.h
 *
 *  Created on: 2023. 1. 5.
 *      Author: poweryhs
 */

#ifndef ASW_M1_SEQ_SEQMAIN_H_
#define ASW_M1_SEQ_SEQMAIN_H_


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

extern INTERNAL_STATE INTERNAL_MAIN_STATE;
extern Uint16 INTERNAL_SUB_STATE;


/*============================================================================
    Function Prototypes
============================================================================*/
extern void SeqMainIsrCtr(void);
extern void SeqMainTask100us(void);
extern void SeqMainTask1ms(void);
extern void SeqMainTask10ms(void);
extern void SeqMainTask100ms(void);

void SeqMain_SetInternalMainState(INTERNAL_STATE MainState);
void SeqMain_SetInternalSubState(Uint16 SubState);



#endif /* ASW_M1_SEQ_SEQMAIN_H_ */
