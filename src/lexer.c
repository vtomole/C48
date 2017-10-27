//https://llvm.org/docs/tutorial/LangImpl01.html#language
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#include "./identifier.c"
#include "./utils.c"

char* number ="" , *symbol ="" ;

struct  token_list *token_list_lexer = NULL;
struct token_object Token;
/*
  CHeck if number and symbol are empty
  Symbol here refers to string
  if not then create appropriate token
 */
void check_num_symbol()
{

  if(number!="")
		{
		 
		  Token.type = "num";
		  Token.value = number;
		  number = "";
		   /*printf("%s\n", Token.type);
		     printf("%s\n", Token.value);*/		 
		  token_list_lexer = prepend_token(Token, token_list_lexer);
		} 
  if(symbol!= "")
    {     printf("symbol:%s\n",symbol);
	      
	      if(strcmp(symbol,"for") == 0||strcmp(symbol,"do")==0||strcmp(symbol,"while")==0||strcmp(symbol,"if")==0||strcmp(symbol,"else")==0)
		{
		  Token.type = "reserved";
		  
		}
	      else if(strcmp(symbol,"true")==0||strcmp(symbol,"false")==0)
		{
		  Token.type = "boolean";
		}
	      else{Token.type = "string";}
	      
	      Token.value = symbol;
	      symbol = "";
	       /*printf("%s\n", Token.type);
		 printf("%s\n", Token.value);*/
	      token_list_lexer = prepend_token(Token, token_list_lexer);	      
	    }
	  
}

/*
  read complete program and create token list
 */
token_list* lexer_1(char* program2)
{    
  char* program = trimwhitespace(program2);
  int i;  
  int parenthesis=0;
  int n = strlen(program);
  //trim white space before and after program
  if(!(isparanthesis(program[0]))&&(strcmp(program,"q")!=0))
	{ printf("Invalid number of Parenthesis at begining or end");
	}

  //loop through each character and create appropriate tokens.
    for(i=0; i< n; i++)
    {  

     Token.type = NULL;
     Token.value = NULL;
     /*
       if parenthesis
       increase count of parenthesis
       Check if it is after a string or number
       Use open and close parenthesis as terminology
       create token
      */
      if(isparanthesis(program[i]))
	{ 
	  parenthesis ++;
	  check_num_symbol();
	   if(program[i]=='(')
	     {
	      
	      Token.type = "open_paren";	      
	      Token.value = "(" ;
	      /*printf("%s\n", Token.type);
		printf("%s\n", Token.value);*/
	      token_list_lexer = prepend_token(Token, token_list_lexer);
	     }
	   if(program[i]==')')
	     {check_num_symbol();
	       Token.type = "close_paren";	      
	       Token.value =")";
	        /*printf("%s\n", Token.type);
		  printf("%s\n", Token.value);*/
	      token_list_lexer = prepend_token(Token, token_list_lexer);
	     }
	}
      /*
       if digit
       keep looping until you read complete number      
       create token
       set number to null again
      */
     else if(isdigit(program[i]))
     NUMBER :{
	while (isdigit (program[i]))
	{	    
	  number  = append(number, program[i]);	
	 
	  i++;
	}
	  i = i-1;  
	  Token.type = "num";
	  Token.value = number;
	  /*printf("%s\n", Token.type);
	    printf("%s\n", Token.value);*/
	   token_list_lexer = prepend_token(Token, token_list_lexer);
	  number = "";  
	}
      /*
       if space
       Check if it is after a string or number
       if yes then create token
       else ignore
      */
      else if(iswhitespace(program[i]))
	{
	  i++;
	 check_num_symbol();	  
	}
       /*
       if operator
       Check if it is follwed by a number      
       if yes then create a signed number token
       else craete a operator token
       primitive is being used for TYpe
      */
     else if (isoperator(program[i]))
       {
	 check_num_symbol();
	  if(isdigit(program[i+1]))
	    {
	      number = append(number, program[i]);
	      
	      i++;
	      goto NUMBER;
	    }
	  
	  Token.type = "primitive";	  
	  Token.value = append("",program[i]);	  
	  /*printf("%s\n", Token.type);
	    printf("%s\n", Token.value);*/
	  token_list_lexer = prepend_token(Token, token_list_lexer);
       }
      /*
	If nothing else then add characters in symbol.
	THis will include alphabets and special symbols taht are not yet defined as operators
       */
     else
       {	 
	 symbol = append(symbol,program[i]);
       }
    
      
      
    }

    /*
      Check if count of parenthesis were even in program
     */
    if((parenthesis%2)!=0)
	{
	  printf("Invalid number of parenthesis\n");
	}
    
    return token_list_lexer;
    
}

