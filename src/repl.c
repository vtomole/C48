#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#include <assert.h>
//#include "lexer.c"
#include "lexer_tmp.c"
#include "parser.c"

#include "vm.h"
#include "vm.c"
//#include "read_2.c"
#include "eval-apply.c"
#include "print.c"
#include "compiler.c"


int main(char *argc, char **argv[]){

  char str[20];
  struct pair *list = NULL;
  struct  token_list *token_list = NULL;
  struct  token_list *token_list2 = NULL;
  struct token_object object1;
  struct object *expr_list;
  struct object *expr;
  struct object *expr2;
  struct object *result_expr = NULL;
  object* code_tree = NULL;
  char* operator = "third";
  char* string = "\"A string\"";
  int b = 20, c = 30;
  // hashtable_t *env = ht_create( 65536 );
  char* result = NULL;

  token_list = lexer_tmp1("(+ 137 349)");

  // print_token_list(token_list);
  //token_list = reverse_token_list(token_list);
    
 
 
  //print_token_list(lexer_tmp1("(+ 137 349)"));

  // print_token_list_value(lexer_tmp1("(+ 876 485)"));
  //print_token_list_value(lexer_tmp1("(+ 137 349)"));

  //print(eval(parse(lexer_tmp( "(+ 876 485)"), expr_list),token_list));
  //lexer_tmp("(set position (* 60 (+ initial rate)))");
  //lexer_tmp("(+ 137 349)");
 
  
  while (1){     
    printf("repl>");
    fgets (str, 20, stdin);
    //printf("=>");
    //micro_read(str);
     print(eval(parse(lexer_tmp1(str), expr_list),token_list));
    
     }
    
    return 0;
  }//end of main>

