#pragma once
#include "tardis.h"
#include <vector>

class INFTab
{
private:
    int _width;
    int _length;
    std::vector< std::vector< int > >  staMat;
    TARDIS * table;

public:
    INFTab( TARDIS * table);
    ~INFTab();
    bool isINF(int from, int to, int Time);
    int findSpace(int from, int to, int Tb);
    void INFThis(int from, int to, int Time);
};

INFTab::INFTab(TARDIS * tab)
{
    table = tab;
    _width = table->width();
    _length = TARDIS_default_volum;
    staMat = std::vector< std::vector<int> > ( TARDIS_default_volum,  std::vector<int> (_width, 0));
}
INFTab::~INFTab()
{

}

bool INFTab::isINF(int from, int to, int Time)
{
    if(from>=0 && to >=0 && from <=  _width && to <= _width && Time >=0 && Time <= _length )
    {
        int i = table->findDict(from,to);
        if( ! (i >= 0) )
            std::cout << "from " << from << " to " << to << " i " << i << std::endl;
        assert(i < _width);

        if(  staMat[ Time ] [ i ] == 0 )
        {
            return  false;
        }
    }
    return true;
}
int INFTab::findSpace(int from, int to, int Tb)
{  //从Tb开始 沿着from to 向下找 一直找到 不是INF的位置
    for(int i = Tb; i < _length; i++)
    {
        if( isINF(from,to,i) == false)
        {
            return i;
        }
    }
}
void INFTab::INFThis(int from, int to, int Time)
{
    if(from>=0 && to >=0 && from <= _width && to <= _width && Time >=0 && Time <= _length)
    {
        int i = table->findDict(from,to);
        staMat[ Time ] [ i ] = 1;
    }
}
