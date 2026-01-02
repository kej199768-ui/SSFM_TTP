/*
 * BswAdc.h
 *
 *  Created on: 2022. 11. 29.
 *      Author: poweryhs
 */

#ifndef BSW_BSWADC_H_
#define BSW_BSWADC_H_

/*============================================================================
    Includes
============================================================================*/
#include "BswCommon.h"
#include "BswVehicleDefine.h"


/*============================================================================
    Macros
============================================================================*/

//
//ADCTRIGSEL
//
#define ADCTRIG0	0x00	//Software only
#define ADCTRIG1	0x01	//CPU1 Timer 0, TINT0n
#define ADCTRIG2	0x02	//CPU1 Timer 1, TINT1n
#define ADCTRIG3	0x03	//CPU1 Timer 2, TINT2n
#define ADCTRIG4	0x04	//GPIO, ADCEXTSOC
#define ADCTRIG5	0x05	//ePWM1, ADCSOCA
#define ADCTRIG6	0x06	//ePWM1, ADCSOCB
#define ADCTRIG7	0x07	//ePWM2, ADCSOCA
#define ADCTRIG8	0x08	//ePWM2, ADCSOCB
#define ADCTRIG9	0x09	//ePWM3, ADCSOCA
#define ADCTRIG10	0x0A	//ePWM3, ADCSOCB
#define ADCTRIG11	0x0B	//ePWM4, ADCSOCA
#define ADCTRIG12	0x0C	//ePWM4, ADCSOCB
#define ADCTRIG13	0x0D	//ePWM5, ADCSOCA
#define ADCTRIG14	0x0E	//ePWM5, ADCSOCB
#define ADCTRIG15	0x0F	//ePWM6, ADCSOCA
#define ADCTRIG16	0x10	//ePWM6, ADCSOCB
#define ADCTRIG17	0x11	//ePWM7, ADCSOCA
#define ADCTRIG18	0x12	//ePWM7, ADCSOCB
#define ADCTRIG19	0x13	//ePWM8, ADCSOCA
#define ADCTRIG20	0x14	//ePWM8, ADCSOCB
#define ADCTRIG21	0x15	//ePWM9, ADCSOCA
#define ADCTRIG22	0x16	//ePWM9, ADCSOCB
#define ADCTRIG23	0x17	//ePWM10, ADCSOCA
#define ADCTRIG24	0x18	//ePWM10, ADCSOCB
#define ADCTRIG25	0x19	//ePWM11, ADCSOCA
#define ADCTRIG26	0x1A	//ePWM11, ADCSOCB
#define ADCTRIG27	0x1B	//ePWM12, ADCSOCA
#define ADCTRIG28	0x1C	//ePWM12, ADCSOCB
#define ADCTRIG29	0x1D	//CPU2 Timer 0, TINT0n
#define ADCTRIG30	0x1E	//CPU2 Timer 1, TINT1n
#define ADCTRIG31	0x1F	//CPU2 Timer 2, TINT2n

//
//ADCINTSEL
//
#define INTSELEOC0	0x0		//EOC0 is trigger for ADCINT
#define INTSELEOC1	0x1		//EOC1 is trigger for ADCINT
#define INTSELEOC2	0x2		//EOC2 is trigger for ADCINT
#define INTSELEOC3	0x3		//EOC3 is trigger for ADCINT
#define INTSELEOC4	0x4		//EOC4 is trigger for ADCINT
#define INTSELEOC5	0x5		//EOC5 is trigger for ADCINT
#define INTSELEOC6	0x6		//EOC6 is trigger for ADCINT
#define INTSELEOC7	0x7		//EOC7 is trigger for ADCINT
#define INTSELEOC8	0x8		//EOC8 is trigger for ADCINT
#define INTSELEOC9	0x9		//EOC9 is trigger for ADCINT
#define INTSELEOC10	0xA		//EOC10is trigger for ADCINT
#define INTSELEOC11	0xB		//EOC11is trigger for ADCINT
#define INTSELEOC12	0xC		//EOC12is trigger for ADCINT
#define INTSELEOC13	0xD		//EOC13is trigger for ADCINT
#define INTSELEOC14	0xE		//EOC14is trigger for ADCINT
#define INTSELEOC15	0xF		//EOC15is trigger for ADCINT

/*============================================================================
    Enumerations
============================================================================*/

/*============================================================================
    Data Structures
============================================================================*/

/*============================================================================
    Global variables
============================================================================*/
extern float gfCurrCal[CURRSNSRNUM];
extern float gfVoltCal[VOLTSNSRNUM];
extern float gfCurrRaw[CURRSNSRNUM];
extern float gfVoltRaw[VOLTSNSRNUM];

extern Uint16 giAdcoffsetCplFlag;
/*============================================================================
    Private Variables/Constants
============================================================================*/

/*============================================================================
    Function Prototypes
============================================================================*/
void InitAdcConfig(void);
void InitDACConfig(void);
void BswAdcIsrOffsetCalc(void);
void BswAdcIsrCalc(void);


#endif /* INITADC_H_ */

