#ifndef _FDIAGCHKM_H
#define _FDIAGCHKM_H

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
	Extern variables
============================================================================*/
extern Uint16 giCbAbnormalSubState;
extern Uint16 giInhibitSubState;
extern Uint16 giFatalSubState;
extern Uint16 giFaultSubState;
extern Uint16 giResumeSubState;
extern Uint16 giNormalSubState;
extern Uint16 giHwIsrPinState;
extern Uint16 gIiccuRedayState;
extern Uint16 giIccuControllableState;

/*============================================================================
	Extern Function Prototypes
============================================================================*/
void FdiagChkMIsrCtr(void);
void FdiagChkMTask100us(void);
void FdiagChkMTask1ms(void);
void FdiagChkMTask10ms(void);
void FdiagChkMTask100ms(void);

Uint16 FdiagChkMConCbAbnormal(void);
Uint16 FdiagChkMConFatal(void);
Uint16 FdiagChkMConFault(void);
Uint16 FdiagChkMConResume(void);
Uint16 FdiagChkMConNormal(void);
Uint16 FdiagChkMConInhibit(void);
Uint16 FdiagChkMConIccuReady(void);
Uint16 FdiagChkMConFdcControllable(void);

#endif
