#include <stdio.h>
#include <sys/types.h>
#include <pthread.h>
#include <unistd.h>
#include "calcul.h"

struct predicatRdv {

// regrouoes les donn�e partag�es entres les threads participants aux RdV :

  pthread_mutex_t verrou;
  pthread_cond_t cond;
  int *compteur;
  int nbThreads;
};

struct params {

  int idThread;
  struct predicatRdv * varPartagee;


};

// fonction associ�e a chaque thread participant au RdV.

void * participant (void * p){ 

  struct params * args = (struct params *) p;
  struct predicatRdv * predicat = args -> varPartagee;
  // simulation d'un long calcul pour le travail avant RdV

  calcul(args -> idThread + rand() % 10); // c'est un exemple.

  // RdV 
  pthread_mutex_lock(args->verrou);
  while (...) {  // attention : le dernier arriv� ne doit pas attendre. Il doit r�veiller tous les autres.
   attente
  }


  ...
  calcul ( ...); // reprise et poursuite de l'execution.


  ...
  pthread_exit(NULL); // fortement recommand�.
}




int main(int argc, char * argv[]){
  
  if (argc!=2) {
    printf(" argument requis ");
    printf("./prog nombre_Threads");
    exit(1);
  }

 
  // initialisations 
  pthread_t threads[atoi(argv[1])];
  struct params tabParams[atoi(argv[1])];

 ...

  srand(atoi(argv[1]));  // initialisation de rand pour la simulation de longs calculs
 
  // cr�ation des threards 
  for (int i = 0; i < atoi(argv[1]); i++){
    tabParams[i].idThread = ...;
    tabParams[i].varPartagee = ...; 

    if (pthread_create(&threads[i], NULL, ...) != 0){
      perror("erreur creation thread");
      exit(1);
    }
  }

  // attente de la fin des  threards. Partie obligatoire 
  for (int i = 0; i < atoi(argv[1]); i++){
  ...
    }
  printf("thread principal : fin de tous les threads secondaires");

  // terminer "proprement". 
  ...
 
}
 
