%{
    #include <stdio.h>
    union{int i; float d; char* s;} yylval;
    #define LITENT 302
    #define LITFLOAT 304
    #define ID 305
    #define LITCH 306
%}
number ([0-9])
lettre ([a-zA-Z])

%option noyywrap
%%
if|then|else|throw {return 300;}
0|[1-9][0-9]* {yylval.i = atoi(yytext);return LITENT;}
0[0-7]+ {yylval.i =strtol(yytext,NULL,8);return LITENT;}
0x([0-9A-F])+ {yylval.i =strtol(yytext,NULL,16);return LITENT;}
([a-zA-Z])([a-zA-Z0-9_])* {yylval.s = malloc(strlen(yytext));strcpy(yylval.s,yytext);return ID;}
(\.[0-9]|[0-9]+\.)[0-9]*([eE][+-]?[0-9]+)? { yylval.d =strtod(yytext,NULL); return LITFLOAT;}
[ \n\t]+ {}
"//".*[\n] {}
"/*"([^*]|"*"+[^*\\])*"*"+"/" {}
\"[^"]*\" {yylval.s = malloc(strlen(yytext)-2);strncpy(yylval.s,yytext+1,strlen(yytext)-2);return LITCH;}
. {return yytext[0];}
%%
int main(){

    int j;
    while ((j=yylex())!= 0)
        printf("Jeton : %d de lexeme : %s\n",j,yytext);
        if(j == LITENT)
            printf("de valeur %ld\n", yylval.i);
        else if (j==LITFLOAT)
            printf("de valeur %f\n", yylval.d);
        else if (j == ID)
            printf("de valeur %s\n",yylval.s);
        else if (j == LITCH)
            printf("de valeur %s\n", yylval.s);
        else printf("\n");
}

