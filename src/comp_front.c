#include "comp_front.h"

int is_operator(char *s){
  int i;
  for(i = 0; operators[i] != NULL; i++){
    if(isequal(s, operators[i])){
      return 1;
    }
  }
  return 0;
}

int is_bcond(char *s){
  int i;
  for(i = 0; bcond[i] != NULL; i++){
    if(isequal(s, bcond[i])){
      return 1;
    }
  }
  return 0;
}

int is_ccond(char *s){
  int i;
  for(i = 0; ccond[i] != NULL; i++){
    if(isequal(s, ccond[i])){
      return 1;
    }
  }
  return 0;
}

int is_ifelse(char *s){
  int i;
  for(i = 0; ifelse[i] != NULL; i++){
    if(isequal(s, ifelse[i])){
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
  // sprintf(expr, "%s %s %s", op, num1, num2); 
  free(num1);
  free(num2);
  return expr;
}

char *construct_ifelse(stack *op_stack, stack *num_stack){
  char *op = (char*)pop(op_stack);
  while(!isequal(op, "if")){
    op = (char*)pop(op_stack);
  }
  char *num3 = (char*)pop(num_stack);
  char *num2 = (char*)pop(num_stack);
  char *num1 = (char*)pop(num_stack);
  char *expr = malloc(sizeof(char)*100);
  sprintf(expr, "( %s %s %s )", num1, num2, num3);
  // sprintf(expr, "%s %s %s", op, num1, num2); 
  free(num1);
  free(num2);
  free(num3);
  return expr;
}

char *construct_varset(stack *op_stack, stack *num_stack){
  char *op = (char*)pop(op_stack);
  char *num2 = (char*)pop(num_stack);
  char *num1 = (char*)pop(num_stack);
  char *var = (char*)pop(num_stack);
  char *expr = malloc(sizeof(char)*100);
  sprintf(expr, "( ( %s %s %s ) %s )", op, var, num1, num2);
  // sprintf(expr, "%s %s %s", op, num1, num2); 
  free(var);
  free(num1);
  free(num2);
  return expr;
}

int precedence(char *op) {
  if(isequal(op, "(") || isequal(op, ")")){
    return 1;
  }
  else if(isequal(op, "if") || isequal(op, "else") || isequal(op, "set")){
    return 4;
  }
  else if(is_ccond(op)){
    return 5;
  }
  else if(is_bcond(op)){
    return 6;
  }
  else if(isequal(op, "+") || isequal(op, "-")){
    return 7;
  }
  else if(isequal(op, "*") || isequal(op, "/")){
    return 8;
  }
  else if(isequal(op, "^")){
    return 9;
  }
  else{
    return 0;
  }
}

int is_keyword(char *op){
  int keyword = is_operator(op) || is_ccond(op) || is_bcond(op);
  keyword |= is_ifelse(op) || isequal(op, "set");
  return keyword;
}

char *prefix(char *infix) {
  char *token, *temp;
  stack *op_stack = create_stack();
  stack *num_stack = create_stack();

  token = strtok(infix, DEL);
  do{
    // printf("char : %s\n", token); 
    if(!is_keyword(token)){
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
    print_stack(op_stack, "OP");
    print_stack(num_stack, "NUM");
    printf("-------------------------\n");
  }
  while(token = strtok(NULL, DEL));

  char *expr;
  while(op_stack->size > 0) {
    // print_stack(op_stack, "OP");
    // print_stack(num_stack, "NUM");
    // printf("-------------------------\n");
    temp = (char*)pop(op_stack);
    if(is_ifelse(temp)){
      push(op_stack, (void*)temp);
      expr = construct_ifelse(op_stack, num_stack);
      push(num_stack, (void*)expr);
    }
    else if(isequal(temp, "set")){
      push(op_stack, (void*)temp);
      expr = construct_varset(op_stack, num_stack);
      push(num_stack, (void*)expr);
    }
    else if(!isequal(temp, "(") ){
      push(op_stack, (void*)temp);
      expr = construct_expr(op_stack, num_stack);
      push(num_stack, (void*)expr);
    } 
    
  }
  expr = (char*)pop(num_stack);
  return expr;
} 

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

