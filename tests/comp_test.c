#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#include <assert.h>
#include "../src/lexer.c"
#include "../src/lexer_tmp.c"
#include "../src/parser.c"
#include "../src/comp_front.c"

//#include "../src/vm.h"
//#include "../src/vm.c"
//#include "../src/read_2.c"
#include "../src/eval-apply.c"
#include "../src/print.c"
#include "../src/compiler.c"


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
  
  //stack_test();
   // queue_test();

 prefix_test("( 7 + 4 - 5 )");     // should be ( - ( + 7 4 ) 5 )
  prefix_test("( 7 * 4 - 5 )");     // should be ( - ( * 7 4 ) 5 )
  prefix_test("( 7 + 4 * 5 )");     // should be ( + 7 ( * 4 5 ) )
  prefix_test("7 / 4 * 5");         // should be ( * ( / 7 4 ) 5 )
  prefix_test(" x + 5 < x - 3");    // should be ( < ( + x 5) ( - x 3 ) )
  prefix_test(" x + 3 < 10 && x - 2 > 0"); // should be ( && ( < ( + x 3 ) 10 ) ( > ( - x 2 ) 0 ) )
  prefix_test("( 7 + ( ( 4 - 5 ) * 3 ) )"); // should be ( + 7 ( * ( - 4 5 ) 3 ) )
  prefix_test("set x ( 3 + 4 ) x - 5");  // should be ( ( set x ( + 3 4 ) ) ( - x 5 ) ) 
prefix_test("if ( x > 10 ) x - 10 else if ( x > 5 ) x - 5 else if ( x == 0 ) x * 100 else NULL"); 

  // prefix_test("fun add(x, y) {


   //x + y


   //}"); //=> (define (add x y) (+ x y)) 

   // prefix_test("print(add(42, 13))"); //=> (print (add (42 13)))
   return 0;
}
