//encrypt text for extra security 
//file can be empty - add error message
//create decrypter
//better comments

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>

int encodeText()
{
	
	
	int i = 0;
	int j = 0;
	
	FILE *fileInp;//declare file pointer
	char textInp[500];//create character variable of 500 bytes to write the contents of the file to
	char filename[50];
	printf("Enter the name of the file you want to read from\n");
	scanf("%s",filename);
	fileInp = fopen(filename,"r");//open file to read from
   	if(fileInp == NULL) {//checks if the file exists
      		perror("Error opening file");//if file doesn't exist then print error message
      		return(-1);//program exit due to error
   	}
   	fgets(textInp,500,(FILE*)fileInp);//copy contents of file to textInp variable
	fclose(fileInp);


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
	
	printf("You're encoded message is:\n%s. the jay, pig, fox, zebra and my %s wolves quack\n",container, positions);
	
	char filename2[100];
	FILE *fileOut;//declare file pointer
	printf("Enter a name for the file where your encoded message will be saved\n");
	while((getchar())!='\n');//clear input buffer by reading values in it until reaching '\n' character so the program doesn't take the extra characters when looking for file name
	fgets(filename2,100,stdin);
	int valid=0;
	while(valid==0){
		for (i=0;i<strlen(filename2);i++){
			if ((filename2[i] == '/')){
				printf("Invalid filename, cannot use '/'\n"); 
				printf("Enter a name for the file where your encoded message will be saved\n");
				while((getchar())!='\n');//clear input buffer by reading values in it until reaching '\n' character so the program doesn't take the extra characters when looking for file name
				fgets(filename2,100,stdin);
			}
			else{
				valid=1;
			}
		}
	}
	
	fileOut = fopen(filename2,"w");//open file to write to
	//write output to file
   	fputs(container, fileOut);
   	fputs(". the jay, pig, fox, zebra and my ",fileOut);
   	fputs(positions, fileOut);
   	fputs(positions,fileOut);
   	fputs(" wolves quack\n",fileOut);
	fclose(fileOut);
	
	return(0);
}

int decodeText()
{

	FILE *fileInp;//declare file pointer
	char encoded[1093];//create character variable of 10393 (max size of final message) bytes to write the contents of the file to
	char filename[50];
	printf("Enter the name of the file you want to read from\n");
	scanf("%s",filename);
	fileInp = fopen(filename,"r");//open file to read from
   	if(fileInp == NULL) {//checks if the file exists
      		perror("Error opening file");//if file doesn't exist then print error message
      		return(-1);//program exit due to error
   	}
   	fgets(encoded,1093,(FILE*)fileInp);//copy contents of file to textInp variable
	fclose(fileInp);
	
	char container[] = "how vexingly quick 9761240835 daft zebras jump";
	char positions[1000]="";//variable to store the long string of digits from the encoded message
	char message[500] = "";//variable that will hold the decoded message

	int i=80;//position of the first digit in the position strings (find better way of doing this as poor maintainability)
	
	char digit[]="p";
	while(encoded[i]!=' '){//iterate through encoded until the end of the string of digits (' ')
		digit[0]=encoded[i];//get value of encoded[i] that can be used with strcat()
		strcat(positions,digit);//append the character to positions
		//puts(positions);//for testing
		i++;//increment to go to next character in encoded
	}
	
	//for loop atoi on each pair of digits and compare with container

	int num;//integer to store the value retreived from 'positions'
	char toJoin[]="tj";//place holder string to enable use of atoi on numbers in a string that can be 1 or 2 digits long
	char character[]="c";//placeholder char to enable strcat()
	for(i=0;i<strlen(positions);i=i+2){//iterate through the pairs of digits in 'positions'
		toJoin[0]=positions[i];
		toJoin[1]=positions[i+1];
		num = atoi(toJoin);//convert number in string to integer
		character[0]=container[num];
		strcat(message,character);//append current character to message string
	}
	
	printf("You're decoded message is:\n%s\n",message);
	
	char filename2[100];
	FILE *fileOut;//declare file pointer
	printf("Enter a name for the file where your decoded message will be saved\n");
	while((getchar())!='\n');//clear input buffer by reading values in it until reaching '\n' character so the program doesn't take the extra characters when looking for file name
	fgets(filename2,100,stdin);
	int valid=0;
	while(valid==0){
		for (i=0;i<strlen(filename2);i++){
			if ((filename2[i] == '/')){
				printf("Invalid filename, cannot use '/'\n"); 
				printf("Enter a name for the file where your decoded message will be saved\n");
				while((getchar())!='\n');//clear input buffer by reading values in it until reaching '\n' character so the program doesn't take the extra characters when looking for file name
				fgets(filename2,100,stdin);
			}
			else{
				valid=1;
			}
		}
	}
	
	fileOut = fopen(filename2,"w");//open file to write to
	//write output to file
	fputs(message, fileOut);
	fclose(fileOut);

	return(0);	
}

int main()
{

	printf("Do you want to (E)ncode or (D)ecode?\n");//ask user for input of E or D
	int c;//char to store input result
	//while loop to ensure that the only input is E or D; all other input ignored
	while((c!='E')&&(c!= 'D')){
		c= getchar();
	}
	if(c =='E'){
		while((getchar())!='\n');//clear input buffer by reading values in it until reaching '\n' character so the program doesn't take the extra characters when looking for file name
		encodeText();
	}
	else if(c =='D'){
		while((getchar())!='\n');//clear input buffer by reading values in it until reaching '\n' character so the program doesn't take the extra characters when looking for file name
		decodeText();
	}
	else{
		printf("Error\n");
		return(-1);
	}
	
	return(0);
}
