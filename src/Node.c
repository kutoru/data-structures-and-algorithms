#include "Node.h"

// ANYTYPE

ANYTYPE fromInt(int value) {
    ANYTYPE out;
    out.dataType = INT;
    out.value.i = value;
    return out;
}

int toInt(ANYTYPE value) {
    if (value.dataType != INT) {
        return -1;
    } else {
        return value.value.i;
    }
}

ANYTYPE fromNode(Node* value) {
    ANYTYPE out;
    out.dataType = NODE;
    out.value.n = value;
    return out;
}

Node* toNode(ANYTYPE value) {
    if (value.dataType != NODE) {
        return NULL;
    } else {
        return value.value.n;
    }
}

void printValue(ANYTYPE value) {
    switch (value.dataType) {
    case NONE:
        printf("NONE ");
        break;
    case INT:
        printf("%d ", value.value.i);
        break;
    case BOOL:
        printf("%d ", value.value.b);
        break;
    case CHAR:
        printf("%c", value.value.c);
        break;
    case NODE:
        printValue(value.value.n->value);
        break;
    case BTNODE:
        printf("%c", value.value.btn->value);
        break;
    case ARRAYLIST:
        alPrint(value.value.al);
        break;
    default:
        printf("Unknown value type;\n");
    }
}
