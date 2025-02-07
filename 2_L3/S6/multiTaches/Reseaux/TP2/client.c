#include <netinet/in.h>
#include <stdio.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include<arpa/inet.h>
#include<string.h>

/* Programme client */
int sendTCP(int sock, void * msg, int sizeMsg){
  int tailleM = sizeMsg;
  int tailleE = 0;
  //envoie taille msg : 
  printf("taille msg = %d\n",sizeMsg);
  int envoieTaille = send(sock,&sizeMsg,sizeof(sizeMsg),0);
  if (envoieTaille == -1){
    perror("Client : pb pour envoyer la taille du msg :");
    exit(1); // je choisis ici d'arrêter le programme car le reste
	     // dépendent de la réussite de la création de la socket.
  }

  //envoie le dit msg :
  while (tailleE< sizeMsg) {
    int envoieM = send(sock,((char *)msg + tailleE),tailleM - tailleE,0);
    if (envoieM == -1){
      perror("Client : pb pour envoyer le msg :");
      exit(1); // je choisis ici d'arrêter le programme car le reste
        // dépendent de la réussite de la création de la socket.
    }
    tailleE = tailleE + envoieM;
  }
  return tailleE;
}

int main(int argc, char *argv[]) {

  /* je passe en paramètre l'adresse de la socket du serveur (IP et
     numéro de port) et un numéro de port à donner à la socket créée plus loin.*/

  /* Je teste le passage de parametres. Le nombre et la nature des
     paramètres sont à adapter en fonction des besoins. Sans ces
     paramètres, l'exécution doit être arrétée, autrement, elle
     aboutira à des erreurs.*/
  if (argc != 3){
    printf("utilisation : %s ip_serveur port_serveur port_client\n", argv[0]);
    exit(1);
  }

  /* Etape 1 : créer une socket */   
  int ds = socket(PF_INET, SOCK_STREAM, 0);

  /* /!\ : Il est indispensable de tester les valeurs de retour de
     toutes les fonctions et agir en fonction des valeurs
     possibles. Voici un exemple */
  if (ds == -1){
    perror("Client : pb creation socket :");
    exit(1); // je choisis ici d'arrêter le programme car le reste
	     // dépendent de la réussite de la création de la socket.
  }
  
  /* J'ajoute des traces pour comprendre l'exécution et savoir
     localiser des éventuelles erreurs */
  printf("Client : creation de la socket réussie \n");
  
  // Je peux tester l'exécution de cette étape avant de passer à la
  // suite. Faire de même pour la suite : n'attendez pas de tout faire
  // avant de tester.
  
 
  struct sockaddr_in aS;
   aS.sin_family = AF_INET;
   inet_pton(AF_INET, argv[1],&(aS.sin_addr));
   aS.sin_port = htons(atoi(argv[2])) ; // num´ero est `a passer en param`etre !
   socklen_t lg = sizeof(struct sockaddr_in);
   int con = connect(ds,(struct sockaddr*)&aS,lg);
   if (con == -1){
    perror("Client : pb de nommage de la socket client :");
    close(ds);
    exit(1); // je choisis ici d'arrêter le programme car le reste
	     // dépendent de la réussite de la création de la socket.
  }
   /*
   sendTCP :
   */
   
  /* Etape 4 : envoyer un message au serveur  (voir sujet pour plus de détails)*/
  printf("msg a envoyer : \n");
  char msg[20];
  fgets(msg,sizeof(msg),stdin);
  msg[strlen(msg)] = '\0';
  int tailleM = strlen(msg);

  int envoie = sendTCP(ds,msg, strlen(msg));

  if (envoie == -1){
    perror("Client : pb pour envoyer le msg :");
    close(ds);
    exit(1); // je choisis ici d'arrêter le programme car le reste
	     // dépendent de la réussite de la création de la socket.
  }

  /* Etape 5 : recevoir un message du serveur (voir sujet pour plus de détails)*/
int r;
  int rec = recv(ds, &r, sizeof(r), 0);
   if (rec == -1){
      perror("Client : pb pour recevoir le msg :");
      close(ds);
      exit(1); // je choisis ici d'arrêter le programme car le reste
         // dépendent de la réussite de la création de la socket.
   }
printf("reponse du serve : %d \n",r);

  /* Etape 6 : fermer la socket (lorsqu'elle n'est plus utilisée)*/
  
  
  printf("Client : je termine\n");
  close(ds);
  return 0;
}
