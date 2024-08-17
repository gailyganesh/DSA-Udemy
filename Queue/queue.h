#pragma once

#include <iostream>
#include "linked_list_node.h"


//Queue implementation here done with linked list we can't do with vector
//because it is FIFO so we need to add in one end and remove from another
//so in vector add or remove at the first is O(n)
class Queue
{
    private:
        LinkedListNode* mFirst;
        LinkedListNode* mLast;
        int mLength;
    public:
        Queue(int value);
        ~Queue();
        void printQueue();
        int getLength();
        LinkedListNode* getFirst();
        LinkedListNode* getLast();
        void makeEmpty();
        void enqueue(int value);
        int dequeue();
        bool isEmpty();
};