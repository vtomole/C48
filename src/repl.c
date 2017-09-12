#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "vm.h"
#include "vm.c"
#include "hash.c"
#include "read.c"
#include "eval-apply.c"
#include "compiler.c"
#include "utilities.c"

//Global variables
char* str;
//Linked list implementation taken from: http://www.zentut.com/c-tutorial/c-linked-list/

const char *type_array[1];
int command = 0;

int main(char *argc, char **argv[]){
  
  char str[20];
  while (1){     
    printf("repl>");
    fgets (str, 20, stdin);
    printf("=>%s\n", eval(read(str)));
  }
  return 0;
  
}//end of main
