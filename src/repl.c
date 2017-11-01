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

  while (1){     
    printf("repl>");
    fgets (str, 10000, stdin);
    printf("=>");
    //micro_read(str);
    print(eval(parse(lexer_tmp(prefix(str)), expr_list),environment));
    //print(eval(parse(lexer_tmp(str), expr_list),environment));
    
  }
  return 0;
}//end of main>

