%{
    int cpt_lignes = 0;
    int cpt_caracteres = 0;
    int cpt_mots = 0;
%}
%option noyywrap
%%

\n {cpt_lignes += 1; cpt_caracteres += 1;}
[^ \t\n]+ {cpt_mots += 1; cpt_caracteres += yyleng;}
[ \t]+ {cpt_caracteres += yyleng;}
. {cpt_caracteres += 1;}
%%
int main(int argc, char *argv[]){
    
    if (argc == 2){
        yyin = fopen(argv[1], "r");
        if(yyin== NULL){
            perror("Le fichier est vide");
            exit(1);
        }
    
    }
    else{
        perror("Usage : ./delblancs nomFichierALire");
        exit(1);
        
    }

    yylex();
    printf("Nombre de caractères : %d\n" , cpt_caracteres);
    printf("Nombre de mots : %d\n", cpt_mots);
    printf("Nombre de lignes : %d\n", cpt_lignes);

    fclose(yyin);
    return 0;
}

