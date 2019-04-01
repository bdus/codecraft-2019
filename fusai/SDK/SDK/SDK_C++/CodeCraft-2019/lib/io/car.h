
/*
#(id,from,to,speed,planTime, priority, preset)
(1001, 1, 16, 4, 1, 0, 0)
(1002, 1, 16, 4, 1, 0, 0)
(1003, 1, 16, 4, 1, 0, 0)
*/
struct Car
{
    //std::string id;
    int id;
    int from;
    int to;
    int speed;
    int planTime;
    int distance; // abs(from - to) 一开始应该是0 初赛写的时候失去理智
    bool priority;
    bool preset;

/*  为了初始化 和 赋值 重载*/
    Car () {*this = -1;}
    Car (int val) {*this = val;}
    Car (std::string line) {*this = line;}
    //Car (int id,int from, int to, int speed, int planTime) : id(id), from(from), to(to), speed(speed), planTime(planTime) {}
//    Car (std::string id,int from, int to, int speed, int planTime) : id(id), from(from), to(to), speed(speed), planTime(planTime) {}
   // Car (char * id,int from, int to, int speed, int planTime) : id(id), from(from), to(to), speed(speed), planTime(planTime) {}

    friend std::ostream & operator<< (std::ostream& o, Car const & c)
    {
        o << "c : " << c.id << ", " << c.from << ", " << c.to << ", " <<c.speed << ", " <<c.planTime << ", " << c.distance
        << ( c.priority? std::string (", priority") : std::string (" ") )
        << ( c.preset? std::string (", preset") : std::string (" ") )
         << std::endl;
        return o;
    }

    Car & operator= (std::string const& line)
    {
//        char st[50];
//        sscanf(line.c_str(),"(%[^,],%d,%d,%d,%d)",st,&this->from, &this->to, &this->speed,&this->planTime);
//        this->id = std::string(st);
        int prior=0, pres=0;
        //#(id,from,to,speed,planTime, priority, preset)
        sscanf(line.c_str(),"(%d,%d,%d,%d,%d,%d,%d)",&this->id,&this->from, &this->to, &this->speed,&this->planTime,&prior,&pres);
        this->distance = 0;//std::abs(this->to - this->from);
        this->priority = ( (prior==0)?false:true ) ;
        this->preset = ( (pres==0)?false:true );
        return *this;
    }
    Car & operator= (int const& val)
    {
        this->id = val;
        this->from = val;
        this->to = val;
        this->speed = val;
        this->planTime = val;
        this->distance = 0;
        this->priority = false;
        this->preset = false;
        return *this;
    }
    Car & operator= (Car const & c)
    {
        this->id = c.id;
        this->from = c.from;
        this->to = c.to;
        this->speed = c.speed;
        this->planTime = c.planTime;
        this->distance = c.distance;
        this->preset = c.preset;
        this->priority = c.priority;
        return *this;
    }
/*  为了排序重载 */
    bool operator== (Car const & c)
    {
        //这里需要调！！！！！！！！！
        return  ( this->from == c.from ) && (this->to == c.to) && (this->speed == c.speed) && (this->planTime == c.planTime) && (this->preset) ;//&& (this->priority);
    }
    friend bool operator < (Car const & a, Car const & b)
    {
        //return (a.speed < b.speed);// ? true: (a.distance < b.distance);
        //这里需要调！！！！！！！！！
        return  (a.preset < b.preset)? true : (a.distance/a.speed < b.distance/b.speed)?true : (a.speed < b.speed) ? true: (a.distance < b.distance) ? true : (a.planTime < b.planTime);
        //return  (a.preset < b.preset)? true : (a.priority < b.priority)? true: (a.distance/a.speed < b.distance/b.speed)?true : (a.speed < b.speed) ? true: (a.distance < b.distance) ? true : (a.planTime < b.planTime);
    }
    friend bool operator > (Car const & a, Car const & b)
    {
        return  b < a;
    }
};
