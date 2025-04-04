#include <stdlib.h>
#include <sys/types.h>
#include <iostream>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/msg.h>
#include <stdio.h>//perror

struct msgbuff {
long mtype;// doit toujours etre en premier(c'est l'etiquette) 
long mtext;
//on peut avoir plusieur chose en plus du msg et type
};

int main(int argc, char * argv[]){
    if (argc != 2){
    printf("nombre d'argument incorrect = ./prog id_process_lancer");
    exit(0);
}

    key_t cle = ftok("./pourCle.txt", 10);
    if(cle == -1){
    printf("erreur cle");
    exit(1);
}
    int f_id = msgget(cle, 0666);



    pid_t pid = getpid();
    struct msgbuff demande ={.mtype = 1, .mtext = (long)pid};
    int send = msgsnd(f_id,&demande,(size_t) sizeof(demande),0); //envoie la donnée 858785
    if(send == -1){
    printf("erreur du send");
    exit(1);
}else{
    printf("msg envoyer\n");
}
    


    struct msgbuff data;
    int wait = msgrcv(f_id,&data,(size_t) sizeof(data) ,pid ,0);
    if(wait == -1){
    printf("erreur du recv");
    exit(1);
}
        printf("voici le msg : %ld \n",data.mtext);
    
    


    struct msgbuff drop ={.mtype = 1, .mtext = 0};
    int finish = msgsnd(f_id,&drop,(size_t) sizeof(drop),0); //envoie la donnée 858785
    if(finish == -1){
    printf("erreur du finish \n");
    exit(1);
}else{
    printf("fini \n");
}

}