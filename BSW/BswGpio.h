/*
 * BswGpio.h
 *
 *  Created on: 2022. 11. 29.
 *      Author: poweryhs
 */

#ifndef BSW_BSWGPIO_H_
#define BSW_BSWGPIO_H_

/*============================================================================
    Includes
============================================================================*/
#include "BswCommon.h"

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
void InitGpioConfig(void);
void InitPWMEnaFltGpioConfig(void);
void InitGpioInOutConfig(void);

void BswGpio_EnableRly(void);
void BswGpio_DisableRly(void);

void BswGpio_PfcLSSw_PosEn(void);
void BswGpio_PfcLSSw_NegEn(void);
void BswGpio_PfcLSSw_DeadBand(void);

#if 0
void InitHWFltGpioConfig(void);
void InitComGpioConfig(void);

Uint8 BswGpioGetCurrOcDIState(Uint8 DiNum);
Uint8 BswGpioGetVoltOvDIState(Uint8 DiNum);
Uint8 BswGpioGetGateFltDIState(Uint8 DiNum);
Uint8 BswGpioGetGateHwFltDIState();
Uint8 BswGpioGetGateRdyDIState(Uint8 DiNum);
void BswGpioSetGateResetState();
void BswGpioClearGateResetState();
Uint8 BswGpioGetGateResetState();
#endif

#endif /* BSW_BSWGPIO_H__ */
