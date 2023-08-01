#pragma once

#include <stdio.h>

typedef struct BTNode {
    BTNode* left;
    BTNode* right;
    char value;
} BTNode;

typedef enum DataType {NONE, CHAR, BTNODE} DataType;

// Isn't exactly an "anytype", but I didn't want to use void pointers
typedef struct ANYTYPE {
    DataType dataType;

    union value {
        char c;
        BTNode* btn;
    } value;
} ANYTYPE;

typedef struct Node {
    Node* next;
    Node* prev;
    ANYTYPE value;
} Node;

// Doesn't add \n at the end
void printNode(Node*);
