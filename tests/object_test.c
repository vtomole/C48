#include "../src/object.c"

int main(){
  
  object *add = create_object("+", OP);
  object *num1 = create_object("1", NUM);
  object *num2 = create_object("2", NUM);
  object *list = NULL;
  //printf("Created objects\n");
 
  list = cons(num2, list);
  list = cons(num1, list);
  list = cons(add, list);
  
  
  //printf("Cons objects\n");
 
  int count = count_object(list);
  printf("count is %d\n", count);
 
 
  //char *res = get_list(cons3);
  //printf("%s\n", res);

  return 0;
}
