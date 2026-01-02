/*
 * AswMain.h
 *
 *  Created on: 2023. 1. 4.
 *      Author: poweryhs
 */

#ifndef ASW_BACKUP_ASWCAL_H_
#define ASW_BACKUP_ASWCAL_H_

/*============================================================================
    Includes
============================================================================*/
#include <ASW_backup/AswCommon.h>
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
extern float gfVPfcDcLinkSSGainCal;
extern Uint16 giVPfcSoftStart_TimerCal;     //100 * 1ms

//(KEJ) PLL PI
extern float gfGridPLLKpCal;
extern float gfGridPLLKiCal;
extern float gfGridPLLFF;

//(KEJ) PFC DcLinkV PI
extern float gfPfcDcLinkVoltPIKpCal;
extern float gfPfcDcLinkVoltPIKiCal;
extern float gfPfcDcLinkVoltPIKpMinCal;
extern float gfPfcDcLinkVoltPIKiMinCal;
extern float gfPfcDcLinkVoltPIOutMax;
extern float gfPfcDcLinkVoltPIOutMin;
extern float gfVPfcDcLinkRefMaxCal;
extern float gfVPfcDcLinkRefMinCal;
extern float gfDrPfcDcLinkVoltBsf;

//(KEJ) PFC DcLinkV Err Rate limiter
extern float gfVPfcDcLinkCmdRateLimitCal;

//(KEJ) PFC Curr PI
extern float gfPfcCurrPIKpCal;
extern float gfPfcCurrPIKiCal;
extern float gfPfcCurrPIKpMaxCal;
extern float gfPfcCurrPIKiMaxCal;
extern float gfPfcCurrPIOutMax;
extern float gfPfcCurrPIOutMin;

//extern float gfCurr_HiFlt_Cal[CurrSnsrNum];
//extern float gfVolt_HiFlt_Cal[CurrSnsrNum];
//extern float gfVolt_LowInhibit_Cal[CurrSnsrNum];
//
//extern float gfLdcCurrPIKpCal;
//extern float gfLdcCurrPIKiCal;
//extern float gfLdcCurrPIKaCal;
//extern float gfLdcCurrPIOutMaxCal;
//extern float gfLdcCurrPIOutMinCal;
//extern float gfLdcCurrPIOutSSCal;
//extern float gfLdcCurrCtrRefMaxCal;
//
//extern float gfLdcOutVoltPIKpCal;
//extern float gfLdcOutVoltPIKiCal;
//extern float gfLdcOutVoltPIKaCal;
//extern float gfLdcOutVoltPIOutMaxCal;
//extern float gfLdcOutVoltPIOutMinCal;
//extern float gfLdcOutVoltCtrCmdCal;
//
//extern float gfLdcSrPwmOffCmpCal;
//
//extern float gfVLdcOutCmdRateLimitCal;
//extern float gfVLdcOutSSGainCal;
//extern Uint16 giVLdcOutSoftStart_TimerCal;
//extern float gfVLdcOutRefMaxCal;
//extern float gfVLdcOutRefMinCal;
//extern float gfVLdcOutCmdSSMinCal;
//
//extern float gfObcOutVoltPIKpCal;
//extern float gfObcOutVoltPIKiCal;
//extern float gfObcOutVoltPIKaCal;
//extern float gfVObcOutRefCal;
//extern float gfIObcOutCmdCal;
//
//extern float gfxDataVDcDcOutCal[4];
//extern float gfyDataIObcOutRefMaxCal[4];
//extern float gf1diRefMaxGenDataCntCal;
//extern float gfIObcOutRefMaxRateLimitCal;

/*============================================================================
    Private Variables/Constants
============================================================================*/

/*============================================================================
    Function Prototypes
============================================================================*/

#endif /* ASW_M0_MAIN_ASWMAIN_H_ */
