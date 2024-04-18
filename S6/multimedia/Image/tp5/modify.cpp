// test_couleur.cpp : Seuille une image en niveau de gris

#include <stdio.h>
#include "image_ppm.h"


int main(int argc, char* argv[])
{
  char cNomImgLue[250],cNomImgEcrite[250];
  int nH, nW, nTaille, k;
  sscanf(argv[3], "%d", &k);
  if (argc != 4 || k<-128 || k>128) 
     {
       printf("Usage: ImageIn.pgm ImageOut.pgm \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgEcrite);
   

   OCTET *ImgIn, *ImgOut;
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   allocation_tableau(ImgIn, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgOut, OCTET, nH * nW);

   


 for (int i=0; i < nH * nW; i++)
     {
        int newPix = ImgIn[i] + k;
        
        if (newPix > 255){newPix = 255;}
        else if (newPix < 0) {newPix = 0;}
        ImgOut[i] = newPix;
        
  }

 
    ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);

    free(ImgIn);free(ImgOut);

   return 1;
}
