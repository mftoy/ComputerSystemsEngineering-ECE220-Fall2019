/*
I will calculate Pascal's triangle based on the formula given in the MP3 page.
I need 3 integers(1 unsigned long and 2 regular):
i:  holds the number in each row
ii:  used for multiplication in the formula
co_eff: holds value to be printed

After we get input from user (row number), I need to print row+1 numbers
(coefficients) in that row. Therefore, I made a loop that starts from 0 to i=row
Within each row, I need to calculate that specific coefficient. Because I will 
use multiplication over and over, I created another loop to calculate 
the coefficient. In the second loop, I will start from ii=1 till coeffient 
number based on formula. I will set coefficient to 1 initially at each 
coefficient  and multiply formula  on to co_eff. I will be printing coefficient
once multiplication loop is done. At the end, I will print new line to have a
 nicer look on terminal.
 */
#include <stdio.h>
#include <stdlib.h>

int main()
{
  int row;
  printf("Enter a row index: ");
  scanf("%d",&row);

  // Write your code here
  unsigned long co_eff; // declare coefficient variable
  int i, ii;// declare two variables for the loop
  for(i=0; i<= row; i++){ // this loop is to print coefficients
    co_eff =1; // set the coefficient to 1 initially
    for(ii=1;ii<=i;ii++){ // this loop calculate the coefficient 
      co_eff = co_eff * (row +1-ii)/ ii;// formula on MP3 website
    }
    printf("%lu ",co_eff);// print coefficient to the screen
  }
  printf("\n");// print new line to have a nicer look on the terminal
  return 0;
}
