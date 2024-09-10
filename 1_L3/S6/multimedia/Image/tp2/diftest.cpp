#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
    if (argc != 4) 
    {
        printf("Usage: %s ImageSeuillee.pgm ImageDilatee.pgm ImageContours.pgm\n", argv[0]);
        return 1;
    }

    char cNomImgSeuillee[250], cNomImgDilatee[250], cNomImgContours[250];
    sscanf(argv[1], "%s", cNomImgSeuillee);
    sscanf(argv[2], "%s", cNomImgDilatee);
    sscanf(argv[3], "%s", cNomImgContours);

    int nH, nW, nTaille;

    OCTET *ImgSeuillee, *ImgDilatee, *ImgContours;

    lire_nb_lignes_colonnes_image_pgm(cNomImgSeuillee, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgSeuillee, OCTET, nTaille);
    allocation_tableau(ImgDilatee, OCTET, nTaille);
    allocation_tableau(ImgContours, OCTET, nTaille);

    lire_image_pgm(cNomImgSeuillee, ImgSeuillee, nTaille);
    lire_image_pgm(cNomImgDilatee, ImgDilatee, nTaille);

    for (int i = 0; i < nTaille; ++i) {
        if (ImgSeuillee[i] == 255 && ImgDilatee[i] == 255) {
            // Les deux pixels appartiennent à l'objet, donc c'est le fond
            ImgContours[i] = 255;
        } else {
            // Sinon, c'est un contour
            ImgContours[i] = 0;
        }
    }

    ecrire_image_pgm(cNomImgContours, ImgContours, nH, nW);

    free(ImgSeuillee);
    free(ImgDilatee);
    free(ImgContours);

    return 0;
}
