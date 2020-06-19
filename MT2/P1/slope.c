#include <stdio.h>
#include "slope.h"


// Return index of the first row that is not a slope; otherwise return -1
int find_nonslope_row(int array[6][6]) {
  // Your code starts here
int rownum,col;
int in,de;

for(rownum =0;rownum<6;rownum++){
  in =0;
  de =0;
  for(col =0;col<5;col++){
    if(array[rownum][col] <array[rownum][col+1]){
      in++;
    }else if(array[rownum][col] >array[rownum][col+1])  {
      de++;
    }
  }
  if(in == 5 || de == 5){
    in =0;
    de =0;
  }else{
    return rownum;
  }
}
return -1;
}

int read_array(char* filename, int array[6][6]){
  // Your code starts here
  FILE *reader = fopen(filename, "r");
  int i, j;
  if(reader == NULL){
    return 0;
  }
  for(i=0;i<6;i++){
    for(j=0;j<6;j++){
      fscanf(reader,"%d",&array[i][j]);

    }
  }
  fclose(reader);
  return 1;
}
