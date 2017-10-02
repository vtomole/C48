int test_num = 0;
char* result = NULL;

int are_equal (char *program, char *expected){
  test_num ++ ;
  char *input =  print_token_list_debug(list_lexer(program),result);
  printf("%s\n",input);
  if(strcmp(input,expected) == 0){
    printf("test %d passed \n",test_num);
  }
  else{
    printf("test %d failed \n",test_num);
  
  }
}


void lexer_tests (){

 
  are_equal("(set position (* 60 (+ initial rate)))", "[left_paren,(][symbol,set][symbol,position][left_paren,(][identifier,*][num,60][left_paren,(][identifier,+][symbol,initial][symbol,rate][right_paren,)][right_paren,)][right_paren,)]");
  are_equal("(+ 137 349)", "[left_paren,(][identifier,+][num,137][num,349][right_paren,)]");
  are_equal("(- 1000 334)", "[left_paren,(][identifier,-][num,1000][num,334][right_paren,)]");
  are_equal("(* 5 99) ", "[left_paren,(][identifier,*][num,5][num,99][right_paren,)]");
  are_equal("(/ 10 5)","[left_paren,(][identifier,/][num,10][num,5][right_paren,)]");
  are_equal("(+ 2.7 10 ) ", "[left_paren,(][identifier,+][num,2.7][num,10][right_paren,)]");
  
  
}
