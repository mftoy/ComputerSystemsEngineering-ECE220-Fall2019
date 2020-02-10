#include <stdio.h>
#include <math.h>

#define M_PI 3.14159265358979323846

/*
 * main
 *  DESCRIPTION: compute a set of points of a function and print the results
 *  INPUTS: console (int, float float) -- equation related constants
 *  OUTPUTS: console (x, f(x)) -- sequence of values to be printed
 *  RETURN VALUE: 0
 *  SIDE EFFECTS: none
 */
int main()
{
    // Declare variables
  int n,i;
  float omega_1, omega_2, input, output;
    // Prompt user for input 
  printf("Enter the values of n, omega1, omega2 in that order\n");
    // Get user input
  scanf("%d %f %f",&n, &omega_1, &omega_2);
    // Compute function output
    /* for i from 0 to n-1
     *     compute and print xi and f(xi)
     *     use sin() function from math.h
     */
    for(i=0;i<n;i++){
      input = i * M_PI / n;
      output = sin(omega_1*input)+ 0.5 * sin(omega_2*input);
      printf("(%f, %f)\n", input,output);
 }

    return 0;
}

