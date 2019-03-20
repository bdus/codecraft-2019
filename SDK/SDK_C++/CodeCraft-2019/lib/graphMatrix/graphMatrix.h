#pragma once

#include "../vector/Vector.h"
/*
    注意Vector的
        remove 是 erase
        insert 是 push_back

*/

#include "graph.h"

#include "vertex.h"
#include "edge.h"

namespace MyDSA
{

    template <typename Tv, typename Te>
    class GraphMatrix : public Graph<Tv,Te>
    {
    private:
        Vector< Vertex<Tv> > V;             // set of Vertex
        Vector< Vector<Edge<Te> * > > E;    // set of edge 邻接矩阵（Adjacency Matrix)

    public:
        GraphMatrix() {this->n = this->e = 0;}
        ~GraphMatrix()
        {
            for(int i =0; i < this->n; i++)
                for(int j =0; j < this->n; j++)
                    delete E[i][j];                
        }
    // 顶点的基本操作：查询第i个顶点（0 <= i < n）
        virtual Tv& vertex ( int i ) { return V[i].data; } //数据
        virtual int inDegree ( int i ) { return V[i].inDegree; } //入度
        virtual int outDegree ( int i ) { return V[i].outDegree; } //出度
        virtual int firstNbr ( int i ) { return nextNbr ( i, this->n ); } //首个邻接顶点
        virtual int nextNbr ( int i, int j ) //相对于顶点j的下一邻接顶点（改用邻接表可提高效率）
        { while ( ( -1 < j ) && ( !exists ( i, --j ) ) ); return j; } //逆向线性试探
        virtual VStatus& status ( int i ) { return V[i].status; } //状态
        virtual int& dTime ( int i ) { 
            std::cout << "V[i].data : " << V[i].data  << '\n' << "V[i].dTime : " << V[i].dTime << std::endl;
            return V[i].dTime; } //时间标签dTime
        virtual int& fTime ( int i ) { return V[i].fTime; } //时间标签fTime
        virtual int& parent ( int i ) { return V[i].parent; } //在遍历树中的父亲
        virtual int& priority ( int i ) { return V[i].priority; } //在遍历树中的优先级数
    // 顶点的动态操作
        virtual int insert ( Tv const& vertex ) { //插入顶点，返回编号
            for ( int j = 0; j < this->n; j++ ) E[j].push_back ( NULL ); this->n++; //各顶点预留一条潜在的关联边
            E.push_back ( Vector<Edge<Te>*> ( this->n, this->n, ( Edge<Te>* ) NULL ) ); //创建新顶点对应的边向量
            return V.push_back ( Vertex<Tv> ( vertex ) ); //顶点向量增加一个顶点
        }
        virtual Tv remove ( int i ) { //删除第i个顶点及其关联边（0 <= i < n）
            for ( int j = 0; j < this->n; j++ ) //所有出边
                if ( exists ( i, j ) ) { delete E[i][j]; V[j].inDegree--; } //逐条删除
            E.erase ( i ); this->n--; //删除第i行
            Tv vBak = vertex ( i ); V.erase ( i ); //删除顶点i
            for ( int j = 0; j < this->n; j++ ) //所有入边
                if ( Edge<Te> * e = E[j].erase ( i ) ) { delete e; V[j].outDegree--; } //逐条删除
            return vBak; //返回被删除顶点的信息
        }
    // 边的确认操作
        virtual bool exists ( int i, int j ) //边(i, j)是否存在
        { return ( 0 <= i ) && ( i < this->n ) && ( 0 <= j ) && ( j < this->n ) && E[i][j] != NULL; }
        // 边的基本操作：查询顶点i与j之间的联边（0 <= i, j < n且exists(i, j)）
        virtual EType & type ( int i, int j ) { return E[i][j]->type; } //边(i, j)的类型
        virtual Te& edge ( int i, int j ) { return E[i][j]->data; } //边(i, j)的数据
        virtual int& weight ( int i, int j ) { return E[i][j]->weight; } //边(i, j)的权重
        // 边的动态操作
        virtual void insert ( Te const& edge, int w, int i, int j ) { //插入权重为w的边e = (i, j)
            if ( exists ( i, j ) ) return; //确保该边尚不存在
            E[i][j] = new Edge<Te> ( edge, w ); //创建新边
            this->e++; V[i].outDegree++; V[j].inDegree++; //更新边计数与关联顶点的度数
        }
        virtual Te remove ( int i, int j ) { //删除顶点i和j之间的联边（exists(i, j)）
            Te eBak = edge ( i, j ); delete E[i][j]; E[i][j] = NULL; //备份后删除边记录
            this->e--; V[i].outDegree--; V[j].inDegree--; //更新边计数与关联顶点的度数
            return eBak; //返回被删除边的信息
        } 

    };

}
