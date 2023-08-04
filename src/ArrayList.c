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

// Temporary function
void alPrintInt(ArrayList* list) {
    if (!list) {
        printf("The list is NULL;\n");
        return;
    }

    printf("cap: %d; len: %d;\n", list->capacity, list->length);
    for (int i = 0; i < list->length; i++) {
        printf("%d", list->array[i]);
    }
    printf(";\n");
}

void _alGrow(ArrayList* list) {
    if (list->capacity > 1) {
        list->capacity = (int)(list->capacity * 1.5);
    } else {
        list->capacity = 2;
    }
    list->array = (char*)realloc(list->array, list->capacity * sizeof(char));
}

void alAppend(ArrayList* list, char value) {
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

// If index is in bounds, sets the value at the index. Returns the old value
char alSet(ArrayList* list, int index, char value) {
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

ArrayList* alCloneArray(char* array, int len) {
    ArrayList* list = alNew(len);
    for (int i = 0; i < len; i++) {
        alAppend(list, array[i]);
    }
    return list;
}

ArrayList* alClone(ArrayList* list) {
    ArrayList* newList = alNew(list->capacity);
    for (int i = 0; i < list->length; i++) {
        alAppend(newList, alGet(list, i));
    }
    return newList;
}

void alFill(ArrayList* list, int amount, char value) {
    for (int i = 0; i < amount; i++) {
        if (i >= list->length) {
            alAppend(list, value);
        } else {
            alSet(list, i, value);
        }
    }
}

void alReverse(ArrayList* list) {
    int len = list->length;
    if (len < 2) {
        return;
    }

    for (int i = 0; i < len / 2; i++) {
        char temp = list->array[i];
        list->array[i] = list->array[len - 1 - i];
        list->array[len - 1 - i] = temp;
    }
}

void arrayListTest() {
    printf("ArrayList test\n");

    ArrayList* list = alNew(5);
    alPrint(list);

    alAppend(list, 'k');
    alAppend(list, 'u');
    alAppend(list, 'o');
    alAppend(list, 'r');
    alInsert(list, 2, 'k');
    alInsert(list, 5, 'u');
    alPrint(list);

    printf("Replaced char: %c\n", alSet(list, 2, 't'));
    alPrint(list);
    alAppend(list, 'p');
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

    alAppend(list, ' ');
    alAppend(list, 'k');
    alAppend(list, 'u');
    alAppend(list, 'o');
    alAppend(list, 'r');
    alAppend(list, 'r');
    alPrint(list);

    alDelete(&list);
    alPrint(list);
}
