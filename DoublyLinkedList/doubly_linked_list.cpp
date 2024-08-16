#include "doubly_linked_list.h"
#include <string>

using namespace std;

DoublyLinkedList::DoublyLinkedList(int value) {
    mHead = new DoublyLinkedListNode(value);
    mTail = mHead;
    mLength = 1;
}

DoublyLinkedList::~DoublyLinkedList() {
    makeEmpty();
}

void DoublyLinkedList::makeEmpty()
{
    DoublyLinkedListNode* temp = mHead;
    while(temp)
    {
        mHead=mHead->next;
        delete temp;
        temp=mHead;
        mLength--;
    }
    if(mLength!=0)
    {
        std::cout << "Not deleted all the nodes still " << mLength <<" remaining";
    }
    mHead = nullptr;
    mTail = nullptr;
}

void DoublyLinkedList::printList()
{
    DoublyLinkedListNode* temp = mHead;
    std::cout << "[";
    while(temp)
    {
        std::cout << temp->value;
        if(temp != mTail)
        {
            std::cout << ", ";
        }
        temp=temp->next;
    }
    std::cout << "]" << std::endl;
}

void DoublyLinkedList::printHead()
{
    std::cout << "Head: " << mHead->value << std::endl;
}

void DoublyLinkedList::printTail()
{
    std::cout << "Tail: " << mTail->value << std::endl;
}

void DoublyLinkedList::printLength()
{
    std::cout << "Length: " << mLength << std::endl;
}

DoublyLinkedListNode* DoublyLinkedList::getHead()
{
    return mHead;
}

DoublyLinkedListNode* DoublyLinkedList::getTail()
{
    return mTail;
}

int DoublyLinkedList::getLength()
{
    return mLength;
}

void DoublyLinkedList::append(int value)
{
    DoublyLinkedListNode* newNode = new DoublyLinkedListNode(value);
    if(mLength==0)
    {
        mTail = newNode;
        mHead = mTail;
    }
    else
    {
        mTail->next = newNode;
        newNode->prev = mTail;
        mTail = newNode;
    }
    mLength++;
}

void DoublyLinkedList::deleteLast()
{
    if(mLength==0)
    {
        return;
    }
    else if(mLength==1)
    {
        makeEmpty();
    }
    else
    {
        mTail=mTail->prev;
        delete mTail->next;
        mTail->next=nullptr;
        mLength--;
    }
}

void DoublyLinkedList::prepend(int value)
{
    DoublyLinkedListNode* newNode = new DoublyLinkedListNode(value);
    if(mLength==0)
    {
        mHead=newNode;
        mTail=newNode;
    }
    else
    {
        newNode->next=mHead;
        mHead->prev=newNode;
        mHead=newNode;
    }
    mLength++;
}

void DoublyLinkedList::deleteFirst()
{
    if(mLength==0)
    {
        return;
    }
    else if (mLength==1)
    {
        makeEmpty();
    }
    else
    {
        mHead = mHead->next;
        delete mHead->prev;
        mHead->prev = nullptr;
        mLength--;
    }
}

DoublyLinkedListNode* DoublyLinkedList::get(int index)
{
    if(index < 0 || index >= mLength)
    {
        return nullptr;
    }
    if(index<mLength/2)
    {
        DoublyLinkedListNode* temp = mHead;
        for (int i=0; i<index; ++i)
        {
            temp=temp->next;
        }
        return temp;
    }
    else
    {
        DoublyLinkedListNode* temp = mTail;
        for(int i=mLength-1;i>index;i--)
        {
            temp=temp->prev;
        }
        return temp;
    }
}

bool DoublyLinkedList::set(int index, int value)
{
    DoublyLinkedListNode* temp = get(index);
    if(temp)
    {
        temp->value=value;
        return true;
    }
    return false;
}

bool DoublyLinkedList::insert(int index, int value)
{
    if(index==0) prepend(value);
    else if(index==mLength) append(value);
    else
    {
        DoublyLinkedListNode* temp=get(index);
        if(temp==nullptr)
        {
            return false;
        }
            DoublyLinkedListNode* newNode = new DoublyLinkedListNode(value);
            newNode->prev=temp->prev;
            newNode->next=temp;
            temp->prev->next = newNode;
            temp->prev=newNode;
            mLength++;
            return true;
            
    }
    return true;
}

void DoublyLinkedList::deleteNode(int index)
{
    if(index==0) deleteFirst();
    else if(index==mLength-1) deleteLast();
    else
    {
        DoublyLinkedListNode* temp=get(index);
        if(temp==nullptr) return;
        temp->prev->next=temp->next;
        temp->next->prev=temp->prev;
        delete temp;
        mLength--;
    }
}

// Function to convert nullptr to 0 for comparison
auto ptrToNum = [](DoublyLinkedListNode* ptr) -> string {
    return (ptr == nullptr) ? "0 (nullptr)" : std::to_string(ptr->value);
};

// Helper function to check test result
auto checkTestResult = [](bool condition) {
    cout << (condition ? "PASS" : "FAIL") << endl;
};

int main() {
    DoublyLinkedList* myList = new DoublyLinkedList(10);
    myList->printHead();
    myList->printTail();
    myList->printLength();

    //Test for append
    // Test 1: Append To Non-Empty List
    {
        cout << "\n------ DoublyLinkedList Test: Append To Non-Empty List ------\n";
        
        DoublyLinkedList ll(1);
        cout << "Before append: ";
        ll.printList();
        
        ll.append(2);
        
        cout << "After append: ";
        ll.printList();
        
        cout << "Expected Length: 2, Actual Length: " << ll.getLength() << endl;
        cout << "Expected Tail Value: 2, Actual Tail Value: " << ll.getTail()->value << endl;
        cout << "Expected Head Value: 1, Actual Head Value: " << ll.getHead()->value << endl;
    }

    // Test 2: Append To Empty List
    {
        cout << "\n-------- DoublyLinkedList Test: Append To Empty List --------\n";
        
        DoublyLinkedList ll(1);
        ll.makeEmpty();  // Make list empty
        cout << "Before append: ";
        ll.printList();
        
        ll.append(2);
        
        cout << "After append: ";
        ll.printList();
        
        cout << "Expected Length: 1, Actual Length: " << ll.getLength() << endl;
        cout << "Expected Tail Value: 2, Actual Tail Value: " << ll.getTail()->value << endl;
        cout << "Expected Head Value: 2, Actual Head Value: " << ll.getHead()->value << endl;
    }
    
    // Test 3: Multiple Appends
    {
        cout << "\n-------- DoublyLinkedList Test: Multiple Appends --------\n";
        
        DoublyLinkedList ll(1);
        cout << "Before append: ";
        ll.printList();
        
        ll.append(2);
        ll.append(3);
        
        cout << "After append: ";
        ll.printList();
        
        cout << "Expected Length: 3, Actual Length: " << ll.getLength() << endl;
        cout << "Expected Tail Value: 3, Actual Tail Value: " << ll.getTail()->value << endl;
        cout << "Expected Head Value: 1, Actual Head Value: " << ll.getHead()->value << endl;
    }

    // Test 1: DeleteLastSingleElementList
    {
        cout << "\n------ DoublyLinkedList Test: DeleteLastSingleElementList ------\n";
        DoublyLinkedList ll(1);
        
        cout << "Before deleteLast: ";
        ll.printList();
        
        ll.deleteLast();
        
        cout << "After deleteLast: ";
        ll.printList();
        
        cout << "Expected Length: 0, Actual Length: " << ll.getLength() << endl;
        cout << "Expected Head: 0 (nullptr), Actual Head: " << ptrToNum(ll.getHead()) << endl;
        cout << "Expected Tail: 0 (nullptr), Actual Tail: " << ptrToNum(ll.getTail()) << endl;
    }

    // Test 2: DeleteLastMultipleElementList
    {
        cout << "\n----- DoublyLinkedList Test: DeleteLastMultipleElementList -----\n";
        DoublyLinkedList ll(1);
        ll.append(2);
        ll.append(3);
        
        cout << "Before deleteLast: ";
        ll.printList();
        
        ll.deleteLast();
        
        cout << "After deleteLast: ";
        ll.printList();
        
        cout << "Expected Length: 2, Actual Length: " << ll.getLength() << endl;
        cout << "Expected Tail Value: 2, Actual Tail Value: " << ll.getTail()->value << endl;
    }

    // Test 3: DeleteLastEmptyList
    {
        cout << "\n-------- DoublyLinkedList Test: DeleteLastEmptyList --------\n";
        DoublyLinkedList ll(1);
        ll.makeEmpty();
        
        cout << "Before deleteLast: ";
        ll.printList();
        
        ll.deleteLast();
        
        cout << "After deleteLast: ";
        ll.printList();
        
        cout << "Expected Length: 0, Actual Length: " << ll.getLength() << endl;
        cout << "Expected Head: 0 (nullptr), Actual Head: " << ptrToNum(ll.getHead()) << endl;
        cout << "Expected Tail: 0 (nullptr), Actual Tail: " << ptrToNum(ll.getTail()) << endl;
    }

    // Test 4: RepeatedDeleteLast
    {
        cout << "\n------- DoublyLinkedList Test: RepeatedDeleteLast -------\n";
        DoublyLinkedList ll(1);
        ll.append(2);
        ll.append(3);
        
        cout << "Before deleteLast: ";
        ll.printList();
        
        ll.deleteLast();
        ll.deleteLast();
        ll.deleteLast();
        
        cout << "After deleteLast: ";
        ll.printList();
        
        cout << "Expected Length: 0, Actual Length: " << ll.getLength() << endl;
        cout << "Expected Head: 0 (nullptr), Actual Head: " << ptrToNum(ll.getHead()) << endl;
        cout << "Expected Tail: 0 (nullptr), Actual Tail: " << ptrToNum(ll.getTail()) << endl;
    }

    return 0;
}
