#pragma once

#include <iostream>
#include "doubly_linked_list_node.h"

class DoublyLinkedList
{
    private:
        DoublyLinkedListNode* mHead;
        DoublyLinkedListNode* mTail;
        int mLength;
    public:
        DoublyLinkedList(int value);
        ~DoublyLinkedList();
        void printList();
        void printHead();
        void printTail();
        void printLength();
        DoublyLinkedListNode* getHead();
        DoublyLinkedListNode* getTail();
        int getLength();
        void makeEmpty();

        //Here it is O(1) but in STL we have std::forward_list where we don't have mTail so it is O(n)
        void append(int value);
        //O(n) because in C++ std::list is used for to represent this but it won't have tail
        void deleteLast();
        //O(1)
        void prepend(int value);
        //O(1)
        void deleteFirst();

        //O(n)
        DoublyLinkedListNode* get(int index);
        //O(n)
        bool set(int index, int value);

        //O(n)
        bool insert(int index, int value);
        //O(n)
        void deleteNode(int index);

/************************ leetcode problems ***************************************/
        void swapFirstLast();
        void reverse();
        bool isPalindrome();
        void swapPairs();
};