#pragma once

#include <iostream>
#include "bst_node.h"

class BST
{
    private:
        BSTNode* root;
        bool rContains(BSTNode* currentNode, int value);
        BSTNode* rInsert(BSTNode* currentNode, int value);
        int minValue(BSTNode* currentNode);
        BSTNode* deleteNode(BSTNode* currentNode, int value);
        void DFSPreOrder(BSTNode* currentNode);
        void DFSPostOrder(BSTNode* currentNode);
        void DFSInOrder(BSTNode* currentNode);

    public:
        BST();
        BST(int value);
        ~BST();
        BSTNode* getRoot();
        bool insert(int value);
        bool contains(int value);
        bool rContains(int value);
        void rInsert(int value);
        void destroy(BSTNode* node);
        void deleteNode(int value);
        void BFS(); //Breadth first search
        void DFSPreOrder(); // Depth first search pre-order
        void DFSPostOrder(); // Depth first search post-order
        void DFSInOrder(); // Depth first search In-order
};