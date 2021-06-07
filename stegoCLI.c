    //get user input as to what exactly they want to do with this program
    //check if program executables have been created- if not, use system() to gcc *all* the .c files into .out files with the same name (one time(?) run)
    //use exec(), execv() or execve() {?} to execute the programs that want to be used (scrapped, used system() instead.)

#include <stdio.h>
#include <sys/types.h>                              //These two --
#include <unistd.h>                                 //--Are for forking and waiting. Maybe remove?
#include <stdlib.h>                                 //For system(), to use gcc to compile all files
#include <string.h>                                 //For strcmp, to check user input against possible cases
#include <unistd.h>

void check_permissions(void){                       //Check if programs will be able to write to, and create files.

    char filepath[128];
    getcwd(filepath,sizeof(filepath));
    printf("Directory this program was run from is %s\n", filepath);
    
    int returnval = access(filepath, W_OK);         //using access() to check if we have permissions for this directory. OK returns 0, anything else means we do not.
    if (returnval ==0){
        printf("This program has write permissions.\n");
    }
    else{
        printf("This program does not have execute permissions.\n");
    }

    returnval = access(filepath, R_OK);
    if (returnval == 0){
        printf("This program has read permissions.\n");
    }
    else{
        printf("This program does not have execute permissions.\n");
    }

    returnval = access(filepath, X_OK);
    if (returnval == 0){
        printf("This program has execute permissions.\n");
    }
    else{
        printf("This program does not have execute permissions.\n");
    }
}

void ask_encrypt(void){
    int i=0;
    char encrypt_yn[32];
    while(i!=1){
            printf("Do you want to encrypt your text file first?\n");
                fgets(encrypt_yn, 32, stdin);                                   //get user input from terminal and place it into 'input' variable
                encrypt_yn[strcspn(encrypt_yn, "\n")] = 0;
                encrypt_yn[strcspn(encrypt_yn, "\0")] = 0;
                //printf("%s", encrypt_yn);                                     Debugging
                if(*encrypt_yn =='y'){                                          //Note- '' are critical here, versus "".
                    printf("Running Encrpyt.out (text to binary converter)\n");
                    system("./Encrpyt.out"); 
                    i=1;
                }
                else if(*encrypt_yn =='n'){
                    i=1;
                }
                else{
                    printf("\nUnknown response.\n");
                }    
    }

    return;
}

int main(){
    printf("First, checking if the program has write permissions in the current directory. Without them, you cannot create or edit files.\n");
    check_permissions();
    char input[32];

    printf("\nThis is Group D's Steganography program.\n");
    while(1){                                                                   //Loops program, as after system() is called, and the external function has run, it returns to this program.
        printf("Type the appropriate number for what you want to do.\n");
        printf("1: Encrypt/Decrypt a text file, by hiding a message within another text file. \n2: Hide a text file within a .BMP image.\n3: Hide a text file within a .wav audio file.\n\n");
    
        fgets(input, 32, stdin);                                                //get user input from terminal and place it into 'input' variable
        input[strcspn(input, "\n")] = 0;                                        //remove the newline that fgets takes at the end of user input, if it can fit. Otherwise, does nothing if there is no newline character. https://stackoverflow.com/questions/41252808/string-compare-in-c-with-fgets
        //fork(); //fork() does *not* work on windows machines. 
        
	    /* Check if executable files have already been compiled with gcc */
        if( access( "Audio_Stego.out", F_OK ) == 0 ) {                          //Check if the first executable alphabetically exists. Replace with counting how many .out files there are? Unsure how to check if all unique .out files exist.
        
	    } 
        else {
        //first executable does not exist, either due to not being run previously or been deleted
        printf("First executable not found, (re)compiling all executables.\n");
        system("gcc -o Audio_Stego.out Audio_Stego.c \n ");                     //Compile files. A newline is needed at the end of all of these, otherwise some may be skipped before the next system() is called.
        system("gcc -o Encrpyt.out Encrpyt.c \n");
        system("gcc file_handler.c steg_functions.c -o file_handler.out -lm  \n");
        system("gcc -o textSteg.out textSteg.c \n");
        
	    }
		/* Compare user input to known commands. I'd do cases here, but I was already using char[] by the time I realised switch cases only work with integers. */
		if( 0 == strcmp(input, "1") ){                                          //User wants to encrypt text
			printf("Running textSteg.out \n");                                  //Interestingly, without the \n, system() would run first.
    		
    		system("./textSteg.out");
		}
		else if( 0 == strcmp(input, "2") ){                                     //User wants to hide text within BMP image
			
            ask_encrypt();
            
            printf("Running file_handler.out\n");                               //Currently fails to compile this.
			system("./file_handler.out");
		}
		else if( 0 == strcmp(input, "3") ){                                     //User wants to hide text within Audio file
			printf("Running Encrpyt.out (text to binary converter)\n");
			system("./Encrpyt.out");                                            //Hiding text within audio needs text to first be converted to binary.
    
			printf("Running Audio_Stego.out \n");
		
			system("./Audio_Stego.out");
		}
		/*else if( 0 == strcmp(input, "4") ){                                     
			
		}*/
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