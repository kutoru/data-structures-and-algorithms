#include "Sort.h"

void printArray(int* array, int len) {
    for (int i = 0; i < len; i++) {
        printf("%d ", array[i]);
    }
    printf(";\n");
}

void bubbleSort(int* array, int len) {
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

int _qsPartition(int* array, int lo, int hi) {
    int pivot = array[hi];
    int index = lo - 1;

    for (int i = lo; i < hi; i++) {
        if (array[i] <= pivot) {
            index++;
            int temp = array[i];
            array[i] = array[index];
            array[index] = temp;
        }
    }

    index++;
    array[hi] = array[index];
    array[index] = pivot;

    return index;
}

void _qsHelper(int* array, int lo, int hi) {
    if (lo >= hi) {
        return;
    }

    int pivotIndex = _qsPartition(array, lo, hi);

    _qsHelper(array, lo, pivotIndex - 1);
    _qsHelper(array, pivotIndex + 1, hi);
}

void quickSort(int* array, int len) {
    _qsHelper(array, 0, len - 1);
}

void sortTest() {
    printf("Sort test\n");

    int len = 50;
    int array1[] = {48, 73, 55, 96, 4, 35, 12, 38, 30, 92, 71, 25, 19, 47, 53, 88, 7, 69, 83, 15, 75, 93, 54, 28, 34, 57, 81, 46, 64, 61, 79, 94, 67, 86, 99, 6, 76, 26, 23, 27, 39, 32, 2, 66, 97, 9, 98, 44, 95, 45};

    printArray(array1, len);
    bubbleSort(array1, len);
    printArray(array1, len);

    len = 50;
    int array2[] = {62, 17, 4, 85, 93, 50, 41, 31, 27, 92, 79, 56, 8, 81, 23, 6, 89, 54, 91, 60, 80, 98, 84, 19, 65, 66, 53, 68, 12, 71, 9, 32, 2, 69, 1, 95, 97, 73, 14, 36, 77, 78, 90, 59, 63, 57, 47, 70, 29, 18};

    printArray(array2, len);
    quickSort(array2, len);
    printArray(array2, len);
}
