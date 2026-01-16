#ifndef ASW_M3_CTR_CTRPFC_H
#define ASW_M3_CTR_CTRPFC_H

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
extern float gfVGrid_Mag;
extern float gfVGrid_Mag_LPF;
extern dq gdqVgrid_dqe;
extern dq gdqVgrid_dqe_LPF;
extern Uint16 giVPfcSoftStart_Timer;
extern float gffgrid;
extern float gffgrid_LPF;
extern float gffV2L;
extern float gfVV2LRef;
extern float gfVPfcDcLinkRef;
extern float gfIPfcLRef;

extern float gfVPfcDcLinkCmd;

extern Uint16 guHS_en;
extern Uint16 guLS_en;
extern float gfHS_duty;
extern float gfLS_duty;

extern Uint16 giPLL_inhibit;
extern Uint16 giPwmTest_inhibit;
extern Uint16 giIController_inhibit;
extern Uint16 giController_inhibit;
extern Uint16 giTest_type;
extern float  gfIin_ref_test;

extern float gfFMFreqCenter;
extern float gfFMFreqDelta;
extern float gfFMModulationFreq_Slow;
extern float gfFMModulationFreq_Fast;


/*============================================================================
	Function Prototypes
============================================================================*/
extern void CtrPfcIsrCtr(void);
extern void CtrPfcTask100us(void);
extern void CtrPfcTask1ms(void);
extern void CtrPfcTask10ms(void);
extern void CtrPfcTask100ms(void);

extern void CtrPfcPwmTest(void);

extern void CtrDisPwm(void);

#endif
