#include <stdio.h>
#include <stdlib.h>
#include "bitmap.h"


/*
 * Greyscale filter function which changes each pixel's color to 
 * grey.
 */
void greyscale_filter(Bitmap *bmp) {
    // TODO: Complete this function
    Pixel pix;
    for (int i=0; i < bmp->width*bmp->height; i++) {
        fread(&pix.blue, sizeof(unsigned char), 1, stdin);
        fread(&pix.green, sizeof(unsigned char), 1, stdin);
        fread(&pix.red, sizeof(unsigned char), 1, stdin);
        unsigned char grey = (pix.blue + pix.green + pix.red) / 3;
        pix.blue = grey;
        pix.green = grey;
        pix.red = grey;
        fwrite(&pix, sizeof(Pixel), 1, stdout);
    } 
}

int main() {
    // Run the filter program with greyscale_filter to process the pixels.
    // You shouldn't need to change this implementation.
    run_filter(greyscale_filter, 1);
    return 0;
}
