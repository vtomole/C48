#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#include <assert.h>
#include "lexer.c"
#include "lexer_tmp.c"
#include "parser.c"
#include "comp_front.c"

//#include "vm.h"
//#include "vm.c"
//#include "read_2.c"
#include "eval-apply.c"
#include "print.c"
#include "compiler.c"


int main(int argc, char **argv){

  char str[10000];
  struct pair *list = NULL;
  struct  token_list *token_list = NULL;
  struct  token_list *token_list2 = NULL;
  struct token_object object1;
  struct object *expr_list;
  struct object *expr;
  struct object *expr2;
  struct object *a;
  struct object *h;
  struct object *number;
  struct object *list2;
  struct object *result_expr = NULL;
  object* code_tree = NULL;
  object* environment = NULL;
  object* environment2 = NULL;
  object *cons1 = NULL;
  object *temp_list = NULL;
  char* operator = "third";
  char* string = "\"A string\"";
  int b = 20, c = 30;
  // hashtable_t *env = ht_create( 65536 );
  char* result = NULL;

  object *add1 = create_primitiveop("+");
  object *num11 = create_number("4");
  object *num22 = create_number("5");

  
  
  temp_list = cons(num22, temp_list);
  temp_list = cons(num11, temp_list);
  temp_list = cons(add1, temp_list);

  // cons1 = parse(lexer_tmp("( 5 )"), result_expr); // THIS WORKS
   cons1 = parse(lexer_tmp("( + 4 5 )"),result_expr); // THIS WORKS
  // cons1 = parse(lexer_tmp("( + 3 4 5 ) )"),result_expr);
  // cons1 = parse(lexer_tmp("( + 3 ( + 4 5 ) )"),result_expr);
  // cons1 = parse(lexer_tmp("( + ( + 4 5 ) 3 )"),result_expr);
  // cons1 = parse(lexer_tmp("( - ( + 4 5 ) ( + 1 2 ) )"),result_expr);
  printf("Should be + is %s\n", car(cons1)->variable);
  printf("Should be 4 is %d\n", car(cdr(cons1))->number);
  printf("Should be 5 is %d\n", car(cdr(cdr(cons1)))->number);
  //  printf("should be 5 is %d\n", car(cdr(cdr(cdr(cons1))))->number);
  //  printf("Should be null %s\n", car(cdr(cdr(cdr(cons1))))->);
  print(eval(parse(lexer_tmp("( + 4 5 )"), expr_list),environment));

  /*
  while (1) {     
    printf("repl>");
    fgets (str, 10000, stdin);
    printf("=>");
    //micro_read(str);
    //print(eval(parse(lexer_tmp(prefix(str)), expr_list),environment));
    object* cons1 = parse(lexer_tmp(str), expr_list);
    //printf("Should be + %s\n", car(cons1)->variable);
    //printf("Should be cons %s\n", car(cdr(cons1))->type);
    //printf("Should be + %s\n", car(car(cdr(cons1)))->variable);
    // printf("Should be 4 %d\n", car(cdr(car(cdr(cons1))))->number);
    print(eval(parse(lexer_tmp(str), expr_list),environment));    
  }
  */
  return 0;
}//end of main>

