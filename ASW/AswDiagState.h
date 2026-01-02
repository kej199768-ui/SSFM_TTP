/*
 * AswDiagState.h
 *
 *  Created on: 2023. 1. 9.
 *      Author: poweryhs
 */

#ifndef ASW_ASWDIAGSTATE_H_
#define ASW_ASWDIAGSTATE_H_

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
    IGVOLTSNSR_READY                = 0U
    , IGVOLTSNSR_NORMAL             = 1U
    , IGVOLTSNSR_VOLTLO_FLT         = 2U
    , IGVOLTSNSR_VOLTHI_FLT         = 3U
    , IGVOLTSNSR_RATIONAL_FLT       = 4U
}IGVOLTSNSR_STATE;

typedef enum {
    ICCUMODE_INHIBIT                = 0U
    , ICCUMODE_CHARGING             = 1U
    , ICCUMODE_V2L                  = 2U
    , ICCUMODE_V2G                  = 3U
}ICCUMODE_STATE;

typedef enum {
    IG_OFF                          = 0U
    , IG_GOOFF                      = 1U
    , IG_ON                         = 2U
    , IG_SWOV_FLT                   = 3U
}IGVOLT_STATE;

typedef enum {
    AUXBATVOLTSNSR_READY            = 0U
    , AUXBATVOLTSNSR_NORMAL         = 1U
    , AUXBATVOLTSNSR_VOLTLO_FLT     = 2U
    , AUXBATVOLTSNSR_VOLTHI_FLT     = 3U
    , AUXBATVOLTSNSR_RATIONAL_FLT   = 4U
}AUXBATVOLTSNSR_STATE;

typedef enum {
    AUXBATVOLT_NORMAL               = 0U
    , AUXBATVOLT_SWOV_FLT           = 1U
    , AUXBATVOLT_SWUV_INHIBIT       = 2U
}AUXBATVOLT_STATE;

typedef enum {
    SMPSVOLTSNSR_READY              = 0U
    , SMPSVOLTSNSR_NORMAL           = 1U
    , SMPSVOLTSNSR_VOLTLO_FLT       = 2U
    , SMPSVOLTSNSR_VOLTHI_FLT       = 3U
    , SMPSVOLTSNSR_RATIONAL_FLT     = 4U
}SMPSVOLTSNSR_STATE;

typedef enum {
    SMPSVOLT_NORMAL                 = 0U
    , SMPSVOLT_SWOV_FLT             = 1U
    , SMPSVOLT_SWUV_INHIBIT         = 2U
}SMPSVOLT_STATE;

typedef enum {
    RLY_OFF                         = 0U
    , RLY_ON                        = 1U
    , RLY_OPEN                      = 2U
    , RLY_MELTING                   = 3U
}RLY_STATE;

typedef enum {
    ECU_NORMAL                      = 0U
    , ECU_PORTRUN                   = 1U
}ECU_STATE;

typedef enum {
    FCU_NORMAL                      = 0U
    , FCU_INHIBIT                   = 1U
    , FCU_FLT                       = 2U
}FCU_STATE;

typedef enum {
    BMS_NORMAL                      = 0U
    , BMS_INHIBIT                   = 1U
    , BMS_FLT                       = 2U
}BMS_STATE;

#if 0
typedef enum {

}FAILSAFE_STATE;
#endif

typedef enum {
    CANHS_NORMAL                    = 0U
    , CANHS_NOTREADY                = 1U
    , CANHS_BUSOFF                  = 2U
    , CANHS_TIMEOUT                 = 3U
}CANHS_STATE;

typedef enum {
    CANFD_NORMAL                    = 0U
    , CANFD_NOTREADY                = 1U
    , CANFD_BUSOFF                  = 2U
    , CANFD_TIMEOUT                 = 3U
}CANFD_STATE;

typedef enum {
    ICCUVOLTSNSR_READY               = 0U
    , ICCUVOLTSNSR_NORMAL            = 1U
    , ICCUVOLTSNSR_VOLTLO_FLT        = 2U
    , ICCUVOLTSNSR_VOLTHI_FLT        = 3U
    , ICCUVOLTSNSR_RATIONAL_FLT      = 4U
    , ICCUVOLTSNSR_VOLTSTUCK_FLT     = 5U
}ICCUVOLTSNSR_STATE;

typedef enum {
    ICCUVOLT_NORMAL                  = 0U
    , ICCUVOLT_HWOV_FLT              = 1U
    , ICCUVOLT_SWOV_FLT              = 2U
    , ICCUVOLT_UV_INHIBIT_FLT        = 3U
}ICCUVOLT_STATE;


typedef enum {
    ICCUCURRSNSR_READY               = 0U
    , ICCUCURRSNSR_NORMAL            = 1U
    , ICCUCURRSNSR_VOLTLO_FLT        = 2U
    , ICCUCURRSNSR_VOLTHI_FLT        = 3U
    , ICCUCURRSNSR_RATIONAL_FLT      = 4U
//  , ICCUCURRSNSR_VOLTSTUCK_FLT     = 4U
}ICCUCURRSNSR_STATE;

typedef enum {
    ICCUCURR_NORMAL                  = 0U
    , ICCUCURR_HWOC_WAITRESUME       = 1U
    , ICCUCURR_SWOC_WAITRESUME       = 2U
    , ICCUCURR_HWOC_FLT              = 3U
    , ICCUCURR_SWOC_FLT              = 4U
}ICCUCURR_STATE;

typedef enum {
    TEMPSNSR_READY                  = 0U
    , TEMPSNSR_NORMAL               = 1U
    , TEMPSNSR_VOLTLO_FLT           = 2U
    , TEMPSNSR_VOLTHI_FLT           = 3U
    , TEMPSNSR_RATIONAL_FLT         = 4U
//  , TEMPSNSR_VOLTSTUCK_FLT        = 4
}TEMPSNSR_STATE;

typedef enum {
    MALFUNC_NORMAL                  = 0U
    , MALFUNC_INPATH_FLT            = 1U
    , MALFUNC_OUTPATH_FLT           = 2U
    , MALFUNC_FDCINVOLT_FLT         = 3U
    , MALFUNC_FDCOUTVOLT_FLT        = 4U
}MALFUNC_STATE;

typedef enum {
    PWM_NORMAL                      = 0U
    , PWM_OUT_FLT                   = 1U
}PWM_STATE;

typedef enum {
    GATE_NOTREADY                   = 0U
    , GATE_NORMAL                   = 1U
    , GATE_HWFLT                    = 2U
}GATE_STATE;

typedef enum {
    OPERATING_NON                   = 0U 
    , OPERATING_PFCRLYON            = 1U
    , OPERATING_PFCSOFTSTART        = 2U
    , OPERATIN_PFCON                = 3U
    , OPERATIN_DCDCSOFTSTART        = 4U
    , OPERATIN_DCDCON               = 5U
    , OPERATIN_CCCHARGING           = 6U
    , OPERATIN_CPCHARGING           = 7U
    , OPERATIN_CVCHARGING           = 8U
}OPERATING_STATE;

typedef enum {
    TEMP_NORMAL                     = 0U
    , TEMP_HIGH_DERATING            = 1U
    , TEMP_HIGH_FLT                 = 2U
}TEMP_STATE;

typedef enum {
    DERATING_NORMAL                 = 0U
    , DERATING_GRIDVOLT             = 1U
    , DERATING_TEMP                 = 2U
    , DERATING_GRIDVOLTTEMP         = 3U
}DERATING_STATE;

typedef enum
{
    VOLTCTRSTATE_INHIBIT            = 0U
    , VOLTCTRSTATE_READY_SS         = 1U
    , VOLTCTRSTATE_NORMAL           = 2U
    , VOLTCTRSTATE_FLT              = 3U
}VOLTCTRSTATE;

typedef enum
{
    CURRCTRSTATE_INHIBIT            = 0U
    , CURRCTRSTATE_NORMAL           = 1U
    , CURRCTRSTATE_FLT              = 2U
}CURRCTRSTATE;

typedef enum
{
    ICCUOBCMODE_CHAGING             = 0U
    , ICCUOBCMODE_DISCHAGING        = 1U
}ICCUOBCMODE;


/*============================================================================
    Global variables
============================================================================*/

/*============================================================================
    Private Variables/Constants
============================================================================*/

/*============================================================================
    Function Prototypes
============================================================================*/





#endif /* ASW_ASWDIAGSTATE_H_ */
