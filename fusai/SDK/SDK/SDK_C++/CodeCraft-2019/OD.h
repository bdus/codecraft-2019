#pragma once
#include <iostream>
#include "lib/basicStruct.h"
#include "lib/vector/Vector.h"
#include <vector>
#include "lib/graph/AdjMatNet.h"


struct DijkPUT0 { //针对BFS算法的顶点优先级更新器
   virtual void operator() ( AdjMatNet * g, int uk, int v) {
      if ( g->status ( v ) == UNDISCOVERED ) //对于uk每一尚未被发现的邻接顶点v
      {        
        // std::cout << "weight " << weight << "prio" << g->priority ( uk ) << "; ";
        if ( g->priority ( v ) > g->priority ( uk ) + g->length(uk,v) ) { //将其到起点的距离作为优先级数
            g->priority ( v ) = g->priority ( uk ) +  g->length(uk,v); //更新优先级（数）
            g->parent ( v ) = uk; //更新父节点
         }
      }
   }
};


class ODMat
{
private:
    AdjMatNet g;
    std::vector<std::vector<int>> _ODMat;
    std::vector<std::vector<int>> _ODMat_dis;

    void CreateOD(MyDSA::Vector<Car> const & );
    void cal_dis(MyDSA::Vector<Car> & carList);

public:

    int readOD(int i, int j) { if(g.exists(i,j)) return _ODMat[i][j]; }

    std::vector<std::vector<int>> const get() { return  _ODMat; }
    std::vector<std::vector<int>> const get_dis() { return  _ODMat_dis; }

    ODMat(AdjMatNet const & gra, MyDSA::Vector<Car> & carList) : 
        g(gra),
         _ODMat(std::vector<std::vector<int>> (g.n_v(),std::vector<int>(g.n_v(),0))),
         _ODMat_dis(std::vector<std::vector<int>> (g.n_v(),std::vector<int>(g.n_v(),-1)))
    {
        CreateOD(carList);
        cal_dis(carList);
    }
};

void ODMat::cal_dis(MyDSA::Vector<Car> & carList)
{
    for(int i = 0; i < g.n_v(); i++)
    {
        for(int j = 0; j < g.n_v(); j++ )
        {
            if(readOD(i,j) > 0)
            {
                g.PFS(i,DijkPUT0());
                _ODMat_dis[i][j] = g.findPath_t(i,j);
            }
        }
    }
    for(int k = 0; k < carList.size(); k++)
    {
        int i = g.CrossId( carList[k].from );
        int j = g.CrossId( carList[k].to );
        if(g.exists(i,j))
        {
            carList[k].distance = _ODMat_dis[i][j];
        }
    }
}

void ODMat::CreateOD(MyDSA::Vector<Car> const & carList)
{
    for(int k = 0; k < carList.size(); k++)
    {
        int i = g.CrossId( carList[k].from );
        int j = g.CrossId( carList[k].to );
        //if(g.length(i,j) > 0)
        if(g.exists(i,j))
        {
            _ODMat[i][j]++;
        }
     }
}
