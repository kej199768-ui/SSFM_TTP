/*
 * MonCal.h
 *
 *  Created on: 2023. 1. 5.
 *      Author: poweryhs
 */

#ifndef ASW_M2_MON_MONCAL_H_
#define ASW_M2_MON_MONCAL_H_

/*============================================================================
    Includes
============================================================================*/
#include "../AswCommon.h"

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
extern float gfPfcCurrAdcScaleCal;
extern float gfInVoltAdcScaleCal;
extern float gfPfcVoltAdcScaleCal;
extern float gfPfcNtcAdcScaleCal;

extern float gfDcDcCurrAdcScaleCal;
extern float gfDcDcVoltAdcScaleCal;


extern Uint16 gf1dTempDataCntCal;
extern float gfxDataVntcCal[8];
extern float  gfyDataTempCal[8];

extern float gfISRTS;

/*============================================================================
    Function Prototypes
============================================================================*/
void MonCalIsrCtr(void);


#endif /* ASW_M2_MON_MONCAL_H_ */
