/*
 * SeqMain.c
 *
 *  Created on: 2023. 1. 5.
 *      Author: poweryhs
 */

/*============================================================================
    Includes
============================================================================*/
#include "../M0_MAIN/AswMainApi.h"
#include "../M2_MON/MonApi.h"
#include "../M3_CTR/CtrApi.h"
#include "../M4_FDIAG/FdiagApi.h"
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
INTERNAL_STATE INTERNAL_MAIN_STATE  = STAT_CBABNORMAL_STATE;
Uint16 giInternalMainState          = 0U;
Uint16 INTERNAL_SUB_STATE           = 0U;
Uint16 giInternalSubState           = 0U;

/*============================================================================
    Private Variables/Constants
============================================================================*/

/*============================================================================
    Function Prototypes
============================================================================*/
void SeqMainChkMainState(void);

/*============================================================================
    Function Implementations
============================================================================*/
void SeqMainIsrCtr(void) {}
void SeqMainTask100us(void) {}
void SeqMainTask1ms(void)
{
    SeqMainChkMainState();
}
void SeqMainTask10ms(void) {}
void SeqMainTask100ms(void) {}


/*----------------------------------------------------------------------------
    Func : ICCU OBC MainState ÆÇÁ¤
    Period : 1ms
    Parameter : INTERNAL_MAIN_STATE
----------------------------------------------------------------------------*/
void SeqMainChkMainState()
{
    Uint16 iCbAbnormalSubState = FdiagApi_GetChkConCbAbnormal();
    Uint16 iInhibitSubState = FdiagApi_GetChkConInhibit();
    Uint16 iFatalSubState = FdiagApi_GetChkConFatal();
    Uint16 iFaultSubState = FdiagApi_GetChkConFault();
    Uint16 iResumeSubState = FdiagApi_GetChkConResume();
    Uint16 iNormalSubState = FdiagApi_GetChkConNormal();

    giInternalMainState = 0U;
    giInternalSubState = 0U;
    if (iCbAbnormalSubState != 0x0000U)
    {
        giInternalMainState = STAT_CBABNORMAL_STATE;
        giInternalSubState = iCbAbnormalSubState;
    }
    else if (iFatalSubState != 0x0000U)
    {
        giInternalMainState = STAT_FATAL_STATE;
        giInternalSubState = iFatalSubState;
    }
    else if(iFaultSubState != 0x0000U)
    {
        giInternalMainState = STAT_FAULT_STATE;
        giInternalSubState = iFaultSubState;
    }
    else if (iResumeSubState != 0x0000U)
    {
        giInternalMainState = STAT_RESUME_STATE;
        giInternalSubState = iResumeSubState;
    }
    else if (iInhibitSubState != 0x0000U)
    {
        giInternalMainState = STAT_INHIBIT_STATE;
        giInternalSubState = iInhibitSubState;
    }
    else
    {
        giInternalMainState = STAT_NORMAL_STATE;
        giInternalSubState = iNormalSubState;
    }

    INTERNAL_MAIN_STATE = (INTERNAL_STATE)giInternalMainState;
    INTERNAL_SUB_STATE = giInternalSubState;

    //DA1 = (float)INTERNAL_MAIN_STATE;
    //DA2 = (float)INTERNAL_SUB_STATE;

}

void SeqMain_SetInternalMainState(INTERNAL_STATE MainState)
{
    INTERNAL_MAIN_STATE = MainState;
}
void SeqMain_SetInternalSubState(Uint16 SubState)
{
    INTERNAL_SUB_STATE = SubState;
}


