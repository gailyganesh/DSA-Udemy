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
    if(mHead) std::cout << "Head: " << mHead->value << std::endl;
}

void DoublyLinkedList::printTail()
{
    if(mTail) std::cout << "Tail: " << mTail->value << std::endl;
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

void DoublyLinkedList::swapFirstLast()
{
    if(mLength<2) return;
    auto temp = mHead->value;
    mHead->value = mTail->value;
    mTail->value = temp;
}

void DoublyLinkedList::reverse()
{
    if(mLength<2) return;
    auto current = mHead;
    for(int i=0; i<mLength; i++)
    {
        auto temp = current->next;
        current->next = current->prev;
        current->prev = temp;
        current=temp;
    }
    auto temp = mHead;
    mHead = mTail;
    mTail = temp;
}

bool DoublyLinkedList::isPalindrome()
{
    if(mLength<2) return true;
    auto forward=mHead;
    auto reverse=mTail;
    while(forward != reverse)
    {
        if(forward->value!=reverse->value) return false;
        forward=forward->next;
        reverse=reverse->prev;
    }
    return true;
}

void DoublyLinkedList::swapPairs()
{
    if(mLength<2) return;
    DoublyLinkedListNode* prev=nullptr;
    auto couple1=mHead;
    auto couple2=mHead->next;
    auto after=mHead->next->next;
    for(int i=0; i<mLength; i++)
    {
        couple1->next=couple2->next;
        couple2->next=couple1;
        couple2->prev=couple1->prev;
        couple1->prev=couple2;

        if(prev) prev->next=couple2;
        else mHead=couple2;
        if(after) after->prev=couple1;
        else mTail=couple1;

        prev=couple1;
        couple1=couple1->next;
        if(couple1) couple2=couple1->next;
        else
        {
            break;
        }
        if(couple2) after=couple2->next;
        else
        {
            break;
        }
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

    // Test: Swap First and Last with Single Node
    {
        cout << "\n----- Test: Swap First and Last with Single Node -----\n";
        DoublyLinkedList list(1);
        cout << "DLL before swapping first and last:\n";
        list.printList();
        list.swapFirstLast();
        cout << "DLL after swapping first and last:\n";
        list.printList();
        int headValue = list.getHead()->value;
        int tailValue = list.getTail()->value;
        cout << "Head value after swapping: " << headValue << " - EXPECTED: 1\n";
        cout << "Tail value after swapping: " << tailValue << " - EXPECTED: 1\n";
        cout << ((headValue == 1 && tailValue == 1) ? "PASS\n" : "FAIL\n");
    }

    // Test: Swap First and Last with Two Nodes
    {
        cout << "\n----- Test: Swap First and Last with Two Nodes -----\n";
        DoublyLinkedList list(1);
        list.append(2);
        cout << "DLL before swapping first and last:\n";
        list.printList();
        list.swapFirstLast();
        cout << "DLL after swapping first and last:\n";
        list.printList();
        int headValue = list.getHead()->value;
        int tailValue = list.getTail()->value;
        cout << "Head value after swapping: " << headValue << " - EXPECTED: 2\n";
        cout << "Tail value after swapping: " << tailValue << " - EXPECTED: 1\n";
        cout << ((headValue == 2 && tailValue == 1) ? "PASS\n" : "FAIL\n");
    }

    // Test: Swap First and Last with Multiple Nodes
    {
        cout << "\n----- Test: Swap First and Last with Multiple Nodes -----\n";
        DoublyLinkedList list(1);
        list.append(2);
        list.append(3);
        list.append(4);
        cout << "DLL before swapping first and last:\n";
        list.printList();
        list.swapFirstLast();
        cout << "DLL after swapping first and last:\n";
        list.printList();
        int headValue = list.getHead()->value;
        int tailValue = list.getTail()->value;
        int headNextValue = list.getHead()->next->value;
        int tailPrevValue = list.getTail()->prev->value;
        cout << "Head value after swapping: " << headValue << " - EXPECTED: 4\n";
        cout << "Tail value after swapping: " << tailValue << " - EXPECTED: 1\n";
        cout << "Value after head after swapping: " << headNextValue << " - EXPECTED: 2\n";
        cout << "Value before tail after swapping: " << tailPrevValue << " - EXPECTED: 3\n";
        bool pass = headValue == 4 && tailValue == 1 && headNextValue == 2 && tailPrevValue == 3;
        cout << (pass ? "PASS\n" : "FAIL\n");
    }

    // Test: Reverse Single Node
    {
        cout << "\n----- Test: Reverse Single Node -----\n";
        DoublyLinkedList list(1);
        cout << "DLL before reversing:\n";
        list.printList();
        list.reverse();
        cout << "DLL after reversing:\n";
        list.printList();
        int headValue = list.getHead()->value;
        int tailValue = list.getTail()->value;
        cout << "Head value after reversing: " << headValue << " - EXPECTED: 1\n";
        cout << "Tail value after reversing: " << tailValue << " - EXPECTED: 1\n";
        cout << ((headValue == 1 && tailValue == 1) ? "PASS\n" : "FAIL\n");
    }

    // Test: Reverse Two Nodes
    {
        cout << "\n----- Test: Reverse Two Nodes -----\n";
        DoublyLinkedList list(1);
        list.append(2);
        cout << "DLL before reversing:\n";
        list.printList();
        list.reverse();
        cout << "DLL after reversing:\n";
        list.printList();
        int headValue = list.getHead()->value;
        int tailValue = list.getTail()->value;
        cout << "Head value after reversing: " << headValue << " - EXPECTED: 2\n";
        cout << "Tail value after reversing: " << tailValue << " - EXPECTED: 1\n";
        cout << ((headValue == 2 && tailValue == 1) ? "PASS\n" : "FAIL\n");
    }

    // Test: Reverse Multiple Nodes
    {
        cout << "\n----- Test: Reverse Multiple Nodes -----\n";
        DoublyLinkedList list(1);
        list.append(2);
        list.append(3);
        list.append(4);
        cout << "DLL before reversing:\n";
        list.printList();
        list.reverse();
        cout << "DLL after reversing:\n";
        list.printList();
        int headValue = list.getHead()->value;
        int tailValue = list.getTail()->value;
        int headNextValue = list.getHead()->next->value;
        int tailPrevValue = list.getTail()->prev->value;
        cout << "Head value after reversing: " << headValue << " - EXPECTED: 4\n";
        cout << "Tail value after reversing: " << tailValue << " - EXPECTED: 1\n";
        cout << "Value after head after reversing: " << headNextValue << " - EXPECTED: 3\n";
        cout << "Value before tail after reversing: " << tailPrevValue << " - EXPECTED: 2\n";
        bool pass = headValue == 4 && tailValue == 1 && headNextValue == 3 && tailPrevValue == 2;
        cout << (pass ? "PASS\n" : "FAIL\n");
    }

    // Test: Is Palindrome with Single Node
    {
        cout << "\n----- Test: Is Palindrome with Single Node -----\n";
        DoublyLinkedList list(1);
        cout << "DLL:\n";
        list.printList();
        bool result = list.isPalindrome();
        cout << "Is Palindrome: " << (result ? "true" : "false") << " - EXPECTED: true\n";
        cout << (result ? "PASS\n" : "FAIL\n");
    }

    // Test: Is Palindrome with Two Nodes
    {
        cout << "\n----- Test: Is Palindrome with Two Nodes -----\n";

        DoublyLinkedList list(1);
        list.append(1);
        cout << "DLL (equal values):\n";
        list.printList();
        bool result1 = list.isPalindrome();
        cout << "Is Palindrome: " << (result1 ? "true" : "false") << " - EXPECTED: true\n";
        cout << (result1 ? "PASS\n" : "FAIL\n");

        DoublyLinkedList list2(1);
        list2.append(2);
        cout << "\nDLL (different values):\n";
        list2.printList();
        bool result2 = list2.isPalindrome();
        cout << "Is Palindrome: " << (result2 ? "true" : "false") << " - EXPECTED: false\n";
        cout << (result2 ? "FAIL\n" : "PASS\n");
    }

    // Test: Is Palindrome with Multiple Nodes
    {
        cout << "\n----- Test: Is Palindrome with Multiple Nodes -----\n";

        DoublyLinkedList list(1);
        list.append(2);
        list.append(3);
        list.append(2);
        list.append(1);
        cout << "DLL (palindrome):\n";
        list.printList();
        bool result1 = list.isPalindrome();
        cout << "Is Palindrome: " << (result1 ? "true" : "false") << " - EXPECTED: true\n";
        cout << (result1 ? "PASS\n" : "FAIL\n");

        DoublyLinkedList list2(1);
        list2.append(2);
        list2.append(3);
        list2.append(3);
        list2.append(2);
        cout << "\nDLL (not palindrome):\n";
        list2.printList();
        bool result2 = list2.isPalindrome();
        cout << "Is Palindrome: " << (result2 ? "true" : "false") << " - EXPECTED: false\n";
        cout << (result2 ? "FAIL\n" : "PASS\n");
    }

    // Test: Swap Pairs with Single Node
    {
        cout << "\n----- Test: Swap Pairs with Single Node -----\n";
        DoublyLinkedList list(1);
        cout << "DLL before swapping pairs:\n";
        list.printList();
        list.swapPairs();
        cout << "\nDLL after swapping pairs:\n";
        list.printList();
        int value = list.getHead()->value;
        cout << "Head value after swapping pairs: " << value << " - EXPECTED: 1\n";
        cout << (value == 1 ? "PASS\n" : "FAIL\n");
    }

    // Test: Swap Pairs with Two Nodes
    {
        cout << "\n----- Test: Swap Pairs with Two Nodes -----\n";
        DoublyLinkedList list(1);
        list.append(2);
        cout << "DLL before swapping pairs:\n";
        list.printList();
        list.swapPairs();
        cout << "\nDLL after swapping pairs:\n";
        list.printList();
        int headValue = list.getHead()->value;
        int nextValue = list.getHead()->next->value;
        cout << "Head value after swapping pairs: " << headValue << " - EXPECTED: 2\n";
        cout << "Next value after swapping pairs: " << nextValue << " - EXPECTED: 1\n";
        cout << (headValue == 2 && nextValue == 1 ? "PASS\n" : "FAIL\n");
    }

    // Test: Swap Pairs with Multiple Nodes
    {
        cout << "\n----- Test: Swap Pairs with Multiple Nodes -----\n";
        DoublyLinkedList list(1);
        list.append(2);
        list.append(3);
        list.append(4);
        cout << "DLL before swapping pairs:\n";
        list.printList();
        list.swapPairs();
        cout << "\nDLL after swapping pairs:\n";
        list.printList();
        //cout << "PASS/FAIL test: ";
        cout << (list.getHead()->value == 2 && 
                 list.getHead()->next->value == 1 && 
                 list.getHead()->next->next->value == 4 &&
                 list.getHead()->next->next->next->value == 3 ? "PASS\n" : "FAIL\n");
    }

    return 0;
}
