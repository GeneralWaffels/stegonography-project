/*
Functions relating to steganography.

Current issues: 
-no way to know how long hidden data is, so when encoding there is a lot of junk data at the end
    Possible solutions: 
    -set all values after to 0
    -place length of data in the file somewhere
*/

#include <stdio.h>
#include <stdlib.h>
#include "file_handler2.h"

//uses least sig bits to store each bit of a file
imageArray* leastSigBitEncodeData(imageArray* container, char* fileName) { //takes an imageArray to hide the file in and the name of the file to hide
    FILE* file = fopen(fileName, "rb");
    
    //get size of file to hide
    fseek(file, 0L, SEEK_END);
    unsigned int size = ftell(file);
    #ifdef DEBUG
    printf("Size of file to hide: %d bytes\n", size);
    #endif
    fseek(file, 0L, SEEK_SET);

    //check file will fit in container
    if (!(container->width*container->height*container->numColours) >= size) {
        puts("File to hide must be <= 1/8th the size of the container");
        return NULL;
    }

    puts("Encoding data into image...");

    uint8_t currentByte;
    int currentBit;
    uint8_t bitmask;

    for (int byte = 0; byte < size; ++byte) {
        bitmask = 0x80; //reset bitmask after each byte
        fread(&currentByte, 1, 1, file); //read byte of file
        for(int bit = 0; bit < 8; ++bit) { //for each bit of byte
            currentBit = currentByte & bitmask; //use bitmask to get value of just one bit
            //change byte in pixel array based on result
            if (currentBit == 0x0) {
                container->pixels[byte*8 + bit] &= 0xFE; //and bitmask with 11111110, setting last bit to 0 while retaining other bits
            }
            else {
                container->pixels[byte*8 + bit] |= 0x01; //or bitmask with 00000001, setting last bit to 1 while retaining other bits
            }
            bitmask>>=1; //change bitmask to mask off next bit on next loop
        }
    }

    fclose(file);

    puts("Done");
    return container;
}

//uses least sig bits to store a colour, making up a second image
imageArray* leastSigBitEncodeImage(imageArray* container, imageArray* hiddenImg) { //takes two imageArrays, one to hide and the other to hide that in
    //check hiddenImg is smaller than the container
    if (container->width < hiddenImg->width || container->height < hiddenImg->height) {
        puts("Image to hide must be smaller than the image it is being hidden in");
        return NULL;
    }

    puts("Encoding image into image...");

    for (int row = 0; row < hiddenImg->height; ++row) {
        for (int col = 0; col < hiddenImg->width; ++col) {
            for (int i = 0; i < 3; ++i) { //each byte for R, G and B
                uint8_t hiddenByte = hiddenImg->pixels[(row*hiddenImg->width + col)*hiddenImg->numColours+i]; //get colour byte to hide
                int pixelToChange = (row*container->width + col)*hiddenImg->numColours+i;
                if (hiddenByte < 0x80u) { //convert from one byte to 1 bit
                    hiddenByte = 0xFEu;
                }
                else {
                    hiddenByte = 0xFFu;
                    container->pixels[pixelToChange] |= 0x01u; //set container lsb to 1
                }
                container->pixels[pixelToChange] &= hiddenByte; //set container lsb to 0
            }
        }
    }

    puts("Done");
    return container;
}

//reads each least sig bit and places them together to make a file
void leastSigBitDecodeData(imageArray* container, char* fileName) { //takes imageArray containing hidden data and file name to output data to
    puts("Decoding data from image...");
    FILE* file = fopen(fileName, "wb");

    uint8_t currentByte;
    int currentBit;
    uint8_t newByte = 0x0;
    int numBitsWritten = 0;

    for (int byte = 0; byte < (container->width*container->height*container->numColours)/8; ++byte) {
        currentByte = container->pixels[byte];
        currentBit = currentByte & 0x01; //get just last bit of byte
        newByte |= currentBit<<(7-numBitsWritten); //shift bit left by 7-numBitsWritten so each bit will be in a different place in the new byte
        ++numBitsWritten;
        if (numBitsWritten == 8) { //when 8 bits have been written to the new byte write new byte to file
            fwrite(&newByte, 1, 1, file);

            numBitsWritten = 0;
            newByte = 0x0;
        }
    }

    puts("Done");
}

//reads each least sig bit and interprets them as colour, modifying the imageArray accordingly
imageArray* leastSigBitDecodeImage(imageArray* container) { //takes imageArray containing hidden image
    puts("Decoding image from image...");
    for (int byte = 0; byte < container->height*container->width*container->numColours; ++byte) { //for every byte of pixel data
        uint8_t leastBit = container->pixels[byte] & 0x01u; //get last bit
        if (leastBit == 0x01u) { //convert bit to byte
            leastBit = 0xFFu;
        } 
        else {
            leastBit = 0x00u;
        }
        
        container->pixels[byte] = leastBit; //write this conversion to the imageArray
    }

    puts("Done");
    return container;
}

int main() {
    //tests
    imageArray* img = leastSigBitEncodeData(loadImg("../testData/test.bmp"), "../testData/test.txt");
    outputPng("../testData/dataEncodeTestOutput.png", img);
    leastSigBitDecodeData(loadImg("../testData/dataEncodeTestOutput.png"), "../testData/dataEncodeTestOutput.txt");

    return 0;
}