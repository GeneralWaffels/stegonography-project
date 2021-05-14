#include <stdio.h>
#include <stdint.h>
 
#define N 882
 
int audio_samples ()
{
    // Create a 20 ms audio buffer (assuming Fs = 44.1 kHz)
    int16_t buf[N] = {0}; // buffer
    int n;                // buffer index
     
    // Open WAV file with FFmpeg and read raw samples via the pipe.
 // to allow this part of the code to work you need to [ sudo apt-get install ffmpeg ] 
    FILE *pipein;
    pipein = popen("ffmpeg -i test.wav -f s16le -ac 1 -", "r");
    fread(buf, 2, N, pipein);
    pclose(pipein);
     
    // Print the sample values in the buffer to a CSV file
    FILE *csvfile;
    csvfile = fopen("samples.csv", "w");
    for (n=0 ; n<N ; ++n) fprintf(csvfile, "%d\n", buf[n]);
    fclose(csvfile);
}

