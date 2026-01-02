/*============================================================================
	Includes
============================================================================*/
#include "FdiagApi.h"
#include "FdiagChkM.h"
#include "FdiagChkIO.h"
#include "FdiagChkS.h"
#include "FdiagChkCtr.h"
#include "FdiagChkFS.h"


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


/*============================================================================
	Private Variables/Constants
============================================================================*/

/*============================================================================
	Function Prototypes
============================================================================*/

/*============================================================================
	Function Implementations
============================================================================*/

//ChkM Api Function
void FdiagApi_ChkMIsrCtr(void)							{FdiagChkMIsrCtr();}
void FdiagApi_ChkMTask100us(void)						{FdiagChkMTask100us();}
void FdiagApi_ChkMTask1ms(void)							{FdiagChkMTask1ms();}
void FdiagApi_ChkMTask10ms(void)						{FdiagChkMTask10ms();}
void FdiagApi_ChkMTask100ms(void)						{FdiagChkMTask100ms();}

#if 0
Uint16 FdiagApi_GetChkConCbAbnormal()					{ return giCbAbnormalSubState;}
Uint16 FdiagApi_GetChkConInhibit()						{ return giInhibitSubState;}
Uint16 FdiagApi_GetChkConFatal()						{ return giFatalSubState;}
Uint16 FdiagApi_GetChkConFault()						{ return giFaultSubState;}
Uint16 FdiagApi_GetChkConResume()						{ return giResumeSubState;}
Uint16 FdiagApi_GetChkConNormal()						{ return giNormalSubState;}
#endif

Uint16 FdiagApi_GetChkConCbAbnormal(void)				{ return FdiagChkMConCbAbnormal();}
Uint16 FdiagApi_GetChkConFatal(void)					{ return FdiagChkMConFatal(); }
Uint16 FdiagApi_GetChkConFault(void)					{ return FdiagChkMConFault(); }
Uint16 FdiagApi_GetChkConResume(void)					{ return FdiagChkMConResume(); }
Uint16 FdiagApi_GetChkConInhibit(void)					{ return FdiagChkMConInhibit(); }
Uint16 FdiagApi_GetChkConNormal(void)					{ return FdiagChkMConNormal(); }
Uint16 FdiagApi_GetChkConHwIsrPin(void)					{ return giHwIsrPinState;}

//ChksFs Api Function 
ICCUMODE_STATE FdiagApi_GetIccuModeState(void)			{return FdiagChkFS_GetIccuModeState(); }


//ChkS Api Function
TEMP_STATE FdiagApi_GetTempState(Uint16 SnsrNum)		{ return giTempState[SnsrNum]; }
GATE_STATE FdiagApi_GetGateState(Uint16 SnsrNum)		{ return giGateState[SnsrNum]; }
DERATING_STATE FdiagApi_GetDeratingState(void)			{ return FdiagChkS_GetDeratingState(); }
RLY_STATE FdiagApi_GetRlyState(void)					{ return FdiagChkS_GetRlyState();}
AUXBATVOLT_STATE FdiagApi_GetAuxBatVoltState(void)		{ return giAuxBatVoltState; }

//ChkIO Api Fuction
ICCUVOLTSNSR_STATE FdiagApi_GetVoltSnsrState(Uint16 SnsrNum)	{ return giVoltSnsrState[SnsrNum]; }

//ChkCtr Api Fuction
CURRCTRSTATE FdiagApi_GetPfcCurrCtrState()						{ return giPfcLCurrCtrState; }
CURRCTRSTATE FdiagApi_GetDcDcCurrCtrState()						{ return gIDcDcOutCurrCtrState; }
void FdiagApi_ChagePfcCurrCtrState(CURRCTRSTATE CtrState)		{ giPfcLCurrCtrState = CtrState; }
void FdiagApi_ChageDcDcCurrCtrState(CURRCTRSTATE CtrState)		{ gIDcDcOutCurrCtrState = CtrState; }

VOLTCTRSTATE FdiagApi_GetGridPllCtrState(void)					{ return giGridVoltCtrState; }
VOLTCTRSTATE FdiagApi_GetPfcDcLinkVoltCtrState(void)			{ return giPfcDcLinkVoltCtrState; }
VOLTCTRSTATE FdiagApi_GetDcDcLinkVoltCtrState(void)				{ return giV2XDcLinkVoltCtrState; }
VOLTCTRSTATE FdiagApi_GetOutVoltCtrState(void)					{ return giOutVoltCtrState; }
VOLTCTRSTATE FdiagApi_GetV2LVoltCtrState(void)					{ return giV2LVoltCtrState; }

void FdiagApi_ChangeGridPllState(VOLTCTRSTATE state)			{ giGridVoltCtrState = state; }
void FdiagApi_ChangePfcDcLinkVoltCtrState(VOLTCTRSTATE CtrState){ giPfcDcLinkVoltCtrState= CtrState; }
void FdiagApi_ChangeDcDcLinkVoltCtrState(VOLTCTRSTATE CtrState) { giV2XDcLinkVoltCtrState = CtrState; }
void FdiagApi_ChangeOutVoltCtrState(VOLTCTRSTATE CtrState)		{ giOutVoltCtrState = CtrState; }
void FdiagApi_ChangeV2LVoltCtrState(VOLTCTRSTATE CtrState)		{ giV2LVoltCtrState = CtrState; }
