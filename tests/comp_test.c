#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#include <assert.h>
#include "../src/comp_front.c"
// #include "../src/lexer.c"
// #include "../src/lexer_tmp.c"
// #include "../src/parser.c"


// //#include "../src/vm.h"
// //#include "../src/vm.c"
// //#include "../src/read_2.c"
// #include "../src/eval-apply.c"
// #include "../src/print.c"
// #include "../src/compiler.c"

void prefix_test(char *expr){
  char *res;
  res = prefix(expr);
  printf("prefix_test: %s\n", res);
  
}


int main(){
  // char *fib = "fun fib(n){\n\tif(n < 2) {\n\t\treturn n;\n\t}\n\telse{\n\t\treturn fib(n - 1) + fib (n - 2);\n\t}\n}\0";
  char *fib = "fun fib(n){\n\tif ( n < 2 ) {\n\t\treturn n;\n\t}\n\telse{\n\t\treturn fib ( n - 1 ) + fib ( n - 2 );\n\t}\n}\0";

  // int a = 1;
  // int b = 2;
  // int *c = &a;
  // printf("c = %d\n", *c);
  // c = &b;
  // printf("c = %d\n", *c);
  
  // stack_test();
  // queue_test();

  // prefix_test("( 7 + 4 - 5 )");     // should be ( - ( + 7 4 ) 5 )
  // prefix_test("( 7 * 4 - 5 )");     // should be ( - ( * 7 4 ) 5 )
  // prefix_test("( 7 + 4 * 5 )");     // should be ( + 7 ( * 4 5 ) )
  // prefix_test("7 / 4 * 5");         // should be ( * ( / 7 4 ) 5 )
  // prefix_test(" x + 5 < x - 3");    // should be ( < ( + x 5) ( - x 3 ) )
  // prefix_test(" x + 3 < 10 && x - 2 > 0"); // should be ( && ( < ( + x 3 ) 10 ) ( > ( - x 2 ) 0 ) )
  // prefix_test("( 7 + ( ( 4 - 5 ) * 3 ) )"); // should be ( + 7 ( * ( - 4 5 ) 3 ) )
  // prefix_test("set x ( 3 + 4 ) x - 5");  // should be ( ( set x ( + 3 4 ) ) ( - x 5 ) ) 
  // prefix_test("if ( x > 10 ) x - 10 else if ( x > 5 ) x - 5 else if ( x == 0 ) x * 100 else NULL"); 
  
  char *comp = compile(fib);
  printf("function: %s\n", comp);

  return 0;
}

