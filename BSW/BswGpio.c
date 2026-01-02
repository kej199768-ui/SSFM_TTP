/*
 * BswGpio.c
 *
 *  Created on: 2022. 11. 29.
 *      Author: poweryhs
 */


/*============================================================================
    Includes
============================================================================*/
#include "F28x_Project.h"
#include "BswCommon.h"
#include "BswGpio.h"

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

/*============================================================================
    GPIO all port initialization
============================================================================*/
void InitGpioConfig()
{
    EALLOW;
    GpioCtrlRegs.GPACTRL.all = 0x00000000;
    GpioCtrlRegs.GPBCTRL.all = 0x00000000;
    GpioCtrlRegs.GPCCTRL.all = 0x00000000;
    GpioCtrlRegs.GPDCTRL.all = 0x00000000;
    EDIS;
}

/*******************************************************************************************************
 * 기능 : PWM Enable 및 FLT GPIO 설정
 *******************************************************************************************************/
void InitPWMEnaFltGpioConfig()
{
    EALLOW;

    /***************************************************************************
    ** EPwm Output Enable
    ***************************************************************************/
    //===========================================================================
    //PWM 1A ~ 4B   (EPwm1~4_config)
    //===========================================================================
    GpioCtrlRegs.GPBPUD.bit.GPIO32  = 0;    // Enable pullup
    GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 0;    // GPIO
    GpioCtrlRegs.GPBDIR.bit.GPIO32  = 1;    // Output
    GpioDataRegs.GPBSET.bit.GPIO32  = 1;    // PWM1~4 Output Enable
    //===========================================================================
    //PWM 5A ~ 8B   (EPwm5~8_config)
    //===========================================================================
    GpioCtrlRegs.GPBPUD.bit.GPIO33  = 0;    // Enable pullup
    GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 0;    // GPIO
    GpioCtrlRegs.GPBDIR.bit.GPIO33  = 1;    // Output
    GpioDataRegs.GPBSET.bit.GPIO33  = 1;    // PWM5~8 Output Enable
    //===========================================================================
    //PWM 9A ~ 12B  (EPwm9~12_config)
    //===========================================================================
    GpioCtrlRegs.GPBPUD.bit.GPIO34  = 0;    // Enable pullup
    GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0;    // GPIO
    GpioCtrlRegs.GPBDIR.bit.GPIO34  = 1;    // Output
    GpioDataRegs.GPBSET.bit.GPIO34  = 1;    // PWM9~12 Output Enable
    //===========================================================================
    //PWM 13A ~ 16B (EPwm13~16_config)
    //===========================================================================
    GpioCtrlRegs.GPBPUD.bit.GPIO35  = 0;    // Enable pullup
    GpioCtrlRegs.GPBMUX1.bit.GPIO35 = 0;    // GPIO
    GpioCtrlRegs.GPBDIR.bit.GPIO35  = 1;    // Output
    GpioDataRegs.GPBSET.bit.GPIO35  = 1;    // PWM13~16 Output Enable


    /***************************************************************************
    ** Trip-Zone Input
    ***************************************************************************/
    //===========================================================================
    // TZ1
    //===========================================================================
    GpioCtrlRegs.GPEPUD.bit.GPIO143  = 0;   // Enable pullup
    GpioCtrlRegs.GPEMUX1.bit.GPIO143 = 0;   // GPIO
    GpioCtrlRegs.GPEDIR.bit.GPIO143  = 0;   // Input
    //===========================================================================
    // TZ2
    //===========================================================================
    GpioCtrlRegs.GPEPUD.bit.GPIO144  = 0;   // Enable pullup
    GpioCtrlRegs.GPEMUX2.bit.GPIO144 = 0;   // GPIO
    GpioCtrlRegs.GPEDIR.bit.GPIO144  = 0;   // Input
    //===========================================================================
    // TZ3
    //===========================================================================
    GpioCtrlRegs.GPEPUD.bit.GPIO145  = 0;   // Enable pullup
    GpioCtrlRegs.GPEMUX2.bit.GPIO145 = 0;   // GPIO
    GpioCtrlRegs.GPEDIR.bit.GPIO145  = 0;   // Input
    //===========================================================================
    // TZ4
    //===========================================================================
    GpioCtrlRegs.GPEPUD.bit.GPIO146  = 0;   // Enable pullup
    GpioCtrlRegs.GPEMUX2.bit.GPIO146 = 0;   // GPIO
    GpioCtrlRegs.GPEDIR.bit.GPIO146  = 0;   // Input
    //===========================================================================
    // TZ5
    //===========================================================================
    GpioCtrlRegs.GPEPUD.bit.GPIO147  = 0;   // Enable pullup
    GpioCtrlRegs.GPEMUX2.bit.GPIO147 = 0;   // GPIO
    GpioCtrlRegs.GPEDIR.bit.GPIO147  = 0;   // Input

    EDIS;

}
/*******************************************************************************************************
 * 기능 : GPIO 입출력 설정
 *******************************************************************************************************/
void InitGpioInOutConfig()
{
    EALLOW;

    //GPIO OUTPUT CONTROL ENABLE
    //===========================================================================
    //GPIO53, ENABLE GPIO 37 ~ 44
    //===========================================================================
    GpioCtrlRegs.GPBPUD.bit.GPIO53  = 0;    // Enable pullup
    GpioCtrlRegs.GPBMUX2.bit.GPIO53 = 0;    // GPIO
    GpioCtrlRegs.GPBDIR.bit.GPIO53 = 1;    // Output
    GpioDataRegs.GPBSET.bit.GPIO53  = 1;    // GPIO37 ~ 44 ENABLE

    //===========================================================================
    //GPIO37, Relay signal
    //===========================================================================
    GpioCtrlRegs.GPBPUD.bit.GPIO37  = 0;    // Enable pullup
    GpioCtrlRegs.GPBMUX1.bit.GPIO37 = 0;    // GPIO
    GpioCtrlRegs.GPBDIR.bit.GPIO37  = 1;    // Output
    GpioDataRegs.GPBCLEAR.bit.GPIO37  = 1;    // GPIO37 clear

    //===========================================================================
    //GPIO38, Relay signal
    //===========================================================================
    GpioCtrlRegs.GPBPUD.bit.GPIO38  = 0;    // Enable pullup
    GpioCtrlRegs.GPBMUX1.bit.GPIO38 = 0;    // GPIO
    GpioCtrlRegs.GPBDIR.bit.GPIO38  = 1;    // Output
    GpioDataRegs.GPBCLEAR.bit.GPIO38  = 1;    // GPIO38 clear

    //===========================================================================
    //GPIO39, Relay signal
    //===========================================================================
    GpioCtrlRegs.GPBPUD.bit.GPIO39  = 0;    // Enable pullup
    GpioCtrlRegs.GPBMUX1.bit.GPIO39 = 0;    // GPIO
    GpioCtrlRegs.GPBDIR.bit.GPIO39  = 1;    // Output
    GpioDataRegs.GPBCLEAR.bit.GPIO39  = 1;    // GPIO39 clear

    //===========================================================================
    
    EDIS;
}

void BswGpio_EnableRly()
{
    GpioDataRegs.GPBSET.bit.GPIO37 = 1;    // RLY GPIO Set
}
void BswGpio_DisableRly()
{
    GpioDataRegs.GPBCLEAR.bit.GPIO37 = 1;   //RLY GPIO Clear
}

void BswGpio_PfcLSSw_PosEn()
{
    GpioDataRegs.GPBCLEAR.bit.GPIO38 = 1;
    GpioDataRegs.GPBSET.bit.GPIO39 = 1;
}
void BswGpio_PfcLSSw_NegEn()
{
    GpioDataRegs.GPBSET.bit.GPIO38 = 1;
    GpioDataRegs.GPBCLEAR.bit.GPIO39 = 1;
}
void BswGpio_PfcLSSw_DeadBand()
{
    GpioDataRegs.GPBCLEAR.bit.GPIO38 = 1;
    GpioDataRegs.GPBCLEAR.bit.GPIO39 = 1;
}



#if 0
/*******************************************************************************************************
 * 기능 : HW FLT GPIO 설정
 *******************************************************************************************************/
void InitHWFltGpioConfig()
{
    EALLOW;
    //===========================================================================
    //Input Voltage High Flt : GPIO32
    //===========================================================================
    GpioCtrlRegs.GPBPUD.bit.GPIO32  = 0;   // 0: Enables the Pull-Up.   1: Disables the Pull-Up.
    GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 0;   // GPIO output
    GpioCtrlRegs.GPBDIR.bit.GPIO32  = 0;   // 0: Configures pin as input.   1: Configures pin as output.

    //===========================================================================
    //Output Voltage High Flt : GPIO33
    //===========================================================================
    GpioCtrlRegs.GPBPUD.bit.GPIO33  = 0;   // 0: Enables the Pull-Up.   1: Disables the Pull-Up.
    GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 0;   // GPIO output
    GpioCtrlRegs.GPBDIR.bit.GPIO33  = 0;   // 0: Configures pin as input.   1: Configures pin as output.

    //===========================================================================
    //Current1 High Flt : GPIO34
    //===========================================================================
    GpioCtrlRegs.GPBPUD.bit.GPIO34  = 0;   // 0: Enables the Pull-Up.   1: Disables the Pull-Up.
    GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0;   // GPIO output
    GpioCtrlRegs.GPBDIR.bit.GPIO34  = 0;   // 0: Configures pin as input.   1: Configures pin as output.

    //===========================================================================
    //Current2 High Flt : GPIO35
    //===========================================================================
    GpioCtrlRegs.GPBPUD.bit.GPIO35  = 0;   // 0: Enables the Pull-Up.   1: Disables the Pull-Up.
    GpioCtrlRegs.GPBMUX1.bit.GPIO35 = 0;   // GPIO output
    GpioCtrlRegs.GPBDIR.bit.GPIO35  = 0;   // 0: Configures pin as input.   1: Configures pin as output.

    //===========================================================================
    //Gate Flt : GPIO69
    //===========================================================================
    GpioCtrlRegs.GPCPUD.bit.GPIO69  = 0;   // 0: Enables the Pull-Up.   1: Disables the Pull-Up.
    GpioCtrlRegs.GPCMUX1.bit.GPIO69 = 0;   // GPIO output
    GpioCtrlRegs.GPCDIR.bit.GPIO69  = 0;   // 0: Configures pin as input.   1: Configures pin as output.
    EDIS;
}


void InitComGpioConfig()
{
    EALLOW;

#if 0
    //===========================================================================
    //MCBSP
    //===========================================================================
    GpioCtrlRegs.GPAPUD.bit.GPIO20  = 0;   // Enable pullup
    GpioCtrlRegs.GPAMUX2.bit.GPIO20 = 2;   // MDXA

    GpioCtrlRegs.GPAPUD.bit.GPIO22  = 0;   // Enable pullup
    GpioCtrlRegs.GPAMUX2.bit.GPIO22 = 2;   // MCLKXA
    GpioCtrlRegs.GPAQSEL2.bit.GPIO22 = 3;


    GpioCtrlRegs.GPAPUD.bit.GPIO23  = 0;   // Enable pullup
    GpioCtrlRegs.GPAMUX2.bit.GPIO23 = 2;   // MFSXA
    GpioCtrlRegs.GPAQSEL2.bit.GPIO22 = 3;
#endif

    //===========================================================================
    //SPI
    //===========================================================================
    GpioCtrlRegs.GPBPUD.bit.GPIO54  = 0;   // Enable pullup
    GpioCtrlRegs.GPBMUX2.bit.GPIO54 = 1;   // SPIA_SIMO

    GpioCtrlRegs.GPBPUD.bit.GPIO56  = 0;   // Enable pullup
    GpioCtrlRegs.GPBMUX2.bit.GPIO56 = 1;   // SPIA_CLK
    GpioCtrlRegs.GPBQSEL2.bit.GPIO56 = 3;

    GpioCtrlRegs.GPBPUD.bit.GPIO57  = 0;   // Enable pullup
    GpioCtrlRegs.GPBMUX2.bit.GPIO57 = 0;   // SPIA_STEn인데 GPIO mode로 signal 한다.
    GpioCtrlRegs.GPBDIR.bit.GPIO57  = 1;   // output
    GpioDataRegs.GPBDAT.bit.GPIO57  = 1;   // initial disable to transmit data. (active low)
    GpioCtrlRegs.GPBQSEL2.bit.GPIO57 = 3;
    EDIS;
}

Uint8 BswGpioGetVoltOvDIState(Uint8 DiNum)
{
    Uint8 iVoltHwFltGpio = 0;
    if(DiNum == 0)
    {
        iVoltHwFltGpio = GpioDataRegs.GPBDAT.bit.GPIO32;
    }
    else if(DiNum == 1)
    {
        iVoltHwFltGpio = GpioDataRegs.GPBDAT.bit.GPIO33;
    }
    return iVoltHwFltGpio;
}

Uint8 BswGpioGetCurrOcDIState(Uint8 DiNum)
{
    Uint8 iCurrHwFltGpio = 0;
    if(DiNum == 0)
    {
        iCurrHwFltGpio = GpioDataRegs.GPBDAT.bit.GPIO34;
    }
    else if(DiNum == 1)
    {
        iCurrHwFltGpio = GpioDataRegs.GPBDAT.bit.GPIO35;
    }
    return iCurrHwFltGpio;
}

Uint8 BswGpioGetGateHwFltDIState()
{
    Uint8 iGateFltGpio = 0;
    iGateFltGpio = GpioDataRegs.GPCDAT.bit.GPIO69;
    return iGateFltGpio;
}


Uint8 BswGpioGetGateFltDIState(Uint8 DiNum)
{
    Uint8 iGateFltGpio = 0;
    if(DiNum == 0)
    {
        iGateFltGpio = GpioDataRegs.GPBDAT.bit.GPIO56;
    }
    else if(DiNum == 1)
    {
        iGateFltGpio = GpioDataRegs.GPBDAT.bit.GPIO57;
    }
    else if(DiNum == 2)
    {
        iGateFltGpio = GpioDataRegs.GPBDAT.bit.GPIO58;
    }
    else if(DiNum == 3)
    {
        iGateFltGpio = GpioDataRegs.GPBDAT.bit.GPIO59;
    }
    return iGateFltGpio;
}


Uint8 BswGpioGetGateRdyDIState(Uint8 DiNum)
{
    Uint8 iGateRdyGpio = 0;
    if(DiNum == 0)
    {
        iGateRdyGpio = GpioDataRegs.GPBDAT.bit.GPIO50;
    }
    else if(DiNum == 1)
    {
        iGateRdyGpio = GpioDataRegs.GPBDAT.bit.GPIO51;
    }
    else if(DiNum == 2)
    {
        iGateRdyGpio = GpioDataRegs.GPBDAT.bit.GPIO52;
    }
    else if(DiNum == 3)
    {
        iGateRdyGpio = GpioDataRegs.GPBDAT.bit.GPIO53;
    }
    return iGateRdyGpio;
}


void BswGpioSetGateResetState()
{
    GpioDataRegs.GPBSET.bit.GPIO41  = 1;
}

void BswGpioClearGateResetState()
{
    GpioDataRegs.GPBCLEAR.bit.GPIO41  = 1;
}

Uint8 BswGpioGetGateResetState()
{
    return GpioDataRegs.GPBDAT.bit.GPIO41;
}

#endif

