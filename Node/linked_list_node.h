#include <iostream>

using namespace std;

class LinkedListNode { 
    public:
        int value;
        LinkedListNode* next;

        LinkedListNode(int value) {
            this->value = value;
            next = nullptr;
        }
}; 