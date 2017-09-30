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
  char* symbol;
  char *string;
  int number;
 
}object;



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
constructor_cell* cons2(void* first_element, void* list){

  constructor_cell* cell = malloc(sizeof(constructor_cell));
  if(cell == NULL){
    printf("Error creating a new node.\n");
    exit(0);
  }
  cell->car = first_element;
  cell->cdr = list;
  return cell;
}



object* cons3(object car, object cdr){

  object *cell = malloc(sizeof(object));
  //cell->type = List;
  //cell->car = car;
    //cell->cdr = cdr;
  return cell;
  
};

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

//prints the parameters in a list
void print_code_tree(constructor_cell* code_tree){
  print_token_list2(code_tree->cdr);
}

//recursively adds the token_lists to the code tree
constructor_cell* parse(token_list* token_list, constructor_cell* code_tree){
  if(token_list == NULL){
    return code_tree;
  }
  code_tree = cons2(&token_list, &code_tree);
  print_token_list2(token_list);
  printf("///////////////////////////\n");
  parse(token_list->next, code_tree);
}

