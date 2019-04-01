#pragma once
#include <iostream>
#include <map>
#include <string>
#include <stdio.h>
#include <vector>
#include "lib/DEBUG.h"
#include "lib/graph/AdjMatNet.h"
//class AdjMatNet;

//#include <sstream>

// std::map<std::map<int,int>,int> makeDict(MyDSA::Vector<Road> const & eList)
// {
//     std::map<std::map<int,int>,int> ans;
//     for(int i = 0, int j = 0; i < eList.size(); i++)
//     {
//         ans.insert(std::pair<std::pair<int,int>,int>(std::pair<int,int>(eList[i].from,eList[i].to),j++));
//         if(eList[i].isDuplex)
//             ans.insert(std::pair<std::pair<int,int>,int>(std::pair<int,int>(eList[i].to,eList[i].from),j++));
//     }
//     return ans;
// }

// std::map<std::string,int> makeDict(MyDSA::Vector<Road> const & eList)
// {
//     std::map<std::string,int> ans;
//     char cstr[50] = "";
//     //std::stringstream sstr;
//     int j = 0;
//     for(int i = 0; i < eList.size(); i++)
//     {
//         sprintf(cstr,"%d,%d",eList[i].from,eList[i].to);
//         ans.insert(std::pair<std::string,int>(std::string(cstr),j));
//         j=j+1;
//         if(eList[i].isDuplex)
//         {
//             sprintf(cstr,"%d,%d",eList[i].to,eList[i].from);
//             ans.insert(std::pair<std::string,int>(std::string(cstr),j));
//             j++;
//         }
//     }
//     return ans;
// }

// int readTARDIS(int const & time, int const & from, int const & to,std::vector<std::vector<int>> const & TARDIS, std::map<std::string,int> & adict)
// {
//     char cstr[50] = "";
//     sprintf(cstr,"%d,%d",from,to);
//     std::string sstr(cstr);
//     int i = adict[sstr];
//     //加判断 time / i 越界、expand

//     assert(0 <= time && time < TARDIS.size() );
//     assert(0 <= i && i < TARDIS[0].size() );

//     return TARDIS[ time ][ i ];
// }

// void writeTARDIS(int const & time, int const & from, int const & to,std::vector<std::vector<int>> & TARDIS, std::map<std::string,int> & adict)
// {
//     //一个隐患
//     char cstr[100] = "";
//     sprintf(cstr,"%d,%d",from,to);
//     std::string sstr(cstr);
//     int i = adict[sstr];
//     assert( i < adict.size() );
//     //加判断 time / i 越界、expand
//     assert(0 <= time && time < TARDIS.size() );
//     assert(0 <= i && i < TARDIS[0].size() );
//     //std::cout << time << "," << i << std::endl;
//     TARDIS[ time ][ i ]++;
// }

// void _updateTARDIS(int const & Rb, int const & Re, int Tb, int const & Te, std::vector<std::vector<int>> & TARDIS, std::map<std::string,int> & adict)
// {
//     //expand 判断容量
//     while(Tb < Te){

//         #ifndef NDECHO
//         std::cout << "from Node " << Rb << " to Node " << Re   \
//          << " time :( " <<  Tb << "  ) " << std::endl;
//         #endif
//          Tb++;
//         writeTARDIS(Tb,Rb,Re,TARDIS,adict);
//     }
// }


const int TARDIS_default_volum =2000;
#ifndef CSTR_LEN
#define CSTR_LEN 80
#endif
class TARDIS
{
protected:
    // int w;
    // int _size;
    // int _capacity;
    AdjMatNet g;

    std::map<std::string,int> adict;
    std::vector<std::vector<int>> TABLE;

    void expand();

    void makeDict(MyDSA::Vector<Road> const & eList);


    //int read(int const & time, int const & from, int const & to);
    //void write(int const & time, int const & from, int const & to);

public:
    int findDict(int const & from, int const & to);
    int size() { return TABLE.size(); }
    int width() { return adict.size(); }

    int read(int const & time, int const & from, int const & to);
    void write(int const & time, int const & from, int const & to);
    TARDIS(MyDSA::Vector<Road> const & eList, AdjMatNet const & gra);//, int (AdjMatNet::*CrossId)(int) ) ;

    void _updateTARDIS(int const & Rb, int const & Re, int Tb, int const & Te);

    void print();

    ~TARDIS();
};

void TARDIS::print()
{
    for(int i = 0,cnt = 1; i < TABLE.size();i++ )
    {
        for(auto c : TABLE[i])
        {
            //std::cout << c << ' ';
            cnt += c;
        }
        if(cnt == 0 )  continue;
        std::cout  << '|' ;
        std::cout << i << " : ";
        for(auto c : TABLE[i])
        {
            std::cout << c << ' ';
        }
        std::cout  << '<' << std::endl;
        cnt = 0;
    }
}

void TARDIS::_updateTARDIS(int const & Rb, int const & Re, int Tb, int const & Te)
{
    while(Tb < Te)
    {
        write(Tb,Rb,Re);
        Tb++;
    }
}
int TARDIS::findDict(int const & from, int const & to)
{
    char cstr[CSTR_LEN] = "";
    sprintf(cstr,"%d,%d",from,to);
    std::string cmd(cstr);

    auto iter = adict.find(cmd);
    if(iter!=adict.end())
    {
       return iter->second;
    }   
    return -1;
}
void TARDIS::write(int const & time, int const & from, int const & to)
{
    int i = findDict(from,to);

    if(i == -1)
    {
        std::cout << "fail write : -1" << from << "," << to << std::endl;
        return;
    }

        
    assert(i != -1);
    assert(0 <= time && time < TABLE.size() ); ///扩容
    assert(0 <= i && i < TABLE[0].size() );

    TABLE[ time ][ i ]++;
}

int TARDIS::read(int const & time, int const & from, int const & to)
{
    int i = findDict(from,to);
    if(i == -1)
    {
        std::cout << "fail read : -1" << from << "," << to << std::endl;        
        return MYINF;
    }
    
    //加判断 time / i 越界、expand
    assert(i != -1) ;
    assert(0 <= time );
    assert(time < TABLE.size() );
    assert(0 <= i && i < TABLE[0].size() );

    return TABLE[ time ][ i ];
}

TARDIS::TARDIS(MyDSA::Vector<Road> const & eList, AdjMatNet const & gra ) : g(gra)
{
    //g = gg;
    //根据道路造字典
    makeDict(eList);
    /** 根据字典长度判断 构造规划表
     *
     *  规划表的容量是 时间长度
     *  每个装的是和adict相同的一个向量
     * */
    TABLE =  std::vector<std::vector<int>> (TARDIS_default_volum, std::vector<int>(adict.size() , 0));
}

TARDIS::~TARDIS()
{

}

/*
    造字典 adict
    输入"1,2" 表示查询从路id 1-2 方向的路径编号
        adict["1,2"]
        返回值是从0 到 2*eList.size()-1
*/
void TARDIS::makeDict(MyDSA::Vector<Road> const & eList)
{
    //std::map<std::string,int> ans;
    char cstr[CSTR_LEN] = "";
    //std::stringstream sstr;
    int j = 0;
    for(int i = 0; i < eList.size(); i++)
    {
        //sprintf(cstr,"%d,%d",eList[i].from,eList[i].to);
        sprintf(cstr,"%d,%d",g.CrossId(eList[i].from),g.CrossId(eList[i].to));
        adict.insert(std::pair<std::string,int>(std::string(cstr),j));
        //std::cout << std::string(cstr) << " , " << j << std::endl;
        j=j+1;
        if(eList[i].isDuplex)
        {
            sprintf(cstr,"%d,%d",g.CrossId(eList[i].to),g.CrossId(eList[i].from));
            adict.insert(std::pair<std::string,int>(std::string(cstr),j));
            //std::cout << std::string(cstr) << " , " << j << std::endl;
            j++;
        }
    }
    assert(j <= eList.size()*2 );
    //return adict;
}
