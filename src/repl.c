#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#include <assert.h>
#include <stddef.h>
#include "environment.c"
#include "read.c"
#include "eval-apply.c"
#include "print.c"
#include "garbage_collector.c"


int main(int argc, char **argv){
  char str[1000];
  object* cons1;
  char* res;
  FILE  *fp, *fp1, *fp2;
  
  init();
  /*fp1 = fopen("hello.c48", "r");
  fgets (str, 10000, fp1);
  res = prefix(str);
  fclose(fp1);
  fp2 = fopen("hello.sexpr", "w");
  fprintf(fp2, "%s", res);
  fclose(fp2);
  fp = fopen("hello.sexpr", "r");*/
  while (1) {
    printf("repl> ");
    print(eval(read(stdin), the_global_environment));
    printf("\n");
  }    
  return 0;
}//end of main>

