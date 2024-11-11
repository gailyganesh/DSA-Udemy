#pragma once

#include <iostream>
#include <vector>

namespace Algorithms
{
void merge(int array[], int leftIdx, int middleIdx, int rightIdx)
{
    int leftArraySize = middleIdx - leftIdx+1;
    int rightArraySize = rightIdx - middleIdx;

    std::vector<int> leftArray(leftArraySize);
    std::vector<int> rightArray(rightArraySize);
    for (int i = 0; i< leftArraySize; i++)
    {
        leftArray[i]=array[leftIdx+i];
    }
    for (int j = 0; j< rightArraySize; j++)
    {
        rightArray[j]=array[j+middleIdx+1];
    }
    int leftItr=0, rightItr=0;
    while(leftItr<leftArraySize && rightItr<rightArraySize)
    {
        if(leftArray[leftItr] <= rightArray[rightItr])
        {
            array[leftIdx]=leftArray[leftItr];
            leftItr++;
            leftIdx++;
        }
        else
        {
            array[leftIdx]=rightArray[rightItr];
            rightItr++;
            leftIdx++;
        }
    }
    while(leftItr!=leftArraySize)
    {
        array[leftIdx] = leftArray[leftItr];
        leftItr++;
        leftIdx++;
    }
    while(rightItr!=rightArraySize)
    {
        array[leftIdx]=rightArray[rightItr];
        rightItr++;
        leftIdx++;
    }
}

void mergeSort(int array[], int leftIndex, int rightIndex)
{
    if(leftIndex >= rightIndex) return;
    int middleIndex = leftIndex+(rightIndex-leftIndex)/2;
    mergeSort(array, leftIndex, middleIndex);
    mergeSort(array, middleIndex+1, rightIndex);
    merge(array, leftIndex, middleIndex, rightIndex);
}
} // Algorithms
