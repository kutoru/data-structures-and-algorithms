#pragma once

#include <stdio.h>
#include <stdbool.h>
#include "ArrayList.h"

struct Node;
struct BTNode;

// ANYTYPE

typedef enum DataType {NONE, INT, BOOL, CHAR, NODE, BTNODE, ARRAYLIST} DataType;

// Isn't exactly an "anytype", but I didn't want to use void pointers
typedef struct ANYTYPE {
    DataType dataType;

    union value {
        int i;
        bool b;
        char c;
        Node* n;
        BTNode* btn;
        ArrayList* al;
    } value;
} ANYTYPE;

ANYTYPE fromInt(int value);
int toInt(ANYTYPE value);

ANYTYPE fromNode(Node* value);
Node* toNode(ANYTYPE value);

void printValue(ANYTYPE value);

// NODES

typedef struct Node {
    Node* next;
    Node* prev;
    ANYTYPE value;
} Node;

typedef struct BTNode {
    BTNode* left;
    BTNode* right;
    char value;
} BTNode;
