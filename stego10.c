#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//#define N 2646000

void stego(int length, char buffer[], char str[], int N);
void to_bin(int n, int a, char str[]);
void to_bin_two(int a);
void new_buf();
//void lsb(int a);

int main()
{

	printf("\n****************************");
	printf("\nYou have entered audio Stego");
	printf("\n****************************");
	
	char name_of_file[50];
	printf("\nWhat is the name of your audio file: ");
	scanf("%s", name_of_file);
	
	
	//name of output file from nathan's code
	char tgt[50];
	printf("\nWhat is the name of your output file: ");
	scanf("%s", tgt);
	
	int N;
	printf("How long is your audio in seconds: ");
	scanf("%d", &N);
	
	//44100Hz is the frequency of sample collections
	N = N*44100;

	FILE *ptr;
	ptr = fopen(tgt, "r");
	
	char str[10000], temp;
	int i, j=0;
	int length;
	
	//reversing the bit string from the nathan's file
	
	if (ptr==NULL)
	{
		perror("Error opening file");
		return(-1);
	}
	if (fgets (str, 1000, ptr) != NULL)
	{
		puts(str);
		//calculating the length of the string
		length = strlen(str);
		i =0;
		j = length -1; 
		
	
		while (i<j)
		{
			temp =str[i];
			str[i]=str[j];
			str[j]=temp;
			i++;
			j--;
		}
		//printf("%s", str);
	}
	fclose(ptr);
	
	printf("%d", length);
	
	
	//storing the ffmpeg command in buffer to allow it take name of file instead of recompiling it.
	char array[100];
	sprintf(array, "ffmpeg -i %s -f s16le -ac -1 -", name_of_file);

	stego(length, array, str, N);
	
}

void stego(int length, char buffer[], char str[], int N)
{
	//16 bit signed integers
	int16_t buf[N];
	int n;

	// opening a pipe which will take the sample values and save them to a buffer
	FILE *pipein;
	
	
	pipein = popen (buffer ,"r");
	// buf is the buffer, reading 2 bytes at a time of N samples 
	fread(buf, 2, N, pipein);
	pclose(pipein);


	for (n=0 ; n<length ; ++n)
	{	//("%d" , buf[n]);
		//printf("\n%d\n", buf[n]);
		to_bin(n, buf[n], str);
		
		//lsb(buf[n]);
	}
	
	printf("the length is: %d", length);
	
	int p = length+1; 

	for (n=p; n<N ; ++n)
	{
		to_bin_two(buf[n]);
		//lsb(buf[n]);
	}
	
	free(buf);
	new_buf();
}
void to_bin(int n, int a, char str[])
{
	FILE *fptr;
	
	
	int c, k;
	int i=1, o=0;
	
	if ((fptr = fopen("myfile.txt", "a")) == NULL)
	{/* File open failed. */
		printf("Can’t open myfile\n"); 
		exit(1);
	}
	
	else
	{
		//only printing 15bit and replacing the LSB with file
		for (c = 15; c > 0; c--)
		  {
		    k = a >> c;

		    if (k & 1)
		    {
		    	
		    	//printf("1");
		      	fprintf(fptr, "%d", i);
		    }
		    else
		    {
		    	//printf("0");
		      	fprintf(fptr, "%d", o);
		    }	
		 
		 //printf("In file!!");
		  }
		  //printf("\n");
		  fprintf(fptr, "%c", str[n]);
		  fprintf(fptr, "\n");
		  //printf("Closing file!!");
		  fclose(fptr);
		  
		  }
		  
		  return;
		  
}
void to_bin_two(int a)
{
	FILE *bin;
	
	
	int c, k;
	int i=1, o=0;
	
	if ((bin = fopen("myfile.txt", "a")) == NULL)
	{// File open failed. 
		printf("Can’t open myfile\n"); 
		exit(1);
	}
	
	else
	{
		for (c = 15; c >= 0; c--)
		  {
		    k = a >> c;

		    if (k & 1)
		    {
		    	//printf("1");
		      	fprintf(bin, "%d", i);
		    }
		    else
		    {
		    	//printf("0");
		      	fprintf(bin, "%d", o);
		    }	
		 
		 //printf("In file!!");	
		  }
		  //printf("\n");
		  fprintf(bin, "\n");
		  //printf("Closing file!!");
		  
		  
		  }
		  fclose(bin);
		  return;
		  
}


void new_buf()
{
	FILE *pfile;
	//FILE *ptr;
	char line[17]; //each line is a known size
	char **space;
	char *eptr;
	//int16_t array[N];
	int i = 0, num = 0;
		
	//open file
	pfile = fopen("myfile.txt", "r");
	
	//find number of lines in file to know how much memory to allocate
	while(fgets(line, sizeof(line), pfile))
		num++;
	
	//back to start
	rewind(pfile);
	
	//allocate memory for buffer
	space = (char**)malloc(num*sizeof(char *));
	int *arr = malloc(sizeof (line)*sizeof(char));
	
	//allocate memory for each line
	for(int m = 0;m<num;m++)
		space[m] = (char*)malloc(sizeof(line)*sizeof(char));
	
	//read line, one by one
	while(fgets(line, sizeof(line), pfile))
	{
		//clean-up data...etc...etc..
		
		//copy new data to buffer; increment buffer
		strcpy(space[i], line);

		i++;
		
		
	}
	printf("%d", i);
	
	//ptr = fopen("new_samples.csv", "a");
	//generic output
	int x;
	//short a;


	for(x = 0; x<i; x+=2)
	{
		//printf("%s", space[x]);
		arr[x] = strtol(space[x], &eptr, 2);
		//printf("%d", a);
		//fprintf(ptr, "%d\n", a);
		
	}
	
	/*
	for (x=0; x<i; x+=2)
	{
		printf("\n%d", arr[x]);
	}
	
	*/
	 // Create audio buffe
    	 int n=i/2;                // buffer index
   	 //double Fs = 44100.0;  // sampling frequency
     
    // Pipe the audio data to ffmpeg, which writes it to a wav file
        FILE *pipeout;
        pipeout = popen("ffmpeg -y -f s16le -ar 44100 -ac 1 -i - output.wav", "w");
        fwrite(arr, 2, n, pipeout);
        pclose(pipeout);
	

	//cleanup
	free(space);
	//free(arr);
	fclose(pfile);
	//fclose(ptr);

}

