////////////////////////////////////////////////////////////////////////////////
// File: fresnel_auxiliary_cosine_integral.c                                  //
// Routine(s):                                                                //
//    Fresnel_Auxiliary_Cosine_Integral                                       //
//    xFresnel_Auxiliary_Cosine_Integral                                      //
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <math.h>           // required for fabsl()
#include <float.h>          // required for LDBL_EPSILON

//                         Externally Defined Routines                        //
long double CxChebyshev_Tn_Series(long double x, const long double a[], int degree)
{
    long double yp2 = 0.0L;
    long double yp1 = 0.0L;
    long double y = 0.0L;
    long double two_x = x + x;
    int k;

    // Check that degree >= 0.  If not, then return 0. //

    if (degree < 0) return 0.0L;

    // Apply Clenshaw's recursion save the last iteration. //

    for (k = degree; k >= 1; k--, yp2 = yp1, yp1 = y)
        y = two_x * yp1 - yp2 + a[k];

    // Now apply the last iteration and return the result. //

    return x * yp1 - yp2 + a[0];
}


//                         Internally Defined Routines                        //
double      Fresnel_Auxiliary_Cosine_Integral(double x);
long double xFresnel_Auxiliary_Cosine_Integral(long double x);

static long double CChebyshev_Expansion_0_1(long double x);
static long double CChebyshev_Expansion_1_3(long double x);
static long double CChebyshev_Expansion_3_5(long double x);
static long double CChebyshev_Expansion_5_7(long double x);
static long double CAsymptotic_Series(long double x);

//                         Internally Defined Constants                       //
static long double const Csqrt_2pi = 2.506628274631000502415765284811045253006L;


////////////////////////////////////////////////////////////////////////////////
// double Fresnel_Auxiliary_Cosine_Integral( double x )                       //
//                                                                            //
//  Description:                                                              //
//     The Fresnel auxiliary cosine integral, f(x), is the integral from 0 to //
//     infinity of the integrand                                              //
//                     sqrt(2/pi) exp(-2xt) cos(t^2) dt                       //
//     where x >= 0.                                                          //
//                                                                            //
//  Arguments:                                                                //
//     double  x  The argument of the Fresnel auxiliary cosine integral f()   //
//                where x >= 0.                                               //
//                                                                            //
//  Return Value:                                                             //
//     The value of the Fresnel auxiliary cosine integral f evaluated at      //
//     x >= 0.                                                                //
//                                                                            //
//  Example:                                                                  //
//     double y, x;                                                           //
//                                                                            //
//     ( code to initialize x )                                               //
//                                                                            //
//     y = Fresnel_Auxiliary_Cosine_Integral( x );                            //
////////////////////////////////////////////////////////////////////////////////
double Fresnel_Auxiliary_Cosine_Integral(double x)
{
    return (double)xFresnel_Auxiliary_Cosine_Integral((long double)x);
}


////////////////////////////////////////////////////////////////////////////////
// long double xFresnel_Auxiliary_Cosine_Integral( double x )                 //
//                                                                            //
//  Description:                                                              //
//     The Fresnel auxiliary cosine integral, f(x), is the integral from 0 to //
//     infinity of the integrand                                              //
//                     sqrt(2/pi) exp(-2xt) cos(t^2) dt                       //
//     where x >= 0.                                                          //
//                                                                            //
//  Arguments:                                                                //
//     long double  x  The argument of the Fresnel auxiliary cosine integral  //
//                     f() where x >= 0.                                      //
//                                                                            //
//  Return Value:                                                             //
//     The value of the Fresnel auxiliary cosine integral f evaluated at      //
//     x >= 0.                                                                //
//                                                                            //
//  Example:                                                                  //
//     double y, x;                                                           //
//                                                                            //
//     ( code to initialize x )                                               //
//                                                                            //
//     y = xFresnel_Auxiliary_Cosine_Integral( x );                           //
////////////////////////////////////////////////////////////////////////////////
long double xFresnel_Auxiliary_Cosine_Integral(long double x)
{
    if (x == 0.0L) return 0.5L;
    if (x <= 1.0L) return CChebyshev_Expansion_0_1(x);
    if (x <= 3.0L) return CChebyshev_Expansion_1_3(x);
    if (x <= 5.0L) return CChebyshev_Expansion_3_5(x);
    if (x <= 7.0L) return CChebyshev_Expansion_5_7(x);
    return CAsymptotic_Series(x);
}


////////////////////////////////////////////////////////////////////////////////
// static long double Chebyshev_Expansion_0_1( long double x )                //
//                                                                            //
//  Description:                                                              //
//     Evaluate the Fresnel auxiliary cosine integral, f(x), on the interval  //
//     0 < x <= 1 using the Chebyshev interpolation formula.                  //
//                                                                            //
//  Arguments:                                                                //
//     long double  x  The argument of the Fresnel auxiliary cosine integral  //
//                     where 0 < x <= 1.                                      //
//                                                                            //
//  Return Value:                                                             //
//     The value of the Fresnel auxiliary cosine integral f evaluated at      //
//     x where 0 < x <= 1.                                                    //
//                                                                            //
//  Example:                                                                  //
//     long double y, x;                                                      //
//                                                                            //
//     ( code to initialize x )                                               //
//                                                                            //
//     y = Chebyshev_Expansion_0_1(x);                                        //
////////////////////////////////////////////////////////////////////////////////

static long double CChebyshev_Expansion_0_1(long double x)
{
    static long double const c[] = {
       +4.200987560240514577713e-1L,  -9.358785913634965235904e-2L,
       -7.642539415723373644927e-3L,  +4.958117751796130135544e-3L,
       -9.750236036106120253456e-4L,  +1.075201474958704192865e-4L,
       -4.415344769301324238886e-6L,  -7.861633919783064216022e-7L,
       +1.919240966215861471754e-7L,  -2.175775608982741065385e-8L,
       +1.296559541430849437217e-9L,  +2.207205095025162212169e-11L,
       -1.479219615873704298874e-11L, +1.821350127295808288614e-12L,
       -1.228919312990171362342e-13L, +2.227139250593818235212e-15L,
       +5.734729405928016301596e-16L, -8.284965573075354177016e-17L,
       +6.067422701530157308321e-18L, -1.994908519477689596319e-19L,
       -1.173365630675305693390e-20L
    };

    static const int degree = sizeof(c) / sizeof(long double) - 1;
    static const long double midpoint = 0.5L;
    static const long double scale = 0.5L;

    return CxChebyshev_Tn_Series((x - midpoint) / scale, c, degree);
}


////////////////////////////////////////////////////////////////////////////////
// static long double Chebyshev_Expansion_1_3( long double x )                //
//                                                                            //
//  Description:                                                              //
//     Evaluate the Fresnel auxiliary cosine integral, f(x), on the interval  //
//     1 < x <= 3 using the Chebyshev interpolation formula.                  //
//                                                                            //
//  Arguments:                                                                //
//     long double  x  The argument of the Fresnel auxiliary cosine integral  //
//                     where 1 < x <= 3.                                      //
//                                                                            //
//  Return Value:                                                             //
//     The value of the Fresnel auxiliary cosine integral f evaluated at      //
//     x where 1 < x <= 3.                                                    //
//                                                                            //
//  Example:                                                                  //
//     long double y, x;                                                      //
//                                                                            //
//     ( code to initialize x )                                               //
//                                                                            //
//     y = Chebyshev_Expansion_1_3(x);                                        //
////////////////////////////////////////////////////////////////////////////////

static long double CChebyshev_Expansion_1_3(long double x)
{
    static long double const c[] = {
       +2.098677278318224971989e-1L,  -9.314234883154103266195e-2L,
       +1.739905936938124979297e-2L,  -2.454274824644285136137e-3L,
       +1.589872606981337312438e-4L,  +4.203943842506079780413e-5L,
       -2.018022256093216535093e-5L,  +5.125709636776428285284e-6L,
       -9.601813551752718650057e-7L,  +1.373989484857155846826e-7L,
       -1.348105546577211255591e-8L,  +2.745868700337953872632e-10L,
       +2.401655517097260106976e-10L, -6.678059547527685587692e-11L,
       +1.140562171732840809159e-11L, -1.401526517205212219089e-12L,
       +1.105498827380224475667e-13L, +2.040731455126809208066e-16L,
       -1.946040679213045143184e-15L, +4.151821375667161733612e-16L,
       -5.642257647205149369594e-17L, +5.266176626521504829010e-18L,
       -2.299025577897146333791e-19L, -2.952226367506641078731e-20L,
       +8.760405943193778149078e-21L
    };

    static const int degree = sizeof(c) / sizeof(long double) - 1;
    static const long double midpoint = 2.0L;

    return CxChebyshev_Tn_Series((x - midpoint), c, degree);

}


////////////////////////////////////////////////////////////////////////////////
// static long double Chebyshev_Expansion_3_5( long double x )                //
//                                                                            //
//  Description:                                                              //
//     Evaluate the Fresnel auxiliary cosine integral, g(x), on the interval  //
//     3 < x <= 5 using the Chebyshev interpolation formula.                  //
//                                                                            //
//  Arguments:                                                                //
//     long double  x  The argument of the Fresnel auxiliary cosine integral  //
//                     where 3 < x <= 5.                                      //
//                                                                            //
//  Return Value:                                                             //
//     The value of the Fresnel auxiliary cosine integral f evaluated at      //
//     x where 3 < x <= 5.                                                    //
//                                                                            //
//  Example:                                                                  //
//     long double y, x;                                                      //
//                                                                            //
//     ( code to initialize x )                                               //
//                                                                            //
//     y = Chebyshev_Expansion_3_5(x);                                        //
////////////////////////////////////////////////////////////////////////////////

static long double CChebyshev_Expansion_3_5(long double x)
{
    static long double const c[] = {
       +1.025703371090289562388e-1L,  -2.569833023232301400495e-2L,
       +3.160592981728234288078e-3L,  -3.776110718882714758799e-4L,
       +4.325593433537248833341e-5L,  -4.668447489229591855730e-6L,
       +4.619254757356785108280e-7L,  -3.970436510433553795244e-8L,
       +2.535664754977344448598e-9L,  -2.108170964644819803367e-11L,
       -2.959172018518707683013e-11L, +6.727219944906606516055e-12L,
       -1.062829587519902899001e-12L, +1.402071724705287701110e-13L,
       -1.619154679722651005075e-14L, +1.651319588396970446858e-15L,
       -1.461704569438083772889e-16L, +1.053521559559583268504e-17L,
       -4.760946403462515858756e-19L, -1.803784084922403924313e-20L,
       +7.873130866418738207547e-21L
    };

    static const int degree = sizeof(c) / sizeof(long double) - 1;
    static const long double midpoint = 4.0L;

    return CxChebyshev_Tn_Series((x - midpoint), c, degree);
}


////////////////////////////////////////////////////////////////////////////////
// static long double Chebyshev_Expansion_5_7( long double x )                //
//                                                                            //
//  Description:                                                              //
//     Evaluate the Fresnel auxiliary cosine integral, g(x), on the interval  //
//     5 < x <= 7 using the Chebyshev interpolation formula.                  //
//                                                                            //
//  Arguments:                                                                //
//     long double  x  The argument of the Fresnel auxiliary cosine integral  //
//                     where 5 < x <= 7.                                      //
//                                                                            //
//  Return Value:                                                             //
//     The value of the Fresnel auxiliary cosine integral f evaluated at      //
//     x where 5 < x <= 7.                                                    //
//                                                                            //
//  Example:                                                                  //
//     long double y, x;                                                      //
//                                                                            //
//     ( code to initialize x )                                               //
//                                                                            //
//     y = Chebyshev_Expansion_5_7(x);                                        //
////////////////////////////////////////////////////////////////////////////////

static long double CChebyshev_Expansion_5_7(long double x)
{
    static long double const c[] = {
       +6.738667333400589274018e-2L,  -1.128146832637904868638e-2L,
       +9.408843234170404670278e-4L,  -7.800074103496165011747e-5L,
       +6.409101169623350885527e-6L,  -5.201350558247239981834e-7L,
       +4.151668914650221476906e-8L,  -3.242202015335530552721e-9L,
       +2.460339340900396789789e-10L, -1.796823324763304661865e-11L,
       +1.244108496436438952425e-12L, -7.950417122987063540635e-14L,
       +4.419142625999150971878e-15L, -1.759082736751040110146e-16L,
       -1.307443936270786700760e-18L, +1.362484141039320395814e-18L,
       -2.055236564763877250559e-19L, +2.329142055084791308691e-20L,
       -2.282438671525884861970e-21L
    };

    static const int degree = sizeof(c) / sizeof(long double) - 1;
    static const long double midpoint = 6.0L;

    return CxChebyshev_Tn_Series((x - midpoint), c, degree);

}


////////////////////////////////////////////////////////////////////////////////
// static long double Asymptotic_Series( long double x )                      //
//                                                                            //
//  Description:                                                              //
//     For a large argument x, the auxiliary Fresnel cosine integral, f(x),   //
//     can be expressed as the asymptotic series                              //
//      f(x) ~ 1/(x*sqrt(2pi))[1 - 3/4x^4 + 105/16x^8 + ... +                 //
//                                                (4j-1)!!/(-4x^4)^j + ... ]  //
//                                                                            //
//  Arguments:                                                                //
//     long double  x  The argument of the Fresnel auxiliary cosine integral  //
//                     where x > 7.                                           //
//                                                                            //
//  Return Value:                                                             //
//     The value of the Fresnel auxiliary cosine integral f evaluated at      //
//     x where x > 7.                                                         //
//                                                                            //
//  Example:                                                                  //
//     long double y, x;                                                      //
//                                                                            //
//     ( code to initialize x )                                               //
//                                                                            //
//     y = Asymptotic_Series( x );                                            //
////////////////////////////////////////////////////////////////////////////////
#define NUM_ASYMPTOTIC_TERMS 35
static long double CAsymptotic_Series(long double x)
{
    long double x2 = x * x;
    long double x4 = -4.0L * x2 * x2;
    long double xn = 1.0L;
    long double factorial = 1.0L;
    long double f = 0.0L;
    long double term[NUM_ASYMPTOTIC_TERMS + 1];
    long double epsilon = LDBL_EPSILON / 4.0L;
    int j = 3;
    int i = 0;

    term[0] = 1.0L;
    term[NUM_ASYMPTOTIC_TERMS] = 0.0L;
    for (i = 1; i < NUM_ASYMPTOTIC_TERMS; i++) {
        factorial *= ((long double)j * (long double)(j - 2));
        xn *= x4;
        term[i] = factorial / xn;
        j += 4;
        if (fabsl(term[i]) >= fabsl(term[i - 1])) {
            i--;
            break;
        }
        if (fabsl(term[i]) <= epsilon) break;
    }

    for (; i >= 0; i--) f += term[i];

    return f / (x * Csqrt_2pi);
}