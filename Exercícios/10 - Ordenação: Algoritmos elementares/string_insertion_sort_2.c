#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

void freeLines(wchar_t **lines) {
    int i;

    for (i = 0; lines[i][0] != '\0'; i++)
        free(lines[i]);
    free(lines[i]);
}

void readLine(wchar_t **line, wchar_t c, int i, int length) {
    if (c == '\n' || c == WEOF) {
        (*line)[i] = '\0';
        return;
    }
    (*line)[i] = c;
    if (i == length - 1) {
        length *= 2;
        *line = realloc(*line, length * sizeof(wchar_t));
    }
    readLine(line, getwchar(), i + 1, length);
}

wchar_t **readLines() {
    int i = 0, lines = 1;
    wchar_t **text = malloc(sizeof(wchar_t *));

    do {
        text[i] = malloc(sizeof(wchar_t));
        readLine(text + i, getwchar(), 0, 1);
        if (i < lines - 1)
            continue;
        lines *= 2;
        text = realloc(text, lines * sizeof(wchar_t *));
    } while (text[i++][0] != '\0');
    return text;
}

void insertionSort(wchar_t **lines) {
    int i;
    wchar_t *tmp;

    if (lines[1][0] == '\0')
        return;
    insertionSort(lines + 1);
    tmp = *lines;
    for (i = 0; lines[i + 1][0] != '\0' && wcscmp(lines[i + 1], tmp) < 0; i++)
        lines[i] = lines[i + 1];
    lines[i] = tmp;
}

int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    wchar_t **t;
    int i;

    wprintf(L"This program orders the lines of a text in lexicographic "
            L"order.\nType in a sequence of lines and press Enter twice:\n");
    t = readLines();
    insertionSort(t);

    wprintf(L"New sequence:\n");
    for (i = 0; t[i][0] != '\0'; i++)
        wprintf(L"%ls\n", t[i]);
    freeLines(t);
    free(t);
    return 0;
}
