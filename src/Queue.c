#include "Queue.h"

Queue* qNew(DataType dataType) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->dataType = dataType;
    queue->head = NULL;
    queue->tail = NULL;
    queue->length = 0;
    return queue;
}

void qDelete(Queue** queue) {
    Node* temp = (*queue)->head;
    while (temp) {
        Node* toDelete = temp;
        temp = temp->next;
        free(toDelete);
    }

    free(*queue);
    *queue = NULL;
}

void qPrint(Queue* queue) {
    if (!queue) {
        printf("The queue is NULL;\n");
        return;
    }

    printf("Len: %d;", queue->length);

    if (!queue->head) {
        printf("The head is NULL;\n");
        return;
    }

    Node* temp = queue->head;
    while (temp) {
        printValue(temp->value);
        temp = temp->next;
    }
    printf(";\n");
}

void qPush(Queue* queue, ANYTYPE value) {
    if (value.dataType != queue->dataType) {
        return;
    }

    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;
    newNode->prev = NULL;

    if (!queue->head) {
        queue->head = newNode;
        queue->tail = queue->head;
    } else {
        queue->tail->next = newNode;
        queue->tail = queue->tail->next;
    }

    queue->length++;
}

ANYTYPE qPop(Queue* queue) {
    if (!queue->head) {
        return (ANYTYPE) {NONE};
    }

    ANYTYPE oldValue = queue->head->value;

    Node* toDelete = queue->head;
    if (queue->head == queue->tail) {
        queue->tail = NULL;
    }
    queue->head = queue->head->next;
    free(toDelete);

    queue->length--;
    return oldValue;
}

ANYTYPE qPeek(Queue* queue) {
    if (!queue->head) {
        return (ANYTYPE) {NONE};
    }

    return queue->head->value;
}

void queueTest() {
    printf("Queue test\n");

    Queue* queue = qNew(CHAR);
    qPrint(queue);

    qPush(queue, (ANYTYPE) {CHAR, 'k'});
    qPrint(queue);
    printf("Pop: %c\n", qPop(queue).value.c);
    qPrint(queue);
    printf("Pop: %c\n", qPop(queue).value.c);

    qPush(queue, (ANYTYPE) {CHAR, 'u'});
    qPush(queue, (ANYTYPE) {CHAR, 't'});
    qPush(queue, (ANYTYPE) {CHAR, 'o'});
    qPush(queue, (ANYTYPE) {CHAR, 'r'});
    qPrint(queue);

    printf("Peek: %c\n", qPeek(queue).value.c);
    printf("Pop: %c\n", qPop(queue).value.c);
    qPrint(queue);
    qPush(queue, (ANYTYPE) {CHAR, 'a'});
    qPush(queue, (ANYTYPE) {CHAR, 'b'});
    qPrint(queue);
    printf("Peek: %c\n", qPeek(queue).value.c);
    printf("Pop: %c\n", qPop(queue).value.c);
    qPrint(queue);

    qDelete(&queue);
    qPrint(queue);
}
