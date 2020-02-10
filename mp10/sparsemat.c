#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>

/*  INTRO PARAGRAPH
  In this file, I implemented 7 functions to make matrix addition and
  multiplication operations as well as reading a matrix entries from a file and
  writing matrix results to a file. Function algorithms are as follows:

  load_tuples:  In this function, I opened the file in the argument to read matrix entries.
                First of all, memory allocated for matrix struct. Matrix size entries are
                scanned from the file and assigned to matrix struct. Then, each line in the
                file until the end of file and set_tuples function assigned values to
                corresponding nodes in the file. Then, function closes the file and return a
                pointer to matrix struct.

  gv_tuples:    In this function, I need to return value at specific row, col pairs in the
                matrix. I start with defining a pointer to current node. A while loop goes
                through all nodes in the matrix. If row and col matches with the function
                arguments, function return the value at the node. Otherwise, functions
                return 0 as zeros are not stored.

  set_tuples:   In this function we will add nodes to current linked list. We have 3 pointers:
                previous node, current node and next node. If matrix head is NULL, then allocate
                memory for new item and store the node at the head.  If new node needs to be
                placed at the first item according row major order (meaning head needs to change),
                I place the node here and update head pointer. Otherwise, I go through each node
                in the list using a while loop. If row variable at the current node is bigger
                than the argument variables, I check for col variable. If correct location for
                both row and col found function creates the node there if value is not zero. If
                there is already such an item, it changes value or deletes the node if zero. At
                the end, if function has not terminated yet, I add new node to tail.

  save_tuples:  I start with creating a file pointer and opening file with the name in the argument
                to write entries. First of all, I print matrix size in the file. Later, all nodes in
                the struct printed in the file as a new line. Finally, file closed and program exits.

  add_tuples:   In this function, I add two matrixes with the same size. If matrix sizes do not match,
                function returns NULL. Then, I allocated memory for new matrix and assigned correct
                parameters. Then, I go through every entry in the matrix A and save them in matrix C.
                Then, I go through every entry in matrix B and summ them up with current values in the
                matrix C. save_tuples function creates required nodes. Function returns a pointer to
                result matrix.

  mult_tuples:  In this matrix, I will perform matrix multiplication. I check the matrix sizes. If sizes
                do not match, function returns NULL. Then, function allocate memory for new matrix with
                correct matrix size. Then, I go over all entries in the matrix A and find relevant entries
                in matrix B and multiplfy them. Addition is added to current elements in the matrix.

  destroy_tuples: This function frees the allocated memory. I declare a pointer to hold current and previous
                  node. Going over all entries, function deletes previous pointers memory.
*/


sp_tuples * load_tuples(char* input_file)
{

  sp_tuples * mat_t = (sp_tuples *)malloc(sizeof(sp_tuples));//get pointer to the matrix

  FILE * file;//declare file pointer

  file = fopen(input_file,"r");//open file for reading

  int m, n;//declare integers
  fscanf(file, "%d %d\n", &m, &n);//get the matrix dimension

  mat_t->m = m;//assign matrix dimensions to tuple matrix
  mat_t->n = n;//assign matrix dimensions to tuple matrix
  mat_t->tuples_head = NULL;//equate current node pointer to head of the linked list
  mat_t -> nz = 0 ;// initialize nonzero elements

  int row, col;//declare col and row variables
  double value;//declare value variable

  //get elements from file
  while(1) {//read the lines in the file until the end of it
    fscanf(file, "%d %d %lf\n", &row, &col, &value);//read the line
    set_tuples(mat_t,row,col,value);//add the values as a node to the matrix
    if(feof(file)) {//if end of the file
      break;//stop reading
    }
  }

  fclose(file);//close file for reading
  return mat_t;//return pointer to the matrix
}



double gv_tuples(sp_tuples * mat_t,int row,int col)
{
  sp_tuples_node* curr = mat_t -> tuples_head;//define a pointer to the head

  while(curr){//while current node is NOT Null
    if ((curr-> row == row) && (curr->col == col)){//if row and col of given node are equal to parameters
      return curr->value;//return the value on that node
    }
    else {//otherwise
      curr = curr->next;//look at the next node
    }

  }
  return 0;//all nodes are checked, no ocuurance and return zero
}



void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{
  sp_tuples_node* curr = NULL;//get a pointer to a node
  sp_tuples_node* prev = NULL;//declare a previous pointer
  sp_tuples_node* next = NULL;//declare a next pointer

  if((mat_t->tuples_head == NULL)){//first non-zero entry read
    if(value!=0){//if value is not zero
    curr = malloc(sizeof(sp_tuples_node));//allocate memory
    curr-> row = row;//assign row variables
    curr-> col = col;//fill out the node
    curr-> value = value;//fill out the node info
    curr->next = NULL;//fill out node info
    mat_t->nz++;//increase non=zero counter
    mat_t->tuples_head = curr;//update head
  }
    return;//exit the loop
  }

  curr = mat_t->tuples_head;//get a pointer to first node

  if((curr == mat_t->tuples_head) && (curr->row > row)){//if new node is between head and next node
    if(value != 0){//if value is not zero
    sp_tuples_node* new = malloc(sizeof(sp_tuples_node));//allocated memory for new node
    new-> row = row;//assign row variables
    new-> col = col;//fill out the node
    new-> value = value;//fill out the node info
    new->next = curr;//fill out node info
    mat_t->tuples_head = new;//update node head
    mat_t->nz++;//increase non=zero counter
  }
    return;//exit the loop
  }

  while(curr != NULL){//go over all nodes

    if((curr->row > row)){//row number smaller than current node, add new node to prev
      if(value != 0){//if value is not zero
      sp_tuples_node* new = malloc(sizeof(sp_tuples_node));//new node memory allocated
      new-> row = row;//assign row variables
      new-> col = col;//fill out the node
      new-> value = value;//fill out the node info
      new->next = curr;//fill out node info
      prev->next = new;//update previous node's next pointer
      mat_t->nz++;//increase non=zero counter
    }
      return;//exit the loop
    }
    else if(curr->row == row){
      if (curr->col > col){
        if(value!=0){//if value is not zero
        sp_tuples_node* new = malloc(sizeof(sp_tuples_node));//new node memory allocated
        new-> row = row;//assign row variables
        new-> col = col;//fill out the node
        new-> value = value;//fill out the node info
        new->next = curr;//fill out node info
        prev->next = new;//update previous node's next pointer
        mat_t->nz++;//increase non=zero counter
      }
        return;//exit the loop
      }
      else if(curr->col == col){//if there is the same row and col number
        if(value != 0){//if new value is not zero
          curr->value = value;//update current nodes value
          return;//exit the loop
        }
        else{//if new value is zero then delete that node
          next = curr->next;//get a pointer to next item
          prev->next = next;//update prev nodes next pointer
          free(curr);//free the allocated memory
          mat_t->nz--;//1 nonzero item deleted
          return;//exit the loop
        }
      }
      else if(curr->col < col){//node has not reached yet
        prev = curr;//update prev node
        curr = curr->next;//update current node
      }
    }
    else if (curr->row < row){//node has not reached yet
      prev = curr;//update prev node
      curr = curr->next;//update current node
    }
  }
  //if program did not stop until this point then add the node to the tail
  if(value!=0){//if value is not zero
  sp_tuples_node* new = malloc(sizeof(sp_tuples_node));//allocate memory for new node
  new-> row = row;//assign row variables
  new-> col = col;//fill out the node
  new-> value = value;//fill out the node info
  new->next = curr;//fill out node info
  prev->next = new;
  mat_t->nz++;//increase non=zero counter
}
  return;//exit the loop

}



void save_tuples(char * file_name, sp_tuples * mat_t)
{
  FILE *file;//get a file pointer
  file = fopen(file_name,"w");//create a file with given name to write

  int m = mat_t->m;//get matrix size
  int n = mat_t->n;//get matrix size

  fprintf(file, "%d %d\n",m,n);//write matrix size to the file

  sp_tuples_node* curr = mat_t->tuples_head;//get the node head

  while(curr!= NULL){//go over all nodes
    int row = curr->row;//get their row
    int col = curr->col;//get their col
    double value = curr->value;//get their value

    fprintf(file, "%d %d %lf\n",row,col,value);//print the node

    curr = curr->next;//go to next node
  }


  fclose(file);//close the file
	return;//exit the program
}



sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB){
  if((matA->m != matB->m)||(matA->n != matB->n)){//check matrix sizes
	   return NULL;//return error
   }

   sp_tuples * matC = (sp_tuples *)malloc(sizeof(sp_tuples));//allocate memory for new matrix

   matC -> m = matA->m;//initiliaze new matrix
   matC->n = matA->n;//initiliaze new matrix
   matC->nz = 0;// initialize new matrix
   matC->tuples_head = NULL;//initialize new matrix

   sp_tuples_node *entry = matA->tuples_head;//pointer to matrix A head

   while(entry != NULL){//go over every entries in the matrix A
     int row = entry->row;// get row parameter
     int col = entry->col;//get col variable
     double value = entry -> value;//get the value
     set_tuples( matC, row,col, value);//create tuple in the matrix C
     entry = entry->next;//go to next node
   }

   entry = matB -> tuples_head;//get a pointer to matrix B head

   while(entry != NULL){//go over every entri in the matrix B
     int row = entry->row;//get row parameter
     int col = entry->col;//get col parameter
     double value = entry -> value;//get value parameter
     value = value + gv_tuples( matC, row, col);//addcurrent value in matrix C to value
     set_tuples( matC, row,col, value);//save the node in matrix C
     entry = entry->next;// go to next entry
   }
   return matC;//return matrix C pointer
}



sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB){

  if((matA->n) != (matB-> m)){//check matrix sizes
    return NULL;//return error
  }

  sp_tuples * matC = (sp_tuples *)malloc(sizeof(sp_tuples));//allocate memory for result matrix

  matC->m = matA->m;//initiliaze result matrix variables
  matC->n = matB->n;//initiliaze result matrix variables
  matC->nz = 0;//initiliaze result matrix variables
  matC->tuples_head = NULL;//initiliaze result matrix variables

  sp_tuples_node *entryA = matA->tuples_head;//get a pointer to matrix A head

  while(entryA != NULL){//go over every node in matrix A

    sp_tuples_node *entryB = matB->tuples_head;//get a pointer to matrix B

    while((entryB != NULL)&&(entryB->row != entryA->col)){//find the entries matching row parameter in matrix B
        entryB = entryB ->next;//go to next entry
    }

    while((entryB != NULL) && (entryB->row <= entryA->col)){//for variables matching row variable

      int row = entryA->row;//get the row variable
      int col = entryB->col;//get the col variable
      double value = gv_tuples( matC, row, col);//get the current value in the matrix C
      value = value + (entryA->value)*(entryB->value);//add multiplication to current value
      set_tuples( matC, row,col, value);//assign it to correct node
      entryB = entryB->next;// go to next node in the matrix B
    }
    entryA = entryA -> next;//go to next node in the matrix A
    }
  return matC;//return pointer to result matrix
}



void destroy_tuples(sp_tuples * mat_t){
  sp_tuples_node* curr = NULL;//get a pointer to a node
  sp_tuples_node* prev = NULL;//declare a previous pointer

  curr = mat_t->tuples_head;//get tuple head
  free(mat_t);//free memory for matrix

  while(curr){//for every node
    prev = curr;//update prev pointer
    curr = curr->next;//update current node
    free(prev);//deallocate memory for the current node
  }
  return;//close the function
}
