/*
 * BswSpi.c
 *
 *  Created on: 2022. 11. 29.
 *      Author: poweryhs
 */

/*============================================================================
    Includes
============================================================================*/
#include "F28x_Project.h"
#include "Bswspi.h"
#include "BswApi.h"
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
int giSPIAdata[DACCHANNELNUM] = {0U, };
int giSPIBdata[DACCHANNELNUM] = {0U, };
Uint16 giDACA[DACCHANNELNUM] = {0U, };
Uint16 giDACB[DACCHANNELNUM] = {0U, };
Uint16 giSPIdataindex = 0U;
/*============================================================================
    Private Variables/Constants
============================================================================*/

/*============================================================================
    Function Prototypes
============================================================================*/

/*============================================================================
    Function Implementations
============================================================================*/
void InitSpiDACConfig(void)
{
    //===========================================================================
    //SPI A Initial Configuration
    //===========================================================================
    //Initial flags clear
    SpiaRegs.SPICCR.bit.SPISWRESET = 0;     //Initialization. all flag clear. (like EALLOW)

    //Mode & function setting
    SpiaRegs.SPICTL.bit.MASTER_SLAVE = 1;
    SpiaRegs.SPICCR.bit.HS_MODE = 0;
    SpiaRegs.SPICCR.bit.SPILBK = 0;

    //3-wire
    SpiaRegs.SPIPRI.bit.TRIWIRE = 1;

    //CLK
    SpiaRegs.SPICTL.bit.CLK_PHASE = 0;
    SpiaRegs.SPICCR.bit.CLKPOLARITY = 0;
    SpiaRegs.SPIBRR.bit.SPI_BIT_RATE = 3;   //SPICLK = LSPCLK/(x) = 50MHz / 4 = 12.5MHz. Register value 0~3 means"x=4"

    //ETC
    SpiaRegs.SPICCR.bit.SPICHAR = 15;       //16bit
    SpiaRegs.SPICTL.bit.SPIINTENA = 0;
    SpiaRegs.SPICTL.bit.TALK = 1;

    //Ready
    SpiaRegs.SPICCR.bit.SPISWRESET = 1;     //ready to use SPI
}

void BswSpi_DACISR(void)
{
    //SPI DAC A
    giSPIAdata[0] = 0x8000 + ((int)(giDACA[0]));
    giSPIAdata[1] = 0x9000 + ((int)(giDACA[1]));
    giSPIAdata[2] = 0xA000 + ((int)(giDACA[2]));
    giSPIAdata[3] = 0xB000 + ((int)(giDACA[3]));

//    //SPI DAC B
//    giSPIBdata[0] = 0x8000 + ((Uint16)(0.2f * giDACB[0]));
//    giSPIBdata[1] = 0x9000 + ((Uint16)(0.4f * giDACB[1]));
//    giSPIBdata[2] = 0xA000 + ((Uint16)(0.6f * giDACB[2]));
//    giSPIBdata[3] = 0xB000 + ((Uint16)(0.8f * giDACB[3]));

    for (giSPIdataindex=0; giSPIdataindex<DACCHANNELNUM; giSPIdataindex++)
    {
        SpiaRegs.SPITXBUF = giSPIAdata[giSPIdataindex];

        GpioDataRegs.GPBCLEAR.bit.GPIO57 = 1;
        DELAY_US(1.3);
        GpioDataRegs.GPBSET.bit.GPIO57 = 1;
    }
}

void BswSpi_DAC100us(void)
{
    //SPI DAC A
    giSPIAdata[0] = 0x8000 + ((int)(0.2f * giDACA[0]));
    giSPIAdata[1] = 0x9000 + ((int)(0.4f * giDACA[1]));
    giSPIAdata[2] = 0xA000 + ((int)(0.6f * giDACA[2]));
    giSPIAdata[3] = 0xB000 + ((int)(0.8f * giDACA[3]));

//    //SPI DAC B
//    giSPIBdata[0] = 0x8000 + ((Uint16)(0.2f * giDACB[0]));
//    giSPIBdata[1] = 0x9000 + ((Uint16)(0.4f * giDACB[1]));
//    giSPIBdata[2] = 0xA000 + ((Uint16)(0.6f * giDACB[2]));
//    giSPIBdata[3] = 0xB000 + ((Uint16)(0.8f * giDACB[3]));

    for (giSPIdataindex = 0; giSPIdataindex<DACCHANNELNUM; giSPIdataindex++)
    {
        SpiaRegs.SPITXBUF = giSPIAdata[giSPIdataindex];

        GpioDataRegs.GPBCLEAR.bit.GPIO57 = 1;
        DELAY_US(1.3);
        GpioDataRegs.GPBSET.bit.GPIO57 = 1;
    }
}

void BswSpi_SetDACA(Uint8 ch, Uint16 data)
{
    giDACA[ch] = data;
}
