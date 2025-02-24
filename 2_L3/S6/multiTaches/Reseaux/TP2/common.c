#include "common.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include<arpa/inet.h>
#include<string.h>
/*
Le hostname -I de archlinux :
ip -4 addr show | grep "inet" | awk '{print $2}' | cut -d/ -f1
*/
int recvTCP(int sock,void * msg){

   int sizeMsg;
   int tailleREC = recv(sock, &sizeMsg,sizeof(sizeMsg) , 0);
   if (tailleREC == -1){
    perror("Client : pb pour recevoir le msg :");
    exit(1); // je choisis ici d'arrêter le programme car le reste
	     // dépendent de la réussite de la création de la socket.
  }

   int tailleR = 0;
   char * msgF =(char*)malloc(sizeMsg);
   int tailleM = sizeMsg;

   while (sizeMsg) {
   int recu = recv(sock, &msgF + tailleR, tailleM - tailleR,0);
   if (recu == -1){
    perror("Client : pb pour envoyer le msg :");
    exit(1); // je choisis ici d'arrêter le programme car le reste
	     // dépendent de la réussite de la création de la socket.
  }
  memcpy(msg + strlen(msg),msgF,recu);
  tailleR = tailleR + recu;
   }
   free(msgF);
   return tailleR;
}

int sendTCP(int sock, void * msg, int sizeMsg){
  int tailleM = sizeMsg;
  int tailleE = 0;
  //envoie taille msg : 
  int envoieTaille = send(sock,&tailleM,sizeof(tailleM),0);
  if (envoieTaille == -1){
    perror("Client : pb pour envoyer le msg :");
    exit(1); // je choisis ici d'arrêter le programme car le reste
	     // dépendent de la réussite de la création de la socket.
  }

  //envoie le dit msg :
  while (sizeMsg) {
  int envoieM = send(sock,(&tailleM+tailleE),tailleM - tailleE,0);
  if (envoieM == -1){
    perror("Client : pb pour envoyer le msg :");
    exit(1); // je choisis ici d'arrêter le programme car le reste
	     // dépendent de la réussite de la création de la socket.
  }
  tailleE = tailleE + envoieTaille;
  }
  return tailleE;
   }

