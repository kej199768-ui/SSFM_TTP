#ifndef _COMCAN_H
#define _COMCAN_H

/*============================================================================
   Includes
============================================================================*/
#include "../AswCommon.h"
/*============================================================================
   Macros
============================================================================*/

/*============================================================================
   Enumerations
============================================================================*/

/*============================================================================
   Data Structures
============================================================================*/
//High Speed Can data structures
typedef union Can_Rx_Data_FCU1
{
    Uint8 data[8];
    struct 
    {
        Uint8 Fcu1_Fdc1RunCmd_HS : 8;
        Uint8 Fcu1_StckHvPRlyClzSts_HS : 8;
        Uint8 Fcu1_Fdc1LsTrgtVlt_HS : 8;
        Uint8 Fcu1_Fdc1LsCurBstUpLim_HS : 8;
        Uint8 e : 8;
        Uint8 f : 8;
        Uint8 g : 8;
        Uint8 h : 8;
    }Sig;
}CanRxDataFCU1;

typedef union Can_Rx_Data_FCU2
{
    Uint8 data[8];
    struct 
    {
        Uint8 Fcu1_DrvCycSet_HS : 8;
        Uint8 Fcu1_WuCycSet_HS : 8;
        Uint8 Fcu1_FcVltSum_HS : 8;
        Uint8 Fcu1_Fdc1HsVltUpLim_HS : 8;
        Uint8 e : 8;
        Uint8 f : 8;
        Uint8 g : 8;
        Uint8 h : 8;
    } Sig;
}CanRxDataFCU2;

typedef union Can_Rx_Data_BMS
{
    Uint8 data[8];
    struct 
    {
        Uint8 a : 8;
        Uint8 b : 8;
        Uint8 c : 8;
        Uint8 d : 8;
        Uint8 e : 8;
        Uint8 f : 8;
        Uint8 g : 8;
        Uint8 h : 8;
    }Sig;
}CanRxDataBMS;

typedef union Can_Rx_Data_VCU
{
    Uint8 data[8];
    struct 
    {
        Uint8 a : 8;
        Uint8 b : 8;
        Uint8 c : 8;
        Uint8 d : 8;
        Uint8 e : 8;
        Uint8 f : 8;
        Uint8 g : 8;
        Uint8 h : 8;
    }Sig;
}CanRxDataVCU;

typedef union Can_Rx_Data_LDC
{
    Uint8 data[8];
    struct 
    {
        Uint8 a : 8;
        Uint8 b : 8;
        Uint8 c : 8;
        Uint8 d : 8;
        Uint8 e : 8;
        Uint8 f : 8;
        Uint8 g : 8;
        Uint8 h : 8;
    }Sig;
}CanRxDataLDC;


typedef union Can_Tx_Data_FDC1
{
    Uint8 data[8];
    struct 
    {
        Uint8 Fdc1_LsVlt_HS : 8;            //Fdc1_Low Side Voltage
        Uint8 Fdc1_HsVlt_HS : 8;            //Fdc1_High Side Voltage
        Uint8 Fdc1_LsCur_HS : 8;            //Fdc1_Low Side(input) Current(Boost : +, Buck : -)
        Uint8 Fdc1_HsHvltkReactReq_HS : 8;      //Fdc1_HighsideHighVoltageInterlockReactionRequest
                                      //0x0: FDC1 High side HVIL Reaction Not Request ^ 0x1 : FDC1 High side HVIL Reaction Request
        Uint8 Fdc1_Ctrb_HS : 8;               //Fdc1_Controllable Flag 
                                      //0x0: FDC1 Converting stop^0x1: FDC1 Converting start
        Uint8 Fdc1_Flt_HS : 8;               //Fdc1_Fault Flag, 0x0: None^0x1: Fault occurred
        Uint8 Fdc1_Wrn_HS : 8;               //Fdc1_Warning Flag, 0x0: None^0x1: Warning occurred
        Uint8 Reserved : 8;
    }Sig;
}CanTxDataFDC1;

typedef union Can_Tx_Data_FDC2
{
    Uint8 data[8];
    struct 
    {
        Uint8 Fdc1_LsCurLim_HS : 8;            //Fdc1_LowSideCurrentLimit
        Uint8 Fdc1_SiCMdulTmp_HSv : 8;         //Fdc1_SiC Module Temperature
        Uint8 Fdc1_ClntTmp_HS : 8;            //Fdc1_Coolant Temperature
        Uint8 Fdc1_LsVHvltkReactReq_HS : 8;      //Fdc1_LowsideHighVoltageInterlockReactionRequest
                                      //0x0: FDC1 Low side HVIL Reaction Not Request^0x1: FDC1Low side HVIL Reaction Request
        Uint8 Fdc1_FdcRdy_HS : 8;            //Fdc1_Ready Flag
                                      //0x0: FDC1 Low side HVIL Reaction Not Request^0x1: FDC1
        Uint8 Fdc1_RSDReq_HS : 8;            //Fdc1_RSDRequest, 0x0: None^0x1: RSD on request
        Uint8 Fdc1_DrteMde_HS : 8;            //Fdc1_DeratingModeOnOff, 0x0: off^0x1: on
        Uint8 Fdc1_Flt_OutOfDuty_HS : 8;      //Fdc1_OutOfDuty_Fault Flag, 0x0: None^0x1: Fault occurred
    }Sig;
}CanTxDataFDC2;

typedef union Can_Tx_Data_FDC3
{
    Uint8 data[8];
    struct 
    {
        Uint8 Fdc1_FailSafeGrp_HS : 8;         //Fdc1_FailsafeSafeGroup, 0x7: None fault, 
        Uint8 Fdc1_FailSafeIdx_HS : 8;         //Fdc1_FailsafeSafeIndex, 0xFF : NoneFault
        Uint8 Fdc1_Mde_HSc : 8;               //Fdc1_Mode
        Uint8 Fdc1_Sts_HS : 8;               //Fdc1_Status
        Uint8 e : 8;
        Uint8 f : 8;
        Uint8 g : 8;
        Uint8 h : 8;
    }Sig;
}CanTxDataFDC3;



//Can-FD data structures

typedef union CanFD_Rx_Data_FCU
{
    Uint8 data[64];
    struct 
    {
        Uint16 Buff0 : 16;
        Uint16 Buff1 : 16;
        Uint16 Buff2 : 16;
        Uint16 Buff3 : 16;
        Uint16 Buff4 : 16;
        Uint16 Buff5 : 16;
        Uint16 Buff6 : 16;
        Uint16 Buff7 : 16;
        Uint16 Buff8 : 16;
        Uint16 Buff9 : 16;
        Uint16 Buff10 : 16;
        Uint16 Buff11 : 16;
        Uint16 Buff12 : 16;
        Uint16 Buff13 : 16;
        Uint16 Buff14 : 16;
        Uint16 Buff15 : 16;
        Uint16 Buff16 : 16;
        Uint16 Buff17 : 16;
        Uint16 Buff18 : 16;
        Uint16 Buff19 : 16;
        Uint16 Buff20 : 16;
        Uint16 Buff21 : 16;
        Uint16 Buff22 : 16;
        Uint16 Buff23 : 16;
        Uint16 Buff24 : 16;
        Uint16 Buff25 : 16;
        Uint16 Buff26 : 16;
        Uint16 Buff27 : 16;
        Uint16 Buff28 : 16;
        Uint16 Buff29 : 16;
        Uint16 Buff30 : 16;
        Uint16 Buff31 : 16;
    }Sig;
}CanFDRxDataFCU;

typedef union CanFD_Rx_Data_BMS
{
    Uint8 data[64];
    struct 
    {
        Uint16 Buff0 : 16;
        Uint16 Buff1 : 16;
        Uint16 Buff2 : 16;
        Uint16 Buff3 : 16;
        Uint16 Buff4 : 16;
        Uint16 Buff5 : 16;
        Uint16 Buff6 : 16;
        Uint16 Buff7 : 16;
        Uint16 Buff8 : 16;
        Uint16 Buff9 : 16;
        Uint16 Buff10 : 16;
        Uint16 Buff11 : 16;
        Uint16 Buff12 : 16;
        Uint16 Buff13 : 16;
        Uint16 Buff14 : 16;
        Uint16 Buff15 : 16;
        Uint16 Buff16 : 16;
        Uint16 Buff17 : 16;
        Uint16 Buff18 : 16;
        Uint16 Buff19 : 16;
        Uint16 Buff20 : 16;
        Uint16 Buff21 : 16;
        Uint16 Buff22 : 16;
        Uint16 Buff23 : 16;
        Uint16 Buff24 : 16;
        Uint16 Buff25 : 16;
        Uint16 Buff26 : 16;
        Uint16 Buff27 : 16;
        Uint16 Buff28 : 16;
        Uint16 Buff29 : 16;
        Uint16 Buff30 : 16;
        Uint16 Buff31 : 16;
    }Sig;
}CanFDRxDataBMS;

typedef union CanFD_Rx_Data_VCU
{
    Uint8 data[64];
    struct 
    {
        Uint16 Buff0 : 16;
        Uint16 Buff1 : 16;
        Uint16 Buff2 : 16;
        Uint16 Buff3 : 16;
        Uint16 Buff4 : 16;
        Uint16 Buff5 : 16;
        Uint16 Buff6 : 16;
        Uint16 Buff7 : 16;
        Uint16 Buff8 : 16;
        Uint16 Buff9 : 16;
        Uint16 Buff10 : 16;
        Uint16 Buff11 : 16;
        Uint16 Buff12 : 16;
        Uint16 Buff13 : 16;
        Uint16 Buff14 : 16;
        Uint16 Buff15 : 16;
        Uint16 Buff16 : 16;
        Uint16 Buff17 : 16;
        Uint16 Buff18 : 16;
        Uint16 Buff19 : 16;
        Uint16 Buff20 : 16;
        Uint16 Buff21 : 16;
        Uint16 Buff22 : 16;
        Uint16 Buff23 : 16;
        Uint16 Buff24 : 16;
        Uint16 Buff25 : 16;
        Uint16 Buff26 : 16;
        Uint16 Buff27 : 16;
        Uint16 Buff28 : 16;
        Uint16 Buff29 : 16;
        Uint16 Buff30 : 16;
        Uint16 Buff31 : 16;
    }Sig;
}CanFDRxDataVCU;

typedef union CanFD_Rx_Data_LDC
{
    Uint8 data[64];
    struct 
    {
        Uint16 Buff0 : 16;
        Uint16 Buff1 : 16;
        Uint16 Buff2 : 16;
        Uint16 Buff3 : 16;
        Uint16 Buff4 : 16;
        Uint16 Buff5 : 16;
        Uint16 Buff6 : 16;
        Uint16 Buff7 : 16;
        Uint16 Buff8 : 16;
        Uint16 Buff9 : 16;
        Uint16 Buff10 : 16;
        Uint16 Buff11 : 16;
        Uint16 Buff12 : 16;
        Uint16 Buff13 : 16;
        Uint16 Buff14 : 16;
        Uint16 Buff15 : 16;
        Uint16 Buff16 : 16;
        Uint16 Buff17 : 16;
        Uint16 Buff18 : 16;
        Uint16 Buff19 : 16;
        Uint16 Buff20 : 16;
        Uint16 Buff21 : 16;
        Uint16 Buff22 : 16;
        Uint16 Buff23 : 16;
        Uint16 Buff24 : 16;
        Uint16 Buff25 : 16;
        Uint16 Buff26 : 16;
        Uint16 Buff27 : 16;
        Uint16 Buff28 : 16;
        Uint16 Buff29 : 16;
        Uint16 Buff30 : 16;
        Uint16 Buff31 : 16;
    }Sig;
}CanFDRxDataLDC;


typedef union CanFD_Tx_Data_FCU
{
    Uint8 data[64];
    struct 
    {
        Uint16 Buff0 : 16;
        Uint16 Buff1 : 16;
        Uint16 Buff2 : 16;
        Uint16 Buff3 : 16;
        Uint16 Buff4 : 16;
        Uint16 Buff5 : 16;
        Uint16 Buff6 : 16;
        Uint16 Buff7 : 16;
        Uint16 Buff8 : 16;
        Uint16 Buff9 : 16;
        Uint16 Buff10 : 16;
        Uint16 Buff11 : 16;
        Uint16 Buff12 : 16;
        Uint16 Buff13 : 16;
        Uint16 Buff14 : 16;
        Uint16 Buff15 : 16;
        Uint16 Buff16 : 16;
        Uint16 Buff17 : 16;
        Uint16 Buff18 : 16;
        Uint16 Buff19 : 16;
        Uint16 Buff20 : 16;
        Uint16 Buff21 : 16;
        Uint16 Buff22 : 16;
        Uint16 Buff23 : 16;
        Uint16 Buff24 : 16;
        Uint16 Buff25 : 16;
        Uint16 Buff26 : 16;
        Uint16 Buff27 : 16;
        Uint16 Buff28 : 16;
        Uint16 Buff29 : 16;
        Uint16 Buff30 : 16;
        Uint16 Buff31 : 16;
    }Sig;
}CanFDTxDataFCU;


/*============================================================================
   Global variables
============================================================================*/

/*============================================================================
   Function Prototypes
============================================================================*/
void ComCanIsrCtr(void);
void ComCanTask100us(void);
void ComCanTask1ms(void);
void ComCanTask10ms(void);
void ComCanTask100ms(void);

#endif
