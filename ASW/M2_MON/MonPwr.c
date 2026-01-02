/*
 * MonPwr.c
 *
 *  Created on: 2023. 1. 5.
 *      Author: poweryhs
 */

/*============================================================================
    Includes
============================================================================*/
#include "MonPwr.h"
#include "MonAdc.h"
#include "MonApi.h"

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
float gfIccuInPwr        = 0.f;
float gfIccuOutPwr       = 0.f;

/*============================================================================
    Private Variables/Constants
============================================================================*/

/*============================================================================
    Function Prototypes
============================================================================*/
void MonPwrInPwrHwCalc1ms(void);
void MonPwrInPwrSwCalc1ms(void);

/*============================================================================
    Function Implementations
============================================================================*/
void MonPwrIsrCtr(void)     {}
void MonPwrTask100us(void)  {}
void MonPwrTask1ms(void)
{
    MonPwrInPwrSwCalc1ms();     //Debug 필요
}
void MonPwrTask10ms(void)   {}
void MonPwrTask100ms(void)  {}


void MonPwrInPwrHwCalc1ms(void)
{
    float fGridVoltHwLpf = MonApi_GetVoltHwLpf(VoltSnsrGrid);
    float fBoostCurrHwLpf = MonApi_GetCurrHwLpf(CurrSnsrPhase);
    float fDCLinkVoltHwLpf = MonApi_GetVoltHwLpf(VoltSnsrDCLink);
    float fOutVoltHwLpf = MonApi_GetVoltHwLpf(VoltSnsrOut);
    float fDcDcOutCurrHwLpf = MonApi_GetCurrHwLpf(CurrSnsrDcDcOut);
    
    gfIccuInPwr = fGridVoltHwLpf * fBoostCurrHwLpf;
    //    gfPfcOutPwr = fDCLinkVoltHwLpf * 
    gfIccuOutPwr = fOutVoltHwLpf * fDcDcOutCurrHwLpf;
}

//Debug 필요
void MonPwrInPwrSwCalc1ms(void) 
{
    float fGridVoltSwLpf = MonApi_GetVoltSwLpf(VoltSnsrGrid);
    float fBoostCurrSwLpf = MonApi_GetCurrSwLpf(CurrSnsrPhase);
    float fDCLinkVoltSwLpf = MonApi_GetVoltSwLpf(VoltSnsrDCLink);
    float fOutVoltSwLpf = MonApi_GetVoltSwLpf(VoltSnsrOut);
    float fDcDcOutCurrSwLpf = MonApi_GetCurrSwLpf(CurrSnsrDcDcOut);

    gfIccuInPwr = fGridVoltSwLpf * fBoostCurrSwLpf;
    //    gfPfcOutPwr = fDCLinkVoltSwLpf * 
    gfIccuOutPwr = fOutVoltSwLpf * fDcDcOutCurrSwLpf;

}



