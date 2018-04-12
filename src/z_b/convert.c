#include "convert.h"

//Builds properly
object *convert_symlist(struct symlist *syms){
  if(syms == NULL){ return the_empty_list; }
  object *obj = make_symbol(syms->sym->name);
  return cons(obj, convert_symlist(syms->next));
}


//Builds properly
object *convert_func(struct symbol *func){
  object *b, *fun, *params, *expr;

  params = convert_symlist(func->syms);
  expr = convert_expr(func->func);
  
  fun = cons(make_symbol(func->name), params);
  
  return cons(define_symbol, cons(fun, cons(expr, the_empty_list)));         
}

//Builds properly
object *convert_exprlist(struct ast *a){
  if(!a){
    return the_empty_list;
  }
  else if(a->nodetype == 'L') {
    object *obj = convert_expr(a->l);
    return cons(obj, convert_exprlist(a->r));
  }
  else {
    object *obj = convert_expr(a);
    return cons(obj, the_empty_list);
  }
}

//Builds properly
object *convert_funccall(struct ufncall *f){
  object *name = make_symbol(f->s->name);
  object *list = convert_exprlist(f->l);
  return cons(name, list);
}

//Builds properly
object *convert_builtinfunc(struct fncall *f){
  char *str;
  switch(f->functype){
  case B_sqrt:
     str = "sqrt";
     break;
   case B_exp:
     str = "exp";
     break;
   case B_log:
     str = "log";
     break;
   case B_print:
     str = "print";
     break;
  }
  
  object *name = make_symbol(str);
  object *list = convert_exprlist(f->l);
  return cons(name, list);
}

//Builds properly
object *convert_varexpr(struct ast* a){
 object *var = make_symbol(((struct symasgn*)a)->s->name);
 object *expr = convert_expr(((struct symasgn*)a)->v);
 object *varexpr = cons(var, cons(expr, the_empty_list));
 return cons(let_symbol, cons(varexpr, the_empty_list)); 
}

object *convert_expr(struct ast* a){
  object *car, *cdr, *op, *obj;
  object *cond, *tl, *el;
  char *operation = malloc(sizeof(char));
  char *val;
  int num;
  //printf("node type %c\n", a->nodetype);
  if(!a)
    return the_empty_list;
  
  switch(a->nodetype){
  case 'K': 
    num = (float)((struct numval *)a)->number;
    return make_fixnum(num);
  case 'M':
    num = (float)-((struct numval *)a)->number;
    return make_fixnum(num);
  case 'N':
    val = ((struct symref *)a)->s->name;
    return make_symbol(val);
  case 'C':
    return convert_funccall((struct ufncall*)a);
  case 'F':
    return convert_builtinfunc((struct fncall*)a);
  case '=':
    return convert_varexpr(a);
  case 'L':
    car = convert_expr(a->l);
    cdr = convert_expr(a->r);
    if(cdr->obj_type != PAIR){ cdr = cons(cdr, the_empty_list); }
    return cons(car, cdr);
  /** Creates Operation Objects**/
  case '+': case '-': case '*':  case '/':  case '%':
    car = convert_expr(a->l);
    cdr = convert_expr(a->r);
    sprintf(operation, "%c", a->nodetype);
    op = make_symbol(operation);
    return cons(op, cons(car, cons(cdr, the_empty_list)));

  /** Creates Comparison Object **/
  case '1': 
    car = convert_expr(a->l);
    cdr = convert_expr(a->r);
    op = make_symbol(">");
    return cons(op, cons(car, cons(cdr, the_empty_list)));
  case '2': 
    car = convert_expr(a->l);
    cdr = convert_expr(a->r);
    op = make_symbol("<");
    return cons(op, cons(car, cons(cdr, the_empty_list)));
  case '3': 
    car = convert_expr(a->l);
    cdr = convert_expr(a->r);
    op = make_symbol("!=");
    return cons(op, cons(car, cons(cdr, the_empty_list)));
  case '4': 
    car = convert_expr(a->l);
    cdr = convert_expr(a->r);
    op = make_symbol("=");
    return cons(op, cons(car, cons(cdr, the_empty_list)));
  case '5': 
    car = convert_expr(a->l);
    cdr = convert_expr(a->r);
    op = make_symbol(">=");
    return cons(op, cons(car, cons(cdr, the_empty_list)));
  case '6':
    car = convert_expr(a->l);
    cdr = convert_expr(a->r);
    op = make_symbol("<=");
    return cons(op, cons(car, cons(cdr, the_empty_list)));
  case 'W':
    cond = convert_expr(((struct flow*)a)->cond);
    car = make_symbol("while");
    cdr = convert_expr(((struct flow*)a)->tl);
    return cons(car, cons(cond, cons(cdr, the_empty_list)));
  case 'I':
    cond = convert_expr(((struct flow*)a)->cond);
    tl = convert_expr(((struct flow*)a)->tl);
    el = convert_expr(((struct flow*)a)->el);
    return cons(if_symbol, cons(cond, cons(tl, cons(el, the_empty_list))));
  }
}



