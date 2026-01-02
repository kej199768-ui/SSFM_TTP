#ifndef _FDIAGCHKFS_H
#define _FDIAGCHKFS_H

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

/*============================================================================
	Function Prototypes
============================================================================*/
void FdiagChkFSIsrCtr(void);
void FdiagChkFSTask100us(void);
void FdiagChkFSTask1ms(void);
void FdiagChkFSTask10ms(void);
void FdiagChkFSTask100ms(void);


Uint16 FdiagChkFS_GetEcuPostRunState(void);
Uint16 FdiagChkFS_GetIccuModeState();
Uint16 FdiagChkFS_GetVcmsState(void);
Uint16 FdiagChkFS_GetFcuState(void);
Uint16 FdiagChkFS_GetBmsState(void);
Uint16 FdiagChkFS_GetInterLockState(void);
Uint16 FdiagChkFS_GetCanHsState(void);
Uint16 FdiagChkFS_GetCanFdState(void);



#endif
