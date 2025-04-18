#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>
/*
 cr�ation et initialisation d'un tableau de s�maphores pour le
 traitement synchronis�. Le nombre d'�l�ments correspond au nombre de
 traitements -1 et les valeurs initiales sont � 0 (� la case i, la
 valeur corerspond � la derni�re zone trait�e par le processus
 P_(i+1))

 cr�ation d'un segment de memoire partag� qui sera un tableau d'entier (un �l�lement correspondra � une zone)
 */

int main(int argc, char * argv[]){
  
  if (argc!=5) {
    printf("Nbre d'args invalide, utilisation :\n");
    printf("%s nombre-traitements nombre-zones fichier-pour-cle-ipc entier-pour-cl�-ipc\n", argv[0]);
    exit(0);
  }
	  
  int cle = ftok(argv[3], atoi(argv[4]));

  int nbSem = atoi(argv[1]) -1;

  int idSem=semget(cle, nbSem, 0600);
  
  if(idSem == -1){
    perror("erreur semget : ");
    exit(-1);
  }

  printf("sem id : %d \n", idSem);


  
  // initialisation des s�maphores � 0
 
  ushort tabinit[nbSem];
  for (int i = 0; i < nbSem; i++) tabinit[i] = 0;
 

  union semun{
    int val;
    struct semid_ds * buf;
    ushort * array;
  } valinit;
  
  valinit.array = tabinit;

  if (semctl(idSem, nbSem, SETALL, valinit) == -1){
    perror("erreur initialisation sem : ");
    exit(1);
  }

  /* test affichage des valeurs des s�maphores du tableau */
  valinit.array = (ushort*)malloc(nbSem * sizeof(ushort));

  if (semctl(idSem, nbSem, GETALL, valinit) == -1){
    perror("erreur initialisation sem : ");
    exit(1);
  } 
   
  printf("Valeurs des sempahores apres initialisation [ "); 
  for(int i=0; i < nbSem-1; i++){
    printf("%d, ", valinit.array[i]);
  }
  printf("%d ] \n", valinit.array[nbSem-1]);

  free(valinit.array);



  // cr�ation et initialisation du segment de m�moire partag� :

  // on r�utilise la m�me cl� puisque la num�rotation des IPC d�pend du type d'objet.
  int laMem = shmget(cle, atoi(argv[2])*sizeof(int), 0600);
 if (laMem == -1){
    perror("erreur shmget : ");
    exit(-1);
  }

  printf("creation segment de m�moire ok. mem id : %d \n", laMem);
 
	  
  //attachement au segment pour pouvoir y acc�der
  int * p_att = (int *)shmat(laMem, NULL, 0);
  if (p_att== (int *)-1){
    perror("erreur shmat : ");
    exit(-1);
  }

  // j'ai un pointeur sur le segment, j'initialise le tableau 
	 
  for(int i=0; i < atoi(argv[2]); i++){
    p_att[i] = 0;
  }

  // d�tachement pour signaler au syst�me la fin de l'utilisation du segment

  if (shmdt(p_att) == -1){
    perror("erreur shmdt : ");
    exit(-1);
  }
  
  return 0;
}
