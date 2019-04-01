#pragma once
#include "../vector/Vector.h"
#include "../list/list.h"

namespace MyDSA
{
    template <typename T>
    class VStack : public Vector<T>
    {
        //vector[0] 是 栈底
    public:
        void push(T e) { this->push_back(e); } //为什么需要加上this-> ?
        T pop() { return this->pop_back(); }
        T & top() { return (*this)[this->size()-1]; }
    }; 

    template <typename T>
    class LStack : public List<T>
    {
        //header是 栈头
    public:
        void push(T e) { this->insertAsFirst(e); }
        T pop() {return this->remove(this->first()); }
        T & top() {return (*this)[0];};

    };

    // template <typename T>
    // T & LStack<T>::top()
    // {
    //     return (*this)[0];        
    // }

}