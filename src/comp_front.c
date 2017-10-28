#include <stdio.h>
#include <string.h>
#include "stack.c"
#include "utils.c"

#define DEL " \n\r\t"
#define SIZE 100

char *operators[] = {"+", "-", "*", "/", "%", "^", "(", ")", '\0'};

int precedence(char *op) {
  if(isequal(op, "+") || isequal(op, "-")){
    return 2;
  }
  else if(isequal(op, "*") || isequal(op, "/")){
    return 3;
  }
  else if(isequal(op, "^")){
    return 4;
  }
  else if(isequal(op, "(") || isequal(op, ")")){
    return 1;
  }
  else{
    return 0;
  }
}

int is_operator(char *s){
  int i;
  for(i = 0; operators[i] != NULL; i++){
    if(isequal(s, operators[i])){
      return 1;
    }
  }
  return 0;
}

char *construct_expr(stack *op_stack, stack *num_stack){
  char *op = (char*)pop(op_stack);
  char *num2 = (char*)pop(num_stack);
  char *num1 = (char*)pop(num_stack);
  char *expr = malloc(sizeof(char)*100);
  sprintf(expr, "( %s %s %s )", op, num1, num2); 
  free(num1);
  free(num2);
  return expr;
}

char *prefix(char *infix) {
  char *token, *temp;//, *p = malloc(sizeof(char) * 100);
  stack *op_stack = create_stack();
  stack *num_stack = create_stack();

  token = strtok(infix, DEL);
  do{
    // printf("char : %s\n", token); 
    if(!is_operator(token)){
      // printf("number : %s\n", token);
      char *n = malloc(sizeof(char)*5);
      strcpy(n, token);
      push(num_stack, (void*)n);
    }
    else{
      // printf("symbol : %s\n", token);
      if(isequal(token, "(")){
        push(op_stack, (void*)token);
      }
      else{
        if(isequal(token, ")")){
          temp = (char*)check_first(op_stack);
          while(!isequal(temp, "(")){
            char *expr = construct_expr(op_stack, num_stack);
            push(num_stack, (void*)expr);
            temp = (char*)check_first(op_stack);
          }
        }
        else{
          temp = (char*)check_first(op_stack);
          if(precedence(token) > precedence(temp)){
            push(op_stack, token);
          }
          else{
            temp = (char*)check_first(op_stack);
            while(temp != NULL && precedence(token) <= precedence(temp)){
              char *expr = construct_expr(op_stack, num_stack);
              push(num_stack, (void*)expr);
              temp = (char*)check_first(op_stack);
            }
            push(op_stack, (void*)token);
          }
        }
      }
    }
    //  print_stack(op_stack, "OP");
    //  print_stack(num_stack, "NUM");
    //  printf("-------------------------\n");
  }
  while(token = strtok(NULL, DEL));

  while(op_stack->size > 0) {
    temp = (char*)pop(op_stack);
    if(!isequal(temp, "(")){
      push(op_stack, (void*)temp);
      char *expr = construct_expr(op_stack, num_stack);
      push(num_stack, (void*)expr);
    } 
    
  }
  char *expr = (char*)pop(num_stack);
  return expr;
} 
//converts infix expression to postfix
char *postfix(char *infix) {
  char *token, *p = malloc(sizeof(char) * 100);
  stack *op_stack = create_stack();
  
  token = strtok(infix, DEL);
  do{
    // printf("char : %s\n", token);
    if(!is_operator(token)){
      printf("number : %s\n", token);
      strcat(p, token);
      strcat(p, " ");
    }
    else{
      printf("symbol : %s\n", token);
      if(isequal(token, "(")){
        // strcat(p, "( ");
        push(op_stack, (void*)token);
      }
      else{
        if(isequal(token, ")")){
          char *temp = (char*)check_first(op_stack);
          while(!isequal(temp, "(")){
            pop(op_stack);
            strcat(p, temp);
            strcat(p, " ");
            temp = (char*)check_first(op_stack);
          }
        }
        else{
          char *temp = (char*)check_first(op_stack);
          if(precedence(token) > precedence(temp)){
            push(op_stack, token);
          }
          else{
            char *temp = (char*)check_first(op_stack);
            while(temp != NULL && precedence(token) <= precedence(temp)){
              temp = (char*)pop(op_stack);
              strcat(p, temp);
              strcat(p, " ");
              temp = (char*)check_first(op_stack);
            }
            push(op_stack, (void*)token);
          }
        }
      }
    }
  }
  while(token = strtok(NULL, DEL));

  while(op_stack->first != NULL) {
    char *temp = (char*)pop(op_stack);
    if(isequal(temp, "(")){
      // strcat(p, ") ");
    } 
    else if(isequal(temp, ")")){
      // strcat(p, "( ");
    } 
    else{
      strcat(p, temp);
      strcat(p, " ");
    }
 } 
  return p;
} 
