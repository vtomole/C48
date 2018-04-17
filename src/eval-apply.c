#include "eval-apply.h"

/*Temporary import of print if this breaks expression.c this is why*/
/**print()
 *this function is used to print our token_list/code tree
 * Parameters:
 *-obj, the object pointer representing the head of the list/tree we want to print
 */
void print(object *obj);
object *make_lambda(object *parameters, object *body);

/**self_evaluatingp()
 *this function checks whether the function is primitive
 * Parameters:
 *-exp, the procedure we are trying to check
 * Returns:
 *-1 if the object is a primitive_proc,
 *-0 otherwise
 */
int self_evaluatingp(object *exp) {
    return booleanp(exp) || numberp(exp) || characterp(exp) || floatp(exp) ||
           is_string(exp);
}

char variablep(object *expression) { return is_symbol(expression); }

/**is_tagged_list()
 *this function checks whether we have tagged the list
 * Parameters:
 *-expression,
 * Returns:
 *-1 if the first object of expression is a symbor and tag is set
 *-0 otherwise
 */
char is_tagged_list(object *expression, object *tag) {
    object *the_car;

    if (is_pair(expression)) {
        the_car = car(expression);
        return is_symbol(the_car) && (the_car == tag);
    }
    return 0;
}

char is_quoted(object *expression) { return is_tagged_list(expression, quote_symbol);
char is_definition(object *exp) { return is_tagged_list(exp, define_symbol); } }
char is_assignment(object *exp) { return is_tagged_list(exp, set_symbol); }
object *text_of_quotation(object *exp) { return cadr(exp); }
object *assignment_variable(object *exp) { return car(cdr(exp)); }
object *assignment_value(object *exp) { return car(cdr(cdr(exp))); }

/**definition_variable()
 *this function checks ??
 * Parameters:
 *-exp, the object we are checking the definition of
 * Returns:
 *-cadr(exp) the value of the given object, if the object is a symbol/operator
 *-caadr(exp) the rest of the given list, otherwise
 */
object *definition_variable(object *exp) {
    if (is_symbol(cadr(exp))) {
        return cadr(exp);
    }
    else {
        return caadr(exp);
    }
}

/**definition_value()
 *this function checks ??
 * Parameters:
 *-exp, the object we are defining the of value of
 * Returns:
 *-cadr(exp) the value of the given object, if the object is a symbol/operator
 *-caadr(exp) the rest of the given list, otherwise
 */
object *definition_value(object *exp) {
    if (is_symbol(cadr(exp))) {
        return caddr(exp);
    }
    else {
        return make_lambda(cdadr(exp), cddr(exp));
    }
}

object *make_if(object *predicate, object *consequent,
                object *alternative) {
    object *end = the_empty_list;
    if(alternative->obj_type != EMPTY_LIST){
      end = cons(alternative, the_empty_list);
    }
    return cons(if_symbol,
                cons(predicate,
                     cons(consequent,
                          end)));
}

char is_if(object *expression) { return is_tagged_list(expression, if_symbol); }
object *if_predicate(object *exp) { return cadr(exp); }
object *if_consequent(object *exp) { return caddr(exp); }

object *if_alternative(object *exp) {
    if (is_the_empty_list(cdddr(exp))) {
        return false;
    }
    else {
        return cadddr(exp);
    }
}

object *make_lambda(object *parameters, object *body) { return cons(lambda_symbol, cons(parameters, body)); }
char is_lambda(object *exp) { return is_tagged_list(exp, lambda_symbol); }
object *lambda_parameters(object *exp) { return cadr(exp); }
object *lambda_body(object *exp) { return cddr(exp); }
object *make_begin(object *seq) { return cons(begin_symbol, seq); }
char is_begin(object *exp) { return is_tagged_list(exp, begin_symbol); }
object *begin_actions(object *exp) { return cdr(exp); }
char is_last_exp(object *seq) { return is_the_empty_list(cdr(seq)); }
object *first_exp(object *seq) { return car(seq); }
object *rest_exps(object *seq) { return cdr(seq); }
char is_cond(object *exp) { return is_tagged_list(exp, cond_symbol); }
object *cond_clauses(object *exp) { return cdr(exp); }
object *cond_predicate(object *clause) { return car(clause); }
object *cond_actions(object *clause) { return cdr(clause); }
char is_cond_else_clause(object *clause) { return cond_predicate(clause) == else_symbol; }

object *sequence_to_exp(object *seq) {
    if (is_the_empty_list(seq)) {
        return seq;
    }
    else if (is_last_exp(seq)) {
        return first_exp(seq);
    }
    else {
        return make_begin(seq);
    }
}

object *expand_clauses(object *clauses) {
    object *first;
    object *rest;
    
    if (is_the_empty_list(clauses)) {
        return false;
    }
    else {
        first = car(clauses);
        rest  = cdr(clauses);
        if (is_cond_else_clause(first)) {
            if (is_the_empty_list(rest)) {
                return sequence_to_exp(cond_actions(first));
            }
            else {
                fprintf(stderr, "else clause isn't last cond->if");
                exit(1);
            }
        }
        else {
            return make_if(cond_predicate(first),
                           sequence_to_exp(cond_actions(first)),
                           expand_clauses(rest));
        }
    }
}

object *cond_to_if(object *exp) { return expand_clauses(cond_clauses(exp)); }
object *make_application(object *operator, object *operands) { return cons(operator, operands); }
char is_application(object *exp) { return is_pair(exp); }
object *operator(object *exp) { return car(exp); }
object *operands(object *exp) { return cdr(exp); }
char is_no_operands(object *ops) { return is_the_empty_list(ops); }
object *first_operand(object *ops) { return car(ops); }
object *rest_operands(object *ops) { return cdr(ops); }
char is_let(object *exp) { return is_tagged_list(exp, let_symbol); }
object *let_bindings(object *exp) { return cadr(exp); }
object *let_body(object *exp) { return cddr(exp); }
object *binding_parameter(object *binding) { return car(binding); }
object *binding_argument(object *binding) { return cadr(binding); }

object *bindings_parameters(object *bindings) {
	return is_the_empty_list(bindings) ?
               the_empty_list :
               cons(binding_parameter(car(bindings)),
                    bindings_parameters(cdr(bindings)));
}

object *bindings_arguments(object *bindings) {
    return is_the_empty_list(bindings) ?
               the_empty_list :
               cons(binding_argument(car(bindings)),
                    bindings_arguments(cdr(bindings)));
}

object *let_parameters(object *exp) { return bindings_parameters(let_bindings(exp)); }
object *let_arguments(object *exp) { return bindings_arguments(let_bindings(exp)); }

object *let_to_application(object *exp) {
    return make_application(
               make_lambda(let_parameters(exp),
                           let_body(exp)),
               let_arguments(exp));
}

object *eval(object *exp, object *env);

object *list_of_values(object *exps, object *env) {
    if (is_no_operands(exps)) {
        return the_empty_list;
    }
    else {
        return cons(eval(first_operand(exps), env),
                    list_of_values(rest_operands(exps), env));
    }
}

object *eval_assignment(object *exp, object *env) {
    set_variable_value(assignment_variable(exp), 
                       eval(assignment_value(exp), env),
                       env);
    //print(exp);
    return ok_symbol;
}

object *eval_definition(object *exp, object *env) {
    define_variable(definition_variable(exp), 
                    eval(definition_value(exp), env),
                    env);
    //print(exp);
    return ok_symbol;
}


object *eval(object *exp, object *env) {
    object *procedure;
    object *arguments;

tailcall:
    if (self_evaluatingp(exp)) {
        return exp;
    }
    else if (variablep(exp)) {
      //printf("Lookup\n");
        return lookup_variable_value(exp, env);
    }
    else if (is_quoted(exp)) {
        return text_of_quotation(exp);
    }
    else if (is_assignment(exp)) {
        return eval_assignment(exp, env);
    }
    else if (is_definition(exp)) {
        return eval_definition(exp, env);
    }
    else if (is_if(exp)) {
        exp = is_true(eval(if_predicate(exp), env)) ?
                  if_consequent(exp) :
                  if_alternative(exp);
        goto tailcall;
    }
    else if (is_lambda(exp)) {
        return make_compound_proc(lambda_parameters(exp),
                                  lambda_body(exp),
                                  env);
    }
    else if (is_begin(exp)) {
        exp = begin_actions(exp);
        while (!is_last_exp(exp)) {
            eval(first_exp(exp), env);
            exp = rest_exps(exp);
        }
        exp = first_exp(exp);
        goto tailcall;
    }
    else if (is_cond(exp)) {
        exp = cond_to_if(exp);
        goto tailcall;
    }
    else if (is_let(exp)) {
        exp = let_to_application(exp);
        goto tailcall;
    }
    else if (is_application(exp)) {
      procedure = eval(operator(exp), env);
        arguments = list_of_values(operands(exp), env);
        if (primitivep(procedure)) {
            return (procedure->primitive_proc.fn)(arguments);
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


