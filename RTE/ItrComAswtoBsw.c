/*
 * ItrCom.c
 *
 *  Created on: 2023. 1. 4.
 *      Author: poweryhs
 */


/*============================================================================
    Includes
============================================================================*/
#include <ASW_backup/AswMainApi.h>
#include "ItrComAswtoBsw.h"
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

void ItrCom_AswIsrCtr()         	{AswApi_AswIsrCtr();}       //{AswMainApi_IsrCtr();}
void ItrCom_AswTask100us()          {AswApi_AswTask100us();}    //{AswMainApi_Task100us();}
void ItrCom_AswTask1ms()        	{AswApi_AswTask1ms();}      //{AswMainApi_Task1ms();}
void ItrCom_AswTask10ms()       	{AswApi_AswTask10ms();}     //{AswMainApi_Task10ms();}
void ItrCom_AswTask100ms()      	{AswApi_AswTask100ms();}    //{AswMainApi_Task10ms();}



//void ItrCom_AswCurrOcHwFltIsr(Uint8 HwFltNum)     {AswApi_ChkCurrHwOcFlt(HwFltNum);}
//void ItrCom_AswVoltOvHwFltIsr(Uint8 HwFltNum)     {AswApi_ChkVoltHwOvFlt(HwFltNum);}
//void ItrCom_AswGateHwFltIsr(Uint8 HwFltNum)       {AswApi_ChkGateHwFlt(HwFltNum);}



