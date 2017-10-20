#include <stdio.h>
#include <string.h>
#include "stack.c"
#include "utils.c"

#define DEL " /s/n/r/t"
#define SIZE 100

char *construct_expr(stack *num, char *op){
  char *a = (char*)pop(num);
  char *b = (char*)pop(num);
  char str[SIZE];

  sprintf(str, "( %s %s %s )", op, b, a);
  printf("constuct_expr: str = %s\n", str);
  return str;
}

char *translate(char *str){
  char *a = "+";
  char *b = "4";
  char *c = "5";

  stack *op = create_stack();
  stack *num = create_stack();

  push(num, (void*)b);
  push(op, (void*)a);
  push(num, (void*)c);

  char *op_pop = (char*)pop(op);
  char *con_num = construct_expr(num, op_pop);
  printf("translate: con_num = %s\n", con_num);

  return con_num;
}
