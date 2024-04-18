// test_couleur.cpp : Seuille une image couleur

#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
  char cNomImgLue[250];
  //char cNomImgEcrite[250];
  int nH, nW, nTaille, nR, nG, nB;

  if (argc != 2)
     {
       printf("Usage: ImageIn.ppm\n");
       exit (1) ;
     }

   sscanf (argv[1],"%s",cNomImgLue) ;
   //sscanf (argv[2],"%s",cNomImgEcrite);

   OCTET *ImgIn;
   //OCTET *ImgOut;

   lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;

   int nTaille3 = nTaille * 3;
   allocation_tableau(ImgIn, OCTET, nTaille3);
   lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
   //allocation_tableau(ImgOut, OCTET, nTaille3);

    // création de l'histogramme et initialisation à 0
    int rouge[256];
    int vert[256];
    int bleu[256];
    for(int i=0;i<256;i++) rouge[i]=0;
    for(int i=0;i<256;i++) vert[i]=0;
    for(int i=0;i<256;i++) bleu[i]=0;

   for (int i=0; i < nTaille3; i+=3)
     {
       nR = ImgIn[i];
       nG = ImgIn[i+1];
       nB = ImgIn[i+2];

       rouge[nR]+=1;
       vert[nG]+=1;
       bleu[nB]+=1;
     }

    // écriture dans le terminal, indice valeur
    for(int i=0;i<256;i++){
        printf("%d %d %d %d\n",i,rouge[i],vert[i],bleu[i]);
    }

   //ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn);
   return 1;
}
