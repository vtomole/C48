#include "environment.h" 
void print(object *obj);

/**count_objects()
 *This function is used to count the objects we have
 * Parameters:
 *-cursor, an object pointer used to deterimine our place in the list/tree
 * Returns:
 *-c, the count of objects we have
 */
int count_objects(object* cursor){
  int c = 0;
  while(cursor != NULL){
    c++;
    cursor = cursor->cons_cell.cdr;
  }
  return c;
}

/**Allocation
*This struct is used for our garbage collector to maintain a list of allocated blocks of memory
* Fields:
*-pair, the cons_Cell we are allocation memory to
*-mark, 1 if marked 0 if not marked, initialzed to 1
*-next, a pointer to the next place we allocated memory to
*/
struct Allocation {
	
         struct cons_cell pair;
	int mark : 1;
	struct Allocation *next;
};

/*list used for the garbage collector*/
struct Allocation *global_allocations = NULL;

/** alloc_object()
 *alloc_object is the function used to allocate memory upon the creation of an object
 *This should be the only place we call malloc
 * Returns:
 *-an object with a defined space in memory
 */
object* alloc_object(){
  object *obj;

  obj = malloc(sizeof(object));

  if(obj == NULL){
    fprintf(stderr, "out of memory\n");
    exit(1);
  }
  return obj;

}

/*global variables*/
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

/*function delcarations*/
object *cons(object *car, object *cdr);
object *car(object *pair);
object *cdr(object *pair);

//Boolean Functions
char is_the_empty_list(object *obj) { return obj == the_empty_list; }
char booleanp(object *obj) { return obj->obj_type == BOOLEAN; }
char is_false(object *obj) {return obj == false; }
char is_true(object *obj) { return !is_false(obj); }

/**make symbol()
 *this function is used to generate an object of type symbol i.e.
 * Parameters:
 *- *value, a char string that represents what symbol the object we are creating is
 * Returns:
 *- *obj, the newly created object with obj_type symbol
 */
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

/**make_fixnum()
   *this function is used to generate an object of type FIXNUM which we use as ints
   * Parameters:
   *-value, the actual numerical value of our fixnum object
   * Returns:
   *-obj, a newly created object pointer for our fixnum
   */
object *make_fixnum(long value) {
    object *obj;

    obj = alloc_object();
    obj->obj_type = FIXNUM;
    obj->number = value;
    return obj;
}

/**make float()
 *this function is used to generate an object of type float, i.e 2.1
 * Parameters:
 *- value, a double that represents what number the object we are creating is
 * Returns:
 *- *obj, the newly created object with obj_type float
 */
object *make_float(double value) {
    object *obj;

    obj = alloc_object();
    obj->obj_type = FLOAT;
    obj->decimal = value;
    return obj;
}

/**make_character()
 * this function is used to generate an object of type char i.e. 'a', '4' etc.
 * Parameters:
 *-value, the given charater our char object represents
 * Returns:
 *-obj, a newly created object pointer for our character
 */
object *make_character(char value) {
    object *obj;

    obj = alloc_object();
    obj->obj_type = CHARACTER;
    obj->character = value;
    return obj;
}

/**make_string()
 *this function is used to generate an object of type String
 * Parameters:
 *-value, the string of our new object
 * Returns:
 *-obj, a newly created object pointer for our string
 */
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

char is_symbol(object *obj) { return obj->obj_type == SYMBOL; }
char numberp(object *obj) { return obj->obj_type == FIXNUM; }
char floatp(object *obj) { return obj->obj_type == FLOAT; }
char characterp(object *obj) {return obj->obj_type == CHARACTER;}
char is_string(object *obj) { return obj->obj_type == STRING; }
char is_pair(object *obj) { return obj->obj_type == PAIR; }

/**cons()
 *This function is used to cons the given objects onto our list 
 *This function is one of two functions that should be allowed to call malloc
 * Parameters:
 *-car, the first object in the list
 *-cdr, the rest of the list
 * returns:
 *-obj, the list with the two given arguments cons' onto it
 */
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

//car/cdr get/set methods
object *car(object *pair) { return pair->cons_cell.car; }
object *cdr(object *pair) { return pair->cons_cell.cdr; }
void set_car(object *obj, object* value) { obj->cons_cell.car = value; }
void set_cdr(object *obj, object* value) {obj->cons_cell.cdr = value; }

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

/**char_to_enum()
 * this function is used determine the enumuration of the sent in char pointer
 * Parameters:
 *-proc, the character we are evaluating
 * Returns:
 *-returns the primitive_type either a MATH function or a Char function
 */
primitive_type char_to_enum(char* proc){
  if(strcmp(proc, "+") == 0 || 
     strcmp(proc, "-") == 0 ||
     strcmp(proc, "*") == 0 ||
     strcmp(proc, "/") == 0 ||
     strcmp(proc, "%") == 0){
    return MATH;
  }else if(strcmp(proc, "<>") == 0 ||
           strcmp(proc, "==") == 0){   
     return EQUALITY;
  }else if(strcmp(proc, ">")  == 0 || 
           strcmp(proc, "<")  == 0 ||
	   strcmp(proc, ">=") == 0 ||
           strcmp(proc, "<=") == 0){
    return COMPARISON;
  }else{
    return CHAR;
  }
}

/**set_acceptables()
 *this function is used to determine the acceptable types for an operator in our typechecker
 * Parameters:
 *-obj, the object that we are setting acceptables for
 * -prim_type si the enumartion used to determine what type the object is.
 * Returns:
 *-obj, the object is returned with an updated acceptables field, based on prim_type
 */
object *set_acceptable(object *obj, primitive_type prim_type){
  switch (prim_type){
  case 0:
    obj->primitive_proc.acceptables = cons(make_fixnum(FIXNUM), (cons (make_fixnum(FLOAT), the_empty_list)));
    //print(obj->primitive_proc.acceptables);
    break;
  case 1:
    obj->primitive_proc.acceptables = cons(make_fixnum(FIXNUM), cons (make_fixnum(FLOAT), cons (make_fixnum(CHARACTER), cons (make_fixnum(STRING), the_empty_list))));
    //print(obj->primitive_proc.acceptables);
    break;
  case 2:
    obj->primitive_proc.acceptables = cons(make_fixnum(FIXNUM), cons (make_fixnum(FLOAT), cons (make_fixnum(CHARACTER), cons (make_fixnum(STRING), cons (make_fixnum(BOOLEAN), the_empty_list)))));
    //print(obj->primitive_proc.acceptables);
    break;
  case 3:
    obj->primitive_proc.acceptables = cons(make_fixnum(CHARACTER),  the_empty_list);
    break;
  default:
    //printf("This should not happen after PLUS\n");
    obj->primitive_proc.acceptables = the_empty_list;
    
  }
  return obj;
}

/**make_primitive_proc()
 * is used to assign the primitive type to an object as well as updating the objects acceptables list by calling set_acceptables
 * Parameters:
 *-arguments, an object function pointer containing the nessecary elements to determin the primitive procedure
 *-proc, the char string representing the actual primitive procedure, i.e. +, char, etc.
 * Returns:
 *-obj, a newly created object that has a proper type and acceptables list
 */
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

char primitivep(object *obj) { return obj->obj_type == PRIMITIVE_PROC; }

/**is_foo_proc()
 *the following functions are used to determine which procedure the given arguements are
 * Parameters:
 *-arguments, an object pointer that we are trying to determine the type of procdeure it is
 * Returns:
 *-true, if the argument is the named procedure
 *-false, otherwise
 */
object *is_null_proc(object *arguments)    { return is_the_empty_list(car(arguments)) ? true : false; }
object *is_boolean_proc(object *arguments) { return booleanp(car(arguments)) ? true : false; }
object *is_symbol_proc(object *arguments)  { return is_symbol(car(arguments)) ? true : false; }
object *is_integer_proc(object *arguments) { return numberp(car(arguments)) ? true : false; }
object *is_char_proc(object *arguments)    { return characterp(car(arguments)) ? true : false; }
object *is_string_proc(object *arguments)  { return is_string(car(arguments)) ? true : false; }
object *is_pair_proc(object *arguments)    { return is_pair(car(arguments)) ? true : false; }
char is_compound_proc(object *obj);

/**is_procedure_proc()
 *this function is used to determine whether the given procedure is a primitive or compound procedure
 * Parameters:
 *-arguments, the object that we are trying to determine the type of procedure from
 * Returns:
 *-true if primitive,
 *-false if compound
 */
object *is_procedure_proc(object *arguments) {
    object *obj;
    
    obj = car(arguments);
    return (primitivep(obj) ||
            is_compound_proc(obj)) ?
                true :
                false;
}
/* end of procedure determining functions*/ 

/**foo_to_bar()
 *The below functions are used to convert objects from one object type to another they all follow the same format
 * Parameters:
 *-arguments, the object that we are converting to a new type
 * Returns:
 *-the given object with an updated type
 */
object *char_to_integer_proc(object *arguments) { return make_fixnum((car(arguments))->character); }
object *integer_to_char_proc(object *arguments) { return make_character((car(arguments))->number); }
object *number_to_string_proc(object *arguments) {
    char buffer[100];

    sprintf(buffer, "%ld", (car(arguments))->number);
    return make_string(buffer);
}
object *string_to_number_proc(object *arguments) { return make_fixnum(atoi((car(arguments))->string)); }
object *symbol_to_string_proc(object *arguments) { return make_string((car(arguments))->symbol); }
object *string_to_symbol_proc(object *arguments) { return make_symbol((car(arguments))->string); }
/* end of conversion functions*/

/**add_proc()
 *This function is used to actually preform the named calculation
 *used for additionn
 * Parameters:
 *-arguements, the actual list of arguements for the procedure
 * Returns:
 *-a new fixnum object with the correct value of the operation performed on the given operands
 */
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

/**sub_proc()
 *this function is used to actually preform the named calculation
 *used for subtraction
 * Parameters:
 *-arguements, the actual list of arguements for the procedure
 * Returns:
 *-a new fixnum object with the correct value of the operation performed on the given operands
 */
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

/**mul_proc()
 *this function is used to actually preform the named calculation
 *used for multiplication
 * Parameters:
 *-arguements, the actual list of arguements for the procedure
 * Returns:
 *-a new fixnum object with the correct value of the operation performed on the given operands
 */
object *mul_proc(object *arguments) {
    long result = 1;
    double resultf = 1;
    
    if(car(arguments)->obj_type == FIXNUM){
	    while (!is_the_empty_list(arguments)) {
		result *= (car(arguments))->number;
		arguments = cdr(arguments);
	    }
	    return make_fixnum(result);
    }
    else if(car(arguments)->obj_type == FLOAT){
	    while (!is_the_empty_list(arguments)) {
		resultf *= (car(arguments))->decimal;
		arguments = cdr(arguments);
	    }
	    return make_float(resultf);
    }
}

/**quotient_proc
 *this function is used to actually preform the named calculation
 *used for division
 *assumes that all 0's will be found at compile time
 * Parameters:
 *-arguements, the actual list of arguements for the procedure
 * Returns:
 *-a new fixnum object with the correct value of the operation performed on the given operands
 */
object *quotient_proc(object *arguments) {
    long result = 0;
    double resultf = 0;
    
    if(car(arguments)->obj_type == FIXNUM){
	    result += (car(arguments))->number;
	    arguments = cdr(arguments);

	    while (!is_the_empty_list(arguments)) {
		result /= (car(arguments))->number;
		arguments = cdr(arguments);
	    }
	    return make_fixnum(result);
    }
    else if(car(arguments)->obj_type == FLOAT){
	    resultf += (car(arguments))->decimal;
	    arguments = cdr(arguments);

	    while (!is_the_empty_list(arguments)) {
		resultf /= (car(arguments))->decimal;
		arguments = cdr(arguments);
	    }
	    return make_float(resultf);
    }
}

/**remainder_proc() 
 *this function is used to actually preform the named calculation
 *used for the modulo operation(a.k.a remainder)
 * Parameters:
 *-arguements, the actual list of arguements for the procedure
 * Returns:
 *-a new fixnum object with the correct value of the operation performed on the given operands
 */
object *remainder_proc(object *arguments) {
    long result = 0;
    double resultf = 0;
    
    if(car(arguments)->obj_type == FIXNUM){
	    result += (car(arguments))->number;
	    arguments = cdr(arguments);

	    while (!is_the_empty_list(arguments)) {
		result %= (car(arguments))->number;
		arguments = cdr(arguments);
	    }
	    return make_fixnum(result);
    }
}

/**is_number_equal_proc()
 *This function is used to check equivalence between the given arguments this is used exclusivly for numbers
 *and operates differently than the is_eq_proq function defined below
 * Parameters:
 *-arguements, the actual list of arguements for the procedure
 * Returns:
 *-a new fixnum object with the correct value of the operation performed on the given operands
 */
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

/**is_less_than_proc()
 *This function is used to check if the first or prior argument(s) is less than the second or later argument(s)
 * Parameters:
 *-arguements, the actual list of arguements for the procedure
 * Returns:
 *-a new fixnum object with the correct value of the operation performed on the given operands
 */
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

/**is_greater_than_proc()
 *This function is used to check if the first or prior argument(s) is greater than the seconde or later argument(s)
 * Parameters:
 *-arguements, the actual list of arguements for the procedure
 * Returns:
 *-a new fixnum object with the correct value of the operation performed on the given operands
 */
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

/**foo_proc()
 *these 3 are functions are used by eval to get the arguements of a procedure
 *removes the first car/cdr 
 *this function represents the actual car/cdr procedures on the back end as well
 * Parameters:
 *-arguements, a list of objects to cons/evaluate in other functions
 * Returns:
 * the next objects in the given arguments
 */
object *cons_proc(object *arguments) { return cons(car(arguments), cadr(arguments)); }
object *car_proc(object *arguments) { return caar(arguments); }
object *cdr_proc(object *arguments) {return cdar(arguments);}

/**set_car()/set_cdr()
 *These two functions are used to allow the user, to call the set_car and set_cdr functions
 * Parameters:
 *-arguments the object we are assigning to car/cdr
 * Returns:
 *-ok_symbol, an object to display the proper completion of the functions
 */
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

object *greater_than_proc(object *arguments) {
    long previousNum;
    long nextNum;
    double previousFloat;
    double nextFloat;
    char previousChar;
    char nextChar;
    char* previousString;
    char* nextString;
    int previousBool;
    int nextBool;

    switch (car(arguments)->obj_type) {
        case FIXNUM:	    
	    previousNum = (car(arguments))->number;
	    while (!is_the_empty_list(arguments = cdr(arguments))) {
		nextNum = (car(arguments))->number;
		if (previousNum > nextNum) {
		    previousNum = nextNum;
		}
		else {
		    return false;
		}
	    }
	    return true;
            break;
	case FLOAT:
	    previousFloat = (car(arguments))->decimal;
	    while (!is_the_empty_list(arguments = cdr(arguments))) {
		nextFloat = (car(arguments))->decimal;
		if (previousFloat > nextFloat) {
		    previousFloat = nextFloat;
		}
		else {
		    return false;
		}
	    }
	    return true;
            break;
        case CHARACTER:    
	    previousChar = (car(arguments))->character;
	    while (!is_the_empty_list(arguments = cdr(arguments))) {
		nextChar = (car(arguments))->character;
		if (previousChar > nextChar) {
		    previousChar = nextChar;
		}
		else {
		    return false;
		}
	    }
	    return true;
            break;
        case STRING:	    
	    previousString = (car(arguments))->string;
	    while (!is_the_empty_list(arguments = cdr(arguments))) {
		nextString = (car(arguments))->string;
		if (strcmp(previousString, 
                           nextString) > 0) {
		    previousString = nextString;
		}
		else {
		    return false;
		}
	    }
	    return true;
            break;
        default:
            return (car(arguments) > cadr(arguments)) ? true : false;
    }
}

object *less_than_proc(object *arguments) {
    long previousNum;
    long nextNum;
    double previousFloat;
    double nextFloat;
    char previousChar;
    char nextChar;
    char* previousString;
    char* nextString;
    int previousBool;
    int nextBool;

    switch (car(arguments)->obj_type) {
        case FIXNUM:	    
	    previousNum = (car(arguments))->number;
	    while (!is_the_empty_list(arguments = cdr(arguments))) {
		nextNum = (car(arguments))->number;
		if (previousNum < nextNum) {
		    previousNum = nextNum;
		}
		else {
		    return false;
		}
	    }
	    return true;
            break;
	case FLOAT:
	    previousFloat = (car(arguments))->decimal;
	    while (!is_the_empty_list(arguments = cdr(arguments))) {
		nextFloat = (car(arguments))->decimal;
		if (previousFloat < nextFloat) {
		    previousFloat = nextFloat;
		}
		else {
		    return false;
		}
	    }
	    return true;
            break;
        case CHARACTER:    
	    previousChar = (car(arguments))->character;
	    while (!is_the_empty_list(arguments = cdr(arguments))) {
		nextChar = (car(arguments))->character;
		if (previousChar < nextChar) {
		    previousChar = nextChar;
		}
		else {
		    return false;
		}
	    }
	    return true;
            break;
        case STRING:	    
	    previousString = (car(arguments))->string;
	    while (!is_the_empty_list(arguments = cdr(arguments))) {
		nextString = (car(arguments))->string;
		if (strcmp(previousString, 
                           nextString) < 0) {
		    previousString = nextString;
		}
		else {
		    return false;
		}
	    }
	    return true;
            break;
        default:
            return (car(arguments) < cadr(arguments)) ? true : false;
    }
}

object *not_equal_to_proc(object *arguments) {
    long previousNum;
    long nextNum;
    double previousFloat;
    double nextFloat;
    char previousChar;
    char nextChar;
    char* previousString;
    char* nextString;
    int previousBool;
    int nextBool;

    switch (car(arguments)->obj_type) {
        case FIXNUM:	    
	    previousNum = (car(arguments))->number;
	    while (!is_the_empty_list(arguments = cdr(arguments))) {
		nextNum = (car(arguments))->number;
		if (previousNum != nextNum) {
		    previousNum = nextNum;
		}
		else {
		    return false;
		}
	    }
	    return true;
            break;
	case FLOAT:
	    previousFloat = (car(arguments))->decimal;
	    while (!is_the_empty_list(arguments = cdr(arguments))) {
		nextFloat = (car(arguments))->decimal;
		if (previousFloat != nextFloat) {
		    previousFloat = nextFloat;
		}
		else {
		    return false;
		}
	    }
	    return true;
            break;
        case CHARACTER:    
	    previousChar = (car(arguments))->character;
	    while (!is_the_empty_list(arguments = cdr(arguments))) {
		nextChar = (car(arguments))->character;
		if (previousChar != nextChar) {
		    previousChar = nextChar;
		}
		else {
		    return false;
		}
	    }
	    return true;
            break;
        case STRING:	    
	    previousString = (car(arguments))->string;
	    while (!is_the_empty_list(arguments = cdr(arguments))) {
		nextString = (car(arguments))->string;
		if (strcmp(previousString, 
                           nextString) != 0) {
		    previousString = nextString;
		}
		else {
		    return false;
		}
	    }
	    return true;
            break;
	case BOOLEAN:	    
	    previousBool = (car(arguments))->boolean;
	    while (!is_the_empty_list(arguments = cdr(arguments))) {
		nextBool = (car(arguments))->boolean;
		if (previousBool != nextBool) {
		    previousBool = nextBool;
		}
		else {
		    return false;
		}
	    }
	    return true;
            break;
        default:
            return (car(arguments) != cadr(arguments)) ? true : false;
    }
}

object *equal_to_proc(object *arguments) {
    long previousNum;
    long nextNum;
    double previousFloat;
    double nextFloat;
    char previousChar;
    char nextChar;
    char* previousString;
    char* nextString;
    int previousBool;
    int nextBool;

    switch (car(arguments)->obj_type) {
        case FIXNUM:	    
	    previousNum = (car(arguments))->number;
	    while (!is_the_empty_list(arguments = cdr(arguments))) {
		nextNum = (car(arguments))->number;
		if (previousNum == nextNum) {
		    previousNum = nextNum;
		}
		else {
		    return false;
		}
	    }
	    return true;
            break;
	case FLOAT:
	    previousFloat = (car(arguments))->decimal;
	    while (!is_the_empty_list(arguments = cdr(arguments))) {
		nextFloat = (car(arguments))->decimal;
		if (previousFloat == nextFloat) {
		    previousFloat = nextFloat;
		}
		else {
		    return false;
		}
	    }
	    return true;
            break;
        case CHARACTER:    
	    previousChar = (car(arguments))->character;
	    while (!is_the_empty_list(arguments = cdr(arguments))) {
		nextChar = (car(arguments))->character;
		if (previousChar == nextChar) {
		    previousChar = nextChar;
		}
		else {
		    return false;
		}
	    }
	    return true;
            break;
        case STRING:	    
	    previousString = (car(arguments))->string;
	    while (!is_the_empty_list(arguments = cdr(arguments))) {
		nextString = (car(arguments))->string;
		if (strcmp(previousString, 
                           nextString) == 0) {
		    previousString = nextString;
		}
		else {
		    return false;
		}
	    }
	    return true;
            break;
	case BOOLEAN:	    
	    previousBool = (car(arguments))->boolean;
	    while (!is_the_empty_list(arguments = cdr(arguments))) {
		nextBool = (car(arguments))->boolean;
		if (previousBool == nextBool) {
		    previousBool = nextBool;
		}
		else {
		    return false;
		}
	    }
	    return true;
            break;
        default:
            return (car(arguments) == cadr(arguments)) ? true : false;
    }
}

object *greater_or_equal_to_proc(object *arguments) {
    long previousNum;
    long nextNum;
    double previousFloat;
    double nextFloat;
    char previousChar;
    char nextChar;
    char* previousString;
    char* nextString;
    int previousBool;
    int nextBool;

    switch (car(arguments)->obj_type) {
        case FIXNUM:	    
	    previousNum = (car(arguments))->number;
	    while (!is_the_empty_list(arguments = cdr(arguments))) {
		nextNum = (car(arguments))->number;
		if (previousNum >= nextNum) {
		    previousNum = nextNum;
		}
		else {
		    return false;
		}
	    }
	    return true;
            break;
	case FLOAT:
	    previousFloat = (car(arguments))->decimal;
	    while (!is_the_empty_list(arguments = cdr(arguments))) {
		nextFloat = (car(arguments))->decimal;
		if (previousFloat >= nextFloat) {
		    previousFloat = nextFloat;
		}
		else {
		    return false;
		}
	    }
	    return true;
            break;
        case CHARACTER:    
	    previousChar = (car(arguments))->character;
	    while (!is_the_empty_list(arguments = cdr(arguments))) {
		nextChar = (car(arguments))->character;
		if (previousChar >= nextChar) {
		    previousChar = nextChar;
		}
		else {
		    return false;
		}
	    }
	    return true;
            break;
        case STRING:	    
	    previousString = (car(arguments))->string;
	    while (!is_the_empty_list(arguments = cdr(arguments))) {
		nextString = (car(arguments))->string;
		if (strcmp(previousString, 
                           nextString) != 0) {
		    previousString = nextString;
		}
		else {
		    return false;
		}
	    }
	    return true;
            break;
        default:
            return (car(arguments) >= cadr(arguments)) ? true : false;
    }
}

object *less_or_equal_to_proc(object *arguments) {
    long previousNum;
    long nextNum;
    double previousFloat;
    double nextFloat;
    char previousChar;
    char nextChar;
    char* previousString;
    char* nextString;
    int previousBool;
    int nextBool;

    switch (car(arguments)->obj_type) {
        case FIXNUM:	    
	    previousNum = (car(arguments))->number;
	    while (!is_the_empty_list(arguments = cdr(arguments))) {
		nextNum = (car(arguments))->number;
		if (previousNum <= nextNum) {
		    previousNum = nextNum;
		}
		else {
		    return false;
		}
	    }
	    return true;
            break;
	case FLOAT:
	    previousFloat = (car(arguments))->decimal;
	    while (!is_the_empty_list(arguments = cdr(arguments))) {
		nextFloat = (car(arguments))->decimal;
		if (previousFloat <= nextFloat) {
		    previousFloat = nextFloat;
		}
		else {
		    return false;
		}
	    }
	    return true;
            break;
        case CHARACTER:    
	    previousChar = (car(arguments))->character;
	    while (!is_the_empty_list(arguments = cdr(arguments))) {
		nextChar = (car(arguments))->character;
		if (previousChar <= nextChar) {
		    previousChar = nextChar;
		}
		else {
		    return false;
		}
	    }
	    return true;
            break;
        case STRING:	    
	    previousString = (car(arguments))->string;
	    while (!is_the_empty_list(arguments = cdr(arguments))) {
		nextString = (car(arguments))->string;
		if (strcmp(previousString, 
                           nextString) <= 0) {
		    previousString = nextString;
		}
		else {
		    return false;
		}
	    }
	    return true;
            break;
        default:
            return (car(arguments) <= cadr(arguments)) ? true : false;
    }
}

/**is_eq_proc()
 *this function is used to determine whether two arguments are equivalent
 * Parameters:
 *-arguements, the actual list of arguements for the procedure
 * Returns:
 *-a new fixnum object with the correct value of the operation performed on the given operands
 */
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
	case FLOAT:
            return (obj1->decimal == 
                    obj2->decimal) ?
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
	case BOOLEAN:
            return (obj1->boolean ==
                    obj2->boolean) ?
                        true : false;
            break;
        default:
            return (obj1 == obj2) ? true : false;
    }
}

/**make_compound_proc()
 *this function is used to make a compound procedure
 *a compound procedure is a user defined function such as factorial where the user creates and defines how the procedure will work
 * Parameters: 
 *-parameters,the nessecary paramters as defined in our struct object
 *-body, the actual compound procedure we are creating 
 *-env, the environment we are using this procedure in
 * Returns:
 *-a new object representing the compound procedure
 */
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

object *list_proc(object *arguments) { return arguments; }
char is_compound_proc(object *obj) { return obj->obj_type == COMPOUND_PROC; }

//Environment functions
object *enclosing_environment(object *env) { return cdr(env); }
object *first_frame(object *env) { return car(env); }
object *make_frame(object *variables, object *values) { return cons(variables, values); }
object *frame_variables(object *frame) { return car(frame); }
object *frame_values(object *frame) { return cdr(frame); }

/**add_binding_to_frame()
 *Allows the user to make local variables
 * Parameters:
 *-var, is the variable you are creating
 *-val, is the value of the created variable
 *-frame, the frame of the environment this variable will be on
 */
void add_binding_to_frame(object *var, object *val, 
                          object *frame) {
    set_car(frame, cons(var, car(frame)));
    set_cdr(frame, cons(val, cdr(frame)));
}

/**extend_environment()
 *This function is used to make mor frames for the given environment
 * Parameters:
 *-vars, the variables we are extending
 *-vals, the values of the variables we are extending
 *-base_env, the environment we are adding frames to
 */
object *extend_environment(object *vars, object *vals, object *base_env) { return cons(make_frame(vars, vals), base_env);}

/**lookup_variable_value()
 *This function is used to lookup a variable from our environment
 * Parameters:
 *-var, the variable we are looking for
 *-env, the environment we are searching through
 */
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
    fprintf(stderr, "unbound variable (value)\n");
    exit(1);
}

/**lookup_variable_type()
 *This function is used to update a given variable
 * Parameters:
 *-var, the variable we are updating
 *-val, the value we are changing the variable to
 *-env, the environment of the variable
 */
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
    fprintf(stderr, "unbound variable (type)\n");
    exit(1);
}

/**set_variable_value()
 *This function is used to update a given variable
 * Parameters:
 *-var, the variable we are updating
 *-val, the value we are changing the variable to
 *-env, the environment of the variable
 */
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
    fprintf(stderr, "unbound variable (set)\n");
    exit(1);
}

/**define_variable()
 *This function is used to define a variable for the user, and is what calls the creation function described above
 * Parameters:
 *-var, the variable(s) we are defining
 *-val, the value(s) we are using when defining var
 *-env, the environment the variable(s) will be bound to
 */
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

/**setup_environment()
 *This function is used to initilize an environment, it is what makes sure the lists of contained memory and variables are cleared
 * Returns:
 *-an object pointer with the new environment
 */
object *setup_environment(void) {
    object *initial_env;
    
    initial_env = extend_environment(
                      the_empty_list,
                      the_empty_list,
                      the_empty_environment);
    return initial_env;
}

/**init()
 *this function intializes all our procedures, environments, symbols, etc.
 */
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
    add_procedure("/"        , quotient_proc);
    add_procedure("%"        , remainder_proc);

    add_procedure("="        , is_number_equal_proc);

    add_procedure(">"        , greater_than_proc);
    add_procedure("<"        , less_than_proc);
    add_procedure("<>"	     , not_equal_to_proc);
    add_procedure("=="	     , equal_to_proc);
    add_procedure(">="	     , greater_or_equal_to_proc);
    add_procedure("<="	     , less_or_equal_to_proc);

    add_procedure("cons"    , cons_proc);
    add_procedure("car"     , car_proc);
    add_procedure("cdr"     , cdr_proc);
    add_procedure("set-car!", set_car_proc);
    add_procedure("set-cdr!", set_cdr_proc);
    add_procedure("list"    , list_proc);

    //add_procedure("eq?", is_eq_proc);
}
