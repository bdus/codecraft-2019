const int INF = -1;//1000000000;

//template <typename T>
void Dijkstra(int n, int s, std::vector<std::vector<int>> G, std::vector<bool>& vis, std::vector<int>& d, std::vector<int>& pre)
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
       fill(d.begin(), d.end(), INF);                         //初始化最短距离矩阵，全部为INF
 
       for (int i = 0; i < n; ++i)                            //新添加
              pre[i] = i;
 
       d[s] = 0;                                              //起点s到达自身的距离为0
       for (int i = 0; i < n; ++i)
       {
              int u = -1;                                     //找到d[u]最小的u
              int MIN = INF;                                  //记录最小的d[u]
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
                     return;
              vis[u] = true;                                  //标记u已被访问
              for (int v = 0; v < n; ++v)
              {
                     //遍历所有顶点，如果v未被访问&&u能够到达v&&以u为中介点可以使d[v]更优
                     if (vis[v] == false && d[u] + G[u][v] < d[v]) {
                           d[v] = d[u] + G[u][v];             //更新d[v]
                           pre[v] = u;                        //记录v的前驱顶点为u（新添加）
                     }
              }
       }
}

template <typename T>
void DFSPrint(int s, int v, std::vector<T> pre)
{
       if (v == s) {
              std::cout << s << " ";
              return;
       }
       DFSPrint(s, pre[v], pre);
       std::cout << v << " ";
}

template <typename T>
std::vector<std::vector<T>> onesG(int w, int h, T const &val)
{    
    //std::vector<std::vector<float>> G(num_v,std::vector<float>(num_v,INF));
    return std::vector<std::vector<T>> (w,std::vector<T>(h,val));    
}

template <typename T>
void setG(std::vector<std::vector<T>> & G, MyDSA::Vector<Road> const & eList)
{
    for(int i = 0; i < eList.size(); i++)
    {
        //std::cout << eList[i].id << std::endl;
        G[eList[i].from-1][eList[i].to-1] = eList[i].length;
        if(eList[i].isDuplex)
            G[eList[i].to-1][eList[i].from-1] = eList[i].length;
    }
}

template <typename T>
void print(std::vector<std::vector<T>> const & G)
{
    for(auto v : G)
    {
        for(auto c : v)
        {
            std::cout << c << ' ';
        }            
        std::cout << std::endl;
    }       
}