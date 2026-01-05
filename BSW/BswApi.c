/*7
 * BswApi.c
 *
 *  Created on: 2023. 1. 4.
 *      Author: poweryhs
 */

/*============================================================================
    Includes
============================================================================*/
#include "BswAdc.h"
#include "BswIsr.h"
#include "BswTask.h"
#include "BswPwm.h"
#include "BswGpio.h"
#include "BswCal.h"

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
float BswApi_GetCurr(Uint8 SnsrNum)                         {return gfCurrCal[SnsrNum];}
float BswApi_GetVolt(Uint8 SnsrNum)                         {return gfVoltCal[SnsrNum];}
float BswApi_GetCurrRaw(Uint8 SnsrNum)                      {return gfCurrRaw[SnsrNum];}
float BswApi_GetVoltRaw(Uint8 SnsrNum)                      {return gfVoltRaw[SnsrNum];}

float BswApi_GetISRTS()                                     { return gfISRTScal; }
void BswApi_ChangeISRTS(float EvtNum, float Freq)           { BswCal_ChangeIsrTs(EvtNum, Freq); }

//void BswApi_SetPwmPhase(Uint8 ch, float NomalizedPhase)     {BswPwm_SetPwmPhase(ch, NomalizedPhase);}
void BswApi_SetPwmDuty(Uint8 ch, Bool Deadband, float Duty)   {BswPwm_SetPwmDuty(ch, Deadband, Duty); }
void BswApi_SetPwmADuty(Uint8 ch, float Duty)                 { BswPwm_SetPwmADuty(ch, Duty); }
void BswApi_SetPwmBDuty(Uint8 ch, float Duty)                 { BswPwm_SetPwmBDuty(ch, Duty); }

void BswApi_SetPwmFreq(Uint8 ch, Uint8 CarrMode, float Freq){ BswPwm_SetFreq(ch, CarrMode, Freq); }
void BswApi_SetPwmFreqUpCnt(Uint8 ch, float Freq)           { BswPwm_SetFreqUpCnt(ch, Freq); }
void BswApi_SetPwmFreqUpDownCnt(Uint8 ch, float Freq)       { BswPwm_SetFreqUpDownCnt(ch, Freq); }

void BswApi_EnablePfcPwm()                                  { BswPwm_EnablePfcPwm();}
void BswApi_EnablePfcHSPwm()                                { BswPwm_EnablePfcHSPwm(); }
void BswApi_DisablePfcPwm()                                 { BswPwm_DisablePfcPwm();}
void BswApi_DisablePfcHSPwm()                               { BswPwm_DisablePfcHSPwm(); }

void BswApi_EnablePfcRly()                                  { BswGpio_EnableRly();  }
void BswApi_DisablePfcRly()                                 { BswGpio_DisableRly(); }

void BswApi_Gpio43En()                                      { BswGpio_Gpio43En(); }
void BswApi_Gpio43Dis()                                     { BswGpio_Gpio43Dis(); }
void BswApi_Gpio44En()                                      { BswGpio_Gpio44En(); }
void BswApi_Gpio44Dis()                                     { BswGpio_Gpio44Dis(); }

void BswApi_PfcLSSw_PosEn()                                 { BswGpio_PfcLSSw_PosEn(); }
void BswApi_PfcLSSw_NegEn()                                 { BswGpio_PfcLSSw_NegEn(); }
void BswApi_PfcLSSw_DeadBand()                              { BswGpio_PfcLSSw_DeadBand(); }
void BswApi_PfcHSPwmPosDitheringMode()                      { BswPwm_PfcHSPwmPosDitheringMode(); }
void BswApi_PfcHSPwmNegDitheringMode()                      { BswPwm_PfcHSPwmNegDitheringMode(); }
void BswApi_PfcHSPwmNormalMode()                            { BswPwm_PfcHSPwmNormalMode(); }

Uint8 BswApi_GetPwmEvtNum(Uint8 ch)                         { return BswPwm_GetPwmEvtNum(ch); }


//void BswApi_SetPwmPhase(Uint8 ch, float NomalizedPhase)     {BswPwm_SetPwmPhase(ch, NomalizedPhase);}
//void BswApi_SetSrPwmDuty(float Duty)                        {BswPwm_SetSrPwmDuty(Duty);}
//void BswApi_EnableObcPWM()                                  {BswPwm_EnableObcPwm();}
//void BswApi_DisableObcPWM()                                 {BswPwm_DisableObcPwm();}
//void BswApi_EnableSrPWM()                                   {BswPwm_EnableSrPwm();}
//void BswApi_DisableSrPWM()                                  {BswPwm_DisableSrPwm();}



