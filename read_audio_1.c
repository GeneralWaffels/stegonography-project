//This code reads 20ms from the beginning of the .wav file and then prints all the values into a .csv file
//The wav file format is 16 bitt -signed integer samples, with a sampling frequency of 44.1khz

//to compile this ocde you need to 
// gcc read_audio_1.c -o read_audio_1 -lm
// -lm is used to indiacte that the maths library will be used


#include <stdio.h>
#include <stdint.h>
 
//to avoid buffer overflow N = 44100* seconds [duration of the audio] 
 
#define N 2646000

// Declaring function present in this code 
void sample_values(char buffer[]);

int main()
{

	char ans;
	
	printf("\n**************");
	printf("\n Audio Stego ");
	printf("\n**************");
	
	printf("\nDo you have an audio file y/n : ");
	scanf("%c", &ans);
	
	if ( ans == 'y' || ans == 'Y')
	{
	char name_of_file[50];
  	printf("\nName of audio file: ");
  	scanf("%s", name_of_file);
  	
  	// getting the name of the audio file, but has to be in the same directory as the code

  	char buffer[100];
  	sprintf(buffer, "ffmpeg -i %s -f s16le -ac 1 -", name_of_file);
	//printf("%s", buffer);
	
	sample_values(buffer);
	}
	
	else
	{
	printf("Wrong place");
	}


return 0;

}
void sample_values(char buffer[])
{

    // Create a 20 ms audio buffer (assuming Fs = 44.1 kHz)
    int16_t buf[N] = {0}; // buffer
    // used a fixed length int data type int16_t to make sure that I got 16 bit signed integer samples
    //this type is defined in the stdint.h header file
    
    
    int n;                // buffer index
    
    // Open WAV file with FFmpeg and read raw samples via the pipe.
    FILE *pipein;
       
    pipein = popen(buffer, "r");
    // popen() fucntion lauches a seperate program, which is accessible via the pipe
    // the first argumnet is the command line for the program being launched [ffmepg] 
    // the secons arguemnt 'r' means that we'll be reading data from that program
    // ffmpeg -i starwars.wav -f s16le -ac 1 -"
    // -i ------- read data from the standard input in this case the pipe
    // -f s16le ----- tells ffmepg that the fromat of the audio data it reads is raw PCM( pulse code modulation, is to reprsnet the sampled analog signals digitally ), sigend integer, 16 bit and little endian 
    // -ac 1 -------- the number of channes in the audio data it is reading is one  
    
    fread(buf, 2, N, pipein);
    pclose(pipein);
    //close the pipe

    // Print the sample values in the buffer to a CSV file    
    FILE *csvfile;
    csvfile = fopen("samples.csv", "w");
    for (n=0 ; n<N ; ++n) 
    	fprintf(csvfile, "%d\n", buf[n]);
    fclose(csvfile);
    

 
    
}
