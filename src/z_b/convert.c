#include "convert.h"


object *convert_list(struct symlist *syms){
  if(syms == NULL){ printf("No params\n"); return NULL; }
  object *obj = create_object(syms->sym->name, VAR);
  printf("%s\n", syms->sym->name);
  return cons(obj, convert_list(syms->next));
}

object *convert_func(struct symbol *func){
  object *b, *def, *params, *expr;
  
  def = create_object("define", FUNCEXPR);
  params = convert_list(func->syms);
  expr = convert(func->func);
  
  b = create_object(func->name, FUNC);
  b = cons(b, cons(params, NULL));
  b = cons(b, cons(expr, NULL));
  
  return cons(def, cons(b, NULL));  
}

object *convert(struct ast* a){
  object *car, *cdr, *op, *obj;
  char *val;
  if(!a)
    return NULL;
  switch(a->nodetype){
  case 'K': 
    val = malloc(10);
    sprintf(val, "%d", (int)((struct numval *)a)->number);
    return create_object(val, NUM);
  case 'M':
    val = malloc(10);
    sprintf(val, "%d", (int)-((struct numval *)a)->number);
    return create_object(val, NUM);
  case 'N':
    val = ((struct symref *)a)->s->name;
    return create_object(val, VAR);
  //case '=':
  
  /** Creates Operation Objects**/
  case '+': case '-': case '*':  case '/':  case '%':
    car = convert(a->l);
    cdr = convert(a->r);
    op = create_object((char *)a->nodetype, OP);
    return cons(op, cons(car, cons(cdr, NULL)));

  /** Creates Comparison Object **/
  case '1': 
    car = convert(a->l);
    cdr = convert(a->r);
    op = create_object(">", BCOND);
    return cons(op, cons(car, cons(cdr, NULL)));
  case '2': 
    car = convert(a->l);
    cdr = convert(a->r);
    op = create_object("<", BCOND);
    return cons(op, cons(car, cons(cdr, NULL)));
  case '3': 
    car = convert(a->l);
    cdr = convert(a->r);
    op = create_object("!=", BCOND);
    return cons(op, cons(car, cons(cdr, NULL)));
  case '4': 
    car = convert(a->l);
    cdr = convert(a->r);
    op = create_object("==", BCOND);
    return cons(op, cons(car, cons(cdr, NULL)));
  case '5': 
    car = convert(a->l);
    cdr = convert(a->r);
    op = create_object(">=", BCOND);
    return cons(op, cons(car, cons(cdr, NULL)));
  case '6':
    car = convert(a->l);
    cdr = convert(a->r);
    op = create_object("<=", BCOND);
    return cons(op, cons(car, cons(cdr, NULL)));
    
  }
}

