/*************************************************************** 
  Team:    Team06
  Members:  Hagar, Bryce
            Ramirez, Ruben 
  File Name: compute.h
  Assignment number: Project 1 Part 2
  Notes: Read "readme.txt" for notes on project.

  This project was created by the sole efforts of the team members listed above. The team possesses a single Linux computer environment which was used for the entirety of the project for ease of compiling & debugging. Our team github repo will reflect that the vast majority of the content was pushed from the Ubuntu- Linux distro. 
***************************************************************/
#ifndef compute
  #include "structures.h"

//******* Function Prototypes *******//

// Function calls all other functions in compute.c to create child processes for distrubted computing solutions //
void launchShellProgram(shellParam *SP);

// Inserts a "0" at index argVect[2] and shifts-right all other elements //
void createArguments(shellParam *SP, char **argVect);

// prepare argument vector for forking //
int reformatArguments(char **argVect, int i, int *processNumber);

// print error note //
void printErrorNote(void);

// divide & conquor with fork //
void createChildProcesses(shellParam *SP, char **argVect,int processNumber, pid_t *pidHolder);

// check for redirect //
void checkRedirect(shellParam *SP, char **argVect, int index);

// Kill all potential zombie children! // 
void killAllZombies(pid_t processNumber,pid_t *pidHolder);

// Garbage Collect //
void garbageDestroy(char *argVect[]);

#endif
