#include <stdio.h>
#include <stdlib.h>

char *resizeString(char *string, int *size) {
    *size *= 2;
    return realloc(string, *size * sizeof(char));
}

char *readInput(int *size) {
    char c, *string = malloc(sizeof(char));
    int i;
    *size = 1;

    for (i = 0; (c = getchar()) != '\n' || c == EOF; string[i++] = c)
        if (i == *size - 1)
            string = resizeString(string, size);
    string[i++] = '\0';
    *size = i;
    return string;
}

int recursiveDeleteCharacter(char *string, char c, int size) {
    int pivot;

    if (size == 0)
        return 0;
    pivot = recursiveDeleteCharacter(string, c, --size);
    if (string[size] != c)
        string[pivot++] = string[size];
    return pivot;
}

int deleteCharacters(char *string, int size, char *chars) {
    int i;

    for (i = 0; chars[i] != '\0'; i++)
        size = recursiveDeleteCharacter(string, chars[i], size);
    return size;
}

void deleteCharacter(char *string, char c) {
    int i, j;

    for (i = j = 0; string[j] != '\0'; j++)
        if (string[j] != c)
            string[i++] = string[j];
    string[i] = string[j];
}

int main() {
    char *string;
    int stringSize, charQuantity;

    printf("This program deletes given characters from a given string. Type "
           "in a string and press ENTER:\n");
    string = readInput(&stringSize);

    printf("Type in characters to be deleted: ");
    stringSize = deleteCharacters(string, stringSize, readInput(&charQuantity));
    printf("This is the resulting string:\n%s\n", string);
    return 0;
}
