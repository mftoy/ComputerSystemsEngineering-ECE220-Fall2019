#include <stdlib.h>
#include <stdio.h>


int is_prime(int number); /* function declaration*/
int print_semiprimes(int a, int b); /*function declaration*/


int main(){
   int a, b;
   printf("Input two numbers: ");
   scanf("%d %d", &a, &b);
   if( a <= 0 || b <= 0 ){
     printf("Inputs should be positive integers\n");
     return 1;
   }

   if( a > b ){
     printf("The first number should be smaller than or equal to the second number\n");
     return 1;
   }

   // TODO: call the print_semiprimes function to print semiprimes in [a,b] (including a and b)
   int out; //initiate a char to store function output
   out = print_semiprimes(a,b); //call print_semiprimes function to print semi prime numbers
   return out; // if there is an semi prime number, function will return 1. if not, it will return 0.
}


/*
 * TODO: implement this function to check the number is prime or not.
For this function I will loop from 2(first prime number) until function argument
If there is any number in the loop that can divide function argument without 
remainder, then argument is not a prime number. It will return 0 and exit 
program.  
 * Input    : a number
 * Return   : 0 if the number is not prime, else 1
 */
int is_prime(int number)
{
  int i; // loop counter
  for(i=2;i<number;i++){ // for loop from 2 to function argument
    if (number%i == 0)//if modular result 0, then number is not prime
      return 0;//return 0 for non-prime numbers
  }
  return 1;//return 1 if no number stopped the for loop
}


/*
 * TODO: implement this function to print all semiprimes in [a,b] (including a, b).
I will create a nested for loop. Outer loop will start from a until b. Inner 
loop will check if any number can divide n without remainder. If so,it will 
check if it is prime number or not. 
prime or not.
 * Input   : a, b (a should be smaller than or equal to b)
 * Return  : 0 if there is no semiprime in [a,b], else 1
 */
int print_semiprimes(int a, int b)
{
  int n,k, prime_check=0; // parameter declarations
  for (n=a;n<=b;n++){ // this loop will count number from a to b
    for (k=2;k<n;k++){ // this loop will check if n is not semiprime by looking numbers smaller than n
      if ((n%k ==0) && (is_prime(k)) && (is_prime(n/k))){//if k can divide n without remainder and both n/k and k are prime numbers, then n is semiprime number
        printf("%d ", n); // print semiprime numbers
        prime_check =1;// if there is semiprime number return 1
        break;//break first loop if n is a semiprime number. Otherwise it will print twice
      }
    }
  }
  printf("\n"); // print new line at the end of program
  return prime_check;//return 1 if there is semiprime number, otherwise 0
}
