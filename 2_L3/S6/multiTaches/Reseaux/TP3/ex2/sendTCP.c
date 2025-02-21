int sendTCP(int sock, void *msg, int sizeMsg) {
  int nbTotalOctetsEnvoyes = 0;

  while (nbTotalOctetsEnvoyes < sizeMsg) {
    int resSend = send(sock, msg + nbTotalOctetsEnvoyes, sizeMsg - nbTotalOctetsEnvoyes, 0);
    if (resSend <= 0) {
      return resSend;
    }
    nbTotalOctetsEnvoyes += resSend;
  }

  return 1;
}

int sendTCPdebug(int sock, void *msg, int sizeMsg, int *nbSend, int *nbOctets) {
  int nbTotalOctetsEnvoyes = 0;
  int i = 0;

  while (nbTotalOctetsEnvoyes < sizeMsg) {
    int resSend = send(sock, msg + nbTotalOctetsEnvoyes, sizeMsg - nbTotalOctetsEnvoyes, 0);
    if (resSend <= 0) {
      return resSend;
    }
    nbTotalOctetsEnvoyes += resSend;
    i++;
  }

  *nbSend = i;
  *nbOctets = nbTotalOctetsEnvoyes;

  return 1;
}