/*
 * BswCal.h
 *
 *  Created on: 2023. 1. 4.
 *      Author: poweryhs
 */

#ifndef BSW_BSWCAL_H_
#define BSW_BSWCAL_H_

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
//extern float gfObcCurrSnsrGainCal;
//extern float gfLdcCurrSnsrGainCal;
//extern float gfObcVoltSnsrGainCal;
//extern float gfLdcVoltSnsrGainCal;

extern float gfPwmFreqInitCal;
extern Uint16 giAdcOffsetCalCntCal;
extern float gfIsrTsInitCal;
extern Uint16 giDeadBandCal;
extern Uint16 giDeadBandSrCal;

extern float gfPfcCurrAdcGainCal;
extern float gfPfcInVoltAdcGainCal;
extern float gfPfcOutVoltAdcGainCal;

extern float gfPfcCurrOffsetCal;
extern float gfPfcInVoltOffsetCal;
extern float gfPfcOutVoltOffsetCal;

/*============================================================================
    Private Variables/Constants
============================================================================*/

/*============================================================================
    Function Prototypes
============================================================================*/



#endif /* BSW_BSWCAL_H_ */
