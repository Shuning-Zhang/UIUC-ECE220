#include <stdio.h>
#include <stdlib.h>
#include "maze.h"
/*in this code we are solving the maze,which first we create the maze, but also using the 2D array
and by solving the maze using recursive function, which i chosed to go down first
solved the maze. and take the start case into consideration. then print and destory the maze
*/
/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
    // Your code here. Make sure to replace following line with your own code.
    int row,col,i,j;
    char enter;
    maze_t *cmaze = malloc(sizeof(maze_t));//malloc maze

    FILE *reader;
    reader = fopen(fileName,"r");
    fscanf(reader,"%d %d%c",&col,&row,&enter);


    cmaze->height = row;
    cmaze->width = col;

    cmaze -> cells =(char**)malloc(row*sizeof(char*));//allocate for maze cells
    for(i=0;i<row;i++){
      cmaze->cells[i] = (char*)malloc(col*sizeof(char));
    }
    char c;
    i=0;
    j=0;
    while((c=fgetc(reader))!=EOF){
      if(c == '\n'){ //if get change line move to the next row of array
        i++;
        j=0;
        continue;
      }else{//if not change line update the array value
        cmaze->cells[i][j] = c;
        j++;
      }
    }
    fclose(reader);

    for(i=0;i<row;i++){//finding the address of S
      for(j=0;j<col;j++){
        if(cmaze->cells[i][j] == START){//store it into startRow and startColumn
          cmaze->startRow = i;
          cmaze->startColumn =j;
        }
      }
    }
    for(i=0;i<row;i++){//finding the address of E
      for(j=0;j<col;j++){
        if(cmaze->cells[i][j] == END){//store it into endRow and endColumn
          cmaze->endRow = i;
          cmaze->endColumn =j;
        }
      }
    }
    return cmaze;
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
    // Your code here.
    int i;
    for(i=0;i<maze->height;i++){//free cells
      free(maze->cells[i]);
    }
    free(maze->cells);
    free(maze);//free maze
    maze = NULL;
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    // Your code here.
    int row,col,i,j;
    row = maze->height;//copy height into row
    col = maze->width;//copy width into col
    for(i=0;i<row;i++){
      for(j=0;j<col;j++){
        printf("%c",maze->cells[i][j]);
      }
      printf("\n");
    }
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */
int solveMazeDFS(maze_t * maze, int col, int row)
{
    // Your code here. Make sure to replace following line with your own code.
    if((col>(maze->width)-1) || (col <0) || (row>(maze->height)-1) || (row<0)){//check if out of bound
      maze->cells[maze->startRow][maze->startColumn] = START;
      return 0;
    }
    if(maze->cells[row][col] != EMPTY && maze->cells[row][col] != START && maze->cells[row][col] != END){//check the cell type
      return 0;
    }
    if(maze->cells[row][col] == END){//reached end
      maze->cells[maze->startRow][maze->startColumn] = START;//change start back
      return 1;
    }
    maze->cells[row][col] = PATH;//mark the cells
    if(solveMazeDFS(maze,col,row+1) == 1){//check the downward cell
      return 1;
    }
    if(solveMazeDFS(maze,col-1,row) == 1){//check the cell to the left
      return 1;
    }
    if(solveMazeDFS(maze,col+1,row) == 1){//check the cell to the right
      return 1;
    }
    if(solveMazeDFS(maze,col,row-1) == 1){//check the upward cell
      return 1;
    }
    maze->cells[row][col] = VISITED;// mark the cell to visited
    maze->cells[maze->startRow][maze->startColumn] = START;
    return 0;
}
