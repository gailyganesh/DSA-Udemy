#include "stack.h"
#include <string>
#include <vector>
#include <stack>

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

/************************ leetcode problems ***************************************/
string reverseString(const string& str) {
    //   +=====================================================+
    //   |                 WRITE YOUR CODE HERE                |
    //   | Description:                                        |
    //   | - This function reverses the input string 'str'.    |
    //   | - Uses a stack to hold the characters.              |
    //   | - Pops from stack and appends to 'reversedString'.  |
    //   | - Return type: string                               |
    //   |                                                     |
    //   | Tips:                                               |
    //   | - Use a stack to hold each character of the string. |
    //   | - Push each character of 'str' onto the stack.      |
    //   | - Pop from the stack and append to 'reversedString' |
    //   |   until the stack is empty.                         |
    //   | - Return the reversed string.                       |
    //   | - Check output from Test.cpp in "User logs".        |
    //   +=====================================================+

    std::vector<char>stack;
    for(auto character:str)
    {
        stack.push_back(character);
    }
    std::string reverse="";
    while(!stack.empty())
    {
        reverse+=stack.back();
        stack.pop_back();
    }
    return reverse;
}

bool isBalancedParentheses(const string& parentheses) {
    int openParentheses=0;
    for(auto character:parentheses)
    {
        if(character=='(') openParentheses+=1;
        if(character==')') openParentheses-=1;
        if(openParentheses<0) return false;
    }
    return (openParentheses==0) ? true: false;
}

void sortStack(stack<int>& inputStack) {
    stack<int> additionalStack;
    while(!inputStack.empty())
    {
        additionalStack.push(inputStack.top());
        inputStack.pop();
    }

    while(!additionalStack.empty())
    {
        int temp=additionalStack.top();
        additionalStack.pop();
        while(!inputStack.empty()&&temp>inputStack.top())
        {
            additionalStack.push(inputStack.top());
            inputStack.pop();
        }
        inputStack.push(temp);
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

    cout << "\n----- Test: Empty Parentheses -----\n";
    {
        string input = "";
        cout << "Input: \"" << input << "\"\n";
        cout << "Output: " << (isBalancedParentheses(input) ? "Balanced" : "Unbalanced") << " - EXPECTED: Balanced\n";
        cout << (isBalancedParentheses(input) ? "PASS\n" : "FAIL\n");
    }

    cout << "\n----- Test: Balanced Parentheses -----\n";
    {
        string inputs[] = {"()", "(())", "(()(()))"};
        for (const string &input : inputs) {
            cout << "Input: \"" << input << "\"\n";
            cout << "Output: " << (isBalancedParentheses(input) ? "Balanced" : "Unbalanced") << " - EXPECTED: Balanced\n";
            cout << (isBalancedParentheses(input) ? "PASS\n" : "FAIL\n");
        }
    }

    cout << "\n----- Test: Unbalanced Opening Parentheses -----\n";
    {
        string inputs[] = {"(", "(()", "((())"};
        for (const string &input : inputs) {
            cout << "Input: \"" << input << "\"\n";
            cout << "Output: " << (isBalancedParentheses(input) ? "Balanced" : "Unbalanced") << " - EXPECTED: Unbalanced\n";
            cout << (!isBalancedParentheses(input) ? "PASS\n" : "FAIL\n");
        }
    }

    cout << "\n----- Test: Unbalanced Closing Parentheses -----\n";
    {
        string inputs[] = {")", "())", "(()))"};
        for (const string &input : inputs) {
            cout << "Input: \"" << input << "\"\n";
            cout << "Output: " << (isBalancedParentheses(input) ? "Balanced" : "Unbalanced") << " - EXPECTED: Unbalanced\n";
            cout << (!isBalancedParentheses(input) ? "PASS\n" : "FAIL\n");
        }
    }

    cout << "\n----- Test: Mixed Parentheses -----\n";
    {
        string balancedInput = "()()";
        string unbalancedInputs[] = {"()(", "())()"};

        cout << "Input: \"" << balancedInput << "\"\n";
        cout << "Output: " << (isBalancedParentheses(balancedInput) ? "Balanced" : "Unbalanced") << " - EXPECTED: Balanced\n";
        cout << (isBalancedParentheses(balancedInput) ? "PASS\n" : "FAIL\n");

        for (const string &input : unbalancedInputs) {
            cout << "Input: \"" << input << "\"\n";
            cout << "Output: " << (isBalancedParentheses(input) ? "Balanced" : "Unbalanced") << " - EXPECTED: Unbalanced\n";
            cout << (!isBalancedParentheses(input) ? "PASS\n" : "FAIL\n");
        }
    }

    cout << "\n----- Test: Already Sorted -----\n";
    {
        stack<int> s;
        s.push(3);
        s.push(2);
        s.push(1);
        sortStack(s);
        int expected[] = {1, 2, 3};
        bool pass = true;
        for (int i : expected) {
            if (s.top() != i) {
                pass = false;
                break;
            }
            s.pop();
        }
        cout << (pass ? "PASS\n" : "FAIL\n");
    }

    cout << "\n----- Test: Unsorted Stack -----\n";
    {
        stack<int> s;
        s.push(1);
        s.push(3);
        s.push(2);
        sortStack(s);
        int expected[] = {1, 2, 3};
        bool pass = true;
        for (int i : expected) {
            if (s.top() != i) {
                pass = false;
                break;
            }
            s.pop();
        }
        cout << (pass ? "PASS\n" : "FAIL\n");
    }

    cout << "\n----- Test: Reverse Empty String -----\n";
    {
        string input = "";
        cout << "Input: \"" << input << "\"\n";
        cout << "Output: \"" << reverseString(input) << "\" - EXPECTED: \"\"\n";
        cout << (reverseString(input) == "" ? "PASS\n" : "FAIL\n");
    }

    cout << "\n----- Test: Reverse Single Character String -----\n";
    {
        string input = "A";
        cout << "Input: \"" << input << "\"\n";
        cout << "Output: \"" << reverseString(input) << "\" - EXPECTED: \"A\"\n";
        cout << (reverseString(input) == "A" ? "PASS\n" : "FAIL\n");
    }

    cout << "\n----- Test: Reverse Two Character String -----\n";
    {
        string input = "AB";
        cout << "Input: \"" << input << "\"\n";
        cout << "Output: \"" << reverseString(input) << "\" - EXPECTED: \"BA\"\n";
        cout << (reverseString(input) == "BA" ? "PASS\n" : "FAIL\n");
    }

    cout << "\n----- Test: Reverse Multiple Character String -----\n";
    {
        string input = "Hello, World!";
        cout << "Input: \"" << input << "\"\n";
        cout << "Output: \"" << reverseString(input) << "\" - EXPECTED: \"!dlroW ,olleH\"\n";
        cout << (reverseString(input) == "!dlroW ,olleH" ? "PASS\n" : "FAIL\n");
    }

    cout << "\n----- Test: Reverse String With Whitespace -----\n";
    {
        string input = "  A B C  ";
        cout << "Input: \"" << input << "\"\n";
        cout << "Output: \"" << reverseString(input) << "\" - EXPECTED: \"  C B A  \"\n";
        cout << (reverseString(input) == "  C B A  " ? "PASS\n" : "FAIL\n");
    }

    cout << "\n----- Test: Reverse String With Special Characters -----\n";
    {
        string input = "@#$%^&*()";
        cout << "Input: \"" << input << "\"\n";
        cout << "Output: \"" << reverseString(input) << "\" - EXPECTED: \")(*&^%$#@\"\n";
        cout << (reverseString(input) == ")(*&^%$#@" ? "PASS\n" : "FAIL\n");
    }

    cout << "\n----- Test: Empty Parentheses -----\n";
    {
        string input = "";
        cout << "Input: \"" << input << "\"\n";
        cout << "Output: " << (isBalancedParentheses(input) ? "Balanced" : "Unbalanced") << " - EXPECTED: Balanced\n";
        cout << (isBalancedParentheses(input) ? "PASS\n" : "FAIL\n");
    }

    cout << "\n----- Test: Balanced Parentheses -----\n";
    {
        string inputs[] = {"()", "(())", "(()(()))"};
        for (const string &input : inputs) {
            cout << "Input: \"" << input << "\"\n";
            cout << "Output: " << (isBalancedParentheses(input) ? "Balanced" : "Unbalanced") << " - EXPECTED: Balanced\n";
            cout << (isBalancedParentheses(input) ? "PASS\n" : "FAIL\n");
        }
    }

    cout << "\n----- Test: Unbalanced Opening Parentheses -----\n";
    {
        string inputs[] = {"(", "(()", "((())"};
        for (const string &input : inputs) {
            cout << "Input: \"" << input << "\"\n";
            cout << "Output: " << (isBalancedParentheses(input) ? "Balanced" : "Unbalanced") << " - EXPECTED: Unbalanced\n";
            cout << (!isBalancedParentheses(input) ? "PASS\n" : "FAIL\n");
        }
    }

    cout << "\n----- Test: Unbalanced Closing Parentheses -----\n";
    {
        string inputs[] = {")", "())", "(()))"};
        for (const string &input : inputs) {
            cout << "Input: \"" << input << "\"\n";
            cout << "Output: " << (isBalancedParentheses(input) ? "Balanced" : "Unbalanced") << " - EXPECTED: Unbalanced\n";
            cout << (!isBalancedParentheses(input) ? "PASS\n" : "FAIL\n");
        }
    }

    cout << "\n----- Test: Mixed Parentheses -----\n";
    {
        string balancedInput = "()()";
        string unbalancedInputs[] = {"()(", "())()"};

        cout << "Input: \"" << balancedInput << "\"\n";
        cout << "Output: " << (isBalancedParentheses(balancedInput) ? "Balanced" : "Unbalanced") << " - EXPECTED: Balanced\n";
        cout << (isBalancedParentheses(balancedInput) ? "PASS\n" : "FAIL\n");

        for (const string &input : unbalancedInputs) {
            cout << "Input: \"" << input << "\"\n";
            cout << "Output: " << (isBalancedParentheses(input) ? "Balanced" : "Unbalanced") << " - EXPECTED: Unbalanced\n";
            cout << (!isBalancedParentheses(input) ? "PASS\n" : "FAIL\n");
        }
    }

    cout << "\n----- Test: Empty Stack -----\n";
    {
        stack<int> s;
        sortStack(s);
        cout << "Stack is " << (s.empty() ? "empty" : "not empty") << " - EXPECTED: empty\n";
        cout << (s.empty() ? "PASS\n" : "FAIL\n");
    }

    cout << "\n----- Test: Single Element -----\n";
    {
        stack<int> s;
        s.push(42);
        sortStack(s);
        cout << "Top element: " << s.top() << " - EXPECTED: 42\n";
        cout << (s.top() == 42 ? "PASS\n" : "FAIL\n");
    }

    cout << "\n----- Test: Already Sorted -----\n";
    {
        stack<int> s;
        s.push(3);
        s.push(2);
        s.push(1);
        sortStack(s);
        int expected[] = {1, 2, 3};
        bool pass = true;
        for (int i : expected) {
            if (s.top() != i) {
                pass = false;
                break;
            }
            s.pop();
        }
        cout << (pass ? "PASS\n" : "FAIL\n");
    }

    cout << "\n----- Test: Unsorted Stack -----\n";
    {
        stack<int> s;
        s.push(1);
        s.push(3);
        s.push(2);
        sortStack(s);
        int expected[] = {1, 2, 3};
        bool pass = true;
        for (int i : expected) {
            if (s.top() != i) {
                pass = false;
                break;
            }
            s.pop();
        }
        cout << (pass ? "PASS\n" : "FAIL\n");
    }

    cout << "\n----- Test: All Equal Elements -----\n";
    {
        stack<int> s;
        s.push(5);
        s.push(5);
        s.push(5);
        sortStack(s);
        bool pass = true;
        while (!s.empty() && pass) {
            if (s.top() != 5) {
                pass = false;
            }
            s.pop();
        }
        cout << (pass ? "PASS\n" : "FAIL\n");
    }
    return 0;
}