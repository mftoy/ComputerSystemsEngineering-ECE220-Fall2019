#include "sudoku.h"

/*   INTRO PARAGRAPH
     In this file, I've filled out the given functions in the rubric. I will
     explain my algorithm for each function in the following paragraphs.

     is_val_in_row: I introduced a column variable j and created a loop to check
     each number in the given row. If any number in the row is equal to argument
     value, I terminate the program and retun 1. Otherwise, it returns 0. I chose
     this method over other search algorithms because our matrix is not in
     ascending/descending order.

     is_val_in_col: Similar to function explanation above, I introduce a row
     variable i. I look at every number in that column and return 1 if argument
     value is equal to any number, and 0 otherwise.

     is_val_in_3x3_zone: In this function, I declare two new variables: box_row
     and box_col. These two represents indexes for 9 3x3 boxes. I divided original
     row and column variable by 3 to obtain box indexes. After I find box indexes,
     I created 2 nested for loops to check each element in the box. If any number
     is equal to given argument value, function return 1. And 0 otherwise.

     is_val_valid: For this function, I declared three flag variables. Each variable
     is assigned to column, row and 3x3 box checker functions. If any one of these
    flags is 1 then it means, given value is existed in either row, col or 3x3 box.
    In this case, function returns 0. Otherwise, it returns 1.

    solve_sudoku: I implemented backtracking algorithm given in the rubric. I
    started with declaring two variables for row and column number. Using a two
    nested loop, I looked at every number in the sudoku. If loop finds a number
    that is equal to 0, then I set the flag to 0 and stop the loops. Next if statement
    checks if flag is stil 1. If so it return 1. Otherwise, I know the non filled
    location from previous loops. By declaring a number variable and looping it
    from 1 to 9, I check if any of these numbers is valid according to is_val_valid
    function. If so, I assign that number to that location in sudoku. Next, I
    implemented backtracking algorithm with an if statement. In the if statement
    we call solve_sudoku function and it continues to solve rest of the sudoku
    assuming current number is valid at that location. If sudoku is unsolvable with the
    given number, program will exit if statement and assign that location 0 again.
    Loop will continue trying next numbers. However, if sudoku is solvable with
    that number, if statement will terminate the program and return 1. As a result,
    we will be able to solve the sudoku.
 */



//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------

// You are free to declare any private functions if needed.

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);

  // BEG TODO
  int j; // declare a column variable
  for(j=0;j<9;j++){ // loop column variable from 0 to 8
    if(sudoku[i][j] == val){// if any number in that row is equal to argument value
      return 1;//return 1
    }
  }
  return 0;// return 0 otherwise
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);

  // BEG TODO
  int i;//declare a row variable
  for(i=0;i<9;i++){//loop row variable from 0 to 8
    if(sudoku[i][j] == val){// if any number in that column is equalt argument value
      return 1;//return 1
    }
  }
  return 0;//return 0 otherwise
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9);

  // BEG TODO
  int box_row, box_col, row, col;//declare 3x3 box and loop variables
  box_row = i / 3;//find box row index
  box_col = j / 3;// find box col index
  for(row= box_row*3;row < box_row*3+3;row++){//loop every row in the 3x3 box
    for(col = box_col*3;col < box_col*3+3;col++){// loop every column in the 3x3 box
      if(sudoku[row][col] == val){// if any number in the box is equalto given argument value
        return 1;// return 1
      }
    }
  }

  return 0;// return 0 otherwise
  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);

  // BEG TODO

  if(is_val_in_row(val, i, sudoku)|| is_val_in_col(val, j, sudoku)|| is_val_in_3x3_zone(val, i, j, sudoku)){
    //if any of the functions above returns 1
    return 0;//given value is not valid
  }
  return 1;//otherwise it is valid
  // END TODO
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {

  // BEG TODO.
  int i, j;//declare row and column loop variables
  int flag = 1;//declare flag variable

  for(i=0;i<9;i++){//look at every number in the rows
    for(j=0;j<9;j++){//look at every number in the columns
      if(sudoku[i][j]==0){//if suduko is empty
      flag = 0;//set flag to 0
      break;//stop the column loop
      }
    }
    if(flag == 0){//there is a non filled location
      break;//stop the row variables
    }
  }

  if(flag == 1){//if sudoku is all filled
    return 1;// return 1
  }
  else{ //otherwise find a number to fill that location
  int num;//declare loop variable
  for(num = 1;num<=9;num++){//range number from 1 to 9
    if(is_val_valid(num, i, j,sudoku)){//if number in the loop is valid
      sudoku[i][j] = num;//assign that number to that location
      if(solve_sudoku(sudoku)){//check if rest of the sudoku solvable
        return 1;//if it can be solvable, exit program 1
      }
      //if we come to this line, it means rest of the sudoku is not solvable
      sudoku[i][j] = 0; // then set that location to zero again and try other numbers in the loop
    }
  }
}
  return 0;//if function is not solvable with any number for that location terminate function and return 0
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
