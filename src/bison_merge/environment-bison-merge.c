# include "environment-bison-merge.h" 
object* allocate_object(){
  object *obj;

  obj = malloc(sizeof(object));

  if(obj == NULL){
    fprintf(stderr, "out of memory\n");
    exit(1);
  }
  return obj;

}



int nullp(object *obj){ return obj==empty_list; }
int pairp(object *obj){ return obj->obj_type == PAIR; }
int symbolp(object *obj){ return obj->obj_type == SYMBOL; }
int truep(object *obj){ return obj->boolean == true; }
int falsep(object *obj){ return obj->boolean == false; }
int booleanp(object *obj){ return obj->obj_type == BOOLEAN; }
int numberp(object *obj){ return obj->obj_type == NUMBER; }
int stringp(object *obj){ return obj->obj_type == STRING; }
int characterp(object *obj){ return obj->obj_type == CHARACTER; }
char compoundp(object *obj) { return obj->obj_type == COMPOUND_PROCEDURE;}


object* cons(object *car, object *cdr);
object* make_frame(object *variables, object *values){ return cons(variables,values); }
  
object* extend_environment(object *vars, object *vals, object *base_env){ return cons(make_frame(vars, vals), base_env); }





/**
 *This function checks if the cells car is ???
 * Parameters:
 * - cell, an object ???
 * Return Value:
 * - ???
 */
object* car(object *obj){ return obj->cons_cell.car; }

void set_car(object *z, object *new_value){
  z->cons_cell.car = new_value;
}

void set_cdr(object *z, object *new_value){
  z->cons_cell.cdr = new_value;
}

/**
 *This function checks that the cells cdr is ???
 * Parameters:
 * - cell
 * Return Value:
 * - ???
 */
object* cdr(object *obj){ return obj->cons_cell.cdr; }

/**
 *This function constructs ????
 * Parameters:
 * - car, the first object in the code tree
 * - cdr, the rest of the objects in the code tree
 * Return Value:
 * - test1, an object ???
 */
object* cons(object *car, object *cdr){
  object *obj;
   
  obj = allocate_object();
  obj -> obj_type = PAIR;
  obj->cons_cell.car = car;
  obj->cons_cell.cdr = cdr;
  
  return obj;  
}
#define caar(obj)   car(car(obj))
#define cadr(obj)   car(cdr(obj))
#define cdar(obj)   cdr(car(obj))
#define cddr(obj)   cdr(cdr(obj))
#define caaar(obj)  car(car(car(obj)))
#define caadr(obj)  car(car(cdr(obj)))
#define cadar(obj)  car(cdr(car(obj)))
#define caddr(obj)  car(cdr(cdr(obj)))
#define cdaar(obj)  cdr(car(car(obj)))
#define cdadr(obj)  cdr(car(cdr(obj)))
#define cddar(obj)  cdr(cdr(car(obj)))
#define cdddr(obj)  cdr(cdr(cdr(obj)))
#define caaaar(obj) car(car(car(car(obj))))
#define caaadr(obj) car(car(car(cdr(obj))))
#define caadar(obj) car(car(cdr(car(obj))))
#define caaddr(obj) car(car(cdr(cdr(obj))))
#define cadaar(obj) car(cdr(car(car(obj))))
#define cadadr(obj) car(cdr(car(cdr(obj))))
#define caddar(obj) car(cdr(cdr(car(obj))))
#define cadddr(obj) car(cdr(cdr(cdr(obj))))
#define cdaaar(obj) cdr(car(car(car(obj))))
#define cdaadr(obj) cdr(car(car(cdr(obj))))
#define cdadar(obj) cdr(car(cdr(car(obj))))
#define cdaddr(obj) cdr(car(cdr(cdr(obj))))
#define cddaar(obj) cdr(cdr(car(car(obj))))
#define cddadr(obj) cdr(cdr(car(cdr(obj))))
#define cdddar(obj) cdr(cdr(cdr(car(obj))))
#define cddddr(obj) cdr(cdr(cdr(cdr(obj))))

/**
 *This function creates an object representing a number
 * Parameters:
 * - number, the value of the object to create
 * Return Value:
 * - num an object with type number and value number
 */
object *create_number(int value) {
    object *obj;
    
    obj = allocate_object();
    obj->obj_type = NUMBER;
    obj->number = value;      
    return obj;
}

object *create_character(char value) {
    object *obj;
    
    obj = allocate_object();
    obj->obj_type = CHARACTER;
    obj->character = value;      
    return obj;
}

/**
 *This function creates an object representing a number
 * Parameters:
 * - number, the value of the object to create
 * Return Value:
 * - num an object with type number and value number
 */
object *create_string(char *value) {
    object *obj;

    obj = allocate_object();
    obj->obj_type = STRING;
    obj->string = malloc(strlen(value) + 1);
    if (obj->string == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }
    strcpy(obj->string, value);
    return obj;
}

/**
 *This function creates an object representing a variable
 * Parameters:
 * - variable the value of the object to create
 * Return Value:
 * -var, an object with type "variable", and value variable
 */


object* create_symbol(char *value){
  object *obj, *element;
  
  element = symbol_table;

 
  while(!nullp(element)){
    if(strcmp(car(element)->symbol, value) == 0){
      return car(element);
    }    
    element = cdr(element);
  }
  
  obj = allocate_object();
  obj->obj_type = SYMBOL;
  obj->symbol = malloc(strlen(value) + 1); 

  if(obj->symbol == NULL){
    fprintf(stderr, "out of memory\n");
    exit(1);
  }
  
  strcpy(obj->symbol, value);
  symbol_table = cons(obj, symbol_table);
  /*printf("Nullp %s\n", car(symbol_table)->symbol);*/
  return obj;
}

/**
 *This function creates an object representing a primitive operation
 * Parameters:
 * - variable the value of the object to create
 * Return Value:
 * -var, an object with type "primeop", and value variable
 */


/*constructor_cell* code_tree = NULL; //Put the cells in this*/

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

object* assignment_variable(object *exp) {return cadr(exp); };
object* assignment_value(object *exp) {return caddr(exp); };
object* frame_variables (object *frame) { return car(frame); }
object* frame_values (object *frame) { return cdr(frame); }
void add_binding_to_frame(object *var, object *val, object *frame){
  set_car(frame, cons(var, car(frame)));
  set_cdr(frame, cons(val, cdr(frame))); 

}
object* enclosing_environment(object *env) { return cdr(env); }
object* first_frame(object *env) { return car(env); }


int count_objects(object* cursor){
  int c = 0;
  while(cursor != NULL){
    c++;
    cursor = cursor->cons_cell.cdr;
  }
  return c;
}

object* lookup_variable_value(object* var, object* env){
  object *frame;
    object *vars;
    object *vals;
    while (!nullp(env)) {
        frame = first_frame(env);
        vars = frame_variables(frame);
        vals = frame_values(frame);
        while (!nullp(vars)) {
            if (var == car(vars)) {
                return car(vals);
            }
            vars = cdr(vars);
            vals = cdr(vals);
        }
        env = enclosing_environment(env);
    }
    fprintf(stderr, "unbound variable\n");
    exit(1);
}

void set_variable_value(object *var, object *val, object* env){
  object *frame, *vars, *vals;

  while(!nullp(env)){
    frame = first_frame(env);
    vars = frame_variables(frame);
    vals = frame_values(frame);

    while(!nullp(vars)){
      if(var == car(vars)){
	set_car(vals,val);
	return;
      }
      vars = cdr(vars);
      vals = cdr(vals);
    }
    env = enclosing_environment(env);
  }
  fprintf(stderr, "unboud variable\n");
  exit(1);

}

void define_variable (object *var, object *val, object* env){
  object *frame, *vars, *vals;
  
  frame = first_frame(env);
  vars = frame_variables(frame);
  vals = frame_values(frame);

  while(!nullp(vars)){
    if(var == car(vars)){
      set_car(vals,val);
      return;
    }
    vars = cdr(vars);
    vals = cdr(vals);
  }
  add_binding_to_frame(var, val, frame);   
}

/**
 *Recursivly adds tokens to the code_tree
 * Parameters:
 * -token_list, the list of tokens to add to the code_tree
 * -code_tree, the code_tree being built
 */

/*Will return object list*/
/*
 * this method recursivly goes through parse to create an unknown number of lists
 * by doing this each call to parse_rec should be a nested statement
 * each statement returns a list containing all the statements before a right or left paren
 * no seg_faults however the code isn't doing anything visible with the temp_list it creates and maintains.
**/
object *create_primitive_procedure(object *(*fn)(struct object *arguments)){
  object *obj;

  obj = allocate_object();
  obj->obj_type = PRIMITIVE_PROCEDURE;
  obj->primitive_procedure.fn = fn;
  return obj;
}

object *make_procedure(object* parameters, object* body, object* env){
  object* obj;

  obj = allocate_object();
  obj->obj_type = COMPOUND_PROCEDURE;
  obj->compound_procedure.parameters = parameters;
  obj->compound_procedure.body = body;
  obj->compound_procedure.env = env;
  return obj;
}

object *setup_environment(){
  object *initial_environment;

  initial_environment = extend_environment(empty_list, empty_list, empty_environment);

  return initial_environment;
}

object* nullp_procedure(object *arguments){
  return nullp(car(arguments)) ? true_symbol : false_symbol;
}

object* add_procedure(object *arguments){
  int result = 0;
  while(!nullp(arguments)){
    result += car(arguments)->number;
    arguments = cdr(arguments);
  }
  return create_number(result);
}

object* sub_procedure(object *arguments){
  int result;
  while(!nullp(arguments)){
    result -= car(arguments)->number;
    arguments = cdr(arguments);
  }
  return create_number(result);
}

object* mul_procedure(object *arguments){
  int result = 1;
  while(!nullp(arguments)){
    result *= car(arguments)->number;
    arguments = cdr(arguments);
  }
  return create_number(result);
}



void  initialize_environment(void) {

    empty_list = allocate_object();
     
    empty_list->obj_type = EMPTY_LIST;

    false_symbol = allocate_object();
    false_symbol->obj_type = BOOLEAN;
    false_symbol->boolean = 1;

    true_symbol = allocate_object();
    true_symbol->obj_type = BOOLEAN;
    true_symbol->boolean = 0;
    
    
    symbol_table = empty_list;    
    quote_symbol = create_symbol("quote");
    define_symbol = create_symbol("define");
    set_symbol = create_symbol("set!");
    ok_symbol = create_symbol("ok");
    if_symbol = create_symbol("if");
    lambda_symbol = create_symbol("lambda");
    begin_symbol = create_symbol("begin");
    cond_symbol = create_symbol("cond");
    else_symbol = create_symbol("else");
    /*let_symbol = create_symbol("let");*/
    
    
    empty_environment = empty_list;

    environment = setup_environment();

#define add_procedure(scheme_name, c_name)              \
    define_variable(create_symbol(scheme_name),           \
                    create_primitive_procedure(c_name),        \
                    environment);

    add_procedure("null?"      , nullp_procedure);      
    add_procedure("+"        , add_procedure);
    add_procedure("-"        , sub_procedure);
    add_procedure("*"        , mul_procedure);
    /*add_procedure("quotient" , quotient_proc);
    add_procedure("remainder", remainder_proc);
    add_procedure("="        , number_equalp_procedure);
    add_procedure("<"        , less_thanp_proceduce);
    add_procedure(">"        , greater_thanp_procedure);
    add_procedure("print"    , print_proc);*/
}
