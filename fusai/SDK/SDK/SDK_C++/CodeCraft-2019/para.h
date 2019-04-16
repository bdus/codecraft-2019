#pragma once
#include <cassert>
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
    const float para0 = 0.3;
    const float para1 = 0.15;   //时间阻抗系数
    const float para2 = 0.15;   //时间阻抗系数
    const float para3 = 0.15;   //时间阻抗系数

    const float para4 = 0.01;   //主干道罚项

    const float th1 = 0.2;   //时间阻抗系数
    const float th2 = 0.5;   //时间阻抗系数
    const float th3 = 0.8;   //时间阻抗系数

inline float evalT(int const & length, int const & channel, int const & V_car, int const & V_r, int const & N_car, int const & N_car_t)
{

    float base = min(V_car,V_r);
    float vol = length*channel*para0;

    //int vol = length*channel;
    float rati = (float)N_car/ (float)vol + 0.05; //考虑浮点数
    float t0 = (float)length/base;

    //计算时间阻抗

    float t  = 0;
    if(0.0 < rati && rati< 0.9 && t0 > 0.0 )
    {
        float R = 1;
        if( rati < th1 )
        {
            R= 1;
        }
        else if( rati < th2)
        {
            float R1 = para1 * pow(rati /th1,4);
            R = 1+ R1;
        }
        else if(rati < th3 )
        {
            float R1 = para1 * pow(rati /th1,4);
            float R2 = para2 * pow(rati /th2 ,4);
            R = 1+ R1 + R2 ;
        }
        else
        {
            float R1 = para1 * pow(rati /th1,4);
            float R2 = para2 * pow(rati /th2 ,4);
            float R3 = para3 * pow(rati /th3,4);
            R = 1 + R1 + R2 + R3 ;
        }
        //std::cout << R << std::endl;
        if(R > 8)
            return MYINF;
    	t = t0*(R);
        return t;
    }
    else
        return MYINF;
    //计算道路可达性
}
