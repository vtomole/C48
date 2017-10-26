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
    printf("%s\n", result->variable);
  }
  else if(strcmp(result->type, "string") == 0){
    printf("%s\n", result-> string);
  }
  else if(strcmp(result->type, "cons") == 0){

    printf("(%s %d %d)\n", car(result)->variable,  car(cdr (result)) ->number, car (cdr (cdr (result))) ->number);;
   
  }
  else if(strcmp(result->type, "boolean") == 0){
    if(result->boolean == true){
      
    printf("#t\n");
    }
    else{
      printf("#f\n");
    }
  }
  else{
    printf("Oops, can't print that yet\n");
  }
}
