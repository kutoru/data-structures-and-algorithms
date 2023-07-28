#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "Node.h"

typedef struct Stack {
    Node* head;
} Stack;

Stack* sNew();
void sDelete(Stack**);
void sPrint(Stack*);

void sPush(Stack*, char);
char sPop(Stack*);
char sPeek(Stack*);

void stackTest();
