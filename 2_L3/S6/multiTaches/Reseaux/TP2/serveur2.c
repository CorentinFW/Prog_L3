#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

/* Programme serveur */
/* 32768 et ip 162.38.84.75 */
// char *mesfin = (char*)malloc(tailleTCP)
// memcpy permet de copier le msg hasardeux par le vrai créer

int recvTCP(int sock, void *msg, int sizeMsg) {
  int nbTotalOctetsRecus = 0;

  while (nbTotalOctetsRecus < sizeMsg) {
    int resRecv = recv(sock, msg + nbTotalOctetsRecus, sizeMsg - nbTotalOctetsRecus, 0);
    if (resRecv <= 0) {
      return resRecv;
    }
    nbTotalOctetsRecus += resRecv;
  }

  return 36;
}

/*
void *recvTailleEtMessageTCP(int sock) {
  int tailleM;
  int recT = recv(sock, &tailleM, sizeof(tailleM), 0);
  if (recT == -1) {
    perror("Client : pb pour recevoir la taille du msg");
    exit(1); // je choisis ici d'arrêter le programme car le reste
             // dépendent de la réussite de la création de la socket.
  }
  printf("taille du futur message : %d \n", tailleM);
  void *msg = (void *)malloc(tailleM);
  recvTCP(sock, msg, tailleM);
  return msg;
}
*/

int main(int argc, char *argv[]) {

  /* Je passe en paramètre le numéro de port qui sera donné à la socket créée
   * plus loin.*/

  /* Je teste le passage de parametres. Le nombre et la nature des
     paramètres sont à adapter en fonction des besoins. Sans ces
     paramètres, l'exécution doit être arrétée, autrement, elle
     aboutira à des erreurs.*/
  if (argc != 2) {
    printf("utilisation : %s port_serveur\n", argv[0]);
    exit(1);
  }

  /* Etape 1 : créer une socket */
  int ds = socket(PF_INET, SOCK_STREAM, 0);

  /* /!\ : Il est indispensable de tester les valeurs de retour de
     toutes les fonctions et agir en fonction des valeurs
     possibles. Voici un exemple */
  if (ds == -1) {
    perror("Serveur : pb creation socket :");
    exit(1); // je choisis ici d'arrêter le programme car le reste
             // dépendent de la réussite de la création de la socket.
  }

  /* J'ajoute des traces pour comprendre l'exécution et savoir
     localiser des éventuelles erreurs */
  printf("Serveur : creation de la socket réussie \n");

  // Je peux tester l'exécution de cette étape avant de passer à la
  // suite. Faire de même pour la suite : n'attendez pas de tout faire
  // avant de tester.

  /* Etape 2 : Nommer la socket du seveur */
  struct sockaddr_in ad;
  ad.sin_family = AF_INET;
  ad.sin_addr.s_addr = INADDR_ANY;
  ad.sin_port = htons(atoi(argv[1]));
  int sockS = bind(ds, (struct sockaddr *)&ad, sizeof(ad));
  if (sockS == -1) {
    perror("Serveur : pb creation de la socket serve :");
    exit(1); // je choisis ici d'arrêter le programme car le reste
             // dépendent de la réussite de la création de la socket.
  }

  /* Etape 4 : recevoir un message du client (voir sujet pour plus de détails)*/
  listen(ds, 7);
  struct sockaddr_in aC;
  socklen_t lg = sizeof(struct sockaddr_in);
  int dSC = accept(ds, (struct sockaddr *)&aC, &lg);

  if (dSC == -1) {
    perror("Serveur : vote RN :");
    exit(1); // je choisis ici d'arrêter le programme car le reste
             // dépendent de la réussite de la création de la socket.
  }
  /*
  int tailleM;
  recv(dSC, &tailleM,sizeof(tailleM) , 0);
  printf("taille du futur message : %d",tailleM);
  char msg[200];
  recv(dSC, msg, sizeof(msg),0);
  printf("reçu : %s ",msg);
*/
  char msg[4];
  int msg2 = recvTCP(ds,&msg,4);
  if (msg2 == -1) {
    perror("probleme dans la reception du msg tcp ");
    exit(1); // je choisis ici d'arrêter le programme car le reste
             // dépendent de la réussite de la création de la socket.
  }
  printf("voici le msg du client : %s \n",msg);

  /* Etape 5 : envoyer un message au serveur (voir sujet pour plus de détails)*/
  int r = strlen(msg) - 1;
  send(dSC, &r, sizeof(r), 0);
  /* Etape 6 : fermer la socket (lorsqu'elle n'est plus utilisée)*/
  close(ds);
  close(dSC);

  printf("Serveur : je termine\n");
  return 0;
}
