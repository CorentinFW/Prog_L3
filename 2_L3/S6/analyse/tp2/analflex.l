%{
    #include <stdio.h>
%}
number ([0-9])
lettre ([a-zA-Z])
%option noyywrap
%%
if|then|else|throw {return 300;}
0|[1-9][0-9]* {return 301;}
0[0-7]* {return 302;}
0x([0-9A-F])+ {return 303;}
([a-zA-Z])([a-zA-Z0-9_])* {return 304;}
(\.[0-9]|[0-9]+\.)[0-9]*([eE][+-]?[0-9]+)? { return 305;}
[ \n\t]+ {return 306;}
"//".*[\n] {return 307;}
"/*"([^*]|"*"+[^*\\])*"*"+"/" {return 308;}
%%
int main(){

    int j;
    while ((j=yylex())!= 0)
        printf("Jeton : %d de lexeme : %s\n",j,yytext);
        
}

