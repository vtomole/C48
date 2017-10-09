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
  struct object *first;  //The list first object
  struct object *next;   //The objects next adjacent object
}object;

object *create_object(char *value, int type){
  object *obj = malloc(sizeof(obj));
  obj->value = value;
  obj->type = type;
  return obj;
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
  printf("obj->next: %s\n", obj->next->value);
  printf("list->first: %s\n", list->first->value);
  return list;
}

object *car(object *list){
  assert(list->type == LIST);
  return list->first;
}

object *cdr(object *list){
  assert(list->type == LIST);
  return list->first->next;
}

char *get_list(object *list, int count){
  char *a, *b, *c;
  if(list == NULL){
    printf("%d\n", count);
    return "";
  }
  else if(list->type == LIST){
    printf("%d\n", count++);
    a = get_list(car(list), count);
    b = get_list(cdr(list), count);
    c = (char*)malloc(sizeof(char)*100);
    sprintf(c, "( %s %s)", a, b);
    return c;
  }
  else{
    c = (char*)malloc(sizeof(char)*100);
    sprintf(c,"%s %s", list->value, get_list(list->next, count++));
    return c;
  }
}



// struct *cons_list;

// /**
//  * struct symbol{//typedef struct symbol???
//  *  char *name;
//  *  struct symbol *next;
//  *}symbol;
//  */

// typedef struct object{
//   int type;
//   struct cons_list *list;
 
//   char* variable;
//   char *string;
//   int number;
// }object;

// typedef cons_list{
//   object *car;
//   cons_list *cdr;
// }cons_list;

// /**
//  *This function constructs ????
//  * Parameters:
//  * - car, the first object in the code tree
//  * - cdr, the rest of the objects in the code tree
//  * Return Value:
//  * - test1, an object ???
//  */
// object* cons_objs(object *car, object *cdr){
//   // struct object *object1;
//   object *list = malloc(sizeof(list));

//   list->type = LIST;
//   list->cons_cell.car = car;
//   if(cdr->type == LIST){
//     cdr = cdr->cons_cell.car;
//   }
//   list->cons_cell.cdr = cdr;

//   return list;
// }

// /**
//  *This function checks if the cells car is ???
//  * Parameters:
//  * - cell, an object ???
//  * Return Value:
//  * - ???
//  */
// object* car1(object *cell){
//   assert (cell->type == LIST);
//   return cell->cons_cell.car;
// }

// /**
//  *This function checks that the cells cdr is ???
//  * Parameters:
//  * - cell
//  * Return Value:
//  * - ???
//  */
// object* cdr1(object *cell){
//   if(cell->type == LIST){
//     return cell->cons_cell.cdr;
//   }
//   else{
//     return NULL;
//   }
// }

// /**
//  *This function creates an object representing a number
//  * Parameters:
//  * - number, the value of the object to create
//  * Return Value:
//  * - num an object with type number and value number
//  */
// object* create_number(int number){
//   // struct object *object1;
//   object *num = (object*)malloc(sizeof(object));
//   num->type  = NUM;
//   //num->value = number;
//   num->number = number;
//   return num;
// }

// /**
//  *This function creates an object representing a variable
//  * Parameters:
//  * - variable the value of the object to create
//  * Return Value:
//  * -var, an object with type "variable", and value variable
//  */
// object* create_variable(char* variable){
//   // struct object *object1;
//   object *var = (object*)malloc(sizeof(object));
//   var->type = VAR;
//   //var->value = variable;
//   var->variable = variable;
//   return var;
// }

// /**
//  *This function creates an object representing a primitive operation
//  * Parameters:
//  * - variable the value of the object to create
//  * Return Value:
//  * -var, an object with type "primeop", and value variable
//  */
// object* create_primitiveop(char* variable){
//   // struct object *object1;
//   object *var = (object*)malloc(sizeof(object));
//   var->type = OP;
//   //var->value = variable;
//   var->variable = variable;
//   return var;
// }

// char *print_list(object *obj, int count){
//   char *a, *b, *c;
//   if(obj->type == LIST){
//     a = print_list(car1(obj), count++);
//     b = print_list(cdr1(obj), count++);
//     // a = print_list(car1(obj));
//     // b = print_list(cdr1(obj));
//     c = malloc(sizeof(char)*100);
//     sprintf(c, "(%s %s)", a, b);
//   }
//   else if(obj->type == OP || obj->type == VAR){
//     c = obj->variable;
//   }
//   else{
//     c = malloc(sizeof(char)*8);
//     sprintf(c, "%d", obj->number);
//   }
//   return c;
// }

// //constructor_cell* code_tree = NULL; //Put the cells in this

// typedef struct type_list{
//   struct object val;
//   struct type_list *next;
// }type_list;

// /**Use this when you dereference void pointer to pointer fine
//  *This function gets the head of the code tree
//  * Parameters:
//  * -car, the cell containing the the type and value of the head of the code tree
//  * Return Value:
//  * -car, a c string of the value of the head of the code_tree
//  */
// char* get_car(void* car){
//   return *(char**)car;
// }