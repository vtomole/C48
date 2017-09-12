char  *apply(char operator, int arguments[]){
  
  int i;
  char* answer = (char*)malloc(8 * sizeof(char));
  switch(operator){
  case '+':
    sprintf(answer, "%d", arguments[0] + arguments[1]);
    return ahnswer;
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
}
