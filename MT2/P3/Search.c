#include <stdio.h>
#include "Search.h"

//Your implementation of this function must be recursive
//return 1 if item found in data; otherwise, return 0
int Search(int item, int data[ROW][COL], int start_row, int end_row, int start_col, int end_col){
    //Your code starts here
    int i,j;
    i = start_row;
    j = end_col;

    if((start_row > end_row) || (start_col > end_col)){
      return 0;
    }
    if(data[i][j] == item){
      return 1;
    }

    if(start_col != end_col){
      if((data[0][j] > item)){
        return Search(item,data,start_row,end_row,start_col,end_col-1);
        }

    }

    if(data[i][end_col] < item){
      return Search(item,data,i+1,end_row,start_col,j);

    }
return 0;



}
