#include "bst.h"
#include <queue>
#include <functional>
#include <string>
#include <sstream>

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

BSTNode* BST::rInsert(BSTNode* currentNode, int value)
{
    if(currentNode == nullptr)
    {
        return new BSTNode(value);
    }
    else if(value < currentNode->value)
    {
        currentNode->left = rInsert(currentNode->left, value);
    }
    else if(value > currentNode->value)
    {
        currentNode->right = rInsert(currentNode->right, value);
        
    }
    return currentNode;
}

void BST::rInsert(int value)
{
    if(root==nullptr)
    {
        root = rInsert(root, value);
        return;
    }
    rInsert(root, value);
}

int BST::minValue(BSTNode* currentNode)
{
    if(currentNode == nullptr) return INT_MIN;
    if(currentNode->left == nullptr) return currentNode->value;
    minValue(currentNode->left);
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

bool BST::rContains(BSTNode* currentNode, int value)
{
    if(currentNode == nullptr) return false;
    if (currentNode->value == value) return true; //Base condition
    else if(value < currentNode->value) return rContains(currentNode->left, value);
    else return rContains(currentNode->right, value);
}

bool BST::rContains(int value)
{
    return rContains(root, value);
}

void BST::destroy(BSTNode* currentNode)
{
    if (currentNode == nullptr) return;
    if (currentNode->left) destroy(currentNode->left);
    if (currentNode->right) destroy(currentNode->right);
    delete currentNode;
}

BSTNode* BST::deleteNode(BSTNode* currentNode, int value)
{
    if(currentNode == nullptr) return nullptr;
    if(value < currentNode->value)
    {
        currentNode->left = deleteNode(currentNode->left, value);
    }
    else if(value > currentNode->value)
    {
        currentNode->right = deleteNode(currentNode->right, value);
    }
    else
    {
        if(currentNode->left == nullptr && currentNode->right == nullptr)
        {
            delete(currentNode);
            return nullptr;
        }
        else if(currentNode->left && currentNode->right == nullptr)
        {
            auto temp = currentNode->left;
            delete(currentNode);
            return temp;
        }
        else if (currentNode->right && currentNode->left == nullptr)
        {
            auto temp = currentNode->right;
            delete(currentNode);
            return temp;
        }
        else
        {
            currentNode->value = minValue(currentNode->right);
            currentNode->right = deleteNode(currentNode->right, currentNode->value);
        }
    }
    return currentNode;
}

void BST::deleteNode(int value)
{
    root = deleteNode(root, value);
}

void BST::BFS()
{
    std::queue<BSTNode*> mInternalQueue;
    mInternalQueue.push(root);
    while(!mInternalQueue.empty())
    {
        auto temp = mInternalQueue.front();
        if(temp->left) mInternalQueue.push(temp->left);
        if(temp->right) mInternalQueue.push(temp->right);
        std::cout << temp->value << " ";
        mInternalQueue.pop();
    }
}

void BST::DFSPreOrder(BSTNode* currentNode)
{
    if(currentNode == nullptr) return;
    std::cout << currentNode->value << " ";
    DFSPreOrder(currentNode->left);
    DFSPreOrder(currentNode->right);
}

void BST::DFSPreOrder()
{
    DFSPreOrder(root);
}

void BST::DFSPostOrder(BSTNode* currentNode)
{
    if(currentNode == nullptr) return;
    DFSPostOrder(currentNode->left);
    DFSPostOrder(currentNode->right);
    std::cout << currentNode->value << " ";
}

void BST::DFSPostOrder()
{
    DFSPostOrder(root);
}

void BST::DFSInOrder(BSTNode* currentNode)
{
    if(currentNode == nullptr) return;
    DFSInOrder(currentNode->left);
    std::cout << currentNode->value << " ";
    DFSInOrder(currentNode->right);
}

void BST::DFSInOrder()
{
    DFSInOrder(root);
}

// DO NOT MAKE CHANGES TO CAPTUREOUTPUT FUNCTION //
inline string captureOutput(std::function<void()> func) {
    std::stringstream buffer;
    std::streambuf* sbuf = std::cout.rdbuf();
    cout.rdbuf(buffer.rdbuf());
    func();
    cout.rdbuf(sbuf);
    return buffer.str();
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

    {
        cout << "\n----- Test: rContains in Empty Tree -----\n";
        BST bst;
        int valueToSearch = 42;
        cout << "Searching for value " << valueToSearch
             << " in an empty tree - EXPECTED: false\n";
        cout << (bst.rContains(valueToSearch) ? "FAIL\n" : "PASS\n");
    }

    {
        cout << "\n----- Test: rContains with One Element -----\n";
        BST bst;
        bst.insert(10);
        cout << "Inserting 10, then checking if it's contained - EXPECTED: true\n";
        cout << (bst.rContains(10) ? "PASS\n" : "FAIL\n");
        cout << "Checking for non-existent value 5 - EXPECTED: false\n";
        cout << (bst.rContains(5) ? "FAIL\n" : "PASS\n");
    }

    {
        cout << "\n----- Test: rContains with Multiple Elements -----\n";
        BST bst;
        bst.insert(10);
        bst.insert(5);
        bst.insert(15);
        cout << "Inserting 10, 5, 15, then checking if they're contained - EXPECTED: true\n";
        cout << (bst.rContains(10) && bst.rContains(5) && bst.rContains(15) ? "PASS\n" : "FAIL\n");
        cout << "Checking for non-existent value 1 - EXPECTED: false\n";
        cout << (bst.rContains(1) ? "FAIL\n" : "PASS\n");
    }

    {
        cout << "\n----- Test: rContains with Duplicate Insert -----\n";
        BST bst;
        bst.insert(10);
        bst.insert(10); // Duplicate insert
        cout << "Inserting 10 twice, then checking if it's contained - EXPECTED: true\n";
        cout << (bst.rContains(10) ? "PASS\n" : "FAIL\n");
        cout << "Checking for non-existent value 15 - EXPECTED: false\n";
        cout << (bst.rContains(15) ? "FAIL\n" : "PASS\n");
    }

    {
        cout << "\n----- Test: rContains with Complex Structure -----\n";
        BST bst;
        bst.insert(50);
        bst.insert(30);
        bst.insert(70);
        bst.insert(20);
        bst.insert(40);
        bst.insert(60);
        bst.insert(80);
        cout << "Inserting 50, 30, 70, 20, 40, 60, 80, then checking if they're contained - EXPECTED: true\n";
        cout << (bst.rContains(50) && bst.rContains(30) && bst.rContains(70) &&
                 bst.rContains(20) && bst.rContains(40) && bst.rContains(60) &&
                 bst.rContains(80) ? "PASS\n" : "FAIL\n");
        cout << "Checking for non-existent value 10 - EXPECTED: false\n";
        cout << (bst.rContains(10) ? "FAIL\n" : "PASS\n");
    }

    {
        cout << "\n----- Test: rInsert into Empty Tree -----\n";
        BST bst;
        int valueToInsert = 42;
        bst.rInsert(valueToInsert);
        cout << "Inserting value " << valueToInsert << " into an empty tree.\n";
        cout << "EXPECTED: Node with value 42 exists\n";
        cout << (bst.rContains(42) ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: rInsert Unique Values -----\n";
        BST bst;
        bst.rInsert(10);
        bst.rInsert(5);
        bst.rInsert(15);
        cout << "Inserting unique values 10, 5, 15.\n";
        cout << "EXPECTED: Each value is contained within the tree\n";
        cout << (bst.rContains(10) && bst.rContains(5) && bst.rContains(15) ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: rInsert Duplicate Value -----\n";
        BST bst;
        bst.rInsert(10);
        bst.rInsert(10); // Attempting duplicate insert
        cout << "Inserting value 10 twice.\n";
        // Note: rInsert does not explicitly handle duplicates; it depends on tree structure verification
        cout << "EXPECTED: Tree structure unchanged by duplicate insert\n";
        cout << (bst.rContains(10) ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: rInsert to Form Complex Structure -----\n";
        BST bst;
        // Inserting multiple values to form a more complex tree structure
        bst.rInsert(50);
        bst.rInsert(30);
        bst.rInsert(70);
        bst.rInsert(20);
        bst.rInsert(40);
        bst.rInsert(60);
        bst.rInsert(80);
        cout << "Inserting values to form a complex tree structure.\n";
        cout << "EXPECTED: All inserted values are correctly contained within the tree\n";
        cout << (bst.rContains(50) && bst.rContains(30) && bst.rContains(70) &&
                 bst.rContains(20) && bst.rContains(40) && bst.rContains(60) &&
                 bst.rContains(80) ? "PASS\n" : "FAIL\n");
    }

    // Test: Delete Node from an Empty Tree
    {
        cout << "\n----- Test: Delete Node from Empty Tree -----\n";
        BST bst;
        bst.deleteNode(42); // Attempt to delete from an empty tree
        cout << "Attempting to delete value 42 from an empty tree.\n";
        cout << (bst.getRoot() == nullptr ? "PASS\n" : "FAIL\n");
    }

    // Test: Delete Leaf Node
    {
        cout << "\n----- Test: Delete Leaf Node -----\n";
        BST bst;
        bst.rInsert(50);
        bst.rInsert(30);
        bst.rInsert(70);
        bst.rInsert(20); // Leaf node
        bst.deleteNode(20); // Deleting the leaf node
        cout << "Deleting leaf node 20.\n";
        cout << (!bst.rContains(20) ? "PASS\n" : "FAIL\n");
    }

    // Test: Delete Node with One Child
    {
        cout << "\n----- Test: Delete Node with One Child -----\n";
        BST bst;
        bst.rInsert(50);
        bst.rInsert(30);
        bst.rInsert(70);
        bst.rInsert(20); // Leaf node
        bst.rInsert(25); // Node with one child
        bst.deleteNode(20); // Deleting node with one child
        cout << "Deleting node 20, which has one child 25.\n";
        cout << (!bst.rContains(20) && bst.rContains(25) ? "PASS\n" : "FAIL\n");
    }

    // Test: Delete Node with Two Children
    {
        cout << "\n----- Test: Delete Node with Two Children -----\n";
        BST bst;
        bst.rInsert(50);
        bst.rInsert(30);
        bst.rInsert(70);
        bst.rInsert(20);
        bst.rInsert(40);
        bst.rInsert(60);
        bst.rInsert(80);
        bst.deleteNode(30); // Node with two children
        cout << "Deleting node 30, which has two children (20 and 40).\n";
        cout << (!bst.rContains(30) && bst.rContains(20) && bst.rContains(40) ? "PASS\n" : "FAIL\n");
    }

    // Test: Delete Root Node
    {
        cout << "\n----- Test: Delete Root Node -----\n";
        BST bst;
        bst.rInsert(50);
        bst.rInsert(30);
        bst.rInsert(70);
        bst.deleteNode(50); // Deleting the root node
        cout << "Deleting root node 50.\n";
        cout << (!bst.rContains(50) ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: Single Node BST -----\n";
        BST tree;
        std::string output = captureOutput([&]() {
            tree.insert(10);
            tree.BFS();
        });
        cout << "EXPECTED: 10 \n";
        cout << "RETURNED: " << output << "\n";
        cout << (output == "10 " ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: Multiple Nodes BST -----\n";
        BST tree;
        std::string output = captureOutput([&]() {
            tree.insert(10);
            tree.insert(5);
            tree.insert(20);
            tree.BFS();
        });
        cout << "EXPECTED: 10 5 20 \n";
        cout << "RETURNED: " << output << "\n";
        cout << (output == "10 5 20 " ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: Full Tree BST -----\n";
        BST tree;
        std::string output = captureOutput([&]() {
            tree.insert(10);
            tree.insert(5);
            tree.insert(20);
            tree.insert(3);
            tree.insert(7);
            tree.insert(15);
            tree.insert(25);
            tree.BFS();
        });
        cout << "EXPECTED: 10 5 20 3 7 15 25 \n";
        cout << "RETURNED: " << output << "\n";
        cout << (output == "10 5 20 3 7 15 25 " ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: Single Node BST -----\n";
        BST tree;
        std::string output = captureOutput([&]() {
            tree.insert(10);
            tree.DFSPreOrder();
        });
        cout << "EXPECTED: 10 \n";
        cout << "RETURNED: " << output << "\n";
        cout << (output == "10 " ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: Multiple Nodes BST -----\n";
        BST tree;
        std::string output = captureOutput([&]() {
            tree.insert(10);
            tree.insert(5);
            tree.insert(20);
            tree.DFSPreOrder();
        });
        cout << "EXPECTED: 10 5 20 \n";
        cout << "RETURNED: " << output << "\n";
        cout << (output == "10 5 20 " ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: Full Tree BST -----\n";
        BST tree;
        std::string output = captureOutput([&]() {
            tree.insert(10);
            tree.insert(5);
            tree.insert(20);
            tree.insert(3);
            tree.insert(7);
            tree.insert(15);
            tree.insert(25);
            tree.DFSPreOrder();
        });
        cout << "EXPECTED: 10 5 3 7 20 15 25 \n";
        cout << "RETURNED: " << output << "\n";
        cout << (output == "10 5 3 7 20 15 25 " ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: Single Node BST -----\n";
        BST tree;
        std::string output = captureOutput([&]() {
            tree.insert(10);
            tree.DFSPostOrder();
        });
        cout << "EXPECTED: 10 \n";
        cout << "RETURNED: " << output << "\n";
        cout << (output == "10 " ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: Multiple Nodes BST -----\n";
        BST tree;
        std::string output = captureOutput([&]() {
            tree.insert(10);
            tree.insert(5);
            tree.insert(20);
            tree.DFSPostOrder();
        });
        cout << "EXPECTED: 5 20 10 \n";
        cout << "RETURNED: " << output << "\n";
        cout << (output == "5 20 10 " ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: Full Tree BST -----\n";
        BST tree;
        std::string output = captureOutput([&]() {
            tree.insert(10);
            tree.insert(5);
            tree.insert(20);
            tree.insert(3);
            tree.insert(7);
            tree.insert(15);
            tree.insert(25);
            tree.DFSPostOrder();
        });
        cout << "EXPECTED: 3 7 5 15 25 20 10 \n";
        cout << "RETURNED: " << output << "\n";
        cout << (output == "3 7 5 15 25 20 10 " ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: Single Node BST -----\n";
        BST tree;
        std::string output = captureOutput([&]() {
            tree.insert(10);
            tree.DFSInOrder();
        });
        cout << "EXPECTED: 10 \n";
        cout << "RETURNED: " << output << "\n";
        cout << (output == "10 " ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: Multiple Nodes BST -----\n";
        BST tree;
        std::string output = captureOutput([&]() {
            tree.insert(10);
            tree.insert(5);
            tree.insert(20);
            tree.DFSInOrder();
        });
        cout << "EXPECTED: 5 10 20 \n";
        cout << "RETURNED: " << output << "\n";
        cout << (output == "5 10 20 " ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: Full Tree BST -----\n";
        BST tree;
        std::string output = captureOutput([&]() {
            tree.insert(10);
            tree.insert(5);
            tree.insert(20);
            tree.insert(3);
            tree.insert(7);
            tree.insert(15);
            tree.insert(25);
            tree.DFSInOrder();
        });
        cout << "EXPECTED: 3 5 7 10 15 20 25 \n";
        cout << "RETURNED: " << output << "\n";
        cout << (output == "3 5 7 10 15 20 25 " ? "PASS\n" : "FAIL\n");
    }
    return 0;
}