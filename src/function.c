#include <stdio.h>
#include <string.h>
#include "prefix.c"

int is_whitespace(char c){
  return c == ' ' || c == '\t' || c == '\r' || c == '\n'; 
}

char *get_name(char *line){
  int i = 0;
  while(!is_whitespace(line[i]) && line[i] != '('){
    i++;
  }
  char *name = malloc(sizeof(char)*(i+1));
  memcpy(name, line, i);
  return name;
}

char *get_params(char *line){
  int j, i = 0, count = 0;
  while(line[i] != ')'){
    if(!is_whitespace(line[i])){
      count++;
    }
    i++;
  }

  char *param = malloc(sizeof(char)*(count+1));
  count = 0;
  for(j = 0; j < i; j++){
    char c = line[j];
    if(c == ','){
      param[count++] = ' ';
    }
    else if(!is_whitespace(c)){
      param[count++] = c;
    }
  }
  printf("param is %s\n", param);
  return param;
}

// char *get_block(char *line){
//   int i = 1, count = 0;
//   while(line[i] != '}' && count == 0){
//     count = line[i] == '}' ? count-- : (line[i] == '{' ? count++ : count);
//   }

//   char *block = malloc(sizeof(char))
// }

char *get_function(char *line){
  int i = 4;
  //skipping to the name
  while(is_whitespace(line[i])){
    i++;
  }
  char *name = get_name(&line[i]);

  //skipping to the first param
  while(line[i] != '('){
    i++;
  }
  i++;
  char *params = get_params(&line[i]);
  
  //skipping to the funtion
  while(line[i] != '{'){
    i++;
  }
  char *block = prefix(&line[i]);
  char *fun = malloc(sizeof(char)*100);
  sprintf(fun, "( define ( %s %s ) ( %s ) )", name, params, block);
  free(block);
  free(name);
  free(params);

  return fun;
}