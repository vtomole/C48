#include <stdio.h>
#include <stdlib.h>

typedef struct item item;

typedef struct stack stack;

stack *create_stack();

void push(stack *s, void *value);

void *pop(stack *s);

void *check_first(stack *s);

void print_stack(stack *s, char *name);