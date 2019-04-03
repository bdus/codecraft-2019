#include "iostream"
#include "para.h"
#include "lib/io/basicStruct.h"
#include "lib/vector/Vector.h"
#include "lib/graph/AdjMatNet.h"
#include "pfs.h"
#include "lib/io/fileread.h"
#include "lib/DEBUG.h"
#include <stdlib.h>
#include <algorithm>
#include "tardis.h"
#include "lib/io/AnsTable.h"

/* 安排预设车
		这时候沿着路径遍历本质上就是评价这条路径
		其意义在于 规划在TARDIS上 在时空上影响后车
			考虑到预设车未必就能按照 其planTime出发

				首先假设预设车没出发就一直堵在出口
			如果有大量同planTime、OD的预设车的话 其存在 视作为一条持续存在的OD流	（未得到验证）

			再假如阻滞模型能够正确估计时间
			那么就能够正确delay 将这条OD流明白的安排在TARDIS上 （未得到验证）

		于是现在的问题
			其实就是评价路径 给一个合适的delay

		那么我们依据什么评价路径
			现在的策略等于是将delay的评价交给了para中还没写出来的分类模型 与回归模型 (作用是估计时间、判断路况 避免死锁)
			并且加上一个假设：一条路径的时空子路死锁、那么这条路也死锁
			于是 我们不需要再判断一整段路如何
				对于能够绕路的 绕路
					不能绕路的 在时间上调整

			那这直觉上不是一个线性的分类
				我们要尽量减少模型参数、避免过拟合
				由于是在for循环的最里面 c*car*O(n*n)
				c直接影响了模型复杂度 因此要用简单的模型

				模型：非线性、快速、简单、收敛快
			（特征工程、设计一下loss）
		感觉也可以转化成弱监督或者含隐变量em的方法

	估计delay
		delay是在时间上调整的策略 （但是唯一的吗？)
		delay现在是XJBS的 最多加了 排序策略+指数平滑
		delay也是一个回归问题[0,n]、不过也可以看作分类[0,n]
		但目前就排序+ema cpp太难了
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

/* read txt */
    MyDSA::Vector<Car> carList;
    textread(carList,carPath,1);
    //carList.sort(); //排序需要调！
    //print(carList);

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
	//AnsTable outAns;

	//todo OD矩阵

/* 构建 数据结构 end*/

//-------------------- process begin ---------------------------------
    for(int i = 0, delay = 0; i < carList.size(); i++)	
    {

		Car car = carList[i];
		delay = 0;				 // update delay delay_bk
		std::vector<int> ans;	 // path buf
		//bool finded = false;	 // search flag

		// ------------- (这里！ 目前还是！int！) ---------
		int laste = -1;


		//delay 策略还是改一下吧 考虑上ml
		if(true == car.preset)	
		{
			int realPt;
			presetAnstb.read(car.id,realPt,ans);			
            car.planTime = realPt;
            
			do
			{
				laste = evalPath_t(gd, table, car,ans,TimeDijkPU(),false,delay);
				if(laste == -1 )
				{
					delay+=2;
				}
			}
			while( laste == -1 );			
		}
		
		reverse(ans.begin(),ans.end());

		//update
        std::vector<int> prio;
        gd.getPrio(prio);

		unsigned int j =0 ;
        while(j < ans.size()-1)
        {
            table._updateTARDIS((ans[j]), (ans[j+1]),prio[ (ans[j])], prio[ (ans[j+1])] );			
            j++;
        }
		//carList.erase(i); //这个操作复杂度很高 接下来把carList 换成 链表
	}	


	// //木有排序 先随便high
    // for(int i = 0, delay = 0; i < carList.size(); i++)
    // {
	// 	Car car = carList[i];
	// 	delay = 0;				 // update delay delay_bk
	// 	std::vector<int> ans;	 // path buf
	// 	//bool finded = false;	 // search flag

	// 	// ------------- (这里！ 目前还是！int！) ---------
	// 	int laste = -1;


	// 	//delay 策略还是改一下吧 考虑上ml
	// 	if(false == car.preset)	
	// 	{
	// 		do
	// 		{
	// 			DIJK(gd,car,table, TimeDijkPU(), delay);
	// 			laste = gd.findPath_t(gd.CrossId(car.from),gd.CrossId(car.to),ans);
	// 			if(laste == -1 )
	// 			{
	// 				delay+=3;
	// 				ans.clear();
	// 			}
	// 		}while (laste == -1);
	// 	}
	// 	reverse(ans.begin(),ans.end());

	// 	//update
    //     std::vector<int> prio;
    //     gd.getPrio(prio);

	// 	std::vector<int> path;

	// 	unsigned int j =0 ;
    //     while(j < ans.size()-1)
    //     {
    //         //table._updateTARDIS(gd.CrossId(ans[j]), gd.CrossId(ans[j+1]),prio[ gd.CrossId(ans[j])], prio[ gd.CrossId(ans[j+1])] );
    //         //std::cout << gd.CrossId(ans[j]) << " - " << gd.CrossId(ans[j+1]) << " : from " ;
    //         //std::cout << prio[ gd.CrossId(ans[j])] << " to " << prio[ gd.CrossId(ans[j+1])]  << " \n" ;
    //         // outfile << "," << gd.roadid(ans[j],ans[j+1]);
    //         // std::cout << gd.roadid(ans[j],ans[j+1])<< ":" <<  ans[j] << " - " << (ans[j+1]) << " : from " ;
    //         // std::cout << prio[ (ans[j])] << " to " << prio[ (ans[j+1])]  << " \n" ;
	// 		path.push_back( gd.roadid(ans[j],ans[j+1]) );
    //         table._updateTARDIS((ans[j]), (ans[j+1]),prio[ (ans[j])], prio[ (ans[j+1])] );			
    //         j++;
    //     }
	// 	presetAnstb.push_back(car.id,prio[0],path );
	// }


//---------------------process end  --------------------------------

std::cout << "------------last car : " << table.lastCar() << std::endl;
presetAnstb.print(answerPath);

	return 0;
}
