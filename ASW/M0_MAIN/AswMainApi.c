/*
 * AswMainApi.c
 *
 *  Created on: 2023. 1. 4.
 *      Author: poweryhs
 */


/*============================================================================
    Includes
============================================================================*/
#include <ASW/M0_MAIN/AswMain.h>
#include <ASW/M0_MAIN/AswMainApi.h>
#include <ASW/M4_FDIAG/FdiagApi.h>
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
void MainApi_AswIsrCtr(void)        {AswIsrCtr();}
void MainApi_AswTask100us(void)     {AswTask100us();}
void MainApi_AswTask1ms(void)       {AswTask1ms();}
void MainApi_AswTask10ms(void)      {AswTask10ms();}
void MainApi_AswTask100ms(void)     {AswTask100ms();}

//void AswApi_ChkCurrHwOcFlt(Uint16 SnsrNum)      {FdiagApi_ChkCurrHwOcFlt(SnsrNum);}
//void AswApi_ChkVoltHwOvFlt(Uint16 SnsrNum)      {FdiagApi_ChkVoltHwOvFlt(SnsrNum);}
//void AswApi_ChkGateHwFlt(Uint16 SnsrNum)        {FdiagApi_ChkGateHwFlt(SnsrNum);}
void AswApi_ChkCurrHwOcFlt(Uint16 SnsrNum){}
void AswApi_ChkVoltHwOvFlt(Uint16 SnsrNum){}
void AswApi_ChkGateHwFlt(Uint16 SnsrNum){}
