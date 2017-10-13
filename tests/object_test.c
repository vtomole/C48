#include "../src/object.c"

int main(){
  
  object *add = create_object("+", OP);
  object *num1 = create_object("1", NUM);
  object *num2 = create_object("2", NUM);
  object *list = NULL;
  //printf("Created objects\n");
 
  object *cons1 = cons(num2, list);
  object *cons2 = cons(num1, cons1);
  object *cons3 = cons(add, cons2);
  
  //printf("Cons objects\n");
 
  int count = count_object(cons3);
  printf("count is %d\n", count);
 
 
  //char *res = get_list(cons3);
  //printf("%s\n", res);

  return 0;
}
