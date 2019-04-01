#pragma once
#include <iostream>
#include <vector>


void print(std::vector<CarPath> const & pAList)
{
    for(auto p : pAList)
    {
        std::cout << p.id << "," << p.startTime;
        for(auto c: p.path)
        {
            std::cout  << ", "<< c ;
        }
        std::cout  << " |< " << std::endl;
    }
}

template <typename T>
void print(const std::vector<T> & v)
{
#ifndef NDECHO
    std::cout << "\nprint ： ";
    for(int i = 0; i < v.size(); i++)
    {
       std::cout<< v[i] << " ";
    }
    std::cout << std::endl;
#endif // NDECHO
}

template <typename T>
void print(std::vector<std::vector<T>> const & G)
{
#ifndef NDECHO
    for(auto v : G)
    {
        for(auto c : v)
        {
            // if(c >= 100000)
            // std::cout << "-1 ";
            // else
            std::cout << c << ' ';
        }
        std::cout << std::endl;
    }
#endif
}

#ifdef _MyDSAVECTOR_H_

template <typename T>
void print(const MyDSA::Vector<T> & v ) //, char s[] = "print ： ")
{
#ifndef NDECHO
    std::cout << "\nprint ： ";
    for(int i = 0; i < v.size(); i++)
    {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;
#endif // NDECHO
}
#endif
