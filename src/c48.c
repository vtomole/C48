#include <string.h>
#include <stdlib.h>
#include <stdio.h>

//Global variables
   
//Linked list implementation taken from: http://www.zentut.com/c-tutorial/c-linked-list/
typedef struct node{
  int data;
  struct node* next;
}node;

typedef struct pair{
  void *car;
  void *cdr;
}pair;

int command = 0;
int data;
 
node* head = NULL;
node* tmp = NULL;

 
/*
  return the number of elements in the list
*/
int count(node *head)
{
  node *cursor = head;
  int c = 0;
  while(cursor != NULL)
    {
      c++;
      cursor = cursor->next;
    }
  return c;
}


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

pair* prepend1(pair* head, void *cdr)
{
  pair* new_pair = create1(cdr,head);
  head = new_pair;
  return head;
}
pair *read(char *program){
  pair pair1;
  pair pair2;
  pair pair3;

  char * program_1;
  int i = 0;
  char operator = '+';
  int b = 20;
  int c = 30;
  int count =0;

  pair* head = NULL;

 
  if(program[0] != '('){
    //It's an atom

  }
  //It's it's a list
  else{
    const char s[2] = " ";
    const char s1[2] = "(";
    char *token;
   
    /* get the first token */
    token = strtok(program, s);

 
    /* walk through other tokens */
    while( token != NULL ) 
      {
	//if(token[0] == '('){
	//token = strtok(program, s1);
	// printf("Token should not have parentheses %s\n", token);
	//printf( " %s\n", token );
	if(token[0] == '('){
	  operator = token[1];
	}
	else if (token[1] == ')'){
     
	  c = token[0] - '0';
	}
	else{
	  b = token[0] - '0';

	}
    
	token = strtok(NULL, s);  

      }
  }
   
  pair1.car = &b;
  pair1.cdr = &pair2;
  
  //pair1.cdr = &c;
  pair2.car = &b;
  pair2.cdr = &pair3;
  
  head = prepend1(head, &c);
  head = prepend1(head, &b);
  head = prepend1(head, &operator);

  /* while(head != NULL)
     {
     // head = head->cdr;
     count++;*/   

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
    printf("Your char is not in this variable\n");
  }

 

}

char *eval(pair *head){

  pair *cursor = head;
  int count=0;
  char operator;
  char *answer;
  int first,second;

  operator = *(char*)head->car;
  //printf("In eval  should be +  %c\n",  operator);
  head =  (pair*)head->cdr;

  first = *(int*)head->car;
  //printf("In eval  should be 20  %d\n", first );

  head =  (pair*)head->cdr;

  second = *(int*)head->car;
  //printf("In eval  should be 20  %d\n", second );
   
  
  
  int arguments[2] = {first,second};

  answer = apply(operator, arguments);

  //char *answer = "Hello";
  return answer;
}


int main(char *argc, char **argv[]){

  char str[20];
   while(1){
  printf("repl>");
  fgets (str, 20, stdin);
  printf("=>");
  // printf("%s\n" ,str);
  printf("%s\n", eval(read(str)));

  }
  return 0;
  
}
