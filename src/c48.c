#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "vm.h"
#include "vm.c"
#include "lexer.c"



//Global variables
   
//Linked list implementation taken from: http://www.zentut.com/c-tutorial/c-linked-list/

typedef struct pair{
  void *car;
  void *cdr;
}pair;

const char *type_array[1];
int command = 0;

 
pair* create1(void* car,void* cdr)
{
  //pair* pair = (pair*)malloc(sizeof(pair));
  pair* pair = malloc(sizeof(pair));
  if(pair == NULL)
    {
      printf("Error creating a new node.\n");
      exit(0);
    }
  pair->car = car;
  pair->cdr = cdr;
 
  return pair;
}

pair* cons(void *car, pair* cdr)
{
 
  pair* new_pair = create1(car,cdr);
  car = new_pair;
  return car;
}





int read_list (pair* list_so_far){

  return 0;
}

char *micro_read (char* program){
  
  char* next_token = read_token(program);
  
  pair* list_so_far;
 
  if(strcmp(next_token,"left-paren") == 0){
    //printf("Left parentheses\n");

    read_list(list_so_far);

  }
  else{
    return next_token;
  }


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
  char operator = '+';
  int b = 20,d;
  int c = 30;
  int count =0;
  char* token, substr;
  
  pair* head = NULL;
   
  const char s[2] = " ";
  const char s1[2] = "(";
    
   
  /* get the first token */
  token = strtok(program, s);
  
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
  //printf("value of b %d\n", b);
  //printf("value of c %d\n", c);
  
   
  pair1.car = &b;
  pair1.cdr = &pair2;
  
  //pair1.cdr = &c;
  pair2.car = &b;
  pair2.cdr = &pair3;
  
 
  head = cons(&b,head);
  head = cons(&c,head);
  head = cons(&operator, head);

   
  

  return head;

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

char *eval(pair *head){

  pair *cursor = head;
  int num_nodes=0;
  char operator;
  char *answer;
  int first,second,i;
  //num_nodes = count (head);
  
  i=0;
  //if(strcmp(type_array[i], "integer") == 0){

  //  printf("It's an integer\n");
    
  // }
    
     

  
  // printf("The number of nodes %d\n", num_nodes);
  
  operator = *(char*)head->car;
  //printf("In eval  should be +  %c\n", operator );
  head =  (pair*)head->cdr;

  first = *(int*)head->car;
  //printf("In eval  should be 20  %d\n", first );

  head =  (pair*)head->cdr;

  second = *(int*)head->car;
  //printf("In eval  should be 20  %d\n", second );
   
  
  
  int arguments[2] = {first,second};

  answer = apply(operator, arguments);
  
  return answer;
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
  push(3);
  push(5);
  push(9);
  push(1);
  push(12);
  

  //while(!isEmpty()) {
  int data = peek();
  //printf("%d\n",data);
  //}
  //  compile();
  
  while(1){     
  printf("repl>");
  fgets (str, 20, stdin);
  printf("=>");
  //micro_read(str);
  printf("%s\n", eval(read(str)));

  }
  return 0;
  
}//end of main
