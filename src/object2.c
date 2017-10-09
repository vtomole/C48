#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define NUM 0
#define VAR 1
#define OP 2
#define LIST 3

char *get_car(object *);
char *get_cdr(object *);

typedef struct object{
  int type;
  char *value;
  struct object *first;  //The list first object
  struct object *next;   //The objects next adjacent object
  
}object;

object *create_object(char *value, int type){
  object *obj = malloc(sizeof(obj));
  obj->value = value;
  obj->type = type;
  obj->first = NULL;
  obj->next = NULL;
  return obj;
}

object *copy(object *obj){
/**  
  object *copy = malloc(sizeof(copy));
  copy->type = obj->type;
  if(obj->type == LIST){
    copy->first = copy(obj->first);
  }
  else{
    
  }
**/
}

object *init_list(object *obj){
  object *list = malloc(sizeof(list));
  list->first = obj;
  list->type = LIST;
  return list;
}

object *cons(object *obj, object *list){
  assert(list->type == LIST);
  obj->next = list->first;
  list->first = obj;
  return list;
}

object *car(object *list){
  assert(list->type == LIST);
  return list->first;
}

object *cdr(object *list){
  assert(list->type == LIST);
  list->cur = list->cur->next;
  return list;
}


////// Printing Statements //////

char *get_list(object *list){
  char *a = malloc(sizeof(char) * 100);
  sprintf(a, "( %s %s)", get_car(list), get_cdr(list));
	return a;
}

//char *get_next(object *obj){  
//}

char *get_car(object *list){
  assert(list->type == LIST);
  object *first = list->first;
  if(first->type == LIST){
    char *a = malloc(sizeof(char) * 100);
    sprintf(a, " %s %s", get_car(list), get_cdr(list));
  }
  else{
    return first->value;
  }
}

char *get_cdr(object *list){
  
}






