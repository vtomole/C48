#include "../src/object.c"

int main(){
  object *add = create_object("+", OP);
  printf("one\n");
  object *num1 = create_object("5", NUM);
  printf("two\n");
  object *num2 = create_object("6", NUM);
  printf("three\n");

  object *list = init_list(num2);
  printf("Init list\n");

  // list = cons(num1, list);
  // list = cons(add, list);

  printf("test ended");
  
  

  return 0;
}