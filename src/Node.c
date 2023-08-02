#include "Node.h"

void printNode(Node* node) {
    if (!node) {
        printf("NULL ");
        return;
    }

    // i hate this
    switch (node->value.dataType) {
    case NONE:
        printf("NONE ");
        break;
    case CHAR:
        printf("%c", node->value.value.c);
        break;
    case BTNODE:
        printf("%c", node->value.value.btn->value);
        break;
    case ARRAYLIST:
        alPrint(node->value.value.al);
        break;
    }
}
