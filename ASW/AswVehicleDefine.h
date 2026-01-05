/*
 * AswVehicleDefine.h
 *
 *  Created on: 2023. 1. 4.
 *      Author: poweryhs
 */

#ifndef ASW_ASWVEHICLEDEFINE_H_
#define ASW_ASWVEHICLEDEFINE_H_


 /*============================================================================
     Includes
 ============================================================================*/

 /*============================================================================
     Macros
 ============================================================================*/

#define ICCUFirmVer         230310_T00_V1_0
#define OBCFirmVer          230310_T00_V1_0
#define LDCFirmVer          230310_T00_V1_0
#define DefOBCType          1      // 1: totempolePFC + LLC 2병렬
#define DefLDCType          1      // 1: ACF, PSFB
#define DefFdcType          1      // 1: ACF, PSFB
 //CCS상에서 기능 검증
#define TestMode            4      // 0: Normal 모드 1 : sw로직 검증, 2 : Openloop Test, 3 : 출력전압 및 전류 제어. 4 : 입출력, 전류 제어
#if(TestMode == 0)
#elif(TestMode == 1)
#elif(TestMode == 2)
#elif(TestMode == 3)
#elif(TestMode == 4)
#define DefInhibitTest
#define DefControlTest
//#define OpenloopPwmTest
//#define DefDisableInVoltCtr
//#define DefOutVoltSS
//#define DefDisableInVoltDrt
#define DefAdaptiveGainControl
#define DefDisableVoltUVInhibit
//#define DefDisableInVoltHighInhibit
#define DefDisableGateRdyInhibit      
//#define DefDisableFltRetry
//#define DefTempAdcTest
//#define DefVoltAdcTest
//#define DefCurrAdcTest
#define DefDisableHWFlt
//#define DefOutVoltRisingEdgeDet        
//#define DefDisableSnsrFltDiag
#define DefDisableCom
#define DefDisbaleInterlock
#endif

#if(DefOBCType == 1)
#ifdef DefInhibitTest
#define AdcNum              25U
#else
#define AdcNum              13U
#endif
#define AdcCurrPhase        0U
#define AdcCurrDcDcOut      1U
#define AdcVoltGrid         2U
#define AdcVoltDCLink       3U
#define AdcVoltOut          4U
#define AdcVoltNtcPFC       5U
#define AdcVoltNtcDCDC      6U
#define AdcVoltNtcHsink     7U
#define AdcVoltAuxBat       8U
#define AdcVoltSmps         9U
#define AdcVoltIG           10U
#ifdef DefInhibitTest       
#define AdcInhibit          11U
#endif

#define BoostPFCNum         1U       //Phase number
#define DCDCNum             1U       //Phase number

#define CurrSnsrNum         2U       //Number of Module
#define CurrPfcSnsrNum      1U
#define CurrDcDcSnsrNum     1U
#define CurrSnsrPhase       0U
#define CurrSnsrDcDcOut     1U

#define CurrLpfSnsrNum      2U       //Number of Module
#define CurrSnsrLpfPhase    0U
#define CurrSnsrLpfDcDcOut  1U

#define CurrCtrNum          2U       //Number of CtrModule
#define CurrCtrPhase        0U
#define CurrCtrDcDcOut      1U

#define VoltSnsrNum         3U       //Number of Module
#define VoltSnsrGrid        0U
#define VoltSnsrDCLink      1U
#define VoltSnsrOut         2U

#define VoltLpfSnsrNum      3U       //Number of Module
#define VoltSnsrLpfGrid     0U
#define VoltSnsrLpfDCLink   1U
#define VoltSnsrLpfOut      2U

#define VoltCtrNum          3U       //Number of Ctr Module
#define VoltCtrGridPll      0U
#define VoltCtrDCLink       1U
#define VoltCtrOut          2U

#define TempSnsrNum         3U       //Number of Module
#define NtcSnsrBoost        0U       
#define NtcSnsrDcDc         1U       
#define NtcSnsrDcDc         1U       

#define CurrFltNum          2U
#define GateSnsrNum         2U
#define GateSnsrPfc         0U
#define GateSnsrDcDc        1U
#define GateFltNum          2U
#define GateRdyNum          2U
#endif

#define DefPFCBoostL           610.0e-6f
#define DefPFCLinkCap          660.0e-6f
#define DefOutCap              19.5e-6f
#define DefTurnRatio           0.6315789473684f // Ns/Np = 12/191

#define DeffBWGridPLL               10.0f       //[Hz] PLL control BandWidth
#define DeffBWPFCDCLinkVolt         10.0f       //[Hz] PFC DCLink BandWidth
#define DeffBWPFCCurr               1000.0f        //[Hz] PFC Current BandWidth

#define PWMFREQ             70000.f
#define PWMTS               1.429e-5f
#define ISRPWMEVTNUM        1//4
#define ISRFREQ             PWMFREQ/ISRPWMEVTNUM
//#define ISRTS               PWMTS*ISRPWMEVTNUM

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

#endif /* ASW_ASWVEHICLEDEFINE_H_ */
