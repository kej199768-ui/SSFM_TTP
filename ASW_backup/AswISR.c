/*
 * AswMain.c
 *
 *  Created on: 2023. 1. 4.
 *      Author: poweryhs
 */


/*============================================================================
    Includes
============================================================================*/
#include <ASW_backup/AswISR.h>
#include <ASW_backup/AswSeq.h>
#include <ASW_backup/AswTask.h>
#include "math.h"
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
float  gfIObcLdc[CurrSnsrNum];
float  gfVObcLdc[CurrSnsrNum];
//Uint8 giInhibitTest;


//Current diag
CURR_STATE giCurrState[CurrSnsrNum] = { CURR_NORMAL, };
Uint16 giCurrFltFlag = 0;

//Input voltage diag
VOLT_STATE giVoltState[VoltSnsrNum] = { VOLT_NORMAL, };
Uint16 giVolt_Uv_Timer[VoltSnsrNum] = { 0, };
Uint16 giVoltFltFlag = 0;

//Ldc voltage control
PI_con gPiVLdcOut = PI_con_defaults;
float gfPiVLdcOut = 0.;
float gfVLdcOutRef = 0.;
Uint16 giVLdcOutSoftStart_Timer = 0;
VOLTCTR_STATE giLdcOutVoltCtrState = VOLTCTRSTATE_INHIBIT;


//Ldc current control
CURRCTR_STATE giLdcCurrCtrState;
PI_con gPiILdc = PI_con_defaults;
float gfLdcPwmDuty = 0.;
float gfLdcPwmPhase = 0.;
float gfLdcSrPwmDuty = 0.;
SR_STATE giSrMode = SRSTATE_SROFF;
float gfLdcCurrPIOutMax;                       // for SoftStart

Uint8 giFlag_ILdcCtrCpl_Delay = 0;
Uint8 giFlag_ILdcCtrCpl = 0;

LDCCTRMODE_STATE giLdcCtrModeState = LDC_INHIBIT;

/*============================================================================
    Private Variables/Constants
============================================================================*/

/*============================================================================
    Function Prototypes
============================================================================*/

/*============================================================================
    Function Implementations
============================================================================*/

/*----------------------------------------------------------------------------
	Func : ADC 센싱
	Period : ISR
	Parameter : 
----------------------------------------------------------------------------*/

void MonAdcIsr()
{
    gfIObcLdc[0] = ItrCom_GetCurr(0);
    gfVObcLdc[0] = ItrCom_GetVolt(0);
#ifdef DefInhibitTest
//       giInhibitTest = ItrCom_GetTestInhibit();
#endif
}


/*----------------------------------------------------------------------------
	Func : 전류 SW 고장 진단
	Period : ISR
	Parameter : giCurrState
----------------------------------------------------------------------------*/
void FdiagChkIO_RunCurrSwFlt(Uint8 SnsrNum)
{
	float fIObcLdc = gfIObcLdc[SnsrNum];

	switch (giCurrState[SnsrNum])
	{
	case CURR_NORMAL:
		if (fIObcLdc > gfCurr_HiFlt_Cal[SnsrNum])
			
		{
			giCurrState[SnsrNum] = CURR_SWOC_FLT;
			Seq_SetInteralMainState(STAT_FAULT_STATE);
			ItrCom_DisablePfcPWM();
//			ItrCom_DisableObcPWM();		/* Fix : PWM OFF 함수*/
//			ItrCom_DisableSrPWM();		/* Fix : PWM OFF 함수*/
			giCurrFltFlag |= (0x0001 << SnsrNum);
		}
		break;
	case CURR_HWOC_WAITRESUME:
	case CURR_SWOC_WAITRESUME:
		break;
	case CURR_HWOC_FLT:
		break;
	case CURR_SWOC_FLT:
		break;
	default:
		giCurrState[SnsrNum] = CURR_NORMAL;
		break;
	}
}


/*----------------------------------------------------------------------------
	Func : 전압 SW 고장 진단
	Period : ISR
	Parameter : giVoltState
----------------------------------------------------------------------------*/
void FdiagChkIO_RunVoltSwFlt(Uint8 SnsrNum)
{
	float fVObcLdc = gfVObcLdc[SnsrNum];

	switch (giVoltState[SnsrNum])
	{
	case VOLT_NORMAL:
		if(fVObcLdc > gfVolt_HiFlt_Cal[SnsrNum])
		{
			giVoltState[SnsrNum] = VOLT_SWOV_FLT;
			Seq_SetInteralMainState(STAT_FAULT_STATE);
			ItrCom_DisablePfcPWM();
//			ItrCom_DisableObcPWM();		/* Fix : PWM OFF 함수*/
//			ItrCom_DisableSrPWM();		/* Fix : PWM OFF 함수*/
			giVoltFltFlag |= (0x0001 << SnsrNum);
		}
#ifndef DefDisableVoltUVInhibit
		else if(fVObcLdc < gfVolt_LowInhibit_Cal[SnsrNum])
		{
			giVoltState[SnsrNum] = VOLT_UV_INHIBIT;
			ItrCom_DisableObcPWM();		/* Fix : PWM OFF 함수*/
			ItrCom_DisableSrPWM();		/* Fix : PWM OFF 함수*/
		}
#endif
		break;
	case VOLT_HWOV_FLT:
	case VOLT_SWOV_FLT:
		break;
	case VOLT_UV_INHIBIT:
		break;
	default:
		break;
	}
}

/*----------------------------------------------------------------------------
    Func : LDC 출력 전압 제어기
    Period : Isr
    Parameter :
----------------------------------------------------------------------------*/
void CtrLdcOutVolt()
{
    float fVLdcOut = ItrCom_GetVolt(VoltSnsrLdcOut);
    //  float fVGrid_Rms        = MonApi_GetGridVoltRms();
    float Ts_VLdcOut = Ts50k;
    float fVLdcOutCmd = 0.0;
    float fVLdcOutRefErr = 0.0;
    float fVLdcOutRef = gfVLdcOutRef;

    // 개발 필요
//  fVLdcOutCmd = fVOut + gfVLdcOutCmdOffsetCal;
    fVLdcOutCmd = gfLdcOutVoltCtrCmdCal;
    //  fVLdcOutCmd = LIMIT_MIN(fVLdcOutCmd, gfVLdcOutRefMinCal);

    switch (giLdcOutVoltCtrState)
    {
    case VOLTCTRSTATE_INHIBIT:
        gPiVLdcOut.Kp = gfLdcOutVoltPIKpCal;
        gPiVLdcOut.Ki = gfLdcOutVoltPIKiCal;
        gPiVLdcOut.Ka = gfLdcOutVoltPIKaCal;
        gPiVLdcOut.OutMax = gfLdcOutVoltPIOutMaxCal;
        gPiVLdcOut.OutMin = gfLdcOutVoltPIOutMinCal;
        gPiVLdcOut.Integ = 0.0;
        gPiVLdcOut.out = 0.0;
        gPiVLdcOut.Tsamp = Ts_VLdcOut;
        gfVLdcOutRef = fVLdcOut;
        if (Seq_GetInteralMainState() == STAT_NORMAL_STATE)
        {
            giLdcOutVoltCtrState = VOLTCTRSTATE_READY_SS;
        }
        giLdcCtrModeState = LDC_INHIBIT;
        break;

    case VOLTCTRSTATE_READY_SS:
        if ((fVLdcOut > gfVLdcOutCmdSSMinCal)
            && (fVLdcOut > gfVLdcOutSSGainCal * fVLdcOut)
            )
        {
            TIMER_TICK(giVLdcOutSoftStart_Timer);
            if (giVLdcOutSoftStart_Timer > giVLdcOutSoftStart_TimerCal)
            {
                TIMER_RESET(giVLdcOutSoftStart_Timer);
                giLdcOutVoltCtrState = VOLTCTRSTATE_NORMAL;
            }
        }
        else
        {
            TIMER_RESET(giVLdcOutSoftStart_Timer);
        }

    case VOLTCTRSTATE_NORMAL:
        if (Seq_GetInteralMainState() != STAT_NORMAL_STATE)
        {
            giLdcOutVoltCtrState = VOLTCTRSTATE_INHIBIT;
            break;
        }

        //전압지령 Rate Limit
        fVLdcOutRefErr = fVLdcOutCmd - fVLdcOutRef;

        if (fVLdcOutRefErr > gfVLdcOutCmdRateLimitCal)
        {
            fVLdcOutRef += gfVLdcOutCmdRateLimitCal;
        }
        else if (fVLdcOutRefErr < -gfVLdcOutCmdRateLimitCal)
        {
            fVLdcOutRef -= gfVLdcOutCmdRateLimitCal;
        }
        else
        {
            fVLdcOutRef = fVLdcOutCmd;
        }

        gfVLdcOutRef = LIMIT_MAX(fVLdcOutRef, gfVLdcOutRefMaxCal);
        gfVLdcOutRef = LIMIT_MIN(fVLdcOutRef, gfVLdcOutRefMinCal);

        //Calculate the outer loop PI controller using Trapezoidal Rule
        gPiVLdcOut.Kp = 0.0f;
        gPiVLdcOut.Ki = 30.0f;
        gPiVLdcOut.Ka = 0.0f;
        gPiVLdcOut.OutMax = gfLdcOutVoltPIOutMaxCal;

        gPiVLdcOut.Ref = gfVLdcOutRef;
        gPiVLdcOut.Fdb = fVLdcOut;
        PI_Control_calc(&gPiVLdcOut);

        break;
    case VOLTCTRSTATE_FLT:
        break;
    default:
        break;
    }
}



/*----------------------------------------------------------------------------
	Func : Ldc 전류 제어기
	Period : Isr
	Parameter : gPiILdc
----------------------------------------------------------------------------*/
void CtrLdcCurr(void)
{
	float Ts_ILdcCtr = Ts66k;
	float fILdc = 0.f;
	fILdc = gfIObcLdc[CurrSnsrLdcOut];
 
	switch (giLdcCurrCtrState)
	{
	case CURRCTRSTATE_INHIBIT:
		gPiILdc.Kp			= gfLdcCurrPIKpCal;
		gPiILdc.Ki			= gfLdcCurrPIKiCal;
		gPiILdc.Ka			= gfLdcCurrPIKaCal;
		gPiILdc.OutMax		= gfLdcCurrPIOutMaxCal;
		gPiILdc.OutMin		= gfLdcCurrPIOutMinCal;
		gPiILdc.FF			= 0.0;
		gPiILdc.Integ		= 0.0;
		gPiILdc.Tsamp		= Ts_ILdcCtr;
		giFlag_ILdcCtrCpl	= FALSE;
		giFlag_ILdcCtrCpl_Delay = FALSE;
		gfLdcPwmPhase		= 0.;
		gfLdcCurrPIOutMax	= 0.0;
		ItrCom_DisablePfcPWM();
//		ItrCom_DisableObcPWM();		/* Fix : PWM OFF 함수*/
//		ItrCom_DisableSrPWM();		/* Fix : PWM OFF 함수*/
		if (Seq_GetInteralMainState() == STAT_NORMAL_STATE)
		{
			giLdcCurrCtrState = CURRCTRSTATE_READY_SS;
		}
		break;
	case CURRCTRSTATE_READY_SS:
	case CURRCTRSTATE_NORMAL:
		if (Seq_GetInteralMainState() != STAT_NORMAL_STATE)
		{
			giLdcCurrCtrState = CURRCTRSTATE_INHIBIT;
			ItrCom_DisablePfcPWM();
//			ItrCom_DisableObcPWM();		/* Fix : PWM OFF 함수*/
//			ItrCom_DisableSrPWM();		/* Fix : PWM OFF 함수*/
			break;
		}

		gPiILdc.Kp = 0.00025;
		gPiILdc.Ki = 1.3;
		gPiILdc.Ka = 1 / 0.00025;

		gPiILdc.Ref = gfLdcCurrCtrRefMaxCal;
		gPiILdc.Fdb = fILdc;
        gPiILdc.FF = 0.0;
		gPiILdc.OutMax = gfLdcCurrPIOutMax;

		PI_Control_calc(&gPiILdc);

        if (gPiVLdcOut.out < gPiILdc.out)
        {
            gfLdcPwmDuty = gPiILdc.out = gPiVLdcOut.out;
            giLdcCtrModeState = LDC_CVCTR;

        }
        else
        {
            gfLdcPwmDuty = gPiVLdcOut.Integ = gPiILdc.out;
            giLdcCtrModeState = LDC_CCCTR;
        }

		gfLdcPwmPhase = 0.5 - gfLdcPwmDuty;
		//ItrCom_SetPwmPhase(1, gfLdcPwmPhase);				//Primary lagging

/*
		if (fILdc < 50.)
		{
			giSrMode = SRSTATE_SRANDING1;
		}
		else
		{
			giSrMode = SRSTATE_SRSLEADING;
		}
*/
		//giSrMode = SRSTATE_SROFF;


		switch(giSrMode)
		{
			case SRSTATE_SROFF:				
				gfLdcSrPwmDuty = 0.;
				//ItrCom_SetSrPwmduty(gfLdcSrPwmDuty);
				//ItrCom_SetPwmPhase(3, 0.);
				//ItrCom_SetPwmPhase(4, 0.5);
				break;
			case SRSTATE_SRANDING:				//SLead & SLag
				gfLdcSrPwmDuty = gfLdcPwmDuty - gfLdcSrPwmOffCmpCal;
				gfLdcSrPwmDuty = LIMIT_MIN(gfLdcSrPwmDuty, 0.0);
				//ItrCom_SetSrPwmduty(gfLdcSrPwmDuty);
				//ItrCom_SetPwmPhase(3, 0.);
				//ItrCom_SetPwmPhase(4, 0.5);
				break;
			case SRSTATE_SRORING:				//SLag | SLead
				gfLdcSrPwmDuty = 0.5 + gfLdcPwmPhase  - gfLdcSrPwmOffCmpCal;
				gfLdcSrPwmDuty = LIMIT_MIN(gfLdcSrPwmDuty, 0.0);
				//ItrCom_SetSrPwmduty(gfLdcSrPwmDuty);
				//ItrCom_SetPwmPhase(3, gfLdcPwmPhase);
				//ItrCom_SetPwmPhase(4, gfLdcPwmPhase + 0.5);
				break;
			case SRSTATE_SRSLEADING:
				gfLdcSrPwmDuty = 0.5 - gfLdcSrPwmOffCmpCal;					
				gfLdcSrPwmDuty = LIMIT_MIN(gfLdcSrPwmDuty, 0.0);
				//ItrCom_SetSrPwmduty(gfLdcSrPwmDuty);
				//ItrCom_SetPwmPhase(3, gfLdcPwmPhase);
				//ItrCom_SetPwmPhase(4, gfLdcPwmPhase + 0.5);
				break;
			default :
				gfLdcSrPwmDuty = 0.;					
				//ItrCom_SetPwmPhase(3, 0.);
				//ItrCom_SetPwmPhase(4, 0.);
				break;
		}
		break;

	case CURRCTRSTATE_FLT:
		break;
	default:
		break;
	}
}



CURR_STATE FdiagChkIO_GetCurrState(Uint8 SnsrNum){	return giCurrState[SnsrNum];}
CURRCTR_STATE Ctr_GetLdcCurrCtrState() { return giLdcCurrCtrState; }

VOLT_STATE FdiagChkIO_GetVoltState(Uint8 SnsrNum){	return giVoltState[SnsrNum];}
