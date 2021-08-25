#include <stdbool.h>
#include <stdlib.h>

bool byte_diff (char * a, char * b) {
    unsigned int i, count = 0;

    for (i = 0; a[i] != '\0' || b[i] != '\0'; i++){
        if (a[i] != b[i])
            count++;
        if (count > 1)
            return false;
    }
    if (b[i] != '\0' || a[i] != '\0')
        return false;
    return true;
}

char * toString (char c) {
    char * string;
    string = malloc(2 * sizeof(string));
    string[0] = c;
    string[1] = '\0';
    return string;
}
