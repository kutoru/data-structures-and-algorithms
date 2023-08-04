#include "WeightedAdjacencyMatrix.h"

typedef struct WeightedAdjacencyMatrix {
    int* array;
    int length;
} WeightedAdjacencyMatrix;

int wamGet(WeightedAdjacencyMatrix* wam, int x, int y) {
    return wam->array[(y * wam->length) + x];
}

void wamSet(WeightedAdjacencyMatrix* wam, int x, int y, int value) {
    wam->array[(y * wam->length) + x] = value;
}

WeightedAdjacencyMatrix* wamNew(int sideLen) {
    WeightedAdjacencyMatrix* wam = (WeightedAdjacencyMatrix*)malloc(sizeof(WeightedAdjacencyMatrix));
    wam->array = (int*)calloc(sideLen*sideLen, sizeof(int));
    wam->length = sideLen;
    return wam;
}

void wamDelete(WeightedAdjacencyMatrix** wam) {
    free((*wam)->array);
    free(*wam);
    *wam = NULL;
}

void wamPrint(WeightedAdjacencyMatrix* wam) {
    if (!wam) {
        printf("The wam is NULL;\n");
        return;
    }

    printf("Len: %d;\n", wam->length);

    for (int i = 0; i < wam->length; i++) {
        for (int j = 0; j < wam->length; j++) {
            printf("%d ", wamGet(wam, i, j));
        }
        printf(";\n");
    }
}

// Yes, i treated char lists both as boolean and integer lists.
// I wouldn't do that in an actual project, but for now I'm just tired of generics ok
ArrayList* bfs(WeightedAdjacencyMatrix* graph, int source, int target) {
    ArrayList* seen = alNew(graph->length);
    alFill(seen, graph->length, false);
    ArrayList* prev = alNew(graph->length);
    alFill(prev, graph->length, -1);

    alSet(seen, source, 1);
    Queue* queue = qNew(CHAR);
    qPush(queue, (ANYTYPE) {CHAR, source});

    do {
        int curr = qPop(queue).value.c;
        if (curr == target) {
            break;
        }

        for (int i = 0; i < graph->length; i++) {
            if (alGet(seen, i) == true) {
                continue;
            }

            if (wamGet(graph, curr, i) == 0) {
                continue;
            }

            alSet(seen, i, true);
            alSet(prev, i, curr);
            qPush(queue, (ANYTYPE) {CHAR, i});
        }
    } while (queue->length > 0);

    alDelete(&seen);
    qDelete(&queue);

    ArrayList* out = alNew(graph->length);
    if (alGet(prev, target) == -1) {
        alDelete(&prev);
        return out;
    }

    int curr = target;
    while (alGet(prev, curr) != -1) {
        alAppend(out, curr);
        curr = alGet(prev, curr);
    }

    alAppend(out, source);
    alReverse(out);

    alDelete(&prev);
    return out;
}

void weightedAdjacencyMatrixTest() {
    printf("Weighted adjacency matrix test\n");

    WeightedAdjacencyMatrix* wam = wamNew(5);
    wamPrint(wam);

    // Graph1
    wamSet(wam, 0, 2, 5);
    wamSet(wam, 1, 0, 25);
    wamSet(wam, 1, 3, 15);
    wamSet(wam, 2, 1, 10);
    wamSet(wam, 2, 4, 20);
    wamSet(wam, 4, 1, 10);
    wamPrint(wam);

    ArrayList* list = bfs(wam, 0, 3);
    alPrintInt(list);
    alDelete(&list);
    

    wamDelete(&wam);
    wamPrint(wam);
}
