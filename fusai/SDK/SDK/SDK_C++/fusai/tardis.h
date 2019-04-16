#pragma once
#include <iostream>
#include <map>
#include <string>
#include <stdio.h>
#include <vector>
#include "lib/DEBUG.h"
#include "lib/graph/AdjMatNet.h"
#include <fstream>

const int TARDIS_default_volum =10000;
#ifndef CSTR_LEN
#define CSTR_LEN 80
#endif

class TARDIS
{
protected:
    int _width; //同一条路 单双算两条 总共路的个数

    int _last_car;

    int _capacity;
    AdjMatNet * g;
    std::vector<std::vector<int> > mdict; //从道路id对 到 TABLE实际道路编号的映射 邻接矩阵形式存储
    //std::map<std::string,int> adict;  //从道路id对 到 TABLE实际道路编号的映射

    std::vector<std::vector<int> > TABLE; // 时间空间上 某条路上 车的个数

/*        当前路的路况
            一开始所有路都是畅通的
            根据delay信息 一些路慢慢地不能走了    */
//    std::vector<std::vector<int>> tabSta; // 时间空间上 某条路 是否已经不能走了

    std::vector<int> tabSum;

    void expand();

   // void makeDict(MyDSA::Vector<Road> const & eList);
    int makeMDict(MyDSA::Vector<Road> const & eList);

    //int read(int const & time, int const & from, int const & to);
    //void write(int const & time, int const & from, int const & to);

public:

    int findDict(int const & from, int const & to);
    int size() { return TABLE.size(); }
    int width() { return _width; }
    int lastCar( ) { return _last_car;}

    int read(int const & time, int const & from, int const & to);
    void write(int const & time, int const & from, int const & to);
    TARDIS(MyDSA::Vector<Road> const & eList, AdjMatNet * gra);//, int (AdjMatNet::*CrossId)(int) ) ;


    void _updateTARDIS(int const & Rb, int const & Re, int Tb, int const & Te);

    void print();
    void print(std::string answerPath);
    ~TARDIS();

    int readRoadSum(int from, int to);

//        //查看Tb时刻 from-to路的状态
//    bool isINF(int from, int to, int Time);
//
//    //从Tb时刻开始 找from-to路上可行时间
//    int findSpace(int from, int to, int Tb);
//
//    // 将Tb时刻 from-to路设为INF
//    void INFThis(int from, int to, int Time);
};

//bool TARDIS::isINF(int from, int to, int Time)
//{
//    if(from>=0 && to >=0 && from <= _width && to <= _width && Time >=0 && Time <= TARDIS_default_volum)
//    {
//        int i = findDict(from,to);
//        if(  tabSta[ Time ] [ i ] == 0 )
//        {
//            return  false;
//        }
//    }
//    return true;
//}
//int TARDIS::findSpace(int from, int to, int Tb)
//{  //从Tb开始 沿着from to 向下找 一直找到 不是INF的位置
//    for(int i = Tb; i < TARDIS_default_volum; i++)
//    {
//        if( isINF(from,to,i) == false)
//        {
//            return i;
//        }
//    }
//}
//void TARDIS::INFThis(int from, int to, int Time)
//{
//    if(from>=0 && to >=0 && from <= _width && to <= _width && Time >=0 && Time <= TARDIS_default_volum)
//    {
//        int i = findDict(from,to);
//        tabSta[ Time ] [ i ] = 1;
//    }
//}

int TARDIS::readRoadSum(int from, int to)
{
    int i = findDict(from, to);
    if(i==-1)
        return MYINF;
    return tabSum[i];
}

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
    int ans = mdict[from][to];
    if( ! (ans >= 0) )
            std::cout << "from " << from << " to " << to << " i " << ans << std::endl;
    assert(ans >=0);
    return ans;
}
void TARDIS::write(int const & time, int const & from, int const & to)
{
    int i = findDict(from,to);

    LOG(i != -1, "faile write : -1, i == %d" , i);
    LOG(0 <= time , "time illegally, time : ",time );
    LOG( time < (int)TABLE.size(), "time illegally, time : %d, size %d :",time , (int)TABLE.size() ) ;
    LOG(0 <= i && i < (int)TABLE[0].size() , "TARDIS::write no road between from - to");

    if(time > _last_car)
        _last_car = time;

    tabSum[i]++;
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

    int a = TABLE[ time ][ i ];
//   int b = TABLE[ time+1 ][ i ];
//   int c = TABLE[ time-1 ][ i ];

    return a;
}

TARDIS::TARDIS(MyDSA::Vector<Road> const & eList, AdjMatNet *gra )
{
    g = gra;
    //根据道路造字典
    mdict =  std::vector<std::vector<int>> (eList.size(), std::vector<int>(eList.size(), -1));
    //makeDict(eList);
    this->_width = makeMDict(eList);
    /** 根据字典长度判断 构造规划表
     *
     *  规划表的容量是 时间长度
     *  每个装的是和adict相同的一个向量
     * */
    TABLE =  std::vector<std::vector<int>> (TARDIS_default_volum, std::vector<int>(_width, 0));
    tabSum = std::vector<int>(_width, 0);
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

/*
    造字典 adict
    输入"1,2" 表示查询从路id 1-2 方向的路径编号
        adict["1,2"]
        返回值是从0 到 2*eList.size()-1
    用邻接矩阵存
*/
int TARDIS::makeMDict(MyDSA::Vector<Road> const & eList)
{
    #ifndef _ECHOOFF
    std::ofstream outfile;
    outfile.open(std::string("tableid_from_to.txt"));
    #endif // _ECHOOFF

    int j = 0;
    for(int i = 0; i < eList.size(); i++)
    {
        int md_from = g->CrossId(eList[i].from);
        int md_to = g->CrossId(eList[i].to);
        mdict[md_from][md_to] = j;
        #ifndef _ECHOOFF
        outfile << eList[i].from << "," << eList[i].to << "," << eList[i].length << ","<< eList[i].channel << ", road " << g->roadid(md_from,md_to) << "," << j << std::endl;
        #endif // _ECHOOFF
        j++;
        if(eList[i].isDuplex)
        {
            mdict[md_to][md_from] = j;
            #ifndef _ECHOOFF
            outfile << eList[i].to << "," << eList[i].from  << "," << eList[i].length << ","<< eList[i].channel << ", road " << g->roadid(md_to,md_from) << "," << j << std::endl;
            #endif // _ECHOOFF
            j++;
        }
    }
    return j;
}
void TARDIS::print(std::string answerPath)
{
    std::ofstream outfile;
    outfile.open(answerPath);
    for(unsigned int i = 0,cnt = 1; i < TABLE.size();i++ )
    {
        for(auto c : TABLE[i])
        {
            //std::cout << c << ' ';
            cnt += c;
        }
        if(cnt == 0 )  continue;

        for(auto c : TABLE[i])
        {
            outfile<< c << ' ';
        }
        outfile << std::endl;
        cnt = 0;
    }
}
