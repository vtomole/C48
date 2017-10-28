#include "stdio.h"
#include "../src/comp_front.c"

void stack_test(){
  char str[25];
  char *a = "+";
  char *b = "4";
  char *c = "5";
  sprintf(str, "( %s %s %s )", a, b, c);

  stack *s = create_stack();
  
  push(s, (void*)"working");
  push(s, (void*)"is");
  push(s, (void*)"world");
  push(s, (void*)"hello");
  push(s, (void*)str);
  

  void *rtrn = pop(s);
  while(rtrn != NULL){
    printf("%s\n", (char*)rtrn);
    rtrn = pop(s);
  }

  push(s, (void*)1);
  push(s, (void*)2);
  push(s, (void*)3);
  push(s, (void*)4);
  push(s, (void*)5);

  rtrn = pop(s);
  while(rtrn != NULL){
    printf("%d\n", (int)rtrn);
    rtrn = pop(s);
  }
}

void prefix_test(){
  char *str = "( 7 - 4  + 5 )";
  char *res = postfix(str);
  // char *res = (char*)malloc(sizeof(char) * 200);
  printf("prefix_test: %s\n", res);
}


int main(){
  
  // stack_test();
  prefix_test();

  return 0;
}