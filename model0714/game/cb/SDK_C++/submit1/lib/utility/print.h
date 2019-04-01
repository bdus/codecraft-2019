#pragma once
#include <iostream>
#include <vector>

template <typename T>
void print(const std::vector<T> & v)
{
    std::cout << "\nprint ： ";
    for(int i = 0; i < v.size(); i++)
    {
       std::cout<< v[i] << " ";
    }
    std::cout << std::endl;
}


#ifdef _MyDSAVECTOR_H_

template <typename T>
void print(const MyDSA::Vector<T> & v ) //, char s[] = "print ： ") 
{       
    std::cout << "\nprint ： ";
    for(int i = 0; i < v.size(); i++)
    {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;    
}
#endif
