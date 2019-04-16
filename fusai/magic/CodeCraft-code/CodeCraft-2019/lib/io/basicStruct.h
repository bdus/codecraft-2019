#pragma once
#include <iostream>
#include <sstream>
#include <vector>
// #ifndef abs
// #define abs(x) ((x)?x:-x)
// #endif

#include "car.h"
#include "carPath.h"

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
