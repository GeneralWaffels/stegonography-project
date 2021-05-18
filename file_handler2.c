/*
Functions for converting different file formats to and from a single structure, using stb libraries

TODO:
Keep track of metadata / original header so this can't be used to indentify steg techniques
Set fileType field of imageArray correctly
Create function that outputs to filetype specified in imageArray
*/

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "file_handler2.h"

imageArray* loadImg(char* name) {
    int width, height, numColours;
    uint8_t *data = stbi_load(name, &width, &height, &numColours, 0);

    //allocate memory for new imageArray and set values
    imageArray* image = malloc(sizeof(imageArray));
    image->fileType = 0;
    image->width = width;
    image->height = height;
    image->numColours = numColours;
    image->pixels = data;//malloc(width*height*nrChannels);

    return image;
}

//convert imageArray to bmp file
void outputBmp(char* name, imageArray* image) { //takes name for the file that will be created and the imageArray to be converted
    stbi_write_bmp(name, image->width, image->height, image->numColours, image->pixels);
    stbi_image_free(image->pixels);
}
//convert to png
void outputPng(char* name, imageArray* image) {
    stbi_write_png(name, image->width, image->height, image->numColours, image->pixels, image->width * image->numColours);
    stbi_image_free(image->pixels);
}
//convert to jpg
void outputJpg(char* name, imageArray* image) {
    stbi_write_jpg(name, image->width, image->height, image->numColours, image->pixels, image->width * image->numColours);
    stbi_image_free(image->pixels);
}