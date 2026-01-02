#ifndef _FDIAGCAL_H
#define _FDIAGCAL_H

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
//Sensor diag
extern float gfAdcSnsrVoltHiFltCal;
extern float gfAdcSnsrVoltLoFltCal;

//Current sensor diagnosis
extern Uint16 giCurrSnsr_VoltHiFlt_TimerCal;
extern Uint16 giCurrSnsr_VoltLoFlt_TimerCal;
extern Uint16 giCurrSnsr_RationalFlt_TimerCal;
extern float gfCurrSnsr_RationalFlt_Cal[CurrSnsrNum];

//Current diagnosis
extern Uint16 giCurr_Oc_Resume_TimeCal;
extern Uint16 giCurr_HwOc_HealCnt_TimerCal;
extern float gfIccuCurr_CurrHiFlt_Cal[CurrSnsrNum];
extern Uint16 giCurr_Oc_count_MaxDTCCal;

//Volt sensor diag
extern Uint16 giVoltSnsr_VoltHiFlt_TimerCal;
extern Uint16 giVoltSnsr_VoltLoFlt_TimerCal;
extern Uint16 giVoltSnsr_RationalFlt_TimerCal;
extern float gfVoltSnsr_RationalFlt_Cal[VoltSnsrNum];

//Volt diag
extern float gfVolt_VoltHiFlt_Cal[VoltSnsrNum];
extern float gfVolt_VoltLowFlt_Cal[VoltSnsrNum];
extern Uint16 giVolt_Ov_TimerCal;
extern Uint16 giVolt_Ov_count_MaxDTCCal;
extern Uint16 giVolt_Ov_HealCnt_TimerCal;
extern Uint16 giVolt_Uv_TimerCal;

//BatVolt sensor diagnosis
extern Uint16 giAuxBatVoltSnsr_VoltHiFlt_TimerCal;
extern Uint16 giAuxBatVoltSnsr_VoltLoFlt_TimerCal;
extern Uint16 giAuxBatVoltSnsr_RationalFlt_TimerCal;
extern float gfAuxBatVoltSnsr_RationalFlt_Cal;

//BatVolt diag
extern float gfAuxBatVolt_VoltHiFlt_Cal;
extern float gfAuxBatVolt_VoltLowFlt_Cal;
extern float gfAuxBatVolt_VoltHiFltClr_Cal;
extern float gfAuxBatVolt_VoltLowFltClr_Cal; 
extern Uint16 giAuxBatVolt_SwOv_TimerCal;
extern Uint16 giAuxBatVolt_SwUv_TimerCal;

//Smpsvolt sensor diag
extern Uint16 giSmpsVoltSnsr_VoltHiFlt_TimerCal;	
extern Uint16 giSmpsVoltSnsr_VoltLoFlt_TimerCal;	
extern Uint16 giSmpsVoltSnsr_RationalFlt_TimerCal;	
extern float gfSmpsVoltSnsr_RationalFlt_Cal;	

//Smpsvolt diag;
extern float gfSmpsVolt_VoltHiFlt_Cal;	
extern float gfSmpsVolt_VoltLowFlt_Cal;	
extern float gfSmpsVolt_VoltHiFltClr_Cal;	
extern float gfSmpsVolt_VoltLowFltClr_Cal;	
extern Uint16 giSmpsVolt_SwOv_TimerCal;	
extern Uint16 giSmpsVolt_SwUv_TimerCal;

//IgVolt snsr diag
extern Uint16 giIgVoltSnsr_VoltHiFlt_TimerCal;
extern Uint16 giIgVoltSnsr_VoltLowFlt_TimerCal;
extern Uint16 giIgVoltSnsr_RationalFlt_TimerCal;
extern float gfIgVoltSnsr_RationalFlt_Cal;

//Ig diag
extern float gfIgVolt_ON_Cal;
extern float gfIgVolt_OFF_Cal;
extern float gfIgVolt_SwOv_Cal;
extern float gfIgVolt_SwOvClr_Cal;
extern Uint16 giIgVolt_OFF_TimerCal;
extern Uint16 giIg_SwOv_Flt_Timer_Cal;

//Temp Snsr diag
extern Uint16 giTempSnsr_VoltHiFlt_TimerCal;
extern Uint16 giTempSnsr_VoltLoFlt_TimerCal;

//Temp diag
extern float gfTempHighDrtOnCal;
extern float gfTempHighOnCal;
extern float gfTempHighDrtOffCal;
extern Uint16 giTempHigh_TimerCal;

//Derating Diag
extern float gfVGridDrtStateOnCal;
extern float gfVGridDrtStateOffCal;

//InvoltHighInhibit
extern Uint16 giInVoltHighInhibitCntCal;
extern float gfGridVoltHighInhibitHysCal;

//Gate Diag
extern Uint16 giGate_Flt_TimerCal;
extern Uint16 giGate_Flt_count_MaxDTCCal;
extern Uint16 giGate_NotRdy_TimerCal;
extern Uint16 giGate_HwScp_HealCnt_TimerCal;

//Rly diag
extern float gfVRly_ON_RatioCal;
extern Uint16 giChMode_RlyOn_TimerCal;
extern Uint16 giDisChMode_RlyOn_TimerCal;

//CurrCtrState
extern float gfCurrCtrFltCal[CurrCtrNum];
extern Uint16 giCurrCtrFltTimerCal[CurrCtrNum];

extern float gfPfcLCurrCtrFltCal;
extern Uint16 giPfcLCurrCtrFltTimerCal;
extern float gfDcDcOutCurrCtrFltCal;
extern Uint16 gIDcDcOutCurrCtrFltTimerCal;


//PLLCtr diag
extern float gfGridPLL_Voltq_KCal;
extern float gfGridPLL_Voltd_Cal;
extern Uint16 giGridPLL_Normal_TimerCal;
extern Uint16 giGridPLL_CtrFlt_TimerCal;
extern Uint16 giGridPLL_Flt_TimerCal;
extern Uint8 giGridPLL_Flt_count_MaxDTCCal;
extern Uint8 giGridPLL_Flt_HealCnt_TimerCal;

//VoltCtrState
extern float gfDcLinkVoltCtrFltCal;
extern Uint16 giDcLinkVoltCtrFltTimerCal;
extern float gfOutVoltCtrFltCal;
extern Uint16 giOutVoltCtrFltTimerCal;
extern float gfV2LVoltCtrFltCal;
extern Uint16 giV2LVoltCtrFltTimerCal;


/*============================================================================
	Function Prototypes
============================================================================*/

#endif
