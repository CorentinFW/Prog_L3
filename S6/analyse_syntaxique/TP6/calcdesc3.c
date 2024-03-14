#include <complex.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// pour compiler voici la commande : 
//gcc -o caldesc calcdescv1.c lex.yy.c -lm -lfl
double valeur;
int jeton; 
int numcar;
int yylex();
                           /* les macros sont des blocs : pas de ';' apres */
#define AVANCER {jeton=yylex();}
#define TEST_AVANCE(prevu) {if (jeton==(prevu)) AVANCER else ERREUR_SYNTAXE}
#define ERREUR_SYNTAXE {printf("\nMot non reconnu : erreur de syntaxe \
au caractère numéro %d, de jeton %d \n",numcar,jeton); exit(1);} 
#define INVITE "Veuillez saisir une expression numérique SVP (q pour quitter) : "

/* déclarations en avant des fonctions */
void X();double E();double R(double g);double T();double S(double g);double F();double G(); double C();

int jeton;                       /* caractère courant du flot d'entrée */
int numcar=0;                    /* numero du caractère courant (jeton) */

void X(){			/* AXIOME */
  double r;
  if (jeton==-1){     /* règle : X -> EOF */  
    exit(0);
  } else if (jeton=='q'){		/* regle : X -> 'q' '\n' */
    AVANCER;
    if (jeton=='\n')
      return;			/* OK */
    else
      ERREUR_SYNTAXE;		/* q suivi d'autre chose */
  }
  else {
    r=E();			/* regle : X -> E '\n' X */
    if (jeton=='\n'){
      printf("Mot reconnu de valeur : %f\n",r);
      printf(INVITE);
      numcar=0;			/* réinit */
      AVANCER;			/* avance au prochain jeton */
      X();			/* boucle tq pas 'q' */
    }
    else ERREUR_SYNTAXE;          /* expression reconnue mais reste des car */
  }
}
double E(){                       	/* regle : E->TR */
  return R(T());		
}
double R(double g){
if (jeton=='+') {             /* regle : R->+TR */
    AVANCER;
    return R(g+T());		/* associativité à gauche */
				/* return g+R(T()); asso à droite */
  }
if (jeton=='-') {
    AVANCER;
    return R(g-T());
    }
else                          /* regle : R->epsilon */
    return g;                   /* ret la partie gauche */
}
double T(){                      	/* regle : T->FS */
  return S(F());
}
double S(double g){
  if (jeton=='*') {             /* regle : S->*FS */
    AVANCER;
    return S(g*F());		/* associativité à gauche */
				/* return g*S(F()); asso à droite */
  }
  if (jeton=='/') {             /* regle : S->*FS */
    AVANCER;
    return S(g/F());		/* associativité à gauche */
				/* return g*S(F()); asso à droite */
  }
  else                          /* regle : S->epsilon */
    return g;                   /* ret la partie gauche */
}

double F(){
    double resG = G();
    return C(resG);
}
double C(double gg){

    if(jeton == '^'){
        AVANCER
        return C(pow(gg,G()));
    }
    else {
    return gg;
    }

}

double G(){
    double e=0;
    if (jeton=='(') {
    AVANCER;
    e=E();
    TEST_AVANCE(')');
    }
    else if (jeton==300){
    e=valeur;
    AVANCER;
    }
    else
    ERREUR_SYNTAXE;
    return e;
}

int main(){                         /* Fonction principale */
  printf(INVITE);
  numcar=0;			/* init */
  AVANCER;                      /* initialiser jeton sur le premier car */
  X();				/* axiome */
  return 0;			/* ne retourne jamais que par X */
}
