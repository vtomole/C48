%option noyywrap nodefault yylineno
%{
# include "expression.h"
# include "parser.tab.h"
%}

/* float exponent */
EXP	([Ee][-+]?[0-9]+)

%%
 /* single character ops */
"+" |
"-" |
"*" |
"/" |
"%" |
"=" |
"|" |
"," |
";" |
"(" |
")" |
"{" |
"}" |
"]" |
"["   { return yytext[0]; }

 /* comparison ops */
">"     { yylval.fn = 1; return CMP; }
"<"     { yylval.fn = 2; return CMP; }
"<>"    { yylval.fn = 3; return CMP; }
"=="    { yylval.fn = 4; return CMP; }
">="    { yylval.fn = 5; return CMP; }
"<="    { yylval.fn = 6; return CMP; }

 /* keywords */

"if"    { return IF; }
"then"  { return THEN; }
"else"  { return ELSE; }
"while" { return WHILE; }
"do"    { return DO; }
"fun"   { return FUN;}
"for"   { return FOR; }
	/** "end"   { return EOL; } **/

 /* built in functions */
"sqrt"  { yylval.fn = B_sqrt; return FUNCT; }
"exp"   { yylval.fn = B_exp; return FUNCT; }
"log"   { yylval.fn = B_log; return FUNCT; }
"print" { yylval.fn = B_print; return FUNCT; }
"return" { return RETURN; }
 /* debug hack */
"debug"[0-9]+ { debug = atoi(&yytext[5]); printf("debug set to %d\n", debug); }


 /* names */
[a-zA-Z][a-zA-Z0-9]*  { yylval.s = lookup(yytext); return NAME; }

[0-9]+"."[0-9]*{EXP}? |
"."?[0-9]+{EXP}? { yylval.d = atof(yytext); return NUMBER; }

"//".*"\n"  
"/*"(\n|([^*][^/]))*"*/" 
[ \t\n]   /* ignore white space */

	/** [\n]    /* ignore white space */
\\\n    printf("c> "); /* ignore line continuation */
'\n'    { return EOL; }
'\Z'    { return END; }
.       { yyerror("Mystery character %c\n", *yytext); }

%%
/** "\Z"    { return EofF; } **/
