#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>//perror
#include <unistd.h>
#include <stdio.h>
#include <sys/sem.h>
#include <stdlib.h>

int main(int argc, char * argv[]){
    if (argc != 2){
    printf("nombre d'argument incorrect = ./rdv id_du_ftok ");
    exit(0);
}

key_t clef = ftok("./pourCle.txt", atoi(argv[1]));
if(clef == -1){
    printf("erreur dans la clef \n");
    exit(1);
}

int idSem = semget(clef,1,0666);
if(idSem == -1){
    printf("erreur dans l'id du semaphore \n");
    exit(1);
}
printf("je declare mes operation Z P et V \n");
struct sembuf opp;
opp.sem_num = 0;
opp.sem_op = -1;
opp.sem_flg = 0;

struct sembuf opz;
opz.sem_num = 0;
opz.sem_op = 0;
opz.sem_flg = 0;

struct sembuf opv;
opv.sem_num = 0;
opv.sem_op = 1;
opv.sem_flg = 0;

printf("avant P \n");
int op1 = semop(idSem,&opp,1);
if(op1 == -1){
    printf("erreur dans l'op1 \n");
    exit(1);
}

printf("avant Z \n");
int op2 = semop(idSem,&opz,1);
if(op2 == -1){
    printf("erreur dans l'op2 \n");
    exit(1);
}


printf("libérer \n");
}