#pragma once

#include <iostream>

namespace Algorithms
{
namespace BasicSort
{
    void insertionSort(int array[], int size)
    {
        for (int i = 1; i<size; i++)
        {
            int j=i-1;
            while(j>-1 && array[j+1]<array[j])
            {
                auto temp = array[j+1];
                array[j+1]=array[j];
                array[j]=temp;
                j--;
            }
        }
    }
} // BasicSort
} // Algorithms
