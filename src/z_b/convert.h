#include <stdlib.h>
#include <string.h>
#include "../environment.c"
#include "../eval-apply.c"
#include "../print.c"

object *convert_symlist(struct symlist *);

object *convert_func(struct symbol *);

//object *convert_exprlist(struct ast *);

object *convert_funccall(struct ufncall *);

object *convert_expr(struct ast *);
