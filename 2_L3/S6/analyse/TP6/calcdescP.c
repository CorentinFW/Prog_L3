/** @file evaldesc.c
 *@author Michel Meynard
 *@brief Evaluation descendante récursive d'expression arithmétique.
 *Chaque expression arithmétiques est composée de littéraux entiers sur un car, 
 * des opérateurs +, * et du parenthésage (). On utilise l'associativité à 
 * gauche : 1+2+3=(1+2)+3; 1*2*3=(1*2)*3. Soit rediriger en entrée un fichier, 
 * soit terminer par deux caractères EOF (Ctrl-D), un pour lancer la lecture,
 * l'autre comme "vrai" EOF.
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
/* la compile  gcc -o calcdescP calcdescP.c lex.yy.c -lm*/

                             /* les macros sont des blocs : pas de ';' apres */
#define AVANCER {jeton=yylex();numcar++;}
#define TEST_AVANCE(prevu) {if (jeton==(prevu)) AVANCER else ERREUR_SYNTAXE}
#define ERREUR_SYNTAXE {printf("\nMot non reconnu : erreur de syntaxe \
au caractère numéro %d, de jeton %d \n",numcar,jeton); exit(1);} 
#define INVITE "Veuillez saisir une expression numérique SVP (q pour quitter) : "

/* déclarations en avant des fonctions */
void X();double E();double R(double g);double T();double S(double g);double F();double C(double g);double G();

double valeur;
int jeton;                       /* caractère courant du flot d'entrée */
int numcar=0;                    /* numero du caractère courant (jeton) */
int yylex();

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
  else if(jeton=='-'){
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
  else if(jeton=='/'){
    AVANCER;
    return S(g/F());
  }
  else                          /* regle : S->epsilon */
    return g;                   /* ret la partie gauche */
}
double F(){
    return C(G());
}

double C(double g){
if(jeton=='^'){
    AVANCER;
    return pow(g,C(G()));
}
else {
    return g;
}
}

double G(){
  double r;                        /* resultat */
  if (jeton=='(') {             /* regle : F->(E) */
    AVANCER;
    r=E();
    TEST_AVANCE(')');
  }
  else 
    if (jeton==300) {       /* regle : F->0|1|...|9 */
      r=valeur;              /* valeur comprise entre 0 et 9 */
      AVANCER;
    }
    else ERREUR_SYNTAXE;
  return r;
}
int main(){                         /* Fonction principale */
  printf(INVITE);
  numcar=0;			/* init */
  AVANCER;                      /* initialiser jeton sur le premier car */
  X();				/* axiome */
  return 0;			/* ne retourne jamais que par X */
}
