#include "../src/print.c"

int main(){
  int count;
  char *str;
  
  object *add = create_object("+", OP);
  object *num1 = create_object("1", NUM);
  object *num2 = create_object("2", NUM);

  object *sub = create_object("-",  OP);
  object *num3 = create_object("7", NUM);
  object *list1 = NULL;
  object *list2 = NULL;

  list1 = cons(num2, NULL);
  list1 = cons(num1, list1);
  list1 = cons(add, list1);

  list2 = cons(num3, NULL);
  list2 = cons(list1, list2);
  list2 = cons(sub, list2);


  print_expr(list2);
  printf("\n");


  return 0;
}
