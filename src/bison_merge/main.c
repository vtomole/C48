/*
 * main.c file
 */

#include "expression.h"
#include "parser.h"
#include "lexer.h"
#include "environment-bison-merge.c"
#include "eval-bison-merge.c"
#include "print-bison-merge.c"

#include <stdio.h>
 
/* 
 // This parser declaration is in parser.h after bison runs.
 int yyparse(SExpression **expression, yyscan_t scanner); 
*/

SExpression *getAST(const char *source_code){
  /* get Abstract Syntax Tree , i.e. 
     source_code as text => parse_tree with SExpression for root node */
  SExpression *expression;
  yyscan_t scanner;
  YY_BUFFER_STATE state;
  int parse_status;
  int lex_status;

  lex_status = yylex_init(&scanner);             
  if (lex_status) return NULL;                   

  state = yy_scan_string(source_code, scanner);   

  parse_status = yyparse(&expression, scanner);   
  if (parse_status) return NULL;                 

  yy_delete_buffer(state, scanner);               
  yylex_destroy(scanner);

  return expression;
}

/* (+ 5 6) -> cons(left (cons right (cons left null)  null))    */

object *convert_ast(SExpression *e, object* exp){ 
  switch (e->type) {
   
  case plus:
   exp = cons(create_number(e->left->value), empty_list);
   exp = cons(create_number(e->right->value), exp);
   exp = cons(create_symbol("+"), exp);   

  }
  /*printf("Here\n");*/
  /*print(exp);*/
  return exp;

}

/* -- "execute" the parse tree -- 
 *
 *  (This is where the "now run it" part would
 *   happen for a larger programming language.)
 */
 
int evaluate(SExpression *e){
  switch (e->type) {
  case eVALUE:
    return e->value;
  case multiply:
    return evaluate(e->left) * evaluate(e->right);
  case plus:
    return evaluate(e->left) + evaluate(e->right);
  default:          
    return 0;
  }
}

/* -- start graphviz parse tree code -- 
 *
 * write_graphviz(expression) creates the file tree.dot
 * which can be used to generate an image of the parse tree
 * using the graphiz.org "dot" command, i.e.

       dot -Tpng < tree.dot > tree.png 
 */

char* node_name(SExpression *e){
  /* return char* description of parse tree node, e.g. '+', '-', '3', etc */
  char* name = (char *)malloc(16); 
  switch (e->type){
  case eVALUE:
    sprintf(name, "%i", e->value);
    return name;
  case multiply:
    sprintf(name, "*");
    return name;
  case plus:
    sprintf(name, "+");
    return name;
  default:  
    sprintf(name, "???");
    return name;
  }
}

/* We need to declare this before write_node so
   that the recursive mutual calls compile properly. */
void write_tree(SExpression *e, FILE *dotfile, int node);

void write_node(SExpression *e, FILE *dotfile, int node, int parent){
  fprintf(dotfile, " %i -> %i;\n", parent, node);
  write_tree(e, dotfile, node);
}

void write_tree(SExpression *e, FILE *dotfile, int node){
  fprintf(dotfile, " %i [label=\"%s\"];\n", node, node_name(e));
  if (e->left != NULL) write_node(e->left, dotfile, 2*node, node);
  if (e->right != NULL) write_node(e->right, dotfile, 2*node+1, node);
}

void write_graphviz(SExpression *e){
  FILE *dotfile = fopen("tree.dot", "w");
  fprintf(dotfile, "digraph tree {\n");
  write_tree(e, dotfile, 1);
  fprintf(dotfile, "}\n");
  fclose(dotfile);
}

/* -- main -- */

int main(int argc, char **argv){
  SExpression *e = NULL;
  char test[1000];
  int result = 0;
  object* exp;
  initialize_environment();
  while(1){
  printf("repl> ");
  fgets(test,1000,stdin);
  e = getAST(test);
  /*e = typecheck(e)*/
  exp = convert_ast(e, exp);
  print(eval(exp, environment));
  write_graphviz(e);
  
  /*printf("%d", evaluate(e));*/
  printf("\n");
  deleteExpression(e);
  }
  return 0;
  }

