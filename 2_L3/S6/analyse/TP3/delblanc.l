%{
    #include <stdio.h>
%}

%option noyywrap
%%
^[ \t]*\n {} 
^[ \t]+ {}
[ \t]+$ {}
[ \t]+ {putchar(' ');}
. {putchar(yytext[0]);}
\n[ \t]<EOF> {}
%%
int main(int argc, char *argv[]){

    if(argc == 3){
        yyin = fopen(argv[1],"r");
        if(yyin == NULL){
            perror("fichier vide");
        }
    }else{
        perror("pas le mm nombre d'argument");
        exit(1);
    }
    freopen(argv[2],"w",stdout);

    yylex();
    fclose(yyin);
    return 0;
        
}