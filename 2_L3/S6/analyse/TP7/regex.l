%{
#include <stdio.h>
union {
    char value;
} yylval;
int metsChar(){
    yylval.value = yytext[0];
}
#define LITERAL 300
#define OR 301
#define STAR 302
#define OPEN_PAR ((int)'(')
#define CLOSE_PAR ((int)')')
#define NEW_CALC ((int)'\n')
#define IGNORE_WHITE -2
#define COMMENT -1
#define ERROR -3
int jeton;
int numcar;
%}

%option noyywrap
%%

\|                          {return OR;}
\*                          {return STAR;}
[ \t]+                      {return IGNORE_WHITE;}
\n                          {return NEW_CALC;}
\/\*([^\/]|\*+[^\/])*\/     {return COMMENT;}
[a-z]|@|0                   {metsChar();return LITERAL;}
\(                          {return OPEN_PAR;}
\)                          {return CLOSE_PAR;}
.                           {return yytext[0];}
%%

int avance(){
    jeton=yylex();numcar+=yyleng;
    if(jeton < 0){
        avance();
    }
}

int erreurSyntaxe(){
    printf("\nMot non reconnu : erreur de syntaxe au caractère numéro %d \n",numcar);
    exit(1);
}

int testAvance(int prevu){
    if (jeton==prevu){
        avance();
    }else{
        erreurSyntaxe();
    }
}