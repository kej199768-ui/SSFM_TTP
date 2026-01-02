/*
 * MonAdc.h
 *
 *  Created on: 2023. 1. 5.
 *      Author: poweryhs
 */

#ifndef ASW_M2_MON_MONADC_H_
#define ASW_M2_MON_MONADC_H_

/*============================================================================
    Includes
============================================================================*/
#include "../AswCommon.h"
#include <Util.h>

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
extern float gfIIccu[CurrSnsrNum];
extern float gfIIccuHwLpf[CurrSnsrNum];
extern float gfIIccuSwLpf[CurrSnsrNum];
extern filter1 gf1IiccuSwLpf[CurrSnsrNum];
extern float gfIIccuAdcResult[CurrSnsrNum];

extern float gfVIccu[VoltSnsrNum];
extern float gfVIccuHwLpf[VoltSnsrNum];
extern float gfVIccuSwLpf[VoltSnsrNum];
extern filter1 gf1ViccuSwLpf[VoltSnsrNum];
extern float gfVIccuAdcResult[VoltSnsrNum];

extern float gfVGridAvgSwLpf;
extern float gfVGridRms;
extern filter1 gf1VGridAvgSwLpf;

extern float gfVntc[TempSnsrNum];
extern float gfVntcHwLpf[TempSnsrNum];
extern float gfVntcSwLpf[TempSnsrNum];
extern filter1 gf1VntcSwLpf[TempSnsrNum];
extern float gfVntcAdcResult[TempSnsrNum];
extern float gfTemp[TempSnsrNum];
extern float gfTempMax;

extern float gfVauxbat;
extern float gfVauxbatHwLpf;
extern float gfVauxbatSwLpf;
extern filter1 gf1VauxbatSwLpf;
extern float gfVauxbatAdcResult;

extern float gfVSmps;
extern float gfVSmpsHwLpf;
extern float gfVSmpsSwLpf;
extern filter1 gf1SmpsSwLpf;
extern float gfVSmpsAdcResult;

extern float gfVig;
extern float gfVigHwLpf;
extern float gfVigSwLpf;
extern filter1 gf1VigSwLpf;
extern float gfVigAdcResult;

#ifdef DefInhibitTest
extern Uint16 giInhibitTest;
#endif

extern float gfVDcLink_Test;

/*============================================================================
    Private Variables/Constants
============================================================================*/

/*============================================================================
    Function Prototypes
============================================================================*/

/*============================================================================
    Function Implementations
============================================================================*/
void MonAdcIsrCtr(void);
void MonAdcTask100us(void);
void MonAdcTask1ms(void);
void MonAdcTask10ms(void);
void MonAdcTask100ms(void);


/*============================================================================
    Function Implementations
============================================================================*/



#endif /* ASW_M2_MON_MONADC_H_ */
