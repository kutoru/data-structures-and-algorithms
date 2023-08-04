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

LinkedList* llNew(DataType dataType);
void llDelete(LinkedList** list, bool cleanupValues);
void llPrint(LinkedList* list);

// The idea here is that you will first call the get method and then do whatever you want with the node that you got
// Append, prepend and insert return the newly created node
// beSafe checks if the passed node belongs to the passed list at the cost of extra runtime.

bool llBelongs(LinkedList* list, Node* node);
Node* llAppend(LinkedList* list, ANYTYPE value);
Node* llPrepend(LinkedList* list, ANYTYPE value);
Node* llInsert(LinkedList* list, Node* node, ANYTYPE value, bool beSafe);
ANYTYPE llPop(LinkedList* list, Node* node, bool beSafe);
Node* llGet(LinkedList* list, int index);
int llGetIndex(LinkedList* list, Node* node);

void linkedListTest();
