//https://llvm.org/docs/tutorial/LangImpl01.html#language
//#include "token.c"
#include "identifier.c"


/**
 * This function creates the preliminary tree
 * The returned tree is generated by iterating through program and creating tokens for each statement
 * Parameters:
 * - program the string containing the code we will run
 * Return Value:
 * - a list of tokens created by iterating through program
 * Example call:
 * List_Lexer("( + 1 1)");
 * expected return val: tokenlist of length 5
 */
//TODO: check for Booleans, Characters, Strings
token_list* lexer_tmp1 (char *program){   
 static int last_character = ' ';
  int i;
   
  struct  token_list *token_list = NULL;
  struct token_object object1;
  struct identifier *id;
  const char s[2] = " ";
  char *token;
  int num_right; 

  const char *right_par = ")";
   
  program = strdup(program);
  /* get the first token */
  token = strtok(program, s);

 
  /* walk through other tokens */
  while( token != NULL ) 
    {
      num_right = count_chars(token, ')');
	
      if(token[0] == '('){
	 
	memmove(token, token+1, strlen(token));


	object1.type = "left_paren";
	object1.value = "(";
	token_list = prepend_token(object1, token_list);
	object1.type = token_type(token);
	object1.value = token;
	token_list =  prepend_token(object1, token_list);

	  
	  
      }
      else if ( num_right>= 1){ 


	    
	token[strlen(token)-num_right] = 0;
	 
	object1.type = token_type(token);
	object1.value = token;
	 
	token_list = prepend_token(object1, token_list);

	object1.type = "right_paren";
	object1.value = ")";
	token_list = prepend_token(object1, token_list);
	
	 
	for(i =1; i < num_right; i++){
	    
	     
	  object1.type = "right_paren";
	  object1.value = ")";
	  token_list = prepend_token(object1, token_list);

	}
	    
	 
     
	 
      }
      else{
	object1.type = token_type(token);
	object1.value = token;
	token_list = prepend_token(object1, token_list);

      }
    
      token = strtok(NULL, s);  

    }

  if(token_list == NULL){

    object1.type = "primitive";
    object1.value = "open_paren";
    token_list = prepend_token(object1, token_list);

  }

   


  return  token_list;
}//end of list_lexer()

/**
 * This is a temp version of list_lexer to test the creation of tokens 
 * This function creates the preliminary tree
 * The returned tree is generated by iterating through program and creating tokens for each statement
 * Parameters:
 * - program the string containing the code we will run
 * Return Value:
 * - a list of tokens created by iterating through program
 * Example call:
 * List_Lexer_tmp("( + 1 1)");
 * expected return val: tokenlist of length 5
 */ 
//TODO: check for Booleans, Characters, Strings
token_list* list_lexer_tmp (char *program){
  static int last_character = ' ';
  int i;
   
  struct  token_list *token_list = NULL;
  struct token_object object1;
  struct identifier  *id;

  object1.type = "identifier";
  object1.value = "open_paren";
  token_list = prepend_token(object1, token_list);

 
  //printf("is alpha-test char %c\n",program[0]);
  //printf("is alpha-test %d\n",isalpha(program[0])); 
  for(i =0; i < strlen(program); i++){
    //Check if it's whitespace
    if(iswhitespace(program[i])){
      //???
    }else if (program[i] == '('){      //check if it is an open parentheses
      object1.type = "identifier";
      object1.value = "open_paren";
      token_list = prepend_token(object1, token_list);
    }else if (program[i] == ')'){      //check if it is an closed parentheses
      object1.type = "identifier";
      object1.value = "closed_paren";
      token_list = prepend_token(object1, token_list);
    }else if (isalpha(program[i])){    //check if its in the alphabet
      object1.type = "symbol";
      id =  read_identifier(program, i);
      object1.value = id->identifier_token;
      program = chopN( program, id->length ); 
      printf("IDENTIFIER %s\n", object1.value);
      token_list = prepend_token(object1, token_list);
    }else if(isdigit(program[i])){    //check if its a number
      object1.type = "num";
      id =  read_number(program, i);
      object1.value = id->identifier_token;
      program = chopN( program, id->length ); 
      printf("NUMBER VALUE %s\n", object1.value);
      token_list = prepend_token(object1, token_list);
    }else{                           //Invalid Syntax
      printf("Illegal syntax\n");
    }
  }

  printf("The number %d\n", count_token_list(token_list));
  //print_token_list(reverse_token_list(token_list));
  
  return token_list;
}//end of list_lexer_tmp

