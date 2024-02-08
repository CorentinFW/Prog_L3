/**
 * @file afd.h
 * @brief Définition d'un AFD du langage C
 * @author Michel Meynard
 */
#define EINIT 0
#define EI 1 
#define EIF 2
#define EID 3
#define ESEP 4
#define ECHIFFRE 5
#define EFLOAT 6
#define EP 7
#define ESLASH 8
#define ESLASHET 9
#define EDSLASH 10
#define ECOM 11
#define ESLASHDET 12
#define ECOM2 13
#define NBETAT 14

int TRANS[NBETAT][256];		/* table de transition : état suivant */
int JETON[NBETAT];		/* jeton (1-32000) ou non final (0) ? */

void classe(int ed, int cd, int cf, int ef){

for(int i = cd;i<=cf;i++){
    TRANS[ed][i]=ef;
}
}


void creerAfd(){			/* Construction de l'AFD */
  int i;int j;			/* variables locales */
  for (i=0;i<NBETAT;i++){
    for(j=0;j<256;j++) TRANS[i][j]=-1; /* init vide */
    JETON[i]=0;			/* init tous états non finaux */
  }
//EINIT
TRANS[EINIT]['i'] = EI;
classe(EINIT,EID,'a','h');classe(EINIT,EID,'j','z');classe(EINIT,EID,'A','Z');
classe(EINIT,ECHIFFRE,'0','9');
TRANS[EINIT]['\t'] = ESEP;TRANS[EINIT]['\n'] = ESEP;
TRANS[EINIT]['.']= EP;
TRANS[EINIT]['/']= ESLASH;

//EI
TRANS[EI]['f'] = EIF;
classe(EI,EID,'a','e');classe(EI,EID,'g','z');classe(EI,EID,'A','Z');classe(EI,EID,'0','9');

//ECHIFFRE
TRANS[ECHIFFRE]['.']= EFLOAT;
classe(ECHIFFRE,ECHIFFRE,'0','9');

//EDSLASH
classe(EDSLASH,ECOM,0,255);
TRANS[EDSLASH]['\n']= ECOM;

//EP
classe(EP,EFLOAT,'0','9');

//EID
classe(EID,EID,'a','z');classe(EID,EID,'A','Z');classe(EID,EID,'0','9');

//ESEP
TRANS[ESEP]['\t'] = ESEP;TRANS[ESEP]['\n'] = ESEP;

//EFLOAT
classe(EFLOAT,EFLOAT,'0','9');

//ESLASH
TRANS[ESLASH]['*'] = ESLASHET;

//ESLASHET
classe(ESLASHET,ESLASHET,0,255);
TRANS[ESLASHET]['*']= ESLASHDET;

//ESLASHDET
classe(ESLASHDET,ESLASHET,0,255);
TRANS[ESLASHDET]['*'] = ESLASHDET;
TRANS[ESLASHDET]['/'] = ECOM2;

JETON[EI] = 300;
JETON[EIF] = 301;
JETON[EID] = 302;
JETON[ESEP] = 303;
JETON[ECHIFFRE] = 304;
JETON[EFLOAT] = 305;
JETON[ECOM] = 306;
JETON[ECOM2] = 307;
} 