%{
#  include <stdio.h>
#  include <stdlib.h>
#  include <string.h>
#  include "environment-bison-merge.c"
#  include "eval-bison-merge.c"
#  include "print-bison-merge.c"
#  include "expression.h"

int yylex();

/* (+ 5 6) -> cons(left (cons right (cons left null)  null))    */
object *convert_ast(struct ast *e){
  if(!e){
    yyerror("Internal error, null eval");
  }
  switch (e->nodetype) {
  /*constant*/
  case 'K': return create_number(((struct numval *)e)->number);

/*name reference*/
  case 'N' : return create_number(((struct symref *)e)->s->value);

    /*assignment */
    /*case '=':  return create_symbol(((struct symasgn *)e)->s->value);*/
 
  case '+':
    return cons(create_symbol("+"),cons(convert_ast(e->l), cons(convert_ast(e->r), empty_list)));

  case '-':
    return cons(create_symbol("-"),cons(convert_ast(e->l), cons(convert_ast(e->r), empty_list)));
    
  case '*':
    return cons(create_symbol("*"),cons(convert_ast(e->l), cons(convert_ast(e->r), empty_list)));

    case '/':
    return cons(create_symbol("/"),cons(convert_ast(e->l), cons(convert_ast(e->r), empty_list)));

    /*comparisons*/ 
  case '1': return cons(create_symbol(">"),cons(convert_ast(e->l), cons(convert_ast(e->r), empty_list)));

  case '2': return cons(create_symbol("<"),cons(convert_ast(e->l), cons(convert_ast(e->r), empty_list)));

  case '3': return cons(create_symbol("!="),cons(convert_ast(e->l), cons(convert_ast(e->r), empty_list)));

  case '4': return cons(create_symbol("=="),cons(convert_ast(e->l), cons(convert_ast(e->r), empty_list)));

  case '5': return cons(create_symbol(">="),cons(convert_ast(e->l), cons(convert_ast(e->r), empty_list)));

  case '6': return cons(create_symbol("<="),cons(convert_ast(e->l), cons(convert_ast(e->r), empty_list)));

  /*control flow*/

  }  
}
%}

%union {
  struct ast *a;
  double d;
  struct symbol *s;		/* which symbol */
  struct symlist *sl;
  int fn;			/* which function */
}

/* declare tokens */
%token <d> NUM
%token <s> NAME
%token <fn> FUNC
%token EOL

%token IF THEN ELSE WHILE DO LET


%nonassoc <fn> CMP
%right '='
%left '+' '-'
%left '*' '/'
%nonassoc '|' UMINUS

%type <a> exp stmt list explist
%type <sl> symlist

%start calclist

%%

stmt: IF exp THEN list           { $$ = newflow('I', $2, $4, NULL); }
   | IF exp THEN list ELSE list  { $$ = newflow('I', $2, $4, $6); }
   | WHILE exp DO list           { $$ = newflow('W', $2, $4, NULL); }
   | exp
;

list: /* nothing */ { $$ = NULL; }
   | stmt ';' list { if ($3 == NULL)
	                $$ = $1;
                      else
			$$ = newast('L', $1, $3);
                    }
   ;

exp: exp CMP exp          { $$ = newcmp($2, $1, $3); }
   | exp '+' exp          { $$ = newast('+', $1,$3); }
   | exp '-' exp          { $$ = newast('-', $1,$3);}
   | exp '*' exp          { $$ = newast('*', $1,$3); }
   | exp '/' exp          { $$ = newast('/', $1,$3); }
   | '|' exp              { $$ = newast('|', $2, NULL); }
   | '(' exp ')'          { $$ = $2; }
   | '-' exp %prec UMINUS { $$ = newast('M', $2, NULL); }
   | NUM               { $$ = newnum($1); }
   | FUNC '(' explist ')' { $$ = newfunc($1, $3); }
   | NAME                 { $$ = newref($1); }
   | NAME '=' exp         { $$ = newasgn($1, $3); }
   | NAME '(' explist ')' { $$ = newcall($1, $3); }
;

explist: exp
 | exp ',' explist  { $$ = newast('L', $1, $3); }
;
symlist: NAME       { $$ = newsymlist($1, NULL); }
 | NAME ',' symlist { $$ = newsymlist($1, $3); }
;

calclist: /* nothing */
  | calclist stmt EOL {
    if(debug) dumpast($2, 0);
    initialize_environment();
    print(convert_ast($2));
    printf("\n");
    print(eval(convert_ast($2), environment));
    printf("\n");
    printf(">");
    //printf("= %4.4g\n> ", evaluate($2));
     treefree($2);
    }
  | calclist LET NAME '(' symlist ')' '=' list EOL {
                       dodef($3, $5, $8);
                       printf("Defined %s\n> ", $3->name); }

  | calclist error EOL { yyerrok; printf("> "); }
 ;
%%
