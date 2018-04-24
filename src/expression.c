#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include "expression.h"
#include "read_file.c"


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


