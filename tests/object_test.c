#include "../src/print.c"

void test_one(){
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
}

void test_two(){
  object *a, *b, *c;
  a = create_object("+", OP);
  b = create_object("x", VAR);
  c = create_object("-1", NUM);
  object *add_list = cons(a, cons(b, cons(c, NULL)));
  
  a = create_object("*", OP);
  b = create_object("x", VAR);
  c = create_object("10", NUM);
  object *mult_list = cons(a, cons(b, cons(c, NULL)));

  a = create_object("<", BCOND);
  b = create_object("x", VAR);
  c = create_object("10", NUM);
  object *lt_list = cons(a, cons(b, cons(c, NULL)));

  a = create_object(">", BCOND);
  b = create_object("x", VAR);
  c = create_object("0", NUM);
  object *gt_list = cons(a, cons(b, cons(c, NULL)));

  a = create_object("and", CCOND);
  object *and_list = cons(a, cons(gt_list, cons(lt_list, NULL)));

  object *if_list = cons(and_list, cons(mult_list, cons(add_list, NULL)));

  print_expr(add_list);
  printf("\n\n");

  print_expr(mult_list);
  printf("\n\n");

  print_expr(if_list);
  printf("\n");
}

void test_three(){
  object *a, *b, *c;
  a = create_object("+", OP);
  b = create_object("2", NUM);
  c = create_object("x", VAR);
  object *add_list = cons(a, cons(b, cons(c, NULL)));

  print_expr(add_list);
  printf("\n");

  a = create_object("x", VAR);
  b = create_object("10", NUM);
  object *varassign = cons(a, cons(b, NULL));

  a = create_object("var", VAREXPR);
  object *varexpr = cons(a, cons(varassign, cons(add_list, NULL)));

  print_expr(varexpr);
  printf("\n");
}

int main(){

  // test_one();
  // test_two();
  test_three();

  return 0;
}
