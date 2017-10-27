#include "object.h"

enum boolean {true, false};

typedef struct object{
  int type;
  char* value;
  struct cons_cell{
    struct object *car;
    struct object *cdr;
  }cons_cell;
 
  char* variable;
  char* string;
  int number;
  enum boolean boolean;
}object;

/**
 *This function creates an object 
 * Parameters:
 * - value, the value of the object to create
 * Return Value:
 * - An object with type enum and char value
 */
object* create_object(char* value, int type){
  object* obj = (object*)malloc(sizeof(object));
  if(obj == NULL){
    printf("Obj is NULL\n");
  }
  obj->value = value;
  obj->type = type;
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
  object *obj = (object*)malloc(sizeof(object));
  if(obj == NULL){
    printf("is NULL\n");
    return NULL;
  }
  obj->type = LIST;
  obj->cons_cell.car = car;
  obj->cons_cell.cdr = cdr;
  return obj;
}

/**
 *This function checks if the cells car is ???
 * Parameters:
 * - cell, an object ???
 * Return Value:
 * - ???
 */
object *car(object *cell){
  return cell->cons_cell.car;
}

/**
 *This function checks that the cells cdr is ???
 * Parameters:
 * - cell
 * Return Value:
 * - ???
 */
object *cdr(object *cell){
  return cell->cons_cell.cdr;
}
  
void count_list(object *obj, char *name){
  int count = 0;
  object *temp = obj;
  while(temp != NULL){
    count++;
    temp = temp->cons_cell.cdr;
  }
  printf("%s is size of %d\n", name, count);
}


