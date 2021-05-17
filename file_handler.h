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
    unsigned int colourDepth; //number of bits per pixel
    unsigned int numColours; //number of colours per pixel
    unsigned int headerLength; //length of header in bytes
    uint8_t* header; //storing header allows original to be preserved, making it less obvious file has been modified
    uint8_t* pixels;
} imageArray;

imageArray* bmpToArray(char* name);
void arrayToBmp(char* name, imageArray* image);

#endif