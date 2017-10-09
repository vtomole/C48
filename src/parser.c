#include "object.c"
#include "token.c"

/**
 *This function prints out the token list
 * Parameters:
 * -token_list, the token_list to print
 */
void print_token_list2(token_list* token_list){
  void* ptr;
  while(&token_list->val !=NULL){
    ptr = &token_list->val;
    printf("%s %s \n", ((struct token_object*)ptr)->value, ((struct token_object*)ptr)->type);
    ptr = &token_list->next;
    token_list = *(struct token_list**)ptr;
  }
}

/**
 *Recursivly adds tokens to the code_tree
 * Parameters:
 * -token_list, the list of tokens to add to the code_tree
 * -code_tree, the code_tree being built
 */
//Will return object list
object* parse(token_list* token_list, object* code_tree){
  if(token_list == NULL){
    return code_tree;
  }
  //Check the properties of token
  //Create the object.
  code_tree = cons(code_tree, code_tree);
  print_token_list2(token_list);
  // printf("///////////////////////////\n");
  parse(token_list->next, code_tree);
}

