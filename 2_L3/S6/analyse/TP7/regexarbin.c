/** @file analdesc.c        
 *@author Michel Meynard
 *@brief Analyse descendante récursive d'expression arithmétique
 *
 * Ce fichier contient un reconnaisseur d'expressions arithmétiques composée de 
 * littéraux entiers sur un car, des opérateurs +, * et du parenthésage ().
 * Remarque : soit rediriger en entrée un fichier, soit terminer par deux 
 * caractères EOF (Ctrl-D), un pour lancer la lecture, l'autre comme "vrai" EOF.
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "arbin.h"
#include "lex.yy.c"
                             /* les macros sont des blocs : pas de ';' apres */

extern int jeton;
extern int numcar;

Arbin S();
Arbin X(Arbin l);
Arbin E();
Arbin R(Arbin l);
Arbin T();
Arbin Y(Arbin l);
Arbin F();



//? S -> E X
Arbin S(){
  Arbin v = E();
  return X(v);
}
//? X -> '|' E X
//? X -> epsilon
Arbin X(Arbin l){
  if (jeton==OR) {             /* regle : X->|EX */
    avance();
    Arbin r = E();
    l = X(ab_construire('|',l,r));
  }
  return l ;                        /* regle : X->epsilon */
}

//? E -> T R
Arbin E(){
  Arbin v = T();
  return R(v);                          /* regle : E-> TR */
}

//? R -> T R | epsilon
Arbin R(Arbin l){
  if (jeton==OPEN_PAR || jeton ==LITERAL) {             /* regle : R->TR */
    Arbin r = T();
    l = R(ab_construire('.',l,r));
  }
  return l ;                        /* regle : R->epsilon */
}

//? T -> F Y
Arbin T(){
  Arbin v = F();
  return Y(v);
}
//? Y -> * Y | epsilon
Arbin Y(Arbin l){
  if (jeton==STAR) {
    avance();
    l = ab_construire('*',ab_creer(),l);
    l = Y(l);
  }
  return l ;                        /* regle : R->epsilon */
}
//? F -> (S) | a | ... | z | 0 | @
Arbin F(void){
  if (jeton==OPEN_PAR) {             /* regle : F->(S) */
    avance();
    Arbin v = S();
    testAvance(CLOSE_PAR);
    return v;
  } else if (jeton==LITERAL){         /* regle : F->a..z | 0 | @ */
    Arbin v = ab_construire(yylval.value,ab_creer(),ab_creer());
    avance();
    return v;
  }else erreurSyntaxe();
  return 0;
}
int main(void){                 /* Fonction principale */
  avance();			/* initialiser jeton sur le premier car */
  int no_ligne = 1;
  Arbin result;
  while(jeton != EOF){
    result = S();                          /* axiome */
    if(jeton == NEW_CALC){
      printf("\nArbre n°%d:\n",no_ligne);
      ab_afficher(result);
      avance();
      no_ligne++;
    }else{
      break;
    }
  }
  if (jeton==0){               /* expression reconnue et rien après */
    printf("\nArbre n°%d:\n",no_ligne);
    ab_afficher(result);
    avance();
    printf("\nFin de parcours !\n");
  }else erreurSyntaxe();           /* expression reconnue mais il reste des car */
  return 0;
}
