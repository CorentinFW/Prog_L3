#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>


struct uneChaine{ char c ;
int x, y ;
struct uneChaine *suiv;
};


int main(int argc, char * argv[]){
if (argc != 2){
    printf("nombre d'argument incorrect = ./rdv id_du_ftok nbr_zone");
    exit(0);
}

key_t cle = ftok("./pourCle.txt", atoi(argv[1]));
if(cle == -1){
    printf("erreur cle");
    exit(1);
}
struct uneChaine man;
int idSem = semget(cle, 1, 0666);
int idMem = shmget(cle, atoi(argv[2])*sizeof(struct uneChaine), 0666);
void* connect = shmat (idMem, NULL, 0);




int detachement = shmdt (connect);
}