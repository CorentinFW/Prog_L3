#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>

// Fonction calcul (environ 1 seconde)
void calcul() {
    int i = 0;
    while(i<1000000000) {
        i++;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("arguments : ./prog idTraitement nbZones \n");
        exit(1);
    }

    int idTraitement = atoi(argv[1]);
    int nbZones = atoi(argv[2]);

    printf("[T%d] Début du traitement sur %d zones \n", idTraitement, nbZones);

    key_t cle = ftok("./pourCle.txt", 6);
    if(cle == -1) {
        perror("Problème clé");
        exit(1);
    }

    int idSem = semget(cle, 1, IPC_CREAT|0666);
    if(idSem == -1) {
        perror("Problème semget");
        exit(1);
    }

    int idMem = shmget(cle, nbZones*sizeof(int), IPC_CREAT|0600);
    if(idMem == -1){
        perror("Problème shmget");
        exit(1);
    }

    int *image;
    if((image = (int *)shmat(idMem, NULL, 0)) == (int *)-1){
        perror("Problème shmat");
        exit(1);
    }

    printf("[T%d] Je commence le traitement\n", idTraitement);

    for(int i = 0; i < nbZones; i++) {
        struct sembuf operationP;
        operationP.sem_num = i;
        operationP.sem_op = -idTraitement;
        operationP.sem_flg = 0;
        if(semop(idSem, &operationP, 1) == -1) {
            perror("Problème opération P");
            exit(1);
        }
        printf("[T%d] Traitement de la zone %d/%d...\n", idTraitement, i, nbZones);
        calcul();
        image[i] = idTraitement;
        struct sembuf operationV;
        operationV.sem_num = i;
        operationV.sem_op = idTraitement+1;
        operationV.sem_flg = 0;
        if(semop(idSem, &operationV, 1) == -1) {
            perror("Problème opération V");
            exit(1);
        }
    }

    printf("[T%d] J'ai finit le traitement !\n", idTraitement);
    printf("[T%d] Etat de l'image :\n  [ ", idTraitement);

    for(int i = 0; i < nbZones; i++) {
        printf("%d ", image[i]);
    }

    printf("]\n");

    if(shmdt(image) == -1) {
        perror("Problème shmdt");
        exit(1);
    }

    exit(0);
}
