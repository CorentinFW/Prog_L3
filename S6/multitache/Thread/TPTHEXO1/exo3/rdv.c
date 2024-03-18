#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "calcul.h"

#define MAX_THREADS 4

struct predicatRdv {
    pthread_mutex_t lock;
    pthread_cond_t cond;
    int count; // Compte le nombre de threads qui ont atteint le point de rendez-vous
    int barrier_count; // Compte le nombre de threads qui ont atteint la barrière
    pthread_cond_t barrier_cond; // Condition de la barrière
};

struct params {
    int idThread;
    struct predicatRdv *varPartagee;
};

void init(struct predicatRdv *b) {
    pthread_mutex_init(&(b->lock), NULL);
    pthread_cond_init(&(b->cond), NULL);
    pthread_cond_init(&(b->barrier_cond), NULL);
    b->count = 0;
    b->barrier_count = 0;
}

void *participant(void *p) {
    struct params *args = (struct params *)p;
    struct predicatRdv *predicat = args->varPartagee;

    // Simulation d'un long calcul pour le travail avant le RdV
    printf("Thread %d : Premier travail effectué.\n", args->idThread);
    calcul(args->idThread + rand() % 10);
    printf("Thread %d : Premier travail terminé.\n", args->idThread);

    // Barrière pour attendre que tous les threads atteignent cet emplacement
    pthread_mutex_lock(&predicat->lock);
    predicat->barrier_count++;
    printf("Thread %d : Atteint la barrière.\n", args->idThread);
    if (predicat->barrier_count == MAX_THREADS) {
        printf("Thread %d : Dernier arrivé à la barrière, lever la barrière.\n", args->idThread);
        pthread_cond_broadcast(&predicat->barrier_cond);
    } else {
        printf("Thread %d : Attendre à la barrière.\n", args->idThread);
        pthread_cond_wait(&predicat->barrier_cond, &predicat->lock);
    }
    pthread_mutex_unlock(&predicat->lock);

    // RdV
    pthread_mutex_lock(&predicat->lock);
    predicat->count++;
    printf("Thread %d : Atteint le point de rendez-vous.\n", args->idThread);
    if (predicat->count == MAX_THREADS) {
        printf("Thread %d : Dernier arrivé, signaler le rendez-vous.\n", args->idThread);
        pthread_cond_broadcast(&predicat->cond);
    } else {
        printf("Thread %d : Attendre le rendez-vous.\n", args->idThread);
        pthread_cond_wait(&predicat->cond, &predicat->lock);
    }

    // Reprise et poursuite de l'exécution
    printf("Thread %d : Reprise et poursuite de l'exécution.\n", args->idThread);
    calcul(3);

    pthread_mutex_unlock(&predicat->lock);

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Argument requis.\n");
        printf("./prog nombre_Threads\n");
        exit(1);
    }

    pthread_t threads[MAX_THREADS];
    struct params tabParams[MAX_THREADS];
    struct predicatRdv varP;
    init(&varP);

    srand(atoi(argv[1]));

    // Création des threads
    for (int i = 0; i < atoi(argv[1]); i++) {
        tabParams[i].idThread = i;
        tabParams[i].varPartagee = &varP;

        if (pthread_create(&threads[i], NULL, participant, (void *)&tabParams[i]) != 0) {
            perror("Erreur lors de la création du thread");
            exit(1);
        }
    }

    // Attente de la fin des threads
    for (int i = 0; i < atoi(argv[1]); i++) {
        int join_thread = pthread_join(threads[i], NULL);
        if (join_thread != 0) {
            perror("Erreur lors de la jointure du thread");
            exit(1);
        }
    }

    // Destruction des mutex et conditions
    pthread_mutex_destroy(&varP.lock);
    pthread_cond_destroy(&varP.cond);
    pthread_cond_destroy(&varP.barrier_cond);

    printf("Thread principal : fin de tous les threads secondaires\n");
    return 0;
}
