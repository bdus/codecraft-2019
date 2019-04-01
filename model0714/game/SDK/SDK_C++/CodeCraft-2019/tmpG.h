#pragma once
#include "para.h"
#include "tardis.h"

//const int INF = 1000000; //100w

// typedef enum { UNDISCOVERED, DISCOVERED, VISITED } VStatus; //顶点状态

// template <typename Tv, typename Te> struct BfsPU { //针对BFS算法的顶点优先级更新器
//    virtual void operator() (std::vector<std::vector<int>> const & g, int uk, int v ) {
//       if ( g->status ( v ) == UNDISCOVERED ) //对于uk每一尚未被发现的邻接顶点v
//          if ( g->priority ( v ) > g->priority ( uk ) + 1 ) { //将其到起点的距离作为优先级数
//             g->priority ( v ) = g->priority ( uk ) + 1; //更新优先级（数）
//             g->parent ( v ) = uk; //更新父节点
//          } //如此效果等同于，先被发现者优先
//    }
// };

//template <typename PU>
// void PFS(int n,int s,std::vector<std::vector<int>> const & G)
// {
//     /*
//     n : 定点个数
//     s : 源点
//     G：           图的邻接矩阵
//     vis
//     d：           存储源点s到达其它顶点的最短距离
//     pre：         存储从起点s到达顶点v的最短路径上v的前一个顶点 （新添加）
//     */
//     std::vector<VStatus> vis(n);
//     std::vector<int> d(n);
//     std::vector<int> pre(n);

//     fill(d.begin(), d.end(), INF);                         //初始化最短距离矩阵，全部为INF

//     for (int i = 0; i < n; ++i)                            //新添加
//             pre[i] = i;

//     d(s) = 0;
//     vis(s) = VISITED;


//     while(1)
//     {
//         for(int w = )
//     }

// }

//template <typename T>
int Dijkstra(int n, Car const & car, std::vector<std::vector<int>> const & G, std::vector<std::vector<int>> const & G_v, std::vector<std::vector<int>> const & G_sp , std::vector<bool>& vis, std::vector<float>& d, std::vector<int>& pre,std::vector<std::vector<int>> const & TARDIS, std::map<std::string,int> & adict,int delay = 0 )
{
       /*
       param
       n：           顶点个数
       s：           源点
       G：           图的邻接矩阵
       vis：         标记顶点是否已被访问
       d：           存储源点s到达其它顶点的最短距离
       pre：         存储从起点s到达顶点v的最短路径上v的前一个顶点 （新添加）
       */
       int s = car.from -1;
       fill(d.begin(), d.end(), MYINF);                         //初始化最短距离矩阵，全部为INF

       for (int i = 0; i < n; ++i)                            //新添加
              pre[i] = i;

       d[s] = 0.0;                                              //起点s到达自身的距离为0
       for (int i = 0; i < n; ++i)
       {
              int u = -1;                                     //找到d[u]最小的u
              int MIN = MYINF;                                  //记录最小的d[u]
              for (int j = 0; j < n; ++j)                     //开始寻找最小的d[u]
              {
                     if (vis[j] == false && d[j] < MIN)
                     {
                           u = j;
                           MIN = d[j];
                     }
              }
              //找不到小于INF的d[u]，说明剩下的顶点和起点s不连通
              if (u == -1)
                     return -1;
              vis[u] = true;                                  //标记u已被访问
              for (int v = 0; v < n; ++v)
              {
                     //遍历所有顶点，如果v未被访问&&u能够到达v&&以u为中介点可以使d[v]更优

                     //float weigth =  d[u] + evalT(G[u][v],G_v[u][v],car.speed,G_sp[u][v], readTARDIS(car.planTime + d[u],car.from,car.to,TARDIS,adict) );
                     float weigth = d[u] + G[u][v];
                     if(weigth >= MYINF)
                            weigth = MYINF;
                        //std::cout << "wei: " << weigth << std::endl;
                     assert(weigth >=0 );
                     assert(weigth <= MYINF);
                     if (vis[v] == false && /*d[u] + G[u][v]*/weigth < d[v]) {
                           d[v] = weigth;// d[u] + G[u][v];             //更新d[v]
                           pre[v] = u;                        //记录v的前驱顶点为u（新添加）
                     }
              }
       }
       return car.planTime + delay;
}
// void Dijkstra(int n, int s, std::vector<std::vector<int>> G, std::vector<bool>& vis, std::vector<int>& d, std::vector<int>& pre)
// {
//        /*
//        param
//        n：           顶点个数
//        s：           源点
//        G：           图的邻接矩阵
//        vis：         标记顶点是否已被访问
//        d：           存储源点s到达其它顶点的最短距离
//        pre：         存储从起点s到达顶点v的最短路径上v的前一个顶点 （新添加）
//        */
//        fill(d.begin(), d.end(), INF);                         //初始化最短距离矩阵，全部为INF

//        for (int i = 0; i < n; ++i)                            //新添加
//               pre[i] = i;

//        d[s] = 0;                                              //起点s到达自身的距离为0
//        for (int i = 0; i < n; ++i)
//        {
//               int u = -1;                                     //找到d[u]最小的u
//               int MIN = INF;                                  //记录最小的d[u]
//               for (int j = 0; j < n; ++j)                     //开始寻找最小的d[u]
//               {
//                      if (vis[j] == false && d[j] < MIN)
//                      {
//                            u = j;
//                            MIN = d[j];
//                      }
//               }
//               //找不到小于INF的d[u]，说明剩下的顶点和起点s不连通
//               if (u == -1)
//                      return;
//               vis[u] = true;                                  //标记u已被访问
//               for (int v = 0; v < n; ++v)
//               {
//                      //遍历所有顶点，如果v未被访问&&u能够到达v&&以u为中介点可以使d[v]更优
//                      if (vis[v] == false && d[u] + G[u][v] < d[v]) {
//                            d[v] = d[u] + G[u][v];             //更新d[v]
//                            pre[v] = u;                        //记录v的前驱顶点为u（新添加）
//                      }
//               }
//        }
// }
// template <typename T>
// void DFSPrint(int s, int v, std::vector<T> pre, std::ofstream & outfile)
// {
//        if (v == s) {
//               outfile << s+1 ;
//               //std::cout << s+1 ;
//               return;
//        }
//        DFSPrint(s, pre[v], pre,outfile);
//        outfile << "," << v+1 ;
//        //std::cout << "," << v+1 ;
// }

template <typename T>
void DFSPrintp(int s, int v, std::vector<T> const & pre,std::vector<T> & ans)
{
       if (v == s) {
              //outfile << s+1 ;
              //std::cout << s+1 ;
              ans.push_back(s+1);
              return;
       }
       DFSPrintp(s, pre[v], pre, ans);
       //outfile << "," << v+1 ;
       //std::cout << "," << v+1 ;
       ans.push_back(v+1);
}

// template <typename T>
// void DFSPrintp(int s, int v, std::vector<T> const & pre, std::vector<int> const & d, std::vector<T> & ans)
// {
//        if (v == s) {
//               //outfile << s+1 ;
//               //std::cout << s+1 ;
//               std::cout << d[v] << ' ';
//               ans.push_back(s+1);
//               return;
//        }
//        DFSPrintp(s, pre[v], pre, ans);
//        //outfile << "," << v+1 ;
//        //std::cout << "," << v+1 ;
//        ans.push_back(v+1);
// }


// template <typename Tv>
// void getRoad(std::vector<int> const & ans,std::vector<std::vector<Tv>> const & G)
// {
//     int i = 0;
//     while(i < ans.size()-1)
//     {
//         //std::cout << ans[i]-1 << ' ' << ans[i+1]-1 << '\n' ;
//         std::cout << G[ ans[i]-1][ ans[i+1]-1] << ',' ;
//         std::cout <<  ans[i] << "," << ans[i+1] << '\n' ;
//         i++;
//     }
//     std::cout << std::endl;
// }

//逻辑有问题
//template <typename Tv>
//void updateTARDIS(std::vector<int> const & ans, std::vector<float> const & d, std::vector<std::vector<Tv>> const & G, Car const & car,  int const & delay, std::vector<std::vector<int>> & TARDIS, std::map<std::string,int> & adict)
//{
//    int i = 0;
//    while(i < ans.size()-1)
//    {
//        assert(ans[i]-1 < d.size());
//        assert( ans[i+1] -1 < d.size());
//        #ifndef NDECHO
//        std::cout << "from Node " << ans[i] << " to Node " << ans[i+1]  << ", Road " \
//         << G[ ans[i]-1][ ans[i+1]-1]  \
//         << " time :( " <<  (int)d[ ans[i]-1 ] + car.planTime-1 + delay << " - "  \
//         << (int)d[ ans[i+1] -1 ]  + car.planTime -1 + delay << " ) " << std::endl;
//        #endif
//
//        _updateTARDIS(
//            ans[i],
//            ans[i+1],
//            (int)d[ ans[i]-1 ] + car.planTime-1 + delay,
//             (int)d[ ans[i+1] -1 ]  + car.planTime -1 + delay
//            ,TARDIS,adict);
//        i++;
//    }
//    std::cout << std::endl;
//}

template <typename Tv>
void getRoad(std::vector<int> const & ans,std::vector<std::vector<Tv>> const & G,std::ofstream & outfile)
{
    int i = 0;
    while(i < ans.size()-2)
    {
        //std::cout << ans[i]-1 << ' ' << ans[i+1]-1 << '\n' ;
        outfile << G[ ans[i]-1][ ans[i+1]-1] << ',';
        i++;
    }
    outfile << G[ ans[i]-1][ ans[i+1]-1];
    //std::cout << std::endl;
}


template <typename T>
std::vector<std::vector<T>> onesG(int w, int h, T const &val)
{
    //std::vector<std::vector<float>> G(num_v,std::vector<float>(num_v,INF));
    return std::vector<std::vector<T>> (h,std::vector<T>(w,val));
}

// template <typename T,typename Tv>
// void setG(std::vector<std::vector<T>> & G, std::vector<std::vector<Tv>> & Gv,  MyDSA::Vector<Road> const & eList)
// {
//     for(int i = 0; i < eList.size(); i++)
//     {
//         //std::cout << eList[i].id << std::endl;
//         G[eList[i].from-1][eList[i].to-1] = eList[i].length;
//         Gv[eList[i].from-1][eList[i].to-1] = eList[i].id ;
//         if(eList[i].isDuplex)
//         {
//             G[eList[i].to-1][eList[i].from-1] = eList[i].length;
//             Gv[eList[i].to-1][eList[i].from-1] = eList[i].id;
//         }

//     }
// }

// template <typename T>/*,typename Tv>*/
// void setG(  std::vector<std::vector<T>> & G,
//             std::vector<std::vector<T>> & G_id,
//             std::vector<std::vector<T>> & G_v,
//             std::vector<std::vector<T>> & G_sp,
//             MyDSA::Vector<Road> const & eList)
// {
//     for(int i = 0; i < eList.size(); i++)
//     {
//         //std::cout << eList[i].id << std::endl;
//         G[eList[i].from-1][eList[i].to-1] = eList[i].length;
//         G_id[eList[i].from-1][eList[i].to-1] = atoi(eList[i].id );
//         G_v[eList[i].from-1][eList[i].to-1] = eList[i].channel;
//         G_sp[eList[i].from-1][eList[i].to-1] = eList[i].speed;
//         if(eList[i].isDuplex)
//         {
//             G[eList[i].to-1][eList[i].from-1] = eList[i].length;
//             G_id[eList[i].to-1][eList[i].from-1] = eList[i].id;
//             G_v[eList[i].to-1][eList[i].from-1] = eList[i].channel;
//             G_sp[eList[i].to-1][eList[i].from-1] = eList[i].speed;
//         }
//     }
// }

// template <typename T>
// void print(std::vector<std::vector<T>> const & G)
// {
//     for(auto v : G)
//     {
//         for(auto c : v)
//         {
//             if(c == 1000000000)
//             std::cout << "-1 ";
//             else
//             std::cout << c << ' ';
//         }

//     }
// }
