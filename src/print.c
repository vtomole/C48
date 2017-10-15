//Worked on object.c and object2.c
//Working on printing expressions and traversing the list
//Should work like the parser function but reverse
#include "object.c"

void print_expr(object *);

void print_arith(object *list){
  printf("( %s ", car(list)->value);
  print_expr(car(cdr(list)));
  print_expr(cdr(cdr(list)));
  printf(") ");
}

void print_expr(object *obj){
   if(obj->type == LIST){
    if(car(obj)->type == OP){
      print_arith(obj);
    }
    else{
      printf("%s ", car(obj)->value);
    }
  }
  else if(obj->type != EMPTY){
    printf("%s ", obj->value);
  }
}
