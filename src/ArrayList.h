#pragma once

#include <stdlib.h>
#include <stdio.h>

typedef struct ArrayListTag {
    char* array;
    int capacity;
    int length;
} ArrayList;

ArrayList* alNew(int);
void alDelete(ArrayList**);
void alPrint(ArrayList*);

void alPush(ArrayList*);
void alInsert(ArrayList*, int, char);
char alReplace(ArrayList*, int, char);
char alPop(ArrayList*, int);
char alGet(ArrayList*, int);

void alTest();
