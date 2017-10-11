
/**
 *This function determines whether the given arguement is a number or string
 * Parameters:
 * - exp, this is an object containing an arguement value 
 * Return Value:
 * - 1 if the given object is a number or a string
 * - 0 otherwise
 */
int self_evaluatingp (object *exp){
  if(strcmp(exp->type, "number") == 0){  
    return 1;
  }else if(strcmp(exp->type, "string") == 0){
    return 1;
  }else{
    return 0;
  }
}

/**
 *This function determines whether a given expression is primitive
 * Parameters:
 * - exp, this is an object containing an expression
 * Return Value:
 * - 1 if the given object is a primitive expression
 * - 0 otherwise
 */
int primitivep (object *exp){
  if(strcmp(exp->type, "primop") == 0){  
    return 1;
  }else{
    return 0;
  }
}

/**
 *This function executes our primitive operations i.e. +, -, *, /
 * Parameters:
 * - procedure,
 * - arguments, 
 * Return Value:
 * - procedure, 
 */
object *apply_primitive_procedure(object *procedure , object *arguments){
  if(strcmp(procedure->variable, "+")== 0){
    //printf("ITS A PLUS\n");
    struct object *object1;
    object *test1 = malloc(sizeof(*object1));

    int  first = car(arguments)->number;
    int second = car(cdr(arguments))->number;
    int temp = first + second;
    char* answer = malloc(sizeof(temp));
    sprintf(answer,"%d",temp);
    procedure = create_number(answer);
  }
  else if (strcmp(procedure->variable, "-")== 0){
    //printf("ITS A PLUS\n");
    struct object *object1;
    object *test1 = malloc(sizeof(*object1));

    int  first = car(arguments)->number;
    int second = car(cdr(arguments))->number;
    int temp = first - second;
    char* answer = malloc(sizeof(int));
    snprintf(answer,sizeof(int),"%d",temp);
    procedure = create_number(answer);
  }
  else if (strcmp(procedure->variable, "*")== 0){
    //printf("ITS A PLUS\n");
    struct object *object1;
    object *test1 = malloc(sizeof(*object1));

    int  first = car(arguments)->number;
    int second = car(cdr(arguments))->number;
    int temp = first * second;
    char* answer = malloc(sizeof(int));
    snprintf(answer,sizeof(int),"%d",temp);
    procedure = create_number(answer);
  }
  else if (strcmp(procedure->variable, "/")== 0){
    //printf("ITS A PLUS\n");
    struct object *object1;
    object *test1 = malloc(sizeof(*object1));

    int  first = car(arguments)->number;
    int second = car(cdr(arguments))->number;
    int temp = first / second;
    char* answer = malloc(sizeof(int));
    snprintf(answer,sizeof(int),"%d",temp);
    procedure = create_number(answer);
  }
  else if (strcmp(procedure->variable, "%")== 0){
    //printf("ITS A PLUS\n");
    struct object *object1;
    object *test1 = malloc(sizeof(*object1));

    int  first = car(arguments)->number;
    int second = car(cdr(arguments))->number;
    int temp = first % second;
    char* answer = malloc(sizeof(int));
    snprintf(answer,sizeof(int),"%d",temp);
    procedure = create_number(answer);
  }
  else{
    printf("Procedure has not been implemented yet\n"); 
  }

  return procedure;
}

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
object  *apply(object *procedure , object* arguments){
   if (primitivep(procedure)){
     procedure = apply_primitive_procedure(procedure, arguments);
    } else{
     printf("Unkown apply procedure\n");
   }
 
  return procedure;
}

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
object *eval(object* exp, token_list* env ){
  if (self_evaluatingp(exp)){
    return exp;
  } else{
    exp = apply(car(exp), cdr(exp));
  }
 
  return exp;
}

