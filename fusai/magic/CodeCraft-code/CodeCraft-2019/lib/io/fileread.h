#pragma once

#include <fstream>
#include <string>
#include <stdio.h>
#include <iostream>
#include <list>

/**
 *  input:
 *      string filename
 *      int headlines (# lines to ignore at begining)
 *
*/
// void textread(std::string & filename, int headerlines)
// {
//     std::ifstream myfile(filename);
//     std::string line;
//     if(myfile.is_open())
//     {
//         while(headerlines--)
//         {
//             getline(myfile,line);
//         }

//         while(getline(myfile,line))
//         {
//             std::cout << line << std::endl;
// 	        int id, from, to, speed,p;
// 	        sscanf(line.c_str(),"(%d,%d,%d,%d,%d)",&id,&from, &to, &speed,&p);
// 	        std::cout << id <<  from <<  to <<  speed << p << std::endl;

//         }
//         myfile.close();
//     }
//     else
//     {
//         std::cout << "Failed to open file." << std::endl;
//     }
// }

template <typename T>
void textread(MyDSA::Vector<T> & anslist, std::string & filename, int headerlines)
{
    std::ifstream myfile(filename);
    std::string line;
    if(myfile.is_open())
    {
        while(headerlines--)
        {
            getline(myfile,line);
        }

        while(getline(myfile,line))
        {
            #ifdef _DEBUG
            std::cout << line << std::endl;
	        T e(line);
            std::cout << e << std::endl;
            #endif
            anslist.push_back(line);
        }
        myfile.close();
    }
    else
    {
        std::cout << "Failed to open file." << std::endl;
    }
}

template <typename T>
void textread(std::vector<T> & anslist, std::string & filename, int headerlines)
{
    std::ifstream myfile(filename);
    std::string line;
    if(myfile.is_open())
    {
        while(headerlines--)
        {
            getline(myfile,line);
        }

        while(getline(myfile,line))
        {
            #ifdef _DEBUG
            std::cout << line << std::endl;
	        T e(line);
            std::cout << e << std::endl;
            #endif
            anslist.push_back(line);
        }
        myfile.close();
    }
    else
    {
        std::cout << "Failed to open file." << std::endl;
    }
}

template <typename T>
void textread(std::list<T> & anslist, std::string & filename, int headerlines)
{
    std::ifstream myfile(filename);
    std::string line;
    if(myfile.is_open())
    {
        while(headerlines--)
        {
            getline(myfile,line);
        }

        while(getline(myfile,line))
        {
            #ifdef _DEBUG
            std::cout << line << std::endl;
	        T e(line);
            std::cout << e << std::endl;
            #endif
            anslist.push_back(line);
        }
        myfile.close();
    }
    else
    {
        std::cout << "Failed to open file." << std::endl;
    }
}