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

int main()
{
    return 0;
}