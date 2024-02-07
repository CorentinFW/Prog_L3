// test_couleur.cpp : Seuille une image en niveau de gris

#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250],cNomImgLue2[250];
  int nH, nW, nTaille, S;
  
  if (argc != 4) 
     {
       printf("Usage: ImageIn.pgm ImageOut.pgm \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue);
   sscanf (argv[2],"%s",cNomImgLue2);
   sscanf (argv[2],"%s",cNomImgEcrite);
  printf("%c",argv[2]);
   OCTET *ImgIn,*ImgIn2, *ImgOut;
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   allocation_tableau(ImgIn, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgIn2, OCTET, nTaille);
   lire_image_pgm(cNomImgLue2, ImgIn2, nH * nW);
   allocation_tableau(ImgOut, OCTET, nTaille);

for(int x = 0;x<2;x++){
 for (int i=1; i < nH-1; i++)
   for (int j=1; j < nW-1; j++)
     {
       if ((ImgIn[i*nW+j+1] == 255 || ImgIn[i*nW+j-1] == 255 || ImgIn[(i+1)*nW+j] == 255 || ImgIn[(i-1)*nW+j] == 255 
       || ImgIn[(i-1)*nW+j+1] == 255
       || ImgIn[(i-1)*nW+j-1] == 255 || ImgIn[(i+1)*nW+j+1] == 255|| ImgIn[(i+1)*nW+j-1] == 255)
       &&
       (ImgIn2[i*nW+j+1] == 255 || ImgIn2[i*nW+j-1] == 255 || ImgIn2[(i+1)*nW+j] == 255 || ImgIn2[(i-1)*nW+j] == 255 
       || ImgIn2[(i-1)*nW+j+1] == 255
       || ImgIn2[(i-1)*nW+j-1] == 255 || ImgIn2[(i+1)*nW+j+1] == 255|| ImgIn2[(i+1)*nW+j-1] == 255)
       )
       {
        ImgOut[i*nW+j]=255;
        //printf("%d \n",i);
       }
       if ((ImgIn[i*nW+j+1] == 0 || ImgIn[i*nW+j-1] == 0 || ImgIn[(i+1)*nW+j] == 0 || ImgIn[(i-1)*nW+j] == 0 
       || ImgIn[(i-1)*nW+j+1] == 0
       || ImgIn[(i-1)*nW+j-1] == 0 || ImgIn[(i+1)*nW+j+1] == 0 || ImgIn[(i+1)*nW+j-1] == 0) 
       &&
       (ImgIn2[i*nW+j+1] == 0 || ImgIn2[i*nW+j-1] == 0 || ImgIn2[(i+1)*nW+j] == 0 || ImgIn2[(i-1)*nW+j] == 0 
       || ImgIn2[(i-1)*nW+j+1] == 0
       || ImgIn2[(i-1)*nW+j-1] == 0 || ImgIn2[(i+1)*nW+j+1] == 0 || ImgIn2[(i+1)*nW+j-1] == 0)
       )
       ImgOut[i*nW+j]=255;
       else ImgOut[i*nW+j]=0;
     }
}


   ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn); free(ImgIn2);free(ImgOut);

   return 1;
}
