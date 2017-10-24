#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.c"

// #define SYM 0
// #define NUM 1
// #define IDEN 2

//enum Token{
//  tok_eof = -1,
//  tok_def = -2,
//  tok_identifier = -4,
//  tok_number = -5,
//};

/**
 * token_objects is represent the tokens in our token list
 * Parameters:
 * - type, a character representing whether the token is an identifier, operator, or an arguement
 * - value, the original string value of the token. i.e. 5, (, +, etc.
 */
typedef struct token_object{
  char* type;
  char* value;
}token_object;

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

token_object* create_token_object(char *type, char *value){
  token_object *tok_obj = malloc(sizeof(tok_obj));
  tok_obj->type = type;
  tok_obj->value = value;
  return tok_obj;
}

token_list* create_token_list(token_object tok_obj){
  token_list *tok_list = malloc(sizeof(tok_list));
  tok_list->val = tok_obj;
  tok_list->next = NULL;
  return tok_list;
}

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
    return "primitive";
  }
}

/**
 * This function recursivly constructs a the token list in reverse order
 * Parameters:
 * - head the start of the token list to reverse
 * Return Value:
 * - head the start of the reversed token list
 */ 
token_list* reverse_token_list(token_list *head){
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
token_list* prepend_token(struct token_object val, struct token_list *cdr){
  
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
char* first_value (struct token_list *list){
  if(list){
    return list->val.value;
  }
  return 0;
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
    return list->val.type;
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
  return list -> next;
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
void print_token_list(struct token_list *list){
  if(list){
    printf("%s\n", first(list));
    print_token_list(rest(list));
  }
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
void print_token_list_value(struct token_list *list){
  if(list){
    printf("%s\n", first_value(list));
    print_token_list_value(rest(list));
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

