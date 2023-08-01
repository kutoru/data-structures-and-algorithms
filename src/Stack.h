#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "Node.h"

typedef struct Stack {
    DataType dataType;
    Node* head;
    int length;
} Stack;

Stack* sNew(DataType);
void sDelete(Stack**);
void sPrint(Stack*);

void sPush(Stack*, ANYTYPE);
ANYTYPE sPop(Stack*);
ANYTYPE sPeek(Stack*);

void stackTest();
