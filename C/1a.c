#include <stdio.h>
#include <stdlib.h>

#include "file_handling.c"

int main(int argc, char const *argv[])
{
    char *fname = "../1_input.csv";
    int line_len = 15;
    int counter = 0;
    int cur_depth;
    int last_depth = 100000;
    // Really large number to make sure the first iteration never returns
    // that it is deeper than the last depth.

    FILE *fptr;
    fptr = fopen(fname, "r");

    char *str;
    str = (char *) malloc(line_len);

    while (!feof(fptr)) {
        fgets(str, line_len, fptr);
        cur_depth = atoi(str);
        if (cur_depth > last_depth)
            counter++;
        
        last_depth = cur_depth;
    }
    
    printf("Amount of times the depth was higher: %i\n", counter);

    fclose(fptr);
    return 0;
}