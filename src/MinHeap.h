#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ArrayList.h"

typedef struct MinHeap {
    ArrayList* array;
} MinHeap;

MinHeap* mhNew(int);
void mhDelete(MinHeap**);
void mhPrint(MinHeap*);

void mhPush(MinHeap*, char);
char mhPop(MinHeap*);
bool mhFind(MinHeap*, char);

void minHeapTest();
