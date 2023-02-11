#include "./queueArray.h"
#include <stdio.h>

Queue *newQueue(int capacity) {
    Queue *q = malloc(sizeof(Queue));

    q->array = malloc(capacity * sizeof(int));
    q->start = 0;
    q->end = -1;
    q->capacity = capacity;
    return q;
}

void freeQueue(Queue *q) {
    free(q->array);
    free(q);
}

Queue *resize(Queue *q) {
    q->capacity *= 2;
    return realloc(q, q->capacity * sizeof(Queue));
}

int length(Queue *q) { return q->end - q->start + 1; }

bool isFull(Queue *q) { return length(q) == q->capacity; }

bool isEmpty(Queue *q) { return !length(q); }

void shift(Queue *q) {
    int i, offset;

    for (i = offset = q->start; i <= q->end; i++)
        q->array[i - offset] = q->array[i];
    q->start = 0;
    q->end -= offset;
}

bool insert(Queue *q, int value) {
    if (isFull(q))
        return false;
    if (q->end == q->capacity - 1)
        shift(q);
    q->array[++q->end] = value;
    return true;
}

int dequeue(Queue *q) {
    int i = q->array[q->start++];

    q->start %= q->capacity;
    return i;
}

int minimum(int a, int b) { return (b > a) ? a : b; }

bool blocked(char **map, int height, int width, int x, int y) {
    return (x < 0 || x >= width || y < 0 || y >= height || map[x][y] == '#');
}

int distance(int size, int dist[][size], int a, int b) {
    int i, min;

    if (dist[a][b] > 0)
        return dist[a][b];
    min = size;
    for (i = 0; i < size; i++)
        if (dist[a][i] > 0)
            min = minimum(min, dist[a][i] + distance(size, dist, i, b));
    return min;
}

int *distanceFrom(int size, int dist[][size], int to) {
    int from, *distFrom = malloc(size * sizeof(int));
    Queue *points = newQueue(size);

    for (from = 0; from < size; from++)
        distFrom[from] = size;
    distFrom[to] = 0;
    insert(points, to);

    while (!isEmpty(points)) {
        from = dequeue(points);
        for (to = 0; to < size; to++) {
            if (dist[from][to] != 1 || distFrom[to] < size)
                continue;
            distFrom[to] = distFrom[from] + 1;
            insert(points, to);
        }
    }
    return distFrom;
}

int main() {
    int i, dist[6][6] = {{0, 1, 0, 0, 0, 0}, {0, 0, 1, 0, 0, 0},
                         {0, 0, 0, 0, 1, 0}, {0, 0, 1, 0, 1, 0},
                         {1, 0, 0, 0, 0, 0}, {0, 1, 0, 0, 0, 0}};
    int *distFrom = distanceFrom(6, dist, 3);

    for (i = 0; i < 6; i++)
        printf("%d ", distFrom[i]);
    printf("\n");
    printf("%d\n", distance(6, dist, 3, 0));
    return 0;
}
