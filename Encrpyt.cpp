// Encrpyt.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


// Instructions - Input file must be in the same folder as program, and the output file will be saved to the same location. File must have format of .txt
#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>                                             // supports memory managment
#include <string.h>                                             // support string manipulation
#include <uchar.h>                                              // supports encrpytion
#define MAX 256
FILE* fp;                                                       // point to input file
FILE* fp2;                                                      // point to output file
char line[MAX];                                                 // define array with maximun space
char tgt[MAX];                                                  // define array with maximun space
char file[256], * end;                                          // array to read file letter by letter and point to the end
int hex_to_binary(char*);                                        

int main() {

    printf("Enter the name of the .txt file: ");                         // enter name of file to be opened and read
    fgets(file, 256, stdin);                                        // *file must be in same folder as program folder (visual studio)

    printf("Enter your output file name:");                         // enter name of file to be created with encrypted text
    scanf("%s", tgt);                                               // file will be saved in the same folder where the intiial text file must be

    if ((end = strchr(file, '\n')) != NULL)                         // points to the first character in the file. The end of the file is null 
        *end = '\0';
    FILE* fp = fopen(file, "r");                                    // points to the input file and opens it for reading
    //fprintf(fp, "test123");   testing to see if file is opened
 
    fp2 = fopen(tgt, "wt");                                         // open second file (output file) for writing
   
    int c;
   
        fp = fopen(file,"rb");                                      // opening file to read binary 
        if (fp)
        {
            do
            {
                c = fgetc(fp);                                      // c is equal to the the next character in the first file
                if (EOF != c)                                       //  if it is not the end of the file print the current c
                    fprintf(fp2,"%02X ",c);                         // print in hex first to target file 
            } while (EOF != c);                                     // loop whilst it is not the end  of the file
            
        }
    fclose(fp);                                                     // close input file
    fclose(fp2);                                                    // close output file

    fp = fopen(tgt, "r");                                           // open input file with tgt array 
   

    while (!feof(fp)) {                                             // while it is not the end of the file
        fgets(line, MAX, fp);                                       // read all lines of the text file and save to array
        hex_to_binary(line);                                        //  send line array to hex to binary function                                    

    }
  
    return 0;
}
int hex_to_binary(char* hex_string)
{


    int i = 0;                                                       // character counter to ensure 8 bit encryption 
    fp2 = fopen(tgt, "wt");                                          // open target file for writing 
    while (hex_string[i])                                            // counts the string in hex in relation to i
    {

        switch (hex_string[i])                                     
        {
        case '0':                                                    // if character is 0
                 {
                     if (i % 2 == 0)                                 // checking the character count to ensure 8 bit encription so the last bit in the 8bit word is changed
                                 fprintf(fp2, "0001");
                     else
                                 fprintf(fp2, "0000");
                 }
         break;

        case '1':                                                    
                {
                if (i % 2 == 0)                                       
                    fprintf(fp2, "0000");
                else
                    fprintf(fp2, "0001");
                }
                 break;

            case '2': 
            {
                if (i % 2 == 0)
                    fprintf(fp2, "0011");
                else
                    fprintf(fp2, "0010");
            }
                break;

            case '3':
            {
                if (i % 2 == 0)
                    fprintf(fp2, "0010");
                else
                    fprintf(fp2, "0011");
            }
                break;
            case '4':
            {
                if (i % 2 == 0)
                    fprintf(fp2, "0101");
                else
                    fprintf(fp2, "0100");
            }
                break;
            case '5':
            {
                if (i % 2 == 0)
                    fprintf(fp2, "0100");
                else
                    fprintf(fp2, "0100");
            }
                break;
            case '6': 
            {
                if (i % 2 == 0)
                    fprintf(fp2, "0111");
                else
                    fprintf(fp2, "0110");
            }
                break;
            case '7': 
            {
                if (i % 2 == 0)
                    fprintf(fp2, "0110");
                else
                    fprintf(fp2, "0111");
            }
                break;
            case '8':
            {
                if (i % 2 == 0)
                    fprintf(fp2, "1001");
                else
                    fprintf(fp2, "1000");
            }
                break;
            case '9': 
            {
                if (i % 2 == 0)
                    fprintf(fp2, "1000");
                else
                    fprintf(fp2, "1001");
            }
                break;
            case 'A':
            {
                if (i % 2 == 0)
                    fprintf(fp2, "1011");
                else
                    fprintf(fp2, "1010");
            }
                 break;
            case 'B':
            {
                if (i % 2 == 0)
                    fprintf(fp2, "1010");
                else
                    fprintf(fp2, "1011");
            }
                break;
            case 'C': 
            {
                if (i % 2 == 0)
                    fprintf(fp2, "1101");
                else
                    fprintf(fp2, "1100");
            }
                 break;
            case 'D':
            {
                if (i % 2 == 0)
                    fprintf(fp2, "1100");
                else
                    fprintf(fp2, "1101");
            }
                 break;
            case 'E': 
            {
                if (i % 2 == 0)
                    fprintf(fp2, "1111");
                else
                    fprintf(fp2, "1110");
            }
                break;
            case 'F':
            {
                if (i % 2 == 0)
                    fprintf(fp2, "1110");
                else
                fprintf(fp2, "1111");
            }
                break;
            case 'a': 
            {
                if (i % 2 == 0)
                    fprintf(fp2, "1011");
                else
                fprintf(fp2, "1010");
            }
                break;
            case 'b':
            {
                if (i % 2 == 0)
                    fprintf(fp2, "1010");
                else
                    fprintf(fp2, "1011");
            }
            break;
            case 'c':
            {
                if (i % 2 == 0)
                    fprintf(fp2, "1101");
                else
                    fprintf(fp2, "1100");
            }
            break;
            case 'd':
            {
                if (i % 2 == 0)
                    fprintf(fp2, "1100");
                else
                    fprintf(fp2, "1101");
            }
                    break;
            case 'e': 
            {
                if (i % 2 == 0)
                    fprintf(fp2, "1111");
                else
                    fprintf(fp2, "1110");
            }
                    break;
            case 'f': 
            {
                if (i % 2 == 0)
                    fprintf(fp2, "1110");
                else
                    fprintf(fp2, "1111");
            }
            break;
    }
            printf("%c", hex_string[i]);                                // print the binary character 
            i++;                                                        // increase i by 1
        }
        return 0;
    }
