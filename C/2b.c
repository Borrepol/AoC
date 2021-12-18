#include <stdio.h>
#include <stdlib.h>

#include "file_handling.c"

#define UP 0
#define DOWN 1
#define FORWARD 2

void parse_array(char **a1, int **a2, int count) {
    char c;
    int j;

    for (int i = 0; i < count; i++) {
        a2[i] = (int *) malloc(sizeof(int) * 2);
        switch (a1[i][0]) {
            case 'u':
                a2[i][0] = UP;
                break;
            case 'd':
                a2[i][0] = DOWN;
                break;
            default:
                a2[i][0] = FORWARD;
                break;
        }

        j = 1;
        do {
            c = a1[i][j];
            if (c == ' ') {
               a2[i][1] = a1[i][j + 1] - '0'; // Converting char to int.
               break;
            } 
            j++;
        } while (c != '\0');
    }
}

int main(int argc, char const *argv[])
{
    char *fname = "../2_input.csv";
    FILE *fptr = open_file(fname);

    int line_count = count_lines(fptr);

    char *array[line_count];
    int *array1[line_count];

    read_file_str(fptr, array);
    parse_array(array, array1, line_count);
    
    int depth, h_pos, aim, x;
    depth = h_pos = aim = 0;

    for (int i = 0; i < line_count; i++)
    {
        x = array1[i][1];
        switch (array1[i][0]) {
            case UP:
                aim -= x;
                break;
            case DOWN:
                aim += x;
                break;
            case FORWARD:
                h_pos += x;
                depth += aim * x;
                break;
            default:
                fprintf(stderr, "Something went wrong in processing.");
                return 1;
                break;
        }
    }
    
    printf("Final depth: %i\nFinal horizontal position: %i\nMultiplied: %i\n", depth, h_pos, depth * h_pos);

    return 0;
}
