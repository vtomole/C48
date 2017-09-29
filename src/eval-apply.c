enum type {Symbol,String, Number, List, Procedure, Lambda};
struct env{
  enum type type;
  void* value;
}env;

char  *apply(char operator, int arguments[]){
  
  int i;
  char* answer = (char*)malloc(8 * sizeof(char));
  switch(operator){
  case '+':
    sprintf(answer, "%d", arguments[0] + arguments[1]);
    return answer;
    break;
  case '-':
    sprintf(answer, "%d", arguments[0] - arguments[1]);
    return answer;
    break;
  case '*':
    sprintf(answer, "%d", arguments[0] * arguments[1]);
    return answer;
    break;
  case '/':
    sprintf(answer, "%d", arguments[0] / arguments[1]);
    return answer;
    break;
  default:
    return "Your char is not in this variable\n";
  }

}

constructor_cell *eval( constructor_cell* exp, struct env env ){

 
  return exp;
}
