#include <sys/types.h>
#include <pthread.h>
#include <unistd.h>
#include "calcul.h"
#include <stdio.h>
#include <stdlib.h>

// Pour implémenter un rendez-vous entre tâches où chaque tâche doit attendre que toutes aient terminé la première phase avant de poursuivre,
// Il convient d'utiliser l'attente d'un événement plutôt que l'exclusion mutuelle. En effet, l'exclusion mutuelle sert à protéger l'accès à une ressource partagée (pour éviter les conflits), alors que dans le cas du rendez-vous, il s'agit de synchroniser le passage à l'étape suivante en attendant qu'un certain événement (ici, la complétion de la première phase par toutes les tâches) se produise.


/// Structure regroupant les données partagées entre les threads participants au RdV
struct predicatRdv
{
  int nbThreads;         // nombre total de threads participants
  int count;             // compteur de threads arrivés
  pthread_mutex_t mutex; // mutex pour protéger l'accès à 'count'
  pthread_cond_t cond;   // variable condition pour le rendez-vous
};

struct params
{
  // Structure pour regrouper les paramètres d'un thread.
  int idThread;                    // identifiant de thread, de 1 à N
  struct predicatRdv *varPartagee; // pointeur sur les données partagées (RdV)
};

void *participant(void *p)
{
  struct params *args = (struct params *)p;
  struct predicatRdv *predicat = args->varPartagee;

  // Phase 1 : premier travail
  printf("Thread %d : début du premier travail\n", args->idThread);
  calcul(args->idThread + rand() % 10); // simulation d'un long calcul
  printf("Thread %d : fin du premier travail\n", args->idThread);

  // Rendez-vous : synchronisation
  // The thread acquires the mutex lock to ensure exclusive access to the shared data (predicat->count). 
  // This prevents race conditions where multiple threads might try to modify count simultaneously.
  pthread_mutex_lock(&predicat->mutex);
  predicat->count++;
  if (predicat->count < predicat->nbThreads)
  {
    // Si ce n'est pas le dernier thread, on attend que tous les threads soient arrivés.
    // The pthread_cond_wait function releases the mutex and puts the thread to sleep until it is signaled.
    pthread_cond_wait(&predicat->cond, &predicat->mutex);
    // Then the waiting thread wakes up and automatically reacquires the mutex before returning from pthread_cond_wait.
  }
  else
  {
    // Dernier thread arrivé : il réveille tous les autres
    // If the current thread is the last one to arrive (predicat->count == predicat->nbThreads), 
    //it signals all waiting threads using pthread_cond_broadcast. This wakes up all threads that are waiting on the condition variable cond
    pthread_cond_broadcast(&predicat->cond);
  }
  // The mutex is released by calling pthread_mutex_unlock, allowing other threads to acquire the mutex and proceed.
  // This ensures that the critical section is protected and that only one thread can modify the shared data at a time.
  pthread_mutex_unlock(&predicat->mutex);

  // Phase 2 : second travail
  printf("Thread %d : début du second travail\n", args->idThread);
  calcul(args->idThread + rand() % 10); // reprise du calcul
  printf("Thread %d : fin du second travail\n", args->idThread);

  pthread_exit(NULL); // Fin du thread
}

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    printf("Usage : ./prog nombre_Threads\n");
    printf("Exemple : ./prog 5\n");
    exit(1);
  }

  int nbThreads = atoi(argv[1]);

  // Déclaration des tableaux pour les threads et leurs paramètres
  pthread_t threads[nbThreads];
  struct params tabParams[nbThreads];

  // Initialisation de la donnée partagée pour le rendez-vous
  struct predicatRdv rdv;
  rdv.nbThreads = nbThreads;
  rdv.count = 0;
  pthread_mutex_init(&rdv.mutex, NULL);
  pthread_cond_init(&rdv.cond, NULL);

  srand(nbThreads); // initialisation de rand pour la simulation de longs calculs

  // Création des threads
  for (int i = 0; i < nbThreads; i++)
  {
    tabParams[i].idThread = i + 1; // numérotation de 1 à nbThreads
    tabParams[i].varPartagee = &rdv;
    if (pthread_create(&threads[i], NULL, participant, (void *)&tabParams[i]) != 0)
    {
      perror("Erreur creation thread");
      exit(1);
    }
  }

  // Attente de la fin de tous les threads secondaires
  for (int i = 0; i < nbThreads; i++)
  {
    pthread_join(threads[i], NULL);
  }
  printf("Thread principal : fin de tous les threads secondaires\n");

  // Nettoyage des ressources utilisées
  pthread_mutex_destroy(&rdv.mutex);
  pthread_cond_destroy(&rdv.cond);

  return 0;
}
