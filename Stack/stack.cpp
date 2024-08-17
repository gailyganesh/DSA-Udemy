#include "stack.h"
#include <string>

using namespace std;

Stack::Stack(int value) {
    mTop=new LinkedListNode(value);
    mHeight=1;
}

Stack::~Stack() {
    makeEmpty();
}

void Stack::makeEmpty()
{
    while(mTop)
    {
        auto temp = mTop;
        mTop=mTop->next;
        delete temp;
        mHeight--;
    }
}

void Stack::printStack()
{
    auto temp = mTop;
    while(temp)
    {
        std::cout << temp->value << std::endl;
        temp=temp->next;
    }
}

void Stack::printTop()
{
    if(mTop) std::cout << "Top: " << mTop->value << std::endl;
}

void Stack::printHeight()
{
    std::cout << "Height " << mHeight << std::endl;
}

int Stack::getHeight()
{
    return mHeight;
}

LinkedListNode* Stack::getTop()
{
    return mTop? mTop:nullptr;
}

int Stack::getTopValue()
{
    return mTop?mTop->value:INT_MIN;
}

void Stack::push(int value)
{
    auto newNode = new LinkedListNode(value);
    newNode->next = mTop;
    mTop = newNode;
    mHeight++;
}

int Stack::pop()
{
    if(mHeight==0) return INT_MIN;
    else
    {
        auto popped_value = mTop->value;
        auto temp = mTop;
        mTop = mTop->next;
        delete temp;
        mHeight--;
        return popped_value;
    }
}

// Helper function to check test result
    auto checkTestResult = [](bool condition) {
        cout << (condition ? "PASS" : "FAIL") << endl;
    };

int main()
{
    // Test 1: Ensure top points to newNode
    {
        cout << "\n------ Stack Test: Ensure top points to newNode ------\n";
        
        Stack stack(5);
        auto topNode = stack.getTop();
        
        cout << "Expected Top Value: 5\n";
        cout << "Actual Top Value: " << topNode->value << "\n";
        cout << "Expected Top Next: nullptr (same as 0)\n";
        cout << "Actual Top Next: " << topNode->next << "\n";
        
        checkTestResult(
            topNode->value == 5 &&
            topNode->next == nullptr
        );
    }

    // Test 2: Initialize With Value
    {
        cout << "\n------ Stack Test: Initialize With Value ------\n";
        
        Stack stack(5);
        
        cout << "Expected Top Value: 5\n";
        cout << "Actual Top Value: " << stack.getTop()->value << "\n";
        
        checkTestResult(stack.getTop()->value == 5);
    }

    // Test 3: Initialize Height
    {
        cout << "\n------ Stack Test: Initialize Height ------\n";
        
        Stack stack(5);
        
        cout << "Expected Height: 1\n";
        cout << "Actual Height: " << stack.getHeight() << "\n";
        
        checkTestResult(stack.getHeight() == 1);
    }

    // Test 4: Initialize Next to Null
    {
        cout << "\n------ Stack Test: Initialize Next to Null ------\n";
        
        Stack stack(5);
        
        cout << "Expected Top Next: nullptr (same as 0)\n";
        cout << "Actual Top Next: " << stack.getTop()->next << "\n";
        
        checkTestResult(stack.getTop()->next == nullptr);
    }
    // Test: Push Single Element
    {
        cout << "\n----- Test: Push Single Element -----\n";
        Stack stack(10);
        cout << "Initial top value: " << stack.getTop()->value << " - EXPECTED: 10\n";
        cout << "Initial height: " << stack.getHeight() << " - EXPECTED: 1\n";
        stack.push(20);
        cout << "Top value after pushing 20: " << stack.getTop()->value << " - EXPECTED: 20\n";
        cout << "Height after pushing: " << stack.getHeight() << " - EXPECTED: 2\n";
        cout << ((stack.getTop()->value == 20) && (stack.getHeight() == 2) ? "PASS\n" : "FAIL\n");
    }

    // Test: Push Multiple Elements
    {
        cout << "\n----- Test: Push Multiple Elements -----\n";
        Stack stack(1);
        stack.push(2);
        stack.push(3);
        stack.push(4);
        stack.push(5);

        auto top = stack.getTop();
        cout << "Full stack structure - EXPECTED: 5 4 3 2 1\n";
        cout << (top->value == 5 && top->next->value == 4 &&
                 top->next->next->value == 3 && top->next->next->next->value == 2 &&
                 top->next->next->next->next->value == 1 ? "PASS\n" : "FAIL\n");
    }

    // Test: Push After Make Empty
    {
        cout << "\n----- Test: Push After Make Empty -----\n";
        Stack stack(10);
        stack.push(20);
        stack.push(30);
        stack.makeEmpty();
        
        cout << "Top after makeEmpty: " << (stack.getTop() == nullptr ? "nullptr" : "not nullptr") << " - EXPECTED: nullptr\n";
        cout << "Height after makeEmpty: " << stack.getHeight() << " - EXPECTED: 0\n";
        stack.push(40);
        cout << "Top value after pushing 40: " << stack.getTop()->value << " - EXPECTED: 40\n";
        cout << "Height after pushing: " << stack.getHeight() << " - EXPECTED: 1\n";
        cout << ((stack.getTop()->value == 40) && (stack.getHeight() == 1) ? "PASS\n" : "FAIL\n");
    }

    // Test: Pop Single Element
    {
        cout << "\n----- Test: Pop Single Element -----\n";
        Stack stack(10);
        int poppedValue = stack.pop();
        cout << "Popped value: " << poppedValue << " - EXPECTED: 10\n";
        cout << "Top after pop: " << (stack.getTop() == nullptr ? "nullptr" : "not nullptr") << " - EXPECTED: nullptr\n";
        cout << "Height after pop: " << stack.getHeight() << " - EXPECTED: 0\n";
        cout << ((poppedValue == 10) && (stack.getTop() == nullptr) && (stack.getHeight() == 0) ? "PASS\n" : "FAIL\n");
    }

    // Test: Pop Multiple Elements
    {
        cout << "\n----- Test: Pop Multiple Elements -----\n";
        Stack stack(1);
        stack.push(2);
        stack.push(3);
        stack.push(4);
        stack.push(5);

        bool pass = true;
        for (int expected = 5; expected >= 1; expected--) {
            int poppedValue = stack.pop();
            int topValue = stack.getTopValue();
            int height = stack.getHeight();
            cout << "Popped value: " << poppedValue << " - EXPECTED: " << expected << "\n";
            cout << "Top value after pop: " << topValue << " - EXPECTED: " << (expected - 1 == 0 ? "INT_MIN" : to_string(expected - 1)) << "\n";
            cout << "Height after pop: " << height << " - EXPECTED: " << (expected - 1) << "\n";
            if (poppedValue != expected || topValue != (expected - 1 == 0 ? INT_MIN : expected - 1) || height != (expected - 1)) {
                pass = false;
                break;
            }
        }
        cout << (pass ? "PASS\n" : "FAIL\n");
    }

    // Test: Pop From Empty Stack
    {
        cout << "\n----- Test: Pop From Empty Stack -----\n";
        Stack stack(10);
        stack.pop(); // Pop the only element
        int poppedValue = stack.pop();
        cout << "Popped value from empty stack: " << poppedValue << " - EXPECTED: INT_MIN\n";
        cout << "Top after pop from empty stack: " << (stack.getTop() == nullptr ? "nullptr" : "not nullptr") << " - EXPECTED: nullptr\n";
        cout << "Height after pop from empty stack: " << stack.getHeight() << " - EXPECTED: 0\n";
        cout << ((poppedValue == INT_MIN) && (stack.getTop() == nullptr) && (stack.getHeight() == 0) ? "PASS\n" : "FAIL\n");
    }
    return 0;
}