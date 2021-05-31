#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define N 2646000

void stego(int length, char buffer[], char str[]);
void to_bin(int n, int a, char str[]);
void to_bin_2(int a);
//void new_buf();
//void lsb(int a);

int main()
{

	printf("\n****************************");
	printf("\nYou have entered audio Stego");
	printf("\n****************************");
	
	char name_of_file[50];
	printf("\nWhat is the name of your audio file: ");
	scanf("%s", name_of_file);
	
	char tgt[50];
	printf("\nWhat is the name of your output file: ");
	scanf("%s", tgt);

	FILE *ptr;
	ptr = fopen(tgt, "r");
	
	char str[10000], temp;
	int i, j=0;
	int length;
	
	//reversing the bit string from the tgt file
	
	if (ptr==NULL)
	{
		perror("Error opening file");
		return(-1);
	}
	if (fgets (str, 1000, ptr) != NULL)
	{
		puts(str);
		
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
	
	
	char buffer[100];
	sprintf(buffer, "ffmpeg -i %s -f s16le -ac -1 -", name_of_file);

	stego(length, buffer, str);
	
}

void stego(int length, char buffer[], char str[])
{
	int16_t buf[N] = {0};
	int n, c, k;
	int i=1;
	int o=0;
	//char t;
	
	int turner;
	FILE *pipein;
	//FILE *csvfile; 
	
	pipein = popen (buffer ,"r");
	fread(buf, 2, N, pipein);
	pclose(pipein);
	
	for (n=0 ; n<length ; ++n)
	{
		to_bin(n, buf[n], str);
		//lsb(buf[n]);
	}
	
	for (n=(length+1) ; n<N ; ++n)
	{	//("%d" , buf[n]);
		//printf("\n%d\n", buf[n]);
		to_bin_2(buf[n]);
		//lsb(buf[n]);
	}	
	
	 //new_buf();

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
		  
}


void to_bin_2(int a)
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
		for (c = 15; c >= 0; c--)
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
		  fprintf(fptr, "\n");
		  //printf("Closing file!!");
		  fclose(fptr);
		  
		  }
		  
}

void new_buf()
{
	FILE *pfile;
	FILE *ptr;
	char line[17]; //each line is a known size
	char **buffer;
	char *eptr;
	int16_t array[N] ={0};
	int i = 0, num = 0;
		
	//open file
	pfile = fopen("myfile.txt", "r");
	
	//find number of lines in file to know how much memory to allocate
	while(fgets(line, sizeof(line), pfile))
		num++;
	
	//back to start
	rewind(pfile);
	
	//allocate memory for buffer
	buffer = (char**)malloc(num*sizeof(char *));
	
	//allocate memory for each line
	for(int m = 0;m<num;m++)
		buffer[m] = (char*)malloc(sizeof(line)*sizeof(char));
	
	//read line, one by one
	while(fgets(line, sizeof(line), pfile))
	{
		//clean-up data...etc...etc..
		
		//copy new data to buffer; increment buffer
		strcpy(buffer[i], line);

		i++;
	}
	
	//ptr = fopen("new_samples.csv", "a");
	//generic output
	int x;
	short a;
	for(x = 0; x<i; x+=2)
	{
		//printf("%s", buffer[x]);
		array[x] = (int)strtol(buffer[x], &eptr, 2);
		//fprintf(ptr, "%d\n", a);
		
	}
//	for (x=0; x<i; x+=2)
//	{
//		printf("\n%d", array[x]);
//	}
	
	 // Create audio buffe
    	 int n;                // buffer index
   	 double Fs = 44100.0;  // sampling frequency
     
    // Pipe the audio data to ffmpeg, which writes it to a wav file
        FILE *pipeout;
        pipeout = popen("ffmpeg -y -f s16le -ar 44100 -ac 1 -i - output.wav", "w");
        fwrite(array, 2, i, pipeout);
        pclose(pipeout);
	
	
	//cleanup
	free(buffer);
	fclose(pfile);
	fclose(ptr);
}
