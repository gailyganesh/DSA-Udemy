#pragma once

#include <iostream>
#include <vector>

namespace Algorithms
{

void swap(int array[], int firstIndex, int secondIndex)
{
    int temp = array[firstIndex];
    array[firstIndex] = array[secondIndex];
    array[secondIndex] = temp;
}
int pivot(int array[], int pivotIdx, int endIdx)
{
    int swapIdx=pivotIdx;
    for(int i=pivotIdx+1; i<=endIdx; i++)
    {
        if(array[i]<array[pivotIdx])
        {
            swapIdx++;
            swap(array, i, swapIdx);
        }
    }
    swap(array, pivotIdx, swapIdx);
    return swapIdx;
}

void quickSort(int array[], int leftIndex, int rightIndex)
{
    if(leftIndex>=rightIndex) return;
    auto pivotIdx = pivot(array,leftIndex,rightIndex);
    quickSort(array,leftIndex,pivotIdx-1);
    quickSort(array,pivotIdx+1, rightIndex);
}
} // Algorithms
