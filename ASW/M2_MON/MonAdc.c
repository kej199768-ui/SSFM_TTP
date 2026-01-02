/*
 * MonAdc.c
 *
 *  Created on: 2023. 1. 5.
 *      Author: poweryhs
 */

/*============================================================================
    Includes
============================================================================*/
#include "MonAdc.h"
#include "../M0_Main/AswMainApi.h"
#include "MonCal.h"

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
float gfIIccu[CurrSnsrNum]           = { 0.f, };
float gfIIccuHwLpf[CurrSnsrNum]      = { 0.f, };
float gfIIccuSwLpf[CurrSnsrNum]      = { 0.f, };
filter1 gf1IiccuSwLpf[CurrSnsrNum]   = {filter1_defaults,};
float gfIIccuAdcResult[CurrSnsrNum]  = { 0.f, };

float gfVIccu[VoltSnsrNum]           = { 0.f, };
float gfVIccuHwLpf[VoltSnsrNum]      = { 0.f, };
float gfVIccuSwLpf[VoltSnsrNum]      = { 0.f, };
filter1 gf1ViccuSwLpf[VoltSnsrNum]   = { filter1_defaults, };
float gfVIccuAdcResult[VoltSnsrNum]  = { 0.f, };

float gfVGridAvgSwLpf                = 0.0f;
float gfVGridRms                     = 0.0f;
filter1 gf1VGridAvgSwLpf             = filter1_defaults;

float gfVntc[TempSnsrNum]            = { 0.f, };
float gfVntcHwLpf[TempSnsrNum]       = { 0.f, };
float gfVntcSwLpf[TempSnsrNum]       = { 0.f, };
filter1 gf1VntcSwLpf[TempSnsrNum]    = { filter1_defaults, };
float gfVntcAdcResult[TempSnsrNum]   = { 0.f, };
float gfTemp[TempSnsrNum]            = { 0.f, };
float gfTempMax                     = 0.f;

float gfCurrAdcResultOffset[CurrSnsrNum] = { 0.f, };
float gfVoltAdcResultOffset[VoltSnsrNum] = { 0.f, };

float gfVauxbat                     = 0.f;
float gfVauxbatHwLpf                = 0.f;
float gfVauxbatSwLpf                = 0.f;
filter1 gf1VauxbatSwLpf             = filter1_defaults;
float gfVauxbatAdcResult            = 0.f;

float gfVSmps                       = 0.f;
float gfVSmpsHwLpf                  = 0.f;
float gfVSmpsSwLpf                  = 0.f;
filter1 gf1VSmpsSwLpf               = filter1_defaults;
float gfVSmpsAdcResult              = 0.f;

float gfVig                         = 0.f;
float gfVigHwLpf                    = 0.f;
float gfVigSwLpf                    = 0.f;
filter1 gf1VigSwLpf                 = filter1_defaults;
float gfVigAdcResult                = 0.f;

float gfVsmps                       = 0.f;
float gfVsmpsHwLpf                  = 0.f;
float gfVsmpsSwLpf                  = 0.f;
filter1 gf1VsmpsSwLpf               = filter1_defaults;
float gfVsmpsAdcResult              = 0.f;

#ifdef DefInhibitTest
Uint16 giInhibitTest                = 0U;
#endif
Uint16 giAdcResultTest              = 2047U;  

float gfVDcLink_Test                = 0.f;


/*============================================================================
    Private Variables/Constants
============================================================================*/

/*============================================================================
    Function Prototypes
============================================================================*/
void MonAdcIsr(void);
void MonAdc100us(void);
void MonAdcTemp(void);
void MonAdcAvgRms(void);
/*============================================================================
    Function Implementations
============================================================================*/
void MonAdcIsrCtr(void)
{
    MonAdcIsr();
}
void MonAdcTask100us(void)
{
    MonAdc100us();
}
void MonAdcTask1ms(void)
{
//    MonAdcTemp();
    MonAdcAvgRms();
}
void MonAdcTask10ms(void) {}
void MonAdcTask100ms(void) {}


/*----------------------------------------------------------------------------
    Func : 전류 전압 ADC
    Period : ISR
    Parameter : 
----------------------------------------------------------------------------*/
void MonAdcIsr(void)
{
    //ICCU PFC단 인덕터 전류 센싱
    gfIIccuAdcResult[CurrSnsrPhase]    = ItrCom_GetCurrRaw(CurrSnsrPhase);
    //gfIIccu[CurrSnsrPhase]             = gfPfcCurrAdcScaleCal * (gfIIccuAdcResult[CurrSnsrPhase] - 2047.5f);  //simulation
    gfIIccu[CurrSnsrPhase]              = ItrCom_GetCurr(CurrSnsrPhase);

    //ICCU 입력전압, DC Link 전압 센싱
    gfVIccuAdcResult[VoltSnsrGrid]      = ItrCom_GetVoltRaw(VoltSnsrGrid);
    gfVIccuAdcResult[VoltSnsrDCLink]    = ItrCom_GetVoltRaw(VoltSnsrDCLink);
//    gfVIccu[VoltSnsrGrid]               = gfInVoltAdcScaleCal * (gfVIccuAdcResult[VoltSnsrGrid] - 2047.5f);   //simulation
//    gfVIccu[VoltSnsrDCLink]             = gfPfcVoltAdcScaleCal * gfVIccuAdcResult[VoltSnsrDCLink];
    gfVIccu[VoltSnsrGrid]               = ItrCom_GetVolt(VoltSnsrGrid);
    gfVIccu[VoltSnsrDCLink]             = ItrCom_GetVolt(VoltSnsrDCLink);
//    gfVIccu[VoltSnsrDCLink]             = gfVDcLink_Test;               //Test

    //gfVPfcDcLinkCmd                     = 

    ////ICCU DC/DC단 출력 전류 센싱
    //gfIIccuAdcResult[CurrSnsrDcDcOut] = API_RD_RAW_I_DC();
    //gfIIccu[CurrSnsrDcDcOut] = gfDcDcCurrAdcScaleCal * (gfIIccuAdcResult[CurrSnsrDcDcOut] - 2047.5f);

    ////ICCU 출력전압 센싱
    //gfVIccuAdcResult[VoltSnsrOut] = API_RD_RAW_V_DC();
    //gfVIccu[VoltSnsrOut] = gfDcDcVoltAdcScaleCal * gfVIccuAdcResult[VoltSnsrOut];

//    gfVig = API_RD_ROW_IGN_SEN();
//    gfVauxbat = API_RD_ROW_BAT_SEN();
//    gfVsmps = API_RD_ROW_V_AUX();

}

/*----------------------------------------------------------------------------
    Func : 전류 전압 ADC SW LPF
    Period : 100us
    Parameter :
----------------------------------------------------------------------------*/
void MonAdc100us(void)
{
//    Uint8 i = 0;
    
    //ICCU PFC단 전류 LPF
    gfIIccuSwLpf[CurrSnsrPhase] = LPF1(Ts10k, 1000.f, gfIIccu[CurrSnsrPhase], &gf1IiccuSwLpf[CurrSnsrPhase]);;

    //ICCU 입력전압 및 DC Link 전압 센싱 LPF
    gfVIccuSwLpf[VoltSnsrGrid]    = LPF1(Ts10k, 1000.f, gfVIccu[VoltSnsrGrid] , &gf1ViccuSwLpf[VoltSnsrGrid] );
    gfVIccuSwLpf[VoltSnsrDCLink]  = LPF1(Ts10k, 1000.f, gfVIccu[VoltSnsrDCLink] , &gf1ViccuSwLpf[VoltSnsrDCLink] );

}

/*----------------------------------------------------------------------------
    Func : 온도 추정 
    Period : 1ms
    Parameter :
----------------------------------------------------------------------------*/
void MonAdcTemp(void)
{
    Uint8 i = 0U;
    float fTempMax = 0.f;

//  gfVntcAdcResult[0] = API_RD_ROW_V_NTC1();
//  gfVntcAdcResult[1] = API_RD_ROW_V_NTC2();
//  gfVntcAdcResult[2] = API_RD_ROW_V_NTC3();
// 
//  for (i = 0; i < TempSnsrNum; i++)
//  {
//    gfVntc[i] = gfPfcNtcAdcScaleCal * gfVntcAdcResult[i];
//  }

//  for (i = 0; i < TempSnsrNum; i++)
    for (i = 0U; i < 1U; i++)
    {
        gfTemp[i] = Interp1DCalc(gfxDataVntcCal, gfyDataTempCal, gf1dTempDataCntCal, gf1dTempDataCntCal, gfVntcSwLpf[i]);
        if (gfTemp[i] > fTempMax)
        {
            fTempMax = gfTemp[i];
        }
    }
    gfTempMax = fTempMax;
    
}

/*----------------------------------------------------------------------------
    Func : 입력 Rms 전압 도출
    Period : 1ms
    Parameter :
----------------------------------------------------------------------------*/
void MonAdcAvgRms(void)
{
    gfVGridAvgSwLpf = LPF1(Ts1k, 10.0f, (fabs)(gfVIccu[VoltSnsrGrid]), &gf1VGridAvgSwLpf);      //1st LPF averaging
    gfVGridRms = gfVGridAvgSwLpf * AVGtoRMS;
}
