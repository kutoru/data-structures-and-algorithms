#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Node.h"

typedef struct BinarySearchTree {
    BTNode* root;
} BinarySearchTree;

BinarySearchTree* bstNew();
void bstDelete(BinarySearchTree** tree);
void bstPrint(BinarySearchTree* tree);

void bstInsert(BinarySearchTree* tree, char value);
bool bstFind(BinarySearchTree* tree, char value);
void bstRemove(BinarySearchTree* tree, char value);

void binarySearchTreeTest();
