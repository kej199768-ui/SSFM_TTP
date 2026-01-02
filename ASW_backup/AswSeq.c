/*
 * AswMain.c
 *
 *  Created on: 2023. 1. 4.
 *      Author: poweryhs
 */


/*============================================================================
    Includes
============================================================================*/
#include <ASW_backup/AswMain.h>
#include <ASW_backup/AswTask.h>

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
INTERNAL_STATE INTERNAL_MAIN_STATE = 0;
Uint16 giInternalMainState = 0;
Uint16 INTERNAL_SUB_STATE = 0;
Uint16 giInternalSubState = 0;
/*============================================================================
    Private Variables/Constants
============================================================================*/

/*============================================================================
    Function Prototypes
============================================================================*/

/*============================================================================
    Function Implementations
============================================================================*/

/*----------------------------------------------------------------------------
    Func : ICCU OBC MainState ÆÇÁ¤
    Period : 1ms
    Parameter : INTERNAL_MAIN_STATE
----------------------------------------------------------------------------*/
void SeqChkMainState()
{
    Uint16 iInhibitSubState = FdiagChkMConInhibit();
    Uint16 iFaultSubState = FdiagChkMConFault();
    Uint16 iNormalSubState = FdiagChkMConNormal();

    giInternalMainState = 0;
    giInternalSubState = 0;
    if (iFaultSubState != 0x0000)
    {
        giInternalMainState = STAT_FAULT_STATE;
        giInternalSubState = iFaultSubState;
    }
    else if (iInhibitSubState != 0x0000)
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

}

void Seq_SetInteralMainState(INTERNAL_STATE MainState)
{
    INTERNAL_MAIN_STATE = MainState;
}
void Seq_SetInteralSubState(Uint16 SubState)
{
    INTERNAL_SUB_STATE = SubState;
}

INTERNAL_STATE Seq_GetInteralMainState() { return INTERNAL_MAIN_STATE; }
Uint16 Seq_GetInteralSubState() { return INTERNAL_SUB_STATE; }





