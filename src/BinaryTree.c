#include "BinaryTree.h"

void _recInsert(BTNode* node, char* array, int currIndex, int len) {
    int leftIndex = currIndex * 2 + 1;
    int rightIndex = currIndex * 2 + 2;

    if (leftIndex >= len) {
        return;
    }

    node->left = (BTNode*)malloc(sizeof(BTNode));
    node->left->value = array[leftIndex];
    node->left->left = NULL;
    node->left->right = NULL;

    if (rightIndex >= len) {
        return;
    }

    node->right = (BTNode*)malloc(sizeof(BTNode));
    node->right->value = array[rightIndex];
    node->right->left = NULL;
    node->right->right = NULL;

    _recInsert(node->left, array, leftIndex, len);
    _recInsert(node->right, array, rightIndex, len);
}

BinaryTree* btNewFromArray(char* array, int len) {
    BinaryTree* tree = (BinaryTree*)malloc(sizeof(BinaryTree));

    tree->root = (BTNode*)malloc(sizeof(BTNode));
    tree->root->value = array[0];
    tree->root->left = NULL;
    tree->root->right = NULL;

    _recInsert(tree->root, array, 0, len);

    return tree;
}

void _recDelete(BTNode* node) {
    if (!node) {
        return;
    }

    _recDelete(node->left);
    _recDelete(node->right);

    free(node);
}

void btDelete(BinaryTree** tree) {
    _recDelete((*tree)->root);
    free(*tree);
    *tree = NULL;
}

int _recGetSize(BTNode* node) {
    if (!node) {
        return 0;
    }

    return 1 + _recGetSize(node->left) + _recGetSize(node->right);
}

int btGetSize(BinaryTree* tree) {
    return _recGetSize(tree->root);
}

void _recFillArray(char* array, BTNode* node, int currIndex) {
    if (!node) {
        return;
    }

    array[currIndex] = node->value;
    _recFillArray(array, node->left, currIndex * 2 + 1);
    _recFillArray(array, node->right, currIndex * 2 + 2);
}

char* btToArray(BinaryTree* tree) {
    int size = btGetSize(tree);
    char* array = (char*)malloc(size * sizeof(char));
    _recFillArray(array, tree->root, 0);
    return array;
}

void btPrint(BinaryTree* tree) {
    if (!tree) {
        printf("The tree is NULL;\n");
        return;
    }

    int size = btGetSize(tree);
    printf("Size: %d;\n", size);

    char* array = btToArray(tree);
    for (int i = 0; i < size; i++) {
        printf("%c ", array[i]);
    }
    free(array);
    printf(";\n");
}

void _recPreOrderTrav(BTNode* node, ArrayList* list) {
    if (!node) {
        return;
    }

    alPush(list, node->value);
    _recPreOrderTrav(node->left, list);
    _recPreOrderTrav(node->right, list);
}

ArrayList* preOrderTraversal(BinaryTree* tree) {
    int size = btGetSize(tree);
    ArrayList* array = alNew(size);
    _recPreOrderTrav(tree->root, array);
    return array;
}

void _recInOrderTrav(BTNode* node, ArrayList* list) {
    if (!node) {
        return;
    }

    _recInOrderTrav(node->left, list);
    alPush(list, node->value);
    _recInOrderTrav(node->right, list);
}

ArrayList* inOrderTraversal(BinaryTree* tree) {
    int size = btGetSize(tree);
    ArrayList* array = alNew(size);
    _recInOrderTrav(tree->root, array);
    return array;
}

void _recPostOrderTrav(BTNode* node, ArrayList* list) {
    if (!node) {
        return;
    }

    _recPostOrderTrav(node->left, list);
    _recPostOrderTrav(node->right, list);
    alPush(list, node->value);
}

ArrayList* postOrderTraversal(BinaryTree* tree) {
    int size = btGetSize(tree);
    ArrayList* array = alNew(size);
    _recPostOrderTrav(tree->root, array);
    return array;
}

ArrayList* breadthFirstTraversal(BinaryTree* tree) {
    ArrayList* list = alNew(btGetSize(tree));
    Queue* queue = qNew(BTNODE);

    ANYTYPE tempVal;
    tempVal.dataType = BTNODE;
    tempVal.value.btn = tree->root;
    qPush(queue, tempVal);

    while (queue->length > 0) {
        BTNode* node = qPop(queue).value.btn;
        alPush(list, node->value);

        if (node->left) {
            tempVal.value.btn = node->left;
            qPush(queue, tempVal);
        }
        if (node->right) {
            tempVal.value.btn = node->right;
            qPush(queue, tempVal);
        }
    }

    return list;
}

bool _recCompareTrees(BTNode* node1, BTNode* node2) {
    if (!node1 && !node2) {
        return true;
    }

    if (!node1 || !node2) {
        return false;
    }

    if (node1->value != node2->value) {
        return false;
    }

    return
        _recCompareTrees(node1->left, node2->left) &&
        _recCompareTrees(node1->right, node2->right);
}

bool compareTrees(BinaryTree* tree1, BinaryTree* tree2) {
    return _recCompareTrees(tree1->root, tree2->root);
}

void treeTraversalTest() {
    printf("Tree traversal test\n");

    char array1[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o'};
    int len1 = 15;
    BinaryTree* tree = btNewFromArray(array1, len1);
    btPrint(tree);

    ArrayList* preList = preOrderTraversal(tree);
    alPrint(preList);
    alDelete(&preList);

    ArrayList* inList = inOrderTraversal(tree);
    alPrint(inList);
    alDelete(&inList);

    ArrayList* postList = postOrderTraversal(tree);
    alPrint(postList);
    alDelete(&postList);

    ArrayList* bfList = breadthFirstTraversal(tree);
    alPrint(bfList);
    alDelete(&bfList);

    char array2[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p'};
    int len2 = 14;
    BinaryTree* tree2 = btNewFromArray(array2, len2);
    btPrint(tree2);

    printf("Comparison: %d;\n", compareTrees(tree, tree2));

    btDelete(&tree);
    btPrint(tree);
    btDelete(&tree2);
    btPrint(tree2);
}
