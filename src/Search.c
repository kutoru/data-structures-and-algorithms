#include "Search.h"

int binarySearch(int* array, int len, int value) {
    int lo = 0;
    int hi = len;

    do {
        int m = lo + (hi - lo) / 2;
        int v = array[m];

        if (v == value) {
            return m;
        } else if (v > value) {
            hi = m;
        } else {
            lo = m + 1;
        }

    } while (lo < hi);

    return -1;
}

// rare O(sqrt(N)) algorithm
int boolSearch(bool* array, int len) {
    int jumpAmount = sqrt(len);
    int i;

    for (i = jumpAmount; i < len; i += jumpAmount) {
        if (array[i]) {
            break;
        }
    }

    i -= jumpAmount;

    for (int j = 0; j <= jumpAmount && i < len; j++, i++) {
        if (array[i]) {
            return i;
        }
    }

    return -1;
}

void searchTest() {
    printf("Search test\n");

    int len = 50;
    int intArray[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43, 45, 47, 49, 51, 53, 55, 57, 59, 61, 63, 65, 67, 69, 71, 73, 75, 77, 79, 81, 83, 85, 87, 89, 91, 93, 95, 97, 99};

    // Should be 34
    printf("Binary search: %d\n", binarySearch(intArray, len, 69));

    len = 50;
    bool boolArray[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

    // Should be 21
    printf("Bool search: %d\n", boolSearch(boolArray, len));
}
