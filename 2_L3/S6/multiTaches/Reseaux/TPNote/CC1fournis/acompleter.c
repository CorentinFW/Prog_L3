#include <stdio.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>

#include "biblio.h"



int main(int argc, char* argv[]) {


  if(argc != 4) {
    printf("Utilisation : %s <mon_numero> <IP_serveur_distant_UDP> <port_serveur_distant_UDP> \n", argv[0]);
    printf("Avec :\n <mon_numero> : le numero qui vous a ete affecte par l'enseignant(e). Si vous avez oublié de le demander, faites le. \n");
    printf("<IP_serveur_distant_UDP> et <port_serveur_distant_UDP> : sont l'IP et le numero de port affichés au tableau\n");	
    exit(EXIT_FAILURE);
  }


  /* Création d'une socket pour échanger avec le serveur UDP distant :
     NE PAS MODIFIER */
  int ds_UDP = socket(PF_INET, SOCK_DGRAM, 0);

  if (ds_UDP == -1){
    perror("Erreur creation socket UDP :");
    exit(EXIT_FAILURE);
  }
  
  /* Création d'une socket d'écoute TCP : NE PAS MODIFIER */   
  int ds_TCP = socket(PF_INET, SOCK_STREAM, 0);
  if (ds_TCP == -1){
    perror("Erreur creation socket TCP :");
    exit(EXIT_FAILURE);
  }

  printf("Client : creation de la socket réussie \n");

  /* L'appel suivant (fonction etape_initiale) enregistre votre
     processus auprès du serveur UDP distant. Cette fonction effectue
     les étapes suivantes (vous N'AVEZ PAS à les (re)faire :
     
     - nommage de la socket TCP passée en paramètre 

     - mise en écoute de cette socket TCP 

     - envoi d'un message au serveur UDP, via la socket UDP passée en    	
     paramètre. Ce message contient des informations sur votre processus 
     et l'adresse de votre socket TCP.
       
     Ne pas modifier cet appel de fonction !
  */

  int res = etape_initiale(ds_UDP, ds_TCP, argv);
  if (res == -1){
    printf("Erreur etape initiale : verifier les parametres de votre programme. Aussi pour rappel, le code fourni jusqu'à cet affichage ne doit pas être modifié !");
    exit(EXIT_FAILURE);
  }
  

  /* votre travail commence à partir de là. */
	
  /* Aidez vous des valeurs de retour des fonctions et de traces
     d'exécution pour comprendre des éventuelles erreurs dans votre
     code. Avant le dépot de votre travail, garder uniquement des
     traces qui ont du sens.*/

  /* A présent, vous devez recevoir un message de type chaîne de
     caractères et l'afficher. Ce message est envoyé par le serveur
     UDP. Si tout se passe bien, ce message sera la prochaine étape
     (nommée instruction) à réaliser dans votre programme. Une
     instruction se terminera par la mention 'Fin instruction' dans le
     message. En cas de problème, le message sera une notification
     d'erreur de démarrage */
  printf(" Aucune erreur avant instruction\n");

  
    char instruction[2024];
  socklen_t lgAdr = sizeof(ds_UDP);
  ssize_t resRec = recvfrom(ds_UDP,&instruction,sizeof(instruction),0,(struct sockaddr*)&ds_UDP,&lgAdr);
if(resRec == -1){
   perror("Erreur lors de la reception du message");
   exit(1);
}
else{
   printf("message reçu : %s\n",instruction);
}

printf("Maintenant la phase TCP commence\n");
struct sockaddr_in addrTCP;
addrTCP.sin_family = AF_INET;
socklen_t lgAdr2 = sizeof(addrTCP);
ssize_t resRec2 = recvfrom(ds_UDP, &addrTCP, sizeof(addrTCP), 0, (struct sockaddr*)&ds_UDP, &lgAdr2);
if (resRec2 == -1) {
    perror("Erreur lors de la réception de l'adresse TCP");
    exit(1);
}
else {
    printf("Adresse TCP reçue : %s:%d\n", inet_ntoa(addrTCP.sin_addr), ntohs(addrTCP.sin_port));
}

  


// Créer une socket TCP cliente
int ds_TCP_client = socket(PF_INET, SOCK_STREAM, 0);
if (ds_TCP_client == -1) {
    perror("Erreur création socket TCP client");
    exit(EXIT_FAILURE);
}
     // Assurez-vous que la famille d'adresses est bien définie pour IPv4
    addrTCP.sin_port = htons(ntohs(addrTCP.sin_port)); // Confirmer que le port est bien en format réseau

// Connexion à la socket TCP du serveur
int resConnect = connect(ds_TCP_client, (struct sockaddr*)&addrTCP, sizeof(addrTCP));
if (resConnect == -1) {
    perror("Erreur lors de la connexion TCP");
    exit(EXIT_FAILURE);
}
else {
    printf("Connexion à la socket TCP réussie !\n");
}


printf("Serveur : demande d'acces a la socket réussie \n");

  close(lgAdr);

  int resCloseUDP = close(ds_UDP);
  if(resCloseUDP == -1){
   perror("Erreur lors de la fermeture de la Socket UDP");
   exit(1);
}

  int resCloseTCP = close(ds_TCP);
  if(resCloseTCP == -1){
   perror("Erreur lors de la fermeture de la Socket TCP");
   exit(1);
}
  printf("CC : je termine\n");
  exit(EXIT_SUCCESS);
}
