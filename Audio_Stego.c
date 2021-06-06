#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//Declare all the functions used 
void stego(char tgt[]); 
 
int main()
{
    //Declare all the variables
    char tgt[50];
    
//Quick explaination of the program and what is acceptable
printf("\n-----Welcome to Audio Stegnography-----");
printf("\nFew things to remember: ");
printf("\n1. Your audio file must be in the same location as this code and the your binary output file");
printf("\n2. The format of the audio file must be WAV");
printf("\n3. Be aware that the file may become faster or slower if the frequency of the audio file is not 441.kHz");
    
    //Ask for the name of binary output message [Nathan's output]
    printf("\nName of BINARY output file: ");
    scanf("%s", tgt);
    
    //going into audio stego function
    stego(tgt);
}
 
void stego(char tgt[])
{
    //Overview
//Lauches two instances of FFMPEG, one to read the values and one to submit.
//In the interim is where the LSB encryption happens
   
    //Declare all the variables
    int16_t sample; //Storing each sample values
    int count; //Counting sample value
    int n=0; //Dummy variable used as incrementing after every turn of the while loop
    int len; //Stores the length of the binary string
    char str[10000]; //Stores the actual binary string
    int c, k; //Dummy variables used in converting to binary
    char line[17]; //Length of each line in the file: file.txt, it is a known size
    char *eptr; //Temporary pointer
    char command[100]; //Buffer stroing FFMPEG command used later
    char audio_name[50]; //Stores the audio file name
    int i=1; //Variables used to print binary numbers in the file:file.txt
    int o=0;
    
    //Declare all the files
    FILE *pipein; //Reading values from the audio file, one at a time
    FILE *pipeout; //Putting new sample values through one at a time
    FILE *tgtfile; //Binary string file [coming from Nathan's code]
    FILE *fptr; //Storing sample values at a time in file.txt
    
    //Asking for the name of the audio file
    printf("\nWhat is the name of your AUDIO file: ");
    scanf("%s", audio_name);
    
    
    //storing the name of the audio file and the command in a buffer
    sprintf (command, "ffmpeg -i %s -f s16le -ac -1 -", audio_name);
    
    //Read the binary output file and the workout the length of the string
    tgtfile = fopen(tgt, "r"); 
    
    if (tgtfile == NULL)
    {
        printf("\nError opening the output file\n");
        exit(1);
    }
    
    else
    {
            fgets(str, 10000, tgtfile);
            puts(str);
            
            //workout the length of the string
            len = strlen(str);
            
            //checker
            //printf("\nLength of the binary string is: %d", len);
    }
    
    fclose(tgtfile);
    
    
    //Open both pipes
    pipein  = popen(command, "r"); //this pipe is the taking the original audio file
    pipeout = popen("ffmpeg -y -f s16le -ar 44100 -ac 1 -i - out.wav", "w");  //this outputs the stego audio
     
    //This while loop reads, modifies and writes one sample at a time
    
    while(1)
    {
        
        count = fread(&sample, 2, 1, pipein); // read one 2-byte sample
        
        
        if (count != 1) 
            break;
        else if (n<(len-1))
        {
         //lsb encryption code   
            
            // chose the option 'w' because I just want to read the first line everytime
            fptr = fopen("file.txt", "w");
            
            //convert sample to binary
            for (c = 15; c > 0; c--)
                
            {
                    k = sample >> c;
                    
                    //does k=1
                    if (k&1)
                    {
                     fprintf(fptr, "%d", i);   
                    }
                    //does k=0
                    else
                    {
                     fprintf(fptr, "%d", o);   
                    }
                    
                    //print each bit from binary string to file
                    
            }
            
            //replace the 16th bit with the binary string 
            fprintf(fptr, "%c\n", str[n]);
            // read line and place into buffer to be be converted to int16_t
            fscanf(fptr, "%[^\n]", line);
            
            //convert line to int and pass it as a sample
            sample = strtol(line, &eptr, 2);
            
            fclose(fptr);
        }
        
        //increment the buffer
        ++n;
        
        //passing each sample separately and making it into a wav file
        fwrite(&sample, 2, 1, pipeout);
    }
    
     
    // Close input and output pipes
    pclose(pipein);    
    pclose(pipeout);
    
}
