#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>

int main(int argc, char * argv[]){
  
  if (argc!=4) {
    printf("Nbre d'args invalide, utilisation :\n");
    printf("%s  fichier-pour-cle-ipc entier-pour-clef-ipc\n", argv[0]);
    exit(0);
  }
int cleSem=ftok(argv[1], atoi(argv[2]));
printf("recup de la cle\n");
int idSem = semget(cleSem, atoi(argv[3]), 0);
printf("recup de l'idSem\n");
struct sembuf rdv = {0,-1,0}; // = P 
printf("sembuf fait\n");
int NewSem = semop(idSem,&rdv,1);
printf("j'attend les copain\n");
struct sembuf rdv2 = {0,0,0}; // = Z
semop(idSem, &rdv2, 1);
printf("on est libérer\n");

}