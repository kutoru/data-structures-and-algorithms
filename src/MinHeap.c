#include "MinHeap.h"

MinHeap* mhNew(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->array = alNew(capacity);
    return heap;
}

void mhDelete(MinHeap** heap) {
    alDelete(&(*heap)->array);
    free(*heap);
    *heap = NULL;
}

void mhPrint(MinHeap* heap) {
    if (!heap) {
        printf("The heap is NULL;\n");
        return;
    }
    alPrint(heap->array);
}

int _getParent(int index) {
    return (index - 1) / 2;
}

int _getLeftChild(int index) {
    return index * 2 + 1;
}

int _getRightChild(int index) {
    return index * 2 + 2;
}

void _heapifyUp(MinHeap* heap, int index) {
    if (index == 0) {
        return;
    }

    int parentIndex = _getParent(index);
    char parent = alGet(heap->array, parentIndex);
    char value = alGet(heap->array, index);

    if (parent > value) {
        alReplace(heap->array, index, parent);
        alReplace(heap->array, parentIndex, value);
        _heapifyUp(heap, parentIndex);
    }
}

void _heapifyDown(MinHeap* heap, int index) {
    if (index >= heap->array->length) {
        return;
    }

    int leftIndex = _getLeftChild(index);
    int rightIndex = _getRightChild(index);

    if (leftIndex >= heap->array->length) {
        return;
    }

    char leftValue = alGet(heap->array, leftIndex);
    char rightValue = alGet(heap->array, rightIndex);
    char value = alGet(heap->array, index);

    if (leftValue > rightValue && value > rightValue) {
        alReplace(heap->array, index, rightValue);
        alReplace(heap->array, rightIndex, value);
        _heapifyDown(heap, rightIndex);
    } else if (rightValue > leftValue && value > leftValue) {
        alReplace(heap->array, index, leftValue);
        alReplace(heap->array, leftIndex, value);
        _heapifyDown(heap, leftIndex);
    }
}

void mhPush(MinHeap* heap, char value) {
    alPush(heap->array, value);
    _heapifyUp(heap, heap->array->length - 1);
}

char mhPop(MinHeap* heap) {
    if (heap->array->length == 0) {
        return '\0';
    }

    if (heap->array->length == 1) {
        return alPop(heap->array, 0);
    }

    char lastValue = alPop(heap->array, heap->array->length - 1);
    char outValue = alReplace(heap->array, 0, lastValue);
    _heapifyDown(heap, 0);

    return outValue;
}

// Checks both children of currIndex
bool _recFind(MinHeap* heap, char value, int currIndex) {

    // Left child

    int leftIndex = _getLeftChild(currIndex);
    if (leftIndex >= heap->array->length) {
        return false;
    }

    char leftValue = alGet(heap->array, leftIndex);
    if (value == leftValue) {
        return true;
    } else if (value > leftValue) {
        if (_recFind(heap, value, leftIndex)) {
            return true;
        }
    }

    // Right child

    int rightIndex = _getRightChild(currIndex);
    if (rightIndex >= heap->array->length) {
        return false;
    }

    char rightValue = alGet(heap->array, rightIndex);
    if (value == rightValue) {
        return true;
    } else if (value > rightValue) {
        if (_recFind(heap, value, rightIndex)) {
            return true;
        }
    }

    // If both are > than value and the recursion didn't find the value

    return false;
}

bool mhFind(MinHeap* heap, char value) {
    if (heap->array->length == 0) {
        return false;
    }

    char rootValue = alGet(heap->array, 0);
    if (value == rootValue) {
        return true;
    } else if (value < rootValue) {
        return false;
    } else {
        return _recFind(heap, value, 0);
    }
}

void minHeapTest() {
    printf("MinHeap test\n");

    char array[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o'};
    int len = 15;

    MinHeap* heap = mhNew(len);
    mhPrint(heap);

    for (int i = 0; i < len; i++) {
        mhPush(heap, array[i]);
    }
    mhPrint(heap);

    printf("Pop: %c;\n", mhPop(heap));
    printf("Pop: %c;\n", mhPop(heap));
    mhPrint(heap);

    printf("Find: %d;\n", mhFind(heap, 'n'));
    printf("Find: %d;\n", mhFind(heap, 'b'));
    printf("Find: %d;\n", mhFind(heap, 'c'));
    printf("Find: %d;\n", mhFind(heap, 'z'));

    mhDelete(&heap);
    mhPrint(heap);
}
