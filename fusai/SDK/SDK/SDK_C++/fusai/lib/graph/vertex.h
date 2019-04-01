
typedef enum { UNDISCOVERED, DISCOVERED, VISITED } VStatus; //顶点状态
//template <typename Tv>
struct Vertex //
{
    //std::string data;
    int id;
    int inDegree, outDegree; VStatus status; //数据、出入度数、状态
    std::vector<int> roads;
    //#(id,roadId,roadId,roadId,roadId)
    int dTime, fTime; //时间标签
    int parent; int priority; //在遍历树中的父节点、优先级数

    Vertex ( int const& d = -1 ) : //构造新顶点
        id ( d ), inDegree ( 0 ), outDegree ( 0 ), status ( UNDISCOVERED ),
        dTime ( -1 ), fTime ( -1 ), parent ( -1 ), priority ( MYINF ) {} //暂不考虑权重溢出  应该首先定义MYINF

    Vertex ( int const& d, int const& r1, int const& r2, int const& r3, int const& r4 ) : //构造新顶点
        id ( d ), inDegree ( 0 ), outDegree ( 0 ), status ( UNDISCOVERED ),
        dTime ( -1 ), fTime ( -1 ), parent ( -1 ), priority ( MYINF ) {
            if(r1 != -1) roads.push_back(r1);
            if(r2 != -1) roads.push_back(r2);
            if(r3 != -1) roads.push_back(r3);
            if(r4 != -1) roads.push_back(r4);
        } //暂不考虑权重溢出
//

};
