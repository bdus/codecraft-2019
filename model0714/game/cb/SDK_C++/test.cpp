#include<iostream>
#include<math.h>
#include<limits.h>
using namespace std;
inline double fast_exp(double x)
{
    x = 1.0 + x/256;
    x *= x;x *= x;x *= x;x *= x;
    x *= x;x *= x;x *= x;x *= x;
    return x;
}
inline int min( int a, int b ) { return a < b ? a : b; }
inline int max( int a, int b ) { return a > b ? a : b; }
inline float min( float a, float b ) { return a < b ? a : b; }
inline float evalT(int length, int volum, int V_car, int V_r, int N_car)
{
    const float a = 0.5;
    int vol = length*volum *a ;
    if(N_car>=volum)
        return INT_MAX;
    else
    {
        return length / min(V_car,V_r/*,V_car_in_r*/) *  fast_exp(N_car+1);
    }   
}

int main()
{
    int i = 8;
    cout << (i - (i >> 2)) << endl;
    cout << exp(1) << endl;
    cout << fast_exp(1) << endl;
    cout << evalT(10,5,5,5,0) << endl;
    cout << evalT(10,5,5,5,5) << endl;
    cout << evalT(10,5,5,5,10) << endl;
    cout << evalT(10,5,5,5,20) << endl;
    return 0;
}
