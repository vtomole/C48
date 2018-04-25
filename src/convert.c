#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

#include "environment.c"
#include "eval-apply.c"
#include "print.c"



object *make_if_stmt(object *cond, object *tl, object *el){
  object *exp;
	tl = cons(begin_symbol, tl);
	el = cons(begin_symbol, el);
	exp = cons(if_symbol, cons(cond, cons(tl, cons(el, the_empty_list))));
	//exp = cons(cond_symbol, cons(cond, cons(tl, 
  return exp;
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

object *make_for_loop(object *assign, object *cond, object *inc, object *expr){
	object* temp = expr;
	while(temp->cons_cell.cdr != the_empty_list){  
		temp = cdr(temp);
	}
  temp->cons_cell.cdr = cons(inc, the_empty_list);
  object *w = make_while_loop(cond, expr);
  return cons(assign, w);
}

object *make_increment(char *name, char *op){
  object *n = make_symbol(name);
  object *num = make_fixnum(1);
  object *inc = make_arith(op, n, num);
  return make_assign(name, inc);
}

object *make_define_func(char *name, object *params, object *expr){
  object *n = make_symbol(name);
  object *fun = cons(n, params);
  return cons(define_symbol, cons(fun, expr));
}





