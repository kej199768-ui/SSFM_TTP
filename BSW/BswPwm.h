/*
 * BswPwm.h
 *
 *  Created on: 2022. 11. 29.
 *      Author: poweryhs
 */

#ifndef BSW_BSWPWM_H_
#define BSW_BSWPWM_H_
/*============================================================================
    Includes
============================================================================*/
#include "BswCommon.h"

/*============================================================================
    Macros
============================================================================*/
#define CNTUP               1
#define CNTDOWN             0

#define EVT1ST              0
#define EVT2ND              1
#define EVT3RD              2

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

void InitEPwm1Config(void);
void InitEPwm2Config(void);
void InitEPwm3Config(void);
void InitEPwm4Config(void);
void InitEPwm5Config(void);
void InitEPwm6Config(void);

void BswPwm_SetDeadtime (Uint8 ch, float dt_ns );
void BswPwm_SetPwmADuty (Uint8 ch, float Duty );
void BswPwm_SetPwmBDuty (Uint8 ch, float Duty );
void BswPwm_SetPwmDuty (Uint8 ch, Bool Deadband, float Duty );
void BswPwm_SetFreq (Uint8 ch, Uint8 CarrMode, float Freq );
void BswPwm_SetFreqUpCnt (Uint8 ch, float Freq );
void BswPwm_SetFreqUpDownCnt (Uint8 ch,float Freq );
void BswPwm_ForceLowPwmA (Uint8 ch);
void BswPwm_ForceLowPwmB (Uint8 ch);
void BswPwm_ForceLowPwm(Uint8 ch);
void BswPwm_EnablePwm(Uint8 ch);


//void BswPwm_SetPwmPhase(Uint8 ch, float NomalizedPhase);
//void BswPwm_SetSrPwmDuty(float Duty);
void BswPwm_DisablePfcPwm();
void BswPwm_DisablePfcHSPwm();
void BswPwm_EnablePfcPwm();
void BswPwm_EnablePfcHSPwm();
void BswPwm_PfcHSPwmPosDitheringMode();
void BswPwm_PfcHSPwmNegDitheringMode();
void BswPwm_PfcHSPwmNormalMode();

Uint8 BswPwm_GetPwmTzFlgState(Uint8 ch);

Uint8 BswPwm_GetPwmEvtNum (Uint8 ch);

#endif /* INITPWM_H_ */
