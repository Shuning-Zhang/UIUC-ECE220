#include <stdlib.h>
#include <stdio.h>
#include "slope.h"


int main() {
    int array[6][6];
    if(read_array("data.txt", array) == 0){
        printf("No valid input file.\n");
        return 0;
    }
    int index = find_nonslope_row(array);
    printf("row index = %d\n", index);
}

