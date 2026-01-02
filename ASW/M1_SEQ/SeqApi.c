/*
 * SeqApi.c
 *
 *  Created on: 2023. 1. 5.
 *      Author: poweryhs
 */

/*============================================================================
    Includes
============================================================================*/
#include "SeqApi.h"
#include "SeqMain.h"


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
    Private Variables/Constants
============================================================================*/

/*============================================================================
    Function Prototypes
============================================================================*/

/*============================================================================
    Function Implementations
============================================================================*/
void SeqApi_RunSeqMainIsrCtr(void)                      { SeqMainIsrCtr(); }
void SeqApi_RunSeqMainTask100us(void)                   { SeqMainTask100us(); }
void SeqApi_RunSeqMainTask1ms(void)                     { SeqMainTask1ms(); }
void SeqApi_RunSeqMainTask10ms(void)                    { SeqMainTask10ms(); }
void SeqApi_RunSeqMainTask100ms(void)                   { SeqMainTask100ms();}

INTERNAL_STATE SeqApi_GetInternalMainState(void)         { return INTERNAL_MAIN_STATE;}
Uint16 SeqApi_GetInternalSubState(void)                  { return INTERNAL_SUB_STATE; }
void SeqApi_SetInternalMainState(INTERNAL_STATE MainState)   { SeqMain_SetInternalMainState(MainState); }
void SeqApi_SetInternalSubState(Uint16 SubState)             { SeqMain_SetInternalSubState(SubState); }

