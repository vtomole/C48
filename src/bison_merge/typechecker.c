#include "expression.h"

/*SExpression *typecheck(SExpression *e){
	switch (e->type) {
		case eVALUE:
			return e->value;
		case multiply:
			return typecheck(e->left) * typecheck(e->right);
		case plus:
			return typecheck(e->left) + typecheck(e->right);
		default:          
			return e;
	}
}*/

/*
-Search the original AST from bison/flex
-Check left
-Check right
-Compare these to parent
-return 0 - if there is no error
-return 1 - if there is an error
-may add other error notations in the future to indicate specific errors

int *typecheck(SExpression *e){
	if(e->left != NULL){
		typecheck(e->left);
	}
	if(e->right != NULL){
		return typecheck(e->right);
	}
}
