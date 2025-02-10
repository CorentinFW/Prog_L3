%{
    #include <stdio.h>
int nbligne = 0;
int nbcar = 0;
int nbmots = 0;
%}

%option noyywrap
%%
\n {nbligne++; nbcar++;}
[^ \t\n] {nbmots++; nbcar += yyleng;}
. {nbcar++;}
%%
int main(int argc, char *argv[]){
    if(argc == 2){
        yyin = fopen(argv[1],"r");
        if(yyin == NULL){
            perror("fichier vide");
        }
    }else{
        perror("pas le mm nombre d'argument");
        exit(1);
    }
    //freopen(argv[2],"w",stdout);

    yylex();
    printf(" lignes : %d \n mots : %d \n chara : %d \n", nbligne,nbmots,nbcar);
    fclose(yyin);
    return 0;
        
}