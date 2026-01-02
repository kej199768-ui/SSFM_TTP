#ifndef _FDIAGAPI_H
#define _FDIAGAPI_H

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
//ChkM Api Function
void FdiagApi_ChkMIsrCtr(void);
void FdiagApi_ChkMTask100us(void);
void FdiagApi_ChkMTask1ms(void);
void FdiagApi_ChkMTask10ms(void);
void FdiagApi_ChkMTask100ms(void);

Uint16 FdiagApi_GetChkConCbAbnormal(void);
Uint16 FdiagApi_GetChkConInhibit(void);
Uint16 FdiagApi_GetChkConFatal(void);
Uint16 FdiagApi_GetChkConFault(void);
Uint16 FdiagApi_GetChkConResume(void);
Uint16 FdiagApi_GetChkConNormal(void);
Uint16 FdiagApi_GetChkConHwIsrPin(void);
Uint16 FdiagApi_GetHwFltFlag(void);

//ChkFS Api Function
ICCUMODE_STATE FdiagApi_GetIccuModeState(void);

//ChkS Api Function
TEMP_STATE FdiagApi_GetTempState(Uint16 SnsrNum);
GATE_STATE FdiagApi_GetGateState(Uint16 SnsrNum);
DERATING_STATE FdiagApi_GetDeratingState(void);
RLY_STATE FdiagApi_GetRlyState(void);
AUXBATVOLT_STATE FdiagApi_GetAuxBatVoltState(void);

//ChkIO Api Fuction
Uint16 FdiagApi_GetVoltHwOv_Interrupt(Uint16 SnsrNum);
Uint16 FdiagApi_GetCurrHwOc_Interrupt(Uint16 SnsrNum);
void FdiagApi_ChkVoltHwOvFlt(Uint16 SnsrNum);
void FdiagApi_ChkGateHwFlt(Uint16 SnsrNum);
ICCUVOLTSNSR_STATE FdiagApi_GetVoltSnsrState(Uint16 SnsrNum);


//ChkCtr Api Fuction
CURRCTRSTATE FdiagApi_GetPfcCurrCtrState(void);
CURRCTRSTATE FdiagApi_GetDcDcCurrCtrState(void);

void FdiagApi_ChagePfcCurrCtrState(CURRCTRSTATE CtrState);
void FdiagApi_ChageDcDcCurrCtrState(CURRCTRSTATE CtrState);



VOLTCTRSTATE FdiagApi_GetGridPllCtrState(void);
VOLTCTRSTATE FdiagApi_GetPfcDcLinkVoltCtrState(void);
VOLTCTRSTATE FdiagApi_GetDcDcLinkVoltCtrState(void);
VOLTCTRSTATE FdiagApi_GetOutVoltCtrState(void);
VOLTCTRSTATE FdiagApi_GetV2LVoltCtrState(void);

void FdiagApi_ChangeGridPllState(VOLTCTRSTATE state);
void FdiagApi_ChangePfcDcLinkVoltCtrState(VOLTCTRSTATE CtrState);
void FdiagApi_ChangeDcDcLinkVoltCtrState(VOLTCTRSTATE CtrState);
void FdiagApi_ChangeOutVoltCtrState(VOLTCTRSTATE CtrState);
void FdiagApi_ChangeV2LVoltCtrState(VOLTCTRSTATE CtrState);

#endif

