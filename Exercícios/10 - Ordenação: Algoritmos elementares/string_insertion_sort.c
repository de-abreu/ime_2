#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

typedef struct {
	wchar_t **lines;
	int lineCount;
} Text;

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

void freeLines(wchar_t **lines, int i, int size) {
	while (i < size)
		free(lines[i++]);
}

Text *readText() {
	Text *t = malloc(sizeof(Text));
	int i;

	t->lines = malloc(sizeof(wchar_t *));
	t->lineCount = 1;
	for (i = 0; readLine(t->lines + i); i++) {
		if (i < t->lineCount - 1)
			continue;
		t->lineCount *= 2;
		t->lines = realloc(t->lines, t->lineCount * sizeof(wchar_t *));
	}

	freeLines(t->lines, i, t->lineCount);
	t->lineCount = i;
	return t;
}

void insertionSort(wchar_t **lines, int size) {
	int i;
	wchar_t *tmp;

	if (size <= 1)
		return;
	--size;
	insertionSort(lines, size);
	tmp = lines[size];
	for (i = size; i > 0 && wcscmp(lines[i - 1], tmp) > 0; i--)
		lines[i] = lines[i - 1];
	lines[i] = tmp;
}

int main() {
	setlocale(LC_ALL, "pt_BR.UTF-8");
	Text *t;
	int i;

	wprintf(L"This program orders the lines of a text in lexicographic "
	        L"order.\nType in a sequence of lines and press Enter twice:\n");
	t = readText();
	insertionSort(t->lines, t->lineCount);

	wprintf(L"New sequence:\n");
	for (i = 0; i < t->lineCount; i++)
		wprintf(L"%ls\n", t->lines[i]);
	freeLines(t->lines, 0, t->lineCount);
	free(t->lines);
	free(t);
	return 0;
}
