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
  object* cons1 = the_empty_environment;
  char* res;
  FILE  *fp, *fp1, *fp2;
  /* USES S EXPRESSIONS */
  init();
  /*fp1 = fopen("hello.c48", "r");
  fgets (str, 10000, fp1);
  res = prefix(str);
  fclose(fp1);
  fp2 = fopen("hello.sexpr", "w");
  fprintf(fp2, "%s", res);
  fclose(fp2);
  fp = fopen("hello.sexpr", "r");*/
  /*while (1) {
    printf("repl> ");
    print(typecheck_eval(read(stdin), the_global_environment));
    printf("\n");
    }*/
  object *temp_list = the_empty_list;

 
  object *add =  make_symbol("+");
 
  object *num1 = make_float(2.9);
  object *num2 = make_float(1.1);

  
 
  temp_list = cons(num2, temp_list);
  
 
 
  temp_list = cons(num1, temp_list);
  
  temp_list = cons(add, temp_list);
 
  //print(temp_list);
  

  print(eval(typecheck(temp_list, the_global_environment), the_global_environment));

  
  return 0;
}//end of main>

