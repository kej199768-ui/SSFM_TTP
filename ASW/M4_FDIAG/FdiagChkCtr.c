/*============================================================================
	Includes
============================================================================*/
#include "FdiagChkCtr.h" 
#include "FdiagChkM.h"
#include "FdiagCal.h"
#include "FdiagApi.h"
#include "../M0_MAIN/AswMainApi.h"
#include "../M1_SEQ/SeqApi.h"
#include "../M2_MON/MonApi.h"
#include "../M3_CTR/CtrApi.h"

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
//PLL diag
Uint16 	giGridPLL_Normal_Timer = 0U;
Uint16 	giGridPLL_CtrFlt_Timer = 0U;
Uint16 	giGridPLL_Flt_Timer = 0U;
Uint8 giGridPLL_Flt_count = 0U;
Uint8 giGridPLL_Flt_HealCycle = 0U;
Uint8 giGridPLL_Flt_HealState = 0U;

//CtrState
CURRCTRSTATE giPfcLCurrCtrState			= CURRCTRSTATE_INHIBIT;
CURRCTRSTATE gIDcDcOutCurrCtrState		= CURRCTRSTATE_INHIBIT;

Uint16 giPfcLCurrCtrFltTimer			= 0U;
//Uint16 giPfcL1CurrCtrFltTimer			= 0U;
//Uint16 giPfcL2CurrCtrFltTimer			= 0U;
Uint16 gIDcDcOut1CurrCtrFltTimer		= 0U;
Uint16 gIDcDcOut2CurrCtrFltTimer		= 0U;

VOLTCTRSTATE giGridVoltCtrState			= VOLTCTRSTATE_INHIBIT;
VOLTCTRSTATE giPfcDcLinkVoltCtrState	= VOLTCTRSTATE_INHIBIT;
VOLTCTRSTATE giV2XDcLinkVoltCtrState	= VOLTCTRSTATE_INHIBIT;
VOLTCTRSTATE giOutVoltCtrState			= VOLTCTRSTATE_INHIBIT;
VOLTCTRSTATE giV2LVoltCtrState			= VOLTCTRSTATE_INHIBIT;

Uint16 giGridVoltCtrFltTimer			= 0U;
Uint16 giDcLinkVoltCtrFltTimer			= 0U;
Uint16 giOutVoltCtrFltTimer				= 0U;
Uint16 giV2LVoltCtrFltTimer				= 0U;

/*============================================================================
	Private Variables/Constants
============================================================================*/

/*============================================================================
	Function Prototypes
============================================================================*/
void FdiagChkCtr_RunPfcCurrCtrState(void);
void FdiagChkCtr_ChagePfcCurrCtrState(CURRCTRSTATE state);
void FdiagChkCtr_RunDcDcCurrCtrState(void);
void FdiagChkCtr_ChageDcDcCurrCtrState(CURRCTRSTATE state);


// Grid PLL Ctr
void FdiagChkCtr_RunGridPLLCtrState(void);
void FdiagChkCtr_ChangeGridPllState(VOLTCTRSTATE state);

// Volt Ctr
void FdiagChkCtr_RunPfcLinkVoltCtrState(void);
void FdiagChkCtr_ChagePfcLinkVoltCtrState(VOLTCTRSTATE state);
void FdiagChkCtr_RunV2XDcLinkVoltCtrState(void);
void FdiagChkCtr_ChageV2XDcLinkVoltCtrState(VOLTCTRSTATE state);
void FdiagChkCtr_RunOutVoltCtrState(void);
void FdiagChkCtr_ChageOutVoltCtrState(VOLTCTRSTATE state);
void FdiagChkCtr_RunV2LVoltCtrState(void);
void FdiagChkCtr_ChageV2LVoltCtrState(VOLTCTRSTATE state);



/*============================================================================
	Function Implementations
============================================================================*/
void FdiagChkCtrIsrCtr(void) {}
void FdiagChkCtrTask100us(void) {}
void FdiagChkCtrTask1ms(void) {
	FdiagChkCtr_RunGridPLLCtrState();
	//FdiagChkCtr_ChangeGridPllState(VOLTCTRSTATE_NORMAL);
}
void FdiagChkCtrTask10ms(void) {
	ICCUMODE_STATE iIccuModeState = FdiagChkFS_GetIccuModeState();

	FdiagChkCtr_RunPfcCurrCtrState();

	if (iIccuModeState == ICCUMODE_V2L)
	{
		FdiagChkCtr_RunV2XDcLinkVoltCtrState();
		FdiagChkCtr_RunV2LVoltCtrState();
	}
	else if (iIccuModeState == ICCUMODE_V2G)
	{
		FdiagChkCtr_RunV2XDcLinkVoltCtrState();
	}
	else
	{
		FdiagChkCtr_RunPfcLinkVoltCtrState();
		FdiagChkCtr_RunOutVoltCtrState();
	}
	FdiagChkCtr_RunDcDcCurrCtrState();

	//	FdiagChkCtr_ChagePfcCurrCtrState(CURRCTRSTATE_NORMAL);
	//	FdiagChkCtr_ChagePfcLinkVoltCtrState(VOLTCTRSTATE_NORMAL);

}
void FdiagChkCtrTask100ms(void) {

    FdiagChkCtr_GridPllFltHealCount();
}

/*----------------------------------------------------------------------------
	Func : PFC전류제어진단
	Period : 10ms
	Parameter : giPfcLCurrCtrState
----------------------------------------------------------------------------*/
void FdiagChkCtr_RunPfcCurrCtrState() {
	float fIPfcL[CurrPfcSnsrNum] = { 0.0f, };
	float fIPfcLRef = CtrApi_GetIPfcLRef();
	fIPfcL[CurrSnsrPhase] = MonApi_GetCurr(CurrSnsrPhase);
	//fIPfcL[CurrSnsrPhase] = MonApi_GetCurr(CurrSnsrPhase2);

	switch (giPfcLCurrCtrState)
	{
	case CURRCTRSTATE_INHIBIT:
		TIMER_RESET(giPfcLCurrCtrFltTimer);
		//TIMER_RESET(giPfcL1CurrCtrFltTimer);
		//TIMER_RESET(giPfcL2CurrCtrFltTimer);
		break;
	case CURRCTRSTATE_NORMAL:
		if (fabs(fIPfcLRef - fIPfcL[CurrSnsrPhase]) > gfPfcLCurrCtrFltCal)
		{
			TIMER_TICK(giPfcLCurrCtrFltTimer);
			if (giPfcLCurrCtrFltTimer > giPfcLCurrCtrFltTimerCal)
			{
				TIMER_RESET(giPfcLCurrCtrFltTimer);
				FdiagChkCtr_ChagePfcCurrCtrState(CURRCTRSTATE_FLT);
			}
		}
		else
		{
			TIMER_RESET(giPfcLCurrCtrFltTimer);
		}

		/*if (fabs(fIPfcLRef - fIPfcL[CurrSnsrPhase2]) > gfPfcLCurrCtrFltCal)
		{
			TIMER_TICK(giPfcL2CurrCtrFltTimer);
			if (giPfcL2CurrCtrFltTimer > giPfcLCurrCtrFltTimerCal)
			{
				TIMER_RESET(giPfcL2CurrCtrFltTimer);
				FdiagChkCtr_ChagePfcCurrCtrState(CURRCTRSTATE_FLT);
			}
		}
		else
		{
			TIMER_RESET(giPfcL2CurrCtrFltTimer);
		}*/


		break;
	case CURRCTRSTATE_FLT:
		TIMER_RESET(giPfcLCurrCtrFltTimer);
		//TIMER_RESET(giPfcL2CurrCtrFltTimer);
		break;
	default:
		break;
	}
}

/*----------------------------------------------------------------------------
	Func : PFC전류제어상태변경
	Period : 10ms
	Parameter : giPfcLCurrCtrState
----------------------------------------------------------------------------*/
void FdiagChkCtr_ChagePfcCurrCtrState(CURRCTRSTATE state) {
	giPfcLCurrCtrState = state;
}

/*----------------------------------------------------------------------------
	Func : DCDC전류제어진단
	Period : 10ms
	Parameter : giPfcLCurrCtrState
----------------------------------------------------------------------------*/
void FdiagChkCtr_RunDcDcCurrCtrState() {
	//float fIDcDcOut[CurrDcDcSnsrNum] = { 0.0f, };
	//float fIDcDcOutRef = CtrApi_GetIDcDcOutMRef();
	//fIDcDcOut[CurrSnsrPhase] = MonApi_GetCurr(CurrSnsrDcDcOut);
	////fIDcDcOut[CurrSnsrPhase2] = MonApi_GetCurr(CurrSnsrDcDcOut2);

	//switch (gIDcDcOutCurrCtrState)
	//{
	//case CURRCTRSTATE_INHIBIT:
	//	TIMER_RESET(gIDcDcOut1CurrCtrFltTimer);
	//	TIMER_RESET(gIDcDcOut2CurrCtrFltTimer);
	//	break;
	//case CURRCTRSTATE_NORMAL:
	//	if (fabs(fIDcDcOutRef - fIDcDcOut[CurrSnsrPhase1]) > gfPfcLCurrCtrFltCal)
	//	{
	//		TIMER_TICK(gIDcDcOut1CurrCtrFltTimer);
	//		if (gIDcDcOut1CurrCtrFltTimer > giPfcLCurrCtrFltTimerCal)
	//		{
	//			TIMER_RESET(gIDcDcOut1CurrCtrFltTimer);
	//			FdiagChkCtr_ChageDcDcCurrCtrState(CURRCTRSTATE_FLT);
	//		}
	//	}
	//	else
	//	{
	//		TIMER_RESET(gIDcDcOut1CurrCtrFltTimer);
	//	}

	//	if (fabs(fIDcDcOutRef - fIDcDcOut[CurrSnsrPhase2]) > gfPfcLCurrCtrFltCal)
	//	{
	//		TIMER_TICK(gIDcDcOut2CurrCtrFltTimer);
	//		if (gIDcDcOut2CurrCtrFltTimer > giPfcLCurrCtrFltTimerCal)
	//		{
	//			TIMER_RESET(gIDcDcOut2CurrCtrFltTimer);
	//			FdiagChkCtr_ChageDcDcCurrCtrState(CURRCTRSTATE_FLT);
	//		}
	//	}
	//	else
	//	{
	//		TIMER_RESET(gIDcDcOut2CurrCtrFltTimer);
	//	}


	//	break;
	//case CURRCTRSTATE_FLT:
	//	TIMER_RESET(gIDcDcOut1CurrCtrFltTimer);
	//	TIMER_RESET(gIDcDcOut2CurrCtrFltTimer);
	//	break;
	//default:
	//	break;
	//}
}

/*----------------------------------------------------------------------------
	Func : DCDC전류제어상태변경
	Period : 10ms
	Parameter : giPfcLCurrCtrState
----------------------------------------------------------------------------*/
void FdiagChkCtr_ChageDcDcCurrCtrState(CURRCTRSTATE state) {
	gIDcDcOutCurrCtrState = state;
}

/*----------------------------------------------------------------------------
	Func : Grid PLL 진단
	Period : 1ms
	Parameter : giGridVoltCtrState
	Etc : PLL 제어 정상 판단을 수행 하기위해 1ms 주기 제어 
----------------------------------------------------------------------------*/
void FdiagChkCtr_RunGridPLLCtrState(void)
{
	dq dqVgrid_dqe = CtrApi_GetGriddqVolt();
	dq dqVgrid_dqe_LPF = CtrApi_GetGriddqVoltLpf();
	float fVGrid_Mag_LPF = CtrApi_GetVgridMagLpf();

	switch (giGridVoltCtrState)
	{
	case VOLTCTRSTATE_INHIBIT:
		break;
	case VOLTCTRSTATE_READY_SS:
		if ((dqVgrid_dqe_LPF.q >= gfGridPLL_Voltq_KCal * fVGrid_Mag_LPF) && (dqVgrid_dqe_LPF.d <= gfGridPLL_Voltd_Cal))
		{
			TIMER_TICK(giGridPLL_Normal_Timer);
			TIMER_RESET(giGridPLL_CtrFlt_Timer);
			if (giGridPLL_Normal_Timer > giGridPLL_Normal_TimerCal)
			{
				TIMER_RESET(giGridPLL_Normal_Timer);
				FdiagChkCtr_ChangeGridPllState(VOLTCTRSTATE_NORMAL);
			}
		}
		else
		{
			TIMER_TICK(giGridPLL_CtrFlt_Timer);
//			TIMER_RESET(giGridPLL_Normal_Timer);
			if (giGridPLL_CtrFlt_Timer > giGridPLL_CtrFlt_TimerCal)
			{
				TIMER_RESET(giGridPLL_CtrFlt_Timer);
				FdiagChkCtr_ChangeGridPllState(VOLTCTRSTATE_FLT);
			}
		}
		break;
	case VOLTCTRSTATE_NORMAL:
		if ((dqVgrid_dqe_LPF.q < gfGridPLL_Voltq_KCal * fVGrid_Mag_LPF)	&& (dqVgrid_dqe_LPF.d > gfGridPLL_Voltd_Cal))
		{
//			FdiagChkCtr_ChangeGridPllState(VOLTCTRSTATE_READY_SS);
			TIMER_TICK(giGridPLL_CtrFlt_Timer);
			TIMER_RESET(giGridPLL_Normal_Timer);
			if (giGridPLL_CtrFlt_Timer > giGridPLL_CtrFlt_TimerCal)
			{
				TIMER_RESET(giGridPLL_CtrFlt_Timer);
				FdiagChkCtr_ChangeGridPllState(VOLTCTRSTATE_FLT);
			}
		}
		break;

	case VOLTCTRSTATE_FLT:
		TIMER_TICK(giGridPLL_Flt_Timer);
		if (giGridPLL_Flt_Timer > giGridPLL_Flt_TimerCal)		//100ms
		{
			TIMER_RESET(giGridPLL_Flt_Timer);

			giGridPLL_Flt_count++;

			//giGridPLL_Flt_HealCycle = CLEAR;

			giGridPLL_Flt_HealState = SET;

			if (giGridPLL_Flt_count >= giGridPLL_Flt_count_MaxDTCCal)
			{
				giGridPLL_Flt_count = giGridPLL_Flt_count_MaxDTCCal;
			}
			else if (giGridPLL_Flt_count == 0)
			{
			    FdiagChkCtr_ChangeGridPllState(VOLTCTRSTATE_INHIBIT);
			}

//			if ((dqVgrid_dqe_LPF.q >= gfGridPLL_Voltq_KCal * fVGrid_Mag_LPF) && (dqVgrid_dqe_LPF.d <= gfGridPLL_Voltd_Cal))
//			{
//				FdiagChkCtr_ChangeGridPllState(VOLTCTRSTATE_INHIBIT);
//			}
		}
		break;
	default:
		break;
	}
}

/*----------------------------------------------------------------------------
	Func : PLL 상태 변경
	Period : Non
	Parameter : giGridPllState
----------------------------------------------------------------------------*/
void FdiagChkCtr_ChangeGridPllState(VOLTCTRSTATE state)
{
	giGridVoltCtrState = state;
}

/*----------------------------------------------------------------------------
	Func : PLL 이상 Heal
	Period : 100ms
	Parameter : giGridPLL_Flt_count
----------------------------------------------------------------------------*/
void FdiagChkCtr_GridPllFltHealCount(void)
{
	if (giGridPLL_Flt_HealState == SET)
	{
		if (giGridPLL_Flt_HealCycle > giGridPLL_Flt_HealCnt_TimerCal)
		{
			giGridPLL_Flt_HealCycle = 0U;
			if (giGridPLL_Flt_count > 0U)
			{
				giGridPLL_Flt_count--;
			}
			else
			{
				giGridPLL_Flt_HealState = CLEAR;
			}
		}
		else
		{
			giGridPLL_Flt_HealCycle++;
		}
	}
}

/*----------------------------------------------------------------------------
	Func : PFC DcLink전압제어진단
	Period : 10ms
	Parameter : giVoltCtrState[CtrNum]
----------------------------------------------------------------------------*/
void FdiagChkCtr_RunPfcLinkVoltCtrState() {
	float fVPfcLink = 0.0f;
	float fVPfcLinkRef = CtrApi_GetVPfcLinkRef();
	fVPfcLink = MonApi_GetVolt(VoltSnsrDCLink);

	switch (giPfcDcLinkVoltCtrState)
	{
	case VOLTCTRSTATE_INHIBIT:
		TIMER_RESET(giDcLinkVoltCtrFltTimer);
		break;
	case VOLTCTRSTATE_READY_SS:
	case VOLTCTRSTATE_NORMAL:
		if (fabs(fVPfcLinkRef - fVPfcLink) > gfDcLinkVoltCtrFltCal)
		{
			TIMER_TICK(giDcLinkVoltCtrFltTimer);
			if (giDcLinkVoltCtrFltTimer > giDcLinkVoltCtrFltTimerCal)
			{
				TIMER_RESET(giDcLinkVoltCtrFltTimer);
				FdiagChkCtr_ChagePfcLinkVoltCtrState(VOLTCTRSTATE_FLT);
			}
		}
		else
		{
			TIMER_RESET(giDcLinkVoltCtrFltTimer);
		}
		break;
	case VOLTCTRSTATE_FLT:
		TIMER_RESET(giDcLinkVoltCtrFltTimer);
		break;
	default:
		break;
	}
}

/*----------------------------------------------------------------------------
	Func : Pfc DcLink 전압제어상태변경
	Period : 10ms
	Parameter : giVoltCtrState[CtrNum]
----------------------------------------------------------------------------*/
void FdiagChkCtr_ChagePfcLinkVoltCtrState(VOLTCTRSTATE state) {
	giPfcDcLinkVoltCtrState = state;
}

/*----------------------------------------------------------------------------
	Func : V2XDcLink전압제어진단
	Period : 10ms
	Parameter : giVoltCtrState[CtrNum]
----------------------------------------------------------------------------*/
void FdiagChkCtr_RunV2XDcLinkVoltCtrState() {
	/*float fVDcDcLink = MonApi_GetVolt(VoltSnsrDCLink);;
	float fVV2XDcLinkRef = CtrApi_GetVDcDcLinkRef();

	switch (giV2XDcLinkVoltCtrState)
	{
	case VOLTCTRSTATE_INHIBIT:
		TIMER_RESET(giDcLinkVoltCtrFltTimer);
		break;
	case VOLTCTRSTATE_READY_SS:
	case VOLTCTRSTATE_NORMAL:
		if (fabs(fVV2XDcLinkRef - fVDcDcLink) > gfDcLinkVoltCtrFltCal)
		{
			TIMER_TICK(giDcLinkVoltCtrFltTimer);
			if (giDcLinkVoltCtrFltTimer > giDcLinkVoltCtrFltTimerCal)
			{
				TIMER_RESET(giDcLinkVoltCtrFltTimer);
				FdiagChkCtr_ChageV2XDcLinkVoltCtrState(VOLTCTRSTATE_FLT);
			}
		}
		else
		{
			TIMER_RESET(giDcLinkVoltCtrFltTimer);
		}
		break;
	case VOLTCTRSTATE_FLT:
		TIMER_RESET(giDcLinkVoltCtrFltTimer);
		break;
	default:
		break;
	}*/
}

/*----------------------------------------------------------------------------
	Func : DcLink 전압제어상태변경
	Period : 10ms
	Parameter : giVoltCtrState[CtrNum]
----------------------------------------------------------------------------*/
void FdiagChkCtr_ChageV2XDcLinkVoltCtrState(VOLTCTRSTATE state) {
	giV2XDcLinkVoltCtrState = state;
}

/*----------------------------------------------------------------------------
	Func : 출력전압제어진단
	Period : 10ms
	Parameter : giVoltCtrState[CtrNum]
----------------------------------------------------------------------------*/
void FdiagChkCtr_RunOutVoltCtrState() {
	/*float fVOut = 0.0f;
	float fVOutRef = CtrApi_GetVOutRef();
	fVOut = MonApi_GetVolt(VoltSnsrOut);

	switch (giOutVoltCtrState)
	{
	case VOLTCTRSTATE_INHIBIT:
		TIMER_RESET(giOutVoltCtrFltTimer);
		break;
	case VOLTCTRSTATE_READY_SS:
	case VOLTCTRSTATE_NORMAL:
		if (fabs(fVOutRef - fVOut) > gfOutVoltCtrFltCal)
		{
			TIMER_TICK(giOutVoltCtrFltTimer);
			if (giOutVoltCtrFltTimer > giOutVoltCtrFltTimerCal)
			{
				TIMER_RESET(giOutVoltCtrFltTimer);
				FdiagChkCtr_ChageOutVoltCtrState(VOLTCTRSTATE_FLT);
			}
		}
		else
		{
			TIMER_RESET(giOutVoltCtrFltTimer);
		}
		break;
	case VOLTCTRSTATE_FLT:
		TIMER_RESET(giOutVoltCtrFltTimer);
		break;
	default:
		break;
	}*/
}

/*----------------------------------------------------------------------------
	Func : 출력전압제어상태변경
	Period : 10ms
	Parameter : giVoltCtrState[CtrNum]
----------------------------------------------------------------------------*/
void FdiagChkCtr_ChageOutVoltCtrState(VOLTCTRSTATE state) {
	giOutVoltCtrState = state;
}

/*
/*----------------------------------------------------------------------------
	Func : V2L전압제어진단
	Period : 10ms
	Parameter : giVoltCtrState[CtrNum]
----------------------------------------------------------------------------*/
void FdiagChkCtr_RunV2LVoltCtrState() {
	/*float fVV2L = 0.0f;
	float fVV2LRef = CtrApi_GetVV2LRef();
	fVV2L = CtrApi_GetVV2L();

	switch (giV2LVoltCtrState)
	{
	case VOLTCTRSTATE_INHIBIT:
		TIMER_RESET(giV2LVoltCtrFltTimer);
		break;
	case VOLTCTRSTATE_READY_SS:
	case VOLTCTRSTATE_NORMAL:
		if (fabs(fVV2LRef - fVV2L) > gfV2LVoltCtrFltCal)
		{
			TIMER_TICK(giV2LVoltCtrFltTimer);
			if (giV2LVoltCtrFltTimer > giV2LVoltCtrFltTimerCal)
			{
				TIMER_RESET(giV2LVoltCtrFltTimer);
				FdiagChkCtr_ChageV2LVoltCtrState(VOLTCTRSTATE_FLT);
			}
		}
		else
		{
			TIMER_RESET(giV2LVoltCtrFltTimer);
		}
		break;
	case VOLTCTRSTATE_FLT:
		TIMER_RESET(giOutVoltCtrFltTimer);
		break;
	default:
		break;
	}*/
}

/*----------------------------------------------------------------------------
	Func : V2L전압제어상태변경
	Period : 10ms
	Parameter : giVoltCtrState[CtrNum]
----------------------------------------------------------------------------*/
void FdiagChkCtr_ChageV2LVoltCtrState(VOLTCTRSTATE state) {
	//giV2LVoltCtrState = state;
}



VOLTCTRSTATE FdiagChkCtr_GetGridPllCtrState()			{ return giGridVoltCtrState; }
VOLTCTRSTATE FdiagChkCtr_GetDcLinkVoltCtrState(void)	{ return giPfcDcLinkVoltCtrState; }
VOLTCTRSTATE FdiagChkCtr_GetOutVoltCtrState(void)		{ return giOutVoltCtrState; }
CURRCTRSTATE FdiagChkCtr_GetPfcCurrCtrState(void)		{ return giPfcLCurrCtrState; }
CURRCTRSTATE FdiagChkCtr_GetDcDcCurrCtrState(void)		{ return gIDcDcOutCurrCtrState; }
