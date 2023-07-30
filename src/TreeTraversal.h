#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "ArrayList.h"

typedef struct BTNode {
    char value;
    BTNode* left;
    BTNode* right;
} BTNode;

typedef struct BinaryTree {
    BTNode* root;
} BinaryTree;

void treeTraversalTest();
