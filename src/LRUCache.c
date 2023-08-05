#include "LRUCache.h"

typedef struct LRU {
    LinkedList* list;
    Map* lookup;
    Map* reverseLookup;
    int capacity;
} LRU;

LRU* lruNew(int capacity) {
    LRU* lru = (LRU*)malloc(sizeof(LRU));
    lru->list = llNew(INT);
    lru->lookup = mapNew(INT, NODE, 10);
    lru->reverseLookup = mapNew(NODE, INT, 10);
    lru->capacity = capacity;
    return lru;
}

void lruDelete(LRU** lru) {
    llDelete(&(*lru)->list, false);
    mapDelete(&(*lru)->lookup);
    mapDelete(&(*lru)->reverseLookup);
    free(*lru);
    *lru = NULL;
}

void lruPrint(LRU* lru) {
    if (!lru) {
        printf("The LRU is NULL;\n");
        return;
    }

    printf("Cap: %d;\n", lru->capacity);
    llPrint(lru->list);
    mapPrint(lru->lookup);
    mapPrint(lru->reverseLookup);
}

// -1 value keeps the old node's value
void _updateNode(LRU* lru, Node* node, int key, int value) {
    ANYTYPE oldNodeValue = fromNode(node);
    mapRemove(lru->reverseLookup, oldNodeValue);

    ANYTYPE nodeValue = llPop(lru->list, node, false);
    Node* newNode;
    if (value == -1) {
        newNode = llInsert(lru->list, lru->list->head, nodeValue, false);
    } else {
        newNode = llInsert(lru->list, lru->list->head, fromInt(value), false);
    }

    ANYTYPE k = fromInt(key);
    ANYTYPE v = fromNode(newNode);
    mapSet(lru->lookup, k, v);
    mapSet(lru->reverseLookup, v, k);
}

void _addValue(LRU* lru, int key, int value) {
    Node* node = llPrepend(lru->list, fromInt(value));

    ANYTYPE k = fromInt(key);
    ANYTYPE v = fromNode(node);
    mapSet(lru->lookup, k, v);
    mapSet(lru->reverseLookup, v, k);
}

void _trimCache(LRU* lru) {
    for (int i = lru->list->length - 1; i >= lru->capacity; i--) {
        Node* node = lru->list->tail;

        ANYTYPE value = fromNode(node);
        ANYTYPE key = mapRemove(lru->reverseLookup, value);
        mapRemove(lru->lookup, key);

        llPop(lru->list, node, false);
    }
}

void lruUpdate(LRU* lru, int key, int value) {
    ANYTYPE k = fromInt(key);
    ANYTYPE nodeValue = mapGet(lru->lookup, k);

    if (nodeValue.dataType == NONE) {
        _addValue(lru, key, value);
        _trimCache(lru);
    } else {
        _updateNode(lru, toNode(nodeValue), key, value);
    }
}

int lruGet(LRU* lru, int key) {
    ANYTYPE k = fromInt(key);
    ANYTYPE nodeValue = mapGet(lru->lookup, k);
    if (nodeValue.dataType == NONE) {
        return -1;
    }

    Node* node = toNode(nodeValue);
    int value = toInt(node->value);
    _updateNode(lru, node, key, -1);

    return value;
}

void lruCacheTest() {
    printf("LRU cache test\n");

    LRU* lru = lruNew(5);
    lruPrint(lru);

    lruUpdate(lru, 5, 50);
    lruUpdate(lru, 69, 690);
    lruUpdate(lru, 2, 20);
    lruUpdate(lru, 12, 120);
    lruUpdate(lru, 9, 90);
    lruPrint(lru);

    printf("Get: %d;\n", lruGet(lru, 69));
    printf("Get: %d;\n", lruGet(lru, 2));
    lruPrint(lru);

    lruUpdate(lru, 72, 727);
    lruPrint(lru);

    lruDelete(&lru);
    lruPrint(lru);
}
