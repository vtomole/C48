#include "expression.h"

/*TypeChecker elements*/

/*enum the types an object can be*/
static enum typeCode{
	ERROR,
	NUMBER,
	VALUE
}

/*Environment elements*/

static scope scopes = enterScope(); /*need to make scope struct*/

typeCode lookUpVar(char *x){
	scope cur = scopes;
	while(cur != NULL){
		typecode t = cur.name;
		if(t != NULL)
			return t;
		cur = cur->next;
	}
	return 0; /*error needs to be thrown*/
}

void addVar(char *x, typeCode t){
	scope cur = scopes;
	scope newScope;

	/*iterate through current scopes*/
	while(cur != NULL){
		if(strcmp(cur->name, x) == 0)
			/* needs to throw an error */
		cur = cur->next;
	}
	
	/* declare and add new scope */
	cur.addScope(x, t);
}
	
void enterScope(){
	scopes.addScope();
}

void leaveScope(){
	scopes.removeScope();
}

/*typecheck elements*/

void typecheck(Program p){
	Prog prog = (Prog p);
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

Object visit(Stm_Decl p, Env env){
	env.addVar(p.ident_, typeCode(p.type_));
	return null;
}

Object visit(Stm_Assign p, Env env){
	TypeCode t = env.lookUpVar(p.ident_);
	checkExpr(p.expr_, t, env);
	return null;
}

Object visit(Stm_Block p, Env env){
	env.enterScope(); /* under environment elements */
	for(Stm s : p.liststm_){
		checkStm(s, env);
	}
	env.leaveScope();
	return null;
}

Object visit(Stm_print p, Env env){
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

TypeCode visit(Expr_add p, Env env){
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

TypeCode visit(Type_INT t, Object arg){
	return TypeCode.INT;
}

TypeCode visit(Type_Double t, Object arg){
	return TypeCode.DOUBLE;
}


