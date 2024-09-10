#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "arbin.h"
//compilation :
//gcc -o expdesc expdesc.c arbin.c
#define AVANCER {jeton=getchar();numcar++;}
#define TEST_AVANCE(prevu) {if (jeton==(prevu)) AVANCER else ERREUR_SYNTAXE}
#define ERREUR_SYNTAXE {printf("\nMot non reconnu; erreur de syntaxe \
au caractère numéro %d \n",numcar); exit(1);}
Arbin S();Arbin X(Arbin);Arbin E();Arbin R(Arbin);Arbin T();Arbin Y(Arbin);Arbin F();

int jeton; /* caractère courant du flot d'entrée */
int numcar=0; /* numero du caractère courant (jeton) */

Arbin S(){ // S->EX
    return X(E());
}

Arbin X(Arbin g){ // X->'|'EX|epsilon
    Arbin d;
    if(jeton == '|'){
        AVANCER
        d =E();
        return X(ab_construire('|',g,d));
    }
    else {
        return g;
    }

}

Arbin E(){ // E-> TR
    return R(T());
}

Arbin R(Arbin g){ // R->TR|epsilon
    // pour décider si on est dans le cas TR ou le cas epsilon, on regarde premiers(T)=premiers(F)={(,minuscule,@,0}
    if(jeton == '(' || jeton == '@' || jeton == '0' || islower(jeton)){
        Arbin d=T();
        return R(ab_construire('.', g,d));
    }
    else {
    return g;
    }
}

Arbin T(){ //T-> FY
    return Y(F());
}

Arbin Y(Arbin g){ // Y->*Y|epsilon
    if(jeton == '*'){
        AVANCER
        return Y(ab_construire('*', g, ab_creer()));
    }
    else{
        return g;
    }
}

Arbin F(){ // F->(S)|@|0|a-z
    Arbin r;
    if(jeton=='('){
        AVANCER
        r=S();
        TEST_AVANCE(')');
    }
    else {
    if(islower(jeton) || jeton=='0' || jeton=='@'){
        r= ab_construire(jeton, ab_creer(), ab_creer());
        AVANCER
    }
    else{
        ERREUR_SYNTAXE
    }
    }
}

int main(){
    Arbin r;
    printf("entrer une exp reg : \n");
    AVANCER;
    r=S();//axiome
    if (jeton=='\n'){
        printf("mot reconnu dont l'arbre absrait est : \n");
        ab_afficher(r);
    } else{
        ERREUR_SYNTAXE;
    }
    return 0;
}