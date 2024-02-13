// test_couleur.cpp : Seuille une image en niveau de gris

#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille, S;
  
  if (argc != 3) 
     {
       printf("Usage: ImageIn.pgm ligne \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf(argv[2],"%d",S);

   OCTET *ImgIn;
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
    
   allocation_tableau(ImgIn, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
//    if (S>nW){
//     printf("erreur la valeur de la ligne attendu est trop grande");
//     exit(1);
//    }
   int histo[nW];
    for(int j = 1;j<nW-1;j++){
        histo[j] = ImgIn[nW*S+j];
    }
    for(int j = 1;j<nW-1;j++){
        printf("%d %d\n",j,histo[j]);
        }
    free(ImgIn);
    free(histo);
}

