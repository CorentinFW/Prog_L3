%{
#include <stdio.h>
extern double valeur;
extern int numcar;
%}
%option noyywrap
%%
[ \t]+ {numcar+=yyleng;}
[0-9]+ {numcar+=yyleng;valeur = atof(yytext);return 300;}
[0-9]+\. {numcar+=yyleng;valeur = atof(yytext);return 300;}
\.[0-9]+ {numcar+=yyleng;valeur = atof(yytext);return 300;}
[0-9]+\.[0-9]+ {numcar+=yyleng;valeur = atof(yytext);return 300;}
.|\n {numcar+=1;return (int)yytext[0];}
%%
