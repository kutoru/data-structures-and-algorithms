#include "BinarySearchTree.h"

BinarySearchTree* bstNew() {
    BinarySearchTree* tree = (BinarySearchTree*)malloc(sizeof(BinarySearchTree));
    tree->root = NULL;
    tree->height = 0;
    return tree;
}

void _recBstDelete(BTNode* node) {
    if (!node) {
        return;
    }

    _recBstDelete(node->left);
    _recBstDelete(node->right);
    free(node);
}

void bstDelete(BinarySearchTree** tree) {
    _recBstDelete((*tree)->root);
    free(*tree);
    *tree = NULL;
}

void _recBstPrint(BTNode* node) {
    if (!node) {
        return;
    }

    _recBstPrint(node->left);
    printf("%d ", node->value);
    _recBstPrint(node->right);
}

void bstPrint(BinarySearchTree* tree) {
    if (!tree) {
        printf("The tree is NULL;\n");
        return;
    }

    printf("Height: %d;\n", tree->height);
    _recBstPrint(tree->root);
    printf(";\n");
}

int _recBstInsert(BTNode* node, char value, int currHeight) {
    if (node->value >= value) {
        if (node->left) {
            return _recBstInsert(node->left, value, currHeight + 1);
        }

        BTNode* newNode = (BTNode*)malloc(sizeof(BTNode));
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->value = value;
        node->left = newNode;
    } else {
        if (node->right) {
            return _recBstInsert(node->right, value, currHeight + 1);
        }

        BTNode* newNode = (BTNode*)malloc(sizeof(BTNode));
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->value = value;
        node->right = newNode;
    }

    return currHeight;
}

void bstInsert(BinarySearchTree* tree, char value) {
    if (tree->root) {
        int height = _recBstInsert(tree->root, value, 1);
        if (height > tree->height) {
            tree->height = height;
        }
        return;
    }

    BTNode* newNode = (BTNode*)malloc(sizeof(BTNode));
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->value = value;
    tree->root = newNode;
    tree->height = 1;
}

bool _recBstFind(BTNode* node, char value) {
    if (!node) {
        return false;
    }

    if (node->value == value) {
        return true;
    }

    if (node->value > value) {
        return _recBstFind(node->left, value);
    } else {
        return _recBstFind(node->right, value);
    }
}

bool bstFind(BinarySearchTree* tree, char value) {
    return _recBstFind(tree->root, value);
}

// The case when a node with the value has two children is too hard to implement, I might do it later
// Same for the case when the root has the value
void _recBstRemove(BTNode* parent, bool isLeft, BTNode* node, char value) {
    if (!node) {
        return;
    }

    if (node->value > value) {
        _recBstRemove(node, true, node->left, value);
        return;
    }

    if (node->value < value) {
        _recBstRemove(node, false, node->right, value);
        return;
    }

    if (node->value == value) {
        if (node->left && node->right) {
            // not implemented
            return;
        }

        if (!node->left && !node->right) {
            if (isLeft) {
                parent->left = NULL;
            } else {
                parent->right = NULL;
            }
        }

        if (!node->left) {
            if (isLeft) {
                parent->left = node->right;
            } else {
                parent->right = node->right;
            }
        }

        if (!node->right) {
            if (isLeft) {
                parent->left = node->left;
            } else {
                parent->right = node->left;
            }
        }

        free(node);
    }
}

void bstRemove(BinarySearchTree* tree, char value) {
    _recBstRemove(NULL, false, tree->root, value);
}

void binarySearchTreeTest() {
    printf("Binary search tree test\n");

    BinarySearchTree* tree = bstNew();
    bstPrint(tree);

    bstInsert(tree, 'k');
    bstInsert(tree, 'U');
    bstInsert(tree, 't');
    bstInsert(tree, 'o');
    bstInsert(tree, 'R');
    bstInsert(tree, 'u');
    bstPrint(tree);

    printf("Find: %d;\n", bstFind(tree, 'o'));
    printf("Find: %d;\n", bstFind(tree, 'r'));

    bstDelete(&tree);
    bstPrint(tree);
}
