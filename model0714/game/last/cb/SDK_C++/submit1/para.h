#pragma once
#include <math.h>

#ifndef MYINF
//#define MYINF
const int MYINF = 1000000.0; //100w
#endif // MYINF

#undef min
#undef max
template <typename T>
inline T min( T const & a, T const & b ) { return a < b ? a : b; }
inline int max( int a, int b ) { return a > b ? a : b; }
//inline float min( float a, float b ) { return a < b ? a : b; }
inline double fast_exp(double x)
{
    x = 1.0 + x/256;
    x *= x;x *= x;x *= x;x *= x;
    x *= x;x *= x;x *= x;x *= x;
    return x;
}
inline float evalT(int const & length, int const & channel, int const & V_car, int const & V_r, int const & N_car)
{
    const float a = 0.5;
    int vol = length*channel *a ;
    if(N_car>=vol)
        return MYINF;
    else
    {
        int ans = length / min(V_car,V_r) *  fast_exp( 3.1415 /2.0 * (float)N_car/ (float)vol );
        if(ans < 0)
            return MYINF;
        else if(ans > MYINF)
            return MYINF;
        //else if(ans > length / min(V_car,V_r) *1.5  )
           // return MYINF;
        else
            return ans;

    }
}
