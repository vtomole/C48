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

typedef enum {EMPTY_LIST, BOOLEAN, SYMBOL, FIXNUM, FLOAT,
              CHARACTER, STRING, PAIR, PRIMITIVE_PROC,
              COMPOUND_PROC} object_type;

typedef enum {MATH, EQUALITY, COMPARISON, CHAR, PREDICATE} primitive_type;

typedef struct object{  
  object_type obj_type;
  struct cons_cell{
    struct object *car;
    struct object *cdr;
  }cons_cell;
 
  char* symbol;
  char *string;
  char character;
  long number;
  //enum boolean empty_list;
  int boolean;
  double decimal;
  
  struct primitive_proc{
    struct object *(*fn)(struct object *arguments);
    primitive_type prim_type;
    struct object* acceptables;
  }primitive_proc;

  struct compound_proc {
    struct object *parameters;
    struct object *body;
    struct object *env;
  }compound_proc;
  
}object;

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

/*global variables*/
object *the_empty_list;
object *false;
object *true;
object *symbol_table;
object *quote_symbol;
object *define_symbol;
object *set_symbol;
object *setcar_symbol;
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

void  initialize_environment(void);
