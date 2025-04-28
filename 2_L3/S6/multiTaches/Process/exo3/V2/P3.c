#include <iostream>
#include <stdio.h> //perror
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

union semun {
  int val;
  struct semid_ds *buf;
  ushort *array;
};

void afficherSemaphores(int idSem, int nbSem) {
  ushort *valeurs = new ushort[nbSem];
  semun arg;
  arg.array = valeurs;

  if (semctl(idSem, 0, GETALL, arg) == -1) {
    perror("Erreur GETALL : ");
    delete[] valeurs;
    return;
  }

  cout << "État des sémaphores [ ";
  for (int i = 0; i < nbSem; i++) {
    cout << valeurs[i];
    if (i < nbSem - 1)
      cout << ", ";
  }
  cout << " ]" << endl;

  delete[] valeurs;
}

int main(int argc, char *argv[]) {
  if (argc != 5) {
    printf("Usage: %s nombre-semaphore nombre-zones fichier-pour-cle-ipc "
           "entier-pour-cle-ipc\n",
           argv[0]);
    exit(1);
  }

  int nombre_zones = atoi(argv[2]);
  int nbSem = atoi(argv[1]) - 1;

  key_t cle = ftok(argv[3], atoi(argv[4]));

  if (cle == -1) {
    perror("Erreur ftok d: ");
    exit(2);
  }

  key_t cleGlobale = ftok(argv[3], atoi(argv[4])+1);
  if (cleGlobale == -1) {
    perror("Erreur ftok d: ");
    exit(2);
  }

  cout << "ftok ok" << endl;

  int idSem = semget(cle, nbSem, 0600);

  if (idSem == -1) {
    perror("erreur semget : ");
    exit(2);
  }

  cout << "semget ok" << endl;

  int sh_id = shmget(cle, nombre_zones * sizeof(int), 0600);
  if (sh_id == -1) {
    perror("erreur shmget : ");
    exit(2);
  }

  int sh_id_glo = shmget(cle, atoi(argv[1]) * sizeof(int), 0600);
  if (sh_id == -1) {
    perror("erreur shmget : ");
    exit(2);
  }

  cout << "shmget ok" << endl;

  struct sembuf opv;
  opv.sem_num = 1;
  opv.sem_op = +1;
  opv.sem_flg = 0;

/*
  struct sembuf opvReset;
  opvReset.sem_num = 0;
  opvReset.sem_op = +1;
  opvReset.sem_flg = 0;
*/

/*
  struct sembuf opz;
  opz.sem_num = 0;
  opz.sem_op = 0;
  opz.sem_flg = 0;
*/

  struct sembuf opp;
  opp.sem_num = 1;
  opp.sem_op = -1;
  opp.sem_flg = 0;

  pid_t pid = getpid();

  afficherSemaphores(idSem, nbSem);

/* // Pas besoin de faire Z car P est bloquant
  // /!\ les sémaphores doivent être initialisé à -1 !
  // demande l'accès exclusif à la zone de mémoire
  int op1 = semop(idSem, &opz, 1);
  if (op1 == -1) {
    perror("erreur op1 : ");
    exit(2);
  }
  */

  // s'attache à la zone de mémoire
  int *attachement = (int *)shmat(sh_id, NULL, 0);
  if (attachement == (void *)-1) {
    perror("erreur attachement : ");
    exit(2);
  }

  // s'attache à la zone de mémoire Globale
  int *attachementGlobale = (int *)shmat(sh_id_glo, NULL, 0);
  if (attachementGlobale == (void *)-1) {
    perror("erreur attachement : ");
    exit(2);
  }

  int dejaTraite = 0;
  int DroitDeTraite = attachementGlobale[1];


  while (dejaTraite < DroitDeTraite) {

  // n'est pas le premier processus, se bloque l'accès en attendant le
  // précédent.
  int op0 = semop(idSem, &opp, 1);
  if (op0 == -1) {
    perror("erreur op1 : ");
    exit(2);
  }

  afficherSemaphores(idSem, nbSem);

    // Traitement
  cout << pid << " débute le traitement" << endl;

    attachement[dejaTraite] -= 2;
    cout << "Zone[" << dejaTraite << "] mise à jour à " << attachement[dejaTraite] << endl;

  int Alea = rand() % 10;
  sleep(Alea);


  // Mise a jour de l'avancement globale du traitement

  // Traitement
  cout << pid << " débute le traitement Globale" << endl;


    attachementGlobale[2] += 1;
    cout << "Nombres de zone traité par P3 mise à jour à " << attachement[2] << endl;



if(atoi(argv[1]) > 2){
    cout << pid << " donne l'autorisation de continuer" << endl;
  // Donne l'accès à la zone de mémoire suivante
  int op2 = semop(idSem, &opv, 1);
  if (op2 == -1) {
    perror("erreur op2 : ");
    exit(2);
  }
}

dejaTraite++;
}
/* // Ne dois pas rendre l'accès, car ferait passer le sémaphore 
// à 1 et autoriserait une potentielle connexion illégal
cout << pid << " rend l'accès à son sémaphore" << endl;
  // Rend l'accès à la zone de mémoire
  int op3 = semop(idSem, &opvReset, 1);
  if (op3 == -1) {
    perror("erreur op2 : ");
    exit(2);
  }
*/
  afficherSemaphores(idSem, nbSem);

  // se détache de la zone de mémoire
  int detachement = shmdt(attachement);
  if (detachement == -1) {
    perror("erreur detachement : ");
    exit(2);
  }

    // se détache de la zone de mémoire
  int detachementGlobale = shmdt(attachementGlobale);
  if (detachementGlobale == -1) {
    perror("erreur detachement : ");
    exit(2);
  }

  return 0;
}