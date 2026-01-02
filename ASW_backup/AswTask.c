/*
 * AswSeq.c
 *
 *  Created on: 2023. 1. 4.
 *      Author: poweryhs
 */


/*============================================================================
    Includes
============================================================================*/
#include <ASW_backup/AswCal.h>
#include <ASW_backup/AswISR.h>
#include <ASW_backup/AswSeq.h>
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
Uint8 giInhibitTest                 = 0;
Uint8 giObcInhibitTest              = 0;
Uint16 giInhibitSubState			= 0;
Uint16 giFaultSubState				= 0;
Uint16 giNormalSubState				= 0;
OBCLDCMODE_STATE giObcLdcModeState	= OBCLDCMODE_CHARGING;
//OBCLDCMODE_STATE giObcLdcModeState	= OBCLDCMODE_INHIBIT;



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
	Func : Inhibit 진단
	Period : 1ms
	Parameter : giInhibitSubState
----------------------------------------------------------------------------*/
Uint16 FdiagChkMConInhibit()
{
	Uint16 iInhibitSubStateTemp = 0;

#ifdef DefInhibitTest
	if (giInhibitTest == CLEAR)
	{
		iInhibitSubStateTemp |= STAT_TEST_INHIBIT;
	}
#endif
	giInhibitSubState = iInhibitSubStateTemp;
	return giInhibitSubState;
}


/*----------------------------------------------------------------------------
	Func : Fault 진단
	Period : 1ms
	Parameter : giFaultSubState
----------------------------------------------------------------------------*/
Uint16 FdiagChkMConFault()
{
	Uint16 iFaultSubStateTemp = 0;
	Uint8 i = 0;


	for (i = 0; i < CurrSnsrNum; i++)
	{
		if ((FdiagChkIO_GetCurrState(i) == CURR_SWOC_FLT)
			|| (FdiagChkIO_GetCurrState(i) == CURR_HWOC_FLT)
			)
		{
			iFaultSubStateTemp |= (STAT_OBCINOC_FLT << i);	//iFaultSubStateTemp |= (0x0001 << i);
		}
	}

	for (i = 0; i < VoltSnsrNum; i++)
	{
		if ((FdiagChkIO_GetVoltState(i) == VOLT_SWOV_FLT)
			|| (FdiagChkIO_GetVoltState(i) == VOLT_HWOV_FLT)
			)
		{
			iFaultSubStateTemp |= (STAT_OBCINOV_FLT << i);	//iFaultSubStateTemp |= (0x0001 << i);
		}
	}

	giFaultSubState = iFaultSubStateTemp;
	return giFaultSubState;
}


/*----------------------------------------------------------------------------
	Func : Normal 진단
	Period : 1ms
	Parameter : giNormalSubState
----------------------------------------------------------------------------*/
Uint16 FdiagChkMConNormal()
{
	Uint16 iNormalSubStateTemp = 0;

	giNormalSubState = iNormalSubStateTemp;
	
	if (giObcLdcModeState == OBCLDCMODE_CHARGING)
	{
		giNormalSubState |= STAT_CHARGING_MODE;
	}
	if (giObcLdcModeState == OBCLDCMODE_DISCHARGING)
	{
		giNormalSubState |= STAT_DISCHARGING_MODE;
	}
	if (giObcLdcModeState == OBCLDCMODE_SEPERATELDC)
	{
		giNormalSubState |= STAT_SEPERATELDC_MODE;
	}

	return giNormalSubState;
}
