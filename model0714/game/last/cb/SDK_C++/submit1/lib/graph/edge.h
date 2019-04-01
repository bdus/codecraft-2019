

typedef enum { UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD } EType; //边在遍历树中所属的类型
//template <typename Te>
struct Edge { //边对象（为简化起见，并未严格封装）
    //std::string id;
    int id;
     int weight; EType type; //数据、权重、类型
    int length; int speed; int channel; int from; int to; bool isDuplex;
    //#(id,length,speed,channel,from,to,isDuplex)

    Edge ( )  {} //Edge ("",MYINF,MYINF,0,0,0,0,false) ;} //构造

    Edge ( int const& d, int  const& w,
        int  const& length, int  const& speed, int  const& channel, int  const& from, int  const& to, bool  const& isDuplex
     ) : id ( d ), weight ( w ), type ( UNDETERMINED ) ,
     length(length), speed(speed), channel(channel), from(from), to(to) ,isDuplex(isDuplex) {

     } //构造


};
