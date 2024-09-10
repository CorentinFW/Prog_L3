#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NB_JOUEURS 4
#define NB_TOURS 10

// Structure pour les données partagées entre les threads
struct DonneesPartagees {
    int equipe_gagnante;
    int niveau_eau_equipe1;
    int niveau_eau_equipe2;
    pthread_mutex_t mutex_eau;
};

// Structure pour les paramètres d'un joueur
struct ParametresJoueur {
    int id;
    struct DonneesPartagees* donnees;
};

// Fonction pour simuler un temps aléatoire entre min et max secondes
void attenteAleatoire(int min, int max) {
    int temps_attente = min + rand() % (max - min + 1);
    sleep(temps_attente);
}

// Fonction pour simuler l'action de remplir le seau
void remplirSeau(struct ParametresJoueur* joueur) {
    printf("Equipe %d, Joueur %d : Remplissage du seau...\n", joueur->donnees->equipe_gagnante, joueur->id);
    attenteAleatoire(3, 10); // Simulation d'une action de remplissage
}

// Fonction pour le thread joueur
void* threadJoueur(void* param) {
    struct ParametresJoueur* joueur = (struct ParametresJoueur*)param;

    for (int tour = 1; tour <= NB_TOURS; tour++) {
        printf("Equipe %d, Joueur %d : Tour %d\n", joueur->donnees->equipe_gagnante, joueur->id, tour);
        
        pthread_mutex_lock(&joueur->donnees->mutex_eau);

        // Simulation de l'action de remplir le seau
        remplirSeau(joueur);

        // Mise à jour du niveau d'eau
        if (joueur->donnees->equipe_gagnante == 1)
            joueur->donnees->niveau_eau_equipe1++;
        else
            joueur->donnees->niveau_eau_equipe2++;

        // Vérification de l'équipe gagnante
        if (joueur->donnees->niveau_eau_equipe1 >= NB_TOURS) {
            printf("Equipe 1 a gagné !\n");
            joueur->donnees->equipe_gagnante = 1;
        } else if (joueur->donnees->niveau_eau_equipe2 >= NB_TOURS) {
            printf("Equipe 2 a gagné !\n");
            joueur->donnees->equipe_gagnante = 2;
        }

        pthread_mutex_unlock(&joueur->donnees->mutex_eau);

        // Attente avant le prochain tour
        attenteAleatoire(1, 5);
    }

    return NULL;
}

// Fonction pour le thread équipe
void* threadEquipe(void* param) {
    struct DonneesPartagees* donnees = (struct DonneesPartagees*)param;
    pthread_t joueurs[NB_JOUEURS];
    struct ParametresJoueur params[NB_JOUEURS];

    // Création des threads joueurs
    for (int i = 0; i < NB_JOUEURS; i++) {
        params[i].id = i + 1;
        params[i].donnees = donnees;
        if (pthread_create(&joueurs[i], NULL, threadJoueur, (void*)&params[i]) != 0) {
            perror("Erreur lors de la création du thread joueur");
            exit(EXIT_FAILURE);
        }
    }

    // Attente de la fin des threads joueurs
    for (int i = 0; i < NB_JOUEURS; i++) {
        if (pthread_join(joueurs[i], NULL) != 0) {
            perror("Erreur lors de l'attente de la fin du thread joueur");
            exit(EXIT_FAILURE);
        }
    }

    return NULL;
}

int main() {
    pthread_t equipes[2];
    struct DonneesPartagees donnees;
    pthread_mutex_init(&donnees.mutex_eau, NULL);

    donnees.equipe_gagnante = 0;
    donnees.niveau_eau_equipe1 = 0;
    donnees.niveau_eau_equipe2 = 0;

    // Création des threads équipes
    if (pthread_create(&equipes[0], NULL, threadEquipe, (void*)&donnees) != 0 ||
        pthread_create(&equipes[1], NULL, threadEquipe, (void*)&donnees) != 0) {
        perror("Erreur lors de la création des threads équipe");
        exit(EXIT_FAILURE);
    }

    // Attente de la fin des threads équipes
    if (pthread_join(equipes[0], NULL) != 0 || pthread_join(equipes[1], NULL) != 0) {
        perror("Erreur lors de l'attente de la fin des threads équipe");
        exit(EXIT_FAILURE);
    }

    // Libération des ressources
    pthread_mutex_destroy(&donnees.mutex_eau);

    return EXIT_SUCCESS;
}
