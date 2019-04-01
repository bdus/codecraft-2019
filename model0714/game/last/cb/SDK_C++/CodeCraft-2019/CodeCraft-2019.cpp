#include "iostream"
#include "lib/vector/Vector.h"
#include "lib/fileread.h"
#include "lib/utility/print.h"
#include <vector>
#include <fstream>
#include "para.h"
#include <map>
#include <string>
#include "tardis.h"

#include <stdio.h>
#include "lib/graph/AdjMatNet.h"

#include "lib/DEBUG.h"
#include <stdlib.h>

#include <algorithm>

#include "OD.h"


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

struct TimeDijkPU0 { //针对BFS算法的顶点优先级更新器
   virtual void operator() ( AdjMatNet * g, int uk, int v ,Car const & car,TARDIS * tb ) {
      if ( g->status ( v ) == UNDISCOVERED ) //对于uk每一尚未被发现的邻接顶点v
      {
        float weight = evalT(
            g->length(uk,v) ,
            g->channel(uk,v),
            car.speed,
            g->speed(uk,v),
            0
              );
        // std::cout << "weight " << weight << "prio" << g->priority ( uk ) << "; ";
        if ( g->priority ( v ) > g->priority ( uk ) + weight ) { //将其到起点的距离作为优先级数
            g->priority ( v ) = g->priority ( uk ) +  weight; //更新优先级（数）

            g->parent ( v ) = uk; //更新父节点
         }
      }
   }
};
struct TimeDijkPU { //针对BFS算法的顶点优先级更新器
   virtual void operator() ( AdjMatNet * g, int uk, int v ,Car const & car,TARDIS * tb ) {
      if ( g->status ( v ) == UNDISCOVERED ) //对于uk每一尚未被发现的邻接顶点v
      {
        int Nc = tb->read( g->priority(uk),uk,v);
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
        // std::cout << "weight " << weight << "prio" << g->priority ( uk ) << "; ";
        if ( g->priority ( v ) > g->priority ( uk ) + weight ) { //将其到起点的距离作为优先级数
            g->priority ( v ) = g->priority ( uk ) +  weight; //更新优先级（数）

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


int main(int argc, char *argv[])
{
    std::cout << "Begin" << std::endl;

	if(argc < 5){
		std::cout << "please input args: carPath, roadPath, crossPath, answerPath" << std::endl;
		exit(1);
	}

	std::string carPath(argv[1]);
	std::string roadPath(argv[2]);
	std::string crossPath(argv[3]);
	std::string answerPath(argv[4]);

	std::cout << "carPath is " << carPath << std::endl;
	std::cout << "roadPath is " << roadPath << std::endl;
	std::cout << "crossPath is " << crossPath << std::endl;
	std::cout << "answerPath is " << answerPath << std::endl;

	// TODO:read input filebuf
	// TODO:process
	// TODO:write output file

    // read input file
    /* test car */

    //std::vector<Car> carList;
    MyDSA::Vector<Car> carList;
    textread<Car>(carList,carPath,1);
    // print(carList);
    carList.sort();
    // print(carList);

    // std::cout << carList.pop_back() << std::endl;
    /* test car end */

    /* Cross test */

    MyDSA::Vector<Cross> vList;
    textread<Cross>(vList,crossPath,1);
    // print(vList);

    /* Cross test end */

    /* Road test */

    MyDSA::Vector<Road> eList;
    textread<Road>(eList,roadPath,1);
    // print(eList);

    /* Road test end */


    /** Graph test */


    AdjMatNet gd(vList,eList);

    // for(int i = 0; i < vList.size(); i++)
    // {
    //     for(int road : gd.Nbrs_T( vList[i].id ) )
    //     {
    //         cout << gd.roadid(
    //             gd.CrossId( vList[i].id ),
    //             gd.NbrCross(road, gd.CrossId( vList[i].id ) )
    //         ) << "== " << road <<endl;
    //     }
    // }
    //     for(int i = 0; i < vList.size(); i++)
    // {
    //     for(int road : gd.Nbrs( gd.CrossId( vList[i].id )))
    //     {
    //         cout << gd.roadid(
    //             gd.CrossId( vList[i].id ),
    //             gd.NbrCross(road, gd.CrossId( vList[i].id ) )
    //         ) << "== " << road <<endl;
    //     }
    // }

    // gd.print();

     /** Graph test end */

    /*** 时间规划表 */
    //函数功能正常！！！！！！！！！！！！！！！！！！！！！
    TARDIS table(eList, gd );
    // table.print();

    // TARDIS 扩容
    //void expandTARDIS();

    /*** 时间规划表 end  */

    /* OD 矩阵 */
     //ODMat odmat(gd, carList);

    //carList.sort();
    //print(carList);
    //print(odmat.get_dis() );
//
//   for(auto v : odmat.get_dis())
//   {
//       for(auto c : v)
//       {
//           // if(c >= 100000)
//           // std::cout << "-1 ";
//           // else
//           std::cout << c << ' ';
//       }
//       std::cout << std::endl;
//   }

    // carList.sort();
    // print(carList);

    /* OD 矩阵 end */

    /*  路径评价 函数 （有待数值优化、调参） paras.h */

    // cout << evalT(10,5,5,5,0) << endl;
    // cout << evalT(10,5,5,5,5) << endl;
    // cout << evalT(10,5,5,5,10) << endl;
    // cout << evalT(10,5,5,5,20) << endl;

    /** paras end*/

    std::ofstream outfile;
    outfile.open(answerPath);
    outfile << "#(carId,StartTime,RoadId...)\n";

    int delay = 0;
    int delay_bk = 0;

    for(int i = 0; i < carList.size(); i++)
    {
        Car car = carList[i];//[carList.size() -1 - i];
        // std::cout << car.id << " :=========from " << car.from << ", to " << car.to << "===== speed " << car.speed << "========"<< car.distance/car.speed <<"========\n";
        delay = 0;
        std::vector<int> ans;

        bool finded = false;
        int laste = -1;

        //delay_bk = delay;

        do
        {
            //一次带权遍历 更新最小树
            DIJK(gd,car,table, TimeDijkPU(), delay);
            //找树是否由 from 到 to 的通路
           //finded = gd.findPath(gd.CrossId(car.from),gd.CrossId(car.to),ans);
           laste = gd.findPath_t(gd.CrossId(car.from),gd.CrossId(car.to),ans);
            // 如果有通路 继续规划下一条 如果没有 推迟 重新规划 找是否有路
            //if(finded == false)
            if(laste == -1 )
            {
                delay+=3;
                // cout << "没找到路: " << delay << endl;
                //system("sleep 5");
                ans.clear();
            }
        } while (laste == -1);

        delay = delay*0.5 + delay_bk*0.5;


        // cout << "找到的路" << endl;

        reverse(ans.begin(),ans.end());
        // print(ans);

        //update
        std::vector<int> prio;
        gd.getPrio(prio);

        outfile << "(" << car.id << "," << car.planTime+delay;

        int j =0 ;
        while(j < ans.size()-1)
        {
            //table._updateTARDIS(gd.CrossId(ans[j]), gd.CrossId(ans[j+1]),prio[ gd.CrossId(ans[j])], prio[ gd.CrossId(ans[j+1])] );
            //std::cout << gd.CrossId(ans[j]) << " - " << gd.CrossId(ans[j+1]) << " : from " ;
            //std::cout << prio[ gd.CrossId(ans[j])] << " to " << prio[ gd.CrossId(ans[j+1])]  << " \n" ;
            outfile << "," << gd.roadid(ans[j],ans[j+1]);
            // std::cout << gd.roadid(ans[j],ans[j+1])<< ":" <<  ans[j] << " - " << (ans[j+1]) << " : from " ;
            // std::cout << prio[ (ans[j])] << " to " << prio[ (ans[j+1])]  << " \n" ;
            table._updateTARDIS((ans[j]), (ans[j+1]),prio[ (ans[j])], prio[ (ans[j+1])] );
            j++;
        }
        outfile << ")\n";
    }


    std::cout << "------------last car : " << table.lastCar() << std::endl;
    // table.print();
    // std::ofstream outfile;
    // outfile.open(answerPath);

    // outfile << "#(carId,StartTime,RoadId...)\n";



	return 0;
}
