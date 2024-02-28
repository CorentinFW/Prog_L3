// test_couleur.cpp : Seuille une image en niveau de gris

#include <stdio.h>
#include "image_ppm.h"


int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgLue2[250];
  int nH, nW, nTaille,nH2,nW2,nTaille2;
  
  if (argc != 3) 
     {
       printf("Usage: ImageIn.pgm ImageOut.pgm \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgLue2);

   OCTET *ImgIn, *ImgIn2;
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue2, &nH2, &nW2);
   nTaille2 = nH2 * nW2;
  
   allocation_tableau(ImgIn, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgIn2, OCTET, nH2 * nW2);
   lire_image_pgm(cNomImgLue2, ImgIn2, nH2 * nW2);
	
    double Eqm = 0;
 for (int i=0; i < nH; i++)
 for (int j=0; j<nW;j++)
     {
        Eqm += pow(ImgIn[i*nW+j] - ImgIn2[i*nW+j],2);
  }
    Eqm = Eqm/(nH*nW);
    printf("L'eqm des deux images est : %f \n",Eqm);
   free(ImgIn); free(ImgIn2);

   return 1;
}
