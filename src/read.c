//https://llvm.org/docs/tutorial/LangImpl01.html#language

enum Token {
  tok_eof = -1,
  tok_def = -2,
  tok_identifier = -4,
  tok_number = -5,
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
   
  const char s[2] = " ";
  const char s1[2] = "(";
    
   
  /* get the first token */
  token = strtok(program, s);

  //printf("%s", token);
  if(strcmp(token, "q\n") == 0){
    //operator = 'q';
    operator = 'q';
    head = cons(&operator, head);
    //cons(&token ,head);
    //return head;
  }
  /* walk through other tokens */
  while( token != NULL ) 
    {
      //if(token[0] == '('){
      //token = strtok(program, s1);
      // printf("Token should not have parentheses %s\n", token);
      //	printf("Strlen of token %d\n", strlen(token));
      //	printf("Parsing token %c\n", token[strlen (token)- 2]);
      //printf( " dat token %s\n", token );


	
      if(token[0] == '('){
	operator = token[1];
      }
      else if(token[strlen(token)- 2] == ')'){
	//printf("Right paren\n");
	for(i =0; i < strlen(token); i++){
	  // printf("Token at i %c\n", token[i]);
	  if(token[i] == ')'){
	    token[i] = '\0';
	    // printf("I'm in here folks\n");
	    break;
	  }
	  else{
	    token[i] = token[i];
	  }
	    
	}
	//printf("The token after %s\n", token);
	if(isnumber(token)){
	  b = atoi(token);
	  head = cons(&b,head);
	   
	  //type_array[count] = "integer";
	  count++;
	}
      }
      else{
	// printf( "The token at 0 %c\n", token[0]);
	c = token[0] - '0';
	//printf("that token as an int %d\n", c);

      }

      /*else if (isnumber(token)){
      //printf("A digit is here\n");
      // printf("the token %s\n", token);
      c = atoi(token);
      printf("this is the c %d\n", c);
      }
      else if (token[1] == ')'){
     
      d = token[0] - '0';
      }

      */
    
      token = strtok(NULL, s);  

    }

  /*printf("value of operator %c\n", operator);
    printf("value of b(var 1) %d\n", b);
    printf("value of c(var 2) %d\n", c);*/
  
   
  pair1.car = &b;
  pair1.cdr = &pair2;
  
  //pair1.cdr = &c;
  pair2.car = &b;
  pair2.cdr = &pair3;
  
  
  head = cons(&b,head);
  head = cons(&c,head);
  head = cons(&operator, head);

   
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
