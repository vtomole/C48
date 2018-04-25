%option noyywrap nodefault yylineno
%{
# include "expression.h" 
# include "parser.tab.h"

%}

/* float exponent */
EXP	([Ee][-+]?[0-9]+)

%%
 /* single character ops */

"\"" |
"="  |
"|"  |
","  |
";"  |
"("  |
")"  |
"{"  |
"}"  |
"]"  |
"["   { return yytext[0]; }

"++"  { yylval.s = "+"; return INC; }
"--"  { yylval.s = "-"; return INC; }

  /* arith ops */
"+"   { yylval.s = "+"; return ARITH_1; }
"-"   { yylval.s = "-"; return ARITH_1; }

"/"   { yylval.s = "/"; return ARITH_2; }
"*"   { yylval.s = "*"; return ARITH_2; }
"%"   { yylval.s = "%"; return ARITH_2; }

 /* comparison ops */
">"   { yylval.s = ">";   return CMP_1; }
"<"   { yylval.s = "<";   return CMP_1; }
"!="  { yylval.s = "!=";  return CMP_1; }
"=="  { yylval.s = "=";  return CMP_1; } 
">="  { yylval.s = ">=";  return CMP_1; } 
"<="  { yylval.s = "<=";  return CMP_1; }
"||"  { yylval.s = "or";  return CMP_2; }
"&&"  { yylval.s = "and"; return CMP_2; }


 /* keywords */

"if"    { return IF; }
"then"  { return THEN; }
"else"  { return ELSE; }
"while" { return WHILE; }
"do"    { return DO; }
"fun"   { return FUN;}
"for"   { return FOR; }

 /* built in functions */
"sqrt"  { yylval.s = "sqrt";  return FUNCT; }
"exp"   { yylval.s = "exp";   return FUNCT; }
"log"   { yylval.s = "log";   return FUNCT; }
"print" { yylval.s = "print"; return FUNCT; }
"return" { return RETURN; }
"#scm" { return ISCM; }
"#c48" { return IC48; }


 /* names */
\"[a-zA-Z0-9 '?;:,.<>{}!@#$%^&*()]*\"  { yylval.s = strdup(yytext); return STR; }
[a-zA-Z][a-zA-Z0-9]*  { yylval.s = strdup(yytext); return NAME; }
[a-zA-Z/.][a-zA-Z0-9/_]*  { yylval.s = strdup(yytext); return FILENAME; }
[0-9]+                { yylval.d = atof(yytext); return NUMBER; }
[0-9]+"."[0-9]*{EXP}? |
"."?[0-9]+{EXP}? { yylval.d = atof(yytext); return DOUBLE; }

"//".*"\n"  
"/*"(\n|([^*][^/]))*"*/" 
[ \t\n]   /* ignore white space */

	/** [\n]    /* ignore white space */
\\\n     /* ignore line continuation */
'\n'    { return EOL; }
. 
%%
/** "\Z"    { return EofF; } **/
