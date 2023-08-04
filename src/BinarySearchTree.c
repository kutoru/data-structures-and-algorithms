#include "BinarySearchTree.h"

BinarySearchTree* bstNew() {
    BinarySearchTree* tree = (BinarySearchTree*)malloc(sizeof(BinarySearchTree));
    tree->root = NULL;
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

    _recBstPrint(tree->root);
    printf(";\n");
}

void _recBstInsert(BTNode* node, char value) {
    if (node->value >= value) {
        if (node->left) {
            return _recBstInsert(node->left, value);
        }

        BTNode* newNode = (BTNode*)malloc(sizeof(BTNode));
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->value = value;
        node->left = newNode;
    } else {
        if (node->right) {
            return _recBstInsert(node->right, value);
        }

        BTNode* newNode = (BTNode*)malloc(sizeof(BTNode));
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->value = value;
        node->right = newNode;
    }
}

void bstInsert(BinarySearchTree* tree, char value) {
    if (tree->root) {
        _recBstInsert(tree->root, value);
        return;
    }

    BTNode* newNode = (BTNode*)malloc(sizeof(BTNode));
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->value = value;
    tree->root = newNode;
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

BTNode* _deleteMin(BTNode* node) {
    if (!node) {
        return NULL;
    }

    if (!node->left) {
        BTNode* temp = node->right;
        free(node);
        return temp;
    }

    node->left = _deleteMin(node->left);
    return node;
}

void _removeRoot(BinarySearchTree* tree) {
    BTNode* root = tree->root;

    if (root->left && root->right) {
        BTNode* min = root->right;
        while (min->left) {
            min = min->left;
        }

        root->value = min->value;
        root->right = _deleteMin(root->right);
        return;
    }

    if (!root->left && !root->right) {
        tree->root = NULL;
    }

    if (root->left) {
        tree->root = root->left;
    }

    if (root->right) {
        tree->root = root->right;
    }

    free(root);
}

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
            BTNode* min = node->right;
            while (min->left) {
                min = min->left;
            }

            node->value = min->value;
            node->right = _deleteMin(node->right);
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
    if (tree->root->value == value) {
        _removeRoot(tree);
    } else {
        _recBstRemove(NULL, false, tree->root, value);
    }
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
    bstInsert(tree, 'y');
    bstInsert(tree, 'x');
    bstPrint(tree);

    printf("Find: %d;\n", bstFind(tree, 'o'));
    printf("Find: %d;\n", bstFind(tree, 'r'));

    bstRemove(tree, 82);
    bstRemove(tree, 'u');
    bstRemove(tree, 'x');
    bstPrint(tree);

    bstDelete(&tree);
    bstPrint(tree);
}
