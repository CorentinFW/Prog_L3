int recvTCP(int sock, void *msg, int sizeMsg) {
  int nbTotalOctetsRecus = 0;

  while (nbTotalOctetsRecus < sizeMsg) {
    int resRecv = recv(sock, msg + nbTotalOctetsRecus, sizeMsg - nbTotalOctetsRecus, 0);
    if (resRecv <= 0) {
      return resRecv;
    }
    nbTotalOctetsRecus += resRecv;
  }

  return 1;
}

int recvTCPdebug(int sock, void *msg, int sizeMsg, int *nbRecv, int *nbOctets) {
  int nbTotalOctetsRecus = 0;
  int i = 0;

  while (nbTotalOctetsRecus < sizeMsg) {
    int resRecv = recv(sock, msg + nbTotalOctetsRecus, sizeMsg - nbTotalOctetsRecus, 0);
    if (resRecv <= 0) {
      return resRecv;
    }
    nbTotalOctetsRecus += resRecv;
    i++;
  }

  *nbRecv = i;
  *nbOctets = nbTotalOctetsRecus;

  return 1;
}