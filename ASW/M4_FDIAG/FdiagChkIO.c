/*============================================================================
	Includes
============================================================================*/
#include "FdiagChkIO.h"
#include "FdiagChkM.h"
#include "FdiagChkS.h"
#include "FdiagCal.h"
#include "FdiagApi.h"
#include "../M0_MAIN/AswMainApi.h"
#include "../M1_SEQ/SeqApi.h"
#include "../M2_MON/MonApi.h"
#include "../M3_CTR/CtrApi.h"
#include "../M6_COM/ComApi.h"

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

//Voltage sensor diag
ICCUVOLTSNSR_STATE giVoltSnsrState[VoltSnsrNum]			= { ICCUVOLTSNSR_READY, };
Uint16 giVoltSnsr_VoltHiFlt_Timer[VoltSnsrNum]			= { 0U, };
Uint16 giVoltSnsr_VoltLoFlt_Timer[VoltSnsrNum]			= { 0U, };
Uint16 giVoltSnsr_RationalFlt_Timer[VoltSnsrNum]		= { 0U, };
Uint16 giVoltSnsrFltFlag								= 0U;

//Input voltage diag
ICCUVOLT_STATE giVoltState[VoltSnsrNum]					= { ICCUVOLT_NORMAL, };
Uint16 giVolt_Ov_Timer[VoltSnsrNum]						= { 0U, };
Uint16 giVolt_Ov_count[VoltSnsrNum]						= { 0U, }; 
Uint16 giVolt_Ov_HealCycle[VoltSnsrNum]					= { 0U, };
Uint16 giVolt_Ov_HealState[VoltSnsrNum]					= { 0U, };
Uint16 giVolt_Uv_Timer[VoltSnsrNum]						= { 0U, };
Uint16 giVoltFltFlag									= 0U;

//Current sensor diag
ICCUCURRSNSR_STATE giCurrSnsrState[CurrSnsrNum]			= { ICCUCURRSNSR_READY, };
Uint16 giCurrSnsr_VoltHiFlt_Timer[CurrSnsrNum]			= { 0U, };
Uint16 giCurrSnsr_VoltLoFlt_Timer[CurrSnsrNum]			= { 0U, };
Uint16 giCurrSnsr_RationalFlt_Timer[CurrSnsrNum]		= { 0U, };
Uint16 giCurrSnsrFltFlag								= 0U;

//Current diag
ICCUCURR_STATE giCurrState[CurrSnsrNum]					= { ICCUCURR_NORMAL, };
Uint16 giCurr_Oc_Resume_Timer[CurrSnsrNum]				= { 0U, };
Uint16 giCurr_Oc_count[CurrSnsrNum]						= { 0U, };
Uint16 giCurr_Oc_HealCycle[CurrSnsrNum]					= { 0U, };
Uint16 giCurr_Oc_HealState[CurrSnsrNum]					= { 0U, };
Uint16 giCurr_Oc_FltFlag[CurrSnsrNum]					= { 0U, };
Uint16 giCurr_Oc_FltFlag_HealCnt[CurrSnsrNum]			= { 0U, };
Uint16 giCurrFltFlag									= 0U;
Uint8 giCurr_Oc_Do_TripReset[CurrSnsrNum]				= { 0U, };

/*============================================================================
	Private Variables/Constants
============================================================================*/

/*============================================================================
	Function Prototypes
============================================================================*/
//Curr sensor and Curr diag
void FdiagChkIO_RunCurrSnsrState(Uint16 SnsrNum);                                   //전류 센서 상태 진단
void FdiagChkIO_ChangeCurrSnsrState(Uint16 SnsrNum, ICCUCURRSNSR_STATE state);      //전류 센서 상태 변경
void FdiagChkIO_RunCurrSwFlt(Uint16 SnsrNum);                                       //전류 sw 고장
void FdiagChkIO_RunCurrState(Uint16 SnsrNum);                                       //
void FdiagChkIO_ChangeCurrState(Uint16 SnsrNum, ICCUCURR_STATE state);
void FdiagChkIO_CurrHwOcHealCount(Uint16 SnsrNum);

//Volt sensor and Volt diag
void FdiagChkIO_RunVoltSnsrState(Uint16 SnsrNum);
void FdiagChkIO_ChangeVoltSnsrState(Uint16 SnsrNum, ICCUVOLTSNSR_STATE state);
void FdiagChkIO_RunVoltSwFlt(Uint16 SnsrNum);
void FdiagChkIO_RunVoltState(Uint16 SnsrNum);
void FdiagChkIO_ChangeVoltState(Uint16 SnsrNum, ICCUVOLT_STATE state);
void FdiagChkIO_VoltOvHealCount(Uint16 SnsrNum);

/*============================================================================
	Function Implementations
============================================================================*/
void FdiagChkIOIsrCtr()
{
    FdiagChkIO_RunCurrSwFlt(0);
    FdiagChkIO_RunVoltSwFlt(0);
    FdiagChkIO_RunVoltSwFlt(1);
}

void FdiagChkIOTask100us()
{

}

void FdiagChkIOTask1ms()
{
    FdiagChkIO_RunCurrSnsrState(0);
    FdiagChkIO_RunCurrState(0);
    FdiagChkIO_RunVoltSnsrState(0);
    FdiagChkIO_RunVoltSnsrState(1);
    FdiagChkIO_RunVoltState(0);
    FdiagChkIO_RunVoltState(1);
}

void FdiagChkIOTask10ms()
{
}

void FdiagChkIOTask100ms()
{
    FdiagChkIO_CurrHwOcHealCount(0);
    FdiagChkIO_VoltOvHealCount(0);
    FdiagChkIO_VoltOvHealCount(1);
}

/****************************************************************************/
/*----------------------------------------------------------------------------
	Func : 전류 센서 SW 고장 진단
	Period : 1ms
	Parameter : iIccuCurrSnsrState
----------------------------------------------------------------------------*/
void FdiagChkIO_RunCurrSnsrState(Uint16 SnsrNum)
{
	float fIIccu = MonApi_GetCurr(SnsrNum);				
	float fAdcResult = MonApi_GetCurrAdcResult(SnsrNum);
	float fIOutFdcBmsCan = ComApi_GetCanOutCurr();
	//Uint16 iAuxBatVoltState = FdiagChkS_GetAuxBatVoltState();
	Uint16 iIccuCurrSnsrState = FdiagChkIO_GetCurrSnsrState(SnsrNum);


    switch (iIccuCurrSnsrState)
    {
    case ICCUCURRSNSR_READY:
    case ICCUCURRSNSR_NORMAL:
        if (fAdcResult >= gfAdcSnsrVoltHiFltCal)			//ADC 입력전압 (VDD 98%) 이상 즉시
        {
            TIMER_RESET(giCurrSnsr_VoltLoFlt_Timer[SnsrNum]);
            TIMER_RESET(giCurrSnsr_RationalFlt_Timer[SnsrNum]);
            TIMER_TICK(giCurrSnsr_VoltHiFlt_Timer[SnsrNum]);
            if (giCurrSnsr_VoltHiFlt_Timer[SnsrNum] >= giCurrSnsr_VoltHiFlt_TimerCal)
            {
                FdiagChkIO_ChangeCurrSnsrState(SnsrNum, ICCUCURRSNSR_VOLTHI_FLT);			//giCurrSnsrState[SnsrNum] = ICCUCURRSNSR_VOLTHI_FLT;
                giCurrSnsr_VoltHiFlt_Timer[SnsrNum] = 0U;
                giCurrSnsrFltFlag |= (0x0001U << SnsrNum);
            }
        }
        else if (fAdcResult <= gfAdcSnsrVoltLoFltCal)			//ADC 입력전압 0.2V 이하 즉시
        {
            TIMER_RESET(giCurrSnsr_VoltHiFlt_Timer[SnsrNum]);
            TIMER_RESET(giCurrSnsr_RationalFlt_Timer[SnsrNum]);
            TIMER_TICK(giCurrSnsr_VoltLoFlt_Timer[SnsrNum]);

            if (giCurrSnsr_VoltLoFlt_Timer[SnsrNum] >= giCurrSnsr_VoltLoFlt_TimerCal)
            {
                FdiagChkIO_ChangeCurrSnsrState(SnsrNum, ICCUCURRSNSR_VOLTLO_FLT);  	//giCurrSnsrState[SnsrNum] = ICCUCURRSNSR_VOLTLO_FLT;
                giCurrSnsr_VoltLoFlt_Timer[SnsrNum] = 0U;
                giCurrSnsrFltFlag |= (0x0001U << SnsrNum);
            }
        }
        else
        {
            TIMER_RESET(giCurrSnsr_VoltHiFlt_Timer[SnsrNum]);
            TIMER_RESET(giCurrSnsr_VoltLoFlt_Timer[SnsrNum]);
            TIMER_RESET(giCurrSnsr_RationalFlt_Timer[SnsrNum]);
            FdiagChkIO_ChangeCurrSnsrState(SnsrNum, ICCUCURRSNSR_NORMAL);
        }
            break;
        case ICCUCURRSNSR_VOLTLO_FLT:
            break;
        case ICCUCURRSNSR_VOLTHI_FLT:
            break;
        case ICCUCURRSNSR_RATIONAL_FLT:
            break;
        default:
            break;
    }

}

/*----------------------------------------------------------------------------
	Func : 전류센서 상태 변경
	Period : Non
	Parameter : giCurrSnsrState
----------------------------------------------------------------------------*/
void FdiagChkIO_ChangeCurrSnsrState(Uint16 SnsrNum, ICCUCURRSNSR_STATE state)
{
	giCurrSnsrState[SnsrNum] = state;
}

/*----------------------------------------------------------------------------
	Func : 전류 SW 고장 진단
	Period : ISR
	Parameter : iCurrstate
----------------------------------------------------------------------------*/
void FdiagChkIO_RunCurrSwFlt(Uint16 SnsrNum)
{
	float fIIccu = fabs(MonApi_GetCurr(SnsrNum));
	Uint16 iIccuCurrSnsrState = FdiagChkIO_GetCurrSnsrState(SnsrNum);
	Uint16 iCurrstate = FdiagChkIO_GetCurrState(SnsrNum);
	Uint16 iRlyState = FdiagChkS_GetRlyState();

	switch (iCurrstate)
	{
	case ICCUCURR_NORMAL:
		if (giCurrSnsrState[SnsrNum] == ICCUCURRSNSR_NORMAL)
		{
			if ((SnsrNum == CurrSnsrPhase)/* || (SnsrNum == CurrSnsrPhase2)*/ )
			{
				if (fIIccu > gfIccuCurr_CurrHiFlt_Cal[SnsrNum])    //SWF
				{
					if (iRlyState == RLY_ON)
					{
						FdiagChkIO_ChangeCurrState(SnsrNum, ICCUCURR_SWOC_WAITRESUME);
						SeqApi_SetInternalMainState(STAT_RESUME_STATE);
						giCurrFltFlag |= (0x0001U << SnsrNum);
						FdiagChkS_SetPwmEnState(GateSnsrPfc, CLEAR);
					}
					else
					{
						//FdiagChkS_ChangeRlyState(RLY_MELTING);
						//SeqApi_SetInternalMainState(STAT_FATAL_STATE);  //Check!
						FdiagChkS_SetPwmEnState(GateSnsrPfc, CLEAR);
					}
				}

			}
			/*else if ((SnsrNum == CurrSnsrDcDcOut1) || (SnsrNum == CurrSnsrDcDcOut2))
			{
				if (iIccuDcDcCurrOcDiState == HIGH)
				{
					FdiagChkIO_ChangeCurrState(SnsrNum, ICCUCURR_HWOC_WAITRESUME);
					SeqApi_SetInteralMainState(STAT_RESUME_STATE);
					giCurrFltFlag |= (0x0001U << SnsrNum);
					FdiagChkS_SetPwmEnState(GateSnsrDcDc, CLEAR);
				}
				else if (fIIccu > gfIccuCurr_CurrHiFlt_Cal[SnsrNum])
				{
					FdiagChkIO_ChangeCurrState(SnsrNum, ICCUCURR_SWOC_WAITRESUME);
					SeqApi_SetInteralMainState(STAT_RESUME_STATE);
					giCurrFltFlag |= (0x0001U << SnsrNum);
					FdiagChkS_SetPwmEnState(GateSnsrDcDc, CLEAR);
				}
			}*/
		}
		break;
	case ICCUCURR_HWOC_WAITRESUME:
	    break;
	case ICCUCURR_SWOC_WAITRESUME:
		break;
	case ICCUCURR_HWOC_FLT:
		break;
	case ICCUCURR_SWOC_FLT:
		break;
	default:
		giCurrState[SnsrNum] = ICCUCURR_NORMAL;
		break;
	}
	
}


/*----------------------------------------------------------------------------
	Func : 전류 상태 진단 
	Period : 1ms
	Parameter : giCurrState
----------------------------------------------------------------------------*/
void FdiagChkIO_RunCurrState(Uint16 SnsrNum)
{
    float fIIccu = MonApi_GetCurr(SnsrNum);
	Uint16 iIccuPfcCurrOcDiState = 0; //gpio OCP signal
	//Uint16 iIccuDcDcCurrOcDiState = 0; //gpio OCP signal

	switch (giCurrState[SnsrNum])
	{
		case ICCUCURR_NORMAL :
			break;
		case ICCUCURR_HWOC_WAITRESUME:
		case ICCUCURR_SWOC_WAITRESUME:
#ifndef DefDisableFltRetry
			TIMER_TICK(giCurr_Oc_Resume_Timer[SnsrNum]);

			if ((giCurr_Oc_Resume_Timer[SnsrNum] > (giCurr_Oc_Resume_TimeCal >> 2U))		//25ms
				&& ((((SnsrNum == CurrSnsrPhase)) && (iIccuPfcCurrOcDiState == SET))
                /*|| (((SnsrNum == CurrSnsrDcDcOut1) || (SnsrNum == CurrSnsrDcDcOut2)) && (iIccuDcDcCurrOcDiState == SET))*/))
			{ 
				giCurr_Oc_Do_TripReset[SnsrNum] = SET;
			}

			if ((giCurr_Oc_Resume_Timer[SnsrNum] > (giCurr_Oc_Resume_TimeCal >> 1U))	//50ms
				&& (giCurr_Oc_Do_TripReset[SnsrNum] == SET))
			{ 
				giCurr_Oc_Do_TripReset[SnsrNum] = CLEAR;
			}
			
			if (giCurr_Oc_Resume_Timer[SnsrNum] > giCurr_Oc_Resume_TimeCal)		//100ms
			{
				TIMER_RESET(giCurr_Oc_Resume_Timer[SnsrNum]);
				giCurr_Oc_count[SnsrNum]++;
				giCurr_Oc_HealCycle[SnsrNum] = CLEAR;										// 고장 발생 중에서는 Heal 안함
				giCurr_Oc_HealState[SnsrNum] = SET;
				if (giCurr_Oc_count[SnsrNum] >= giCurr_Oc_count_MaxDTCCal)				// DTC 동작 추가 개발 필요
				{
				    giCurr_Oc_count[SnsrNum] = giCurr_Oc_count_MaxDTCCal;
				}
				if ((giCurrState[SnsrNum] == ICCUCURR_SWOC_WAITRESUME) && (fIIccu < gfIccuCurr_CurrHiFlt_Cal[SnsrNum]))
				{
					FdiagChkIO_ChangeCurrState(SnsrNum, ICCUCURR_NORMAL);
					giCurrFltFlag &= (~(0x0001U << SnsrNum));
				}
			}
#endif
			break;
		case ICCUCURR_HWOC_FLT:
			break;
		case ICCUCURR_SWOC_FLT:
			break;
		default:
			giCurrState[SnsrNum] = ICCUCURR_NORMAL;
			break;
	}
}


/*----------------------------------------------------------------------------
	Func : 전류 상태 변경
	Period : Non
	Parameter : giCurrState
----------------------------------------------------------------------------*/
void FdiagChkIO_ChangeCurrState(Uint16 SnsrNum, ICCUCURR_STATE state)
{
	giCurrState[SnsrNum] = state;
}


/*----------------------------------------------------------------------------
	Func : 전류 고장 Heal (for DTC)
	Period : 100ms
	Parameter : giCurr_Oc_count
----------------------------------------------------------------------------*/
void FdiagChkIO_CurrHwOcHealCount(Uint16 SnsrNum)
{
	if (giCurr_Oc_HealState[SnsrNum] == SET)
	{
		if (giCurr_Oc_HealCycle[SnsrNum] > giCurr_HwOc_HealCnt_TimerCal)
		{
			TIMER_RESET(giCurr_Oc_HealCycle[SnsrNum]);
			if (giCurr_Oc_count[SnsrNum] > 0U)
			{
				giCurr_Oc_count[SnsrNum]--;
			}
			else
			{
				giCurr_Oc_HealState[SnsrNum] = CLEAR;
			}
		}
		else
		{
			TIMER_TICK(giCurr_Oc_HealCycle[SnsrNum]);
		}
	}
}


/*----------------------------------------------------------------------------
	Func : 전압 센서 상태 진단
	Period : 1ms
	Parameter : giVoltState[SnsrNum]
----------------------------------------------------------------------------*/
void FdiagChkIO_RunVoltSnsrState(Uint16 SnsrNum)
{
	float fVIccu = MonApi_GetVolt(SnsrNum);
	float fAdcResult = MonApi_GetVoltAdcResult(SnsrNum);
	Uint16 iAuxBatVoltState = FdiagChkS_GetAuxBatVoltState();
	Uint16 iIccuVoltSnsrState = FdiagChkIO_GetVoltSnsrState(SnsrNum);

    switch (iIccuVoltSnsrState)
    {
    case ICCUVOLTSNSR_READY:
    case ICCUVOLTSNSR_NORMAL:
        if (fAdcResult > gfAdcSnsrVoltHiFltCal)			//ADC 입력전압 4.5V이상 10ms 유지 시
        {
            TIMER_RESET(giVoltSnsr_VoltLoFlt_Timer[SnsrNum]);
            TIMER_RESET(giVoltSnsr_RationalFlt_Timer[SnsrNum]);
            TIMER_TICK(giVoltSnsr_VoltHiFlt_Timer[SnsrNum]);

            if (giVoltSnsr_VoltHiFlt_Timer[SnsrNum] > giVoltSnsr_VoltHiFlt_TimerCal)
            {
                FdiagChkIO_ChangeVoltSnsrState(SnsrNum, ICCUVOLTSNSR_VOLTHI_FLT);
                TIMER_RESET(giVoltSnsr_VoltHiFlt_Timer[SnsrNum]);
                giVoltSnsrFltFlag |= (0x0001U << SnsrNum);
            }
        }
        else if (fAdcResult <= gfAdcSnsrVoltLoFltCal)	//ADC 입력전압 0.5V 이하 10ms 유지 시
        {
            TIMER_RESET(giVoltSnsr_VoltHiFlt_Timer[SnsrNum]);
            TIMER_RESET(giVoltSnsr_RationalFlt_Timer[SnsrNum]);
            TIMER_TICK(giVoltSnsr_VoltLoFlt_Timer[SnsrNum]);
            if (giVoltSnsr_VoltLoFlt_Timer[SnsrNum] > giVoltSnsr_VoltLoFlt_TimerCal)
            {
                FdiagChkIO_ChangeVoltSnsrState(SnsrNum, ICCUVOLTSNSR_VOLTLO_FLT);
                TIMER_RESET(giVoltSnsr_VoltLoFlt_Timer[SnsrNum]);
                giVoltSnsrFltFlag |= (0x0001U << SnsrNum);
            }
        }
        else
        {
            TIMER_RESET(giVoltSnsr_VoltHiFlt_Timer[SnsrNum]);
            TIMER_RESET(giVoltSnsr_VoltLoFlt_Timer[SnsrNum]);
            TIMER_RESET(giVoltSnsr_RationalFlt_Timer[SnsrNum]);
            FdiagChkIO_ChangeVoltSnsrState(SnsrNum, ICCUVOLTSNSR_NORMAL);
        }
        break;
    case ICCUVOLTSNSR_VOLTLO_FLT:
        break;
    case ICCUVOLTSNSR_VOLTHI_FLT:
        break;
    case ICCUVOLTSNSR_RATIONAL_FLT:
        break;
    default:
        break;
    }
}


/*----------------------------------------------------------------------------
	Func : 전압 센서 상태 변경
	Period : Non
	Parameter : giVoltState[SnsrNum]
----------------------------------------------------------------------------*/
void FdiagChkIO_ChangeVoltSnsrState(Uint16 SnsrNum, ICCUVOLTSNSR_STATE state)
{
	giVoltSnsrState[SnsrNum] = state;
}


/*----------------------------------------------------------------------------
	Func : 전압 SW 고장 진단
	Period : ISR
	Parameter : giVoltState
----------------------------------------------------------------------------*/
void FdiagChkIO_RunVoltSwFlt(Uint16 SnsrNum)
{
	float fVIccu = MonApi_GetVolt(SnsrNum);
	float fVGridRms = MonApi_GetGridVoltRms();
	Uint16 iIccuVoltSnsrState = FdiagChkIO_GetVoltSnsrState(SnsrNum);
	Uint16 iVoltstate = FdiagChkIO_GetVoltState(SnsrNum);

	switch (iVoltstate)
	{
	case ICCUVOLT_NORMAL:
		if ((giVoltSnsrState[SnsrNum] == ICCUVOLTSNSR_NORMAL) && (SnsrNum == VoltSnsrGrid))
		{
			if ((fVIccu > gfVolt_VoltHiFlt_Cal[SnsrNum]) || (fVIccu < -1.0f * gfVolt_VoltHiFlt_Cal[SnsrNum]))
			{
				FdiagChkIO_ChangeVoltState(SnsrNum, ICCUVOLT_SWOV_FLT);
				SeqApi_SetInternalMainState(STAT_FAULT_STATE);
				FdiagChkS_SetPwmEnState(SnsrNum, CLEAR);
				giVoltFltFlag |= (0x0001U << SnsrNum);
			}
#ifndef DefDisableVoltUVInhibit
			else if (fVGridRms < gfVolt_VoltLowFlt_Cal[SnsrNum])
			{
				FdiagChkIO_ChangeVoltState(SnsrNum, ICCUVOLT_UV_INHIBIT_FLT);
				FdiagChkS_SetPwmEnState(SnsrNum, CLEAR);
			}
#endif
		}
		else if ((giVoltSnsrState[SnsrNum] == ICCUVOLTSNSR_NORMAL) && (SnsrNum != VoltSnsrGrid))
		{
			if (fVIccu > gfVolt_VoltHiFlt_Cal[SnsrNum])
			{
				FdiagChkIO_ChangeVoltState(SnsrNum, ICCUVOLT_SWOV_FLT);
				SeqApi_SetInternalMainState(STAT_FAULT_STATE);
				if (SnsrNum == VoltSnsrDCLink)
				{
					FdiagChkS_SetPwmEnState(SnsrNum, CLEAR);
				}
				else if (SnsrNum == VoltSnsrOut)
				{
					FdiagChkS_SetPwmEnState(SnsrNum, CLEAR);
				}
				giVoltFltFlag |= (0x0001 << SnsrNum);
			}
#ifndef DefDisableVoltUVInhibit
			else if (fVIccu < gfVolt_VoltLowFlt_Cal[SnsrNum])
			{
				FdiagChkIO_ChangeVoltState(SnsrNum, ICCUVOLT_UV_INHIBIT_FLT);
				if (SnsrNum == VoltSnsrDCLink)
				{
					FdiagChkS_SetPwmEnState(SnsrNum, CLEAR);
				}
				else if (SnsrNum == VoltSnsrOut)
				{
					FdiagChkS_SetPwmEnState(SnsrNum, CLEAR);
				}
			}
#endif
		}
		break;
	case ICCUVOLT_HWOV_FLT:
	case ICCUVOLT_SWOV_FLT:
		break;
	case ICCUVOLT_UV_INHIBIT_FLT:
		break;
	default:
		break;
	}
}

/*----------------------------------------------------------------------------
	Func : 전압 상태 진단
	Period : 1ms
	Parameter : giVoltState[SnsrNum]
----------------------------------------------------------------------------*/
void FdiagChkIO_RunVoltState(Uint16 SnsrNum)
{
	float fVIccu = MonApi_GetVolt(SnsrNum);
	float fVGridRms = MonApi_GetGridVoltRms();

	switch (giVoltState[SnsrNum])
	{
	case ICCUVOLT_NORMAL:
		break;
	case ICCUVOLT_HWOV_FLT:
	case ICCUVOLT_SWOV_FLT:
#ifndef DefDisableFltRetry
		TIMER_TICK(giVolt_Ov_Timer[SnsrNum]);

		if (giVolt_Ov_Timer[SnsrNum] > giVolt_Ov_TimerCal)		//100ms
		{
			TIMER_RESET(giVolt_Ov_Timer[SnsrNum]);
			giVolt_Ov_count[SnsrNum]++;
			giVolt_Ov_HealCycle[SnsrNum] = CLEAR;
			giVolt_Ov_HealState[SnsrNum] = SET;
			if (giVolt_Ov_count[SnsrNum] >= giVolt_Ov_count_MaxDTCCal)
			{
			    giVolt_Ov_count[SnsrNum] = giVolt_Ov_count_MaxDTCCal;
			}
			if (fabs(fVIccu) < gfVolt_VoltHiFlt_Cal[SnsrNum])
            {
                FdiagChkIO_ChangeVoltState(SnsrNum, ICCUVOLT_NORMAL);
				giVoltFltFlag &= (~(0x0001U << SnsrNum));
			}
		}
#endif
		break;
	case ICCUVOLT_UV_INHIBIT_FLT:
#ifndef DefDisableVoltUVInhibit
		TIMER_TICK(giVolt_Uv_Timer[SnsrNum]);
		if (giVolt_Uv_Timer[SnsrNum] > giVolt_Uv_TimerCal)		//100ms
		{
			TIMER_RESET(giVolt_Uv_Timer[SnsrNum]);
			if ((SnsrNum == VoltSnsrGrid)
				&& (fVGridRms > gfVolt_VoltLowFlt_Cal[SnsrNum])
				)
			{
				FdiagChkIO_ChangeVoltState(SnsrNum, ICCUVOLT_NORMAL);
			}
			else if ((SnsrNum != VoltSnsrGrid)
				&& (fVIccu > gfVolt_VoltLowFlt_Cal[SnsrNum])
				)
			{
				FdiagChkIO_ChangeVoltState(SnsrNum, ICCUVOLT_NORMAL);
			}
		}
#endif
		break;
	default:
//		giVoltState[SnsrNum] = ICCUVOLT_NORMAL;
		break;
	}

}

/*----------------------------------------------------------------------------
	Func : 전압 상태 변경
	Period : Non
	Parameter : giVoltState[SnsrNum]
----------------------------------------------------------------------------*/
void FdiagChkIO_ChangeVoltState(Uint16 SnsrNum, ICCUVOLT_STATE state)
{
	giVoltState[SnsrNum] = state;
}


/*----------------------------------------------------------------------------
	Func : 전압 고장 Heal (for DTC)
	Period : 100ms
	Parameter : giCurr_Oc_count
----------------------------------------------------------------------------*/
void FdiagChkIO_VoltOvHealCount(Uint16 SnsrNum)
{
	if (giVolt_Ov_HealState[SnsrNum] == SET)
	{
		if (giVolt_Ov_HealCycle[SnsrNum] > giVolt_Ov_HealCnt_TimerCal)
		{
			giVolt_Ov_HealCycle[SnsrNum] = 0U;
			if (giVolt_Ov_count[SnsrNum] > 0U)
			{
				giVolt_Ov_count[SnsrNum]--;
			}
			else
			{
				giVolt_Ov_HealState[SnsrNum] = CLEAR;
			}
		}
		else
		{
			giVolt_Ov_HealCycle[SnsrNum]++;
		}
	}
}




ICCUVOLTSNSR_STATE FdiagChkIO_GetVoltSnsrState(Uint16 SnsrNum)	{ return giVoltSnsrState[SnsrNum]; }
ICCUVOLT_STATE FdiagChkIO_GetVoltState(Uint16 SnsrNum)			{ return giVoltState[SnsrNum]; }
ICCUCURRSNSR_STATE FdiagChkIO_GetCurrSnsrState(Uint16 SnsrNum)	{ return giCurrSnsrState[SnsrNum]; }
ICCUCURR_STATE FdiagChkIO_GetCurrState(Uint16 SnsrNum)			{ return giCurrState[SnsrNum]; }

