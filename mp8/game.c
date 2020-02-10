#include "game.h"
/*  INTRO PARAGRAPH
In this MP, I implemented make_game, remake_game, get_cell, move_w, move_s,
move_a, move_d and legal_move_check functions. I will provide what I have done
for each function in the following paragraphs.

make_game: For this I need to set row and column numbers in the struct. Also, I
           needed to initialize score for the game. LAstly, I used a for loop
           to set each cell to -1(empty).

remake_game: In this function, I need to set new row and column number to a new
             memory location freed from old game. For this purpose, I used
             single pointer which is game struct instead of double pointer as
             defined in the argument. Then, I set row, column and score in the
             new game. Lstly, I used a for loop to initialize all cells to -1.

get_cell: In this function I need to return a pointer to cell array in the game.
          First, I created a if statement to check legitimate indexes. If index
          entries are not valid, function return NULL. For valid entries, I
          declared an index variable to convert 2D array indexes to 1D array
          index. Then, Function return the some of cells pinter in the struct
          and index variable.

move_w: In this function, I need to slide all tiles. If two tiles match, I
        combine them. While combining cells, I also update the score. Then, I
        slide all cell to upwards. I have two nested loops in this function.
        The first one checks for tiles to combine and the other one is for
        sliding cells. I declared a integer array called dummy. This array
        stores non-empty values in the row and its index. For non-empty cells,
        if their value equal to value in the dummy, then I found the pointer for
        the variable and set that location to twice of its value. Also, I update
        score at this point. Then,I set current location to -1 to empty it and
        clear dummy array to avoid double slide in one function. If cells are
        not the same, I update the dummy array to current cell location.
        In the slide up loops,  I start from the first row and check for non-empty
        cells. For non- empty cells, I check if there is any empty cells above
        that cell and finally replace the current cell with the tpo most empty cell.

move_s: This function has the same algorithm as move_w function. First, I check
        for cells with the same value from bottom to top and combine them. Also,
        I slide cells downwards using the same algorithm in the move_w.

move_a: This function has the same algorithm as move_w function except I check
        cells in the same row intead of checking cells in the same column. First,
        I combine the same value cells in the same row and slide them left.

move_d: This function has the same algorithm as move_a function. Intead of
        starting from leftmost column, I start from rightmost column to combine
        cells. Then I slide cells to the right.

legal_move_check: In this function, I need to find if there is any possible
                  move left in the game board. For this pupose, I check for
                  empty cells in the board array. If there are empty arrays in
                  the board, user can move cells. If all cells have a value, then
                  I check for the same value neighbors in the up, down, right
                  and left neighbors. If there is a the same value neighbor,
                  user can combine those cells. If non of these is possible, then
                  function returns 0.


*/

game * make_game(int rows, int cols)
/*! Create an instance of a game structure with the given number of rows
    and columns, initializing elements to -1 and return a pointer
    to it. (See game.h for the specification for the game data structure)
    The needed memory should be dynamically allocated with the malloc family
    of functions.
*/
{
    //Dynamically allocate memory for game and cells (DO NOT modify this)
    game * mygame = malloc(sizeof(game));
    mygame->cells = malloc(rows*cols*sizeof(cell));

    //YOUR CODE STARTS HERE:  Initialize all other variables in game struct
    mygame->rows = rows; // set the struct row to argument rows
    mygame->cols = cols; // set the struct cols to argument cols
    mygame->score = 0; // initialize score to 0


    int i; // declare an loop variable
    for (i=0;i<rows*cols;i++){//for every variable in the board
      mygame->cells[i]= -1;//set every cell to -1
    }

    return mygame;//return the struct
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
   (* _cur_game_ptr)->rows = new_rows; //set new rows in the new game board
   (* _cur_game_ptr)->cols = new_cols; // set new cols in the new game board
   (* _cur_game_ptr)->score = 0; // set new score to zero

   int i;// declare loop variable
   for (i=0;i<new_rows*new_cols;i++){ // go over eveery cell in the array
     (* _cur_game_ptr)->cells[i]= -1; // set every cell to -1
   }


	return;// terminate function
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
    //YOUR CODE STARTS HERE

    if(row >= 0 && col >= 0 && row< cur_game->rows && col < cur_game->cols){
      // check if the row and col arguments are legitimate
      int index = row*(cur_game->cols)+col;// if so calculate 1D array index
      return cur_game->cells + index; // return some of cells pointer plus index
    }
    return NULL;// return Null for invalid row and column index
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
    int row, col; //declare loop variables
    int flag = 0; // declare flag to check if any cells changed


    for(col=0;col<(cur_game->cols);col++){//go over each col
      int dummy[2] = {-1, -1};// declare integer array to store non empty values
      for(row=0;row<(cur_game->rows);row++){// go over each row
        cell* value; // declare a cell pointer
        value = get_cell(cur_game,row,col);// set the pointer to current cell
        if(*value != -1){// if cell is non-empty
          if(*value == dummy[0]){// check if its equal to previous non-empty variable
            int index = dummy[1]*(cur_game->cols)+col;// if so, calculate index for previous variable
            cur_game->cells[index] = 2*dummy[0];//assign sum of two variables to upper elements
            cur_game->score += 2*dummy[0]; // update the score
            *value = -1;// set the current cell to -1
            dummy [0]= -1;//clear dummy array
            dummy[1] = -1; // clear dummy array
            flag =1 ;//set flag to 1
          }
          else {//value is not empty and not previous non-empty value
            dummy [0]= * value;//set the dummy array to current value
            dummy[1] = row;//set the dummy array to current index
          }
        }
      }
    }

    for(col=0;col<(cur_game->cols);col++){// go over every col
      for(row=0;row<(cur_game->rows);row++){//go over every row
        cell *value;// declare a cel pointer
        value = get_cell(cur_game,row,col);// set the pointer to current cell
        if(*value != -1){// if non-empty cell
          int empty_row = -1;// declare a veriable to find the empty cells in that col
          int i;// declare loop variable

          for (i = row -1; i>=0;i--){//look at the cells above current cell
            cell *dummy = get_cell(cur_game,i,col);//declare a pointer to top cells
            if (*dummy == -1){// if those cells are empty
              empty_row = i;//update empty row
            }
            else{//if encountered non empty cell
              break;// stop the loop
            }
          }

          if (empty_row != -1){// if there are empty cells
            cell* index = get_cell(cur_game,empty_row,col);// get the address of the empty cell
            *index = *value;//set that cell to current cell's value
            *value = -1;//set current cell to zero
            flag =1;// set flag 1
          }
        }
      }
    }

    return flag;// return flag
};

int move_s(game * cur_game) //slide down
{
    //YOUR CODE STARTS HERE
    int row, col;// declare loop variables
    int flag =0;//set flag variable


    for(col=0;col<(cur_game->cols);col++){//go over evry col
      int dummy[2]={-1 , -1};// declare an array to find match cells
      for(row=(cur_game->rows)-1;row>=0;row--){//go over every row
        cell *value;// declare a cell pointer
        value = get_cell(cur_game,row,col);//set pointer to current cell
        if(*value != -1){// if cell is non-empty
          if(*value == dummy[0]){//check if it is the same with previous one
            cell* index = get_cell(cur_game, dummy[1], col);// if so get the previous cell
            *index = 2*dummy[0];// update the previous cell
            cur_game->score += 2*dummy[0];// update the score
            *value = -1;// empty the current cell
            dummy[0]=-1;// empty dummy array to avoid double combine
            dummy[1]= -1;//empty dummy array
            flag = 1;// set flag to 1

          }
          else{// if values are not equal
            dummy[0] = *value;//set the dummy array to current value
            dummy[1]=row;// set dummy array to current location

          }
        }
      }
    }

    for(col=0;col<(cur_game->cols);col++){//go over every col in the game
      for(row=(cur_game->rows)-1;row>=0;row--){//go over every row in the game
        cell *value;// declare cell pointer
        value = get_cell(cur_game,row, col);// set pointer to the current cell
        if(*value != -1){// if the cell is not empty
          int empty_row = -1;// declare a empty_row variable
          int i;// declare a loop variable

          for(i = row+1;i<(cur_game->rows);i++){// look at the cell below
            cell *dummy = get_cell(cur_game,i,col);//get the cells below
            if(*dummy == -1){// if they are empty
              empty_row=i;// update empty_row
            }
            else{//non-empty cell encountered
              break;//stop for loop
            }
          }

          if(empty_row != -1)  {// non empty_row encountered
            cell *index = get_cell(cur_game, empty_row,col);//get the non empty cell
            *index = *value;//update the empty cell
            *value = -1;//empty the current cell
            flag  =1;// set flag to 1
          }
          }
        }
      }
    return flag;// return flag
};

int move_a(game * cur_game) //slide left
{
    //YOUR CODE STARTS HERE
    int row, col;//declare loop variables
    int flag =0;// declare flag variable

      for(row=0;row<(cur_game->rows);row++){//go over every row
        int dummy[2] = {-1 , -1};//set an match cells array
        for(col=0;col<(cur_game->cols);col++){//go over every column
            cell *value;//declare a cell pointer
            value = get_cell(cur_game,row,col);//aset pointer to current cell
            if(*value != -1){//if non-empty cell
              if(*value == dummy[0]){//check if its equal to previous cell
                  cell* index = get_cell(cur_game, row, dummy[1]);//get the previous cell
                  * index = 2* dummy[0];//update previous cell
                  cur_game->score += 2*dummy[0];//update game score
                  *value = -1;//set the current cell to zero
                  dummy[0]=-1;//empty the array
                  dummy[1]=-1;//empty the array
                  flag =1;// set flag to 1
              }
              else{// if non-empty variable
                dummy[0]= *value;//set array to current variable
                dummy[1]= col;// set array to current location

              }
            }
        }
      }

      for(row=0;row<(cur_game->rows);row++){// go over each row
        for(col=0;col<(cur_game->cols);col++){// go over each col
          cell *value = get_cell(cur_game,row,col);//get a cell pointer
          if(*value != -1){// if non-empty cell
            int empty_col = -1;//declare an empty cell variable
            int i;//set loop variables
            for(i = col -1; i >=0; i--){//for cells right of current cell
              cell *dummy = get_cell(cur_game,row,i);// get those cell
              if(*dummy == -1){// if there are empty
                empty_col = i;// update empty cell index
              }
              else{// otherwise
                break;// stop the loop
              }
            }

            if(empty_col != -1){//if there is any empty cells
              cell *index = get_cell(cur_game,row, empty_col);//get the empty cell pointer
              *index = *value;//update empty cell
              *value = -1;//empty current cell
              flag =1;// update flag
            }
          }

        }
      }


    return flag;//return flag
};

int move_d(game * cur_game){ //slide to the right
    //YOUR CODE STARTS HERE
    int row, col;//declare loop variables
    int flag =0;//declare flag variable

    for(row=0;row<(cur_game->rows);row++){//go over every row
      int dummy[2] = {-1, -1};//initialize a dummy array
      for(col=(cur_game->cols)-1;col>= 0;col--){//go over every col
        cell* value = get_cell(cur_game,row,col);//get a pointer to current cell
        if(*value != -1){//for non-empty cells
          if(*value == dummy[0]){//if there are equal to previous value
            cell* index = get_cell(cur_game, row, dummy[1]);// get the previous cell
            * index = 2* dummy[0];//update the previous cell
            cur_game->score += 2*dummy[0];// update the score
            *value = -1;// empty the current cell
            dummy[0]=-1;// clear dummy array
            dummy[1]=-1;//clear dummy array
            flag =1;// set flag to 1
          }
          else{// if there are equal to previous value
            dummy[0]= *value;//update dummy array
            dummy[1]= col;//update dummy index
          }
        }
      }
    }

    for(row=0;row<(cur_game->rows);row++){//go over every row
      for(col=(cur_game->cols)-1;col>= 0;col--){//go over every col
        cell *value = get_cell(cur_game,row,col);// get the current cell
        if(*value != -1){//if cell is non empty
          int empty_col = -1;//set an empty col variable
          int i;//declare a loop variable

          for(i = col+1; i <(cur_game->cols); i++){//for cell right of current cell
            cell* dummy= get_cell(cur_game,row,i);//get those cells pointer
            if(*dummy == -1){//if they are empty
              empty_col = i;//update the empty column
            }
            else{//otherwise
              break;//stop the loop
            }
          }

          if(empty_col != -1){//if there are non-empty cells
            cell *index = get_cell(cur_game,row, empty_col);//get the pointer to empty cell
            *index = *value;//update the empty cell
            *value = -1;//clear the current cell
            flag =1;// set flag to 1
          }
        }
      }
    }

    return flag;// return flag
};

int legal_move_check(game * cur_game)
/*! Given the current game check if there are any legal moves on the board. There are
    no legal moves if sliding in any direction will not cause the game to change.
	Return 1 if there are possible legal moves, 0 if there are none.
 */
{
    //YOUR CODE STARTS HERE
    cell *dummy = get_cell(cur_game,0,0);//get a pointer to first element
    int i;//declare loop variable
    for(i=0;i<((cur_game->cols)*(cur_game->rows));i++){//go over every element in the board
      if(*(dummy +i) == -1){// if there empty cell
        return 1;// game is not done
      }
    }
    int row,col;//declare loop variables
    for(row=0;row<cur_game->rows;row++){//go over every row
      for(col=0;col<cur_game->cols;col++){//go over every col
        dummy = get_cell(cur_game,row,col);//get the current cell's pointer

        cell *neighbor = get_cell(cur_game,row-1,col);//get the up neighbor
        if(neighbor != NULL && *neighbor == *dummy){//if it is equal to current cell
          return 1;//user can use move_w
        }

        neighbor = get_cell(cur_game,row,col-1);//get the pointer to left neighbor
        if(neighbor != NULL && *neighbor == *dummy){//if it is equal to current cell
          return 1;//user can use move_a
        }

        neighbor = get_cell(cur_game,row+1,col);//get pointer to bottom cell
        if(neighbor != NULL && *neighbor == *dummy){//if that cell equal to current cell
          return 1;// user can use move_s
        }

        neighbor = get_cell(cur_game,row,col+1);//get pointer to right cell
        if(neighbor != NULL && *neighbor == *dummy){//if that cell equal to current cell
          return 1;//user can use move_d
        }
      }
    }
    return 0;// otherwise game is done
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
