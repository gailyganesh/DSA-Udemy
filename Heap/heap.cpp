#include "heap.h"

using namespace std;

Heap::Heap() {
}

Heap::~Heap() {
}

void Heap::printHeap() {
  std::cout << "[ ";
  for(auto i:mHeap)
  {
    std::cout << i;
  }
  std::cout << " ]";
}

int Heap::leftChild(int index)
{
  return (index*2)+1; // without leaving 0th element empty
}

int Heap::rightChild(int index)
{
  return (index*2)+2; // without leaving 0th element empty
}

int Heap::parent(int index)
{
  return (index-1)/2;
}

void Heap::swap(int index1, int index2)
{
  auto temp = mHeap[index1];
  mHeap[index1]=mHeap[index2];
  mHeap[index2]=temp;
}

void Heap::insert(int value)
{
  mHeap.push_back(value);
  int currentIdx = mHeap.size()-1;
  while(true)
  {
    int parentIdx = parent(currentIdx);
    if(parentIdx<0) break;
    else if(value>mHeap[parentIdx])
    {
      swap(parentIdx, currentIdx);
      currentIdx=parentIdx;
    }
    else
    {
      break;
    }
  }
}

int Heap::remove()
{
  if(mHeap.empty())
  {
    return INT_MIN;
  }
  auto max_value=mHeap.front();
  if(mHeap.size()==1)
  {
    mHeap.pop_back();
  }
  else
  {
    mHeap[0]=mHeap.back();
    mHeap.pop_back();
    sinkDown(0);
  }
  return max_value;
}

void Heap::sinkDown(int index)
{
  int maxIdx=index;
  while(true)
  {
    int leftchildIdx=leftChild(maxIdx);
    int rightchildIdx=leftchildIdx+1;
    if(leftchildIdx<mHeap.size() && mHeap[leftchildIdx]>mHeap[maxIdx])
    {
      maxIdx=leftchildIdx;
    }
    if(rightchildIdx<mHeap.size() && mHeap[rightchildIdx]>mHeap[maxIdx])
    {
      maxIdx=rightchildIdx;
    }
    if(maxIdx!=index)
    {
      swap(maxIdx,index);
      index=maxIdx;
    }
    else
    {
      return;
    }
  }
}

int main() {
  return 0;
}