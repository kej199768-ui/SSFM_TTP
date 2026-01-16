/*
 * Util.h
 *
 *  Created on: 2023. 1. 3.
 *      Author: poweryhs
 */

#ifndef UTIL_H_
#define UTIL_H_

#include "Common.h"
#include "math.h"
#include "stdlib.h"


 /*-----------------------------------------------------------------------------
 Define the structure of the 3-phase variable
 -----------------------------------------------------------------------------*/
typedef struct {
    float  u;
    float  v;
    float  w;

}uvw;
#define uvw_defaults {0.f,0.f,0.f}

/*-----------------------------------------------------------------------------
Define the structure of the Line to Line variable
-----------------------------------------------------------------------------*/
typedef struct {
    float uv;
    float vw;
    float wu;
}uvw_LL;

#define uvw_LL_defaults 	{0.f,0.f,0.f}

/*-----------------------------------------------------------------------------
Define the structure of the d-q variable
-----------------------------------------------------------------------------*/
//int와 같이 dq가 구조체를 선언
typedef struct {
    float  d;
    float  q;
}dq;

#define dq_defaults {0.f,0.f}

/*-----------------------------------------------------------------------------
Define the structure of the 1-order filter
-----------------------------------------------------------------------------*/
typedef struct {
    float input;
    float input_old1;
    float output;
    float output_old1;
}filter1;

#define filter1_defaults {0.f,0.f,0.f,0.f}

/*-----------------------------------------------------------------------------
Define the structure of the 2-order filter
-----------------------------------------------------------------------------*/
typedef struct {
    float input;
    float input_old1;
    float input_old2;
    float output;
    float output_old1;
    float output_old2;
}filter2;

#define filter2_defaults {0.f,0.f,0.f,0.f,0.f,0.f}

/*-----------------------------------------------------------------------------
Define the structure of the PI controller
-----------------------------------------------------------------------------*/
typedef struct {
    float  Ref;             // Input : Reference input
    float  Fdb;                 // Input : Feedback input
    float  Integ;
    float  Kp;                      // Parameter: Proportional gain
    float  Ki;                      // Parameter: Integral gain
    float  Ka;                      // Parameter: Anti-windup gain
    Uint16  Alpha;                  // Parameter: IP-PI control ratio
    float  Tsamp;                   // Parameter: Sampling time
    float  Err;                 // Variable: Error
    float  FF;                      // Variable: Feedforward term
    float  Fb;                      // Variable: Feedback term
    float  OutMax;                  // Variable: Output limit max
    float  OutMin;                  // Variable: Output limit min
    float  outtemp;
    float  out;                 // Variable: PI control out
}PI_con;

#define PI_con_defaults { 0.f,0.f,0.f,0.f,0.f,0.f,0,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f}

/*-----------------------------------------------------------------------------
Define the structure of the PID controller
-----------------------------------------------------------------------------*/

typedef struct {
    float  Ref;                 // Input : Reference input
    float  Fdb;                 // Input : Feedback input
    float  Integ;
    float  Diff;
    float  Kp;                  // Parameter: Proportional gain
    float  Ki;                  // Parameter: Integral gain
    float  Kd;                  // Parameter: Differentail gain
    float  Ka;                  // Parameter: Anti-windup gain
    Uint16  Alpha;              // Parameter: IP-PI control ratio
    float  Tsamp;               // Parameter: Sampling time
    float  Err;                 // Variable: Error
    float  Err1;                // Variable: Error
    float  FF;                  // Variable: Feedforward term
    float  Fb;                  // Variable: Feedback term
    float  OutMax;              // Variable: Output limit max
    float  OutMin;              // Variable: Output limit min
    float  outtemp;
    float  out;                 // Variable: PI control out
}PID_con;

#define PID_con_defaults { 0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f}


/*-----------------------------------------------------------------------------
Define the structure of the PIR controller
-----------------------------------------------------------------------------*/
typedef struct {
    float  Ref;                 // Input : Reference input
    float  Fdb;                 // Input : Feedback input
    float  Integ;
    float  Kp;                  // Parameter: Proportional gain
    float  Ki;                  // Parameter: Integral gain
    float  Res;                 // Parameter: Resonant Filter
    float  Ka;                  // Parameter: Anti-windup gain
    Uint16 Alpha;               // Parameter: IP-PI control ratio
    float  Tsamp;               // Parameter: Sampling time
    float  Err;                 // Variable: Error
    float  FF;                  // Variable: Feedforward term
    float  Fb;                  // Variable: Feedback term
    float  OutMax;              // Variable: Output limit max
    float  OutMin;              // Variable: Output limit min
    float  outtemp;
    float  out;                 // Variable: PI control out
    filter2 ResFilter;
}PIR_con;

#define PIR_con_defaults { 0.f,0.f,0.f,0.f,0.f,0.f,0.f,0,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,filter2_defaults}


/*-----------------------------------------------------------------------------
Define the structure of the PI + Complex 2P2Z controller
-----------------------------------------------------------------------------*/
typedef struct {
    float  Ref;                 // Input : Reference input
    float  Fdb;                 // Input : Feedback input
    float  Integ;
    float  Kp;                  // Parameter: Proportional gain
    float  Ki;                  // Parameter: Integral gain
    float  Ka;                  // Parameter: Anti-windup gain
    Uint16 Alpha;               // Parameter: IP-PI control ratio
    float  Tsamp;               // Parameter: Sampling time
    float  Err;                 // Variable: Error
    float  ErrCPX2P2Z;          // Variable: Err and Complex 2P2Z
    float  FF;                  // Variable: Feedforward term
    float  Fb;                  // Variable: Feedback term
    float  OutMax;              // Variable: Output limit max
    float  OutMin;              // Variable: Output limit min
    float  outtemp;
    float  out;                 // Variable: PI control out
    filter2 CPX2P2Z;
}PICPX2P2Z_con;

#define PICPX2P2Z_con_defaults { 0.f,0.f,0.f,0.f,0.f,0.f,0U,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,filter2_defaults}



/*-----------------------------------------------------------------------------
Define the structure of the 2P1Z controller Trapezoidal
-----------------------------------------------------------------------------*/

typedef struct {
    float  Ref;                     // Input : Reference input
    float  Fdb;                     // Input : Feedback input
    float  Kp;                      // Parameter: Proportional gain
    float  Wp;                      // Parameter: Pole1
    float  Wz;                      // Parameter: Zero1
    float  Ka;                      // Parameter: Anti-windup gain
    float  Tsamp;                   // Parameter: Sampling time
    float  Err;                     // Variable: Error
    float  Err1;                    // Variable: Error
    float  Err2;                    // Variable: Error
    float  FF;                      // Variable: Feedforward term
    float  Fb;                      // Variable: Feedback term
    float  OutMax;                  // Variable: Output limit max
    float  OutMin;                  // Variable: Output limit min
    float  outtemp;
    float  outtemp1;
    float  outtemp2;
    float  out;                 // Variable: PI control out
}TPOZ_con;

#define TPOZ_con_defaults { 0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f}

/*-----------------------------------------------------------------------------
Define the structure of the 2P2Z controller Trapezoidal
-----------------------------------------------------------------------------*/

typedef struct {
    float  Ref;                 // Input : Reference input
    float  Fdb;                 // Input : Feedback input
    float  Kp;                  // Parameter: Proportional gain
    float  Wp1;                 // Parameter: Pole1
    float  Wz1;                 // Parameter: Zero1
    float  Wp2;                 // Parameter: Pole2
    float  Wz2;                 // Parameter: Zero2
    float  Ka;                  // Parameter: Anti-windup gain
    float  Tsamp;               // Parameter: Sampling time
    float  Err;                 // Variable: Error
    float  Err1;                // Variable: Error
    float  Err2;                // Variable: Error
    float  Err3;                // Variable: Error
    float  FF;                  // Variable: Feedforward term
    float  Fb;                  // Variable: Feedback term
    float  OutMax;              // Variable: Output limit max
    float  OutMin;              // Variable: Output limit min
    float  outtemp;
    float  outtemp1;
    float  outtemp2;
    float  outtemp3;
    float  out;                 // Variable: PI control out
}TPTZ_con;

#define TPTZ_con_defaults { 0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f}


//reference frame
extern uvw L2LtoPhase(uvw_LL* in);
extern dq park_calc(dq* in, float angle);
extern dq ipark_calc(dq* in, float angle);
extern dq clacke_calc(uvw* in);
extern uvw iclacke_calc(dq* in);
extern uvw SVPWM_calc(uvw* in);
extern uvw Positive_Seq(uvw* in, uvw* in_APF);
extern uvw Negative_Seq(uvw* in, uvw* in_APF);
extern uvw Zero_Seq(uvw* in, uvw* in_APF);

//PI control
extern void PI_Control_calc(PI_con* in);
extern void PID_Control_calc(PID_con* in);
extern void PIR_Control_calc(PIR_con* in, float Wres);
extern void PICPX2P2Z_Control_calc(PICPX2P2Z_con* in, float Wp, float ZetaPole, float Wz, float ZetaZero);
extern void TPOZ_Control_calc(TPOZ_con* in);
extern void TPTZ_Control_calc(TPTZ_con* in);


// 1-order digital Filter
extern float LPF1(float Tsamp, float fc, float in, filter1* out);
// 2-order digital Filter
extern float LPF2(float Tsamp, float fc, float zeta, float in, filter2* out);
extern float HPF2(float Tsamp, float fc, float zeta, float in, filter2* out);
extern float BPF2(float Tsamp, float fc, float Band, float in, filter2* out);
extern float BSF2(float Tsamp, float fc, float zeta, float in, filter2* out);
extern float SBPF2(float Tsamp, float fc, float zeta, float in, filter2* out);
extern float APF1(float Tsamp, float fc, float in, filter1* out);
extern float APF2(float Tsamp, float fc, float in, filter2* out);
extern float RES(float Tsamp, float Ws, float Kr, float h, float in, filter2* out);
extern float CPXTPTZF2(float Tsamp, float Kp, float Wp, float ZetaPole, float Wz, float ZetaZero, float in, filter2* out);
// interpolation
float Interp1DCalc(float* x, float* y, Uint16 xsize, Uint16 ysize, float input);
float Interp2DCalc(float* x, float* y, float* value, Uint16 xsize, Uint16 ysize, float xinput, float yinput);
float Interp3DCalc(float* x, float* y, float* z, float* value, Uint16 xsize, Uint16 ysize, Uint16 zsize, float xinput, float yinput, float zinput);

// Random
extern float GetRandom(float Max, float Min);

#endif /* UTIL_H_ */
