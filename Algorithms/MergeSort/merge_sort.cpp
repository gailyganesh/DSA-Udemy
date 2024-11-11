#include "merge_sort.h"

using namespace Algorithms;
using namespace std;

// Utility function to compare two arrays for equality
bool areArraysEqual(int a[], int b[], int size) {
    for (int i = 0; i < size; i++) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

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
        cout << "\n----- Test: EqualLengthArrays -----\n";
        int arr[] = {1, 3, 5, 2, 4, 6};
        int expected[] = {1, 2, 3, 4, 5, 6};
        cout << "Original Array: "; printArray(arr, 6); cout << "\n";
        merge(arr, 0, 2, 5);
        cout << "EXPECTED: "; printArray(expected, 6); cout << "\n";
        cout << "RETURNED: "; printArray(arr, 6); cout << "\n";
        cout << (areArraysEqual(arr, expected, 6) ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: UnequalLengthArrays -----\n";
        int arr[] = {2, 4, 7, 1, 5, 6};
        int expected[] = {1, 2, 4, 5, 6, 7};
        cout << "Original Array: "; printArray(arr, 6); cout << "\n";
        merge(arr, 0, 2, 5);
        cout << "EXPECTED: "; printArray(expected, 6); cout << "\n";
        cout << "RETURNED: "; printArray(arr, 6); cout << "\n";
        cout << (areArraysEqual(arr, expected, 6) ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: OneElementEachArray -----\n";
        int arr[] = {2, 1};
        int expected[] = {1, 2};
        cout << "Original Array: "; printArray(arr, 2); cout << "\n";
        merge(arr, 0, 0, 1);
        cout << "EXPECTED: "; printArray(expected, 2); cout << "\n";
        cout << "RETURNED: "; printArray(arr, 2); cout << "\n";
        cout << (areArraysEqual(arr, expected, 2) ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: NoOverlap -----\n";
        int arr[] = {1, 3, 5, 8, 10, 2, 4, 6, 7, 9};
        int expected[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        cout << "Original Array: "; printArray(arr, 10); cout << "\n";
        merge(arr, 0, 4, 9);
        cout << "EXPECTED: "; printArray(expected, 10); cout << "\n";
        cout << "RETURNED: "; printArray(arr, 10); cout << "\n";
        cout << (areArraysEqual(arr, expected, 10) ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: FullOverlap -----\n";
        int arr[] = {3, 5, 7, 9, 11, 1, 2, 4, 6, 8, 10};
        int expected[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
        cout << "Original Array: "; printArray(arr, 11); cout << "\n";
        merge(arr, 0, 4, 10);
        cout << "EXPECTED: "; printArray(expected, 11); cout << "\n";
        cout << "RETURNED: "; printArray(arr, 11); cout << "\n";
        cout << (areArraysEqual(arr, expected, 11) ? "PASS\n" : "FAIL\n");
    }
    // SingleElementArray test
    {
        cout << "\n----- Test: SingleElementArray -----\n";
        int arr[] = {42};
        int expected[] = {42};
        cout << "Original Array: "; printArray(arr, 1); cout << "\n";
        mergeSort(arr, 0, 0);
        cout << "EXPECTED: "; printArray(expected, 1); cout << "\n";
        cout << "RETURNED: "; printArray(arr, 1); cout << "\n";
        cout << (areArraysEqual(arr, expected, 1) ? "PASS\n" : "FAIL\n");
    }

    // AlreadySortedArray test
    {
        cout << "\n----- Test: AlreadySortedArray -----\n";
        int arr[] = {1, 2, 3, 4, 5};
        int expected[] = {1, 2, 3, 4, 5};
        cout << "Original Array: "; printArray(arr, 5); cout << "\n";
        mergeSort(arr, 0, 4);
        cout << "EXPECTED: "; printArray(expected, 5); cout << "\n";
        cout << "RETURNED: "; printArray(arr, 5); cout << "\n";
        cout << (areArraysEqual(arr, expected, 5) ? "PASS\n" : "FAIL\n");
    }

    // ReverseSortedArray test
    {
        cout << "\n----- Test: ReverseSortedArray -----\n";
        int arr[] = {5, 4, 3, 2, 1};
        int expected[] = {1, 2, 3, 4, 5};
        cout << "Original Array: "; printArray(arr, 5); cout << "\n";
        mergeSort(arr, 0, 4);
        cout << "EXPECTED: "; printArray(expected, 5); cout << "\n";
        cout << "RETURNED: "; printArray(arr, 5); cout << "\n";
        cout << (areArraysEqual(arr, expected, 5) ? "PASS\n" : "FAIL\n");
    }

    // RandomArray test
    {
        cout << "\n----- Test: RandomArray -----\n";
        int arr[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
        int expected[] = {1, 1, 2, 3, 3, 4, 5, 5, 5, 6, 9};
        cout << "Original Array: "; printArray(arr, 11); cout << "\n";
        mergeSort(arr, 0, 10);
        cout << "EXPECTED: "; printArray(expected, 11); cout << "\n";
        cout << "RETURNED: "; printArray(arr, 11); cout << "\n";
        cout << (areArraysEqual(arr, expected, 11) ? "PASS\n" : "FAIL\n");
    }

    // DuplicatesArray test
    {
        cout << "\n----- Test: DuplicatesArray -----\n";
        int arr[] = {3, 3, 3, 1, 2, 2, 2};
        int expected[] = {1, 2, 2, 2, 3, 3, 3};
        cout << "Original Array: "; printArray(arr, 7); cout << "\n";
        mergeSort(arr, 0, 6);
        cout << "EXPECTED: "; printArray(expected, 7); cout << "\n";
        cout << "RETURNED: "; printArray(arr, 7); cout << "\n";
        cout << (areArraysEqual(arr, expected, 7) ? "PASS\n" : "FAIL\n");
    }

    // LargeSizeArray test
    {
        cout << "\n----- Test: LargeSizeArray -----\n";
        const int SIZE = 1000;
        int arr[SIZE];
        int expected[SIZE];
        for (int i = 0; i < SIZE; i++) {
            arr[i] = SIZE - i;
            expected[i] = i + 1;
        }
        cout << "Array: SIZE 1000" << "\n";
        mergeSort(arr, 0, SIZE - 1);
        // cout << "EXPECTED: "; printArray(expected, SIZE); cout << "\n";
        // cout << "RETURNED: "; printArray(arr, SIZE); cout << "\n";
        cout << (areArraysEqual(arr, expected, SIZE) ? "PASS\n" : "FAIL\n");
    }

    // NegativeNumbersArray test
    {
        cout << "\n----- Test: NegativeNumbersArray -----\n";
        int arr[] = {3, -1, 4, -5, 6, -2};
        int expected[] = {-5, -2, -1, 3, 4, 6};
        cout << "Original Array: "; printArray(arr, 6); cout << "\n";
        mergeSort(arr, 0, 5);
        cout << "EXPECTED: "; printArray(expected, 6); cout << "\n";
        cout << "RETURNED: "; printArray(arr, 6); cout << "\n";
        cout << (areArraysEqual(arr, expected, 6) ? "PASS\n" : "FAIL\n");
    }
    return 0;
}