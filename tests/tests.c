int assert (char *input, char* expected){

  if(strcmp(input,expected) == 0){
    return 0;
  }
  else{
    return 1;
  }
}


void *tests (){
  char* result = NULL;
  
  int passed = 0;
  int run = 0;
  printf("The result %s\n",print_token_list(list_lexer("(set position (* 60 (+ initial rate)))"), result));

  if(assert(print_token_list(list_lexer("(set position (* 60 (+ initial rate)))"),result), "(setposition(*60(+initialrate)))")== 0){
    passed++;
  }
  run++;
  if(assert(print_token_list(list_lexer("(+ (+ 2 3) 7)"),result), "(+(+23)7)")== 0){
    passed++;
  }
  run++;
  

  printf("%d tests run. %d tests passed\n", run,  passed);
 


}
