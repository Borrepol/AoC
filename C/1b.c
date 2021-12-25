#include <stdio.h>
#include <stdlib.h>

#include "file_handling.c"

// Here use a sliding window instead of single measurements.
// Compare sums of three depths. Stop when you can no longer
// make a sum of three.

int main(int argc, char const *argv[])
{
    char *fname = "../1_input.csv";
    FILE *fptr = open_file_r(fname);
    // In an if-statement: 0 is false, any other value is true.
    if (!fptr)
        return FILE_NONE_ERROR;

    int line_count, line_len, cur_depth, last_depth, counter;
    line_count = count_lines(fptr);
    line_len = 15;
    counter = 0;
    last_depth = 100000;
    // Really large number to make sure the first iteration never returns
    // that it is deeper than the last depth.

    int *data = read_file_int(fptr);

    for (int i = 0; i < line_count - 2; i++) {
        cur_depth = 0;
        for (int j = 0; j < 3; j++) {
            cur_depth += data[i + j];
        }

        if (cur_depth > last_depth)
            counter++;
        
        last_depth = cur_depth;
    }
    
    printf("Amount of times the depth was higher: %i\n", counter);

    fclose(fptr);
    return 0;
}