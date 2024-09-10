#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>



int main(int argc, char * argv[]){

    if(argc != 4){
        printf("./traitIm  fichier int Nombre_semaphore\n");
        exit(0);
    }
    int nbSem = argv[3];
    //clef
    int clef = ftok(argv[1],atoi(argv[2]));
    int idShm = shmget(clef,0,0666);
    int idSem = semget(clef,nbSem,0666);

    int * image = (int *)shmat(idShm,NULL,0);
    printf("image = %d \n", image);
    if(image == (void *)-1){
        perror("echec attachement\n");
        exit(0);
    }
    printf("Attachement réussi\n");

    struct sembuf Inc = 
    {
        {0,1,0}
    };
    
    // for(int i =0; i<= 3;i++){
    //     printf("%d \n", image[i]);
    // }

    int detach = shmdt(image);
    if(detach == -1){
        perror("Echec detachement\n");
        exit(0);
    }

    printf("detachement reussi\n");

}