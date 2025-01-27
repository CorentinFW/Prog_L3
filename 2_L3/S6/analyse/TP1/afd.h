/**
 * @file afd.h
 * @brief Définition d'un AFD du langage C
 * @author Michel Meynard
 */
#define EINIT 0
#define EA 1
#define EAB 2
#define EABC 3
#define EB 4
#define EBD 5
#define NBETAT 6

int TRANS[NBETAT][256];		/* table de transition : état suivant */
int JETON[NBETAT];		/* jeton (1-32000) ou non final (0) ? */

/** construit un ensemble de transitions de ed à ef pour un intervale de char
*@param ed l'état de départ
*@param ef l'état final
*@param cd char de début
*@param cf char de fin
*/

void classe(int ed, int cd, int cf, int ef) {
    for (int c = cd; c <= cf; c++) {
        TRANS[ed][c] = ef;  // Crée la transition pour chaque caractère dans l'intervalle [cd, cf]
    }
}


void creerAfd() {
    int i, j;
    for (i = 0; i < NBETAT; i++) {
        for (j = 0; j < 256; j++) {
            TRANS[i][j] = -1;  // Initialise toutes les transitions à -1 (pas de transition)
        }
        JETON[i] = 0;  // Initialise tous les états à non-final
    }

    // Définition des transitions spécifiques
    TRANS[EINIT]['i'] = EI;
    TRANS[EI]['f'] = EIF;
    TRANS[EINIT]['_'] = EID;

    TRANS[EINIT][\t] = ESEP;
    TRANS[EINIT][\t] = ESEP;
    TRANS[EINIT][" "] = ESEP;

    TRANS[ESEP][\t] = ESEP;
    TRANS[ESEP][\t] = ESEP;
    TRANS[ESEP][" "] = ESEP;

    TRANS[ECHIFFRE]["."] = EFLOAT;
    TRANS[EINIT]["."] = EP;

    TRANS[EINIT]["/"] = ESLASH;
    TRANS[ESLASH]["*"] = ESLASHET;
    TRANS[ESLASHET]["*"] = ESLASHDET;
    TRANS[ESLASHDET]["*"] = ESLASHDET;
    TRANS[ESLASHDET]["/"] = ECOM2;

    TRANS[ESLASH]["/"] = EDSLASH;
    TRANS[EDSLASH]["\n"] = ECOM;


    // Utilisation de la fonction classe pour définir des plages de caractères
    classe(EINIT, 'a', 'h', EID);  // Transition pour les minuscules de 'a' à 'z' vers l'état EID
    classe(EINIT, 'j', 'z', EID);
    classe(EINIT, 'A', 'Z', EID);

    classe(EI, 'a', 'e', EID);  // Transition pour les minuscules de 'a' à 'z' vers l'état EID
    classe(EI, 'g', 'z', EID);
    classe(EI, 'A', 'Z', EID);
    classe(EI, '0', '9', EID);

    classe(EIF, 'a', 'z', EID);  // Transition pour les minuscules de 'a' à 'z' vers l'état EID
    classe(EIF, 'A', 'Z', EID);
    classe(EIF, '0', '9', EID);

    classe(EINIT,'0','9', ECHIFFRE);
    classe(ECHIFFRE,'0','9', ECHIFFRE);
    classe(EFLOAT,'0','9', EFLOAT);
    classe(EP,'0','9', EFLOAT);

    classe(ESLASHET,0,41, ESLASHET);
    classe(ESLASHET,43,255, ESLASHET);

    classe(ESLASHDET,0,41,ESLASHET);
    classe(ESLASHDET,43,46,ESLASHET);
    classe(ESLASHDET,48,255,ESLASHET);

    classe(EDSLASH,0,9,EDSLASH);
    classe(EDSLASH,11,255,EDSLASH);

    // Définition des états finaux et des jetons
    JETON[EA] = 300;   // Jeton pour l'état EA
    JETON[EIF] = 301;  // Jeton pour l'état EIF
    JETON[EID] = 302;
    JETON[ESEP] = 303;
    JETON[ECHIFFRE] = 304;
    JETON[EFLOAT] = 305;
    JETON[ECOM2] = 306;
    JETON[ECOM] = 307;
}
/* les bd sont à filtrer : commentaires */
