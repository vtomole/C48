#include "../src/print.c"

object *arithexpr_test(){
  object *a, *b, *c;
  a = create_object("+", OP);
  b = create_object("1", NUM);
  c = create_object("2", NUM);
  object *add = cons(a, cons(b, cons(c, NULL)));

  a = create_object("-",  OP);
  b = create_object("7", NUM);
  object *sub = cons(a, cons(add, cons(b, NULL)));

  return sub;
}

object *ifexpr_test(){
  object *a, *b, *c;
  a = create_object("+", OP);
  b = create_object("x", VAR);
  c = create_object("-1", NUM);
  object *add = cons(a, cons(b, cons(c, NULL)));
  
  a = create_object("*", OP);
  b = create_object("x", VAR);
  c = create_object("10", NUM);
  object *mult = cons(a, cons(b, cons(c, NULL)));

  a = create_object("<", BCOND);
  b = create_object("x", VAR);
  c = create_object("10", NUM);
  object *lt = cons(a, cons(b, cons(c, NULL)));

  a = create_object(">", BCOND);
  b = create_object("x", VAR);
  c = create_object("0", NUM);
  object *gt = cons(a, cons(b, cons(c, NULL)));

  a = create_object("and", CCOND);
  object *and = cons(a, cons(gt, cons(lt, NULL)));

  object *if_list = cons(and, cons(mult, cons(add, NULL)));

  return if_list;
}

object *varexpr_test(){
  object *a, *b, *c;
  a = create_object("+", OP);
  b = create_object("2", NUM);
  c = create_object("x", VAR);
  object *add_list = cons(a, cons(b, cons(c, NULL)));

  a = create_object("x", VAR);
  b = create_object("10", NUM);
  object *varassign = cons(a, cons(b, NULL));

  a = create_object("var", VAREXPR);
  object *varexpr = cons(a, cons(varassign, cons(add_list, NULL)));

  return varexpr;
}

object *funcexpr_test(){
  object *a, *b, *c;
  a = create_object("x", VAR);
  b = create_object("y", VAR);
  c = create_object("z", VAR);
  object *params = cons(a, cons(b, cons(c, NULL)));

  a = create_object("/", OP);
  b = create_object("2", NUM);
  c = create_object("x", VAR);
  object *expr1 = cons(a, cons(b, cons(c, NULL)));

  a = create_object("*", OP);
  b = create_object("z", VAR);
  c = create_object("y", VAR);
  object *expr2 = cons(a, cons(b, cons(c, NULL)));

  b = create_object("func_name", FUNC);
  b = cons(b, cons(params, NULL));
  b = cons(b, cons(expr1, NULL));

  a = create_object("func", FUNCEXPR);
  object *func = cons(a, cons(b, cons(expr2, NULL)));
  return func;
}

object *funcapply_test(){
  object *a, *b, *c;
  a = create_object("+", OP);
  b = create_object("x", VAR);
  c = create_object("2", NUM);
  object *expr1 = cons(a, cons(b, cons(c, NULL)));
  
  a = create_object("10", NUM);
  object *args = cons(expr1, cons(a, NULL));

  a = create_object("apply", FUNCAPPLY);
  b = create_object("func_name", FUNC);
  object *funcapply = cons(a, cons(b, cons(args, NULL)));

  return funcapply;
}

int main(){

  ////should return ( - ( + 1 2) 7 )
  object *arithexpr = arithexpr_test();
  print_expr(arithexpr);
  printf("\n");
  free(arithexpr);

  ////should return ( (and ( > x 0 ) ( < x 10 ) ) ( * x 10 ) ( + x -1 ) )
  object *ifexpr = ifexpr_test();
  print_expr(ifexpr);
  printf("\n");
  free(ifexpr);

  ////should return ( var ( x 10 ) ( + 2 x ) )
  object *varexpr = varexpr_test();
  print_expr(varexpr);
  printf("\n");
  free(varexpr);
  
  ////should return ( func ( ( func_name ( x y z ) ) ( / 2 x ) ) ( * z y ) )
  object *funcexpr = funcexpr_test();
  print_expr(funcexpr);
  printf("\n");
  free(funcexpr);

  ////should return (apply ( func_name ( ( + x 2 ) 10 ) ) )
  object *funcapply = funcapply_test();
  print_expr(funcapply);
  printf("\n");
  free(funcapply);

  return 0;
}
