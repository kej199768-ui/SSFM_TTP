#ifndef _FDIAGCHKCTR_H
#define _FDIAGCHKCTR_H
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
//CtrState
extern CURRCTRSTATE			giPfcLCurrCtrState;
extern CURRCTRSTATE			gIDcDcOutCurrCtrState;


extern VOLTCTRSTATE			giGridVoltCtrState;
extern VOLTCTRSTATE			giPfcDcLinkVoltCtrState;
extern VOLTCTRSTATE			giV2XDcLinkVoltCtrState;
extern VOLTCTRSTATE			giOutVoltCtrState;
extern VOLTCTRSTATE			giV2LVoltCtrState;

/*============================================================================
	Function Prototypes
============================================================================*/
void FdiagChkCtrIsrCtr(void);
void FdiagChkCtrTask100us(void);
void FdiagChkCtrTask1ms(void);
void FdiagChkCtrTask10ms(void);
void FdiagChkCtrTask100ms(void);

VOLTCTRSTATE FdiagChkCtr_GetGridPllCtrState(void);
VOLTCTRSTATE FdiagChkCtr_GetDcLinkVoltCtrState(void);
VOLTCTRSTATE FdiagChkCtr_GetOutVoltCtrState(void);

CURRCTRSTATE FdiagChkCtr_GetPfcCurrCtrState(void);
CURRCTRSTATE FdiagChkCtr_GetDcDcCurrCtrState(void);

#endif
