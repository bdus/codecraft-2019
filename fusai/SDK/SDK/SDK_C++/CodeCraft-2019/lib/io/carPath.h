#pragma once

/*
定义个carpath
主要是为了存presetAnswer.txt
后面结果规划表能不能用得到看情况吧
有个问题就是查找的时候，得多建一个map 很讨厌

一个carpath只存一条路径
#(carId,StartTime,RoadId...)

*/
struct CarPath
{
    int id;
    int startTime;
    std::vector<int> path;//可以按照路的id存 也可以按照节点id存 先约定好 不要搞混了

    CarPath () {*this = -1;}
    CarPath (int val) {*this = val;}
    CarPath (std::string line) {*this = line;}

//  这里有bug
//    friend std::ostream & operator<< (std::ostream& o, CarPath const & c)
//    {
//        o << "c : " << c.id << ", " << c.startTime << " | path : ";
//     //if(path->length() > 0)
////     for(int i = 0; i < path.size(); i++)
////     {
////          o << path[]i]  << " ";
////     }
////       o << " |< " << std::endl;
//        return o;
//    }

    CarPath & operator= (std::string const& line)
    {//#(carId,StartTime,RoadId...)
        //std::istringstream stream(line);
        int num = 0;
        int cnt = 0;

        for(unsigned int n =0; n < line.length(); n++)
        {
            if( line[n] >= '0' && line[n] <='9')
            {
                num = num*10 + line[n]-'0';
            }
            else
            {
                if( num!=0 )
                {
                    if(cnt == 0)
                    {
                        this->id = num;
                        cnt++;
                    }
                    else if(cnt == 1)
                    {
                        this->startTime = num;
                        cnt++;
                    }
                    else
                    {
                        //std::cout << num << " ";
                        path.push_back(num);
                    }
                }
                num=0;
            }
        }

       return *this;
    }
    CarPath & operator= (int const& val)
    {
        this->id = 0;
        this->startTime = 0;
        this->path.clear();
        return *this;
    }
    CarPath & operator= (CarPath const & c)
    {
        this->id = c.id;
        this->startTime = c.startTime ;
        this->path = c.path;
        return *this;
    }
};
