/*
 * Define the struct of list node
 *
 * */
# pragma once

#ifndef NULL
#define NULL 0
#endif
//g++ -c list.h
namespace MyDSA
{

#ifndef ListNodePosi
#define ListNodePosi(T) ListNode<T>*
#endif

    typedef int Rank; // rank
    //template <typename T> struct ListNode<T>* ListNodePosi;
    template <typename T>
    struct ListNode
    {
        T data;
        ListNodePosi(T)  prev; ListNodePosi(T)  succ;

        ListNode(){}
        ListNode(T e, ListNodePosi(T)  p = NULL, ListNodePosi(T)  s = NULL) : data(e), prev(p), succ(s) {} ;

        ListNodePosi(T) insertAsPred(T const& e);
        ListNodePosi(T) insertAsSucc(T const& e);
    };
    // #undef ListNodePosi
    // template <typename T>    
    // typedef ListNode<T> * ListNodePosi;
}

#include "listnode_implemention.h"
