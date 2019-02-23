#include <stdio.h>
#include <stdlib.h>
#include "bitmap.h"
/*
 * Gaussian blur filter function. Which gets 8 pixels surrounding
 * each pixels and use those 9 pixels to get the pixel from the
 * provided function apply_gaussian_kernel.
 */
void gaussian_blur_filter(Bitmap *bmp) {
    // TODO: Complete this function
    Pixel pix_array[bmp->height][bmp->width];
    Pixel pix;
    for (int i=0; i < bmp->height; i++) {
        for (int j=0; j < bmp->width; j++) {
            fread(&pix.blue, sizeof(unsigned char), 1, stdin);
            fread(&pix.green, sizeof(unsigned char), 1, stdin);
            fread(&pix.red, sizeof(unsigned char), 1, stdin);
            pix_array[i][j] = pix; 
        }
    }
    int row, col;
    Pixel three[3][3];
    for (int i=0; i < bmp->height; i++) {
        for (int j=0; j < bmp->width; j++) {
            row = i, col = j;
            if (row - 1 < 0) {
                row ++;
            }else if (row + 1 == bmp->height) {
                row --;
            }
            if (col - 1 < 0) {
                col ++;
            } else if (col + 1 == bmp->width) {
                col --;
            }
            for (int r = 0; r < 3; r++) {
                for (int c = 0; c < 3; c++) {
                    three[r][c] = pix_array[row + r - 1][col + c - 1];
                }
            }
            Pixel result = apply_gaussian_kernel(three[0], three[1], three[2]);
            fwrite(&result, sizeof(Pixel), 1, stdout);
        }
    }
}

int main() {
    // Run the filter program with gaussian_blur_filter to process the pixels.
    // You shouldn't need to change this implementation.
    run_filter(gaussian_blur_filter, 1);
    return 0;
}
