#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "vertex.h"
#include "edge.h"
#include <map>
#include <stdio.h>

#define DEFAULT_INFINITY -1
#define FEFAULT_SIZE 100

#ifndef CSTR_LEN
#define CSTR_LEN 80
#endif

//template <typename Tv, typename Te>
class AdjMatNet
{
private:
    int num_v;
    int num_e;

    std::vector< Vertex > V;
    std::vector<std::vector< Edge >> E;
    std::map<int,int> _CrossId;
    std::map<int,std::string> _RoadId;

    void makeVDict(MyDSA::Vector<Cross> const & vList);
    void makeEDict(MyDSA::Vector<Road> const & eList);

    void initE(MyDSA::Vector<Road> const & eList);
    void initV(MyDSA::Vector<Cross> const & vList);


public:
    void reset();

    int CrossId(int cross);
    std::string RoadId(int road);
    std::vector<int> Nbrs_T(int const & id) {return Nbrs(CrossId(id)); }
    std::vector<int> const & Nbrs(int node);//图节点node = CrossId(crossid)

    int NbrCross(int const & road, int const & node);
    int NbrCross_T(int const & road, int const & cross_id);
    // int firstNbr(int i) { return NbrCross(V[i].roads[0],i) ;  } //第一个相邻的节点 实现有问题

    AdjMatNet(MyDSA::Vector<Cross> const & vList, MyDSA::Vector<Road> const & eList)
        : num_v(vList.size() ) ,  num_e(eList.size() )  // , E( std::vector< std::vector<Edge >  > (num_v, std::vector< Edge > (num_v,Edge())) )
    {
        makeVDict(vList); //首先构造cross中顶点id 到图顶点id 的映射  图id = CrossId(顶点id)
        initE(eList);//初始化邻接矩阵； 这样道路和 图顶点id对 就有了关系 CrossId(from),CrossId(to) 对应 道路
        makeEDict(eList); //再次利用road.txt的信息 构造 道路id 查询 真实 from,to定点对的映射
        initV(vList); //再次遍历cross.txt 利用邻边信息 构造 利用 真实顶点id 查询邻边的roadid
        reset();
    }
    ~AdjMatNet();
    void print();

    //顶点的确认操作
    const int n_v() {return num_v;}
    VStatus& status ( int i ) { return V[i].status; }
    int& parent ( int i ) { return V[i].parent; }
    int& priority ( int i ) { return V[i].priority; }

    //边的确认操作
    const int n_e() {return num_e;}
    bool exists ( int i, int j ) //边(i, j)是否存在
        {return E[i][j].length > 0; }
         //{ return ( 0 <= i ) && ( i < this->num_v ) && ( 0 <= j ) && ( j < this->num_v ) && E[i][j].from != -1 ; }
    EType & type ( int i, int j ) { return E[i][j].type; }
    int& length ( int i, int j ) { return E[i][j].length; }
    int& channel( int i, int j) {return E[i][j].channel; }
    int& speed( int i, int j) {return E[i][j].speed; }
    int roadid(int i, int j) {return E[i][j].id; }

    //算法
    template <typename PU> void pfs(int s , PU prioUpdater);
    template <typename PU> void PFS(int s , PU prioUpdater);

    //template <typename PU> void dijk(int s, Car const & car,TARDIS const & table, PU prioUpdater);
    //template <typename PU> void DIJK(Car const & car,TARDIS const & table, PU prioUpdater);

    void test(int s, int v ,std::vector<int> & ans);
    bool findPath(int s, int v,std::vector<int> & ans);
    int findPath_t(int s, int v,std::vector<int> & ans);
    int findPath_t(int s, int v);
    void getPrio(std::vector<int> & prio );
};

/*
    孤立节点
        连通图出现孤立节点的情况 要么是官方路网有错 要么是 当前时间、当前节点周围的边权都是INF
        出现孤立节点的情况的时候 应该延迟时间出发
    template <typename PU> bool DIJK(Car const & car,TARDIS const & table, PU prioUpdater);
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    （这个地方有问题）
*/
// template <typename PU> void  AdjMatNet::dijk(Car const & car,TARDIS const & table, PU prioUpdater)
// {
//     reset(); int v = CrossId(car.from);
//     do
//         if( UNDISCOVERED == status(v) )
//             DIJK(car,table, prioUpdater);
//     while(s != (v = ( ++v % num_v)));
// }

// template <typename PU> void  AdjMatNet::DIJK(Car const & car,TARDIS const & table, PU prioUpdater)
// {
//     reset();
//     int s = CrossId(car.from);
//     priority(s) = 0; status(s) = VISITED; parent(s) = -1;
//     while(1)
//     {
//         for(auto r : Nbrs( s ) )
//         {
//             prioUpdater(this,s, NbrCross(r,s) ,car, table );
//             //std::cout << NbrCross(r,s) << "WEIGHT : "<< priority <<' ';
//         }
//         for(int shortest = MYINF, w = 0; w < num_v; w++)
//         {
//             if(UNDISCOVERED == status(w) )
//                 if(shortest > priority(w) )
//                 {
//                     shortest = priority(w);
//                     s = w;
//                 }
//         }
//         if( VISITED == status(s) ) break;
//         status( s )  = VISITED;
//         type(parent( s ), s ) = TREE;
//     }
// }



template <typename PU> void AdjMatNet::pfs(int s , PU prioUpdater)
{
    reset(); int v = s;
    do
        if( UNDISCOVERED == status(v) )
            PFS(v,prioUpdater);
    while(s != (v = ( ++v % num_v)));
}
void AdjMatNet::getPrio(std::vector<int> & ans)
{
    ans.resize(num_v);

    // std::cout << "---------------- graph test ----------------"  << std::endl;


    for(int i = 0; i < num_v; i++)
    {
        //std::cout << parent(i) << ' ';
        //ans.push_back(ans);
        ans[i] = priority(i);
        //std::cout << weight(i) << ' ';
    }

    // std::cout << "---------------- graph test end ----------------"  << std::endl;

}
bool AdjMatNet::findPath(int s, int v, std::vector<int> & ans)
{
    for(; (v) != -1; v = parent(v) )
    {
        ans.push_back(v);
        if(v == s)
            return true;
    }
    return false;
}
int AdjMatNet::findPath_t(int s, int v)
{
    int v_bk = v;
    for(; (v) != -1; v = parent(v) )
    {
        // ans.push_back(v);
        if(v == s)
            return priority(v_bk) - priority(s);
    }
    return false;
}
int AdjMatNet::findPath_t(int s, int v, std::vector<int> & ans)
{
    int v_bk = v;
    for(; (v) != -1; v = parent(v) )
    {
        ans.push_back(v);
        if(v == s)
            return priority(v_bk) - priority(s);
    }
    return false;
}
void AdjMatNet::test(int s, int v ,std::vector<int> & ans)
{
        if (v == s) {
            //outfile << s+1 ;
            //std::cout << s + 1;
            ans.push_back(s+1);
            return;
       }
       test(s, parent(v) ,ans);
       //outfile << "," << v+1 ;
       //std::cout << "," << v+1 ;
       ans.push_back(v+1);

    // std::cout << "---------------- graph test ----------------"  << std::endl;

    // for(int i = 0; i < num_v; i++)
    // {
    //     std::cout << parent(i) << ' ';
    // }

    // std::cout << "---------------- graph test end ----------------"  << std::endl;

//    for(auto r : Nbrs( s ) )
//    {
//        //prioUpdater(this,s,NbrCross(r,s));
//        std::cout << NbrCross(r,s) << ' ';
//    }
    // std::cout <<  s << ",,,,,"<<  CrossId(55)  << std::endl;
    // for(auto c : Nbrs( s ) )
    // {
    //     //cout << c  << endl;
    //     std::cout << CrossId( NbrCross(c,CrossId(55) ) ) << ' ';
    // }
}

template <typename PU> void AdjMatNet::PFS(int s , PU prioUpdater)
{
    priority(s) = 0; status(s) = VISITED; parent(s) = -1;
    while(1)
    {
        for(auto r : Nbrs( s ) )
        {
            prioUpdater(this,s, NbrCross(r,s) );
            //std::cout << NbrCross(r,s) << "WEIGHT : "<< priority <<' ';
        }
        for(int shortest = MYINF, w = 0; w < num_v; w++)
        {
            if(UNDISCOVERED == status(w) )
                if(shortest > priority(w) )
                {
                    shortest = priority(w);
                    s = w;
                }
        }
        if( VISITED == status(s) ) break;
        status( s )  = VISITED;
        type(parent( s ), s ) = TREE;
    }
}
int AdjMatNet::NbrCross(int const & road, int const &  node)
{
    int a,b;
    sscanf(RoadId(road).c_str(),"%d,%d",&a,&b);
    a = CrossId(a);
    b = CrossId(b);
    if(node == a )
        return b;
    else if(node == b)
        return a;
    else
        return -1;
}

int AdjMatNet::NbrCross_T(int const & road, int const &  cross_id)
{
    int a,b;
    sscanf(RoadId(road).c_str(),"%d,%d",&a,&b);
    if(cross_id == a)
        return b;
    else if(cross_id == b)
        return a;
    else
        return -1;
}

std::vector<int> const & AdjMatNet::Nbrs(int node)
{
    return this->V[node].roads;
}
/*
Cross.txt 信息
#(id,roadId,roadId,roadId,roadId)
(1, 5000, 5005, -1, -1)

将id 和 i 对应 i作为图的节点编号
反过来图的节点编号i查 真实id 返回vList[i]

道路没有id

*/
void  AdjMatNet::makeVDict(MyDSA::Vector<Cross> const & vList)
{
    for(int i = 0; i < vList.size(); i++)
    {
        _CrossId.insert( std::pair<int,int>(vList[i].id ,i));
    }
}
int AdjMatNet::CrossId(int cross)
{
    auto iter = _CrossId.find(cross);
    if(iter!=_CrossId.end())
    {
       return iter->second;
    }
    return -1;
}
void  AdjMatNet::makeEDict(MyDSA::Vector<Road> const & eList)
{
    char cstr[CSTR_LEN] = "";
    for(int i = 0; i < eList.size(); i++)
    {
        sprintf(cstr,"%d,%d",eList[i].from,eList[i].to);
        _RoadId.insert(
            std::pair<int,std::string>(eList[i].id,std::string (cstr))
        );
    }
}

std::string AdjMatNet::RoadId(int road)
{
   auto iter = _RoadId.find(road);
   if(iter!=_RoadId.end())
   {
      return iter->second;
   }
   return NULL;
}

/* 邻接表的构造（邻接表只存相应的邻边）
* cross.txt 中的信息
* #(id,roadId,roadId,roadId,roadId)
* (1, 5000, 5005, -1, -1)
* 根据路标号id 和
*/
void AdjMatNet::initV(MyDSA::Vector<Cross> const & vList)
{
    V.resize(num_v);
    for(int i = 0; i <num_v; i++)
    {
        V[CrossId(vList[i].id)] = Vertex(
        vList[i].id, vList[i].roadId1 , vList[i].roadId2, vList[i].roadId3, vList[i].roadId4
        );
    }
}


/*邻接矩阵的构造 (这里可以改进 现在的邻接矩阵太密了)
* road.txt中的信息
* #(id,length,speed,channel,from,to,isDuplex)
* #(5001, 10, 5, 1, 2, 3, 1)
* 根据 from to 和CrossId 得到 图节点id
* 将信息存到图节点id的位置
*/
void AdjMatNet::initE(MyDSA::Vector<Road> const & eList)
{
    E.resize(num_v);
    for(int i = 0; i < num_v; i++ )
    {
        E[i].resize(num_v);
        for(int j = 0; j < num_v; j++)
        {
            E[i][j]  = Edge(-1,MYINF,MYINF,-1,-1,-1,-1,false);
        }
    }
    for(int i = 0; i < eList.size(); i++)
    {
        E[CrossId(eList[i].from) ][CrossId(eList[i].to)].length  = eList[i].length;
        //std::cout << E[eList[i].from-1][eList[i].to-1].id << std::endl;
        //std::cout << eList[i].id << std::endl;
        E[CrossId(eList[i].from) ][CrossId(eList[i].to)].id =  eList[i].id;
        E[CrossId(eList[i].from) ][CrossId(eList[i].to)].channel = eList[i].channel;
        E[CrossId(eList[i].from) ][CrossId(eList[i].to)].speed = eList[i].speed;
        E[CrossId(eList[i].from) ][CrossId(eList[i].to)].exist = true;
        if(eList[i].isDuplex)
         {
            E[CrossId(eList[i].to)][CrossId(eList[i].from)].length  = eList[i].length;
            E[CrossId(eList[i].to)][CrossId(eList[i].from)].id = eList[i].id;
            E[CrossId(eList[i].to)][CrossId(eList[i].from)].channel = eList[i].channel;
            E[CrossId(eList[i].to)][CrossId(eList[i].from)].speed = eList[i].speed;
            E[CrossId(eList[i].to)][CrossId(eList[i].from)].exist = true;
        }
    }
}

void AdjMatNet::reset()
{
    for(int i = 0; i < this->num_v; i++)
    {
        status(i) = UNDISCOVERED;
        // dTime(i) = fTime(i) = -1;// 状态，时间标签

        parent(i) = -1; priority(i) = MYINF; //(在遍历树中的)父节点，优先级数
        for(int j = 0; j < num_v; j++)//所有边的类型
             if(exists(i,j)) type(i,j) = UNDETERMINED;
    }
}
void AdjMatNet::print()
{
    std::cout << "size : ========" << E.size() << "," << E[0].size() << "========="<< std::endl;
    for(std::vector<Edge> var : E)
    {
        for(Edge c : var)
        {
            if(c.length == MYINF)
                std::cout <<  -1 << ' ';
            else
                std::cout <<  c.length << " ";
        }
        std::cout << '|' <<  std::endl;
    }
}
AdjMatNet::~AdjMatNet()
{
}

