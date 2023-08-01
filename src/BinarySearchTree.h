#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Node.h"

typedef struct BinarySearchTree {
    BTNode* root;
    int height;
} BinarySearchTree;

BinarySearchTree* bstNew();
void bstDelete(BinarySearchTree**);
void bstPrint(BinarySearchTree*);

void bstInsert(BinarySearchTree*, char);
bool bstFind(BinarySearchTree*, char);
void bstRemove(BinarySearchTree*, char);

void binarySearchTreeTest();
