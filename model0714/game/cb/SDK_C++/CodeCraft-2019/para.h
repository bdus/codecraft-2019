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
    const float para1 = 0.15;   //时间阻抗系数
    const int para2 = 4;            //时间阻抗指数
    const float para3 = 0.5;   //道路的容量限制阈值
    const float para4 = 1.5;   //道路的容量限制阈值 para4

    float t0 = (float)length/min(V_car,V_r);

    int vol = length*channel;
    float rati = (float)N_car/ (float)vol;// + 0.01; 考虑浮点数

    //计算时间阻抗
    float R = 1 + para1 * pow(rati/para3,para2); // +
    float t  = R*t0;

    //计算道路可达性

    //道路可达性(如果判断不可达,断路)
    if(rati >= para3) //超过一定容量 断路
        return MYINF;
    else if(R > para4)//阻抗大于一定值 断路
        return MYINF;
    else  //返回时间阻抗
        return t;
//
//    int vol = length*channel *a ;
//    if(N_car>=vol)
//        return MYINF;
//    else
//    {
//        float rati = (float)N_car/ (float)vol;
//        float ans = length / min(V_car,V_r) ;
//        if(ans < 0)
//            return MYINF;
//        else if(ans > MYINF)
//            return MYINF;
//            if( rati < 0.2 )
//                return ans;
//            else if( rati < 0.5)
//                return ans*2;
//            else
//                return ans * fast_exp(5*rati);
//
//    }
}
