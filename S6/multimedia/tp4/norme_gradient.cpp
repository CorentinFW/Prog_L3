// test_couleur.cpp : Seuille une image en niveau de gris

#include <stdio.h>
#include "image_ppm.h"
#include <iostream>
#include <cmath>

int main(int argc, char* argv[])
{
  char cNomImgLue[255], cNomImgEcrite[255];
  int nH, nW, nTaille;
  
  if (argc != 3) 
     {
       printf("Usage: ImageIn.pgm \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgEcrite);


   OCTET *ImgIn, *ImgOut;
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  //nh = ligne , nw = colone
   allocation_tableau(ImgIn, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgOut, OCTET, nTaille);
   
    for(int i =0;i<nH-1;i++){
        for(int j = 0;j<nW-1;j++){
            ImgOut[i*nW+j] = ImgIn[i*nW+j];
        }
    }

   for(int i =0;i<nH-1;i++)
   for(int j = 0; j<nW-1;j++){
   ImgOut[i*nW+j] = sqrt(pow((ImgIn[(i+1)*nW+j]-ImgIn[i*nW+j]),2) + pow((ImgIn[i*nW+j+1]-ImgIn[i*nW+j]),2));
}

ecrire_image_pgm(cNomImgEcrite,ImgOut,nH,nW);
free(ImgIn);free(ImgOut);
return 1;
/*
   int histo[256];
   for(int i = 0;i<256;i++){
   histo[i]= 0;
}
    
    
    for(int i = 0 ;i<nH;i++)
    for(int j = 0;j<nW;j++){
        histo[ImgIn[i*nW+j]] += 1;
    }
    for(int j = 0;j<256;j++){
        printf("%d %d\n",j,histo[j]);
        }
        */
}
