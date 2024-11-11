#include "quick_sort.h"
#include <algorithm>

using namespace Algorithms;
using namespace std;

void printArray(int arr[], int size) {
    cout << "[";
    for (int i = 0; i < size; i++) {
        cout << arr[i];
        if (i != size - 1) {
            cout << ", ";
        }
    }
    cout << "]";
}

int main()
{
    {
        cout << "\n----- Test: SimpleArray -----\n";
        int array[] = {4, 2, 8, 5, 3};
        cout << "Before: "; printArray(array, 5); cout << "\n";
        int swapIndex = pivot(array, 0, 4);
        cout << "After: "; printArray(array, 5); cout << "\n";
        cout << "Swap Index: " << swapIndex << ", Value: " << array[swapIndex] << "\n";
        cout << (swapIndex == 2 && array[swapIndex] == 4 ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: AllElementsEqual -----\n";
        int array[] = {5, 5, 5, 5, 5};
        cout << "Before: "; printArray(array, 5); cout << "\n";
        int swapIndex = pivot(array, 0, 4);
        cout << "After: "; printArray(array, 5); cout << "\n";
        cout << "Swap Index: " << swapIndex << ", Value: " << array[swapIndex] << "\n";
        cout << (swapIndex == 0 && array[swapIndex] == 5 ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: AlreadySorted -----\n";
        int array[] = {1, 2, 3, 4, 5};
        cout << "Before: "; printArray(array, 5); cout << "\n";
        int swapIndex = pivot(array, 0, 4);
        cout << "After: "; printArray(array, 5); cout << "\n";
        cout << "Swap Index: " << swapIndex << ", Value: " << array[swapIndex] << "\n";
        cout << (swapIndex == 0 && array[swapIndex] == 1 ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: ReverseSorted -----\n";
        int array[] = {5, 4, 3, 2, 1};
        cout << "Before: "; printArray(array, 5); cout << "\n";
        int swapIndex = pivot(array, 0, 4);
        cout << "After: "; printArray(array, 5); cout << "\n";
        cout << "Swap Index: " << swapIndex << ", Value: " << array[swapIndex] << "\n";
        cout << (swapIndex == 4 && array[swapIndex] == 5 ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: PivotInMiddle -----\n";
        int array[] = {3, 5, 2, 1, 4};
        cout << "Before: "; printArray(array, 5); cout << "\n";
        int swapIndex = pivot(array, 1, 4);
        cout << "After: "; printArray(array, 5); cout << "\n";
        cout << "Swap Index: " << swapIndex << ", Value: " << array[swapIndex] << "\n";
        cout << (swapIndex == 4 && array[swapIndex] == 5 ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: SingleElement -----\n";
        int array[] = {3};
        cout << "Before: "; printArray(array, 1); cout << "\n";
        int swapIndex = pivot(array, 0, 0);
        cout << "After: "; printArray(array, 1); cout << "\n";
        cout << "Swap Index: " << swapIndex << ", Value: " << array[swapIndex] << "\n";
        cout << (swapIndex == 0 && array[swapIndex] == 3 ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: SimpleArray -----\n";
        int array[] = {4, 2, 8, 5, 3};
        cout << "Before: "; printArray(array, 5); cout << "\n";
        quickSort(array, 0, 4);
        cout << "After: "; printArray(array, 5); cout << "\n";
        cout << (std::is_sorted(array, array + 5) ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: AllElementsEqual -----\n";
        int array[] = {5, 5, 5, 5, 5};
        cout << "Before: "; printArray(array, 5); cout << "\n";
        quickSort(array, 0, 4);
        cout << "After: "; printArray(array, 5); cout << "\n";
        cout << (std::is_sorted(array, array + 5) ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: AlreadySorted -----\n";
        int array[] = {1, 2, 3, 4, 5};
        cout << "Before: "; printArray(array, 5); cout << "\n";
        quickSort(array, 0, 4);
        cout << "After: "; printArray(array, 5); cout << "\n";
        cout << (std::is_sorted(array, array + 5) ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: ReverseSorted -----\n";
        int array[] = {5, 4, 3, 2, 1};
        cout << "Before: "; printArray(array, 5); cout << "\n";
        quickSort(array, 0, 4);
        cout << "After: "; printArray(array, 5); cout << "\n";
        cout << (std::is_sorted(array, array + 5) ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: SingleElement -----\n";
        int array[] = {3};
        cout << "Before: "; printArray(array, 1); cout << "\n";
        quickSort(array, 0, 0);
        cout << "After: "; printArray(array, 1); cout << "\n";
        cout << (std::is_sorted(array, array + 1) ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: MultipleDuplicates -----\n";
        int array[] = {5, 3, 3, 2, 2};
        cout << "Before: "; printArray(array, 5); cout << "\n";
        quickSort(array, 0, 4);
        cout << "After: "; printArray(array, 5); cout << "\n";
        cout << (std::is_sorted(array, array + 5) ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: LargeArray -----\n";
        int array[1000];
        for (int i = 0; i < 1000; i++) {
            array[i] = rand() % 1000; // Values between 0 and 999
        }
        cout << "Array: SIZE 1000\n";
        quickSort(array, 0, 999);
        cout << (std::is_sorted(array, array + 1000) ? "PASS\n" : "FAIL\n");
    }
    return 0;
}