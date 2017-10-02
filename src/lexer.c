//https://llvm.org/docs/tutorial/LangImpl01.html#language
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <limits.h>

/**
 * token_objects is represent the tokens in our token list
 * Parameters:
 * - type, a character representing whether the token is an identifier, operator, or an arguement
 * - value, the original string value of the token. i.e. 5, (, +, etc.
 */
struct token_object{
  char* type;
  char* value;
}token_object;

/**
 *identifier is
 * Parameters:
 * - identifier_token, used to determine the type of identifier 
 * - length, the length of the identifier plus whitespace
 */
struct identifier{
  char* identifier_token;
  int length;
}identifier;

/**
 *token_list is a collection of token_objects used to create a code tree
 * Parameters:
 * - val, the value of the token_object in the list
 * - next, points to the next token_object in the list
 */
typedef struct token_list{
  struct token_object val;
  struct token_list *next;
}token_list;

/**
 * This function advance the pointer to a new location effectivly removing N character from the string
 * Parameters:
 * - the buffer to edit
 * - n the number of characters to chop off
 * Return Value:
 * - charBuffer with N characters chopped off 
 */ 
//Chop off first N characters
char* chopN(char *charBuffer, int n){   
  return charBuffer + n;   
}

/**
 * This function recursivly constructs a the token list in reverse order
 * Parameters:
 * - head the start of the token list to reverse
 * Return Value:
 * - head the start of the reversed token list
 */ 
token_list* reverse_tokenlist(token_list *head){
  token_list *prev    = NULL;
  token_list *current = head;
  token_list *next;
  while (current != NULL){
      next  = current->next;
      current->next = prev;
      prev = current;
      current = next;
  }
  head = prev;
  return head;
}

/**
 * This function does ???
 * Parameters:
 * - val ???
 * - cdr the rest of the tokenlist
 * Return Value:
 * - pair
 * Example call:
 * 
 * expected return val: 
 */ 
token_list* cons1(struct token_object val, struct token_list *cdr){
 
  //pair *pair = (pair*)malloc(sizeof(pair));
  token_list *pair = malloc(sizeof(pair));
  if(pair == NULL){
      printf("Error creating a new node.\n");
      exit(0);
    }
  pair->val = val;
  pair->next = cdr;
 
  return pair;
}

enum Token{
  tok_eof = -1,
  tok_def = -2,
  tok_identifier = -4,
  tok_number = -5,
};

static char* indentifier_string;
static double number_value;

/**
 * This function counts the rest of the elements in a tokenlist
 * Parameters:
 * - cursor the list of tokens to count
 * Return Value:
 * - c the number of tokens in the tokenlist 
 */ 
int count_token_list (token_list* cursor){
  int c = 0;
  while(cursor != NULL){
    c++;
    cursor = cursor->next;
  }
  return c;
}

/**
 * This function returns the value of the first element in a list
 * Parameters:
 * - list the list you want the head of 1
 * Return Value:
 * - the value of the first element in the list
 * Example call:
 * 
 * expected return val: 
 */ 
char* first (struct token_list *list){
  if(list){
    return list->val.value;
  }
  return 0;
}

/**
 *This function returns the type of th current token from the given token_list
 * Parameters:
 * - list, the head of the token_list
 * Return Value:
 * - the value of the head token from list
 * - 0 if list in NULL
 */
char* find_value (struct token_list *list){
  if(list){
    return list->val.value;
  }
  return 0;
}

/**
 *This function determines the type of the current token from the token_list
 * Parameters:
 * - list, the head of the token_list
 * Return Value:
 * - character representing the value of the token from list or 0 if list is NULL
 */
char* find_type (struct token_list *list){
  if(list){
    return list->val.type;
  }
  return 0;
}

/**
 * This function returns the element in the next position in a list
 * Parameters:
 * - list the list you are calling rest on
 * 
 * Return Value:
 * - the next element in the list
 * Example call:
 * 
 * expected return val: 
 */ 
token_list* rest( struct token_list *list){
  return list ->  next;
}

/**
 * This function does ???
 * https://stackoverflow.com/questions/14259540/c-programming-strcat-using-pointer
 * Parameters:
 * - s ???
 * - t ???
 * Return Value:
 * - p ???
 * Example call:
 * 
 * expected return val: 
 */ 
char *scat(char *s,char *t){
    char *p=malloc(strlen(s)+strlen(t)+1);  /* 3: you will have to reserve memory to hold the copy. */
    int ptr =0, temp = 0;                   /* 4 initialise some helpers */

    while(s[temp]!='\0'){                   /* 5. use the temp to "walk" over string 1 */
      p[ptr++] = s[temp++];
    }

    temp=0;

    while(t[temp]!='\0'){                   /* and string two */
      p[ptr++]=t[temp++];
    }
    return p;
}

/**
 * This function recursivly prints the token list
 * Parameters:
 * - list the token to print
 * - result the tokenlist to print from
 * Return Value:
 * - result returns the list of tokens after printing them
 * Example call:
 * 
 * expected return val: 
 */ 
char* print_token_list(struct token_list *list, char *result){
  if(result == NULL){
    result = first(list);
    print_token_list(rest(list), result);
  }else if(list && result !=NULL){ 
    result = scat(result, first(list));
    //printf("The result %s\n", result);
    // printf("%s\n", first(list));
    print_token_list(rest(list), result);
  }else{
  return result;
  }
}
/**
 *This is a testing function to test the ability to read from and utilze our token_list
 *this function is recursive 
 * Parameters:
 * - list, the token_list we are testing over
 * - result, ???
 * Return Value:
 * - result, used to recurse through our list
 */
char* print_token_list_debug(struct token_list *list, char *result){
  if(result == NULL){
    result = ("[");
    result = scat(result,find_type(list));
    result = scat(result,",");
    result = scat(result, find_value(list));
    result = scat(result,"]");
    print_token_list_debug(rest(list), result);
  }else if(list && result !=NULL){
    result = scat(result,"[");
    result = scat(result, find_type(list));
    result = scat(result,",");     
    result = scat(result, find_value(list));
    result = scat(result,"]");
    print_token_list_debug(rest(list), result);
  }else{
    return result;
  }
}

/**
 * This function checks if a given character is whitespace
 * Parameters:
 * - c the character to check
 * Return Value:
 * - 1 if the character is whitespace
 * - 0 otherwise 
 */ 
int iswhitespace (char c){
  if(c == '\n' || c == ' '){
    return 1;
  }else{
    return 0;
  }
}

/**
 * This function appends a given char to the end of the given string
 * Parameters:
 * - s the string to append characters to
 * - c the char to append
 * Return Value:
 * - a string with the given char at the end of the original string
 * Example call:
 * append("hello", '!');
 * expected return val: hello! 
 */ 
char* append(char* s, char c){

  int len = strlen(s);

  printf("Char s %s\n", s);
  printf("Length %c\n", s[1]); 
  s[len-1] = c;
  printf("In append\n");//used for testing?
  s[len+1] = '\0';

  return s;
}

/**
 * This function reads identifiers from the given program
 * Parameters:
 * - program the string containing the code we will run
 * - the index of the identifier to read
 * Return Value:
 * - ???
 * Example call:
 * 
 * expected return val: 
 */ 
struct identifier* read_identifier (char* program, int index){
  struct identifier *identifier1;
  const char s[2] = " ";
  
  program = chopN( program, index );
  
  char *string = strdup(program);
  printf("the string %s\n", string);
  
  identifier1->identifier_token= strtok(string, s);
  printf("In read_identifier\n");
  identifier1->length = strlen(identifier1->identifier_token);

  if(identifier1 == NULL){
    printf("It's null\n");
  }

  return identifier1;
}

/**
 * This function reads numbers from the given program
 * Parameters:
 * - program the string containing the code we will run
 * - the index of the number to read
 * Return Value:
 * - ???
 * Example call:
 * 
 * expected return val: 
 */ 
struct identifier* read_number (char* program, int index){
  struct identifier *identifier1;
  const char s[2] = " ";

  program = chopN( program, index );
  char *string = strdup(program);
  identifier1->identifier_token= strtok(string, s);
  identifier1->length = strlen(identifier1->identifier_token);
  
  return identifier1;
}

////////////////////////Lexer////////////////////////////////

/**
 * This function determines the type used in the creation of a token
 * Parameters:
 * - token the string we are creating the token from
 * Return Value:
 * - the type the token has, identifier, num, or symbol.
 * Example call:
 * token_type('+');
 * expected return val: identifier
 */ 
char* token_type (char* token){
  if (isalpha(token[0])){
    return "symbol";
  }else if (isdigit(token[0])){
    return "num";
  }else{
    return "identifier";
  }
}

/**
 * This function calculates the length of the given string
 * We are computing the length once at this point
 *  because it is a relatively lengthy operation,
 *  and we don't want to have to compute it anew
 *  every time the i < length condition is checked.
 * Parameters:
 * - program the string containing the code we will run
 * Return Value:
 * - a list of tokens created by iterating through program
 * Example call:
 * List_Lexer_tmp("( + 1 1)");
 * expected return val: tokenlist of length 5
 */
int count_chars(char* string, char ch)//is string here replaceable by program?
{
  int count = 0;
  int i;
  int length = strlen(string);

  for (i = 0; i < length; i++){
      if (string[i] == ch){
	count++;
      }
  }
  return count;
}

/**
 * This function creates the preliminary tree
 * The returned tree is generated by iterating through program and creating tokens for each statement
 * Parameters:
 * - program the string containing the code we will run
 * Return Value:
 * - a list of tokens created by iterating through program
 * Example call:
 * List_Lexer("( + 1 1)");
 * expected return val: tokenlist of length 5
 */
//TODO: check for Booleans, Characters, Strings
token_list* list_lexer (char *program){   
  struct token_list  *token_list = NULL;
  struct token_object object1;
  struct identifier  *id;
  static int last_character = ' ';
  const char  s[2] = " ";
  const char *right_par = ")";
  char *token;
  int num_right; 
  int i;
   
  program = strdup(program);
  /* get the first token */
  token = strtok(program, s);
 
  /* walk through other tokens */
  while( token != NULL ){
      num_right = count_chars(token, ')');
      if(token[0] == '('){
	memmove(token, token+1, strlen(token));

	object1.type = "left_paren";
	object1.value = "(";
	token_list = cons1(object1, token_list);
	object1.type = token_type(token);
	object1.value = token;
	token_list = cons1(object1, token_list);	  
      }else if ( num_right>= 1){    
	token[strlen(token)-num_right] = 0;
	 
	object1.type = token_type(token);
	object1.value = token;
	 
	token_list = cons1(object1, token_list);

	object1.type = "right_paren";
	object1.value = ")";
	token_list = cons1(object1, token_list);
	 
	for(i =1; i < num_right; i++){ 
	  object1.type = "right_paren";
	  object1.value = ")";
	  token_list = cons1(object1, token_list);
	}
      }else{
	object1.type = token_type(token);
	object1.value = token;
	token_list = cons1(object1, token_list);
      }
      token = strtok(NULL, s);  
  }
  if(token_list == NULL){
    object1.type = "identifier";
    object1.value = "open_paren";
    token_list = cons1(object1, token_list);
  }
  return  reverse_tokenlist(token_list);
}//end of list_lexer()

/**
 * This is a temp version of list_lexer to test the creation of tokens 
 * This function creates the preliminary tree
 * The returned tree is generated by iterating through program and creating tokens for each statement
 * Parameters:
 * - program the string containing the code we will run
 * Return Value:
 * - a list of tokens created by iterating through program
 * Example call:
 * List_Lexer_tmp("( + 1 1)");
 * expected return val: tokenlist of length 5
 */ 
//TODO: check for Booleans, Characters, Strings
token_list* list_lexer_tmp (char *program){
  static int last_character = ' ';
  int i;
   
  struct  token_list *token_list = NULL;
  struct token_object object1;
  struct identifier  *id;

  object1.type = "identifier";
  object1.value = "open_paren";
  token_list = cons1(object1, token_list);

  //this section is causing seg_faults
  /* object1.type = "operator";
     object1.value = "+";
     token_list = cons1(object1, token_list);
  
     object1.type = "identifier";
     object1.value = "open_paren";
     token_list = cons1(object1, token_list);
  
     object1.type = "operator";
     object1.value = "+";
     token_list = cons1(object1, token_list);
  
     object1.type = "num";
     object1.value = "2";
     token_list = cons1(object1, token_list);
     object1.type = "num";
     object1.value = "3";
     token_list = cons1(object1, token_list);
  
     object1.type = "identifier";
     object1.value = "closed_paren";
     token_list = cons1(object1, token_list);
  
     object1.type = "num";
     object1.value = "7";
     token_list = cons1(object1, token_list);
 
     object1.type = "identifier";
     object1.value = "closed_paren";*/
  //printf("is alpha-test char %c\n",program[0]);
  //printf("is alpha-test %d\n",isalpha(program[0])); 
  for(i =0; i < strlen(program); i++){
    //Check if it's whitespace
    if(iswhitespace(program[i])){
      //???
    }else if (program[i] == '('){      //check if it is an open parentheses
      object1.type = "identifier";
      object1.value = "open_paren";
      token_list = cons1(object1, token_list);
    }else if (program[i] == ')'){      //check if it is an closed parentheses
      object1.type = "identifier";
      object1.value = "closed_paren";
      token_list = cons1(object1, token_list);
    }else if (isalpha(program[i])){    //check if its in the alphabet
      object1.type = "symbol";
      id =  read_identifier(program, i);
      object1.value = id->identifier_token;
      program = chopN( program, id->length ); 
      printf("IDENTIFIER %s\n", object1.value);
      token_list = cons1(object1, token_list);
    }else if(isdigit(program[i])){    //check if its a number
      object1.type = "num";
      id =  read_number(program, i);
      object1.value = id->identifier_token;
      program = chopN( program, id->length ); 
      printf("NUMBER VALUE %s\n", object1.value);
      token_list = cons1(object1, token_list);
    }else{                           //Invalid Syntax
      printf("Illegal syntax\n");
    }
  }

  printf("The number %d\n", count_token_list(token_list));
  //print_token_list(reverse_token_list(token_list));
  
  return token_list;
}//end of list_lexer_tmp

