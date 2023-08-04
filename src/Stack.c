#include "Stack.h"

Stack* sNew(DataType dataType) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->dataType = dataType;
    stack->head = NULL;
    stack->length = 0;
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

    printf("Len: %d;", stack->length);

    if (!stack->head) {
        printf("The head is NULL;\n");
        return;
    }

    Node* temp = stack->head;
    while (temp) {
        printValue(temp->value);
        temp = temp->next;
    }
    printf(";\n");
}

void sPush(Stack* stack, ANYTYPE value) {
    if (value.dataType != stack->dataType) {
        return;
    }

    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;
    newNode->prev = NULL;

    if (!stack->head) {
        stack->head = newNode;
    } else {
        newNode->next = stack->head;
        stack->head = newNode;
    }

    stack->length++;
}

ANYTYPE sPop(Stack* stack) {
    if (!stack->head) {
        return (ANYTYPE) {NONE};
    }

    ANYTYPE oldValue = stack->head->value;

    Node* toDelete = stack->head;
    stack->head = stack->head->next;
    free(toDelete);

    stack->length--;
    return oldValue;
}

ANYTYPE sPeek(Stack* stack) {
    if (!stack->head) {
        return (ANYTYPE) {NONE};
    }

    return stack->head->value;
}

void stackTest() {
    printf("Stack test\n");

    Stack* stack = sNew(CHAR);
    sPrint(stack);

    sPush(stack, (ANYTYPE) {CHAR, 'k'});
    sPush(stack, (ANYTYPE) {CHAR, 'u'});
    sPush(stack, (ANYTYPE) {CHAR, 't'});
    sPush(stack, (ANYTYPE) {CHAR, 'o'});
    sPush(stack, (ANYTYPE) {CHAR, 'r'});
    sPrint(stack);

    printf("Pop: %c\n", sPop(stack).value.c);
    sPrint(stack);
    printf("Peek: %c\n", sPeek(stack).value.c);
    printf("Pop: %c\n", sPop(stack).value.c);
    sPrint(stack);

    sDelete(&stack);
    sPrint(stack);
}
