
/* interface to the lexer */
extern int yylineno; /* from lexer */
void yyerror(char *s, ...);


/*to read commands from a file */
int open_file(const char *name);
