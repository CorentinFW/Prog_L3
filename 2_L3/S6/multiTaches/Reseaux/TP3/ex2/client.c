#include <stdio.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include<arpa/inet.h>
#include<string.h>
#include <sys/stat.h>

#include "sendTCP.c"
#include "recvTCP.c"

#define MAX_BUFFER_SIZE 146980

int main(int argc, char *argv[]) {

  if (argc != 4){
    printf("utilisation : client ip_serveur port_serveur nom_fichier\n Remaque : le parametre nom_fichier correspond au nom d'un fichier existant dans le répertoire emission\n");
    exit(0);
  }

  /* etape 1 : créer une socket */   
  int ds = socket(PF_INET, SOCK_STREAM, 0);
  
  if (ds == -1){
    perror("Client : pb creation socket :");
    exit(1);
  }
  
  printf("Client : creation de la socket réussie \n");
  
  /* etape 2 : designer la socket du serveur */
  struct sockaddr_in adServ;
  socklen_t lgAdServ = sizeof(adServ);
  adServ.sin_family = AF_INET;
  adServ.sin_addr.s_addr = inet_addr(argv[1]);
  adServ.sin_port = htons((short)atoi(argv[2]));
  
  /* etape 3 : demander une connexion */
  int resConnect = connect(ds, (struct sockaddr*)&adServ, lgAdServ);

  if (resConnect == -1) {
    perror("Client : pb demande de connexion :");
    exit(1);
  }

  printf("Client : demande de connexion au serveur envoyée \n");
  
  /* etape 4 : envoi de fichier : attention la question est générale. Il faut creuser pour définir un protocole d'échange entre le client et le serveur pour envoyer correctement un fichier */

  int totalSent = 0; // variable pour compter le nombre total d'octet effectivement envoyés au serveur du début à la fin des échanges.
 
  /* le bout de code suivant est une lecture de contenu d'un fichier dont le nom est passé en paramètre.
     - pour lire un fichier, il faut l'ouvrir en mode lecture
     - la lecture se fait par blocs d'octets jusqu'à la fin du fichier.
     - la taille d'un bloc est définie par la constante MAX_BUFFER_SIZE que vous pouvez modifier.

     Le code est à compléter pour mettre en place l'envoi d'un fichier.
  */

  // construction du nom du chemin vers le fichier
  char* filepath = malloc(strlen(argv[3]) + 16); // ./emission/+nom fichier +\0
  filepath[0] = '\0';
  strcat(filepath, "./emission/");
  strcat(filepath, argv[3]);

  printf("Client : je vais envoyer %s\n", filepath);

  // obtenir la taille du fichier
  struct stat attributes;
  if(stat(filepath, &attributes) == -1){
    perror("Client : erreur stat");
    free(filepath);
    exit(1);
  }

  int file_size = attributes.st_size; // cette copie est uniquement informer d'où obtenir la taille du fichier.
  
  char *file_name = argv[3];
  
  printf("Client : taille du fichier : %d octets\n", file_size);
  
  int tailleNomFichier = strlen(file_name);
  int nbSend1, nbOctets1;
  int resSendTCP1 = sendTCPdebug(ds, &tailleNomFichier, sizeof(int), &nbSend1, &nbOctets1);
  
  if (resSendTCP1 == -1) {
    perror("Client : pb envoi du message 1 :");
    exit(1);
  }
  
  if (resSendTCP1 == 0) {
    printf("Client : socket déconnectée \n");
    exit(1);
  }
  
  totalSent += nbOctets1;
  
  printf("Client : taille du nom du fichier envoyée \n");
  
  int nbSend2, nbOctets2;
  int resSendTCP2 = sendTCPdebug(ds, file_name, strlen(file_name), &nbSend2, &nbOctets2);
  
  if (resSendTCP2 == -1) {
    perror("Client : pb envoi du message 2 : \n");
    exit(1);
  }
  
  if (resSendTCP2 == 0) {
    printf("Client : socket déconnectée \n");
    exit(1);
  }
  
  totalSent += nbOctets2;
  
  printf("Client : nom du fichier envoyé \n");
  
  int nbSend3, nbOctets3;
  int resSendTCP3 = sendTCPdebug(ds, &file_size, sizeof(int), &nbSend3, &nbOctets3);
  
  if (resSendTCP3 == -1) {
    perror("Client : pb envoi du message 3 : \n");
    exit(1);
  }
  
  if (resSendTCP3 == 0) {
    printf("Client : socket déconnectée \n");
    exit(1);
  }
  
  totalSent += nbOctets3;
  
  printf("Client : taille du fichier envoyé \n");

  
  // lecture du contenu d'un fichier
  FILE* file = fopen(filepath, "rb");
  if(file == NULL){
    perror("Client : erreur ouverture fichier \n");
    free(filepath);
    exit(1);   
  }
  free(filepath);

  int total_lu = 0;
  char buffer[MAX_BUFFER_SIZE];

  while(total_lu < file_size){
    size_t read = fread(buffer, sizeof(char), MAX_BUFFER_SIZE, file);
    if(read == 0){
      if(ferror(file) != 0){
        perror("Client : erreur lors de la lecture du fichier \n");
        fclose(file);
        exit(1);
      }else{
        printf("Client : arrivé a la fin du la lecture du fichier\n");// fin du fichier
      	break;
      }
    }
    printf("Client : j'ai lu un bloc du fichier (%ld octets) \n", read);  
    
    int nbSend5, nbOctets5;
    int resSendTCP5 = sendTCPdebug(ds, buffer, read, &nbSend5, &nbOctets5);
    
    if (resSendTCP5 == -1) {
      perror("Client : pb envoi du message 5 : \n");
      exit(1);
    }
    
    if (resSendTCP5 == 0) {
      printf("Client : socket déconnectée \n");
      exit(1);
    }
    
    totalSent += nbOctets5;
    
    printf("Client : bloc du fichier envoyé \n");
    
    total_lu += read;
  }

  // fermeture du fichier
  fclose(file); 
   
  printf("Client : j'ai lu au total : %d octets \n", total_lu);  
  printf("Client : j'ai envoyé au total : %d octets \n", totalSent);
  
  close(ds);
  
  printf("Client : c'est fini\n");
}

