#ifndef ASW_M3_CTR_CTRAPI_H
#define ASW_M3_CTR_CTRAPI_H

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
void CtrApi_CtrMIsrCtr(void);
void CtrApi_CtrMTask100us(void);
void CtrApi_CtrMTask1ms(void);
void CtrApi_CtrMTask10ms(void);
void CtrApi_CtrMTask100ms(void);

float CtrApi_GetVgridMag(void);
float CtrApi_GetVgridMagLpf(void);
dq CtrApi_GetGriddqVolt(void);
dq CtrApi_GetGriddqVoltLpf(void);
float CtrApi_Getfgrid(void);
float CtrApi_GetfgridLpf(void);
float CtrApi_GetfV2L(void);
float CtrApi_GetVV2L(void);
float CtrApi_GetVV2LRef(void);
float CtrApi_GetIPfcLRef(void);
//float CtrApi_GetIDcDcOutRef(void);
//float CtrApi_GetIDcDcOutMRef(void);

float CtrApi_GetVPfcLinkRef(void);
//float CtrApi_GetVDcDcLinkRef(void);
//float CtrApi_GetVOutRef(void);

#endif
