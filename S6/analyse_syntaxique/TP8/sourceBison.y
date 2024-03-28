%{
#include <stdio.h>
#include <stdlib.h>
#include "arbin.h"
void yyerror(char*);
int yylex();
%}
%union { /* YYSTYPE */
int typeInt;
Arbin tree;

}
%token<typeInt> SYMBOLE /*terminaux aka les jetons*/
%type<tree> s t e f /*non terminaux*/
// TODO : déclaration des tokens et des non terminaux
// ligne permet de lancer l'exp apres un entré ( en gros c'est le input)
%%
ligne : error '\n' {yyerrok; exit(0);} /* error est un token fourni par bison et émit lors d'une erreur d'analyse  ; yyerrok signale que l'erreur a été traitée */
      | s '\n' {ab_afficher($1); exit(0);}
      ;
s   : s '|' e {$$=ab_construire('|', $1, $3);}
    | e {$$=$1;}
    ;
e   : e t {$$ = ab_construire('.',$1,$2);}
    | t {$$ = $1;}
    ;
t   : t '*' {$$ = ab_construire('*',$1, NULL);}
    | f {$$ = $1;}
    ;
f   : '(' s ')' {$$=$2;}
    | SYMBOLE {$$=ab_construire(yylval.typeInt, NULL, NULL);}
    ;
%%
int yylex(){
    int i=getchar();
    if ((i>='a' && i<='z')||i=='@'||i=='0'){
        yylval.typeInt=i;
        return SYMBOLE;
    }
    else return i;
}
void yyerror(char *s) {
    fprintf(stderr,"ERREUR : %s\n",s);
}
int main(){
    return yyparse();
}