#pragma once

#include <iostream>
#include "linked_list_node.h"


//Stack implementation here done with linked list we can also do with vector
//remember always point nullptr towards end
class Stack
{
    private:
        LinkedListNode* mTop;
        int mHeight;
    public:
        Stack(int value);
        ~Stack();
        void printStack();
        void printTop();
        void printHeight();
        int getHeight();
        LinkedListNode* getTop();
        int getTopValue();
        void makeEmpty();
        void push(int value);
        int pop();
};