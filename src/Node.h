#pragma once

#include <stdio.h>
#include "ArrayList.h"

typedef struct BTNode {
    BTNode* left;
    BTNode* right;
    char value;
} BTNode;

typedef enum DataType {NONE, CHAR, BTNODE, ARRAYLIST} DataType;

// Isn't exactly an "anytype", but I didn't want to use void pointers
typedef struct ANYTYPE {
    DataType dataType;

    union value {
        char c;
        BTNode* btn;
        ArrayList* al;
    } value;
} ANYTYPE;

typedef struct Node {
    Node* next;
    Node* prev;
    ANYTYPE value;
} Node;

void printNode(Node*);
