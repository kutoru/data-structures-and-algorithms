#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "LInkedList.h"

typedef struct TrieNode {
    TrieNode* array[26];
    char value;
    bool isWord;
} TrieNode;

typedef struct Trie {
    TrieNode* root;
} Trie;

Trie* trieNew();
void trieDelete(Trie** trie);
void triePrint(Trie* trie);

void trieAdd(Trie* trie, ArrayList* word);
void trieRemove(Trie* trie, ArrayList* word);
bool trieFind(Trie* trie, ArrayList* word);
LinkedList* trieFindAll(Trie* trie, ArrayList* word);

void trieTest();
