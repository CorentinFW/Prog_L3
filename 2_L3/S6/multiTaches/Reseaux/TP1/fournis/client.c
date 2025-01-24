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

int main(int argc, char *argv[]) {

  /* je passe en paramètre l'adresse de la socket du serveur (IP et
     numéro de port) et un numéro de port à donner à la socket créée plus loin.*/

  /* Je teste le passage de parametres. Le nombre et la nature des
     paramètres sont à adapter en fonction des besoins. Sans ces
     paramètres, l'exécution doit être arrétée, autrement, elle
     aboutira à des erreurs.*/
  if (argc != 4){
    printf("utilisation : %s ip_serveur port_serveur port_client\n", argv[0]);
    exit(1);
  }

  /* Etape 1 : créer une socket */   
  int ds = socket(PF_INET, SOCK_DGRAM, 0);

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
  
  /* Etape 2 : Nommer la socket du client */
  struct sockaddr_in adc;
   adc.sin_family = AF_INET ;
   adc.sin_addr.s_addr = INADDR_ANY;
   //inet_pton(AF_INET, argv[2],&(adc.sin_addr));
   adc.sin_port = htons(atoi(argv[3])) ; // num´ero est `a passer en param`etre !
   int rename = bind(ds,(struct sockaddr*)&adc,sizeof(adc));

   if (rename == -1){
    perror("Client : pb de nommage de la socket client :");
    close(ds);
    exit(1); // je choisis ici d'arrêter le programme car le reste
	     // dépendent de la réussite de la création de la socket.
  }
  /* Etape 3 : Désigner la socket du serveur */
   struct sockaddr_in ads;
   ads.sin_family = AF_INET;
   inet_pton(AF_INET, argv[1],&(ads.sin_addr));
   ads.sin_port = htons(atoi(argv[2]));
   // int rec = bind(ds,(struct sockaddr*)&ads,sizeof(ads));
  /* Etape 4 : envoyer un message au serveur  (voir sujet pour plus de détails)*/
  printf("msg a envoyer : \n");
  char msg[20];
  fgets(msg,sizeof(msg),stdin);
  int send = sendto(ds,msg, strlen(msg)+1,0,(struct sockaddr*)&ads,sizeof(ads));

  if (send == -1){
    perror("Client : pb pour envoyer le msg :");
    close(ds);
    exit(1); // je choisis ici d'arrêter le programme car le reste
	     // dépendent de la réussite de la création de la socket.
  }

  /* Etape 5 : recevoir un message du serveur (voir sujet pour plus de détails)*/
struct sockaddr_in ads2;
   ads2.sin_family = AF_INET;

 

  socklen_t lgAd = sizeof(ads2);  
  int recmsg;
  int rec = recvfrom(ds, &recmsg, sizeof(recmsg)+1, 0, (struct sockaddr*)&ads2, &lgAd);
   if (rec == -1){
      perror("Client : pb pour recevoir le msg :");
      close(ds);
      exit(1); // je choisis ici d'arrêter le programme car le reste
         // dépendent de la réussite de la création de la socket.
   }



  printf("msg reçu : %d \n",recmsg);
  printf("voici l'adresse : %s \n",inet_ntoa(ads2.sin_addr));//tranfo aussi le format
   printf("voici l'adresse : %d \n",ntohs(ads2.sin_port));//transfo le format du port

  /* Etape 6 : fermer la socket (lorsqu'elle n'est plus utilisée)*/
  
  
  printf("Client : je termine\n");
  close(ds);
  return 0;
}
