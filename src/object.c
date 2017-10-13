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

int count_object(object *obj){
  int c = 0;
  printf("Starting count\n");
  while(obj != NULL){
    c++;
    printf("count: %d\n", c);
    obj = obj->cons_cell.cdr;
  }
  printf("Finished count\n");
  return c;
}

char *get_list(object *obj){
  char *str;
  
  if(obj->type == LIST){
    str = malloc(sizeof(char) * 100);
    object *a = car(obj);
    
    if(a->type == OP){
      object *b = car(cdr(obj));
      //object *c = car(cdr(cdr(obj)));
      //printf("got b and c\n");
      sprintf(str, "( %s)", a->value);//, get_list(b), get_list(c));
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



