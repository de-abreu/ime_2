#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3
#define SIDES 4

typedef struct tile {
    int x, y, g, f;
    struct tile *prev;
    char c;
} Tile;

typedef struct queue {
    Tile *t;
    struct queue *next;
} Queue;

typedef struct {
    int height, width;
    Tile ***tiles, *start, *end;
} Map;

Tile *newTile(int x, int y, int g, char c) {
    Tile *t = malloc(sizeof(Tile));

    t->x = x;
    t->y = y;
    t->g = g;
    t->c = c;
    return t;
}

Queue *newQueue(Tile *t, Queue *next) {
    Queue *q = malloc(sizeof(Queue));

    q->t = t;
    q->next = next;
    return q;
}

Queue *freeNode(Queue *q) {
    Queue *next = q->next;

    free(q);
    return next;
}

void freeQueue(Queue *q) {
    if (!q)
        return;
    freeQueue(q->next);
    free(q);
}

Tile **readTiles(FILE *f, Map *m, int row) {
    int i;
    char c;
    Tile **tiles = malloc((m->width + 2) * sizeof(Tile *));

    tiles[0] = NULL;
    tiles++;
    for (i = 0; i < m->width; i++) {
        if ((c = getc(f)) == '#')
            tiles[i] = NULL;
        else if (c == 's') {
            m->start = tiles[i] = newTile(i, row, 0, c);
            tiles[i]->prev = NULL;
        } else {
            tiles[i] = newTile(i, row, INT_MAX, c);
            if (c == 'e')
                m->end = tiles[i];
        }
    }
    getc(f);
    tiles[i] = NULL;
    return tiles;
}

Tile ***readRows(FILE *f, Map *m) {
    int i;
    Tile ***rows = malloc((m->height + 2) * sizeof(Tile **));
    rows[0] = calloc(m->width + 2, sizeof(Tile *));
    rows++;
    for (i = 0; i < m->height; i++)
        rows[i] = readTiles(f, m, i);
    rows[i] = calloc(m->width + 2, sizeof(Tile *));
    return rows;
}

Map *newMap(FILE *f) {
    Map *m = malloc(sizeof(Map));

    fscanf(f, "%d %d\n", &(m->width), &(m->height));
    m->tiles = readRows(f, m);
    return m;
}

Queue *push(Queue *q, Tile *t) {
    if (!q)
        return newQueue(t, NULL);
    if (q->t != t) {
        if (q->t->f > t->f)
            return newQueue(t, q);
        q->next = push(q->next, t);
    }
    return q;
}

Tile *pop(Queue **q) {
    Tile *t;

    if (!(*q))
        return NULL;
    t = (*q)->t;
    *q = freeNode(*q);
    return t;
}

Tile **listNeighbors(Map *m, Tile *t) {
    Tile **neighbors = malloc(SIDES * sizeof(Tile *));

    neighbors[NORTH] = m->tiles[t->y - 1][t->x];
    neighbors[EAST] = m->tiles[t->y][t->x + 1];
    neighbors[SOUTH] = m->tiles[t->y + 1][t->x];
    neighbors[WEST] = m->tiles[t->y][t->x - 1];
    return neighbors;
}

int manhattan(Tile *start, Tile *end) {
    return abs(start->x - end->x) + abs(start->y + end->y);
}

Tile *Astar(Map *m) {
    int i, distance;
    Queue *openSet = newQueue(m->start, NULL);
    Tile *t, **neighbors;

    while ((t = pop(&openSet)) && t != m->end) {
        neighbors = listNeighbors(m, t);

        for (i = 0; i < SIDES; i++) {
            if (!neighbors[i])
                continue;
            distance = t->g + 1;
            if (distance >= neighbors[i]->g)
                continue;
            neighbors[i]->prev = t;
            neighbors[i]->g = distance;
            neighbors[i]->f = distance + manhattan(neighbors[i], m->end);
            openSet = push(openSet, neighbors[i]);
        }
        free(neighbors);
    }
    freeQueue(openSet);
    return t;
}

void printMap(Map *m) {
    int i, j;
    Tile *t;

    for (i = 0; i < m->height; i++) {
        for (j = 0; j < m->width; j++) {
            t = m->tiles[i][j];
            if (t)
                printf("%c", t->c);
            else
                printf("#");
        }
        printf("\n");
    }
    printf("\n");
}

int path(Tile *end, int count) {
    if (!end->prev)
        printf("Start");
    else {
        count = path(end->prev, count + 1);
        end->c = 'O';
        if (end->prev->y > end->y)
            printf(" -> North");
        else if (end->prev->y < end->y)
            printf(" -> South");
        else if (end->prev->x < end->x)
            printf(" -> East");
        else
            printf(" -> West");
    }
    return count;
}

int main(int argc, char *argv[]) {
    int length = 0;
    FILE *f = fopen(argv[1], "r");
    Map *m = newMap(f);

    fclose(f);
    if (!Astar(m)) {
        printf("There's no viable path from start to goal.\n");
        return 1;
    }
    printf("From start to goal, there's the path: ");
    length = path(m->end, length);
    printf("\n");
    m->end->c = 'e';
    printf("\nHere its representation:\n");
    printMap(m);
    return 0;
}
