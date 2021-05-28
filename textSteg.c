//increase the 'noise' around real characters
//spaces already present remain - will be in the same place
//encrypt text for extra security 
//look into something similar to spam mimic (sentances, morse, words...)
//need better capacity - allow for longer strings of text as input and can create more noise in output
//file can be empty - add error message
//create decrypter
//better comments


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>

int main()
{
	
	int random;//variable that gets set to a random number in order to pick a character from a random position in characters[]
	srand(time(NULL));//seed rand() with time so rand() is random/different for each run of the program
	
	
	int i = 0;//variable for for loop
	int j = 0;//variable for for loop
	
	FILE *fileInp;//declare file pointer
	char textInp[255];//create character variable of 100 bytes to write the contents of the file to
	fileInp = fopen("text","r");//open file called text to read from
   	if(fileInp == NULL) {//checks if the file exists
      		perror("Error opening file");//if file doesn't exist then print error message
      		return(-1);//program exit due to error
   	}
   	fgets(textInp,255,(FILE*)fileInp);
	fclose(fileInp);//close file

	printf("%s\n",textInp);
	
	for(i = 0; textInp[i] != '\0'; ++i){
		while (!( (textInp[i] >= 'a' && textInp[i] <= 'z') || (textInp[i] >= 'A' && textInp[i] <= 'Z') || (textInp[i] >= '0' && textInp[i] <= '9') || textInp[i] == '\0') ){
			for(j = i; textInp[j] != '\0'; ++j){
				textInp[j] = textInp[j+1];
			}
			textInp[j] = '\0'; 
		}
	}

	
	for(i=0;i<strlen(textInp);i++){
		if (textInp[i] >= 'A' && textInp[i] <= 'Z'){
			textInp[i] = tolower(textInp[i]);
		}
	}

	
	puts(textInp);
	return(0);
}
