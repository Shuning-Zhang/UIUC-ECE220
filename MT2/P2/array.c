#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "array.h"


void print_matirx(int arr[][n]){
  for(int i = 0 ; i < n ; ++i){
    for(int j = 0; j < n ; ++j){
      printf("%d\t", arr[i][j]);
    }
    printf("\n");
  }
}


void init_1st_row(int arr[][n]){
  // Your code starts here
  int j;
  int RandomNumber;
  arr[0][0] = 0;
  for(j =1;j<n;j++){
    RandomNumber = rand()%100;
    arr[0][j] = RandomNumber;
  }
}


void init_1st_col(int arr[][n]){
  // Your code starts here
  int i;
  int RandomNumber;
  for(i =1;i<n;i++){
    RandomNumber = rand()%100;
    arr[i][0] = RandomNumber;
  }
}


void build_matrix_max(int arr[][n]){
  // Your code starts here

  int i,j;
  int num;
  i =1;
  j=1;
  while((i<n) && (j<n)){
    num = arr[i][j-1];
    if(num < arr[i-1][j]){
      num = arr[i-1][j];
    }
    arr[i][j] = num;
    if((i == 1) && (j != n-1)){
      i = j+1;
      j =1;
    }else if(j == n-1){
      j = i+1;
      i =n-1;
    }else{
      i--;
      j++;
    }
  }
}
