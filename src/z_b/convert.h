#include <stdlib.h>
#include "environment.c"
#include "print.c"

object *convert_symlist(struct symlist *);

object *convert_func(struct symbol *);

//object *convert_exprlist(struct ast *);

object *convert_funccall(struct ufncall *);

object *convert_expr(struct ast *);
