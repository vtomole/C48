#include "../src/object.c"

int main(){
  
  object *add = create_object("+", OP);
  object *num1 = create_object("1", NUM);
  object *num2 = create_object("2", NUM);
  object *list = create_object(NULL, EMPTY);
  //printf("Created objects\n");
 
  object *cons1 = cons(num1, num2);
  object *cons2 = cons(add, cons1);
  //printf("Cons objects\n");

  
  char *res = get_list(cons2);
  printf("%s\n", res);

  return 0;
}
