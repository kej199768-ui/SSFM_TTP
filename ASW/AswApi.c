/*
 * AswApi.c
 *
 *  Created on: 2023. 1. 4.
 *      Author: poweryhs
 */


/*============================================================================
    Includes
============================================================================*/


#include "AswApi.h"
#include "AswCommon.h"
#include "M0_MAIN/AswMainApi.h"


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
void AswApi_AswIsrCtr(void)        {MainApi_AswIsrCtr();}
void AswApi_AswTask100us(void)     {MainApi_AswTask100us();}
void AswApi_AswTask1ms(void)       {MainApi_AswTask1ms();}
void AswApi_AswTask10ms(void)      {MainApi_AswTask10ms();}
void AswApi_AswTask100ms(void)     {MainApi_AswTask100ms();}

void AswApi_AswCurrOcHwFltIsr(void)
{
    Uint8 i = 0;
    for(i = 0; i < CurrSnsrNum ; i++)
    {
        AswApi_ChkCurrHwOcFlt(i);
    }
}
void AswApi_AswVoltOvHwFltIsr(void)
{
    Uint8 i = 0;
    for(i = 0; i < VoltSnsrNum ; i++)
    {
        AswApi_ChkVoltHwOvFlt(i);
    }
}
void AswApi_AswGateHwFltIsr(void)
{
    Uint8 i = 0;
    for(i = 0; i < GateSnsrNum ; i++)
    {
        AswApi_ChkGateHwFlt(i);
    }
}


