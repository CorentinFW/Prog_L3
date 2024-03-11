#include <string.h>
#include <stdio.h>//perror
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
//#include <iostream>
#include <pthread.h>
#include "calcul.h"

struct paramsFonctionThread {

  int idThread;
  int *VarGloPro;
  pthread_mutex_t *Verrou;

};

void * fonctionThread (void * params){

  struct paramsFonctionThread * args = (struct paramsFonctionThread *) params;

  
  pthread_exit(NULL);
}


int main(int argc, char * argv[]){

  if (argc < 2 ){
    printf("utilisation: %s  nombre_threads  \n", argv[0]);
    return 1;
  }     
  pthread_t threads[atoi(argv[1])];
  int VariablePartage;
  pthread_mutex_t mutex;
  pthread_mutex_init(&mutex,NULL);

  struct paramsFonctionThread args[atoi(argv[1])];
  // cr�ation des threards 
  
  for (int i = 0; i < atoi(argv[1]); i++){
    args[i].idThread = i;
    args[i].VarGloPro = &VariablePartage;
    args[i].Verrou = &mutex;
    if (pthread_create(&threads[i], NULL,fonctionThread, &args[i]) != 0){
      perror("erreur creation thread");
      exit(1);
    }
    int res = pthread_join(threads[i], NULL);
    //exit(1); = seul le 1er thread sera afficher ( et surement créer)
  }

// garder cette saisie et modifier le code en temps venu.
  // char c; 
  // char m[400];
  // printf("saisir un caractére \n");
  // fgets(m, 1, stdin);
  // printf("le m est : %s",m);

  return 0;
 
}
 
