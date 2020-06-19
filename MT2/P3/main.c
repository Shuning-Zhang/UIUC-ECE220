#include <stdlib.h>
#include <stdio.h>
#include "Search.h"

int main(){
    int data[4][5] = {{3, 10, 29, 50, 59},
                      {6, 14, 30, 52, 63},
                      {7, 18, 32, 54, 64},
                      {9, 27, 48, 55, 66}};
    int items[9] = {7, 32, 50, 66, 0, 16, 19, 62, 70};
    printf("Searching in data:\n");
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 5; j++){
            printf("%d ", data[i][j]);
        }
        printf("\n");
    }
    for(int i = 0; i < 9; i++){
        if(Search(items[i], data, 0, 3, 0, 4)){
            printf("%d found!\n", items[i]);
        } else{
            printf("%d not found!\n", items[i]);
        }
    }
    return 0;
}
