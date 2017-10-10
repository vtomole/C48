#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define NUM 0
#define VAR 1
#define OP 2
#define LIST 3
#define STR 4
#define FUNC



typedef struct object{
  int type;
  char *value;
  struct object *car;  //The list first object
  struct object *cdr;   //The objects next adjacent object
  
}object;

object *create_object(char *value, int type){
  object *obj = malloc(sizeof(obj));
  obj->value = value;
  obj->type = type;
  obj->car = NULL;
  obj->cdr = NULL;
  return obj;
}



object *cons(object *obj, object *list){
  assert(list->type == LIST);
  object *cons = malloc(sizeof(cons));
  cons->type = LIST;
  cons->car = obj;
  cons->cdr = list;
  return cons;
}

object *car(object *obj){
  assert(obj->type == LIST);
  return obj->car; 
}

object *cdr(object *obj){
  assert(obj->type == LIST);
  return obj->cdr; 
}



////// Printing Statements //////

char *get_list(object *obj){
  char *a, *b, *c;
  if(obj->type == OP){
    a = get_list(car(obj));
    b = get_list(cdr(obj));
    c = get_list(car(cdr(obj)));
    sprintf(a, "( %s %s %s)", a, b, c);
    return a;
  }

  return " ";
}






