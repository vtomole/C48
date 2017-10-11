/**
 *This function prints the given object
 * Parameters:
 * -result, the object to print
 */
char* print(object* result){
  if(strcmp(result->type, "number") == 0){
    printf("%d\n", result->number);
  }
  else if(strcmp(result->type, "variable") == 0){
    printf("%d\n", result->number);
  }
  else if(strcmp(result->type, "string") == 0){
    printf("%s\n", result-> string);
  }
  else if(strcmp(result->type, "list") == 0){
    printf("%d\n", result->number);
  }
  else{
    printf("Oops, can't print that yet\n");
  }
}
