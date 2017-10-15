#include "../src/print.c"

int main(){
  /**
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
  **/


  object *add = create_object("+", OP);
  object *var1 = create_object("x", VAR);
  object *num1 = create_object("-1", NUM);
  object *add_list = NULL;
  add_list = cons(num1, add_list);
  add_list = cons(var1, add_list);
  add_list = cons(add, add_list);
  
  object *sub = create_object("*", OP);
  object *var2 = create_object("x", VAR);
  object *num2 = create_object("10", NUM);
  object *mult_list = NULL;
  mult_list = cons(num2, mult_list);
  mult_list = cons(var2, mult_list);
  mult_list = cons(sub, mult_list);

  object *lt = create_object("<", BCOND);
  object *var3 = create_object("x", VAR);
  object *num3 = create_object("10", NUM);
  object *lt_list = NULL;
  lt_list = cons(num3, lt_list);
  lt_list = cons(var3, lt_list);
  lt_list = cons(lt, lt_list);

  object *gt = create_object(">", BCOND);
  object *var4 = create_object("x", VAR);
  object *num4 = create_object("0", NUM);
  object *gt_list = NULL;
  gt_list = cons(num4, gt_list);
  gt_list = cons(var4, gt_list);
  gt_list = cons(gt, gt_list);

  object *and = create_object("and", CCOND);
  object *and_list = NULL;
  and_list = cons(lt_list, and_list);
  and_list = cons(gt_list, and_list);
  and_list = cons(and, and_list);

  object *if_list = NULL;
  if_list = cons(add_list, if_list);
  if_list = cons(mult_list, if_list);
  if_list = cons(and_list, if_list);

  print_expr(add_list);
  printf("\n");

  print_expr(mult_list);
  printf("\n");

  print_expr(if_list);
  printf("\n");

  return 0;
}
