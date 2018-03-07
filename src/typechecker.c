#include "expression.h"

/**********************************************************
* Notes
*
* Data types:
*
* Env: environment for evaluating the scopes
* Expr: parent model of Expr_
* Expr_Add:
* Expr_Double:
* Expr_Int:
* Expr_Var:
* object: Node from tree, arguement in this situation
* Prog: Used to read statements, similar to Stm_Block
* Program: Assumed to be the orignal tree
* scope: layers of the program that contain variable names
* Stm: parent model of Stm_
* Stm_Assign:
* Stm_Block:
* Stm_Decl:
* Stm_Print:
* Type: Parent model of Type_
* Type_Int:
* Type_Double:
* typeCode: enum of the data types, assumed to be types from lexer.l

***********************************************************/
/*TypeChecker elements*/

/*enum the types an object can be*/
static enum typeCode{
	ERROR,
	NUMBER,
	VALUE
	/*NAME,
	NUM,
	EOL*/	
}

/*Environment elements*/
typedef struct scope{
	char *name;
	scope *next;
}scope;

static scope scopes = enterScope();

typeCode lookUpVar(char *x){
	scope cur = scopes;
	while(cur != NULL){
		typeCode t = cur.name; /*interesting*/
		if(t != NULL)
			return t;
		cur = cur->next;
	}
	return 0; /*error needs to be thrown*/
}

void addVar(char *x, typeCode t){
	scope cur = scopes;
	scope newScope; /* need to allocate memory */

	/*iterate through current scopes*/
	while(cur != NULL){
		if(strcmp(cur->name, x) == 0)
			/* needs to throw an error */
		cur = cur->next;
	}
	
	/* declare and add new scope */
	cur->next = newScope;
}
	
void enterScope(){
	scope newScope; /* need to allocate memory */

	scopes->next = newScope;
}

void leaveScope(){
	/* need to free memory */
	scopes->next = NULL;
}

/*typecheck elements*/

void typecheck(object *e){
	Prog prog = (Prog e);
	Env env = new Env(); //fix new
	for(Stm s : prog.liststm_){
		checkStm(s, env);
	}
}

/*statement accepter elements*/

void checkStm(Stm st, Env env){
	//call the statement checker in the environment
	//make sure it accepts. make sure type is valid in env.
}

/*statement checker elements*/
//contains the methods of the java StmChecker class that implements Stm.Visitor

object visit(Stm_Decl p, Env env){
	env.addVar(p.ident_, typeCode(p.type_));
	return null;
}

object visit(Stm_Assign p, Env env){
	TypeCode t = env.lookUpVar(p.ident_);
	checkExpr(p.expr_, t, env);
	return null;
}

object visit(Stm_Block p, Env env){
	env.enterScope(); /* under environment elements */
	for(Stm s : p.liststm_){
		checkStm(s, env);
	}
	env.leaveScope();
	return null;
}

object visit(Stm_Print p, Env env){
	//make sure that a type must exist
	inferExpr(p.expr_, env);
	return null;
}

/*expression checker elements*/

void checkExpr(Expr e, TypeCode t, Env env){
	TypeCode expr_type = inferExpr(e, env);
	if(expr_type != t){
		/* needs to throw an error*/
	}
}

/*type inference elements*/
//contains the methods of the java TypeInferrer class that implements Exp.Visitor

TypeCode visit(Expr_Var p, Env env){
	return env.lookupVar(p.ident_);
}

TypeCode visit(Expr_Int p, Env env){
	return TypeCode.INT;
}

TypeCode visit(Expr_Double p, Env env){
	return TypeCode.DOUBLE;
}

TypeCode visit(Expr_Add p, Env env){
	TypeCode t1 = p.expr_1.accept(this, env); //this refers to p
	TypeCode t2 = p.expr_2.accept(this, env);
		
	if(t1 != t2){
		/* needs to throw an error */
	}

	return t1;
}

/*TypeCode elements*/
TypeCode typeCode(Type t){
	return t.accept(new TypeCoder(), null); //fix new
}

/*TypeCoder elements*/
//contains the methods of the java TypeCoder class that implements Type.Visitor

TypeCode visit(Type_Int t, object arg){
	return TypeCode.INT;
}

TypeCode visit(Type_Double t, object arg){
	return TypeCode.DOUBLE;
}


