/*
 * AswInternalState.h
 *
 *  Created on: 2023. 1. 9.
 *      Author: poweryhs
 */

#ifndef ASW_ASWINTERNALSTATE_H_
#define ASW_ASWINTERNALSTATE_H_

/*============================================================================
    Includes
============================================================================*/
#include "AswVehicleDefine.h"

/*============================================================================
    Macros
============================================================================*/

/*============================================================================
    Enumerations
============================================================================*/
typedef enum {
    STAT_CBABNORMAL_STATE       = 0U
    ,STAT_INHIBIT_STATE         = 1U
    ,STAT_FATAL_STATE           = 2U
    ,STAT_FAULT_STATE           = 3U
    ,STAT_RESUME_STATE          = 4U
    ,STAT_NORMAL_STATE          = 5U
}INTERNAL_STATE;

enum INTERNAL_CBABNORMAL_STATE {
    STAT_CBABNORMAL_NORMAL          = 0x0000U        
    , STAT_ECU_POSTRUN              = 0x0001U        //0
    , STAT_AUXBATVOLT_FLT           = 0x0002U        //1
    , STAT_IGVOLT_FLT               = 0x0004U        //2
    , STAT_RESERVED_CBABNORMAL2     = 0x0008U        //3
    , STAT_RESERVED_CBABNORMAL3     = 0x0010U        //4
    , STAT_RESERVED_CBABNORMAL4     = 0x0020U        //5
    , STAT_RESERVED_CBABNORMAL5     = 0x0040U        //6
    , STAT_RESERVED_CBABNORMAL6     = 0x0080U        //7
    , STAT_RESERVED_CBABNORMAL7     = 0x0100U        //8
    , STAT_RESERVED_CBABNORMAL8     = 0x0200U        //9
    , STAT_RESERVED_CBABNORMAL9     = 0x0400U        //10
    , STAT_RESERVED_CBABNORMAL10    = 0x0800U        //11
    , STAT_RESERVED_CBABNORMAL11    = 0x1000U        //12
    , STAT_RESERVED_CBABNORMAL12    = 0x2000U        //13
    , STAT_RESERVED_CBABNORMAL13    = 0x4000U        //14
    , STAT_RESERVED_CBABNORMAL14    = 0x8000U        //15
};

enum INTERNAL_INHIBIT_STATE{
#if(DefOBCType == 1)
    STAT_SYSINHIBIT_NORMAL          = 0x0000U
    , STAT_IGOFF                    = 0x0001U        //0
    , STAT_ICCUMODE_INHIBIT         = 0x0002U        //1
    , STAT_VCMS_INHIBIT             = 0x0004U        //2
    , STAT_BMS_INHIBIT              = 0x0008U        //3
    , STAT_CANHSNOTREADY            = 0x0010U        //4
    , STAT_CANFDNOTREADY            = 0x0020U        //5
    , STAT_INTERLOCK                = 0x0040U        //6
    , STAT_GATERDY_INHIBIT          = 0x0080U        //7
    , STAT_ADCSNSR_INHIBIT          = 0x0100U        //8
    , STAT_AUXBATVOLTUV_INHIBIT     = 0x0200U        //9
    , STAT_SMPSVOLTUV_INHIBIT       = 0x0400U        //10
    , STAT_GRIDPLL_INHIBIT          = 0x0800U        //11
    , STAT_GRIDVOLTUV_INHIBIT       = 0x1000U        //12
    , STAT_DCLINKVOLTUV_INHIBIT     = 0x2000U        //13
    , STAT_OUTVOLTUV_INHIBIT        = 0x4000U        //14
    , STAT_TEST_INHIBIT             = 0x8000U        //15
#endif
};

enum INTERNAL_FATAL_STATE{
#if(DefOBCType == 1)
    STAT_FATAL_NORMAL               = 0x0000U
    , STAT_PFCCURR1SNSR_FLT         = 0x0001U        //0
    , STAT_PFCCURR2SNSR_FLT         = 0x0002U        //1
    , STAT_OUTCURR1SNSR_FLT         = 0x0004U        //2
    , STAT_OUTCURR2SNSR_FLT         = 0x0008U        //3
    , STAT_GRIDVOLTSNSR_FLT         = 0x0010U        //4
    , STAT_DCLINKVOLTSNSR_FLT       = 0x0020U        //5
    , STAT_OUTVOLTSNSR_FLT          = 0x0040U        //6
    , STAT_AUXBATVOLTSNSR_FLT       = 0x0080U        //7
    , STAT_SMPSVOLTSNSR_FLT         = 0x0100U        //8
    , STAT_IGVOLTSNSR_FLT           = 0x0200U        //9
    , STAT_TEMPSNSR1_FLT            = 0x0400U        //10
    , STAT_TEMPSNSR2_FLT            = 0x0800U        //11
    , STAT_TEMPSNSR3_FLT            = 0x1000U        //12
    , STAT_MALFUNC_FLT              = 0x2000U        //13
    , STAT_RLYMELT_FLT              = 0x4000U        //14
    , STAT_RESERVED_FATAL15         = 0x8000U        //15
#endif
 };

enum INTERNAL_FAULT_STATE {
#if(DefOBCType == 1)
    STAT_FAULT_NORMAL               = 0x0000U
    , STAT_GRIDVOLTUV_FLT           = 0x0001U        //0
    , STAT_DCLINKVOLTUV_FLT         = 0x0002U        //1
    , STAT_GRIDVOLTOV_FLT           = 0x0004U        //2
    , STAT_DCLINKVOLTOV_FLT         = 0x0008U        //3
    , STAT_OUTVOLTOV_FLT            = 0x0010U        //4
    , STAT_TEMP1HIGH_FLT            = 0x0020U        //5
    , STAT_TEMP2HIGH_FLT            = 0x0040U        //6
    , STAT_TEMP3HIGH_FLT            = 0x0080U        //7
    , STAT_SMPSVOLTOV_FLT           = 0x0100U        //8
    , STAT_GRIDPLL_FLT              = 0x0200U        //9
    , STAT_GRIDVOLTCTR_FLT          = 0x0400U        //10
    , STAT_DCLINKVOLTCTR_FLT        = 0x0800U        //11
    , STAT_OUTVOLTCTR_FLT           = 0x1000U        //12
    , STAT_INDCURRCTR_FAULT         = 0x2000U        //13
    , STAT_DCDCCURRCTR_FAULT        = 0x4000U        //14
    , STAT_RESERVED_FAULT15         = 0x8000U        //15
#endif
};

enum INTERNAL_RESUME_STATE {
#if(DefOBCType == 1)
    STAT_RESUME_NORMAL              = 0x0000U
    , STAT_PFCCURR1_RESUME          = 0x0001U        //0
    , STAT_PFCCURR2_RESUME          = 0x0002U        //1
    , STAT_OUTCURR1_RESUME          = 0x0004U        //2
    , STAT_OUTCURR2_RESUME          = 0x0008U        //3
    , STAT_PFCGATE_RESUME           = 0x0010U        //4
    , STAT_DCDCGATE_RESUME          = 0x0020U        //5
    , STAT_RESERVED_RESUME6         = 0x0040U        //6
    , STAT_RESERVED_RESUME7         = 0x0080U        //7
    , STAT_RESERVED_RESUME8         = 0x0100U        //8
    , STAT_RESERVED_RESUME9         = 0x0200U        //9
    , STAT_RESERVED_RESUME10        = 0x0400U        //10
    , STAT_RESERVED_RESUME11        = 0x0800U        //11
    , STAT_RESERVED_RESUME12        = 0x1000U        //12
    , STAT_RESERVED_RESUME13        = 0x2000U        //13
    , STAT_RESERVED_RESUME14        = 0x4000U        //14
    , STAT_RESERVED_RESUME15        = 0x8000U        //15
#endif
};

enum INTERNAL_NORMAL_STATE {
#if(DefOBCType == 1)
    STAT_NORMAL                     = 0x0000U
    , STAT_ICCUCHARGING             = 0x0001U        //0
    , STAT_ICCUDISCHARGING          = 0x0002U        //1
    , STAT_PFCRLYON                 = 0x0004U        //2
    , STAT_PFCSOFTSTART             = 0x0008U        //3
    , STAT_PFCON                    = 0x0010U        //4
    , STAT_DCDCSOFTSTART            = 0x0020U        //5
    , STAT_DCDCON                   = 0x0040U        //6
    , STAT_CCCHARGING               = 0x0080U        //7
    , STAT_CPCHARGING               = 0x0100U        //8
    , STAT_CVCHARGING               = 0x0200U        //9
    , STAT_DCDCSINGLEMOUDLE         = 0x0400U        //10
    , STAT_TEMPDEREATING            = 0x0800U        //11
    , STAT_GRIDVOLTDEREATING        = 0x1000U        //12
    , STAT_CANHS                    = 0x2000U        //13
    , STAT_CANFD                    = 0x4000U        //14
    , STAT_RESERVED_NORMAL15        = 0x8000U        //15
#endif
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
