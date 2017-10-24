#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define EMPTY -1
#define NUM 0
#define VAR 1
#define OP 2
#define LIST 3
#define CCOND 4
#define NOT 5
#define BCOND 6
#define VAREXPR 7
#define FUNCEXPR 8
#define FUNC 9
#define FUNCAPPLY 10

typedef struct object object;

object* create_object(char* value, int type);

object* cons(object *car, object *cdr);

object *car(object *cell);

object *cdr(object *cell);
  
void count_list(object *obj, char *name);



