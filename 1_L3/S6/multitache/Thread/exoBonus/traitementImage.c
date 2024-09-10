#include <iostream>
#include <sys/types.h>
#include <pthread.h>
#include <unistd.h>
#include "../calcul.h"

// structure qui regroupe les variables partag�es entre les threads.
struct varPartagees {
  int nbZones;
  int * di; // le tableau indiqu� dans l'�nonc�
  pthread_mutex_t verrou; //verrous du tableau di
  pthread_cond_t cond;
};

// structure qui regroupe les param�tres d'un thread
struct params {

  int idThread; // cet entier correspond au num�ro de traitement associ� � un thread
  
  struct varPartagees * vPartage;


};

// fonction associ�e � chaque thread secondaire � cr�er.

void *traitement(void *p) {
    struct params *args = (struct params *) p;
    struct varPartagees *vPartage = args->vPartage;

    for (int i = 1; i <= vPartage->nbZones; i++) {
        // Attendre que le thread précédent ait terminé de traiter la zone précédente
        if (args->idThread > 0) {
            printf("Thread %d : en attente que le thread %d termine la zone %d.\n", args->idThread, args->idThread - 1, i);
            pthread_mutex_lock(&vPartage->verrou);
            
            while (vPartage->di[args->idThread - 1] <= vPartage->di[args->idThread]) {
                pthread_cond_wait(&vPartage->cond, &vPartage->verrou);
            }
            pthread_mutex_unlock(&vPartage->verrou);
        }

        // Traiter la zone actuelle
        printf("Thread %d : je fais le traitement pour la zone %d.\n", args->idThread, i);
        // Dans cette partie, le traitement de la zone i est à faire en faisant une simulation d'un long calcul (appel à calcul(...))
        calcul(1);

        // Mettre à jour le tableau di pour signaler que le traitement de cette zone est terminé
        pthread_mutex_lock(&vPartage->verrou);
        vPartage->di[args->idThread] = i;
        pthread_cond_broadcast(&vPartage->cond); // Signaler à tous les threads que le traitement de cette zone est terminé
        pthread_mutex_unlock(&vPartage->verrou);

        printf("Thread %d : j'ai fini le traitement pour la zone %d.\n", args->idThread, i);
    }

    pthread_mutex_lock(&vPartage->verrou);
    vPartage->di[args->idThread]++;
    pthread_mutex_unlock(&vPartage->verrou);

    printf("Thread %d : Toutes les zones ont été traitées.\n", args->idThread);
    pthread_exit(NULL);
}







int main(int argc, char * argv[]){
  
  if (argc!=3) {
    std::cout << " argument requis " << std::endl;
    std::cout << "./prog nombre_Traitements nombre_Zones" << std::endl;
    exit(1);
  }

 
   // initialisations 
  pthread_t threads[atoi(argv[1])];
  struct params tabParams[atoi(argv[1])];

  struct varPartagees vPartage;
  int tab[atoi(argv[1])];

  vPartage.di = tab;

  for(int i = 0 ; i < atoi(argv[1]); i++){
    vPartage.di[i]=0;
  }

  vPartage.nbZones =  atoi(argv[2]);
  pthread_mutex_init(&vPartage.verrou, NULL);
  pthread_cond_init(&vPartage.cond, NULL);
  
 

  srand(atoi(argv[1]));  // initialisation de rand pour la simulation de longs calculs
  
  

  // cr�ation des threads 
  for (int i = 0; i < atoi(argv[1]); i++){
    tabParams[i].idThread = i;
    tabParams[i].vPartage = &vPartage;
    if (pthread_create(&threads[i], NULL, traitement, &tabParams[i]) != 0){
      perror("erreur creation thread");
      exit(1);
    }
  }

  

  
  // attente de la fin des  threards. Partie obligatoire 
  for (int i = 0; i < atoi(argv[1]); i++){
    int join_thread = pthread_join(threads[i], NULL);
    if (join_thread != 0){
      perror("erreur join thread");
      exit(1);
    }
  }
  std::cout << "thread principal : fin de tous les threads secondaires" << std::endl;

  // lib�rer les ressources avant terminaison 
  pthread_mutex_destroy(&vPartage.verrou);
  for (int i = 0; i < atoi(argv[1]); i++){
    pthread_cond_destroy(&vPartage.cond);
  }
  return 1;
}
 
