#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "Node.h"
#include "LinkedList.h"

typedef struct MapNode {
    ANYTYPE key;
    ANYTYPE value;
} MapNode;

typedef struct MapNodeList {
    MapNode* array;
    int length;
} MapNodeList;

typedef struct Map {
    DataType keyType;
    DataType valueType;
    MapNodeList** listContainer;
    int size;
} Map;

Map* mapNew(DataType keyType, DataType valueType, int size);
void mapDelete(Map** map);
void mapPrint(Map* map);

ANYTYPE mapSet(Map* map, ANYTYPE key, ANYTYPE value);
ANYTYPE mapRemove(Map* map, ANYTYPE key);
ANYTYPE mapGet(Map* map, ANYTYPE key);

void mapTest();
