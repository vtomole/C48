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
  /*fp1 = fopen("hello.c48", "r");
  fgets (str, 10000, fp1);
  res = prefix(str);
  fclose(fp1);
  fp2 = fopen("hello.sexpr", "w");
  fprintf(fp2, "%s", res);
  fclose(fp2);
  fp = fopen("hello.sexpr", "r");
  while (1) {
    printf("repl> ");
<<<<<<< HEAD
    //print(eval(typecheck(read(stdin), the_global_environment), the_global_environment));
    //print(eval(read(stdin), the_global_environment));
    print(typecheck(read(stdin), the_global_environment));
=======
    print(eval(typecheck(read(stdin), the_global_environment),the_global_environment));
>>>>>>> 3a3ebf39a414335a5b22463de7dfb4761a3043ab
    printf("\n");
    }*/
  object *temp_list = the_empty_list;

 
  object *add =  make_symbol("-");
 
  object *num1 = make_float(2.9);
  object *num2 = make_float(1.1);

  
 
  temp_list = cons(num2, temp_list);
  
 
 
  temp_list = cons(num1, temp_list);
  
  temp_list = cons(add, temp_list);
 
  //print(temp_list);

 

  fp = fopen(argv[1], "r");
  object *exp;

  

  while ((exp = read(fp)) != NULL) {
    //print(exp);
    //print(eval(typecheck(exp, the_global_environment), the_global_environment));
    //print(typecheck(exp, the_global_environment));
    print(eval(exp, the_global_environment));
    }

  fclose(fp);

  
  return 0;
}//end of main>

