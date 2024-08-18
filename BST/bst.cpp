#include "bst.h"

using namespace std;

BST::BST()
{
    root = nullptr;
}

BST::BST(int value)
{
    root = new BSTNode(value);
}

BST::~BST()
{
    destroy(root);
}

BSTNode* BST::getRoot()
{
    return root;
}

bool BST::insert(int value)
{
    if(root==nullptr)
    {
        root = new BSTNode(value);
        return true;
    }
    auto temp = root;
    while(temp)
    {
        if(value < temp->value)
        {
            if(temp->left==nullptr)
            {
                temp->left = new BSTNode(value);
                return true;
            }
            else
            {
                temp = temp->left;
            }
        }
        else if(value > temp->value)
        {
            if(temp->right==nullptr)
            {
                temp->right = new BSTNode(value);
                return true;
            }
            else
            {
                temp = temp->right;
            }
        }
        else
        {
            return false;
        }
    }
    return false;
}

bool BST::contains(int value)
{
    auto temp = root;
    while(temp)
    {
        if(temp->value==value) return true;
        else if(value<temp->value) temp=temp->left;
        else temp=temp->right;
    }
    return false;
}

void BST::destroy(BSTNode* currentNode)
{
    if (currentNode == nullptr) return;
    if (currentNode->left) destroy(currentNode->left);
    if (currentNode->right) destroy(currentNode->right);
    delete currentNode;
}

int main()
{
    {
        cout << "\n----- Test: Insert Into Empty Tree -----\n";
        BST tree;
        cout << "Inserting value of 10:\n";
        tree.insert(10);
        cout << "Root value: " << tree.getRoot()->value << " - EXPECTED: 10\n";
        cout << (tree.getRoot()->left == nullptr && tree.getRoot()->right == nullptr ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: Insert To Left -----\n";
        BST tree;
        tree.insert(10);
        tree.insert(5);
        cout << "Root value: " << tree.getRoot()->value << " - EXPECTED: 10\n";
        cout << "Left child value: " << tree.getRoot()->left->value << " - EXPECTED: 5\n";
        cout << (tree.getRoot()->right == nullptr ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: Insert To Right -----\n";
        BST tree;
        tree.insert(10);
        tree.insert(15);
        cout << "Root value: " << tree.getRoot()->value << " - EXPECTED: 10\n";
        cout << "Right child value: " << tree.getRoot()->right->value << " - EXPECTED: 15\n";
        cout << (tree.getRoot()->left == nullptr ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: Insert Duplicate Value -----\n";
        BST tree;
        tree.insert(10);
        cout << "Inserting duplicate value 10: " << (tree.insert(10) ? "FAIL\n" : "PASS\n");
    }

    {
        cout << "\n----- Test: Insert Multiple Values -----\n";
        BST tree;
        tree.insert(10);
        tree.insert(5);
        tree.insert(15);
        tree.insert(3);
        tree.insert(8);
        tree.insert(12);
        tree.insert(18);
    
        // Verify the structure of the tree
        cout << "Verifying the structure of the tree:\n";
        cout << "Root value: " << tree.getRoot()->value << " - EXPECTED: 10 - " << (tree.getRoot()->value == 10 ? "PASS\n" : "FAIL\n");
        cout << "Left child of root: " << tree.getRoot()->left->value << " - EXPECTED: 5 - " << (tree.getRoot()->left->value == 5 ? "PASS\n" : "FAIL\n");
        cout << "Right child of root: " << tree.getRoot()->right->value << " - EXPECTED: 15 - " << (tree.getRoot()->right->value == 15 ? "PASS\n" : "FAIL\n");
        cout << "Left child of left child of root: " << tree.getRoot()->left->left->value << " - EXPECTED: 3 - " << (tree.getRoot()->left->left->value == 3 ? "PASS\n" : "FAIL\n");
        cout << "Right child of left child of root: " << tree.getRoot()->left->right->value << " - EXPECTED: 8 - " << (tree.getRoot()->left->right->value == 8 ? "PASS\n" : "FAIL\n");
        cout << "Left child of right child of root: " << tree.getRoot()->right->left->value << " - EXPECTED: 12 - " << (tree.getRoot()->right->left->value == 12 ? "PASS\n" : "FAIL\n");
        cout << "Right child of right child of root: " << tree.getRoot()->right->right->value << " - EXPECTED: 18 - " << (tree.getRoot()->right->right->value == 18 ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: Contains in Empty Tree -----\n";
        BST bst;
        int valueToSearch = 42;
        cout << "Searching for value " << valueToSearch << " in an empty tree - EXPECTED: false\n";
        cout << (bst.contains(valueToSearch) ? "FAIL\n" : "PASS\n");
    }

    {
        cout << "\n----- Test: Contains with One Element -----\n";
        BST bst;
        bst.insert(10);
        cout << "Inserting 10, then checking if it's contained - EXPECTED: true\n";
        cout << (bst.contains(10) ? "PASS\n" : "FAIL\n");
        cout << "Checking for non-existent value 5 - EXPECTED: false\n";
        cout << (bst.contains(5) ? "FAIL\n" : "PASS\n");
    }

    {
        cout << "\n----- Test: Contains with Multiple Elements -----\n";
        BST bst;
        bst.insert(10);
        bst.insert(5);
        bst.insert(15);
        cout << "Inserting 10, 5, 15, then checking if they're contained - EXPECTED: true\n";
        cout << (bst.contains(10) && bst.contains(5) && bst.contains(15) ? "PASS\n" : "FAIL\n");
        cout << "Checking for non-existent value 1 - EXPECTED: false\n";
        cout << (bst.contains(1) ? "FAIL\n" : "PASS\n");
    }

    {
        cout << "\n----- Test: Contains with Duplicate Insert -----\n";
        BST bst;
        bst.insert(10);
        bst.insert(10); // Duplicate insert
        cout << "Inserting 10 twice, then checking if it's contained - EXPECTED: true\n";
        cout << (bst.contains(10) ? "PASS\n" : "FAIL\n");
        cout << "Checking for non-existent value 15 - EXPECTED: false\n";
        cout << (bst.contains(15) ? "FAIL\n" : "PASS\n");
    }

    {
        cout << "\n----- Test: Contains with Complex Structure -----\n";
        BST bst;
        bst.insert(50);
        bst.insert(30);
        bst.insert(70);
        bst.insert(20);
        bst.insert(40);
        bst.insert(60);
        bst.insert(80);
        cout << "Inserting 50, 30, 70, 20, 40, 60, 80, then checking if they're contained - EXPECTED: true\n";
        cout << (bst.contains(50) && bst.contains(30) && bst.contains(70) && bst.contains(20) && bst.contains(40) && bst.contains(60) && bst.contains(80) ? "PASS\n" : "FAIL\n");
        cout << "Checking for non-existent value 10 - EXPECTED: false\n";
        cout << (bst.contains(10) ? "FAIL\n" : "PASS\n");
    }
    return 0;
}