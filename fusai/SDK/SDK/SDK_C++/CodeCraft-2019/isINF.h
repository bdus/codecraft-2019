#pragma once


bool isINF(int from, int to, int Time, TARDIS * table, std::vector<std::vector<int>> &  tabSta)
{
    int _width = tabSta[0].size() ;
    int _length =  tabSta.size();
    if(from>=0 && to >=0 && from <=  _width && to <= _width && Time >=0 && Time <= _length )
    {
        int i = table->findDict(from,to);
        if(  tabSta[ Time ] [ i ] == 0 )
        {
            return  false;
        }
    }
    return true;
}
int findSpace(int from, int to, int Tb, TARDIS * table, std::vector<std::vector<int>> &  tabSta)
{  //从Tb开始 沿着from to 向下找 一直找到 不是INF的位置
    for(int i = Tb; i < TARDIS_default_volum; i++)
    {
        if( isINF(from,to,i, table,tabSta) == false)
        {
            return i;
        }
    }
}
void INFThis(int from, int to, int Time, TARDIS * table, std::vector<std::vector<int>> &  tabSta)
{
    int _width = tabSta[0].size() ;
    int _length =  tabSta.size();
    if(from>=0 && to >=0 && from <= _width && to <= _width && Time >=0 && Time <= _length)
    {
        int i = table->findDict(from,to);
        tabSta[ Time ] [ i ] = 1;
    }
}
