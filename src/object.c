#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define NUM 0
#define VAR 1
#define OP 2
#define LIST 3

typedef struct object{
  int type;
  char *value;
  
  struct cons_cell{
    struct object *car;
    struct object *cdr;
  }cons_cell;
}object;


/**
 *This function creates an object 
 * Parameters:
 * - value, the value of the object to create
 * Return Value:
 * - An object with type enum and char value
 */
object* create_object(char* value, int type){
  object *obj = malloc(sizeof(obj));
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
  object *obj = malloc(sizeof(obj));
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
object* car(object *cell){
  assert (cell->type == LIST);
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
  assert (cell->type == LIST);
  return cell->cons_cell.cdr;
}

char *get_list(object *obj){
  char *c;
  
  if(obj->type == LIST){
    c = malloc(sizeof(char) * 100);
    
    object *a = car(obj);
    object *b = cdr(obj);
    
    char *x = get_list(a);
    printf("b is null: %d\n", b == NULL);
    printf("b has type NUM: %d\n", b->type == NUM);
    printf("b has type OP: %d\n", b->type == OP);
    printf("b has type LIST: %d\n", b->type == LIST);
    printf("b has type VAR: %d\n", b->type == VAR);
    
    char *y = get_list(b);
    
    sprintf(c, "%s %s", x, y);
    if(a->type == OP){
      sprintf(c, "( %s)", c);
    }
    return c;
  }
  else{
    c = obj->value;
    return c;
  }
  
}
