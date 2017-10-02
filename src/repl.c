#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#include <assert.h>
#include "lexer.c"
#include "parser.c"
#include "vm.h"
#include "vm.c"
#include "hash.c"
#include "../tests/lexer_tests.c"
#include "../tests/tests.c"
//#include "read_2.c"
#include "eval-apply.c"
#include "print.c"
#include "compiler.c"





typedef struct pair{
  void *car;
  enum type type;
  void *cdr;
}pair;


const char *type_array[1];
int command = 0;

 
pair* create1(void* car,enum type type, void* cdr)
{
  //pair* pair = (pair*)malloc(sizeof(pair));
  pair* pair = malloc(sizeof(pair));
  if(pair == NULL)
    {
      printf("Error creating a new node.\n");
      exit(0);
    }
  pair->car = car;
  pair-> type = type;
  pair->cdr = cdr;
 
  return pair;
}



int read_list (pair* list_so_far){

  return 0;
}


int isnumber (char *s){
  if(s == NULL || *s == '\0' || isspace(*s)){
    return 0;
  }
  else{
    char* p;
    strtod(s, &p);
    return *p == '\0';
  }
}



int count (pair* cursor){
  int c = 0;
  while(cursor != NULL){
    c++;
    cursor = cursor->cdr;
  }
  return c;
}

char* car (struct pair *list){
  if(list){
    return list->car;
  }
  return 0;
}

pair* cdr( struct pair *list){
  return list -> cdr;
  
}

void printInt(void *n)
{
  printf("%d\n", *(int *)n);
}


void printChar(void *n)
{
  printf("%s\n", (char *)n);
}

int main(char *argc, char **argv[]){

  char str[20];
  struct pair *list = NULL;
  struct  token_list *token_list = NULL;
  struct  token_list *token_list2 = NULL;
  struct token_object object1;
  struct object *expr;
   struct object *expr2;
  struct object *result_expr = NULL;
  constructor_cell* cell = NULL;
  constructor_cell* code_tree = NULL;
  char* operator = "third";
  char* string = "\"A string\"";
  int b = 20, c = 30;
  // hashtable_t *env = ht_create( 65536 );
  pair* env;
  char* result = NULL;

 

    
  //printf("IDENTIFIER %s\n",read_identifier("Hello how are you doing?", 6));
  //print_token_list(list_lexer("(set position (* 60 (+ initial rate)))"));
  // print_token_list(list_lexer("(+ (+ 2 3) 7)"), result);
  //list_lexer("11 12 45 87 98 45 8476 2635");
  //tests();

  
  //print_token_list(token_list);

  

  //ptr3 = &token_list->val;
  // printf("%s %s \n", ((struct object*)ptr3)->value, ((struct object*)ptr3)->type);
  
  
  object1.type = "identifier";
  object1.value = "+";

  expr = create_number (349);

  //printf("THE NUMBER %d\n", expr->number);

  expr2 = cons(expr,NULL);

  expr = create_number (137);

  expr2 = cons(expr,expr2);
  
  //expr = create_variable("+");

  expr = create_primitiveop("+");

  expr2 = cons(expr,expr2);
  
 
  /*expr2= cdr1(expr2);

  printf("EXPR2 TYPE SECOND TYPE SHOULD BE NUMBER %s \n", car1(expr2)->type);

   expr2= cdr1(expr2);
   printf("EXPR2 TYPE SECOND TYPE SHOULD BE NUMBER %s \n", car1(expr2)->type);*/

    result_expr = eval(expr2, token_list);

    print1(result_expr);

    //printf("RESULT_EXPR TYPE THE FIRST TIME %s \n", result_expr->type);

  //printf("ENUM %d\n",expr.number);
  //expr.symbol.name = "+";
  //expr = cons3 (expr, result_expr);

  //printf("SYMBOL %s\n", expr->symbol.name);
  token_list = prepend_token(object1, token_list);

    
  // printf("%s %s \n", ((struct object*)ptr3)->value, ((struct object*)ptr3)->type);
 
  
  //printf("%s %s \n", token_list2->val.value, token_list2->val.type);

  /* char* a = "hello";
    ptr3 = &a;
    a = *(char **)ptr3;
    printf("SHOULD PRINT HELLO %s\n",a );*/

  object1.type = "num";
  object1.value = "137";
  token_list = prepend_token(object1, token_list);

  object1.type = "num";
  object1.value = "349";
  token_list = prepend_token(object1, token_list);

  object1.type = "right_paren";
  object1.value = ")";
  token_list = prepend_token(object1, token_list);
  
  //print_token_list2(token_list);
  //printf("////////////////////////////////////////////\n");
    //code_tree = parse(token_list, cell);
  //print_token_list2(code_tree->car);

  // printf("TRYING TO PRINT IT %s\n", token_list->val.value);

  //void *ptr1 = &token_list;
   //printf("%s\n", *(char **)ptr1->val.value);
   //token_list2 = (struct token_list*)ptr1;

   // printf("%s\n", token_list2->val.value);

  // print(code_tree);
  //print(eval(code_tree, env));
 

  //push(3);
  //push(5);
  //push(9);
  //push(1);
  //push(12);

  //while(!isEmpty()) {
  //int data = peek();
  //printf("%d\n",data);
  //}
  //  compile();
  
  /* while (1){     
     printf("repl>");
     fgets (str, 20, stdin);
     //printf("=>");
     //micro_read(str);
     printf("=>%s\n", eval(read(str)));
     /*char str[20];
     while (1){     
     printf("repl>");
     fgets (str, 20, stdin);
     printf("=>%s\n", eval(read(str)));
     }


     }*/
  return 0;
}//end of main
