#include "../src/object.c"

int main(){
  char *str_list;
  object *add = create_object("+", OP);
  object *num1 = create_object("5", NUM);
  object *num2 = create_object("6", NUM);
  
  object *sub = create_object("-", OP);
  object *num3 = create_object("3", NUM);
  
  //printf("add: %s\n", get_list(add));
  //printf("num1: %s\n", get_list(num1));
  //printf("num2: %s\n", get_list(num2));
  
  object *cons1 = cons(num1, num2);
  char *a = cons1->cons_cell.car->value;
  char *b = cons1->cons_cell.cdr->value;
  //printf("car = %s, cdr = %s\n", a, b);
  
  object *x = car(cons1);
  object *y = cdr(cons1);
  a = cons1->cons_cell.car->value;
  b = cons1->cons_cell.cdr->value;
  printf("car = %s, cdr = %s\n", x->value, y->value);
  
 
  
  
  printf("test ended\n");
  
  

  return 0;
}
