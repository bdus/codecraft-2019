#include "iostream"
#include "./lib/graphMatrix/graphMatrix.h"
#include "lib/vector/Vector.h"
#include "lib/fileread.h"
#include "lib/utility/print.h"
//#include <vector>
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
    Car as(0,0,0,0,0);
    Car bs = {0,0,0,0,1};
    std::cout << (bs == as) << std::endl;
    std::cout << (bs < as) << std::endl;
    std::cout << (bs > as) << std::endl;
    as = "(10000, 15, 35, 6, 1)";
    std::cout << as << std::endl;
    
    MyDSA::Vector<Car> carList;
    textread<Car>(carList,carPath,1);
    print(carList);
    carList.sort();
    print(carList);
        
    std::cout << carList.pop_back() << std::endl;
    

        
        
    //std::vector<Car> carList;
    //MyDSA::GraphMatrix<Cross,Road> dg;
    

   	// MyDSA::GraphMatrix<char, int> dg;
    // char vertex = 'a';
    // dg.insert(vertex);
    // dg.insert('b');
    // dg.insert('c');
    // int edg = 10;
            
    // dg.insert(edg,10,0,1);
    // dg.insert(edg,10,0,2);
    // for (int i = 0; i < 3; i++)
    // {
    //     for(int j = 0; j < 3; j++)
    //         if(dg.exists(i,j)) 
    //             std::cout << dg.edge(i,j) << ' ';
    //         else
    //             std::cout << "  ";
    //     std::cout << std::endl;
    // }


    // std::cout << "bfs" << std::endl;
    // dg.bfs(0);

    // std::cout << "bfs2" << std::endl;
    // dg.bfs(0);

    // std::cout << "dijk" << std::endl;
    // dg.dijkstra(0);
	
	
	return 0;
}