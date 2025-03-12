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
  int tailleR = 0;
  while (tailleR < sizeMsg) {
    int recu = recv(sock, &msg + tailleR, sizeMsg - tailleR, 0);
    if (recu == -1) {
      perror("Client : pb pour recevoir le msg :");
      exit(1); // je choisis ici d'arrêter le programme car le reste
               // dépendent de la réussite de la création de la socket.
    }
    tailleR = tailleR + recu;
  }
  return 1;
}

int recvTCP2(int dsC, void* mesTCP, int sizeOfTheMaximumMessageICanReceive) {
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
  char msg[400];
  int msg2 = recvTCP2(dSC,&msg,sizeof(msg));
  if (msg2 == -1) {
    perror("Serveur : vote RN :");
    close(dSC);
    close(ds);
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
