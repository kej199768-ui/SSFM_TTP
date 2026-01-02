/*============================================================================
	Includes
============================================================================*/
#include "FdiagChkM.h" 
#include "FdiagChkIO.h" 
#include "FdiagChkS.h" 
#include "FdiagChkCtr.h" 
#include "FdiagChkFS.h" 
#include "FdiagApi.h"
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
Uint16 giCbAbnormalSubState = 0U;
Uint16 giInhibitSubState = 0U;
Uint16 giFatalSubState = 0U;
Uint16 giFaultSubState = 0U;
Uint16 giResumeSubState = 0U;
Uint16 giNormalSubState = 0U;
Uint16 giHwIsrPinState = 0U;
Uint16 gIiccuRedayState = 0U;
Uint16 giIccuControllableState = 0U;
Bool giIccuReadyState = 0U;
Bool giIccuControllable = 0U;


/*============================================================================
	Private Variables/Constants
============================================================================*/

/*============================================================================
	Global Function Prototypes
============================================================================*/

/*============================================================================
	Function Implementations
============================================================================*/
void FdiagChkMIsrCtr()
{
	FdiagChkIOIsrCtr();
	//FdiagChkSIsrCtr();
}

void FdiagChkMTask100us()
{
}

void FdiagChkMTask1ms()
{
	FdiagChkIOTask1ms();
	FdiagChkSTask1ms();
	FdiagChkCtrTask1ms();
	FdiagChkFSTask1ms();
}

void FdiagChkMTask10ms()
{
//	FdiagChkIOTask10ms();
//	FdiagChkCtrTask10ms();
}

void FdiagChkMTask100ms()
{
//	FdiagChkIOTask100ms();
    FdiagChkCtrTask100ms();
}



/*----------------------------------------------------------------------------
	Func : 제어보드 이상 진단
	Period : 1ms
	Parameter : giCbAbnormalSubState
----------------------------------------------------------------------------*/
Uint16 FdiagChkMConCbAbnormal()
{
	Uint16 iCbAbnormalSubStateTemp = 0U;

	if (FdiagChkFS_GetEcuPostRunState() != ECU_NORMAL)
	{
		iCbAbnormalSubStateTemp |= STAT_ECU_POSTRUN;
	}
	if (FdiagChkS_GetAuxBatVoltState() != AUXBATVOLT_NORMAL)
	{
		iCbAbnormalSubStateTemp |= STAT_AUXBATVOLT_FLT;
	}
	if (FdiagChkS_GetIgVoltState() == IG_SWOV_FLT)
	{
		iCbAbnormalSubStateTemp |= STAT_IGVOLT_FLT;
	}
	giCbAbnormalSubState = iCbAbnormalSubStateTemp;
	return giCbAbnormalSubState;
}

/*----------------------------------------------------------------------------
	Func : Inhibit 진단
	Period : 1ms
	Parameter : giInhibitSubState
----------------------------------------------------------------------------*/
Uint16 FdiagChkMConInhibit()
{
	Uint16 iInhibitSubStateTemp = 0U;
	Uint8 i = 0U;
	ICCUMODE_STATE iIccuModeState = FdiagChkFS_GetIccuModeState();
	if (FdiagChkS_GetIgVoltState() == OFF)
	{
		iInhibitSubStateTemp |= STAT_IGOFF;
	}

	if (iIccuModeState == ICCUMODE_INHIBIT)
	{
		iInhibitSubStateTemp |= STAT_ICCUMODE_INHIBIT;
	}

#ifndef DefDisableCom
	if (FdiagChkFS_GetVcmsState() != VCMS_NORMAL)
	{
		iInhibitSubStateTemp |= STAT_VCMS_INHIBIT;
	}
	if (FdiagChkFS_GetBmsState() != BMS_NORMAL)
	{
		iInhibitSubStateTemp |= STAT_BMS_INHIBIT;
	}
	if (FdiagChkFS_GetCanHsState() != CANHS_NORMAL)
	{
		iInhibitSubStateTemp |= STAT_CANNOTREADY;
	}
	if (FdiagChkFS_GetCanFdState() != CANFD_NORMAL)
	{
		iInhibitSubStateTemp |= STAT_CANNOTREADY;
	}
#endif

#ifndef DefDisbaleInterlock
	if (FdiagChkFS_GetInterLockState() != TRUE)
	{
		iInhibitSubStateTemp |= STAT_INTERLOCK;
	}
#endif

	//	for (i = 0U; i < GateSnsrNum; i++)
	for (i = 0U; i < GateSnsrNum; i++)
	{
		if (FdiagChkS_GetGateState(i) == GATE_NOTREADY)
		{
			iInhibitSubStateTemp |= STAT_GATERDY_INHIBIT;
		}
	}

//	for (i = 0U; i < CurrSnsrNum; i++)
//	{
//		if (FdiagChkIO_GetCurrSnsrState(i) == ICCUCURRSNSR_READY)
//		{
//			iInhibitSubStateTemp |= STAT_ADCSNSR_INHIBIT;
//		}
//	}
	if (FdiagChkIO_GetCurrSnsrState(0) == ICCUCURRSNSR_READY)
    {
        iInhibitSubStateTemp |= STAT_ADCSNSR_INHIBIT;
    }

//	for (i = 0U; i < VoltSnsrNum; i++)
//	{
//		if (FdiagChkIO_GetVoltSnsrState(i) == ICCUVOLTSNSR_READY)
//		{
//			iInhibitSubStateTemp |= STAT_ADCSNSR_INHIBIT;
//		}
//	}
	for (i = 0U; i < 2; i++)
    {
        if (FdiagChkIO_GetVoltSnsrState(i) == ICCUVOLTSNSR_READY)
        {
            iInhibitSubStateTemp |= STAT_ADCSNSR_INHIBIT;
        }
    }

//	for (i = 0U; i < TempSnsrNum; i++)
//	{
//		if (FdiagChkS_GetTempSnsrState(i) == TEMPSNSR_READY)
//		{
//			iInhibitSubStateTemp |= STAT_ADCSNSR_INHIBIT;
//		}
//	}
#if 0
	if (FdiagChkS_GetAuxBatVoltSnsrState() == AUXBATVOLTSNSR_READY)
	{
		iInhibitSubStateTemp |= STAT_ADCSNSR_INHIBIT;
	}

	if (FdiagChkS_GetSmpsVoltSnsrState() == AUXBATVOLT_NORMAL)
	{
		iInhibitSubStateTemp |= STAT_ADCSNSR_INHIBIT;
	}
#endif
	if (FdiagChkS_GetAuxBatVoltState() == AUXBATVOLT_SWUV_INHIBIT)
	{
		iInhibitSubStateTemp |= STAT_AUXBATVOLTUV_INHIBIT;
	}

	//개발 중
	/*
	if (FdiagChkS_GetSmpsVoltState() == SMPSVOLT_SWUV_INHIBIT)
	{
		iInhibitSubStateTemp |= STAT_SMPSVOLTSNSRUV_INHIBIT;
	}
	*/
	if ((iIccuModeState == ICCUMODE_CHARGING)
		|| (iIccuModeState == ICCUMODE_V2G)
		)
	{
		if (FdiagChkCtr_GetGridPllCtrState() == VOLTCTRSTATE_READY_SS)
		{
			iInhibitSubStateTemp |= STAT_GRIDPLL_INHIBIT;
		}
	}

	if (iIccuModeState == ICCUMODE_CHARGING)
	{
		if (FdiagChkIO_GetVoltState(VoltSnsrGrid) == ICCUVOLT_UV_INHIBIT_FLT)
		{
			iInhibitSubStateTemp |= STAT_GRIDVOLTUV_INHIBIT;
		}

		if (FdiagChkIO_GetVoltState(VoltSnsrDCLink) == ICCUVOLT_UV_INHIBIT_FLT)
		{
			iInhibitSubStateTemp |= STAT_DCLINKVOLTUV_INHIBIT;
		}
	}

	if (FdiagChkIO_GetVoltState(VoltSnsrOut) == ICCUVOLT_UV_INHIBIT_FLT)
	{
		iInhibitSubStateTemp |= STAT_OUTVOLTUV_INHIBIT;
	}

#ifdef DefInhibitTest
	if (MonApi_GetInhibitstate() == CLEAR)
	{
		iInhibitSubStateTemp |= STAT_TEST_INHIBIT;
	}
#endif

	giInhibitSubState = iInhibitSubStateTemp;
	return giInhibitSubState;
}

/*----------------------------------------------------------------------------
	Func : Fatal 진단
	Period : 1ms
	Parameter : giFatalSubState
----------------------------------------------------------------------------*/
Uint16 FdiagChkMConFatal()
{
	Uint16 iFatalSubStateTemp = 0U;
	Uint16 iTempSnsrFltFlag = 0U;
	Uint8 i = 0U;
//	for (i = 0U; i < CurrSnsrNum; i++)
//	{
//		if ((FdiagChkIO_GetCurrSnsrState(i) != ICCUCURRSNSR_READY)
//			&& (FdiagChkIO_GetCurrSnsrState(i) != ICCUCURRSNSR_NORMAL)
//			)
//		{
//			iFatalSubStateTemp |= (STAT_PFCCURR1SNSR_FLT << i);	//iFatalSubStateTemp |= (0x0001 << i);
//		}
//	}
	for (i = 0U; i < 1; i++)
    {
        if ((FdiagChkIO_GetCurrSnsrState(i) != ICCUCURRSNSR_READY)
            && (FdiagChkIO_GetCurrSnsrState(i) != ICCUCURRSNSR_NORMAL)
            )
        {
            iFatalSubStateTemp |= (STAT_PFCCURR1SNSR_FLT << i); //iFatalSubStateTemp |= (0x0001 << i);
        }
    }

//	for (i = 0U; i < VoltSnsrNum; i++)
//	{
//		if ((FdiagChkIO_GetVoltSnsrState(i) != ICCUVOLTSNSR_READY)
//			&& (FdiagChkIO_GetVoltSnsrState(i) != ICCUVOLTSNSR_NORMAL)
//			)
//		{
//			iFatalSubStateTemp |= (STAT_GRIDVOLTSNSR_FLT << i);	//iFatalSubStateTemp |= (0x0001 << (i+ CurrSnsrNum));
//		}
//	}
	for (i = 0U; i < 2; i++)
    {
        if ((FdiagChkIO_GetVoltSnsrState(i) != ICCUVOLTSNSR_READY)
            && (FdiagChkIO_GetVoltSnsrState(i) != ICCUVOLTSNSR_NORMAL)
            )
        {
            iFatalSubStateTemp |= (STAT_GRIDVOLTSNSR_FLT << i); //iFatalSubStateTemp |= (0x0001 << (i+ CurrSnsrNum));
        }
    }

	for (i = 0U; i < TempSnsrNum; i++)
	{
		if ((FdiagChkS_GetTempSnsrState(i) != TEMPSNSR_READY)
			&& (FdiagChkS_GetTempSnsrState(i) != TEMPSNSR_NORMAL)
			)
		{
			iTempSnsrFltFlag |= (STAT_TEMPSNSR1_FLT << i);
		}
	}

	if ((FdiagChkS_GetIGVoltSnsrState() != IGVOLTSNSR_READY)
		&&(FdiagChkS_GetIGVoltSnsrState() != IGVOLTSNSR_NORMAL)
		)
	{
		iFatalSubStateTemp |= STAT_IGVOLTSNSR_FLT;
	}

	if ((FdiagChkS_GetAuxBatVoltSnsrState() != AUXBATVOLTSNSR_READY)
		&& (FdiagChkS_GetAuxBatVoltSnsrState() != AUXBATVOLTSNSR_NORMAL)
		)
	{
		iFatalSubStateTemp |= STAT_AUXBATVOLTSNSR_FLT;
	}
	// 개발 중
	if ((FdiagChkS_GetSmpsVoltSnsrState() != SMPSVOLTSNSR_READY)
		&& (FdiagChkS_GetSmpsVoltSnsrState() != SMPSVOLTSNSR_NORMAL)
		)
	{
		iFatalSubStateTemp |= STAT_SMPSVOLTSNSR_FLT;
	}
	if (FdiagChkS_GetMalfuncState() != MALFUNC_NORMAL)
	{
		iFatalSubStateTemp |= STAT_MALFUNC_FLT;
	}


	if ((FdiagChkS_GetRlyState() != RLY_OFF)
		&& (FdiagChkS_GetRlyState() != RLY_ON)
		)
	{
		iFatalSubStateTemp |= STAT_RLYMELT_FLT;
	}

	giFatalSubState = iFatalSubStateTemp;
	return giFatalSubState;
}


/*----------------------------------------------------------------------------
	Func : Fault 진단
	Period : 1ms
	Parameter : giFaultSubState
----------------------------------------------------------------------------*/
Uint16 FdiagChkMConFault()
{
	Uint16 iFaultSubStateTemp = 0U;
	Uint8 i = 0U;
	ICCUMODE_STATE iIccuModeState = FdiagChkFS_GetIccuModeState();
	
	if ((iIccuModeState == ICCUMODE_V2L) || (iIccuModeState == ICCUMODE_V2G))
	{
		for (i = 0U; i < VoltSnsrNum - 1U; i++)
		{
			if (FdiagChkIO_GetVoltState(i) == ICCUVOLT_UV_INHIBIT_FLT)
			{
				iFaultSubStateTemp |= (STAT_GRIDVOLTUV_FLT << i);	//iFaultSubStateTemp |= (0x0001 << i);
			}
		}
	}

	for (i = 0U; i < VoltSnsrNum; i++)
	{
		if ((FdiagChkIO_GetVoltState(i) == ICCUVOLT_SWOV_FLT) || (FdiagChkIO_GetVoltState(i) == ICCUVOLT_HWOV_FLT))
		{
			iFaultSubStateTemp |= (STAT_GRIDVOLTOV_FLT << i);	//iFaultSubStateTemp |= (0x0001 << i);
		}
	}

	for (i = 0U; i < TempSnsrNum; i++)
	{
		if (FdiagApi_GetTempState(i) == TEMP_HIGH_FLT)
		{
			iFaultSubStateTemp |= (STAT_TEMP1HIGH_FLT << i);	//iFaultSubStateTemp |= (0x0001 << (i + VoltSnsrNum));
		}
	}

	//개발 중
/*
	if (FdiagChkS_GetSmpsVoltState(i) == SMPSVOLT_SWOV_FLT)
	{
		iFaultSubStateTemp |= STAT_SMPSVOLTOV_FLT;
	}
*/
	if ((iIccuModeState == ICCUMODE_CHARGING) || (iIccuModeState == ICCUMODE_V2G))
	{
		if (FdiagChkCtr_GetGridPllCtrState() == VOLTCTRSTATE_FLT)
		{
			iFaultSubStateTemp |= STAT_GRIDPLL_FLT;
		}
	}

	if ((iIccuModeState == ICCUMODE_V2L)
		|| (iIccuModeState == ICCUMODE_V2G)
		)
	{
		/*
		if (FdiagChkCtr_GetGridVoltCtrState() == VOLTCTRSTATE_FLT)
		{
			iFaultSubStateTemp |= STAT_GRIDVOLTCTR_FLT;
		}
		*/
	}

	if (FdiagChkCtr_GetDcLinkVoltCtrState() == VOLTCTRSTATE_FLT)
	{
		iFaultSubStateTemp |= STAT_DCLINKVOLTCTR_FLT;
	}

	if (iIccuModeState == ICCUMODE_CHARGING)
	{
		if (FdiagChkCtr_GetOutVoltCtrState() == VOLTCTRSTATE_FLT)
		{
			iFaultSubStateTemp |= STAT_OUTVOLTCTR_FLT;
		}
	}

	if ((iIccuModeState == ICCUMODE_CHARGING) || (iIccuModeState == ICCUMODE_V2G))
	{
		if (FdiagChkCtr_GetPfcCurrCtrState() == CURRCTRSTATE_FLT)
		{
			iFaultSubStateTemp |= (STAT_INDCURRCTR_FAULT);
		}
	}

	if (FdiagChkCtr_GetDcDcCurrCtrState() == CURRCTRSTATE_FLT)
	{
		iFaultSubStateTemp |= (STAT_DCDCCURRCTR_FAULT);
	}

	giFaultSubState = iFaultSubStateTemp;
	return giFaultSubState;

}


/*----------------------------------------------------------------------------
	Func : Resume 진단
	Period : 1ms
	Parameter : giResumeSubState
----------------------------------------------------------------------------*/
Uint16 FdiagChkMConResume()
{
	Uint16 iResumeSubStateTemp = 0U;
	Uint8 i = 0U;

	for (i = 0U; i < CurrSnsrNum; i++)
	{
		if (FdiagChkIO_GetCurrState(i) != ICCUCURR_NORMAL)
		{
			iResumeSubStateTemp |= (STAT_PFCCURR1_RESUME << i);	//iResumeSubStateTemp |= (0x0001 << i);
		}
	}

	for (i = 0U; i < GateSnsrNum; i++)
	{
		if (FdiagChkS_GetGateState(i) == GATE_HWFLT)
		{
			iResumeSubStateTemp |= (STAT_PFCGATE_RESUME << i );	///iFaultSubStateTemp |= (0x0001 << (i + CurrSnsrNum));
		}

	}

#if 0
	if (FdiagChkS_GetPwmoutState() != PWM_NORMAL)
	{
		iResumeSubStateTemp |= STAT_PWMOUT_RESUME;
	}
#endif

	giResumeSubState = iResumeSubStateTemp;
	return giResumeSubState;
}


/*----------------------------------------------------------------------------
	Func : Normal 진단
	Period : 1ms
	Parameter : giNormalSubState
----------------------------------------------------------------------------*/
Uint16 FdiagChkMConNormal()
{
	Uint16 iNormalSubStateTemp = 0;
	Uint8 iIccuModeState = FdiagChkFS_GetIccuModeState();

	if (iIccuModeState == ICCUMODE_CHARGING)
	{
		iNormalSubStateTemp |= STAT_ICCUCHARGING;
	}
	if ((iIccuModeState == ICCUMODE_V2L)
		|| (iIccuModeState == ICCUMODE_V2G)
		)
	{
		iNormalSubStateTemp |= STAT_ICCUDISCHARGING;
	}

	if (FdiagChkS_GetOperModeState() == OPERATING_PFCRLYON)
	{
		iNormalSubStateTemp |= STAT_PFCRLYON;
	}
	if (FdiagChkS_GetOperModeState() == OPERATING_PFCSOFTSTART)
	{
		iNormalSubStateTemp |= STAT_PFCSOFTSTART;
	}
	if (FdiagChkS_GetOperModeState() == OPERATIN_PFCON)
	{
		iNormalSubStateTemp |= STAT_PFCON;
	}
	if (FdiagChkS_GetOperModeState() == OPERATIN_DCDCSOFTSTART)
	{
		iNormalSubStateTemp |= STAT_DCDCSOFTSTART;
	}
	if (FdiagChkS_GetOperModeState() == OPERATIN_DCDCON)
	{
		iNormalSubStateTemp |= STAT_DCDCON;
	}
	if (FdiagChkS_GetOperModeState() == OPERATIN_CCCHARGING)
	{
		iNormalSubStateTemp |= STAT_CCCHARGING;
	}
	if (FdiagChkS_GetOperModeState() == OPERATIN_CPCHARGING)
	{
		iNormalSubStateTemp |= STAT_CPCHARGING;
	}
	if (FdiagChkS_GetOperModeState() == OPERATIN_CVCHARGING)
	{
		iNormalSubStateTemp |= STAT_CVCHARGING;
	}


	if ((FdiagChkS_GetDeratingState() == DERATING_TEMP)
		|| (FdiagChkS_GetDeratingState() == DERATING_GRIDVOLTTEMP)
		)
	{
		iNormalSubStateTemp |= STAT_TEMPDEREATING;
	}
	if ((FdiagChkS_GetDeratingState() == DERATING_GRIDVOLT)
		|| (FdiagChkS_GetDeratingState() == DERATING_GRIDVOLTTEMP)
		)
	{
		iNormalSubStateTemp |= STAT_GRIDVOLTDEREATING;
	}

#ifndef DefDisableCom
	if (FdiagChkFS_GetCanHsState() == CANHS_NORMAL)
	{
		iNormalSubStateTemp |= STAT_CANHS;
	}
	if (FdiagChkFS_GetCanFdState() == CANFD_NORMAL)
	{
		iNormalSubStateTemp |= STAT_CANFD;
	}
#endif
	giNormalSubState = iNormalSubStateTemp;
	return giNormalSubState;
}

#if 0
/*----------------------------------------------------------------------------
	Func : ICCU PFC State 진단
	Period : 1ms
	Parameter : giRunPfcState
----------------------------------------------------------------------------*/
void FdiagChkMRunPfcState(void)
{
	Uint16 giRunPfcState;
	switch (giRunPfcState)
	{
	case STAT_PFCINHIBIT:
		break;
	case STAT_PFCREADY:
		break;
	case STAT_PFCNORMAL:
		break;
	default:
		break;
	}

}
#endif




/*----------------------------------------------------------------------------
	Func : ICCU Ready 진단
	Period : 1ms
	Parameter : giIccuReadyState
----------------------------------------------------------------------------*/
Uint16 FdiagChkMConIccuReady(void)
{
	Uint16 IiccuReadyState = 0U;

	if (((giCbAbnormalSubState | giFatalSubState | giFaultSubState | giResumeSubState) == 0x0000)
		&& ((giInhibitSubState & ~STAT_VCMS_INHIBIT) == 0)
		)
	{
		IiccuReadyState = TRUE;
	}
	else
	{
		IiccuReadyState = FALSE;
	}
	giIccuReadyState = IiccuReadyState;
	return giIccuReadyState;
}


/*----------------------------------------------------------------------------
	Func : ICCU Controllable 진단
	Period : 1ms
	Parameter : giIccuControllable
----------------------------------------------------------------------------*/
Uint16 FdiagChkMConFdcControllable(void)
{
	Uint16 IiccuControllable = 0U;
	if ((giCbAbnormalSubState | giFatalSubState | giFaultSubState | giResumeSubState | giInhibitSubState) == 0x0000)
	{
		IiccuControllable = TRUE;
	}
	else
	{
		IiccuControllable = FALSE;
	}
	giIccuControllable = IiccuControllable;
	return giIccuControllable;
}
