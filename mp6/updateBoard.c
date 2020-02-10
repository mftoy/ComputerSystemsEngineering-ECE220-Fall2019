/*INTRO PARAGRAPH
	In this program, I will implement the Game of Life algorithm introduced in
  MP6 website. There are three functions in this file: countLiveNeighbor,
  updateBoard and aliveStable.

  countLiveNeighbor counts live cells given a row and column indices. We need
  to look at 8 neighbor cells around the particular (row,column). For this reason,
  I created 2 nested for loops ranging from "row-1" to "row+1" and "col-1" to
  "col+1". After each for loop state, I check if the loop variables are valid.
  For example, rows should be in the range of 0 to "boardRowSize-1" and columns
  should be in the range of 0 to "boardRowSize-1". Then, I make sure loop indices
	are not equal to function row and col indeces. If they are neighbor cells, I
	count the number of are alive cells by incrementing count for each neigbor cell
	with value 1. Lastly, function returns count number.

	updateBoard function update the board according to given specifications. First,
	I create another array at the same size board to equate number. The reason is
	the board stores current cell states and new array stores values for next state
	based	on given specification. If a live cell is surrounded by 2 or 3 alive cells
	then that cells is alive in the next state. If not, new array should be changed to
	0. On the other hand, if a dead cell is surrounded by 3 cells, that dead cell
	should be turned into a 1 in the next state. This function implement this with
	for loops and if statements. Lastly, board is assigned to new array before
	function terminated to update board array.

	aliveStable function check if alive cells change states in the next cycle.
	It goes over every element with a for loop. If element is 1, it calls countLiveNeighbor
	function. If the function return a number other than 2 or 3 than live cells will
	change state. Therefore, function return 0. Otherwise, if none of the cells change
	their value, then function returns 1.
 */

#include <stdio.h>
#include <stdlib.h>
/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */

int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){
int liveNeighbor=0; // set liveNeighbor count to 0
int r, c, index; // declare variables for rows, columns and board 1-D index
for(r = row-1;r<=row+1;r++){//look for row neighboring cells
	if(r>=0 && r<boardRowSize){// check if the given index is valid
		for(c = col-1;c<=col+1;c++){//look for col neigboring cells
			if(c>=0  && c<boardColSize){//check if the given index is valid
				if (c!= col || r!=row){ // skip the cell itself
					index = r*boardColSize + c;//calculate 1-D index
					if(board[index]==1){//if the neigboring cells is aliveStable
						liveNeighbor++;//increment count
					}
				}
			}
		}
	}
}
return liveNeighbor;//return the count
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
void updateBoard(int* board, int boardRowSize, int boardColSize) {
	int r,c,i;//declare row, col and loop indices
	int count;// declare count variable
	int boardIndex;// declare 1-D index
	int newCells[boardRowSize*boardColSize];//create a new array for next state of cells
	for(i=0;i<boardRowSize*boardColSize;i++){//for all the elements in board
		newCells[i]=board[i];//assign them to new array
	}
for (r =0;r<boardRowSize;r++){//go over all rows
	for(c=0;c<boardColSize;c++){//go over all columns
		count = countLiveNeighbor(board,boardRowSize,boardColSize,r,c);//count number of live neighbors
		boardIndex = r * boardColSize + c;//calculate 1-D index
		if (board[boardIndex]==1){//if the cell is live
			if (count != 2 && count != 3){ //check if count is not 2 or 3
				newCells[boardIndex] = 0;//if not, next state will be dead cell
			}
		}
		else if (count == 3){//check if there are 3 live cells around a dead cell
			newCells[boardIndex] = 1;//if so, assign live cell in the next stage
		}
	}
}
for(i=0;i<boardRowSize*boardColSize;i++){//for every element in the next stage array
	board[i]=newCells[i];//update board array at the end
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
int aliveStable(int* board, int boardRowSize, int boardColSize){
	int i;//declare loop variable
	for(i=0;i<boardRowSize*boardColSize;i++){ //for every element in the board
		if(board[i] == 1){//if cell is alive
			int row = i / boardColSize;//calculate row index in 2-D
			int col = i % boardColSize;//calculate col index in 2-D
			int flag = countLiveNeighbor(board,boardRowSize,boardColSize, row, col);//check number of count cell
			if (!(flag ==2 || flag == 3 )){//if there are less than 2 or more than 3 live cells,
				return 0; // then it will change state in the next state
			}
		}
	}
	return 1;//if the program is not interrupted then it will not change state
}
