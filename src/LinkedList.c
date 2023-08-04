#include "LinkedList.h"

LinkedList* llNew(DataType dataType) {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    list->dataType = dataType;
    list->head = NULL;
    list->tail = NULL;
    list->length = 0;
    return list;
}

void llDelete(LinkedList** list) {
    Node* temp = (*list)->head;
    while (temp) {
        Node* toDelete = temp;
        temp = temp->next;

        if ((*list)->dataType == ARRAYLIST) {
            alDelete(&toDelete->value.value.al);
        }
        free(toDelete);
    }

    free(*list);
    *list = NULL;
}

void llPrint(LinkedList* list) {
    if (!list) {
        printf("The linked list is NULL;\n");
        return;
    }

    printf("Len: %d;\n", list->length);

    if (!list->head) {
        printf("Head: %p; Tail: %p;\n", list->head, list->tail);
        return;
    }

    printf("From head:\n");
    Node* temp = list->head;
    while (temp) {
        printNode(temp);
        temp = temp->next;
    }
    printf(";\n");

    // Maybe I will change this boolean to an argument, or I might just delete this
    if (false) {
        printf("From tail:\n");
        temp = list->tail;
        while (temp) {
            printNode(temp);
            temp = temp->prev;
        }
        printf(";\n");
    }
}

bool llBelongs(LinkedList* list, Node* node) {
    if (!node) {
        return false;
    }

    Node* temp = list->head;
    while (temp) {
        if (temp == node) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

Node* llAppend(LinkedList* list, ANYTYPE value) {
    if (value.dataType != list->dataType) {
        return NULL;
    }

    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;
    newNode->prev = NULL;

    if (!list->head) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        newNode->prev = list->tail;
        list->tail->next = newNode;
        list->tail = newNode;
    }

    list->length++;
    return newNode;
}

Node* llPrepend(LinkedList* list, ANYTYPE value) {
    if (value.dataType != list->dataType) {
        return NULL;
    }

    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;
    newNode->prev = NULL;

    if (!list->head) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        newNode->next = list->head;
        list->head->prev = newNode;
        list->head = newNode;
    }

    list->length++;
    return newNode;
}

// Inserts a new node before the passed node.
Node* llInsert(LinkedList* list, Node* node, ANYTYPE value, bool beSafe) {
    if (value.dataType != list->dataType || !node ||
        node->value.dataType != list->dataType) {
        return NULL;
    }

    if (beSafe) {
        if (!llBelongs(list, node)) {
            return NULL;
        }
    }

    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;
    newNode->prev = NULL;

    Node* prevNode = node->prev;
    newNode->prev = prevNode;
    if (prevNode) {
        prevNode->next = newNode;
    }

    newNode->next = node;
    node->prev = newNode;

    if (node == list->head) {
        list->head = newNode;
    }

    list->length++;
    return newNode;
}

// Removes the node from the list and frees it. Returns the node's value.
ANYTYPE llPop(LinkedList* list, Node* node, bool beSafe) {
    if (!node) {
        return (ANYTYPE) {NONE};
    }

    if (beSafe) {
        if (!llBelongs(list, node)) {
            return (ANYTYPE) {NONE};
        }
    }

    Node* prevNode = node->prev;
    Node* nextNode = node->next;
    if (prevNode) {
        prevNode->next = nextNode;
    }
    if (nextNode) {
        nextNode->prev = prevNode;
    }

    if (node == list->head) {
        list->head = nextNode;
    }
    if (node == list->tail) {
        list->tail = prevNode;
    }

    ANYTYPE oldValue = node->value;
    free(node);
    list->length--;
    return oldValue;
}

Node* llGet(LinkedList* list, int index) {
    if (index < 0 || index >= list->length) {
        return NULL;
    }

    if (index == 0) {
        return list->head;
    }

    Node* node = list->head;
    for (int i = 0; i < index; i++) {
        if (!node) {
            return NULL;
        }
        node = node->next;
    }

    return node;
}

int llGetIndex(LinkedList* list, Node* node) {
    if (!node) {
        return -1;
    }

    Node* temp = list->head;
    for (int i = 0; temp; i++) {
        if (temp == node) {
            return i;
        }
        temp = temp->next;
    }

    return -1;
}

void linkedListTest() {
    printf("LinkedList test\n");

    LinkedList* list = llNew(CHAR);
    llPrint(list);

    llAppend(list, (ANYTYPE) {CHAR, 'u'});
    llAppend(list, (ANYTYPE) {CHAR, 'o'});
    llAppend(list, (ANYTYPE) {CHAR, 'r'});
    llAppend(list, (ANYTYPE) {CHAR, 'u'});
    llPrint(list);

    Node* node = llGet(list, 1);
    printf("Got value: %c\n", node->value.value.c);
    printf("Got index: %d\n", llGetIndex(list, node));
    printf("Belongs: %d\n", llBelongs(list, node));

    llInsert(list, node, (ANYTYPE) {CHAR, 't'}, false);
    llInsert(list, llGet(list, 0), (ANYTYPE) {CHAR, 'k'}, false);
    llInsert(list, llGet(list, 6), (ANYTYPE) {CHAR, 'b'}, false);
    llPrint(list);

    node = llGet(list, 0);
    llPop(list, node, false);
    llPop(list, llGet(list, 4), false);
    llPop(list, llGet(list, 4), false);
    llPrint(list);

    llDelete(&list);
    llPrint(list);
}
