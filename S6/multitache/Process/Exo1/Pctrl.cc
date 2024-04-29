#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>

typedef struct Msg {
    long monetiquette;
    long msg;
} msg;

int main(int argc, char * argv[]) {
    if(argc != 2){
        perror("argument manquant, ou en trop");
    }
    key_t cle = ftok(argv[1], 10);

    int f_id = msgget(cle, IPC_CREAT|0666);

    while (1) {
    
    
        printf("Pctrl : Je recupere une demande d'acces\n");

        msg demande_acces;
        int res = msgrcv(f_id, &demande_acces, (size_t) sizeof(demande_acces.msg), (long) 1, 0);

        printf("Pctrl : J'ai une demande de la part de %ld\n", demande_acces.msg);
        printf("Pctrl : Je donne l'acces a %ld\n", demande_acces.msg);

        msg donne_acces = {.monetiquette = demande_acces.msg, .msg = 0};
        res = msgsnd(f_id, &donne_acces, (size_t) sizeof(demande_acces.msg), 0);

        printf("Pctrl : J'attend que %ld finisse\n", demande_acces.msg);

        msg fin_access;
        res = msgrcv(f_id, &fin_access, (size_t) sizeof(fin_access.msg), (long) 2, 0);
    }

    printf("Pctrl : Je termine\n");

}