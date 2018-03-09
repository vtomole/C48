#include <stdlib.h>
#include "object.c"
#include "print.c"

object *convert_list(struct symlist *);

object *convert_func(struct symbol *);

object *convert(struct ast *);

