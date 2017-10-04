#include "token.c"

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

static char* indentifier_string;
static double number_value;



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
