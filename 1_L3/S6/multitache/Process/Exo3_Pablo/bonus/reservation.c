#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>

#define NBRESSOURCES 6

// Fonction calcul (environ 1 seconde)
void calcul() {
    int i = 0;
    while(i<1000000000) {
        i++;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 1) {
        printf("arguments : ./prog \n");
        exit(1);
    }

    printf("Début processus utilisateur\n");

    key_t cle = ftok("./pourCle.txt", 10);
    if(cle == -1) {
        perror("Problème clé");
        exit(1);
    }

    int idSem = semget(cle, NBRESSOURCES, IPC_CREAT|0666);
    if(idSem == -1) {
        perror("Problème semget");
        exit(1);
    }

    printf("Sélectionnez vos ressources :\n  [0] Imprimante \n  [1] Drone\n  [2] Aspirateur\n  [3] Chat\n  [4] Appareil à raclette\n  [5] Chaussures de ski\n  [-1] OK\n");
    int ressourcesChoisies[5];
    int choix;
    int X = 0;
    do {
        printf("> ");
        scanf("%d", &choix);
        if(choix == -1) break;
        int dejaSelectionne = 0;
        if(choix >= 0 && choix < NBRESSOURCES) {
            for(int i = 0; i < X; i++) {
                if(ressourcesChoisies[i] == choix) dejaSelectionne = 1;
            }
            if(dejaSelectionne) {
                printf("Cette ressource est déjà sélectionnée\n");
            } else {
                ressourcesChoisies[X] = choix;
                X++;
            }
        } else {
            printf("Cette ressource n'existe pas\n");
        }
    } while(X < 6 && choix != -1);

    printf("Vous avez choisi %d ressources\n", X);

    printf("Attente de toutes les ressources...\n");

    struct sembuf tabOpP[X];
    for(int i = 0; i < X; i++) {
        struct sembuf sb = {(u_short)ressourcesChoisies[i], (short)-1, 0};
        tabOpP[i] = sb;
    }

    if(semop(idSem, tabOpP, X) == -1) {
        perror("Problème opérations P");
        exit(1);
    }

    printf("Ressources obtenues, début du calcul...\n");

    calcul();

    printf("Calcul terminé, libération des ressources\n");

    struct sembuf tabOpV[X];
    for(int i = 0; i < X; i++) {
        struct sembuf sb = {(u_short)ressourcesChoisies[i], (short)+1, 0};
        tabOpV[i] = sb;
    }

    if(semop(idSem, tabOpV, X) == -1) {
        perror("Problème opérations V");
        exit(1);
    }

    printf("Ressources libérées\n");

    printf("Fin processus utilisateur\n");

    exit(0);
}
