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
#include <iterator>
#include <list>
#include "isINF.h"


/*

                膨胀变形
                保持理智

                加了排序
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
    //MyDSA::Vector<Car> carList;
    std::vector<Car> carList;
    textread(carList,carPath,1);
    std::sort(carList.begin(),carList.end());
    //carList.sort(); //排序需要调！
    //print(carList);
//    std::list<Car> carList;
//    std::copy(carVector.begin(),carVector.end(),std::back_inserter(carList));


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

	TARDIS table(eList, &gd);
	//table.print();

	//todo 答案表
	AnsTable presetAnstb(pAList);
	//anstb.push_back(0,1,std::vector<int> (5,0));
	//anstb.print(answerPath);
	AnsTable outAns;

	//delay 矩阵
    std::vector<std::vector<int> > delayMat1 (gd.n_v(), std::vector<int>(gd.n_v() , 0));
    std::vector<std::vector<int> > delayMat2 (gd.n_v(), std::vector<int>(gd.n_v() , 0));
    std::vector<std::vector<int> > delayMat3 (gd.n_v(), std::vector<int>(gd.n_v() , 0));

    //  status
    INFTab staTable(&table);
    //print(staTable);
//    std::cout << table.width() << std::endl;
//    std::cout <<  staTable.isINF(0,1,5) << std::endl;
//       staTable.INFThis(0,1,5);
//       staTable.INFThis(0,1,6);
//       staTable.INFThis(0,1,7);
//    std::cout <<  staTable.isINF(0,1,5) << std::endl;
//    std::cout <<  staTable.findSpace(0,1,5) << std::endl;

/* 构建 数据结构 end*/

    int tmp = 0;
    int delay_cnt = 0;
	//加了排序
    for(int i = 0, delay = 0, delay_bk = 0; i < carList.size(); i++)
    {
		Car car = carList[i];
		std::vector<int> ans;	 // path buf
		std::vector<int> pathbuf;	 // path buf
		//bool finded = false;	 // search flag
		int gfrom = gd.CrossId(car.from) ;
		int gto = gd.CrossId(car.to) ;

		// ------------- (这里！ 目前还是！int！) ---------
		int laste = -1;

		//delay 策略
		if(true == car.preset)
		{
            delay = delayMat1[ gfrom ][ gto ];
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
				laste = evalPath_t(gd, table, car,ans,TimeDijkPU(),true,delay);
				if(laste < 0)
				{
                    staTable.INFThis( ans[0], ans[1] , (car.planTime+delay) );
                    //delay += 3;
                    delay =  max(delay+3, staTable.findSpace(ans[0],ans[1],car.planTime+delay) ) ;
                    delay_cnt++;
				}
				else
				{
                    break;
				}
			}while( laste == -1 );
			delayMat1[ gd.CrossId(car.from) ][ gd.CrossId(car.to) ] = delay;

			outAns.push_back(car.id, car.planTime, pathbuf);
			//convert roadid (pathbuf) to node (ans)
		}
		else if(true == car.priority)
		{
            delay = delayMat2[ gd.CrossId(car.from) ][ gd.CrossId(car.to) ];
            //delay =  max(delay, findSpace(gfrom,gto,car.planTime+delay ,&table,staTable) ) ;
			do
			{
				DIJK(gd,car,table, TimeDijkPU(), delay);
				laste = gd.findPath_t(gd.CrossId(car.from),gd.CrossId(car.to),ans);
				reverse(ans.begin(),ans.end());


				if(ans.size() < 2)
				{
				    laste = -1;
				    tmp++;
                }

				//cout << laste << endl;
				if(laste < 1  )
				{
                    tmp--;
                    assert( tmp == 0);
                    //print(ans);
                    //std::cout << gfrom << "," << gto << std::endl;
					//assert( (gfrom == ans[0]) );
					//staTable.INFThis(gfrom,ans[1], (car.planTime+delay) );
					delay += 3;
					//delay =  max(delay+3, staTable.findSpace(gfrom,ans[1],car.planTime+delay) ) ;

					 delay_cnt++;
					//cout << "delay ..." << endl;
					ans.clear();
				}
			}while (laste < 1);
            delayMat2[ gd.CrossId(car.from) ][ gd.CrossId(car.to) ] = delay ;
		}
		else
		{
            delay = delayMat3[ gd.CrossId(car.from) ][ gd.CrossId(car.to) ];
            //delay =  max(delay, findSpace(gfrom,gto,car.planTime+delay,&table,staTable) ) ;
			do
			{
				DIJK(gd,car,table, TimeDijkPU(), delay);
				laste = gd.findPath_t(gd.CrossId(car.from),gd.CrossId(car.to),ans);
				//laste = evalPath_t(gd, table, car,ans,TimeDijkPU(),true,0);
				if(ans.size() < 2)
                    laste = -1;
				//cout << laste << endl;
				if(laste < 1  )
				{
					delay+=3;
					//delay =  max(delay, findSpace(gfrom,gto,car.planTime+delay,&table,staTable) ) ;
					delay_cnt++;
					//cout << "delay ..." << endl;
					//INFThis(gfrom,gto, (car.planTime+delay) ,&table,staTable);
					ans.clear();
				}
			}while (laste < 1);
            delayMat3[ gd.CrossId(car.from) ][ gd.CrossId(car.to) ] = delay ;
			reverse(ans.begin(),ans.end());
		}

		//update
        std::vector<int> prio;
        gd.getPrio(prio);

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
				int pid = gd.roadid(ans[j],ans[j+1]);
				PathId.push_back( pid );
			}

            //std::cout << gd.roadid(ans[j],ans[j+1])<< ":" <<  ans[j] << " - " << (ans[j+1]) << " : from " ;
            //std::cout << prio[ (ans[j])] << " to " << prio[ (ans[j+1])]  << " \n" ;
            table._updateTARDIS((ans[j]), (ans[j+1]),prio[ (ans[j])], prio[ (ans[j+1])] );
            j++;
        }

        LOG( prio[ans[0]] != 1000000 ,"prio" );
        if(car.preset == false)
          outAns.push_back(car.id, prio[ ans[0] ], PathId);

        #ifndef _ECHOOFF
		if( i != 0 && i%1000 == 0 )
			table.print( std::string ("bin/")  + std::to_string(i) + std::string (".txt") );
        #endif // _ECHOOFF
	}

//---------------------process end  --------------------------------

std::cout << "------------last car : " << table.lastCar() << " total delay " << delay_cnt << std::endl;
std::cout << "para0 " <<  para0 << ", para1 " << para1
        << ", para2" << para2
        << ", para3" << para3
        << ", para4" << para4
        << ", th1" << th1
        << ", th2" << th2
        << ", th3" << th3
        << std::endl;
outAns.print(answerPath);

//table.print();
	return 0;
}
