#include "eval-apply.h"
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
    
    int  first = read_arg(arguments);
    int second = read_arg(cdr(arguments));
    int temp = first + second;
    char* answer = malloc(sizeof(temp));
    sprintf(answer,"%d",temp);
    procedure = create_number(answer);
  }
  else if (strcmp(procedure->variable, "-")== 0){
    //printf("ITS A PLUS\n");
    struct object *object1;
    object *test1 = malloc(sizeof(*object1));

    int  first = read_arg(arguments);
    int second = read_arg(cdr(arguments));
    int temp = first - second;
    char* answer = malloc(sizeof(int));
    snprintf(answer,sizeof(int),"%d",temp);
    procedure = create_number(answer);
  }
  else if (strcmp(procedure->variable, "*")== 0){
    //printf("ITS A PLUS\n");
    struct object *object1;
    object *test1 = malloc(sizeof(*object1));

    int  first = read_arg(arguments);
    int second = read_arg(cdr(arguments));
    int temp = first * second;
    char* answer = malloc(sizeof(int));
    snprintf(answer,sizeof(int),"%d",temp);
    procedure = create_number(answer);
  }
  else if (strcmp(procedure->variable, "/")== 0){
    //printf("ITS A PLUS\n");
    struct object *object1;
    object *test1 = malloc(sizeof(*object1));

    int  first = read_arg(arguments);
    int second = read_arg(cdr(arguments));
    int temp = first / second;
    char* answer = malloc(sizeof(int));
    snprintf(answer,sizeof(int),"%d",temp);
    procedure = create_number(answer);
  }
  else if (strcmp(procedure->variable, "%")== 0){
    //printf("ITS A PLUS\n");
    struct object *object1;
    object *test1 = malloc(sizeof(*object1));

    int  first = read_arg(arguments);
    int second = read_arg(cdr(arguments));
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

//Function is used to recursively call arithmatic operators
int read_arg(object *arg){
  //is a number
  if(arg->cons_cell.car->variable == NULL){
    return arg->cons_cell.car->number;
  }else{
    //is an operator
    return apply_primitive_procedure(arg->cons_cell.car, arg->cons_cell.cdr)->number;
  }
}


/**
 *This function determines whether the given arguement is a number or string
 * Parameters:
 * - exp, this is an object containing an arguement value 
 * Return Value:
 * - 1 if the given object is a number or a string
 * - 0 otherwise
 */
int selfevaluatingp (object *exp){

  if(strcmp(exp->type, "number") == 0){  
    return 1;
  }else if(strcmp(exp->type, "string") == 0){
   
    return 1;
  }
  
 else if(strcmp(exp->type, "boolean") == 0){
    return 1;
  }
   else if(strcmp(exp->type, "empty_list") == 0){
    return 1;
  }

  else{
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
  if(strcmp(exp->type, "primitive") == 0){  
    return 1;
  }else{
    return 0;
  }
}

int variablep (object *exp){
  if(strcmp(exp->type, "variable") == 0){  
    return 1;
  }else{
    return 0;
  }
}
int eqp(object *obj1, object *obj2){
  return obj1 == obj2;
}

int tagged_listp(object *exp, object *tag){
  
  if(pairp(exp)){
    return eqp(car(exp), tag);
  }
  else{
    return 0;
  }

}


int quotep (object *exp){ return tagged_listp(exp,quote); }

object* text_of_quotation (object *exp) { return cadr(exp); }


char no_operandsp(object *ops);
object* first_operand(object *ops);
object* rest_operands(object *ops);



object *eval(object* exp, object* env );
object* list_of_values(object *exps, object *env){
  if(no_operandsp(exps)){
    return empty_list;
  }
  else{
    return cons(eval(first_operand(exps), env),list_of_values(rest_operands (exps), env));
  }

}

char applicationp(object *exp){ return pairp(exp); }
object* operator(object *exp){ return car(exp); }
object* operands(object *exp){ return cdr(exp); }
char no_operandsp(object *ops){ return nullp(ops); }
object* first_operand(object *ops){ return car(ops);}
object* rest_operands(object *ops) {return cdr(ops);}




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

object  *apply(object* exp, object* env){
  object *function , *arguments;
  function = eval(operator(exp),env);
  arguments = list_of_values(operands(exp), env);
  
   if (primitivep(function)){
    return apply_primitive_procedure(function, arguments);
    } else{
     printf("Unkown apply procedure\n");
   }
 
  return function;
}

object* lookup_variable_value(object* exp, object* env){

  if(env == NULL){
    return exp;
  }
  else{
    if (strcmp(car(car(env))->variable, exp->variable) == 0){
    return (car (cdr (car (env))));
    }
    else{
      lookup_variable_value(exp, cdr(env));
  }

 
  }
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
object *eval(object* exp, object* env ){
  object* function, arguments;
 
  if (selfevaluatingp(exp)){    
    return exp;
  }
  else if (variablep(exp)){
    return lookup_variable_value(exp, env);
  }
  else if (quotep(exp)){
    return text_of_quotation(exp);
  }
  /* else if (assignmentp(exp)){
    return eval_assignment(exp, env);
  }
  else if (definitionp(exp)){
    return eval_definition(exp, env);
  }
  else if (ifp(exp)){
    return eval_if(exp,env);
  }
  else if (lambdap(exp)){
    return make_function(lambda_parameters(exp), lambda_body(exp), env);
  }
  else if (beginp(exp)){
    return eval_sequence(begin_actions(exp), env);    
  }
  else if (condp(exp)){
    return eval(cond_to_if(exp), env);
  }
  else if (applicationp(exp)){
    return apply(eval (operator(exp), env), list_of_values(operands(exp),env));
    }*/
    

 else {
        fprintf(stderr, "cannot eval unknown expression type\n");
        exit(1);
    }

}

