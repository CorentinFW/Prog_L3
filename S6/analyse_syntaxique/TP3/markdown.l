%{
%}
%option noyywrap
%%
\* {putchar('<'); putchar('u'); putchar('l'); putchar('>');}

%%
int main(int argc, char *argv[]){
    
    if (argc == 2){
        yyin = fopen(argv[1], "r");
        if(yyin== NULL){
            perror("Le fichier est vide");
            exit(1);
        }
        //     char* invite="Saisissez un(des) mot(s) matchant a(b+c)?|bd suivi de EOF (CTRL-D) SVP : ";
        //     printf("%s", invite);
        //     while ((j=yylex())!=0) 
        //         printf("\nJeton : %i; de lexeme %s\n%s",j,yytext,invite);
        // }
    
    }
    else{
        perror("Usage : ./delblancs nomFichierALire");
        exit(1);
        
    }

    yylex();
    fclose(yyin);
    return 0;
}

