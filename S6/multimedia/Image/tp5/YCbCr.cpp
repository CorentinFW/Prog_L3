// test_couleur.cpp : Seuille une image en niveau de gris

#include <stdio.h>
#include "image_ppm.h"


int main(int argc, char* argv[])
{
  char NomY[250], NomCb[250],NomCr[250],cNomImgEcrite[250];
  int nH, nW, nTaille;
  
  if (argc != 5) 
     {
       printf("Usage: ImageIn.pgm ImageOut.pgm \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",NomY) ;
   sscanf (argv[2],"%s",NomCb);
   sscanf (argv[3],"%s",NomCr);
   sscanf (argv[4],"%s",cNomImgEcrite);


   OCTET *Y, *Cb, *Cr, *ImgOut;
   
   lire_nb_lignes_colonnes_image_pgm(NomY, &nH, &nW);
   nTaille = nH * nW;
  
   allocation_tableau(Y, OCTET, nTaille);
   lire_image_pgm(NomY, Y, nH * nW);
   allocation_tableau(Cb, OCTET, nH * nW);
   lire_image_pgm(NomCb, Cb, nH * nW);
   allocation_tableau(Cr, OCTET, nH * nW);
   lire_image_pgm(NomCr, Cr, nH * nW);  
   allocation_tableau(ImgOut, OCTET, nH * nW * 3);

   
	
int R,G,B;
 for (int i=0; i < nH * nW; i++)
     {

        R = Y[i] + 1.402*(Cr[i]-128);
        G = Y[i] - 0.34414*(Cb[i]-128) - 0.714414*(Cr[i]-128);
        B = Y[i] + 1.772*(Cb[i] -128);
        if(R< 0){R = 0;}
        else if (R> 255) {R = 255;}
        if(G< 0){G = 0;}
        else if (G> 255) {G = 255;}
        if(B< 0){B = 0;}
        else if (B> 255) {B = 255;}
        ImgOut[3*i] = R;
        ImgOut[3*i+1] = G;
        ImgOut[3*i+2] = B;
  }

 
    ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH, nW);

    free(Cb); free(Y);free(Cr);free(ImgOut);

   return 1;
}
