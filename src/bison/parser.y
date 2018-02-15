%{
 
/*
 * Parser.y file
 * To generate the parser run: "bison Parser.y"
 */
#include "expression.h"
#include "parser.h"
#include "lexer.h"
  
%}

%code requires {
#ifndef YY_TYPEDEF_YY_SCANNER_T
#define YY_TYPEDEF_YY_SCANNER_T
typedef void* yyscan_t;
#endif
}

%output  "parser.c"
%defines "parser.h"
 
%define api.pure
%lex-param   { yyscan_t scanner }
%parse-param { SExpression **expression }
%parse-param { yyscan_t scanner }

%union {
  int value;
  SExpression *expression;
}
 
%left '+' TOKEN_PLUS
%left '*' TOKEN_MULTIPLY
%left '-' TOKEN_MINUS
%left '/' TOKEN_DIVIDE
%left '=' TOKEN_SET
 
%token TOKEN_LPAREN
%token TOKEN_RPAREN
%token TOKEN_PLUS
%token TOKEN_MULTIPLY
%token <value> TOKEN_NUMBER
%token TOKEN_MINUS
%token TOKEN_DIVIDE
%token TOKEN_SET

%type <expression> expr
 
%%
 
input
  : expr                              { *expression = $1; }
  ;
 
expr
  : expr[L] TOKEN_PLUS expr[R]        { $$ = createOperation(PLUS, $L,$R);}
  | expr[L] TOKEN_MULTIPLY expr[R]    { $$ = createOperation(MULTIPLY, $L,$R);}
  | expr[L] TOKEN_MINUS expr[R]       { $$ = createOperation(MINUS, $L,$R);}
  | expr[L] TOKEN_DIVIDE expr[R]      { $$ = createOperation(DIVIDE, $L,$R);}
  | expr[L] TOKEN_SET expr[R]         { $$ = createOperation(SET, $L,$R);}
  | TOKEN_LPAREN expr[E] TOKEN_RPAREN { $$ = $E;}
  | TOKEN_NUMBER                      { $$ = createNumber($1);}
  ;

%%
