#pragma once

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    Node* next;
    char value;
} Node;

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
