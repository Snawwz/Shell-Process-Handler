/*************************************************************** 
  Team:     Team06
  Members:  Hagar, Bryce
            Ramirez, Ruben 
  File Name: compute.c
  Assignment number: Project 1 Part 2
  Notes: Read "readme.txt" for notes on project.

  This project was created by the sole efforts of the team members listed above. The team possesses a single Linux computer environment which was used for the entirety of the project for ease of compiling & debugging. Our team github repo will reflect that the vast majority of the content was pushed from the Ubuntu- Linux distro. 
***************************************************************/
#include "compute.h"

// Function calls all other functions in compute.c to create child processes for distrubted computing solutions //
void launchShellProgram(shellParam *SP){
    int i=1, processNumber=1, j;
    char *argVect[MAXARGS];
    pid_t pidHolder[MAX_PROCESS];

    // Initializes elements of pidHolder to -1 //
    for(j=0;j<MAX_PROCESS;j++){
        pidHolder[j] = -1;
    }

    // fill argVect w arguments from user input//
    createArguments(SP, argVect);

    // reformat argument vector for proper forking //
    i = reformatArguments(argVect, i, &processNumber);

    // check to make sure (# of Processes) <= 10 //
    if(processNumber > MAX_PROCESS){
        printf("\nshell cannot create more than 10 processes.\n");
        garbageDestroy(argVect);
        return;
    }

    // print error if user entered a '0' or letters at argVect[1] //
    if(processNumber == 0){
        printErrorNote();
    }

    // divide & conquor with fork //
    createChildProcesses(SP, argVect, i, pidHolder);

    // wait for all children processes to die //
    killAllZombies(processNumber, pidHolder);

    // garbage collect //
    garbageDestroy(argVect);    
}


// inserts a "0" at index argVect[2] and shifts-right all other elements //
void createArguments(shellParam *SP, char **argVect){
    int j;
    // If user inputted 3 arguments //
    if(SP->argumentCount == 3){
        for(j=0;j<MAXARGS;j++){
            if(j==0 || SP->argumentVector[j-1] != NULL){
                if(j==2){
                    argVect[j] = strdup("0");
                }
                else if(j==3){
                    argVect[j] = strdup(SP->argumentVector[j-1]);
                }
                else{
                    argVect[j] = strdup(SP->argumentVector[j]);
                }
            }
            else{
                argVect[j] = NULL;
            }
        }
    }
    // If user inputted anything but 3 arguments //
    else{
        for(j=0;j<MAXARGS;j++){
            if(SP->argumentVector[j] != NULL){
                argVect[j] = strdup(SP->argumentVector[j]);
                }
            else{
                argVect[j] = NULL;
            }
        }
    }
}


// prepare argument vector for forking //
int reformatArguments(char **argVect, int i, int *processNumber){
    // converts string to integer if argVect[1] != NULL //
    if(argVect[1] != NULL){
        i = atoi(argVect[1]);
        *processNumber = i;
    }
    // initialize index to 0 //
    if(argVect[2] != NULL){
        sprintf(argVect[2],"0");
    }
    return i;
}


// print error note //
void printErrorNote(void){
    printf("\nshell please use correct syntax: \n");
    printf(">>> <[file_name] [process_number] [value_number]>\n");
    printf("                         ^\n");
    printf("                         |\n");
    printf("             OOPS        |       OOPS\n");
    printf("      /------------------------------------\\ \n");
    printf("      | Must be an integer(i):  0 < i < 11 |\n");
    printf("      |____________________________________|\n\n");
}


// divide & conquor with fork //
void createChildProcesses(shellParam *SP, char **argVect,int processNumber, pid_t *pidHolder){
    pid_t pid;
    int index = 0;
    while(processNumber){
        processNumber--;
        pid = fork();
        // child process //
        if (pid == 0){
            checkRedirect(SP,argVect,index);
            // Updates argVect[2] with index && checks for redirect //
            checkRedirect(SP,argVect,index);
            if (execvp(argVect[0], argVect) == -1) {
                perror("shell");
            }
            exit(EXIT_FAILURE);
        }
        // error forking //
        else if (pid < 0) {
            perror("shell");
            } 
        // store parent PID //
        else{
            	pidHolder[index] = pid;
        }
       index++;
    }
} 


// check for redirect & also updates argVect[2]//
void checkRedirect(shellParam *SP, char **argVect, int index){
    if(argVect[2] != NULL){// Allows standard 1-word shell programs to run such as 'ls'
        sprintf(argVect[2],"%d", index);
    }
    // Check for input redirect //
    if(SP->inputRedirect != NULL){
        FILE *fip = freopen(SP->inputRedirect, "r", stdin);
        UNUSED(fip);// macro to remove unused variable gcc warning //
    }

    // Check for output redirect //
    if(SP->outputRedirect != NULL){
        if (index == 0){// Remove file if it already exists
            if(access(SP->outputRedirect, F_OK)!= -1){
                remove(SP->outputRedirect);
            }
        }
        FILE *fop = freopen(SP->outputRedirect, "a", stdout);
        UNUSED(fop);// macro to remove unused variable gcc warning //
    }
}


// Kill all potential zombie children! // 
void killAllZombies(pid_t processNumber,pid_t *pidHolder){
    int j;
    pid_t wpid;

    while(processNumber){
        for(j=0;j<MAX_PROCESS;j++){
            if(pidHolder[j]!=-1){
                wpid = waitpid(pidHolder[j], NULL, WNOHANG);
            }
            if(wpid == pidHolder[j]){
                pidHolder[j] = -1;
                processNumber--;
            }
        }
    }
}


// Garbage Collect //
void garbageDestroy(char *argVect[]){
    int i;
    for (i=MAXARGS-1;i>=0;i--){
        if (argVect[i] != NULL){
            free(argVect[i]);
        }
    }
}


