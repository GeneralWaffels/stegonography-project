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
	
	
	int random;
	srand(time(NULL));//seed rand() with time so actually random
	
	
	int i = 0;
	int j = 0;
	
	FILE *fileInp;
	char textInp[100];
	fileInp = fopen("text","r");
   	if(fileInp == NULL) {
      		perror("Error opening file");
      		return(-1);
   	}
   	if( fgets (textInp, 100, fileInp)!=NULL ) {
   	}
	fclose(fileInp);	
	
	
	char final[(sizeof(textInp)*2)];

	
	for(i=0;i<strlen(textInp)-1;i++){
		random = (rand()%(sizeof(characters)));
		final[j] = characters[random];
		final[j+1] = textInp[i];
		j=j+2;
	}
	printf("%s\n",final);
	
	
	return(0);
}
