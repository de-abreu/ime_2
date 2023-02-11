#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

typedef struct {
    int key;
    wchar_t *data;
} Node;

typedef struct {
    Node *items;
    int size;
} Array;

/* Freeing memory*/

void freeArray(Array *A) {
    int i;

    for (i = 0; i < A->size; i++)
        free(A->items[i].data);
    free(A->items);
    free(A);
}

/* Read functions */

bool readLine(wchar_t **line) {
	int i = 0, length = 1;
	wchar_t c;

	*line = malloc(sizeof(wchar_t));
	while ((c = getwchar()) != WEOF && c != '\n') {
		if (i == length - 1) {
			length *= 2;
			*line = realloc(*line, length * sizeof(wchar_t));
		}
		(*line)[i++] = c;
	}
	(*line)[i] = '\0';

	if (i)
        return true;
	return false;
}

Array *readText() {
	Array *A = malloc(sizeof(Array));
	int i;

	A->items = malloc(sizeof(Node));
	A->size = 1;
	for (i = 0; readLine(&(A->items[i].data)); i++) {
        A->items[i].key = i;
		if (i < A->size - 1)
			continue;
		A->size *= 2;
		A->items = realloc(A->items, A->size * sizeof(Node));
	}
	A->size = i;
	return A;
}

/* Sort wchars */

void swap(Node *a, Node *b) {
    Node tmp = *a;
    *a = *b;
    *b = tmp;
}

bool compareRadix (wchar_t *a, wchar_t *b) {
	int i;

	for (i = 0; a[i] != '\0'; i++) {
		if (a[i] > b[i] || b[i] == '\0')
			return true;
		if (a[i] < b[i])
			return false;
	}
	return false;
}

Node * medianOfDatasets(Node *a, Node *b, Node *c) {
	if (compareRadix(a->data, b->data) ^ compareRadix(a->data, b->data))
		return a;
	if (compareRadix(a->data, b->data) ^ compareRadix(c->data, b->data))
		return b;
	return c;
}

int partitionByData (Node *n, int size) {
	int i, j, last = size - 1;

	swap(n + last, medianOfDatasets(n, n + size / 2, n + last));
	for (i = j = 0; i < last; i++)
	    if (compareRadix(n[last].data, n[i].data))
			swap(&n[i], &n[j++]);
	swap(&n[i], &n[j]);
	return j;
}

void quickSortData (Node *n, int size) {
	int pivot;

	if (size <= 1)
		return;
	pivot = partitionByData(n, size);
	quickSortData(n, pivot++);
	quickSortData(n + pivot, size - pivot);
}

/* Sort ints */

Node * medianOfKeys(Node *a, Node *b, Node *c) {
	if ((a->key > b->key) ^ (a->key > c->key))
		return a;
	if ((b->key < a->key) ^ (b->key < c->key))
		return b;
	return c;
}

int partitionByKey (Node *n, int size) {
	int i, j, last = size - 1;

	swap(n + last, medianOfKeys(n, n + size / 2, n + last));
	for (i = j = 0; i < last; i++)
	    if (n[i].key <= n[last].key)
			swap(&n[i], &n[j++]);
	swap(&n[i], &n[j]);
	return j;
}

void quickSortKeys (Node *n, int size) {
	int pivot;

	if (size <= 1)
		return;
	pivot = partitionByKey(n, size);
	quickSortKeys(n, pivot++);
	quickSortKeys(n + pivot, size - pivot);
}

/* Driver function */

int main () {
    setlocale(LC_ALL, "pt_BR.UTF-8");
	Array *A;
	int i;

    wprintf(L"This program orders the lines of a text in lexicographic "
	        L"order, and then by their insertion order.\nType in a sequence "
            L"of lines and press Enter twice:\n");
    A = readText();

    quickSortData(A->items, A->size);
    wprintf(L"\nSort by data:\n");
	for (i = 0; i < A->size; i++)
		wprintf(L"%ls\n", A->items[i].data);

    quickSortKeys(A->items, A->size);

    wprintf(L"\nSort by key:\n");
	for (i = 0; i < A->size; i++)
		wprintf(L"%ls\n", A->items[i].data);

    freeArray(A);
    return 0;
}
