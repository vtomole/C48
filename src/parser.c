//#include "parser.h"

enum type{Symbol, List, Function, String, Number};

typedef struct constructor_cell{
  void* car; //first element
  void* cdr; //rest of the list w/ first element 
}constructor_cell;

struct symbol{//typedef struct symbol???
  char *name;
  struct symbol *next;
}symbol;

typedef struct object{
  char* type;
  struct cons_cell{
    struct object *car;
    struct object *cdr;
  }cons_cell;
 
  char* variable;
  char *string;
  int number;
}object;

/**
 *This function constructs ????
 * Parameters:
 * - car, the first object in the code tree
 * - cdr, the rest of the objects in the code tree
 * Return Value:
 * - test1, an object ???
 */
object* cons(object *car, object *cdr){
  struct object *object1;
  object *test1 = malloc(sizeof(*object1));

  test1->type = "cons";
  test1->cons_cell.car = car;
  test1->cons_cell.cdr = cdr;

  return test1;
}

/**
 *This function checks if the cells car is ???
 * Parameters:
 * - cell, an object ???
 * Return Value:
 * - ???
 */
object* car1(object *cell){
  assert (strcmp(cell->type, "cons") == 0);
  return cell->cons_cell.car;
}

/**
 *This function checks that the cells cdr is ???
 * Parameters:
 * - cell
 * Return Value:
 * - ???
 */
object* cdr1(object *cell){
  assert (strcmp(cell->type, "cons") == 0);
  return cell->cons_cell.cdr;
}

/**
 *This function creates an object representing a number
 * Parameters:
 * - number, the value of the object to create
 * Return Value:
 * - num an object with type number and value number
 */
object* create_number(int number){
  struct object *object1;
  object *num = malloc(sizeof(*object1));
  num->type  ="number";
  //num->value = number;
  num->number = number;
  return num;
}

/**
 *This function creates an object representing a variable
 * Parameters:
 * - variable the value of the object to create
 * Return Value:
 * -var, an object with type "variable", and value variable
 */
object* create_variable(char* variable){
  struct object *object1;
  object *var = malloc(sizeof(*object1));
  var->type = "variable";
  //var->value = variable;
  var->variable = variable;
  return var;
}

/**
 *This function creates an object representing a primitive operation
 * Parameters:
 * - variable the value of the object to create
 * Return Value:
 * -var, an object with type "primeop", and value variable
 */
object* create_primitiveop(char* variable){
  struct object *object1;
  object *var = malloc(sizeof(*object1));
  var->type = "primop";
  //var->value = variable;
  var->variable = variable;
  return var;
}

//constructor_cell* code_tree = NULL; //Put the cells in this

typedef struct type_list{
  struct object val;
  struct type_list *next;
}type_list;

/**Use this when you dereference void pointer to pointer fine
 *This function gets the head of the code tree
 * Parameters:
 * -car, the cell containing the the type and value of the head of the code tree
 * Return Value:
 * -car, a c string of the value of the head of the code_tree
 */
char* get_car(void* car){
  return *(char**)car;
}
  
/**
 *This function creates cells for the code tree
 * Parameters:
 * - first_element, equivalent to car, the token at the head of the code tree
 * - list, equivalent to cdr, the token_list that car points to
 * Return Value:
 * -cell, a constructor_cell to be used in the code tree
 */
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
 *This function prints the code_tree
 * Parameters:
 * -code_tree, the code_tree to print
 */
void print_code_tree(constructor_cell* code_tree){
  print_token_list2(code_tree->cdr);
}

/**
 *Recursivly adds tokens to the code_tree
 * Parameters:
 * -token_list, the list of tokens to add to the code_tree
 * -code_tree, the code_tree being built
 */
constructor_cell* parse(token_list* token_list, constructor_cell* code_tree){
  if(token_list == NULL){
    return code_tree;
  }

  code_tree = construct_cell(&token_list, &code_tree);
  print_token_list2(token_list);
  // printf("///////////////////////////\n");
  parse(token_list->next, code_tree);
}

