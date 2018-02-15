typedef enum {EMPTY_LIST, BOOLEAN, SYMBOL, NUMBER,
              CHARACTER, STRING, PAIR, PRIMITIVE_PROCEDURE,
              COMPOUND_PROCEDURE} object_type;



enum boolean{true, false};
typedef struct object{
  
  object_type obj_type;
  struct cons_cell{
    struct object *car;
    struct object *cdr;
  }cons_cell;
 
  char* symbol;
  char *string;
  char character;
  int number;
  enum boolean empty_list;
  enum boolean boolean;

  struct{
    /*fn is a pointer to stuct arguments*/
    struct object *(*fn)(struct object *arguments);
  }primitive_procedure;

  struct{
    struct object *parameters;
    struct object *body;
    struct object *env;
  }compound_procedure;
  
}object;

object *empty_list;
object *quote_symbol;
object *set_symbol;
object *ok_symbol;
object *define_symbol;
object *if_symbol;
object *false_symbol;
object *true_symbol;
object *begin_symbol;
object *lambda_symbol;
object *cond_symbol;
object *else_symbol;
object *symbol_table;
object *empty_environment;
object *the_global_environment;
object *environment;

object* cons(object *car, object *cdr);
void  initialize_environment(void);
