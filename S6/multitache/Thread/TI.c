#include <sys/types.h>
#include <pthread.h>
#include <unistd.h>
#include "calcul.h"


// Structure qui regroupe les variables partagées entre les threads.
struct varPartagees {
    int nbZones;
    int *di; // le tableau indiqué dans l'énoncé
    pthread_mutex_t mutex; // Mutex pour la synchronisation
    pthread_cond_t cond; // Condition pour la synchronisation
};

// Structure qui regroupe les paramètres d'un thread
struct params {
    int idThread; // cet entier correspond au numéro de traitement associé à un thread
    struct varPartagees *vPartage;
};

// Fonction associée à chaque thread secondaire à créer.
void *traitement(void *p) {
    struct params *args = (struct params *)p;
    struct varPartagees *vPartage = args->vPartage;

    for (int i = 1; i <= vPartage->nbZones; i++) {
        pthread_mutex_lock(&vPartage->mutex);

        // Attente du tour du thread courant
        while (*(vPartage->di) != i) {
            pthread_cond_wait(&vPartage->cond, &vPartage->mutex);
        }

        pthread_mutex_unlock(&vPartage->mutex);

        // Traitement de la zone i
        cout << "Thread " << args->idThread << " traite la zone " << i << endl;
        calcul(); // Simulation d'un long calcul

        // Signal pour réveiller le thread suivant
        pthread_mutex_lock(&vPartage->mutex);
        (*(vPartage->di))++;
        pthread_cond_broadcast(&vPartage->cond);
        pthread_mutex_unlock(&vPartage->mutex);
    }

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cout << "Argument requis" << endl;
        cout << "./prog nombre_Traitements nombre_Zones" << endl;
        exit(1);
    }

    // Initialisations
    srand(time(NULL)); // Initialisation de rand pour la simulation de longs calculs

    pthread_t threads[atoi(argv[1])];
    struct params tabParams[atoi(argv[1])];

    struct varPartagees vPartage;
    vPartage.nbZones = atoi(argv[2]);
    vPartage.di = new int;
    *(vPartage.di) = 1; // Initialisation du numéro de zone en cours de traitement
    pthread_mutex_init(&vPartage.mutex, NULL); // Initialisation du mutex
    pthread_cond_init(&vPartage.cond, NULL);   // Initialisation de la condition

    // Création des threads
    for (int i = 0; i < atoi(argv[1]); i++) {
        tabParams[i].idThread = i + 1;
        tabParams[i].vPartage = &vPartage;
        if (pthread_create(&threads[i], NULL, traitement, (void *)&tabParams[i]) != 0) {
            perror("erreur creation thread");
            exit(1);
        }
    }

    // Attente de la fin des threads
    for (int i = 0; i < atoi(argv[1]); i++) {
        pthread_join(threads[i], NULL);
    }

    cout << "Thread principal : fin de tous les threads secondaires" << endl;

    // Libérer les ressources avant terminaison
    delete vPartage.di;
    pthread_mutex_destroy(&vPartage.mutex);
    pthread_cond_destroy(&vPartage.cond);

    return 0;
}
