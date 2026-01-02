/*
 * Common.h
 *
 *  Created on: 2023. 1. 3.
 *      Author: poweryhs
 */

#ifndef COMMON_H_
#define COMMON_H_

#include "stdbool.h"
#include "stdio.h"

#define CPUCLK              200e6f
#define INVCPUCLKTOUS		0.005f		// 1/200

#define Fs10                10.f
#define Fs100               100.f
#define Fs1k                1000.f
#define Fs10k               10000.f
#define Fs20k               20000.f
#define Ts10                0.1f
#define Ts100               0.01f
#define Ts1k                0.001f
#define Ts10k               0.0001f
#define Ts20k               0.00005f

#define INV3                0.3333333333333f
#define SQRT2               1.4142135623731f
#define SQRT3               1.7320508075689f
#define INVSqrt2            0.7071067811865f
#define INVSqrt3            0.5773502691896f

#define	HalfPI				1.570796327f
#define PI                  3.141592654f
#define PI2                 6.283185307f
#define INVPI				0.3183098861838f
#define INVPI2				0.1591549430919f
#define INVPI180			57.2957795130823f

#define RmstoAVG            0.9003165946415f         //2*1.414214/3.141592654
#define AVGtoRMS            1.1107203909733f

#define YES                 1U
#define NO                  0U

#define SET                 1U
#define CLEAR               0U

#define HIGH                1U
#define LOW                 0U

#define TRUE                1U
#define FALSE               0U

#define ON                  1U
#define OFF                 0U

#define kENABLE             1U
#define kDISABLE            0U

#define TIMER_TICK(TimeVariable)                TimeVariable++
#define TIMER_RESET(TimeVariable)               TimeVariable = 0U
#define COUNT_TICK(CountVariable)               CountVariable++
#define COUNT_RESET(CountVariable)              CountVariable = 0U
#define LIMIT_MAX(CurrVariable,MaxVariable)     (((CurrVariable) > (MaxVariable)) ? (MaxVariable) : (CurrVariable))
#define LIMIT_MIN(CurrVariable,MinVariable)     (((CurrVariable) < (MinVariable)) ? (MinVariable) : (CurrVariable))
#define MAX(CurrVariable,MaxVariable)           (((CurrVariable) > (MaxVariable)) ? (CurrVariable) : (MaxVariable))
#define MIN(CurrVariable,MinVariable)           (((CurrVariable) < (MinVariable)) ? (CurrVariable) : (MinVariable))
#define POW2(Variable)					        ((Variable) * (Variable))

#define BIT0_MASK   (0x00000001U)
#define BIT1_MASK   (0x00000002U)
#define BIT2_MASK   (0x00000004U)
#define BIT3_MASK   (0x00000008U)
#define BIT4_MASK   (0x00000010U)
#define BIT5_MASK   (0x00000020U)
#define BIT6_MASK   (0x00000040U)
#define BIT7_MASK   (0x00000080U)
#define BIT8_MASK   (0x00000100U)
#define BIT9_MASK   (0x00000200U)
#define BIT10_MASK  (0x00000400U)
#define BIT11_MASK  (0x00000800U)
#define BIT12_MASK  (0x00001000U)
#define BIT13_MASK  (0x00002000U)
#define BIT14_MASK  (0x00004000U)
#define BIT15_MASK  (0x00008000U)
#define BIT16_MASK  (0x00010000U)
#define BIT17_MASK  (0x00020000U)
#define BIT18_MASK  (0x00040000U)
#define BIT19_MASK  (0x00080000U)
#define BIT20_MASK  (0x00100000U)
#define BIT21_MASK  (0x00200000U)
#define BIT22_MASK  (0x00400000U)
#define BIT23_MASK  (0x00800000U)
#define BIT24_MASK  (0x01000000U)
#define BIT25_MASK  (0x02000000U)
#define BIT26_MASK  (0x04000000U)
#define BIT27_MASK  (0x08000000U)
#define BIT28_MASK  (0x10000000U)
#define BIT29_MASK  (0x20000000U)
#define BIT30_MASK  (0x40000000U)
#define BIT31_MASK  (0x80000000U)

typedef unsigned char       Uint8;
typedef unsigned char       Bool;
typedef signed char         int8;
#ifndef DSP28_DATA_TYPES
#define DSP28_DATA_TYPES
typedef int                 int16;
typedef long                int32;
typedef long long           int64;
typedef unsigned int        Uint16;
typedef unsigned long       Uint32;
typedef unsigned long long  Uint64;
//typedef float               float32;
//typedef long double         float64;
#endif

#endif /* COMMON_H_ */

