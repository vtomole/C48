#include "eval-apply.h"
/**eval_assignmenttp()
 *This function is used to 
 * Parameters:
 * -exp, the expression we are setting variables for 
 * -env, the environment we are typechecking in
 * Returns:
 *-exp, 
 */
object *eval_assignmenttp(object *exp, object *env) {
    set_variable_value(assignment_variable(exp), 
                       eval(assignment_value(exp), env),
                       env);
    //print(exp);
    return exp;
}

/**goto_end()
 *This function is used to goto the end of a given expression
 * Parameters:
 *-expression, the expression we want to see the last value of 
 * Returns:
 *-exp, the end value returned as exp.
 */
object *goto_end (object *exp) {
  object *prev;
  object *next;

  next = exp;

  while (!is_the_empty_list(next)) {
    prev = car(next);
    next = cdr(next);
  }
  //print(prev);

  return exp;

}

/**eval_definitiontp()
 *This function is used to ???
 * Parameters:
 *-exp, an expression or  code tree 
 *-env, the environment we are typechecking in
 * Returns:
 *-exp,???
 */
object *eval_definitiontp(object *exp, object *env) {
    define_variable(definition_variable(exp), 
                    eval(definition_value(exp), env),
                    env);
    return exp;
}

/**typecheck()
 *This function is used to typecheck the given code tree. This goes through each statement recursively and makes sure that the expressions match the with proper variables 
 *This function doesn't alter the code tree it just errors out if there is a problem
 * Parameters:
 *-exp, The start of the expression(code Tree) we want to typecheck
 *-env, The environment our types are defined in, also holds user variables and definitions
 * Returns:
 *-exp, The original expression sent in unless it errors out if there is a type error
 */
object *typecheck(object *exp, object *env) {
    object *procedure;
    object *arguments;
    object *type_object;
    object *primary_type;
    object *acceptables;
    object *type_arguments;
    object* static_exp;
    object *end_list;

    static_exp = exp;

tailcall:
    if (self_evaluatingp(exp)) {
        return static_exp;
    }
	else if (variablep(exp)) {
      return lookup_variable_value(exp, env);
    }
	else if (is_quoted(exp)) {//what is a quoted?
        return static_exp;
    }
	else if (is_assignment(exp)) {
      //printf("It's an assignment \n");
      return eval_assignmenttp(exp, env);
    }
	else if (is_definition(exp)) {
      //printf("It's define \n");
        return eval_definitiontp(exp, env);
    }
	else if (is_if(exp)) {//exp is an if/else if expression
      //printf("It's if \n");
        exp = is_true(eval(if_predicate(exp), env)) ?
                  if_consequent(exp) :
                  if_alternative(exp);
        goto tailcall;
    }
	else if (is_lambda(exp)) {//exp is a lambda expression
		//printf("It's lambda \n");
        return make_compound_proc(lambda_parameters(exp),
                                  lambda_body(exp),
                                  env);
    }
	else if (is_begin(exp)) {//exp is part of a compound procedure
      //printf("It's begin \n");
        exp = begin_actions(exp);
        while (!is_last_exp(exp)) {
            eval(first_exp(exp), env);
            exp = rest_exps(exp);
        }
        exp = first_exp(exp);
        goto tailcall;
    }
	else if (is_cond(exp)) {
      //printf("It's cond \n");
        exp = cond_to_if(exp);
        goto tailcall;
    }
	else if (is_let(exp)) {
      //printf("It's let \n");
        exp = let_to_application(exp);
        goto tailcall;
    } 
	else if (is_application(exp)) {
		//printf("It's apply \n");
		procedure = eval(operator(exp), env);
		arguments = list_of_values(operands(exp), env);
		type_arguments = list_of_values(operands(exp), env);	
		if (primitivep(procedure)) {
			acceptables = procedure->primitive_proc.acceptables;
		
			//Determine the type of the first operand
			primary_type = car(cdr(type_arguments));'
	  
			//check the remaining operands and make sure they match the first
			while (!is_the_empty_list(type_arguments)) {
				if(primary_type->obj_type != car(type_arguments)->obj_type){
					fprintf(stderr, "Type error expression\n");
					exit(1);
				}	      
				type_arguments = cdr(type_arguments);
			}
	  
			type_arguments = list_of_values(operands(exp), env);

			int type_flag = 0;

			while (!is_the_empty_list(acceptables)) {
				if(primary_type->obj_type == car(acceptables)->number){
					type_flag = 1;
				}	     
				acceptables = cdr(acceptables);
			}
	  
			if(type_flag == 0){
				fprintf(stderr, "Type error variables\n");
				exit(1);
			}

			//printf("Static exp\n");
			//print(static_exp);
			return static_exp;
        }
		else if (is_compound_proc(procedure)) {
	  
			env = extend_environment( 
                       procedure->compound_proc.parameters,
                       arguments,
                       procedure->compound_proc.env);
			exp = make_begin(procedure->compound_proc.body);
	    
			goto tailcall;
		}
		else {
			fprintf(stderr, "unknown procedure type\n");
			exit(1);
		}
    } 
	else {
        fprintf(stderr, "cannot eval unknown expression type\n");
        exit(1);
    }
    fprintf(stderr, "eval illegal state\n");
    exit(1);
}
