#include "queue.h"
#include <string>

using namespace std;

Queue::Queue(int value) {
    mFirst=new LinkedListNode(value);
    mLast=mFirst;
    mLength=1;
}

Queue::~Queue() {
    makeEmpty();
}

void Queue::makeEmpty()
{
    while(mFirst)
    {
        auto temp = mFirst;
        mFirst=mFirst->next;
        delete temp;
        mLength--;
    }
    mLast = nullptr;
}

void Queue::printQueue()
{
    auto temp = mFirst;
    while(temp)
    {
        std::cout << temp->value << std::endl;
        temp=temp->next;
    }
}

LinkedListNode* Queue::getFirst()
{
    return mFirst;
}

LinkedListNode* Queue::getLast()
{
    return mLast;
}

int Queue::getLength()
{
    return mLength;
}

void Queue::enqueue(int value)
{
    auto newNode = new LinkedListNode(value);
    if(mFirst==nullptr)
    {
        mFirst=newNode;
        mLast=newNode;
    }
    else
    {
        mLast->next=newNode;
        mLast=newNode;
    }
    mLength++;
}

int Queue::dequeue()
{
    if(mFirst==nullptr) return INT_MIN;
    auto temp=mFirst;
    auto DequeuedValue=temp->value;
    mFirst=mFirst->next;
    delete temp;
    mLength--;
    return DequeuedValue;
}

bool Queue::isEmpty()
{
    return mFirst?false:true;
}

 // Helper function to check test result
    auto checkTestResult = [](bool condition) {
        cout << (condition ? "PASS" : "FAIL") << endl;
    };

int main()
{
    // Test 1: Constructor initializes length to 1
    {
        cout << "\n------ Queue Test: Constructor Initializes Length to One ------\n";
        Queue q(5);
        cout << "Expected Length: 1\n";
        cout << "Actual Length: " << q.getLength() << "\n";
        
        checkTestResult(q.getLength() == 1);
    }

    // Test 2: Constructor initializes first node value
    {
        cout << "\n------ Queue Test: Constructor Initializes First Node Value ------\n";
        Queue q(5);
        auto first = q.getFirst();
        
        cout << "Expected First Value: 5\n";
        cout << "Actual First Value: " << first->value << "\n";
        
        checkTestResult(first->value == 5);
    }

    // Test 3: Constructor sets first and last node to same
    {
        cout << "\n------ Queue Test: Constructor Sets First and Last Node to Same ------\n";
        Queue q(5);
        auto first = q.getFirst();
        auto last = q.getLast();
        
        cout << "First and Last should be same\n";
        
        checkTestResult(first == last);
    }

    // Test 4: Check if queue is empty returns false
    {
        cout << "\n------ Queue Test: Check If Queue Is Empty Returns False ------\n";
        Queue q(0);
        
        cout << "Expected: Queue is not empty\n";
        
        checkTestResult(!q.isEmpty());
    }

    // Test 5: Constructor initializes with negative value
    {
        cout << "\n------ Queue Test: Constructor Initializes With Negative Value ------\n";
        Queue q(-5);
        auto first = q.getFirst();
        
        cout << "Expected First Value: -5\n";
        cout << "Actual First Value: " << first->value << "\n";
        
        checkTestResult(first->value == -5);
    }

    // Test 6: Constructor initializes with large value
    {
        cout << "\n------ Queue Test: Constructor Initializes With Large Value ------\n";
        Queue q(999999);
        auto first = q.getFirst();
        
        cout << "Expected First Value: 999999\n";
        cout << "Actual First Value: " << first->value << "\n";
        
        checkTestResult(first->value == 999999);
    }

    // Test: Enqueue Operation with Initially Non-Empty Queue
    {
        cout << "\n----- Test: Non-Empty Queue -----\n";
        Queue queue(10);
        
        // Enqueue 20
        queue.enqueue(20);
        cout << "After enqueue 20 - First value: " << queue.getFirst()->value << " - EXPECTED: 10\n";
        cout << "Last value: " << queue.getLast()->value << " - EXPECTED: 20\n";
        cout << "Length: " << queue.getLength() << " - EXPECTED: 2\n";

        // Enqueue 30
        queue.enqueue(30);
        cout << "After enqueue 30 - First value: " << queue.getFirst()->value << " - EXPECTED: 10\n";
        cout << "Last value: " << queue.getLast()->value << " - EXPECTED: 30\n";
        cout << "Length: " << queue.getLength() << " - EXPECTED: 3\n";

        cout << ((queue.getFirst()->value == 10) && (queue.getLast()->value == 30) && 
                 (queue.getLength() == 3) ? "PASS\n" : "FAIL\n");
    }

    // Test: Enqueue Operation with Initially Empty Queue
    {
        cout << "\n----- Test: Empty Queue -----\n";
        Queue queue(10);
        queue.makeEmpty();
        cout << "After makeEmpty - Length: " << queue.getLength() << " - EXPECTED: 0\n";
        cout << "Queue is " << (queue.isEmpty() ? "empty" : "not empty") << " - EXPECTED: empty\n";

        // Enqueue 40 to an empty queue
        queue.enqueue(40);
        cout << "After enqueue 40 - First value: " << queue.getFirst()->value << " - EXPECTED: 40\n";
        cout << "Last value: " << queue.getLast()->value << " - EXPECTED: 40\n";
        cout << "Length: " << queue.getLength() << " - EXPECTED: 1\n";

        cout << ((queue.getFirst()->value == 40) && (queue.getLast()->value == 40) && 
                 (queue.getLength() == 1) ? "PASS\n" : "FAIL\n");
    }

    // Test: Dequeue Operation on Non-Empty Queue
    {
        cout << "\n----- Test: Dequeue Operation on Non-Empty Queue -----\n";
        Queue queue(10);
        queue.enqueue(20);
        queue.enqueue(30);

        // Dequeue first value
        cout << "Dequeue result: " << queue.dequeue() << " - EXPECTED: 10\n";
        cout << "First value: " << queue.getFirst()->value << " - EXPECTED: 20\n";
        cout << "Last value: " << queue.getLast()->value << " - EXPECTED: 30\n";
        cout << "Length: " << queue.getLength() << " - EXPECTED: 2\n";

        // Dequeue second value
        cout << "Dequeue result: " << queue.dequeue() << " - EXPECTED: 20\n";
        cout << "First value: " << queue.getFirst()->value << " - EXPECTED: 30\n";
        cout << "Last value: " << queue.getLast()->value << " - EXPECTED: 30\n";
        cout << "Length: " << queue.getLength() << " - EXPECTED: 1\n";

        cout << ((queue.getFirst()->value == 30) && (queue.getLast()->value == 30) && 
                 (queue.getLength() == 1) ? "PASS\n" : "FAIL\n");
    }

    // Test: Dequeue Operation on Empty Queue
    {
        cout << "\n----- Test: Dequeue Operation on Empty Queue -----\n";
        Queue queue(10);
        queue.makeEmpty();

        // Dequeue from empty queue
        cout << "Dequeue result: " << queue.dequeue() << " - EXPECTED: " << INT_MIN << "\n";
        cout << "Length: " << queue.getLength() << " - EXPECTED: 0\n";

        cout << ((queue.getLength() == 0) ? "PASS\n" : "FAIL\n");
    }

    // Test: Dequeue Operation Until the Queue is Empty
    {
        cout << "\n----- Test: Dequeue Operation Until the Queue is Empty -----\n";
        Queue queue(10);
        queue.enqueue(20);
        queue.enqueue(30);

        // Dequeue all values
        cout << "Dequeue result: " << queue.dequeue() << " - EXPECTED: 10\n";
        cout << "Dequeue result: " << queue.dequeue() << " - EXPECTED: 20\n";
        cout << "Dequeue result: " << queue.dequeue() << " - EXPECTED: 30\n";

        // Dequeue from empty queue
        cout << "Dequeue result: " << queue.dequeue() << " - EXPECTED: " << INT_MIN << "\n";
        cout << "Length: " << queue.getLength() << " - EXPECTED: 0\n";
        cout << "Queue is " << (queue.isEmpty() ? "empty" : "not empty") << " - EXPECTED: empty\n";

        cout << ((queue.getLength() == 0) && queue.isEmpty() ? "PASS\n" : "FAIL\n");
    }
    return 0;
}