#include "WeightedAdjacencyMatrix.h"

const int MAX_VAL = CHAR_MAX;

// The end goal would be to make the arrays dynamically change their size, but for now its fine

typedef struct GraphEdge {
    int to;
    int weight;
} GraphEdge;

typedef struct EdgeList {
    GraphEdge* array;
    int length;
} EdgeList;

typedef struct WeightedAdjacencyList {
    EdgeList* lists;
    int length;
} WeightedAdjacencyList;

WeightedAdjacencyList* walNew(int length) {
    WeightedAdjacencyList* wal = (WeightedAdjacencyList*)malloc(sizeof(WeightedAdjacencyList));
    wal->lists = (EdgeList*)calloc(length, sizeof(EdgeList));
    wal->length = length;
    return wal;
}

void walDelete(WeightedAdjacencyList** wal) {
    for (int i = 0; i < (*wal)->length; i++) {
        if ((*wal)->lists[i].array) {
            free((*wal)->lists[i].array);
        }
    }

    free((*wal)->lists);
    free(*wal);
    *wal = NULL;
}

void walPrint(WeightedAdjacencyList* wal) {
    if (!wal) {
        printf("The wal is NULL;\n");
        return;
    }

    printf("Len: %d;\n", wal->length);

    for (int i = 0; i < wal->length; i++) {
        EdgeList list = wal->lists[i];
        printf("%d: ", i);

        if (!list.array) {
            printf("NULL;\n");
        } else {
            for (int j = 0; j < list.length; j++) {
                printf("%d (%d), ", list.array[j].to, list.array[j].weight);
            }
            printf(";\n");
        }
    }
}

// Graph1
void walFill1(WeightedAdjacencyList* wal) {
    wal->lists[0].length = 1;
    wal->lists[1].length = 2;
    wal->lists[2].length = 2;
    wal->lists[3].length = 0;
    wal->lists[4].length = 1;

    wal->lists[0].array = (GraphEdge*)malloc(1 * sizeof(GraphEdge));
    wal->lists[1].array = (GraphEdge*)malloc(2 * sizeof(GraphEdge));
    wal->lists[2].array = (GraphEdge*)malloc(2 * sizeof(GraphEdge));
    wal->lists[4].array = (GraphEdge*)malloc(1 * sizeof(GraphEdge));

    wal->lists[0].array[0] = (GraphEdge) {2, 5};
    wal->lists[1].array[0] = (GraphEdge) {0, 25};
    wal->lists[1].array[1] = (GraphEdge) {3, 15};
    wal->lists[2].array[0] = (GraphEdge) {1, 10};
    wal->lists[2].array[1] = (GraphEdge) {4, 20};
    wal->lists[4].array[0] = (GraphEdge) {1, 10};
}

// Graph2
void walFill2(WeightedAdjacencyList* wal) {
    wal->lists[0].length = 2;
    wal->lists[1].length = 2;
    wal->lists[2].length = 1;
    wal->lists[3].length = 1;
    wal->lists[4].length = 0;

    wal->lists[0].array = (GraphEdge*)malloc(2 * sizeof(GraphEdge));
    wal->lists[1].array = (GraphEdge*)malloc(2 * sizeof(GraphEdge));
    wal->lists[2].array = (GraphEdge*)malloc(1 * sizeof(GraphEdge));
    wal->lists[3].array = (GraphEdge*)malloc(1 * sizeof(GraphEdge));

    wal->lists[0].array[0] = (GraphEdge) {1, 1};
    wal->lists[0].array[1] = (GraphEdge) {2, 5};
    wal->lists[1].array[0] = (GraphEdge) {2, 7};
    wal->lists[1].array[1] = (GraphEdge) {3, 3};
    wal->lists[2].array[0] = (GraphEdge) {4, 1};
    wal->lists[3].array[0] = (GraphEdge) {2, 2};
}

bool walk(WeightedAdjacencyList* graph, int curr, int target, ArrayList* seen, ArrayList* path) {
    if (alGet(seen, curr)) {
        return false;
    }

    alSet(seen, curr, true);

    alAppend(path, curr);
    if (curr == target) {
        return true;
    }

    EdgeList adjs = graph->lists[curr];
    for (int i = 0; i < adjs.length; i++) {
        GraphEdge edge = adjs.array[i];

        if (walk(graph, edge.to, target, seen, path)) {
            return true;
        }
    }

    alPop(path, path->length - 1);
    return false;
}

ArrayList* dfs(WeightedAdjacencyList* graph, int source, int target) {
    ArrayList* seen = alNew(graph->length);
    alFill(seen, graph->length, false);
    ArrayList* path = alNew(graph->length);

    walk(graph, source, target, seen, path);

    alDelete(&seen);
    return path;
}

bool _hasUnvisited(ArrayList* seen, ArrayList* dists) {
    for (int i = 0; i < seen->length; i++) {
        if (!alGet(seen, i) && alGet(dists, i) < MAX_VAL) {
            return true;
        }
    }

    return false;
}

int _getLowestUnvisited(ArrayList* seen, ArrayList* dists) {
    int index = -1;
    int lowestDist = MAX_VAL;

    for (int i = 0; i < seen->length; i++) {
        if (alGet(seen, i)) {
            continue;
        }

        if (lowestDist > alGet(dists, i)) {
            lowestDist = alGet(dists, i);
            index = i;
        }
    }

    return index;
}

ArrayList* dijkstraShortestPath(WeightedAdjacencyList* graph, int source, int target) {
    ArrayList* seen = alNew(graph->length);
    alFill(seen, graph->length, false);
    ArrayList* prev = alNew(graph->length);
    alFill(prev, graph->length, -1);
    ArrayList* dists = alNew(graph->length);
    alFill(dists, graph->length, MAX_VAL);
    alSet(dists, source, 0);

    while (_hasUnvisited(seen, dists)) {
        int curr = _getLowestUnvisited(seen, dists);
        alSet(seen, curr, true);

        EdgeList adjs = graph->lists[curr];
        for (int i = 0; i < adjs.length; i++) {
            GraphEdge edge = adjs.array[i];
            if (alGet(seen, edge.to)) {
                continue;
            }

            int dist = alGet(dists, curr) + edge.weight;
            if (dist < alGet(dists, edge.to)) {
                alSet(dists, edge.to, dist);
                alSet(prev, edge.to, curr);
            }
        }
    }

    ArrayList* out = alNew(graph->length);

    int curr = target;
    while (alGet(prev, curr) != -1) {
        alAppend(out, curr);
        curr = alGet(prev, curr);
    }

    alAppend(out, source);
    alReverse(out);

    alDelete(&seen);
    alDelete(&prev);
    alDelete(&dists);
    return out;
}

void weightedAdjacencyListTest() {
    printf("Weighted adjacency list test\n");

    printf("\ndfs:\n");
    WeightedAdjacencyList* wal = walNew(5);
    walPrint(wal);

    walFill1(wal);
    walPrint(wal);

    ArrayList* list = dfs(wal, 0, 3);
    alPrintInt(list);
    alDelete(&list);

    walDelete(&wal);
    walPrint(wal);

    printf("\ndijkstra's shortest path:\n");
    WeightedAdjacencyList* wal2 = walNew(5);
    walPrint(wal2);

    walFill2(wal2);
    walPrint(wal2);

    ArrayList* list2 = dijkstraShortestPath(wal2, 0, 4);
    alPrintInt(list2);
    alDelete(&list2);

    walDelete(&wal2);
    walPrint(wal2);
}
