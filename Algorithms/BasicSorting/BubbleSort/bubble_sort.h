#pragma once

#include <iostream>

namespace Algorithms
{
namespace BasicSort
{
    void bubbleSort(int array[], int size)
    {
        for (int i = size-1; i>0; i--)
        {
            for(int j=0; j<i; j++)
            {
                if(j<size && array[j]>array[j+1])
                {
                    auto temp = array[j];
                    array[j] = array[j+1];
                    array[j+1] = temp;
                }
            }
        }
    }
} // BasicSort
} // Algorithms
