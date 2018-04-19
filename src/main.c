#include "expression.h"
#include <stdio.h>

/* We need to declare this before write_node so
   that the recursive mutual calls compile properly. */
/**
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
**/

int main(int argc, char *argv[]){
  if(argc > 1 && argv[1][0] == 'r'){
    open_file("test.txt");
 }
  else{
    //printf("In else statement\n");
    printf("> ");
  }
  return yyparse();
}
