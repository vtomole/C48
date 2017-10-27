//#include "parser.h"

//struct symbol{//typedef struct symbol???
//  char *name;
//  struct symbol *next;
//}symbol;

enum boolean {true, false};

typedef struct object{
  char* type;
  struct cons_cell{
    struct object *car;
    struct object *cdr;
  }cons_cell;
 
  char* variable;
  char *string;
  int number;
  enum boolean boolean;
}object;

object *create_object(char *value, char *type){
  object *obj = malloc(sizeof(obj));
  obj->type = type;
  obj->variable = value;
return obj;
}

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
object* car(object *cell){
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
object* cdr(object *cell){
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
object* create_number(char* number){
  struct object *object1;
  object *num = malloc(sizeof(*object1));
  num->type  ="number";
  int temp = atoi(number);
  num->number = temp;
  return num;
}

/**
 *This function creates an object representing a number
 * Parameters:
 * - number, the value of the object to create
 * Return Value:
 * - num an object with type number and value number
 */
object* create_string(char* string){
  struct object *object1;
  object *str = malloc(sizeof(*object1));
  str->type  ="string";
  str->string = string;
  return str;
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

object* create_boolean(char* variable){
  struct object *object1;
  object *var = malloc(sizeof(*object1));
  var->type = "boolean";
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


int count_objects(object* cursor){
  int c = 0;
  while(cursor != NULL){
    c++;
    cursor = cursor->cons_cell.cdr;
  }
  return c;
}


/**
 *Recursivly adds tokens to the code_tree
 * Parameters:
 * -token_list, the list of tokens to add to the code_tree
 * -code_tree, the code_tree being built
 */

//Will return object list
/*
 * this method recursivly goes through parse to create an unknown number of lists
 * by doing this each call to parse_rec should be a nested statement
 * each statement returns a list containing all the statements before a right or left paren
 * no seg_faults however the code isn't doing anything visible with the temp_list it creates and maintains.
**/
object* parse_rec(token_list* token_list, object* list_sofar){
  struct object *expr3;
  struct object *temp_list;

   while(token_list != NULL){
    if(strcmp(token_list->val.type,"right_paren")==0){
      //indicates the start of a new list
      expr3 = parse_rec(token_list->next, temp_list);
      temp_list = cons(expr3, temp_list);
    }else if(strcmp(token_list->val.type,"left_paren") == 0){
      //end of a list
      return temp_list;
    }else if(strcmp(token_list->val.type,"primitive")==0){
      //constructing an operator onto the list
      expr3 = create_primitiveop(token_list->val.value);
      temp_list = cons(expr3, temp_list); 
    }else if(strcmp(token_list->val.type,"num")==0){
      //constructing a number onto the list
      expr3 = create_number(token_list->val.value);
      temp_list = cons(expr3, temp_list);
    }else if(strcmp(token_list->val.type,"string")==0){
      //constructing a string onto the list
      expr3 = create_string(token_list->val.value);
      temp_list = cons(expr3, temp_list);     
    }else if(strcmp(token_list->val.type,"boolean")==0){
      //constructing a boolean onto the list
      expr3 = create_boolean(token_list->val.value);
      temp_list = cons(expr3, temp_list);      
    }else{
      printf("invalid token\n");
      exit(0);
    }
    token_list = token_list->next;
  }
   //throw an error no closed parenthesis
   printf("invalid syntax");
   exit(0);

}

object* parse(token_list* token_list, object* expr_list){
  struct object *expr2;

  //print_token_list(token_list);

   while(token_list != NULL){
    if(strcmp(token_list->val.type,"right_paren")==0){
      //indicates the start of a new list
      expr2 = parse_rec(token_list->next,expr_list);
      expr_list = cons(expr2, expr_list);
    }else if(strcmp(token_list->val.type,"left_paren") == 0){
      //end of a list
    }else if(strcmp(token_list->val.type,"primitive")==0){
      //constructing an operator onto the list
      expr2 = create_primitiveop(token_list->val.value);
      expr_list = cons(expr2, expr_list); 
    }
    else if(strcmp(token_list->val.type,"variable")==0){
      //constructing an operator onto the list
      expr2 = create_primitiveop(token_list->val.value);
      expr_list = cons(expr2, expr_list); 
    }
    else if(strcmp(token_list->val.type,"num")==0){
      //constructing a number onto the list
      expr2 = create_number(token_list->val.value);
      if(count_token_list(token_list) == 1){
	return expr2;
      }else{
	expr_list = cons(expr2, expr_list);
      }
    }else if(strcmp(token_list->val.type,"string")==0){
      //constructing a string onto the list
      expr2 = create_string(token_list->val.value);
      if(count_token_list(token_list) == 1){
	return expr2;
      }else{
	expr_list = cons(expr2, expr_list);
      }	 
    }else if(strcmp(token_list->val.type,"boolean")==0){
      //constructing a string onto the list
      expr2 = create_boolean(token_list->val.value);
      if(count_token_list(token_list) == 1){
	return expr2;
      }else{
	expr_list = cons(expr2, expr_list);
      }	 
    }else{
      printf("invalid token\n");
      exit(0);
    }
    token_list = token_list->next;
   }
   return expr_list;
}
