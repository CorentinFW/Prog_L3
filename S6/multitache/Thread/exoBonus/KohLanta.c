#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <cstdlib>
#include <ctime>

using namespace std;

// Structure pour partager les données entre les threads
struct Equipe {
    int seau;
    pthread_mutex_t mutex;
    pthread_cond_t condition;
    bool aGagne; // Indique si l'équipe a gagné
    int nbJoueurs; // Nombre total de joueurs dans l'équipe
    int nbJoueursRevenus; // Nombre de joueurs revenus après avoir rempli le seau
};

// Structure des paramètres passés aux threads joueurs
struct JoueurParams {
    char nom[2]; // Nom du joueur (R1, R2, B1, B2, etc.)
    Equipe* equipe;
    int ordre; // Ordre de départ dans l'équipe
    pthread_t thread;
};

// Fonction pour simuler le remplissage du seau par un joueur
void* jouer(void* param) {
    JoueurParams* joueurParams = (JoueurParams*)param;
    Equipe* equipe = joueurParams->equipe;

    while (true) {
        pthread_mutex_lock(&equipe->mutex);

        // Départ du joueur
        printf("%s : Départ\n", joueurParams->nom);

        // Prise d'eau
        printf("%s : Prise d'eau\n", joueurParams->nom);
        usleep(rand() % 1000000); // Temps de simulation de remplissage de l'eau

        // Retour avec l'eau
        printf("%s : Retour avec l'eau\n", joueurParams->nom);

        // Remplissage du seau
        if (!equipe->aGagne) {
            equipe->seau++;
            printf("%s : Remplissage du seau, total : %d\n", joueurParams->nom, equipe->seau);
            if (equipe->seau >= 10) {
                printf("L'équipe a gagné ! Equipe %s\n", joueurParams->nom[0] == 'R' ? "rouge" : "bleue");
                equipe->aGagne = true;
                pthread_cond_broadcast(&equipe->condition); // Signaler à tous les joueurs que le jeu est terminé
                break; // Sortir de la boucle si l'équipe a gagné
            }
        }

        equipe->nbJoueursRevenus++;
        if (equipe->nbJoueursRevenus == equipe->nbJoueurs) {
            // Tous les joueurs sont revenus, réinitialiser la variable de condition pour permettre aux joueurs de repartir
            equipe->nbJoueursRevenus = 0;
            pthread_cond_broadcast(&equipe->condition);
        } else {
            // Attendre que tous les joueurs reviennent
            pthread_cond_wait(&equipe->condition, &equipe->mutex);
        }

        pthread_mutex_unlock(&equipe->mutex);
    }

    pthread_exit(NULL);
}

int main() {
    srand(time(NULL)); // Initialisation de rand pour la simulation

    Equipe equipeRouge;
    equipeRouge.seau = 0;
    equipeRouge.aGagne = false;
    equipeRouge.nbJoueurs = 4;
    equipeRouge.nbJoueursRevenus = 0;
    pthread_mutex_init(&equipeRouge.mutex, NULL);
    pthread_cond_init(&equipeRouge.condition, NULL);

    Equipe equipeBleue;
    equipeBleue.seau = 0;
    equipeBleue.aGagne = false;
    equipeBleue.nbJoueurs = 4;
    equipeBleue.nbJoueursRevenus = 0;
    pthread_mutex_init(&equipeBleue.mutex, NULL);
    pthread_cond_init(&equipeBleue.condition, NULL);

    JoueurParams params[8];

    // Création des joueurs
    for (int i = 0; i < 4; ++i) {
        // Joueurs de l'équipe rouge
        sprintf(params[i].nom, "R%d", i + 1);
        params[i].equipe = &equipeRouge;
        params[i].ordre = i;

        // Joueurs de l'équipe bleue
        sprintf(params[i + 4].nom, "B%d", i + 1);
        params[i + 4].equipe = &equipeBleue;
        params[i + 4].ordre = i;
    }

    // Création des threads pour les joueurs
    for (int i = 0; i < 8; ++i) {
        if (pthread_create(&params[i].thread, NULL, jouer, (void*)&params[i]) != 0) {
            cerr << "Erreur lors de la création des threads des joueurs" << endl;
            exit(1);
        }
    }

    // Attente de la fin du jeu pour chaque équipe
    pthread_mutex_lock(&equipeRouge.mutex);
    while (!equipeRouge.aGagne) {
        pthread_cond_wait(&equipeRouge.condition, &equipeRouge.mutex);
    }
    pthread_mutex_unlock(&equipeRouge.mutex);

    pthread_mutex_lock(&equipeBleue.mutex);
    while (!equipeBleue.aGagne) {
        pthread_cond_wait(&equipeBleue.condition, &equipeBleue.mutex);
    }
    pthread_mutex_unlock(&equipeBleue.mutex);

    // Join des threads des joueurs
    for (int i = 0; i < 8; ++i) {
        pthread_join(params[i].thread, NULL);
    }

    // Libération des ressources
    pthread_mutex_destroy(&equipeRouge.mutex);
    pthread_cond_destroy(&equipeRouge.condition);
    pthread_mutex_destroy(&equipeBleue.mutex);
    pthread_cond_destroy(&equipeBleue.condition);

    return 0;
}
