#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "Node.h"

typedef struct Queue {
    DataType dataType;
    Node* head;
    Node* tail;
    int length;
} Queue;

Queue* qNew(DataType);
void qDelete(Queue**);
void qPrint(Queue*);

void qPush(Queue*, ANYTYPE);
ANYTYPE qPop(Queue*);
ANYTYPE qPeek(Queue*);

void queueTest();
