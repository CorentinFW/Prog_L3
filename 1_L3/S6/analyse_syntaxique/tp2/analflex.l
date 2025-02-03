%{ 
    union{long int i;char* s;double d;} yylval;
%}
%option noyywrap
%%
if|then|else|throw {return 300;}
0|[1-9][0-9]* {yylval.i = atoi(yytext); return 301;}//entier base 10
0[0-7]* {yylval.i = strtol(yytext, NULL, 8); return 302;}//strtol pour octet et hexa
0x([0-9A-F])+ {yylval.i = strtol(yytext, NULL, 16); return 303;}
([a-zA-Z])([a-zA-Z0-9_])* {yylval.s = strdup(yytext); return 304;}
(([0-9])+\.|\.[0-9])[0-9]*[eE][+-]?[1-9][0-9]* {yylval.d = atof(yytext); return 305;}
[\n \t]+ {return 306;}
"//".*[\n] {return 307;}
"/*"([^*]|"*"+[^*\\])*"*"+"/" {return 308;}
%%
/* ZONE DES FONCTIONS C */
int main(){
    int j;
    
    char* invite="Saisissez un(des) mot(s) matchant a(b+c)?|bd suivi de EOF (CTRL-D) SVP : ";
    printf("%s", invite);
    while ((j=yylex())!=0) 
        printf("\nJeton : %i; de lexeme %s\n%s",j,yytext,invite);

    return 0;
}
