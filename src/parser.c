typedef struct constructor_cell{
  void* car; //first element
  void* cdr; //rest of the list w/ first element
}constructor_cell;

//constructor_cell* code_tree = NULL; //Put the cells in this

typedef struct type_list{
  struct object val;
  struct type_list *next;
}type_list;
  
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

//while list is not null
//check type
//put type in type list (v1)
//or dont use type list
//and just create a cons cell
constructor_cell* parse(token_list* token_list, constructor_cell* code_tree){
  while(token_list != NULL){
    code_tree = cons2(&token_list, &code_tree);
  }
}

