/*
 * BswIsr.c
 *
 *  Created on: 2021. 12. 22.
 *      Author: IPCL
 */
/*============================================================================
    Includes
============================================================================*/
#include "F28x_Project.h"
#include "BswIsr.h"
#include "BswTask.h"
#include "BswAdc.h"
#include "BswSpi.h"
#include "../RTE/ItrComAswtoBsw.h"


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
Uint16 BswTask1msCnt    = 0;
Uint16 BswTask10msCnt   = 0;
Uint16 BswTask100msCnt  = 0;
Uint32 CntCtrISR        = 0;
Uint32 CntAdca          = 0;

/*============================================================================
    Private Variables/Constants
============================================================================*/

/*============================================================================
    Function Prototypes
============================================================================*/
void BswAdcIsrOffsetCalc();

/*============================================================================
    Function Implementations
============================================================================*/
__interrupt void adcb1_isr()
{
    CntCtrISR++;

        BswApi_Gpio43En();

//    DELAY_US(15);
    BswAdcIsrOffsetCalc();

    if(giAdcoffsetCplFlag == TRUE)
    {
        BswAdcIsrCalc();
        ItrCom_AswIsrCtr();

        BswSpi_DACISR();
    }

    BswApi_Gpio43Dis();

    AdcbRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //clear INT1 flag
    //
    // Check if overflow has occurred
    //
    if(AdcbRegs.ADCINTOVF.bit.ADCINT1 == 1)
    {
        AdcbRegs.ADCINTOVFCLR.bit.ADCINT1 = 1; //clear INT1 overflow flag
        AdcbRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //clear INT1 flag
    }
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

__interrupt void Timer1_Task_100us_isr(void)
{
    EINT;
    BswTask100us();

    BswTask1msCnt++;
    if(BswTask1msCnt >= 10 )
    {
        BswTask1msCnt = 0;
        BswTask1ms();
    }

    BswTask10msCnt++;
    if(BswTask10msCnt >= 100)
    {
        BswTask10msCnt = 0;
        BswTask10ms();
    }

    BswTask100msCnt++;
    if(BswTask100msCnt >= 1000)
    {
        BswTask100msCnt = 0;
        BswTask100ms();
    }
//
//    if(giAdcoffsetCplFlag == TRUE)
//    {
//        BswTask100us();
//
//        BswTask1msCnt++;
//        if(BswTask1msCnt >= 10 )
//        {
//            BswTask1msCnt = 0;
//            BswTask1ms();
//        }
//
//        BswTask10msCnt++;
//        if(BswTask10msCnt >= 100)
//        {
//            BswTask10msCnt = 0;
//            BswTask10ms();
//        }
//
//        BswTask100msCnt++;
//        if(BswTask100msCnt >= 1000)
//        {
//            BswTask100msCnt = 0;
//            BswTask100ms();
//        }
//    }

}

#if 0

__interrupt void Xint1_isr()
{
//    GpioDataRegs.GPCSET.bit.GPIO72  = 1;   // SET

    ItrCom_AswVoltOvHwFltIsr(INVOLTHWFLT);
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

//    GpioDataRegs.GPCCLEAR.bit.GPIO72  = 1;   // CLEAR
}
__interrupt void Xint2_isr()
{
//    GpioDataRegs.GPCSET.bit.GPIO72  = 1;   // SET

    ItrCom_AswVoltOvHwFltIsr(OUTVOLTHWFLT);
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

 //   GpioDataRegs.GPCCLEAR.bit.GPIO72  = 1;   // CLEAR

}
__interrupt void Xint3_isr()
{
//    GpioDataRegs.GPCSET.bit.GPIO72  = 1;   // SET

    ItrCom_AswCurrOcHwFltIsr(CURRHWFLT1);
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;

//    GpioDataRegs.GPCCLEAR.bit.GPIO72  = 1;   // CLEAR

}
__interrupt void Xint4_isr()
{
//    GpioDataRegs.GPCSET.bit.GPIO72  = 1;   // SET

    ItrCom_AswCurrOcHwFltIsr(CURRHWFLT2);
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;

//    GpioDataRegs.GPCCLEAR.bit.GPIO72  = 1;   // CLEAR

}
__interrupt void Xint5_isr()
{
//    GpioDataRegs.GPCSET.bit.GPIO72  = 1;   // SET

    ItrCom_AswGateHwFltIsr(GATEHWFLT);
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;

//    GpioDataRegs.GPCCLEAR.bit.GPIO72  = 1;   // CLEAR

}

#endif


