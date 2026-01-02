/*
 * BswPwm.c
 *
 *  Created on: 2022. 11. 29.
 *      Author: poweryhs
 */

/*============================================================================
    Includes
============================================================================*/
#include "F28x_Project.h"
#include "BswPwm.h"
#include "BswCal.h"
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
volatile struct EPWM_REGS *ePWM_Regs[] = {
        0,
        &EPwm1Regs,
        &EPwm2Regs,
        &EPwm3Regs,
        &EPwm4Regs,
        &EPwm5Regs,
        &EPwm6Regs,
        &EPwm7Regs,
        &EPwm8Regs,
        &EPwm9Regs,
        &EPwm10Regs,
        &EPwm11Regs,
        &EPwm12Regs
};

float gfPwmFreq = 0.;
float gfduty_test = 0.;


/*============================================================================
    Private Variables/Constants
============================================================================*/

/*============================================================================
    Function Prototypes
============================================================================*/
void BswPwm_InitFltPWM(Uint8 ch);
/*============================================================================
    Function Implementations
============================================================================*/

// High Speed
void InitEPwm1Config()                                             
{
    EALLOW;

    ClkCfgRegs.PERCLKDIVSEL.bit.EPWMCLKDIV  = 0x0;
    EPwm1Regs.TBCTL.bit.HSPCLKDIV           = TB_DIV1;              // Clock ratio to SYSCLKOUT
    EPwm1Regs.TBCTL.bit.CLKDIV              = TB_DIV1;

    BswPwm_ForceLowPwm(1);
    //BswPwm_SetFreqUpCnt(1, gfPwmFreqInitCal);
    BswPwm_SetFreqUpDownCnt(1, gfPwmFreqInitCal);

    EPwm1Regs.TBCTR                         = 0;                    // Clear counter
    EPwm1Regs.TBPHS.bit.TBPHS               = 0;//                    // Phase is 0
    EPwm1Regs.TBCTL.bit.PHSDIR              = TB_UP;              // Count UP on sync (=180 deg)

    // Setup TBCLK
    EPwm1Regs.TBCTL.bit.CTRMODE             = TB_COUNT_UPDOWN;      // Count up down
    EPwm1Regs.TBCTL.bit.PHSEN               = TB_ENABLE;            // Enable phase loading
    EPwm1Regs.TBCTL.bit.PRDLD               = TB_SHADOW;
    EPwm1Regs.EPWMSYNCINSEL.bit.SEL         = SYNC_IN_SRC_DISABLE_ALL;
    EPwm1Regs.EPWMSYNCOUTEN.bit.ZEROEN      = 0;      // **

    EPwm1Regs.CMPCTL.bit.SHDWAMODE          = CC_SHADOW;            // Load registers every ZERO
    EPwm1Regs.CMPCTL.bit.SHDWBMODE          = CC_SHADOW;
    EPwm1Regs.CMPCTL.bit.LOADAMODE          = CC_CTR_PRD;
    EPwm1Regs.CMPCTL.bit.LOADBMODE          = CC_CTR_PRD;

    //Initialize
    EPwm1Regs.CMPA.bit.CMPA                 = 0;

    // Set actions
//    EPwm1Regs.AQCTLA.bit.ZRO                = AQ_CLEAR;
//    EPwm1Regs.AQCTLA.bit.PRD                = AQ_SET;
    EPwm1Regs.AQCTLA.bit.CAU                = AQ_CLEAR;
    EPwm1Regs.AQCTLA.bit.CAD                = AQ_SET;
    ////////////////////////////////////////////////////////////
    EPwm1Regs.CMPB.bit.CMPB                 = 0;
    EPwm1Regs.AQCTLB.bit.CBU                = AQ_SET;
    EPwm1Regs.AQCTLB.bit.CBD                = AQ_CLEAR;
    ////////////////////////////////////////////////////////////

    //Q2 (HS LS)
    //Setup DeadBand
    EPwm1Regs.DBCTL.bit.OUT_MODE            = DB_FULL_ENABLE;
    EPwm1Regs.DBCTL.bit.IN_MODE             = DBA_ALL;
    EPwm1Regs.DBCTL.bit.POLSEL              = DB_ACTV_HIC;      //ePwm1B A의 반전 동작
    EPwm1Regs.DBRED.bit.DBRED               = giDeadBandCal;    //20 : 100ns
    EPwm1Regs.DBFED.bit.DBFED               = giDeadBandCal;

    //Event Trigger
    EPwm1Regs.ETSEL.bit.SOCAEN              = 1;
    EPwm1Regs.ETSEL.bit.SOCASEL             = ET_CTR_ZERO;
    EPwm1Regs.ETPS.bit.SOCAPRD              = ET_1ST;

    EPwm1Regs.ETSEL.bit.SOCBEN              = 1;
    EPwm1Regs.ETSEL.bit.SOCBSEL             = ET_CTR_PRD;
    EPwm1Regs.ETPS.bit.SOCBPRD              = ET_1ST;

    EDIS;
}

// Low Speed
void InitEPwm2Config()
{
    EALLOW;

    ClkCfgRegs.PERCLKDIVSEL.bit.EPWMCLKDIV  = 0x0;
    EPwm2Regs.TBCTL.bit.HSPCLKDIV           = TB_DIV1;              // Clock ratio to SYSCLKOUT
    EPwm2Regs.TBCTL.bit.CLKDIV              = TB_DIV1;

    BswPwm_ForceLowPwm(2);
    //BswPwm_SetFreqUpCnt(2, gfPwmFreqInitCal);
    BswPwm_SetFreqUpDownCnt(2, gfPwmFreqInitCal);

    EPwm2Regs.TBCTR                         = 0;                    // Clear counter
    EPwm2Regs.TBPHS.bit.TBPHS               = 0;                    // Phase is 0
    EPwm2Regs.TBCTL.bit.PHSDIR              = TB_UP;                // Count DOWN on sync (=180 deg)

    // Setup TBCLK
    EPwm2Regs.TBCTL.bit.CTRMODE             = TB_COUNT_UPDOWN;          // Count up
    EPwm2Regs.TBCTL.bit.PHSEN               = TB_ENABLE;            // Enable phase loading
    EPwm2Regs.TBCTL.bit.PRDLD               = TB_SHADOW;
    EPwm2Regs.EPWMSYNCINSEL.bit.SEL         = SYNC_IN_SRC_DISABLE_ALL;
    EPwm2Regs.EPWMSYNCOUTEN.bit.ZEROEN      = 1;      // **

    EPwm2Regs.CMPCTL.bit.SHDWAMODE          = CC_SHADOW;            // Load registers every ZERO
    EPwm2Regs.CMPCTL.bit.SHDWBMODE          = CC_SHADOW;
    EPwm2Regs.CMPCTL.bit.LOADAMODE          = CC_CTR_ZERO;
    EPwm2Regs.CMPCTL.bit.LOADBMODE          = CC_CTR_ZERO;

    //Set Actions
    EPwm2Regs.CMPA.bit.CMPA                 = 0;

    //Q3 (LS HS)
    EPwm2Regs.AQCTLA.bit.ZRO                = AQ_SET;
    EPwm2Regs.AQCTLA.bit.PRD                = AQ_CLEAR;
//    EPwm2Regs.AQCTLA.bit.CAU                = AQ_CLEAR;
//    EPwm2Regs.AQCTLA.bit.CAD                = AQ_SET;

    //Setup deadband
    EPwm2Regs.DBCTL.bit.OUT_MODE            = DB_FULL_ENABLE;
    EPwm2Regs.DBCTL.bit.IN_MODE             = DBA_ALL;
    EPwm2Regs.DBCTL.bit.POLSEL              = DB_ACTV_HIC;
    EPwm2Regs.DBRED.bit.DBRED               = giDeadBandCal;
    EPwm2Regs.DBFED.bit.DBFED               = giDeadBandCal;

    EDIS;
}

//SR1
void InitEPwm3Config()
{
//    EALLOW;
//    ClkCfgRegs.PERCLKDIVSEL.bit.EPWMCLKDIV = 0x0;
//    EPwm3Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;        // Clock ratio to SYSCLKOUT
//    EPwm3Regs.TBCTL.bit.CLKDIV = TB_DIV1;
//    /**********************************************************************
//    EPWM3 Config
//    **********************************************************************/
//
//    BswPwm_ForceLowPwm(3);
//    BswPwm_SetFreqUpCnt(3, gfPwmFreqInitCal);
//
//    EPwm3Regs.TBCTR                     = 0;                        // Clear counter
//    EPwm3Regs.TBPHS.bit.TBPHS           = 0;              // DPHS       // Phase is 0
//    EPwm3Regs.TBCTL.bit.PHSDIR          = TB_UP;                // Count DOWN on sync (=180 deg)
//
//    // Setup TBCLK
//    EPwm3Regs.TBCTL.bit.CTRMODE         = TB_COUNT_UP;      // Count up
//    EPwm3Regs.TBCTL.bit.PHSEN           = TB_ENABLE;          // Enable phase loading
//    EPwm3Regs.EPWMSYNCINSEL.bit.SEL     = SYNC_IN_SRC_SYNCOUT_EPWM2;         // 정방향
//    EPwm3Regs.EPWMSYNCOUTEN.bit.ZEROEN  = 0;
//
//    EPwm3Regs.CMPCTL.bit.SHDWAMODE      = CC_SHADOW;            // Load registers every ZERO
//    EPwm3Regs.CMPCTL.bit.SHDWBMODE      = CC_SHADOW;
//    EPwm3Regs.CMPCTL.bit.LOADAMODE      = CC_CTR_ZERO;
//    EPwm3Regs.CMPCTL.bit.LOADBMODE      = CC_CTR_ZERO;
//
//    EPwm3Regs.CMPA.bit.CMPA             = 0;        //NcountTs_UPDOWN>>1 + DPHS-DABPHS - Margin, DPHS-DABPHS < 0 ==> 0
//    EPwm3Regs.AQCTLA.bit.PRD            = AQ_SET;
////    EPwm3Regs.AQCTLA.bit.ZRO            = AQ_SET;
//    EPwm3Regs.AQCTLA.bit.CAU            = AQ_CLEAR;//AQ_SET;
//
//    // Active Low PWMs - Setup Deadband
//    EPwm3Regs.DBCTL.bit.OUT_MODE        = DB_FULL_ENABLE;
//    EPwm3Regs.DBCTL.bit.POLSEL          = DB_ACTV_HI;
//    EPwm3Regs.DBCTL.bit.IN_MODE         = DBA_ALL;
//    EPwm3Regs.DBRED.bit.DBRED           = giDeadBandSrCal;   //20 : 100ns
//
//    EDIS;
}

//SR2
void InitEPwm4Config()
{
//    EALLOW;
//    ClkCfgRegs.PERCLKDIVSEL.bit.EPWMCLKDIV = 0x0;
//    EPwm4Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;        // Clock ratio to SYSCLKOUT
//    EPwm4Regs.TBCTL.bit.CLKDIV = TB_DIV1;
//    /**********************************************************************
//    EPWM3 Config
//    **********************************************************************/
//
//    BswPwm_ForceLowPwm(4);
//    BswPwm_SetFreqUpCnt(4, gfPwmFreqInitCal);
//
//    EPwm4Regs.TBCTR                 = 0;                        // Clear counter
//    EPwm4Regs.TBPHS.bit.TBPHS       = 0;              // DPHS       // Phase is 0
//    EPwm4Regs.TBCTL.bit.PHSDIR      = TB_UP;                // Count DOWN on sync (=180 deg)
//
//    // Setup TBCLK
//    EPwm4Regs.TBCTL.bit.CTRMODE     = TB_COUNT_UP;      // Count up
//    EPwm4Regs.TBCTL.bit.PHSEN       = TB_ENABLE;          // Enable phase loading
//    EPwm4Regs.EPWMSYNCINSEL.bit.SEL = SYNC_IN_SRC_SYNCOUT_EPWM2;         // 정방향
//    EPwm4Regs.EPWMSYNCOUTEN.bit.ZEROEN = 0;
//
//
//    EPwm4Regs.CMPCTL.bit.SHDWAMODE  = CC_SHADOW;            // Load registers every ZERO
//    EPwm4Regs.CMPCTL.bit.SHDWBMODE  = CC_SHADOW;
//    EPwm4Regs.CMPCTL.bit.LOADAMODE  = CC_CTR_ZERO;
//    EPwm4Regs.CMPCTL.bit.LOADBMODE  = CC_CTR_ZERO;
//    EPwm4Regs.CMPA.bit.CMPA         = 0;//NcountTs_UPDOWN>>1 + DPHS-DABPHS - Margin, DPHS-DABPHS < 0 ==> 0
//
//    EPwm4Regs.AQCTLA.bit.PRD        = AQ_SET;
////    EPwm6Regs.AQCTLA.bit.ZRO = AQ_SET;
//    EPwm4Regs.AQCTLA.bit.CAU        = AQ_CLEAR;//AQ_SET;
//
//    // Active Low PWMs - Setup Deadband
//    EPwm4Regs.DBCTL.bit.OUT_MODE    = DB_FULL_ENABLE;
//    EPwm4Regs.DBCTL.bit.POLSEL      = DB_ACTV_HI;
//    EPwm4Regs.DBCTL.bit.IN_MODE     = DBA_ALL;
//    EPwm4Regs.DBRED.bit.DBRED       = giDeadBandSrCal;   //20 : 100ns
//
//    EDIS;
}

void InitEPwm5Config()
{
    EALLOW;

    ClkCfgRegs.PERCLKDIVSEL.bit.EPWMCLKDIV  = 0x0;
    EPwm5Regs.TBCTL.bit.HSPCLKDIV           = TB_DIV1;              // Clock ratio to SYSCLKOUT
    EPwm5Regs.TBCTL.bit.CLKDIV              = TB_DIV1;

    BswPwm_ForceLowPwm(5);
    //BswPwm_SetFreqUpCnt(1, gfPwmFreqInitCal);
    BswPwm_SetFreqUpDownCnt(5, gfPwmFreqInitCal);

    EPwm5Regs.TBCTR                         = 0;                    // Clear counter
    EPwm5Regs.TBPHS.bit.TBPHS               = 0;//                    // Phase is 0
    EPwm5Regs.TBCTL.bit.PHSDIR              = TB_UP;              // Count UP on sync (=180 deg)

    // Setup TBCLK
    EPwm5Regs.TBCTL.bit.CTRMODE             = TB_COUNT_UPDOWN;      // Count up down
    EPwm5Regs.TBCTL.bit.PHSEN               = TB_DISABLE;            // Enable phase loading
    EPwm5Regs.TBCTL.bit.PRDLD               = TB_SHADOW;
    EPwm5Regs.EPWMSYNCINSEL.bit.SEL         = SYNC_IN_SRC_DISABLE_ALL;
    EPwm5Regs.EPWMSYNCOUTEN.bit.ZEROEN      = 0;      // **

    EPwm5Regs.CMPCTL.bit.SHDWAMODE          = CC_SHADOW;            // Load registers every ZERO
    EPwm5Regs.CMPCTL.bit.SHDWBMODE          = CC_SHADOW;
    EPwm5Regs.CMPCTL.bit.LOADAMODE          = CC_CTR_ZERO;
    EPwm5Regs.CMPCTL.bit.LOADBMODE          = CC_CTR_ZERO;

    // Set actions

    EPwm5Regs.CMPA.bit.CMPA                 = 0;

    //Q2 (HS LS)
    EPwm5Regs.AQCTLA.bit.ZRO                = AQ_SET;
    EPwm5Regs.AQCTLA.bit.PRD                = AQ_CLEAR;
    EPwm5Regs.AQCTLA.bit.CAU                = AQ_CLEAR;
    EPwm5Regs.AQCTLA.bit.CAD                = AQ_SET;

    //Setup DeadBand
    EPwm5Regs.DBCTL.bit.OUT_MODE            = DB_FULL_ENABLE;
    EPwm5Regs.DBCTL.bit.IN_MODE             = DBA_ALL;
    EPwm5Regs.DBCTL.bit.POLSEL              = DB_ACTV_HIC;      //ePwm1B A의 반전 동작
    EPwm5Regs.DBRED.bit.DBRED               = giDeadBandCal;    //20 : 100ns
    EPwm5Regs.DBFED.bit.DBFED               = giDeadBandCal;

    //Event Trigger
//    EPwm5Regs.ETSEL.bit.SOCAEN              = 1;
//    EPwm5Regs.ETSEL.bit.SOCASEL             = ET_CTR_ZERO;
//    EPwm5Regs.ETPS.bit.SOCAPRD              = ET_1ST;

    EDIS;
}

void BswPwm_SetPwmADuty (Uint8 ch, float Duty )
{
    Uint16 iDutyCntA = 0;
    iDutyCntA = (Uint16)((float) ePWM_Regs[ ch ]->TBPRD * Duty);
    EALLOW;
    ePWM_Regs[ ch ]->CMPA.bit.CMPA = iDutyCntA;
    EDIS;
}

void BswPwm_SetPwmBDuty (Uint8 ch, float Duty )
{
    Uint16 iDutyCntB = 0;
    iDutyCntB = (Uint16)((float) ePWM_Regs[ ch ]->TBPRD * Duty);
    EALLOW;
    ePWM_Regs[ ch ]->CMPB.bit.CMPB = iDutyCntB;
    EDIS;
}

void BswPwm_SetPwmDuty (Uint8 ch, Bool Deadband, float Duty )
{

    Uint16 iDutyCntA = 0;
    Uint16 iDutyCntB = 0;

    if(Deadband == TRUE)
    {
        iDutyCntA = (Uint16)((((float) ePWM_Regs[ ch ]->TBPRD) * Duty)+ ( ePWM_Regs[ ch ]->DBFED.bit.DBFED ));
    }
    else
    {
        iDutyCntA = (Uint16)(((float) ePWM_Regs[ ch ]->TBPRD) * Duty);
    }
    EALLOW;
    ePWM_Regs[ ch ]->CMPA.bit.CMPA = iDutyCntA;
//    iDutyCntB = ePWM_Regs[ ch ]->TBPRD - iDutyCntA;
    iDutyCntB = iDutyCntA;
    ePWM_Regs[ ch ]->CMPB.bit.CMPB = iDutyCntB;
    EDIS;


}


void BswPwm_SetDeadtime (Uint8 ch, float Deadtime_ns )
{
    Uint16 iDeadband = 0;
    iDeadband = (Uint16)(Deadtime_ns*(float)CPUCLK*1e-9);

    ePWM_Regs[ ch ]->DBFED.bit.DBFED = iDeadband;
    ePWM_Regs[ ch ]->DBRED.bit.DBRED = iDeadband;
}

void BswPwm_SetFreq (Uint8 ch, Uint8 CarrMode, float Freq )
{
    ePWM_Regs[ ch ]->TBCTL.bit.CTRMODE             = CarrMode;
    if(CarrMode == TB_COUNT_UPDOWN)
    {
        ePWM_Regs[ ch ]->TBPRD                     = ( Uint32 ) ( ( float ) CPUCLK / Freq * 0.5);
    }
    else
    {
        ePWM_Regs[ ch ]->TBPRD                     = ( Uint32 ) ( ( float ) CPUCLK / Freq );
    }
}

void BswPwm_SetFreqUpCnt (Uint8 ch, float Freq )
{
    ePWM_Regs[ ch ]->TBPRD                     = ( Uint32 ) ( ( float ) CPUCLK / Freq );
}

void BswPwm_SetFreqUpDownCnt (Uint8 ch, float Freq )
{
    EALLOW;
    ePWM_Regs[ ch ]->TBPRD                     =  (((( Uint32 )(( float ) CPUCLK / Freq))>>2)<<1);
    EDIS;
}

void BswPwm_InitFltPWM(Uint8 ch)
{
    EALLOW;
#ifndef DefDisableHWFlt
//    ePWM_Regs[ ch ]->TZSEL.bit.OSHT1               = TRUE;          //Enable TZ1 as a one-shot trip source for this ePWM module
//    ePWM_Regs[ ch ]->TZSEL.bit.OSHT2               = TRUE;          //Enable TZ2 as a one-shot trip source for this ePWM module
//    ePWM_Regs[ ch ]->TZSEL.bit.OSHT3               = TRUE;          //Enable TZ3 as a one-shot trip source for this ePWM module
    ePWM_Regs[ ch ]->TZCTL.bit.TZA                 = TZ_FORCE_LO;
    ePWM_Regs[ ch ]->TZCTL.bit.TZB                 = TZ_FORCE_LO;
    ePWM_Regs[ ch ]->TZFRC.bit.OST                 = TRUE;
#endif
    EDIS;
}

void BswPwm_ForceLowPwmA (Uint8 ch)
{
    EALLOW;
    ePWM_Regs[ ch ]->TZCTL.bit.TZA                 = TZ_FORCE_LO;
    ePWM_Regs[ ch ]->TZCTL.bit.TZB                 = TZ_NO_CHANGE;
    ePWM_Regs[ ch ]->TZFRC.bit.OST                 = TRUE;
    EDIS;
}
void BswPwm_ForceLowPwmB (Uint8 ch)
{
    EALLOW;
    ePWM_Regs[ ch ]->TZCTL.bit.TZA                 = TZ_NO_CHANGE;
    ePWM_Regs[ ch ]->TZCTL.bit.TZB                 = TZ_FORCE_LO;
    ePWM_Regs[ ch ]->TZFRC.bit.OST                 = TRUE;
    EDIS;
}

void BswPwm_ForceLowPwm (Uint8 ch)
{
    EALLOW;
    ePWM_Regs[ ch ]->TZCTL.bit.TZA                 = TZ_FORCE_LO;
    ePWM_Regs[ ch ]->TZCTL.bit.TZB                 = TZ_FORCE_LO;
    ePWM_Regs[ ch ]->TZFRC.bit.OST                 = TRUE;
    EDIS;
}

void BswPwm_DisablePfcPwm()
{
    BswPwm_ForceLowPwm(1);
    BswPwm_ForceLowPwm(2);
    GpioDataRegs.GPBCLEAR.bit.GPIO32 = 1;
}

void BswPwm_DisablePfcHSPwm()
{
    BswPwm_ForceLowPwm(1);

    EALLOW;
//    EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_IMMEDIATE;
    EPwm1Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;
//    EPwm1Regs.AQCSFRC.bit.CSFA = 1;
//    EPwm1Regs.AQCSFRC.bit.CSFB = 1;
    EDIS;

    BswPwm_SetPwmADuty(1, 0.f);
    BswPwm_SetPwmBDuty(1, 1.f);
}

void BswPwm_EnablePwm (Uint8 ch)
{
    EALLOW;
    ePWM_Regs[ ch ]->TZCLR.bit.OST                 = TRUE;
    EDIS;
}

void BswPwm_EnablePfcPwm()
{
    BswPwm_EnablePwm(1);
    BswPwm_EnablePwm(2);

    GpioDataRegs.GPBSET.bit.GPIO32 = 1;
}

void BswPwm_EnablePfcHSPwm()
{
    BswPwm_EnablePwm(1);
    GpioDataRegs.GPBSET.bit.GPIO32 = 1;
}

void BswPwm_PfcHSPwmPosDitheringMode()
{
//    EALLOW;
//    EPwm1Regs.AQCSFRC.bit.CSFA = 0;
//    EPwm1Regs.AQCSFRC.bit.CSFB = 1;
//    EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_IMMEDIATE;
//    EDIS;

    BswPwm_SetPwmADuty(1, 0.05f);
    BswPwm_SetPwmBDuty(1, 1.f);
}

void BswPwm_PfcHSPwmNegDitheringMode()
{
//    EALLOW;
//    EPwm1Regs.AQCSFRC.bit.CSFA = 1;
//    EPwm1Regs.AQCSFRC.bit.CSFB = 0;
//    EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_IMMEDIATE;
//    EDIS;

    BswPwm_SetPwmADuty(1, 0.f);
    BswPwm_SetPwmBDuty(1, 0.95f);
}

void BswPwm_PfcHSPwmNormalMode()
{
    EALLOW;
    //EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
//    EPwm1Regs.AQCSFRC.bit.CSFA = 0;
//    EPwm1Regs.AQCSFRC.bit.CSFB = 0;
    EPwm1Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;

    EDIS;
}


Uint8 BswPwm_GetPwmEvtNum (Uint8 ch)
{
    return ePWM_Regs[ ch ]->ETPS.bit.SOCAPRD;
}

Uint8 BswPwm_GetPwmTzFlgState(Uint8 ch)
{
    return ePWM_Regs[ ch ]->TZFRC.bit.OST;
}
