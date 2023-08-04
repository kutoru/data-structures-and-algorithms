#include "Map.h"

// I don't want to deal with other types for now
bool _checkTypes(DataType kType, DataType vType) {
    return (kType == INT && vType == NODE) ||
           (kType == NODE && vType == INT);
}

bool _checkKey(Map* map, ANYTYPE key) {
    return key.dataType == map->keyType;
}

bool _checkValue(Map* map, ANYTYPE value) {
    return value.dataType == map->valueType;
}

Map* mapNew(DataType keyType, DataType valueType, int size) {
    if (!_checkTypes(keyType, valueType) || size > 100) {
        return NULL;
    }

    Map* map = (Map*)malloc(sizeof(Map));
    map->keyType = keyType;
    map->valueType = valueType;
    map->listContainer = (MapNodeList**)malloc(size * sizeof(MapNodeList*));
    for (int i = 0; i < size; i++) {
        map->listContainer[i] = (MapNodeList*)calloc(1, sizeof(MapNodeList));
    }
    map->size = size;

    return map;
}

void mapDelete(Map** map) {
    for (int i = 0; i < (*map)->size; i++) {
        MapNodeList* list = (*map)->listContainer[i];
        if (list->array) {
            free(list->array);
        }
        free(list);
    }

    free((*map)->listContainer);
    free(*map);
    *map = NULL;
}

void mapPrint(Map* map) {
    if (!map) {
        printf("The map is NULL;\n");
        return;
    }

    printf("Map:\n");

    for (int i = 0; i < map->size; i++) {
        MapNodeList* list = map->listContainer[i];

        for (int j = 0; j < list->length; j++) {
            MapNode node = list->array[j];

            int k, v;
            if (map->keyType == INT) {
                k = node.key.value.i;
                v = node.value.value.n->value.value.i; // this is probably the worst line of code i have ever written
            } else {
                k = node.key.value.n->value.value.i; // now i did it two times
                v = node.value.value.i;
            }
            printf("K: %d, V: %d;\n", k, v);
        }
    }
}

int _hashKey(Map* map, ANYTYPE key) {
    if (key.dataType == INT) {
        return key.value.i % map->size;
    } else if (key.dataType == NODE) {
        return (intptr_t)key.value.n % map->size;
    } else {
        return -1;
    }
}

int _findNodeIndex(MapNodeList* list, ANYTYPE key) {
    for (int i = 0; i < list->length; i++) {
        MapNode node = list->array[i];

        if (key.dataType == INT) {
            if (node.key.value.i == key.value.i) {
                return i;
            }
        } else {
            if (node.key.value.n == key.value.n) {
                return i;
            }
        }
    }

    return -1;
}

// If key does not exist, creates a new pair.
// If it does, changes the value and returns the old value.
ANYTYPE mapSet(Map* map, ANYTYPE key, ANYTYPE value) {
    ANYTYPE out = (ANYTYPE){NONE};
    if (!_checkKey(map, key) || !_checkValue(map, value)) {
        return out;
    }

    int index = _hashKey(map, key);
    MapNodeList* list = map->listContainer[index];
    MapNode node = (MapNode){(ANYTYPE){NONE}, (ANYTYPE){NONE}};

    int nodeIndex = _findNodeIndex(list, key);
    if (nodeIndex > -1) {
        out = list->array[nodeIndex].value;
        list->array[nodeIndex].value = value;
    } else {
        // Yes, i am reallocating the array for each new key
        list->array = (MapNode*)realloc(list->array, (list->length + 1) * sizeof(MapNode));
        list->array[list->length] = (MapNode){key, value};
        list->length++;
    }

    return out;
}

ANYTYPE mapRemove(Map* map, ANYTYPE key) {
    ANYTYPE out = (ANYTYPE){NONE};
    if (!_checkKey(map, key)) {
        return out;
    }

    int index = _hashKey(map, key);
    MapNodeList* list = map->listContainer[index];

    int nodeIndex = _findNodeIndex(list, key);
    if (nodeIndex > -1) {
        out = list->array[nodeIndex].value;

        if (list->length == 1) {
            // Freeing the array if it only had one item
            free(list->array);
            list->array = NULL;
        } else {
            // Otherwise, overwriting the element and cutting the last position off
            list->array[nodeIndex] = list->array[list->length - 1];
            list->array = (MapNode*)realloc(list->array, (list->length - 1) * sizeof(MapNode));
        }

        list->length--;
    }

    return out;
}

ANYTYPE mapGet(Map* map, ANYTYPE key) {
    ANYTYPE out = (ANYTYPE){NONE};
    if (!_checkKey(map, key)) {
        return out;
    }

    int index = _hashKey(map, key);
    MapNodeList* list = map->listContainer[index];

    int nodeIndex = _findNodeIndex(list, key);
    if (nodeIndex > -1) {
        out = list->array[nodeIndex].value;
    }

    return out;
}

void mapTest() {
    printf("Map test\n");

    printf("\nINT as key and NODE as value:\n");
    Map* map = mapNew(INT, NODE, 6);
    mapPrint(map);

    LinkedList* list = llNew(INT);
    for (int i = 0; i < 6; i++) {
        llAppend(list, fromInt(i * 10));
        mapSet(map, fromInt(5 - i), fromNode(list->tail));
    }
    llPrint(list);
    mapPrint(map);

    printValue(mapSet(map, fromInt(1), fromNode(llGet(list, 3))));
    printf("\n");
    printValue(mapSet(map, fromInt(72), fromNode(llGet(list, 1))));
    printf("\n");
    printValue(mapGet(map, fromInt(2)));
    printf("\n");
    printValue(mapRemove(map, fromInt(4)));
    printf("\n");
    printValue(mapGet(map, fromInt(4)));
    printf("\n");
    mapPrint(map);

    llDelete(&list, false);
    mapDelete(&map);
    mapPrint(map);

    printf("\nNODE as key and INT as value:\n");
    map = mapNew(NODE, INT, 6);
    mapPrint(map);

    list = llNew(INT);
    for (int i = 0; i < 6; i++) {
        llAppend(list, fromInt(i * 10));
        mapSet(map, fromNode(list->tail), fromInt(5 - i));
    }
    llPrint(list);
    mapPrint(map);

    printValue(mapSet(map, fromNode(llGet(list, 3)), fromInt(3)));
    printf("\n");
    Node* node = llAppend(list, fromInt(90));
    printValue(mapSet(map, fromNode(node), fromInt(72)));
    printf("\n");
    printValue(mapGet(map, fromNode(node)));
    printf("\n");
    printValue(mapRemove(map, fromNode(llGet(list, 4))));
    printf("\n");
    printValue(mapGet(map, fromNode(llGet(list, 4))));
    printf("\n");
    mapPrint(map);

    llDelete(&list, false);
    mapDelete(&map);
    mapPrint(map);
}
