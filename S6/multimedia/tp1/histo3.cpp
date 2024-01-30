// test_couleur.cpp : Seuille une image couleur 

#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille, nR, nG, nB, S,S2,S3;
  
  if (argc != 6) 
     {
       printf("Usage: ImageIn.ppm ImageOut.ppm Seuil \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgEcrite);
   sscanf (argv[3],"%d",&S);
   sscanf (argv[4],"%d",&S2);
   sscanf (argv[5],"%d",&S3);

   OCTET *ImgIn;
   
   lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   int nTaille3 = nTaille * 3;
   allocation_tableau(ImgIn, OCTET, nTaille3);
   lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
   /*allocation_tableau(ImgOut, OCTET, nTaille3);*/
	int Rouge[nTaille];
	int Vert[nTaille];
	int Bleue[nTaille];
    int compteur = 0;
   for (int i=0; i < nTaille3; i+=3)
     {
       nR = ImgIn[i];
       nG = ImgIn[i+1];
       nB = ImgIn[i+2];
       Rouge[compteur] = nR;
       Vert[compteur] = nG;
       Bleue[compteur] = nB;
     }
    for(int i=0;i<nTaille;i++){
        printf("%d %d %d %d\n",i,Rouge[i],Vert[i],Bleue[i]);
    }

   free(ImgIn);
   return 1;
}
