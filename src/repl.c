#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#include <assert.h>
#include "lexer.c"
#include "lexer_tmp.c"
#include "parser.c"

#include "vm.h"
#include "vm.c"
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
  char* operator = "third";
  char* string = "\"A string\"";
  int b = 20, c = 30;
  // hashtable_t *env = ht_create( 65536 );
  char* result = NULL;

  /* token_list = lexer_tmp1("(+ 137 349)");

  h = create_variable("h");
  a = create_variable("a");
  number = create_number("2");

  environment = cons(number, environment);
  environment = cons(a, environment);
  environment = cons (environment, environment2);

  list2 = (car (car(environment)));


  object *add = create_object("+", "string");
  object *num1 = create_object("1", "string");
  object *num2 = create_object("2", "string");
  //printf("Created objects\n");
 
  cons1 = cons(num2, cons1);
  cons1 = cons(num1, cons1);
  cons1 = cons(add, cons1);
  

  //print(cons1);

  // printf("Number of objects %d\n",count_objects(cons1));


  // print_token_list(token_list);
  //token_list = reverse_token_list(token_list);
    
 
 
  //print_token_list(lexer_tmp1("(+ 137 349)"));

  // print_token_list_value(lexer_tmp1("(+ 876 485)"));
  // print_token_list(lexer_tmp("(+ 1 2)"));


  // print_token_list_value(lexer_tmp("(    + 1 2)"));

  //print(eval(a, environment));

  //print(eval(parse(lexer_tmp("\"Hello\""), expr_list),token_list));
  //lexer_tmp("(set position (* 60 (+ initial rate)))");
  // lexer_tmp("\"Hello\"");*/
 
  
   while (1){     
    printf("repl>");
    fgets (str, 10000, stdin);
    //printf("=>");
    //micro_read(str);
    print(eval(parse(lexer_1(str), expr_list),environment));
    
    }
  return 0;
}//end of main>

