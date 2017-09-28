/**
 * Executes the operation returning the result
 * This function implements our defined functions among other operation native to c
 * Parameters:
 * - operator the function or operation to perform
 * - arguments[] an array containing the nessecary arguments to execute the command
 * Return Value:
 * - answer the result of the operation
 * Example call:
 * apply('+', int[1,2])
 * expected return val: 3
 */ 
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

}//end of apply

/**
 * Evaluates the given arguements to create the code tree that apply will execute over
 * This function takes in an expression and and the environment hash table and creates the tree
 * Parameters:
 * - exp_env the expresssion and the environment the expression is in
 * Return Value:
 * - answer the head of the code tree
 * Example call:
 * 
 * expected return val: 
 */ 
char *eval(eval_arguments exp_env){

  pair* head = exp_env.head;
  hashtable_t *environment = exp_env.environment;
  pair *cursor = head;
  int num_nodes=0;
  char operator;
  char *answer;
  int first,second,i;
  //num_nodes = count (head);
  //  
  
  i=0;
  //if(strcmp(type_array[i], "integer") == 0){

  //  printf("It's an integer\n");
    
  // }
    
     

  if( *(char*)head->car == 'q'){
    exit(0);
  }
  else{

  
    // printf("The number of nodes %d\n", num_nodes);
  
    operator = *(char*)head->car;
    printf("In eval  should be +  %c\n", operator );
 
    head =  (pair*)head->cdr;
  

    first = *(int*)head->car;
    //printf("In eval  should be 20  %d\n", first );
 

    head =  (pair*)head->cdr;
  

    second = *(int*)head->car;
    //printf("In eval  should be 20  %d\n", second );
 
  
  
    int arguments[2] = {first,second};
    ht_set(environment, "key1", "hello world" ); 
    printf( "%s\n", ht_get(environment, "key1" ) );

    answer = apply(operator, arguments);
  }
  return answer;
}//end of eval

/**
 * Prints the code tree returned by eval
 * This function is primarily for testing our tree generation
 * Parameters:
 * - answer the head of the code tree to print
 * Return Value:
 * - none
 * Example call:
 * print(eval());
 * expected return val: null
 */ 
void print(char* answer){
  //TODO
}
