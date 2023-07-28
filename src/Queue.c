#include "Queue.h"

Queue* qNew() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->head = NULL;
    queue->tail = NULL;
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

    if (!queue->head) {
        printf("The head is NULL;\n");
        return;
    }

    Node* temp = queue->head;
    while (temp) {
        printf("%c", temp->value);
        temp = temp->next;
    }
    printf(";\n");
}

void qPush(Queue* queue, char value) {
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
}

char qPop(Queue* queue) {
    if (!queue->head) {
        return '\0';
    }

    char oldValue = queue->head->value;

    Node* toDelete = queue->head;
    if (queue->head == queue->tail) {
        queue->tail = NULL;
    }
    queue->head = queue->head->next;
    free(toDelete);

    return oldValue;
}

char qPeek(Queue* queue) {
    if (!queue->head) {
        return '\0';
    }

    return queue->head->value;
}

void queueTest() {
    printf("Queue test\n");

    Queue* queue = qNew();
    qPrint(queue);

    qPush(queue, 'k');
    qPrint(queue);
    printf("Pop: %c\n", qPop(queue));
    qPrint(queue);
    printf("Pop: %c\n", qPop(queue));

    qPush(queue, 'u');
    qPush(queue, 't');
    qPush(queue, 'o');
    qPush(queue, 'r');
    qPrint(queue);

    printf("Peek: %c\n", qPeek(queue));
    printf("Pop: %c\n", qPop(queue));
    qPrint(queue);
    qPush(queue, 'a');
    qPush(queue, 'b');
    qPrint(queue);
    printf("Peek: %c\n", qPeek(queue));
    printf("Pop: %c\n", qPop(queue));
    qPrint(queue);

    qDelete(&queue);
    qPrint(queue);
}
