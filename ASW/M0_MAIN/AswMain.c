/*
 * AswMain.c
 *
 *  Created on: 2023. 1. 4.
 *      Author: poweryhs
 */


/*============================================================================
    Includes
============================================================================*/
#include <ASW/M0_MAIN/AswMain.h>
#include <ASW/M1_SEQ/SeqApi.h>
#include <ASW/M2_MON/MonApi.h>
#include <ASW/M3_CTR/CtrApi.h>
#include <ASW/M4_FDIAG/FdiagApi.h>
#include <ASW/M6_COM/ComApi.h>
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
//Uint8 Test_Rly;
//Uint8 Test_PWM_EN;
//float Test_HSDuty;
//Uint8 Test_Emios;
//Uint8 Test_Pow_En;
//Uint8 Test_Aux_En;
//Uint8 Test_LSLS;
//Uint8 Test_LSHS;
//Uint8 TEST_PFC_XLT;
//Uint8 TEST_TRIP_RESET;
//Uint8 TEST_IPH_SCP;
//Uint8 TEST_IDC_SCP;
//Uint8 TEST_LV_OVP;
//Uint8 TEST_LV_SCP;

/*============================================================================
    Private Variables/Constants
============================================================================*/

/*============================================================================
    Function Prototypes
============================================================================*/

/*============================================================================
    Function Implementations
============================================================================*/
void AswIsrCtr(void)
{
	MonApi_AdcIsrCtr();             //ADC sensing
    CtrApi_CtrMIsrCtr();
    FdiagApi_ChkMIsrCtr();
}
void AswTask100us(void)
{
    MonApi_AdcTask100us();
    CtrApi_CtrMTask100us();
}
void AswTask1ms(void)
{
    MonApi_AdcTask1ms();
    CtrApi_CtrMTask1ms();
    FdiagApi_ChkMTask1ms();
    SeqApi_RunSeqMainTask1ms();
}
void AswTask10ms(void)
{
////  MonAdcTask10ms();
//    FdiagApi_ChkMTask10ms();
}
void AswTask100ms(void)
{
////  MonAdcTask100ms();
    FdiagApi_ChkMTask100ms();
}




