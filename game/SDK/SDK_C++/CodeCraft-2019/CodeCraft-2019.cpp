#include "iostream"
#include "./lib/graphMatrix/graphMatrix.h"
#include "lib/vector/Vector.h"
#include "lib/fileread.h"
#include "lib/utility/print.h"
#include <vector>
#include "tmpG.h"
#include <fstream>

//#define _RUN
#define _DEBUG

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
    // Car as(0,0,0,0,0);
    // Car bs = {0,0,0,0,1};
    // std::cout << (bs == as) << std::endl;
    // std::cout << (bs < as) << std::endl;
    // std::cout << (bs > as) << std::endl;
    // as = "(10000, 15, 35, 6, 1)";
    // std::cout << as << std::endl;
    
    MyDSA::Vector<Car> carList;
    textread<Car>(carList,carPath,1);
    //print(carList);
    // carList.sort();
    // print(carList);

    // std::cout << carList.pop_back() << std::endl;
    /* test car end */
    
    /* Cross test */

    // Cross as(0,0,0,0,0);
    // Cross bs = {0,0,0,0,1};
    // as = "(10000, 15, 35, 6, 1)";
    // std::cout << as << std::endl;
    // std::cout << bs << std::endl;
    MyDSA::Vector<Cross> vList;
    textread<Cross>(vList,crossPath,1);
    //print(vList); 

    /* Cross test end */

    /* Road test */

    // Road as(0,0,0,0,0,0,0);
    // Road bs = {0,0,0,0,1,0,0};
    // as = "(5000, 10, 5, 1, 1, 2, 1)";
    // std::cout << as << std::endl;
    // std::cout << bs << std::endl;
    MyDSA::Vector<Road> eList;
    textread<Road>(eList,roadPath,1);
    //print(eList);

    /* Road test end */

    int num_v = vList.size();

    std::vector<std::vector<int>> G = onesG(num_v,num_v,INF);

    setG(G,eList); 

    //print(G);

    std::ofstream outfile;
    outfile.open(answerPath);
    
    outfile << "#(carId,StartTime,RoadId...)\n";

    for(int i = 0; i < carList.size(); i++)
    {
        Car car = carList[i];
        std::vector<bool> vis(num_v);
        std::vector<int> d(num_v);
        std::vector<int> pre(num_v);

        Dijkstra(num_v,car.from-1,G,vis,d,pre);
        //std::cout << "(" << car.id << "," ;
        outfile << "(" << car.id << "," ;
        DFSPrint(car.from-1,car.to-1, pre, outfile);
        //std::cout << ")\n";
        outfile << ")\n";
    }
    

    // std::vector<bool> vis(num_v);
    // std::vector<int> d(num_v);
    // std::vector<int> pre(num_v);

    // Dijkstra(num_v,15,G,vis,d,pre);
    
    // for (auto x : d)
    //     std::cout << x << " ";
    // std::cout << std::endl;

    // //输出从起点s到顶点v的最短路径
    
    // DFSPrint(15, 35, pre);
    
    // print(pre);

	return 0;
}