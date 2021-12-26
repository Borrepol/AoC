#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "file_handling.c"

void copy_array(int *dest, int* src, int len) {
    for (int i = 0; i < len; i++) {
        dest[i] = src[i];
    }
}

// Start with the leftmost bit.

int main(int argc, char const *argv[])
{
    char *fname = "../3_input.csv";
    FILE *fptr = open_file_rb(fname);
    int line_count = count_lines(fptr);
    int *report = (int *) malloc(sizeof(int) * line_count);

    read_file_binary_int(fptr, report);

    int *cur, *zeros, *ones, zeros_i, ones_i, cur_len;

    cur = (int *) malloc(sizeof(int) * line_count);
    zeros = (int *) malloc(sizeof(int) * line_count);
    ones = (int *) malloc(sizeof(int) * line_count);
    zeros_i = 0;
    ones_i = 0;

    cur_len = line_count;
    copy_array(cur, report, cur_len);

    // Oxygen generator rating

    for (int i = 11; i >= 0; i--) {
        for (int j = 0; j < cur_len; j++) {
            if (cur[j] & (int) pow(2, i)) {
                // it's a one.
                ones[ones_i++] = cur[j];
            }
            else {
                zeros[zeros_i++] = cur[j];
            }
        }
        if (ones_i >= zeros_i) {
            cur_len = ones_i;
            copy_array(cur, ones, cur_len);
        }
        else {
            cur_len = zeros_i;
            copy_array(cur, zeros, cur_len);
        }
        zeros_i = ones_i = 0;
    }

    int oxy = cur[0];

    cur_len = line_count;
    copy_array(cur, report, cur_len);

    for (int i = 11; i >= 0; i--) {
        for (int j = 0; j < cur_len; j++) {
            if (cur[j] & (int) pow(2, i)) {
                ones[ones_i++] = cur[j];
            }
            else {
                zeros[zeros_i++] = cur[j];
            }
        }
        if (zeros_i <= ones_i) {
            cur_len = zeros_i;
            copy_array(cur, zeros, cur_len);
        }
        else {
            cur_len = ones_i;
            copy_array(cur, ones, cur_len);
        }
        zeros_i = ones_i = 0;
    }    
    
    int co2 = cur[0];

    printf("Oxygen Generator Rating: %i\nCO2 Scrubber Rating: %i\nProduct: %i\n", oxy, co2, oxy * co2);

    return 0;
}
