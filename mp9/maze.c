/*  INTRO PARAGRAPH
  In this file, I have createMaze, destroyMaze, printMaze and solveMazeDFS functions.
    createMaze: This function reads the file and assign maze variable. For file is opened for read.
                Number of rows and columns are read and assigned in the maze_t struct. Then I allocate
                memory for cells in 2D array structure. Then, I read every line in the file and assign
                characters to appropriate cells. Function assign start and row and column when
                encountered with those characters. Finally, function return pointer to the maze.

    destroyMaze:  This function frees memory allocated for maze. First of all, I free the char
                  array meaning row string for the cells one by one in a for loop. Then, I free
                  array of char pointer. Finally, maze freed.

    printMaze:    This function has a nested loop to go over every element in the array. It prints
                  single char for each element and prints new line at the end at the enf of rows.

    solveMazeDFS: This function implements DFS algorithm given in the website. First of all, I start
                  with returning false if indexes out of bound. If element is either Wall or Path or
                  Visited before, return false. If cells reached the end return true. If cell is none
                  of them, then assign that cell to Path. Later check if left neighbor is solution,
                  then right neigbor, then down neigbor and then up neigbor. If any of them are solution
                  return the Start cell from Path to Start and return true. If no solution, assign cell
                  as visited and return false.

*/

#include <stdio.h>
#include <stdlib.h>
#include "maze.h"


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
    maze_t * maze = (maze_t *)malloc(sizeof(maze_t)); //get a pointer to the matrix

    FILE * in_file; // declare file pointer
    in_file = fopen(fileName,"r");//open file to read
//assign start
    int m ,n;//declare integers for row and column numbers
    fscanf(in_file, "%d %d\n", &m, &n);//scan row and column numbers from file

    maze->width = n;//update struct variables
    maze->height = m;//update struct variables
    int i , j;//declare loop variables

    maze->cells = malloc(m*sizeof(char *));//get pointer to array of char pointer at the number of column

    for (i=0;i<m;i++){//for every column element
      maze->cells[i] = malloc(n*sizeof(char));//get a char array at the number of column
    }



    for(i=0;i<m;i++){//for the remaining lines (rows)
        char dummy[2*n];//declare a string
        fgets(dummy,2*n,in_file);//read the line
        for(j=0;j<n;j++){//go over number of columns
        maze->cells[i][j]= dummy[j];//assign every char value to maze cells
        if(dummy[j] == 'S'){//If start point
          maze->startRow = i;//update maze variables
          maze->startColumn = j;//update maze variables
        }
        else if(dummy[j] == 'E'){//If end point
          maze->endRow = i;//update maze variables
          maze->endColumn = j;//update maze variables
        }
      }
    }

    fclose(in_file);//close the file
    return maze;//return pointer to the maze
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
    int i;//declare loop variable
    for(i=0;i< maze->height;i++){//for number of rows
      free(maze->cells[i]);//free the char array
    }
    free(maze->cells);//free array of char pointers
    free(maze);//free the overall maze
    return;
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
    int n = maze->width;//get maze width
    int m = maze->height;//get maze height
    int i, j;//declare loop variables

    for(i=0;i<m;i++){//for every rows
      for(j=0;j<n;j++){//for every columns
        printf("%c", maze->cells[i][j]);//print the char
      }
      printf("\n");//go to next line for next rows
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
    if(col<0 || row <0 || col>=maze->width || row >=maze->height){//if cells out of bound
      return 0;//return false
    }

    if(maze->cells[row][col] == WALL || maze->cells[row][col] == PATH || maze->cells[row][col] == VISITED){
      //if cell is wall or path or visited before
      return 0;//return false
    }

    if(maze->cells[row][col] == END){//if reached end
      return 1;//return true
    }

    maze->cells[row][col] = PATH ;//assign path to the cell

    if(solveMazeDFS(maze,col -1, row)){//go left
      if(col == maze->startColumn && row == maze->startRow)//if start point
        maze->cells[row][col] = START;//assign start
        return 1;
    }

    if(solveMazeDFS(maze,col + 1, row)){//go right
      if(col == maze->startColumn && row == maze->startRow)//if start point
        maze->cells[row][col] = START;//assign start
        return 1;
    }

    if(solveMazeDFS(maze,col , row +1)){//go down
      //if(maze->cells[row+1][col] != START)
      if(col == maze->startColumn && row == maze->startRow)//if start point
        maze->cells[row][col] = START;//assign start
        return 1;
    }

    if(solveMazeDFS(maze,col , row -1)){//go up
      //if(maze->cells[row-1][col] != START)
      if(col == maze->startColumn && row == maze->startRow)//if start point
        maze->cells[row][col] = START;//assign start
        return 1;
    }

    maze->cells[row][col] = VISITED ;//assign visited before returning false

    return 0;//return
}
