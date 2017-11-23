#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#include <assert.h>
#include "lexer.c"
#include "lexer_tmp.c"
#include "environment.c"
#include "comp_front.c"
#include "read.c"
#include "eval.c"
#include "print.c"



int main(int argc, char **argv){
  char str[1000];
  object* cons1;
  token_list* token_list;
  char* res;
  FILE  *fp, *fp1, *fp2;
  
  initialize_environment();
  fp1 = fopen("hello.c48", "r");
  fgets (str, 10000, fp1);
  res = prefix(str);
  fclose(fp1);
  fp2 = fopen("hello.sexpr", "w");
  fprintf(fp2, "%s", res);
  fclose(fp2);
  fp = fopen("hello.sexpr", "r");
  
  while (1) {
    printf("repl> ");
    print(eval(read(stdin), environment));
    printf("\n");
  }    
  return 0;
}//end of main>

