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

void postfix_test(){
  char *str = "( 7 - 4  + 5 )";
  char *res = postfix(str); 
  printf("postfix_test: %s\n", res);
}

void prefix_test(char *expr){
  char *res;
  res = prefix(expr);
  printf("prefix_test: %s\n", res);
  
}


int main(){
  
   stack_test();
   queue_test();

   prefix_test("( 7 + 4 - 5 )");     // should be ( - ( + 7 4 ) 5 )
  // prefix_test("( 7 * 4 - 5 )");     // should be ( - ( * 7 4 ) 5 )
  // prefix_test("( 7 + 4 * 5 )");     // should be ( + 7 ( * 4 5 ) )
  // prefix_test("7 / 4 * 5");         // should be ( * ( / 7 4 ) 5 )
  // prefix_test(" x + 5 < x - 3");    // should be ( < ( + x 5) ( - x 3 ) )
  // prefix_test(" x + 3 < 10 && x - 2 > 0"); // should be ( && ( < ( + x 3 ) 10 ) ( > ( - x 2 ) 0 ) )
  // prefix_test("( 7 + ( ( 4 - 5 ) * 3 ) )"); // should be ( + 7 ( - 4 5 ) )
  //prefix_test("if ( x > 10 ) x - 10 else if ( x > 5 ) x - 5 else if ( x == 0 ) x * 100 else NULL"); 
  //prefix_test("set x ( 3 + 4 ) x - 5");  // should be ( ( set x ( + 3 4 ) ) ( - x 5 ) ) 

  return 0;
}
