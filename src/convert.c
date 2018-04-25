#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#include "environment.c"
#include "eval-apply.c"
#include "print.c"
#include "read.c"

void load_file_scm(char* fileName){
  FILE  *fp = fopen(fileName, "r");
  object *exp;

  while (!feof(fp)) {
    exp = read(fp);
    eval(exp, the_global_environment);
    printf("Hi");  
  }
  printf("Nope\n");

  fclose(fp);
}

void include_scm(char *fileName){
  char *ex = ".scm";
  int len = strlen(fileName) + strlen(ex);
  char *f = (char*)malloc(sizeof(char) * len);
  sprintf(f, "%s%s", fileName, ex);
  load_file_scm(f);
  free(f);
}

void include_c48(char *fileName){
  char *ex = ".c48";
  int len = strlen(fileName) + strlen(ex);
  char *f = (char*)malloc(sizeof(char) * len);
  sprintf(f, "%s%s", fileName, ex);
  open_file(f);
  //yyrestart();
  free(f);
}

/** make_if_stmt()
 * Makes a 'if else statement' object
 * Parameters:
 * -cond, the object of the condition
 * -tl, the object of the list of statements of if
 * -el, the object of the list of statements of else
 * Returns:
 * The object of the if statement with else 
 */
object *make_if_stmt(object *cond, object *tl, object *el){
	if(el == the_empty_list)
		el = cons(el, the_empty_list);
	tl = cons(cond, cons(cons(begin_symbol, tl), the_empty_list));
	el = cons(else_symbol, el);
	return cons(cond_symbol, cons(tl, cons(el, the_empty_list)));
}


/** make_if_elseif_stmt()
 * Makes a 'if elseif else.. statement' object
 * Parameters:
 * -cond, the object of the condition
 * -tl, the object of the list of statements of if
 * -stmt, the object another if else statment
 * Returns:
 * The object of the if statement with concatinated if else 
 */
object *make_if_elseif_stmt(object *cond, object *tl, object *stmt){
	tl = cons(cond, cons(cons(begin_symbol, tl), the_empty_list));
	stmt = cdr(stmt);
	return cons(cond_symbol, cons(tl, stmt));
}

/** get_array_index()
 * Makes a 'get array element at index' object
 * Parameters:
 * -name, the name of the array
 * -index, the index of the array
 * Returns:
 * The object of 'a get array element at index '
 */
object *get_array_index(char *name, object *index){
  object *sym = make_symbol("nth");
  object *n = make_symbol(name);
  return cons(sym, cons(index, cons(n, the_empty_list)));
}

/** set_array_index()
 * Makes a 'set array element at index to expression' object
 * Parameters:
 * -name, the name of the array
 * -index, the index of the array
 * -expr, expression to assign
 * Returns:
 * The object of 'a set array element at index to expression'
 */
object *set_array_index(char *name, object *index, object *expr){
  object *i = get_array_index(name, index);
  return cons(define_symbol, cons(i, cons(expr, the_empty_list)));
}

/** make_define_array()
 * Makes a 'define array' object
 * Parameters:
 * -name, the name of the array
 * -list, list of elements to assign
 * Returns:
 * The object of 'define array'
 */
object *make_define_array(char *name, object *list){
  object *n = make_symbol(name);  
  list = cons (quote_symbol, cons(list, the_empty_list));
  list = cons(n, cons(list, the_empty_list));
  return cons(define_symbol, list);
}

/** make_assign()
 * Makes a 'assign expression to varable' object
 * Parameters:
 * -name, the name of the variable
 * -expr, expression to assign
 * Returns:
 * The object of 'assign expression to varable'
 */
object *make_assign(char *name, object *expr){
  object *n = make_symbol(name);
  return cons(define_symbol, cons(n, cons(expr, the_empty_list)));
}

/** make_arith()
 * Makes an 'arithmic expression' object
 * Parameters:
 * -op, operand
 * -first, frist expression
 * -second, second expression
 * Returns:
 * The object of 'arithmic expression'
 */
object *make_arith(char *op, object *first, object *second){
  object *sym = make_symbol(op);
  return cons(sym, cons(first, cons(second, the_empty_list)));
}

/** make_comp()
 * Makes an 'compare expression' object
 * Parameters:
 * -cmp, comparator operand
 * -first, frist expression
 * -second, second expression
 * Returns:
 * The object of 'compare expression'
 */
object *make_comp(char *cmp, object *first, object *second){
  object *sym = make_symbol(cmp);
  return cons(sym, cons(first, cons(second, the_empty_list)));
}

/** make_while_loop()
 * Makes a 'while loop' object
 * Parameters:
 * -cond, condition
 * -expr, list of statements
 * Returns:
 * The object of 'while loop'
 */
object *make_while_loop(object *cond, object *expr){
  object *w = make_symbol("while");
  return cons(w, cons(cond, cons(expr, the_empty_list)));
}

/** make_for_loop()
 * Makes a 'for loop' object
 * Parameters:
 * -assign, varable assign
 * -cond, condition
 * -inc, incrementor
 * -expr, list of statements
 * Returns:
 * The object of 'for loop'
 */
object *make_for_loop(double from, double to, object *expr){
  object *f = make_fixnum(from);
  object *t = make_fixnum(to);
  return cons(make_symbol("for-loop"), cons(f, cons(t, expr)));
}


/** make_increment()
 * Makes a 'variable increment' object
 * Parameters:
 * -name, name of the varaible to increment
 * -op, character of the operand
 * Returns:
 * The object of 'for loop'
 */
object *make_increment(char *name, char *op){
  object *n = make_symbol(name);
  object *num = make_fixnum(1);
  object *inc = make_arith(op, n, num);
  return make_assign(name, inc);
}

/** make_define_func()
 * Makes a 'defining a function' object
 * Parameters:
 * -name, name of the function
 * -params, list of paraters for function
 * -expr, list of statements
 * Returns:
 * The object of 'defining a function'
 */
object *make_define_func(char *name, object *params, object *expr){
  object *n = make_symbol(name);
  object *fun = cons(n, params);
  return cons(define_symbol, cons(fun, expr));
}





