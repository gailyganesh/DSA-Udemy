#pragma once

#include <iostream>

using namespace std;

class HashTableLLNode
{
    public:
        std::string key;
        int value;
        HashTableLLNode* next;
        HashTableLLNode(std::string key, int value)
        {
            this->key= key;
            this->value = value;
            this->next = nullptr;
        }
};