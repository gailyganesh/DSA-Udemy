#pragma once

#include <iostream>
#include <vector>

// which is used in priority_queue in C++ because of O(logn)
// Here it is max heap where max value at top
class Heap {
private:
  std::vector<int> mHeap;
  int leftChild(int index);
  int rightChild(int index);
  int parent(int index);
  void swap(int index1, int index2);
  void sinkDown(int index);

public:
  Heap();
  ~Heap();
  void printHeap();
  const std::vector<int> &getHeap();
  void insert(int value);
  int remove();
};

class MinHeap {
private:
  std::vector<int> mMinHeap;
  int leftChild(int index);
  int rightChild(int index);
  int parent(int index);
  void swap(int index1, int index2);
  void sinkDown(int index);

public:
  MinHeap() = default;
  ~MinHeap() = default;
  void printMinHeap();
  const std::vector<int> &getMinHeap();
  void insert(int value);
  int remove();
};