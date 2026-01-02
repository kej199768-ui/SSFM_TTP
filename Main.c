/*============================================================================
     Includes
 ============================================================================*/
#include <Common.h>
#include "f28x_project.h"
//#include "driverlib.h"
#include "BSW/BswPwm.h"
#include "BSW/BswGPIO.h"
#include "BSW/BswAdc.h"
#include "BSW/BswIsr.h"
#include "BSW/BswTask.h"

/*============================================================================
     FLASH
 ============================================================================*/
#ifdef _FLASH
#pragma CODE_SECTION(adcb1_isr, ".TI.ramfunc");
#pragma CODE_SECTION(Timer1_Task_100us_isr, ".TI.ramfunc");
extern Uint16 RamfuncsLoadStart;
extern Uint16 RamfuncsLoadSize;
extern Uint16 RamfuncsLoadEnd;
extern Uint16 RamfuncsRunStart;
#endif


/*============================================================================
     Define function
 ============================================================================*/

/*============================================================================
     Define Global Variables
 ============================================================================*/

/*============================================================================
     Main Function
 ============================================================================*/
void main(void)
{
/*============================================================================
     Step1. Initialize System Control
     (PLL, WatchDog, Enable Clock)
 ============================================================================*/
    InitSysCtrl();

/*============================================================================
         Step2. Initialize GPIO (ePWMx)
 ============================================================================*/
    InitGpioConfig();

    InitEPwm1Gpio();
    InitEPwm2Gpio();
    InitEPwm3Gpio();
    InitEPwm4Gpio();
    InitEPwm5Gpio();

/*============================================================================
         Step3. Initialize interrupts
         (Disable CPU interrupts)
 ============================================================================*/
    DINT;                                                   //Disable Global Interrupt
    InitPieCtrl();                                          //Initialize PIE control registers

    //Disable CPU interrupts and clear all CPU interrupt flags
    IER = 0x0000;
    IFR = 0x0000;

    InitPieVectTable();                                     //Initializing PIE interrupts vector table

    //Interrupt Vector Remapping
    EALLOW;
    PieVectTable.ADCB1_INT = &adcb1_isr;                    //Function for ADCA interrupt 1
    PieVectTable.TIMER1_INT = &Timer1_Task_100us_isr;
    EDIS;

/*============================================================================
         Step4. Initialize Device Peripherals (configuration)
 ============================================================================*/
    InitAdcConfig();                                        //Initializing ADC config.

    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;                   //Reset
    EDIS;

    //Initializing Function
    InitPWMEnaFltGpioConfig();
    InitGpioInOutConfig();
    InitEPwm1Config();
    InitEPwm2Config();
    InitEPwm3Config();
    InitEPwm4Config();
    //InitEPwm5Config();

    //GPIO setting
    EALLOW;
    GpioDataRegs.GPBSET.bit.GPIO32 = 1;                     //PWM IC enable
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;                   //enable
    EDIS;

/*============================================================================
         Step5. Enable interrupts
 ============================================================================*/
    //Enable Cpu Interrupt
    IER |= M_INT1;                                          //INT1 (for ADCA1)
    IER |= M_INT13;                                         //INT13 (for Timer1)

    //Enable ePWM INTn
    EALLOW;
    PieCtrlRegs.PIEIER1.bit.INTx2 = 1;                      //ADCA1 INT
    EDIS;

    //Initialize CPU Timer
    EALLOW;
    InitCpuTimers();
    ConfigCpuTimer(&CpuTimer1, 200, 100);                   //(Timer, fc(MHz), Period(us))
    CpuTimer1Regs.TCR.all = 0x4000;
    EDIS;

    //Enable global Interrupts
    EINT;
    ERTM;

/*============================================================================
         Step6. IDLE loop
 ============================================================================*/
    for(;;)
    {
        asm ("NOP");
    }

}

//END OF FILE


