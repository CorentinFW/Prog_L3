#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>

int main(int argc, char * argv[]){
if (argc != 2){
    printf("nombre d'argument incorrect = ./rdv id_du_ftok ");
    exit(0);
}

key_t cle = ftok("./pourCle.txt", atoi(argv[1]));
if(cle == -1){
    printf("erreur cle");
    exit(1);
}
int idSem = semget(cle, 1, 0666);



}