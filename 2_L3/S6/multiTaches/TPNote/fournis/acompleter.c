#include <stdio.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include "common.h"
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


  /* Enregistrement auprès du serveur UDP distant. Cette fonction
     effectue les étapes suivantes (vous N'AVEZ PAS à les
     (re)faire :
     
     - nommage de la socket TCP passée en parametre 

     - mise en écoute de cette socket TCP 

     - envoi d'un message au serveur UDP, via la socket UDP passée en    	
       paramètre. Ce message contient des informations sur votre processus 
       et l'adresse de votre socket TCP.
       
       Ne pas modifier cet appel de fonction !
  */

  int res = etape_initiale(ds_UDP, ds_TCP, argv);
  if (res == -1){
    printf("Erreur etape initiale : verifier les parametres de votre programme et la bonne création des sockets");
    exit(EXIT_FAILURE);
  }


	/* votre travail commence à partir de là */

////////////////////////////////////////////////////////////////////////////////////////
 /* arrivé ici lors de l'exécution, votre assistant affiche la première étape à réaliser.*/
    
   // Etape 1
   
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

close(ds_UDP);

/*================================================================================================================================*/


int ds_TCP_C = socket(PF_INET, SOCK_STREAM, 0);
  if (ds_TCP_C == -1){
    perror("Erreur creation socket TCP_client :");
    exit(EXIT_FAILURE);
  }
/*client : */
struct sockaddr_in aS;
   aS.sin_family = AF_INET;
   aS.sin_addr = addrTCP.sin_addr;
   aS.sin_port = addrTCP.sin_port ; 
   socklen_t lg = sizeof(struct sockaddr_in);
  int con = connect(ds_TCP_C,(struct sockaddr*)&addrTCP,lg);
  if (con == -1){
    perror("Client : pb de nommage de la socket client :");
    close(ds_TCP);
    close(ds_TCP_C);
    exit(1); 
  }

/*serveur*/
  struct sockaddr_in ad;
  ad.sin_family = AF_INET;
  ad.sin_addr.s_addr = INADDR_ANY;
  ad.sin_port = htons(atoi(argv[1]));
  int sockS = bind(ds_TCP, (struct sockaddr *)&ad, sizeof(ad));
  if (sockS == -1) {
    exit(1); 
  }

  int ecoute = listen(ds_TCP, 7);
  if (ecoute == -1) {
    perror("serveur : l'ecoute n'a pas ecouté :");
    close(ds_TCP);
    exit(1); // je choisis ici d'arrêter le programme car le reste
             // dépendent de la réussite de la création de la socket.
  }

  struct sockaddr_in aC;
  socklen_t lg2 = sizeof(struct sockaddr_in);

  int dSC = accept(ds_TCP, (struct sockaddr *)&addrTCP, &lg2);
   if (dSC == -1){
    perror("serve : pb de nommage de la socket client :");
    close(ds_TCP);
    close(ds_TCP_C);
    exit(1); 
  }

////////////////////////////////////////////////////////////////////////////////////////   
   
  /* Etape 2 : cette étape commence par le bloc d'instructions suivant. Vous devez le decommenter sans rien modifier */
 
 /*
  void * message_a_envoyer;
  int taille_message_a_envoyer;
  
  init_donnee(&message_a_envoyer, &taille_message_a_envoyer); // crée un espace mémoire, l'initialise et renvoie son adresse et sa taille. 
  if(message_a_envoyer == NULL) {
    printf("Cet affichage ne devrait pas se produire. Autrement, signaler le problème\n");
    exit(EXIT_FAILURE);	
  } 
  */
 
////////////////////////////////////////////////////////////////////////////////////////
    
 /* Etape 3 : décommentez la décalartion suivante et utilisez la pour la réalisation de cette étape.*/


  // char * messageEtape3[2000];
  

    printf("Je termine\n");
    exit(EXIT_SUCCESS);
}
