#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
    char cNomImgLue[250], cNomHisto[250];
    int nH, nW, nTaille, coligne, numColigne;
    //1 = ligne ; 2 = colonne
    
    if (argc != 4) 
        {
        printf("Usage: ImageIn.pgm ImageOut.pgm Seuil \n"); 
        exit (1) ;
        }
    
    sscanf (argv[1],"%s",cNomImgLue);
    sscanf (argv[2],"%d", &coligne);
    sscanf (argv[3],"%d", &numColigne);

    OCTET *ImgIn, *ImgOut;
    
    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;
    
    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nH * nW);


    if(coligne==1){
        int histo[nW]; 
        for(int i=0; i<nW; i++){
            histo[i]=0;
        }
        
        int cpt = 0;
        
        // for(int i=0; i<nW; i++){
        //     printf("%d \n", ImgIn[i]);
        // }

        for(int i=(numColigne-1)*nW; i<(numColigne*nW); i++){
            histo[cpt]=ImgIn[i];
            cpt+=1;
        }

        for(int i=0; i<nW; i++){
            printf("%d %d\n", i, histo[i]);
        }
    }
    else if(coligne==2){
        int histo[nH];
        for(int i=0; i<nH; i++){
            histo[i]=0;
        }

        int cpt = 0;

        for(int i=0; i<nH; i++){
            histo[cpt]=ImgIn[numColigne+i*nW];
            cpt+=1;
        }

        for(int i=0; i<nW; i++){
            printf("%d %d\n", i, histo[i]);
        }
    }

    
}