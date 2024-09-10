#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>
#include "calcul.h"

int main(int argc, char * argv[]){

    if (argc!=6) {
        printf("Nbre d'args invalide, utilisation :\n");
        printf("%s numeroTraitement nombreTraitements nombreZones fichier-pour-cle-ipc entier-pour-cl�-ipc\n", argv[0]);
        exit(0);
    }

    int cle = ftok(argv[4], atoi(argv[5]));

    int nbSem = atoi(argv[2]) -1;

    int idSem=semget(cle, nbSem, 0);

    int laMem = shmget(cle, 0, 0666);
    if (laMem == -1){
        perror("erreur shmget : ");
        exit(-1);
    }

    int * tabTraitements;

    for(int i = 0 ; i < atoi(argv[2]) ; i++){
        if((tabTraitements = (int *)shmat(laMem, NULL, 0))==(int *)-1){
            perror("shmat");
            exit(-1);
        }
        else{
            printf("J'attends de pouvoir travailler\n");
            struct sembuf traitementSuivant = {atoi(argv[1]), 0, 0};
            semop(idSem, &traitementSuivant, 1);

            printf("Je commence le traitement de la zone %d\n", i);
            tabTraitements[atoi(argv[1])-1]+=1;
            int dtres = shmdt((int *)tabTraitements);
            if(atoi(argv[1]) != atoi(argv[2])){
                struct sembuf traitementSuivant = {atoi(argv[1])+1, -1, 0};
                semop(idSem, &traitementSuivant, 1);
            }
            printf("Zone terminée\n");
            if(atoi(argv[1]) != 1){
                struct sembuf traitementSuivant = {atoi(argv[1]), 1, 0};
                semop(idSem, &traitementSuivant, 1);
            }
        }
    }

    if(atoi(argv[1]) == atoi(argv[2])){
        int res = shmctl(laMem, IPC_RMID, NULL);
        if (res == -1){
            perror("erreur shmctl : ");
            exit(-1);
        }
    }
    printf("J'ai fini toutes les zones, je termine\n");
}