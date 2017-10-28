#include <stdio.h>
#include <stdlib.h>

typedef struct item{
  void *value;
  struct item *next;
}item;

typedef struct stack{
  item *first;
  int size;
}stack;

stack *create_stack(){
  stack *temp = (stack*)malloc(sizeof(stack));
  temp->first = NULL;
  temp->size = 0;
  return temp;
}

void push(stack *s, void *value){
  if(value != NULL){
    item *temp = (item*)malloc(sizeof(item));
    temp->value = value;
    temp->next = s->first;
    s->first = temp;
    s->size++;
    // printf("Pushing: %s\n", (char*)(s->first)->value); // Doesnet work with ints
  }
}

void *pop(stack *s){
  // printf("(%d)\n", s->size);
  if(s->size > 0){
    s->size--;
    // printf("reduced size ");
    // printf("Popping: %s\n", (char*)(s->first)->value); // doesnt work with ints
    item *temp = s->first;
    s->first = temp->next;
    return temp->value;
  }
  return NULL;
}

void *check_first(stack *s){
  if(s->size){
    return (s->first)->value;
  }
  return NULL;
}

void print_stack(stack *s, char *name){
  item *temp = s->first;
  printf("%s(%d): ", name, s->size);
  while(temp != NULL){
    char *val = (char*)temp->value;
    printf("[%s]->", val);
    temp = temp->next;
  }
  printf("end\n");
}
