#pragma once

#include <iostream>

using namespace std;

class DoublyLinkedListNode { 
    public:
        int value;
        DoublyLinkedListNode* next;
        DoublyLinkedListNode* prev;

        DoublyLinkedListNode(int value) {
            this->value = value;
            next = nullptr;
            prev = nullptr;
        }
};