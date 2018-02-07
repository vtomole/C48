/*calculator with AST */

%{
  #include <stdio.h>
  #include <stdlib.h>
  #include "fb3-2.h"
  %}

%union {
  struct ast *a;
  double d;
  struct symbol *s;
  struct symlist *sl;
  int fn;
}

/*Declare tokens */
%token <d> NUMBER
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
