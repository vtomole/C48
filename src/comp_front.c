#include "comp_front.h"


char *next(char *line, char token){
  int i = 0, j = 0, k = 0;
  int instring = 0;
  
  //Finding the next index with token
  while(line != '\0' && line[i] != token){
    i++;
  }

  //Creating the next string
  char *next = malloc(sizeof(char)*(i+1));
  for(j = 0; j < i; j++){
    next[j] = line[j];
  }
  return next;
}

char *trim_front(char *line, int len){
  int i = len;
  while(is_whitespace(line[i])){
    i++;
  }
  line = &line[i];
  return line;
}

int count_func(char *line){
  int i = 0, count = 0;
  while(line[i] != '{'){
    i++;
  }
  i++;
  while(line[i] != '}' && count == 0){
    count = line[i] == '}' ? count-- : (line[i] == '{' ? count++ : count);
    i++;
  }
  i++;
  while(iswhitespace(line[i])){
    i++;
  }
  return i;
}

char *compile(char *line){
  int i = 0;
  char *n = next(line, ' ');
  char *comp = malloc(sizeof(char)*100);

  while(line[i] != '\0'){
    if(isequal(n, "fun")){
      char *s = get_function(&line[i]);
      i += count_func(line);
      sprintf(comp, "%s\n%s", comp, s);
      free(s);
    }
    else{
      i += strlen(n);
    }
    
    free(n);
    n = next(&line[i], ' ');
  }

  return comp;
}

