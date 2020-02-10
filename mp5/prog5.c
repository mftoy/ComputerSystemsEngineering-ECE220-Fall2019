/*
 *
 * prog5.c - source file adapted from UIUC ECE198KL Spring 2013 Program 4
 *           student code -- GOLD VERSION by Steven S. Lumetta
 */


/*
 * The functions that you must write are defined in the header file.
 * Blank function prototypes with explanatory headers are provided
 * in this file to help you get started.
 */



 /* INTRO PARAGRAPH
 I used to given descriptions of functions to design my algorithm and code itself.
 In the set_seed function, I will declare two integers one for seed and the other one
 for checking sscanf output. If sscanf returns 1, it means it is a valid input. I
 will check this in an if statement. If sscanf returns 1, I will initiate srand and
 set_seed will return 1. Otherwise, it will print error code and return 0.

 In the start_game program, I will call rand function to assign random values to solutions.
 I will modulus-8 to make sure every solution is smaller than 8. Also, modulus will return 0
 and never return 8. Therefore, I will add 1 to correct. Lastly, I will assign these values
 to function arguments using pointers.

 In the make_guess function, I will start with parsing guess_str. If sscanf return any number
 other than 4, it means either not 4 guesses entered or there is a char somewhere in the
 guess_str. I will use a if statement to terminate function with an error code. Also, in
 another if statement, I will check guesses. If there are not in the range from 1 to 8, I will
 terminate the function. Otherwise, I will assign the guesses to pointers. Later, I will
 introduce some variables to identify matched pairs(flags) and count perfect and mismatched
 pairs. With several if statements, I will check how many guesses are perfect matches. If
 there is a  perfect match, I will change their flags to 1 and increment perfect pair count.
 Then, for each guess, I will check if guess flag is 0. If so, I will compare the number with
 solutions and related solution flag. If solution is not paired and solution equals to guess,
 I will increment mismatched count. Lastly, I will print number of mismatches and perfect
 matches with printf.

 */


#include <stdio.h>
#include <stdlib.h>

#include "prog5.h"


/*
 * You will need to keep track of the solution code using file scope
 * variables as well as the guess number.
 */

static int guess_number;
static int solution1;
static int solution2;
static int solution3;
static int solution4;


/*
 * set_seed -- This function sets the seed value for pseudorandom
 * number generation based on the number the user types.
 * The input entered by the user is already stored in the string seed_str by the code in main.c.
 * This function should use the function sscanf to find the integer seed value from the
 * string seed_str, then initialize the random number generator by calling srand with the integer
 * seed value. To be valid, exactly one integer must be entered by the user, anything else is invalid.
 * INPUTS: seed_str -- a string (array of characters) entered by the user, containing the random seed
 * OUTPUTS: none
 * RETURN VALUE: 0 if the given string is invalid (string contains anything
 *               other than a single integer), or 1 if string is valid (contains one integer)
 * SIDE EFFECTS: initializes pseudo-random number generation using the function srand. Prints "set_seed: invalid seed\n"
 *               if string is invalid. Prints nothing if it is valid.
 */
int
set_seed (const char seed_str[])
{
//    Example of how to use sscanf to read a single integer and check for anything other than the integer
//    "int seed" will contain the number typed by the user (if any) and the string "post" will contain anything after the integer
//    The user should enter only an integer, and nothing else, so we will check that only "seed" is read.
//    We declare
//    int seed;
//    char post[2];
//    The sscanf statement below reads the integer into seed.
//    sscanf (seed_str, "%d%1s", &seed, post)
//    If there is no integer, seed will not be set. If something else is read after the integer, it will go into "post".
//    The return value of sscanf indicates the number of items read succesfully.
//    When the user has typed in only an integer, only 1 item should be read sucessfully.
//    Check that the return value is 1 to ensure the user enters only an integer.
//    Feel free to uncomment these statements, modify them, or delete these comments as necessary.
//    You may need to change the return statement below
  int seed, seedFlag=0; //declare variables for seed number and seed control
  char post[2];// declare char variable
  seedFlag = sscanf(seed_str,"%d%1s",&seed,post); //use sscanf to parse seed_str
  if (seedFlag==1){ // if seedFlag is 1, it means only one integer entered without any char
    srand(seed); // set srand to start random numbers
    return 1;// return 1 b/c correct input entered
   }
  else{// if seedFlag is not 1, it means input is not correct
    printf("set_seed: invalid seed\n");//print error code

   }
  return 0;// return 0 because correct input did not terminate the program
}


/*
 * start_game -- This function is called by main.c after set_seed but before the user makes guesses.
 *               This function creates the four solution numbers using the approach
 *               described in the wiki specification (using rand())
 *               The four solution numbers should be stored in the static variables defined above.
 *               The values at the pointers should also be set to the solution numbers.
 *               The guess_number should be initialized to 1 (to indicate the first guess)
 * INPUTS: none
 * OUTPUTS: *one -- the first solution value (between 1 and 8)
 *          *two -- the second solution value (between 1 and 8)
 *          *three -- the third solution value (between 1 and 8)
 *          *four -- the fourth solution value (between 1 and 8)
 * RETURN VALUE: none
 * SIDE EFFECTS: records the solution in the static solution variables for use by make_guess, set guess_number
 */
void
start_game (int* one, int* two, int* three, int* four)
{
    solution1 = rand()%8+1; // assign a random value between 1 and 8 to solution1
    solution2 = rand()%8+1; // assign a random value between 1 and 8 to solution2
    solution3 = rand()%8+1; // assign a random value between 1 and 8 to solution3
    solution4 = rand()%8+1; // assign a random value between 1 and 8 to solution4

    *one = solution1; // set first argument pointer to solution1
    *two = solution2; // set second argument pointer to solution2
    *three = solution3; // set third argument pointer to solution3
    *four = solution4; // set fourth argument pointer to solution4

    guess_number = 1;// initiate guess number

}

/*
 * make_guess -- This function is called by main.c after the user types in a guess.
 *               The guess is stored in the string guess_str.
 *               The function must calculate the number of perfect and misplaced matches
 *               for a guess, given the solution recorded earlier by start_game
 *               The guess must be valid (contain only 4 integers, within the range 1-8). If it is valid
 *               the number of correct and incorrect matches should be printed, using the following format
 *               "With guess %d, you got %d perfect matches and %d misplaced matches.\n"
 *               If valid, the guess_number should be incremented.
 *               If invalid, the error message "make_guess: invalid guess\n" should be printed and 0 returned.
 *               For an invalid guess, the guess_number is not incremented.
 * INPUTS: guess_str -- a string consisting of the guess typed by the user
 * OUTPUTS: the following are only valid if the function returns 1 (A valid guess)
 *          *one -- the first guess value (between 1 and 8)
 *          *two -- the second guess value (between 1 and 8)
 *          *three -- the third guess value (between 1 and 8)
 *          *four -- the fourth color value (between 1 and 8)
 * RETURN VALUE: 1 if the guess string is valid (the guess contains exactly four
 *               numbers between 1 and 8), or 0 if it is invalid
 * SIDE EFFECTS: prints (using printf) the number of matches found and increments guess_number(valid guess)
 *               or an error message (invalid guess)
 *               (NOTE: the output format MUST MATCH EXACTLY, check the wiki writeup)
 */
int
make_guess (const char guess_str[], int* one, int* two,
	    int* three, int* four)
{
//  One thing you will need to read four integers from the string guess_str, using a process
//  similar to set_seed
//  The statement, given char post[2]; and four integers w,x,y,z,
//  sscanf (guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post)
//  will read four integers from guess_str into the integers and read anything else present into post
//  The return value of sscanf indicates the number of items sucessfully read from the string.
//  You should check that exactly four integers were sucessfully read.
//  You should then check if the 4 integers are between 1-8. If so, it is a valid guess
//  Otherwise, it is invalid.
//  Feel free to use this sscanf statement, delete these comments, and modify the return statement as needed

  int w, x , y, z, guessFlag; // declare guess integers and guessFlag
  char post[2]; // declare char variable
  guessFlag=sscanf(guess_str,"%d%d%d%d%1s",&w,&x,&y,&z,post); //parse guess_str with sscanf


  if (guessFlag!=4){ //if guessFlag is not 4, wrong input entered
    printf("make_guess: invalid guess\n");//print error code
    return 0;//exit the program
  }

    if((w>0) && (w<9) && (x>0) && (x<9) && (y>0) && (y<9) && (z>0) && (z<9)){//if arguments in the range of 1 to 8
      *one = w;//assign pointers to first guess
      *two = x;//assign pointers to second guess
      *three = y;//assign pointers to third guess
      *four = z;//assign pointers to fourth guess
    }
    else {// if guesses are in the range of 1 to 8. wrong input
      printf("make_guess: invalid guess\n"); // print error code
      return 0;// exit the program
    }


  int guess1Flag = 0, guess2Flag = 0, guess3Flag = 0, guess4Flag = 0;//declare guess flags
  int sol1Flag = 0, sol2Flag = 0, sol3Flag = 0, sol4Flag = 0;//declare solution flags
  int perfect = 0 , mismatched = 0;// declare counter variables

  if (w == solution1){// if first guess is equal to solution,
    guess1Flag = 1;// set guess flag to 1 to indicate pairs
    sol1Flag =1;//set solution flag to 1 to indicate pairs
    perfect++;//increment perfect couters
  }

  if (x == solution2){// if second guess is equal to solution,
    guess2Flag = 1;// set guess flag to 1 to indicate pairs
    sol2Flag =1;//set solution flag to 1 to indicate pairs
    perfect++;//increment perfect couters
  }

  if (y == solution3){// if first guess is equal to solution,
    guess3Flag = 1;// set guess flag to 1 to indicate pairs
    sol3Flag =1;//set solution flag to 1 to indicate pairs
    perfect++;//increment perfect couters
  }

  if (z == solution4){// if first guess is equal to solution,
    guess4Flag = 1;// set guess flag to 1 to indicate pairs
    sol4Flag =1;//set solution flag to 1 to indicate pairs
    perfect++;//increment perfect couters
  }

  if (guess1Flag != 1){ // if first guess is not paired,
    if(w==solution2 && sol2Flag == 0){//check if solution 2 is not paired and guess is equal to solution
      mismatched++;//if so, increment mismatched
      guess1Flag =1;//guess is paired
      sol2Flag = 1; // solution paired
    }
    else if (w==solution3 && sol3Flag == 0){// if solution 3 equals to guess,
      mismatched++;//increment mismatched
      guess1Flag =1;//gues paired
      sol3Flag = 1; // solution paired
    }
    else if (w==solution4 && sol4Flag == 0){//if solution 4 equals to guess,
      mismatched++;//increment mismatched
      guess1Flag =1;//gues paired
      sol4Flag = 1; // solution paired
    }
  }

  if (guess2Flag != 1){// if second guess is not paired,
    if(x==solution1 && sol1Flag == 0){//check if solution 1 is not paired and guess is equal to solution
      mismatched++;//if so, increment mismatched
      guess2Flag =1;//guess is paired
      sol1Flag = 1; // solution paired
    }
    else if (x==solution3 && sol3Flag == 0){// if solution 3 equals to guess,
      mismatched++;//increment mismatched
      guess2Flag =1;//gues paired
      sol3Flag = 1; // solution paired
    }
    else if (x==solution4 && sol4Flag == 0){//if solution 4 equals to guess,
      mismatched++;//if so, increment mismatched
      guess2Flag =1;//guess is paired
      sol4Flag = 1; // solution paired
    }
  }

  if (guess3Flag != 1){// if third guess is not paired,
    if(y==solution1 && sol1Flag == 0){//check if solution 1 is not paired and guess is equal to solution
      mismatched++;//if so, increment mismatched
      guess3Flag =1;//guess is paired
      sol1Flag = 1; // solution paired
    }
    else if (y==solution2 && sol2Flag == 0){//if solution 2 is not paired and guess is equal to solution
      mismatched++;//if so, increment mismatched
      guess3Flag =1;//guess is paired
      sol2Flag = 1; // solution paired
    }
    else if (y==solution4 && sol4Flag == 0){//if solution 4 is not paired and guess is equal to solution
      mismatched++;//if so, increment mismatched
      guess3Flag =1;//guess is paired
      sol4Flag = 1; // solution paired
    }
  }

  if (guess4Flag != 1){// if fourth guess is not paired,
    if(z==solution1 && sol1Flag == 0){//check if solution 1 is not paired and guess is equal to solution
      mismatched++;//if so, increment mismatched
      guess4Flag =1;//guess is paired
    }
    else if (z==solution2 && sol2Flag == 0){//if solution 2 is not paired and guess is equal to solution
      mismatched++;//if so, increment mismatched
      guess4Flag =1;//guess is paired
    }
    else if (z==solution3 && sol3Flag == 0){// if solution 3 equals to guess,
      mismatched++;//if so, increment mismatched
      guess4Flag =1;//guess is paired
    }
  }

  printf("With guess %d, you got %d perfect matches and %d misplaced matches.\n",guess_number++,perfect,mismatched );// print counters
  return 1;// exit the program
}
