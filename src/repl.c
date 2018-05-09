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
#include "typechecker.c"

int main(int argc, char **argv){
  char str[1000];
  object* cons1 = the_empty_environment;
  char* res;
  FILE  *fp, *fp1, *fp2;
  /* USES S EXPRESSIONS */
  init();
  

  fp = fopen(argv[1], "r");
 
  object *exp;

  while (!feof(fp)) {
    //print(exp);
    //print(eval(typecheck(exp, the_global_environment), the_global_environment));
    //print(typecheck(exp, the_global_environment));
    exp = read(fp);
    print(eval(exp, the_global_environment));
    //printf("\n");
    }

  fclose(fp);
  
  return 0;
}//end of main>

