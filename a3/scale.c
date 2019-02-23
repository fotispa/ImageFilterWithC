#include <stdio.h>
#include <stdlib.h>
#include "bitmap.h"
//Global variable saving scale_factor
int scale_factor;
/*
 * Scale filter function scaling images by its scale_factor.
 */
void scale_filter(Bitmap *bmp) {
    // TODO: Complete this function
    Pixel pix_array[bmp->width];
    for (int i=0; i < bmp->height; i++) {
        //read each row of the pixels
        for (int j=0; j < bmp->width; j++) {
            Pixel pix;
            fread(&pix.blue, sizeof(unsigned char), 1, stdin);
            fread(&pix.green, sizeof(unsigned char), 1, stdin);
            fread(&pix.red, sizeof(unsigned char), 1, stdin);
            pix_array[j] = pix;
        }
        //print pixels scale_factor times width and height
        for (int k=0; k < scale_factor; k++) {
            for (int l=0; l < bmp->width; l++) {
                for (int m=0; m < scale_factor; m++) {
                    fwrite(&pix_array[l], sizeof(Pixel), 1, stdout);
                 }
            }
        }
    }
    bmp->height *= scale_factor;
    bmp->width *= scale_factor; 
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: scale scale_factor\n");
        exit(1);
    }
    scale_factor = atoi(argv[1]);
    // Run the filter program with scale_filter to process the pixels.
    // You shouldn't need to change this implementation.
    run_filter(scale_filter, scale_factor);
    return 0;
}
