#include <stdio.h>
#include <string.h>
#include "stack.c"
//#include "utils.c"

#define DEL " \n\r\t"
#define SIZE 100

#define AND "&&"
#define OR "||"
#define XOR "^^"
#define NOT "!"
#define GT ">"
#define LT "<"
#define EQ "=="

char *operators[] = {"+", "-", "*", "/", "%", "^", "(", ")", '\0'};
char *ccond[] = {AND, OR, XOR, NOT, '\0'};
char *bcond[] = {GT, LT, EQ,'\0'};
char *ifelse[] = {"if", "else", '\0'};

int is_operator(char *s);

int is_bcond(char *s);

int is_ccond(char *s);

int is_ifelse(char *s);

char *construct_expr(stack *o, stack *n);

char *construct_ifelse(stack *o, stack *n);

char *construct_varset(stack *o, stack *n);

int precedence(char *op);

int is_keyword(char *op);

char *prefix(char *infix);

char *postfix(char *infix);
