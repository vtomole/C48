//https://llvm.org/docs/tutorial/LangImpl01.html#language

struct object{
  char* type;
  char* value;
}object;

struct identifier{
  char* identifier_token;
  int length;
}identifier;

typedef struct token_list{
  struct object val;
  struct token_list *next;
}token_list;

//Chop off first N characters
char * chopN(char * charBuffer, int n )
{   
   return charBuffer + n;   
}   

token_list* cons1(struct object val, struct token_list *cdr)
{
 
  //pair* pair = (pair*)malloc(sizeof(pair));
  token_list* pair = malloc(sizeof(pair));
  if(pair == NULL)
    {
      printf("Error creating a new node.\n");
      exit(0);
    }
  pair->val = val;
   pair->next = cdr;
 
  return pair;
}

enum Token {
  tok_eof = -1,
  tok_def = -2,
  tok_identifier = -4,
  tok_number = -5,
};

static char* indentifier_string;
static double number_value;

int iswhitespace (char c){
  if(c == '\n' || c == ' ' ){
    return 1;
  }
  else{
    return 0;
  }
}

struct identifier* read_identifier (char* program, int index){
  struct identifier *identifier1;
  const char s[2] = " ";
  program = chopN( program, index );
  char *string = strdup(program);
  identifier1->identifier_token= strtok(string, s);
  identifier1->length = strlen(identifier1->identifier_token);
  
  return identifier1;

}

struct identifier* read_number (char* program, int index){
  struct identifier *identifier1;
  const char s[2] = " ";
  program = chopN( program, index );
  char *string = strdup(program);
  identifier1->identifier_token= strtok(string, s);
  identifier1->length = strlen(identifier1->identifier_token);
  
  return identifier1;

}
//Lexer

//TODO: check for Booleans, Characters, Strings
token_list* list_lexer (char *program){
  static int last_character = ' ';
  int i;
   
  struct  token_list *token_list = NULL;
  struct object object1;
  struct identifier *id;

   object1.type = "identifier";
   object1.value = "open_paren";
   token_list = cons1(object1, token_list);

  //printf("is alpha-test char %c\n",program[0]);
  //printf("is alpha-test %d\n",isalpha(program[0])); 
  for(i =0; i < strlen(program); i++){
    //Check if it's whitespace
    if(iswhitespace(program[i])){
	
      }
    //check if it is an open parentheses
      else if (program[i] == '('){
	 object1.type = "identifier";
	 object1.value = "open_paren";
	 token_list = cons1(object1, token_list);

      }
    //check if it is a closed parentheses
     else if (program[i] == ')'){
	 object1.type = "identifier";
	 object1.value = "closed_paren";
	 token_list = cons1(object1, token_list);

      }    
    //check if its in the alphabet
     else if (isalpha(program[i])){
      
      object1.type = "symbol";
      id =  read_identifier(program, i);
      object1.value = id->identifier_token;
      program = chopN( program, id->length ); 
      printf("IDENTIFIER %s\n", object1.value);
      token_list = cons1(object1, token_list);

    }
    //check if its a number
    else if(isdigit(program[i])){
      object1.type = "num";
      id =  read_number(program, i);
      object1.value = id->identifier_token;
      program = chopN( program, id->length ); 
      printf("NUMBER VALUE %s\n", object1.value);
      token_list = cons1(object1, token_list);

    }
    //invalid syntax
    else{
      printf("Illegal syntax\n");
      
    }
  }

  return token_list;
}

