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
  
   struct sockaddr_in ad ;
   ad.sin_family = AF_INET ;
   ad.sin_addr.s_addr = INADDR_ANY ;
   ad.sin_port = htons(42493);
   int res = bind(ds, (struct sockaddr*)&ad, sizeof(ad)) ;

   if(res == -1){
      printf("Erreur dans le nommage de la socket. \n");
   }

  /* Etape 3 : Désigner la socket du serveur */

   struct sockaddr_in sockDistante ;
   sockDistante.sin_family = AF_INET ;
   sockDistante.sin_addr.s_addr = inet_addr(argv[1]) ; 
   sockDistante.sin_port = htons(atoi(argv[2])) ;
   
  /* Etape 4 : envoyer un message au serveur  (voir sujet pour plus de détails)*/
  
   socklen_t lgAdr = sizeof(sockDistante) ;
   char msg[20];
   scanf("%s", msg);
   res = sendto(ds, &msg, strlen(msg)+1, 0, (struct sockaddr *)&sockDistante, lgAdr) ;

   if(res == -1){
      printf("Erreur dans l'envoi du message");
   }
   // else{
   //    printf('%s', msg);
   // }

  /* Etape 5 : recevoir un message du serveur (voir sujet pour plus de détails)*/
  

   int messageServ;
   ssize_t msg_serv = recvfrom(ds, &messageServ, sizeof(messageServ), 0, (struct sockaddr *)&sockDistante, &lgAdr) ;

   if(msg_serv == -1){
      printf("Erreur dans la réponse du serveur \n");
   }
   else{
      printf("Message du serveur : %d \n", messageServ);
   }


   //check si c'est la bonne adresse :

   char ip_Distante[INET_ADDRSTRLEN];
   inet_ntop(AF_INET,&(client.sin_addr),ip_Distante,INET_ADDRSTRLEN);
   printf("Serveur : Adresse de l'expediteur : %s:%d\n",ip_Distante,ntohs(client.sin_port));


  /* Etape 6 : fermer la socket (lorsqu'elle n'est plus utilisée)*/
  
  int c = close(ds);
  if(c == -1){
   printf("La socket client n'a pas correctement fermé \n");
  }

  printf("Client : je termine\n");
  return 0;
}
