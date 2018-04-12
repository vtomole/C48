%{
#  include <stdio.h>
#  include <stdlib.h>
#  include "expression.h"
#  include "convert.c"
%}

%union {
  struct ast *a;
  double d;
  struct symbol *s;		/* which symbol */
  struct symlist *sl;
  int fn;			/* which function */
}

/* declare tokens */
%token <d> NUMBER
%token <s> NAME
%token <fn> FUNCT
%token EOL 

%token IF THEN ELSE WHILE DO FUN FOR END RETURN


%nonassoc <fn> CMP
%right '='
%left '+' '-'
%left '*' '/' '%'
%nonassoc '|' UMINUS

%type <a> exp stmt list explist
%type <sl> symlist

%start calclist

%%

stmt:IF '(' exp ')' '{' list '}'                   { $$ = newflow('I', $3, $6, NULL); }
   | IF '(' exp ')'  '{' list '}' ELSE '{'list '}'  { $$ = newflow('I', $3, $6, $10); }
   | IF '(' exp ')'  '{' list '}' ELSE stmt         { $$ = newflow('I', $3, $6, $9); }
   | WHILE '(' exp ')'  '{' list '}'                { $$ = newflow('W', $3, $6, NULL); }    
   | exp
;

list: /* nothing */ { $$ = NULL; }
   | stmt ';' list { if ($3 == NULL) $$ = $1; else $$ = newast('L', $1, $3); }
   ;

exp: exp CMP exp          { $$ = newcmp($2, $1, $3); }
   | exp '+' exp          { $$ = newast('+', $1,$3); }
   | exp '-' exp          { $$ = newast('-', $1,$3);}
   | exp '*' exp          { $$ = newast('*', $1,$3); }
   | exp '/' exp          { $$ = newast('/', $1,$3); }
   | exp '%' exp          { $$ = newast('%', $1,$3); }
   | '|' exp              { $$ = newast('|', $2, NULL); }
   | '(' exp ')'          { $$ = $2; }
   | '-' exp %prec UMINUS { $$ = newast('M', $2, NULL); }
   | NUMBER               { $$ = newnum($1); }
   | FUNCT '(' explist ')'{ $$ = newfunc($1, $3); }
   | NAME                 { $$ = newref($1); }
   | NAME '=' exp         { $$ = newasgn($1, $3); }
   | NAME '(' explist ')' { $$ = newcall($1, $3); }
   | RETURN exp           { $$ = $2; }
;

explist:            { $$ = NULL; }
 | exp
 | exp ',' explist  { $$ = newast('L', $1, $3); }
;
symlist:      { $$ = NULL; }
 | NAME       { $$ = newsymlist($1, NULL); }
 | NAME ',' symlist { $$ = newsymlist($1, $3); }
;

calclist: /* nothing */
  | calclist EOL
  | calclist stmt ';' 
    //{ if(debug) dumpast($2, 0); printf("= %4.4g\n> ", eval_ast($2)); treefree($2); }
    { if(debug) dumpast($2, 0); print(convert_expr($2)); treefree($2); printf("\n"); }
    //{ test_print(); }
            
  | calclist FUN NAME '(' symlist ')' '{' list '}' 
    //{ dodef($3, $5, $8); printf("Defined %s\n> ", $3->name); }
	  { dodef($3, $5, $8); print(convert_func($3)); printf("\n"); }
	  //{ test_print(); }
  
  | calclist error  { yyerrok; printf("> "); }
 ;
%%
