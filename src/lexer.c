//https://llvm.org/docs/tutorial/LangImpl01.html#language

struct object{
  char* type;
  char* value;
}object;

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

char* read_identifier (char* program, int index){
  char *identifier=  "hi";
  char *identifier1;
  const char s[2] = " ";
  program = chopN( program, index );
  printf("PROGRAM: %s\n", program);
  char *string = strdup(program);
  identifier1=   strtok(string, s);
  
  return identifier1;

}
//Lexer
token_list* list_lexer (char *program){
  static int last_character = ' ';
  int i;
   
  struct  token_list *token_list = NULL;
  struct object object1;

   object1.type = "identifier";
   object1.value = "open_paren";
   token_list = cons1(object1, token_list);

  //printf("is alpha-test char %c\n",program[0]);
  //printf("is alpha-test %d\n",isalpha(program[0])); 
  for(i =0; i < strlen(program); i++){

    printf("program at i %c\n", program[i]);
    if(iswhitespace(program[i])){
	
      }
      
      else if (program[i] == '('){
	 object1.type = "identifier";
	 object1.value = "open_paren";
	 token_list = cons1(object1, token_list);

      }
     else if (program[i] == ')'){
	 object1.type = "identifier";
	 object1.value = "closed_paren";
	 token_list = cons1(object1, token_list);

      }    
      
     else if (isalpha(program[i])){

      
      object1.type = "symbol";
      object1.value = read_identifier(program, i);
      printf("IDENTIFIER %s\n", object1.value);
      token_list = cons1(object1, token_list);

    }
    //read-number
    else if(isdigit(program[i])){
      printf("It is a number\n");

    }
    
    else{
      
    }
  }

  return token_list;
}

