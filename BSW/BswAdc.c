/*
 * BswAdc.c
 *
 *  Created on: 2022. 11. 29.
 *      Author: poweryhs
 */

/*============================================================================
    Includes
============================================================================*/
#include "F28x_project.h"
#include "..\Util.h"
#include "BswVehicleDefine.h"
#include "BswCal.h"
#include "BswAdc.h"


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
Uint16 giAdcOffsetCalCnt;
Uint16 giAdcoffsetCplFlag;
float gfAdcResult[ADCCHANNELNUM] = {0.,};
filter1 gf1AdcResulLpf[ADCCHANNELNUM] = {0.,};
float gfAdcResultLpf[ADCCHANNELNUM] = {0.,};
float gfAdcResultOffset[ADCCHANNELNUM] = {0.,};

float gfCurrCal[CURRSNSRNUM] = {0.,};
float gfVoltCal[VOLTSNSRNUM] = {0.,};
float gfCurrRaw[CURRSNSRNUM] = {0.,};
float gfVoltRaw[VOLTSNSRNUM] = {0.,};


/*============================================================================
    Private Variables/Constants
============================================================================*/

/*============================================================================
    Function Prototypes
============================================================================*/

/*============================================================================
    Function Implementations
============================================================================*/

/************************************************************************
ADC Configuration
Current Sensor : ADCINA0 (IL)
Voltage Sensor : ADCINA3 (PFC IN), ADCINA4 (PFC OUT)
************************************************************************/
void InitAdcConfig()
{
    Uint16 acqps;

    EALLOW;
    //write configurations
    AdcaRegs.ADCCTL2.bit.PRESCALE = 6; //set ADCCLK divider to /4       //define adc clock
    AdcSetMode(ADC_ADCA, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);  //adc mode set, bit resolution, input mode
    AdcbRegs.ADCCTL2.bit.PRESCALE = 6; //set ADCCLK divider to /4
    AdcSetMode(ADC_ADCB, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);
    AdccRegs.ADCCTL2.bit.PRESCALE = 6; //set ADCCLK divider to /4
    AdcSetMode(ADC_ADCC, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);
    AdcdRegs.ADCCTL2.bit.PRESCALE = 6; //set ADCCLK divider to /4
    AdcSetMode(ADC_ADCD, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);

    //Set pulse positions to late
    AdcaRegs.ADCCTL1.bit.INTPULSEPOS = 1;                               //EOC에 interrupt pulse 발생
    AdcbRegs.ADCCTL1.bit.INTPULSEPOS = 1;
    AdccRegs.ADCCTL1.bit.INTPULSEPOS = 1;
    AdcdRegs.ADCCTL1.bit.INTPULSEPOS = 1;

    //power up the ADC
    AdcaRegs.ADCCTL1.bit.ADCPWDNZ = 1;
    AdcbRegs.ADCCTL1.bit.ADCPWDNZ = 1;
    AdccRegs.ADCCTL1.bit.ADCPWDNZ = 1;
    AdcdRegs.ADCCTL1.bit.ADCPWDNZ = 1;

    //delay for 1ms to allow ADC time to power up
    DELAY_US(1000);

    if(ADC_RESOLUTION_12BIT == AdcaRegs.ADCCTL2.bit.RESOLUTION)
    {
        acqps = 14; //75ns
    }
    else //resolution is 16-bit
    {
        acqps = 63; //320ns
    }

    // Inductor Current
    AdcbRegs.ADCSOC0CTL.bit.CHSEL   = ADC_CHANNEL_0;    //ADCA SOC0 will convert pin U1 (ADCA0)
    AdcbRegs.ADCSOC0CTL.bit.ACQPS   = acqps;            //sample window is 100 SYSCLK cycles
    AdcbRegs.ADCSOC0CTL.bit.TRIGSEL = ADCTRIG5;         //trigger on ePWM1 SOCA
    AdcbRegs.ADCSOC1CTL.bit.CHSEL   = ADC_CHANNEL_0;    //ADCA SOC0 will convert pin U1
    AdcbRegs.ADCSOC1CTL.bit.ACQPS   = acqps;            //sample window is 100 SYSCLK cycles
    AdcbRegs.ADCSOC1CTL.bit.TRIGSEL = ADCTRIG6;         //trigger on ePWM1 SOCB

    // Input Voltage
    AdcbRegs.ADCSOC2CTL.bit.CHSEL   = ADC_CHANNEL_3;    //ADCA SOC2 will convert pin T2 (ADCA3)
    AdcbRegs.ADCSOC2CTL.bit.ACQPS   = acqps;
    AdcbRegs.ADCSOC2CTL.bit.TRIGSEL = ADCTRIG5;
    AdcbRegs.ADCSOC3CTL.bit.CHSEL   = ADC_CHANNEL_3;
    AdcbRegs.ADCSOC3CTL.bit.ACQPS   = acqps;
    AdcbRegs.ADCSOC3CTL.bit.TRIGSEL = ADCTRIG6;

    // Output Voltage
    AdcbRegs.ADCSOC4CTL.bit.CHSEL   = ADC_CHANNEL_4;    //ADCA SOC4 will convert pin U3 (ADCA4)
    AdcbRegs.ADCSOC4CTL.bit.ACQPS   = acqps;
    AdcbRegs.ADCSOC4CTL.bit.TRIGSEL = ADCTRIG5;
    AdcbRegs.ADCSOC5CTL.bit.CHSEL   = ADC_CHANNEL_4;
    AdcbRegs.ADCSOC5CTL.bit.ACQPS   = acqps;
    AdcbRegs.ADCSOC5CTL.bit.TRIGSEL = ADCTRIG6;


    /**********************************************************************
      ADC Interrupt Setting
    **********************************************************************/
    AdcbRegs.ADCINTSEL1N2.bit.INT1SEL   = INTSELEOC5;   //end of ADCA EOC5 will set INT1 flag
    AdcbRegs.ADCINTSEL1N2.bit.INT1E     = 1;            //enable INT1 flag
    AdcbRegs.ADCINTFLGCLR.bit.ADCINT1   = 1;            //make sure INT1 flag is cleared

    EDIS;
}

void BswAdcIsrOffsetCalc()
{
    int i = 0;

    if(giAdcOffsetCalCnt < giAdcOffsetCalCntCal)        //giAdcOffsetCalCntCal = 25k ==> ISRFREQ 25kHz ==> 1s
    {
        giAdcoffsetCplFlag = FALSE;
        gfAdcResult[0] = (AdcbResultRegs.ADCRESULT0 + AdcbResultRegs.ADCRESULT1) * 0.5;         //PFC Inductor Current
        gfAdcResult[1] = (AdcbResultRegs.ADCRESULT2 + AdcbResultRegs.ADCRESULT3) * 0.5;         //AC Input Voltage
        gfAdcResult[2] = (AdcbResultRegs.ADCRESULT4 + AdcbResultRegs.ADCRESULT5) * 0.5;         //DC Output Voltage

        for(i=0;i<ADCCHANNELNUM;i++)
        {
            gfAdcResultLpf[i] = LPF1(gfIsrTsInitCal, 10, gfAdcResult[i] ,&gf1AdcResulLpf[i] );
        }
    }
    else if(giAdcOffsetCalCnt == giAdcOffsetCalCntCal)        //giAdcOffsetCalCntCal = 25k ==> ISRFREQ 25kHz ==> 1s
    {
        memcpy(gfAdcResultOffset,gfAdcResultLpf,sizeof(float)*ADCCHANNELNUM);
    }
    else
    {
        giAdcOffsetCalCnt = giAdcOffsetCalCntCal + 1;
        giAdcoffsetCplFlag = TRUE;
    }

    giAdcOffsetCalCnt++;
}

void BswAdcIsrCalc()
{
    if(giAdcoffsetCplFlag == TRUE)
    {
        gfCurrRaw[0]    = (AdcbResultRegs.ADCRESULT0 + AdcbResultRegs.ADCRESULT1) * 0.5;        //PFC Inductor Current
        gfVoltRaw[0]    = (AdcbResultRegs.ADCRESULT2 + AdcbResultRegs.ADCRESULT3) * 0.5;        //AC Input Voltage
        gfVoltRaw[1]    = (AdcbResultRegs.ADCRESULT4 + AdcbResultRegs.ADCRESULT5) * 0.5;        //DC Link Output Voltage

        gfCurrCal[0]    = (gfCurrRaw[0] - gfPfcCurrOffsetCal) * gfPfcCurrAdcGainCal;
        gfVoltCal[0]    = (gfVoltRaw[0] - gfPfcInVoltOffsetCal) * gfPfcInVoltAdcGainCal;
        gfVoltCal[1]    = (gfVoltRaw[1] - gfPfcOutVoltOffsetCal) * gfPfcOutVoltAdcGainCal;

//        gfCurrCal[0]    = (gfCurrRaw[0] - gfAdcResultOffset[0]) * gfPfcCurrAdcGainCal;
//        gfVoltCal[0]    = (gfVoltRaw[0] - gfAdcResultOffset[1]) * gfPfcInVoltAdcGainCal;
//        gfVoltCal[0]    = (gfVoltRaw[0] - 2103.f) * gfPfcInVoltAdcGainCal;
//        gfVoltCal[1]    = (gfVoltRaw[1] - gfAdcResultOffset[2]) * gfPfcOutVoltAdcGainCal;
//        gfVoltCal[1]    = gfVoltRaw[1] * gfPfcOutVoltAdcGainCal;

//        gfCurrCal[0]    = (gfCurrRaw[0] - 2047.) * gfPfcCurrAdcGainCal;
//        gfVoltCal[0]    = (gfVoltRaw[0] - 2102.) * gfPfcInVoltAdcGainCal;
//        gfVoltCal[1]    = (gfVoltRaw[1] - 0.) * gfPfcOutVoltAdcGainCal;

    }
}


