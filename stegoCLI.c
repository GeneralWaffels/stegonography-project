    //get user input as to what exactly they want to do with this program
    //check if program executables have been created- if not, use system() to gcc *all* the .c files into .out files with the same name (one time(?) run)
    //use exec(), execv() or execve() {?} to execute the programs that want to be used (scrapped, used system() instead.)

#include <stdio.h>
#include <sys/types.h> //These two --
#include <unistd.h>    //--Are for forking and waiting. Maybe remove?
#include <stdlib.h> //For system(), to use gcc to compile all files
#include <string.h> //For strcmp, to check user input against possible cases

//This is what will be run first. All the other programs will be activated from here. 

int main(){

    char input[32];
    printf("\nThis is Group D's Steganography program.\n");
    while(1){ //Loops program, as after system() is called, and the external function has run, it returns to this program.
        printf("Type the appropriate number for what you want to do.\n");
        printf("1: Encrypt/Decrypt a text file, by hiding a message within another text file. \n2: Hide a text file within a .BMP image.\n3: Hide a text file within a .wav audio file.\n\n");
    
        fgets(input, 32, stdin); //get user input from terminal and place it into 'input' variable
        input[strcspn(input, "\n")] = 0;   //remove the newline that fgets takes at the end of user input, if it can fit. Otherwise, does nothing if there is no newline character. https://stackoverflow.com/questions/41252808/string-compare-in-c-with-fgets
        //fork(); //fork() does *not* work on windows machines. 
        
	    /* Check if executable files have already been compiled with gcc */
        if( access( "Audio_Stego.out", F_OK ) == 0 ) {
        //Check if the first executable alphabetically exists. Replace with counting how many .out files there are? Unsure how to check if all unique .out files exist.
	    } 
        else {
        //first executable does not exist, either due to not being run previously or been deleted
        printf("First executable not found, (re)compiling all executables.");
        system("gcc -o Audio_Stego.out Audio_Stego.c"); //Compile files
        system("gcc -o Encrpyt.out Encrpyt.c");
        system("gcc file_handler.c steg_functions.c -o file_handler.out -lm  ");
        //system("gcc -o steg_functions.out steg_functions.c file_handler_header.c");
        system("gcc -o textSteg.out textSteg.c");
        
	    }
		/* Compare user input to known commands. I'd do cases here, but I was already using char[] by the time I realised switch cases only work with integers. */
		if( 0 == strcmp(input, "1") ){ //User wants to encrypt text
			printf("Running textSteg.out \n"); //Interestingly, without the \n, system() would run first.
    		
    		system("./textSteg.out");
		}
		else if( 0 == strcmp(input, "2") ){ //User wants to hide text within BMP image
			printf("Running steg_functions.out\n"); //Currently fails to compile this.
			system("./Encrpyt.out"); 
			system("./steg_functions.out");
		}
		else if( 0 == strcmp(input, "3") ){ //User wants to hide text within Audio file
			printf("Running Encrpyt.out (text to binary converter)\n");
			system("./Encrpyt.out"); //Hiding text within audio needs text to first be converted to binary.
		
			printf("Running Audio_Stego.out \n");
		
			system("./Audio_Stego.out");
		}
		else if( 0 == strcmp(input, "4") ){ //User wants to convert images to different format
			printf("Running file_handler.out\n");
			system("./file_handler.out");
		}
		else{
		printf("\nCommand not recognised.\n");
		}
        //system("./Encrpyt.out"); //text and hex to binary
        //system("./textSteg.out");
        }
        
    return 0;
}

//Ideas- use fork() and wait() to actually launch the other .c programs from here? Need to to this in sequential order for some things, since if I'm wanting to hide a
//text file, it would be best to ask if I want to encrypt it further first, and then ask how I want to hide this.