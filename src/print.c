#include "print.h"

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
    printf("( %s ", car(list)->value);  // not
    print_ccond(car(cdr(list)));  //First expression
    printf(") ");
  }
  else if(car(list)->type == CCOND){
    printf("( ");
    printf("%s ", car(list)->value); // and | or | xor
    print_ccond(car(cdr(list)));  //First expression
    print_ccond(car(cdr(cdr(list)))); //Second expression
    printf(") ");
  }
}

void print_if(object *list){
  printf("( ");
  print_ccond(car(list)); //Condition
  print_expr(car(cdr(list))); // Then statement
  print_expr(car(cdr(cdr(list)))); //else statment
  printf(") ");
}

void print_varassign(object *list){
  printf("( ");
  printf("%s ", car(list)->value);
  print_expr(car(cdr(list)));
  printf(") ");
}

void print_varexpr(object *list){
  printf("( ");
  printf("%s ", car(list)->value);
  print_varassign(car(cdr(list)));
  print_expr(car(cdr(cdr(list))));
  printf(") ");
}

void print_funcassign(object *list){
  printf("( ( ");
  printf("%s ", car(car(list))->value);
  printf("( ");
  object *obj = car(cdr(car(list)));
  while(obj != NULL){
    printf("%s ", car(obj)->value);
    obj = cdr(obj);
  }
  printf(") ) ");
  print_expr(car(cdr(list)));
  printf(") ");
}

void print_funcexpr(object *list){
  printf("( ");
  printf("%s ", car(list)->value);
  print_funcassign(car(cdr(list)));
  print_expr(car(cdr(cdr(list))));
  printf(") ");
}

void print_funcapply(object *list){
  printf("( ");
  printf("%s ", car(list)->value);
  printf("( %s ( ", car(cdr(list))->value);
  object *temp = car(cdr(cdr(list)));
  while(temp != NULL){
    print_expr(car(temp));
    temp = cdr(temp);
  }
  printf(") ) ) ");
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
    else if(car(obj)->type == VAREXPR){
      print_varexpr(obj);
    }
    else if(car(obj)->type == FUNCEXPR){
      print_funcexpr(obj);
    }
    else if(car(obj)->type == FUNCAPPLY){
      print_funcapply(obj);
    }
    else{
      printf("%s ", car(obj)->value);
    }
  }
  else if(obj->type != EMPTY){
    printf("%s ", obj->value);
  }
}

