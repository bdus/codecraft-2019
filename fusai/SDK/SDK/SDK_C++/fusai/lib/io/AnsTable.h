#ifndef ANSTABLE_H
#define ANSTABLE_H
#include <map>
#include <vector>
#include "basicStruct.h"
#include "../DEBUG.h"

class AnsTable
{
    private:
        void makeDict(std::vector<CarPath> const & pAList);

    protected:
        int _size;

        /*hum 很膨胀的写了动态的结构 用来保存结果
        保存结构:
            int carid, int planTime. int roadid,...
            1000    1   100 101 102
         */
        std::vector<std::vector<int> *> _AnsTable;

        /*
            映射： roadid 到 表的真实下标
        */
        std::map<int,int> _dict;
        int findDict(int const & );

    public:
        AnsTable() :_size(0) {}
        AnsTable(std::vector<CarPath> const & pAList);
        ~AnsTable() {
            for(unsigned int i = 0; i < _AnsTable.size(); i++)
            {
                delete _AnsTable[i];
            }
        }
        const int size() {return _size;}
        void push_back(int const & carid, int const &  planTime, std::vector<int> const & nodes);
        void read(int const & carid, int & planTime, std::vector<int> & ans);
        void print();
        void print(std::string const & answer);
};
int AnsTable::findDict(int const & carid)
{
    auto iter = _dict.find(carid);
    if(iter!=_dict.end())
    {
       return iter->second;
    }
    return -1;
}
AnsTable::AnsTable(std::vector<CarPath> const & pAList) : _size(0)
{
    makeDict(pAList);
}

void AnsTable::makeDict(std::vector<CarPath> const & pAList)
{
    for(CarPath p : pAList)
    {
        push_back(p.id,p.startTime,p.path);
    }
}
void AnsTable::push_back(int const & carid, int const &  planTime, std::vector<int> const & nodes)
{
    _dict.insert(
        std::pair<int,int>(carid,_size)
    );//这里可能有点问题 如果我要删除某个规划的时候 _dict就失效了
    _size++;

    std::vector<int> * ans = new std::vector<int>();
    ans->push_back(carid);
    ans->push_back(planTime);
    for(int n : nodes)
    {
        ans->push_back(n);
    }
}

void AnsTable::read(int const & carid, int & planTime, std::vector<int> & ans)
{
    int i = findDict(carid);
    if(i == -1)
    {
        std::cout << "Anstable fail read : -1" << std::endl;
        return;
    }
    assert( (*_AnsTable[i])[0] == carid);
    planTime = (*_AnsTable[i])[1];
    ans.assign(_AnsTable[i]->begin()+2,_AnsTable[i]->end());
}

void AnsTable::print()
{

}
void AnsTable::print(std::string const & answer)
{

}
#endif // ANSTABLE_H
