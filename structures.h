/*************************************************************** 
  Team:     Team06
  Members:  Hagar, Bryce
            Ramirez, Ruben  
  File Name: structures.h
  Assignment number: Project 1 
  Notes: Read "readme.txt" for notes on project.

  This project was created by the sole efforts of the team members listed above. The team possesses a single Linux computer environment which was used for the entirety of the project for ease of compiling & debugging. Our team github repo will reflect that the vast majority of the content was pushed from the Ubuntu- Linux distro. 
***************************************************************/

#ifndef structures
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <sys/wait.h>
    #include <unistd.h>
    #define STRNG_BUFSIZE 1024
    #define MAX_PROCESS 10
    #define MAXARGS 32
    #define MAXTOKSIZE 128
    #define TOK_DELIM " <>"
    #define EXIT_LOOP 7
    #define INVALID_INPUT 14
    #define structures
    #define UNUSED(expr) do { (void)(expr); } while (0)


//*** Struct Definitions ***//

    // Structure to hold parsed input data //
    struct PARAM{
        char *inputRedirect;           /* file name or NULL */
        char *outputRedirect;          /* file name or NULL */
        int  argumentCount;            /* number of tokens in argument vector */
        char *argumentVector[MAXARGS]; /* array of strings */
    }; typedef struct PARAM shellParam;

#endif