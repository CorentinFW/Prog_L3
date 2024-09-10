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
    


  /* L'etape suivante dans votre programme :
 - recevoir une adresse d'une socket TCP sous la forme d'une structure struct sockaddr_in. Cette reception se fait via la socket UDP ; 
 - terminer les echanges en UDP 
 
 Ensuite : 
 - creer une socket TCP cliente et envoyer une demande de connexion à l'addresse que vous venez de recevoir. 
 - utiliser la socket TCP serveur que vous avez créée pour accepter la demande de connexion d'un client. 
 
 A ce stade, votre programme est relié à deux autres processus : un client TCP et un serveur TCP. 
 
 Ensuite : 
 - recevoir et afficher la prochaine instruction emise par ce client TCP. Cette instruction est sous forme de chaine de caracteres (Indice : un entier (int) est à recevoir avant le texte de l'instruction).
 Fin instruction
 
CC : je termine*/

  /*char instruction[2024];
    socklen_t lgAdr = sizeof(ds_TCP) ;
     ssize_t msg_serv = recvfrom(ds_UDP, instruction, sizeof(instruction), 0, (struct sockaddr *)&ds_TCP,&lgAdr) ;
  
  if(msg_serv == -1){
      printf("Erreur dans la réponse du client \n");
   }
   else{
      printf("Message du client : %s \n", instruction);
   }*/
  
  /*etape 2 */

// char CodeTCP[2024];
//     socklen_t lgAdr = sizeof(ds_TCP) ;
//      ssize_t msg_serv = recvfrom(ds_UDP, CodeTCP, sizeof(CodeTCP), 0, (struct sockaddr *)&ds_TCP,&lgAdr) ;
  
//   if(msg_serv == -1){
//       printf("Erreur dans la réponse du client \n");
//    }
//    else{
//       printf("Message du client : %s \n", CodeTCP);
//    }



  struct sockaddr_in addTCP;
  socklen_t lgAdd = sizeof(addTCP);
  int clientA = accept(ds_TCP,(struct sockaddr *)&addTCP,&lgAdd);
  char adresseTcp[200];
  int msgAdd = recv(clientA,adresseTcp,sizeof(adresseTcp),0);
  if(msgAdd == -1){
          printf("Erreur dans la réponse du client TCP \n");
      }
      else{
          printf("Message du client TCP : %s \n", adresseTcp);
      }

     struct sockaddr_in client;
   client.sin_family = AF_INET;
   client.sin_addr.s_addr = inet_addr(argv[2]); ; 
   client.sin_port = htons(atoi(argv[3]));
   socklen_t longueurC = sizeof(struct sockaddr_in);
   int ConnectClient = connect(ds_UDP,(struct sockaddr *)&client,longueurC);
 if(ConnectClient == -1){
          printf("Erreur dans la connection au client TCP \n");
      }
      else{
          printf("Client et serveur connecter\n");
      } 
/*


  */

 close(ds_UDP); close(ds_TCP);
  printf("CC : je termine\n");
  exit(EXIT_SUCCESS);
}
