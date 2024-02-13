// test_couleur.cpp : Seuille une image en niveau de gris

#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille, value,ind;
  
  if (argc != 4) 
     {
       printf("Usage: ImageIn.pgm \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%d",&ind);
   sscanf (argv[3],"%d",&value) ;


   OCTET *ImgIn, *ImgOut;
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  //nh = ligne , nw = colone
   allocation_tableau(ImgIn, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
   
   if(ind == 1){
    int profil[nH];
    for(int i = 0;i<nH;i++){
        profil[i] = ImgIn[i*nW+value];
    }
    for(int j = 0;j<nW;j++){
        printf("%d %d\n",j,profil[j]);
        }
   }
   //pour les ligne
   else{
    int profil[nW];
    int compteur = 0;
    for(int i = (value-1)*nW;i<(nW*value);i++){
        profil[compteur] = ImgIn[i];
        compteur += 1;
    }
    for(int j = 0;j<nW;j++){
        printf("%d %d\n",j,profil[j]);
        }
   }
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
