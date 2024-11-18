#include "linked_list.h"
#include <string>
#include <vector>

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
        if(temp->next)
        {
            std::cout << ", ";
        }
        temp=temp->next;
    }
    std::cout << "]" << std::endl;
}

void LinkedList::printHead()
{
    if(mHead) std::cout << "Head: " << mHead->value << std::endl;
}

void LinkedList::printTail()
{
    if(mTail) std::cout << "Tail: " << mTail->value << std::endl;
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

/************************ leetcode problems ***************************************/
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

void LinkedList::partitionList(int x)
{
    if(mHead==nullptr) return;
    LinkedListNode* dummy_head = nullptr;
    LinkedListNode* dummyItr = dummy_head;
    LinkedListNode* lessItr=mHead;
    LinkedListNode* prevItr=nullptr;
    while(lessItr)
    {
        if(lessItr->value<x)
        {
            prevItr=lessItr;
            lessItr=lessItr->next;
        }
        else
        {
            if(prevItr!=nullptr)
            {
                prevItr->next=lessItr->next;
            }
            if(dummy_head == nullptr)
            {
                dummyItr=lessItr;
                dummy_head=dummyItr;
            }
            else
            {
                dummyItr->next=lessItr;
                dummyItr=dummyItr->next;
            }
            lessItr=lessItr->next;
            dummyItr->next=nullptr;
        }
    }
    if(prevItr!=nullptr) prevItr->next=dummy_head;
    else mHead = dummy_head;
    mTail=dummyItr;
}

void LinkedList::removeDuplicates()
{
    auto current=mHead;

    while(current)
    {
        auto runner=current->next;
        auto prev_runner = current;
        while(runner)
        {
            if(current->value == runner->value)
            {
                //delete the runner
                prev_runner->next = runner->next;
                auto temp = runner;
                runner=runner->next;
                temp->next = nullptr;
                delete temp;
                mLength--;
            }
            else
            {
                prev_runner=runner;
                runner=runner->next;
            }
        }
        current = current->next;
    }
}

int LinkedList::binaryToDecimal()
{
    int num=0;
    auto current = mHead;
    for(int i=mLength-1; i>=0; i--)
    {
        auto pow =std::pow(2,i);
        num+=(current->value * pow);
        current=current->next;
    }
    return num;
}

void LinkedList::reverseBetween(int m, int n)
{
    if(m==n) return;
    auto mPtr=mHead;
    auto nPtr=mHead;
    LinkedListNode* mPrevPtr=nullptr;
    if(mPtr && mPtr->next)
    {
        for(int i=0; i<n; i++)
        {
            if(i<m)
            {
                mPrevPtr = mPtr;
                mPtr=mPtr->next;
            }
            nPtr=nPtr->next;
        }
        auto currentPtr=mPtr;
        auto nextPtr=currentPtr->next;
        auto rightPtr=nextPtr;
        while(true)
        {
            rightPtr = nextPtr->next;
            nextPtr->next = currentPtr;
            currentPtr = nextPtr;
            nextPtr = rightPtr;
            if(currentPtr == nPtr)
            {
                break;
            }
        }
        mPtr->next=nextPtr;
        if(mPrevPtr) mPrevPtr->next=nPtr;
        else mHead=nPtr;
    }
}

void LinkedList::bubbleSort()
{
    if(mHead==nullptr || mHead->next==nullptr) return;
    LinkedListNode* endNode=nullptr;
    while(true)
    {
        auto current=mHead;
        auto nextNode=current->next;
        while(true)
        {
            if(current->value>nextNode->value)
            {
                auto temp=current->value;
                current->value=nextNode->value;
                nextNode->value=temp;
            }
            current=nextNode;
            nextNode=current->next;
            if(nextNode==endNode)
            {
                endNode=current;
                break;
            }
        }
        if(endNode==mHead->next) return;
    }
}

void LinkedList::selectionSort()
{
    if(!mHead) return;
    auto currentNode=mHead;
    while(currentNode->next)
    {
        auto lowestValueNode=currentNode;
        auto IteratorNode=currentNode->next;
        while(IteratorNode)
        {
            if(IteratorNode->value<currentNode->value)
            {
                lowestValueNode=IteratorNode;
            }
            IteratorNode=IteratorNode->next;
        }
        if(currentNode!=lowestValueNode)
        {
           auto temp=currentNode->value;
           currentNode->value=lowestValueNode->value;
           lowestValueNode->value=temp;
        }
        currentNode=currentNode->next;
    }
}

void LinkedList::insertionSort() {
    if (mLength < 2) {
        return;
    }

    LinkedListNode* sortedListHead = mHead;
    LinkedListNode* unsortedListHead = mHead->next;
    sortedListHead->next = nullptr;

    while (unsortedListHead != nullptr) {
        LinkedListNode* current = unsortedListHead;
        unsortedListHead = unsortedListHead->next;

        if (current->value < sortedListHead->value) {
            current->next = sortedListHead;
            sortedListHead = current;
        } else {
            LinkedListNode* searchPointer = sortedListHead;
            while (searchPointer->next != nullptr && current->value > searchPointer->next->value) {
                searchPointer = searchPointer->next;
            }
            current->next = searchPointer->next;
            searchPointer->next = current;
        }
    }

    mHead = sortedListHead;
    LinkedListNode* temp = mHead;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    mTail = temp;
}

void LinkedList::merge(LinkedList &otherList)
{
    auto Iterator1=mHead;
    LinkedListNode* prevIter1=nullptr;
    auto Iterator2=otherList.getHead();
    while(Iterator1 && Iterator2)
    {
        if(Iterator2->value<Iterator1->value)
        {
            auto temp=Iterator2->next;
            if(prevIter1)
            {
                prevIter1->next=Iterator2;
                Iterator2->next=Iterator1;
            }
            else
            {
                Iterator2->next=Iterator1;
                mHead=Iterator2;
                prevIter1=Iterator2;
            }
            Iterator2=temp;
        }
        else
        {
            prevIter1=Iterator1;
            Iterator1=Iterator1->next;
        }
    }

    if(mHead == nullptr) mHead=otherList.mHead;
    if(Iterator2)
    {
        if(prevIter1) prevIter1->next=Iterator2;
        mTail=otherList.getTail();
    }
    otherList.mHead=nullptr;
    otherList.mTail=nullptr;
    mLength+=otherList.mLength;
    otherList.mLength=0;
}

// Function to convert nullptr to 0 for comparison
auto ptrToNum = [](LinkedListNode* ptr) -> string {
    return (ptr == nullptr) ? "0 (nullptr)" : std::to_string(ptr->value);
};

// Helper function to check test result
auto checkTestResult = [](bool condition) {
    cout << (condition ? "PASS" : "FAIL") << endl;
};

// Function to convert linked list to vector
    auto listToVector = [](LinkedList& list) {
        vector<int> result;
        LinkedListNode* current = list.getHead();
        while (current != nullptr) {
            result.push_back(current->value);
            current = current->next;
        }
        return result;
    };

/************************ leetcode problems for vector ***************************************/
void removeElement(vector<int>& nums, int val) {
	//   +=====================================================+
	//   |                 WRITE YOUR CODE HERE                |
	//   | Description:                                        |
	//   | - This function removes all occurrences of a        |
	//   |   given value ('val') from an integer vector.       |
	//   | - It modifies the input vector 'nums'.              |
	//   |                                                     |
	//   | Return type: void                                   |
	//   |                                                     |
	//   | Tips:                                               |
	//   | - Uses two pointers 'i' and 'j' for traversal.      |
	//   | - 'i' points to the last element that is not 'val'. |
	//   | - 'j' is used for iterating over the array.         |
	//   | - Check output from Test.cpp in "User logs".        |
	//   +=====================================================+
	int i=0;
	for(int j=0; j<nums.size();j++)
	{
	    if(nums[j] != val)
	    {
	        nums[i]=nums[j];
	        i++;
	    }
	}
	nums.resize(i);
}

vector<int> findMaxMin(vector<int>& myList) {
	//   +=====================================================+
	//   |                 WRITE YOUR CODE HERE                |
	//   | Description:                                        |
	//   | - This function finds the maximum and minimum       |
	//   |   values in a given list of integers.               |
	//   | - It uses a single loop to go through the list.     |
	//   |                                                     |
	//   | Return type: vector<int>                            |
	//   | - Returns a vector containing maximum and minimum.  |
	//   |                                                     |
	//   | Tips:                                               |
	//   | - 'maximum' and 'minimum' keep track of the         |
	//   |   highest and lowest values found.                  |
	//   | - Check output from Test.cpp in "User logs".        |
	//   +=====================================================+
    int max=INT_MIN;
    int min=INT_MAX;
    for (auto val:myList)
    {
        if(val>max) max=val;
        if(val<min) min=val;
    }
    return {max,min};
}

string findLongestString(vector<string>& stringList) {
	//   +=====================================================+
	//   |                 WRITE YOUR CODE HERE                |
	//   | Description:                                        |
	//   | - This function finds the longest string in         |
	//   |   a given list of strings.                          |
	//   | - It uses a single loop to check the length         |
	//   |   of each string.                                   |
	//   |                                                     |
	//   | Return type: string                                 |
	//   | - Returns the longest string found in the list.     |
	//   |                                                     |
	//   | Tips:                                               |
	//   | - 'longestString' keeps track of the longest        |
	//   |   string found so far.                              |
	//   | - Check output from Test.cpp in "User logs".        |
	//   +=====================================================+
    int longest=0;
    std::string longestString="";
    for (auto val:stringList)
    {
        int length=0;
        for(auto ch:val) length++;
        if(length>longest)
        {
            longest=length;
            longestString=val;
        }
    }
    return longestString;
}

int removeDuplicates(vector<int>& nums) {
	//   +=====================================================+
	//   |                 WRITE YOUR CODE HERE                |
	//   | Description:                                        |
	//   | - This function removes duplicate integers          |
	//   |   from a sorted array in-place.                     |
	//   | - It uses two pointers to achieve this.             |
	//   |                                                     |
	//   | Return type: int                                    |
	//   | - Returns the length of the new array.              |
	//   |                                                     |
	//   | Tips:                                               |
	//   | - 'writePointer' is used for storing unique values. |
	//   | - 'readPointer' is used for reading array values.   |
	//   | - Check output from Test.cpp in "User logs".        |
	//   +=====================================================+
    if (nums.size() == 0) {
        return 0;
    }
 
    int writePointer = 1;
 
    for (int readPointer = 1; readPointer < nums.size(); readPointer++) {
        if (nums[readPointer] != nums[readPointer - 1]) {
            nums[writePointer] = nums[readPointer];
            writePointer++;
        }
    }
 
    return writePointer;
}

int maxProfit(vector<int>& prices) {
	//   +=====================================================+
	//   |                 WRITE YOUR CODE HERE                |
	//   | Description:                                        |
	//   | - This function calculates the maximum profit       |
	//   |   from buying and selling a stock.                  |
	//   | - It iterates through the 'prices' array once.      |
	//   |                                                     |
	//   | Return type: int                                    |
	//   |                                                     |
	//   | Tips:                                               |
	//   | - 'minPrice' keeps track of the lowest price.       |
	//   | - 'maxProfit' stores the maximum profit found.      |
	//   | - Use 'min' and 'max' functions to update values.   |
	//   | - Check output from Test.cpp in "User logs".        |
	//   +=====================================================+
    int minPrice=INT_MAX;
    int maxProfit=0;
    //prices: [7,1,5,3,6,4]
    for (int i=0; i<prices.size(); i++)
    {
        if(prices[i]<minPrice)
        {
            minPrice=prices[i];
            maxProfit=0;
        }
        else {
            int diff=prices[i]-minPrice;
            if(diff>maxProfit)maxProfit=diff;
        }
        
    }
    return maxProfit;
}
int main() {

    // Test: ReverseBetweenEmptyList
    {
        cout << "\n------ Test: ReverseBetweenEmptyList ------\n";
        cout << "reverseBetween( 0, 2 )\n";
        
        LinkedList list(1);
        list.makeEmpty();
        
        cout << "BEFORE:    ";
        list.printList();
        
        list.reverseBetween(0, 2);
        
        cout << "AFTER:     ";
        list.printList();
        
        checkTestResult(list.getLength() == 0);
    }

    // Test: ReverseBetweenSingleElement
    {
        cout << "\n------ Test: ReverseBetweenSingleElement ------\n";
        cout << "reverseBetween( 0, 0 )\n";
        
        LinkedList list(1);
        
        cout << "BEFORE:    ";
        list.printList();
        
        list.reverseBetween(0, 0);
        
        cout << "AFTER:     ";
        list.printList();
        
        LinkedListNode* head = list.getHead();
        checkTestResult(head && head->value == 1);
    }

    // Test: ReverseBetweenBothArgumentsSameNumber
    {
        cout << "\n------ Test: ReverseBetweenBothArgumentsSameNumber ------\n";
        cout << "reverseBetween( 1, 1 )\n";
        
        LinkedList list(1);
        list.append(2);
        list.append(3);
        
        cout << "BEFORE:    ";
        list.printList();
        
        list.reverseBetween(1, 1);
        
        cout << "AFTER:     ";
        list.printList();
        
        LinkedListNode* head = list.getHead();
        checkTestResult(
          head && 
          head->value == 1 && 
          head->next->value == 2 && 
          head->next->next->value == 3
        );
    }

    // Test: ReverseBetweenMultipleElements
    {
        cout << "\n------ Test: ReverseBetweenMultipleElements ------\n";
        cout << "reverseBetween( 1, 4 )\n";
        
        LinkedList list(1);
        list.append(2);
        list.append(3);
        list.append(4);
        list.append(5);
        list.append(6);
        
        cout << "BEFORE:    ";
        list.printList();
        
        list.reverseBetween(1, 4);
        
        cout << "AFTER:     ";
        list.printList();
        
        // Check condition
        LinkedListNode* head = list.getHead();
        checkTestResult(
          head && 
          head->value == 1 &&
          head->next->value == 5 &&
          head->next->next->value == 4 &&
          head->next->next->next->value == 3 &&
          head->next->next->next->next->value == 2 && 
          head->next->next->next->next->next->value == 6
        );
    }

    // Test: ReverseBetweenStartAtZero
    {
        cout << "\n------ Test: ReverseBetweenStartAtZero ------\n";
        cout << "reverseBetween( 0, 2 )\n";
        
        LinkedList list(1);
        list.append(2);
        list.append(3);
        list.append(4);
        
        cout << "BEFORE:    ";
        list.printList();
        
        list.reverseBetween(0, 2);
        
        cout << "AFTER:     ";
        list.printList();
        
        // Check condition
        LinkedListNode* head = list.getHead();
        checkTestResult(
          head && 
          head->value == 3 &&
          head->next->value == 2 &&
          head->next->next->value == 1 &&
          head->next->next->next->value == 4
        );
    }

    // Test: ReverseBetweenEndAtLast
    {
        cout << "\n------ Test: ReverseBetweenMiddleToLast ------\n";
        cout << "reverseBetween( 1, 2 )\n";
        
        LinkedList list(1);
        list.append(2);
        list.append(3);
        
        cout << "BEFORE:    ";
        list.printList();
        
        list.reverseBetween(1, 2);
        
        cout << "AFTER:     ";
        list.printList();
        
        // Check condition
        LinkedListNode* head = list.getHead();
        checkTestResult(
          head && 
          head->value == 1 &&
          head->next->value == 3 &&
          head->next->next->value == 2
        );
    }

     // Test: BinaryToDecimalEmptyList
    {
        cout << "\n------ Test: BinaryToDecimalEmptyList ------\n";
        
        LinkedList list(1);
        list.makeEmpty();
        
        cout << "BINARY:    ";
        list.printList();
        
        int decimal = list.binaryToDecimal();
        
        cout << "DECIMAL:   " << decimal << endl;
        
        checkTestResult(decimal == 0);
    }

    // Test: BinaryToDecimalSingleElement
    {
        cout << "\n------ Test: BinaryToDecimalSingleElement ------\n";
        
        LinkedList list(1);
        
        cout << "BINARY:    ";
        list.printList();
        
        int decimal = list.binaryToDecimal();
        
        cout << "DECIMAL:   " << decimal << endl;
        
        checkTestResult(decimal == 1);
    }

    // Test: BinaryToDecimalMultipleElements
    {
        cout << "\n------ Test: BinaryToDecimalMultipleElements ------\n";
        
        LinkedList list(1);
        list.append(0);
        list.append(1);
        list.append(1);
        
        cout << "BINARY:    ";
        list.printList();
        
        int decimal = list.binaryToDecimal();
        
        cout << "DECIMAL:   " << decimal << endl;
        
        checkTestResult(decimal == 11);
    }

    // Test: BinaryToDecimalAllZeros
    {
        cout << "\n------ Test: BinaryToDecimalAllZeros ------\n";
        
        LinkedList list(0);
        list.append(0);
        list.append(0);
        list.append(0);
        
        cout << "BINARY:    ";
        list.printList();
        
        int decimal = list.binaryToDecimal();
        
        cout << "DECIMAL:   " << decimal << endl;
        
        checkTestResult(decimal == 0);
    }

    // Test: BinaryToDecimalAllOnes
    {
        cout << "\n------ Test: BinaryToDecimalAllOnes ------\n";
        
        LinkedList list(1);
        list.append(1);
        list.append(1);
        list.append(1);
        
        cout << "BINARY:    ";
        list.printList();
        
        int decimal = list.binaryToDecimal();
        
        cout << "DECIMAL:   " << decimal << endl;
        
        checkTestResult(decimal == 15);
    }

    //Test for partitionList Leetcode problem
    LinkedList* myList = new LinkedList(10);
    myList->printHead();
    myList->printTail();
    myList->printLength();

    {
        cout << "Ganesh output: " << std::endl;
        LinkedList* mList = new LinkedList(1);
        mList->append(4);
        mList->append(3);
        mList->append(2);
        mList->append(5);
        mList->append(2);
        mList->printList();
        mList->partitionList(9);
        mList->printList();
    }

    // Test: RemoveDuplicatesEmptyList
    {
        cout << "\n------ Test: RemoveDuplicatesEmptyList ------\n";
        
        LinkedList list(1);
        list.makeEmpty();
        
        cout << "BEFORE:    ";
        list.printList();
        
        list.removeDuplicates();
        
        cout << "AFTER:     ";
        list.printList();
        
        LinkedListNode* head = list.getHead();
        checkTestResult(head == nullptr);
    }

    // Test: RemoveDuplicatesSingleElement
    {
        cout << "\n------ Test: RemoveDuplicatesSingleElement ------\n";
        
        LinkedList list(1);
        
        cout << "BEFORE:    ";
        list.printList();
        
        list.removeDuplicates();
        
        cout << "AFTER:     ";
        list.printList();
        
        LinkedListNode* head = list.getHead();
        checkTestResult(head && head->value == 1);
    }

    // Test: RemoveDuplicatesNoDuplicates
    {
        cout << "\n------ Test: RemoveDuplicatesNoDuplicates ------\n";
        
        LinkedList list(1);
        list.append(2);
        list.append(3);
        
        cout << "BEFORE:    ";
        list.printList();
        
        list.removeDuplicates();
        
        cout << "AFTER:     ";
        list.printList();
        
        LinkedListNode* head = list.getHead();
        checkTestResult(head && head->value == 1);
    }

    // Test: RemoveDuplicatesHasDuplicates
    {
        cout << "\n------ Test: RemoveDuplicatesHasDuplicates ------\n";
        
        LinkedList list(1);
        list.append(2);
        list.append(2);
        list.append(3);
        
        cout << "BEFORE:    ";
        list.printList();
        
        list.removeDuplicates();
        
        cout << "AFTER:     ";
        list.printList();
        
        // Check for duplicates
        LinkedListNode* current = list.getHead();
        bool noDuplicates = true;
        
        while (current && current->next) {
            if (current->value == current->next->value) {
                noDuplicates = false;
                break;
            }
            current = current->next;
        }
        
        checkTestResult(noDuplicates);
    }

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

    // Test 1: EmptyList
    {
        cout << "\n------ Test: EmptyList ------\n";

        LinkedList list(0);
        list.deleteFirst();

        cout << "Before: ";
        list.printList();

        list.bubbleSort();

        cout << "After: ";
        list.printList();

        checkTestResult(list.getLength() == 0);
    }

    // Test 2: SingleElement
    {
        cout << "\n------ Test: SingleElement ------\n";

        LinkedList list(5);

        cout << "Before: ";
        list.printList();

        list.bubbleSort();

        cout << "After: ";
        list.printList();

        checkTestResult(list.getHead()->value == 5 && list.getTail()->value == 5);
    }

    // Test 3: TwoElements
    {
        cout << "\n------ Test: TwoElements ------\n";

        LinkedList list(5);
        list.append(3);

        cout << "Before: ";
        list.printList();

        list.bubbleSort();

        cout << "After: ";
        list.printList();

        checkTestResult(listToVector(list) == vector<int>({3, 5}));
    }

    // Test 4: MultipleElements
    {
        cout << "\n------ Test: MultipleElements ------\n";

        LinkedList list(5);
        list.append(3);
        list.append(8);
        list.append(1);

        cout << "Before: ";
        list.printList();

        list.bubbleSort();

        cout << "After: ";
        list.printList();

        checkTestResult(listToVector(list) == vector<int>({1, 3, 5, 8}));
    }

    // Test 5: AlreadySorted
    {
        cout << "\n------ Test: AlreadySorted ------\n";

        LinkedList list(1);
        list.append(3);
        list.append(5);
        list.append(8);

        cout << "Before: ";
        list.printList();

        list.bubbleSort();

        cout << "After: ";
        list.printList();

        checkTestResult(listToVector(list) == vector<int>({1, 3, 5, 8}));
    }

    // Test 6: Reversed
    {
        cout << "\n------ Test: Reversed ------\n";

        LinkedList list(8);
        list.append(5);
        list.append(3);
        list.append(1);

        cout << "Before: ";
        list.printList();

        list.bubbleSort();

        cout << "After: ";
        list.printList();

        checkTestResult(listToVector(list) == vector<int>({1, 3, 5, 8}));
    }

    // Test 1: EmptyList
    {
        cout << "\n------ Test: EmptyList ------\n";

        LinkedList list(0);
        list.deleteFirst();

        cout << "Before: ";
        list.printList();

        list.selectionSort();

        cout << "After: ";
        list.printList();

        checkTestResult(list.getLength() == 0);
    }

    // Test 2: SingleElement
    {
        cout << "\n------ Test: SingleElement ------\n";

        LinkedList list(5);

        cout << "Before: ";
        list.printList();

        list.selectionSort();

        cout << "After: ";
        list.printList();

        checkTestResult(list.getHead()->value == 5 && list.getTail()->value == 5);
    }

    // Test 3: TwoElements
    {
        cout << "\n------ Test: TwoElements ------\n";

        LinkedList list(5);
        list.append(3);

        cout << "Before: ";
        list.printList();

        list.selectionSort();

        cout << "After: ";
        list.printList();

        checkTestResult(listToVector(list) == vector<int>({3, 5}));
    }

    // Test 4: MultipleElements
    {
        cout << "\n------ Test: MultipleElements ------\n";

        LinkedList list(5);
        list.append(3);
        list.append(8);
        list.append(1);

        cout << "Before: ";
        list.printList();

        list.selectionSort();

        cout << "After: ";
        list.printList();

        checkTestResult(listToVector(list) == vector<int>({1, 3, 5, 8}));
    }

    // Test 5: AlreadySorted
    {
        cout << "\n------ Test: AlreadySorted ------\n";

        LinkedList list(1);
        list.append(3);
        list.append(5);
        list.append(8);

        cout << "Before: ";
        list.printList();

        list.selectionSort();

        cout << "After: ";
        list.printList();

        checkTestResult(listToVector(list) == vector<int>({1, 3, 5, 8}));
    }

    // Test 6: Reversed
    {
        cout << "\n------ Test: Reversed ------\n";

        LinkedList list(8);
        list.append(5);
        list.append(3);
        list.append(1);

        cout << "Before: ";
        list.printList();

        list.selectionSort();

        cout << "After: ";
        list.printList();

        checkTestResult(listToVector(list) == vector<int>({1, 3, 5, 8}));
    }

    // Test 1: MergeTwoEmptyLists
    {
        cout << "\n------ Test: MergeTwoEmptyLists ------\n";

        LinkedList list1(0);
        list1.deleteFirst();
        LinkedList list2(0);
        list2.deleteFirst();

        cout << "List1: ";
        list1.printList();

        cout << "List2: ";
        list2.printList();

        list1.merge(list2);

        cout << "Merged: ";
        list1.printList();

        checkTestResult(list1.getLength() == 0);
    }

    // Test 2: MergeEmptyAndNonEmptyLists
    {
        cout << "\n------ Test: MergeEmptyAndNonEmptyLists ------\n";

        LinkedList list1(0);
        list1.deleteFirst();
        LinkedList list2(5);

        cout << "List1: ";
        list1.printList();

        cout << "List2: ";
        list2.printList();

        list1.merge(list2);

        cout << "Merged: ";
        list1.printList();

        checkTestResult(list1.getLength() == 1 &&
                        list1.getHead()->value == 5 &&
                        list1.getTail()->value == 5);
    }

    // Test 3: MergeTwoNonEmptyLists
    {
        cout << "\n------ Test: MergeTwoNonEmptyLists ------\n";

        LinkedList list1(3);
        list1.append(4);
        LinkedList list2(1);
        list2.append(2);

        cout << "List1: ";
        list1.printList();

        cout << "List2: ";
        list2.printList();

        list1.merge(list2);

        cout << "Merged: ";
        list1.printList();

        checkTestResult(list1.getLength() == 4);  // Additional checks could be added
    }

    // Test 4: MergeDifferentLengthLists
    {
        cout << "\n------ Test: MergeDifferentLengthLists ------\n";

        LinkedList list1(1);
        LinkedList list2(2);
        list2.append(3);
        list2.append(4);

        cout << "List1: ";
        list1.printList();

        cout << "List2: ";
        list2.printList();

        list1.merge(list2);

        cout << "Merged: ";
        list1.printList();

        checkTestResult(list1.getLength() == 4);  // Additional checks could be added
    }
    return 0;
}
