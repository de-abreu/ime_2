typedef struct {
    int nUSP;
    char *name;
} Student;

int binarySearch(int nUSP, Student **s, int size) {
    int index;

    if (size <= 0)
        return 0;
    index = size / 2;
    if (s[index]->nUSP >= nUSP)
        return binarySearch(nUSP, s, index);
    index++;
    return index + binarySearch(nUSP, s + index, size - index);
}

char *searchStudent(int nUSP, Student **s, int size) {
    int i = binarySearch(nUSP, s, size);
    return (i < size && s[i]->nUSP == nUSP) ? s[i]->name : "";
}
