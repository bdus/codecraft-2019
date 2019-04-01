#pragma once
namespace MyDSA
{
    template <typename T>
    void Vector<T>::copyFrom ( T const* A, Rank lo, Rank hi ) //复制数组区间A[lo, hi)
    {
        _capacity =  hi - lo + DEFAULT_CAPACITY;
        _elem = new T[_capacity];
        _size = 0;
        while(lo < hi)
            _elem[_size++] = A[lo++];
    }

}