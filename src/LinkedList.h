#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Node.h"

// More specifically, this is a doubly linked list
typedef struct LinkedList {
    DataType dataType;
    Node* head;
    Node* tail;
    int length;
} LinkedList;

LinkedList* llNew(DataType);
void llDelete(LinkedList**);
void llPrint(LinkedList*);

// The idea here is that you will first call the get method and then do whatever you want with the node that you got

bool llBelongs(LinkedList*, Node*);
void llPush(LinkedList*, ANYTYPE);
void llInsert(LinkedList*, Node*, ANYTYPE, bool);
ANYTYPE llPop(LinkedList*, Node*, bool);
Node* llGet(LinkedList*, int);
int llGetIndex(LinkedList*, Node*);

void linkedListTest();
