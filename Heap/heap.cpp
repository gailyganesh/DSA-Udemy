#include "heap.h"

using namespace std;

Heap::Heap() {}

Heap::~Heap() {}

void Heap::printHeap() {
  std::cout << "[ ";
  for (auto i : mHeap) {
    std::cout << i;
  }
  std::cout << " ]";
}

int Heap::leftChild(int index) {
  return (index * 2) + 1; // without leaving 0th element empty
}

int Heap::rightChild(int index) {
  return (index * 2) + 2; // without leaving 0th element empty
}

int Heap::parent(int index) { return (index - 1) / 2; }

void Heap::swap(int index1, int index2) {
  auto temp = mHeap[index1];
  mHeap[index1] = mHeap[index2];
  mHeap[index2] = temp;
}

void Heap::insert(int value) {
  mHeap.push_back(value);
  int currentIdx = mHeap.size() - 1;
  while (true) {
    int parentIdx = parent(currentIdx);
    if (parentIdx < 0)
      break;
    else if (value > mHeap[parentIdx]) {
      swap(parentIdx, currentIdx);
      currentIdx = parentIdx;
    } else {
      break;
    }
  }
}

int Heap::remove() {
  if (mHeap.empty()) {
    return INT_MIN;
  }
  auto max_value = mHeap.front();
  if (mHeap.size() == 1) {
    mHeap.pop_back();
  } else {
    mHeap[0] = mHeap.back();
    mHeap.pop_back();
    sinkDown(0);
  }
  return max_value;
}

void Heap::sinkDown(int index) {
  int maxIdx = index;
  while (true) {
    int leftchildIdx = leftChild(maxIdx);
    int rightchildIdx = leftchildIdx + 1;
    if (leftchildIdx < mHeap.size() && mHeap[leftchildIdx] > mHeap[maxIdx]) {
      maxIdx = leftchildIdx;
    }
    if (rightchildIdx < mHeap.size() && mHeap[rightchildIdx] > mHeap[maxIdx]) {
      maxIdx = rightchildIdx;
    }
    if (maxIdx != index) {
      swap(maxIdx, index);
      index = maxIdx;
    } else {
      return;
    }
  }
}

const std::vector<int> &Heap::getHeap() { return mHeap; }

void MinHeap::printMinHeap() {
  std::cout << "[ ";
  for (auto i : mMinHeap) {
    std::cout << i;
  }
  std::cout << " ]";
}

int MinHeap::leftChild(int index) {
  return (index * 2) + 1; // without leaving 0th element empty
}

int MinHeap::rightChild(int index) {
  return (index * 2) + 2; // without leaving 0th element empty
}

int MinHeap::parent(int index) { return (index - 1) / 2; }

void MinHeap::swap(int index1, int index2) {
  auto temp = mMinHeap[index1];
  mMinHeap[index1] = mMinHeap[index2];
  mMinHeap[index2] = temp;
}

void MinHeap::insert(int value) {
  mMinHeap.push_back(value);
  int currentIdx = mMinHeap.size() - 1;
  while (true) {
    int parentIdx = parent(currentIdx);
    if (parentIdx < 0)
      break;
    else if (value < mMinHeap[parentIdx]) {
      swap(parentIdx, currentIdx);
      currentIdx = parentIdx;
    } else {
      break;
    }
  }
}

int MinHeap::remove() {
  if (mMinHeap.empty()) {
    return INT_MIN;
  }
  auto min_value = mMinHeap.front();
  if (mMinHeap.size() == 1) {
    mMinHeap.pop_back();
  } else {
    mMinHeap[0] = mMinHeap.back();
    mMinHeap.pop_back();
    sinkDown(0);
  }
  return min_value;
}

void MinHeap::sinkDown(int index) {
  int minIdx = index;
  while (true) {
    int leftchildIdx = leftChild(minIdx);
    int rightchildIdx = leftchildIdx + 1;
    if (leftchildIdx < mMinHeap.size() &&
        mMinHeap[leftchildIdx] < mMinHeap[minIdx]) {
      minIdx = leftchildIdx;
    }
    if (rightchildIdx < mMinHeap.size() &&
        mMinHeap[rightchildIdx] < mMinHeap[minIdx]) {
      minIdx = rightchildIdx;
    }
    if (minIdx != index) {
      swap(minIdx, index);
      index = minIdx;
    } else {
      return;
    }
  }
}

const std::vector<int> &MinHeap::getMinHeap() { return mMinHeap; }

int main() {
  {
    Heap heap;
    // Insert values into the heap
    vector<int> values = {10, 20, 30, 5, 15, 25, 35};
    cout << "Inserting values: ";
    for (int value : values) {
      cout << value << " ";
      heap.insert(value);

      // Verify max heap property
      const vector<int> &currentHeap = heap.getHeap();
      bool isValidMaxHeap = true;
      for (size_t i = 0; i < currentHeap.size(); i++) {
        int left = 2 * i + 1;  // Calculating left child index
        int right = 2 * i + 2; // Calculating right child index
        if (left < currentHeap.size() && currentHeap[i] < currentHeap[left]) {
          isValidMaxHeap = false;
          break;
        }
        if (right < currentHeap.size() && currentHeap[i] < currentHeap[right]) {
          isValidMaxHeap = false;
          break;
        }
      }

      cout << "\nHeap after insertion: ";
      heap.printHeap();
      cout << "Max Heap Property Valid? " << (isValidMaxHeap ? "Yes" : "No")
           << "\n";
    }

    // Final Heap structure
    cout << "\nFinal Heap Structure: ";
    heap.printHeap();
  }

  {
    Heap heap;

    // Insert values into the heap
    vector<int> valuesToInsert = {10, 20, 30, 5, 15, 25, 35};
    cout << "Inserting values: ";
    for (int value : valuesToInsert) {
      cout << value << " ";
      heap.insert(value);
    }
    cout << "\nInitial Heap: ";
    heap.printHeap();

    // Remove values from the heap and test after each removal
    while (!heap.getHeap().empty()) {
      int removedValue = heap.remove();
      cout << "\nRemoved Value: " << removedValue;
      cout << "\nHeap after removal: ";
      heap.printHeap();

      // Verify max heap property
      const vector<int> &currentHeap = heap.getHeap();
      bool isValidMaxHeap = true;
      for (size_t i = 0; i < currentHeap.size(); i++) {
        int left = 2 * i + 1;  // Calculating left child index
        int right = 2 * i + 2; // Calculating right child index
        if (left < currentHeap.size() && currentHeap[i] < currentHeap[left]) {
          isValidMaxHeap = false;
          break;
        }
        if (right < currentHeap.size() && currentHeap[i] < currentHeap[right]) {
          isValidMaxHeap = false;
          break;
        }
      }

      cout << "\nMax Heap Property Valid? " << (isValidMaxHeap ? "Yes" : "No")
           << "\n";
    }

    // Check if heap is empty at the end
    cout << "\nFinal Heap (Should be empty): ";
    heap.printHeap();
  }

  {
    MinHeap heap;

    // Insert values into the heap
    vector<int> values = {35, 25, 15, 5, 20, 30, 10};
    cout << "Inserting values: ";
    for (int value : values) {
      cout << value << " ";
      heap.insert(value);

      // Verify min heap property
      const vector<int> &currentHeap = heap.getMinHeap();
      bool isValidMinHeap = true;
      for (size_t i = 0; i < currentHeap.size(); i++) {
        int left = 2 * i + 1;  // Calculating left child index
        int right = 2 * i + 2; // Calculating right child index
        if (left < currentHeap.size() && currentHeap[i] > currentHeap[left]) {
          isValidMinHeap = false;
          break;
        }
        if (right < currentHeap.size() && currentHeap[i] > currentHeap[right]) {
          isValidMinHeap = false;
          break;
        }
      }

      cout << "\nHeap after insertion: ";
      heap.printMinHeap();
      cout << "Min Heap Property Valid? " << (isValidMinHeap ? "Yes" : "No")
           << "\n";
    }

    // Final Heap structure
    cout << "\nFinal Heap Structure: ";
    heap.printMinHeap();
  }

  {
    MinHeap heap;

    // Insert values into the heap
    vector<int> valuesToInsert = {35, 25, 15, 5, 20, 30, 10};
    cout << "Inserting values: ";
    for (int value : valuesToInsert) {
      cout << value << " ";
      heap.insert(value);
    }
    cout << "\nInitial Heap: ";
    heap.printMinHeap();

    // Remove values from the heap and test after each removal
    while (!heap.getMinHeap().empty()) {
      int removedValue = heap.remove();
      cout << "\nRemoved Value: " << removedValue;
      cout << "\nHeap after removal: ";
      heap.printMinHeap();

      // Verify min heap property
      const vector<int> &currentHeap = heap.getMinHeap();
      bool isValidMinHeap = true;
      for (size_t i = 0; i < currentHeap.size(); i++) {
        int left = 2 * i + 1;  // Calculating left child index
        int right = 2 * i + 2; // Calculating right child index
        if (left < currentHeap.size() && currentHeap[i] > currentHeap[left]) {
          isValidMinHeap = false;
          break;
        }
        if (right < currentHeap.size() && currentHeap[i] > currentHeap[right]) {
          isValidMinHeap = false;
          break;
        }
      }

      cout << "\nMin Heap Property Valid? " << (isValidMinHeap ? "Yes" : "No")
           << "\n";
    }

    // Check if heap is empty at the end
    cout << "\nFinal Heap (Should be empty): ";
    heap.printMinHeap();
  }

  {
    MinHeap heap;

    // Insert values into the heap
    vector<int> valuesToInsert = {35, 25, 15, 5, 20, 30, 10};
    cout << "Inserting values: ";
    for (int value : valuesToInsert) {
      cout << value << " ";
      heap.insert(value);
    }
    cout << "\nInitial Heap: ";
    heap.printMinHeap();

    // Remove values from the heap and test after each removal
    while (!heap.getMinHeap().empty()) {
      int removedValue = heap.remove();
      cout << "\nRemoved Value: " << removedValue;
      cout << "\nHeap after removal: ";
      heap.printMinHeap();

      // Verify min heap property
      const vector<int> &currentHeap = heap.getMinHeap();
      bool isValidMinHeap = true;
      for (size_t i = 0; i < currentHeap.size(); i++) {
        int left = 2 * i + 1;  // Calculating left child index
        int right = 2 * i + 2; // Calculating right child index
        if (left < currentHeap.size() && currentHeap[i] > currentHeap[left]) {
          isValidMinHeap = false;
          break;
        }
        if (right < currentHeap.size() && currentHeap[i] > currentHeap[right]) {
          isValidMinHeap = false;
          break;
        }
      }

      cout << "\nMin Heap Property Valid? " << (isValidMinHeap ? "Yes" : "No")
           << "\n";
    }

    // Check if heap is empty at the end
    cout << "\nFinal Heap (Should be empty): ";
    heap.printMinHeap();
  }
  return 0;
}