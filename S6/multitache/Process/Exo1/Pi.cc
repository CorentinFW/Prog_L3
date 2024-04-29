#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <unistd.h>

typedef struct Msg {
    long monetiquette;
    long msg;
} msg;

int main(int argc, char * argv[]) {
        if(argc != 2){
        perror("argument manquant, ou en trop");
    }
    key_t cle = ftok(argv[1], 10);

    int f_id = msgget(cle, 0);

    long monPid = getpid() + 10;

    printf("Pi : Je demande l'acces a la ressource, pid = %ld\n", monPid);
    printf("Pi : Je depose le message, pid = %ld\n", monPid);

    msg demande_acces = {.monetiquette = 1, .msg = monPid};
    int res = msgsnd(f_id, &demande_acces, (size_t) sizeof(demande_acces.msg), 0);

    printf("Pi : Je recupere le message, pid = %ld\n", monPid);

    msg donne_acces;
    res = msgrcv(f_id, &donne_acces, (size_t) sizeof(donne_acces.msg), monPid, 0);

    printf("Pi : Je commence a travailler, pid = %ld\n", monPid);

    sleep(5);

    printf("Pi : Je libere l'access, pid = %ld\n", monPid);

    msg fin_access = {.monetiquette = 2, .msg = monPid};
    res = msgsnd(f_id, &fin_access, (size_t) sizeof(fin_access.msg), 0);

    printf("Pi : Je fini, pid = %ld\n", monPid);
}