#include <stdio.h>
#include <string.h>

#define FILE_NONE_ERROR -1
#define MAX_STR_LEN 15

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

FILE *open_file_r(char *fname) {
    FILE* fptr;
    fptr = fopen(fname, "r");

    if (!fptr) {
        fprintf(stderr, "File with filename \"%s\" does not exist.\n", fname);
        return 0;
    }
    return fptr;
}

FILE *open_file_rb(char *fname) {
    FILE* fptr;
    fptr = fopen(fname, "rb");

    if (!fptr) {
        fprintf(stderr, "File with filename \"%s\" does not exist.\n", fname);
        return 0;
    }
    return fptr;
}

int *read_file_int(FILE* fptr) {
    int line_count = count_lines(fptr);
    int *array = (int *) malloc(line_count * sizeof(int));
    char *cur = (char *) malloc(MAX_STR_LEN);

    for (int i = 0; i < line_count; i++) {
        fgets(cur, MAX_STR_LEN, fptr);
        array[i] = atoi(cur);
    }

    rewind(fptr);
    return array;
}

void read_file_binary_int(FILE* fptr, int* array) {
    int line_count = count_lines(fptr);
    char *cur = (char *) malloc(MAX_STR_LEN);
    for (int i = 0; i < line_count; i++) {
        fgets(cur, MAX_STR_LEN, fptr);
        array[i] = strtol(cur, NULL, 2);
    }
    rewind(fptr);
}

void read_file_str(FILE* fptr, char **array) {
    int line_count = count_lines(fptr);
    for (int i = 0; i < line_count; i++) {
        array[i] = (char *) malloc(MAX_STR_LEN);
        fgets(array[i], MAX_STR_LEN, fptr);
    }
    rewind(fptr);
}