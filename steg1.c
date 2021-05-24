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

int main()
{
	char characters[] = {' ',' ',' ','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','0','1','2','3','4','5','6','7','8','9','!','"','$','%','^','&','*',')','(','-','_','+','=','{','}','[',']',';',':','@',',','.','<','>','/','?','~','#'}; // " \ £ '    characters that break this
//characters to be randomly picked from for creating "noise" around the text to hide. Used as many characters as possible such that any character that is present in the text to be hidden can also be present in the "noise" (if a character could only appear in the input then the text may be easier to decode)
	
	
	int random;//variable that gets set to a random number in order to pick a character from a random position in characters[]
	srand(time(NULL));//seed rand() with time so rand() is random/different for each run of the program
	
	
	int i = 0;//variable for for loop
	int j = 0;//variable for for loop
	
	FILE *fileInp;//declare file pointer
	char textInp[100];//create character variable of 100 bytes to write the contents of the file to
	fileInp = fopen("text","r");//open file called text to read from
   	if(fileInp == NULL) {//checks if the file exists
      		perror("Error opening file");//if file doesn't exist then print error message
      		return(-1);//program exit due to error
   	}
	fclose(fileInp);//close file
	
	
	char final[(sizeof(textInp)*2)];//create character variable that is twice the size of the text from the file such that for each character in the text there is space for another character to be placed before it

	
	for(i=0;i<strlen(textInp)-1;i++){//for loop to iterate through each character
		random = (rand()%(sizeof(characters)));//creates random number to choose a random character from characters
		final[j] = characters[random];//makes the character at position j (initially position 0) a random character (from characters)
		final[j+1] = textInp[i];//makes the next character a character from the input text
		j=j+2;//iterates j by 2 as it writes to 2 places each pass
	}
	printf("%s\n",final);//prints the final, encrypted, text (need to improve by writing to file =)
	
	
	return(0);
}
