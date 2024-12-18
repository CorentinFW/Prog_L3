#include <stdio.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include<arpa/inet.h>
#include<string.h>

/* Programme serveur */
//Adresse du PC : 127.0.0.1

int main(int argc, char *argv[]) {

  /* Je passe en paramètre le numéro de port qui sera donné à la socket créée plus loin.*/

  /* Je teste le passage de parametres. Le nombre et la nature des
     paramètres sont à adapter en fonction des besoins. Sans ces
     paramètres, l'exécution doit être arrétée, autrement, elle
     aboutira à des erreurs.*/
  if (argc != 2){
    printf("utilisation : %s port_serveur\n", argv[0]);
    exit(1);
  }

  /* Etape 1 : créer une socket */   
  int ds = socket(PF_INET, SOCK_STREAM, 0);

  /* /!\ : Il est indispensable de tester les valeurs de retour de
     toutes les fonctions et agir en fonction des valeurs
     possibles. Voici un exemple */
  if (ds == -1){
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

  struct sockaddr_in add;
  add.sin_family = AF_INET ;
  add.sin_addr.s_addr = INADDR_ANY ;
  add.sin_port = htons(atoi(argv[1])) ;
  
  int res = bind(ds, (struct sockaddr *)&add, sizeof(add));
  listen(ds,1);
  if (res == -1) {
        perror("bind failed");
        exit(EXIT_FAILURE);
  }

 
  /* Etape 4 : recevoir un message du client (voir sujet pour plus de détails)*/
   struct sockaddr_in adC;
   socklen_t lgC = sizeof(struct sockaddr_in);
   char load[200];
   scanf("%s",load);
   int client = accept(ds,(struct sockaddr *)&adC,&lgC);
   char msg[200];
   int msgC = recv(client,msg,sizeof(msg),0);
   printf("reçu : %s \n",msg);

  /* Etape 5 : envoyer un message au client (voir sujet pour plus de détails)*/
   printf("1\n");
   char msgS[255];
   fgets(msgS,sizeof(msgS),stdin);
   printf("2\n");
   send(client,&msgS,sizeof(msgS),0);
   printf("3\n");
   
  /* Etape 6 : fermer la socket (lorsqu'elle n'est plus utilisée)*/
  
  int c = close(ds);
  if(c == -1){
   printf("La socket client n'a pas correctement fermé \n");
  }


  printf("Serveur : je termine\n");
  return 0;
}
