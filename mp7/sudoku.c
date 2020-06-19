#include "sudoku.h"

//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------

//in this mp, we are filling out the sudoku, first checking each row col and the 3x3 box,
//to see if the number has appeared before. return true if the number haven't appeared before
//after setting up the checking statement, go into the check_sudoku function, where it would return true if all cell are filled
//and use backtracking to check if the previous filled cell is right or wrong, if wrong clear the filling and try again.
//by doing so it would help fill out the soduko.

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
// check in the row if the number has already appeared, if appeared return 1, if not return 0.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {
  int col;
  assert(i>=0 && i<9);


  for(col =0; col<9;col++){
    if(sudoku[i][col]==val){
      return 1;
    }
  }
  return 0;
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
// check in the col if the number has already appeared, if appeared return 1, if not return 0.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {
  int row;
  assert(j>=0 && j<9);

  // BEG TODO
  for(row=0;row<9;row++){
    if(sudoku[row][j] == val){
      return 1;
    }
  }

  return 0;
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9);
  int a,b,c,d,row,col;
  a = i % 3; //number of row to the left most boundry of 3x3
  b = i - a; //update the row number right most boundry of 3x3
  c = j % 3; //number of col to the top most boundry of 3x3
  d = j - c;//update col to the bottom boundry of 3x3

  for(row = b;row<b+3;row++){ //set the boundry of the grid
    for(col = d;col <d+3;col++){ //set the boundry of the grid
      if(sudoku[row][col]==val){
        return 1;
      }
    }
  }

  return 0;
  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);
  if(is_val_in_row(val,i,sudoku) || is_val_in_col(val,j,sudoku) || is_val_in_3x3_zone(val,i,j,sudoku) ){
    return 0; //if appeared return 0
    //the if statement checks if the number has appeared in the row, col, ot the 3x3 zone.
  }

  return 1;

}
// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {

  int i,j,row,col,num;
  int check =0;

  for(i=0;i<9;i++){
    for(j=0;j<9;j++){
      if(sudoku[i][j] != 0){
        check++; //increment the number of check when a cell is not 0
        if(check == 81){
          return 1;//if all the cell were filled return 1
        }
      }else{
        row =i; //stored the number of row
        col =j; //stored the number of col
      }
    }
  }
  for(num=1;num<=9;num++){
    if(is_val_valid(num,row,col,sudoku)){ //check if the number has appeared before
      sudoku[row][col] = num; //if not fill in the number
      if(solve_sudoku(sudoku)){ //check if the number would work for the next cell
        return 1;
      }
      sudoku[row][col] = 0; //clear the cell if not true.
    }
  }
  return 0;
  // END TODO.
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}
