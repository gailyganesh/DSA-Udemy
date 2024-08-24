#pragma once

#include <iostream>
#include "bst_node.h"

class BST
{
    private:
        BSTNode* root;
    public:
        BST();
        BST(int value);
        ~BST();
        BSTNode* getRoot();
        bool insert(int value);
        bool contains(int value);
        void destroy(BSTNode* node);
};