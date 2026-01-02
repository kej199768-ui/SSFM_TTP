/*============================================================================
	Includes
============================================================================*/
#include "FdiagChkS.h" 
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
ICCUMODE_STATE giIccuModeState		= 0U;
Uint16 giVcmsState			= 0U;
Uint16 giBmsState			= 0U;
Uint16 giFcuState			= 0U;
Uint16 giInterlockState		= 0U;
Uint16 giCanHsState			= 0U;
Uint16 giCanFdState			= 0U;
/*============================================================================
	Private Variables/Constants
============================================================================*/

/*============================================================================
	Function Prototypes
============================================================================*/

/*============================================================================
	Function Implementations
============================================================================*/
void FdiagChkFSIsrCtr(void)
{

}

void FdiagChkFSTask100us(void)
{

}

void FdiagChkFSTask1ms(void)
{
	giIccuModeState = ICCUMODE_CHARGING;	//Charging
//	giIccuModeState = ICCUMODE_V2L;	//V2L
//	giIccuModeState = ICCUMODE_V2G;	//V2G
}

void FdiagChkFSTask10ms(void)
{

}

void FdiagChkFSTask100ms(void)
{

}

ICCUMODE_STATE FdiagChkFS_GetIccuModeState(){ return giIccuModeState; }
Uint16 FdiagChkFS_GetEcuPostRunState()		{ return giEcuRunState; }
Uint16 FdiagChkFS_GetVcmsState()			{ return giVcmsState; }
Uint16 FdiagChkFS_GetBmsState()				{ return giBmsState; }
Uint16 FdiagChkFS_GetFcuState()				{ return giFcuState; }
Uint16 FdiagChkFS_GetInterLockState()		{ return giInterlockState; }
Uint16 FdiagChkFS_GetCanHsState()			{ return giCanHsState; }
Uint16 FdiagChkFS_GetCanFdState()			{ return giCanFdState; }



