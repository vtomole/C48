#include <stdio.h>
#include <stdlib.h>


////////  Item / Stack / Queue  ////////
typedef struct item{
  void *value;
  struct item *next;
}item;

typedef struct stack{
  item *first;
  int size;
}stack;

typedef struct queue{
  item *first;
  int size;
}queue;

////////  Create  ////////
stack *create_stack(){
  stack *temp = (stack*)malloc(sizeof(stack));
  temp->first = NULL;
  temp->size = 0;
  return temp;
}

queue *create_queue(){
  queue *temp = (queue*)malloc(sizeof(queue));
  temp->first = NULL;
  temp->size = 0;
  return temp;
}


////////  Add / Remove  ////////
void push(stack *s, void *value){
  if(value != NULL){
    item *temp = (item*)malloc(sizeof(item));
    temp->value = value;
    temp->next = s->first;
    s->first = temp;
    s->size++;
  }
}

void enqueue(queue *q, void *value){
  if(value != NULL){
    item *temp = (item*)malloc(sizeof(item));
    temp->value = value;
    temp->next = NULL;
    if(q->first == NULL){
      q->first = temp;
    }
    else{
      item *last = q->first;
      while(last->next != NULL){
        last = last->next;
      }
      last->next = temp;
    }
    q->size++;
  }
}

void *pop(stack *s){
  // printf("(%d)\n", s->size);
  if(s->size > 0){
    s->size--;
    item *temp = s->first;
    s->first = temp->next;
    void *val = temp->value;
    free(temp);
    return val;
  }
  return NULL;
}

void *dequeue(queue *q){
  if(q->size > 0){
    q->size--;
    item *temp = q->first;
    q->first = temp->next;
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
