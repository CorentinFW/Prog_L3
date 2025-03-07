#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>


#define MAX_BUFFER_SIZE 146980
// Fonction pour recevoir des données
ssize_t recv_data(int socket, char *buffer, size_t length) {
    size_t totalReceived = 0; // Nombre total d'octets reçus
    ssize_t bytesReceived = 0;

    while (totalReceived < length) {
        bytesReceived = recv(socket, buffer + totalReceived, length - totalReceived, 0);
        if (bytesReceived <= 0) {
            // Erreur ou connexion fermée
            if (bytesReceived == 0) {
                // La connexion a été fermée
                return totalReceived;
            }
            // Si une erreur s'est produite, retourner une valeur négative
            return -1;
        }
        totalReceived += bytesReceived;
    }

    return totalReceived;
}

// Structure pour passer des paramètres au thread
struct ThreadParams {
    int threadId;
    int clientSocket;
};


// Fonction pour gérer les erreurs et fermer le socket
void handleError(const char *message, int socket) {
  perror(message);
  close(socket);
  pthread_exit(NULL);
}

// Fonction pour construire le chemin du fichier
char *buildFilePath(const char *fileName, const char *directory) {
  char *filePath = (char*)malloc(strlen(fileName) + strlen(directory) + 1);
  filePath[0] = '\0';
  strcat(filePath, directory);
  strcat(filePath, fileName);
  return filePath;
}

// Fonction exécutée par chaque thread pour gérer un client
void *handleClient(void *params) {
    struct ThreadParams *p = (struct ThreadParams *)params;
    int threadId = p->threadId;
    int clientSocket = p->clientSocket;
    printf("Thread %d : je suis le thread %d \n", threadId, threadId);

    // Afficher la taille du buffer de réception
    int bufferSize;
    unsigned int optLen = sizeof(bufferSize);
    getsockopt(clientSocket, SOL_SOCKET, SO_SNDBUF, &bufferSize, &optLen);
    printf("Serveur: taille du buffer de réception : %d octets \n", bufferSize);

    int totalReceived = 0; // Compteur du nombre total d'octets reçus du client

    // Recevoir la taille du nom du fichier et le nom du fichier
    int nameSize;
    if (recv_data(clientSocket, (char *)&nameSize, sizeof(int)) <= 0) {
        handleError("Serveur : pb réception taille nom fichier", clientSocket);
    }
    totalReceived += sizeof(int);

    char *fileName = (char*)malloc(nameSize);
    if (recv_data(clientSocket, fileName, nameSize) <= 0) {
        handleError("Serveur : pb réception nom fichier", clientSocket);
    }
    totalReceived += nameSize;
    printf("Serveur, je vais recevoir le fichier %s\n", fileName);

    // Construire le chemin du fichier
    char *filePath = buildFilePath(fileName, "./reception/");
    free(fileName);

    // Ouvrir le fichier pour écriture
    FILE *file = fopen(filePath, "wb");
    if (file == NULL) {
        handleError("Serveur : erreur ouverture fichier", clientSocket);
    }
    free(filePath);

    // Recevoir la taille du fichier
    int fileSize;
    if (recv_data(clientSocket, (char *)&fileSize, sizeof(int)) <= 0) {
        handleError("Serveur : pb réception taille fichier", clientSocket);
    }
    totalReceived += sizeof(int);

    int contentReceived = 0; // Compte le nombre d'octets du fichier reçu
    printf("Serveur, je dois recevoir %d octets (contenu) \n", fileSize);
    int receiveCalls = 0;

    // Recevoir le contenu du fichier
    while (contentReceived < fileSize) {
        char buffer[MAX_BUFFER_SIZE];
        int bytesReceived = recv(clientSocket, buffer, MAX_BUFFER_SIZE, 0);
        if (bytesReceived <= 0) {
            handleError("Serveur : pb réception contenu fichier", clientSocket);
            break;
        }
        receiveCalls++;
        if (fwrite(buffer, sizeof(char), bytesReceived, file) < bytesReceived) {
            handleError("Serveur : erreur écriture fichier", clientSocket);
            break;
        }
        contentReceived += bytesReceived;
    }

    // Fermer le fichier et le socket client
    fclose(file);
    printf("Serveur : fin du dialogue avec le client, nombre total d'octets reçus : %d, dont %d du fichier, reçus en %d appels à recv \n",
           totalReceived + contentReceived, contentReceived, receiveCalls);
    close(clientSocket);
    free(p);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    // Créer une socket d'écoute
    int serverSocket = socket(PF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Serveur : problème création socket");
        exit(1);
    }

    // Nommer la socket
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(0);

    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Serveur : erreur bind");
        close(serverSocket);
        exit(1);
    }

    // Mettre en écoute
    if (listen(serverSocket, 5) < 0) {
        perror("Serveur : erreur listen");
        close(serverSocket);
        exit(1);
    }

    // Afficher les informations du serveur
    socklen_t addrLen = sizeof(serverAddr);
    if (getsockname(serverSocket, (struct sockaddr *)&serverAddr, &addrLen) < 0) {
        perror("Serveur : erreur getsockname");
        close(serverSocket);
        exit(1);
    }
    printf("Serveur : mon numéro de port est : %d \n", ntohs(serverAddr.sin_port));
    printf("Serveur : mon numéro d'adresse est : %s \n", inet_ntoa(serverAddr.sin_addr));

    // Attendre les clients et créer des threads pour les gérer
    int threadCount = 0;
    while (1) {
        printf("Serveur : j'attends la demande d'un client \n");
        struct sockaddr_in clientAddr;
        socklen_t clientAddrLen = sizeof(clientAddr);

        int clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &clientAddrLen);
        if (clientSocket < 0) {
            perror("Serveur : pb accept");
            exit(1);
        }
        printf("Serveur: le client %s:%d est connecté \n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

        // Créer un thread pour gérer le client
        pthread_t thread;
        struct ThreadParams *params = malloc(sizeof(struct ThreadParams));
        params->threadId = threadCount;
        params->clientSocket = clientSocket;
        pthread_create(&thread, NULL, handleClient, (void *)params);
        pthread_detach(thread);
        threadCount++;
    }

    close(serverSocket);
    printf("Serveur : c'est fini\n");
    return 0;
}
