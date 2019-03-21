#ifndef abs
#define abs(x) ((x>=0)?x:-x)
#endif

struct Car
{//#(id,from,to,speed,planTime)
    int id;
    int from;
    int to;
    int speed;
    int planTime;
    int distance; // abs(from - to)

/*  为了初始化 和 赋值 重载*/

    //Car () : id(-1), from(-1), to(-1), speed(-1), planTime(-1) {}
    Car () {*this = -1;}
    //Car (int val) : id(val), from(val), to(val), speed(val), planTime(val) {}
    Car (int val) {*this = val;}
    Car (std::string line) {*this = line;}
    Car (int id,int from, int to, int speed, int planTime) : id(id), from(from), to(to), speed(speed), planTime(planTime) {}   

    friend std::ostream & operator<< (std::ostream& o, Car const & c)
    {
        o << "c : " << c.id << ", " << c.from << ", " << c.to << ", " <<c.speed << ", " <<c.planTime << std::endl; 
        return o;
    }


    Car & operator= (std::string const& line)
    {
        sscanf(line.c_str(),"(%d,%d,%d,%d,%d)",&this->id,&this->from, &this->to, &this->speed,&this->planTime);
        this->distance = abs(this->from - this->to);
    }
    Car & operator= (int const& val)
    {
        this->id = val;
        this->from = val;
        this->to = val;
        this->speed = val;
        this->planTime = val;
        this->distance = 0;
    }
    Car & operator= (Car const & c)
    {
        this->id = c.id;
        this->from = c.from;
        this->to = c.to;
        this->speed = c.speed;
        this->planTime = c.planTime;
        this->distance = abs(c.from - c.to);
    }
/*  为了排序重载 */
    bool operator== (Car const & c)
    {
        return (this->distance == c.distance) && (this->speed == c.speed) && (this->planTime == c.planTime);
    }    
    friend bool operator < (Car const & a, Car const & b)
    {
        return  (a.planTime < b.planTime) || (a.distance < b.distance) || (a.speed < b.speed) ;
    }
    friend bool operator > (Car const & a, Car const & b)
    {
        return  b < a;
    }
};
// std::ostream & operator<< (std::ostream& o, Car const & c)
// {
//     o << "c : " << c.id << ", " << c.from << ", " << c.to << ", " <<c.speed << ", " <<c.planTime << std::endl; 
//     return o;
// }

struct Cross
{//#(id,roadId,roadId,roadId,roadId)
    int id;
    int roadId1;
    int roadId2;
    int roadId3;
    int roadId4;
    Cross(int id, int r1, int r2, int r3, int r4) : id(id), roadId1(r1), roadId2(r2), roadId3(r3), roadId4(r4) {}
};

struct Road
{//#(id,length,speed,channel,from,to,isDuplex)
    int id;
    int length;
    int speed;
    int channel;
    int from;
    int to;
    bool isDuplex;
    Road(int id, int le, int sp, int ch, int fr, int to, bool isD) : id(id), length(le), speed(sp), channel(ch), from(fr), to(to), isDuplex(isD) {}
};
