# include "environment.h" 
void print(object *obj);
int count_objects(object* cursor){
  int c = 0;
  while(cursor != NULL){
    c++;
    cursor = cursor->cons_cell.cdr;
  }
  return c;
}
/* Garbage collector struct*/
/* Delete start */
struct Allocation {
         struct cons_cell pair;
	int mark : 1;
	struct Allocation *next;
};

struct Allocation *global_allocations = NULL;/*list used for the garbage collector*/

/* Delete stop*/

object* alloc_object(){
  object *obj;

  obj = malloc(sizeof(object));

  if(obj == NULL){
    fprintf(stderr, "out of memory\n");
    exit(1);
  }
  return obj;

}


object *the_empty_list;
object *false;
object *true;
object *symbol_table;
object *quote_symbol;
object *define_symbol;
object *set_symbol;
object *ok_symbol;
object *if_symbol;
object *lambda_symbol;
object *begin_symbol;
object *cond_symbol;
object *else_symbol;
object *let_symbol;
object *the_empty_environment;
object *the_global_environment;

object *cons(object *car, object *cdr);
object *car(object *pair);
object *cdr(object *pair);

char is_the_empty_list(object *obj) {
    return obj == the_empty_list;
}

char booleanp(object *obj) {
    return obj->obj_type == BOOLEAN;
}

char is_false(object *obj) {
    return obj == false;
}

char is_true(object *obj) {
    return !is_false(obj);
}

object *make_symbol(char *value) {
    object *obj;
    object *element;
    
    /* search for the symbol in the symbol table */
    element = symbol_table;
    while (!is_the_empty_list(element)) {
        if (strcmp(car(element)->symbol, value) == 0) {
            return car(element);
        }
        element = cdr(element);
    };
    
    /* create the symbol and add it to the symbol table */
    obj = alloc_object();
    obj->obj_type = SYMBOL;
    obj->symbol = malloc(strlen(value) + 1);
    if (obj->symbol == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }
    strcpy(obj->symbol, value);
    symbol_table = cons(obj, symbol_table);
    return obj;
}

char is_symbol(object *obj) {
    return obj->obj_type == SYMBOL;
}

object *make_fixnum(long value) {
    object *obj;

    obj = alloc_object();
    obj->obj_type = FIXNUM;
    obj->number = value;
    return obj;
}

object *make_float(double value) {
    object *obj;

    obj = alloc_object();
    obj->obj_type = FLOAT;
    obj->decimal = value;
    return obj;
}

char numberp(object *obj) {
    return obj->obj_type == FIXNUM;
}

char floatp(object *obj) {
    return obj->obj_type == FLOAT;
}

object *make_character(char value) {
    object *obj;

    obj = alloc_object();
    obj->obj_type = CHARACTER;
    obj->character = value;
    return obj;
}

char characterp(object *obj) {return obj->obj_type == CHARACTER;}

object *make_string(char *value) {
    object *obj;

    obj = alloc_object();
    obj->obj_type = STRING;
    obj->string = malloc(strlen(value) + 1);
    if (obj->string == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }
    strcpy(obj->string, value);
    return obj;
}

char is_string(object *obj) {
    return obj->obj_type == STRING;
}

object* cons(object *car, object *cdr){
  
  struct Allocation *a;
  object *obj;
   
  //add a marker upon the call to cons
  a = malloc(sizeof(struct Allocation));
  a->mark = 0;
  a->next = global_allocations;
  global_allocations = a;
  

  obj = alloc_object();
  obj -> obj_type = PAIR;

  obj->cons_cell = a->pair;

  obj->cons_cell.car = car;
  obj->cons_cell.cdr = cdr;
  
  return obj;  
}

char is_pair(object *obj) {
    return obj->obj_type == PAIR;
}

object *car(object *pair) {
    return pair->cons_cell.car;
}

void set_car(object *obj, object* value) {
    obj->cons_cell.car = value;
}

object *cdr(object *pair) {
    return pair->cons_cell.cdr;
}

void set_cdr(object *obj, object* value) {
    obj->cons_cell.cdr = value;
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

primitive_type char_to_enum(char* proc){
  if(strcmp(proc, "+") ==0 || strcmp(proc, "-") ==0 || strcmp(proc, "+") ==0){
    //printf("It's a plus\n");
    return MATH;
  }
     
  else{
    return CHAR;
  }
}
object *set_acceptable(object *obj, primitive_type prim_type){
  switch (prim_type){
  case 0:
    //printf("In case 1\n");
    obj->primitive_proc.acceptables = cons(make_fixnum(FIXNUM), (cons (make_fixnum(FLOAT), the_empty_list)));
    //print(obj->primitive_proc.acceptables);
    break;
  case 1:
    obj->primitive_proc.acceptables = cons(make_string("CHAR"),  the_empty_list);break;
  default:
    //printf("This should not happen after PLUS\n");
    obj->primitive_proc.acceptables = the_empty_list;
    
  }
  return obj;
}

object *make_primitive_proc(object *(*fn)(struct object *arguments), char *proc) {
    object *obj;

    //printf("PRIM PROC %s\n", proc);

    obj = alloc_object();
    obj->obj_type = PRIMITIVE_PROC;
    obj->primitive_proc.fn = fn;
    obj ->primitive_proc.prim_type = 1;
    set_acceptable(obj, char_to_enum(proc));
    return obj;
}

char primitivep(object *obj) {
    return obj->obj_type == PRIMITIVE_PROC;
}

object *is_null_proc(object *arguments) {
    return is_the_empty_list(car(arguments)) ? true : false;
}

object *is_boolean_proc(object *arguments) {
    return booleanp(car(arguments)) ? true : false;
}

object *is_symbol_proc(object *arguments) {
    return is_symbol(car(arguments)) ? true : false;
}

object *is_integer_proc(object *arguments) {
    return numberp(car(arguments)) ? true : false;
}

object *is_char_proc(object *arguments) {
    return characterp(car(arguments)) ? true : false;
}

object *is_string_proc(object *arguments) {
    return is_string(car(arguments)) ? true : false;
}

object *is_pair_proc(object *arguments) {
    return is_pair(car(arguments)) ? true : false;
}

char is_compound_proc(object *obj);

object *is_procedure_proc(object *arguments) {
    object *obj;
    
    obj = car(arguments);
    return (primitivep(obj) ||
            is_compound_proc(obj)) ?
                true :
                false;
}

object *char_to_integer_proc(object *arguments) {
    return make_fixnum((car(arguments))->character);
}

object *integer_to_char_proc(object *arguments) {
    return make_character((car(arguments))->number);
}

object *number_to_string_proc(object *arguments) {
    char buffer[100];

    sprintf(buffer, "%ld", (car(arguments))->number);
    return make_string(buffer);
}

object *string_to_number_proc(object *arguments) {
    return make_fixnum(atoi((car(arguments))->string));
}

object *symbol_to_string_proc(object *arguments) {
    return make_string((car(arguments))->symbol);
}

object *string_to_symbol_proc(object *arguments) {
    return make_symbol((car(arguments))->string);
}

object *add_proc(object *arguments) {
    long result = 0;
    double resultf = 0;
    
    if(car(arguments)->obj_type == FIXNUM){
	    while (!is_the_empty_list(arguments)) {
		result += (car(arguments))->number;
		arguments = cdr(arguments);
	    }
	    return make_fixnum(result);
    }
    else if(car(arguments)->obj_type == FLOAT){
	    while (!is_the_empty_list(arguments)) {
		resultf += (car(arguments))->decimal;
		arguments = cdr(arguments);
	    }
	    return make_float(resultf);
    }
}

object *sub_proc(object *arguments) {
    long result = 0;
    double resultf = 0;
    
    if(car(arguments)->obj_type == FIXNUM){
	    result += (car(arguments))->number;
	    arguments = cdr(arguments);

	    while (!is_the_empty_list(arguments)) {
		result -= (car(arguments))->number;
		arguments = cdr(arguments);
	    }
	    return make_fixnum(result);
    }
    else if(car(arguments)->obj_type == FLOAT){
	    resultf += (car(arguments))->decimal;
	    arguments = cdr(arguments);

	    while (!is_the_empty_list(arguments)) {
		resultf -= (car(arguments))->decimal;
		arguments = cdr(arguments);
	    }
	    return make_float(resultf);
    }
}

object *mul_proc(object *arguments) {
    long result = 1;
    
    while (!is_the_empty_list(arguments)) {
        result *= (car(arguments))->number;
        arguments = cdr(arguments);
    }
    return make_fixnum(result);
}

object *quotient_proc(object *arguments) {
    return make_fixnum(
        ((car(arguments) )->number)/
        ((cadr(arguments))->number));
}

object *remainder_proc(object *arguments) {
    return make_fixnum(
        ((car(arguments) )->number)%
        ((cadr(arguments))->number));
}

object *is_number_equal_proc(object *arguments) {
    long value;
    
    value = (car(arguments))->number;
    while (!is_the_empty_list(arguments = cdr(arguments))) {
        if (value != ((car(arguments))->number)) {
            return false;
        }
    }
    return true;
}

object *is_less_than_proc(object *arguments) {
    long previous;
    long next;
    
    previous = (car(arguments))->number;
    while (!is_the_empty_list(arguments = cdr(arguments))) {
        next = (car(arguments))->number;
        if (previous < next) {
            previous = next;
        }
        else {
            return false;
        }
    }
    return true;
}

object *is_greater_than_proc(object *arguments) {
    long previous;
    long next;
    
    previous = (car(arguments))->number;
    while (!is_the_empty_list(arguments = cdr(arguments))) {
        next = (car(arguments))->number;
        if (previous > next) {
            previous = next;
        }
        else {
            return false;
        }
    }
    return true;
}

object *cons_proc(object *arguments) {
    return cons(car(arguments), cadr(arguments));
}

object *car_proc(object *arguments) {
    return caar(arguments);
}

object *cdr_proc(object *arguments) {return cdar(arguments);}

object *set_car_proc(object *arguments) {
    set_car(car(arguments), cadr(arguments));
    printf("In set car proc");
    return ok_symbol;
}

object *set_cdr_proc(object *arguments) {
    set_cdr(car(arguments), cadr(arguments));
    printf("IN set cdr proc");
    return ok_symbol;
}



object *is_eq_proc(object *arguments) {
    object *obj1;
    object *obj2;
    
    obj1 = car(arguments);
    obj2 = cadr(arguments);
    
    if (obj1->obj_type != obj2->obj_type) {
        return false;
    }
    switch (obj1->obj_type) {
        case FIXNUM:
            return (obj1->number == 
                    obj2->number) ?
                        true : false;
            break;
        case CHARACTER:
            return (obj1->character == 
                    obj2->character) ?
                        true : false;
            break;
        case STRING:
            return (strcmp(obj1->string, 
                           obj2->string) == 0) ?
                        true : false;
            break;
        default:
            return (obj1 == obj2) ? true : false;
    }
}

object *make_compound_proc(object *parameters, object *body,
                           object* env) {
    object *obj;
    
    obj = alloc_object();
    obj->obj_type = COMPOUND_PROC;
    obj->compound_proc.parameters = parameters;
    obj->compound_proc.body = body;
    obj->compound_proc.env = env;
    return obj;
}

object *list_proc(object *arguments) {return arguments;}
char is_compound_proc(object *obj) {return obj->obj_type == COMPOUND_PROC;}
object *enclosing_environment(object *env) {return cdr(env);}
object *first_frame(object *env) {return car(env);}
object *make_frame(object *variables, object *values) {return cons(variables, values);}
object *frame_variables(object *frame) {return car(frame);}
object *frame_values(object *frame) {return cdr(frame);}

void add_binding_to_frame(object *var, object *val, 
                          object *frame) {
    set_car(frame, cons(var, car(frame)));
    set_cdr(frame, cons(val, cdr(frame)));
}

object *extend_environment(object *vars, object *vals,
                           object *base_env) {
    return cons(make_frame(vars, vals), base_env);
}

object *lookup_variable_value(object *var, object *env) {
//printf("Number of objects in environment %d\n", count_objects(env));
    object *frame;
    object *vars;
    object *vals;
    while (!is_the_empty_list(env)) {
        frame = first_frame(env);
        vars = frame_variables(frame);
        vals = frame_values(frame);
        while (!is_the_empty_list(vars)) {
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

object *lookup_variable_type(object *var, object *env) {
//printf("Number of objects in environment %d\n", count_objects(env));
    object *frame;
    object *vars;
    object *vals;
    while (!is_the_empty_list(env)) {
        frame = first_frame(env);
        vars = frame_variables(frame);
        vals = frame_values(frame);
        while (!is_the_empty_list(vars)) {
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

void set_variable_value(object *var, object *val, object *env) {
    object *frame;
    object *vars;
    object *vals;
 

    while (!is_the_empty_list(env)) {
        frame = first_frame(env);
        vars = frame_variables(frame);
        vals = frame_values(frame);
        while (!is_the_empty_list(vars)) {
            if (var == car(vars)) {
                set_car(vals, val);
                return;
            }
            vars = cdr(vars);
            vals = cdr(vals);
        }
        env = enclosing_environment(env);
    }
    fprintf(stderr, "unbound variable\n");
    exit(1);
}

void define_variable(object *var, object *val, object *env) {
  object *frame, *vars, *vals;
    frame = first_frame(env);    
    vars = frame_variables(frame);
    vals = frame_values(frame);

    while (!is_the_empty_list(vars)) {
        if (var == car(vars)) {
            set_car(vals, val);
            return;
        }
        vars = cdr(vars);
        vals = cdr(vals);
    }
    add_binding_to_frame(var, val, frame);
}

object *setup_environment(void) {
    object *initial_env;
    
    initial_env = extend_environment(
                      the_empty_list,
                      the_empty_list,
                      the_empty_environment);
    return initial_env;
}

void init(void) {
    the_empty_list = alloc_object();
    the_empty_list->obj_type = EMPTY_LIST;

    false = alloc_object();
    false->obj_type = BOOLEAN;
    false->boolean = 0;

    true = alloc_object();
    true->obj_type = BOOLEAN;
    true->boolean = 1;
    
    symbol_table = the_empty_list;
    quote_symbol = make_symbol("quote");
    define_symbol = make_symbol("define");
    set_symbol = make_symbol("set!");
    ok_symbol = make_symbol("ok");
    if_symbol = make_symbol("if");
    lambda_symbol = make_symbol("lambda");
    begin_symbol = make_symbol("begin");
    cond_symbol = make_symbol("cond");
    else_symbol = make_symbol("else");
    let_symbol = make_symbol("let");
    
    the_empty_environment = the_empty_list;

    the_global_environment = setup_environment();

#define add_procedure(scheme_name, c_name)              \
    define_variable(make_symbol(scheme_name),           \
                    make_primitive_proc(c_name, scheme_name),	\
                    the_global_environment);

    add_procedure("null?"      , is_null_proc);
    add_procedure("boolean?"   , is_boolean_proc);
    add_procedure("symbol?"    , is_symbol_proc);
    add_procedure("integer?"   , is_integer_proc);
    add_procedure("char?"      , is_char_proc);
    add_procedure("string?"    , is_string_proc);
    add_procedure("pair?"      , is_pair_proc);
    add_procedure("procedure?" , is_procedure_proc);
    
    add_procedure("char->integer" , char_to_integer_proc);
    add_procedure("integer->char" , integer_to_char_proc);
    add_procedure("number->string", number_to_string_proc);
    add_procedure("string->number", string_to_number_proc);
    add_procedure("symbol->string", symbol_to_string_proc);
    add_procedure("string->symbol", string_to_symbol_proc);
      
    add_procedure("+"        , add_proc);
    add_procedure("-"        , sub_proc);
    add_procedure("*"        , mul_proc);
    add_procedure("quotient" , quotient_proc);
    add_procedure("remainder", remainder_proc);
    add_procedure("="        , is_number_equal_proc);
    add_procedure("<"        , is_less_than_proc);
    add_procedure(">"        , is_greater_than_proc);

    add_procedure("cons"    , cons_proc);
    add_procedure("car"     , car_proc);
    add_procedure("cdr"     , cdr_proc);
    add_procedure("set-car!", set_car_proc);
    add_procedure("set-cdr!", set_cdr_proc);
    add_procedure("list"    , list_proc);

    add_procedure("eq?", is_eq_proc);
}
