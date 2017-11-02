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

  // token_list = lexer_tmp1("(+ 137 349)");
  ///INGORE THIS
  h = create_variable("h");
  a = create_variable("a");
  number = create_number("2");

  environment = cons(number, environment);
  environment = cons(a, environment);
  environment = cons (environment, environment2);

  list2 = (car (car(environment)));


  //This is legit
  //(+ (+ 4 5) (+ 1 2))
  object *add = create_primitiveop("+");
  object *num1 = create_number("1");
  object *num2 = create_number("2");
  //printf("Created objects\n");
 
  temp_list = cons(num2, temp_list);
  temp_list = cons(num1, temp_list);
  temp_list = cons(add, temp_list);

  cons1 = cons(temp_list, cons1);

  temp_list = NULL;

  object *add1 = create_primitiveop("+");
  object *num11 = create_number("4");
  object *num22 = create_number("5");

  
  
  temp_list = cons(num22, temp_list);
  temp_list = cons(num11, temp_list);
  temp_list = cons(add1, temp_list);


  cons1 = cons(temp_list, cons1);

  cons1 = cons(add, cons1);
  
  printf("Should be + %s\n", car(cons1)->variable);
  printf("Should be cons %s\n", car(cdr(cons1))->type);
  printf("Should be + %s\n", car(car(cdr(cons1)))->variable);
  printf("Should be 4 %d\n", car(cdr(car(cdr(cons1))))->number);
  printf("Should be 5 %d\n", car(cdr (cdr(car(cdr(cons1)))))->number);
  printf("Should be cons %s\n", car(cdr(cdr (cons1)))->type);
  printf("Should be + %s\n", car(car(cdr(cdr (cons1))))->variable);
  printf("Should be 1 %d\n", car(cdr(car(cdr(cdr (cons1)))))->number);
  printf("Should be 2 %d\n", car(cdr (cdr(car(cdr (cdr(cons1))))))->number);
   
  //print(cons1);

  print(eval(cons1, environment));

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
  // lexer_tmp("\"Hello\"");
 
  

  //string = prefix("( 1 + 2 - 1 )");     // should be ( - ( + 7 4 ) 5 )

  //printf("Prefix %s\n", string);
  //string = "( + ( + 7 4 ) 5 )";
  //print(eval(parse(lexer_tmp(string), expr_list),environment));
  /* while (1){     
    printf("repl>");
    fgets (str, 10000, stdin);
    printf("=>");
    //micro_read(str);
    print(eval(parse(lexer_tmp(prefix(str)), expr_list),environment));
    //print(eval(parse(lexer_tmp(str), expr_list),environment));
    
    }*/
  return 0;
}//end of main>

