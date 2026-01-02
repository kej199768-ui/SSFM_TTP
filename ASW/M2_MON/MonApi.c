/*
 * MonApi.c
 *
 *  Created on: 2023. 1. 5.
 *      Author: poweryhs
 */


/*============================================================================
    Includes
============================================================================*/
#include "MonApi.h"
#include "MonAdc.h"
#include "MonPwr.h"

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
float MonApi_GetCurr(Uint16 SnsrNum)            { return gfIIccu[SnsrNum]; }
float MonApi_GetVolt(Uint16 SnsrNum)            { return gfVIccu[SnsrNum]; }
float MonApi_GetNtcVolt(Uint16 SnsrNum)         { return gfVntc[SnsrNum]; }
float MonApi_GetAuxBatVolt(void)                { return gfVauxbat; }
float MonApi_GetSmpsVolt(void)                  { return gfVSmps; }
float MonApi_GetIgVolt(void)                    { return gfVig; }
float MonApi_GetTemp(Uint16 SnsrNum)            { return gfTemp[SnsrNum]; }
float MonApi_GetTempMax(void)                   { return gfTempMax; }

float MonApi_GetCurrAdcResult(Uint16 SnsrNum)   {return gfIIccuAdcResult[SnsrNum]; }
float MonApi_GetVoltAdcResult(Uint16 SnsrNum)   {return gfVIccuAdcResult[SnsrNum]; }
float MonApi_GetNtcVoltAdcResult(Uint16 SnsrNum){return gfVntcAdcResult[SnsrNum]; }
float MonApi_GetAuxBatVoltAdcResult(void)       {return gfVauxbatAdcResult; }
float MonApi_GetSmpsVoltAdcResult(void)         {return gfVSmpsAdcResult; }
float MonApi_GetIgVoltAdcResult(void)           {return gfVigAdcResult; }

float MonApi_GetCurrHwLpf(Uint16 SnsrNum)       { return gfIIccuHwLpf[SnsrNum]; }
float MonApi_GetVoltHwLpf(Uint16 SnsrNum)       { return gfVIccuHwLpf[SnsrNum]; }
float MonApi_GetNtcVoltHwLpf(Uint16 SnsrNum)    { return gfVntcHwLpf[SnsrNum]; }
float MonApi_GetAuxBatVoltHwLpf(void)           { return gfVauxbatHwLpf; }
float MonApi_GetSmpsVoltHwLpf(void)             { return gfVSmpsHwLpf; }
float MonApi_GetIgVoltHwLpf(void)               { return gfVigHwLpf; }

float MonApi_GetCurrSwLpf(Uint16 SnsrNum)       { return gfIIccuSwLpf[SnsrNum]; }
float MonApi_GetVoltSwLpf(Uint16 SnsrNum)       { return gfVIccuSwLpf[SnsrNum]; }
float MonApi_GetNtcVoltSwLpf(Uint16 SnsrNum)    { return gfVntcSwLpf[SnsrNum]; }
float MonApi_GetAuxBatVoltSwLpf(void)           { return gfVauxbatSwLpf; }
float MonApi_GetSmpsVoltSwLpf(void)             { return gfVSmpsSwLpf; }
float MonApi_GetIgVoltSwLpf(void)               { return gfVigSwLpf; }


float MonApi_GetGridVoltRms(void)               { return gfVGridRms; }

float MonApi_GetIccuInPwr(void)                 { return gfIccuInPwr; }
float MonApi_GetIccuOutPwr(void)                { return gfIccuOutPwr; }

#ifdef DefInhibitTest
#ifdef DefSimul
Uint16 MonApi_GetInhibitstate(void)             { return giInhibitTest = (Uint16)ItrCom_GetTestInhibit(); }
#else
Uint16 MonApi_GetInhibitstate()                 { return giInhibitTest; }
#endif
#endif

void MonApi_AdcIsrCtr(void)                     { MonAdcIsrCtr(); }
void MonApi_AdcTask100us(void)                  { MonAdcTask100us(); }
void MonApi_AdcTask1ms(void)
{
    MonAdcTask1ms();
    MonPwrTask1ms();
}


