#include <stdio.h>
#include <string.h>
#include "stack.c"
#include "utils.c"

#define DEL " /s/n/r/t"
#define SIZE 100

char *prefix(char *str){
  char *token, *prefix = malloc(sizeof(char) * SIZE);
  stack *op_stack = create_stack();

  while(token = strtok(str, DEL)){
    if(isnumber(token)){
      strcat(prefix, token);
      strcat(prefix, " ");
    }
    else{
      push(op, (void*)token);
    }
  }


  printf("postfix: con_num = %s\n", prefix);

  return prefix;
}
