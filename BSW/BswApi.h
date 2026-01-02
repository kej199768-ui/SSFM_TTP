/*
 * BswApi.h
 *
 *  Created on: 2023. 1. 4.
 *      Author: poweryhs
 */

#ifndef BSW_BSWAPI_H_
#define BSW_BSWAPI_H_

/*============================================================================
    Includes
============================================================================*/
#include "BswCommon.h"

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
float BswApi_GetCurr(Uint8 SnsrNum);
float BswApi_GetVolt(Uint8 SnsrNum);
float BswApi_GetCurrRaw(Uint8 SnsrNum);
float BswApi_GetVoltRaw(Uint8 SnsrNum);

void BswApi_SetPwmDuty(Uint8 ch, Bool Deadband, float Duty);
void BswApi_SetPwmADuty(Uint8 ch, float Duty);
void BswApi_SetPwmBDuty(Uint8 ch, float Duty);

void BswApi_EnablePfcPwm();
void BswApi_EnablePfcHSPwm();
void BswApi_DisablePfcPwm();
void BswApi_DisablePfcHSPwm();

void BswApi_SetPwmPhase(Uint8 ch, float NomalizedPhase);

Uint8 BswApi_GetPwmEvtNum(Uint8 ch);

void BswApi_EnablePfcRly();
void BswApi_DisablePfcRly();

void BswApi_PfcLSSw_PosEn();
void BswApi_PfcLSSw_NegEn();
void BswApi_PfcLSSw_DeadBand();
void BswApi_PfcHSPwmPosDitheringMode();
void BswApi_PfcHSPwmNegDitheringMode();
void BswApi_PfcHSPwmNormalMode();

//float BswApi_GetTempVolt(Uint8 SnsrNum);
//float BswApi_GetTempVoltRaw(Uint8 SnsrNum);
//
//void BswApi_SetPwmPhase(Uint8 ch, float NomalizedPhase);
//void BswApi_SetSrPwmDuty(float Duty);
//void BswApi_EnableObcPWM();
//void BswApi_DisableObcPWM();
//void BswApi_EnableSrPWM();
//void BswApi_DisableSrPWM();

#endif /* BSW_BSWAPI_H_ */
