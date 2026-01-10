/*
 * Util.c
 *
 *  Created on: 2023. 1. 3.
 *      Author: poweryhs
 *  Updated on: 2026. 1. 10.
 *      Author: Kim Eunji
 *      Change: Add Random number generator function
 */

#include "Common.h"
#include "Util.h"


 /* line to line voltage transformation to Phase voltage*/
uvw L2LtoPhase(uvw_LL* in)
{
    uvw out = { 0.0f, };

    out.u = (in->uv - in->wu) * INV3;
    out.v = (in->vw - in->uv) * INV3;
    out.w = (in->wu - in->vw) * INV3;

    return out;
}


/* park transformation function*/
dq park_calc(dq* in, float angle)
{
    dq	out = { 0.0f, };

    out.d = in->d * cosf(angle) + in->q * sinf(angle);
    out.q = in->q * cosf(angle) - in->d * sinf(angle);

    return out;
}/* end of park_calc()*/

/* inverse park transformation function*/
dq ipark_calc(dq* in, float angle)
{
    dq	out = { 0.0f, };

    out.d = in->d * cosf(angle) - in->q * sinf(angle);
    out.q = in->q * cosf(angle) + in->d * sinf(angle);
    return out;
}/* end of ipark_calc()*/

/* clacke transformation function*/
dq clacke_calc(uvw* in)
{
    dq	out = { 0.0f, };

    out.d = in->u;
    out.q = (in->u + 2 * in->v) * 0.57735026918963f;  // 1/sqrt(3) = 0.57735026918963	
    return out;
}/* end of clacke_calc()*/

/* inverse clacke transformation function*/
uvw iclacke_calc(dq* in)
{
    uvw	out = { 0.0f, };

    out.u = in->d;
    out.v = -0.5f * (in->d - SQRT3 * in->q);
    out.w = -(out.u + out.v);
    return out;
}/* end of iclacke_calc()*/



uvw Positive_Seq(uvw* in, uvw* in_APF)
{
    uvw out = { 0.0f, };

    //Positive sequence
    out.u = (in->u - 0.5f * in->v - 0.5f * in->w) * 0.33333333333f + 0.288675f * (in_APF->v - in_APF->w);
    out.v = (in->v - 0.5f * in->w - 0.5f * in->u) * 0.33333333333f + 0.288675f * (in_APF->w - in_APF->u);
    out.w = (in->w - 0.5f * in->u - 0.5f * in->v) * 0.33333333333f + 0.288675f * (in_APF->u - in_APF->v);

    return out;
}

uvw Negative_Seq(uvw* in, uvw* in_APF)
{
    uvw out = { 0.0f, };

    //Negative sequence
    out.u = (in->u - 0.5f * in->v - 0.5f * in->w) * 0.33333333333f - 0.288675f * (in_APF->v - in_APF->w);
    out.v = (in->v - 0.5f * in->w - 0.5f * in->u) * 0.33333333333f - 0.288675f * (in_APF->w - in_APF->u);
    out.w = (in->w - 0.5f * in->u - 0.5f * in->v) * 0.33333333333f - 0.288675f * (in_APF->u - in_APF->v);

    return out;
}

uvw Zero_Seq(uvw* in, uvw* in_APF)
{
    uvw out = { 0.0f, };

    //Negative sequence
    out.u = (in->u + in->v + in->w) * 0.33333333333f;
    out.v = (-0.5f * in->v - 0.5f * in->w - 0.5f * in->u) * 0.33333333333f - 0.288675f * (in_APF->u + in_APF->v + in_APF->w);
    out.w = (-0.5f * in->w - 0.5f * in->u - 0.5f * in->v) * 0.33333333333f + 0.288675f * (in_APF->u + in_APF->v + in_APF->w);

    return out;
}


/* Space Vector PWM calculation function*/
uvw SVPWM_calc(uvw* in)
{
    //	float  temp,Vdc_eff;
    float  Vmax, Vmin, Vsn;
    float  Van_ref, Vbn_ref, Vcn_ref;
    float  INV_Vdc;
    uvw out = { 0.0f, };

    //	Flag_on_off^=1;
    //	Flag_TF=Flag_on_off;

        // 3- element sort Algorithm (Vmax, Vmin)	
    if ((in->u) > (in->v)) { Vmax = (in->u);	Vmin = (in->v); }
    else { Vmax = (in->v); Vmin = (in->u); }
    if ((in->w) > Vmax)	Vmax = (in->w);
    if ((in->w) < Vmin)	Vmin = (in->w);

    Vsn = -(Vmax + Vmin) * 0.5f;
    Van_ref = (in->u) + Vsn;
    Vbn_ref = (in->v) + Vsn;
    Vcn_ref = (in->w) + Vsn;

    /*
        Vdc_eff=Vdc*(1-2*Tdead*INV_Ts);

        if((Vmax-Vmin)>Vdc_eff){
            temp = Vdc_eff/(Vmax-Vmin);
            Van_ref*=temp;
            Vbn_ref*=temp;
            Vcn_ref*=temp;
        }
    */
    /*
    if (Van_ref > Vdc_LPF * 0.5)	Van_ref = Vdc_LPF * 0.5;
    if (Van_ref < -Vdc_LPF * 0.5) 	Van_ref = -Vdc_LPF * 0.5;
    if (Vbn_ref > Vdc_LPF * 0.5)	Vbn_ref = Vdc_LPF * 0.5;
    if (Vbn_ref < -Vdc_LPF * 0.5) 	Vbn_ref = -Vdc_LPF * 0.5;
    if (Vcn_ref > Vdc_LPF * 0.5)	Vcn_ref = Vdc_LPF * 0.5;
    if (Vcn_ref < -Vdc_LPF * 0.5) 	Vcn_ref = -Vdc_LPF * 0.5;

    INV_Vdc = 1. / Vdc_LPF;
    */
    /*	if(Van_ref>0) Van_ref=Van_ref - 0.015*Vdc_LPF;
        else Van_ref=Van_ref + 0.015*Vdc_LPF;
        if(Vbn_ref>0) Vbn_ref=Vbn_ref - 0.015*Vdc_LPF;
        else Vbn_ref=Vbn_ref + 0.015*Vdc_LPF;
        if(Vcn_ref>0) Vcn_ref=Vcn_ref - 0.015*Vdc_LPF;
        else Vcn_ref=Vcn_ref + 0.015*Vdc_LPF;
    */
    /*
    out.u = Ts * (0.5 + (Van_ref * INV_Vdc));	//Ta
    out.v = Ts * (0.5 + (Vbn_ref * INV_Vdc));	//Tb
    out.w = Ts * (0.5 + (Vcn_ref * INV_Vdc));	//Tc
    */

    return out;

}/* end of SVPWM_calc()*/

/* PI control calculation function*/
void PI_Control_calc(PI_con* in)
{
    // Error Calculation
    in->Err = in->Ref - in->Fdb;
    // Integral Calculation
    in->Integ += in->Ki * in->Tsamp * (in->Err - in->Ka * (in->outtemp - in->out));
    // PI: Alpha=0, IP : Alpha=1
    in->Fb = in->Integ + in->Kp * in->Err * (1 - in->Alpha) - in->Kp * in->Fdb * in->Alpha;
    in->outtemp = in->Fb + in->FF;
    in->out = ((in->outtemp) > (in->OutMax)) ? in->OutMax : ((in->outtemp) < (in->OutMin)) ? in->OutMin : in->outtemp;

}/* end of PI_Control_calc()*/

/* PI+LPF control calculation function*/
void PILPF_Control_calc(PI_con* in)
{
    // Error Calculation
    in->Err = in->Ref - in->Fdb;
    // Integral Calculation
    in->Integ += in->Ki * in->Tsamp * (in->Err - in->Ka * (in->outtemp - in->out));
    // PI: Alpha=0, IP : Alpha=1
    in->Fb = in->Integ + in->Kp * in->Err * (1 - in->Alpha) - in->Kp * in->Fdb * in->Alpha;
    in->outtemp = in->Fb + in->FF;
    in->out = ((in->outtemp) > (in->OutMax)) ? in->OutMax : ((in->outtemp) < (in->OutMin)) ? in->OutMin : in->outtemp;

}/* end of PI_Control_calc()*/


void PID_Control_calc(PID_con* in)
{
    //backward
    // Error Calculation
    in->Err = in->Ref - in->Fdb;
    // Integral Calculation
    in->Integ += in->Ki * in->Tsamp * (in->Err - in->Ka * (in->outtemp - in->out));
    // Differentail Calculation
    in->Diff = in->Kd / in->Tsamp * (in->Err - in->Err1);
    // PI: Alpha=0, IP : Alpha=1
    in->Fb = in->Integ + in->Diff + in->Kp * in->Err * (1 - in->Alpha) - in->Kp * in->Fdb * in->Alpha;
    in->outtemp = in->Fb + in->FF;
    in->out = ((in->outtemp) > (in->OutMax)) ? in->OutMax : ((in->outtemp) < (in->OutMin)) ? in->OutMin : in->outtemp;

    /*  //Bilinear
        // Error Calculation
        in->Err = in->Ref - in->Fdb;
        // PI(bilinear)
        in->outtemp += (in->Kp+in->Ki*in->Tsamp)*in->Err - in->Ki*in->Err1;

        in->out =((in->outtemp) > (in->OutMax))?in->OutMax : ((in->outtemp) < (in->OutMin))?in->OutMin : in->outtemp;
    */
    in->Err1 = in->Err;

}/* end of PID_Control_calc()*/

void PIR_Control_calc(PIR_con* in, float Wres)
{
    // Error Calculation
    in->Err = in->Ref - in->Fdb;
    // Integral Calculation
    in->Integ += in->Ki * in->Tsamp * (in->Err - in->Ka * (in->outtemp - in->out));
    //  Resonant Calculation
//    in->Res = RES((float)(Ts), Wres, 2*Wres, 1, in->Err, &in->ResFilter);
    in->Res = RES(in->Tsamp, Wres, 2.0f * Wres, 1.0f, in->Err, &in->ResFilter);
    // PI: Alpha=0, IP : Alpha=1
    in->Fb = in->Integ + in->Res + in->Kp * in->Err * (1 - in->Alpha) - in->Kp * in->Fdb * in->Alpha;
    in->outtemp = in->Fb + in->FF;
    in->out = ((in->outtemp) > (in->OutMax)) ? in->OutMax : ((in->outtemp) < (in->OutMin)) ? in->OutMin : in->outtemp;
}/* end of PIR_Control_calc()*/

void PICPX2P2Z_Control_calc(PICPX2P2Z_con* in, float Wp, float ZetaPole, float Wz, float ZetaZero)
{
    // Error Calculation
    in->Err = in->Ref - in->Fdb;
    // CPX2P2z Calculation
    in->ErrCPX2P2Z = CPXTPTZF2(in->Tsamp, 1.0f, Wp, ZetaPole, Wz, ZetaZero, in->Err, &in->CPX2P2Z);
    // Integral Calculation
    in->Integ += in->Ki * in->Tsamp * (in->ErrCPX2P2Z - in->Ka * (in->outtemp - in->out));
    // PI: Alpha=0, IP : Alpha=1
    in->Fb = in->Integ + in->Kp * in->ErrCPX2P2Z * (1 - in->Alpha) - in->Kp * in->Fdb * in->Alpha;
    in->outtemp = in->Fb + in->FF;
    in->out = ((in->outtemp) > (in->OutMax)) ? in->OutMax : ((in->outtemp) < (in->OutMin)) ? in->OutMin : in->outtemp;
}/* end of PICPX2P2Z_Control_calc()*/


/* 2P1Z(1integrator+1pole+1zero) control calculation function*/
void TPOZ_Control_calc(TPOZ_con* in)
{
    float U1, U2;
    float Kptemp, K1, K2, K3;

    U1 = 8.0f / (4.0f + 2.0f * in->Wp * in->Tsamp);
    U2 = -(4.0f - 2.0f * in->Wp * in->Tsamp) / (4.0f + 2.0f * in->Wp * in->Tsamp);
    Kptemp = in->Kp * in->Tsamp / (4.0f + 2.0f * in->Wp * in->Tsamp);
    K1 = in->Wz * in->Tsamp + 2.0f;
    K2 = 2.0f * in->Wz * in->Tsamp;
    K3 = in->Wz * in->Tsamp - 2.0f;


    // Error Calculation for Negative Feedback
//  in->Err = in->Ref - in->Fdb - in->Ka*(in->outtemp - in->out);  //Anti-windup
    in->Err = in->Ref - in->Fdb;  //non Anti-windup

    // Error Calculation for Positive Feedback
//  in->Err = in->Fdb - in->Ref - in->Ka*(in->outtemp - in->out);  //Anti-windup
//  in->Err = in->Fdb - in->Ref;  //non Anti-windup

    //Compensation Calculation
    in->outtemp = U1 * in->outtemp1 + U2 * in->outtemp2 + Kptemp * (K1 * in->Err + K2 * in->Err1 + K3 * in->Err2);

    in->out = ((in->outtemp) > (in->OutMax)) ? in->OutMax : ((in->outtemp) < (in->OutMin)) ? in->OutMin : in->outtemp;

    in->Err2 = in->Err1;
    in->Err1 = in->Err;
    in->outtemp2 = in->outtemp1;
    in->outtemp1 = in->outtemp;


}/* end of 2P1Z_Control_calc()*/

/* 2pole+2zero control calculation function*/
void TPTZ_Control_calc(TPTZ_con* in)
{
    float Az, Bz, Cz, Dz, Ap, Bp, Cp, Dp;
    float U1, U2, U3;
    //  float Kptemp,K1,K2,K3,K4;
    float Kptemp, K1, K2, K3;

    Az = 2.0f + in->Wz1 * in->Tsamp;
    Bz = in->Wz1 * in->Tsamp - 2.0f;
    Cz = 2.0f + in->Wz2 * in->Tsamp;
    Dz = in->Wz2 * in->Tsamp - 2.0f;

    Ap = 2.0f + in->Wp1 * in->Tsamp;
    Bp = in->Wp1 * in->Tsamp - 2.0f;
    Cp = 2.0f + in->Wp2 * in->Tsamp;
    Dp = in->Wp2 * in->Tsamp - 2.0f;

    U1 = (-Ap * Dp - Bp * Cp + Ap * Cp) / (Ap * Cp);
    U2 = (-Bp * Dp + Ap * Dp + Bp * Cp) / (Ap * Cp);
    U3 = (Bp * Dp) / (Ap * Cp);
    Kptemp = in->Kp * in->Tsamp * 0.5f * Az * Cz / (Ap * Cp);
    K1 = (Az * Dz + Bz * Cz + Az * Cz) / (Az * Cz);
    K2 = (Bz * Dz + Az * Dz + Bz * Cz) / (Az * Cz);
    K3 = (Bz * Dz) / (Az * Cz);

    // Error Calculation for Negative Feedback
//  in->Err = in->Ref - in->Fdb - in->Ka*(in->outtemp - in->out);  //Anti-windup
    in->Err = in->Ref - in->Fdb;  //non Anti-windup

    //Compensation Calculation
    in->outtemp = U1 * in->outtemp1 + U2 * in->outtemp2 + U3 * in->outtemp3 + Kptemp * (in->Err + K1 * in->Err1 + K2 * in->Err2 + K3 * in->Err3);
    //  in->outtemp = 0.7131*in->outtemp1 + 0.5213*in->outtemp2 - 0.2345*in->outtemp3 + (0.273*in->Err - 0.2628*in->Err1 - 0.2729*in->Err2 + 0.2629*in->Err3);

    in->out = ((in->outtemp) > (in->OutMax)) ? in->OutMax : ((in->outtemp) < (in->OutMin)) ? in->OutMin : in->outtemp;

    in->Err3 = in->Err2;
    in->Err2 = in->Err1;
    in->Err1 = in->Err;
    in->outtemp3 = in->outtemp2;
    in->outtemp2 = in->outtemp1;
    in->outtemp1 = in->outtemp;

}/* end of 2P, 2Z Control_calc()*/




/* 1-order Low Pass Filter function*/
float LPF1(float Tsamp, float fc, float in, filter1* out)
{
    float Wc;
    float LPF1_A, LPF1_B, LPF1_C;
    float filter_in, filter_out;
    float output1;

    Wc = PI2 * fc;

    LPF1_A = 2.0f - Tsamp * Wc;
    LPF1_B = 2.0f + Tsamp * Wc;
    LPF1_C = Tsamp * Wc;

    filter_out = (LPF1_A * out->output_old1) / LPF1_B;
    filter_in = LPF1_C * (in + out->input_old1) / LPF1_B;

    out->output = filter_in + filter_out;
    output1 = out->output;

    out->output_old1 = out->output;
    out->input_old1 = in;

    return output1;

}/* end of LPF1*/

/* 2-order Low Pass Filter function*/
float LPF2(float Tsamp, float fc, float zeta, float in, filter2* out)
{
    float Wc;
    float LPF2_A, LPF2_B, LPF2_C, LPF2_D;
    float filter_in, filter_out;
    float output1;

    Wc = PI2 * fc;

    LPF2_A = 4.0f + 4.0f * zeta * Wc * Tsamp + Wc * Wc * Tsamp * Tsamp;;
    LPF2_B = 8.0f - 2.0f * Wc * Wc * Tsamp * Tsamp ;
    LPF2_C = -4.0f + 4.0f * zeta * Wc * Tsamp - Wc * Wc * Tsamp * Tsamp;
    LPF2_D = Wc * Wc * Tsamp * Tsamp;

    filter_out = (LPF2_B * out->output_old1 + LPF2_C * out->output_old2) / LPF2_A;
    filter_in = LPF2_D * (in + 2.0f * out->input_old1 + out->input_old2) / LPF2_A;

    out->output = filter_in + filter_out;
    output1 = out->output;

    out->output_old2 = out->output_old1;
    out->output_old1 = out->output;

    out->input_old2 = out->input_old1;
    out->input_old1 = in;

    return output1;

}/* end of LPF2()*/


/* 2-order High Pass Filter function*/
float HPF2(float Tsamp, float fc, float zeta, float in, filter2* out)
{
    float Wc;
    float HPF2_A, HPF2_B, HPF2_C, HPF2_D;
    float filter_in, filter_out;
    float output1;

    Wc = PI2 * fc;

    HPF2_A = 4.0f + 4.0f * zeta * Wc * Tsamp + Wc * Wc * Tsamp * Tsamp;
    HPF2_B = 8.0f - 2.0f * Wc * Wc * Tsamp * Tsamp ;
    HPF2_C = -4.0f + 4.0f * zeta * Wc * Tsamp - Wc * Wc * Tsamp * Tsamp;
    HPF2_D = 4.0f;

    filter_out =(HPF2_B * out->output_old1 + HPF2_C * out->output_old2) / HPF2_A;
    filter_in = HPF2_D * (in - 2.0f * out->input_old1 + out->input_old2) / HPF2_A;

    out->output = filter_in + filter_out;
    output1 = out->output;

    out->output_old2 = out->output_old1;
    out->output_old1 = out->output;

    out->input_old2 = out->input_old1;
    out->input_old1 = in;

    return output1;

}/* end of HPF2()*/

/* 2-order Band Pass Filter function*/
float BPF2(float Tsamp, float fc, float Band, float in, filter2* out)  //Band = 2*zeta*wWc
{
    float Wc;
    float BPF2_A, BPF2_B, BPF2_C, BPF2_D;
    float filter_in, filter_out;
    float output1;

    Wc = PI2 * fc;

    BPF2_A = 4.0f + 2.0f * Band * Tsamp + Wc * Wc * Tsamp * Tsamp;
    BPF2_B = 8.0f - 2.0f * Wc * Wc * Tsamp * Tsamp;
    BPF2_C = -4.0f + 2.0f * Band * Tsamp - Wc * Wc * Tsamp * Tsamp;
    BPF2_D = 2.0f * Band * Tsamp;


    filter_out = (BPF2_B * out->output_old1 + BPF2_C * out->output_old2) / BPF2_A;
    filter_in = BPF2_D * (in - out->input_old2) / BPF2_A;

    out->output = filter_in + filter_out;
    output1 = out->output;


    out->output_old2 = out->output_old1;
    out->output_old1 = out->output;

    out->input_old2 = out->input_old1;
    out->input_old1 = in;

    return output1;

}/* end of BPF2()*/

/* 2-order Band Stop Filter function*/
float BSF2(float Tsamp, float fc, float zeta, float in, filter2* out)
{
    float Wc;
    float BSF2_A, BSF2_B, BSF2_C, BSF2_D, BSF2_E;
    float filter_in, filter_out;
    float output1;

    Wc = PI2 * fc;

    
    BSF2_A = 4.0f + 4.0f * zeta * Wc * Tsamp + Wc * Wc * Tsamp * Tsamp;
    BSF2_B = 8.0f - 2.0f * Wc * Wc * Tsamp * Tsamp;
    BSF2_C = -4.0f + 4.0f * zeta * Wc * Tsamp - Wc * Wc * Tsamp * Tsamp;
    BSF2_D = 4.0f + Wc * Wc * Tsamp * Tsamp;
    BSF2_E = -8.0f + 2 * Wc * Wc * Tsamp * Tsamp;

    filter_out = (BSF2_B * out->output_old1 + BSF2_C * out->output_old2) / BSF2_A;
    filter_in = (BSF2_D * in + BSF2_E * out->input_old1 + BSF2_D * out->input_old2) / BSF2_A;

    out->output = filter_in + filter_out;
    output1 = out->output;

    out->output_old2 = out->output_old1;
    out->output_old1 = out->output;

    out->input_old2 = out->input_old1;
    out->input_old1 = in;

    return output1;

}/* end of BSF2*/

/* 2-order Intergrate + High Pass Filter function*/
float SBPF2(float Tsamp, float fc, float zeta, float in, filter2* out)
{
    float Wc;
    float SBPF2_A, SBPF2_B, SBPF2_C, SBPF2_D;
    float filter_in, filter_out;
    float output1;

    Wc = PI2 * fc;

    SBPF2_A = 4.0f + 4.0f * zeta * Wc * Tsamp + Wc * Wc * Tsamp * Tsamp;
    SBPF2_B = 8.0f - 2.0f * Wc * Wc * Tsamp * Tsamp;
    SBPF2_C = -4.0f + 4.0f * zeta * Wc * Tsamp - Wc * Wc * Tsamp * Tsamp;
    SBPF2_D = 2.0f * Tsamp;


    filter_out = (SBPF2_B * out->output_old1 + SBPF2_C * out->output_old2) / SBPF2_A;
    filter_in = SBPF2_D * (in - out->input_old2) / SBPF2_A;

    out->output = filter_in + filter_out;
    output1 = out->output;

    out->output_old2 = out->output_old1;
    out->output_old1 = out->output;

    out->input_old2 = out->input_old1;
    out->input_old1 = in;

    return output1;

}/* end of SBPF2()*/

/* 1-order All Pass Filter function*/
float APF1(float Tsamp, float fc, float in, filter1* out)
{
    float Wc;
    float APF1_A, APF1_B;
    float filter_in, filter_out;

    Wc = PI2 * fc;
    APF1_A = 2 - Wc * Tsamp;
    APF1_B = 2 + Wc * Tsamp;

    filter_in = in;
    filter_out = (out->output_old1 + filter_in) * (APF1_A / (APF1_B)) - out->input_old1;

    out->input_old1 = filter_in;
    out->output_old1 = filter_out;

    return filter_out;
}/* end of APF1()*/

/* 2-order All Pass Filter function*/
float APF2(float Tsamp, float fc, float in, filter2* out)
{
    float Wc;
    float APF2_A, APF2_B, APF2_C;
    float filter_in, filter_out;
    float output1;

    Wc = PI2 * fc;

    APF2_A = 4.0f + 2.0f * Wc * Tsamp + PI * 0.5f * Tsamp * Tsamp;
    APF2_B = 8.0f - PI * Tsamp * Tsamp;
    APF2_C = -4.0f + 2.0f * Wc * Tsamp - PI * 0.5f * Tsamp * Tsamp;

    filter_out = (APF2_B * out->output_old1 + APF2_C * out->output_old2) / APF2_A;
    filter_in = (-1.0f * APF2_C * in - APF2_B * out->input_old1 + APF2_A * out->input_old2) / APF2_A;

    out->output = filter_in + filter_out;
    output1 = out->output;

    out->output_old2 = out->output_old1;
    out->output_old1 = out->output;

    out->input_old2 = out->input_old1;
    out->input_old1 = in;

    return output1;

}/* end of APF2()*/

float RES(float Tsamp, float Ws, float Kr, float h, float in, filter2* out)
{
    float Res_A, Res_B, Res_C;
    float output1;
    float filter_in, filter_out;

    Res_A = Tsamp * Tsamp * h * h * Ws * Ws + 4.0f;
    Res_B = 8.0f - 2.0f * Tsamp * Tsamp * h * h * Ws * Ws;
    Res_C = 2.0f * Kr * Tsamp;

    filter_out = (Res_B * out->output_old1 - Res_A * out->output_old2) / Res_A;
    filter_in = Res_C * (in - out->input_old2) / Res_A;

    out->output = filter_in + filter_out;
    output1 = out->output;

    out->output_old2 = out->output_old1;
    out->output_old1 = out->output;

    out->input_old2 = out->input_old1;
    out->input_old1 = in;

    return output1;

}

/* Complex 2pole+2zero Filter*/
float CPXTPTZF2(float Tsamp, float Kp, float Wp, float ZetaPole, float Wz, float ZetaZero, float in, filter2* out)
{
    float Az, Bz, Cz, Ap, Bp, Cp;
    float filter_in, filter_out;


    Az = 4.0f + 4.0f * ZetaZero * Wz * Tsamp + Wz * Wz * Tsamp * Tsamp;
    Bz = -8.0f + 2.0f * Wz * Wz * Tsamp * Tsamp;
    Cz = 4.0f - 4.0f * ZetaZero * Wz * Tsamp + Wz * Wz * Tsamp * Tsamp;

    Ap = 4.0f + 4.0f * ZetaPole * Wp * Tsamp + Wp * Wp * Tsamp * Tsamp;
    Bp = 8.0f - 2.0f * Wp * Wp * Tsamp * Tsamp;
    Cp = -4.0f + 4.0f * ZetaPole * Wp * Tsamp - Wp * Wp * Tsamp * Tsamp;

    //Filter Input Configuration
    out->input = in;

    //Filter Calculation
    filter_in = Kp * (Az * out->input + Bz * out->input_old1 + Cz * out->input_old2) / Ap;
    filter_out = (Bp * out->output_old1 + Cp * out->output_old2) / Ap;
    out->output = filter_in + filter_out;


    out->output_old2 = out->output_old1;
    out->output_old1 = out->output;

    out->input_old2 = out->input_old1;
    out->input_old1 = out->input;

    return out->output;

}/* end of Complex 2P, 2Z Filter2 */


// interpolation
float Interp1DCalc(float* x, float* y, Uint16 xsize, Uint16 ysize, float input)
{
    float output = 0.0f;
    Uint16 id, idlow, idhigh, Minid, Maxid;

    id = Minid = idlow = 0U;
    Maxid = idhigh = xsize - 1U;

    if (input <= x[Minid])
    {
        output = y[Minid];
    }
    else if (input >= x[Maxid])
    {
        output = y[Maxid];
    }
    else
    {
        while (idlow <= idhigh)
        {
            id = ((idlow + idhigh) >> 1U);
#if 0
            if ((input < x[id]))
            {
                idhigh = id - 1;
            }
            else if ((input >= x[id]) && (input < x[id + 1]))
            {
                output = y[id] + (y[id + 1] - y[id]) / (x[id + 1] - x[id]) * (input - x[id]);
                break;
            }
            else
            {
                idlow = id + 1;
            }
#endif
            if ((input < x[id]))
            {
                idhigh = id - 1U;
            }
            else if (input >= x[id + 1U])
            {
                idlow = id + 1U;
            }
            else
            {
                output = y[id] + (y[id + 1U] - y[id]) / (x[id + 1U] - x[id]) * (input - x[id]);
                break;
            }

        }
    }
    return output;
}

float Interp2DCalc(float* x, float* y, float* value, Uint16 xsize, Uint16 ysize, float xinput, float yinput)
{

    float output = 0.0f;
    float output1 = 0.0f;
    float output2 = 0.0f;

    Uint16 xid, xidLow, xidHigh, xidMin, xidMax;
    Uint16 yid, yidLow, yidHigh, yidMin, yidMax;
    float* loc1, * loc2;

    xid = xidMin = xidLow = 0U;
    xidMax = xidHigh = xsize - 1U;
    yid = yidMin = yidLow = 0U;
    yidMax = yidHigh = ysize - 1U;


    if (xinput <= x[xidMin]) {
        xid = xidMin;
    }
    else if (xinput >= x[xidMax]) {
        xid = xidMax;
    }
    else
    {
        while (xidLow <= xidHigh)
        {
            xid = ((xidLow + xidHigh) >> 1U);
            if (xinput < x[xid]) { xidHigh = xid - 1U; }
            else if (xinput >= x[xid + 1U]) { xidLow = xid + 1U; }
            else { break; }
        }
    }

    if (yinput <= y[yidMin]) {
        yid = yidMin;
    }
    else if (yinput >= y[yidMax]) {
        yid = yidMax;
    }
    else
    {
        while (yidLow <= yidHigh)
        {
            yid = ((yidLow + yidHigh) >> 1U);

            if (yinput < y[yid]) { yidHigh = yid - 1U; }
            else if ((yinput >= y[yid]) && (yinput < y[yid + 1U])) { break; }
            else { yidLow = yid + 1U; }
        }
    }
    loc1 = value + yid * xsize + xid;
    loc2 = loc1 + xsize;

    if ((xinput <= x[0U]) || (xinput >= x[xidMax])) {
        if ((yinput <= y[0U]) || (yinput >= y[yidMax])) {
            output = *(loc1);
        }
        else
        {
            output = *(loc1)+(*(loc2)-*(loc1)) * (yinput - y[yid]) / (y[yid + 1U] - y[yid]);
        }
    }
    else
    {
        float temp = 1.0f / (x[xid + 1U] - x[xid]) * (xinput - x[xid]);
        output1 = *(loc1)+(*(loc1 + 1U) - *(loc1)) * temp;
        if ((yinput <= y[0U]) || (yinput >= y[yidMax])) {
            output = output1;
        }
        else
        {
            output2 = *(loc2)+(*(loc2 + 1U) - *(loc2)) * temp;
            output = output1 + (output2 - output1) * (yinput - y[yid]) / (y[yid + 1U] - y[yid]);
        }
    }
    return output;
}

float Interp3DCalc(float* x, float* y, float* z, float* value, Uint16 xsize, Uint16 ysize, Uint16 zsize, float xinput, float yinput, float zinput)
{
    float output11 = 0.0f;
    float output12 = 0.0f;
    float output1 = 0.0f;
    float output21 = 0.0f;
    float output22 = 0.0f;
    float output2 = 0.0f;
    float output = 0.0f;

    Uint16 xid, xidLow, xidHigh, xidMin, xidMax;
    Uint16 yid, yidLow, yidHigh, yidMin, yidMax;
    Uint16 zid, zidLow, zidHigh, zidMin, zidMax;
    float* loc1, * loc2, * loc3, * loc4;

    xid = xidMin = xidLow = 0U;
    xidMax = xidHigh = xsize - 1U;
    yid = yidMin = yidLow = 0U;
    yidMax = yidHigh = ysize - 1U;
    zid = zidMin = zidLow = 0U;
    zidMax = zidHigh = zsize - 1U;

    if (xinput <= x[xidMin]) {
        xid = xidMin;
    }
    else if (xinput >= x[xidMax]) {
        xid = xidMax;
    }
    else
    {
        while (xidLow <= xidHigh)
        {
            xid = ((xidLow + xidHigh) >> 1U);
            if (xinput < x[xid]) { xidHigh = xid - 1U; }
            else if ((xinput >= x[xid]) && (xinput < x[xid + 1U])) { break; }
            else { xidLow = xid + 1U; }
        }
    }

    if (yinput <= y[yidMin]) {
        yid = yidMin;
    }
    else if (yinput >= y[yidMax]) {
        yid = yidMax;
    }
    else
    {
        while (yidLow <= yidHigh)
        {

            yid = ((yidLow + yidHigh) >> 1U);

            if (yinput < y[yid]) { yidHigh = yid - 1U; }
            else if ((yinput >= y[yid]) && (yinput < y[yid + 1U])) { break; }
            else { yidLow = yid + 1U; }
        }
    }


    if (zinput <= z[zidMin]) {
        zid = zidMin;
    }
    else if (zinput >= z[zidMax]) {
        zid = zidMax;
    }
    else
    {
        while (zidMin <= zidMax)
        {

            zid = ((zidMin + zidMax) >> 1U);

            if (zinput < z[zid]) { zidMax = zid - 1U; }
            else if ((zinput >= z[zid]) && (zinput < z[zid + 1U])) { break; }
            else { zidMin = zid + 1U; }
        }
    }

    loc1 = value + zid * (xsize * ysize) + yid * xsize + xid;
    loc2 = loc1 + xsize;
    loc3 = loc1 + (xsize * ysize);
    loc4 = loc3 + xsize;

    if ((xinput <= x[0U]) || (xinput >= x[xsize - 1U])) {
        if ((yinput <= y[0U]) || (yinput >= y[ysize - 1U])) {
            if ((zinput <= z[0U]) || (zinput >= z[zsize - 1U])) {
                output = *(loc1);
            }
            else
            {
                output = *(loc1)+(*(loc3)-*(loc1)) * (zinput - z[zid]) / (z[zid + 1U] - z[zid]);
            }
        }
        else
        {
            float ytemp = (yinput - y[yid]) / (y[yid + 1U] - y[yid]);
            output1 = *(loc1)+(*(loc2)-*(loc1)) * ytemp;
            if ((zinput <= z[0U]) || (zinput >= z[zsize - 1U])) {
                output = output1;
            }
            else
            {
                output2 = *(loc3)+(*(loc4)-*(loc3)) * ytemp;
                output = output1 + (output2 - output1) / (z[zid + 1U] - z[zid]) * (zinput - z[zid]);
            }
        }
    }
    else
    {
        float xtemp = (xinput - x[xid]) / (x[xid + 1U] - x[xid]);
        output11 = *(loc1)+(*(loc1 + 1U) - *(loc1)) * xtemp;
        output21 = *(loc3)+(*(loc3 + 1U) - *(loc3)) * xtemp;
        if ((yinput <= y[0U]) || (yinput >= y[ysize - 1U])) {
            if ((zinput <= z[0U]) || (zinput >= z[zsize - 1U])) {
                output = output11;
            }
            else
            {
                output = output11 + (output21 - output11) / (z[zid + 1U] - z[zid]) * (zinput - z[zid]);
            }
        }
        else
        {
            float ytemp = (yinput - y[yid]) / (y[yid + 1U] - y[yid]);
            output12 = *(loc2)+(*(loc2 + 1U) - *(loc2)) * xtemp;
            output22 = *(loc4)+(*(loc4 + 1U) - *(loc4)) * xtemp;
            output1 = output11 + (output12 - output11) * ytemp;
            output2 = output21 + (output22 - output21) * ytemp;
            if ((zinput <= z[0U]) || (zinput >= z[zsize - 1U])) {
                output = output1;
            }
            else
            {
                output = output1 + (output2 - output1) / (z[zid + 1U] - z[zid]) * (zinput - z[zid]);
            }

        }
    }
    return output;
}
