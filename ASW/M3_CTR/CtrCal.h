#ifndef ASW_M3_CTR_CTRCAL_H
#define ASW_M3_CTR_CTRCAL_H

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
//PFCState
extern float gfVPfcDcLinkSSGainCal;
extern Uint16 giVPfcSoftStart_TimerCal;		//100 * 1ms

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

extern float gfISRTS;

//extern float gfGridPLLKpCal;
//extern float gfGridPLLKiCal;
//extern float gfGridPLLFF;
//
//extern Uint16 giPartCalcCplCntCal;
//
//extern float gfVPfcDcLinkCmdRateLimitCal;
//extern float gfVPfcDcLinkRefMaxCal;
//extern float gfVPfcDcLinkRefMinCal;
//extern float gfVPfcDcLinkCmdOffsetCal;
//extern float gfVPfcDcLinkCmdKCal;
//extern float gfVoMaxCal;
//
//extern Uint16 gf1dIDcDcCmdLimitCntCal;
//extern float gfxDataVGridRmsCal[5];
//extern float gfyDataIDcDcCmdGainCal[5];
//
//extern Uint16 gf1dTempDrtCntCal;
//extern float gfxDataDrtTempCal[2];
//extern float gfyDataDrtCurrCal[2];
//
//
//extern float gfGridVoltPIKpCal;
//extern float gfGridVoltPIKiCal;
//extern float gfGridVoltPIKaCal;
//			   
//extern float gfPfcDcLinkVoltPIKpCal;
//extern float gfPfcDcLinkVoltPIKiCal;
//extern float gfPfcDcLinkVoltPIKpMinCal;
//extern float gfPfcDcLinkVoltPIKiMinCal;
//extern float gfPfcDcLinkVoltPIOutMax;
//extern float gfPfcDcLinkVoltPIOutMin;
//extern float gfFrePfcDcLinkVoltLpf;
//extern float gfFrePfcDcLinkVoltBsf;
//extern float gfDrPfcDcLinkVoltBsf;
//
//extern float gfPfcCurrPIKpCal;
//extern float gfPfcCurrPIKiCal;
//extern float gfPfcCurrPIKpMaxCal;
//extern float gfPfcCurrPIKiMaxCal;
//extern float gfPfcCurrPIOutMax;
//extern float gfPfcCurrPIOutMin;
//
//extern float gfDdeadCal;
//extern float gfBoostDutyMaxCal;
//
////PFCState
//extern float gfVPfcDcLinkSSGainCal;
//extern Uint16 giVPfcSoftStart_TimerCal;
//
////V2L Ctr
//extern float gfV2LVoltRmsRefCal;
//extern float gfV2LVoltFreqRefCal;
//extern float gfVV2LCmdRateLimitCal;
//extern float gfVV2LCmdCal; 
//extern float gfVV2LRefMaxCal;
//extern float gfVV2LCmdMinCal;
//extern float gfVV2LSSGainCal;
//extern float giVV2LSoftStart_TimerCal;
//extern float gfPV2GCmdCal;
//extern float gfPV2GCmdRateLimitCal;
//extern float gfPV2GRefMaxCal;
//extern float gfVV2XDcLinkCmdMinCal;
//extern float gfVV2XDcLinkSSGainCal;
//extern Uint16 giVV2XDcDcSoftStart_TimerCal;
//
////DCDC Volt Ctr
//extern float gfGridEmiRCal;
//extern Uint16 gf1diRefMaxGenDataCntCal;
//extern float gfxDataVDcDcOutCal[4];
//extern float gfyDataiDcDcRefMaxCal[4];
//extern float gfIDcDcOutRefMaxRateLimitCal;
//
//extern float gfVDcDcOutCmdCal;
//extern float gfVDcDcCtrKpCal;
//extern float gfVDcDcCtrKiCal;
//extern float gfVDcDcCtrKaCal;
//
////DCDC LinkVolt Ctr
//extern float gfVV2XDcLinkCmdOffsetCal;
//extern float gfVV2XDcLinkCmdKCal;
//extern float gfVV2XDcLinkRefMinCal;
//extern float gfV2XDcLinkVoltPIKpCal;
//extern float gfV2XDcLinkVoltPIKiCal;
//extern float gfV2XDcLinkVoltPIKpMinCal;
//extern float gfV2XDcLinkVoltPIKiMinCal;
//extern float gfV2XDcLinkVoltPIOutMax;
//extern float gfV2XDcLinkVoltPIOutMin;
//extern float gffV2XDcLinkVoltLpfCal;
//extern float gfDrV2XDcLinkVoltBsfCal;
//extern float gfVV2XDcLinkCmdMinCal;
//extern float gfVV2XDcLinkSSGainCal;
//extern Uint16 giVV2XDcDcSoftStart_TimerCal;
//extern float gfVV2XDcLinkCmdRateLimitCal;
//extern float gfVV2XDcLinkRefMaxCal;
//
////DCDC Curr Ctr
//extern float gfIDcDcCtrKpCal;
//extern float gfIDcDcCtrKiCal;
//extern float gfIDcDcCtrKaCal;
//
//extern float gfIDcDcOutCtrTbCntCal;
//extern float gfIDcDcOutCtrTbCntFFCal;
//extern float gfDcDcSrPwmOnCurrCal;
//extern float gfDcDcSrPwmOffCurrCal;
//
//extern float gfxDataRoCal[9];
//extern float gfyDataNormalVCal[6];
//extern float gf2DtableDataCurrCtrOutCal[6][9];
//
//extern Uint8 gixDataCurrCtrFFNumCal;
//extern Uint8 giyDataCurrCtrFFNumCal;

/*============================================================================
	Function Prototypes
============================================================================*/

#endif
