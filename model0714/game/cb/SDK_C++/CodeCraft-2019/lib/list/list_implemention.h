//#pragma once
//#include "listNode.h"
#ifndef ListNodePosi
#define ListNodePosi(T) ListNode<T>* 
#endif
namespace MyDSA
{
    /*** initlization ***/

    template <typename T>
    void List<T>::init()
    {
        _size = 0;
        //an empty list only have header and trailer
        header = new ListNode<T>;        
        trailer = new ListNode<T>;        
        header->succ = trailer; header->prev = NULL;
        trailer->prev = header; trailer->succ = NULL;    
    }   
    
    template <typename T>
    void List<T>::copyNodes(ListNodePosi(T) p, int n)
    {//复制列表中p开始的n个向量
        init();
        while(n--)
        {
            insertAfter(p->data);
            p = p->succ;
        }
    }

    template <typename T>
    T List<T>::remove(ListNodePosi(T) p)
    {
        T e = p->data;
        p->prev->succ = p->succ; p->succ->prev = p->prev;
        delete p;
        _size--;
        return e;
    }

    template <typename T>
    int List<T>::clear()
    {
        int oldsize = _size;
        while (_size > 0)
            remove(header->succ);
        return oldsize;        
    }

    template <typename T>
    List<T>::~List()
    {
        clear();    
        delete header;
        delete trailer;
    }

    
    //[]
    template <typename T>
    T & List<T>::operator[] (Rank r) const
    {
        ListNodePosi(T) loca = header->succ; //first(); 
        //谜一样的报错
        //list_implemention.h:64:38: error: passing ‘const MyDSA::List<int>’ as ‘this’ argument of ‘MyDSA::ListNode<T>* MyDSA::List<T>::first() [with T = int]’ discards qualifiers [-fpermissive]
        while(r-->0)
            loca = loca->succ;
        return loca->data;
    }

    template <typename T>
    ListNodePosi(T) List<T>::insertAsFirst( T const & e)
    {
        _size++;
        return header->insertAsSucc(e);
    }

    template <typename T>
    ListNodePosi(T) List<T>::insertAsLast( T const & e)
    {
        _size++;
        return trailer->insertAsPred(e);
    }

    template <typename T>
    ListNodePosi(T) List<T>::insertAfter(ListNodePosi(T) p, T const & e)
    {
        _size++;
        return p->insertAsSucc(e);
    }

    template <typename T>
    ListNodePosi(T) List<T>::insertBefore(ListNodePosi(T) p, T const & e)
    {
        _size++;
        return p->insertAsPred(e);
    }
}