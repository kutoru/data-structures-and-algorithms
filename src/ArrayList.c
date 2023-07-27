#include "ArrayList.h"

ArrayList* alNew(int capacity) {
    ArrayList* list = (ArrayList*)malloc(sizeof(ArrayList));
    list->array = (char*)malloc(capacity * sizeof(char));
    list->capacity = capacity;
    list->length = 0;
    return list;
}

void alDelete(ArrayList** list) {
    free((*list)->array);
    free(*list);
    (*list) = NULL;
}

void alPrint(ArrayList* list) {
    if (!list) {
        printf("The list is NULL;\n");
        return;
    }

    printf("cap: %d; len: %d;\n", list->capacity, list->length);
    for (int i = 0; i < list->length; i++) {
        printf("%c", list->array[i]);
    }
    printf(";\n");
}

void _alGrow(ArrayList* list) {
    list->capacity = (int)(list->capacity * 1.5);
    list->array = (char*)realloc(list->array, list->capacity * sizeof(char));
}

void alPush(ArrayList* list, char value) {
    if (list->length == list->capacity) {
        _alGrow(list);
    }

    list->array[list->length] = value;
    list->length++;
}

void alInsert(ArrayList* list, int index, char value) {
    if (index < 0 || index > list->length) {
        return;
    }

    if (list->length == list->capacity) {
        _alGrow(list);
    }

    for (int i = list->length; i > index; i--) {
        list->array[i] = list->array[i-1];
    }

    list->array[index] = value;
    list->length++;
}

char alReplace(ArrayList* list, int index, char value) {
    if (index < 0 || index >= list->length) {
        return '\0';
    }

    char oldValue = list->array[index];
    list->array[index] = value;
    return oldValue;
}

char alPop(ArrayList* list, int index) {
    if (index < 0 || index >= list->length) {
        return '\0';
    }

    char oldValue = list->array[index];
    for (int i = index; i < list->length - 1; i++) {
        list->array[i] = list->array[i+1];
    }
    list->length--;
    return oldValue;
}

char alGet(ArrayList* list, int index) {
    if (index < 0 || index >= list->length) {
        return '\0';
    }

    return list->array[index];
}

void arrayListTest() {
    printf("ArrayList test\n");

    ArrayList* list = alNew(5);
    alPrint(list);

    alPush(list, 'k');
    alPush(list, 'u');
    alPush(list, 'o');
    alPush(list, 'r');
    alInsert(list, 2, 'k');
    alInsert(list, 5, 'u');
    alPrint(list);

    printf("Replaced char: %c\n", alReplace(list, 2, 't'));
    alPrint(list);
    alPush(list, 'p');
    alPrint(list);
    printf("Popped char: %c\n", alPop(list, 0));
    alPrint(list);
    alInsert(list, 0, 'K');
    alPrint(list);
    printf("Popped char: %c\n", alPop(list, 6));
    alPrint(list);

    printf("Got char: %c\n", alGet(list, 1));
    printf("Got char: %c\n", alGet(list, 6));
    printf("Got char: %c\n", alGet(list, 4));

    alPush(list, ' ');
    alPush(list, 'k');
    alPush(list, 'u');
    alPush(list, 'o');
    alPush(list, 'r');
    alPush(list, 'r');
    alPrint(list);

    alDelete(&list);
    alPrint(list);
}