//Worked on object.c and object2.c
//Working on printing expressions and traversing the list
//Should work like the parser function but reverse
#include "object.c"

void print_expr(object *);

void print_arith(object *list){
  printf("( ");
  printf("%s ", car(list)->value); //Operand
  print_expr(car(cdr(list)));  //First Expr
  print_expr(cdr(cdr(list)));  //Second Expr
  printf(") ");
}

void print_bcond(object *list){
  printf("( ");
  printf("%s ", car(list)->value); // > | < | ==
  print_expr(car(cdr(list)));  //First Expr
  print_expr(cdr(cdr(list)));  //Second Expr
  printf(") ");
}

void print_ccond(object *list){
  if(car(list)->type == BCOND){
    print_bcond(list);
  }
  else if(car(list)->type == NOT){
    printf("( %s ", car(list)->value);
    print_ccond(car(cdr(list)));
    printf(") ");
  }
  else if(car(list)->type == CCOND){
    printf("( ");
    printf("%s ", car(list)->value); // and | or | xor
    print_ccond(car(cdr(list)));
    print_ccond(car(cdr(cdr(list))));
    printf(") ");
  }
}

void print_if(object *list){
  printf("( ");
  //printf("IF ");
  print_ccond(car(list));
  //printf("\nTHEN\n  ");
  print_expr(car(cdr(list)));
  //printf("\nELSE\n  ");
  print_expr(car(cdr(cdr(list))));
  printf(") ");
}

void print_expr(object *obj){
   if(obj->type == LIST){
    if(car(obj)->type == OP){
      print_arith(obj);
    }
    else if(car(obj)->type == BCOND){
      print_bcond(obj);
    }
    else if(car(obj)->type == LIST && 
      (car(car(obj))->type == CCOND || car(car(obj))->type == NOT)){
        print_if(obj);
    }
    else if(car(obj)->type == LIST && car(car(obj))->type == BCOND){
      print_bcond(obj);
    }
    else{
      printf("%s ", car(obj)->value);
    }
  }
  else if(obj->type != EMPTY){
    printf("%s ", obj->value);
  }
}

( ( and ( > x 0 ) ( < x 10 ) )
 ( * x 10 )
 ( + x -1 ) 
)