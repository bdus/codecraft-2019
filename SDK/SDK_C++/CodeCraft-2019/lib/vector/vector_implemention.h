#pragma once

#include "vector_bracket.h"

#include "vector_copyfrom.h"


template <typename T>
MyDSA::Vector<T> & MyDSA::Vector<T>::operator= (MyDSA::Vector<T> const& V)
{
    if( _elem ) delete [] _elem;
    copyFrom( V._elem, 0, V.size() );
    return *this;
}

namespace MyDSA
{    
    template <typename T>
    void Vector<T>::expand()
    {
        if(_size < _capacity) return;
        if(_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;
        T * _oldElem = _elem;
        _elem = new T[_capacity <<= 1];
        for(int i = 0; i < _size; i++)
            _elem[i] = _oldElem[i];        
        delete [] _oldElem;
    }

    template <typename T>
    Rank Vector<T>::insert(Rank r, T const & e)
    {
        expand();
        for(int i = _size; i > r; i--)
            _elem[i] = _elem[i-1];
        _elem[r] = e;   _size++;
        return r;
    }

    template <typename T>
    int Vector<T>::disordered() const //判断向量是否已排序
    {
        int n = 0;
        for(int i = 0; i < _size-1; i++)
            if(_elem[i] > _elem[i+1]) n++;
        return n;                
    }

    template <typename T>
    Rank Vector<T>::find ( T const& e, Rank lo, Rank hi ) const //无序向量区间查找
    {
        int ans;
        while(lo < hi--)
        {
            if (_elem[hi] == e) 
                break;            
        }
        return hi;
    }
    template <typename T>
    int Vector<T>::erase(Rank lo, Rank hi)
    {
        //assert(0 < lo < hi && hi -lo < _size && hi < _size)
        // 0 lo hi _size
        // **xxx***
        while (hi < _size)
            _elem[lo++] = _elem[hi++];
        _size = lo;
        //std::cout << "erase(lo,hi) -> _size : " << _size << std::endl;
        return hi - lo;
    }
    template <typename T>
    T Vector<T>::erase(Rank r)
    {
        T _backup = _elem[r];
        erase(r,r+1);        
        return _backup;
    }    
}