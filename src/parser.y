%{
#  include <stdio.h>
#  include <stdlib.h>
#  include "expression.h" 
#  include "convert.c"
%}

%union {
  struct object *obj;
  double d;
  char *s;
}

/* declare tokens */
%token <d> NUMBER DOUBLE 
%token <s> NAME ARITH_1 ARITH_2 CMP_1 CMP_2 FUNCT STR INC
%token EOL 

%token IF THEN ELSE WHILE DO FUN FOR RETURN

%nonassoc CMP_1
%right CMP_2
%right '='
%left ARITH_1
%left ARITH_2
%nonassoc '|' UMINUS

%type <obj> exp stmt list symlist explist comp

%start calclist

%%

stmt: WHILE '(' comp ')'  '{' list '}'    { $$ = make_while_loop($3, $6); }    
   | IF '(' comp ')' '{' list '}'         { $$ = make_if_stmt($3, $6, the_empty_list); }
   | IF '(' comp ')'  '{' list '}' ELSE '{'list '}'  { $$ = make_if_stmt($3, $6, $10); }
   | IF '(' comp ')'  '{' list '}' ELSE stmt         { $$ = make_if_elseif_stmt($3, $6, $9); }
   | FOR '(' exp ';' comp ';' exp ')' '{' list '}'   { $$ = make_for_loop($3, $5, $7, $10); }
   | exp ';'
;

list: /* nothing */ { $$ = the_empty_list; }
   | stmt list      { $$ = cons($1, $2); }
   ;
   
comp: exp CMP_1 exp  { $$ = make_comp($2, $1, $3); }
   | comp CMP_2 comp   { $$ = make_comp($2, $1, $3); }
   ;

exp: comp          
   | exp ARITH_1 exp       { $$ = make_arith($2, $1, $3); }
   | exp ARITH_2 exp       { $$ = make_arith($2, $1, $3); }
   | '(' exp ')'          { $$ = $2; }
   | '-' exp %prec UMINUS { $$ = make_arith("-", make_fixnum(0), $2); }
   | NUMBER               { $$ = make_fixnum($1); }
   | DOUBLE               { $$ = make_float($1); }
   | NAME                 { $$ = make_symbol($1); }
   | NAME '=' exp         { $$ = make_assign($1, $3); }
   | NAME '(' explist ')' { $$ = cons(make_symbol($1), $3); }
   | FUNCT '(' explist ')'{ $$ = cons(make_symbol($1), $3); }
   | '|' exp              { $$ = cons(make_symbol("|"), $2); }
   | RETURN exp           { $$ = $2; }
   | STR                  { $$ = make_symbol($1); }
   | NAME '['']' '=' '[' explist ']'
                          { $$ = make_define_array($1, $6); }
   | NAME '[' exp ']'     { $$ = get_array_index($1, $3); }
   | NAME '[' exp ']' '=' exp
                          { $$ = set_array_index($1, $3, $6); }
   | NAME INC             { $$ = make_increment($1, $2); }
;

explist:            { $$ = the_empty_list; }
 | exp              { $$ = cons($1, the_empty_list); }
 | exp ',' explist  { $$ = cons($1, $3); }
;

symlist:            { $$ = the_empty_list; }
 | NAME             { $$ = make_symbol($1); }
 | NAME ',' symlist { $$ = cons(make_symbol($1), $3); }
;

calclist: /* nothing */
  | calclist EOL
  | calclist stmt
    //{ if(debug) dumpast($2, 0); printf("= %4.4g\n> ", eval_ast($2)); treefree($2); }
    {
      print($2);
      printf("\n");
      eval($2, the_global_environment);
    }
            
  | calclist FUN NAME '(' symlist ')' '{' list '}' 
    //{ dodef($3, $5, $8); printf("Defined %s\n> ", $3->name); }
	  {
	    struct object *function = make_define_func($3, $5, $8);
	    print(function);
	    printf("\n");
	    eval(function, the_global_environment);
	  }
  
  | calclist error EOL { yyerrok; }
 ;
%%
