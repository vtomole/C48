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
    print(eval(typecheck(read(stdin), the_global_environment), the_global_environment));
    
    }*/
  object *temp_list = the_empty_list;
  object *add =  make_symbol(">");
  object *num1 = make_string("apple");
  object *num2 = make_string("banana");
  temp_list = cons(num2, temp_list);
  temp_list = cons(num1, temp_list);
  temp_list = cons(add, temp_list);
  print(eval(typecheck(temp_list, the_global_environment),the_global_environment));
  //print(temp_list);

  //fp = fopen("array.scm", "r");
  //object *exp;

  

  /*while ((exp = read(fp)) != NULL) {
    //print(exp);
    //print(eval(typecheck(exp, the_global_environment), the_global_environment));
    //print(typecheck(exp, the_global_environment));
    print(eval(exp, the_global_environment));
    }

  fclose(fp);*/

  //object *obj = cons(make_symbol("+"), cons(make_fixnum(4), cons(make_fixnum(5), the_empty_list)));
  //print(obj);

  
  return 0;
}//end of main>

