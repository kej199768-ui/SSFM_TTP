/*
 * AswVehicleDefine.h
 *
 *  Created on: 2023. 1. 4.
 *      Author: poweryhs
 */

#ifndef ASW_BACKUP_ASWVEHICLEDEFINE_H_
#define ASW_BACKUP_ASWVEHICLEDEFINE_H_


 /*============================================================================
     Includes
 ============================================================================*/

 /*============================================================================
     Macros
 ============================================================================*/

#define ObcLdcFirmVer       230811_T00_V2_0
#define DefInhibitTest
//#define DefCurrAdcTest
//#define DefVoltAdcTest
#define DefDisableVoltUVInhibit

#ifdef DefInhibitTest
#define AdcNum              7
#else
#define AdcNum              6
#endif
#define AdcCurrObcIn        0
#define AdcCurrObcOut       1
#define AdcCurrLdcOut       2
#define AdcVoltObcIn        3 
#define AdcVoltObcOut       4
#define AdcVoltLdcOut       5
#ifdef DefInhibitTest
#define AdcInhibit          6
#endif

#define SrPwmChNum          2       //PwmChnumber

#define CurrSnsrNum         1       //Number of Sensor
#define CurrSnsrLdcOut      0

#define VoltSnsrNum         1       //Number of Sensor
#define VoltSnsrLdcOut      0

#define TempSnsrNum         4       //Number of Sensor
#define NtcBoost1           0
#define NtcBoost2           1
#define NtcBoost3           2
#define NtcBoost4           3

#define TRTRUNRATIO         12

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

#endif /* ASW_BACKUP_ASWVEHICLEDEFINE_H_ */
