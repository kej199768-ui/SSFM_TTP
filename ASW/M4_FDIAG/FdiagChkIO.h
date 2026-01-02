#ifndef _FdiagChkIO_h
#define _FdiagChkIO_h

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
//current diag
extern ICCUCURRSNSR_STATE giCurrSnsrState[CurrSnsrNum];
extern ICCUCURR_STATE giCurrState[CurrSnsrNum];
extern Uint16 giCurrHwOcIsrFlag[CurrSnsrNum];

//voltage diag
extern ICCUVOLTSNSR_STATE giVoltSnsrState[VoltSnsrNum];
extern ICCUVOLT_STATE giVoltState[VoltSnsrNum];

/*============================================================================
	Global Function Prototypes
============================================================================*/
void FdiagChkIOIsrCtr(void);
void FdiagChkIOTask100us(void);
void FdiagChkIOTask1ms(void);
void FdiagChkIOTask10ms(void);
void FdiagChkIOTask100ms(void);

ICCUVOLTSNSR_STATE FdiagChkIO_GetVoltSnsrState(Uint16 SnsrNum);
ICCUVOLT_STATE FdiagChkIO_GetVoltState(Uint16 SnsrNum);

ICCUCURRSNSR_STATE FdiagChkIO_GetCurrSnsrState(Uint16 SnsrNum);
ICCUCURR_STATE FdiagChkIO_GetCurrState(Uint16 SnsrNum);

#endif
