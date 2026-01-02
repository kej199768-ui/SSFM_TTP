/*
 * AswDiagState.h
 *
 *  Created on: 2023. 1. 9.
 *      Author: poweryhs
 */

#ifndef ASW_BACKUP_ASWDIAGSTATE_H_
#define ASW_BACKUP_ASWDIAGSTATE_H_

/*============================================================================
    Includes
============================================================================*/

/*============================================================================
    Macros
============================================================================*/

/*============================================================================
    Enumerations
============================================================================*/

/*============================================================================
    Data Structures
============================================================================*/
typedef enum {
    VOLT_NORMAL                  = 0
    , VOLT_HWOV_FLT              = 1
    , VOLT_SWOV_FLT              = 2
    , VOLT_UV_INHIBIT            = 3
}VOLT_STATE;

typedef enum {
    CURR_NORMAL                  = 0
    , CURR_HWOC_WAITRESUME       = 1
    , CURR_SWOC_WAITRESUME       = 2
    , CURR_HWOC_FLT              = 3
    , CURR_SWOC_FLT              = 4
}CURR_STATE;

typedef enum {
    TEMP_NORMAL                  = 0
    , TEMP_HIGH_DERATING         = 1
    , TEMP_HIGH_FLT              = 2
}TEMP_STATE;

typedef enum
{
    CURRCTRSTATE_INHIBIT         = 0
    , CURRCTRSTATE_READY_SS      = 1
    , CURRCTRSTATE_NORMAL        = 2
    , CURRCTRSTATE_FLT           = 3
}CURRCTR_STATE;

typedef enum
{
    VOLTCTRSTATE_INHIBIT         = 0
    , VOLTCTRSTATE_READY_SS      = 1
    , VOLTCTRSTATE_NORMAL        = 2
    , VOLTCTRSTATE_FLT           = 3
}VOLTCTR_STATE;

typedef enum
{
    SRSTATE_SROFF                = 0    //SROFF
    , SRSTATE_SRANDING           = 1    //Lead & Lag
    , SRSTATE_SRORING            = 2    //Lag | Lead
    , SRSTATE_SRSLEADING         = 3    //Lead
}SR_STATE;

typedef enum
{
    OBCLDCMODE_INHIBIT          = 0    //INHIBIT
    , OBCLDCMODE_CHARGING       = 1    //OBCCHARGING
    , OBCLDCMODE_DISCHARGING    = 2    //OBCDISCHARGING
    , OBCLDCMODE_SEPERATELDC    = 3    //SEPERATELDC 
}OBCLDCMODE_STATE;

typedef enum
{
    LDC_INHIBIT          = 0    //INHIBIT
    , LDC_CVCTR          = 1    //CV제어
    , LDC_CCCTR          = 2    //CC제어
}LDCCTRMODE_STATE;

/*============================================================================
    Global variables
============================================================================*/

/*============================================================================
    Private Variables/Constants
============================================================================*/

/*============================================================================
    Function Prototypes
===========================================================================*/

#endif /* ASW_BACKUP_ASWDIAGSTATE_H_ */
