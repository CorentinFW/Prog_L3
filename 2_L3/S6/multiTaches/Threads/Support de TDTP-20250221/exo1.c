#include <string.h>
#include <stdio.h>//perror
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#import "calcul.h"

 
struct paramsFonctionThread {

  int idThread;
  int *taskdoneShared;
  pthread_mutex_t *verrou;
  // si d'autres param�tres, les ajouter ici.

};


void * fonctionThread (void * params){

  struct paramsFonctionThread * args = (struct paramsFonctionThread *) params;

  printf("Thread %d \n",args->idThread);
  for(int i =0;i<10000;i++){
    printf("Thread %d : %d \n",args->idThread,i);
    pthread_mutex_lock(args->verrou);
    calcul(10);
    *args->taskdoneShared = (*args->taskdoneShared) +1;

    pthread_mutex_unlock(args->verrou);
  }
  free(args);
  pthread_exit(NULL);
}


int main(int argc, char * argv[]){

  if (argc < 2 ){
    printf("utilisation: %s  nombre_threads  \n", argv[0]);
    return 1;
  }     
  int taskDone = 0;
  
  pthread_t threads[atoi(argv[1])];
  // creation des threards 
  for (int i = 0; i < atoi(argv[1]); i++){

    // Le passage de param�tre est fortement conseill� (�viter les
    // variables globles).
    pthread_mutex_t verrou = PTHREAD_MUTEX_INITIALIZER;
    struct paramsFonctionThread *params = malloc(sizeof(struct paramsFonctionThread));
    params->idThread = i;
    params->taskdoneShared = &taskDone;
    params->verrou = &verrou;
    if (pthread_create(&threads[i], NULL,fonctionThread, params) != 0){
      perror("erreur creation thread");
      exit(1);
    }
  }
for(int i;i< atoi(argv[1]);i++){
  pthread_join(threads[i], NULL);
}

// garder cette saisie et modifier le code en temps venu. 
  
  
  printf("Nombre de tache %d \n",taskDone);

  return 0;
 
}
 
