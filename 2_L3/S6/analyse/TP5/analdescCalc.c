/** @file analdesc.c        
 *@author Michel Meynard
 *@brief Analyse descendante récursive d'expression arithmétique
 *
 * Ce fichier contient un reconnaisseur d'expressions arithmétiques composée de 
 * littéraux entiers sur un car, des opérateurs +, * et du parenthésage ().
 * Remarque : soit rediriger en entrée un fichier, soit terminer par deux 
 * caractères EOF (Ctrl-D), un pour lancer la lecture, l'autre comme "vrai" EOF.
 pour que le programme fonctionne une fois avoir noter le mot il faut ctrl+D 2 fois, le 1er vide le buffer, le 2em l'envoie 
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
                             /* les macros sont des blocs : pas de ';' apres */
#define AVANCER {jeton=getchar();numcar++;}
#define TEST_AVANCE(prevu) {if (jeton==(prevu)) AVANCER else ERREUR_SYNTAXE}
#define ERREUR_SYNTAXE {printf("\nMot non reconnu : erreur de syntaxe \
au caractère numéro %d \n",numcar); exit(1);} 

int E(void);int R(int a);int T(void);int S(int a);int F(void); /* déclars */

int jeton;                       /* caractère courant du flot d'entrée */
int numcar=0;                    /* numero du caractère courant (jeton) */

int E(void){                        /* regle : E->TR */
  return R(T());
}
int R(int a){ /*calcul ici*/
  if (jeton=='+') {             /* regle : R->+TR */
    AVANCER
    int b = T();
    return R(a + b);
  }
  else {return a;};                        /* regle : R->epsilon */
}
int T(void){
  return S(F());                         /* regle : T->FS */
}
int S(int a){/*calcul ici */
  if (jeton=='*') {             /* regle : S->*FS */
    AVANCER
    int b = F();
    return S(a * b);
  }
  else {return a;};                        /* regle : S->epsilon */
}
int F(void){
  int D;
  if (jeton=='(') {             /* regle : F->(E) */
    AVANCER
    D = E();
    TEST_AVANCE(')')
  }
  else 
    if (isdigit(jeton)){      /* regle : F->0|1|...|9 */
      D = jeton - '0';/*c'est equivalent a faire atoi(jeton) mais obliger de faire tel quelle car pas de atoi*/
      AVANCER
}
    else ERREUR_SYNTAXE
    return D;
}
int main(void){                 /* Fonction principale */
  AVANCER			/* initialiser jeton sur le premier car */
  int a = E();                          /* axiome */
  if (jeton==EOF)               /* expression reconnue et rien après */
    printf("\nMot reconnu\n"); 
  else ERREUR_SYNTAXE           /* expression reconnue mais il reste des car */
  printf("valeur calculer est : %d\n",a);
  return 0;
}
