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
/* les macros sont des blocs : pas de ';' apres */
#define AVANCER {jeton=getchar();numcar++;}
#define TEST_AVANCE(prevu) {if (jeton==(prevu)) AVANCER else ERREUR_SYNTAXE}
#define ERREUR_SYNTAXE {printf("\nMot non reconnu : erreur de syntaxe \
au caractère numéro %d \n",numcar); exit(1);}
int E();int R(int test);int T();int S(int test);int F(); /* déclars */
int jeton; /* caractère courant du flot d'entrée */
int numcar=0; /* numero du caractère courant (jeton) */

//regles E
int E(){
    return R(T());
}

//regles R
int R(int test){
    if (jeton=='+') { /* regle : R->+TR */
        AVANCER
        int a = T();
        return R(a+test);
    }
    else return test;; /* regle : R->epsilon */
}

//regles T
int T(){
    return S(F());
}

//regles S
int S(int test){
    if (jeton=='*') { /* regle : S->*FS */
        AVANCER
        int a = F();
        int b = S(test);
        return a*b;
    }
    else return test; ; /* regle : S->epsilon */
}

//regle F
int F(){
    int D;
    if (jeton=='(') { /* regle : F->(E) */
        AVANCER
        D = E();
        TEST_AVANCE(')')
    }
    else if (isdigit(jeton)){ /* regle : F->0|1|...|9 */
        D = jeton -'0';
        AVANCER
    }
    else ERREUR_SYNTAXE
    return D;

}


int main(void){ /* Fonction principale */

AVANCER /* initialiser jeton sur le premier car */
int resultat = E(); /* axiome */
if (jeton==EOF){ /* expression reconnue et rien après */
printf("\nMot reconnu\n");
printf("le resultat est : %d \n",resultat);}
else ERREUR_SYNTAXE /* expression reconnue mais il reste des car */
return 0;
}