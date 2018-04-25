#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include "expression.h"

/** open_file()
 * Opens the code file for the lexer and parser
 * to convert to s-expressions
 * Parameters:
 * -name, the name of the code file 
 * Returns:
 * int, 0 if the file does not exist, 1 if it opened successfully
 */
int open_file(const char *name){
  
  int length = strlen(name) + strlen("./") + 1;
  char *cpy = malloc(sizeof(char) * length);
  strcpy(cpy, "./");
  strcat(cpy, name);
  //printf("trying to open %s\n", cpy);
  FILE *file;
  file = fopen(cpy, "r");
  if(!file){
    fprintf(stderr, "File does not exist.");
    return 0;
  }
  yyset_in(file);
  return 1;
}

/** yyerror()
 * Prints error message and 
 * what line the code has a syntax error
 * Parameters:
 * -s, list of string to print error message 
 */
void yyerror(char *s, ...){
  va_list ap;
  va_start(ap, s);

  fprintf(stderr, "%d: error: ", yylineno);
  vfprintf(stderr, s, ap);
  fprintf(stderr, "\n");
}


int main (int argc, char **argv){
  init(); 
  if(argc > 1){
    open_file(argv[1]);
  }
  else{
    fprintf(stderr, "Please provide file to run\n");
  }
  return yyparse();
}


