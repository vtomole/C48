typedef struct item{
  void *value;
  struct item *next;
}item;

typedef struct stack{
  item *first;
}stack;

stack *create_stack(){
  stack *temp = (stack*)malloc(sizeof(stack));
  temp->first = NULL;
  return temp;
}

void *pop(stack *s){
  if(s->first != NULL){
    item *temp = s->first;
    s->first = temp->next;
    return temp->value;
  }
  return NULL;
}

void push(stack *s, void *value){
  item *temp = (item*)malloc(sizeof(item));
  temp->value = value;
  temp->next = s->first;
  s->first = temp;
}