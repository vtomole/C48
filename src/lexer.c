//https://llvm.org/docs/tutorial/LangImpl01.html#language
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#include "identifier.c"
//#include "utils.c"

char* number ="" , *symbol ="" , *oper="";
int  open = 0 , close =0;
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
		  // printf("number");
		  Token.type = "num";
		  Token.value = number;
		  number = "";
		   /*printf("%s\n", Token.type);
		     printf("%s\n", Token.value);*/	
		  //printf("number");
		  token_list_lexer = prepend_token(Token, token_list_lexer);
		} 
  if(symbol!= "")
    {     //printf("symbol");
	      
	      if(strcmp(symbol,"for") == 0||strcmp(symbol,"do")==0||strcmp(symbol,"while")==0||strcmp(symbol,"if")==0||strcmp(symbol,"else")==0||strcmp(symbol,"begin")==0||strcmp(symbol,"set")==0||strcmp(symbol,"go")==0||strcmp(symbol,"define")==0||strcmp(symbol,"ifelse")==0)
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
void check_oper(char *oper){
  if (!(strcmp(oper,"!=") == 0||strcmp(oper,"==")==0||strcmp(oper,">=")==0||strcmp(oper,"<=")==0||strcmp(oper,"++")==0))
    {printf("invalid operator"); 
      exit(0);}
}
int * paren( ) {

   static int  r[2];
   
      r[1] = open;
      //printf("%d",r[1]);
      r[2] = close;
      

   return r;
}

/*
  read complete program and create token list
 */
token_list* lexer_1(char* program2)
{ //printf("received from parser %s \n", program2);
  char* program = trimwhitespace(program2);
  int i;  

  int n = strlen(program);
  //printf("n %s \n", n);
  //trim white space before and after program
  /*if((!(isparanthesis(program[0])))&&(!(isparanthesis(program[n-1]))))
	{
	  printf("Invalid number of Parenthesis at begining or end");
	  }*/

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
	{ ///printf("paranthesis");
	  check_num_symbol();
	   if(program[i]=='(')
	     {
	       open++;
	      Token.type = "open_paren";	      
	      Token.value = "(" ;
	      /*printf("%s\n", Token.type);
		printf("%s\n", Token.value);*/
	      token_list_lexer = prepend_token(Token, token_list_lexer);
	     }
	   if(program[i]==')')
	     {check_num_symbol();
	       close++;
	       // printf("here");
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
      else if(isdigit(program[i])){
	//printf("digit");
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
	{// printf("space");
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
	 if(i<n-1){
	  if(isdigit(program[i+1]))
	    {number = append(number, program[i]);
	      i++;
	      ///goto NUMBER;
	    }
	  if(isoperator(program[i+1])){
	  while(isoperator(program[i])&&(i<n-1))
	    {
	      oper = append(oper, program[i]);
	      i++;
	    }
	   check_oper(oper);
	   i--;}
	 }
	 else{oper =  append("", program[i]);}
	 
	  
	  Token.type = "primitive";
	  Token.value = oper;	 // printf("operator");  
	  //printf("%s\n", Token.type);
	  //printf("%s\n", Token.value);
	  token_list_lexer = prepend_token(Token, token_list_lexer);
       }
      /*
	If nothing else then add characters in symbol.
	THis will include alphabets and special symbols taht are not yet defined as operators
       */
     else
       {//printf("elsenumber");	 
	 symbol = append(symbol,program[i]);
       }
    }

    /*
      Check if count of parenthesis were even in program
     */
    if(close != open)
	{
	  printf("Invalid number of parenthesis\n");
	}
    //print_token_list(token_list_lexer);
    paren();
    return token_list_lexer;
    
}


