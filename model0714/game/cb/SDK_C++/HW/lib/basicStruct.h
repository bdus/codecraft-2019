#pragma once

// #ifndef abs
// #define abs(x) ((x)?x:-x)
// #endif


struct Car
{//#(id,from,to,speed,planTime)
    //std::string id;
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
//    Car (std::string id,int from, int to, int speed, int planTime) : id(id), from(from), to(to), speed(speed), planTime(planTime) {}
   // Car (char * id,int from, int to, int speed, int planTime) : id(id), from(from), to(to), speed(speed), planTime(planTime) {}

    friend std::ostream & operator<< (std::ostream& o, Car const & c)
    {
        o << "c : " << c.id << ", " << c.from << ", " << c.to << ", " <<c.speed << ", " <<c.planTime << ", " << c.distance << std::endl;
        return o;
    }

    Car & operator= (std::string const& line)
    {
//        char st[50];
//        sscanf(line.c_str(),"(%[^,],%d,%d,%d,%d)",st,&this->from, &this->to, &this->speed,&this->planTime);
//        this->id = std::string(st);
        sscanf(line.c_str(),"(%d,%d,%d,%d,%d)",&this->id,&this->from, &this->to, &this->speed,&this->planTime);
        this->distance = std::abs(this->to - this->from);
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
        return *this;
    }
    Car & operator= (Car const & c)
    {
        this->id = c.id;
        this->from = c.from;
        this->to = c.to;
        this->speed = c.speed;
        this->planTime = c.planTime;
        this->distance = abs(c.to - c.from);
        return *this;
    }
/*  为了排序重载 */
    bool operator== (Car const & c)
    {
        return (this->distance == c.distance) && (this->speed == c.speed) && (this->planTime == c.planTime);
    }
    friend bool operator < (Car const & a, Car const & b)
    {
        //return (a.speed < b.speed);// ? true: (a.distance < b.distance);
        return  (a.planTime < b.planTime)? true : (a.speed < b.speed) ? true: (a.distance < b.distance);
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
    int count;

/*  为了初始化 和 赋值 重载*/
    Cross () {*this = -1;}
    Cross (int val) {*this = val;}
    Cross (std::string line) {*this = line;}
    Cross (int id, int r1, int r2, int r3, int r4) : id(id), roadId1(r1), roadId2(r2), roadId3(r3), roadId4(r4) {count=0;}
    friend std::ostream & operator<< (std::ostream& o, Cross const & c)
    {
        o << "c : " << c.id << ", " << c.roadId1 << ", " << c.roadId2 << ", " <<c.roadId3 << ", " <<c.roadId4 << std::endl;
        return o;
    }

    Cross & operator= (std::string const& line)
    {//#(id,roadId,roadId,roadId,roadId)
        sscanf(line.c_str(),"(%d,%d,%d,%d,%d)",&this->id,&this->roadId1, &this->roadId2, &this->roadId3,&this->roadId4);
        this->count = 0;
        return *this;
    }
    Cross & operator= (int const& val)
    {
        this->id = 0;
        this->roadId1 = -1;
        this->roadId2 = -1;
        this->roadId3 = -1;
        this->roadId4 = -1;
        this->count = 0;
        return *this;
    }
    Cross & operator= (Cross const & c)
    {
        this->id = c.id;
        this->count = c.count;
        this->roadId1 = c.roadId1;
        this->roadId2 = c.roadId2;
        this->roadId3 = c.roadId3;
        this->roadId4 = c.roadId4;
        return *this;
    }

};

struct Road
{//#(id,length,speed,channel,from,to,isDuplex)
     //std::string id;
     int id;
    int length;
    int speed;
    int channel;
    int from;
    int to;
    bool isDuplex;
    int count;

/*  为了初始化 和 赋值 重载*/
    Road () {*this = -1;}
    Road (int val) {*this = val;}
    Road (std::string line) {*this = line;}
    Road(int id, int le, int sp, int ch, int fr, int to, bool isD) : id(id), length(le), speed(sp), channel(ch), from(fr), to(to), isDuplex(isD) {}
    //Road(std::string id, int le, int sp, int ch, int fr, int to, bool isD) : id(id), length(le), speed(sp), channel(ch), from(fr), to(to), isDuplex(isD) {}
    //Road(char * id, int le, int sp, int ch, int fr, int to, bool isD) : id(std::string(id)), length(le), speed(sp), channel(ch), from(fr), to(to), isDuplex(isD) {}
    friend std::ostream & operator<< (std::ostream& o, Road const & c)
    {
        o << "c : " << c.id << ", " << c.length << ", " << c.speed << ", " <<c.channel << ", " <<c.from  << ", " <<c.to <<", " <<c.isDuplex <<  ", " <<c.count << std::endl;
        return o;
    }

    Road & operator= (std::string const& line)
    {//#(id,length,speed,channel,from,to,isDuplex)
        int status;
//        char st[50];
//        sscanf(line.c_str(),"(%[^,],%d,%d,%d,%d,%d,%d)",st,&this->length, &this->speed, &this->channel,&this->from,&this->to,&status);
//        this->id = std::string(st);
        sscanf(line.c_str(),"(%d,%d,%d,%d,%d,%d,%d)",&this->id,&this->length, &this->speed, &this->channel,&this->from,&this->to,&status);
        this->isDuplex = (status==0)?false:true;
        this->count = 0;
        return *this;
    }
    Road & operator= (int const& val)
    {
        //this->id = "";
        this->id = 0;
        this->length = 0;
        this->speed = 0;
        this->channel = 0;
        this->from = 0;
        this->to = 0;
        this->isDuplex = 0;
        this->count = 0;
        return *this;
    }
    Road & operator= (Road const & c)
    {
        this->id = c.id;
        this->length = c.length;
        this->speed = c.speed;
        this->channel = c.channel;
        this->from = c.from;
        this->to = c.to;
        this->isDuplex = c.isDuplex;
        this->count = c.count;
        return *this;
    }

};
