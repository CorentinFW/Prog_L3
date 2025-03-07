#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <cstdlib>
#include <vector>
#include <stdio.h>

using namespace std;

// Structure pour les variables partagées
struct varPartagees {
    int nbZones;
    vector<int> di; // Tableau pour suivre les zones traitées par chaque thread
    vector<pthread_mutex_t> mutexes; // Mutex pour chaque thread
};

// Structure pour les paramètres de chaque thread
struct params {
    int idThread;
    struct varPartagees *vPartage;
};

// Fonction simulant un calcul long
void calcul(int zone) {
    // Attendre un temps aléatoire entre 0 et 1000 microsecondes
    usleep((rand() % 1000000));
}

// Fonction exécutée par chaque thread
void *traitement(void *p) {
    struct params *args = (struct params *)p;
    struct varPartagees *vPartage = args->vPartage;
    int idThread = args->idThread;

    for (int i = 1; i <= vPartage->nbZones; i++) {
        if (idThread != 1) {
            // Attendre que le thread précédent ait terminé le traitement de la zone i
            while (true) {
                pthread_mutex_lock(&vPartage->mutexes[idThread - 1]);
                if (vPartage->di[idThread - 1] >= i) {
                    pthread_mutex_unlock(&vPartage->mutexes[idThread - 1]);
                    break;
                }
                pthread_mutex_unlock(&vPartage->mutexes[idThread - 1]);
                usleep(100); // Attendre un peu avant de revérifier
            }
        }

        // Traiter la zone i
        calcul(i);
        cout << "Thread " << idThread << " traite la zone " << i << endl;

        // Mettre à jour la zone traitée
        pthread_mutex_lock(&vPartage->mutexes[idThread]);
        vPartage->di[idThread] = i;
        pthread_mutex_unlock(&vPartage->mutexes[idThread]);
    }

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cout << "Usage: ./prog nombre_Traitements nombre_Zones" << endl;
        exit(1);
    }

    int nbTraitements = atoi(argv[1]);
    int nbZones = atoi(argv[2]);

    // Initialisation des structures
    pthread_t threads[nbTraitements];
    struct params tabParams[nbTraitements];
    struct varPartagees vPartage;
    vPartage.nbZones = nbZones;
    vPartage.di.resize(nbTraitements, 0);
    vPartage.mutexes.resize(nbTraitements);

    // Initialisation des mutex
    for (int i = 0; i < nbTraitements; i++) {
        pthread_mutex_init(&vPartage.mutexes[i], NULL);
    }

    srand(time(NULL)); // Initialisation de rand pour la simulation de longs calculs

    // Création des threads
    for (int i = 0; i < nbTraitements; i++) {
        tabParams[i].idThread = i + 1;
        tabParams[i].vPartage = &vPartage;
        if (pthread_create(&threads[i], NULL, traitement, (void *)&tabParams[i]) != 0) {
            perror("Erreur création thread");
            exit(1);
        }
    }

    // Attente de la fin des threads
    for (int i = 0; i < nbTraitements; i++) {
        pthread_join(threads[i], NULL);
    }

    cout << "Thread principal : fin de tous les threads secondaires" << endl;

    // Libération des ressources
    for (int i = 0; i < nbTraitements; i++) {
        pthread_mutex_destroy(&vPartage.mutexes[i]);
    }

    return 0;
}
