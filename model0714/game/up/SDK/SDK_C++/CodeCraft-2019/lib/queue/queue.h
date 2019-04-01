/*
 * The implemention of queue
 *
 * use a dual linked list to implement queue
 *
 * */
#include "../list/list.h"

namespace MyDSA 
{
    template <typename T>
    class Queue : public List<T>
    {
    public:
        // use the trail of list as queue entry
        void enqueue(T const & e) { this->insertAsLast(e); }
        // use the header of list as queue exit
        T dequeue() {return this->remove(this->first()); }
        //
        T & front() {return this->front()->data; }

    };
}
