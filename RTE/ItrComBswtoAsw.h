/*
 * ItrCom.h
 *
 *  Created on: 2023. 1. 4.
 *      Author: poweryhs
 */

#ifndef RTE_ITRCOMBSWTOASW_H_
#define RTE_ITRCOMBSWTOASW_H_

/*============================================================================
    Includes
============================================================================*/
#include "RteCommon.h"

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
extern Uint16 giInhibit;
/*============================================================================
    Private Variables/Constants
============================================================================*/

/*============================================================================
    Function Prototypes
============================================================================*/
float ItrCom_GetCurr(Uint8 SnsrNum);
float ItrCom_GetVolt(Uint8 SnsrNum);
float ItrCom_GetTempVolt(Uint8 SnsrNum);
float ItrCom_GetCurrRaw(Uint8 SnsrNum);
float ItrCom_GetVoltRaw(Uint8 SnsrNum);
float ItrCom_GetTempVoltRaw(Uint8 SnsrNum);
//float ItrCom_GetTestInhibit();
float ItrCom_GetVObcOutRefCalSimul();
float ItrCom_GetVLdcOutRefCalSimul();

void ItrCom_SetPwmPhase(Uint8 ch, float NomalizedPhase);
void ItrCom_SetPfcPwmduty(Uint8 ch, Bool Deadband, float Duty);
void ItrCom_SetPfcPwmADuty(Uint8 ch, float Duty);
void ItrCom_SetPfcPwmBDuty(Uint8 ch, float DUty);

void ItrCom_EnablePfcPWM();
void ItrCom_EnablePfcHSPWM();
void ItrCom_DisablePfcPWM();
void ItrCom_DisablePfcHSPWM();
void ItrCom_PfcHSPwmPosDitheringMode();
void ItrCom_PfcHSPwmNegDitheringMode();
void ItrCom_PfcHSPwmNormalMode();

//void ItrCom_SetPwmPhase(Uint8 ch, float NomalizedPhase);
//void ItrCom_SetSrPwmduty(float Duty);
//void ItrCom_EnableObcPWM();
//void ItrCom_DisableObcPWM();
//void ItrCom_EnableSrPWM();
//void ItrCom_DisableSrPWM();

Uint8 ItrCom_GetPwmEvtNum(Uint8 ch);

float ItrCom_GetTestInhibit();

void ItrCom_EnablePfcRly();
void ItrCom_DisablePfcRly();

#endif /* RTE_ITRCOM_H_ */
