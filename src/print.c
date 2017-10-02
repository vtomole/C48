/**
 *This function prints the given object
 * Parameters:
 * -result, the object to print
 */
char* print1(object* result){
  if(strcmp(result->type, "number") == 0){
    printf("%d\n", result->number);
  }else{
    printf("Oops, can't print that yet\n");
  }
}
