#include "iostream"
#include "para.h"
#include "lib/io/basicStruct.h"
#include "lib/vector/Vector.h"
#include "lib/graph/AdjMatNet.h"
#include "pfs.h"
#include "lib/io/fileread.h"
#include <stdlib.h>
#include <algorithm>
#include "tardis.h"
#include "lib/io/AnsTable.h"
#include <list>

//#include "lib/DEBUG.h"

/*
	调参 从膨胀到自闭
*/
using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
    std::cout << "Begin" << std::endl;

	if(argc < 6){
		std::cout << "please input args: carPath, roadPath, crossPath, answerPath" << std::endl;
		exit(1);
	}

	std::string carPath(argv[1]);
	std::string roadPath(argv[2]);
	std::string crossPath(argv[3]);
	std::string presetAnswerPath(argv[4]);
	std::string answerPath(argv[5]);

	std::cout << "carPath is " << carPath << std::endl;
	std::cout << "roadPath is " << roadPath << std::endl;
	std::cout << "crossPath is " << crossPath << std::endl;
	std::cout << "presetAnswerPath is " << presetAnswerPath << std::endl;
	std::cout << "answerPath is " << answerPath << std::endl;

	// TODO:read input filebuf
	// TODO:process
	// TODO:write output file

//-----------------------------------------------------



//-----------------------------------------------------

/* read txt */
    //MyDSA::Vector<Car> carList;
	MyDSA::Vector<Car> carList;
	//std::list<Car> carList;
    textread(carList,carPath,1);
	//test bug
	//print(carList);
	carList.sort();
	//print(carList);
	//std::cout<<carList[1].planTime<<std::endl;
	
	
	

    MyDSA::Vector<Cross> vList;
    textread<Cross>(vList,crossPath,1);
    //print(vList);

    MyDSA::Vector<Road> eList;
    textread<Road>(eList,roadPath,1);
    //print(eList);

	std::vector<CarPath> pAList;
	textread<CarPath>(pAList,presetAnswerPath,1);
	//print(pAList);

/* read txt end */

//-----------------------------------------------------

/* 构建基本数据结构 图、表、答案表 */

    AdjMatNet gd(vList,eList);
    //gd.print();

	TARDIS table(eList, gd);
	//table.print();

	//todo 答案表
	AnsTable presetAnstb(pAList);
	//anstb.push_back(0,1,std::vector<int> (5,0));
	//anstb.print(answerPath);
	AnsTable outAns;

//	std::vector<int> ndes{0,1,2,3};
//	print( gd.node2path(ndes) );
//	std::vector<int> path{501,502,503};
	//print( gd.path2node(gd.CrossId(1),path) );

	//delay 矩阵
    std::vector<std::vector<int> > delayMat (gd.n_v(), std::vector<int>(gd.n_v() , 0));

	//todo OD矩阵

	
/* 构建 数据结构 end*/
	int all_delay = 0;

//-------------------- process begin ---------------------------------
    //int delay_cnt = 0;
	//木有排序 先随便high
    for(int i = 0, delay = 0, delay_bk = 0; i < carList.size(); i++)
    {
		Car car = carList[i];

		delay = delayMat[ gd.CrossId(car.from) ][ gd.CrossId(car.to) ];				 // update delay delay_bk

		std::vector<int> ans;	 // path buf

		std::vector<int> pathbuf;	 // path buf
		//bool finded = false;	 // search flag

		// ------------- (这里！ 目前还是！int！) ---------
		int laste = -1;


		//delay 策略还是改一下吧 考虑上ml
		if(true == car.preset) //处理预置车
		{
			int realPt;
			presetAnstb.read(car.id,realPt,pathbuf);
			if(realPt != car.planTime)
			{
                car.planTime = realPt;
                //cout << car << endl;
			}//assert(realPt == car.planTime);
			ans = gd.path2node(gd.CrossId(car.from), pathbuf);
			do
			{
				laste = evalPath_t(gd, table, car,ans,TimeDijkPU(),true,delay); //针对BFS算法的顶点优先级更新器，这里是不是忘记更新table 了？？
				delay+=17; //delay_cnt++;
			}
			while( laste == -1 );

			outAns.push_back(car.id, car.planTime, pathbuf); //更新结果表
			//convert roadid (pathbuf) to node (ans)
		}
		else
		{
			do
			{
				
				DIJK(gd,car,table, TimeDijkPU(), delay+all_delay); //获得一刻连通树
				laste = gd.findPath_t(gd.CrossId(car.from),gd.CrossId(car.to),ans);//搜索树，获取路径存入ans， 否则返回-1
				//laste = evalPath_t(gd, table, car,ans,TimeDijkPU(),true,0);
				if(ans.size() < 2) //排除只有起点的情况  ===
                    laste = -1;

				
				//cout << laste << endl;
				if(laste < 1  )
				{
					delay+=17; //delay_cnt++;
					//cout << "delay ..." << endl;
					ans.clear(); // ===
				}
			}while (laste < 1);

            delayMat[ gd.CrossId(car.from) ][ gd.CrossId(car.to) ] = delay ; //更新delay表
	
			
			reverse(ans.begin(),ans.end()); //由起点到终点的节点序列
		}


		//update
        std::vector<int> prio;
        gd.getPrio(prio); //获取各节点的priority

		std::vector<int> PathId;

		unsigned int j =0;
        while(j < ans.size()-1)
        {
            //table._updateTARDIS(gd.CrossId(ans[j]), gd.CrossId(ans[j+1]),prio[ gd.CrossId(ans[j])], prio[ gd.CrossId(ans[j+1])] );
            //std::cout << gd.CrossId(ans[j]) << " - " << gd.CrossId(ans[j+1]) << " : from " ;
            //std::cout << prio[ gd.CrossId(ans[j])] << " to " << prio[ gd.CrossId(ans[j+1])]  << " \n" ;
            // outfile << "," << gd.roadid(ans[j],ans[j+1]);
			if(car.preset == false)
			{
				int pid = gd.roadid(ans[j],ans[j+1]); //图ID找真实ID
				PathId.push_back( pid ); //将每段路ID写入PathID
			}

            //std::cout << gd.roadid(ans[j],ans[j+1])<< ":" <<  ans[j] << " - " << (ans[j+1]) << " : from " ;
            //std::cout << prio[ (ans[j])] << " to " << prio[ (ans[j+1])]  << " \n" ;
            table._updateTARDIS((ans[j]), (ans[j+1]),prio[ (ans[j])], prio[ (ans[j+1])] );
            j++;
        }

        //LOG( prio[ans[0]] != 1000000 ,"prio" );
        if(car.preset == false)
          outAns.push_back(car.id, prio[ ans[0] ], PathId);

		if( i != 0 && i%1000 == 0 )
			table.print( std::to_string(i) + std::string (".txt") );
	}


//---------------------process end  --------------------------------

//std::cout << "------------last car : " << table.lastCar() << " total delay " << delay_cnt << std::endl;
outAns.print(answerPath); 
	return 0;  
}
