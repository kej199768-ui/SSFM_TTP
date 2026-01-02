/*============================================================================
	Includes
============================================================================*/
#include "../AswCommon.h"
#include "CtrApi.h"
#include "CtrMain.h"
#include "CtrPfc.h"
#include "CtrDcDc.h"
#include "CtrCal.h"

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
//CtrM Api Function
void CtrApi_CtrMIsrCtr(void)						{ CtrCtrMIsrCtr(); }
void CtrApi_CtrMTask100us(void)						{ CtrCtrMTask100us(); }
void CtrApi_CtrMTask1ms(void)						{ CtrCtrMTask1ms(); }
void CtrApi_CtrMTask10ms(void)						{ CtrCtrMTask10ms(); }
void CtrApi_CtrMTask100ms(void)						{ CtrCtrMTask100ms(); }

float CtrApi_GetVgridMag(void)						{ return gfVGrid_Mag; }
float CtrApi_GetVgridMagLpf(void)					{ return gfVGrid_Mag_LPF; }
dq CtrApi_GetGriddqVolt(void)						{ return gdqVgrid_dqe;}
dq CtrApi_GetGriddqVoltLpf(void)					{ return gdqVgrid_dqe_LPF;}
float CtrApi_Getfgrid(void)							{ return gffgrid; }
float CtrApi_GetfgridLpf(void)						{ return gffgrid_LPF; }
float CtrApi_GetfV2L(void)							{ return gffV2L; }
float CtrApi_GetVV2L(void)							{ return gdqVgrid_dqe.q; }
float CtrApi_GetVV2LRef(void)						{ return gfVV2LRef; }

float CtrApi_GetIPfcLRef(void)						{ return gfIPfcLRef; }
//float CtrApi_GetIDcDcOutRef(void)					{ return gfIDcDcOutRef; }
//float CtrApi_GetIDcDcOutMRef(void)					{ return gfIDcDcMOutRef; }

float CtrApi_GetVPfcLinkRef(void)					{ return gfVPfcDcLinkRef; }
//float CtrApi_GetVDcDcLinkRef(void)					{ return gfVV2XDcLinkRef; }
//float CtrApi_GetVOutRef(void)						{ return gfVOutRef; }


#if 0
float CtrApi_GetInVoltRefCmd()						{ return gfGridVoltCtrRef; }
float CtrApi_GetInCurrLimitCmd()					{ return gfInCurrLimit; }
#endif

