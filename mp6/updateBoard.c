

//partner: sz31, soohar2
//in this program i wrote the three functions in which it checks how many live neighbor the cell has.
//than make another array adding the live neighbor to its corrsponding location, for checking if the cell
//should be alive or dead for the next state. and update the livestable if any cell changes.


 int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){
	int currRow,currCol; //defint the two item for loop
	int LiveN =0; //initialize the life neighbor count
   for(currRow = row -1; currRow <= row+1; currRow++){ //for loop check each neighborof the giving cell
       if(currRow>= 0 && currRow<=boardRowSize-1){
           for(currCol = col-1; currCol <= col+1; currCol++){
               if(currCol>=0 && currCol <= boardColSize-1){
                   if(currRow != row || currCol != col){ //skip the cell itself
                     if (board[currRow*boardColSize+currCol] == 1){ //check if the cell is alive
                             LiveN ++; //increment the neighbor counting
                         }
									 }

               }
           }
       }
   }
 return LiveN; //return the result for later use
}
 /*
  * Update the game board to the next step.
  * Input:
  * board: 1-D array of the current game board. 1 represents a live cell.
  * 0 represents a dead cell
  * boardRowSize: the number of rows on the game board.
  * boardColSize: the number of cols on the game board.
  * Output: board is updated with new values for next step.
  */
  void updateBoard (int* board, int boardRowSize, int boardColSize){
    int neighbor[boardColSize*boardRowSize]; //array for storing the alive neighbor cells
    int r,c;
    for(r=0; r<boardRowSize;r++){
        for(c=0; c< boardColSize; c++){
           neighbor[r*boardColSize+c] = countLiveNeighbor(board,boardRowSize,boardColSize,r,c);
           //put the LiveN in the new array at the place where the cell corrspond.

         }
    }
     for(r=0; r<boardRowSize;r++){ //start at (0,0) check if the cell should be alive or not for the next state
         for(c=0; c< boardColSize; c++){

             if(board[r*boardColSize+c] == 1){
                 if(neighbor[r*boardColSize+c] == 2 || neighbor[r*boardColSize+c] == 3){
                   //comparing the live cell's neighbor with 2 and 3 to see if it's over populated or under populated
                     board[r*boardColSize+c] = 1; //if neighbor = 2 or 3 the cell keep being alive
                 }else{
                   board[r*boardColSize+c] = 0; //if neighbors is not 2 or 3, the cell become dead
                 }
             }
             if(board[r*boardColSize+c] == 0){
                //comparing the dead cell's neighbor with  3 to see if it will become alive again
                 if(neighbor[r*boardColSize+c] == 3){
                     board[r*boardColSize+c] = 1; //if the cell has three neighbor it become alive
                 }
             }
         }
     }

 }
/*

  * aliveStable
  * Checks if the alive cells stay the same for next step
  * board: 1-D array of the current game board. 1 represents a live cell.
  * 0 represents a dead cell
  * boardRowSize: the number of rows on the game board.
  * boardColSize: the number of cols on the game board.
  * Output: return 1 if the alive cells for next step is exactly the same with
  * current step or there is no alive cells at all.
  * return 0 if the alive cells change for the next step.
  */

  /*repeat the steps above but instead of changing the dead cell to alive of alive cell to dead,
  it returns 0 and 1. if no change made return 1, if changes are made return 0
  */
 int aliveStable(int* board, int boardRowSize, int boardColSize){
   int neighbor[boardColSize*boardRowSize];
   int r,c;
   for(r=0; r<boardRowSize;r++){
       for(c=0; c< boardColSize; c++){
          neighbor[r*boardColSize+c] = countLiveNeighbor(board, boardRowSize, boardColSize, r, c);
        }
      }
    for(r=0; r<boardRowSize;r++){
        for(c=0; c< boardColSize; c++){

            if(board[r*boardColSize+c] == 1){
                if(neighbor[r*boardColSize+c] == 2 || neighbor[r*boardColSize+c] == 3){
                    board[r*boardColSize+c] = 1;
                }else{
                  return 0; //there would be change to the board
                }
            }
            if(board[r*boardColSize+c] == 0){
                if(neighbor[r*boardColSize+c] == 3){
                    return 0; //there would be change to the board
                }
            }
        }
    }

	 return 1;
}
