#include "linked_list.h"
#include <string>

using namespace std;

LinkedList::LinkedList(int value) {
    mHead = new LinkedListNode(value);
    mTail = mHead;
    mLength = 1;
}

LinkedList::~LinkedList() {
    makeEmpty();
}

void LinkedList::makeEmpty()
{
    LinkedListNode* temp = mHead;
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
    LinkedListNode* temp = mHead;
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

LinkedListNode* LinkedList::getHead()
{
    return mHead;
}

LinkedListNode* LinkedList::getTail()
{
    return mTail;
}

int LinkedList::getLength()
{
    return mLength;
}

void LinkedList::append(int value)
{
    LinkedListNode* newNode = new LinkedListNode(value);
    if(mLength==0)
    {
        mTail = newNode;
        mHead = mTail;
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
        LinkedListNode* temp = mHead;
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
    LinkedListNode* newNode = new LinkedListNode(value);
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
        LinkedListNode* temp = mHead;
        mHead = mHead->next;
        delete temp;
        mLength--;
    }
}

LinkedListNode* LinkedList::get(int index)
{
    if(index < 0 || index >= mLength)
    {
        return nullptr;
    }
    LinkedListNode* temp = mHead;
    for (int i=0; i<index; ++i)
    {
        temp=temp->next;
    }
    return temp;
}

bool LinkedList::set(int index, int value)
{
    LinkedListNode* temp = get(index);
    if(temp)
    {
        temp->value=value;
        return true;
    }
    return false;
}

bool LinkedList::insert(int index, int value)
{
    if(index<0 || index>mLength) return false;
    else if(index==0)
    {
        prepend(value);
    }
    else if(index == mLength)
    {
        append(value);
    }
    else
    {
        LinkedListNode* newNode = new LinkedListNode(value);
        auto preNode = get(index-1);
        if(!preNode) return false;
        newNode->next = preNode->next;
        preNode->next = newNode;
        mLength++;
    }
    return true;
}

void LinkedList::deleteNode(int index)
{
    if(index<0 || index >= mLength)
    {
        return;
    }
    else if(index == 0)
    {
       return deleteFirst();
    }
    else if(index == mLength-1)
    {
        return deleteLast();
    }
    else
    {
        auto preNode = get(index-1);
        auto temp = preNode->next;
        preNode->next = temp->next;
        delete temp;
        mLength--;
    }
}

void LinkedList::reverse_on2()
{
    if(mLength<=1) return;
    for(int i=mLength-1; i>=0; i--)
    {
        LinkedListNode* current = get(i);
        LinkedListNode* pre = get(i-1);
        current->next = pre;
    }
    LinkedListNode* temp = mHead;
    mHead = mTail;
    mTail = temp;
}

void LinkedList::reverse()
{
    if(mLength<=1) return;
    LinkedListNode* temp = mHead;
    mHead = mTail;
    mTail = temp;
    LinkedListNode* before = nullptr;
    LinkedListNode* after = nullptr;
    for (int i=0; i<mLength;++i)
    {
        after = temp->next;
        temp->next = before;
        before = temp;
        temp = after;
    }
}

LinkedListNode* LinkedList::findMiddleNode_on2()
{
    if(mHead == nullptr) return nullptr;
    
    int length=0;
    LinkedListNode* temp1 = mHead;
    while(temp1)
    {
        temp1 = temp1->next;
        length++;
    }
    int index = length/2;
    int i = 0;
    LinkedListNode* temp = mHead;
    while(i < index)
    {
        temp = temp->next;
        i++;
    }
    return temp;
}

LinkedListNode* LinkedList::findMiddleNode()
{
    auto fast = mHead;
    auto slow = mHead;
    while(fast != nullptr && fast->next != nullptr)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    return slow;
}

//floyd's algorithm
bool LinkedList::hasLoop()
{
    auto fast = mHead;
    auto slow = mHead;
    while(fast != nullptr && fast->next != nullptr)
    {
        fast = fast->next->next;
        slow = slow->next;
        if(fast == slow)
        {
            return true;
        }
    }
    return false;
}

LinkedListNode* LinkedList::findKthFromEnd(int k)
{
    LinkedListNode* measurementEnd=mHead;
    LinkedListNode* measurementStart=mHead;
    for(int i=0; i<k; i++)
    {
        if(measurementEnd==nullptr)
        {
            return nullptr;
        }
        measurementEnd=measurementEnd->next;
    }
    if(k<0) return nullptr;
    while(measurementEnd)
    {
        measurementStart=measurementStart->next;
        measurementEnd=measurementEnd->next;
    }
    return measurementStart;
}

// Function to convert nullptr to 0 for comparison
auto ptrToNum = [](LinkedListNode* ptr) -> string {
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
        
        LinkedListNode* result = ll.get(index);
        
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
        
        LinkedListNode* result = ll.get(index);
        
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
        
        LinkedListNode* result = ll.get(index);
        
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
        
        LinkedListNode* result = ll.get(index);
        
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

     // Test 1: InsertAtBeginning
    {
        cout << "\n------ LinkedList Test: InsertAtBeginning ------\n";
        
        LinkedList ll(1);
        ll.append(2);
        
        cout << "Before: ";
        ll.printList();
        
        bool result = ll.insert(0, 0);
        
        cout << "insert( 0, 0 )\n";
        
        cout << "After: ";
        ll.printList();
        
        checkTestResult(result && ll.get(0)->value == 0); 
    }

    // Test 2: InsertAtEnd
    {
        cout << "\n------ LinkedList Test: InsertAtEnd ------\n";
        
        LinkedList ll(1);
        ll.append(2);
        
        cout << "Before: ";
        ll.printList();
        
        bool result = ll.insert(2, 3);
        
        cout << "insert( 2, 3 )\n";
        
        cout << "After: ";
        ll.printList();
        
        checkTestResult(result && ll.get(2)->value == 3);
    }

    // Test 3: InsertInMiddle
    {
        cout << "\n------ LinkedList Test: InsertInMiddle ------\n";
        
        LinkedList ll(1);
        ll.append(3);
        
        cout << "Before: ";
        ll.printList();
        
        bool result = ll.insert(1, 2);
        
        cout << "insert( 1, 2 )\n";
        
        cout << "After: ";
        ll.printList();
        
        checkTestResult(result && ll.get(1)->value == 2);
    }

    // Test 4: InsertOutOfBounds
    {
        cout << "\n------ LinkedList Test: InsertOutOfBounds ------\n";
        
        LinkedList ll(1);
        ll.append(2);
        
        cout << "Before: ";
        ll.printList();
        
        bool result = ll.insert(3, 3);
        
        cout << "insert( 3, 3 )\n";
        
        cout << "After: ";
        ll.printList();
        
        checkTestResult(!result);
    }

    // Test 5: InsertIntoEmptyList
    {
        cout << "\n------ LinkedList Test: InsertIntoEmptyList ------\n";
        
        LinkedList ll(1);
        ll.makeEmpty();
        
        cout << "Before: ";
        ll.printList();
        
        bool result = ll.insert(0, 1);
        
        cout << "insert( 0, 1 )\n";
        
        cout << "After: ";
        ll.printList();
        
        checkTestResult(result && ll.get(0)->value == 1);
    }

    // Test 6: InsertInvalidIndexNegative
    {
        cout << "\n------ LinkedList Test: InsertInvalidIndexNegative ------\n";
        
        LinkedList ll(1);
        
        cout << "Before: ";
        ll.printList();
        
        bool result = ll.insert(-1, 2);
        
        cout << "insert( -1, 2 )\n";
        
        cout << "After: ";
        ll.printList();
        
        checkTestResult(!result);
    }

    // Test 1: ReverseMultipleElementList
    {
        cout << "\n------ LinkedList Test: ReverseMultipleElementList ------\n";

        LinkedList ll(1);
        ll.append(2);
        ll.append(3);

        cout << "Before: ";
        ll.printList();

        ll.reverse();

        cout << "After: ";
        ll.printList();

        checkTestResult(ll.getHead()->value == 3 && ll.getTail()->value == 1 && ll.getLength() == 3);
    }

    // Test 2: ReverseSingleElement
    {
        cout << "\n------ LinkedList Test: ReverseSingleElement ------\n";

        LinkedList ll(1);

        cout << "Before: ";
        ll.printList();

        ll.reverse();

        cout << "After: ";
        ll.printList();

        checkTestResult(ll.getHead()->value == 1 && ll.getTail()->value == 1 && ll.getLength() == 1);
    }

    // Test 3: ReverseListWithTwoElements
    {
        cout << "\n------ LinkedList Test: ReverseListWithTwoElements ------\n";

        LinkedList ll(1);
        ll.append(2);

        cout << "Before: ";
        ll.printList();

        ll.reverse();

        cout << "After: ";
        ll.printList();

        checkTestResult(ll.getHead()->value == 2 && ll.getTail()->value == 1 && ll.getLength() == 2);
    }

    // Test 4: ReverseListMultipleTimes
    {
        cout << "\n------ LinkedList Test: ReverseListTwice ------\n";

        LinkedList ll(1);
        ll.append(2);
        ll.append(3);

        cout << "Before: ";
        ll.printList();

        ll.reverse();
        ll.reverse();

        cout << "After: ";
        ll.printList();

        checkTestResult(ll.getHead()->value == 1 && ll.getTail()->value == 3 && ll.getLength() == 3);
    }

    // Test 5: CheckIntegrityAfterReverse
    {
        cout << "\n------ LinkedList Test: CheckIntegrityAfterReverse ------\n";

        LinkedList ll(1);
        ll.append(2);
        ll.append(3);

        cout << "Before: ";
        ll.printList();

        ll.reverse();

        cout << "After: ";
        ll.printList();

        LinkedListNode* head = ll.getHead();
        bool result = head->value == 3 && head->next->value == 2 && head->next->next->value == 1 && head->next->next->next == nullptr;

        checkTestResult(result);
    }

    return 0;
}
