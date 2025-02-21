#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h> //perror
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h> //close

#include "recvTCP.c"
#include "sendTCP.c"

#define MAX_BUFFER_SIZE 146980

int main(int argc, char *argv[]) {
  /* etape 0 : gestion des paramètres si vous souhaitez en passer */
  if (argc != 2) {
    printf("utilisation : serveur port_serveur \n");
    exit(0);
  }

  /* etape 1 : creer une socket d'écoute des demandes de connexions*/
  int ds = socket(PF_INET, SOCK_STREAM, 0);

  if (ds == -1) {
    perror("Serveur : pb creation socket :");
    exit(1);
  }

  printf("Serveur : creation de la socket réussie \n");

  /* etape 2 : nommage de la socket */
  struct sockaddr_in ad;
  ad.sin_family = AF_INET;
  ad.sin_addr.s_addr = INADDR_ANY;
  ad.sin_port = htons((short)atoi(argv[1]));
  int resBind = bind(ds, (struct sockaddr *)&ad, sizeof(ad));

  if (resBind == -1) {
    perror("Serveur : pb nommage de la socket :");
    exit(1);
  }

  printf("Serveur : nommage de la socket réussie \n");

  /* etape 3 : mise en ecoute des demandes de connexions */
  int resListen = listen(ds, 10);

  if (resListen == -1) {
    perror("Serveur : pb passage en mode écoute :");
    exit(1);
  }

  printf("Serveur : en attente de connexion... \n");

  /* etape 4 : plus qu'a attendre la demadne d'un client */
  while (1) {
    struct sockaddr_in sockClient;
    socklen_t lgSockClient = sizeof(sockClient);
    int dsClient = accept(ds, (struct sockaddr *)&sockClient, &lgSockClient);

    if (dsClient == -1) {
      perror("Serveur : pb acceptation de la demande :");
      exit(1);
    }

    printf("Serveur : connexion réussite \n");

    int totalRecv = 0; // un compteur du nombre total d'octets recus d'un client
    int nbRecv = 0;    // nombre d'appels à recv

    /* le protocol d'echange avec un client pour recevoir un fichier est à
     * définir. Ici seul un exemple de code pour l'écriture dans un fichier est
     * founi*/

    int tailleNomFichier;
    int nbRecv1, nbOctets1;
    int resRecvTCP1 = recvTCPdebug(dsClient, &tailleNomFichier, sizeof(int),
                                   &nbRecv1, &nbOctets1);

    if (resRecvTCP1 == -1) {
      perror("Serveur : pb réception du message 1 : \n");
      exit(1);
    }

    if (resRecvTCP1 == 0) {
      printf("Serveur : socket déconnectée \n");
      exit(1);
    }

    totalRecv += nbOctets1;
    nbRecv += nbRecv1;

    printf("Serveur : taille du nom du fichier reçue : %d \n",
           tailleNomFichier);

    char nomFichier[tailleNomFichier + 1];
    int nbRecv2, nbOctets2;
    int resRecvTCP2 = recvTCPdebug(dsClient, &nomFichier, tailleNomFichier,
                                   &nbRecv2, &nbOctets2);

    if (resRecvTCP2 == -1) {
      perror("Serveur : pb réception du message 2 : \n");
      exit(1);
    }

    if (resRecvTCP2 == 0) {
      printf("Serveur : socket déconnectée \n");
      exit(1);
    }

    nomFichier[tailleNomFichier] = '\0';

    totalRecv += nbOctets2;
    nbRecv += nbRecv2;

    printf("Serveur : nom du fichier reçu : %s \n", nomFichier);

    int tailleFichier;
    int nbRecv3, nbOctets3;
    int resRecvTCP3 = recvTCPdebug(dsClient, &tailleFichier, sizeof(int),
                                   &nbRecv3, &nbOctets3);

    if (resRecvTCP3 == -1) {
      perror("Serveur : pb réception du message 3 : \n");
      exit(1);
    }

    if (resRecvTCP3 == 0) {
      printf("Serveur : socket déconnectée \n");
      exit(1);
    }

    totalRecv += nbOctets3;
    nbRecv += nbRecv3;

    printf("Serveur : taille du fichier reçue : %d octets \n", tailleFichier);

    // char* filepath = "./reception/"; // cette ligne n'est bien-sur qu'un
    // exemple et doit être modifiée : le nom du fichier doit être reçu.
    char *filepath =
        malloc(strlen(nomFichier) + 17); // ./reception/+nom fichier +\0
    filepath[0] = '\0';
    strcat(filepath, "./reception/");
    strcat(filepath, nomFichier);

    // On ouvre le fichier dans lequel on va écrire
    FILE *file = fopen(filepath, "wb");
    if (file == NULL) {
      perror("Serveur : erreur ouverture fichier: \n");
      exit(1);
    }

    int total_ecrit = 0;
    char buffer[MAX_BUFFER_SIZE];

    printf("Serveur : on est à %d octets reçus depuis le début \n", totalRecv);

    while (total_ecrit < tailleFichier) {
      int resRecv5 = recv(dsClient, buffer,
                          (tailleFichier - total_ecrit < MAX_BUFFER_SIZE
                               ? tailleFichier - total_ecrit
                               : MAX_BUFFER_SIZE),
                          0);

      if (resRecv5 == -1) {
        perror("Serveur : pb réception du message 5 : \n");
        exit(1);
      }

      if (resRecv5 == 0) {
        printf("Serveur : socket déconnectée \n");
        exit(1);
      }

      totalRecv += resRecv5;
      nbRecv += 1;

      printf("Serveur : bloc de fichier reçu (%d octets) \n", resRecv5);

      size_t written = fwrite(buffer, sizeof(char), resRecv5, file);
      if (written < resRecv5) {
        printf("Serveur : Erreur a l'ecriture du fichier \n");
        fclose(file);
        break;
      } else {
        printf("Serveur : Ecrit = %ld // Reçu = %d \n", written, resRecv5);
      }

      total_ecrit += written;

      printf("Serveur : bloc de fichier ecrit (%ld octets) \n", written);
    }

    printf("Serveur : ecriture dans fichier reussie. Vous pouvez vérifier la "
           "création du fichier et son contenu.\n");

    printf("Serveur : total ecrit = %d // taille attendue du fichier = %d \n",
           total_ecrit, tailleFichier);

    printf("Serveur : j'ai reçu au total : %d octets (%d appels à recv) \n",
           totalRecv, nbRecv);
    fclose(file);
    close(dsClient);
  }

  close(ds);

  printf("Serveur : c'est fini\n");
}
