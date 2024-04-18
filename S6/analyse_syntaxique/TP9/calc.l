%{ /* calc.l */
#define YYSTYPE double /* ATTENTION AUX 2 MACROS dans lex et yacc */
#include "y.tab.h" /* JETONS crees par yacc et definition de yylval */
#include <stdlib.h> /* pour double atof(char *) */
#include <stdio.h> /* pour printf */
%}

%option noyywrap
%%
true|vrai|1 {yylval=1;return (BOOL);}
false|faux|0 {yylval=0;return (BOOL);}

-> { return(IMP); }
\| { return(OR); }
\^ { return(XOR); }
& { return(AND); }
! { return(NOT); }
== { return (EQ); }
%%