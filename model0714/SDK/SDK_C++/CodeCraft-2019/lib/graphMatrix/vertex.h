namespace MyDSA
{
    
    template <typename Tv>
    struct Vertex //
    {
        Tv data; int inDegree, outDegree; VStatus status; //数据、出入度数、状态
        //#(id,roadId,roadId,roadId,roadId)
        int dTime, fTime; //时间标签
        int parent; int priority; //在遍历树中的父节点、优先级数   
        
        Vertex ( Tv const& d = ( Tv ) 0 ) : //构造新顶点
            data ( d ), inDegree ( 0 ), outDegree ( 0 ), status ( UNDISCOVERED ),
            dTime ( -1 ), fTime ( -1 ), parent ( -1 ), priority ( INT_MAX ) {} //暂不考虑权重溢出
        
        // Vertex (int const & val = 0) :data ( val ), inDegree ( 0 ), outDegree ( 0 ), status ( UNDISCOVERED ),
        // dTime ( -1 ), fTime ( -1 ), parent ( -1 ), priority ( INT_MAX ) {}
    };
    
} // MyDSA
