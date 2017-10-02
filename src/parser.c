//#include "parser.h"

enum type{Symbol, List, Function, String, Number};

typedef struct constructor_cell{
  void* car; //first element
  void* cdr; //rest of the list w/ first element
 
}constructor_cell;

struct symbol {
  char *name;
  struct symbol *next;
}symbol;



  
 

typedef struct object {
  char* type;

 
  struct cons_cell{
    
    struct object *car;
    struct object *cdr;
  }cons_cell;
 
  char* variable;
  char *string;
  int number;

 
  }object;


object* cons3 (object *car, object *cdr){
  struct object *object1;
  object *test1 = malloc(sizeof(*object1));
  test1->type = "cons";
  test1->cons_cell.car = car;
  test1->cons_cell.cdr = cdr;
  return test1;
}

object* car1 (object *cell){
  assert (strcmp(cell->type, "cons") == 0);

  return cell->cons_cell.car;
}

object* cdr1 (object *cell){
  assert (strcmp(cell->type, "cons") == 0);

  return cell->cons_cell.cdr;
}




object* create_number (int number){
  struct object *object1;
  object *test1 = malloc(sizeof(*object1));
  test1->type = "number";
  test1->number= number;
  return test1;
}

object* create_variable (char* variable){
  struct object *object1;
  object *test1 = malloc(sizeof(*object1));
  test1->type = "variable";
  test1->variable = variable ;
  return test1;
}

object* create_primitiveop (char* variable){
  struct object *object1;
  object *test1 = malloc(sizeof(*object1));
  test1->type = "primop";
  test1->variable = variable ;
  return test1;
}








//constructor_cell* code_tree = NULL; //Put the cells in this

typedef struct type_list{
  struct object val;
  struct type_list *next;
}type_list;

//Use this when you dereference void pointer to pointer fine
char* get_car(void* car){
  return *(char**)car;
}
  
//Cell constructor
constructor_cell* construct_cell(void* first_element, void* list){

  constructor_cell* cell = malloc(sizeof(constructor_cell));
  if(cell == NULL){
    printf("Error creating a new node.\n");
    exit(0);
  }
  cell->car = first_element;
  cell->cdr = list;
  return cell;
}

//prints the parameters in a list
void print_token_list2(token_list* token_list){
  void* ptr;
  while(&token_list->val !=NULL){
    ptr = &token_list->val;
    printf("%s %s \n", ((struct token_object*)ptr)->value, ((struct token_object*)ptr)->type);
    ptr = &token_list->next;
    token_list = *(struct token_list**)ptr;
  }
}

//recursively adds the token_lists to the code tree
constructor_cell* parse(token_list* token_list, constructor_cell* code_tree){
  if(token_list == NULL){
    return code_tree;
  }
  code_tree = construct_cell(&token_list, &code_tree);
  print_token_list2(token_list);
  printf("/////////////token list//////////////\n");
  parse(token_list->next, code_tree);
}

