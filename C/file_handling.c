#include <stdio.h>
#include <string.h>

#define FILE_NONE_ERROR -1

int count_lines(FILE *fptr) {
    char c;
    int linecount = 0;

    while(!feof(fptr)) {
        c = fgetc(fptr);
        if (c == '\n')
            linecount++;
    }
    // Make sure to rewind the pointer.
    rewind(fptr);
    return linecount;
}

FILE *open_file(char *fname) {
    FILE* fptr;
    fptr = fopen(fname, "r");

    if (!fptr) {
        fprintf(stderr, "File with filename \"%s\" does not exist.\n", fname);
        return 0;
    }
    return fptr;
}

int *read_file_int(FILE* fptr) {
    int line_count = count_lines(fptr);
    int *array = (int *) malloc(line_count * sizeof(int));
    char *cur = (char *) malloc(15);

    for (int i = 0; i < line_count; i++) {
        fgets(cur, 15, fptr);
        array[i] = atoi(cur);
    }

    rewind(fptr);
    return array;
}

int read_file_str(FILE* fptr, char **array) {
    int line_count = count_lines(fptr);
    for (int i = 0; i < line_count; i++) {
        array[i] = (char *) malloc(15);
        fgets(array[i], 15, fptr);
    }

    return 0;
}