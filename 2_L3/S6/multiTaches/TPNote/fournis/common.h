#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>

int recvTCP(int sock,void * msg,int sizeMsg);
int sendTCP(int sock, void * msg, int sizeMsg);
int recvTCPImg(int sock, void *msg, int sizeMsg, int *nbRecv, int *nbOctets);
int sendTCPImg(int sock, void *msg, int sizeMsg, int *nbSend, int *nbOctets);

#endif