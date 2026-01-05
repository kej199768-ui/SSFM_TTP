/*
 * MonApi.h
 *
 *  Created on: 2023. 1. 5.
 *      Author: poweryhs
 */

#ifndef ASW_M2_MON_MONAPI_H_
#define ASW_M2_MON_MONAPI_H_

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

/*============================================================================
    Function Prototypes
============================================================================*/
float MonApi_GetCurr(Uint16 SnsrNum);
float MonApi_GetVolt(Uint16 SnsrNum);
float MonApi_GetNtcVolt(Uint16 SnsrNum);
float MonApi_GetAuxBatVolt(void);
float MonApi_GetSmpsVolt(void);
float MonApi_GetIgVolt(void);
float MonApi_GetTemp(Uint16 SnsrNum);
float MonApi_GetTempMax(void);
float MonApi_GetISRTS(void);

float MonApi_GetCurrAdcResult(Uint16 SnsrNum);
float MonApi_GetVoltAdcResult(Uint16 SnsrNum);
float MonApi_GetNtcVoltAdcResult(Uint16 SnsrNum);
float MonApi_GetAuxBatVoltAdcResult(void);
float MonApi_GetSmpsVoltAdcResult(void);
float MonApi_GetIgVoltAdcResult(void);


float MonApi_GetCurrHwLpf(Uint16 SnsrNum);
float MonApi_GetVoltHwLpf(Uint16 SnsrNum);
float MonApi_GetNtcVoltHwLpf(Uint16 SnsrNum);
float MonApi_GetAuxBatVoltHwLpf(void);
float MonApi_GetSmpsVoltHwLpf(void);
float MonApi_GetIgVoltHwLpf(void);

float MonApi_GetCurrSwLpf(Uint16 SnsrNum);
float MonApi_GetVoltSwLpf(Uint16 SnsrNum);
float MonApi_GetNtcVoltSwLpf(Uint16 SnsrNum);
float MonApi_GetAuxBatVoltSwLpf(void);
float MonApi_GetSmpsVoltSwLpf(void);
float MonApi_GetIgVoltSwLpf(void);

float MonApi_GetGridVoltRms(void);

float MonApi_GetIccuInPwr(void);
float MonApi_GetIccuOutPwr(void);

#ifdef DefInhibitTest
Uint16 MonApi_GetInhibitstate(void);
#endif

void MonApi_CalIsrCtr(void);
void MonApi_AdcIsrCtr(void);
void MonApi_AdcTask100us(void);
void MonApi_AdcTask1ms(void);


#endif /* ASW_M2_MON_MONAPI_H_ */
