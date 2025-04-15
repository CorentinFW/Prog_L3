#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>




int main(int argc, char * argv[]){
if (argc != 4){
    printf("nombre d'argument incorrect = ./rdv id_du_ftok nbr_sem nbr_zone");
    exit(0);
}
key_t cle = ftok("./pourCle.txt", atoi(argv[1]));
if(cle == -1){
    printf("erreur cle");
    exit(1);
}
int nombre_sem = atoi(argv[2])-1;
int nombre_zone = atoi(argv[3]);
int idSem = semget(cle, nombre_sem, 0666);
int idMem = shmget(cle, nombre_zone*sizeof(int), 0666);


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

struct sembuf opvSuiv;
opvSuiv.sem_num = 1;
opvSuiv.sem_op = +1;
opvSuiv.sem_flg = 0;

printf("avant de voler le semaphore \n");
int op1 = semop(idSem,&opp,1);
if(op1 == -1){
    perror("erreur op1");
    exit(2);
}
/* le Z ici peut servir mais le P est bloquant car on est a 0 et on finit a -1 apres le P, et dans ce cas P bloque
int op2 = semop(idSem,&opz,1);
if(op2 == -1){
    perror("erreur op2");
    exit(3);
}*/

printf("j'ai le semaphore \n");
int* connect = (int*)shmat (idMem, NULL, 0);
    for(int i = 0; i<nombre_zone;i++){
        connect[i] = (connect[i]+3);
    };
printf("je suis attacher \n");
int detachement = shmdt (connect);
printf("je suis detacher \n");
/* en fait il passe a 0 pour continuer donc apres ce V il passe a 1 et donc si on relance un P2 cela peut produire un interblocage
int op3 = semop(idSem,&opv,1);
if(op3 == -1){
    perror("erreur op3");
    exit(3);
}
printf("j'ai liberer le semaphore \n");
 */
int op4 = semop(idSem,&opvSuiv,1);
if(op4 == -1){
    perror("erreur op4");
    exit(3);
}

}