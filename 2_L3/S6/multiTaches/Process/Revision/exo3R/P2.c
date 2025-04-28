#include <stdlib.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>//perror
#include <unistd.h>
#include <stdio.h>
#include <sys/sem.h>
#include <stdlib.h>

int main(int argc, char * argv[]){
    if (argc != 4){
    printf("nombre d'argument incorrect = ./rdv id_du_ftok nbr_sem nbr_zone");
    exit(0);
}

key_t clef = ftok("./pourCle.txt", atoi(argv[1]));
if(clef == -1){
    printf("erreur dans la clef \n");
    exit(1);
}
int nombre_sem = atoi(argv[2])-1;
int nombre_zone = atoi(argv[3]);

int idSem = semget(clef,nombre_sem,0666);
if(idSem == -1){
    printf("erreur dans l'id du semaphore \n");
    exit(1);
}

int idMem = shmget(clef, nombre_zone, 0666);

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
opv.sem_num = 1;
opv.sem_op = 1;
opv.sem_flg = 0;

printf("avant P \n");
int op1 = semop(idSem,&opp,1);
if(op1 == -1){
    printf("erreur dans l'op1 \n");
    exit(1);
}


int* connect = (int*)shmat(idMem, NULL, 0);


for(int i; i< nombre_zone;i++){
    connect[i] = connect[i] + 1 ;
}


printf("voici la liste modfifier apres P1 : ");
printf("[");
for (int i = 0; i < nombre_zone-1; i++) {
    printf("%d, ", connect[i]);
}
printf("%d] \n", connect[nombre_zone-2]);

int deconnect = shmdt(connect);
printf("je me detache");
if(deconnect == -1){
    printf("detachement probleme");
    exit(1);
}

printf("avant V \n");
int op2 = semop(idSem,&opv,1);
if(op2 == -1){
    printf("erreur dans l'op2 \n");
    exit(1);
}

printf("fini \n");
}