#pragma once

#include <fstream>
#include <string>
#include <stdio.h>
#include "graphMatrix/graph.h"

/**
 *  input:
 *      string filename 
 *      int headlines (# lines to ignore at begining)
 * 
*/ 
void textread(std::string & filename, int headerlines)
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
            std::cout << line << std::endl;
	    int id, from, to, speed,p;
	    sscanf(str.c_str(),"(%d,%d,%d,%d,%d)",&id,&from, &to, &speed,&p);
	    cout << id <<  from <<  to <<  speed << p << endl;
	    
        }
        myfile.close();        
    }
    else
    {
        std::cout << "Failed to open file." << std::endl;        
    }   
}
template <typename Tv, typename Te>
void textread(MyDSA::Graph<Tv,Te> & g, std::string & filename, int headerlines)
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
            std::cout << line << std::endl;
	        int id, from, to, speed,p;
	        sscanf(str.c_str(),"(%d,%d,%d,%d,%d)",&id,&from, &to, &speed,&p);
	        cout << id <<  from <<  to <<  speed << p << endl;
	    
        }
        myfile.close();        
    }
    else
    {
        std::cout << "Failed to open file." << std::endl;        
    }   
}
