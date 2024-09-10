%{
extern double valeur;
extern int numcar;  
%}
%option noyywrap
%%
[0-9]+\.[0.9]*|\.[0-9]+|[0-9]+ {valeur = atof(yytext);numcar += yyleng;return 300;}
[ \t] {numcar++;}
.|\n {numcar++;return (int)yytext[0];}
%%
