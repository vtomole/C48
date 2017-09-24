/*
start over the program split.
make token as string array.
then count number of tokens.
then make token array.
categorize them based on different values.
 */
//https://llvm.org/docs/tutorial/LangImpl01.html#language
int left=0,i , j;
int right=0;
int invalid = 0;
int value= NULL;
char charSet[] = { ' ', '\n', '\t', 0 };
struct Token {
  char name;
  char values;
  char *next = null;
};

int isnumber (char s){
  if(s == NULL || s == '\0' || isspace(s)){
    return 0;
  }
  else{
    char* p;
    strtod(s, &p);
    return *p == '\0';
  }
}

int isoperator (char s){
  if(s == '%'||s == '/'||s == '*'||s == '+'||s == '-'){
    return 1;
  }
  else{    
    return 0;
  }
}

int isbrackets (char s){
  if(s ==')'|| s=='('){
    if(s =='('){left++;}
    else {right++;}
    return 1;
  }
  else{    
    return 0;
  }
}


char* read_token (char *program){
 struct  Token tokens [strlen(program)];
  int a=0;
  for(i = strlen(program);i>=0; i--){
    char s = program[0];
    if(isbrackets(s))
      {
        if(strlen(value)!=0)
	  {
	    tokens[a].name =  "number";
	    tokens[a].values =  value ;
	    a++;
	  }
        tokens[a].name = "bracket";
        tokens[a].values = s;
	a++;
      }
    else if(isoperator(s))
      {
	    if(strlen(value)!=0)
	      {
	        tokens[a].name = "number";
	        tokens[a].values = value;
		a++;
	      }
	    tokens[a].name = "operator";
	    tokens[a].values =  s;
	    a++;
	 
      }
    else if(isnumebr(s))
      {
	value = value+s;

      }
    else if (strchr(charSet, s) != NULL)
      {
        if(strlen(value)!=0)
	      {
	        tokens[a].name =  "number";
	        tokens[a].values = value ;
		a++;
	      }
	    
      }
    else invalid = 1;
}
  if(left != right)
    {
      invalid =1;
    }
  if (a<strlen(program))
    {
      struct Token tokens2[a];
      for( j =0; j<=a;j++)
	{
	  tokens2[a]= tokens[a];
	}
      
    }
  return tokens;
}
