#include "game.h"
/*
in this mp, we are making the game of 2048 and through the functions, we were able to make and remake GAME
and we defined th emove functions using pointer
and compare the vaule stored in the pointer to cell needed
*/

game * make_game(int rows, int cols)

{
    //Dynamically allocate memory for game and cells (DO NOT modify this)
    game * mygame = malloc(sizeof(game));
    mygame->cells = malloc(rows*cols*sizeof(cell));

    //YOUR CODE STARTS HERE:  Initialize all other variables in game struct
    mygame->score =0; //initialize the score
    mygame->rows =rows; //load the row number
    mygame->cols = cols;//load the col number
    int i;
    cell * cell_ptr;
    cell_ptr = mygame->cells;
    for(i=0;i<rows*cols;i++){ //initialize all the cell to -1
        (*cell_ptr) = -1;
        cell_ptr++; //move to the next cell
    }

    return mygame;
}

void remake_game(game ** _cur_game_ptr,int new_rows,int new_cols)
/*! Given a game structure that is passed by reference, change the
game structure to have the given number of rows and columns. Initialize
the score and all elements in the cells to -1. Make sure that any
memory previously allocated is not lost in this function.
*/
{
/*Frees dynamically allocated memory used by cells in previous game,
then dynamically allocates memory for cells in new game.  DO NOT MODIFY.*/
free((*_cur_game_ptr)->cells);
(*_cur_game_ptr)->cells = malloc(new_rows*new_cols*sizeof(cell));

//YOUR CODE STARTS HERE:  Re-initialize all other variables in game struct
   (*_cur_game_ptr)->score =0; //set the new score to 0
   int i;



    cell * cell_ptr;
    cell_ptr = (*_cur_game_ptr)->cells;//create the pointer


    (*_cur_game_ptr)->rows = new_rows;
    (*_cur_game_ptr)->cols = new_cols;
   for(i=0;i<new_rows*new_cols;i++){//initialize all the cell to -1
       (*cell_ptr) = -1;
       cell_ptr++;
   }

return;
}

void destroy_game(game * cur_game)
/*! Deallocate any memory acquired with malloc associated with the given game instance.
    This includes any substructures the game data structure contains. Do not modify this function.*/
{
    free(cur_game->cells);
    free(cur_game);
    cur_game = NULL;
    return;
}

cell * get_cell(game * cur_game, int row, int col)
/*! Given a game, a row, and a column, return a pointer to the corresponding
    cell on the game. (See game.h for game data structure specification)
    This function should be handy for accessing game cells. Return NULL
if the row and col coordinates do not exist.
*/
{


    int rows,cols;
    rows = cur_game->rows;
    cols = cur_game->cols;
    cell * cell_ptr;
    cell_ptr = cur_game->cells;

    if(row>0 && row<rows){//see if the row is in the boundry
      if(col>0 && col<cols){ // see if the cols iis in the boundry
        cell_ptr = cell_ptr+row*cols+col; // create the Pointer
        return cell_ptr;
      }
    }

    return NULL;
}

int move_w(game * cur_game)
/*!Slides all of the tiles in cur_game upwards. If a tile matches with the
   one above it, the tiles are merged by adding their values together. When
   tiles merge, increase the score by the value of the new tile. A tile can
   not merge twice in one turn. If sliding the tiles up does not cause any
   cell to change value, w is an invalid move and return 0. Otherwise, return 1.
*/
{
    //YOUR CODE STARTS HERE
    int i,j,k,b;
    int c=0;
    cell * cell_ptr;
    cell_ptr = cur_game->cells;
    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int a[rows*cols];

    for(b=0;b<rows*cols;b++){
         a[b] =0; //initialize the array to keep track which one has moved
        }
    for(j=0;j<cols;j++){//move up without combining any cell,move out any space
      for(i=0;i<rows;i++){
        if(*(cell_ptr+i*cols+j) != -1){// found the non zero cell
          for(k=0;k<i;k++){
            if(*(cell_ptr+k*cols+j) == -1){//find an empty cell
              *(cell_ptr+k*cols+j) = *(cell_ptr+i*cols+j);//move the value stored in to the empty cell
              *(cell_ptr+i*cols+j) = -1;//clear the value of the origin cell
              c++;
              break;
            }
          }
        }
      }
    }
    //check it's neighbor value to see if could be combined
    for(j=0;j<cols;j++){
      for(i=0;i<rows;i++){
        if(*(cell_ptr+i*cols+j) != -1){
        if(*(cell_ptr+i*cols+j) == *(cell_ptr+(i+1)*cols+j)){//check if the cell would combine with the pne next to it
          if(a[i*cols+j+cols] == 0){
          *(cell_ptr+i*cols+j) = 2 * (*(cell_ptr+i*cols+j));//if could combine the cell
          cur_game->score = cur_game->score + (*(cell_ptr+i*cols+j));//combine update the score
          *(cell_ptr+i*cols+j+cols) = -1; //emmpty the cell
          c = 1;
          a[i*cols+j+cols] = 1;
        }
        }
      }
    }
  }
  for(j=0;j<cols;j++){//move up without combining any cell,move out any space,algrithem same as before
    for(i=0;i<rows;i++){
      if(*(cell_ptr+i*cols+j) != -1){
        for(k=0;k<i;k++){
          if(*(cell_ptr+k*cols+j) == -1){
            *(cell_ptr+k*cols+j) = *(cell_ptr+i*cols+j);
            *(cell_ptr+i*cols+j) = -1;
            break;
          }
        }
      }
    }
  }
  if(c==0){
    return 0;
  }else{
      return 1;
  }
//    for(b=0;b<rows*cols;b++){
//      a[b] =0;
//    }
/*
    for(j=0;j<cols;j++){
      for(i=0;i<rows;i++){
        if(*(cell_ptr+i*cols+j) != -1){
          for(k = 0;k<i;k++){
            if(*(cell_ptr+k*cols+j) == -1){
            w =k-1;
              if(*(cell_ptr+i*cols+j) == *(cell_ptr+w*cols+j)){
                if(a[w*cols+j] != 1){
                  *(cell_ptr+w*cols+j) = *(cell_ptr+w*cols+j)+*(cell_ptr+i*cols+j);
                  *(cell_ptr+i*cols+j) = -1;
                  a[w*cols+j] = 1;
                  c=1;
                  cur_game->score = cur_game->score + 2*(*(cell_ptr+i*cols+j));
                  break;
                }
              }

              *(cell_ptr+k*cols+j) = *(cell_ptr+i*cols+j);
              *(cell_ptr+i*cols+j) = -1;
              break;
            }else if(*(cell_ptr+i*cols+j) == *(cell_ptr+i*cols+j-cols)){
              if(a[i*cols+j-cols] == 0){
                *(cell_ptr+i*cols+j-cols) = *(cell_ptr+i*cols+j-cols)+*(cell_ptr+i*cols+j);
		            cur_game->score = cur_game->score + 2*(*(cell_ptr+i*cols+j));
                *(cell_ptr+i*cols+j) = -1;
                a[i*cols+j-cols] = 1;
                c=1;

                break;
              }
            }
          }
        }
      }
    }

    if(c==0){
      return 0;
    }else{
        return 1;
    }
*/
};

int move_s(game * cur_game) //slide down
{
    //YOUR CODE STARTS HERE
    int i,j,k,b;
    int c=0;
    cell * cell_ptr;
    cell_ptr = cur_game->cells;
    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int a[rows*cols];

    for(b=0;b<rows*cols;b++){
         a[b] =0;
        }
    for(j=0;j<cols;j++){//move down without combining any cell,move out any space
      for(i=rows-1;i>=0;i--){
        if(*(cell_ptr+i*cols+j) != -1){
          for(k=rows-1;k>i;k--){
            if(*(cell_ptr+k*cols+j) == -1){
              *(cell_ptr+k*cols+j) = *(cell_ptr+i*cols+j);
              *(cell_ptr+i*cols+j) = -1;
              c++;
              break;
            }
          }
        }
      }
    }
    //check it's neighbor value to see if could be combined
    for(j=0;j<cols;j++){
      for(i=rows-1;i>0;i--){
        if(*(cell_ptr+i*cols+j) != -1){//if the cell is not empty
        if(*(cell_ptr+i*cols+j) == *(cell_ptr+(i-1)*cols+j)){//check the cell above it if hold same value
          if(a[(i-1)*cols+j+cols] == 0){
          *(cell_ptr+i*cols+j) = 2 * (*(cell_ptr+i*cols+j));//update the cell
          cur_game->score = cur_game->score + (*(cell_ptr+i*cols+j));//update the score
          *(cell_ptr+(i-1)*cols+j) = -1;//empty the cell above it
          c ++;
          a[(i-1)*cols+j+cols] = 1;
        }
      }
    }
  }
  }
    for(j=0;j<cols;j++){//move down without combining any cell,move out any space
    for(i=rows-1;i>=0;i--){
      if(*(cell_ptr+i*cols+j) != -1){
        for(k=rows-1;k>=0;k--){
          if(*(cell_ptr+k*cols+j) == -1){
            *(cell_ptr+k*cols+j) = *(cell_ptr+i*cols+j);
            *(cell_ptr+i*cols+j) = -1;
            break;
          }
        }
      }
    }
    }
    if(c==0){
    return 0;
    }else{
      return 1;
    }
};

int move_a(game * cur_game) //slide left
{
    //YOUR CODE STARTS HERE
    int i,j,k,b;
    int c=0;
    cell * cell_ptr;
    cell_ptr = cur_game->cells;
    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int a[rows*cols];

    for(b=0;b<rows*cols;b++){
         a[b] =0;
       }
       for(i=0;i<rows;i++){//move left any spaces without combine the tiles
         for(j=0;j<cols;j++){
           if(*(cell_ptr+i*cols+j) != -1){
             for(k=0;k<j;k++){
               if(*(cell_ptr+i*cols+k) == -1){
                 *(cell_ptr+i*cols+k) = *(cell_ptr+i*cols+j);
                 *(cell_ptr+i*cols+j) = -1;
                 c++;
                 break;
               }
             }
           }
         }
       }
       for(i=0;i<rows;i++){//check if could combine with any cell
       for(j=0;j<cols-1;j++){
         if(*(cell_ptr+i*cols+j) != -1){//find a non zero cell

         if(*(cell_ptr+i*cols+j) == *(cell_ptr+i*cols+j+1)){//if the one to the right has the same value
           if(a[i*cols+j] == 0){
           *(cell_ptr+i*cols+j) = 2 * (*(cell_ptr+i*cols+j));//update the cell
           cur_game->score = cur_game->score + 2*(*(cell_ptr+i*cols+j+1));//update the score
           *(cell_ptr+i*cols+j+1) = -1;//empty the cell to the right
           c ++;
           a[i*cols+j+1] = 1;

         }
       }
     }
   }
 }

   for(i=0;i<rows;i++){//move left any spaces after combine the tiles
     for(j=1;j<cols;j++){
       if(*(cell_ptr+i*cols+j) != -1){
         for(k=0;k<j;k++){
           if(*(cell_ptr+i*cols+k) == -1){
             *(cell_ptr+i*cols+k) = *(cell_ptr+i*cols+j);
             *(cell_ptr+i*cols+j) = -1;
             break;
           }
         }
       }
     }
   }
   /*
   for(i=0;i<rows;i++){
     for(j=0;j<cols;j++){
       if(a[i*cols+j] == 1 && j%cols != 0){
         for(k=j+1;k<cols;k++){
           if(*(cell_ptr+i*cols+k) != -1){
             *(cell_ptr+i*cols+j) = *(cell_ptr+i*cols+k);
             *(cell_ptr+i*cols+k) = -1;
             break;
           }
         }
       }
     }
   }
   */
   if(c==0){
   return 0;
   }else{
     return 1;
   }
};

int move_d(game * cur_game){ //slide to the right
    //YOUR CODE STARTS HERE
    int i,j,k,b;
    int c=0;
    cell * cell_ptr;
    cell_ptr = cur_game->cells;
    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int a[rows*cols];

    for(b=0;b<rows*cols;b++){
         a[b] =0;
       }
       for(i=0;i<rows;i++){//move right any spaces without combine the tiles
         for(j=cols-1;j>=0;j--){
           if(*(cell_ptr+i*cols+j) != -1){
             for(k=cols-1;k>j;k--){
               if(*(cell_ptr+i*cols+k) == -1){
                 *(cell_ptr+i*cols+k) = *(cell_ptr+i*cols+j);
                 *(cell_ptr+i*cols+j) = -1;
                 c++;
                 break;
               }
             }
           }
         }
       }
       for(i=0;i<rows;i++){//check if the cell could combine with any cell
       for(j=cols-1;j>0;j--){//check from right to left
         if(*(cell_ptr+i*cols+j) != -1){//find an non zero cell
         if(*(cell_ptr+i*cols+j) == *(cell_ptr+i*cols+j-1)){//see if the cell to the left has the same value
           if(a[i*cols+j] == 0){
           *(cell_ptr+i*cols+j) = 2 * (*(cell_ptr+i*cols+j));//if yes update the cell
           cur_game->score = cur_game->score + (*(cell_ptr+i*cols+j));//update the score
           *(cell_ptr+i*cols+j-1) = -1; //empty the cell to the left
           c ++;
           a[i*cols+j+1] = 1;
         }
       }
     }
   }
 }

   for(i=0;i<rows;i++){//move right any spaces after combine the tiles
     for(j=cols-2;j>=0;j--){
       if(*(cell_ptr+i*cols+j) != -1){
         for(k=cols-1;k>j;k--){
           if(*(cell_ptr+i*cols+k) == -1){
             *(cell_ptr+i*cols+k) = *(cell_ptr+i*cols+j);
             *(cell_ptr+i*cols+j) = -1;
             break;
           }
         }
       }
     }
   }
   if(c==0){
   return 0;
   }else{
     return 1;
   }
};

int legal_move_check(game * cur_game)
/*! Given the current game check if there are any legal moves on the board. There are
    no legal moves if sliding in any direction will not cause the game to change.
Return 1 if there are possible legal moves, 0 if there are none.
 */
{
  int i,j;
  int c =0;
  int up,down,left,right,itself;
  cell * cell_ptr;
  cell_ptr = cur_game->cells;
  int rows = cur_game->rows;
  int cols = cur_game->cols;
  for(i=0;i<rows;i++){
    for(j=0;j<cols;j++){
      if(*(cell_ptr+i*cols+j) == -1){
        c++;
      }
    }
  }
    for(i=0;i<rows;i++){
      for(j=0;j<cols;j++){
        itself = *(cell_ptr+i*cols+j);
        if(i-1>=0){//found the cell value to the up
          up = *(cell_ptr+(i+1)*cols+j);
        }else{
          up = 0;
        }
        if(i+1<rows){// found the cell value to the below it
          down = *(cell_ptr+(i-1)*cols+j);
        }else{
          down = 0;
        }
        if(j-1>=0){//found the cell value to the left
          left = *(cell_ptr+(i)*cols+j-1);
        }else{
          left = 0;
        }
        if(j+1<cols){//found the cell value to right
          right = *(cell_ptr+(i)*cols+j+1);
        }else{
          right = 0;
        }
        if(itself == up || itself == down || itself == right || itself == left){
          c++;//check if the  two cell have the same value if yes, return 1
        }
      }
    }
    if(c==0){
    return 0;
    }else{
      return 1;
    }
}                                                                                                                                                                                                               

/*! code below is provided and should not be changed */

void rand_new_tile(game * cur_game)
/*! insert a new tile into a random empty cell. First call rand()%(rows*cols) to get a random value between 0 and (rows*cols)-1.
*/
{

	cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    if (cell_ptr == NULL){
        printf("Bad Cell Pointer.\n");
        exit(0);
    }


	//check for an empty cell
	int emptycheck = 0;
	int i;

	for(i = 0; i < ((cur_game->rows)*(cur_game->cols)); i++){
		if ((*cell_ptr) == -1){
				emptycheck = 1;
				break;
		}
        cell_ptr += 1;
	}
	if (emptycheck == 0){
		printf("Error: Trying to insert into no a board with no empty cell. The function rand_new_tile() should only be called after tiles have succesfully moved, meaning there should be at least 1 open spot.\n");
		exit(0);
	}

    int ind,row,col;
	int num;
    do{
		ind = rand()%((cur_game->rows)*(cur_game->cols));
		col = ind%(cur_game->cols);
		row = ind/cur_game->cols;
    } while ( *get_cell(cur_game, row, col) != -1);
        //*get_cell(cur_game, row, col) = 2;
	num = rand()%20;
	if(num <= 1){
		*get_cell(cur_game, row, col) = 4; // 1/10th chance
	}
	else{
		*get_cell(cur_game, row, col) = 2;// 9/10th chance
	}
}

int print_game(game * cur_game)
{
    cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int i,j;

	printf("\n\n\nscore:%d\n",cur_game->score);


	printf("\u2554"); // topleft box char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // top box char
	printf("\u2557\n"); //top right char


    for(i = 0; i < rows; i++){
		printf("\u2551"); // side box char
        for(j = 0; j < cols; j++){
            if ((*cell_ptr) == -1 ) { //print asterisks
                printf(" **  ");
            }
            else {
                switch( *cell_ptr ){ //print colored text
                    case 2:
                        printf("\x1b[1;31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4:
                        printf("\x1b[1;32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8:
                        printf("\x1b[1;33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 16:
                        printf("\x1b[1;34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 32:
                        printf("\x1b[1;35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 64:
                        printf("\x1b[1;36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 128:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 256:
                        printf("\x1b[32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 512:
                        printf("\x1b[33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 1024:
                        printf("\x1b[34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 2048:
                        printf("\x1b[35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4096:
                        printf("\x1b[36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8192:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
					default:
						printf("  X  ");

                }

            }
            cell_ptr++;
        }
	printf("\u2551\n"); //print right wall and newline
    }

	printf("\u255A"); // print bottom left char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // bottom char
	printf("\u255D\n"); //bottom right char

    return 0;
}

int process_turn(const char input_char, game* cur_game) //returns 1 if legal move is possible after input is processed
{
	int rows,cols;
	char buf[200];
	char garbage[2];
    int move_success = 0;

    switch ( input_char ) {
    case 'w':
        move_success = move_w(cur_game);
        break;
    case 'a':
        move_success = move_a(cur_game);
        break;
    case 's':
        move_success = move_s(cur_game);
        break;
    case 'd':
        move_success = move_d(cur_game);
        break;
    case 'q':
        destroy_game(cur_game);
        printf("\nQuitting..\n");
        return 0;
        break;
	case 'n':
		//get row and col input for new game
		dim_prompt: printf("NEW GAME: Enter dimensions (rows columns):");
		while (NULL == fgets(buf,200,stdin)) {
			printf("\nProgram Terminated.\n");
			return 0;
		}

		if (2 != sscanf(buf,"%d%d%1s",&rows,&cols,garbage) ||
		rows < 0 || cols < 0){
			printf("Invalid dimensions.\n");
			goto dim_prompt;
		}

		remake_game(&cur_game,rows,cols);

		move_success = 1;

    default: //any other input
        printf("Invalid Input. Valid inputs are: w, a, s, d, q, n.\n");
    }




    if(move_success == 1){ //if movement happened, insert new tile and print the game.
         rand_new_tile(cur_game);
		 print_game(cur_game);
    }

    if( legal_move_check(cur_game) == 0){  //check if the newly spawned tile results in game over.
        printf("Game Over!\n");
        return 0;
    }
    return 1;
}
