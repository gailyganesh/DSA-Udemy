#pragma once

#include <iostream>

using namespace std;

class BSTNode { 
    public:
        int value;
        BSTNode* left;
        BSTNode* right;

        BSTNode(int value) {
            this->value = value;
            left = nullptr;
            right = nullptr;
        }
};