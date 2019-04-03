#pragma once
#include <iostream>
#include <map>
#include <string>
#include <stdio.h>
#include <vector>
#include "lib/DEBUG.h"
#include "lib/graph/AdjMatNet.h"


const int TARDIS_default_volum =20000;
#ifndef CSTR_LEN
#define CSTR_LEN 80
#endif

class TARDIS
{
protected:
    // int w;
    int _last_car;
    int _capacity;
    AdjMatNet g;

    std::map<std::string,int> adict;  //从道路id对 到 TABLE实际道路编号的映射
    std::vector<std::vector<int>> TABLE;

    void expand();

    void makeDict(MyDSA::Vector<Road> const & eList);


    //int read(int const & time, int const & from, int const & to);
    //void write(int const & time, int const & from, int const & to);

public:


    int findDict(int const & from, int const & to);
    int size() { return TABLE.size(); }
    int width() { return adict.size(); }
    int lastCar( ) { return _last_car;}

    int read(int const & time, int const & from, int const & to);
    void write(int const & time, int const & from, int const & to);
    TARDIS(MyDSA::Vector<Road> const & eList, AdjMatNet const & gra);//, int (AdjMatNet::*CrossId)(int) ) ;

    void _updateTARDIS(int const & Rb, int const & Re, int Tb, int const & Te);

    void print();

    ~TARDIS();
};

void TARDIS::print()
{
    for(unsigned int i = 0,cnt = 1; i < TABLE.size();i++ )
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

//    if(i == -1)
//    {
//        std::cout << "fail write : -1" << from << "," << to << std::endl;
//        return;
//    }

    LOG(i != -1, "faile write : -1, i == %d" , i);
    LOG(0 <= time , "time illegally, time : ",time );
    LOG( time < (int)TABLE.size(), "time illegally, time : %d, size %d :",time , (int)TABLE.size() ) ;
    LOG(0 <= i && i < (int)TABLE[0].size() , "TARDIS::write no road between from - to");

    if(time > _last_car)
        _last_car = time;

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
    LOG(i != -1, "faile read : -1, i == %d" , i);
    LOG(0 <= time , "time illegally, time : ",time );
    LOG( time < (int)TABLE.size(), "time illegally, time : %d, size %d :",time , (int)TABLE.size() ) ;
    LOG(0 <= i && i < (int)TABLE[0].size() , "TARDIS::write no road between from - to");

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
    //assert(j <= eList.size()*2 , "TARDIS::makeDict  :  bad #road j"  )

}
