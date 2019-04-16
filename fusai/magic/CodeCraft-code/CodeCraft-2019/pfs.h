#ifndef _MYPFS_H_
#define _MYPFS_H_
#include "tardis.h"
#include "lib/graph/AdjMatNet.h"

struct DijkstraPU { //针对BFS算法的顶点优先级更新器
   virtual void operator() ( AdjMatNet * g, int uk, int v ) {
      if ( g->status ( v ) == UNDISCOVERED ) //对于uk每一尚未被发现的邻接顶点v
         if ( g->priority ( v ) > g->priority ( uk ) + g->length ( uk, v ) ) { //将其到起点的距离作为优先级数
            g->priority ( v ) = g->priority ( uk ) +  g->length ( uk, v ); //更新优先级（数）
            //std::cout <<  "\n\n\n++++++++++\n\n\n" << g->weight ( uk, v ) << std::endl;
            g->parent ( v ) = uk; //更新父节点
         } //如此效果等同于，先被发现者优先
   }
};

struct TimeDijkPU { //针对BFS算法的顶点优先级更新器
   virtual void operator() ( AdjMatNet * g, int uk, int v ,Car const & car,TARDIS * tb ) {
      if ( g->status ( v ) == UNDISCOVERED ) //对于uk每一尚未被发现的邻接顶点v
      {
        int Nc1 = tb->read( g->priority(uk),uk,v);
        int Nc0 = tb->read( g->priority(uk) -1 ,uk,v);
        int Nc2 = tb->read( g->priority(uk) +1 ,uk,v);
        int Nc = round((Nc1 + Nc0 + Nc2) /3) ;
        if(Nc == -1)
            Nc = MYINF;
        else if(Nc < 0)
            Nc = MYINF;
        else if(Nc > MYINF)
            Nc = MYINF;
        float weight = evalT(
            g->length(uk,v) ,
            g->channel(uk,v),
            car.speed,
            g->speed(uk,v),
            Nc
              );
        int new_priority = round(g->priority(uk) + weight);
        // std::cout << "weight " << weight << "prio" << g->priority ( uk ) << "; ";
        if ( g->priority ( v ) > new_priority ) { //将其到起点的距离作为优先级数
            g->priority ( v ) = new_priority; //更新优先级（数）

            g->parent ( v ) = uk; //更新父节点
         }
      }
   }
};

template <typename PU> void  DIJK(AdjMatNet & g, Car const & car,TARDIS & table, PU prioUpdater,int delay = 0)
{
    g.reset();
    // int start_time = car.planTime + delay;
    int s = g.CrossId(car.from);
    g.priority(s) = car.planTime + delay;
    g.status(s) = VISITED; g.parent(s) = -1;
    while(1)
    {
        // std::cout << "站在 " << s << "看Nbr ： ";
        for(auto r : g.Nbrs( s ) )
        {
            if( g.roadid(s, g.NbrCross(r,s) )== -1 )
                continue;
            // std::cout << "\n road "<< r<<" Nbr "<< g.NbrCross(r,s) << " , ";
            prioUpdater(&g,s, g.NbrCross(r,s) ,car, &table );
            //std::cout << NbrCross(r,s) << "WEIGHT : "<< priority <<' ';
        }
        // std::cout << ")\n找到最小的 移交控制权：";
        for(int shortest = MYINF, w = 0; w < g.n_v(); w++)
        {
            if(UNDISCOVERED == g.status(w) )
                if(shortest > g.priority(w) )
                {
                    shortest = g.priority(w);
                    s = w;
                }
        }
        // std::cout << s << " 权重 " << g.priority(s) << std::endl;
        if( VISITED == g.status(s) ) break;
        g.status( s )  = VISITED;
        g.type(g.parent( s ), s ) = TREE;
    }
}
template <typename PU>
int evalPath_t(AdjMatNet & g, TARDIS & table, Car const & car, std::vector<int> const & path,  PU prioUpdater, bool const & isNodeNorId,int delay = 0)
{
    /*
     传进来的路径存在path里面 : 头是起始s 尾巴是终点v
     RoadidOrNode ： path以 道路id(false) or 图真实节点(true) 的形式传进来的
     返回s - v 起止时间 / -1
    */
    g.reset();
    const int s = g.CrossId(car.from);
    const int ed = g.CrossId(car.to);
    g.priority(s) = car.planTime + delay;

    if(true == isNodeNorId)
    {
        LOG( s == path[0] && ed == path[ path.size() - 1 ],  "is not node");
        for(unsigned int i = 0; i < path.size()-1; i++) //遍历图节点
        {//更新路上节点的权
            int uk = path[i];
            int v = path[i+1];
            prioUpdater(&g, uk, v, car, &table); // (这里有问题)
            if(g.priority(v) >= MYINF)
                return -1;
        }
    }
    else
    {
        LOG( g.roadid( s,  g.NbrCross( path[0], s ) )  == path[0], "is not roadid");        
        //LOG( g.roadid( ed,  g.NbrCross( path[path.size()-1], ed ) )  == path[path.size()-1],"is not roadid");//is roadid  (这里有问题)

        int uk = 0;//s;
        int v = s;//g.NbrCross(  path[0], uk );
        for(unsigned int i = 0; i < path.size(); i++) //遍历路
        {
            uk = v;
            v = g.NbrCross(  path[i], uk );
            prioUpdater(&g, uk, v, car, &table);
            if(g.priority(v) >= MYINF)
                return -1;
        }
    }
    return g.priority(ed) - g.priority(s);
}

#endif // _MYPFS_H_
