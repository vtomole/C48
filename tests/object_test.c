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

  object *list;
  list = init_list(num2);
  list = cons(num1, list);
  list = cons(add, list);
  
  object *list2;
  list2 = init_list(num3);
  printf("1 list2: %s\n", get_list(list2));
  list2 = cons(list, list2);
  //printf("1 list2: %s\n", get_list(list2));
  list2 = cons(sub, list2);
  //printf("1 list2: %s\n", get_list(list2));
  
  

	//char *str = get_list(list2);
  //printf("%s\n", str);
  
  printf("test ended\n");
  
  

  return 0;
}
