#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define EMPTY -1
#define NUM 0
#define VAR 1
#define OP 2
#define LIST 3

typedef struct object{
  int type;
  char *value;
  
  struct object *car;
  struct object *cdr;
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
  obj->car = car;
  obj->cdr = cdr;

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
  return cell->car;
}

/**
 *This function checks that the cells cdr is ???
 * Parameters:
 * - cell
 * Return Value:
 * - ???
 */
object* cdr(object *cell){
  return cell->cdr;
}

char *get_list(object *obj){
  char *str;
  
  //printf("%d car(obj): %s\n", (car(obj))->type, (car(obj))->value);
  //printf("%d car(cdr(obj)): %s\n", (car(cdr(obj)))->type, (car(cdr(obj)))->value);
  
  if(obj->type == LIST){
    str = malloc(sizeof(char) * 100);
    object *a = car(obj);
    
    if(a->type == OP){
      object *b = car(cdr(obj));
      object *c = car(cdr(cdr(obj)));
      printf("got b and c\n");
      sprintf(str, "( %s %s %s)", a->value, get_list(b), get_list(c));
      return str;
    }
    else{
      printf("empty list? -> %d\n", obj->type == EMPTY);
      return "";
    }
  }
  else{
    printf("Not a list: %s\n", obj->value);
    return obj->value;;
  }
  
  return "";
}



