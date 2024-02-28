// test_couleur.cpp : Seuille une image en niveau de gris

#include <stdio.h>
#include "image_ppm.h"


int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcriteY[250],cNomImgEcriteCb[250],cNomImgEcriteCr[250];
  int nH, nW, nTaille;
  
  if (argc != 5) 
     {
       printf("Usage: ImageIn.pgm ImageOut.pgm \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgEcriteY);
   sscanf (argv[3],"%s",cNomImgEcriteCb);
   sscanf (argv[4],"%s",cNomImgEcriteCr);


   OCTET *ImgIn, *ImgOutY, *ImgOutCr, *ImgOutCb;
   
   lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW *3;
  
   allocation_tableau(ImgIn, OCTET, nTaille);
   lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgOutY, OCTET, nH * nW);
   allocation_tableau(ImgOutCr, OCTET, nH * nW);
   allocation_tableau(ImgOutCb, OCTET, nH * nW);

   
	

 for (int i=0; i < nH * nW; i++)
     {
       ImgOutY[i] = (0.299*ImgIn[3*i]) + (0.587*ImgIn[3*i+1]) + (0.114*ImgIn[3*i+2]);
       ImgOutCb[i] = (-0.1687*ImgIn[3*i]) + (-0.3313*ImgIn[3*i+1]) + (0.5*ImgIn[3*i+2])+128 ;
       ImgOutCr[i] = (0.5*ImgIn[3*i]) + (-0.4187*ImgIn[3*i+1]) + (-0.0813*ImgIn[3*i+2])+128  ;
  }

    ecrire_image_pgm(cNomImgEcriteY, ImgOutY,  nH, nW);
    ecrire_image_pgm(cNomImgEcriteCb, ImgOutCb,  nH, nW);
    ecrire_image_pgm(cNomImgEcriteCr, ImgOutCr,  nH, nW);

    free(ImgIn); free(ImgOutY);free(ImgOutCr);free(ImgOutCb);

   return 1;
}
