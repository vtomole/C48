#include <stdlib.h>
#include <string.h>
#include "../environment.c"
#include "../eval-apply.c"
#include "../print.c"

object *convert(struct ast *);

//Builds properly
object *convert_symlist(struct symlist *);

//Builds properly
object *convert_func(struct symbol *);

object *convert_exprlist(struct ast *);

//Builds properly
object *convert_funccall(struct ufncall *);

//Builds properly (except return)
object *convert_builtinfunc(struct fncall *);

//Builds properly
object *convert_varexpr(struct ast *);

object *convert_expr(struct ast *);


