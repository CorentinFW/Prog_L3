#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>//perror
#include <unistd.h>
#include <stdio.h>
#include <sys/sem.h>
#include <stdlib.h>

union semun {
int val ;
struct semid_ds *buf ; 
unsigned short *array ;
struct seminfo * __buf ; 
} rdv ;


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

/*
struct semid_ds semInfo;
rdv.buf = &semInfo;
if(semctl(idSem, 0, IPC_STAT, rdv) == -1){
        perror("IPC_STAT");   // En cas d'erreur, afficher un message
        exit(1);
    }

if(semInfo.sem_otime == 0) { 
        rdv.val = 3;       // On initialise le sémaphore à 3 (par exemple, attend 3 processus pour le rendez-vous)
        if(semctl(idSem, 0, SETVAL, rdv) == -1){
            perror("Problème au niveau du semctl (SETVAL)"); // En cas d'échec de l'initialisation, affiche une erreur
            exit(1);
        }
        printf("Initialisation réussie\n");
    } else {
        printf("Sémaphore déjà initialisé\n");
    }
*/


struct sembuf opp;
opp.sem_num=0;
opp.sem_op=-1;
opp.sem_flg=0;

struct sembuf opv;
opv.sem_num=0;
opv.sem_op=+1;
opv.sem_flg=0;

struct sembuf opz;
opz.sem_num= 0;
opz.sem_op=0;
opz.sem_flg=0;

int op1 = semop(idSem,&opp,1);
if (op1 == -1){
    perror("erreur op 1");
    exit(1);
}
sleep(3);
printf("j'ai le semaphore \n");/**/
int op2 = semop(idSem,&opz,1);
if (op2 == -1){
    perror("erreur op 2 \n");
    exit(1);
}

printf("je l'ai plus \n");
/* V permet d'incrementer mais dans ce cas de figure si on calcule entre P et Z on peut rebloquer le dernier arriver qui n'aura pas 
le temps d'arriver a Z
int op3 = semop(idSem,&opv,1);
if (op3 == -1){
    perror("erreur op 3 \n");
    exit(1);
}
*/
printf("tous ensemble \n");

return 0;
}