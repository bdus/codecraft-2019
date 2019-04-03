#ifndef ANSTABLE_H
#define ANSTABLE_H
#include <map>
#include <vector>
#include "basicStruct.h"
#include "../DEBUG.h"
#include <fstream>

class AnsTable
{
    private:
        void makeDict(std::vector<CarPath> const & pAList);

    protected:
        int _size;

        /*humm 用来保存结果
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
//        std::cout << "id " << p.id << "pt" << p.startTime ;
//        for(int c : p.path)
//                std::cout << " " << c ;
//        std::cout << std::endl;
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
    _AnsTable.push_back(ans);
}

void AnsTable::read(int const & carid, int & planTime, std::vector<int> & ans)
{
    int i = findDict(carid);
    if(i == -1)
    {
        std::cout << "Anstable fail read : -1" << std::endl;
        return;
    }
    LOG( (*_AnsTable[i])[0] == carid, "AnsTable::read : bad carid %d" , carid);
    planTime = (*_AnsTable[i])[1];
    ans.assign(_AnsTable[i]->begin()+2,_AnsTable[i]->end());
}

void AnsTable::print()
{
    for(int i = 0; i < _size; i++)
    {
        std::cout << "id: " << (*_AnsTable[i])[0] << " planTime: " << (*_AnsTable[i])[1];
        for(int j = 2; j < (int)_AnsTable[i]->size(); j++ )
        {
            std::cout << " " << (*_AnsTable[i])[j] ;
        }
           std::cout << " | "  <<  std::endl;
    }
}
void AnsTable::print(std::string const & answerPath)
{
    std::ofstream outfile;
    outfile.open(answerPath);
    outfile << "#(carId,StartTime,RoadId...)\n";
    for(int i = 0; i < _size; i++)
    {
        outfile << "(" << (*_AnsTable[i])[0] << "," << (*_AnsTable[i])[1];
        for(int j = 2; j < (int)_AnsTable[i]->size(); j++ )
        {
            outfile<< "," << (*_AnsTable[i])[j] ; //这里输出的应该是道路 而不是节点
        }
        outfile << ")\n";
    }
}
#endif // ANSTABLE_H
