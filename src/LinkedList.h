#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Node.h"

// More specifically, this is a doubly linked list
typedef struct LinkedList {
    Node* head;
    Node* tail;
    int length;
} LinkedList;

LinkedList* llNew();
void llDelete(LinkedList**);
void llPrint(LinkedList*);

// The idea here is that you will first call the get method and then do whatever you want with the node that you got

bool llBelongs(LinkedList*, Node*);
void llPush(LinkedList*, char);
void llInsert(LinkedList*, Node*, char, bool);
char llPop(LinkedList*, Node*, bool);
Node* llGet(LinkedList*, int);
int llGetIndex(LinkedList*, Node*);

void linkedListTest();
