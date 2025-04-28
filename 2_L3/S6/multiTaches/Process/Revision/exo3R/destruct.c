#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>

int main(int argc, char * argv[]){

  if (argc!=5) {
    printf("Nbre d'args invalide, utilisation :\n");
    printf("%s fichier-pour-cle-ipc entier-pour-cle-ipc nombre_de_traitement nombre_de_zone\n", argv[0]);
    exit(0);
  }
	  
  int cle=ftok(argv[1], atoi(argv[2]));

  int nbSem = atoi(argv[3])-1;
  int idSem = semget(cle, nbSem, 0600);
  // j'utilise semget de sorte a s'assurer que le tableau a d�truire existe.
  if (idSem==-1){
    perror("erreur  semget");
    exit(-1);
  }

int idMem = shmget(cle, atoi(argv[4])*sizeof(int), 0600);
 if (idMem == -1){
    perror("erreur shmget : ");
    exit(-1);
  }


  printf("sem id : %d \n", idSem);

  // destruction :
  if (semctl(idSem, 0, IPC_RMID, NULL)==-1){
    perror(" erreur semctl : ");
  }
    int destructionMem = shmctl(idMem,IPC_RMID, NULL) ;
    printf("destruction compléter");
  return 0;
}

