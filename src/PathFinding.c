#include "PathFinding.h"

typedef struct Point {
    int x;
    int y;
} Point;

// The maze
typedef struct Maze {
    char* array;
    int rowLen;
    int colLen;
} Maze;

char mazeGet(Maze* maze, Point point) {
    return maze->array[(point.y * maze->rowLen) + point.x];
}

Maze* getNewMaze() {
    char mazeChars[] = {
        '#', '#', '#', '#', '#', '#', '#', '#', ' ', '#',
        '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#',
        '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#',
        '#', ' ', '#', '#', '#', '#', '#', '#', ' ', '#',
        '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
        '#', '$', '#', '#', '#', '#', '#', '#', '#', '#',
    };

    Maze* maze = (Maze*)malloc(sizeof(Maze));
    maze->array = (char*)malloc(100 * sizeof(char));
    memmove(maze->array, mazeChars, sizeof(mazeChars));
    maze->rowLen = 10;
    maze->colLen = 6;

    return maze;
}

// The map here is to mark the points that the algorithm has already visited
typedef struct MazeMap {
    bool* array;
    int rowLen;
    int colLen;
} MazeMap;

bool mapGet(MazeMap* map, Point point) {
    return map->array[(point.y * map->rowLen) + point.x];
}

void mapSet(MazeMap* map, Point point, bool value) {
    map->array[(point.y * map->rowLen) + point.x] = value;
}

MazeMap* getNewMap() {
    MazeMap* map = (MazeMap*)malloc(sizeof(MazeMap));
    map->array = (bool*)calloc(100, sizeof(bool));
    map->rowLen = 10;
    map->colLen = 6;

    return map;
}

typedef struct PointArray {
    Point* array;
    int length;
} PointArray;

PointArray* paNew() {
    PointArray* pArray = (PointArray*)malloc(sizeof(PointArray));
    pArray->array = (Point*)malloc(100 * sizeof(Point));
    pArray->length = 0;
    return pArray;
}

void paPush(PointArray* array, Point value) {
    if (array->length == 100) {
        return;
    }

    array->array[array->length] = value;
    array->length++;
}

void paPop(PointArray* array) {
    array->length--;
}

bool paCompare(PointArray* array1, PointArray* array2) {
    if (array1->length != array2->length) {
        return false;
    }

    for (int i = 0; i < array1->length; i++) {
        if (array1->array[i].x != array2->array[i].x ||
            array1->array[i].y != array2->array[i].y) {
            return false;
        }
    }

    return true;
}

void paPrint(PointArray* array) {
    for (int i = 0; i < array->length; i++) {
        printf("%d, %d\n", array->array[i].x, array->array[i].y);
    }
}

const Point directions[4] = {
    {0, -1},
    {1, 0},
    {0, 1},
    {-1, 0},
};

bool walk(Maze* maze, Point curr, MazeMap* map, PointArray* path) {
    // out of bounds
    if (curr.x < 0 || curr.x >= maze->rowLen ||
        curr.y < 0 || curr.y >= maze->colLen) {
        return false;
    }

    // on a wall
    if (mazeGet(maze, curr) == '#') {
        return false;
    }

    // on the end
    if (mazeGet(maze, curr) == '$') {
        paPush(path, curr);
        return true;
    }

    // already visited
    if (mapGet(map, curr)) {
        return false;
    }

    // otherwise
    mapSet(map, curr, true);
    paPush(path, curr);

    for (int i = 0; i < 4; i++) {
        Point nextLocation = {
            curr.x + directions[i].x,
            curr.y + directions[i].y,
        };

        bool success = walk(maze, nextLocation, map, path);
        if (success) {
            return true;
        }
    }

    paPop(path);
    return false;
}

PointArray* pathFind(Maze* maze, Point start) {
    MazeMap* map = getNewMap();
    PointArray* resultPath = paNew();

    walk(maze, start, map, resultPath);

    free(map->array);
    free(map);
    return resultPath;
}

PointArray* getTargetPath() {
    Point targetPoints[] = {
        {8, 0},
        {8, 1},
        {8, 2},
        {8, 3},
        {8, 4},
        {7, 4},
        {6, 4},
        {5, 4},
        {4, 4},
        {3, 4},
        {2, 4},
        {1, 4},
        {1, 5},
    };

    PointArray* targetPath = paNew();
    memmove(targetPath->array, targetPoints, sizeof(targetPoints));
    targetPath->length = 13;
    return targetPath;
}

void pathFindingTest() {
    printf("Path finding test\n");

    Maze* maze = getNewMaze();
    Point start = {8, 0};

    PointArray* resultPath = pathFind(maze, start);
    printf("Result:\n");
    paPrint(resultPath);

    PointArray* targetPath = getTargetPath();
    printf("Target:\n");
    paPrint(targetPath);

    printf("Comparison: %d\n", paCompare(targetPath, resultPath));

    free(maze->array);
    free(maze);
    free(resultPath->array);
    free(resultPath);
    free(targetPath->array);
    free(targetPath);
}
