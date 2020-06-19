#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "array.h"

int main(){

  int arr[n][n];
  srand(1123353);
  memset(arr, 0, sizeof(int)*n*n);


  init_1st_row( arr );
  init_1st_col( arr );
  build_matrix_max(arr);
  print_matirx(arr); 
  return 0;
}

