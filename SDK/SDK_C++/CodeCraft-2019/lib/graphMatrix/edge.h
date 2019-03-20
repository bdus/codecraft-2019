namespace MyDSA
{
    template <typename Te> 
    struct Edge { //边对象（为简化起见，并未严格封装）
        Te data; int weight; EType type; //数据、权重、类型
        //#(id,length,speed,channel,from,to,isDuplex)
        Edge ( Te const& d, int w ) : data ( d ), weight ( w ), type ( UNDETERMINED ) {} //构造
    };
}