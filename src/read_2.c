/*
strat over the program split.
make token as string array.
then count number of tokens.
then make token array.
categorize them based on different values.
 */
//https://llvm.org/docs/tutorial/LangImpl01.html#language

struct Token {
  char* name;
  char* value;
};


static char* indentifier_string;
static double number_value;

typedef struct pair{
  void *car;
  void *cdr;
}pair;



typedef struct eval_arguments {
  pair *head;
  hashtable_t *environment;
}eval_arguments;

pair* create1(void* car,void* cdr)
{
 
  //pair* pair = (pair*)malloc(sizeof(pair));
  pair* pair = malloc(sizeof(pair));
  if(pair == NULL)
    {
      printf("Error creating a new node.\n");
      exit(0);
    }
  pair->car = car;
  pair->cdr = cdr;
 
  return pair;
}

pair* cons(void *car, pair* cdr)
{
 
  pair* new_pair = create1(car,cdr);
  car = new_pair;
  return car;
}


int isnumber (char *s){
  if(s == NULL || *s == '\0' || isspace(*s)){
    return 0;
  }
  else{
    char* p;
    strtod(s, &p);
    return *p == '\0';
  }
}
const char operators[] ="+-*%/";
int isoperator(char *s)
{
  for(int i =0;i<5;i++)
    {
      if(strcmp(token,operators[i]))
	{
	  return 1;
	}
    }
  return 0;
  }

struct eval_arguments read(char *program){
  pair pair1;
  pair pair2;
  pair pair3;
  hashtable_t *environment = ht_create(65536);

  char * program_1;
  int i = 0;
  char operator = '+', char_quit = 'q';
  int b = 20,d;
  int c = 30;
  int count =0;
  char* token, substr;
  
  pair* head = NULL;   
  const char s[] = "()\n\t\r\f ";   
   
  /* get the first token */
  token = strtok(program, s);

  /*  //printf("%s\n", token);
  if(strcmp(token, "q\n") == 0)
    {
    if(strlen(program)==1)
      {
	operator = 'q';
	head = cons(&operator, head); 
      }
    else
      {
	printf("Invalid Input please insert q to quit");
      }
    }
  */
  int  num_token =0;
while( token != NULL )
  {
    num_token ++;
    if(!((isnumber(token)||(isoperator(token)))
      {
	printf("invalid input") ;
      }
	else if ((isnumber(token))
	  {
	    Token token+num_token;
	    token+num_token.name ="number"+num_token;
	    token+num_token.value =token;
	    
	  }
	  else 
	  {
	    Token token+num_token;
	    token+num_token.name ="operator"+num_token;
	    token+num_token.value =token;
	  }
  }
  

   
  eval_arguments exp_env = {head,environment};

  return exp_env;


}
//Lexer
char* read_token (char *program){
  static int last_character = ' ';
  int i;

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
      switch(program[i]){
      case '(':
	return "left-paren";
	break;
      case ')':
	return "right-paren";
	break;

      case ' ':
     
	continue;
    
      
    
      default:
	//printf("Your char is not in this variable\n");
	return "illegal lexical syntax";
      }
    }
  }

  return 0;
}


int read_list (pair* list_so_far){

  return 0;
}

char *micro_read (char* program){
  
  char* next_token = read_token(program);
  
  pair* list_so_far;
 
  if(strcmp(next_token,"left-paren") == 0){
    //printf("Left parentheses\n");

    read_list(list_so_far);

  }
  else{
    return next_token;
  }


  return 0;
}
