/*
 * BswCal.c
 *
 *  Created on: 2023. 1. 4.
 *      Author: poweryhs
 */

/*============================================================================
    Includes
============================================================================*/
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
//float gfObcCurrSnsrGainCal = 0.040293040293;
//float gfLdcCurrSnsrGainCal = 0.1221;
//float gfObcVoltSnsrGainCal = 0.3243892723167;
//float gfLdcVoltSnsrGainCal = 0.0057097179399;

float gfPfcCurrAdcGainCal       = 0.0305250305250305;
float gfPfcInVoltAdcGainCal     = 0.26713286713287;
float gfPfcOutVoltAdcGainCal    = 0.246264130135098;

float gfPfcCurrOffsetCal        = 2047.5f;
float gfPfcInVoltOffsetCal      = 2102.1f;
float gfPfcOutVoltOffsetCal     = 0.0f;

float gfPwmFreqInitCal      = PWMFREQ;
Uint16 giAdcOffsetCalCntCal = (Uint16)(ISRFREQ);
//float gfIsrTsInitCal        = ISRTS;
Uint16 giDeadBandCal        = 20;       //1clock 5ns
Uint16 giDeadBandSrCal      = 20;

float gfISRTScal               = 1.f / PWMFREQ;


/*============================================================================
    Private Variables/Constants
============================================================================*/

/*============================================================================
    Function Prototypes
============================================================================*/

/*============================================================================
    Function Implementations
============================================================================*/
void BswCal_ChangeIsrTs(float EvtNum, float Freq)
{
    gfISRTScal = EvtNum / Freq;
}

