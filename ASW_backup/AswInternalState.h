/*
 * AswInternalState.h
 *
 *  Created on: 2023. 1. 9.
 *      Author: poweryhs
 */

#ifndef ASW_BACKUP_ASWINTERNALSTATE_H_
#define ASW_BACKUP_ASWINTERNALSTATE_H_

/*============================================================================
    Includes
============================================================================*/
#include <ASW_backup/AswVehicleDefine.h>

/*============================================================================
    Macros
============================================================================*/

/*============================================================================
    Enumerations
============================================================================*/
typedef enum {
    STAT_INHIBIT_STATE         = 0
    ,STAT_FAULT_STATE          = 1
    ,STAT_NORMAL_STATE         = 2
}INTERNAL_STATE;

enum INTERNAL_INHIBIT_STATE{
    STAT_INHIBIT_NORMAL             = 0x0000
    , STAT_TEST_INHIBIT             = 0x0001        //0
    , STAT_LDC_INHIBIT              = 0x0002        //1
    , STAT_RESERVED_INHIBIT2        = 0x0004        //2
    , STAT_RESERVED_INHIBIT3        = 0x0008        //3
    , STAT_RESERVED_INHIBIT4        = 0x0010        //4
    , STAT_RESERVED_INHIBIT5        = 0x0020        //5
    , STAT_RESERVED_INHIBIT6        = 0x0040        //6
    , STAT_RESERVED_INHIBIT7        = 0x0080        //7
    , STAT_RESERVED_INHIBIT8        = 0x0100        //8
    , STAT_RESERVED_INHIBIT9        = 0x0200        //9
    , STAT_RESERVED_INHIBIT10       = 0x0400        //10
    , STAT_RESERVED_INHIBIT11       = 0x0800        //11
    , STAT_RESERVED_INHIBIT12       = 0x1000        //12
    , STAT_RESERVED_INHIBIT13       = 0x2000        //13
    , STAT_RESERVED_INHIBIT14       = 0x4000        //14
    , STAT_RESERVED_INHIBIT15       = 0x8000        //15
};

enum INTERNAL_FAULT_STATE {
    STAT_FAULT_NORMAL               = 0x0000
    , STAT_OBCINOC_FLT              = 0x0001        //0
    , STAT_OBCOUTOC_FLT             = 0x0002        //1
    , STAT_LDCOUTOC_FLT             = 0x0004        //2
    , STAT_OBCINOV_FLT              = 0x0008        //3
    , STAT_OBCOUTOV_FLT             = 0x0010        //4
    , STAT_LDCOUTOV_FLT             = 0x0020        //5
    , STAT_RESERVED_FAULT6          = 0x0040        //6
    , STAT_RESERVED_FAULT7          = 0x0080        //7
    , STAT_RESERVED_FAULT8          = 0x0100        //8
    , STAT_RESERVED_FAULT9          = 0x0200        //9
    , STAT_RESERVED_FAULT10         = 0x0400        //10
    , STAT_RESERVED_FAULT11         = 0x0800        //11
    , STAT_RESERVED_FAULT12         = 0x1000        //12
    , STAT_RESERVED_FAULT13         = 0x2000        //13
    , STAT_RESERVED_FAULT14         = 0x4000        //14
    , STAT_RESERVED_FAULT15         = 0x8000        //15
};

enum INTERNAL_NORMAL_STATE {
    STAT_NORMAL                     = 0x0000
    , STAT_CHARGING_MODE            = 0x0001        //0
    , STAT_DISCHARGING_MODE         = 0x0002        //1
    , STAT_SEPERATELDC_MODE         = 0x0004        //2
    , STAT_RESERVED_NORMAL3         = 0x0008        //3
    , STAT_RESERVED_NORMAL4         = 0x0010        //4
    , STAT_RESERVED_NORMAL5         = 0x0020        //5
    , STAT_RESERVED_NORMAL6         = 0x0040        //6
    , STAT_RESERVED_NORMAL7         = 0x0080        //7
    , STAT_RESERVED_NORMAL8         = 0x0100        //8
    , STAT_RESERVED_NORMAL9         = 0x0200        //9
    , STAT_RESERVED_NORMAL10        = 0x0400        //10
    , STAT_RESERVED_NORMAL11        = 0x0800        //11
    , STAT_RESERVED_NORMAL12        = 0x1000        //12
    , STAT_RESERVED_NORMAL13        = 0x2000        //13
    , STAT_RESERVED_NORMAL14        = 0x4000        //14
    , STAT_RESERVED_NORMAL15        = 0x8000        //15
};
/*============================================================================
    Data Structures
============================================================================*/

/*============================================================================
    Global variables
============================================================================*/

/*============================================================================
    Function Prototypes
============================================================================*/

#endif /* ASWINTERNALSTATE_H_ */
