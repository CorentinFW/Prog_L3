%{				// interlog.y  
#include  <stdio.h>
#define YYSTYPE int             /* inutile */
int yylex(void);  void yyerror(char *s);
%}
%%
%left '|'
%left CONCAT
%left '*'
%%
expr : '(' expr ')' {$$ = $2;}
| expr expr %prec CONCAT { $$= ab_construire('.',$1,$2);}
| expr '|' expr {$$= ab_construire('|',$1,$3);}
| expr '*' {$$= ab_construire('*',$1,ab_creer());}
| SYMBOLE {$$=ab_construire(yylval.i, ab_creer(), ab_creer());}
;
%%
int yylex(void) {
  int c;
  while(((c=getchar())==' ') || (c=='\t'))
    ;
  return c;
}
void yyerror(char *s) {
  fprintf(stderr,"%s\n",s);
}
int main(void){
  printf("Veuillez entrer une expression booléenne S.V.P. : ");
  return yyparse();
}
