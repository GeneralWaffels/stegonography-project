/*
Functions for converting different file formats to and from a single structure.

Might be a waste of time, a lot of this functionality is already present in existing libraries.
Could migrate to those at some point.
*/

#include "file_handler.h"

//convert bmp image to imageArray type
//returns pointer to imageArray
imageArray* bmpToArray(char* name) { //takes name of file as char array
    FILE* file = fopen(name, "rb");

    //check file is bmp
    uint16_t magicBytes;
    fseek(file, 0, SEEK_SET);
    fread(&magicBytes, 2, 1, file);
    if (magicBytes != 0x4d42) {
        return NULL;
    }

    //read relevant header values
    uint32_t offset; //offset to start of pixel data
    fseek(file, 10, SEEK_SET);
    fread(&offset, 4, 1, file);

    uint32_t width;
    fseek(file, 18, SEEK_SET);
    fread(&width, 4, 1, file);
    
    uint32_t height;
    fseek(file, 22, SEEK_SET);
    fread(&height, 4, 1, file);

    uint16_t colourDepth; //number of bits per pixel
    fseek(file, 28, SEEK_SET);
    fread(&colourDepth, 2, 1, file);

    //print values for debugging
    printf("offset: %08x\n", offset);
    printf("width: %08x\n", width);
    printf("height: %08x\n", height);
    printf("colour depth: %04x\n", colourDepth);

    //allocate memory for new imageArray and set values
    imageArray* image = malloc(sizeof(imageArray));
    image->fileType = 0;
    image->width = width;
    image->height = height;
    image->colourDepth = colourDepth;
    image->pixels = malloc(width*height*(colourDepth/8));
    image->header = malloc(offset);
    image->headerLength = offset;

    fseek(file, 0, SEEK_SET); //go to start of file
    fread(image->header, 1, offset, file); //read header into array

    fseek(file, offset, SEEK_SET); //go to pixel data
    fread(image->pixels, 1, width*height*colourDepth, file); //read pixels into array

    fclose(file);

    return image;
}

//convert imageArray to bmp file
void arrayToBmp(char* name, imageArray* image) { //takes name for the file that will be created and the imageArray to be converted
    FILE* file = fopen(name, "wb");

    fwrite(image->header, 1, image->headerLength, file); //write header
    fwrite(image->pixels, 1, image->width*image->height*(image->colourDepth/8), file); //write pixels

    fclose(file);
}