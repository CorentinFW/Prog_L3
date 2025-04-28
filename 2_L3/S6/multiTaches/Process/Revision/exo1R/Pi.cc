#include <cstddef>
#include <stdlib.h>
#include <sys/types.h>
#include <iostream>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>//perror
#include <unistd.h>

struct msgbuff{ //c'est le mm que msgbuf 
long etiquette;
long text;
};

int main( int argc, char * argv[]){
    if (argc != 2){
        printf("nombre d'arg invalide on veut Pctrl code_pour_clef ");
        exit(1);
    }



    key_t clef = ftok("./pourCle.txt", atoi(argv[1]));
    if (clef == -1){
        printf("erreur dans la clef");
        exit(1);
    }
    
    int file = msgget(clef, 0666);

    /*demander la donnée*/
        pid_t id = getpid();
        struct msgbuff msg;
        msg.etiquette = 1;
        msg.text = id;

        int demande = msgsnd(file, &msg,(size_t) sizeof(struct msgbuff), 0);
        if (demande == -1){
        printf("erreur dans la demande de la donner \n");
        exit(1);
    }
        printf("envoie de la demande \n ");
        int data = msgrcv(file, &msg, (size_t) sizeof(struct msgbuff), id, 0);
        if (data == -1){
        printf("erreur dans la data \n");
        exit(1);
    }
        printf("obtention de la donnée , donnée actuelle : %ld \n", msg.text);
        msg.etiquette = 2;
        msg.text = msg.text*10;

        int finish = msgsnd(file, &msg, (size_t) sizeof(struct msgbuff), 0);
        if (clef == -1){
        printf("erreur dans le finish \n");
        exit(1);
    }
        printf("renvoie de la nouvelle donnée , je m'arrete la \n");

}