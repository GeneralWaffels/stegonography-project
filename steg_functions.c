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
#include "file_handler.h"

//uses least sig bits to store each bit of a file
imageArray* leastSigBitEncodeData(imageArray* container, char* fileName) { //takes an imageArray to hide the file in and the name of the file to hide
    FILE* file = fopen(fileName, "rb");
    
    //get size of file to hide
    fseek(file, 0L, SEEK_END);
    unsigned int size = ftell(file);
    printf("size: %d\n", size);
    fseek(file, 0L, SEEK_SET);

    //check file will fit in container
    if (!(container->width*container->height*(container->colourDepth/3) >= size)) {
        puts("File to hide must be <= 1/8th the size of the container");
        return NULL;
    }

    uint8_t currentByte;
    int currentBit;
    uint8_t bitmask;

    for (int byte = 0; byte < size; ++byte) {
        bitmask = 0x80; //reset bitmask after each byte
        fread(&currentByte, 1, 1, file); //read byte of file
        printf("current byte: %02x\n", currentByte);
        for(int bit = 0; bit < 8; ++bit) { //for each bit of byte
            currentBit = currentByte & bitmask; //use bitmask to get value of just one bit
            //change byte in pixel array based on result
            printf("current bit: %02x\n", currentBit);
            printf("bitmask: %02x\n", bitmask);
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

    return container;
}

//reads each least sig bit and places them together to make a file
void leastSigBitDecodeData(imageArray* container, char* fileName) { //takes imageArray containing hidden data and file name to output data to
    FILE* file = fopen(fileName, "wb");

    uint8_t currentByte;
    int currentBit;
    uint8_t newByte = 0x0;
    int numBitsWritten = 0;

    for (int byte = 0; byte < (container->width*container->height*(container->colourDepth/3))/8; ++byte) {
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
}

int main() {
    //test file handler by converting from bmp to array and back again
    arrayToBmp(
        "../testData/fileHandlerTestOutput.bmp",
        bmpToArray("../testData/test.bmp")
    );

    //test steg functions by encoding data then decoding
    imageArray* img = leastSigBitEncodeData(bmpToArray("../testData/test.bmp"), "../testData/test.txt");
    arrayToBmp("../testData/dataEncodeTestOutput.bmp", img);
    leastSigBitDecodeData(bmpToArray("../testData/dataEncodeTestOutput.bmp"), "../testData/dataEncodeTestOutput.txt");
    return 0;
}