#ifndef _FDIAGCHKS_H
#define _FDIAGCHKS_H

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
extern ECU_STATE			giEcuRunState;
extern MALFUNC_STATE		giMalfuncState;
extern PWM_STATE			giPwmoutState;
extern OPERATING_STATE		giOperModeState;
extern DERATING_STATE		giDeratingState;

//IG voltage snsr and IG voltage diag
extern IGVOLTSNSR_STATE		giIgVoltSnsrState;
extern IGVOLT_STATE			giIgVoltState;

//Auxbat voltage snsr and Auxbat voltage diag
extern AUXBATVOLTSNSR_STATE	giAuxBatVoltSnsrState;
extern AUXBATVOLT_STATE		giAuxBatVoltState;
extern Uint16				giAuxBatVoltOvHwIsrFlag;

//Temp snsr and Temp diag
extern TEMPSNSR_STATE		giTempSnsrState[TempSnsrNum];
extern TEMP_STATE			giTempState[TempSnsrNum];

//InvoltHighInhibit
extern Uint16 giInVoltHighInhibitState;

//GateDiag
extern GATE_STATE           giGateState[GateSnsrNum];

/*============================================================================
	Function Prototypes
============================================================================*/
void FdiagChkSIsrCtr(void);
void FdiagChkSTask100us(void);
void FdiagChkSTask1ms(void);
void FdiagChkSTask10ms(void);
void FdiagChkSTask100ms(void);

AUXBATVOLT_STATE FdiagChkS_GetAuxBatVoltState(void);
Uint16 FdiagChkS_GetSmpsVoltState(void);
Uint16 FdiagChkS_GetIgVoltState(void);
Uint16 FdiagChkS_GetTempSnsrState(Uint16 SnsrNum);
Uint16 FdiagChkS_GetTempState(Uint16 SnsrNum);
DERATING_STATE FdiagChkS_GetDeratingState(void);
Uint16 FdiagChkS_GetMalfuncState(void);
Uint16 FdiagChkS_GetPwmoutState(void);
Uint16 FdiagChkS_GetOperModeState(void);
Uint16 FdiagChkS_GetAuxBatVoltSnsrState(void);
Uint16 FdiagChkS_GetSmpsVoltSnsrState(void);
Uint16 FdiagChkS_GetIGVoltSnsrState(void);

void FdiagChkS_ChkGateHwFlt(Uint16 SnsrNum);
Uint16 FdiagChkS_GetGateState(Uint16 SnsrNum);
void FdiagChkS_SetPwmEnState(Uint16 SnsrNum, Uint8 state);

void FdiagChkS_ChangeRlyState(Uint16 state);
RLY_STATE FdiagChkS_GetRlyState(void);

void FdiagChkS_IGState(void);
void FdiagChkS_ChangeIGState(Uint16 state);

void FdiagChkS_SetPwmEnState(Uint16 SnsrNum, Uint8 state);

#endif
