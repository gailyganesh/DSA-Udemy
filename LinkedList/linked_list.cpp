#include "linked_list.h"
#include <string>

using namespace std;

LinkedList::LinkedList(int value) {
    mHead = new Node(value);
    mTail = mHead;
    mLength = 1;
}

LinkedList::~LinkedList() {
    makeEmpty();
}

void LinkedList::makeEmpty()
{
    Node* temp = mHead;
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

void LinkedList::printList()
{
    Node* temp = mHead;
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

void LinkedList::printHead()
{
    std::cout << "Head: " << mHead->value << std::endl;
}

void LinkedList::printTail()
{
    std::cout << "Tail: " << mTail->value << std::endl;
}

void LinkedList::printLength()
{
    std::cout << "Length: " << mLength << std::endl;
}

Node* LinkedList::getHead()
{
    return mHead;
}

Node* LinkedList::getTail()
{
    return mTail;
}

int LinkedList::getLength()
{
    return mLength;
}

void LinkedList::append(int value)
{
    Node* newNode = new Node(value);
    if(mLength==0)
    {
        mTail = newNode;
        mHead = mTail;
        return;
    }
    else
    {
        mTail->next = newNode;
        mTail = newNode;
    }
    mLength++;
}

void LinkedList::deleteLast()
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
        Node* temp = mHead;
        while(temp->next!=mTail)
        {
            temp=temp->next;
        }
        delete mTail;
        mTail = temp;
        mTail->next = nullptr;
        mLength--;
    }
}

void LinkedList::prepend(int value)
{
    Node* newNode = new Node(value);
    if(mLength==0)
    {
        mHead=newNode;
        mTail=newNode;
    }
    else
    {
        newNode->next=mHead;
        mHead=newNode;
    }
    mLength++;
}

void LinkedList::deleteFirst()
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
        Node* temp = mHead;
        mHead = mHead->next;
        delete temp;
        mLength--;
    }
}

Node* LinkedList::get(int index)
{
    if(index < 0 || index >= mLength)
    {
        return nullptr;
    }
    Node* temp = mHead;
    for (int i=0; i<index; ++i)
    {
        temp=temp->next;
    }
    return temp;
}

bool LinkedList::set(int index, int value)
{
    Node* temp = get(index);
    if(temp)
    {
        temp->value=value;
        return true;
    }
    return false;
}

// Function to convert nullptr to 0 for comparison
auto ptrToNum = [](Node* ptr) -> string {
    return (ptr == nullptr) ? "0 (nullptr)" : std::to_string(ptr->value);
};

// Helper function to check test result
auto checkTestResult = [](bool condition) {
    cout << (condition ? "PASS" : "FAIL") << endl;
};

int main() {
    LinkedList* myList = new LinkedList(10);
    myList->printHead();
    myList->printTail();
    myList->printLength();

    //Test for append
    // Test 1: Append To Non-Empty List
    {
        cout << "\n------ LinkedList Test: Append To Non-Empty List ------\n";
        
        LinkedList ll(1);
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
        cout << "\n-------- LinkedList Test: Append To Empty List --------\n";
        
        LinkedList ll(1);
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
        cout << "\n-------- LinkedList Test: Multiple Appends --------\n";
        
        LinkedList ll(1);
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
        cout << "\n------ LinkedList Test: DeleteLastSingleElementList ------\n";
        LinkedList ll(1);
        
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
        cout << "\n----- LinkedList Test: DeleteLastMultipleElementList -----\n";
        LinkedList ll(1);
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
        cout << "\n-------- LinkedList Test: DeleteLastEmptyList --------\n";
        LinkedList ll(1);
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
        cout << "\n------- LinkedList Test: RepeatedDeleteLast -------\n";
        LinkedList ll(1);
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

    // Test 1: PrependToNonEmptyList
    {
        cout << "\n----------- LinkedList Test: PrependToNonEmptyList -----------\n";
        
        LinkedList ll(1);
        cout << "Before prepend: ";
        ll.printList();

        ll.prepend(0);
        
        cout << "After prepend: ";
        ll.printList();
        
        cout << "Expected Length: 2, Actual Length: " << ll.getLength() << endl;
        cout << "Expected Head Value: 0, Actual Head Value: " << ll.getHead()->value << endl;
        cout << "Expected Tail Value: 1, Actual Tail Value: " << ll.getTail()->value << endl;
    }

    // Test 2: PrependToEmptyList
    {
        cout << "\n------------ LinkedList Test: PrependToEmptyList ------------\n";
        
        LinkedList ll(1);
        ll.makeEmpty();  // Making list empty
        cout << "Before prepend: ";
        ll.printList();
        
        ll.prepend(0);
        
        cout << "After prepend: ";
        ll.printList();
        
        cout << "Expected Length: 1, Actual Length: " << ll.getLength() << endl;
        cout << "Expected Head Value: 0, Actual Head Value: " << ll.getHead()->value << endl;
        cout << "Expected Tail Value: 0, Actual Tail Value: " << ll.getTail()->value << endl;
    }

    // Test 3: MultiplePrepend
    {
        cout << "\n------------- LinkedList Test: MultiplePrepend -------------\n";
        
        LinkedList ll(3);
        cout << "Before prepend: ";
        ll.printList();
        
        ll.prepend(2);
        ll.prepend(1);
        
        cout << "After prepend: ";
        ll.printList();
        
        cout << "Expected Length: 3, Actual Length: " << ll.getLength() << endl;
        cout << "Expected Head Value: 1, Actual Head Value: " << ll.getHead()->value << endl;
        cout << "Expected Tail Value: 3, Actual Tail Value: " << ll.getTail()->value << endl;
    }

    // Test 1: DeleteFirstFromNonEmptyList
    {
        cout << "\n------- LinkedList Test: DeleteFirstFromNonEmptyList -------\n";
        LinkedList ll(1);
        ll.append(2);
        
        cout << "Before deleteFirst: ";
        ll.printList();
        
        ll.deleteFirst();
        
        cout << "After deleteFirst: ";
        ll.printList();
        
        cout << "Expected Length: 1, Actual Length: " << ll.getLength() << endl;
        cout << "Expected Head Value: 2, Actual Head Value: " << ll.getHead()->value << endl;
        cout << "Expected Tail Next: 0 (nullptr), Actual Tail Next: " << ptrToNum(ll.getTail()->next) << endl;
    }

    // Test 2: DeleteFirstFromSingleItemList
    {
        cout << "\n------- LinkedList Test: DeleteFirstFromSingleItemList -------\n";
        LinkedList ll(1);
        
        cout << "Before deleteFirst: ";
        ll.printList();
        
        ll.deleteFirst();
        
        cout << "After deleteFirst: ";
        ll.printList();
        
        cout << "Expected Length: 0, Actual Length: " << ll.getLength() << endl;
        cout << "Expected Head: 0 (nullptr), Actual Head: " << ptrToNum(ll.getHead()) << endl;
        cout << "Expected Tail: 0 (nullptr), Actual Tail: " << ptrToNum(ll.getTail()) << endl;
    }

    // Test 3: DeleteFirstFromEmptyList
    {
        cout << "\n-------- LinkedList Test: DeleteFirstFromEmptyList --------\n";
        LinkedList ll(1);
        ll.makeEmpty();
        
        cout << "Before deleteFirst: ";
        ll.printList();
        
        ll.deleteFirst();
        
        cout << "After deleteFirst: ";
        ll.printList();
        
        cout << "Expected Length: 0, Actual Length: " << ll.getLength() << endl;
        cout << "Expected Head: 0 (nullptr), Actual Head: " << ptrToNum(ll.getHead()) << endl;
        cout << "Expected Tail: 0 (nullptr), Actual Tail: " << ptrToNum(ll.getTail()) << endl;
    }

    // Test 1: GetFromNonEmptyList
    {
        cout << "\n--------- LinkedList Test: GetFromNonEmptyList ---------\n";
        LinkedList ll(1);
        ll.append(2);
        ll.append(3);
        
        cout << "Current List: ";
        ll.printList();
        
        int index = 1;
        cout << "Get node at index: " << index << endl;
        
        Node* result = ll.get(index);
        
        cout << "Value of returned node: " << result->value << endl;
    }

    // Test 2: GetFromSingleItemList
    {
        cout << "\n--------- LinkedList Test: GetFromSingleItemList ---------\n";
        LinkedList ll(1);
        
        cout << "Current List: ";
        ll.printList();
        
        int index = 0;
        cout << "Get node at index: " << index << endl;
        
        Node* result = ll.get(index);
        
        cout << "Value of returned node: " << result->value << endl;
    }

    // Test 3: GetFromEmptyList
    {
        cout << "\n--------- LinkedList Test: GetFromEmptyList ---------\n";
        LinkedList ll(1);
        ll.makeEmpty();
        
        cout << "Current List: ";
        ll.printList();
        
        int index = 0;
        cout << "Get node at index: " << index << endl;
        
        Node* result = ll.get(index);
        
        cout << "Value of returned node: " << ptrToNum(result) << endl;
    }

    // Test 4: GetIndexOutOfBounds
    {
        cout << "\n--------- LinkedList Test: GetIndexOutOfBounds ---------\n";
        LinkedList ll(1);
        ll.append(2);
        ll.append(3);
        
        cout << "Current List: ";
        ll.printList();
        
        int index = 3;
        cout << "Get node at index: " << index << endl;
        
        Node* result = ll.get(index);
        
        cout << "Value of returned node: " << ptrToNum(result) << endl;
    }

    // Test 1: SetElementInNonEmptyList
    {
        cout << "\n------ LinkedList Test: SetElementInNonEmptyList ------\n";
        
        LinkedList ll(1);
        ll.append(2);
        ll.append(3);
        
        cout << "Before: ";
        ll.printList();
        
        bool result = ll.set(1, 4);
        
        cout << "set(1, 4)\n";
        
        cout << "After: ";
        ll.printList();
        
        checkTestResult(result && ll.get(1)->value == 4);
    }

    // Test 2: SetElementInSingleItemList
    {
        cout << "\n------ LinkedList Test: SetElementInSingleItemList ------\n";
        
        LinkedList ll(1);
        
        cout << "Before: ";
        ll.printList();
        
        bool result = ll.set(0, 2);
        
        cout << "set(0, 2)\n";
        
        cout << "After: ";
        ll.printList();
        
        checkTestResult(result && ll.get(0)->value == 2);
    }

    // Test 3: SetElementInEmptyList
    {
        cout << "\n------ LinkedList Test: SetElementInEmptyList ------\n";
        
        LinkedList ll(1);
        ll.makeEmpty();
        
        cout << "Before: ";
        ll.printList();
        
        bool result = ll.set(0, 2);
        
        cout << "set(0, 2)\n";
        
        cout << "After: ";
        ll.printList();
        
        checkTestResult(!result);
    }

    // Test 4: SetIndexOutOfBounds
    {
        cout << "\n------ LinkedList Test: SetIndexOutOfBounds ------\n";
        
        LinkedList ll(1);
        ll.append(2);
        ll.append(3);
        
        cout << "Before: ";
        ll.printList();
        
        bool result = ll.set(3, 4);
        
        cout << "set(3, 4)\n";
        
        cout << "After: ";
        ll.printList();
        
        checkTestResult(!result);
    }

    // Test 5: SetElementAndCheckOtherValues
    {
        cout << "\n------ LinkedList Test: SetElementAndCheckOtherValues ------\n";
        
        LinkedList ll(1);
        ll.append(2);
        ll.append(3);
        
        cout << "Before: ";
        ll.printList();
        
        ll.set(1, 4);
        
        cout << "set(1, 4)\n";
        
        cout << "After: ";
        ll.printList();
        
        bool result = (ll.get(0)->value == 1) && (ll.get(2)->value == 3);
        checkTestResult(result);
    }

    return 0;
}