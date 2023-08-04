#include "Trie.h"

Trie* trieNew() {
    Trie* trie = (Trie*)malloc(sizeof(Trie));
    trie->root = (TrieNode*)calloc(1, sizeof(TrieNode));
    return trie;
}

void _recDelete(TrieNode* node) {
    if (!node) {
        return;
    }

    for (int i = 0; i < 26; i++) {
        _recDelete(node->array[i]);
    }

    free(node);
}

void trieDelete(Trie** trie) {
    _recDelete((*trie)->root);
    free(*trie);
    *trie = NULL;
}

void _recGather(TrieNode* node, LinkedList* wordList, ArrayList* word) {
    if (!node) {
        return;
    }

    bool allocated = false;
    if (!word) {
        word = alNew(5);
        allocated = true;
    }

    alAppend(word, node->value);

    if (node->isWord) {
        ANYTYPE temp;
        temp.dataType = ARRAYLIST;
        temp.value.al = alClone(word);
        llAppend(wordList, temp);
    }

    for (int i = 0; i < 26; i++) {
        _recGather(node->array[i], wordList, word);
    }

    alPop(word, word->length - 1);

    if (allocated) {
        alDelete(&word);
    }
}

void triePrint(Trie* trie) {
    if (!trie) {
        printf("The trie is NULL;\n");
        return;
    }

    // Getting all the words
    LinkedList* wordList = llNew(ARRAYLIST);
    for (int i = 0; i < 26; i++) {
        _recGather(trie->root->array[i], wordList, NULL);
    }

    // Printing and deleting them
    llPrint(wordList);
    llDelete(&wordList, true);
}

// Doesn't check for word validity. Will work only with words with letters from a to z.
void trieAdd(Trie* trie, ArrayList* word) {
    TrieNode* node = trie->root;

    for (int i = 0; i < word->length; i++) {
        char letter = alGet(word, i);
        int index = letter - 'a';

        if (!node->array[index]) {
            node->array[index] = (TrieNode*)calloc(1, sizeof(TrieNode));
            node->array[index]->value = letter;
        }

        node = node->array[index];
    }

    node->isWord = true;
}

bool _nodeHasChildren(TrieNode* node) {
    for (int i = 0; i < 26; i++) {
        if (node->array[i]) {
            return true;
        }
    }
    return false;
}

bool _recRemove(TrieNode* parent, ArrayList* word, int currIndex) {
    // Getting current letter and its node, checking if it exists
    char letter = alGet(word, currIndex);
    int index = letter - 'a';
    TrieNode* node = parent->array[index];

    if (!node) {
        return false;
    }

    // If on the last index, checking if the node is valid, and deleting it if necessary
    if (currIndex == word->length - 1) {
        if (!node->isWord) {
            return false;
        }

        if (_nodeHasChildren(node)) {
            node->isWord = false;
            return false;
        }

        free(node);
        parent->array[index] = NULL;
        return true;
    }

    // If not on the last index, checking the next letter
    // If the next node got deleted, checking if the current node can get deleted as well
    bool canDeleteNode = _recRemove(node, word, currIndex + 1);
    if (canDeleteNode && !_nodeHasChildren(node) && !node->isWord) {
        free(node);
        parent->array[index] = NULL;
        return true;
    }
    
    return false;
}

void trieRemove(Trie* trie, ArrayList* word) {
    _recRemove(trie->root, word, 0);
}

bool trieFind(Trie* trie, ArrayList* word) {
    TrieNode* node = trie->root;

    for (int i = 0; i < word->length; i++) {
        char letter = alGet(word, i);
        int index = letter - 'a';

        if (!node->array[index]) {
            return false;
        }

        node = node->array[index];
    }

    return node->isWord;
}

// Find all words that start with the given word
LinkedList* trieFindAll(Trie* trie, ArrayList* word) {
    LinkedList* wordList = llNew(ARRAYLIST);

    TrieNode* node = trie->root;
    for (int i = 0; i < word->length; i++) {
        char letter = alGet(word, i);
        int index = letter - 'a';

        if (!node->array[index]) {
            return wordList;
        }
        node = node->array[index];
    }

    // Instead of creating "tempWord" I could just pop from "word" and then push the popped char back,
    // but I don't want to mutate the original list
    ArrayList* tempWord = alClone(word);
    alPop(tempWord, tempWord->length - 1);
    _recGather(node, wordList, tempWord);
    alDelete(&tempWord);

    return wordList;
}

void trieTest() {
    printf("Trie test:\n");

    Trie* trie = trieNew();
    triePrint(trie);

    char chars1[] = {'k', 'u', 't', 'o', 'r', 'u'};
    int len1 = 6;
    char chars2[] = {'k', 'u', 'r', 'o', 'm', 'i'};
    int len2 = 6;
    char chars3[] = {'h', 'a', 't', 's', 'u', 'n', 'e'};
    int len3 = 7;
    char chars4[] = {'k', 'u'};
    int len4 = 2;

    // char chars1[] = {'a', 'a', 'a'};
    // int len1 = 3;
    // char chars2[] = {'a', 'b', 'a'};
    // int len2 = 3;
    // char chars3[] = {'c', 'c', 'c', 'c'};
    // int len3 = 4;
    // char chars4[] = {'a'};
    // int len4 = 1;

    ArrayList* word1 = alCloneArray(chars1, len1);
    ArrayList* word2 = alCloneArray(chars2, len2);
    ArrayList* word3 = alCloneArray(chars3, len3);
    ArrayList* word4 = alCloneArray(chars4, len4);

    printf("\nTrie add:\n");

    trieAdd(trie, word1);
    trieAdd(trie, word2);
    trieAdd(trie, word3);
    triePrint(trie);

    printf("\nTrie find:\n");

    printf("Find: %d;\n", trieFind(trie, word1));
    alSet(word2, 1, 'g');
    printf("Find: %d;\n", trieFind(trie, word2));
    printf("Find: %d;\n", trieFind(trie, word3));
    printf("Find: %d;\n", trieFind(trie, word4));

    printf("\nTrie find all:\n");

    LinkedList* wordList1 = trieFindAll(trie, word4);
    llPrint(wordList1);
    LinkedList* wordList2 = trieFindAll(trie, word2);
    llPrint(wordList2);
    LinkedList* wordList3 = trieFindAll(trie, word3);
    llPrint(wordList3);

    printf("\nTrie remove:\n");

    trieRemove(trie, word1);
    triePrint(trie);
    trieRemove(trie, word3);
    triePrint(trie);

    printf("\nCleanup:\n");

    llDelete(&wordList1, true);
    llDelete(&wordList2, true);
    llDelete(&wordList3, true);

    alDelete(&word1);
    alDelete(&word2);
    alDelete(&word3);
    alDelete(&word4);

    trieDelete(&trie);
    triePrint(trie);
}
