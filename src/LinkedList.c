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

    if (!list->head) {
        printf("Head: %p; Tail: %p;\n", list->head, list->tail);
        return;
    }

    printf("Len: %d;\n", list->length);

    printf("From head:\n");
    Node* temp = list->head;
    while (temp) {
        printNode(temp);
        temp = temp->next;
    }
    printf(";\n");

    printf("From tail:\n");
    temp = list->tail;
    while (temp) {
        printNode(temp);
        temp = temp->prev;
    }
    printf(";\n");
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

void llPush(LinkedList* list, ANYTYPE value) {
    if (value.dataType != list->dataType) {
        return;
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
}

// Inserts a new node before the passed node.
// beSafe checks if the passed node belongs to the passed list at the cost of extra runtime.
void llInsert(LinkedList* list, Node* node, ANYTYPE value, bool beSafe) {
    if (value.dataType != list->dataType || !node ||
        node->value.dataType != list->dataType) {
        return;
    }

    if (beSafe) {
        if (!llBelongs(list, node)) {
            return;
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

    llPush(list, (ANYTYPE) {CHAR, 'u'});
    llPush(list, (ANYTYPE) {CHAR, 'o'});
    llPush(list, (ANYTYPE) {CHAR, 'r'});
    llPush(list, (ANYTYPE) {CHAR, 'u'});
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
