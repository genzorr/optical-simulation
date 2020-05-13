////////////////////////////////////////////////////////////////////////////////
// File: fresnel_auxiliary_sine_integral.c                                    //
// Routine(s):                                                                //
//    Fresnel_Auxiliary_Sine_Integral                                         //
//    xFresnel_Auxiliary_Sine_Integral                                        //
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <math.h>           // required for fabsl()                      
#include <float.h>          // required for LDBL_EPSILON

//                         Externally Defined Routines                        //
long double SxChebyshev_Tn_Series(long double x, const long double a[], int degree)
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
double      Fresnel_Auxiliary_Sine_Integral(double x);
long double xFresnel_Auxiliary_Sine_Integral(long double x);

static long double SChebyshev_Expansion_0_1(long double x);
static long double SChebyshev_Expansion_1_3(long double x);
static long double SChebyshev_Expansion_3_5(long double x);
static long double SChebyshev_Expansion_5_7(long double x);
static long double SAsymptotic_Series(long double x);

//                         Internally Defined Constants                       //
static long double const Ssqrt_2pi = 2.506628274631000502415765284811045253006L;


////////////////////////////////////////////////////////////////////////////////
// double Fresnel_Auxiliary_Sine_Integral( double x )                         //
//                                                                            //
//  Description:                                                              //
//     The Fresnel auxiliary sine integral, g(x), is the integral from 0 to   //
//     infinity of the integrand                                              //
//                     sqrt(2/pi) exp(-2xt) sin(t^2) dt                       //
//     where x >= 0.                                                          //
//                                                                            //
//  Arguments:                                                                //
//     double  x  The argument of the Fresnel auxiliary sine integral g()     //
//                where x >= 0.                                               //
//                                                                            //
//  Return Value:                                                             //
//     The value of the Fresnel auxiliary sine integral g evaluated at        //
//     x >= 0.                                                                //
//                                                                            //
//  Example:                                                                  //
//     double y, x;                                                           //
//                                                                            //
//     ( code to initialize x )                                               //
//                                                                            //
//     y = Fresnel_Auxiliary_Sine_Integral( x );                              //
////////////////////////////////////////////////////////////////////////////////
double Fresnel_Auxiliary_Sine_Integral(double x)
{
    return (double)xFresnel_Auxiliary_Sine_Integral((long double)x);
}


////////////////////////////////////////////////////////////////////////////////
// long double xFresnel_Auxiliary_Sine_Integral( double x )                   //
//                                                                            //
//  Description:                                                              //
//     The Fresnel auxiliary sine integral, g(x), is the integral from 0 to   //
//     infinity of the integrand                                              //
//                     sqrt(2/pi) exp(-2xt) sin(t^2) dt                       //
//     where x >= 0.                                                          //
//                                                                            //
//  Arguments:                                                                //
//     long double  x  The argument of the Fresnel auxiliary sine integral    //
//                     g() where x >= 0.                                      //
//                                                                            //
//  Return Value:                                                             //
//     The value of the Fresnel auxiliary sine integral g evaluated at        //
//     x >= 0.                                                                //
//                                                                            //
//  Example:                                                                  //
//     double y, x;                                                           //
//                                                                            //
//     ( code to initialize x )                                               //
//                                                                            //
//     y = xFresnel_Auxiliary_Sine_Integral( x );                             //
////////////////////////////////////////////////////////////////////////////////
long double xFresnel_Auxiliary_Sine_Integral(long double x)
{
    if (x == 0.0L) return 0.5L;
    if (x <= 1.0L) return SChebyshev_Expansion_0_1(x);
    if (x <= 3.0L) return SChebyshev_Expansion_1_3(x);
    if (x <= 5.0L) return SChebyshev_Expansion_3_5(x);
    if (x <= 7.0L) return SChebyshev_Expansion_5_7(x);
    return SAsymptotic_Series(x);
}


////////////////////////////////////////////////////////////////////////////////
// static long double Chebyshev_Expansion_0_1( long double x )                //
//                                                                            //
//  Description:                                                              //
//     Evaluate the Fresnel auxiliary sine integral, g(x), on the interval    //
//     0 < x <= 1 using the Chebyshev interpolation formula.                  //
//                                                                            //
//  Arguments:                                                                //
//     long double  x  The argument of the Fresnel auxiliary sine integral    //
//                     where 0 < x <= 1.                                      //
//                                                                            //
//  Return Value:                                                             //
//     The value of the Fresnel auxiliary sine integral g evaluated at        //
//     x where 0 < x <= 1.                                                    //
//                                                                            //
//  Example:                                                                  //
//     long double y, x;                                                      //
//                                                                            //
//     ( code to initialize x )                                               //
//                                                                            //
//     y = Chebyshev_Expansion_0_1(x);                                        //
////////////////////////////////////////////////////////////////////////////////

static long double SChebyshev_Expansion_0_1(long double x)
{
    static long double const c[] = {
       +2.560134650043040830997e-1L,  -1.993005146464943284549e-1L,
       +4.025503636721387266117e-2L,  -4.459600454502960250729e-3L,
       +6.447097305145147224459e-5L,  +7.544218493763717599380e-5L,
       -1.580422720690700333493e-5L,  +1.755845848573471891519e-6L,
       -9.289769688468301734718e-8L,  -5.624033192624251079833e-9L,
       +1.854740406702369495830e-9L,  -2.174644768724492443378e-10L,
       +1.392899828133395918767e-11L, -6.989216003725983789869e-14L,
       -9.959396121060010838331e-14L, +1.312085140393647257714e-14L,
       -9.240470383522792593305e-16L, +2.472168944148817385152e-17L,
       +2.834615576069400293894e-18L, -4.650983461314449088349e-19L,
       +3.544083040732391556797e-20L
    };

    static const int degree = sizeof(c) / sizeof(long double) - 1;
    static const long double midpoint = 0.5L;
    static const long double scale = 0.5L;

    return SxChebyshev_Tn_Series((x - midpoint) / scale, c, degree);
}


////////////////////////////////////////////////////////////////////////////////
// static long double Chebyshev_Expansion_1_3( long double x )                //
//                                                                            //
//  Description:                                                              //
//     Evaluate the Fresnel auxiliary sine integral, g(x), on the interval    //
//     1 < x <= 3 using the Chebyshev interpolation formula.                  //
//                                                                            //
//  Arguments:                                                                //
//     long double  x  The argument of the Fresnel auxiliary sine integral    //
//                     where 1 < x <= 3.                                      //
//                                                                            //
//  Return Value:                                                             //
//     The value of the Fresnel auxiliary sine integral g evaluated at        //
//     x where 1 < x <= 3.                                                    //
//                                                                            //
//  Example:                                                                  //
//     long double y, x;                                                      //
//                                                                            //
//     ( code to initialize x )                                               //
//                                                                            //
//     y = Chebyshev_Expansion_1_3(x);                                        //
////////////////////////////////////////////////////////////////////////////////

static long double SChebyshev_Expansion_1_3(long double x)
{
    static long double const c[] = {
       +3.470341566046115476477e-2L,  -3.855580521778624043304e-2L,
       +1.420604309383996764083e-2L,  -4.037349972538938202143e-3L,
       +9.292478174580997778194e-4L,  -1.742730601244797978044e-4L,
       +2.563352976720387343201e-5L,  -2.498437524746606551732e-6L,
       -1.334367201897140224779e-8L,  +7.436854728157752667212e-8L,
       -2.059620371321272169176e-8L,  +3.753674773239250330547e-9L,
       -5.052913010605479996432e-10L, +4.580877371233042345794e-11L,
       -7.664740716178066564952e-13L, -7.200170736686941995387e-13L,
       +1.812701686438975518372e-13L, -2.799876487275995466163e-14L,
       +3.048940815174731772007e-15L, -1.936754063718089166725e-16L,
       -7.653673328908379651914e-18L, +4.534308864750374603371e-18L,
       -8.011054486030591219007e-19L, +9.374587915222218230337e-20L,
       -7.144943099280650363024e-21L, +1.105276695821552769144e-22L,
       +6.989334213887669628647e-23L
    };

    static const int degree = sizeof(c) / sizeof(long double) - 1;
    static const long double midpoint = 2.0L;

    return SxChebyshev_Tn_Series((x - midpoint), c, degree);
}


////////////////////////////////////////////////////////////////////////////////
// static long double Chebyshev_Expansion_3_5( long double x )                //
//                                                                            //
//  Description:                                                              //
//     Evaluate the Fresnel auxiliary sine integral, g(x), on the interval    //
//     3 < x <= 5 using the Chebyshev interpolation formula.                  //
//                                                                            //
//  Arguments:                                                                //
//     long double  x  The argument of the Fresnel auxiliary sine integral    //
//                     where 3 < x <= 5.                                      //
//                                                                            //
//  Return Value:                                                             //
//     The value of the Fresnel auxiliary sine integral g evaluated at        //
//     x where 3 < x <= 5.                                                    //
//                                                                            //
//  Example:                                                                  //
//     long double y, x;                                                      //
//                                                                            //
//     ( code to initialize x )                                               //
//                                                                            //
//     y = Chebyshev_Expansion_3_5(x);                                        //
////////////////////////////////////////////////////////////////////////////////

static long double SChebyshev_Expansion_3_5(long double x)
{
    static long double const c[] = {
       +3.684922395955255848372e-3L,  -2.624595437764014386717e-3L,
       +6.329162500611499391493e-4L,  -1.258275676151483358569e-4L,
       +2.207375763252044217165e-5L,  -3.521929664607266176132e-6L,
       +5.186211398012883705616e-7L,  -7.095056569102400546407e-8L,
       +9.030550018646936241849e-9L,  -1.066057806832232908641e-9L,
       +1.157128073917012957550e-10L, -1.133877461819345992066e-11L,
       +9.633572308791154852278e-13L, -6.336675771012312827721e-14L,
       +1.634407356931822107368e-15L, +3.944542177576016972249e-16L,
       -9.577486627424256130607e-17L, +1.428772744117447206807e-17L,
       -1.715342656474756703926e-18L, +1.753564314320837957805e-19L,
       -1.526125102356904908532e-20L, +1.070275366865736879194e-21L,
       -4.783978662888842165071e-23L
    };

    static const int degree = sizeof(c) / sizeof(long double) - 1;
    static const long double midpoint = 4.0L;

    return SxChebyshev_Tn_Series((x - midpoint), c, degree);
}


////////////////////////////////////////////////////////////////////////////////
// static long double Chebyshev_Expansion_5_7( long double x )                //
//                                                                            //
//  Description:                                                              //
//     Evaluate the Fresnel auxiliary sine integral, g(x), on the interval    //
//     5 < x <= 7 using the Chebyshev interpolation formula.                  //
//                                                                            //
//  Arguments:                                                                //
//     long double  x  The argument of the Fresnel auxiliary sine integral    //
//                     where 5 < x <= 7.                                      //
//                                                                            //
//  Return Value:                                                             //
//     The value of the Fresnel auxiliary sine integral g evaluated at        //
//     x where 5 < x <= 7.                                                    //
//                                                                            //
//  Example:                                                                  //
//     long double y, x;                                                      //
//                                                                            //
//     ( code to initialize x )                                               //
//                                                                            //
//     y = Chebyshev_Expansion_5_7(x);                                        //
////////////////////////////////////////////////////////////////////////////////

static long double SChebyshev_Expansion_5_7(long double x)
{
    static long double const c[] = {
       +1.000801217561417083840e-3L,  -4.915205279689293180607e-4L,
       +8.133163567827942356534e-5L,  -1.120758739236976144656e-5L,
       +1.384441872281356422699e-6L,  -1.586485067224130537823e-7L,
       +1.717840749804993618997e-8L,  -1.776373217323590289701e-9L,
       +1.765399783094380160549e-10L, -1.692470022450343343158e-11L,
       +1.568238301528778401489e-12L, -1.405356860742769958771e-13L,
       +1.217377701691787512346e-14L, -1.017697418261094517680e-15L,
       +8.186068056719295045596e-17L, -6.305153620995673221364e-18L,
       +4.614110100197028845266e-19L, -3.165914620159266813849e-20L,
       +1.986716456911232767045e-21L, -1.078418278174434671506e-22L,
       +4.255983404468350776788e-24L
    };

    static const int degree = sizeof(c) / sizeof(long double) - 1;
    static const long double midpoint = 6.0L;

    return SxChebyshev_Tn_Series((x - midpoint), c, degree);

}


////////////////////////////////////////////////////////////////////////////////
// static long double Asymptotic_Series( long double x )                      //
//                                                                            //
//  Description:                                                              //
//     For a large argument x, the auxiliary Fresnel sine integral, g(x),     //
//     can be expressed as the asymptotic series                              //
//      g(x) ~ 1/(x^3 * sqrt(8pi))[1 - 15/4x^4 + 945/16x^8 + ... +            //
//                                                (4j+1)!!/(-4x^4)^j + ... ]  //
//                                                                            //
//  Arguments:                                                                //
//     long double  x  The argument of the Fresnel auxiliary sine integral    //
//                     where x > 7.                                           //
//                                                                            //
//  Return Value:                                                             //
//     The value of the Fresnel auxiliary sine integral g evaluated at        //
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
static long double SAsymptotic_Series(long double x)
{
    long double x2 = x * x;
    long double x4 = -4.0L * x2 * x2;
    long double xn = 1.0L;
    long double factorial = 1.0L;
    long double g = 0.0L;
    long double term[NUM_ASYMPTOTIC_TERMS + 1];
    long double epsilon = LDBL_EPSILON / 4.0L;
    int j = 5;
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
    for (; i >= 0; i--) g += term[i];

    g /= (x * Ssqrt_2pi);
    return g / (x2 + x2);
}