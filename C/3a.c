#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "file_handling.c"

int main(int argc, char const *argv[])
{
    char *fname = "../3_input.csv";
    FILE *fptr = open_file_rb(fname);

    int line_count = count_lines(fptr);

    int *input = (int *) malloc(sizeof(int) * line_count);

    read_file_binary_int(fptr, input);
    
    int counters[12] = {0}; // There are 12 digits in the input file.
    
    for (int i = 0; i < line_count; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            if (input[i] & (int) pow(2, j)) {
                counters[j]++;
            }
        }
        
    }

    int gamma, epsilon;
    gamma = 0;

    for (size_t i = 0; i < 12; i++)
    {
        if (counters[i] > line_count / 2)
        {
            // This means there are more ones than zeros in digit i. (position 0 here is the least-significant bit in the input)
            gamma += (int) pow(2, i);
        }
    }
    
    epsilon = gamma ^ 0b111111111111; // XOR with ones is an inversion. (straight inversion '~' does not work, it negates)

    printf("Gamma: %i, Epsilon: %i, Product: %i\n", gamma, epsilon, gamma * epsilon);

    return 0;
}
