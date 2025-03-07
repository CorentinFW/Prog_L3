#include "common.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>

int recvTCP(int dsC, void* mesTCP, int sizeOfTheMaximumMessageICanReceive){
   int tailleTCP;
   int restaille = recv(dsC, &tailleTCP, sizeof(tailleTCP),0);
   if(restaille == -1){
      perror("Erreur lors de la reception de la taille du message TCP");
      return -1;
   }
   printf("tailleTCP : %d\n",tailleTCP);
   int tailleOriginal = tailleTCP;

   if(sizeOfTheMaximumMessageICanReceive < tailleTCP){
      perror("La memoire alloue n'est pas assez grande pour recevoir ce message");
      printf(" nb d'octet a recevoir : %d\n", tailleTCP);
      exit(-1);
   }
   char* mesFin = (char*)malloc(tailleTCP + 1);
      if (!mesFin) {
      perror("Erreur d'allocation de mémoire");
      exit(1);
   }
   printf("Message avant boucle : %s\n", mesFin);
   int octectsEnvo = 0;
   while(tailleTCP > octectsEnvo){
      int resRecTCP = recv(dsC, mesFin + octectsEnvo, tailleTCP - octectsEnvo,0);
      printf("Message recu dans boucle : %s\n", mesFin);
      if(resRecTCP == -1){
         perror("Erreur lors de la reception du message TCP");
         free(mesFin);
         exit(1);
      }
      printf("taille du message recu %d\n",resRecTCP);

      octectsEnvo = octectsEnvo + resRecTCP;
      printf("octectsEnvo Apres boucle %d\n", tailleTCP);

      //strcat(mesTCP,mesFin);
   }
   mesFin[tailleOriginal] = '\0';
   printf("message recu %s\n",mesFin);
   memcpy(mesTCP, mesFin, tailleTCP+1);
   free(mesFin);
   return 1;
}

int sendTCP(int sock, void *msg, int sizeMsg){
   int resSendTaille = send(sock,&sizeMsg,sizeof(sizeMsg),0);
   if(resSendTaille==-1) {
      perror("Erreur lors de l'envoi de la taille du message");
      exit(-1);
   }
   int tailleEnvoye = 0;
   while(tailleEnvoye < sizeMsg){
      int r = send(sock,(char*)msg + tailleEnvoye,sizeMsg-tailleEnvoye,0);
      printf("taille du message envoye %d\n",r);
      if(r==0) {
         perror("Le serveur ne repond pas");
         exit(-1);
         }
      if(r==-1) {
         perror("Erreur lors de l'envoie du message");
         exit(-1);
      }
      tailleEnvoye += r;
   }
   return tailleEnvoye;
}

int recvTCPImg(int sock, void *msg, int sizeMsg, int *nbRecv, int *nbOctets) {
  int nbTotalOctetsRecus = 0;
  int i = 0;

  while (nbTotalOctetsRecus < sizeMsg) {
    int resRecv = recv(sock, msg + nbTotalOctetsRecus, sizeMsg - nbTotalOctetsRecus, 0);
    if (resRecv <= 0) {
      return resRecv;
    }
    nbTotalOctetsRecus += resRecv;
    i++;
  }

  *nbRecv = i;
  *nbOctets = nbTotalOctetsRecus;

  return 1;
}

int sendTCPImg(int sock, void *msg, int sizeMsg, int *nbSend, int *nbOctets) {
  int nbTotalOctetsEnvoyes = 0;
  int i = 0;

  while (nbTotalOctetsEnvoyes < sizeMsg) {
    int resSend = send(sock, msg + nbTotalOctetsEnvoyes, sizeMsg - nbTotalOctetsEnvoyes, 0);
    if (resSend <= 0) {
      return resSend;
    }
    nbTotalOctetsEnvoyes += resSend;
    i++;
  }

  *nbSend = i;
  *nbOctets = nbTotalOctetsEnvoyes;

  return 1;
}