#ifndef STEG_FUNCTIONS_H
#define STEG_FUNCTIONS_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

//all images can be stored in this structure
typedef struct imageArrayStructure {
    unsigned int fileType;
    /*Marker showing what filetype the image was originally, different number for each type:
    0:bmp
    1:...
    */
    unsigned int width;
    unsigned int height;
    unsigned int numColours; //number of colours per pixel
    uint8_t* pixels;
} imageArray;

imageArray* loadImg(char* name);
void outputBmp(char* name, imageArray* image);
void outputPng(char* name, imageArray* image);
void outputJpg(char* name, imageArray* image);

#endif