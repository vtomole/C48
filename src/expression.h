
/* interface to the lexer */
extern int yylineno; /* from lexer */
void yyerror(char *s, ...);


/*to read commands from a file */
int open_file(const char *name);

void init(void);

void load_file_scm(char* fileName);

void yyset_in  (FILE * _in_str);

int yyparse (void);

int yylex (void);



