#include <cstddef>
#include <stdlib.h>
#include <sys/types.h>
#include <iostream>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>//perror

struct msgbuff {
long mtype;// doit toujours etre en premier(c'est l'etiquette) 
long mtext;
//on peut avoir plusieur chose en plus du msg et type
};

int main(int argc, char * argv[]){
if (argc != 2){
    printf("nombre d'argument incorrect = ./Pctrl id_du_ftok_10_de_preference");
    exit(0);

}

key_t cle = ftok("./pourCle.txt", atoi(argv[1]));
if(cle == -1){
    printf("erreur cle");
    exit(1);
}
int f_id = msgget(cle, IPC_CREAT|0666);

while (true){
    struct msgbuff msg;
    //attend une demande
    int wait = msgrcv(f_id,&msg,(size_t) sizeof(msg) ,1 ,0);
    if(wait == -1){
    printf("erreur du recv");
    exit(1);
}else{
    printf("demande reçu de : %ld \n",msg.mtext);
}
    struct msgbuff autor ={.mtype = msg.mtext, .mtext = 858785};
    int send = msgsnd(f_id,&autor,(size_t) sizeof(autor),0); //envoie la donnée 858785
    if(wait == -1){
    printf("erreur du send");
    exit(1);
}else{
    printf("donnée envoyer");
}
    struct msgbuff free;
    int freedom = msgrcv(f_id,&free,(size_t) sizeof(free) ,1 ,0);// retour de la donnée
    if(freedom == -1){
    printf("LIBERE LA DONNEE");
    exit(1);
}else{
    printf("retour de la donnée, donné nouvelle : %ld \n",free.mtext);
}
}


return 0;
}