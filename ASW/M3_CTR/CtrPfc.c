/*============================================================================
	Includes
============================================================================*/
#include "CtrMain.h"
#include "CtrPfc.h"
#include "CtrCal.h"
#include "CtrApi.h"
#include "../M0_MAIN/AswMainApi.h"
#include "../M1_SEQ/SeqApi.h"
#include "../M2_MON/MonApi.h"
#include "../M4_FDIAG/FdiagApi.h"
#include "../M6_COM/ComApi.h"
#include <math.h>

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
//Grid PLL
dq	gdqVgrid_dqs				= dq_defaults;
filter1 gfVgrid_LPF             = filter1_defaults;
filter2 gf2Vgrid_qs_APF			= filter2_defaults;
filter1 gf1Vgrid_ds_APF         = filter1_defaults;
float gfVGrid_BPF				= 0.0f;
filter2 gf2Vgrid_BPF			= filter2_defaults;
dq gdqVgrid_dqe					= dq_defaults;
filter1 gf1Vgrid_de_LPF			= filter1_defaults;
filter1 gf1Vgrid_qe_LPF			= filter1_defaults;
dq gdqVgrid_dqe_LPF				= dq_defaults;
PI_con gPiVgrid_angle			= PI_con_defaults;

float gfWgrid					= 377.f;
float gfWgrid_LPF				= 377.f;
filter1 gf1Wgrid_LPF			= filter1_defaults;
float gfTheta_Grid				= 0.0f;
float gfTheta_Grid_Comp			= 0.0f;
float gfThetaDeg_Grid			= 0.0f;
float gfVGrid_Mag				= SQRT2 * 220.f;
float gfVGrid_Mag_LPF			= SQRT2 * 220.f;
filter1 gf1VGrid_Mag_LPF		= filter1_defaults;
float gffgrid					= 0.0f;
float gffgrid_LPF				= 0.0f;


Uint16 giPartCalcCplCnt			= 0U;

//float gfWgrid_PC				= 0.0f;
//float gfGridAngleKp				= 0.0f;
//float gfGridAngleKi				= 0.0f;
//float gfGridAngleFF				= 0.0f;

//Half Cycle Detection
Uint8 giflag_PosCycle			= 0U;
Uint8 giflag_NegCycle			= 0U;
Uint8 giPos_dead_cnt			= 0U;
Uint8 giFlag_HSSW_Deadzone		= 0U;
Uint8 giFlag_LSSW_Deadzone		= 0U;
Uint8 giNeg_dead_cnt			= 0U;

//Voltage Control
float gfVPfcDcLinkCmd           = 0.0f;
PI_con gPiVPfcDcLink			= PI_con_defaults;
TPOZ_con gTpozVPfcDcLink        = TPOZ_con_defaults;
filter1 gf1VPfcDcLinkLpf		= filter1_defaults;
float gfVPfcDcLinkLpf			= 0.0f;
filter2 gf2VPfcDcLinkBsf		= filter2_defaults;
float gfVPfcDcLinkFilter		= 0.0f;
float gfVPfcDcLinkRef			= 0.0f;
float gfIGridRef				= 0.0f;
float gfIPfcLRef				= 0.0f;
Uint16 giVPfcSoftStart_Timer	= 0U;

//current control
PI_con gPiIPfcL[CurrPfcSnsrNum] = { PI_con_defaults , };
Uint8 giFlag_IPfcLCtrlCpl_Delay = 0U;
Uint8 giFlag_IPfcLCtrlCpl		= 0U;
float gfPosDitheringDuty        = 0.05f;
float gfNegDitheringDuty        = 0.95f;

//V2X control
float gffV2L					= 0.0f;
float gfWV2L					= 0.0f;
float gfTheta_V2L				= 0.0f;
float gfThetaDeg_V2L			= 0.0f;
float gfVV2LRef					= 0.0f;
PI_con gPiVV2Lde				= PI_con_defaults;
PI_con gPiVV2Lqe				= PI_con_defaults;
dq gdqVV2L_dqe					= dq_defaults;
dq gdqVV2L_dqs					= dq_defaults;
float gfPV2GRef					= 0.0;
Uint16 giVV2LSoftStart_Timer	= 0.0;

Uint16 guHS_en    = 0;
Uint16 guLS_en    = 0;
float gfHS_duty   = 0;
float gfLS_duty   = 0;

Uint16 giPLL_inhibit = 0;
Uint16 giPwmTest_inhibit = 0;
Uint16 giIController_inhibit = 0;
Uint16 giController_inhibit = 0;
Uint16 giTest_type = 0;    //DC - 1, AC - 0
float  gfIin_ref_test = 0.;




/*============================================================================
	Private Variables/Constants
============================================================================*/

/*============================================================================
	Function Prototypes
============================================================================*/
void CtrPfcGridPLL(void);
void CtrPfcHalfCycleDet(void);
void CtrPfcDcLinkVoltCtr(void);
//void CtrV2LPfcVoltCtr(void);
void CtrPfcCurrCtr(void);
//void CtrV2GPfcCurrCtr(void);
void CtrPfcPwmTest(void);
void CtrDisPwm(void);

/*============================================================================
	Function Implementations
============================================================================*/
void CtrPfcIsrCtr(void) {
	ICCUMODE_STATE iIccuModeState = FdiagApi_GetIccuModeState();
	if (iIccuModeState == ICCUMODE_CHARGING)
	{
	    if (giIController_inhibit == 1 || giController_inhibit == 1)
	    {
	        CtrPfcCurrCtr();
	    }
	    else if (giPwmTest_inhibit == 1)
	    {
	        CtrPfcPwmTest();
	    }
	    else
	    {
	        CtrDisPwm();
	    }

	}
	else if (iIccuModeState == ICCUMODE_V2L)
	{
		//CtrV2LPfcVoltCtr();
	}
	else if (iIccuModeState == ICCUMODE_V2G)
	{
		/*CtrPfcGridPLL();
		CtrPfcHalfCycleDet();
		CtrV2GPfcCurrCtr();*/
	}
}

void CtrPfcTask100us(void) {
    if (giPLL_inhibit == 1)
          {
              CtrPfcGridPLL();
              CtrPfcHalfCycleDet();
          }

}

void CtrPfcTask1ms(void) {
	ICCUMODE_STATE iIccuModeState = FdiagApi_GetIccuModeState();
	if (iIccuModeState == ICCUMODE_CHARGING)
	{
	    if (giController_inhibit == 1)
	    {
	        CtrPfcDcLinkVoltCtr();
	    }
	}
}

void CtrPfcTask10ms(void) {}

void CtrPfcTask100ms(void) {}


/*----------------------------------------------------------------------------
	Func :입력전압 PLL
	Period : 50us ISR
	Parameter : gfThetaGrid
----------------------------------------------------------------------------*/
void CtrPfcGridPLL(void)
{
    if (giTest_type == 0)
    {
	float Tsamp_gridPLL = Ts10k;
	float fVGrid = MonApi_GetVolt(VoltSnsrGrid);
	float fVGrid_LPF1 = LPF1(Tsamp_gridPLL, 1000.f, fVGrid, &gfVgrid_LPF);
	float ffgrid = 0.0f;
	ICCUVOLTSNSR_STATE iIccuVoltSnsrState = FdiagApi_GetVoltSnsrState(VoltSnsrGrid);
	VOLTCTRSTATE iGridPllState = FdiagApi_GetGridPllCtrState();
	
	switch (iGridPllState)
	{
	case VOLTCTRSTATE_INHIBIT:

		//Adaptive gain control
		gPiVgrid_angle.OutMax = 86.4f * PI2;       //72 * 1.2;	
		gPiVgrid_angle.OutMin = 32.0f * PI2;       //40 * 0.8;
		gPiVgrid_angle.Tsamp = Tsamp_gridPLL;
		gPiVgrid_angle.Integ = 0.0f;
		//gPiVgrid_angle.FF = gfGridPLLFF;
		//gPiVgrid_angle.Ref = 0.0f;

		if (iIccuVoltSnsrState == ICCUVOLTSNSR_NORMAL)
		{
			FdiagApi_ChangeGridPllState(VOLTCTRSTATE_READY_SS);
		}
		break;

	case VOLTCTRSTATE_READY_SS:
	case VOLTCTRSTATE_NORMAL:
		if (iIccuVoltSnsrState != ICCUVOLTSNSR_NORMAL)
		{
			FdiagApi_ChangeGridPllState(VOLTCTRSTATE_INHIBIT);
			break;
		}

		gdqVgrid_dqs.d = fVGrid;
		gdqVgrid_dqs.q = - APF1(Tsamp_gridPLL, gffgrid, gdqVgrid_dqs.d, &gf1Vgrid_ds_APF);

		gdqVgrid_dqe = park_calc(&gdqVgrid_dqs, gfTheta_Grid_Comp);

		gPiVgrid_angle.Kp = gfGridPLLKpCal / gfVGrid_Mag;
		gPiVgrid_angle.Ki = gfGridPLLKiCal / gfVGrid_Mag;
		gPiVgrid_angle.Ka = 1.0f / gPiVgrid_angle.Kp;

		gPiVgrid_angle.Fdb = gdqVgrid_dqe.d;
		PI_Control_calc(&gPiVgrid_angle);

		gfWgrid = gPiVgrid_angle.out;

		gfTheta_Grid += gfWgrid * Tsamp_gridPLL;
		gfTheta_Grid_Comp = gfTheta_Grid + gfWgrid * Tsamp_gridPLL;

        if (gfTheta_Grid > PI)  {   gfTheta_Grid -= PI2;    }
        if (gfTheta_Grid < -PI) {   gfTheta_Grid +- PI2;    }
        if (gfTheta_Grid_Comp > PI)  {   gfTheta_Grid_Comp -= PI2;    }
        if (gfTheta_Grid_Comp < -PI) {   gfTheta_Grid_Comp +- PI2;    }

        gffgrid = gfWgrid * INVPI2;
        if (gffgrid > 86.4f) gffgrid = 86.4f;
        else if (gffgrid < 32.0f) gffgrid = 32.0f;

		gfThetaDeg_Grid = gfTheta_Grid_Comp * INVPI180;

        gfVGrid_Mag = sqrtf(powf(gdqVgrid_dqs.d, 2.0f) + powf(gdqVgrid_dqs.q, 2.0f));
        gfVGrid_Mag_LPF = LPF1(Tsamp_gridPLL, gffgrid, gfVGrid_Mag, &gf1VGrid_Mag_LPF);
        gdqVgrid_dqe_LPF.d = LPF1(Tsamp_gridPLL, 30.0f, gdqVgrid_dqe.d, &gf1Vgrid_de_LPF);
        gdqVgrid_dqe_LPF.q = LPF1(Tsamp_gridPLL, 30.0f, gdqVgrid_dqe.q, &gf1Vgrid_qe_LPF);
        gfVGrid_BPF = BPF2(Tsamp_gridPLL, gffgrid, 20.f, fVGrid, &gf2Vgrid_BPF);           // BPF2(float Tsamp, float fc, float band, double in, filter2 *out)

		break;
	case VOLTCTRSTATE_FLT:
		break;
	default:
		break;
	}
    }
    else if (giTest_type == 1)
    {
        float Tsamp_gridPLL = Ts10k;
        float fVGrid = MonApi_GetVolt(VoltSnsrGrid);
        ICCUVOLTSNSR_STATE iIccuVoltSnsrState = FdiagApi_GetVoltSnsrState(VoltSnsrGrid);

        if (iIccuVoltSnsrState == ICCUVOLTSNSR_NORMAL)
        {
            gfVGrid_Mag     = fVGrid;
            gfVGrid_Mag_LPF = LPF1(Tsamp_gridPLL, 10.0f, fVGrid, &gf1VGrid_Mag_LPF);
            FdiagApi_ChangeGridPllState(VOLTCTRSTATE_NORMAL);
        }
    }
}

/*----------------------------------------------------------------------------
	Func :입력전압 half cycle detection
	Period : 50us
	Parameter : 
----------------------------------------------------------------------------*/
void CtrPfcHalfCycleDet(void) 
{


    if (giTest_type == 0)
    {
        //------------------------------DeadBand start 지점, HSSW Disable----------------------------
        if ((gfThetaDeg_Grid >= -176.0f) && (gfThetaDeg_Grid < -5.0f))
        {
            giflag_PosCycle = TRUE;
            giflag_NegCycle = FALSE;
            if (gfThetaDeg_Grid <= -173.0f)
            {
                giFlag_HSSW_Deadzone = FALSE;
                giFlag_LSSW_Deadzone = TRUE;
            }
            else
            {
                giFlag_HSSW_Deadzone = FALSE;
                giFlag_LSSW_Deadzone = FALSE;
            }
        }
        else if ((gfThetaDeg_Grid >= 4.0f) && (gfThetaDeg_Grid < 175.0f))
        {
            giflag_PosCycle = FALSE;
            giflag_NegCycle = TRUE;
            if (gfThetaDeg_Grid <= 7.f)
            {
                giFlag_HSSW_Deadzone = FALSE;
                giFlag_LSSW_Deadzone = TRUE;
            }
            else
            {
                giFlag_HSSW_Deadzone = FALSE;
                giFlag_LSSW_Deadzone = FALSE;
            }
        }
        else
        {
            giflag_PosCycle = FALSE;
            giflag_NegCycle = FALSE;
            giFlag_HSSW_Deadzone = TRUE;
            giFlag_LSSW_Deadzone = TRUE;
        }
    }
    else if (giTest_type == 1)
    {
        giflag_PosCycle = TRUE;
        giflag_NegCycle = FALSE;
        giFlag_LSSW_Deadzone = FALSE;
        giFlag_HSSW_Deadzone = FALSE;
    }
}


/*----------------------------------------------------------------------------
	Func : PFC단 DCLink 전압 제어기
	Period : 1ms
	Parameter : 
----------------------------------------------------------------------------*/
void CtrPfcDcLinkVoltCtr()
{
	float fVPfcDcLink		= MonApi_GetVolt(VoltSnsrDCLink);
	fVPfcDcLink             = LIMIT_MIN(fVPfcDcLink, 100.0f);
	float fVGrid			= MonApi_GetVolt(VoltSnsrGrid);
	float fVOut				= MonApi_GetVolt(VoltSnsrOut);
	//float fIDcDcOutRef		= CtrApi_GetIDcDcOutRef();
	float fVGrid_Mag		= gfVGrid_Mag;
	float Ts_VoPfcDcLink	= Ts1k;
	float fVPfcDcLinkCmd	= gfVPfcDcLinkCmd;
	float fVPfcDcLinkRefErr	= 0.0f;
	float fVPfcDcLinkRef	= gfVPfcDcLinkRef;
	VOLTCTRSTATE iPfcDcLinkVoltCtrState = FdiagApi_GetPfcDcLinkVoltCtrState();

	//PFC DCLink 전압 목표 설정
	fVPfcDcLinkCmd = LIMIT_MIN(fVPfcDcLinkCmd, gfVPfcDcLinkRefMinCal);
	fVPfcDcLinkCmd = LIMIT_MAX(fVPfcDcLinkCmd, gfVPfcDcLinkRefMaxCal);

	if (giTest_type == 0)
	{
//	    gfVPfcDcLinkFilter = BSF2(Ts1k, gffgrid*2.0f,gfDrPfcDcLinkVoltBsf, fVPfcDcLink, &gf2VPfcDcLinkBsf);
//	    gfVPfcDcLinkFilter = LPF1(Ts1k, 40.f, fVPfcDcLink, &gf2VPfcDcLinkBsf);
	    gfVPfcDcLinkFilter = fVPfcDcLink;
	}
	else if (giTest_type == 1)  {   gfVPfcDcLinkFilter = BSF2(Ts1k, 100.f,gfDrPfcDcLinkVoltBsf, fVPfcDcLink, &gf2VPfcDcLinkBsf);     }


#ifdef DefAdaptiveGainControl
//	gPiVPfcDcLink.Kp = gfPfcDcLinkVoltPIKpCal * gfVPfcDcLinkFilter;
//	gPiVPfcDcLink.Kp = LIMIT_MIN(gPiVPfcDcLink.Kp, gfPfcDcLinkVoltPIKpMinCal);	//출력전압 0V 인 경우, gain 무한대로 하한치 지정
//	gPiVPfcDcLink.Ki = gfPfcDcLinkVoltPIKiCal * gfVPfcDcLinkFilter;
//	gPiVPfcDcLink.Ki = LIMIT_MIN(gPiVPfcDcLink.Ki, gfPfcDcLinkVoltPIKiMinCal);
//	gPiVPfcDcLink.Ka = 1.0f / gPiVPfcDcLink.Kp;

	gTpozVPfcDcLink.Kp = 3009.5;
	gTpozVPfcDcLink.Wz = 19.8;
	gTpozVPfcDcLink.Wp = 176.3;
	gTpozVPfcDcLink.Ka = 1.0f / gTpozVPfcDcLink.Kp;

#else
	gPiVPfcDcLink.Kp = gfPfcDcLinkVoltPIKpCal * 650.0f;
	gPiVPfcDcLink.Ki = gfOutVoltPIKiCal * 650.0f;
	gPiVPfcDcLink.Ka = 1.0f / gfOutVoltPI.Kp;
#endif

	switch (iPfcDcLinkVoltCtrState)
	{
	case VOLTCTRSTATE_INHIBIT:
//		gPiVPfcDcLink.OutMax = gfPfcDcLinkVoltPIOutMax;
//		gPiVPfcDcLink.OutMin = gfPfcDcLinkVoltPIOutMin;
//		gPiVPfcDcLink.Integ = 0.0f;
//		gPiVPfcDcLink.Tsamp = Ts_VoPfcDcLink;

	    gTpozVPfcDcLink.OutMax = gfPfcDcLinkVoltPIOutMax;
	    gTpozVPfcDcLink.OutMin = gfPfcDcLinkVoltPIOutMin;
	    gTpozVPfcDcLink.Tsamp = Ts_VoPfcDcLink;

		gfVPfcDcLinkRef = fVPfcDcLink;
		gfIPfcLRef = 0.0f;
		if ((SeqApi_GetInternalMainState() == STAT_NORMAL_STATE) && (FdiagApi_GetRlyState() == RLY_ON))
		{
			FdiagApi_ChangePfcDcLinkVoltCtrState(VOLTCTRSTATE_READY_SS);
		}

		break;
	case VOLTCTRSTATE_READY_SS:
		if (fVPfcDcLink > gfVPfcDcLinkSSGainCal * fVGrid_Mag)
		{
			TIMER_TICK(giVPfcSoftStart_Timer);
			if (giVPfcSoftStart_Timer > giVPfcSoftStart_TimerCal)
			{
				TIMER_RESET(giVPfcSoftStart_Timer);
				FdiagApi_ChangePfcDcLinkVoltCtrState(VOLTCTRSTATE_NORMAL);
			}
		}
		else
		{
			TIMER_RESET(giVPfcSoftStart_Timer);
		}
		break;
	case VOLTCTRSTATE_NORMAL:
		if ((SeqApi_GetInternalMainState() != STAT_NORMAL_STATE) || (FdiagApi_GetRlyState() != RLY_ON))
		{
			FdiagApi_ChangePfcDcLinkVoltCtrState(VOLTCTRSTATE_INHIBIT);
			break;
		}
		//전압지령 Rate Limit
		fVPfcDcLinkRefErr = fVPfcDcLinkCmd - fVPfcDcLinkRef;

		if (fVPfcDcLinkRefErr > gfVPfcDcLinkCmdRateLimitCal)
		{
			fVPfcDcLinkRef += gfVPfcDcLinkCmdRateLimitCal;
		}
		else if (fVPfcDcLinkRefErr < -gfVPfcDcLinkCmdRateLimitCal)
		{
			fVPfcDcLinkRef -= gfVPfcDcLinkCmdRateLimitCal;
		}
		else
		{
			fVPfcDcLinkRef = fVPfcDcLinkCmd;
		}
		gfVPfcDcLinkRef = fVPfcDcLinkRef;
		gfVPfcDcLinkRef = LIMIT_MAX(fVPfcDcLinkRef, gfVPfcDcLinkRefMaxCal);
		gfVPfcDcLinkRef = LIMIT_MIN(fVPfcDcLinkRef, gfVPfcDcLinkRefMinCal);
	
//		gPiVPfcDcLink.Ref = gfVPfcDcLinkRef;
//		gPiVPfcDcLink.Fdb = gfVPfcDcLinkFilter;
		gTpozVPfcDcLink.Ref = gfVPfcDcLinkRef;
		gTpozVPfcDcLink.Fdb = gfVPfcDcLinkFilter;

		
//		PI_Control_calc(&gPiVPfcDcLink);
		TPOZ_Control_calc(&gTpozVPfcDcLink);

		break;
	case VOLTCTRSTATE_FLT:
		break;
	default:
		break;
	}

}


/*----------------------------------------------------------------------------
	Func : PFC단 전류 제어기
	Period : 50us
	Parameter : gPiIIccu
----------------------------------------------------------------------------*/
void CtrPfcCurrCtr()
{
	float fVPfcDcLink = MonApi_GetVolt(VoltSnsrDCLink);
	fVPfcDcLink = LIMIT_MIN(fVPfcDcLink, 100.0f);

	float fVGrid = MonApi_GetVolt(VoltSnsrGrid);
	float Ts_ILCtr = ISRTS;
	float fIPfcL[CurrPfcSnsrNum] = { 0.0f, };
	float fVGrid_Rms = 0;
	if (giTest_type == 0)       { fVGrid_Rms = gfVGrid_Mag_LPF * INVSqrt2; }  //AC
	else if (giTest_type == 1)  { fVGrid_Rms = gfVGrid_Mag_LPF; }             //DC


	CURRCTRSTATE iCurrCtrState = FdiagApi_GetPfcCurrCtrState();
	float fVGridPfcIn = 0.0f;
	float fInvVDcLink = 1.0f / fVPfcDcLink;
	float fInCurrPIKp = 0.f;
	float fInCurrPIKi = 0.f;
	float fInCurrPIKa = 0.f;

	/*float fPV2GRefErr = 0.0f;
	float fPV2GCmd = gfPV2GCmdCal;
	float fPV2GRef = gfPV2GRef;*/

	fIPfcL[CurrSnsrPhase] = MonApi_GetCurr(CurrSnsrPhase);

#ifdef DefAdaptiveGainControl
	fInCurrPIKp = gfPfcCurrPIKpCal * fInvVDcLink;
	fInCurrPIKp = LIMIT_MAX(fInCurrPIKp, gfPfcCurrPIKpMaxCal);
	fInCurrPIKi = gfPfcCurrPIKiCal * fInvVDcLink;
	fInCurrPIKi = LIMIT_MAX(fInCurrPIKi, gfPfcCurrPIKiMaxCal);
	fInCurrPIKa = 1.0f / fInCurrPIKp;
	
#else
	fInCurrPIKp = gfPfcCurrPIKpCal / 650.0f;
	fInCurrPIKi = gfPfcCurrPIKiCal / 650.0f;
	fInCurrPIKa = 1.0f / fInCurrPIKp;
#endif

	switch (iCurrCtrState)
	{
	case CURRCTRSTATE_INHIBIT:
		gPiIPfcL[CurrSnsrPhase].OutMax	= gfPfcCurrPIOutMax;
		gPiIPfcL[CurrSnsrPhase].OutMin	= gfPfcCurrPIOutMin;
		gPiIPfcL[CurrSnsrPhase].Integ	= 0.0f;
		gPiIPfcL[CurrSnsrPhase].Tsamp	= Ts_ILCtr;
		
		giFlag_IPfcLCtrlCpl = FALSE;
		giFlag_IPfcLCtrlCpl_Delay = FALSE;

		//API_PFC_EMIOS_STOP();     //simulation
		ItrCom_DisablePfcPWM();

//		API_GPIO_PE_HS_PWM_A_EN(CLEAR);
//		API_GPIO_PE_LS_PWM_A_EN(CLEAR);
		ItrCom_SetPfcPwmduty(1, TRUE, 0);       //high speed switch
        ItrCom_PfcLSSw_DeadBand();

		gfPV2GRef = 0.0f;

		//FdiagApi_ChagePfcCurrCtrState(CURRCTRSTATE_NORMAL);   //simulation
		if ((SeqApi_GetInternalMainState() == STAT_NORMAL_STATE) && (FdiagApi_GetRlyState() == RLY_ON) /*&& (FdiagApi_GetPfcDcLinkVoltCtrState() == VOLTCTRSTATE_NORMAL)*/)
        {
            FdiagApi_ChagePfcCurrCtrState(CURRCTRSTATE_NORMAL);
        }


		break;
	case CURRCTRSTATE_NORMAL:
		if ((SeqApi_GetInternalMainState() != STAT_NORMAL_STATE) || (FdiagApi_GetRlyState() != RLY_ON) /*|| (FdiagApi_GetPfcDcLinkVoltCtrState() == VOLTCTRSTATE_NORMAL)*/)
		{
			FdiagApi_ChagePfcCurrCtrState(CURRCTRSTATE_INHIBIT);
			ItrCom_DisablePfcPWM();
			break;
		}
		
		//Calculate gfVoPFCltage reference
		/*gfIGridRef = (gPiVPfcDcLink.out) * fVGrid / (fVGrid_Rms * fVGrid_Rms);
		gfIGridRef = (gPiVPfcDcLink.out) / (INVSqrt2 * gfVGrid_Mag * INVSqrt2) * sinf(gfTheta_Grid + PI * 0.5f);*/

		if (giTest_type == 0)   //AC
		{
		    if (giIController_inhibit == 1)
		    {
//	            gfIGridRef = gfIin_ref_test * gfVGrid_BPF / (fVGrid_Rms * fVGrid_Rms);
		        gfIGridRef = gfIin_ref_test;
		    }
		    else
		    {
//		        gfIGridRef = (gPiVPfcDcLink.out) * gfVGrid_BPF / (fVGrid_Rms * fVGrid_Rms);
                gfIGridRef = (gTpozVPfcDcLink.out) * gfVGrid_BPF / (fVGrid_Rms * fVGrid_Rms);
		    }
		    gfIPfcLRef = gfIGridRef;
		}
		else if (giTest_type == 1)  //DC
		{
		    if (giIController_inhibit == 1)
		    {
		        //gfIGridRef = gfPin_ref_test / gfVGrid_Mag_LPF;
		        gfIGridRef = gfIin_ref_test;
		    }
		    else
		    {
//		        gfIGridRef = gPiVPfcDcLink.out / gfVGrid_Mag_LPF;
                gfIGridRef = gTpozVPfcDcLink.out / gfVGrid_Mag_LPF;
		    }
		    gfIPfcLRef = gfIGridRef;
		}

		//EMI필터단 저항에 따른 전압 drop 보상
		//fVGridPfcIn = fVGrid - gfGridEmiRCal * gfIGridRef;
		fVGridPfcIn = fVGrid;
		
		if ((giFlag_HSSW_Deadzone == FALSE)	&& (giflag_PosCycle == TRUE))		//PosCycle
		{
			if (giFlag_LSSW_Deadzone == TRUE)
			{
//				ItrCom_PfcHSPwmPosDitheringMode();
//				ItrCom_EnablePfcHSPWM();
				ItrCom_PfcLSSw_DeadBand();
				giFlag_IPfcLCtrlCpl = FALSE;
			}
			else
			{
				gPiIPfcL[CurrSnsrPhase].Kp = fInCurrPIKp;
				gPiIPfcL[CurrSnsrPhase].Ki = fInCurrPIKi;
				gPiIPfcL[CurrSnsrPhase].Ka = fInCurrPIKa;

				gPiIPfcL[CurrSnsrPhase].Ref	= gfIPfcLRef;
				gPiIPfcL[CurrSnsrPhase].Fdb	= fIPfcL[CurrSnsrPhase];
				gPiIPfcL[CurrSnsrPhase].FF	= 1.0f - (fVGridPfcIn * fInvVDcLink);
				
				PI_Control_calc(&gPiIPfcL[CurrSnsrPhase]);

				ItrCom_SetPfcPwmduty(1, TRUE, gPiIPfcL[CurrSnsrPhase].out);
				giFlag_IPfcLCtrlCpl = TRUE;

			}
			if (giFlag_IPfcLCtrlCpl_Delay == TRUE)      //Positive cycle
			{

			    ItrCom_PfcHSPwmNormalMode();
			    //Low speed switch control
			    ItrCom_PfcLSSw_PosEn();
                //PWM Enable
                ItrCom_EnablePfcHSPWM();
			}
            giFlag_IPfcLCtrlCpl_Delay = giFlag_IPfcLCtrlCpl;

		}
		else if ((giFlag_HSSW_Deadzone == FALSE) && (giflag_NegCycle == TRUE))		//NegCycle
		{
			if (giFlag_LSSW_Deadzone == TRUE)
			{
//                ItrCom_PfcHSPwmNegDitheringMode();
//                ItrCom_EnablePfcHSPWM();
                ItrCom_PfcLSSw_DeadBand();
                giFlag_IPfcLCtrlCpl = FALSE;
			}
			else
			{
				gPiIPfcL[CurrSnsrPhase].Kp = fInCurrPIKp;
				gPiIPfcL[CurrSnsrPhase].Ki = fInCurrPIKi;
				gPiIPfcL[CurrSnsrPhase].Ka = fInCurrPIKa;

				gPiIPfcL[CurrSnsrPhase].Ref	= gfIPfcLRef;
				gPiIPfcL[CurrSnsrPhase].Fdb	= fIPfcL[CurrSnsrPhase];
				gPiIPfcL[CurrSnsrPhase].FF	= (-fVGridPfcIn * fInvVDcLink);
				
				PI_Control_calc(&gPiIPfcL[CurrSnsrPhase]);

				ItrCom_SetPfcPwmduty(1, TRUE, gPiIPfcL[CurrSnsrPhase].out);
				
				giFlag_IPfcLCtrlCpl = TRUE;
			}
			if (giFlag_IPfcLCtrlCpl_Delay == TRUE)
			{
			    ItrCom_PfcHSPwmNormalMode();
			    //Low speed switch control
                ItrCom_PfcLSSw_NegEn();
                //PWM Enable
                ItrCom_EnablePfcHSPWM();
			}
            giFlag_IPfcLCtrlCpl_Delay = giFlag_IPfcLCtrlCpl;
		}
		else
		{
			gPiIPfcL[CurrSnsrPhase].Integ = 0.0f;
			giFlag_IPfcLCtrlCpl = FALSE;
			giFlag_IPfcLCtrlCpl_Delay = FALSE;

			ItrCom_DisablePfcHSPWM();
			ItrCom_PfcLSSw_DeadBand();

		}
		break;
	case CURRCTRSTATE_FLT:
		break;
	default:
		break;
	}
}

/*----------------------------------------------------------------------------
    Func : PWM output test
    Period : 50us
    Parameter : guHS_en, gfHS_duty, guLS_en, gfLS_duty
----------------------------------------------------------------------------*/
void CtrPfcPwmTest(void)
{
    if ((SeqApi_GetInternalMainState() == STAT_NORMAL_STATE) && (FdiagApi_GetRlyState() == RLY_ON))
    {
        if (giTest_type == 1)
        {
            ItrCom_PfcHSPwmNormalMode();
            ItrCom_SetPfcPwmduty(1, TRUE, gfHS_duty);
            ItrCom_EnablePfcHSPWM();
            ItrCom_PfcLSSw_PosEn();
        }
        else
        {
            ItrCom_DisablePfcHSPWM();
            ItrCom_PfcLSSw_DeadBand();
        }
    }
}

/*----------------------------------------------------------------------------
    Func : PWM output Disable
    Period : 50us
    Parameter : gPiVV2Lde,gPiVV2Lqe
----------------------------------------------------------------------------*/
void CtrDisPwm(void)
{
    ItrCom_DisablePfcPWM();
    ItrCom_PfcLSSw_DeadBand();
}

/*----------------------------------------------------------------------------
	Func : V2L PFC단 전압 제어기
	Period : 50us
	Parameter : gPiVV2Lde,gPiVV2Lqe
----------------------------------------------------------------------------*/
//void CtrV2LPfcVoltCtr(void)
//{
//	float fVDCLink = MonApi_GetVolt(VoltSnsrDCLink);
//	float fVGrid = MonApi_GetVolt(VoltSnsrGrid);
//	float fVV2L_qe_cmd = gfVV2LCmdCal;
//	float fVV2LqeRefErr = 0.0f;
//	float fVV2LqeRef = gfVV2LRef;
//	float Tsamp_V2LPLL = Ts20k;
//	float fInvVDcLink = 1.0f / fVDCLink;
//	VOLTCTRSTATE iV2LVoltCtrState = FdiagApi_GetV2LVoltCtrState();
//
//	gffV2L = gfV2LVoltFreqRefCal;
//	gfWV2L = gffV2L * PI2;
//
//	gdqVgrid_dqs.q = fVGrid;
//	gdqVgrid_dqs.d = APF2(Tsamp_V2LPLL, gffV2L, gdqVgrid_dqs.q, &gf2Vgrid_qs_APF); 
//
//	gfTheta_V2L += gfWV2L * Tsamp_V2LPLL;
//	if (gfTheta_V2L > PI)	gfTheta_V2L -= PI2;        
//	if (gfTheta_V2L < -PI)  gfTheta_V2L += PI2;
//
//	gfThetaDeg_V2L = gfTheta_V2L * INVPI180;
//
//	gdqVgrid_dqe = park_calc(&gdqVgrid_dqs, gfTheta_V2L);
//
//	switch (iV2LVoltCtrState)
//	{
//	case VOLTCTRSTATE_INHIBIT:
//		gPiVV2Lde.Kp = gPiVV2Lqe.Kp = 0.0f;
//		gPiVV2Lde.Ki = gPiVV2Lqe.Ki = PI2 * 20.0f;
//		gPiVV2Lqe.OutMax = 500.0f;
//		gPiVV2Lqe.OutMin = -500.0f;
//		gPiVV2Lde.OutMax = 375.0f;
//		gPiVV2Lde.OutMin = -375.0f;
//		gPiVV2Lde.Tsamp = gPiVV2Lqe.Tsamp = Tsamp_V2LPLL;
//		gPiVV2Lde.Integ = gPiVV2Lqe.Integ = 0.0f;
//		gfVV2LRef = 0.0f;
//
//		if ((SeqApi_GetInteralMainState() == STAT_NORMAL_STATE)
//			&& (FdiagApi_GetDcDcLinkVoltCtrState() == VOLTCTRSTATE_NORMAL)
//			&& (FdiagApi_GetRlyState() == RLY_ON)
//			)
//		{
//			FdiagApi_ChangeV2LVoltCtrState(VOLTCTRSTATE_READY_SS);
//		}
//
//		break;
//	
//	case VOLTCTRSTATE_READY_SS:
//		if ((gdqVgrid_dqe.q > gfVV2LCmdMinCal)
//			&& (gdqVgrid_dqe.q > gfVV2LSSGainCal * fVV2L_qe_cmd)
//			)
//		{
//			TIMER_TICK(giVV2LSoftStart_Timer);
//			if (giVV2LSoftStart_Timer > giVV2LSoftStart_TimerCal)
//			{
//				TIMER_RESET(giVV2LSoftStart_Timer);
//				FdiagApi_ChangeV2LVoltCtrState(VOLTCTRSTATE_NORMAL);
//			}
//		}
//		else
//		{
//			TIMER_RESET(giVV2LSoftStart_Timer);
//		}
//	case VOLTCTRSTATE_NORMAL:
//		if ((SeqApi_GetInteralMainState() != STAT_NORMAL_STATE)
//			|| (FdiagApi_GetDcDcLinkVoltCtrState() != VOLTCTRSTATE_NORMAL)
//			|| (FdiagApi_GetRlyState() != RLY_ON)
//			)
//		{
//			FdiagApi_ChangeV2LVoltCtrState(VOLTCTRSTATE_INHIBIT);
//		}
//
//		fVV2LqeRefErr = fVV2L_qe_cmd - fVV2LqeRef;
//
//		if (fVV2LqeRefErr > gfVV2LCmdRateLimitCal)
//		{
//			fVV2LqeRef += gfVV2LCmdRateLimitCal;
//		}
//		else if (fVV2LqeRefErr < -gfVV2LCmdRateLimitCal)
//		{
//			fVV2LqeRef -= gfVV2LCmdRateLimitCal;
//		}
//		else
//		{
//			fVV2LqeRef = fVV2L_qe_cmd;
//		}
//		
//		gfVV2LRef = LIMIT_MAX(fVV2LqeRef, gfVV2LRefMaxCal);
//		gfVV2LRef = LIMIT_MIN(fVV2LqeRef, 0);
//
//		gPiVV2Lde.Kp = gPiVV2Lqe.Kp = 0.0f;
//		gPiVV2Lde.Ki = gPiVV2Lqe.Ki = PI2 * 20.0f;
//
//		gPiVV2Lqe.Ref = gfVV2LRef;
//		gPiVV2Lqe.Fdb = gdqVgrid_dqe.q;
//		PI_Control_calc(&gPiVV2Lqe);
//
//		gPiVV2Lde.Ref = 0.0f;
//		gPiVV2Lde.Fdb = gdqVgrid_dqe.d;
//		PI_Control_calc(&gPiVV2Lde);
//
//		gdqVV2L_dqe.q = gPiVV2Lqe.out;
//		gdqVV2L_dqe.d = gPiVV2Lde.out;
//
//		gdqVV2L_dqs = ipark_calc(&gdqVV2L_dqe, gfTheta_V2L);
//
//		if ((gfThetaDeg_V2L >= -88) && (gfThetaDeg_V2L < 87))
//		{
//			giflag_PosCycle = TRUE;
//			giflag_NegCycle = FALSE;
//			if (gfThetaDeg_V2L <= -85)
//			{
//				giFlag_LSSW_Deadzone = TRUE;
//			}
//			else
//			{
//				giFlag_LSSW_Deadzone = FALSE;
//			}
//			giFlag_HSSW_Deadzone = FALSE;
//		}
//		else if ((gfThetaDeg_V2L >= 92) || (gfThetaDeg_V2L < -93))
//		{
//			giflag_PosCycle = FALSE;
//			giflag_NegCycle = TRUE;
//			if ((gfThetaDeg_V2L <= 95) && (gfThetaDeg_V2L >= 87))
//			{
//				giFlag_LSSW_Deadzone = TRUE;
//			}
//			else
//			{
//				giFlag_LSSW_Deadzone = FALSE;
//			}
//			giFlag_HSSW_Deadzone = FALSE;
//		}
//		else
//		{
//			giflag_PosCycle = FALSE;
//			giflag_NegCycle = FALSE;
//			giFlag_HSSW_Deadzone = TRUE;
//			giFlag_LSSW_Deadzone = TRUE;
//		}
//
//		if ((giFlag_HSSW_Deadzone == FALSE)
//			&& (giflag_PosCycle == TRUE)
//			)
//		{
//			if (giFlag_LSSW_Deadzone == TRUE)
//			{
//				API_PFC_EMIOSA_DUTY(0.05, HIGH, TRUE);
//				API_PFC_EMIOSB_DUTY(0.05, HIGH, TRUE);
//				API_GPIO_PE_HS_PWM_A_EN(CLEAR);
//				API_GPIO_PE_LS_PWM_A_EN(CLEAR);
//				giFlag_IPfcLCtrlCpl = FALSE;
//			}
//			else
//			{
//				giFlag_IPfcLCtrlCpl = TRUE;
//				API_PFC_EMIOSA_DUTY(1.0 - (gdqVV2L_dqs.q * fInvVDcLink), HIGH, FALSE);
//				API_PFC_EMIOSB_DUTY(1.0 - (gdqVV2L_dqs.q * fInvVDcLink), HIGH, FALSE);
//			}
//			giFlag_IPfcLCtrlCpl_Delay = giFlag_IPfcLCtrlCpl;
//
//			if (giFlag_IPfcLCtrlCpl_Delay == TRUE)
//			{
//				API_PFC_EMIOS_RUN();
//				API_GPIO_PE_HS_PWM_A_EN(CLEAR);
//				API_GPIO_PE_LS_PWM_A_EN(SET);
//			}
//		}
//		else if ((giFlag_HSSW_Deadzone == FALSE)
//			&& (giflag_NegCycle == TRUE)
//			)
//		{
//			if (giFlag_LSSW_Deadzone == TRUE)
//			{
//				API_PFC_EMIOSA_DUTY(0.05, LOW, TRUE);
//				API_PFC_EMIOSB_DUTY(0.05, LOW, TRUE);
//				API_GPIO_PE_HS_PWM_A_EN(CLEAR);
//				API_GPIO_PE_LS_PWM_A_EN(CLEAR);
//				giFlag_IPfcLCtrlCpl = FALSE;
//			}
//			else
//			{
//				giFlag_IPfcLCtrlCpl = TRUE;
//				API_PFC_EMIOSA_DUTY(1.0 + (gdqVV2L_dqs.q * fInvVDcLink), LOW, FALSE);
//				API_PFC_EMIOSB_DUTY(1.0 + (gdqVV2L_dqs.q * fInvVDcLink), LOW, FALSE);
//			}
//			giFlag_IPfcLCtrlCpl_Delay = giFlag_IPfcLCtrlCpl;
//			
//			if (giFlag_IPfcLCtrlCpl_Delay == TRUE) {
//				API_PFC_EMIOS_RUN();
//				API_GPIO_PE_HS_PWM_A_EN(SET);
//				API_GPIO_PE_LS_PWM_A_EN(CLEAR);
//			}
//		}
//		else
//		{
//			giFlag_IPfcLCtrlCpl = FALSE;
//			giFlag_IPfcLCtrlCpl_Delay = FALSE;
//			API_PFC_EMIOS_STOP();
//			API_GPIO_PE_HS_PWM_A_EN(CLEAR);
//			API_GPIO_PE_LS_PWM_A_EN(CLEAR);
//		}
//		break;
//	case VOLTCTRSTATE_FLT:
//		break;
//	default:
//		break;
//	}
//
//	//DA3 = FdiagApi_GetRlyState();
//	//DA4 = FdiagApi_GetDcDcLinkVoltCtrState();
//	//DA5 = gdqVV2L_dqe.q;
//	//DA6 = gdqVV2L_dqe.d;
//	//DA7 = gdqVV2L_dqs.q;
//	//DA8 = gdqVV2L_dqs.d;
//	//DA9 = giflag_PosCycle;
//	//DA10 = iV2LVoltCtrState;
//	
//}

/*----------------------------------------------------------------------------
	Func : V2G PFC단 전류 제어기
	Period : 50us
	Parameter : gPiIIccu
----------------------------------------------------------------------------*/
//void CtrV2GPfcCurrCtr(void)
//{
//	float fVDcLink = MonApi_GetVolt(VoltSnsrDCLink);
//	float fVGrid = MonApi_GetVolt(VoltSnsrGrid);
//	float Ts_ILCtr = Ts20k;
//	float fIPfcL[CurrPfcSnsrNum] = { 0.0f, };
//	float fVGrid_Rms = gfVGrid_Mag_LPF * INVSqrt2;
//	CURRCTRSTATE iCurrCtrState = FdiagApi_GetPfcCurrCtrState();
//	float fVGridPfcIn = 0.0f;
//	float fInvVDcLink = 1.0f / fVDcLink;
//	float fInCurrPIKp = 0.f;
//	float fInCurrPIKi = 0.f;
//	float fInCurrPIKa = 0.f;
//	float fPV2GRefErr = 0.0f;
//	float fPV2GCmd = gfPV2GCmdCal;
//	float fPV2GRef = gfPV2GRef;
//
//
//
//	fIPfcL[CurrSnsrPhase1] = MonApi_GetCurr(CurrSnsrPhase1);
//	fIPfcL[CurrSnsrPhase2] = MonApi_GetCurr(CurrSnsrPhase2);
//
//
//#ifdef DefAdaptiveGainControl
//	fInCurrPIKp = gfPfcCurrPIKpCal * fInvVDcLink;
//	//	fInCurrPIKp = LIMIT_MAX(fInCurrPIKp, gfPfcCurrPIKpMaxCal);
//	fInCurrPIKi = gfPfcCurrPIKiCal * fInvVDcLink;
//	//	fInCurrPIKi = LIMIT_MAX(fInCurrPIKi, gfPfcCurrPIKiMaxCal);
//	fInCurrPIKa = 1.0f / fInCurrPIKp;
//#else
//	fInCurrPIKp = gfPfcCurrPIKpCal / 650.0f;
//	fInCurrPIKi = gfPfcCurrPIKiCal / 650.0f;
//	fInCurrPIKa = 1.0f / fInCurrPIKp;
//#endif
//
//	switch (iCurrCtrState)
//	{
//	case CURRCTRSTATE_INHIBIT:
//		gPiIPfcL[CurrSnsrPhase1].OutMax = gPiIPfcL[CurrSnsrPhase2].OutMax = gfPfcCurrPIOutMax;
//		gPiIPfcL[CurrSnsrPhase1].OutMin = gPiIPfcL[CurrSnsrPhase2].OutMin = gfPfcCurrPIOutMin;
//		gPiIPfcL[CurrSnsrPhase1].Integ = gPiIPfcL[CurrSnsrPhase2].Integ = 0.0f;
//		gPiIPfcL[CurrSnsrPhase1].Tsamp = gPiIPfcL[CurrSnsrPhase2].Tsamp = Ts_ILCtr;
//		giFlag_IPfcLCtrlCpl = FALSE;
//		giFlag_IPfcLCtrlCpl_Delay = FALSE;
//		//API_GPIO_PFC_PWM_EN(FALSE);
//		API_PFC_EMIOS_STOP();
//		API_GPIO_PE_HS_PWM_A_EN(CLEAR);
//		API_GPIO_PE_LS_PWM_A_EN(CLEAR);
//		gfPV2GRef = 0.0f;
//
//		if ((SeqApi_GetInteralMainState() == STAT_NORMAL_STATE)
//			&& (FdiagApi_GetRlyState() == RLY_ON)
//			&& (FdiagApi_GetDcDcLinkVoltCtrState() == VOLTCTRSTATE_NORMAL)
//			)
//		{
//			FdiagApi_ChagePfcCurrCtrState(CURRCTRSTATE_NORMAL);
//		}
//	break;
//	case CURRCTRSTATE_NORMAL:
//		if ((SeqApi_GetInteralMainState() != STAT_NORMAL_STATE)
//			|| (FdiagApi_GetRlyState() != RLY_ON)
//			|| (FdiagApi_GetDcDcLinkVoltCtrState() != VOLTCTRSTATE_NORMAL)
//			)
//		{
//			FdiagApi_ChagePfcCurrCtrState(CURRCTRSTATE_INHIBIT);
//			//API_GPIO_PFC_PWM_EN(FALSE);
//			API_PFC_EMIOS_STOP();
//			break;
//		}
//
//		//전력지령 Rate Limit
//		fPV2GRefErr = fPV2GCmd - fPV2GRef;
//
//		if (fPV2GRefErr > gfPV2GCmdRateLimitCal)
//		{
//			fPV2GRef += gfPV2GCmdRateLimitCal;
//		}
//		else if (fPV2GRefErr < -gfPV2GCmdRateLimitCal)
//		{
//			fPV2GRef -= gfPV2GCmdRateLimitCal;
//		}
//		else
//		{
//			fPV2GRef = fPV2GCmd;
//		}
//
//		gfPV2GRef = LIMIT_MAX(fPV2GRef, gfPV2GRefMaxCal);
//		gfPV2GRef = LIMIT_MIN(fPV2GRef, 0);
//
//		gfIGridRef = -1.0f * gfPV2GRef * gfVGrid_BPF / (fVGrid_Rms * fVGrid_Rms);
//		gfIPfcLRef = gfIGridRef * 0.5f;
//		//EMI필터단 저항에 따른 전압 drop 보상
//		//fVGridPfcIn = fVGrid - gfGridEmiRCal * gfIGridRef;
//		fVGridPfcIn = fVGrid;
//
//		if ((giFlag_HSSW_Deadzone == FALSE)
//			&& (giflag_PosCycle == TRUE)
//			)
//		{
//			if (giFlag_LSSW_Deadzone == TRUE)
//			{
//				API_PFC_EMIOSA_DUTY(0.05f, HIGH, TRUE);
//				API_PFC_EMIOSB_DUTY(0.05f, HIGH, TRUE);
//				API_GPIO_PE_HS_PWM_A_EN(CLEAR);
//				API_GPIO_PE_LS_PWM_A_EN(CLEAR);
//				giFlag_IPfcLCtrlCpl = FALSE;
//			}
//			else
//			{
//				gPiIPfcL[CurrSnsrPhase1].Kp = gPiIPfcL[CurrSnsrPhase2].Kp = fInCurrPIKp;
//				gPiIPfcL[CurrSnsrPhase1].Ki = gPiIPfcL[CurrSnsrPhase2].Ki = fInCurrPIKi;
//				gPiIPfcL[CurrSnsrPhase1].Ka = gPiIPfcL[CurrSnsrPhase2].Ka = fInCurrPIKa;
//
//				gPiIPfcL[CurrSnsrPhase1].Ref = gfIPfcLRef;
//				gPiIPfcL[CurrSnsrPhase1].Fdb = fIPfcL[CurrSnsrPhase1];
//				gPiIPfcL[CurrSnsrPhase1].FF = 1.0f - (fVGridPfcIn * fInvVDcLink);
//
//				PI_Control_calc(&gPiIPfcL[CurrSnsrPhase1]);
//				gPiIPfcL[CurrSnsrPhase2].Ref = gfIPfcLRef;
//				gPiIPfcL[CurrSnsrPhase2].Fdb = fIPfcL[CurrSnsrPhase2];
//				gPiIPfcL[CurrSnsrPhase2].FF = gPiIPfcL[CurrSnsrPhase1].FF;
//
//				PI_Control_calc(&gPiIPfcL[CurrSnsrPhase2]);
//				giFlag_IPfcLCtrlCpl = TRUE;
//
//				API_PFC_EMIOSA_DUTY(gPiIPfcL[CurrSnsrPhase1].out, HIGH, FALSE);
//				API_PFC_EMIOSB_DUTY(gPiIPfcL[CurrSnsrPhase2].out, HIGH, FALSE);
//			}
//			giFlag_IPfcLCtrlCpl_Delay = giFlag_IPfcLCtrlCpl;
//
//			if (giFlag_IPfcLCtrlCpl_Delay == TRUE)
//			{
//				API_PFC_EMIOS_RUN();
//				API_GPIO_PE_HS_PWM_A_EN(CLEAR);
//				API_GPIO_PE_LS_PWM_A_EN(SET);
//			}
//		}
//		else if ((giFlag_HSSW_Deadzone == FALSE)
//			&& (giflag_NegCycle == TRUE)
//			)
//		{
//			if (giFlag_LSSW_Deadzone == TRUE)
//			{
//				API_PFC_EMIOSA_DUTY(0.05, LOW, TRUE);
//				API_PFC_EMIOSB_DUTY(0.05, LOW, TRUE);
//				API_GPIO_PE_HS_PWM_A_EN(CLEAR);
//				API_GPIO_PE_LS_PWM_A_EN(CLEAR);
//				giFlag_IPfcLCtrlCpl = FALSE;
//			}
//			else
//			{
//				gPiIPfcL[CurrSnsrPhase1].Kp = gPiIPfcL[CurrSnsrPhase2].Kp = fInCurrPIKp;
//				gPiIPfcL[CurrSnsrPhase1].Ki = gPiIPfcL[CurrSnsrPhase2].Ki = fInCurrPIKi;
//				gPiIPfcL[CurrSnsrPhase1].Ka = gPiIPfcL[CurrSnsrPhase2].Ka = fInCurrPIKa;
//
//				gPiIPfcL[CurrSnsrPhase1].Ref = -gfIPfcLRef;
//				gPiIPfcL[CurrSnsrPhase1].Fdb = -fIPfcL[CurrSnsrPhase1];
//				gPiIPfcL[CurrSnsrPhase1].FF = 1.0f - (-fVGridPfcIn * fInvVDcLink);
//				PI_Control_calc(&gPiIPfcL[CurrSnsrPhase1]);
//
//				gPiIPfcL[CurrSnsrPhase2].Ref = -gfIPfcLRef;
//				gPiIPfcL[CurrSnsrPhase2].Fdb = -fIPfcL[CurrSnsrPhase2];
//				gPiIPfcL[CurrSnsrPhase2].FF = gPiIPfcL[CurrSnsrPhase1].FF;
//				PI_Control_calc(&gPiIPfcL[CurrSnsrPhase2]);
//
//				API_PFC_EMIOSA_DUTY(gPiIPfcL[CurrSnsrPhase1].out, LOW, FALSE);
//				API_PFC_EMIOSB_DUTY(gPiIPfcL[CurrSnsrPhase2].out, LOW, FALSE);
//
//				giFlag_IPfcLCtrlCpl = TRUE;
//			}
//			giFlag_IPfcLCtrlCpl_Delay = giFlag_IPfcLCtrlCpl;
//
//			if (giFlag_IPfcLCtrlCpl_Delay == TRUE) {
//				API_PFC_EMIOS_RUN();
//				API_GPIO_PE_HS_PWM_A_EN(SET);
//				API_GPIO_PE_LS_PWM_A_EN(CLEAR);
//			}
//		}
//		else
//		{
//			gPiIPfcL[CurrSnsrPhase1].Integ = 0.0f;
//			gPiIPfcL[CurrSnsrPhase2].Integ = 0.0f;
//			giFlag_IPfcLCtrlCpl = FALSE;
//			giFlag_IPfcLCtrlCpl_Delay = FALSE;
//			API_PFC_EMIOS_STOP();
//			API_GPIO_PE_HS_PWM_A_EN(CLEAR);
//			API_GPIO_PE_LS_PWM_A_EN(CLEAR);
//		}
//		break;
//	case CURRCTRSTATE_FLT:
//		break;
//	default:
//		break;
//	}
//}
