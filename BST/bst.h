#pragma once

#include <iostream>
#include "bst_node.h"


//BST implementation here done with linked list we can also do with vector
//remember always point nullptr towards end
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