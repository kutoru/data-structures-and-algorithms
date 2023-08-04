#pragma once

#include <stdlib.h>
#include <stdio.h>

typedef struct ArrayList {
    char* array;
    int capacity;
    int length;
} ArrayList;

ArrayList* alNew(int capacity);
void alDelete(ArrayList** list);
void alPrint(ArrayList* list);
void alPrintInt(ArrayList* list);

void alAppend(ArrayList* list, char value);
void alInsert(ArrayList* list, int index, char value);
char alSet(ArrayList* list, int index, char value);
char alPop(ArrayList* list, int index);
char alGet(ArrayList* list, int index);
ArrayList* alCloneArray(char* array, int arrayLength);
ArrayList* alClone(ArrayList* list);
void alFill(ArrayList* list, int fillAmount, char fillWith);
void alReverse(ArrayList* list);

void arrayListTest();
