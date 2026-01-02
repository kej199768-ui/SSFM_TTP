/*
 * AswMain.c
 *
 *  Created on: 2023. 1. 4.
 *      Author: poweryhs
 */


/*============================================================================
    Includes
============================================================================*/
#include <ASW_backup/AswCal.h>

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

//PFCState
float gfVPfcDcLinkSSGainCal = 0.8f;
Uint16 giVPfcSoftStart_TimerCal = 100U;     //100 * 1ms

//(KEJ) PLL PI
float gfGridPLLKpCal                = 2.0f * DeffBWGridPLL;
float gfGridPLLKiCal                = POW2( DeffBWGridPLL);
float gfGridPLLFF                   = 60.0f * PI2;
//float gfGridPLLKpCal = 2.0f * 0.707f * DeffBWGridPLL / 300.0f;
//float gfGridPLLKiCal = DeffBWGridPLL * DeffBWGridPLL / 300.0f;
//float gfGridPLLFF = 60.0f * PI2;

//(KEJ) PFC DcLinkV PI
float gfPfcDcLinkVoltPIKpCal        = 2.0f * PI2 * DeffBWPFCDCLinkVolt * DefPFCLinkCap;
float gfPfcDcLinkVoltPIKiCal        = POW2(PI2 * DeffBWPFCDCLinkVolt) * DefPFCLinkCap;
float gfPfcDcLinkVoltPIKpMinCal     = 2.0f * PI2 * DeffBWPFCDCLinkVolt * DefPFCLinkCap * 100.0f;
float gfPfcDcLinkVoltPIKiMinCal     = POW2(PI2 * DeffBWPFCDCLinkVolt) * DefPFCLinkCap * 100.0f;
float gfPfcDcLinkVoltPIOutMax       = 5500.0f * 2.0f;
float gfPfcDcLinkVoltPIOutMin       = -5500.0f * 2.0f;
float gfVPfcDcLinkRefMaxCal         = 800.0f;
float gfVPfcDcLinkRefMinCal         = 370.0f;
float gfDrPfcDcLinkVoltBsf          = 0.25f;

//(KEJ) PFC DcLinkV Err Rate limiter
float gfVPfcDcLinkCmdRateLimitCal = 10.0f;

//(KEJ) PFC Curr PI
float gfPfcCurrPIKpCal              = 2.0f * PI2 * DeffBWPFCCurr * DefPFCBoostL;
float gfPfcCurrPIKiCal              = POW2(PI2 * DeffBWPFCCurr) * DefPFCBoostL;
float gfPfcCurrPIKpMaxCal           = 2.0f * PI2 * DeffBWPFCCurr * DefPFCBoostL / 100.0f;
float gfPfcCurrPIKiMaxCal           = POW2(PI2 * DeffBWPFCCurr) * DefPFCBoostL / 100.0f;
float gfPfcCurrPIOutMax             = 0.99f;
float gfPfcCurrPIOutMin             = 0.01f;

//float gfCurr_HiFlt_Cal[CurrSnsrNum] = { 220.0 };
//float gfVolt_HiFlt_Cal[VoltSnsrNum] = { 22.0 };
//float gfVolt_LowInhibit_Cal[VoltSnsrNum] = { 100.0 };
//
//float gfLdcCurrPIKpCal                  = 0.00025;
//float gfLdcCurrPIKiCal                  = 1.3;
//float gfLdcCurrPIKaCal                  = 1/0.00025;
//float gfLdcCurrPIOutMaxCal              = 0.499;
//float gfLdcCurrPIOutMinCal              = 0.;
//float gfLdcCurrPIOutSSCal               = 0.5 / 1500;  // 0.5 /( 0.03 * 50k) //30ms
//float gfLdcCurrCtrRefMaxCal             = 170.0f;       // 0.5 /( 0.03 * 50k) //30ms
//
//
////LdcOutVolt
//float gfLdcOutVoltPIKpCal              = 30.;
//float gfLdcOutVoltPIKiCal              = 25000.;
//float gfLdcOutVoltPIKaCal              = 1 / 30.;
//float gfLdcOutVoltPIOutMaxCal          = 0.499f;
//float gfLdcOutVoltPIOutMinCal          = 0.;
//float gfLdcOutVoltCtrCmdCal            = 13.9f;  // 0.5 /( 0.03 * 50k) //30ms
//
//float gfLdcSrPwmOffCmpCal              = 20.0;
//
//float gfVLdcOutSSGainCal            = 0.9;
//float gfVLdcOutCmdRateLimitCal      = 15.1/500;     // 50ms
//Uint16 giVLdcOutSoftStart_TimerCal  = 100;			// 1x100ms
//float gfVLdcOutRefMaxCal            = 15.1;
//float gfVLdcOutRefMinCal            = 0.0;
//float gfVLdcOutCmdSSMinCal          = 12.5;
//
//
////ObcOutVolt
//float gfObcOutVoltPIKpCal           = 0.02;
//float gfObcOutVoltPIKiCal           = 40.0;
//float gfObcOutVoltPIKaCal           = 1. / 0.02;
//float gfVObcOutRefCal               = 828.;
//float gfIObcOutCmdCal               = 5.0;
//
//float gfxDataVDcDcOutCal[4]         = {440.,520.,650.,828.};
//float gfyDataIObcOutRefMaxCal[4]    = {21.15, 21.15, 16.93, 13.3};
//float gf1diRefMaxGenDataCntCal      = 4  ;
//float gfIObcOutRefMaxRateLimitCal   = 21.15 / 200;  //20ms


/*============================================================================
    Private Variables/Constants
============================================================================*/

/*============================================================================
    Function Prototypes
============================================================================*/

/*============================================================================
    Function Implementations
============================================================================*/


