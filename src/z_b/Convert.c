#include "expression.h"
#include "eval-apply.h"

object *convert(struct ast* a){
  object obj*;
  if(!ast)
    return NULL;
    
  switch(ast->nodetype){
  case 'K': 
    obj = create_object(((struct numval *)a)->number, NUM);
    break;
  case 'M':
    obj = create_object( -((struct numval *)a)->number, NUM);
    break;
  case 'N':
    obj = create_object(((struct numval *)a)->s->value, VAR);
    break;
  //case '=':
  
  /** Creates Operation Objects**/
  case '+': case '-': case '*':  case '/':  case '%':
    object *car = convert(a->l);
    object *cdr = convert(a->r);
    object *op = create_object(a-nodetype, OP);
    obj = cons(op, cons(car, cons(cdr, NULL)));
    
  /** Creates Comparison Object **/
  case '1': 
    object *car = convert(a->l);
    object *cdr = convert(a->r);
    object *op = create_object(">", OP);
    obj = cons(op, cons(car, cons(cdr, NULL)));
  case '2': 
    object *car = convert(a->l);
    object *cdr = convert(a->r);
    object *op = create_object("<", OP);
    obj = cons(op, cons(car, cons(cdr, NULL)));
  case '3': 
    object *car = convert(a->l);
    object *cdr = convert(a->r);
    object *op = create_object("!=", OP);
    obj = cons(op, cons(car, cons(cdr, NULL)));
  case '4': 
    object *car = convert(a->l);
    object *cdr = convert(a->r);
    object *op = create_object("==", OP);
    obj = cons(op, cons(car, cons(cdr, NULL)));
  case '5': 
    object *car = convert(a->l);
    object *cdr = convert(a->r);
    object *op = create_object(">=", OP);
    obj = cons(op, cons(car, cons(cdr, NULL)));
  case '6':
    object *car = convert(a->l);
    object *cdr = convert(a->r);
    object *op = create_object("<=", OP);
    obj = cons(op, cons(car, cons(cdr, NULL)));
  
  
    
  
  
  
  }

}
