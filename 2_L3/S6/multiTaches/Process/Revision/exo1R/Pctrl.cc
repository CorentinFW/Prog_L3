#include <cstddef>
#include <stdlib.h>
#include <sys/types.h>
#include <iostream>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>//perror

struct msgbuff{ //c'est le mm que msgbuf 
long etiquette;
long text;
};

int main( int argc, char * argv[]){
    if (argc != 2){
        printf("nombre d'arg invalide on veut Pctrl code_pour_clef");
        exit(1);
    }



    key_t clef = ftok("./pourCle.txt", atoi(argv[1]));
    if (clef == -1){
        printf("erreur dans la clef");
        exit(1);
    }
    
    int id = msgget(clef, IPC_CREAT | 0666);
    int val = 878587;
    /*attendre un msg*/
    while(1){
        struct msgbuff msg;
        int demande = msgrcv(id, &msg, (size_t) sizeof(struct msgbuff), 1, 0);
        if(demande == -1){
            printf("erreur du recv \n");
            exit(1);
        }else{
            printf("demande reçu de : %ld \n",msg.text);
        }
        printf("demande reçu \n");
        msg.etiquette = msg.text;
        msg.text = val;

        int renvoie = msgsnd(id, &msg,(size_t) sizeof(struct msgbuff), 0);
        if (renvoie == -1){
        printf("erreur dans l'envoie de la donner \n");
        exit(1);
    }
        printf("envoie de la donnée \n");
        int freedom = msgrcv(id, &msg, (size_t) sizeof(struct msgbuff), 2, 0);
        val = msg.text;
        printf("liberation de la donnée, nouvelle donnée : %ld \n", msg.text);
    }
}