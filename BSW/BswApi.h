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

void BswApi_SetSpiA();
void BswApi_SetDACA(Uint8 ch, Uint16 data);

float BswApi_GetISRTS();
void BswApi_ChangeISRTS(float EvtNum, float Freq);

void BswApi_SetPwmDuty(Uint8 ch, Bool Deadband, float Duty);
void BswApi_SetPwmADuty(Uint8 ch, float Duty);
void BswApi_SetPwmBDuty(Uint8 ch, float Duty);

void BswApi_SetPwmFreq(Uint8 ch, Uint8 CarrMode, float Freq);
void BswApi_SetPwmFreqUpCnt(Uint8 ch, float Freq);
void BswApi_SetPwmFreqUpDownCnt(Uint8 ch, float Freq);

void BswApi_EnablePfcPwm();
void BswApi_EnablePfcHSPwm();
void BswApi_DisablePfcPwm();
void BswApi_DisablePfcHSPwm();

void BswApi_SetPwmPhase(Uint8 ch, float NomalizedPhase);

Uint8 BswApi_GetPwmEvtNum(Uint8 ch);

void BswApi_EnablePfcRly();
void BswApi_DisablePfcRly();
void BswApi_Gpio43En();
void BswApi_Gpio43Dis();
void BswApi_Gpio44En();
void BswApi_Gpio44Dis();

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
