/*
 * BSW_Vehicle_Define.h
 *
 *  Created on: 2023. 1. 4.
 *      Author: poweryhs
 */

#ifndef BSW_BSWVEHICLEDEFINE_H_
#define BSW_BSWVEHICLEDEFINE_H_


#define ADCCHANNELNUM       3
#define CURRSNSRNUM         1
#define VOLTSNSRNUM         2

#define CURRHWFLTNUM        2
#define CURRHWFLT1          0
#define CURRHWFLT2          1
#define VOLTHWFLTNUM        2
#define INVOLTHWFLT         0
#define OUTVOLTHWFLT        1
#define GATEHWFLTNUM        1
#define GATEHWFLT           0

#define PWMFREQ             70000.f
#define PWMTS               1.429e-5f
#define ISRPWMEVTNUM        1.f
#define ISRFREQ             PWMFREQ/ISRPWMEVTNUM
#define ISRTS               PWMTS*ISRPWMEVTNUM


//#define DefDisableHWFlt

#endif /* BSW_BSWVEHICLEDEFINE_H_ */
