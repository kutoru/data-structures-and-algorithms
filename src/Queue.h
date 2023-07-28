#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "Node.h"

typedef struct Queue {
    Node* head;
    Node* tail;
} Queue;

Queue* qNew();
void qDelete(Queue**);
void qPrint(Queue*);

void qPush(Queue*, char);
char qPop(Queue*);
char qPeek(Queue*);

void queueTest();
