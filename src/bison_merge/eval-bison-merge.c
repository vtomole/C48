#include "eval-apply.h"

object* eval(object *exp, object *env );
object* eval_assignment(object *exp, object *env){
  
  set_variable_value(assignment_variable(exp), eval(assignment_value(exp), env), env);
  
    return ok_symbol;

}
object* definition_variable (object *exp);
object* eval_definition(object *exp, object *env){

  define_variable(definition_variable(exp), eval(definition_variable(exp),env), env);

  return ok_symbol;
}  


/**
 *This function determines whether the given arguement is a number or string
 * Parameters:
 * - exp, this is an object containing an arguement value 
 * Return Value:
 * - 1 if the given object is a number or a string
 * - 0 otherwise
 */
int self_evaluatingp (object *exp){
  return booleanp(exp) || numberp(exp) || characterp(exp) || stringp(exp) || nullp(exp);
}

/**
 *This function determines whether a given expression is primitive
 * Parameters:
 * - exp, this is an object containing an expression
 * Return Value:
 * - 1 if the given object is a primitive expression
 * - 0 otherwise
 */
int primitivep (object *exp){ return exp->obj_type == PRIMITIVE_PROCEDURE;}

int variablep (object *exp){ return symbolp(exp); }

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

int quotep (object *exp){ return tagged_listp(exp,quote_symbol); }
int assignmentp(object *exp){ return tagged_listp(exp, set_symbol); }
int definitionp(object *exp){ return tagged_listp(exp, define_symbol);}
int ifp(object *exp){ return tagged_listp(exp, if_symbol);}
int lambdap(object *exp){ return tagged_listp(exp, lambda_symbol);}
int beginp(object *exp){ return tagged_listp(exp, begin_symbol);}
int last_expp(object *seq){ return nullp(cdr(seq));}
object* first_exp(object *seq){ return car(seq);}
object* rest_exps(object *seq){ return cdr(seq);}
object* begin_actions(object* exp){ return cdr(exp); }
object* lambda_parameters(object *exp){ return cadr(exp); }
object* lambda_body(object *exp){ return cddr(exp); }
object* if_predicate(object *exp){ return cadr(exp); }
object* if_consequent(object *exp){ return caddr(exp); }
object* if_alternative(object *exp){
  if(nullp(cadddr(exp))){
    return false_symbol;
  }
  else{
    return cadddr(exp);
  }
}

object* make_if(object *predicate, object *consequent, object *alternative){
  return (cons(if_symbol,
	       cons(predicate,
		    cons(consequent,
			 cons(alternative, empty_list)))));
}

object* definition_variable (object *exp){
  if(symbolp(cadr (exp))){
    return cadr(exp);
  }
  else{
    return caadr(exp);
  }
}

object* text_of_quotation (object *exp) { return cadr(exp); }
char no_operandsp(object *ops);
object* first_operand(object *ops);
object* rest_operands(object *ops);

object* make_begin(object *seq){ return cons(begin_symbol, seq); }
object* sequence_to_exp(object *seq){
  if(nullp(seq)){
    return seq;
  }
  else if (last_expp(seq)){
    return first_exp(seq);
  }
  else{
    return make_begin(seq);
  }
}


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


/*cond functions */
int condp(object *exp){ return tagged_listp(exp, cond_symbol); }

object* cond_clauses(object *exp){ return cdr(exp); }
object* cond_predicate(object *clause){ return car(clause); }
int cond_else_clausep (object *clause){
  return eqp(cond_predicate(clause), else_symbol);
}
object* cond_actions(object *clause){ return cdr(clause); }

object* expand_clauses(object *clauses){
  object *first, *rest;
  
  if(nullp(clauses)){
    return false_symbol;
  }
  else{
    first = car(clauses);
    rest = cdr(clauses);

    if(cond_else_clausep(first)){
      if(nullp(rest)){
	  return sequence_to_exp(cond_actions(first));
	}
	else{
	  fprintf(stderr, "ELSE clause isn't last: COND->IF");
	}
    }
  
  else{
    return make_if(cond_predicate(first), sequence_to_exp(cond_actions(first)), expand_clauses(rest));
      
  }
  
}
}	
    

object* cond_to_if (object *exp){
  return expand_clauses(cond_clauses(exp));
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

object  *apply(object* exp, object* env){
  object *procedure , *arguments;
  
  {
        procedure = eval(operator(exp), env);
        arguments = list_of_values(operands(exp), env);

        if (primitivep(procedure)) {
            return (procedure->primitive_procedure.fn)(arguments);
        }
        else if (compoundp(procedure)) {
            env = extend_environment( 
                       procedure->compound_procedure.parameters,
                       arguments,
                       procedure->compound_procedure.env);
            exp = make_begin(procedure->compound_procedure.body);
            return exp;
        }
        else {
            fprintf(stderr, "unknown procedure type\n");
            exit(1);
        }
    }
 
}

object* eval_if(object *exp, object *env){
  if(truep (eval(if_predicate(exp), env))){
    eval(if_consequent(exp), env);
  }
  else{
    eval(if_alternative(exp), env);
  }
}

object* eval_sequence(object *exp, object *env){
   while(!last_expp(exp)){
    eval(first_exp(exp), env);
    exp = rest_exps(exp);
  }
  exp = first_exp(exp);
  return exp;
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
  object* procedure, *arguments;

  if(exp->obj_type){
  tailcall:
  if (self_evaluatingp(exp)){
    return exp;
  }
  else if (variablep(exp)){
    return lookup_variable_value(exp, env);
  }
  else if (quotep(exp)){
    return text_of_quotation(exp);
  }
  else if (assignmentp(exp)){
    return eval_assignment(exp, env);
  }
  else if (definitionp(exp)){
    return eval_definition(exp, env);
  }
  else if (ifp(exp)){
    exp = eval_if(exp,env);
    goto tailcall;
  }
  else if (lambdap(exp)){
    return make_procedure(lambda_parameters(exp), lambda_body(exp), env);
  }
  else if (beginp(exp)){
    exp = eval_sequence(begin_actions(exp), env);
    goto tailcall;
  }
  else if (condp(exp)){
    exp = eval(cond_to_if(exp), env);
    goto tailcall;
  }
  else if (applicationp(exp)){
    exp = apply(exp, env);
    goto tailcall;

  }
  
 else {
        fprintf(stderr, "cannot eval unknown expression type\n");
        exit(1);
	}
  }else{
     printf("Object is null \n");
  }
  
}




