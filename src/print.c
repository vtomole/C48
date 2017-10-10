//Worked on object.c and object2.c
//Working on printing expressions and traversing the list
//Should work like the parser function but reverse

/**
 *This function prints the given object
 * Parameters:
 * -result, the object to print
 */
char* print(object* result){
  if(strcmp(result->type, "number") == 0){
    printf("%d\n", result->number);
  }else{
    printf("Oops, can't print that yet\n");
  }
}
