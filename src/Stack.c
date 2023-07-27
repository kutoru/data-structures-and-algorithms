#include "Stack.h"

Stack* sNew() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->head = NULL;
    return stack;
}

void sDelete(Stack** stack) {
    Node* temp = (*stack)->head;
    while (temp) {
        Node* toDelete = temp;
        temp = temp->next;
        free(toDelete);
    }

    free(*stack);
    *stack = NULL;
}

void sPrint(Stack* stack) {
    if (!stack) {
        printf("The stack is NULL;\n");
        return;
    }

    if (!stack->head) {
        printf("The head is NULL;\n");
        return;
    }

    Node* temp = stack->head;
    while (temp) {
        printf("%c", temp->value);
        temp = temp->next;
    }
    printf(";\n");
}

void sPush(Stack* stack, char value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;

    if (!stack->head) {
        stack->head = newNode;
    } else {
        newNode->next = stack->head;
        stack->head = newNode;
    }
}

char sPop(Stack* stack) {
    if (!stack->head) {
        return '\0';
    }

    char oldValue = stack->head->value;

    Node* toDelete = stack->head;
    stack->head = stack->head->next;
    free(toDelete);

    return oldValue;
}

char sPeek(Stack* stack) {
    if (!stack->head) {
        return '\0';
    }

    return stack->head->value;
}

void stackTest() {
    printf("Stack test\n");

    Stack* stack = sNew();
    sPrint(stack);

    sPush(stack, 'k');
    sPush(stack, 'u');
    sPush(stack, 't');
    sPush(stack, 'o');
    sPush(stack, 'r');
    sPrint(stack);

    printf("Pop: %c\n", sPop(stack));
    sPrint(stack);
    printf("Peek: %c\n", sPeek(stack));
    printf("Pop: %c\n", sPop(stack));
    sPrint(stack);

    sDelete(&stack);
    sPrint(stack);
}
