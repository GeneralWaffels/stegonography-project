//encrypt text for extra security 
//file can be empty - add error message
//create decrypter
//better comments

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>

int encodeText()
{
	
	int random;//variable that gets set to a random number in order to pick a character from a random position in characters[]
	srand(time(NULL));//seed rand() with time so rand() is random/different for each run of the program
	
	int i = 0;
	int j = 0;
	
	FILE *fileInp;//declare file pointer
	char textInp[500];//create character variable of 100 bytes to write the contents of the file to
	fileInp = fopen("text","r");//open file called text to read from
   	if(fileInp == NULL) {//checks if the file exists
      		perror("Error opening file");//if file doesn't exist then print error message
      		return(-1);//program exit due to error
   	}
   	fgets(textInp,500,(FILE*)fileInp);//copy contents of file to textInp variable
	fclose(fileInp);

	//printf("%s\n",textInp);
	
	for(i = 0; textInp[i] != '\0'; ++i){//iterate through textInp
		while (!( (textInp[i] >= 'a' && textInp[i] <= 'z') || (textInp[i] >= 'A' && textInp[i] <= 'Z') || (textInp[i] >= '0' && textInp[i] <= '9') || textInp[i] == '\0') ){//remove characters that are not alphanumeric
			for(j = i; textInp[j] != '\0'; ++j){
				textInp[j] = textInp[j+1];
			}
			textInp[j] = '\0'; 
		}
	}
	
	//iterate through textInp again and change capital letters to lower case
	for(i=0;i<strlen(textInp);i++){
		if (textInp[i] >= 'A' && textInp[i] <= 'Z'){
			textInp[i] = tolower(textInp[i]);
		}
	}
	
	//puts(textInp);
	
	//how vexingly quick 9761240835 daft zebras jump - pangram
	//the jay, pig, fox, zebra and my [num] wolves quack
	
	char container[] = "how vexingly quick 9761240835 daft zebras jump";//pangram (containers all alphanumeric characters to check against the input text with 
	char positions[1000] = "";//will store the positions of each character from the input text (1000 as textInp = 500)
	char position[]= "00";//will store the position of the current character in the for loop, to be appended to positions[]
	

	for(i=0;i<strlen(textInp);i++){//iterate through each character in textInp[]
		j=0;
		while(container[j] != textInp[i]){//find the corrosponding character in the container
			j++;
		}
		if((j>=0)&&(j<=9)){//add 0 to the front of the single digit characters so each character position is the same length
			sprintf(position, "0%d", j);//convert the integer position to string so it can be appended to positions
		
		} else{
			sprintf(position, "%d", j);
		}		
		strcat(positions, position);
	}
	
	printf("%s. the jay, pig, fox, zebra and my %s wolves quack\n",container, positions);
	return(0);
}

int main()
{
	encodeText();
	return(0);
}
