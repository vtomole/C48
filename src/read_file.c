#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int open_file(const char *name){
  
  int length = strlen(name) + strlen("./") + 1;
  char *cpy = malloc(sizeof(char) * length);
  strcpy(cpy, "./");
  strcat(cpy, name);
  //printf("trying to open %s\n", cpy);
  FILE *file;
  file = fopen(cpy, "r");
  if(!file){
    fprintf(stderr, "File does not exist.");
    exit(0);
  }
  yyset_in(file);
  return 1;
}
