#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#include "vm.h"
#include "vm.c"
#include "lexer.c"
#include "hash.c"
#include "../tests/lexer_tests.c"
#include "../tests/tests.c"



//Global variables
char* str;
//Linked list implementation taken from: http://www.zentut.com/c-tutorial/c-linked-list/

enum pair_type {Symbol,String, Number, List, Procedure, Lambda};

typedef struct pair{
  void *car;
  enum pair_type type;
  void *cdr;
}pair;

struct env{
  char* variable;
  pair* value;
}env;


const char *type_array[1];
int command = 0;

 
pair* create1(void* car,enum pair_type type, void* cdr)
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



pair* cons(void *car,enum pair_type type, pair* cdr)
{
 
  pair* new_pair = create1(car,type,cdr);
  car = new_pair;
  return car;
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
pair *read(char *program){
  pair pair1;
  pair pair2;
  pair pair3;

  char * program_1;
  int i = 0;
  char operator = '+', char_quit = 'q';
  int b = 20,d;
  int c = 30;
  int count =0;
  char* token, substr;
  
  pair* head = NULL;
   
  const char s[2] = " ";
  const char s1[2] = "(";
    
   
  /* get the first token */
  token = strtok(program, s);

  //printf("%s", token);
  if(strcmp(token, "q\n") == 0){
    //operator = 'q';
    operator = 'q';
    //head = cons(&operator, head);
    //cons(&token ,head);
    //return head;
  }
  /* walk through other tokens */
  while( token != NULL ) 
    {
      //if(token[0] == '('){
      //token = strtok(program, s1);
      // printf("Token should not have parentheses %s\n", token);
      //	printf("Strlen of token %d\n", strlen(token));
      //	printf("Parsing token %c\n", token[strlen (token)- 2]);
      //printf( " dat token %s\n", token );


	
      if(token[0] == '('){
	operator = token[1];
      }
      else if(token[strlen(token)- 2] == ')'){
	//printf("Right paren\n");
	for(i =0; i < strlen(token); i++){
	  // printf("Token at i %c\n", token[i]);
	  if(token[i] == ')'){
	    token[i] = '\0';
	    // printf("I'm in here folks\n");
	    break;
	  }
	  else{
	    token[i] = token[i];
	  }
	    
	}
	//printf("The token after %s\n", token);
	if(isnumber(token)){
	  b = atoi(token);
	  type_array[count] = "integer";
	  count++;
	}
      }
      else{
	// printf( "The token at 0 %c\n", token[0]);
	c = token[0] - '0';
	//printf("that token as an int %d\n", c);

      }

      /*else if (isnumber(token)){
      //printf("A digit is here\n");
      // printf("the token %s\n", token);
      c = atoi(token);
      printf("this is the c %d\n", c);
      }
      else if (token[1] == ')'){
     
      d = token[0] - '0';
      }

      */
    
      token = strtok(NULL, s);  

    }

  //printf("value of operator %c\n", operator);
  //printf("value of b(var 1) %d\n", b);
  // printf("value of c(var 2) %d\n", c);
  
   
  pair1.car = &b;
  pair1.cdr = &pair2;
  
  //pair1.cdr = &c;
  pair2.car = &b;
  pair2.cdr = &pair3;
  
 
  head = cons(&b,Number,head);
  head = cons(&c,Number,head);
  head = cons(&operator,Symbol, head);

  return head;

}

int self_evaluatingp (pair *exp){
  if(exp->type == Number){
    return 0;
  }
  else if (exp->type == String){
    return 0;
  }
  else {
    return 1;
  }
}
char  *apply(char operator, int arguments[]){
  
  int i;
  char* answer = (char*)malloc(8 * sizeof(char));
  switch(operator){
  case '+':
    sprintf(answer, "%d", arguments[0] + arguments[1]);
    return answer;
    break;
  case '-':
    sprintf(answer, "%d", arguments[0] - arguments[1]);
    return answer;
    break;
  case '*':
    sprintf(answer, "%d", arguments[0] * arguments[1]);
    return answer;
    break;
  case '/':
    sprintf(answer, "%d", arguments[0] / arguments[1]);
    return answer;
    break;
  default:
    return "Your char is not in this variable\n";
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

void print(pair *list){
  if(list){
    
    //printf("%s\n", first(list));
    // print_token_list(rest(list));
    // printf("List is here\n");
    switch(list->type){
    case Number:
      //printf("It's a number\n");
      printInt(list->car);
    
      break;
    case Symbol:
      // printf("It's a symbol\n");
      printChar(list->car);
      break;

    case String:
      // printf("It's a string\n");
      printChar(list->car);
      break;
    default:
      break;
    }

  }
  else{
    // printf("List is not here\n");
  }

}


pair* lookup_variable_value(pair* exp, pair *env){

  print(exp);
  //printChar(exp);
  return exp;



}
pair *eval(pair *head, pair *env){

  pair *cursor = head;
  int num_nodes=0;
  char operator;
  char *answer;
  int first,second,i;
 
  //num_nodes = count (head);
 
  if(head == NULL){
    return NULL;
  }
  

  if(self_evaluatingp (head) == 0){
    //printf("It's self-evaluating\n");
    return head;
  }
  if(head->type == Symbol){
    return lookup_variable_value (head, env);
  }
      

  

  /* if(strcmp (head->type, "number") == 0){
     return 

     }*/

  
 
  i=0;
  //if(strcmp(type_array[i], "integer") == 0){

  //  printf("It's an integer\n");
    
  // }

  
    
  switch(head->type){
  case Symbol:
    operator = *(char*)head->car;
    break;
  default:
    break;
  }
    
  if( *(char*)head->car == 'q'){
    exit(0);
  }
  
  // printf("The number of nodes %d\n", num_nodes);
 
  
  //printf("In eval  should be +  %c\n", operator );

  
  head =  (pair*)head->cdr;

  first = *(int*)head->car;
  //printf("In eval  should be 20  %d\n", first );

  head =  (pair*)head->cdr;

  second = *(int*)head->car;
  //printf("In eval  should be 20  %d\n", second );
   
  
  
  int arguments[2] = {first,second};

  answer = apply(operator, arguments);
  
  return head;
}

//Walk the absract syntax tree and compile each expreswsion
void compile(){
  FILE *fp;
  fp = fopen("test.assembly", "w");

  fputs("args 0\n", fp);
  fputs("gvar x\n", fp);
  fputs("gvar y\n", fp);

  fputs("gvar =\n", fp);
  fputs("call 2\n", fp);
  fclose(fp);



}
//Read the assembly file and write in bytes, use fread and fwrite
void assembler(){


}


int main(char *argc, char **argv[]){
  
  char str[20];
  struct pair *list = NULL;
  struct  token_list *token_list = NULL;
  struct object object1;
  pair* code_tree = NULL;
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
  tests();

  
  //print_token_list(token_list);

  char *ptr = malloc(strlen(operator) + 1);
  strcpy(ptr, operator);

  char *ptr_string = malloc(strlen(string) + 1);
  strcpy(ptr_string, string);
  //code_tree = cons(&b,Number,code_tree);
  //code_tree = cons(&c,Number,code_tree);
  code_tree = cons(ptr,Symbol, code_tree);
  //code_tree = cons(ptr_string, String, code_tree);
  

  // print(code_tree);
  //print(eval(code_tree, env));
 

  //push(3);
  //push(5);
  //push(9);
  //push(1);
  //push(12);
  

  //while(!isEmpty()) {
  int data = peek();
  //printf("%d\n",data);
  //}
  //  compile();
  
  /* while (1){     
     printf("repl>");
     fgets (str, 20, stdin);
     //printf("=>");
     //micro_read(str);
     printf("=>%s\n", eval(read(str)));
 

     }*/
  return 0;
  
}//end of main
