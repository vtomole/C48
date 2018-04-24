#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

#include "environment.c"
#include "eval-apply.c"
#include "print.c"



object *make_if_stmt(object *cond, object *tl, object *el){
  return cons(if_symbol, cons(cond, cons(tl, cons(el, the_empty_list))));
}

object *get_array_index(char *name, object *index){
  object *sym = make_symbol("nth");
  object *n = make_symbol(name);
  return cons(sym, cons(index, cons(n, the_empty_list)));
}

object *set_array_index(char *name, object *index, object *expr){
  object *i = get_array_index(name, index);
  return cons(define_symbol, cons(i, cons(expr, the_empty_list)));
}

object *make_define_array(char *name, object *list){
  object *n = make_symbol(name);  
  list = cons (quote_symbol, cons(list, the_empty_list));
  list = cons(n, cons(list, the_empty_list));
  return cons(define_symbol, list);
}

object *make_assign(char *name, object *expr){
  object *n = make_symbol(name);
  return cons(define_symbol, cons(n, cons(expr, the_empty_list)));
}

object *make_arith(char *op, object *first, object *second){
  object *sym = make_symbol(op);
  return cons(sym, cons(first, cons(second, the_empty_list)));
}


object *make_comp(char *cmp, object *first, object *second){
  object *sym = make_symbol(cmp);
  return cons(sym, cons(first, cons(second, the_empty_list)));
}

object *make_while_loop(object *cond, object *expr){
  object *w = make_symbol("while");
  return cons(w, cons(cond, cons(expr, the_empty_list)));
}

object *make_define_func(char *name, object *params, object *expr){
  object *n = make_symbol(name);
  object *fun = cons(n, params);
  return cons(define_symbol, cons(fun, expr));
}





