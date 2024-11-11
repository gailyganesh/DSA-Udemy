#pragma once

#include <iostream>

namespace Algorithms
{
namespace BasicSort
{
    void selectionSort(int array[], int size)
    {
        for (int i = 0; i<size; i++)
        {
            int minIndex=i;
            for(int j=i+1; j<size; j++)
            {
                if(array[j]<array[minIndex])
                {
                    minIndex = j;
                }
            }
            if(minIndex != i)
            {
                auto temp = array[minIndex];
                array[minIndex] = array[i];
                array[i] = temp;
            }
        }
    }
} // BasicSort
} // Algorithms
