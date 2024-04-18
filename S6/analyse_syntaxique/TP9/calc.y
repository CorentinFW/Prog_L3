%{
#include "y.tab.h"
#include <stdio.h>
#include <stdlib.h>
void yyerror(char*);
int yylex();
%}
%union{
    int typeInt;
}

%token<typeInt> BOOL IMP EQ AND OR XOR NOT  /*terminaux aka les jetons*/
%type<typeInt> exp /*non terminaux*/


%left OR IMP EQ XOR 
%left AND 
%left NOT 
%left '(' ')' 
%%
ligne : error '\n' {yyerrok; exit(0);} /* error est un token fourni par bison et émit lors d'une erreur d'analyse  ; yyerrok signale que l'erreur a été traitée */
      | exp '\n' {printf("exp = %d \n",$1); exit(0);}
      ;
exp : exp AND exp {$$= $1 && $3;}
    | exp OR exp {$$ = $1 || $3;}
    | exp IMP exp {$$ = !($1) || $3; }
    | exp EQ exp {$$ = (!($1) || $3) && (!($3) || $1);}
    | exp XOR exp {$$ = ($1 || $3) && !($1 && $3);}
    | NOT exp {$$ = !($2);}
    | BOOL {$$ = yylval;}
    | '(' exp ')' {$$ = ($2);}
    ;
    
%%

void yyerror(char *s) {
    fprintf(stderr,"ERREUR : %s\n",s);
}
int main(){
    return yyparse();
}