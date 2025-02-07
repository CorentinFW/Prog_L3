#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>

int recvTCP(int sock,void * msg);
int sendTCP(int sock, void * msg, int sizeMsg);

#endif