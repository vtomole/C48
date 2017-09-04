//https://llvm.org/docs/tutorial/LangImpl01.html#language

enum Token {
  tok_eof = -1,
  tok_def = -2,
  tok_identifier = -4,
  tok_number = -5,
};

static char* indentifier_string;
static double number_value;


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

