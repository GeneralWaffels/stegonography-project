// Encrpyt.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uchar.h>
#define MAX 256
FILE* fp;
FILE* fp2;
char line[MAX];
char tgt[MAX];
char file[256], * end;
int hex_to_binary(char*);

int main() {

    printf("Enter the name of the file: ");
    fgets(file, 256, stdin);

    printf("Enter your output file name:");
    scanf("%s", tgt);

    if ((end = strchr(file, '\n')) != NULL)
        *end = '\0';
    FILE* fp = fopen(file, "r");
    //fprintf(fp, "test123");   testing to see if file is opened
 
    fp2 = fopen(tgt, "wt");
   
    int c;
   
        fp = fopen(file,"rb");
        if (fp)
        {
            do
            {
                c = fgetc(fp);
                if (EOF != c)
                    fprintf(fp2,"%02X ",c);             
            } while (EOF != c);
            
        }
    fclose(fp);
    fclose(fp2);

    fp = fopen(tgt, "r");
   

    while (!feof(fp)) {
        fgets(line, MAX, fp);
        hex_to_binary(line);

    }
  
    return 0;
}
int hex_to_binary(char* hex_string)
{


    int i = 0;
    fp2 = fopen(tgt, "wt");
    while (hex_string[i])
    {

        switch (hex_string[i])
        {
        case '0':
                 {
                     if (i % 2 == 0)
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
            printf("%c", hex_string[i]);    
            i++;
        }
        return 0;
    }
  
    
   
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

   