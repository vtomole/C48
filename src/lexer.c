//https://llvm.org/docs/tutorial/LangImpl01.html#language

struct object{
  char* type;
  char* value;
}object;

typedef struct token_list{
  struct object val;
  struct token_list *next;
}token_list;

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
//Lexer
char* read_token (char *program){
  static int last_character = ' ';
  int i;

  struct  token_list *token_list = NULL;
  struct object object1;

  //printf("is alpha-test char %c\n",program[0]);
  //printf("is alpha-test %d\n",isalpha(program[0])); 
  for(i =0; i < strlen(program); i++){
   
    if(isalpha(program[i])){
      printf("It is an alphabet\n");

    }
    //read-number
    else if(isdigit(program[i])){
      printf("It is a number\n");

    }
    
    else{
      
    }
  }

  return 0;
}

