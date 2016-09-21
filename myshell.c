/*************************************************************** 
  Team:     Team06
  Members:  Hagar, Bryce
            Ramirez, Ruben  
  File Name: myshell.c
  Assignment number: Project 1
  Notes: Read "readme.txt" for notes on project.
  
  This project was created by the sole efforts of the team members listed above. The team possesses a single Linux computer environment which was used for the entirety of the project for ease of compiling & debugging. Our team github repo will reflect that the vast majority of the content was pushed from the Ubuntu- Linux distro. 
***************************************************************/

#include "parse.h"
#include "compute.h"


int main(int argc, char **argv)
{
    int errorFlag, i, debugFlag = 0;

    // Check for -Debug option //
    if(argc > 1){
        for(i=1;i<argc;i++){
            if (strcmp(argv[i],"-Debug") == 0){
                debugFlag = 1;
            }
        }
    }

    // Run the shell loop //
    do{
        do{
            /*---------------Initialize struct---------------*/
            shellParam *SP = malloc(sizeof(shellParam));     //
            char *line = malloc (sizeof(char)*STRNG_BUFSIZE);//
            initStruct(SP);                                  //
            errorFlag = 0;                                   //
            /*_______________________________________________*/
            /* ---------ProjectPart1: Run shellLoop----------*/
            errorFlag = shellLoop(SP, debugFlag,line);       //
                        /*Check for invalid input*/          //
                if (errorFlag == INVALID_INPUT){             //
                    checkFlag(errorFlag,line,SP);            //
                    break;                                   //
                }                                            //
                           /*Check for exit*/                // 
                if (errorFlag == EXIT_LOOP){                 //
                    checkFlag(errorFlag,line,SP);            //
                    return 0;                                //
                }                                            // 
            /*_______________________________________________*/    

            /*-------------ProjectPart2: Execute-------------*/
            launchShellProgram(SP);                          //
            /*_______________________________________________*/

            /*---------------Garbage collection--------------*/
            garbageCollect(SP,line);                         //
            /*_______________________________________________*/

        }while(1);
    }while(1);
    return 0;
}





















